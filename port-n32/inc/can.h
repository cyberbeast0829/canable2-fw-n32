/**
 * @file    can.h
 * @brief   CAN/FDCAN interface for CANable2-N32
 */

#ifndef _CAN_H
#define _CAN_H

#include <stdint.h>
#include "n32h47x_48x.h"


// Classic CAN / CANFD nominal bitrates
enum can_bitrate {
    CAN_BITRATE_10K = 0,
    CAN_BITRATE_20K,
    CAN_BITRATE_50K,
    CAN_BITRATE_100K,
    CAN_BITRATE_125K,
    CAN_BITRATE_250K,
    CAN_BITRATE_500K,
    CAN_BITRATE_750K,
    CAN_BITRATE_1000K,
    CAN_BITRATE_83_3K,
    CAN_BITRATE_INVALID,
};


// CANFD data bitrates
enum can_data_bitrate {
    CAN_DATA_BITRATE_2M = 2,
    CAN_DATA_BITRATE_5M = 5,
    CAN_DATA_BITRATE_INVALID,
};


// Bus state
enum can_bus_state {
    OFF_BUS,
    ON_BUS
};


// CAN transmit buffering
#define TXQUEUE_LEN     64    // Number of buffers allocated
#define TXQUEUE_DATALEN 64    // CAN DLC length of data buffers (64 for CANFD)


// Cirbuf structure for CAN TX frames
typedef struct cantxbuf_ {
    uint8_t data[TXQUEUE_LEN][TXQUEUE_DATALEN];
    FDCAN_TxHeaderType header[TXQUEUE_LEN];
    uint16_t head;
    uint16_t tail;
    uint8_t full;
} can_txbuf_t;


// Prototypes
void can_init(void);
void can_enable(void);
void can_disable(void);
void can_set_bitrate(enum can_bitrate bitrate);
void can_set_data_bitrate(enum can_data_bitrate bitrate);
void can_set_silent(uint8_t silent);
void can_set_autoretransmit(uint8_t autoretransmit);
uint32_t can_tx(FDCAN_TxHeaderType *tx_msg_header, uint8_t *tx_msg_data);
uint32_t can_rx(FDCAN_RxHeaderType *rx_msg_header, uint8_t *rx_msg_data);
void can_process(void);
uint8_t is_can_msg_pending(uint8_t fifo);

#endif // _CAN_H
