/**
 * @file    main.c
 * @brief   CANable2 firmware main entry point (N32H473 port)
 *
 * USB-to-CAN bridge firmware implementing the gs_usb (candleLight) protocol.
 *   - Receives gs_host_frame packets via USB vendor bulk EP2 OUT -> CAN TX
 *   - Receives CAN/FDCAN frames and sends them as gs_host_frame via EP1 IN
 */

#include "n32h47x_48x.h"
#include "n32h47x_48x_conf.h"
#include "system.h"
#include "can.h"
#include "gs_usb.h"
#include "led.h"
#include "error.h"
#include "usb_init.h"


int main(void)
{
    // Initialize peripherals
    system_init();
    can_init();
    led_init();
    usb_init();

    // Power-on blink sequence
    led_blue_blink(2);

    // Storage for CAN RX message
    FDCAN_RxHeaderType rx_msg_header;
    uint8_t rx_msg_data[64] = {0};

    while (1)
    {
        led_process();
        can_process();
        gs_usb_process();

        // Check for received CAN messages
        if (is_can_msg_pending(FDCAN_RX_FIFO0))  // RX FIFO 0
        {
            // Read CAN frame
            if (can_rx(&rx_msg_header, rx_msg_data) == SUCCESS)
            {
                // Forward to host as a gs_host_frame (queued on EP1 IN)
                gs_usb_send_can_rx(&rx_msg_header, rx_msg_data);
            }
        }
    }
}
