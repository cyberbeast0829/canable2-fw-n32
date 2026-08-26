/**
 * @file    usb_prop.c
 * @brief   USB Device Property callbacks for CANable2-N32 (CDC ACM)
 *
 * Based on ODrive usb_prop.c.  Provides Device_Property and
 * User_Standard_Requests structures required by the N32 USB library.
 */

#include "usbfsd_lib.h"
#include "usb_conf.h"
#include "usb_prop.h"
#include "usb_desc.h"
#include "usb_pwr.h"

/* Private variables */
static uint8_t Request = 0;

LINE_CODING linecoding =
{
    921600, /* baud rate */
    0x00,   /* stop bits: 1 */
    0x00,   /* parity: none */
    0x08    /* data bits: 8 */
};

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

USB_OneDescriptor String_Descriptor[4] =
{
    {(uint8_t*)Virtual_Com_Port_StringLangID,  VIRTUAL_COM_PORT_SIZ_STRING_LANGID},
    {(uint8_t*)Virtual_Com_Port_StringVendor,   VIRTUAL_COM_PORT_SIZ_STRING_VENDOR},
    {(uint8_t*)Virtual_Com_Port_StringProduct,  VIRTUAL_COM_PORT_SIZ_STRING_PRODUCT},
    {(uint8_t*)Virtual_Com_Port_StringSerial,   VIRTUAL_COM_PORT_SIZ_STRING_SERIAL},
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

    /* Initialize Endpoint 1 IN (Bulk — CDC data device->host)
     * Set to NAK initially — only arm when cdc_process() has data to send.
     * Setting EP_TX_VALID here would cause 64 bytes of garbage from the
     * uninitialized PMA buffer to be sent on the first host IN token. */
    USB_SetEpType(ENDP1, EP_BULK);
    USB_SetEpTxAddr(ENDP1, ENDP1_TXADDR);
    SetEPTxStatus(ENDP1, EP_TX_NAK);

    /* Initialize Endpoint 1 OUT (Bulk — CDC data host->device) */
    USB_SetEpType(ENDP1, EP_BULK);
    USB_SetEpRxAddr(ENDP1, ENDP1_RXADDR);
    USB_SetEpRxCnt(ENDP1, Device_Property.MaxPacketSize);
    SetEPRxStatus(ENDP1, EP_RX_VALID);

    /* Initialize Endpoint 2 (Interrupt IN — CDC notification) */
    USB_SetEpType(ENDP2, EP_INTERRUPT);
    USB_SetEpTxAddr(ENDP2, ENDP2_TXADDR);
    SetEPRxStatus(ENDP2, EP_RX_DIS);
    SetEPTxStatus(ENDP2, EP_TX_NAK);

    USB_SetDeviceAddress(0);
    bDeviceState = ATTACHED;
}

void Virtual_Com_Port_SetConfiguration(void)
{
    if (pInformation->CurrentConfiguration != 0)
    {
        bDeviceState = CONFIGURED;
        USB_ClrDattogTx(ENDP1);
        USB_ClrDattogRx(ENDP1);
    }
}

void Virtual_Com_Port_SetDeviceAddress(void)
{
    bDeviceState = ADDRESSED;
}

void Virtual_Com_Port_Status_In(void)
{
    if (Request == SET_LINE_CODING)
        Request = 0;
}

void Virtual_Com_Port_Status_Out(void)
{
}

USB_Result Virtual_Com_Port_Data_Setup(uint8_t RequestNo)
{
    uint8_t *(*CopyRoutine)(uint16_t) = NULL;

    if (RequestNo == GET_LINE_CODING)
    {
        if (Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT))
            CopyRoutine = Virtual_Com_Port_GetLineCoding;
    }
    else if (RequestNo == SET_LINE_CODING)
    {
        if (Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT))
            CopyRoutine = Virtual_Com_Port_SetLineCoding;
        Request = SET_LINE_CODING;
    }

    if (CopyRoutine == NULL)
        return UnSupport;

    pInformation->Ctrl_Info.CopyData = CopyRoutine;
    pInformation->Ctrl_Info.Usb_wOffset = 0;
    (*CopyRoutine)(0);
    return Success;
}

USB_Result Virtual_Com_Port_NoData_Setup(uint8_t RequestNo)
{
    if (Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT))
    {
        if (RequestNo == SET_COMM_FEATURE || RequestNo == SET_CONTROL_LINE_STATE)
            return Success;
    }
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
    if (wValue0 > 4)
        return NULL;
    return Standard_GetDescriptorData(Length, &String_Descriptor[wValue0]);
}

USB_Result Virtual_Com_Port_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting)
{
    if (AlternateSetting > 0)
        return UnSupport;
    return Success;
}

uint8_t *Virtual_Com_Port_GetLineCoding(uint16_t Length)
{
    if (Length == 0)
    {
        pInformation->Ctrl_Info.Usb_wLength = sizeof(linecoding);
        return NULL;
    }
    return (uint8_t *)&linecoding;
}

uint8_t *Virtual_Com_Port_SetLineCoding(uint16_t Length)
{
    if (Length == 0)
    {
        pInformation->Ctrl_Info.Usb_wLength = sizeof(linecoding);
        return NULL;
    }
    return (uint8_t *)&linecoding;
}

/* Standard request stubs */
void Virtual_Com_Port_GetConfiguration(void) {}
void Virtual_Com_Port_GetInterface(void)     {}
void Virtual_Com_Port_SetInterface(void)     {}
void Virtual_Com_Port_GetStatus(void)        {}
void Virtual_Com_Port_ClearFeature(void)     {}
void Virtual_Com_Port_SetEndPointFeature(void) {}
void Virtual_Com_Port_SetDeviceFeature(void)  {}
