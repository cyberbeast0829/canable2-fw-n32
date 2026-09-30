/**
 * @file    usb_desc.c
 * @brief   USB Descriptors for CANable2-N32 (gs_usb / candleLight)
 *
 * VID/PID match candleLight: 0x1d50:0x606f, so the Linux kernel gs_usb
 * driver binds automatically and Windows can use WinUSB via Zadig.
 *
 * USB topology (single vendor-specific interface):
 *   EP0     : Control
 *   EP1 IN  (0x81) Bulk  device -> host : CAN frames
 *   EP2 OUT (0x02) Bulk  host -> device : CAN frames
 */

#include "usbfsd_lib.h"
#include "usb_desc.h"
#include "gs_usb.h"

/* USB Standard Device Descriptor */
const uint8_t Virtual_Com_Port_DeviceDescriptor[] =
{
    0x12,                       /* bLength */
    USB_DEVICE_DESCRIPTOR_TYPE, /* bDescriptorType */
    0x00, 0x02,                 /* bcdUSB = 2.00 */
    0xFF,                       /* bDeviceClass: Vendor Specific */
    0x00,                       /* bDeviceSubClass */
    0x00,                       /* bDeviceProtocol */
    0x40,                       /* bMaxPacketSize0 = 64 */
    0x50, 0x1D,                 /* idVendor  = 0x1d50 (little-endian) */
    0x6F, 0x60,                 /* idProduct = 0x606f (little-endian) */
    0x00, 0x02,                 /* bcdDevice = 2.00 */
    1,                          /* iManufacturer string index */
    2,                          /* iProduct string index */
    3,                          /* iSerialNumber string index */
    0x01                        /* bNumConfigurations */
};

/* USB Configuration + Interface + Endpoint Descriptors (gs_usb vendor class)
 * Layout matches candleLight's USBD_GS_CAN_CfgDesc, minus the DFU interface:
 *   9  config
 *   9  interface 0 (vendor specific, 2 endpoints)
 *   7  EP1 IN  (bulk)
 *   7  EP2 OUT (bulk)
 * = 32 bytes
 */
const uint8_t Virtual_Com_Port_ConfigDescriptor[] =
{
    /* ---------- Configuration Descriptor ---------- */
    0x09,                                   /* bLength */
    USB_CONFIGURATION_DESCRIPTOR_TYPE,      /* bDescriptorType: Configuration */
    VIRTUAL_COM_PORT_SIZ_CONFIG_DESC,       /* wTotalLength (LSB) */
    0x00,                                   /* wTotalLength (MSB) */
    0x01,                                   /* bNumInterfaces: 1 */
    0x01,                                   /* bConfigurationValue */
    0x00,                                   /* iConfiguration */
    0x80,                                   /* bmAttributes: bus powered */
    0x32,                                   /* bMaxPower: 100mA */

    /* ---------- Interface 0: gs_usb vendor-specific ---------- */
    0x09,                               /* bLength */
    USB_INTERFACE_DESCRIPTOR_TYPE,      /* bDescriptorType: Interface */
    0x00,                               /* bInterfaceNumber */
    0x00,                               /* bAlternateSetting */
    0x02,                               /* bNumEndpoints: 2 (Bulk IN/OUT) */
    0xFF,                               /* bInterfaceClass: Vendor Specific */
    0xFF,                               /* bInterfaceSubClass: Vendor Specific */
    0xFF,                               /* bInterfaceProtocol: Vendor Specific */
    0x00,                               /* iInterface */

    /* ---------- Endpoint 1 IN (bulk, device -> host) ---------- */
    0x07,                               /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,       /* bDescriptorType: Endpoint */
    GSUSB_ENDPOINT_IN,                  /* bEndpointAddress: EP1 IN (0x81) */
    0x02,                               /* bmAttributes: Bulk */
    CAN_DATA_MAX_PACKET_SIZE, 0x00,     /* wMaxPacketSize: 64 */
    0x00,                               /* bInterval (ignored for bulk) */

    /* ---------- Endpoint 2 OUT (bulk, host -> device) ---------- */
    0x07,                               /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,       /* bDescriptorType: Endpoint */
    GSUSB_ENDPOINT_OUT,                 /* bEndpointAddress: EP2 OUT (0x02) */
    0x02,                               /* bmAttributes: Bulk */
    CAN_DATA_MAX_PACKET_SIZE, 0x00,     /* wMaxPacketSize: 64 */
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
    'c', 0, 'a', 0, 'n', 0, 'a', 0, 'b', 0, 'l', 0, 'e', 0
};

const uint8_t Virtual_Com_Port_StringProduct[VIRTUAL_COM_PORT_SIZ_STRING_PRODUCT] =
{
    VIRTUAL_COM_PORT_SIZ_STRING_PRODUCT,
    USB_STRING_DESCRIPTOR_TYPE,
    'C', 0, 'A', 0, 'N', 0, 'a', 0, 'b', 0, 'l', 0, 'e', 0,
    '2', 0, '.', 0, '0', 0
};

uint8_t Virtual_Com_Port_StringSerial[VIRTUAL_COM_PORT_SIZ_STRING_SERIAL] =
{
    VIRTUAL_COM_PORT_SIZ_STRING_SERIAL,
    USB_STRING_DESCRIPTOR_TYPE,
    'N', 0, '3', 0, '2', 0, 'H', 0, '4', 0, '7', 0, '3', 0, '-', 0,
    '0', 0, '0', 0, '0', 0, '1', 0,
};
