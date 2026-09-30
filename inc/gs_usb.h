/**
 * @file    gs_usb.h
 * @brief   gs_usb (candleLight) protocol definitions for CANable2-N32
 *
 * Protocol definitions derived from the candleLight_fw project (MIT License,
 * Copyright (c) 2016 Hubert Denkmair) and the Linux kernel gs_usb driver.
 *
 * This is the authoritative wire format: do NOT reorder struct fields or
 * change the pack/alignment, or the host driver will reject the device.
 */

#ifndef __GS_USB_H
#define __GS_USB_H

#include <stdint.h>
#include "can.h"

/* ==========================================================================
 *  Endpoint addresses (must match usb_desc.c)
 * ========================================================================== */
#define GSUSB_ENDPOINT_IN       0x81    /* device -> host, Bulk */
#define GSUSB_ENDPOINT_OUT      0x02    /* host -> device, Bulk */

/* Endpoint max packet size (USB FS bulk = 64) */
#define CAN_DATA_MAX_PACKET_SIZE 64

/* gs_host_frame header size (echo_id, can_id, dlc, channel, flags, reserved) */
#define GS_FRAME_HEADER_SIZE    12

/* Largest gs_host_frame we model: header + 64 FD data + 4 timestamp = 80.
 * (Classic frames are 20 bytes; FD frames are 76 bytes without timestamp.) */
#define GS_HOST_FRAME_SIZE      (GS_FRAME_HEADER_SIZE + 64 + 4)

/* ==========================================================================
 *  Feature bits (gs_device_bt_const.feature / gs_device_mode.feature)
 * ========================================================================== */
#define GS_CAN_FEATURE_LISTEN_ONLY              (1 << 0)
#define GS_CAN_FEATURE_LOOP_BACK                (1 << 1)
#define GS_CAN_FEATURE_TRIPLE_SAMPLE            (1 << 2)
#define GS_CAN_FEATURE_ONE_SHOT                 (1 << 3)
#define GS_CAN_FEATURE_HW_TIMESTAMP             (1 << 4)
#define GS_CAN_FEATURE_IDENTIFY                 (1 << 5)
#define GS_CAN_FEATURE_USER_ID                  (1 << 6)
#define GS_CAN_FEATURE_PAD_PKTS_TO_MAX_PKT_SIZE (1 << 7)
#define GS_CAN_FEATURE_FD                       (1 << 8)
#define GS_CAN_FEATURE_REQ_USB_QUIRK_LPC546XX   (1 << 9)
#define GS_CAN_FEATURE_BT_CONST_EXT             (1 << 10)
#define GS_CAN_FEATURE_TERMINATION              (1 << 11)
#define GS_CAN_FEATURE_BERR_REPORTING           (1 << 12)
#define GS_CAN_FEATURE_GET_STATE                (1 << 13)
#define GS_CAN_FEATURE_ELM_PROTOCOL             (1 << 14)
#define GS_CAN_FEATURE_FILTER                   (1 << 16)
#define GS_CAN_FEATURE_TDC                      (1 << 17)
#define GS_CAN_FEATURE_BUS_OFF_RECOVERY         (1 << 18)

/* ==========================================================================
 *  gs_host_frame.flags
 * ========================================================================== */
#define GS_CAN_FLAG_OVERFLOW     (1 << 0)
#define GS_CAN_FLAG_FD           (1 << 1)   /* is a CAN-FD frame */
#define GS_CAN_FLAG_BRS          (1 << 2)   /* bit rate switch (FD only) */
#define GS_CAN_FLAG_ESI          (1 << 3)   /* error state indicator (FD only) */

/* ==========================================================================
 *  gs_host_frame.can_id flag bits
 * ========================================================================== */
#define CAN_EFF_FLAG             0x80000000U /* extended frame format */
#define CAN_RTR_FLAG             0x40000000U /* remote transmission request */
#define CAN_ERR_FLAG             0x20000000U /* error message frame */

/* echo_id value used by device for received (RX) frames */
#define GS_HOST_FRAME_ECHO_ID_RX 0xffffffffU

/* ==========================================================================
 *  Vendor control requests (bRequest)
 * ========================================================================== */
enum gs_usb_breq {
    GS_USB_BREQ_HOST_FORMAT = 0,
    GS_USB_BREQ_BITTIMING,
    GS_USB_BREQ_MODE,
    GS_USB_BREQ_BERR,
    GS_USB_BREQ_BT_CONST,
    GS_USB_BREQ_DEVICE_CONFIG,
    GS_USB_BREQ_TIMESTAMP,
    GS_USB_BREQ_IDENTIFY,
    GS_USB_BREQ_GET_USER_ID,
    GS_USB_BREQ_SET_USER_ID,
    GS_USB_BREQ_DATA_BITTIMING,
    GS_USB_BREQ_BT_CONST_EXT,
    GS_USB_BREQ_SET_TERMINATION,
    GS_USB_BREQ_GET_TERMINATION,
    GS_USB_BREQ_GET_STATE,
    GS_USB_BREQ_SET_FILTER,
    GS_USB_BREQ_GET_FILTER,
    GS_USB_BREQ_GET_TDC_CONST,
    GS_USB_BREQ_SET_TDC,
    GS_USB_BREQ_GET_TDC,
    GS_USB_BREQ_BUS_OFF_RECOVERY = 32,
};

/* ==========================================================================
 *  Channel modes / states
 * ========================================================================== */
enum gs_can_mode {
    GS_CAN_MODE_RESET = 0,      /* stop a channel */
    GS_CAN_MODE_START           /* start a channel */
};

enum gs_can_state {
    GS_CAN_STATE_ERROR_ACTIVE = 0,
    GS_CAN_STATE_ERROR_WARNING,
    GS_CAN_STATE_ERROR_PASSIVE,
    GS_CAN_STATE_BUS_OFF,
    GS_CAN_STATE_STOPPED,
    GS_CAN_STATE_SLEEPING
};

/* ==========================================================================
 *  Data types passed between host and device (packed, little-endian)
 * ========================================================================== */
#pragma pack(push, 1)

struct gs_host_config {
    uint32_t byte_order;
};

/* DEVICE_CONFIG: identifies the device to the host driver.
 * Layout is fixed by the kernel driver (4 + 4 + 4 = 12 bytes). */
struct gs_device_config {
    uint8_t  reserved1;
    uint8_t  reserved2;
    uint8_t  reserved3;
    uint8_t  icount;        /* number of channels - 1 */
    uint32_t sw_version;
    uint32_t hw_version;
};

struct gs_device_mode {
    uint32_t mode;
    uint32_t feature;
};

struct gs_device_state {
    uint32_t state;
    uint32_t rxerr;
    uint32_t txerr;
};

struct gs_device_bittiming {
    uint32_t prop_seg;
    uint32_t phase_seg1;
    uint32_t phase_seg2;
    uint32_t sjw;
    uint32_t brp;
};

struct can_bittiming_const {
    uint32_t tseg1_min;
    uint32_t tseg1_max;
    uint32_t tseg2_min;
    uint32_t tseg2_max;
    uint32_t sjw_max;
    uint32_t brp_min;
    uint32_t brp_max;
    uint32_t brp_inc;
};

struct gs_device_bt_const {
    uint32_t feature;
    uint32_t fclk_can;
    struct can_bittiming_const btc;
};

struct gs_device_bt_const_extended {
    uint32_t feature;
    uint32_t fclk_can;
    struct can_bittiming_const btc;
    struct can_bittiming_const dbtc;
};

struct gs_identify_mode {
    uint32_t mode;
};

struct gs_device_termination_state {
    uint32_t state;
};

/* Framing payloads (the flexible array element of gs_host_frame) */
struct classic_can {
    uint8_t data[8];
};

struct classic_can_ts {
    uint8_t data[8];
    uint32_t timestamp_us;
};

struct canfd {
    uint8_t data[64];
};

struct canfd_ts {
    uint8_t data[64];
    uint32_t timestamp_us;
};

/* --------------------------------------------------------------------------
 *  The central USB bulk frame structure.
 *
 *  Fixed header is 20 bytes. The trailing union is a flexible array whose
 *  interpretation depends on the frame type (classic vs FD, with/without TS).
 *  We model the maximum case inline (canfd_ts) so a single struct covers all.
 * -------------------------------------------------------------------------- */
struct gs_host_frame {
    uint32_t echo_id;
    uint32_t can_id;
    uint8_t  can_dlc;
    uint8_t  channel;
    uint8_t  flags;
    uint8_t  reserved;
    union {
        struct classic_can    classic_can;
        struct classic_can_ts classic_can_ts;
        struct canfd          canfd;
        struct canfd_ts       canfd_ts;
    };
};

#pragma pack(pop)

/* ==========================================================================
 *  Public API implemented by gs_usb.c
 * ========================================================================== */

/* Reset internal gs_usb state (called on USB reset / deinit). */
void gs_usb_reset(void);

/* Start handle for the vendor interface (called from SET_CONFIGURATION).
 * Opens EP1 IN / EP2 OUT and primes the first OUT receive. */
void gs_usb_start(void);

/* Main-loop hook: drains TX queue -> EP1 IN, and dispatches OUT frames. */
void gs_usb_process(void);

/* Called by the CAN layer when a frame is received from the bus.
 * Builds a gs_host_frame and queues it for the host. */
void gs_usb_send_frame(uint32_t can_id, uint8_t dlc, uint8_t flags,
                       uint8_t channel, const uint8_t *data, uint32_t len);

/* Convenience: queue a received N32 FDCAN frame to the host. */
void gs_usb_send_can_rx(const FDCAN_RxHeaderType *rx_header, const uint8_t *data);

/* Endpoint completion callbacks (wired up in usb_endp.c). */
void gs_usb_ep_in_cb(void);                       /* EP1 IN bulk TX complete */

/* Called by usb_endp.c when one USB packet arrives on EP2 OUT. The protocol
 * layer reassembles multi-packet CAN-FD frames (76 bytes = 64 + 12) before
 * dispatching to the CAN controller. */
void gs_usb_ep_out_packet(const uint8_t *data, uint32_t len);

/* Vendor control-request dispatch (called from usb_prop.c).
 * Returns 1 if handled, 0 if unsupported. */
int  gs_usb_setup_request(uint8_t bRequest, uint16_t wValue, uint8_t **data,
                          uint16_t *len);

/* Apply a host->device control payload previously received (usb_prop.c). */
void gs_usb_apply_control(uint8_t bRequest, const uint8_t *payload);

#endif /* __GS_USB_H */
