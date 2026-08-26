/**
 * @file    usb_desc.c
 * @brief   USB Descriptors for CANable2-N32 (CDC ACM)
 *
 * VID/PID match original CANable2: 0x16D0 / 0x117E
 */

#include "usbfsd_lib.h"
#include "usb_desc.h"

/* USB Standard Device Descriptor */
const uint8_t Virtual_Com_Port_DeviceDescriptor[] =
{
    0x12,                       /* bLength */
    USB_DEVICE_DESCRIPTOR_TYPE, /* bDescriptorType */
    0x00, 0x02,                 /* bcdUSB = 2.00 */
    0x02,                       /* bDeviceClass: CDC */
    0x02,                       /* bDeviceSubClass */
    0x00,                       /* bDeviceProtocol */
    0x40,                       /* bMaxPacketSize0 = 64 */
    0xD0, 0x16,                 /* idVendor  = 0x16D0 (Openlight Labs) */
    0x7E, 0x11,                 /* idProduct = 0x117E (CANable2) */
    0x00, 0x02,                 /* bcdDevice = 2.00 */
    1,                          /* iManufacturer string index */
    2,                          /* iProduct string index */
    3,                          /* iSerialNumber string index */
    0x01                        /* bNumConfigurations */
};

/* USB Configuration + Interface + Endpoint Descriptors (CDC ACM)
 * Matches STM32 usbd_cdc.c USBD_CDC_CfgFSDesc exactly. */
const uint8_t Virtual_Com_Port_ConfigDescriptor[] =
{
    /* ---------- Configuration Descriptor ---------- */
    0x09,                                   /* bLength */
    USB_CONFIGURATION_DESCRIPTOR_TYPE,      /* bDescriptorType: Configuration */
    VIRTUAL_COM_PORT_SIZ_CONFIG_DESC,       /* wTotalLength (LSB) */
    0x00,                                   /* wTotalLength (MSB) */
    0x02,                                   /* bNumInterfaces: 2 */
    0x01,                                   /* bConfigurationValue */
    0x00,                                   /* iConfiguration */
    0x80,                                   /* bmAttributes: bus powered */
    0xFA,                                   /* bMaxPower: 500mA */

    /* ---------- Interface 0: Communication Class ---------- */
    0x09,                               /* bLength */
    USB_INTERFACE_DESCRIPTOR_TYPE,      /* bDescriptorType: Interface */
    0x00,                               /* bInterfaceNumber */
    0x00,                               /* bAlternateSetting */
    0x01,                               /* bNumEndpoints: 1 (interrupt IN) */
    0x02,                               /* bInterfaceClass: CDC Communication */
    0x02,                               /* bInterfaceSubClass: ACM */
    0x01,                               /* bInterfaceProtocol: AT commands */
    0x00,                               /* iInterface */

    /* Header Functional Descriptor */
    0x05,   /* bLength */
    0x24,   /* bDescriptorType: CS_INTERFACE */
    0x00,   /* bDescriptorSubtype: Header */
    0x10, 0x01,                         /* bcdCDC: 1.10 */

    /* Call Management Functional Descriptor */
    0x05,   /* bLength */
    0x24,   /* bDescriptorType: CS_INTERFACE */
    0x01,   /* bDescriptorSubtype: Call Management */
    0x00,   /* bmCapabilities */
    0x01,   /* bDataInterface: 1 */

    /* ACM Functional Descriptor */
    0x04,   /* bLength */
    0x24,   /* bDescriptorType: CS_INTERFACE */
    0x02,   /* bDescriptorSubtype: ACM */
    0x02,   /* bmCapabilities: line coding + serial state */

    /* Union Functional Descriptor */
    0x05,   /* bLength */
    0x24,   /* bDescriptorType: CS_INTERFACE */
    0x06,   /* bDescriptorSubtype: Union */
    0x00,   /* bMasterInterface: 0 (communication) */
    0x01,   /* bSlaveInterface:  1 (data) */

    /* Endpoint 2 IN (interrupt) */
    0x07,                               /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,       /* bDescriptorType: Endpoint */
    0x82,                               /* bEndpointAddress: EP2 IN */
    0x03,                               /* bmAttributes: Interrupt */
    VIRTUAL_COM_PORT_INT_SIZE, 0x00,    /* wMaxPacketSize: 8 */
    0x10,                               /* bInterval: 16ms */

    /* ---------- Interface 1: Data Class ---------- */
    0x09,                               /* bLength */
    USB_INTERFACE_DESCRIPTOR_TYPE,      /* bDescriptorType: Interface */
    0x01,                               /* bInterfaceNumber */
    0x00,                               /* bAlternateSetting */
    0x02,                               /* bNumEndpoints: 2 (Bulk IN/OUT) */
    0x0A,                               /* bInterfaceClass: CDC Data */
    0x00,                               /* bInterfaceSubClass */
    0x00,                               /* bInterfaceProtocol */
    0x00,                               /* iInterface */

    /* Endpoint 1 OUT (bulk, host -> device) */
    0x07,                               /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,       /* bDescriptorType: Endpoint */
    0x01,                               /* bEndpointAddress: EP1 OUT */
    0x02,                               /* bmAttributes: Bulk */
    VIRTUAL_COM_PORT_DATA_SIZE, 0x00,   /* wMaxPacketSize: 64 */
    0x00,                               /* bInterval (ignored for bulk) */

    /* Endpoint 1 IN (bulk, device -> host) */
    0x07,                               /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,       /* bDescriptorType: Endpoint */
    0x81,                               /* bEndpointAddress: EP1 IN */
    0x02,                               /* bmAttributes: Bulk */
    VIRTUAL_COM_PORT_DATA_SIZE, 0x00,   /* wMaxPacketSize: 64 */
    0x00,                               /* bInterval (ignored for bulk) */
};

/* ---------- String Descriptors ---------- */

const uint8_t Virtual_Com_Port_StringLangID[VIRTUAL_COM_PORT_SIZ_STRING_LANGID] =
{
    VIRTUAL_COM_PORT_SIZ_STRING_LANGID,
    USB_STRING_DESCRIPTOR_TYPE,
    0x09, 0x04     /* LangID = 0x0409: US English */
};

const uint8_t Virtual_Com_Port_StringVendor[VIRTUAL_COM_PORT_SIZ_STRING_VENDOR] =
{
    VIRTUAL_COM_PORT_SIZ_STRING_VENDOR,
    USB_STRING_DESCRIPTOR_TYPE,
    'C', 0, 'y', 0, 'b', 0, 'e', 0, 'r', 0, 'B', 0, 'e', 0, 'a', 0,
    's', 0, 't', 0
};

const uint8_t Virtual_Com_Port_StringProduct[VIRTUAL_COM_PORT_SIZ_STRING_PRODUCT] =
{
    VIRTUAL_COM_PORT_SIZ_STRING_PRODUCT,
    USB_STRING_DESCRIPTOR_TYPE,
    'C', 0, 'y', 0, 'b', 0, 'e', 0, 'r', 0, 'B', 0, 'e', 0, 'a', 0,
    's', 0, 't', 0, ' ', 0, 'U', 0, 'S', 0, 'B', 0, '2', 0, 'C', 0,
    'A', 0, 'N', 0
};

uint8_t Virtual_Com_Port_StringSerial[VIRTUAL_COM_PORT_SIZ_STRING_SERIAL] =
{
    VIRTUAL_COM_PORT_SIZ_STRING_SERIAL,
    USB_STRING_DESCRIPTOR_TYPE,
    'N', 0, '3', 0, '2', 0, 'H', 0, '4', 0, '7', 0, '3', 0, '-', 0,
    '0', 0, '0', 0, '0', 0, '1', 0,
};
