/**
 * @file    usbd_cdc_if.c
 * @brief   USB CDC interface implementation for N32H473
 * 
 * Implements a simple USB CDC ACM device for the CANable2.
 * Data flow:
 *   Host → USB OUT EP1 → rx_buffer → cdc_process() → SLCAN parser → CAN TX
 *   CAN RX → SLCAN frame → cdc_transmit() → tx_buffer → USB IN EP2 → Host
 */

#include "n32h47x_48x.h"
#include "n32h47x_48x_conf.h"
#include "usbfsd_lib.h"
#include "usb_conf.h"
#include "usbd_cdc_if.h"
#include "slcan.h"
#include "system.h"
#include "error.h"

// Private variables
static usbrx_buf_t rxbuf = {0};
static usbtx_buf_t txbuf = {0};
static uint8_t rx_packet_buf[CDC_DATA_FS_MAX_PACKET_SIZE];
static uint8_t tx_active = 0;


// Forward declarations
void USB_ProcessNop(void);


// USB device initialization
void usb_init(void)
{
    NVIC_InitType nvic;
    EXTI_InitType exti;
    GPIO_InitType gpio;

    // Configure USB clock: PLL output → /5 → 48MHz for USB FS
    RCC_ConfigUSBPLLPresClk(RCC_USBPLLCLK_SRC_PLL, RCC_USBPLLCLK_DIV5);
    RCC_ConfigUSBFSClk(RCC_USBFS_CLKSRC_PLLPRES);
    RCC->CFG3 |= RCC_CFG3_USBFSTM;

    // Enable USB clock
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_USBFS, ENABLE);

    // Enable AFIO and GPIO clocks
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
    RCC_EnableAHB1PeriphClk(RCC_AHB_PERIPHEN_GPIOA, ENABLE);

    // Configure USB pins: PA11=DM, PA12=DP, AF10
    GPIO_InitStruct(&gpio);
    gpio.Pin = GPIO_PIN_11 | GPIO_PIN_12;
    gpio.GPIO_Mode = GPIO_MODE_AF_PP;
    gpio.GPIO_Alternate = GPIO_AF10;
    gpio.GPIO_Pull = GPIO_NO_PULL;
    gpio.GPIO_Slew_Rate = GPIO_SLEW_RATE_FAST;
    gpio.GPIO_Current = GPIO_DC_12mA;
    GPIO_InitPeripheral(GPIOA, &gpio);

    // Enable USB LP interrupt
    nvic.NVIC_IRQChannel = USB_FS_LP_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 6;
    nvic.NVIC_IRQChannelSubPriority = 0;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);

    // Enable USB Wakeup interrupt
    nvic.NVIC_IRQChannel = USB_FS_WKUP_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 9;
    nvic.NVIC_IRQChannelSubPriority = 0;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);

    // Configure EXTI line 18 for USB wakeup
    EXTI_ClrITPendBit(EXTI_LINE18);
    exti.EXTI_Line = EXTI_LINE18;
    exti.EXTI_Mode = EXTI_Mode_Interrupt;
    exti.EXTI_Trigger = EXTI_Trigger_Rising;
    exti.EXTI_LineCmd = ENABLE;
    EXTI_InitPeripheral(&exti);

    // Initialize RX/TX buffers
    rxbuf.head = 0;
    rxbuf.tail = 0;
    txbuf.head = 0;
    txbuf.tail = 0;
    tx_active = 0;

    // Initialize USB core
    USB_Init();

    // Prepare first RX on EP1 OUT (endpoint address = 0x01 for EP1 OUT)
    // The N32 USB library reads directly from PMA in the OUT callback
}


// CDC process: check for received data and process TX
void cdc_process(void)
{
    // Process received data from USB
    while (rxbuf.tail != rxbuf.head)
    {
        uint8_t *msg = rxbuf.buf[rxbuf.tail];
        uint32_t len = rxbuf.msglen[rxbuf.tail];

        // Feed each byte through SLCAN parser (character by character)
        extern uint8_t slcan_str[];
        extern uint8_t slcan_str_index;

        for (uint32_t i = 0; i < len; i++)
        {
            if (msg[i] == '\r' || msg[i] == '\n')
            {
                if (slcan_str_index > 0)
                {
                    slcan_parse_str(slcan_str, slcan_str_index);
                    slcan_str_index = 0;
                }
            }
            else if (slcan_str_index < SLCAN_MTU - 1)
            {
                slcan_str[slcan_str_index++] = msg[i];
            }
        }

        rxbuf.tail = (rxbuf.tail + 1) % NUM_RX_BUFS;
    }

    // Process TX buffer - send data to USB if not busy
    if (!tx_active && txbuf.tail != txbuf.head)
    {
        uint32_t available;
        if (txbuf.head > txbuf.tail)
            available = txbuf.head - txbuf.tail;
        else
            available = USBTXQUEUE_LEN - txbuf.tail;

        if (available > CDC_DATA_FS_MAX_PACKET_SIZE)
            available = CDC_DATA_FS_MAX_PACKET_SIZE;

        if (available > 0)
        {
            // USB_SilWrite(endpoint_address, data, length)
            // EP2 IN: endpoint address = 0x82 (IN direction, EP2)
            USB_SilWrite(0x82, &txbuf.data[txbuf.tail], available);
            txbuf.tail = (txbuf.tail + available) % USBTXQUEUE_LEN;
            tx_active = 1;
        }
    }
}


// CDC transmit: queue data for sending via USB
void cdc_transmit(uint8_t *buf, uint16_t len)
{
    for (uint16_t i = 0; i < len; i++)
    {
        uint32_t next_head = (txbuf.head + 1) % USBTXQUEUE_LEN;
        if (next_head == txbuf.tail)
        {
            error_assert(ERR_FULLBUF_USBTX);
            break;
        }
        txbuf.data[txbuf.head] = buf[i];
        txbuf.head = next_head;
    }
}


// EP1 OUT callback - called when USB host sends data to us
void CDC_EP1_OUT_Callback(void)
{
    // Read received data from USB PMA using SIL layer
    // EP1 OUT: endpoint address = 0x01
    uint32_t len = USB_SilRead(0x01, rx_packet_buf);

    if (len > 0 && len <= CDC_DATA_FS_MAX_PACKET_SIZE)
    {
        uint32_t next_head = (rxbuf.head + 1) % NUM_RX_BUFS;
        if (next_head != rxbuf.tail)
        {
            for (uint32_t i = 0; i < len && i < RX_BUF_SIZE; i++)
            {
                rxbuf.buf[rxbuf.head][i] = rx_packet_buf[i];
            }
            rxbuf.msglen[rxbuf.head] = len;
            rxbuf.head = next_head;
        }
        else
        {
            error_assert(ERR_FULLBUF_USBRX);
        }
    }
}


