/**
 * @file    usbd_cdc_if.h
 * @brief   USB CDC interface for CANable2-N32
 */

#ifndef __USBD_CDC_IF_H__
#define __USBD_CDC_IF_H__

#include <stdint.h>

// CDC data max packet size
#define CDC_DATA_FS_MAX_PACKET_SIZE   64

// RX buffering
#define NUM_RX_BUFS        8
#define RX_BUF_SIZE        CDC_DATA_FS_MAX_PACKET_SIZE

// TX buffering: circular buffer
#define USBTXQUEUE_LEN     2048

// Transmit buffering: circular buffer FIFO
typedef struct usbtxbuf_ {
    uint8_t data[USBTXQUEUE_LEN];
    uint32_t head;
    uint32_t tail;
} usbtx_buf_t;

// Receive buffering: circular buffer FIFO
typedef struct _usbrx_buf_ {
    uint8_t buf[NUM_RX_BUFS][RX_BUF_SIZE];
    uint32_t msglen[NUM_RX_BUFS];
    uint32_t head;
    uint32_t tail;
} usbrx_buf_t;

// USB initialization
void usb_init(void);

// CDC transmit function
void cdc_transmit(uint8_t *buf, uint16_t len);

// CDC process function (call in main loop)
void cdc_process(void);

// CDC endpoint OUT callback (called from USB ISR)
void CDC_EP1_OUT_Callback(void);

#endif
