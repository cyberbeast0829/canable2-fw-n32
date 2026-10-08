/**
 * @file    usb_desc.h
 * @brief   USB Descriptor definitions for CANable2-N32 (gs_usb vendor class)
 */

#ifndef __USB_DESC_H
#define __USB_DESC_H

/* Descriptor types */
#define USB_DEVICE_DESCRIPTOR_TYPE              0x01
#define USB_CONFIGURATION_DESCRIPTOR_TYPE       0x02
#define USB_STRING_DESCRIPTOR_TYPE              0x03
#define USB_INTERFACE_DESCRIPTOR_TYPE           0x04
#define USB_ENDPOINT_DESCRIPTOR_TYPE            0x05

/* Descriptor sizes */
#define VIRTUAL_COM_PORT_SIZ_DEVICE_DESC        18
#define VIRTUAL_COM_PORT_SIZ_CONFIG_DESC        32
#define VIRTUAL_COM_PORT_SIZ_STRING_LANGID      4
#define VIRTUAL_COM_PORT_SIZ_STRING_VENDOR      16    /* "candle"  = 7 chars * 2 + 2 */
#define VIRTUAL_COM_PORT_SIZ_STRING_PRODUCT     22    /* "CANable2.0" = 10 chars * 2 + 2 */
#define VIRTUAL_COM_PORT_SIZ_STRING_SERIAL      30    /* "CyberBeast-can" = 14 chars * 2 + 2 */
#define VIRTUAL_COM_PORT_SIZ_STRING_CONFIG      14    /* "gs_usb" = 6 chars * 2 + 2 */
#define VIRTUAL_COM_PORT_SIZ_STRING_INTERFACE   34    /* "gs_usb interface" = 16 chars * 2 + 2 */

/* String descriptor indices used by the device/configuration descriptors. */
#define VIRTUAL_COM_PORT_STR_MANUFACTURER       1
#define VIRTUAL_COM_PORT_STR_PRODUCT            2
#define VIRTUAL_COM_PORT_STR_SERIAL             3
#define VIRTUAL_COM_PORT_STR_CONFIG             4
#define VIRTUAL_COM_PORT_STR_INTERFACE          5

/* ---- Microsoft OS descriptors (Windows driverless / WinUSB auto-binding) ----
 *
 * Windows has no built-in gs_usb driver. These descriptors let Windows bind
 * WinUSB automatically (no Zadig / no manual .inf install):
 *   - the device answers the MS OS String Descriptor at string index 0xEE
 *   - vendor control requests with bRequest == MS_OS_VENDOR_CODE return the
 *     Compatible ID ("WINUSB") and the DeviceInterfaceGUID property.
 *
 * Two schemes are implemented and can be selected at build time:
 *   MSOS_USE_20 == 0 : MS OS 1.0 only (string 0xEE + wIndex 0x0004/0x0005),
 *                      bcdUSB stays 0x0200.  This is what candleLight ships and
 *                      is the most widely validated on Windows.
 *   MSOS_USE_20 == 1 : additionally advertise a BOS + MS OS 2.0 platform
 *                      capability and bump bcdUSB to 0x0201 (needs the BOS
 *                      descriptor to be served correctly).
 * Default is 0 (MS OS 1.0) because MS OS 2.0 was not accepted by the test host;
 * build with  -DMSOS_USE_20=1  to try the 2.0 path.
 */
#ifndef MSOS_USE_20
#define MSOS_USE_20                 0
#endif

#define MS_OS_STRING_INDEX          0xEE    /* string index for MS OS String Descriptor */
#define MS_OS_VENDOR_CODE           0x20    /* bRequest used to fetch MS OS descriptors   */

/* wIndex values that select which MS OS descriptor to return. */
#define MS_OS_WINDEX_COMPAT_ID      0x0004  /* Compatible ID Feature Descriptor  */
#define MS_OS_WINDEX_EXT_PROP       0x0005  /* Extended Properties Feature Descr */

#define MS_OS_STRING_DESC_SIZE          18
#define MS_OS_COMPAT_ID_DESC_SIZE       0x28   /* 40 bytes  */
#define MS_OS_EXT_PROP_DESC_SIZE        0x92   /* 146 bytes */

/* Microsoft OS 2.0 (preferred on Windows 10/11). The device exposes a BOS
 * descriptor with a Platform Capability; Windows then fetches the descriptor
 * set via vendor code MS_OS_VENDOR_CODE with wIndex == MS_OS_20_DESCRIPTOR_INDEX. */
#define MS_OS_20_DESCRIPTOR_INDEX       0x0007 /* wIndex for the descriptor set     */
#define VIRTUAL_COM_PORT_SIZ_BOS_DESC   0x21   /* 33 bytes: BOS hdr(5) + platform cap(28) */
#define MS_OS_20_SET_TOTAL_LEN          0xAA   /* 170 bytes: full descriptor set     */

extern const uint8_t MS_OS_StringDescriptor[MS_OS_STRING_DESC_SIZE];
extern const uint8_t MS_OS_CompatibleID[MS_OS_COMPAT_ID_DESC_SIZE];
extern const uint8_t MS_OS_ExtendedProperties[MS_OS_EXT_PROP_DESC_SIZE];
extern const uint8_t Virtual_Com_Port_BOSDescriptor[VIRTUAL_COM_PORT_SIZ_BOS_DESC];
extern const uint8_t MS_OS_20_DescriptorSet[MS_OS_20_SET_TOTAL_LEN];

extern const uint8_t Virtual_Com_Port_DeviceDescriptor[VIRTUAL_COM_PORT_SIZ_DEVICE_DESC];
extern const uint8_t Virtual_Com_Port_ConfigDescriptor[VIRTUAL_COM_PORT_SIZ_CONFIG_DESC];
extern const uint8_t Virtual_Com_Port_StringLangID[VIRTUAL_COM_PORT_SIZ_STRING_LANGID];
extern const uint8_t Virtual_Com_Port_StringVendor[VIRTUAL_COM_PORT_SIZ_STRING_VENDOR];
extern const uint8_t Virtual_Com_Port_StringProduct[VIRTUAL_COM_PORT_SIZ_STRING_PRODUCT];
extern const uint8_t Virtual_Com_Port_StringConfig[VIRTUAL_COM_PORT_SIZ_STRING_CONFIG];
extern const uint8_t Virtual_Com_Port_StringInterface[VIRTUAL_COM_PORT_SIZ_STRING_INTERFACE];
extern uint8_t Virtual_Com_Port_StringSerial[VIRTUAL_COM_PORT_SIZ_STRING_SERIAL];

#endif /* __USB_DESC_H */
