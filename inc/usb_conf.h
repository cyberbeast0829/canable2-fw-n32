/**
 * @file    usb_conf.h
 * @brief   USB Device configuration for CANable2-N32 (gs_usb vendor class)
 *
 * Endpoint layout:
 *   EP0: Control (bidirectional)
 *   EP1: Bulk IN        — CAN frames device -> host (64 bytes)
 *   EP2: Bulk OUT       — CAN frames host -> device (64 bytes)
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

/* EP1 address — Bulk IN (device -> host, 64 bytes).
 * Use the same PMA address the working CDC build used for EP1 TX. */
#define ENDP1_TXADDR                (0x110)

/* EP2 address — Bulk OUT (host -> device, 64 bytes).
 * Use the same PMA address the working CDC build used for EP2 (0x150). */
#define ENDP2_RXADDR                (0x150)

/* Interrupt mask: Correct Transfer | Reset | Wakeup */
#define IMR_MSK (CTRL_CTRSM | CTRL_WKUPM | CTRL_RSTM)

/* Unused endpoint callbacks → library no-op.
 *   EP1 is IN-only  (no EP1 OUT handler)
 *   EP2 is OUT-only (no EP2 IN handler) */
#define EP2_IN_Callback     USB_ProcessNop
#define EP1_OUT_Callback    USB_ProcessNop
#define EP3_IN_Callback     USB_ProcessNop
#define EP4_IN_Callback     USB_ProcessNop
#define EP5_IN_Callback     USB_ProcessNop
#define EP6_IN_Callback     USB_ProcessNop
#define EP7_IN_Callback     USB_ProcessNop

#define EP3_OUT_Callback    USB_ProcessNop
#define EP4_OUT_Callback    USB_ProcessNop
#define EP5_OUT_Callback    USB_ProcessNop
#define EP6_OUT_Callback    USB_ProcessNop
#define EP7_OUT_Callback    USB_ProcessNop

#endif /* __USB_CONF_H */
