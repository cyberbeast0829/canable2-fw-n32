/**
 * @file    slcan.c
 * @brief   SLCAN protocol: parse CAN frames to/from ASCII strings
 * 
 * Adapted for N32H473. The N32 FDCAN header types use slightly different
 * field names than STM32 (e.g., .ID vs .Identifier, .FDFormat values same).
 */

#include "n32h47x_48x.h"
#include "n32h47x_48x_conf.h"
#include <string.h>
#include "can.h"
#include "error.h"
#include "slcan.h"
#include "system.h"


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

    // Add carriage return
    buf[msg_idx++] = '\r';

    return msg_idx;
}


// Parse an incoming slcan string into a CAN frame (for TX)
// Returns length of parsed data, or -1 on error
int32_t slcan_parse_str(uint8_t *buf, uint8_t len)
{
    if (len < 4) return -1;  // Minimum: t0000 (type + 3 hex id + CR)

    FDCAN_TxHeaderType tx_header;
    memset(&tx_header, 0, sizeof(tx_header));

    uint8_t data_idx = 0;
    uint8_t msg_idx = 0;

    // Determine frame type from first character
    switch (buf[0])
    {
        case 't':  // Standard CAN data frame
            tx_header.FDFormat = FDCAN_CLASSIC_CAN;
            tx_header.TxFrameType = FDCAN_DATA_FRAME;
            tx_header.IdType = FDCAN_STANDARD_ID;
            tx_header.BitRateSwitch = FDCAN_BRS_OFF;
            break;
        case 'T':  // Extended CAN data frame
            tx_header.FDFormat = FDCAN_CLASSIC_CAN;
            tx_header.TxFrameType = FDCAN_DATA_FRAME;
            tx_header.IdType = FDCAN_EXTENDED_ID;
            tx_header.BitRateSwitch = FDCAN_BRS_OFF;
            break;
        case 'r':  // Standard CAN remote frame
            tx_header.FDFormat = FDCAN_CLASSIC_CAN;
            tx_header.TxFrameType = FDCAN_REMOTE_FRAME;
            tx_header.IdType = FDCAN_STANDARD_ID;
            tx_header.BitRateSwitch = FDCAN_BRS_OFF;
            break;
        case 'R':  // Extended CAN remote frame
            tx_header.FDFormat = FDCAN_CLASSIC_CAN;
            tx_header.TxFrameType = FDCAN_REMOTE_FRAME;
            tx_header.IdType = FDCAN_EXTENDED_ID;
            tx_header.BitRateSwitch = FDCAN_BRS_OFF;
            break;
        case 'd':  // Standard CAN FD frame (no BRS)
            tx_header.FDFormat = FDCAN_FD_CAN;
            tx_header.TxFrameType = FDCAN_DATA_FRAME;
            tx_header.IdType = FDCAN_STANDARD_ID;
            tx_header.BitRateSwitch = FDCAN_BRS_OFF;
            break;
        case 'D':  // Extended CAN FD frame (no BRS)
            tx_header.FDFormat = FDCAN_FD_CAN;
            tx_header.TxFrameType = FDCAN_DATA_FRAME;
            tx_header.IdType = FDCAN_EXTENDED_ID;
            tx_header.BitRateSwitch = FDCAN_BRS_OFF;
            break;
        case 'b':  // Standard CAN FD frame (BRS)
            tx_header.FDFormat = FDCAN_FD_CAN;
            tx_header.TxFrameType = FDCAN_DATA_FRAME;
            tx_header.IdType = FDCAN_STANDARD_ID;
            tx_header.BitRateSwitch = FDCAN_BRS_ON;
            break;
        case 'B':  // Extended CAN FD frame (BRS)
            tx_header.FDFormat = FDCAN_FD_CAN;
            tx_header.TxFrameType = FDCAN_DATA_FRAME;
            tx_header.IdType = FDCAN_EXTENDED_ID;
            tx_header.BitRateSwitch = FDCAN_BRS_ON;
            break;
        default:
            return -1;  // Unknown frame type
    }

    msg_idx = 1;

    // Parse ID (hex digits)
    uint32_t id = 0;
    uint8_t id_len = (tx_header.IdType == FDCAN_EXTENDED_ID) ? 8 : 3;

    for (uint8_t i = 0; i < id_len; i++)
    {
        if (msg_idx >= len) return -1;
        uint8_t c = buf[msg_idx++];
        id <<= 4;
        if (c >= '0' && c <= '9')
            id |= (c - '0');
        else if (c >= 'A' && c <= 'F')
            id |= (c - 'A' + 10);
        else if (c >= 'a' && c <= 'f')
            id |= (c - 'a' + 10);
        else
            return -1;
    }
    tx_header.ID = id;

    // Parse DLC
    if (msg_idx >= len) return -1;
    uint8_t dlc_code = buf[msg_idx++];
    uint32_t hal_dlc = __std_dlc_code_to_hal_dlc_code(dlc_code);
    tx_header.DataLength = hal_dlc;
    uint32_t data_bytes = hal_dlc_code_to_bytes(hal_dlc);

    // Parse data bytes (hex encoded, 2 chars per byte)
    uint8_t tx_data[64];
    for (uint8_t i = 0; i < data_bytes; i++)
    {
        if (msg_idx + 1 >= len) return -1;
        uint8_t high = buf[msg_idx++];
        uint8_t low = buf[msg_idx++];
        uint8_t byte_val = 0;
        if (high >= '0' && high <= '9') byte_val = (high - '0') << 4;
        else if (high >= 'A' && high <= 'F') byte_val = (high - 'A' + 10) << 4;
        else if (high >= 'a' && high <= 'f') byte_val = (high - 'a' + 10) << 4;

        if (low >= '0' && low <= '9') byte_val |= (low - '0');
        else if (low >= 'A' && low <= 'F') byte_val |= (low - 'A' + 10);
        else if (low >= 'a' && low <= 'f') byte_val |= (low - 'a' + 10);

        tx_data[i] = byte_val;
    }

    // Send via CAN
    can_tx(&tx_header, tx_data);

    return msg_idx;
}


// Convert standard DLC code to N32 HAL DLC code
static uint32_t __std_dlc_code_to_hal_dlc_code(uint8_t dlc_code)
{
    if (dlc_code >= '0' && dlc_code <= '8')
        return (uint32_t)(dlc_code - '0');  // FDCAN_DLC_BYTES_0..8 map directly
    else if (dlc_code == '9')
        return FDCAN_DLC_BYTES_12;
    else if (dlc_code == 'A' || dlc_code == 'a')
        return FDCAN_DLC_BYTES_16;
    else if (dlc_code == 'B' || dlc_code == 'b')
        return FDCAN_DLC_BYTES_20;
    else if (dlc_code == 'C' || dlc_code == 'c')
        return FDCAN_DLC_BYTES_24;
    else if (dlc_code == 'D' || dlc_code == 'd')
        return FDCAN_DLC_BYTES_32;
    else if (dlc_code == 'E' || dlc_code == 'e')
        return FDCAN_DLC_BYTES_48;
    else if (dlc_code == 'F' || dlc_code == 'f')
        return FDCAN_DLC_BYTES_64;
    else
        return FDCAN_DLC_BYTES_8;  // default
}


// Convert N32 HAL DLC code to standard DLC character
static uint8_t __hal_dlc_code_to_std_dlc_code(uint32_t hal_dlc_code)
{
    switch (hal_dlc_code)
    {
        case FDCAN_DLC_BYTES_0:  return '0';
        case FDCAN_DLC_BYTES_1:  return '1';
        case FDCAN_DLC_BYTES_2:  return '2';
        case FDCAN_DLC_BYTES_3:  return '3';
        case FDCAN_DLC_BYTES_4:  return '4';
        case FDCAN_DLC_BYTES_5:  return '5';
        case FDCAN_DLC_BYTES_6:  return '6';
        case FDCAN_DLC_BYTES_7:  return '7';
        case FDCAN_DLC_BYTES_8:  return '8';
        case FDCAN_DLC_BYTES_12: return '9';
        case FDCAN_DLC_BYTES_16: return 'A';
        case FDCAN_DLC_BYTES_20: return 'B';
        case FDCAN_DLC_BYTES_24: return 'C';
        case FDCAN_DLC_BYTES_32: return 'D';
        case FDCAN_DLC_BYTES_48: return 'E';
        case FDCAN_DLC_BYTES_64: return 'F';
        default: return '8';
    }
}
