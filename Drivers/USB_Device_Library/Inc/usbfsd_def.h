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
*\*\file usbfsd_def.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/
#ifndef __USBFSD_DEF_H__
#define __USBFSD_DEF_H__


typedef enum _RECIPIENT_TYPE
{
    DEVICE_RECIPIENT,    /* Recipient device */
    INTERFACE_RECIPIENT, /* Recipient interface */
    ENDPOINT_RECIPIENT,  /* Recipient endpoint */
    OTHER_RECIPIENT
} RECIPIENT_TYPE;

typedef enum _STANDARD_REQUESTS
{
    GET_STATUS = 0,
    CLR_FEATURE,
    RESERVED1,
    SET_FEATURE,
    RESERVED2,
    SET_ADDRESS,
    GET_DESCRIPTOR,
    SET_DESCRIPTOR,
    GET_CONFIGURATION,
    SET_CONFIGURATION,
    GET_INTERFACE,
    SET_INTERFACE,
    TOTAL_SREQUEST, /* Total number of Standard request */
    SYNCH_FRAME = 12
} STANDARD_REQUESTS;

/* Definition of "USBwValue" */
typedef enum _DESCRIPTOR_TYPE
{
    DEVICE_DESCRIPTOR = 1,
    CONFIG_DESCRIPTOR,
    STRING_DESCRIPTOR,
    INTERFACE_DESCRIPTOR,
    ENDPOINT_DESCRIPTOR
} DESCRIPTOR_TYPE;

/* Feature selector of a SET_FEATURE or CLR_FEATURE */
typedef enum _FEATURE_SELECTOR
{
    ENDPOINT_STALL,
    DEVICE_REMOTE_WAKEUP
} FEATURE_SELECTOR;

/* Definition of "bmRequestType" */
#define REQUEST_TYPE     0x60 /* Mask to get request type */
#define STANDARD_REQUEST 0x00 /* Standard request */
#define CLASS_REQUEST    0x20 /* Class request */
#define VENDOR_REQUEST   0x40 /* Vendor request */

#define RECIPIENT 0x1F /* Mask to get recipient */


#endif /* __USBFSD_DEF_H__ */
