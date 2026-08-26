/**
 * @file    slcan.h
 * @brief   SLCAN protocol parser for CANable2-N32
 */

#ifndef _SLCAN_H
#define _SLCAN_H

#include <stdint.h>
#include "n32h47x_48x.h"

// Maximum rx buffer len
#define SLCAN_MTU        138 + 1 + 16  // canfd 64 frame plus \r plus padding
#define SLCAN_STD_ID_LEN 3
#define SLCAN_EXT_ID_LEN 8

// N32 HAL type aliases (N32 uses different struct names than STM32)
// These are already correct in the N32 HAL: FDCAN_TxHeaderType, FDCAN_RxHeaderType

// Prototypes
int32_t slcan_parse_frame(uint8_t *buf, FDCAN_RxHeaderType *frame_header, uint8_t *frame_data);
int32_t slcan_parse_str(uint8_t *buf, uint8_t len);
int8_t hal_dlc_code_to_bytes(uint32_t hal_dlc_code);

#endif // _SLCAN_H
