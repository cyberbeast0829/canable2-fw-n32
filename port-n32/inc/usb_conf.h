/**
 * @file    usb_conf.h
 * @brief   USB Device configuration for CANable2-N32
 */

#ifndef __USB_CONF_H
#define __USB_CONF_H

// Number of endpoints
#define EP_NUM                      (4)

// Buffer table base address in USB packet memory
#define BTABLE_ADDRESS              (0x00)

// EP0 addresses (control endpoint)
#define ENDP0_RXADDR                (0x40)
#define ENDP0_TXADDR                (0x80)

// EP1 - CDC data OUT (host → device)
#define ENDP1_RXADDR                (0xC0)
#define ENDP1_TXADDR                (0x100)

// EP2 - CDC data IN (device → host)
#define ENDP2_TXADDR                (0x140)

// EP3 - CDC interrupt IN
#define ENDP3_TXADDR                (0x180)

// Interrupt mask
#define IMR_MSK (CTRL_CTRSM | CTRL_WKUPM | CTRL_RSTM)

// CDC endpoint numbers
#define CDC_DATA_EP_IN              2
#define CDC_DATA_EP_OUT             1
#define CDC_INT_EP_IN               3

// CDC data packet size
#define CDC_DATA_FS_MAX_PACKET_SIZE 64

// Callback definitions
#define EP1_OUT_Callback    CDC_EP1_OUT_Callback
#define EP2_IN_Callback     USB_ProcessNop
#define EP3_IN_Callback     USB_ProcessNop
#define EP4_IN_Callback     USB_ProcessNop
#define EP5_IN_Callback     USB_ProcessNop
#define EP6_IN_Callback     USB_ProcessNop
#define EP7_IN_Callback     USB_ProcessNop

#define EP2_OUT_Callback    USB_ProcessNop
#define EP3_OUT_Callback    USB_ProcessNop
#define EP4_OUT_Callback    USB_ProcessNop
#define EP5_OUT_Callback    USB_ProcessNop
#define EP6_OUT_Callback    USB_ProcessNop
#define EP7_OUT_Callback    USB_ProcessNop

#endif /* __USB_CONF_H */
