/**
 * @file    usb_conf.h
 * @brief   USB Device configuration for CANable2-N32 (CDC ACM)
 *
 * Endpoint layout (matching ODrive verified config):
 *   EP0: Control (bidirectional)
 *   EP1: Bulk IN + OUT  — CDC data (64 bytes)
 *   EP2: Interrupt IN     — CDC notification (8 bytes)
 */

#ifndef __USB_CONF_H
#define __USB_CONF_H

/* Number of endpoints (excluding EP0) */
#define EP_NUM                      (4)

/* Buffer table base in USB packet memory (512 bytes total) */
#define BTABLE_ADDRESS              (0x00)

/* EP0 addresses (control: 64 bytes each direction) */
#define ENDP0_RXADDR                (0x40)
#define ENDP0_TXADDR                (0x80)

/* EP1 addresses — CDC Bulk (64 bytes each direction) */
#define ENDP1_RXADDR                (0xC0)
#define ENDP1_TXADDR                (0x110)

/* EP2 addresses — CDC Interrupt IN (8 bytes) */
#define ENDP2_TXADDR                (0x150)

/* Interrupt mask: Correct Transfer | Reset | Wakeup */
#define IMR_MSK (CTRL_CTRSM | CTRL_WKUPM | CTRL_RSTM)

/* CDC class-specific request codes (not provided by N32 USB library) */
#define SET_LINE_CODING         0x20
#define GET_LINE_CODING         0x21
#define SET_CONTROL_LINE_STATE  0x22
#define SET_COMM_FEATURE        0x02

/* Unused endpoint callbacks → library no-op (matching ODrive pattern) */
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
