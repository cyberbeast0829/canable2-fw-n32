/**
 * @file    usb_istr.c
 * @brief   USB interrupt service routine and application stubs for N32 CANable2
 */

#include "n32h47x_48x.h"
#include "usbfsd_lib.h"
#include "usb_conf.h"
#include "usbd_cdc_if.h"

/* These global variables are required by the N32 USB library.
   They are defined here (application level), not in the library itself. */
__IO uint16_t wIstr;
__IO uint8_t  bIntPackSOF = 0;
__IO uint32_t esof_counter = 0;
__IO uint32_t wCNTR = 0;
extern __IO uint16_t SaveRState;
extern __IO uint16_t SaveTState;
extern uint16_t wInterrupt_Mask;

/* USB Device Table - required by N32 USB library */
USB_Device Device_Table = {
    .TotalEndpoint = EP_NUM,
    .TotalConfiguration = 1
};

/* USB Device Info - defined in N32 USB library (usbfsd_init.c) */
extern USB_DeviceMess Device_Info;

/* USB Device Property callbacks */
DEVICE_PROP Device_Property = {
    .Init = (void(*)(void))USB_ProcessNop,
    .Reset = (void(*)(void))USB_ProcessNop,
    .Process_Status_IN = (void(*)(void))USB_ProcessNop,
    .Process_Status_OUT = (void(*)(void))USB_ProcessNop,
    .Class_Data_Setup = 0,
    .Class_NoData_Setup = 0,
    .Class_Get_Interface_Setting = 0,
    .GetDeviceDescriptor = 0,
    .GetConfigDescriptor = 0,
    .GetStringDescriptor = 0,
    .RxEP_buffer = 0,
    .MaxPacketSize = 64,
};

/* Standard requests handler */
USER_STANDARD_REQUESTS User_Standard_Requests = {
    .User_GetConfiguration = (void(*)(void))USB_ProcessNop,
    .User_SetConfiguration = (void(*)(void))USB_ProcessNop,
    .User_GetInterface = (void(*)(void))USB_ProcessNop,
    .User_SetInterface = (void(*)(void))USB_ProcessNop,
    .User_GetStatus = (void(*)(void))USB_ProcessNop,
    .User_ClearFeature = (void(*)(void))USB_ProcessNop,
    .User_SetEndPointFeature = (void(*)(void))USB_ProcessNop,
    .User_SetDeviceFeature = (void(*)(void))USB_ProcessNop,
    .User_SetDeviceAddress = (void(*)(void))USB_ProcessNop,
};

/* Stub callbacks for unused endpoints */
static void EPn_Nop(void) {}

/* Endpoint IN callback function pointer array */
void (*pEpInt_IN[7])(void) = {
    EPn_Nop,           /* EP1 IN (unused) */
    EP2_IN_Callback,   /* EP2 IN (CDC data to host) */
    EP3_IN_Callback,   /* EP3 IN (CDC interrupt) */
    EP4_IN_Callback,
    EP5_IN_Callback,
    EP6_IN_Callback,
    EP7_IN_Callback,
};

/* Endpoint OUT callback function pointer array */
void (*pEpInt_OUT[7])(void) = {
    CDC_EP1_OUT_Callback,  /* EP1 OUT (CDC data from host) */
    EP2_OUT_Callback,
    EP3_OUT_Callback,
    EP4_OUT_Callback,
    EP5_OUT_Callback,
    EP6_OUT_Callback,
    EP7_OUT_Callback,
};

// Forward declarations of USB library internal functions
extern void USB_CorrectTransferLp(void);


/**
 * @brief  USB interrupt service routine (called from USB_FS_LP_IRQHandler)
 */
void USB_Istr(void)
{
    wIstr = _GetISTR();

    // Correct transfer interrupt
    if (wIstr & STS_CTRS & wInterrupt_Mask)
    {
        USB_CorrectTransferLp();
    }

    // Reset interrupt
    if (wIstr & STS_RST & wInterrupt_Mask)
    {
        _SetISTR((uint16_t)CLR_RST);
    }

    // Wakeup interrupt
    if (wIstr & STS_WKUP & wInterrupt_Mask)
    {
        _SetISTR((uint16_t)CLR_WKUP);
    }

    // Suspend interrupt
    if (wIstr & STS_SUSPD & wInterrupt_Mask)
    {
        _SetISTR((uint16_t)CLR_SUSPD);
    }

    // SOF interrupt
    if (wIstr & STS_SOF & wInterrupt_Mask)
    {
        _SetISTR((uint16_t)CLR_SOF);
        bIntPackSOF++;
    }

    // Expected SOF interrupt
    if (wIstr & STS_ESOF & wInterrupt_Mask)
    {
        _SetISTR((uint16_t)CLR_ESOF);
    }
}
