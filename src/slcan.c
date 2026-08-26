/**
 * @file    slcan.c
 * @brief   SLCAN protocol: parse CAN frames to/from ASCII strings
 * 
 * Adapted for N32H473. The N32 FDCAN header types use slightly different
 * field names than STM32 (e.g., .ID vs .Identifier, .FDFormat values same).
 */

#include "n32h47x_48x.h"
#include "n32h47x_48x_conf.h"
#include "can.h"
#include "error.h"
#include "slcan.h"
#include "system.h"
#include "usbd_cdc_if.h"


// Private variables
extern char* fw_id;  // defined in main.c

// Private method prototypes
static uint32_t __std_dlc_code_to_hal_dlc_code(uint8_t dlc_code);
static uint8_t __hal_dlc_code_to_std_dlc_code(uint32_t hal_dlc_code);


// Parse an incoming CAN frame into an outgoing slcan message
int32_t slcan_parse_frame(uint8_t *buf, FDCAN_RxHeaderType *frame_header, uint8_t *frame_data)
{
    // Clear buffer
    for (uint8_t j = 0; j < SLCAN_MTU; j++)
        buf[j] = '\0';

    // Start building the slcan message string at idx 0 in buf[]
    uint8_t msg_idx = 0;

    // Handle classic CAN frames
    if (frame_header->FDFormat == FDCAN_CLASSIC_CAN)
    {
        // Add character for frame type
        if (frame_header->RxFrameType == FDCAN_DATA_FRAME)
        {
            buf[msg_idx] = 't';
        }
        else if (frame_header->RxFrameType == FDCAN_REMOTE_FRAME)
        {
            buf[msg_idx] = 'r';
        }
    }
    // Handle FD CAN frames
    else
    {
        // FD doesn't support remote frames so this must be a data frame

        // Frame with BRS enabled
        if (frame_header->BitRateSwitch == FDCAN_BRS_ON)
        {
            buf[msg_idx] = 'b';
        }
        // Frame with BRS disabled
        else
        {
            buf[msg_idx] = 'd';
        }
    }

    // Assume standard identifier
    uint8_t id_len = SLCAN_STD_ID_LEN;
    uint32_t tmp = frame_header->ID;

    // Check if extended
    if (frame_header->IdType == FDCAN_EXTENDED_ID)
    {
        // Convert first char to upper case for extended frame
        buf[msg_idx] -= 32;
        id_len = SLCAN_EXT_ID_LEN;
    }
    msg_idx++;

    // Add identifier to buffer (hex nibbles)
    for (uint8_t j = id_len; j > 0; j--)
    {
        buf[j] = (tmp & 0xF);
        tmp = tmp >> 4;
        msg_idx++;
    }

    // Add DLC to buffer
    buf[msg_idx++] = __hal_dlc_code_to_std_dlc_code(frame_header->DataLength);
    int8_t bytes = hal_dlc_code_to_bytes(frame_header->DataLength);

    // Check bytes value
    if (bytes < 0) return -1;
    if (bytes > 64) return -1;

    // Add data bytes (hex encoded)
    for (uint8_t j = 0; j < bytes; j++)
    {
        buf[msg_idx++] = (frame_data[j] >> 4);
        buf[msg_idx++] = (frame_data[j] & 0x0F);
    }

    // Convert to ASCII (2nd character to end)
    for (uint8_t j = 1; j < msg_idx; j++)
    {
        if (buf[j] < 0xA) {
            buf[j] += 0x30;
        } else {
            buf[j] += 0x37;
        }
    }

    // Add carriage return
    buf[msg_idx++] = '\r';

    return msg_idx;
}


// Parse an incoming slcan command from the USB CDC port
int32_t slcan_parse_str(uint8_t *buf, uint8_t len)
{
    // Set default header. All values overridden below as needed.
    FDCAN_TxHeaderType frame_header = {
        .TxFrameType = FDCAN_DATA_FRAME,
        .FDFormat = FDCAN_CLASSIC_CAN,
        .IdType = FDCAN_STANDARD_ID,
        .BitRateSwitch = FDCAN_BRS_OFF,
        .ErrorState = FDCAN_ESI_ACTIVE,
        .TxEventFifo = FDCAN_NO_TX_EVENTS,
        .MsgMarker = 0,
    };
    uint8_t frame_data[64] = {0};

    // Convert from ASCII (2nd character to end) to raw nibble values
    for (uint8_t i = 1; i < len; i++)
    {
        if (buf[i] >= 'a')
            buf[i] = buf[i] - 'a' + 10;
        else if (buf[i] >= 'A')
            buf[i] = buf[i] - 'A' + 10;
        else
            buf[i] = buf[i] - '0';
    }

    // Handle each incoming command
    switch (buf[0])
    {
        // Open channel
        case 'O':
            can_enable();
            return 0;

        // Close channel
        case 'C':
            can_disable();
            return 0;

        // Set nominal bitrate
        case 'S':
            if (buf[1] >= CAN_BITRATE_INVALID)
                return -1;
            can_set_bitrate(buf[1]);
            return 0;

        // Set data bitrate (CAN FD)
        case 'Y':
            if (buf[1] == 2)
                can_set_data_bitrate(CAN_DATA_BITRATE_2M);
            else if (buf[1] == 5)
                can_set_data_bitrate(CAN_DATA_BITRATE_5M);
            else
                return -1;
            return 0;

        // Set mode (silent/normal)
        case 'M':
            if (buf[1] == 1)
                can_set_silent(1);
            else
                can_set_silent(0);
            return 0;

        // Set auto-retransmission
        case 'A':
            if (buf[1] == 1)
                can_set_autoretransmit(ENABLE);
            else
                can_set_autoretransmit(DISABLE);
            return 0;

        // Report firmware version
        case 'V':
        {
            extern char* fw_id;
            uint8_t len_id = 0;
            while (fw_id[len_id]) len_id++;
            cdc_transmit((uint8_t*)fw_id, len_id);
            return 0;
        }

        // Report error register
        case 'E':
        {
            char errstr[48] = "CANable Error: 0x";
            uint32_t err = error_reg();
            for (int8_t n = 7; n >= 0; n--) {
                uint8_t nybble = (err >> (n * 4)) & 0xF;
                errstr[17 + 7 - n] = nybble < 10 ? '0' + nybble : 'A' + nybble - 10;
            }
            errstr[25] = '\r';
            cdc_transmit((uint8_t*)errstr, 26);
            return 0;
        }

        // Transmit data frame (standard 11-bit ID)
        case 't':
            break;

        // Transmit data frame (extended 29-bit ID)
        case 'T':
            frame_header.IdType = FDCAN_EXTENDED_ID;
            break;

        // Transmit remote frame (standard ID)
        case 'r':
            frame_header.TxFrameType = FDCAN_REMOTE_FRAME;
            break;

        // Transmit remote frame (extended ID)
        case 'R':
            frame_header.IdType = FDCAN_EXTENDED_ID;
            frame_header.TxFrameType = FDCAN_REMOTE_FRAME;
            break;

        // CAN FD transmit - no BRS (standard ID)
        case 'd':
            frame_header.FDFormat = FDCAN_FD_CAN;
            break;

        // CAN FD transmit - no BRS (extended ID)
        case 'D':
            frame_header.FDFormat = FDCAN_FD_CAN;
            frame_header.IdType = FDCAN_EXTENDED_ID;
            break;

        // CAN FD transmit - with BRS (standard ID)
        case 'b':
            frame_header.FDFormat = FDCAN_FD_CAN;
            frame_header.BitRateSwitch = FDCAN_BRS_ON;
            break;

        // CAN FD transmit - with BRS (extended ID)
        case 'B':
            frame_header.FDFormat = FDCAN_FD_CAN;
            frame_header.BitRateSwitch = FDCAN_BRS_ON;
            frame_header.IdType = FDCAN_EXTENDED_ID;
            break;

        default:
            return -1;
    }

    // Start parsing at second byte (skip command byte)
    uint8_t parse_loc = 1;

    // Zero out identifier
    frame_header.ID = 0;

    // Default to standard ID length
    uint8_t id_len = SLCAN_STD_ID_LEN;
    if (frame_header.IdType == FDCAN_EXTENDED_ID)
        id_len = SLCAN_EXT_ID_LEN;

    // Parse ID nibbles
    while (parse_loc <= id_len)
    {
        frame_header.ID *= 16;
        frame_header.ID += buf[parse_loc++];
    }

    // Parse DLC (already a nibble value)
    uint8_t dlc_code_raw = buf[parse_loc++];

    // Validate DLC range
    if (frame_header.FDFormat == FDCAN_FD_CAN && dlc_code_raw > 0xF)
        return -1;
    if (frame_header.FDFormat == FDCAN_CLASSIC_CAN && dlc_code_raw > 0x8)
        return -1;

    // Convert DLC nibble to HAL DLC code
    frame_header.DataLength = __std_dlc_code_to_hal_dlc_code(dlc_code_raw);

    // Calculate expected data bytes
    int8_t bytes_in_msg = hal_dlc_code_to_bytes(frame_header.DataLength);
    if (bytes_in_msg < 0 || bytes_in_msg > 64)
        return -1;

    // Parse data nibbles into bytes
    for (uint8_t i = 0; i < bytes_in_msg; i++)
    {
        frame_data[i] = (buf[parse_loc] << 4) | buf[parse_loc + 1];
        parse_loc += 2;
    }

    // Queue frame for CAN transmission
    can_tx(&frame_header, frame_data);

    return parse_loc;
}


// Convert raw nibble DLC code (0-15) to N32 HAL DLC code
static uint32_t __std_dlc_code_to_hal_dlc_code(uint8_t dlc_code)
{
    if (dlc_code <= 8)
        return (uint32_t)(dlc_code << 16);  // 0-8 map directly to FDCAN DLC bytes
    else if (dlc_code == 9)
        return FDCAN_DLC_BYTES_12;
    else if (dlc_code == 10)
        return FDCAN_DLC_BYTES_16;
    else if (dlc_code == 11)
        return FDCAN_DLC_BYTES_20;
    else if (dlc_code == 12)
        return FDCAN_DLC_BYTES_24;
    else if (dlc_code == 13)
        return FDCAN_DLC_BYTES_32;
    else if (dlc_code == 14)
        return FDCAN_DLC_BYTES_48;
    else if (dlc_code == 15)
        return FDCAN_DLC_BYTES_64;
    else
        return FDCAN_DLC_BYTES_8;
}


// Convert N32 HAL DLC code to raw nibble value (0-15)
static uint8_t __hal_dlc_code_to_std_dlc_code(uint32_t hal_dlc_code)
{
    return hal_dlc_code >> 16;
}
