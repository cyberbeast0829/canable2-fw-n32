/**
 * @file    gs_usb.c
 * @brief   gs_usb (candleLight) protocol + USB bulk transport for CANable2-N32
 *
 * Transport layer:
 *   - Dispatches vendor control requests from the host (bittiming, mode, ...)
 *   - Receives gs_host_frame on EP2 OUT (bulk) and forwards to the CAN layer
 *   - Queues CAN frames to EP1 IN (bulk) as gs_host_frame
 *
 * CAN mapping:
 *   control: gs_device_bittiming -> can_set_bitrate / can_set_data_bitrate
 *            GS_CAN_MODE_START / RESET -> can_enable / can_disable
 *   RX path: can_rx() -> gs_usb_send_frame() -> EP1 IN
 *   TX path: EP2 OUT -> gs_usb_ep_out_packet() -> can_tx()
 */

#include "n32h47x_48x.h"
#include "n32h47x_48x_conf.h"
#include <string.h>
#include "usbfsd_lib.h"
#include "usbfsd_mem.h"
#include "usb_conf.h"
#include "can.h"
#include "led.h"
#include "system.h"
#include "gs_usb.h"

/* ==========================================================================
 *  Configuration exposed to the host driver
 *
 *  N32 FDCAN clock: PLL /6 = 240 MHz /6 = 40 MHz (see can.c).
 *  The host driver computes bittiming from fclk_can, so this MUST match.
 * ========================================================================== */
#define GS_CAN_CLOCK_HZ   40000000u

static const struct gs_device_config gs_device_config = {
    .reserved1 = 0,
    .reserved2 = 0,
    .reserved3 = 0,
    .icount    = 0,     /* single channel */
    .sw_version = 2,
    .hw_version = 1,
};

/* Nominal bit timing constants (N32 FDCAN, 40 MHz). */
static const struct gs_device_bt_const gs_bt_const = {
    .feature   = GS_CAN_FEATURE_FD
               | GS_CAN_FEATURE_LISTEN_ONLY
               | GS_CAN_FEATURE_LOOP_BACK
               | GS_CAN_FEATURE_ONE_SHOT
               | GS_CAN_FEATURE_BT_CONST_EXT
               | GS_CAN_FEATURE_IDENTIFY,
    .fclk_can  = GS_CAN_CLOCK_HZ,
    .btc = {
        .tseg1_min = 1,
        .tseg1_max = 256,
        .tseg2_min = 1,
        .tseg2_max = 128,
        .sjw_max   = 128,
        .brp_min   = 1,
        .brp_max   = 1024,
        .brp_inc   = 1,
    },
};

/* Data-phase bit timing constants (CAN-FD) are embedded in gs_bt_const_ext. */

static const struct gs_device_bt_const_extended gs_bt_const_ext = {
    .feature   = GS_CAN_FEATURE_FD
               | GS_CAN_FEATURE_LISTEN_ONLY
               | GS_CAN_FEATURE_LOOP_BACK
               | GS_CAN_FEATURE_ONE_SHOT
               | GS_CAN_FEATURE_BT_CONST_EXT
               | GS_CAN_FEATURE_IDENTIFY,
    .fclk_can  = GS_CAN_CLOCK_HZ,
    .btc = {
        .tseg1_min = 1, .tseg1_max = 256,
        .tseg2_min = 1, .tseg2_max = 128,
        .sjw_max   = 128,
        .brp_min   = 1, .brp_max = 1024, .brp_inc = 1,
    },
    .dbtc = {
        .tseg1_min = 1, .tseg1_max = 32,
        .tseg2_min = 1, .tseg2_max = 16,
        .sjw_max   = 8,
        .brp_min   = 1, .brp_max = 32, .brp_inc = 1,
    },
};

/* ==========================================================================
 *  Internal state
 * ========================================================================== */
typedef enum { GS_MODE_OFF = 0, GS_MODE_ON } gs_mode_t;

static volatile gs_mode_t gs_mode = GS_MODE_OFF;
static volatile uint32_t  gs_feature = 0;

/* Latest bittiming received from host (kept for later CAN binding) */
static struct gs_device_bittiming gs_nominal_bt;
static struct gs_device_bittiming gs_data_bt;

/* Timestamp counter updated on SOF (ms -> us) */
static volatile uint32_t gs_timestamp_us = 0;

/* ---- TX queue: frames to be sent to the host on EP1 IN ---- */
#define GS_TX_QUEUE_LEN   32
static struct gs_host_frame gs_tx_queue[GS_TX_QUEUE_LEN];
static volatile uint16_t gs_tx_head = 0;   /* producer (CAN rx / echo) */
static volatile uint16_t gs_tx_tail = 0;   /* consumer (USB IN) */
static volatile uint8_t  gs_tx_active = 0; /* EP1 IN transfer in flight */

/* ---- RX staging: reassembles host frames arriving on EP2 OUT ----
 * A classic frame is a single 20-byte packet. A CAN-FD frame is 76 bytes,
 * which the FS endpoint delivers as two packets (64 + 12), so we must
 * accumulate across packets before handing the frame to the CAN controller. */
static struct gs_host_frame gs_rx_frame __attribute__((aligned(4)));
static uint32_t gs_rx_fill = 0;   /* bytes accumulated so far */

/* ==========================================================================
 *  DLC / length conversion helpers
 *
 *  gs_usb carries the raw DLC nibble (0..15) in gs_host_frame.can_dlc.
 *  The N32 FDCAN HAL encodes the length in bits [19:16] of DataLength.
 * ========================================================================== */
static inline uint32_t gs_dlc_to_hal(uint8_t dlc)
{
    if (dlc <= 8)
        return (uint32_t)dlc << 16;
    switch (dlc) {
        case 9:  return FDCAN_DLC_BYTES_12;
        case 10: return FDCAN_DLC_BYTES_16;
        case 11: return FDCAN_DLC_BYTES_20;
        case 12: return FDCAN_DLC_BYTES_24;
        case 13: return FDCAN_DLC_BYTES_32;
        case 14: return FDCAN_DLC_BYTES_48;
        default: return FDCAN_DLC_BYTES_64;   /* 15 */
    }
}

/* raw DLC nibble -> byte count */
static inline uint32_t gs_dlc_to_bytes(uint8_t dlc)
{
    static const uint8_t map[16] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 12, 16, 20, 24, 32, 48, 64
    };
    return (dlc < 16) ? map[dlc] : 64;
}


/* ==========================================================================
 *  Helpers
 * ========================================================================== */
static inline uint8_t gs_tx_empty(void)
{
    return gs_tx_head == gs_tx_tail;
}

/*
 * Length (bytes) of the gs_host_frame currently at the TX tail.
 *
 * The gs_usb frame header is 12 bytes:
 *     u32 echo_id; u32 can_id; u8 dlc; u8 ch; u8 flags; u8 reserved;
 * followed by the payload union (flexible array, data starts at offset 12).
 *
 * Linux gs_usb sizes RX/TX URBs from the payload type:
 *   classic_can  = u8 data[8]   -> total 12 + 8  = 20 bytes  (fixed)
 *   canfd        = u8 data[64]  -> total 12 + 64 = 76 bytes  (fixed)
 *
 * So the frame length is FIXED per frame type, NOT 12 + actual dlc bytes.
 * (Extra trailing bytes are harmless; a too-short frame truncates data.)
 */
#define GS_FRAME_LEN_CLASSIC   20u   /* 12 header + 8  data */
#define GS_FRAME_LEN_FD        76u   /* 12 header + 64 data */

static uint32_t gs_tx_frame_len(const struct gs_host_frame *f)
{
    if (f->flags & GS_CAN_FLAG_FD)
        return GS_FRAME_LEN_FD;
    return GS_FRAME_LEN_CLASSIC;
}

/*
 * Arm EP1 IN with the next chunk of the current tail frame.
 *
 * The N32 USB FS library performs one packet per SetEPTxValid, so a frame
 * larger than 64 bytes (i.e. CAN-FD with >44 data bytes) must be split into
 * multiple USB packets. The host reassembles a bulk transfer until it sees
 * a short (< 64 byte) packet, so we send 64-byte chunks followed by the
 * remainder. gs_tx_offset tracks progress within the current frame.
 */
static uint16_t gs_tx_offset = 0;

static void gs_usb_kick_tx(void)
{
    if (gs_tx_active || gs_tx_empty())
        return;

    struct gs_host_frame *f = &gs_tx_queue[gs_tx_tail];
    uint32_t total = gs_tx_frame_len(f);
    uint32_t remain = total - gs_tx_offset;
    uint32_t chunk = (remain > CAN_DATA_MAX_PACKET_SIZE)
                   ? CAN_DATA_MAX_PACKET_SIZE : remain;

    USB_CopyUserToPMABuf((uint8_t *)f + gs_tx_offset, ENDP1_TXADDR, chunk);
    USB_SetEpTxCnt(ENDP1, chunk);
    USB_SetEpTxValid(ENDP1);
    gs_tx_active = 1;
}

static int gs_tx_push(const struct gs_host_frame *f)
{
    uint16_t next = (gs_tx_head + 1) % GS_TX_QUEUE_LEN;
    if (next == gs_tx_tail)
        return 0;   /* queue full: drop */
    gs_tx_queue[gs_tx_head] = *f;
    gs_tx_head = next;
    return 1;
}

/* ==========================================================================
 *  Public API
 * ========================================================================== */
void gs_usb_reset(void)
{
    gs_mode        = GS_MODE_OFF;
    gs_feature     = 0;
    gs_tx_head     = 0;
    gs_tx_tail     = 0;
    gs_tx_active   = 0;
    gs_tx_offset   = 0;
    gs_timestamp_us = 0;

    can_disable();
}

void gs_usb_start(void)
{
    /* EP1 IN: Bulk, device -> host */
    USB_SetEpType(ENDP1, EP_BULK);
    USB_SetEpTxAddr(ENDP1, ENDP1_TXADDR);
    USB_SetEpRxAddr(ENDP1, 0);              /* EP1 has no RX side */
    SetEPTxStatus(ENDP1, EP_TX_NAK);
    SetEPRxStatus(ENDP1, EP_RX_DIS);

    /* EP2 OUT: Bulk, host -> device */
    USB_SetEpType(ENDP2, EP_BULK);
    USB_SetEpRxAddr(ENDP2, ENDP2_RXADDR);
    USB_SetEpRxCnt(ENDP2, CAN_DATA_MAX_PACKET_SIZE);
    SetEPRxStatus(ENDP2, EP_RX_VALID);
    SetEPTxStatus(ENDP2, EP_TX_DIS);        /* EP2 has no TX side */

    gs_tx_offset = 0;
}

void gs_usb_process(void)
{
    gs_usb_kick_tx();
}

/* Called from EP1 IN complete callback. */
void gs_usb_ep_in_cb(void)
{
    SetEPTxStatus(ENDP1, EP_TX_NAK);
    gs_tx_active = 0;

    if (gs_tx_empty())
        return;

    struct gs_host_frame *f = &gs_tx_queue[gs_tx_tail];
    gs_tx_offset += CAN_DATA_MAX_PACKET_SIZE;

    if (gs_tx_offset >= gs_tx_frame_len(f)) {
        /* Whole frame sent — advance to the next one. */
        gs_tx_offset = 0;
        gs_tx_tail = (gs_tx_tail + 1) % GS_TX_QUEUE_LEN;
    }

    gs_usb_kick_tx();
}

/*
 * Called from usb_endp.c for each USB packet arriving on EP2 OUT.
 *
 * Host -> Device direction. Reassembles the gs_host_frame (classic = 20 B in
 * one packet; CAN-FD = 76 B as 64 + 12) and queues it on the CAN controller.
 */
void gs_usb_ep_out_packet(const uint8_t *data, uint32_t len)
{
    if (len == 0 || len > CAN_DATA_MAX_PACKET_SIZE)
        return;   /* malformed packet */

    if (gs_rx_fill + len > sizeof(gs_rx_frame))
        gs_rx_fill = 0;   /* overflow guard: restart */

    memcpy((uint8_t *)&gs_rx_frame + gs_rx_fill, data, len);
    gs_rx_fill += len;

    /*
     * Frame is complete when:
     *  - the header is present and the frame is classic (short packet, 20 B), or
     *  - a full FD frame (76 B) has been assembled.
     */
    uint32_t expect;
    if (gs_rx_fill < GS_FRAME_HEADER_SIZE)
        return;   /* need more data to know the type */

    if (gs_rx_frame.flags & GS_CAN_FLAG_FD)
        expect = GS_FRAME_LEN_FD;
    else
        expect = GS_FRAME_LEN_CLASSIC;

    if (gs_rx_fill < expect)
        return;   /* wait for the remaining packets */

    /* Full frame available: dispatch to the CAN controller. */
    struct gs_host_frame *f = &gs_rx_frame;

    FDCAN_TxHeaderType hdr;
    memset(&hdr, 0, sizeof(hdr));

    /* Identifier + type */
    hdr.IdType = (f->can_id & CAN_EFF_FLAG) ? FDCAN_EXTENDED_ID
                                            : FDCAN_STANDARD_ID;
    hdr.ID     = f->can_id & 0x1FFFFFFF;

    /* Frame type: data vs remote */
    hdr.TxFrameType = (f->can_id & CAN_RTR_FLAG) ? FDCAN_REMOTE_FRAME
                                                 : FDCAN_DATA_FRAME;

    /* FD vs classic (BRS handled via BitRateSwitch) */
    if (f->flags & GS_CAN_FLAG_FD) {
        hdr.FDFormat      = FDCAN_FD_CAN;
        hdr.BitRateSwitch = (f->flags & GS_CAN_FLAG_BRS) ? FDCAN_BRS_ON
                                                         : FDCAN_BRS_OFF;
        hdr.ErrorState    = (f->flags & GS_CAN_FLAG_ESI) ? FDCAN_ESI_PASSIVE
                                                         : FDCAN_ESI_ACTIVE;
    } else {
        hdr.FDFormat      = FDCAN_CLASSIC_CAN;
        hdr.BitRateSwitch = FDCAN_BRS_OFF;
        hdr.ErrorState    = FDCAN_ESI_ACTIVE;
    }

    hdr.DataLength  = gs_dlc_to_hal(f->can_dlc);
    hdr.TxEventFifo = FDCAN_NO_TX_EVENTS;
    hdr.MsgMarker   = 0;

    can_tx(&hdr, f->canfd.data);

    /* Prepare for the next frame. */
    gs_rx_fill = 0;
}

void gs_usb_send_frame(uint32_t can_id, uint8_t dlc, uint8_t flags,
                       uint8_t channel, const uint8_t *data, uint32_t len)
{
    struct gs_host_frame f;
    f.echo_id  = GS_HOST_FRAME_ECHO_ID_RX;
    f.can_id   = can_id;
    f.can_dlc  = dlc;
    f.channel  = channel;
    f.flags    = flags;
    f.reserved = 0;

    /* Only the header + the DLC-relevant payload is transmitted; copy what
     * we have (bounded) and leave the rest undefined (never sent). */
    uint32_t copy = len;
    if (copy > 64)
        copy = 64;
    for (uint32_t i = 0; i < copy; i++)
        f.canfd_ts.data[i] = data[i];

    if (gs_tx_push(&f))
        gs_usb_kick_tx();
}

/* ==========================================================================
 *  Vendor control-request dispatch
 *
 *  Returns 1 if handled. For device-to-host requests, *data and *len are
 *  filled and the caller must send them; for host-to-device requests, the
 *  caller must arm an OUT data stage into its own buffer.
 * ========================================================================== */
int gs_usb_setup_request(uint8_t bRequest, uint16_t wValue, uint8_t **data,
                         uint16_t *len)
{
    uint8_t *src = NULL;
    uint16_t l = 0;

    switch (bRequest) {
        /* ---- Device -> Host ---- */
        case GS_USB_BREQ_BT_CONST:
            src = (uint8_t *)&gs_bt_const;
            l   = sizeof(gs_bt_const);
            break;
        case GS_USB_BREQ_BT_CONST_EXT:
            src = (uint8_t *)&gs_bt_const_ext;
            l   = sizeof(gs_bt_const_ext);
            break;
        case GS_USB_BREQ_DEVICE_CONFIG:
            src = (uint8_t *)&gs_device_config;
            l   = sizeof(gs_device_config);
            break;
        case GS_USB_BREQ_TIMESTAMP:
            src = (uint8_t *)&gs_timestamp_us;
            l   = sizeof(gs_timestamp_us);
            break;
        case GS_USB_BREQ_GET_STATE: {
            static struct gs_device_state st;
            st.state = (gs_mode == GS_MODE_ON) ? GS_CAN_STATE_ERROR_ACTIVE
                                               : GS_CAN_STATE_STOPPED;
            st.rxerr = 0;
            st.txerr = 0;
            src = (uint8_t *)&st;
            l   = sizeof(st);
            break;
        }

        /* ---- Host -> Device: caller provides the destination buffer ---- */
        case GS_USB_BREQ_HOST_FORMAT:
        case GS_USB_BREQ_BITTIMING:
        case GS_USB_BREQ_DATA_BITTIMING:
        case GS_USB_BREQ_MODE:
        case GS_USB_BREQ_IDENTIFY:
            src = NULL;             /* usb_prop.c supplies its own buffer */
            l   = 64;               /* max payload */
            break;

        default:
            return 0;   /* unsupported -> caller STALLs */
    }

    (void)wValue;
    if (data) *data = src;
    if (len)  *len  = l;
    return 1;
}

/* ==========================================================================
 *  Called after a host->device control OUT data stage has been received,
 *  to apply the requested change.
 * ========================================================================== */

/*
 * gs_device_bittiming -> nominal bitrate (bit/s).
 *   bitrate = fclk / (brp * (1 + prop_seg + phase_seg1 + phase_seg2))
 */
static uint32_t gs_nominal_bitrate(const struct gs_device_bittiming *bt)
{
    uint32_t brp = bt->brp ? bt->brp : 1;
    uint32_t tq  = 1 + bt->prop_seg + bt->phase_seg1 + bt->phase_seg2;
    if (tq == 0)
        tq = 1;
    return GS_CAN_CLOCK_HZ / (brp * tq);
}

/* Map a measured nominal bitrate to the closest N32 enum. */
static enum can_bitrate gs_bitrate_enum(uint32_t bps)
{
    static const struct { uint32_t bps; enum can_bitrate e; } tbl[] = {
        {   10000, CAN_BITRATE_10K    },
        {   20000, CAN_BITRATE_20K    },
        {   50000, CAN_BITRATE_50K    },
        {  100000, CAN_BITRATE_100K   },
        {  125000, CAN_BITRATE_125K   },
        {  250000, CAN_BITRATE_250K   },
        {  500000, CAN_BITRATE_500K   },
        {  750000, CAN_BITRATE_750K   },
        { 1000000, CAN_BITRATE_1000K  },
    };
    uint32_t best_d = 0xFFFFFFFFu;
    enum can_bitrate best = CAN_BITRATE_1000K;
    for (unsigned i = 0; i < sizeof(tbl) / sizeof(tbl[0]); i++) {
        uint32_t d = (bps > tbl[i].bps) ? (bps - tbl[i].bps)
                                        : (tbl[i].bps - bps);
        if (d < best_d) {
            best_d = d;
            best = tbl[i].e;
        }
    }
    return best;
}

/* ==========================================================================
 *  Vendor control-request application
 * ========================================================================== */
void gs_usb_apply_control(uint8_t bRequest, const uint8_t *payload)
{
    switch (bRequest) {
        case GS_USB_BREQ_BITTIMING: {
            gs_nominal_bt = *(const struct gs_device_bittiming *)payload;
            uint32_t bps = gs_nominal_bitrate(&gs_nominal_bt);
            can_set_bitrate(gs_bitrate_enum(bps));
            break;
        }

        case GS_USB_BREQ_DATA_BITTIMING: {
            gs_data_bt = *(const struct gs_device_bittiming *)payload;
            uint32_t brp = gs_data_bt.brp ? gs_data_bt.brp : 1;
            uint32_t tq  = 1 + gs_data_bt.prop_seg
                         + gs_data_bt.phase_seg1 + gs_data_bt.phase_seg2;
            if (tq == 0) tq = 1;
            uint32_t bps = GS_CAN_CLOCK_HZ / (brp * tq);
            can_set_data_bitrate((bps >= 3500000u) ? CAN_DATA_BITRATE_5M
                                                   : CAN_DATA_BITRATE_2M);
            break;
        }

        case GS_USB_BREQ_MODE: {
            const struct gs_device_mode *m = (const struct gs_device_mode *)payload;
            if (m->mode == GS_CAN_MODE_RESET) {
                can_disable();
                gs_mode    = GS_MODE_OFF;
                gs_feature = 0;
            } else if (m->mode == GS_CAN_MODE_START) {
                gs_feature = m->feature;
                /* Silent (listen-only) mode */
                can_set_silent((m->feature & GS_CAN_FEATURE_LISTEN_ONLY) ? 1 : 0);
                can_enable();
                gs_mode    = GS_MODE_ON;
            }
            break;
        }

        case GS_USB_BREQ_HOST_FORMAT:
            /* candleLight exchanges data in little-endian; ignore value. */
            break;

        case GS_USB_BREQ_IDENTIFY:
            /* No physical identify indicator wired up. */
            break;

        default:
            break;
    }
}

/*
 * Convert a received N32 FDCAN frame into a gs_host_frame and queue it for
 * the host. Called from the main loop after can_rx().
 */
void gs_usb_send_can_rx(const FDCAN_RxHeaderType *rx, const uint8_t *data)
{
    uint32_t can_id = rx->ID & 0x1FFFFFFF;

    if (rx->IdType == FDCAN_EXTENDED_ID)
        can_id |= CAN_EFF_FLAG;
    if (rx->RxFrameType == FDCAN_REMOTE_FRAME)
        can_id |= CAN_RTR_FLAG;

    uint8_t flags = 0;
    if (rx->FDFormat == FDCAN_FD_CAN) {
        flags |= GS_CAN_FLAG_FD;
        if (rx->BitRateSwitch == FDCAN_BRS_ON)
            flags |= GS_CAN_FLAG_BRS;
        if (rx->ErrorState == FDCAN_ESI_PASSIVE)
            flags |= GS_CAN_FLAG_ESI;
    }

    /* Raw DLC nibble is the top part of the HAL DataLength field. */
    uint8_t dlc = (uint8_t)(rx->DataLength >> 16);
    uint32_t nbytes = gs_dlc_to_bytes(dlc);

    gs_usb_send_frame(can_id, dlc, flags, 0 /* single channel */,
                      data, nbytes);
}
