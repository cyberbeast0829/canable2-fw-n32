/**
 * @file    usb_desc.c
 * @brief   USB Descriptors for CANable2-N32 (gs_usb / candleLight)
 *
 * VID/PID match candleLight: 0x1d50:0x606f, so the Linux kernel gs_usb
 * driver binds automatically. On Windows the MS OS descriptors below make
 * Windows auto-bind WinUSB (no Zadig / no manual driver install).
 * Two schemes are selectable via MSOS_USE_20 (see usb_desc.h):
 *   - default (0): MS OS 1.0  -> bcdUSB 2.00, string 0xEE + vendor 0x20
 *   - MSOS_USE_20=1: also BOS + MS OS 2.0 -> bcdUSB 2.01
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
#if MSOS_USE_20
    0x01, 0x02,                 /* bcdUSB = 2.01 (required to advertise BOS /
                                 * MS OS 2.0 platform capability) */
#else
    0x00, 0x02,                 /* bcdUSB = 2.00 (MS OS 1.0 path; no BOS) */
#endif
    0x00,                       /* bDeviceClass: per-interface (match candleLight)
                                 * NOTE: must be 0x00 (not 0xFF) so Windows evaluates
                                 * the interface-level MS OS Compatible ID and
                                 * auto-binds WinUSB. 0xFF makes Windows treat the
                                 * whole device as a single unknown vendor device. */
    0x00,                       /* bDeviceSubClass */
    0x00,                       /* bDeviceProtocol */
    0x40,                       /* bMaxPacketSize0 = 64 */
    (USB_VID & 0xFF), (USB_VID >> 8),   /* idVendor  (default 0x1d50) */
    (USB_PID & 0xFF), (USB_PID >> 8),   /* idProduct (default 0x606f) */
    (USB_BCDDEVICE & 0xFF), (USB_BCDDEVICE >> 8), /* bcdDevice (default 0x0200) */
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
    VIRTUAL_COM_PORT_STR_CONFIG,            /* iConfiguration (index 4) */
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
    VIRTUAL_COM_PORT_STR_INTERFACE,     /* iInterface (index 5) */

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
    'C', 0, 'y', 0, 'b', 0, 'e', 0, 'r', 0, 'B', 0, 'e', 0, 'a', 0,
    's', 0, 't', 0
};

const uint8_t Virtual_Com_Port_StringProduct[VIRTUAL_COM_PORT_SIZ_STRING_PRODUCT] =
{
    VIRTUAL_COM_PORT_SIZ_STRING_PRODUCT,
    USB_STRING_DESCRIPTOR_TYPE,
    'g', 0, 's', 0, '_', 0, 'u', 0, 's', 0, 'b', 0
};

/* Serial number string: built at runtime from the 96-bit device UID
 * (UID_BASE, 12 bytes). Formatted as 24 uppercase hex digits, e.g.
 * "0123456789ABCDEF01234567". This gives every board a unique serial number,
 * which also gives Windows/Linux a stable, per-device instance identity.
 * The string descriptor is UTF-16LE, hence 2 bytes per ASCII character. */
uint8_t Virtual_Com_Port_StringSerial[VIRTUAL_COM_PORT_SIZ_STRING_SERIAL] =
{
    /* Filled in by Virtual_Com_Port_BuildSerial(). */
};

static void u32_to_hex8(char *out, uint32_t val)
{
    static const char digits[] = "0123456789ABCDEF";
    for (int i = 7; i >= 0; i--)
    {
        out[i] = digits[val & 0x0F];
        val >>= 4;
    }
}

/* Build the serial-number string descriptor from the device UID.
 * Call once during USB init (before enumeration). */
void Virtual_Com_Port_BuildSerial(void)
{
    char hex[25];  /* 24 hex chars + NUL */

    u32_to_hex8(hex +  0, *(volatile uint32_t *)(UID_BASE + 0));
    u32_to_hex8(hex +  8, *(volatile uint32_t *)(UID_BASE + 4));
    u32_to_hex8(hex + 16, *(volatile uint32_t *)(UID_BASE + 8));
    hex[24] = '\0';

    Virtual_Com_Port_StringSerial[0] = VIRTUAL_COM_PORT_SIZ_STRING_SERIAL;
    Virtual_Com_Port_StringSerial[1] = USB_STRING_DESCRIPTOR_TYPE;
    for (int i = 0; i < 24; i++)
    {
        Virtual_Com_Port_StringSerial[2 + i * 2]     = (uint8_t)hex[i];
        Virtual_Com_Port_StringSerial[2 + i * 2 + 1] = 0;
    }
}

/* Configuration string (index 4). Windows tolerates iConfiguration==0, but a
 * valid index is safer and matches candleLight (which also exposes one). */
const uint8_t Virtual_Com_Port_StringConfig[VIRTUAL_COM_PORT_SIZ_STRING_CONFIG] =
{
    VIRTUAL_COM_PORT_SIZ_STRING_CONFIG,
    USB_STRING_DESCRIPTOR_TYPE,
    'g', 0, 's', 0, '_', 0, 'u', 0, 's', 0, 'b', 0
};

/* Interface string (index 5). */
const uint8_t Virtual_Com_Port_StringInterface[VIRTUAL_COM_PORT_SIZ_STRING_INTERFACE] =
{
    VIRTUAL_COM_PORT_SIZ_STRING_INTERFACE,
    USB_STRING_DESCRIPTOR_TYPE,
    'g', 0, 's', 0, '_', 0, 'u', 0, 's', 0, 'b', 0, ' ', 0,
    'i', 0, 'n', 0, 't', 0, 'e', 0, 'r', 0, 'f', 0, 'a', 0, 'c', 0, 'e', 0
};

/* ==========================================================================
 *  Microsoft OS descriptors (Windows driverless / WinUSB auto-binding)
 *
 *  Windows has no built-in gs_usb driver. To bind WinUSB automatically
 *  (no manually installed driver / no Zadig) the device exposes:
 *    - string index 0xEE : MS OS String Descriptor ("MSFT100" + vendor code)
 *    - vendor request    : bRequest == MS_OS_VENDOR_CODE, where wIndex selects
 *                          0x0004 -> Compatible ID ("WINUSB")
 *                          0x0005 -> Extended Properties (DeviceInterfaceGUID)
 *
 *  The DeviceInterfaceGUID "{c15b4308-04d3-11e6-b3ea-6057189e6443}" matches
 *  the candleLight ecosystem GUID so existing Windows tools can find the
 *  device by its interface path.
 * ========================================================================== */

/* MS OS String Descriptor (string index 0xEE): "MSFT100" + vendor code.
 * Signature MUST be exactly "MSFT100" (7 chars = 14 bytes UTF-16LE); a wrong
 * signature makes Windows reject the descriptor and record osvc=0. */
const uint8_t MS_OS_StringDescriptor[MS_OS_STRING_DESC_SIZE] =
{
    0x12,                       /* bLength = 18 */
    0x03,                       /* bDescriptorType: STRING */
    'M', 0, 'S', 0, 'F', 0, 'T', 0, '1', 0, '0', 0, '0', 0,  /* "MSFT100" */
    MS_OS_VENDOR_CODE,          /* bMS_VendorCode = 0x20 */
    0x00                        /* bPad */
};

/* MS OS Compatible ID Feature Descriptor (wIndex == 0x0004).
 * Declares interface 0 as compatible with "WINUSB".
 * Layout: 16-byte header + 24-byte function section = 40 bytes. */
const uint8_t MS_OS_CompatibleID[MS_OS_COMPAT_ID_DESC_SIZE] =
{
    0x28, 0x00, 0x00, 0x00,     /* dwLength = 40 */
    0x00, 0x01,                 /* bcdVersion = 1.00 */
    0x04, 0x00,                 /* wIndex = 0x0004 (Compatible ID) */
    0x01,                       /* bCount = 1 section */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  /* 7 reserved */
    /* --- function section for interface 0 --- */
    0x00,                       /* bFirstInterfaceNumber = 0 */
    0x01,                       /* bReserved */
    'W', 'I', 'N', 'U', 'S', 'B', 0x00, 0x00,  /* compatible ID "WINUSB\0\0" */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  /* sub-compatible ID */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00           /* 6 reserved */
};

/* MS OS Extended Properties Feature Descriptor (wIndex == 0x0005).
 * Exposes DeviceInterfaceGUIDs so the device gets a stable device path. */
const uint8_t MS_OS_ExtendedProperties[MS_OS_EXT_PROP_DESC_SIZE] =
{
    0x92, 0x00, 0x00, 0x00,     /* dwLength = 146 */
    0x00, 0x01,                 /* bcdVersion = 1.00 */
    0x05, 0x00,                 /* wIndex = 0x0005 (Extended Properties) */
    0x01, 0x00,                 /* wCount = 1 custom property */

    /* --- Property 1: DeviceInterfaceGUIDs (REG_MULTI_SZ) --- */
    0x88, 0x00, 0x00, 0x00,     /* dwSize = 136 */
    0x07, 0x00, 0x00, 0x00,     /* dwPropertyDataType = 7 (REG_MULTI_SZ) */
    0x2A, 0x00,                 /* wPropertyNameLength = 42 */
    /* "DeviceInterfaceGUIDs" UTF-16LE (20 chars + NUL) */
    'D', 0, 'e', 0, 'v', 0, 'i', 0, 'c', 0, 'e', 0, 'I', 0, 'n', 0, 't', 0,
    'e', 0, 'r', 0, 'f', 0, 'a', 0, 'c', 0, 'e', 0, 'G', 0, 'U', 0, 'I', 0,
    'D', 0, 's', 0, 0x00, 0x00,
    0x50, 0x00, 0x00, 0x00,     /* dwPropertyDataLength = 80 */
    /* "{c15b4308-04d3-11e6-b3ea-6057189e6443}" UTF-16LE + double NUL */
    '{', 0, 'c', 0, '1', 0, '5', 0, 'b', 0, '4', 0, '3', 0, '0', 0, '8', 0,
    '-', 0, '0', 0, '4', 0, 'd', 0, '3', 0, '-', 0, '1', 0, '1', 0, 'e', 0,
    '6', 0, '-', 0, 'b', 0, '3', 0, 'e', 0, 'a', 0, '-', 0, '6', 0, '0', 0,
    '5', 0, '7', 0, '1', 0, '8', 0, '9', 0, 'e', 0, '6', 0, '4', 0, '4', 0,
    '3', 0, '}', 0, 0x00, 0x00, 0x00, 0x00
};

/* ==========================================================================
 *  Microsoft OS 2.0 descriptors (preferred on Windows 10/11)
 *
 *  Windows 10+ first asks for the BOS descriptor.  If it finds a Platform
 *  Capability with the Microsoft OS 2.0 UUID, it issues a vendor request
 *  (bRequest == MS_OS_VENDOR_CODE, wIndex == 0x07) to fetch the descriptor
 *  set below, which declares interface 0 as WinUSB.
 *
 *  MS OS 1.0 (above) is kept as a fallback for older Windows.
 * ========================================================================== */

/* BOS descriptor: BOS header + one Platform Capability descriptor. */
const uint8_t Virtual_Com_Port_BOSDescriptor[VIRTUAL_COM_PORT_SIZ_BOS_DESC] =
{
    /* ---------- BOS Descriptor ---------- */
    0x05,                       /* bLength */
    0x0F,                       /* bDescriptorType: BOS */
    0x21, 0x00,                 /* wTotalLength = 33 (5 + 28) */
    0x01,                       /* bNumDeviceCaps = 1 */

    /* ---------- Platform Capability Descriptor (Microsoft OS 2.0) ---------- */
    0x1C,                       /* bLength = 28 (4 + 16 + 4 + 2 + 1 + 1) */
    0x10,                       /* bDescriptorType: DEVICE_CAPABILITY */
    0x05,                       /* bDevCapabilityType: PLATFORM */
    0x00,                       /* bReserved */
    /* PlatformCapabilityUUID = {D8DD60DF-4589-4CC7-9CD2-659D9E648A9F} */
    0xDF, 0x60, 0xDD, 0xD8, 0x89, 0x45, 0xC7, 0x4C,
    0x9C, 0xD2, 0x65, 0x9D, 0x9E, 0x64, 0x8A, 0x9F,
    0x00, 0x00, 0x03, 0x06,     /* dwWindowsVersion = 0x06030000 (Win 8.1+) */
    MS_OS_20_SET_TOTAL_LEN, 0x00,  /* wMSOSDescriptorSetTotalLength */
    MS_OS_VENDOR_CODE,          /* bMS_VendorCode */
    0x00                        /* bAltEnumCode */
};

/* MS OS 2.0 descriptor set (returned for vendor code 0x20, wIndex 0x0007).
 *
 *   Set Header              (10 bytes)
 *   Function Subset Header   (8 bytes)  - single-interface device
 *   Compatible ID           (20 bytes)  - "WINUSB"
 *   REG Property            (132 bytes) - DeviceInterfaceGUIDs
 *   --------------------------------------------------
 *   Total                   (170 bytes = 0x00AA)
 */
const uint8_t MS_OS_20_DescriptorSet[MS_OS_20_SET_TOTAL_LEN] =
{
    /* ---------- Set Header ---------- */
    0x0A, 0x00,                 /* wLength = 10 */
    0x00, 0x00,                 /* wDescriptorType = SET_HEADER */
    0x00, 0x00, 0x03, 0x06,     /* dwWindowsVersion = 0x06030000 */
    MS_OS_20_SET_TOTAL_LEN, 0x00,  /* wTotalLength = 170 */

    /* ---------- Function Subset Header ---------- */
    0x08, 0x00,                 /* wLength = 8 */
    0x02, 0x00,                 /* wDescriptorType = SUBSET_HEADER_FUNCTION */
    0x00,                       /* bFirstInterface = 0 */
    0x00,                       /* bReserved */
    0xA0, 0x00,                 /* wSubsetLength = 160 (this header + 20 + 132) */

    /* ---------- Compatible ID ---------- */
    0x14, 0x00,                 /* wLength = 20 */
    0x03, 0x00,                 /* wDescriptorType = FEATURE_COMPATIBLE_ID */
    'W', 'I', 'N', 'U', 'S', 'B', 0x00, 0x00,  /* CompatibleID "WINUSB\0\0" */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  /* SubCompatibleID */

    /* ---------- REG Property: DeviceInterfaceGUIDs ---------- */
    0x84, 0x00,                 /* wLength = 132 */
    0x04, 0x00,                 /* wDescriptorType = FEATURE_REG_PROPERTY */
    0x07, 0x00,                 /* wPropertyDataType = 7 (REG_MULTI_SZ) */
    0x2A, 0x00,                 /* wPropertyNameLength = 42 */
    /* "DeviceInterfaceGUIDs" UTF-16LE (20 chars + NUL) */
    'D', 0, 'e', 0, 'v', 0, 'i', 0, 'c', 0, 'e', 0, 'I', 0, 'n', 0, 't', 0,
    'e', 0, 'r', 0, 'f', 0, 'a', 0, 'c', 0, 'e', 0, 'G', 0, 'U', 0, 'I', 0,
    'D', 0, 's', 0, 0x00, 0x00,
    0x50, 0x00,                 /* wPropertyDataLength = 80 */
    /* "{c15b4308-04d3-11e6-b3ea-6057189e6443}" UTF-16LE + double NUL */
    '{', 0, 'c', 0, '1', 0, '5', 0, 'b', 0, '4', 0, '3', 0, '0', 0, '8', 0,
    '-', 0, '0', 0, '4', 0, 'd', 0, '3', 0, '-', 0, '1', 0, '1', 0, 'e', 0,
    '6', 0, '-', 0, 'b', 0, '3', 0, 'e', 0, 'a', 0, '-', 0, '6', 0, '0', 0,
    '5', 0, '7', 0, '1', 0, '8', 0, '9', 0, 'e', 0, '6', 0, '4', 0, '4', 0,
    '3', 0, '}', 0, 0x00, 0x00, 0x00, 0x00
};


