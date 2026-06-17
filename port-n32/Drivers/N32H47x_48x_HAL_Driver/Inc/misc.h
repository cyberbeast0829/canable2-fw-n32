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
*\*\file misc.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/
#ifndef __MISC_H__
#define __MISC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32h47x_48x.h"

/** MISC Driving Functions Declaration **/

/** NVIC Init Structure definition **/
typedef struct
{
    uint8_t NVIC_IRQChannel; /* Specifies the IRQ channel to be enabled or disabled. */

    uint8_t NVIC_IRQChannelPreemptionPriority; /* Specifies the pre-emption priority for the IRQ channel
                                                  specified in NVIC_IRQChannel. */

    uint8_t NVIC_IRQChannelSubPriority; /* Specifies the subpriority level for the IRQ channel specified
                                           in NVIC_IRQChannel. */

    FunctionalState NVIC_IRQChannelCmd; /* Specifies whether the IRQ channel defined in NVIC_IRQChannel
                                           will be enabled or disabled. */
} NVIC_InitType;

/** MISC driver modules **/
#define AIRCR_VECTKEY_MASK       ((uint32_t)0x05FA0000U) /* access key */

/** Vector_Table_Base **/
#define NVIC_VectTab_RAM         ((uint32_t)0x20000000U) /* RAM start address*/
#define NVIC_VectTab_FLASH       ((uint32_t)0x08000000U) /* FLASH start address*/

/** LowPowerMode **/
#define NVIC_LP_SEVONPEND        (SCB_SCR_SEVONPEND)
#define NVIC_LP_SLEEPDEEP        (SCB_SCR_SLEEPDEEP)
#define NVIC_LP_SLEEPONEXIT      (SCB_SCR_SLEEPONEXIT)

/** Preemption_Sub_Priority_Group **/
#define NVIC_PriorityGroup_0 (SCB_AIRCR_PRIGROUP7) /* 0 bits for pre-emption priority 4 bits for subpriority */
#define NVIC_PriorityGroup_1 (SCB_AIRCR_PRIGROUP6) /* 1 bits for pre-emption priority 3 bits for subpriority */
#define NVIC_PriorityGroup_2 (SCB_AIRCR_PRIGROUP5) /* 2 bits for pre-emption priority 2 bits for subpriority */
#define NVIC_PriorityGroup_3 (SCB_AIRCR_PRIGROUP4) /* 3 bits for pre-emption priority 1 bits for subpriority */
#define NVIC_PriorityGroup_4 (SCB_AIRCR_PRIGROUP3) /* 4 bits for pre-emption priority 0 bits for subpriority */

/** Preemption_Priority_Group **/
#define NVIC_PRE_PRIORITY_0           ((uint8_t)0x00U)
#define NVIC_PRE_PRIORITY_1           ((uint8_t)0x01U)
#define NVIC_PRE_PRIORITY_2           ((uint8_t)0x02U)
#define NVIC_PRE_PRIORITY_3           ((uint8_t)0x03U)
#define NVIC_PRE_PRIORITY_4           ((uint8_t)0x04U)
#define NVIC_PRE_PRIORITY_5           ((uint8_t)0x05U)
#define NVIC_PRE_PRIORITY_6           ((uint8_t)0x06U)
#define NVIC_PRE_PRIORITY_7           ((uint8_t)0x07U)
#define NVIC_PRE_PRIORITY_8           ((uint8_t)0x08U)
#define NVIC_PRE_PRIORITY_9           ((uint8_t)0x09U)
#define NVIC_PRE_PRIORITY_10          ((uint8_t)0x0AU)
#define NVIC_PRE_PRIORITY_11          ((uint8_t)0x0BU)
#define NVIC_PRE_PRIORITY_12          ((uint8_t)0x0CU)
#define NVIC_PRE_PRIORITY_13          ((uint8_t)0x0DU)
#define NVIC_PRE_PRIORITY_14          ((uint8_t)0x0EU)
#define NVIC_PRE_PRIORITY_15          ((uint8_t)0x0FU)

/** Sub_Priority_Group **/
#define NVIC_SUB_PRIORITY_0           ((uint8_t)0x00U)
#define NVIC_SUB_PRIORITY_1           ((uint8_t)0x01U)
#define NVIC_SUB_PRIORITY_2           ((uint8_t)0x02U)
#define NVIC_SUB_PRIORITY_3           ((uint8_t)0x03U)
#define NVIC_SUB_PRIORITY_4           ((uint8_t)0x04U)
#define NVIC_SUB_PRIORITY_5           ((uint8_t)0x05U)
#define NVIC_SUB_PRIORITY_6           ((uint8_t)0x06U)
#define NVIC_SUB_PRIORITY_7           ((uint8_t)0x07U)
#define NVIC_SUB_PRIORITY_8           ((uint8_t)0x08U)
#define NVIC_SUB_PRIORITY_9           ((uint8_t)0x09U)
#define NVIC_SUB_PRIORITY_10          ((uint8_t)0x0AU)
#define NVIC_SUB_PRIORITY_11          ((uint8_t)0x0BU)
#define NVIC_SUB_PRIORITY_12          ((uint8_t)0x0CU)
#define NVIC_SUB_PRIORITY_13          ((uint8_t)0x0DU)
#define NVIC_SUB_PRIORITY_14          ((uint8_t)0x0EU)
#define NVIC_SUB_PRIORITY_15          ((uint8_t)0x0FU)

/** SysTick_CLKSource **/
#define SysTick_CLKSource_HCLK_Div8  (~SysTick_CTRL_CLKSOURCE)
#define SysTick_CLKSource_HCLK       (SysTick_CTRL_CLKSOURCE)

void NVIC_PriorityGroupConfig(uint32_t NVIC_PriorityGroup);
void NVIC_Init(NVIC_InitType* NVIC_InitStruct);
void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset);
void NVIC_SystemLPConfig(uint8_t LowPowerMode, FunctionalState Cmd);
void SysTick_CLKSourceConfig(uint32_t SysTick_CLKSource);

#ifdef __cplusplus
}
#endif

#endif /* __MISC_H__ */


