/**
 * @file    usb_init.h
 * @brief   USB FS peripheral initialization for CANable2-N32 (gs_usb)
 */

#ifndef __USB_INIT_H
#define __USB_INIT_H

/**
 * @brief  Bring up the USB FS peripheral: 48 MHz clock, PA11/PA12 AF10,
 *         NVIC + EXTI wakeup, and the USB device core (descriptors are
 *         registered by usb_prop.c).
 */
void usb_init(void);

#endif /* __USB_INIT_H */
