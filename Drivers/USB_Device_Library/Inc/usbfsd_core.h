/**
*     Copyright (c) 2023, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
*\*\file usbfsd_core.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/
#ifndef __USBFSD_CORE_H__
#define __USBFSD_CORE_H__

#include "n32h47x_48x.h"

typedef enum _CONTROL_STATE
{
    WaitSetup,      /* 0 */
    SettingUp,      /* 1 */
    InData,         /* 2 */
    OutData,        /* 3 */
    LastInData,     /* 4 */
    LastOutData,    /* 5 */
    WaitStatusIn,   /* 6 */
    WaitStatusOut,  /* 7 */
    Stalled,        /* 8 */
    Pause           /* 9 */
} USB_ControlState; /* The state machine states of a control pipe */

typedef struct OneDescriptor
{
    uint8_t* Descriptor;
    uint16_t Descriptor_Size;
} USB_OneDescriptor, *PONE_DESCRIPTOR;
/* All the request process routines return a value of this type
   If the return value is not SUCCESS or NOT_READY,
   the software will STALL the correspond endpoint */
typedef enum _RESULT
{
    Success = 0, /* Process successfully */
    Error,
    UnSupport,
    Not_Ready /* The process has not been finished, endpoint will be
                     NAK to further request */
} USB_Result;

/*-*-*-*-*-*-*-*-*-*-* Definitions for endpoint level -*-*-*-*-*-*-*-*-*-*-*-*/
typedef struct _ENDPOINT_INFO
{
    /* When send data out of the device,
     CopyData() is used to get data buffer 'Length' bytes data
     if Length is 0,
      CopyData() returns the total length of the data
      if the request is not supported, returns 0
      (NEW Feature )
       if CopyData() returns -1, the calling routine should not proceed
       further and will resume the SETUP process by the class device
     if Length is not 0,
      CopyData() returns a pointer to indicate the data location
     Usb_wLength is the data remain to be sent,
     Usb_wOffset is the Offset of original data
    When receive data from the host,
     CopyData() is used to get user data buffer which is capable
     of Length bytes data to copy data from the endpoint buffer.
     if Length is 0,
      CopyData() returns the available data length,
     if Length is not 0,
      CopyData() returns user buffer address
     Usb_rLength is the data remain to be received,
     Usb_rPointer is the Offset of data buffer
    */
    uint16_t Usb_wLength;
    uint16_t Usb_wOffset;
    uint16_t PacketSize;
    uint8_t* (*CopyData)(uint16_t Length);
} USB_EndpointMess;

/*-*-*-*-*-*-*-*-*-*-*-* Definitions for device level -*-*-*-*-*-*-*-*-*-*-*-*/

typedef struct _DEVICE
{
    uint8_t TotalEndpoint;      /* Number of endpoints that are used */
    uint8_t TotalConfiguration; /* Number of configuration available */
} USB_Device;

typedef union
{
    uint16_t w;
    struct BW
    {
        uint8_t bb1;
        uint8_t bb0;
    } bw;
} uint16_t_uint8_t;

typedef struct _DEVICE_INFO
{
    uint8_t bmRequestType;     /* bmRequestType */
    uint8_t bRequest;          /* bRequest */
    uint16_t_uint8_t wValues;  /* wValue */
    uint16_t_uint8_t wIndexs;  /* wIndex */
    uint16_t_uint8_t wLengths; /* wLength */

    uint8_t CtrlState; /* of type USB_ControlState */
    uint8_t CurrentFeature;
    uint8_t CurrentConfiguration;    /* Selected configuration */
    uint8_t CurrentInterface;        /* Selected interface of current configuration */
    uint8_t CurrentAlternateSetting; /* Selected Alternate Setting of current
                                        interface*/

    USB_EndpointMess Ctrl_Info;
} USB_DeviceMess;

typedef struct _DEVICE_PROP
{
    void (*Init)(void);  /* Initialize the device */
    void (*Reset)(void); /* Reset routine of this device */

    /* Device dependent process after the status stage */
    void (*Process_Status_IN)(void);
    void (*Process_Status_OUT)(void);

    /* Procedure of process on setup stage of a class specified request with data stage */
    /* All class specified requests with data stage are processed in Class_Data_Setup
     Class_Data_Setup()
      responses to check all special requests and fills USB_EndpointMess
      according to the request
      If IN tokens are expected, then wLength & wOffset will be filled
      with the total transferring bytes and the starting position
      If OUT tokens are expected, then rLength & rOffset will be filled
      with the total expected bytes and the starting position in the buffer

      If the request is valid, Class_Data_Setup returns SUCCESS, else UNSUPPORT

     CAUTION:
      Since GET_CONFIGURATION & GET_INTERFACE are highly related to
      the individual classes, they will be checked and processed here.
    */
    USB_Result (*Class_Data_Setup)(uint8_t RequestNo);

    /* Procedure of process on setup stage of a class specified request without data stage */
    /* All class specified requests without data stage are processed in Class_NoData_Setup
     Class_NoData_Setup
      responses to check all special requests and perform the request

     CAUTION:
      Since SET_CONFIGURATION & SET_INTERFACE are highly related to
      the individual classes, they will be checked and processed here.
    */
    USB_Result (*Class_NoData_Setup)(uint8_t RequestNo);

    /*Class_Get_Interface_Setting
     This function is used by the file usbfsd_core.c to test if the selected Interface
     and Alternate Setting (uint8_t Interface, uint8_t AlternateSetting) are supported by
     the application.
     This function is writing by user. It should return "SUCCESS" if the Interface
     and Alternate Setting are supported by the application or "UNSUPPORT" if they
     are not supported. */

    USB_Result (*Class_Get_Interface_Setting)(uint8_t Interface, uint8_t AlternateSetting);

    uint8_t* (*GetDeviceDescriptor)(uint16_t Length);
    uint8_t* (*GetConfigDescriptor)(uint16_t Length);
    uint8_t* (*GetStringDescriptor)(uint16_t Length);

    /* This field is not used in current library version. It is kept only for
     compatibility with previous versions */
    void* RxEP_buffer;

    uint8_t MaxPacketSize;

} DEVICE_PROP;

typedef struct _USER_STANDARD_REQUESTS
{
    void (*User_GetConfiguration)(void);   /* Get Configuration */
    void (*User_SetConfiguration)(void);   /* Set Configuration */
    void (*User_GetInterface)(void);       /* Get Interface */
    void (*User_SetInterface)(void);       /* Set Interface */
    void (*User_GetStatus)(void);          /* Get Status */
    void (*User_ClearFeature)(void);       /* Clear Feature */
    void (*User_SetEndPointFeature)(void); /* Set Endpoint Feature */
    void (*User_SetDeviceFeature)(void);   /* Set Device Feature */
    void (*User_SetDeviceAddress)(void);   /* Set Device Address */
} USER_STANDARD_REQUESTS;

#define Type_Recipient (pInformation->bmRequestType & (REQUEST_TYPE | RECIPIENT))

#define Usb_rLength Usb_wLength
#define Usb_rOffset Usb_wOffset

#define USBwValue   wValues.w
#define USBwValue0  wValues.bw.bb0
#define USBwValue1  wValues.bw.bb1
#define USBwIndex   wIndexs.w
#define USBwIndex0  wIndexs.bw.bb0
#define USBwIndex1  wIndexs.bw.bb1
#define USBwLength  wLengths.w
#define USBwLength0 wLengths.bw.bb0
#define USBwLength1 wLengths.bw.bb1

uint8_t USB_ProcessSetup0(void);
uint8_t USB_ProcessPost0(void);
uint8_t USB_ProcessOut0(void);
uint8_t USB_ProcessIn0(void);

USB_Result Standard_SetEndPointFeature(void);
USB_Result Standard_SetDeviceFeature(void);

uint8_t* Standard_GetConfiguration(uint16_t Length);
USB_Result Standard_SetConfiguration(void);
uint8_t* Standard_GetInterface(uint16_t Length);
USB_Result Standard_SetInterface(void);
uint8_t* Standard_GetDescriptorData(uint16_t Length, PONE_DESCRIPTOR pDesc);

uint8_t* Standard_GetStatus(uint16_t Length);
USB_Result Standard_ClearFeature(void);
void USB_SetDeviceAddress(uint8_t);
void USB_ProcessNop(void);

extern DEVICE_PROP Device_Property;
extern USER_STANDARD_REQUESTS User_Standard_Requests;
extern USB_Device Device_Table;
extern USB_DeviceMess Device_Info;

/* cells saving status during interrupt servicing */
extern __IO uint16_t SaveRState;
extern __IO uint16_t SaveTState;

#endif /* __USBFSD_CORE_H__ */
