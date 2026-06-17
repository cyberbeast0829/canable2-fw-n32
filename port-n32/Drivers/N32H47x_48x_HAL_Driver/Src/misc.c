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
*\*\file misc.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/
#include "misc.h"


/**
*\*\name    NVIC_PriorityGroupConfig
*\*\fun     Configures the priority grouping: pre-emption priority and subpriority.
*\*\param   NVIC_PriorityGroup :
*\*\            - NVIC_PriorityGroup_0    0 bits for pre-emption priority 4 bits for subpriority
*\*\            - NVIC_PriorityGroup_1    1 bits for pre-emption priority 3 bits for subpriority
*\*\            - NVIC_PriorityGroup_2    2 bits for pre-emption priority 2 bits for subpriority
*\*\            - NVIC_PriorityGroup_3    3 bits for pre-emption priority 1 bits for subpriority
*\*\            - NVIC_PriorityGroup_4    4 bits for pre-emption priority 0 bits for subpriority
*\*\return  none
**/
void NVIC_PriorityGroupConfig(uint32_t NVIC_PriorityGroup)
{
    /* Set the PRIGROUP[10:8] bits according to NVIC_PriorityGroup value */
    SCB->AIRCR = AIRCR_VECTKEY_MASK | NVIC_PriorityGroup;
}

/**
*\*\name    NVIC_Init
*\*\fun     Initializes the NVIC peripheral according to the specified parameters in the NVIC_structure_initializes.
*\*\param   NVIC_InitStruct :
*\*\              - NVIC_IRQChannel :
*\*\                   -  IRQn_Type    Interrupt Number Definition
*\*\        if NVIC_PriorityGroup is NVIC_PriorityGroup_0 :
*\*\              - NVIC_IRQChannelPreemptionPriority :
*\*\                   -  NVIC_PRE_PRIORITY_0
*\*\              - NVIC_IRQChannelSubPriority :
*\*\                   -  NVIC_SUB_PRIORITY_0
*\*\                   -  NVIC_SUB_PRIORITY_1
*\*\                   -  NVIC_SUB_PRIORITY_2
*\*\                   -  NVIC_SUB_PRIORITY_3
*\*\                   -  NVIC_SUB_PRIORITY_4
*\*\                   -  NVIC_SUB_PRIORITY_5
*\*\                   -  NVIC_SUB_PRIORITY_6
*\*\                   -  NVIC_SUB_PRIORITY_7
*\*\                   -  NVIC_SUB_PRIORITY_8
*\*\                   -  NVIC_SUB_PRIORITY_9
*\*\                   -  NVIC_SUB_PRIORITY_10
*\*\                   -  NVIC_SUB_PRIORITY_11
*\*\                   -  NVIC_SUB_PRIORITY_12
*\*\                   -  NVIC_SUB_PRIORITY_13
*\*\                   -  NVIC_SUB_PRIORITY_14
*\*\                   -  NVIC_SUB_PRIORITY_15
*\*\        if NVIC_PriorityGroup is NVIC_PriorityGroup_1 :
*\*\              - NVIC_IRQChannelPreemptionPriority :
*\*\                   -  NVIC_PRE_PRIORITY_0
*\*\                   -  NVIC_PRE_PRIORITY_1
*\*\              - NVIC_IRQChannelSubPriority :
*\*\                   -  NVIC_SUB_PRIORITY_0 to NVIC_SUB_PRIORITY_7
*\*\        if NVIC_PriorityGroup is NVIC_PriorityGroup_2 :
*\*\              - NVIC_IRQChannelPreemptionPriority :
*\*\                   -  NVIC_PRE_PRIORITY_0 to NVIC_PRE_PRIORITY_3
*\*\              - NVIC_IRQChannelSubPriority :
*\*\                   -  NVIC_SUB_PRIORITY_0 to NVIC_SUB_PRIORITY_3
*\*\        if NVIC_PriorityGroup is NVIC_PriorityGroup_3 :
*\*\              - NVIC_IRQChannelPreemptionPriority :
*\*\                   -  NVIC_PRE_PRIORITY_0 to NVIC_PRE_PRIORITY_7
*\*\              - NVIC_IRQChannelSubPriority :
*\*\                   -  NVIC_SUB_PRIORITY_0
*\*\                   -  NVIC_SUB_PRIORITY_1
*\*\        if NVIC_PriorityGroup is NVIC_PriorityGroup_4 :
*\*\              - NVIC_IRQChannelPreemptionPriority :
*\*\                   -  NVIC_PRE_PRIORITY_0
*\*\                   -  NVIC_PRE_PRIORITY_1
*\*\                   -  NVIC_PRE_PRIORITY_2
*\*\                   -  NVIC_PRE_PRIORITY_3
*\*\                   -  NVIC_PRE_PRIORITY_4
*\*\                   -  NVIC_PRE_PRIORITY_5
*\*\                   -  NVIC_PRE_PRIORITY_6
*\*\                   -  NVIC_PRE_PRIORITY_7
*\*\                   -  NVIC_PRE_PRIORITY_8
*\*\                   -  NVIC_PRE_PRIORITY_9
*\*\                   -  NVIC_PRE_PRIORITY_10
*\*\                   -  NVIC_PRE_PRIORITY_11
*\*\                   -  NVIC_PRE_PRIORITY_12
*\*\                   -  NVIC_PRE_PRIORITY_13
*\*\                   -  NVIC_PRE_PRIORITY_14
*\*\                   -  NVIC_PRE_PRIORITY_15
*\*\              - NVIC_IRQChannelSubPriority :
*\*\                   -  NVIC_SUB_PRIORITY_0
*\*\              - NVIC_IRQChannelCmd :
*\*\                   -  ENABLE
*\*\                   -  DISABLE
*\*\return  none
**/
void NVIC_Init(NVIC_InitType* NVIC_InitStruct)
{
    uint32_t tmppriority;
    uint32_t tmppre;
    uint32_t tmpsub = 0x0FU;

    if (NVIC_InitStruct->NVIC_IRQChannelCmd != DISABLE)
    {
        /* Compute the Corresponding IRQ Priority --------------------------------*/
        tmppriority = (0x700U - ((SCB->AIRCR) & (uint32_t)0x700U)) >> 0x08U;
        tmppre      = (0x4U - tmppriority) & ((uint32_t)0x07U);
        tmpsub      = tmpsub >> tmppriority;

        tmppriority = (uint32_t)NVIC_InitStruct->NVIC_IRQChannelPreemptionPriority << tmppre;
        tmppriority |= NVIC_InitStruct->NVIC_IRQChannelSubPriority & tmpsub;
        tmppriority = tmppriority << 0x04;

        NVIC->IP[NVIC_InitStruct->NVIC_IRQChannel] = (uint8_t)tmppriority;

        /* Enable the Selected IRQ Channels --------------------------------------*/
        NVIC->ISER[NVIC_InitStruct->NVIC_IRQChannel >> 0x05U] = (uint32_t)0x01U
                                                               << (NVIC_InitStruct->NVIC_IRQChannel & (uint8_t)0x1FU);
    }
    else
    {
        /* Disable the Selected IRQ Channels -------------------------------------*/
        NVIC->ICER[NVIC_InitStruct->NVIC_IRQChannel >> 0x05] = (uint32_t)0x01
                                                               << (NVIC_InitStruct->NVIC_IRQChannel & (uint8_t)0x1F);
    }
}

/**
*\*\name    NVIC_SetVectorTable
*\*\fun     Sets the vector table location and Offset.
*\*\param   NVIC_vecter_table specifies if the vector table is in RAM or FLASH memory.
*\*\        This parameter can be one of the following values:
*\*\            - NVIC_VectTab_RAM
*\*\            - NVIC_VectTab_FLASH
*\*\param   offset Vector Table base offset field. This value must be a multiple of 0x200.
*\*\return  none
**/
void NVIC_SetVectorTable(uint32_t NVIC_VectTab, uint32_t Offset)
{
    SCB->VTOR = NVIC_VectTab | (Offset & (uint32_t)0x1FFFFF80U);
}


/**
*\*\name    NVIC_SystemLPConfig
*\*\fun     Selects the condition for the system to enter low power mode.
*\*\param   LowPowerMode    Specifies the new mode for the system to enter low power mode.
*\*\        This parameter can be one of the following values:
*\*\            - NVIC_LP_SEVONPEND
*\*\            - NVIC_LP_SLEEPDEEP
*\*\            - NVIC_LP_SLEEPONEXIT
*\*\param   - Cmd :
*\*\             -  ENABLE
*\*\             -  DISABLE
*\*\return  none
**/
void NVIC_SystemLPConfig(uint8_t LowPowerMode, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        SCB->SCR |= LowPowerMode;
    }
    else
    {
        SCB->SCR &= (uint32_t)(~(uint32_t)LowPowerMode);
    }
}

/**
*\*\name  SysTick_CLKSourceConfig
*\*\fun   Configures the SysTick clock source.
*\*\param SysTick_CLKSource :
*\*\       - SysTick_CLKSource_HCLK_Div8    External clock selected as SysTick clock source.
*\*\       - SysTick_CLKSource_HCLK         AHB clock selected as SysTick clock source.
*\*\return  none
 */
void SysTick_CLKSourceConfig(uint32_t SysTick_CLKSource)
{
    if (SysTick_CLKSource == SysTick_CLKSource_HCLK)
    {
        SysTick->CTRL |= SysTick_CLKSource_HCLK;
    }
    else
    {
        SysTick->CTRL &= SysTick_CLKSource_HCLK_Div8;
    }
}


