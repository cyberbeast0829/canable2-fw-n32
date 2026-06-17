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

/***
*\*\file n32h47x_48x_exti.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
***/

#ifndef __N32H47X_48X_EXTI_H__
#define __N32H47X_48X_EXTI_H__

#ifdef __cplusplus
 extern "C" {
#endif
     
#include "n32h47x_48x.h"
     
/*** EXTI Structure Definition Start ***/

/** EXTI mode enumeration **/ 
typedef enum
{
    EXTI_Mode_Event     = 0x00,
    EXTI_Mode_Interrupt = 0x04
} EXTI_ModeType;

/** EXTI Trigger enumeration **/
typedef enum
{
    EXTI_Trigger_Falling        = 0x08,
    EXTI_Trigger_Rising         = 0x0C,
    EXTI_Trigger_Rising_Falling = 0x10
} EXTI_TriggerType;

/** EXTI Init Structure definition **/
typedef struct
{
    uint32_t            EXTI_Line;      /* < Specifies the EXTI lines to be enabled or disabled */

    EXTI_ModeType       EXTI_Mode;      /* < Specifies the mode for the EXTI lines */

    EXTI_TriggerType    EXTI_Trigger;   /* < Specifies the trigger signal active edge for the EXTI lines */
    
    FunctionalState     EXTI_LineCmd;   /* Specifies the new state of the selected EXTI lines. */
} EXTI_InitType;

/*** EXTI Structure Definition End ***/


/*** EXTI Macro Definition Start ***/

/**  EXTI_Lines **/
#define EXTI_LINENONE           ((uint32_t)0x00000000U)  /** No interrupt selected **/
#define EXTI_LINE0              ((uint32_t)0x00000001U)  /** External interrupt line 0 Connected to GPIO **/
#define EXTI_LINE1              ((uint32_t)0x00000002U)  /** External interrupt line 1 Connected to GPIO **/
#define EXTI_LINE2              ((uint32_t)0x00000004U)  /** External interrupt line 2 Connected to GPIO **/
#define EXTI_LINE3              ((uint32_t)0x00000008U)  /** External interrupt line 3 Connected to GPIO **/
#define EXTI_LINE4              ((uint32_t)0x00000010U)  /** External interrupt line 4 Connected to GPIO **/
#define EXTI_LINE5              ((uint32_t)0x00000020U)  /** External interrupt line 5 Connected to GPIO **/
#define EXTI_LINE6              ((uint32_t)0x00000040U)  /** External interrupt line 6 Connected to GPIO **/
#define EXTI_LINE7              ((uint32_t)0x00000080U)  /** External interrupt line 7 Connected to GPIO **/
#define EXTI_LINE8              ((uint32_t)0x00000100U)  /** External interrupt line 8 Connected to GPIO **/
#define EXTI_LINE9              ((uint32_t)0x00000200U)  /** External interrupt line 9 Connected to GPIO **/
#define EXTI_LINE10             ((uint32_t)0x00000400U)  /** External interrupt line 10 Connected to GPIO **/
#define EXTI_LINE11             ((uint32_t)0x00000800U)  /** External interrupt line 11 Connected to GPIO **/
#define EXTI_LINE12             ((uint32_t)0x00001000U)  /** External interrupt line 12 Connected to GPIO **/
#define EXTI_LINE13             ((uint32_t)0x00002000U)  /** External interrupt line 13 Connected to GPIO **/
#define EXTI_LINE14             ((uint32_t)0x00004000U)  /** External interrupt line 14 Connected to GPIO **/
#define EXTI_LINE15             ((uint32_t)0x00008000U)  /** External interrupt line 15 Connected to GPIO **/
#define EXTI_LINE16             ((uint32_t)0x00010000U)  /** External interrupt line 16 Connected to the PVD Output **/
#define EXTI_LINE17             ((uint32_t)0x00020000U)  /** External interrupt line 17 Connected to the RTC Alarm event **/
#define EXTI_LINE18             ((uint32_t)0x00040000U)  /** External interrupt line 18 Connected to the USB Device Wakeup from suspend event **/
#define EXTI_LINE19             ((uint32_t)0x00080000U)  /** External interrupt line 19 Connected to the RTC Tamper or LSE-CSS event **/
#define EXTI_LINE20             ((uint32_t)0x00100000U)  /** External interrupt line 20 Connected to the RTC Wakeup event */
#define EXTI_LINE21             ((uint32_t)0x00200000U)  /** External interrupt line 21 Connected to COMP1 output */
#define EXTI_LINE22             ((uint32_t)0x00400000U)  /** External interrupt line 22 Connected to COMP4 output */
#define EXTI_LINE23             ((uint32_t)0x00800000U)  /** External interrupt line 23 Connected to the USB HS OTG Wakeup from suspend event */
#define EXTI_LINE24             ((uint32_t)0x01000000U)  /** External interrupt line 24 Connected to COMP7 output */
#define EXTI_LINE25             ((uint32_t)0x02000000U)  /** External interrupt line 25 Connected to the LPTIM1 Wakeup event */
#define EXTI_LINE26             ((uint32_t)0x04000000U)  /** External interrupt line 26 Connected to the LPTIM2 Wakeup event */
#define EXTI_LINE27             ((uint32_t)0x08000000U)  /** External interrupt line 27 Connected to the ETH Wakeup event */
#define EXTI_LINE28             ((uint32_t)0x10000000U)  /** External interrupt line 28 Connected to COMP2 output */
#define EXTI_LINE29             ((uint32_t)0x20000000U)  /** External interrupt line 29 Connected to COMP3 output */
#define EXTI_LINE30             ((uint32_t)0x40000000U)  /** External interrupt line 30 Connected to COMP5 output */
#define EXTI_LINE31             ((uint32_t)0x80000000U)  /** External interrupt line 31 Connected to COMP6 output */

/** EXTI_TSSEL_Line **/
#define EXTI_TSSEL_LINE_MASK    (EXTI_TS_SEL_TSSEL)  /** External interrupt line all **/
#define EXTI_TSSEL_LINE0        (EXTI_TS_SEL_EXTI0)  /** External interrupt line 0 **/
#define EXTI_TSSEL_LINE1        (EXTI_TS_SEL_EXTI1)  /** External interrupt line 1 **/
#define EXTI_TSSEL_LINE2        (EXTI_TS_SEL_EXTI2)  /** External interrupt line 2 **/
#define EXTI_TSSEL_LINE3        (EXTI_TS_SEL_EXTI3)  /** External interrupt line 3 **/
#define EXTI_TSSEL_LINE4        (EXTI_TS_SEL_EXTI4)  /** External interrupt line 4 **/
#define EXTI_TSSEL_LINE5        (EXTI_TS_SEL_EXTI5)  /** External interrupt line 5 **/
#define EXTI_TSSEL_LINE6        (EXTI_TS_SEL_EXTI6)  /** External interrupt line 6 **/
#define EXTI_TSSEL_LINE7        (EXTI_TS_SEL_EXTI7)  /** External interrupt line 7 **/
#define EXTI_TSSEL_LINE8        (EXTI_TS_SEL_EXTI8)  /** External interrupt line 8 **/
#define EXTI_TSSEL_LINE9        (EXTI_TS_SEL_EXTI9)  /** External interrupt line 9 **/
#define EXTI_TSSEL_LINE10       (EXTI_TS_SEL_EXTI10) /** External interrupt line 10 **/
#define EXTI_TSSEL_LINE11       (EXTI_TS_SEL_EXTI11) /** External interrupt line 11 **/
#define EXTI_TSSEL_LINE12       (EXTI_TS_SEL_EXTI12) /** External interrupt line 12 **/
#define EXTI_TSSEL_LINE13       (EXTI_TS_SEL_EXTI13) /** External interrupt line 13 **/
#define EXTI_TSSEL_LINE14       (EXTI_TS_SEL_EXTI14) /** External interrupt line 14 **/
#define EXTI_TSSEL_LINE15       (EXTI_TS_SEL_EXTI15) /** External interrupt line 15 **/

/*** EXTI Macro Definition End ***/

/** EXTI Driving Functions Declaration **/
void EXTI_DeInit(void);
void EXTI_InitPeripheral(EXTI_InitType* EXTI_InitStruct);
void EXTI_InitStruct(EXTI_InitType* EXTI_InitStruct);
void EXTI_TriggerSWInt(uint32_t EXTI_Line);
FlagStatus EXTI_GetStatusFlag(uint32_t EXTI_Line);
void EXTI_ClrStatusFlag(uint32_t EXTI_Line);
INTStatus EXTI_GetITStatus(uint32_t EXTI_Line);
void EXTI_ClrITPendBit(uint32_t EXTI_Line);
void EXTI_RTCTimeStampSel(uint32_t EXTI_TSSEL_Line);


#ifdef __cplusplus
}
#endif

#endif /* __N32H47X_48X_EXTI_H__ */

