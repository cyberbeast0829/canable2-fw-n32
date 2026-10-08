/**
 * @file    usb_prop.c
 * @brief   USB Device Property callbacks for CANable2-N32 (gs_usb vendor class)
 *
 * Based on ODrive usb_prop.c.  Provides Device_Property and
 * User_Standard_Requests structures required by the N32 USB library,
 * wired for the gs_usb vendor-class interface.
 */

#include "usbfsd_lib.h"
#include "usb_conf.h"
#include "usb_prop.h"
#include "usb_desc.h"
#include "usb_pwr.h"
#include "gs_usb.h"

/* -------------------------------------------------------------------------- */
/* Vendor control-request state                                               */
/* -------------------------------------------------------------------------- */

/* Destination for host->device vendor payloads (applied on status stage). */
static uint8_t gs_vendor_out_buf_store[64] __attribute__((aligned(4)));

/* Pending host->device vendor request code (0 = none). */
static uint8_t gs_pending_request = 0;

/* -------------------------------------------------------------------------- */
/* Device descriptor wrapper structures                                       */
/* -------------------------------------------------------------------------- */

USB_OneDescriptor Device_Descriptor =
{
    (uint8_t*)Virtual_Com_Port_DeviceDescriptor,
    VIRTUAL_COM_PORT_SIZ_DEVICE_DESC
};

USB_OneDescriptor Config_Descriptor =
{
    (uint8_t*)Virtual_Com_Port_ConfigDescriptor,
    VIRTUAL_COM_PORT_SIZ_CONFIG_DESC
};

USB_OneDescriptor String_Descriptor[6] =
{
    {(uint8_t*)Virtual_Com_Port_StringLangID,    VIRTUAL_COM_PORT_SIZ_STRING_LANGID},
    {(uint8_t*)Virtual_Com_Port_StringVendor,    VIRTUAL_COM_PORT_SIZ_STRING_VENDOR},
    {(uint8_t*)Virtual_Com_Port_StringProduct,   VIRTUAL_COM_PORT_SIZ_STRING_PRODUCT},
    {(uint8_t*)Virtual_Com_Port_StringSerial,    VIRTUAL_COM_PORT_SIZ_STRING_SERIAL},
    {(uint8_t*)Virtual_Com_Port_StringConfig,    VIRTUAL_COM_PORT_SIZ_STRING_CONFIG},
    {(uint8_t*)Virtual_Com_Port_StringInterface, VIRTUAL_COM_PORT_SIZ_STRING_INTERFACE},
};

/* MS OS String Descriptor (string index 0xEE) wrapper for Standard_GetDescriptorData */
USB_OneDescriptor ms_os_string_desc =
{
    (uint8_t*)MS_OS_StringDescriptor,
    MS_OS_STRING_DESC_SIZE
};

/* -------------------------------------------------------------------------- */
/* Core structures required by N32 USB library                                */
/* -------------------------------------------------------------------------- */

USB_Device Device_Table =
{
    EP_NUM,
    1
};

DEVICE_PROP Device_Property =
{
    Virtual_Com_Port_init,
    Virtual_Com_Port_Reset,
    Virtual_Com_Port_Status_In,
    Virtual_Com_Port_Status_Out,
    Virtual_Com_Port_Data_Setup,
    Virtual_Com_Port_NoData_Setup,
    Virtual_Com_Port_Get_Interface_Setting,
    Virtual_Com_Port_GetDeviceDescriptor,
    Virtual_Com_Port_GetConfigDescriptor,
    Virtual_Com_Port_GetStringDescriptor,
    0,
    0x40 /* MAX PACKET SIZE */
};

USER_STANDARD_REQUESTS User_Standard_Requests =
{
    Virtual_Com_Port_GetConfiguration,
    Virtual_Com_Port_SetConfiguration,
    Virtual_Com_Port_GetInterface,
    Virtual_Com_Port_SetInterface,
    Virtual_Com_Port_GetStatus,
    Virtual_Com_Port_ClearFeature,
    Virtual_Com_Port_SetEndPointFeature,
    Virtual_Com_Port_SetDeviceFeature,
    Virtual_Com_Port_SetDeviceAddress
};

/* -------------------------------------------------------------------------- */
/* Callback implementations                                                    */
/* -------------------------------------------------------------------------- */

void Virtual_Com_Port_init(void)
{
    pInformation->CurrentConfiguration = 0;
    PowerOn();
    USB_SilInit();

    gs_usb_reset();

    /* Pull up DP to signal connection to host */
    _EnPortPullup();

    bDeviceState = UNCONNECTED;
}

void Virtual_Com_Port_Reset(void)
{
    pInformation->CurrentConfiguration = 0;
    pInformation->CurrentFeature = Virtual_Com_Port_ConfigDescriptor[7];
    pInformation->CurrentInterface = 0;

    USB_SetBuftab(BTABLE_ADDRESS);

    /* Initialize Endpoint 0 */
    USB_SetEpType(ENDP0, EP_CONTROL);
    SetEPTxStatus(ENDP0, EP_TX_STALL);
    USB_SetEpRxAddr(ENDP0, ENDP0_RXADDR);
    USB_SetEpTxAddr(ENDP0, ENDP0_TXADDR);
    USB_ClrStsOut(ENDP0);
    USB_SetEpRxCnt(ENDP0, Device_Property.MaxPacketSize);
    USB_SetEpRxValid(ENDP0);

    /* EP1 IN (Bulk — gs_usb device->host). NAK until data is queued. */
    USB_SetEpType(ENDP1, EP_BULK);
    USB_SetEpTxAddr(ENDP1, ENDP1_TXADDR);
    SetEPTxStatus(ENDP1, EP_TX_NAK);

    /* EP2 OUT (Bulk — gs_usb host->device). Ready to receive. */
    USB_SetEpType(ENDP2, EP_BULK);
    USB_SetEpRxAddr(ENDP2, ENDP2_RXADDR);
    USB_SetEpRxCnt(ENDP2, CAN_DATA_MAX_PACKET_SIZE);
    SetEPRxStatus(ENDP2, EP_RX_VALID);

    gs_usb_reset();

    USB_SetDeviceAddress(0);
    bDeviceState = ATTACHED;
}

void Virtual_Com_Port_SetConfiguration(void)
{
    if (pInformation->CurrentConfiguration != 0)
    {
        bDeviceState = CONFIGURED;
        USB_ClrDattogTx(ENDP1);
        USB_ClrDattogRx(ENDP2);
        /* Open gs_usb endpoints and prime the first OUT receive. */
        gs_usb_start();
    }
}

void Virtual_Com_Port_SetDeviceAddress(void)
{
    bDeviceState = ADDRESSED;
}

void Virtual_Com_Port_Status_In(void)
{
    /* Apply a staged host->device vendor request once its data is in. */
    if (gs_pending_request != 0)
    {
        gs_usb_apply_control(gs_pending_request, gs_vendor_out_buf_store);
        gs_pending_request = 0;
    }
}

void Virtual_Com_Port_Status_Out(void)
{
}

/*
 * Vendor control-request data callbacks.
 *
 * The N32 USB library drives the data stage through Ctrl_Info.CopyData:
 *   - OUT (host->device): library calls CopyData(Length!=0), expects the
 *     destination buffer where it will copy the received bytes.
 *   - IN  (device->host): library calls CopyData(0) to learn total length,
 *     then CopyData(Length!=0) to fetch each chunk. This is exactly the
 *     Standard_GetDescriptorData() contract.
 */

static uint8_t *gs_vendor_out_buf(uint16_t Length)
{
    (void)Length;
    return gs_vendor_out_buf_store;
}

/* Last vendor IN buffer pointer + length (device->host). */
static uint8_t *gs_vendor_in_ptr = NULL;
static uint16_t gs_vendor_in_len = 0;

static uint8_t *gs_vendor_in_cb(uint16_t Length)
{
    uint32_t off = pInformation->Ctrl_Info.Usb_wOffset;

    if (Length == 0)
    {
        pInformation->Ctrl_Info.Usb_wLength = gs_vendor_in_len - off;
        return NULL;
    }
    return gs_vendor_in_ptr + off;
}

/*
 * Data stage handler for vendor requests.
 *  - Device -> Host (IN):  resolve vendor_data and serve it.
 *  - Host -> Device (OUT): receive into gs_vendor_out_buf; applied in
 *                          Virtual_Com_Port_Status_In().
 */
USB_Result Virtual_Com_Port_Data_Setup(uint8_t RequestNo)
{
    uint8_t *vendor_data = NULL;
    uint16_t vendor_len = 0;

    /* ---- BOS descriptor (Windows 10+ MS OS 2.0 discovery) --------------------
     * GET_DESCRIPTOR for BOS (wValue1 == 0x0F) is a standard, device-recipient
     * request that the N32 library does not handle, so it falls through to here.
     * Returning the BOS + MS OS 2.0 platform capability lets Windows 10/11 fetch
     * the descriptor set below and auto-bind WinUSB with no driver install.
     * Only served when MSOS_USE_20 is enabled (bcdUSB must then be >= 2.01). */
#if MSOS_USE_20
    if (RequestNo == 0x06 /* GET_DESCRIPTOR */ &&
        Type_Recipient == DEVICE_RECIPIENT &&
        pInformation->USBwValue1 == 0x0F /* BOS */)
    {
        gs_vendor_in_ptr = (uint8_t*)Virtual_Com_Port_BOSDescriptor;
        gs_vendor_in_len = VIRTUAL_COM_PORT_SIZ_BOS_DESC;
        pInformation->Ctrl_Info.Usb_wOffset = 0;
        pInformation->Ctrl_Info.CopyData = gs_vendor_in_cb;
        pInformation->Ctrl_Info.Usb_wLength = VIRTUAL_COM_PORT_SIZ_BOS_DESC;
        return Success;
    }
#endif

    /* ---- Microsoft OS descriptors (device recipient, bmRequestType 0xC0) ----
     * Windows issues these to discover the Compatible ID and the
     * DeviceInterfaceGUID so it can auto-bind WinUSB without a driver.
     * They are device-recipient vendor requests, hence handled before the
     * interface-recipient gs_usb vendor requests below. */
    if (Type_Recipient == VENDOR_REQUEST &&
        RequestNo == MS_OS_VENDOR_CODE)
    {
        /* The N32 library byte-swaps wIndex when it copies it out of the PMA
         * (USB_ProcessSetup0 does USB_ByteSwap on the raw word and the 32-bit
         * PMA addressing adds a second reversal). Net effect: USBwIndex holds
         * the wire value with its two bytes swapped, so swap it back to get the
         * real wIndex the host sent (Windows sends 0x0004 / 0x0005 / 0x0007). */
        uint16_t wIndex = (uint16_t)((pInformation->USBwIndex >> 8) |
                                     (pInformation->USBwIndex << 8));

        if (wIndex == MS_OS_WINDEX_COMPAT_ID)
        {
            gs_vendor_in_ptr = (uint8_t*)MS_OS_CompatibleID;
            gs_vendor_in_len = MS_OS_COMPAT_ID_DESC_SIZE;
        }
        else if (wIndex == MS_OS_WINDEX_EXT_PROP)
        {
            gs_vendor_in_ptr = (uint8_t*)MS_OS_ExtendedProperties;
            gs_vendor_in_len = MS_OS_EXT_PROP_DESC_SIZE;
        }
        else if (wIndex == MS_OS_20_DESCRIPTOR_INDEX)
        {
            /* MS OS 2.0 descriptor set (Windows 10/11 path). */
#if MSOS_USE_20
            gs_vendor_in_ptr = (uint8_t*)MS_OS_20_DescriptorSet;
            gs_vendor_in_len = MS_OS_20_SET_TOTAL_LEN;
#else
            return UnSupport;
#endif
        }
        else
        {
            return UnSupport;
        }

        pInformation->Ctrl_Info.Usb_wOffset = 0;
        pInformation->Ctrl_Info.CopyData = gs_vendor_in_cb;
        pInformation->Ctrl_Info.Usb_wLength = gs_vendor_in_len;
        return Success;
    }

    if (Type_Recipient != (VENDOR_REQUEST | INTERFACE_RECIPIENT))
        return UnSupport;

    if (!gs_usb_setup_request(RequestNo, pInformation->USBwValue,
                              &vendor_data, &vendor_len))
        return UnSupport;

    pInformation->Ctrl_Info.Usb_wOffset = 0;

    if (pInformation->bmRequestType & 0x80)
    {
        /* IN: device -> host */
        gs_vendor_in_ptr = vendor_data;
        gs_vendor_in_len = vendor_len;
        pInformation->Ctrl_Info.CopyData = gs_vendor_in_cb;
        pInformation->Ctrl_Info.Usb_wLength = vendor_len;
    }
    else
    {
        /* OUT: host -> device — receive into our buffer, apply on status. */
        gs_pending_request = RequestNo;
        pInformation->Ctrl_Info.CopyData = gs_vendor_out_buf;
        pInformation->Ctrl_Info.Usb_wLength = pInformation->USBwLength;
    }

    return Success;
}

USB_Result Virtual_Com_Port_NoData_Setup(uint8_t RequestNo)
{
    (void)RequestNo;
    return UnSupport;
}

uint8_t *Virtual_Com_Port_GetDeviceDescriptor(uint16_t Length)
{
    return Standard_GetDescriptorData(Length, &Device_Descriptor);
}

uint8_t *Virtual_Com_Port_GetConfigDescriptor(uint16_t Length)
{
    return Standard_GetDescriptorData(Length, &Config_Descriptor);
}

uint8_t *Virtual_Com_Port_GetStringDescriptor(uint16_t Length)
{
    uint8_t wValue0 = pInformation->USBwValue0;
    uint8_t wValue1 = pInformation->USBwValue1;
    uint16_t wValue = pInformation->USBwValue;

    /* MS OS String Descriptor at index 0xEE: lets Windows know the device
     * speaks the Microsoft OS descriptor protocol (and the vendor code).
     * The library byte-swaps wValue, so the index byte may land in either
     * USBwValue0 or USBwValue1 depending on the swap; accept either. */
    if (wValue0 == MS_OS_STRING_INDEX || wValue1 == MS_OS_STRING_INDEX ||
        ((wValue & 0xFF) == MS_OS_STRING_INDEX) ||
        ((wValue >> 8) == MS_OS_STRING_INDEX))
    {
        return Standard_GetDescriptorData(Length, &ms_os_string_desc);
    }

    /* Index = low byte of the (byte-swapped) wValue; mask off the String type
     * in the high byte so we never index out of range. */
    wValue0 &= 0x7F;
    if (wValue0 >= (uint8_t)(sizeof(String_Descriptor) / sizeof(String_Descriptor[0])))
        return NULL;
    return Standard_GetDescriptorData(Length, &String_Descriptor[wValue0]);
}

USB_Result Virtual_Com_Port_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting)
{
    if (Interface > 0)
        return UnSupport;
    if (AlternateSetting > 0)
        return UnSupport;
    return Success;
}

/* Standard request stubs */
void Virtual_Com_Port_GetConfiguration(void) {}
void Virtual_Com_Port_GetInterface(void)     {}
void Virtual_Com_Port_SetInterface(void)     {}
void Virtual_Com_Port_GetStatus(void)        {}
void Virtual_Com_Port_ClearFeature(void)     {}
void Virtual_Com_Port_SetEndPointFeature(void) {}
void Virtual_Com_Port_SetDeviceFeature(void)  {}
