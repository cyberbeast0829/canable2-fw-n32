/**
 * @file    usb_desc.h
 * @brief   USB Descriptor definitions for CANable2-N32 (CDC ACM)
 */

#ifndef __USB_DESC_H
#define __USB_DESC_H

/* Descriptor types */
#define USB_DEVICE_DESCRIPTOR_TYPE              0x01
#define USB_CONFIGURATION_DESCRIPTOR_TYPE       0x02
#define USB_STRING_DESCRIPTOR_TYPE              0x03
#define USB_INTERFACE_DESCRIPTOR_TYPE           0x04
#define USB_ENDPOINT_DESCRIPTOR_TYPE            0x05

/* CDC data sizes */
#define VIRTUAL_COM_PORT_DATA_SIZE              64
#define VIRTUAL_COM_PORT_INT_SIZE               8

/* Descriptor sizes */
#define VIRTUAL_COM_PORT_SIZ_DEVICE_DESC        18
#define VIRTUAL_COM_PORT_SIZ_CONFIG_DESC        67
#define VIRTUAL_COM_PORT_SIZ_STRING_LANGID      4
#define VIRTUAL_COM_PORT_SIZ_STRING_VENDOR      22    /* "CyberBeast" = 10 chars * 2 + 2 */
#define VIRTUAL_COM_PORT_SIZ_STRING_PRODUCT     38    /* "CyberBeast USB2CAN" = 18 chars * 2 + 2 */
#define VIRTUAL_COM_PORT_SIZ_STRING_SERIAL      26    /* "N32H473-0001" = 12 chars * 2 + 2 */

extern const uint8_t Virtual_Com_Port_DeviceDescriptor[VIRTUAL_COM_PORT_SIZ_DEVICE_DESC];
extern const uint8_t Virtual_Com_Port_ConfigDescriptor[VIRTUAL_COM_PORT_SIZ_CONFIG_DESC];
extern const uint8_t Virtual_Com_Port_StringLangID[VIRTUAL_COM_PORT_SIZ_STRING_LANGID];
extern const uint8_t Virtual_Com_Port_StringVendor[VIRTUAL_COM_PORT_SIZ_STRING_VENDOR];
extern const uint8_t Virtual_Com_Port_StringProduct[VIRTUAL_COM_PORT_SIZ_STRING_PRODUCT];
extern uint8_t Virtual_Com_Port_StringSerial[VIRTUAL_COM_PORT_SIZ_STRING_SERIAL];

#endif /* __USB_DESC_H */
