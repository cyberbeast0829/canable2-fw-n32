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
 * @file n32h47x_48x_adc.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
 */
#include "n32h47x_48x_adc.h"
#include "n32h47x_48x_rcc.h"


/* bit data handler */
#define BIT_JUDGE_AND_HANDLER(IS_ENABLE, BIT_MASK)    (((IS_ENABLE) != DISABLE ) ? (BIT_MASK) : (0x00000000U))

#define CTRL1_CLR_MASK          ((uint32_t)0x00000F81U)
#define CTRL2_CLR_MASK          ((uint32_t)0x013F0032U)
#define CTRL3_CLR_MASK          ((uint32_t)0x00000003U)
#define RSEQ3_CLR_MASK          ((uint32_t)0x1E000000U)

#define ALL_ADC_ENALBE_MASK     ((uint32_t)0x00001E00U)
#define ADCBUF_CTRL             ((uint32_t)0x40010000U + 0x4C)

/** ADC Driving Functions Declaration **/ 

/**
*\*\name    ADC_DeInit.
*\*\fun     Reset the ADC registers.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\return  none
**/
void ADC_DeInit(ADC_Module* ADCx)
{
    __IO uint32_t delay = 0x216;
    if (ADCx == ADC1)
    {
        RCC_EnableAHBPeriphReset(RCC_AHB_PERIPHRST_ADC1);
    }
    else if (ADCx == ADC2)
    {
        RCC_EnableAHBPeriphReset(RCC_AHB_PERIPHRST_ADC2);
    }
    else if (ADCx == ADC3)
    {
        RCC_EnableAHBPeriphReset(RCC_AHB_PERIPHRST_ADC3);
    }
    else if (ADCx == ADC4)
    {
        RCC_EnableAHBPeriphReset(RCC_AHB_PERIPHRST_ADC4);
    }
    else
    {
        /*no process*/
    }
    /*Delay about 20us(on the condition @240M systick) to wait for the completion of the ADC reset.Exactly, it need at least 8 ADC sampling clock after ADC reset.
      for example, When the ADC's sampling clock is 80M, the actual latency just need 8*(1/80)us. */
    for(; delay != 0; delay--);
    /*When all ADCs are reset, you must disable ADC BUF.*/
    if((RCC->AHB1PCLKEN&ALL_ADC_ENALBE_MASK) == 0)
    {
        /* ADC BUF Disable  */
        *(uint32_t *)ADCBUF_CTRL  &= (~(0x01U << 13)); 
    }
    else
    {
        /*no process*/
    }
}

/**
*\*\name    ADC_Init.
*\*\fun     Initializes the ADCx peripheral according to the specified parameters in the ADC_InitStruct.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   ADC_InitStruct :
*\*\          - WorkMode
*\*\             - ADC_WORKMODE_INDEPENDENT                  
*\*\             - ADC_WORKMODE_DUAL_REG_INJECT_SIMULT  
*\*\             - ADC_WORKMODE_DUAL_REG_SIMULT_ALTER_TRIG  
*\*\             - ADC_WORKMODE_DUAL_INJ_SIMULT_INTERL 
*\*\             - ADC_WORKMODE_DUAL_INJ_SIMULT   
*\*\             - ADC_WORKMODE_DUAL_REG_SIMULT    
*\*\             - ADC_WORKMODE_DUAL_INTERL     
*\*\             - ADC_WORKMODE_DUAL_ALTER_TRIG  
*\*\             - ADC_WORKMODE_TRIPPLE_REG_INJECT_SIMULT
*\*\             - ADC_WORKMODE_TRIPPLE_REG_SIMULT_ALTER_TRIG 
*\*\             - ADC_WORKMODE_TRIPPLE_INJ_SIMULT_INTERL
*\*\             - ADC_WORKMODE_TRIPPLE_INJ_SIMULT    
*\*\             - ADC_WORKMODE_TRIPPLE_REG_SIMULT  
*\*\             - ADC_WORKMODE_TRIPPLE_INTERL      
*\*\             - ADC_WORKMODE_TRIPPLE_ALTER_TRIG 
*\*\          - MultiChEn
*\*\             - ENABLE
*\*\             - DISABLE
*\*\          - ContinueConvEn
*\*\             - ENABLE
*\*\             - DISABLE
*\*\          - ExtTrigSelect
*\*\             - ADC_EXT_TRIG_REG_CONV_ATIM1_CC4     
*\*\             - ADC_EXT_TRIG_REG_CONV_ATIM1_TRGO     
*\*\             - ADC_EXT_TRIG_REG_CONV_ATIM1_TRGO2    
*\*\             - ADC_EXT_TRIG_REG_CONV_ATIM2_CC4      
*\*\             - ADC_EXT_TRIG_REG_CONV_ATIM2_TRGO     
*\*\             - ADC_EXT_TRIG_REG_CONV_ATIM2_TRGO2    
*\*\             - ADC_EXT_TRIG_REG_CONV_ATIM3_CC4      
*\*\             - ADC_EXT_TRIG_REG_CONV_ATIM3_TRGO     
*\*\             - ADC_EXT_TRIG_REG_CONV_ATIM3_TRGO2          
*\*\             - ADC_EXT_TRIG_REG_CONV_GTIM1_CC4            
*\*\             - ADC_EXT_TRIG_REG_CONV_GTIM2_CC4             
*\*\             - ADC_EXT_TRIG_REG_CONV_GTIM3_CC4             
*\*\             - ADC_EXT_TRIG_REG_CONV_GTIM4_CC4             
*\*\             - ADC_EXT_TRIG_REG_CONV_GTIM5_CC4             
*\*\             - ADC_EXT_TRIG_REG_CONV_GTIM6_CC4             
*\*\             - ADC_EXT_TRIG_REG_CONV_GTIM7_CC4             
*\*\             - ADC_EXT_TRIG_REG_CONV_GTIM8_CC4             
*\*\             - ADC_EXT_TRIG_REG_CONV_GTIM9_CC4             
*\*\             - ADC_EXT_TRIG_REG_CONV_GTIM10_CC4            
*\*\             - ADC_EXT_TRIG_REG_CONV_GTIM1_TRGO            
*\*\             - ADC_EXT_TRIG_REG_CONV_GTIM2_TRGO            
*\*\             - ADC_EXT_TRIG_REG_CONV_GTIM3_TRGO            
*\*\             - ADC_EXT_TRIG_REG_CONV_GTIM4_TRGO            
*\*\             - ADC_EXT_TRIG_REG_CONV_GTIM5_TRGO            
*\*\             - ADC_EXT_TRIG_REG_CONV_GTIM6_TRGO            
*\*\             - ADC_EXT_TRIG_REG_CONV_GTIM7_TRGO            
*\*\             - ADC_EXT_TRIG_REG_CONV_GTIM8_TRGO            
*\*\             - ADC_EXT_TRIG_REG_CONV_GTIM9_TRGO            
*\*\             - ADC_EXT_TRIG_REG_CONV_GTIM10_TRGO           
*\*\             - ADC_EXT_TRIG_REG_CONV_SHRTIM_TRGO1          
*\*\             - ADC_EXT_TRIG_REG_CONV_SHRTIM_TRGO2          
*\*\             - ADC_EXT_TRIG_REG_CONV_SHRTIM_TRGO3          
*\*\             - ADC_EXT_TRIG_REG_CONV_SHRTIM_TRGO4          
*\*\             - ADC_EXT_TRIG_REG_CONV_SHRTIM_TRGO5          
*\*\             - ADC_EXT_TRIG_REG_CONV_SHRTIM_TRGO6          
*\*\             - ADC_EXT_TRIG_REG_CONV_SHRTIM_TRGO7          
*\*\             - ADC_EXT_TRIG_REG_CONV_SHRTIM_TRGO8          
*\*\             - ADC_EXT_TRIG_REG_CONV_SHRTIM_TRGO9          
*\*\             - ADC_EXT_TRIG_REG_CONV_SHRTIM_TRGO10         
*\*\             - ADC_EXT_TRIG_REG_CONV_LPTIM1_OUT            
*\*\             - ADC_EXT_TRIG_REG_CONV_LPTIM2_OUT            
*\*\             - ADC_EXT_TRIG_REG_CONV_EXT_INT0_15           
*\*\             - ADC_EXT_TRIG_REG_CONV_SOFTWARE 
*\*\          - DatAlign
*\*\             - ADC_DAT_ALIGN_R
*\*\             - ADC_DAT_ALIGN_L
*\*\          - Resolution
*\*\             - ADC_DATA_RES_12BIT
*\*\             - ADC_DATA_RES_10BIT
*\*\             - ADC_DATA_RES_8BIT
*\*\             - ADC_DATA_RES_6BIT
*\*\          - ChsNumber: This parameter must be between 1 to 16. 
*\*\return  none
**/
void ADC_Init(ADC_Module* ADCx, ADC_InitType* ADC_InitStruct)
{
    uint32_t tempreg1;
    uint8_t tempreg2;
	
    /* ADC BUF Enable  */
    *(uint32_t *)ADCBUF_CTRL  |= (0x01U << 13); 
    /*---------------------------- ADCx PCTRL Configuration -----------------*/
    /* Get the ADCx PCTRL value */
    tempreg1 = ADCx->PCTRL;
    /* clear ADC_PCTRL register EXPEN RANGESEL VREFLDOEN bits */
    tempreg1 &= (~(ADC_PCTRL_EXPEN_MASK | ADC_PCTRL_RANGESEL_MASK | ADC_PCTRL_VREFLDOEN_MASK));
    /* Set EXPEN RANGESEL VREFLDOEN select bits */
    tempreg1 |= ADC_EXTERN_POWER_SUPPORT;
     /* Store the new register value */
    ADCx->PCTRL = tempreg1;
    /*---------------------------- ADCx CTRL1 Configuration -----------------*/
    /* Get the ADCx CTRL1 value */
    tempreg1 = ADCx->CTRL1;
    /* Clear MUTIMODE and SCANMD bits */
    tempreg1 &= (~CTRL1_CLR_MASK);
    /* Configure ADCx: Muti mode and scan conversion mode */
    /* Set MUTIMOD bits according to WorkMode value */
    /* Set SCANMD bit according to MultiChEn value */
    tempreg1 |= (uint32_t)(ADC_InitStruct->WorkMode | (uint32_t)ADC_InitStruct->MultiChEn );
    /* Write to ADCx CTRL1 */
    ADCx->CTRL1 = tempreg1;

    /*---------------------------- ADCx CTRL2 Configuration -----------------*/
    /* Get the ADCx CTRL2 value */
    tempreg1 = ADCx->CTRL2;
    /* Clear CTU, ALIG ,EXTPRSEL and EXTRSEL bits */
    tempreg1 &= (~CTRL2_CLR_MASK);
    /* Set ALIGN bit according to DatAlign value */
    /* Set EXTSEL and EXTPRSEL bits according to ExtTrigSelect value */
    /* Set CTU bit according to ContinueConvEn value */
    tempreg1 |= (uint32_t)(ADC_InitStruct->DatAlign | ADC_InitStruct->ExtTrigSelect
                          | ((uint32_t)ADC_InitStruct->ContinueConvEn << 1));
    /* Write to ADCx CTRL2 */
    ADCx->CTRL2 = tempreg1;

    /*---------------------------- ADCx CTRL3 Configuration -----------------*/
    /* Get the ADCx CTRL3 value */
    tempreg1 = ADCx->CTRL3;
    /* Clear L bits */
    tempreg1 &= (~CTRL3_CLR_MASK);
    /* Configure ADCx resolution */
    /* Set RES bits according to Resolution value */
    tempreg1 |= ADC_InitStruct->Resolution;
    /* Write to ADCx CTRL3 */
    ADCx->CTRL3 = tempreg1;

    /*---------------------------- ADCx RSEQ3 Configuration -----------------*/
    /* Get the ADCx RSEQ3 value */
    tempreg1 = ADCx->RSEQ3;
    /* Clear L bits */
    tempreg1 &= (~RSEQ3_CLR_MASK);
    /* Configure ADCx: regular channel sequence length */
    /* Set LEN bits according to ChsNumber value */
    tempreg2 = (uint8_t)(ADC_InitStruct->ChsNumber - 1);
    tempreg1 |= (uint32_t)tempreg2 << 25;
    /* Write to ADCx RSEQ3 */
    ADCx->RSEQ3 = tempreg1;
}

/**
*\*\name    ADC_InitStruct.
*\*\fun     Fills all ADC_InitStruct member with default value.
*\*\param   ADC_InitStruct :
*\*\          - WorkMode
*\*\          - MultiChEn
*\*\          - ContinueConvEn
*\*\          - ExtTrigSelect
*\*\          - DatAlign
*\*\          - ChsNumber
*\*\          - Resolution
*\*\return  none
**/
void ADC_InitStruct(ADC_InitType* ADC_InitStruct)
{
    /* Reset ADC init structure parameters values */
    /* Initialize the WorkMode member */
    ADC_InitStruct->WorkMode = ADC_WORKMODE_INDEPENDENT;
    /* initialize the MultiChEn member */
    ADC_InitStruct->MultiChEn = DISABLE;
    /* Initialize the ContinueConvEn member */
    ADC_InitStruct->ContinueConvEn = DISABLE;
    /* Initialize the ExtTrigSelect member */
    ADC_InitStruct->ExtTrigSelect = ADC_EXT_TRIG_REG_CONV_ATIM1_CC4;
    /* Initialize the DatAlign member */
    ADC_InitStruct->DatAlign = ADC_DAT_ALIGN_R;
    /* Initialize the ChsNumber member */
    ADC_InitStruct->ChsNumber = 1;
     /* Initialize the Resolution member */
    ADC_InitStruct->Resolution = ADC_DATA_RES_12BIT;
}


/**
*\*\name    ADC_Enable.
*\*\fun     Configures the specified ADC enable or disable.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ADC_Enable(ADC_Module* ADCx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Set the AD_ON bit to wake up the ADC from power down mode */
        ADCx->CTRL2 |= ADC_ON_EN_MASK;
    }
    else
    {
        /* Disable the selected ADC peripheral */
        ADCx->CTRL2 &= (~ADC_ON_EN_MASK);
    }
}
/**
*\*\name    ADC_SetDMATransferMode.
*\*\fun     Select the DMA mode for data transmission in multi-channels conversion.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   DMAMode :
*\*\          - ADC_MULTI_REG_DMA_DISABLE    :DMA Mode 0
*\*\          - ADC_MULTI_REG_DMA_EACH_ADC   :DMA Mode 1
*\*\          - ADC_MULTI_REG_DMA_LIMIT_RES12_10B :DMA Mode 2
*\*\          - ADC_MULTI_REG_DMA_LIMIT_RES8_6B :DMA Mode 3
*\*\return  none
**/
void ADC_SetDMATransferMode(ADC_Module *ADCx, uint32_t DMAMode)
{
    __IO uint32_t tempreg;
    /* Get the old register value */
    tempreg = ADCx->CTRL2;
    /* Clear the old DMA mode value */
    tempreg &= (~ADC_MULTI_REG_DMA_MODE_MASK);
    /* Set the DMA mode  */
    tempreg |= DMAMode;
    /* Store the new register value */
    ADCx->CTRL2 = tempreg;
}

/**
*\*\name    ADC_CalibrationOperation.
*\*\fun     Starts the selected ADC differential or signal mode calibration process.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   cali_mode : specifies differential or signal mode of calibration.
*\*\          - ADC_CALIBRATION_SINGLE_MODE
*\*\          - ADC_CALIBRATION_DIFF_MODE
*\*\return  none
**/
void ADC_CalibrationOperation(ADC_Module* ADCx, ADC_CALI_MOD cali_mode)
{
    if(cali_mode == ADC_CALIBRATION_DIFF_MODE)
    {
        ADCx->CTRL3 |= ADC_CAL_DIFF_MODE_MASK;
    }
    else
    {
        ADCx->CTRL3 &= (~ADC_CAL_DIFF_MODE_MASK);
    }
    /* Set the flag of starting of calibration */
    ADCx->CTRL2 |= ADC_CALI_EN_MASK;
}
/**
*\*\name    ADC_CalibrationReset.
*\*\fun     Reset the selected ADC differential or signal mode calibration process.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   cali_mode : specifies differential or signal mode of calibration.
*\*\          - ADC_CALIBRATION_SINGLE_MODE
*\*\          - ADC_CALIBRATION_DIFF_MODE
*\*\return  none
**/
void ADC_CalibrationReset(ADC_Module* ADCx, ADC_CALI_MOD cali_mode)
{
    if(cali_mode == ADC_CALIBRATION_DIFF_MODE)
    {
        ADCx->CTRL3 |= ADC_CAL_DIFF_MODE_MASK;
    }
    else
    {
        ADCx->CTRL3 &= (~ADC_CAL_DIFF_MODE_MASK);
    }
    /* Set the flag of reset of calibration */
    ADCx->CTRL2 |= ADC_CALI_RESET_MASK;
}

/**
*\*\name    ADC_GetCalibrationStatus.
*\*\fun     Gets the selected ADC calibration status.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   cali_mode : specifies differential or signal mode of calibration.
*\*\          - ADC_CALIBRATION_SINGLE_MODE
*\*\          - ADC_CALIBRATION_DIFF_MODE
*\*\return  FlagStatus:
*\*\          - RESET : ADCx calibration is finished;
*\*\          - SET   : ADCx calibration is not finished;
**/
FlagStatus ADC_GetCalibrationStatus(ADC_Module* ADCx, ADC_CALI_MOD cali_mode)
{
    FlagStatus bitstatus;

    /* Check the status of CAL bit */
    if ((ADCx->CTRL2 & ADC_CALI_EN_MASK) != (uint32_t)RESET)
    {
        /* CAL bit is set: calibration on going */
        bitstatus = SET;
    }
    else
    {
        /* CAL bit is reset: end of calibration */
        bitstatus = RESET;
    }
    if(cali_mode == ADC_CALIBRATION_DIFF_MODE)
    {
        if((ADCx->CALFACT&ADC_CALFACT_CALFACTD_MASK) != 0)
        {
            bitstatus = RESET;
        }
        else
        {
            /* no process*/
        }
    }
    else
    {
        if((ADCx->CALFACT&ADC_CALFACT_CALFACTS_MASK) != 0)
        {
            bitstatus = RESET;
        }
        else
        {
            /* no process*/
        }
    }
    /* Return the CAL bit status */
    return bitstatus;
}
/**
*\*\name    ADC_SetMultiTwoSamplingDelay.
*\*\fun     Set ADC multimode delay between 2 sampling phases.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   MultiTwoSamplingDelay 
*\*\          - ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_1
*\*\          - ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_2
*\*\          - ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_3
*\*\          - ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_4
*\*\          - ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_5
*\*\          - ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_6
*\*\          - ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_7
*\*\          - ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_8
*\*\          - ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_9
*\*\          - ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_10
*\*\          - ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_11
*\*\          - ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_12
*\*\return  none
*\*\note    1.When ADC resolution is 12, the maximum of the parameter 'MultiTwoSamplingDelay' \
*\*\          can be set ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_12.
*\*\        2.When ADC resolution is 10, the maximum of the parameter 'MultiTwoSamplingDelay' \
*\*\          can be set ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_10.
*\*\        3.When ADC resolution is 8, the maximum of the parameter 'MultiTwoSamplingDelay' \
*\*\          can be set ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_8.
*\*\        4.When ADC resolution is 6, the maximum of the parameter 'MultiTwoSamplingDelay' \
*\*\          can be set ADC_ADC_MULTI_TWOSMP_DELAY_CYCLE_6.
**/
void ADC_SetMultiTwoSamplingDelay(ADC_Module* ADCx, uint32_t MultiTwoSamplingDelay)
{
    __IO uint32_t tempreg;
    /* Get the old register value */
    tempreg = ADCx->CTRL1;
    /* Clear the old delay number */
    tempreg &= (~ADC_ADC_MULTI_TWOSMP_DELAY_MASK);
    /* Set the delay number */
    tempreg |= MultiTwoSamplingDelay;
    /* Store the new register value */
    ADCx->CTRL1 = tempreg;
}

/**
*\*\name    ADC_ConfigDiscModeChannelCount.
*\*\fun     Configures the discontinuous numbers for the selected ADC regular
*\*\        group channels.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   Number : specifies the discontinuous mode regular channel
 *          count value. This number must be range form 1 to 8.
*\*\return  none
**/
void ADC_ConfigDiscModeChannelCount(ADC_Module* ADCx, uint8_t Number)
{
    __IO uint32_t tempreg;
    /* Get the old register value */
    tempreg = ADCx->CTRL1;
    /* Clear the old discontinuous mode channel count */
    tempreg &= (~ADC_DISC_NUM_MASK);
    /* Set the discontinuous mode channel count */
    tempreg |= (((uint32_t)Number - 1) << 2);
    /* Store the new register value */
    ADCx->CTRL1 = tempreg;
}

/**
*\*\name    ADC_EnableAutoInjectedConv.
*\*\fun     Enables or disables the selected ADC automatic injected group
*\*\        conversion after regular one
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ADC_EnableAutoInjectedConv(ADC_Module* ADCx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected ADC automatic injected group conversion */
        ADCx->CTRL1 |= ADC_JAUTO_EN_MASK;
    }
    else
    {
        /* Disable the selected ADC automatic injected group conversion */
        ADCx->CTRL1 &= (~ADC_JAUTO_EN_MASK);
    }
}

/**
*\*\name    ADC_EnableDiscMode.
*\*\fun     Enables or disables the discontinuous mode on regular group
*\*         channel for the specified ADC.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ADC_EnableDiscMode(ADC_Module* ADCx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected ADC regular discontinuous mode */
        ADCx->CTRL1 |= ADC_DISC_REG_EN_MASK;
    }
    else
    {
        /* Disable the selected ADC regular discontinuous mode */
        ADCx->CTRL1 &= (~ADC_DISC_REG_EN_MASK);
    }
}

/**
*\*\name    ADC_EnableInjectedDiscMode.
*\*\fun     Enables or disables the discontinuous mode on injected group
*\*         channel for the specified ADC.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ADC_EnableInjectedDiscMode(ADC_Module* ADCx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected ADC injected discontinuous mode */
        ADCx->CTRL1 |= ADC_DISC_INJ_EN_MASK;
    }
    else
    {
        /* Disable the selected ADC injected discontinuous mode */
        ADCx->CTRL1 &= (~ADC_DISC_INJ_EN_MASK);
    }
}

/**
*\*\name    ADC_ConfigRegularChannel.
*\*\fun     Configures for the selected ADC regular channel its corresponding
*\*\        rank in the sequencer and its sample time.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   ADC_Channel :
*\*\          - ADC_CH_0 : ADC Channel0 selected
*\*\          - ADC_CH_1 : ADC Channel1 selected
*\*\          - ADC_CH_2 : ADC Channel2 selected
*\*\          - ADC_CH_3 : ADC Channel3 selected
*\*\          - ADC_CH_4 : ADC Channel4 selected
*\*\          - ADC_CH_5 : ADC Channel5 selected
*\*\          - ADC_CH_6 : ADC Channel6 selected
*\*\          - ADC_CH_7 : ADC Channel7 selected
*\*\          - ADC_CH_8 : ADC Channel8 selected
*\*\          - ADC_CH_9 : ADC Channel9 selected
*\*\          - ADC_CH_10 : ADC Channel10 selected
*\*\          - ADC_CH_11 : ADC Channel11 selected
*\*\          - ADC_CH_12 : ADC Channel12 selected
*\*\          - ADC_CH_13 : ADC Channel13 selected
*\*\          - ADC_CH_14 : ADC Channel14 selected
*\*\          - ADC_CH_15 : ADC Channel15 selected
*\*\          - ADC_CH_16 : ADC Channel16 selected
*\*\          - ADC_CH_17 : ADC Channel17 selected
*\*\          - ADC_CH_18 : ADC Channel18 selected
*\*\param   Rank : The rank in the regular group sequencer. This parameter must be between 1 to 16.
*\*\param   ADC_SampleTime : The sample time value to be set for the selected channel.
*\*\          - ADC_SAMP_TIME_CYCLES_1_5
*\*\          - ADC_SAMP_TIME_CYCLES_2_5
*\*\          - ADC_SAMP_TIME_CYCLES_4_5
*\*\          - ADC_SAMP_TIME_CYCLES_7_5
*\*\          - ADC_SAMP_TIME_CYCLES_13_5
*\*\          - ADC_SAMP_TIME_CYCLES_19_5
*\*\          - ADC_SAMP_TIME_CYCLES_28_5
*\*\          - ADC_SAMP_TIME_CYCLES_41_5
*\*\          - ADC_SAMP_TIME_CYCLES_55_5
*\*\          - ADC_SAMP_TIME_CYCLES_61_5
*\*\          - ADC_SAMP_TIME_CYCLES_71_5
*\*\          - ADC_SAMP_TIME_CYCLES_181_5
*\*\          - ADC_SAMP_TIME_CYCLES_239_5
*\*\          - ADC_SAMP_TIME_CYCLES_601_5
*\*\return  none
**/
void ADC_ConfigRegularChannel(ADC_Module* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime)
{
    uint32_t tempreg1, tempreg2;
    if (ADC_Channel > ADC_CH_15)  /* if ADC_CH_16 ... ADC_CH_18 is selected */
    {
        /* Get the old register value */
        tempreg1 = ADCx->SAMPT3;
        /* Calculate the mask to clear */
        tempreg2 = ADC_SAMP_TIME_CYCLES_MASK << (4 * (ADC_Channel - 16));
        /* Clear the old channel sample time */
        tempreg1 &= ~tempreg2;
        /* Calculate the mask to set */
        tempreg2 = ((uint32_t)ADC_SampleTime) << (4 * (ADC_Channel - 16));
        /* Set the new channel sample time */
        tempreg1 |= tempreg2;
        /* Store the new register value */
        ADCx->SAMPT3 = tempreg1;
    }
    else if (ADC_Channel > ADC_CH_7) /* if ADC_CH_8 ... ADC_CH_15 is selected */
    {
        /* Get the old register value */
        tempreg1 = ADCx->SAMPT2;
        /* Calculate the mask to clear */
        tempreg2 = ADC_SAMP_TIME_CYCLES_MASK << (4 * (ADC_Channel - 8));
        /* Clear the old channel sample time */
        tempreg1 &= ~tempreg2;
        /* Calculate the mask to set */
        tempreg2 = ((uint32_t)ADC_SampleTime) << (4 * (ADC_Channel - 8));
        /* Set the new channel sample time */
        tempreg1 |= tempreg2;
        /* Store the new register value */
        ADCx->SAMPT2 = tempreg1;
    }
    else /* if ADC_CH_0 ... ADC_CH_7 is selected */
    {
        /* Get the old register value */
        tempreg1 = ADCx->SAMPT1;
        /* Calculate the mask to clear */
        tempreg2 = ADC_SAMP_TIME_CYCLES_MASK << (4 * (ADC_Channel));
        /* Clear the old channel sample time */
        tempreg1 &= ~tempreg2;
        /* Calculate the mask to set */
        tempreg2 = ((uint32_t)ADC_SampleTime) << (4 * (ADC_Channel));
        /* Set the new channel sample time */
        tempreg1 |= tempreg2;
        /* Store the new register value */
        ADCx->SAMPT1 = tempreg1;
    }

    if (Rank < 7)  /* For Rank 1 to 6 */
    {
        /* Get the old register value */
        tempreg1 = ADCx->RSEQ1;
        /* Calculate the mask to clear */
        tempreg2 = ADC_RESQ_SEQ_MASK << (5 * (Rank - 1));
        /* Clear the old SQx bits for the selected rank */
        tempreg1 &= ~tempreg2;
        /* Calculate the mask to set */
        tempreg2 = (uint32_t)ADC_Channel << (5 * (Rank - 1));
        /* Set the SQx bits for the selected rank */
        tempreg1 |= tempreg2;
        /* Store the new register value */
        ADCx->RSEQ1 = tempreg1;
    }
    else if (Rank < 13)   /* For Rank 7 to 12 */
    {
        /* Get the old register value */
        tempreg1 = ADCx->RSEQ2;
        /* Calculate the mask to clear */
        tempreg2 = ADC_RESQ_SEQ_MASK << (5 * (Rank - 7));
        /* Clear the old SQx bits for the selected rank */
        tempreg1 &= ~tempreg2;
        /* Calculate the mask to set */
        tempreg2 = (uint32_t)ADC_Channel << (5 * (Rank - 7));
        /* Set the SQx bits for the selected rank */
        tempreg1 |= tempreg2;
        /* Store the new register value */
        ADCx->RSEQ2 = tempreg1;
    }
    else /* For Rank 13 to 16 */
    {
        /* Get the old register value */
        tempreg1 = ADCx->RSEQ3;
        /* Calculate the mask to clear */
        tempreg2 = ADC_RESQ_SEQ_MASK << (5 * (Rank - 13));
        /* Clear the old SQx bits for the selected rank */
        tempreg1 &= ~tempreg2;
        /* Calculate the mask to set */
        tempreg2 = (uint32_t)ADC_Channel << (5 * (Rank - 13));
        /* Set the SQx bits for the selected rank */
        tempreg1 |= tempreg2;
        /* Store the new register value */
        ADCx->RSEQ3 = tempreg1;
    }
}

/**
*\*\name    ADC_GetDat.
*\*\fun     Get the last ADCx conversion result data for regular channel
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\return  The Data conversion value.
**/
uint16_t ADC_GetDat(ADC_Module* ADCx)
{
    /* Return the selected ADC conversion value */
    return (uint16_t)ADCx->DAT;
}

/**
*\*\name    ADC_GetMutiModeConversionDat.
*\*\fun     Get the last ADC conversion result data in dual-ADC or tripple-ADC mode.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\return  The Data conversion value in dual-ADC or tripple-ADC mode.
**/
uint32_t ADC_GetMutiModeConversionDat(ADC_Module* ADCx)
{
    uint32_t tempreg;
    if( (ADCx == ADC1) || (ADCx == ADC2) )
    {
        tempreg = (uint32_t)ADC1->DAT;
    } 
    else
    {
        tempreg = (uint32_t)ADC3->DAT;
    }
    return tempreg;
}
/**
*\*\name    ADC_SetRegularTriggerEdge.
*\*\fun     Set ADCx group regular conversion trigger polarity.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   ExternalRegularTriggerEdge :
*\*\          - ADC_REG_TRIG_EXT_SOFTWARE     
*\*\          - ADC_REG_TRIG_EXT_RISING     
*\*\          - ADC_REG_TRIG_EXT_FALLING    
*\*\          - ADC_REG_TRIG_EXT_RISINGFALLING      
*\*\return  none
**/
void ADC_SetRegularTriggerEdge(ADC_Module* ADCx, uint32_t ExternalRegularTriggerEdge)
{
    uint32_t tempreg;
    /* Get the old register value */
    tempreg = ADCx->CTRL2;
    /* Clear the old external trigger polarity selection for regular group */
    tempreg &= (~ADC_REG_TRIG_EXT_MASK);
    /* Set the external trigger polarity selection for regular group */
    tempreg |= ExternalRegularTriggerEdge;
    /* Store the new register value */
    ADCx->CTRL2 = tempreg;
}
/**
*\*\name    ADC_SetInjectTriggerEdge.
*\*\fun     Set ADCx group injected conversion trigger polarity.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   ExternalInjectTriggerEdge :
*\*\          - ADC_INJ_TRIG_EXT_SOFTWARE     
*\*\          - ADC_INJ_TRIG_EXT_RISING     
*\*\          - ADC_INJ_TRIG_EXT_FALLING    
*\*\          - ADC_INJ_TRIG_EXT_RISINGFALLING      
*\*\return  none
**/
void ADC_SetInjectTriggerEdge(ADC_Module* ADCx, uint32_t ExternalInjectTriggerEdge)
{
    uint32_t tempreg;
    /* Get the old register value */
    tempreg = ADCx->CTRL2;
    /* Clear the old external trigger polarity selection for injected group */
    tempreg &= (~ADC_INJ_TRIG_EXT_MASK);
    /* Set the external trigger polarity selection for injected group */
    tempreg |= ExternalInjectTriggerEdge;
    /* Store the new register value */
    ADCx->CTRL2 = tempreg;
}
/**
*\*\name    ADC_ConfigExternalTrigRegularConv.
*\*\fun     Configures the ADCx external trigger source for regular channels conversion.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   ADC_ExternalTrigRegularConv :
*\*\          - ADC_EXT_TRIG_REG_CONV_ATIM1_CC4     
*\*\          - ADC_EXT_TRIG_REG_CONV_ATIM1_TRGO     
*\*\          - ADC_EXT_TRIG_REG_CONV_ATIM1_TRGO2    
*\*\          - ADC_EXT_TRIG_REG_CONV_ATIM2_CC4      
*\*\          - ADC_EXT_TRIG_REG_CONV_ATIM2_TRGO     
*\*\          - ADC_EXT_TRIG_REG_CONV_ATIM2_TRGO2    
*\*\          - ADC_EXT_TRIG_REG_CONV_ATIM3_CC4      
*\*\          - ADC_EXT_TRIG_REG_CONV_ATIM3_TRGO     
*\*\          - ADC_EXT_TRIG_REG_CONV_ATIM3_TRGO2          
*\*\          - ADC_EXT_TRIG_REG_CONV_GTIM1_CC4            
*\*\          - ADC_EXT_TRIG_REG_CONV_GTIM2_CC4             
*\*\          - ADC_EXT_TRIG_REG_CONV_GTIM3_CC4             
*\*\          - ADC_EXT_TRIG_REG_CONV_GTIM4_CC4             
*\*\          - ADC_EXT_TRIG_REG_CONV_GTIM5_CC4             
*\*\          - ADC_EXT_TRIG_REG_CONV_GTIM6_CC4             
*\*\          - ADC_EXT_TRIG_REG_CONV_GTIM7_CC4             
*\*\          - ADC_EXT_TRIG_REG_CONV_GTIM8_CC4             
*\*\          - ADC_EXT_TRIG_REG_CONV_GTIM9_CC4             
*\*\          - ADC_EXT_TRIG_REG_CONV_GTIM10_CC4            
*\*\          - ADC_EXT_TRIG_REG_CONV_GTIM1_TRGO            
*\*\          - ADC_EXT_TRIG_REG_CONV_GTIM2_TRGO            
*\*\          - ADC_EXT_TRIG_REG_CONV_GTIM3_TRGO            
*\*\          - ADC_EXT_TRIG_REG_CONV_GTIM4_TRGO            
*\*\          - ADC_EXT_TRIG_REG_CONV_GTIM5_TRGO            
*\*\          - ADC_EXT_TRIG_REG_CONV_GTIM6_TRGO            
*\*\          - ADC_EXT_TRIG_REG_CONV_GTIM7_TRGO            
*\*\          - ADC_EXT_TRIG_REG_CONV_GTIM8_TRGO            
*\*\          - ADC_EXT_TRIG_REG_CONV_GTIM9_TRGO            
*\*\          - ADC_EXT_TRIG_REG_CONV_GTIM10_TRGO           
*\*\          - ADC_EXT_TRIG_REG_CONV_SHRTIM_TRGO1          
*\*\          - ADC_EXT_TRIG_REG_CONV_SHRTIM_TRGO2          
*\*\          - ADC_EXT_TRIG_REG_CONV_SHRTIM_TRGO3          
*\*\          - ADC_EXT_TRIG_REG_CONV_SHRTIM_TRGO4          
*\*\          - ADC_EXT_TRIG_REG_CONV_SHRTIM_TRGO5          
*\*\          - ADC_EXT_TRIG_REG_CONV_SHRTIM_TRGO6          
*\*\          - ADC_EXT_TRIG_REG_CONV_SHRTIM_TRGO7          
*\*\          - ADC_EXT_TRIG_REG_CONV_SHRTIM_TRGO8          
*\*\          - ADC_EXT_TRIG_REG_CONV_SHRTIM_TRGO9          
*\*\          - ADC_EXT_TRIG_REG_CONV_SHRTIM_TRGO10         
*\*\          - ADC_EXT_TRIG_REG_CONV_LPTIM1_OUT            
*\*\          - ADC_EXT_TRIG_REG_CONV_LPTIM2_OUT            
*\*\          - ADC_EXT_TRIG_REG_CONV_EXT_INT0_15           
*\*\          - ADC_EXT_TRIG_REG_CONV_SOFTWARE  
*\*\return  none
**/
void ADC_ConfigExternalTrigRegularConv(ADC_Module* ADCx, uint32_t ADC_ExternalTrigRegularConv)
{
    uint32_t tempreg;

    /* Get the old register value */
    tempreg = ADCx->CTRL2;
    /* Clear the old external event selection for regular group */
    tempreg &= (~ADC_EXT_TRIG_REG_CONV_MASK);
    /* Set the external event selection for regular group */
    tempreg |= ADC_ExternalTrigRegularConv;
    /* Store the new register value */
    ADCx->CTRL2 = tempreg;
}
/**
*\*\name    ADC_ConfigExternalTrigInjectedConv.
*\*\fun     Configures the ADCx external trigger source for injected channels conversion.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   ADC_ExternalTrigInjecConv :
*\*\          - ADC_EXT_TRIG_INJ_CONV_ATIM1_CC4     
*\*\          - ADC_EXT_TRIG_INJ_CONV_ATIM1_TRGO     
*\*\          - ADC_EXT_TRIG_INJ_CONV_ATIM1_TRGO2    
*\*\          - ADC_EXT_TRIG_INJ_CONV_ATIM2_CC4      
*\*\          - ADC_EXT_TRIG_INJ_CONV_ATIM2_TRGO     
*\*\          - ADC_EXT_TRIG_INJ_CONV_ATIM2_TRGO2    
*\*\          - ADC_EXT_TRIG_INJ_CONV_ATIM3_CC4      
*\*\          - ADC_EXT_TRIG_INJ_CONV_ATIM3_TRGO     
*\*\          - ADC_EXT_TRIG_INJ_CONV_ATIM3_TRGO2          
*\*\          - ADC_EXT_TRIG_INJ_CONV_GTIM1_CC4            
*\*\          - ADC_EXT_TRIG_INJ_CONV_GTIM2_CC4             
*\*\          - ADC_EXT_TRIG_INJ_CONV_GTIM3_CC4             
*\*\          - ADC_EXT_TRIG_INJ_CONV_GTIM4_CC4             
*\*\          - ADC_EXT_TRIG_INJ_CONV_GTIM5_CC4             
*\*\          - ADC_EXT_TRIG_INJ_CONV_GTIM6_CC4             
*\*\          - ADC_EXT_TRIG_INJ_CONV_GTIM7_CC4             
*\*\          - ADC_EXT_TRIG_INJ_CONV_GTIM8_CC4             
*\*\          - ADC_EXT_TRIG_INJ_CONV_GTIM9_CC4             
*\*\          - ADC_EXT_TRIG_INJ_CONV_GTIM10_CC4            
*\*\          - ADC_EXT_TRIG_INJ_CONV_GTIM1_TRGO            
*\*\          - ADC_EXT_TRIG_INJ_CONV_GTIM2_TRGO            
*\*\          - ADC_EXT_TRIG_INJ_CONV_GTIM3_TRGO            
*\*\          - ADC_EXT_TRIG_INJ_CONV_GTIM4_TRGO            
*\*\          - ADC_EXT_TRIG_INJ_CONV_GTIM5_TRGO            
*\*\          - ADC_EXT_TRIG_INJ_CONV_GTIM6_TRGO            
*\*\          - ADC_EXT_TRIG_INJ_CONV_GTIM7_TRGO            
*\*\          - ADC_EXT_TRIG_INJ_CONV_GTIM8_TRGO            
*\*\          - ADC_EXT_TRIG_INJ_CONV_GTIM9_TRGO            
*\*\          - ADC_EXT_TRIG_INJ_CONV_GTIM10_TRGO           
*\*\          - ADC_EXT_TRIG_INJ_CONV_SHRTIM_TRGO1          
*\*\          - ADC_EXT_TRIG_INJ_CONV_SHRTIM_TRGO2          
*\*\          - ADC_EXT_TRIG_INJ_CONV_SHRTIM_TRGO3          
*\*\          - ADC_EXT_TRIG_INJ_CONV_SHRTIM_TRGO4          
*\*\          - ADC_EXT_TRIG_INJ_CONV_SHRTIM_TRGO5          
*\*\          - ADC_EXT_TRIG_INJ_CONV_SHRTIM_TRGO6          
*\*\          - ADC_EXT_TRIG_INJ_CONV_SHRTIM_TRGO7          
*\*\          - ADC_EXT_TRIG_INJ_CONV_SHRTIM_TRGO8          
*\*\          - ADC_EXT_TRIG_INJ_CONV_SHRTIM_TRGO9          
*\*\          - ADC_EXT_TRIG_INJ_CONV_SHRTIM_TRGO10         
*\*\          - ADC_EXT_TRIG_INJ_CONV_LPTIM1_OUT            
*\*\          - ADC_EXT_TRIG_INJ_CONV_LPTIM2_OUT            
*\*\          - ADC_EXT_TRIG_INJ_CONV_EXT_INT0_15           
*\*\          - ADC_EXT_TRIG_INJ_CONV_SOFTWARE  
*\*\return  none
**/
void ADC_ConfigExternalTrigInjectedConv(ADC_Module* ADCx, uint32_t ADC_ExternalTrigInjecConv)
{
    uint32_t tempreg;

    /* Get the old register value */
    tempreg = ADCx->CTRL2;
    /* Clear the old external event selection for injected group */
    tempreg &= (~ADC_EXT_TRIG_INJ_CONV_MASK);
    /* Set the external event selection for injected group */
    tempreg |= ADC_ExternalTrigInjecConv;
    /* Store the new register value */
    ADCx->CTRL2 = tempreg;
}

/**
*\*\name    ADC_EnableSoftwareStartConv.
*\*\fun     Enables or disables the selected ADC software start conversion ..
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   Cmd :
*\*\          - ENABLE   
*\*\          - DISABLE  
*\*\return  none 
**/ 
void ADC_EnableSoftwareStartConv(ADC_Module* ADCx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected ADC conversion on external event and start the selected
           ADC conversion */
        ADCx->CTRL2 |= ADC_REG_SWSTART_MASK;
    }
    else
    {
        /* Disable the selected ADC conversion on external event and stop the selected
           ADC conversion */
        ADCx->CTRL2 &= (~ADC_REG_SWSTART_MASK);
    }
}
/**
*\*\name    ADC_GetSoftwareStartConvStatus.
*\*\fun     Gets the selected ADC Software start conversion Status.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4 
*\*\return The new state of ADC software start conversion (SET or RESET). 
**/ 
FlagStatus ADC_GetSoftwareStartConvStatus(ADC_Module* ADCx)
{
    FlagStatus bitstatus ;
    
    if ((ADCx->CTRL2 & ADC_REG_SWSTART_MASK) != (uint32_t)RESET)
    {
        /* SOFT_START bit is set */
        bitstatus = SET;
    }
    else
    {
        /* SOFT_START bit is reset */
        bitstatus = RESET;
    }
    return bitstatus;
}
/**
*\*\name    ADC_EnableSoftwareStartInjectedConv.
*\*\fun    Enables or disables the selected ADC start of the injected channels conversion.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   Cmd :
*\*\          - ENABLE   
*\*\          - DISABLE  
*\*\return  none 
**/ 
void ADC_EnableSoftwareStartInjectedConv(ADC_Module* ADCx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected ADC conversion for injected group on external event and start the selected
           ADC injected conversion */
        ADCx->CTRL2 |= ADC_INJ_SWSTART_MASK;
    }
    else
    {
        /* Disable the selected ADC conversion on external event for injected group and stop the selected
           ADC injected conversion */
        ADCx->CTRL2 &= (~ADC_INJ_SWSTART_MASK);
    }
}
/**
*\*\name    ADC_GetSoftwareStartInjectedConvCmdStatus.
*\*\fun     Gets the selected ADC Software start injected conversion Status.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4 
*\*\return The new state of ADC software start injected conversion (SET or RESET). 
**/ 
FlagStatus ADC_GetSoftwareStartInjectedConvCmdStatus(ADC_Module* ADCx)
{
    FlagStatus bitstatus ;

    /* Check the status of INJ_SWSTART bit */
    if ((ADCx->CTRL2 & ADC_INJ_SWSTART_MASK) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
*\*\name    ADC_StopInjectedConv.
*\*\fun     Stop ADC group injected channels conversion.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4 
*\*\return  none 
**/ 
void ADC_StopInjectedConv(ADC_Module* ADCx)
{
    ADCx->CTRL2 |= ADC_INJ_SWSTOP_MASK;
}
/**
*\*\name    ADC_StopRegularConv.
*\*\fun     Stop ADC group regular channels conversion.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4 
*\*\return  none 
**/ 
void ADC_StopRegularConv(ADC_Module* ADCx)
{
    ADCx->CTRL2 |= ADC_REG_SWSTOP_MASK;
}

/**
*\*\name    ADC_GetGainCompensationCmdStatus.
*\*\fun     Gets the selected ADC gain compensation status.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4 
*\*\return The new state of gain compensation (SET or RESET). 
**/ 
FlagStatus ADC_GetGainCompensationCmdStatus(ADC_Module* ADCx)
{
    FlagStatus bitstatus ;

    /* Check the status of GCOMPEN bit */
    if ((ADCx->CTRL2 & ADC_GAIN_COMPENSATION_EN_MASK) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
*\*\name    ADC_EnableTempSensorVrefint.
*\*\fun     Enables or disables the temperature sensor and Vrefint channel
*\*\param   Cmd :
*\*\          - ENABLE   
*\*\          - DISABLE  
*\*\return  none 
**/ 
void ADC_EnableTempSensorVrefint(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the temperature sensor and Vrefint channel*/
        ADC1->CTRL2 |= ADC_TS_VREFINT_EN_MASK;
        _EnVref1p2()
    }
    else
    {
        /* Disable the temperature sensor and Vrefint channel*/
        ADC1->CTRL2 &= (~ADC_TS_VREFINT_EN_MASK);
        _DisVref1p2()
    }
}

/**
*\*\name    ADC_ConfigInjectedChannel.
*\*\fun     Configures for the selected ADC injected channel its corresponding
*\*\        rank in the sequencer and its sample time.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   ADC_Channel :
*\*\          - ADC_CH_0 : ADC Channel0 selected
*\*\          - ADC_CH_1 : ADC Channel1 selected
*\*\          - ADC_CH_2 : ADC Channel2 selected
*\*\          - ADC_CH_3 : ADC Channel3 selected
*\*\          - ADC_CH_4 : ADC Channel4 selected
*\*\          - ADC_CH_5 : ADC Channel5 selected
*\*\          - ADC_CH_6 : ADC Channel6 selected
*\*\          - ADC_CH_7 : ADC Channel7 selected
*\*\          - ADC_CH_8 : ADC Channel8 selected
*\*\          - ADC_CH_9 : ADC Channel9 selected
*\*\          - ADC_CH_10 : ADC Channel10 selected
*\*\          - ADC_CH_11 : ADC Channel11 selected
*\*\          - ADC_CH_12 : ADC Channel12 selected
*\*\          - ADC_CH_13 : ADC Channel13 selected
*\*\          - ADC_CH_14 : ADC Channel14 selected
*\*\          - ADC_CH_15 : ADC Channel15 selected
*\*\          - ADC_CH_16 : ADC Channel16 selected
*\*\          - ADC_CH_17 : ADC Channel17 selected
*\*\          - ADC_CH_18 : ADC Channel18 selected
*\*\param   Rank : The rank in the injected group sequencer. This parameter must be between 1 to 4.
*\*\param   ADC_SampleTime : The sample time value to be set for the selected channel.
*\*\          - ADC_SAMP_TIME_CYCLES_1_5
*\*\          - ADC_SAMP_TIME_CYCLES_2_5
*\*\          - ADC_SAMP_TIME_CYCLES_4_5
*\*\          - ADC_SAMP_TIME_CYCLES_7_5
*\*\          - ADC_SAMP_TIME_CYCLES_13_5
*\*\          - ADC_SAMP_TIME_CYCLES_19_5
*\*\          - ADC_SAMP_TIME_CYCLES_28_5
*\*\          - ADC_SAMP_TIME_CYCLES_41_5
*\*\          - ADC_SAMP_TIME_CYCLES_55_5
*\*\          - ADC_SAMP_TIME_CYCLES_61_5
*\*\          - ADC_SAMP_TIME_CYCLES_71_5
*\*\          - ADC_SAMP_TIME_CYCLES_181_5
*\*\          - ADC_SAMP_TIME_CYCLES_239_5
*\*\          - ADC_SAMP_TIME_CYCLES_601_5
*\*\return  none
**/
void ADC_ConfigInjectedChannel(ADC_Module* ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime)
{
    uint32_t tempreg1, tempreg2, tempreg3;

    if (ADC_Channel > ADC_CH_15)  /* if ADC_CH_16 ... ADC_CH_18 is selected */
    {
        /* Get the old register value */
        tempreg1 = ADCx->SAMPT3;
        /* Calculate the mask to clear */
        tempreg2 = ADC_SAMP_TIME_CYCLES_MASK << (4 * (ADC_Channel - 16));
        /* Clear the old channel sample time */
        tempreg1 &= ~tempreg2;
        /* Calculate the mask to set */
        tempreg2 = ((uint32_t)ADC_SampleTime) << (4 * (ADC_Channel - 16));
        /* Set the new channel sample time */
        tempreg1 |= tempreg2;
        /* Store the new register value */
        ADCx->SAMPT3 = tempreg1;
    }
    else if (ADC_Channel > ADC_CH_7) /* if ADC_CH_8 ... ADC_CH_15 is selected */
    {
        /* Get the old register value */
        tempreg1 = ADCx->SAMPT2;
        /* Calculate the mask to clear */
        tempreg2 = ADC_SAMP_TIME_CYCLES_MASK << (4 * (ADC_Channel - 8));
        /* Clear the old channel sample time */
        tempreg1 &= ~tempreg2;
        /* Calculate the mask to set */
        tempreg2 = ((uint32_t)ADC_SampleTime) << (4 * (ADC_Channel - 8));
        /* Set the new channel sample time */
        tempreg1 |= tempreg2;
        /* Store the new register value */
        ADCx->SAMPT2 = tempreg1;
    }
    else /* if ADC_CH_0 ... ADC_CH_7 is selected */
    {
        /* Get the old register value */
        tempreg1 = ADCx->SAMPT1;
        /* Calculate the mask to clear */
        tempreg2 = ADC_SAMP_TIME_CYCLES_MASK << (4 * ADC_Channel);
        /* Clear the old channel sample time */
        tempreg1 &= ~tempreg2;
        /* Calculate the mask to set */
        tempreg2 = ((uint32_t)ADC_SampleTime) << (4 * ADC_Channel);
        /* Set the new channel sample time */
        tempreg1 |= tempreg2;
        /* Store the new register value */
        ADCx->SAMPT1 = tempreg1;
    }
    /* Rank configuration */
    /* Get the old register value */
    tempreg1 = ADCx->JSEQ;
    /* Get JLEN value: Number = JLEN+1 */
    tempreg3 = (tempreg1 & ADC_JESQ_LEN_MASK) >> 25;
    /* Calculate the mask to clear: ((Rank-1)+(4-JLEN-1)) */
    tempreg2 = ADC_JESQ_SEQ_MASK << (5 * (((uint32_t)Rank + 3) - (tempreg3 + 1)));
    /* Clear the old JSEQx bits for the selected rank */
    tempreg1 &= ~tempreg2;
    /* Calculate the mask to set: ((Rank-1)+(4-JLEN-1)) */
    tempreg2 = (uint32_t)ADC_Channel << (5 * (((uint32_t)Rank + 3) - (tempreg3 + 1)));
    /* Set the JSEQx bits for the selected rank */
    tempreg1 |= tempreg2;
    /* Store the new register value */
    ADCx->JSEQ = tempreg1;
}

/**
*\*\name    ADC_ConfigInjectedSequencerLength.
*\*\fun     Configures the sequencer length for injected channels
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   Length : The sequencer length. This parameter must be a number between 1 to 4.
**/
void ADC_ConfigInjectedSequencerLength(ADC_Module* ADCx, uint8_t Length)
{
    uint32_t tempreg1,tempreg2;

    /* Get the old register value */
    tempreg1 = ADCx->JSEQ;
    /* Clear the old injected sequnence lenght JLEN bits */
    tempreg1 &= (~ADC_JESQ_LEN_MASK);
    /* Set the injected sequnence lenght JLEN bits */
    tempreg2 = (uint32_t)Length - 1;
    tempreg1 |= tempreg2 << 25;
    /* Store the new register value */
    ADCx->JSEQ = tempreg1;
}

/**
*\*\name    ADC_SetOffsetConfig.
*\*\fun     Set the specified channel conversion offset configuration.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   ADC_Offset :
*\*\          - ADC_REGESTER_OFFSET_1
*\*\          - ADC_REGESTER_OFFSET_2
*\*\          - ADC_REGESTER_OFFSET_3
*\*\          - ADC_REGESTER_OFFSET_4
*\*\param   ADC_OffsetStruct :
*\*\          - OffsetData : Set the selected channel data offset .This parameter must be range from 0 to 0xfff.
*\*\          - OffsetChannel : Set the selected channel .This parameter must be range from 0 to 0x12. means CH0 - CH18.
*\*\          - OffsetDirPositiveEn : Enable or disable the selected channel offset positive direction.
*\*\             - ENABLE
*\*\             - DISABLE
*\*\          - OffsetSatenEn : Enable or disable the selected channel offset saturation .
*\*\             - ENABLE
*\*\             - DISABLE
*\*\          - OffsetEn : Enable or disable the selected channel offset.
*\*\             - ENABLE
*\*\             - DISABLE
*\*\return  none
**/
void ADC_SetOffsetConfig(ADC_Module* ADCx, uint8_t ADC_Offset, ADC_OffsetType* ADC_OffsetStruct)
{
    uint32_t tempreg, temp;

    tempreg = (uint32_t)ADCx;
    tempreg += ADC_Offset;
    /* Get register value */
    temp = *(__IO uint32_t*)tempreg;
    temp &= (~(ADC_OFFSET_DATA_MASK | ADC_OFFSET_EN_MASK | ADC_OFFSET_CH_MASK | ADC_OFFSET_SATEN_EN_MASK| ADC_OFFSET_DIR_MASK ));
    /* Set the selected channel offset direction and channel */
    temp |= ((uint32_t)ADC_OffsetStruct->OffsetData | (((uint32_t)ADC_OffsetStruct->OffsetChannel) << 26));

    /* Set the selected channel offset direction, saturation, enable or disable*/
    temp |= (BIT_JUDGE_AND_HANDLER(ADC_OffsetStruct->OffsetDirPositiveEn,ADC_OFFSET_DIR_MASK) | \
             BIT_JUDGE_AND_HANDLER(ADC_OffsetStruct->OffsetSatenEn,ADC_OFFSET_SATEN_EN_MASK) | \
             BIT_JUDGE_AND_HANDLER(ADC_OffsetStruct->OffsetEn,ADC_OFFSET_EN_MASK));

    *(__IO uint32_t*)tempreg = temp;
}
/**
*\*\name    ADC_GetOffsetConfig.
*\*\fun     Get the specified channel conversion offset configuration.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   ADC_Offset :
*\*\          - ADC_REGESTER_OFFSET_1
*\*\          - ADC_REGESTER_OFFSET_2
*\*\          - ADC_REGESTER_OFFSET_3
*\*\          - ADC_REGESTER_OFFSET_4
*\*\param   ADC_OffsetStruct :
*\*\          - OffsetData : Set the selected channel data offset .This parameter must be range from 0 to 0xfff.
*\*\          - OffsetChannel : Set the selected channel .This parameter must be range from 0 to 0x12. means CH0 - CH18.
*\*\          - OffsetDirPositiveEn : Enable or disable the selected channel offset positive direction.
*\*\             - ENABLE
*\*\             - DISABLE
*\*\          - OffsetSatenEn : Enable or disable the selected channel offset saturation .
*\*\             - ENABLE
*\*\             - DISABLE
*\*\          - OffsetEn : Enable or disable the selected channel offset.
*\*\             - ENABLE
*\*\             - DISABLE
*\*\return  none
**/
void ADC_GetOffsetConfig(ADC_Module* ADCx, uint8_t ADC_Offset, ADC_OffsetType* ADC_OffsetStruct)
{
    uint32_t tempreg,temp;

    tempreg = (uint32_t)ADCx;
    tempreg += ADC_Offset;
    /* Get register value */
    temp = *(__IO uint32_t*)tempreg;
    ADC_OffsetStruct->OffsetEn = ((temp & ADC_OFFSET_EN_MASK) != 0U)? ENABLE: DISABLE;
    ADC_OffsetStruct->OffsetSatenEn = ((temp & ADC_OFFSET_SATEN_EN_MASK)!= 0U)? ENABLE: DISABLE;
    ADC_OffsetStruct->OffsetDirPositiveEn = ((temp & ADC_OFFSET_DIR_MASK) != 0U)? ENABLE: DISABLE;

    ADC_OffsetStruct->OffsetChannel = (uint8_t)((temp & ADC_OFFSET_CH_MASK) >>26);
    ADC_OffsetStruct->OffsetData = (uint16_t)(temp & ADC_OFFSET_DATA_MASK);
}

/**
*\*\name    ADC_ConfigAnalogWatchdogThresholds.
*\*\fun     Configures the high and low thresholds of the analog watchdog 1/2/3.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   Awdg :
*\*\          - ADC_AWDG1
*\*\          - ADC_AWDG2
*\*\          - ADC_AWDG3
*\*\param   HighThreshold : the ADC analog watchdog 1/2/3 high threshold value.
*\*\          - This parameter must be a 12bit value.
*\*\param   LowThreshold : the ADC analog watchdog 1/2/3 low threshold value.
*\*\          - This parameter must be a 12bit value.
*\*\return  none
**/
void ADC_ConfigAnalogWatchdogThresholds(ADC_Module* ADCx, ADC_AWDG Awdg, uint16_t HighThreshold, uint16_t LowThreshold)
{
    if(Awdg == ADC_AWDG1)
    {
        /* Set the ADCx high threshold of AWDG1 */
        ADCx->WDG1HIGH = HighThreshold;
        /* Set the ADCx low threshold of AWDG1 */
        ADCx->WDG1LOW = LowThreshold;
    }
    else if(Awdg == ADC_AWDG2)
    {
        /* Set the ADCx high threshold of AWDG2 */
        ADCx->WDG2HIGH = HighThreshold;
        /* Set the ADCx low threshold of AWDG2 */
        ADCx->WDG2LOW = LowThreshold;
    }
    else if(Awdg == ADC_AWDG3)
    {
        /* Set the ADCx high threshold of AWDG3 */
        ADCx->WDG3HIGH = HighThreshold;
        /* Set the ADCx low threshold of AWDG3 */
        ADCx->WDG3LOW = LowThreshold;
    }
    else
    {
        /*no process */
    }
}
/**
*\*\name    ADC_GetInjectedConversionDat.
*\*\fun     Get the ADC injected channel conversion result.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   ADC_InjectedChannelOffset :
*\*\          - ADC_INJECT_DATA_OFFSET_1
*\*\          - ADC_INJECT_DATA_OFFSET_2
*\*\          - ADC_INJECT_DATA_OFFSET_3
*\*\          - ADC_INJECT_DATA_OFFSET_4
*\*\return  The data conversion value. this date is range 0 - 0xFFFF.
**/
uint16_t ADC_GetInjectedConversionDat(ADC_Module* ADCx, uint8_t ADC_InjectedChannelOffset)
{
    uint32_t tempreg;

    tempreg = (uint32_t)ADCx;
    tempreg += ADC_InjectedChannelOffset;

    /* Returns the selected injected channel conversion data value */
    return (uint16_t)(*(__IO uint32_t*)tempreg);
}

/**
*\*\name    ADC_ConfigAnalogWatchdog1WorkChannelType.
*\*\fun     Enables or disables the analog watchdog 1 on single/all regular or injected channels.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   ADC_AnalogWatchdog :
*\*\          - ADC_ANALOG_WTDG_NONE
*\*\          - ADC_ANALOG_WTDG_SINGLEREG_ENABLE
*\*\          - ADC_ANALOG_WTDG_SINGLEINJEC_ENABLE
*\*\          - ADC_ANALOG_WTDG_SINGLEREG_OR_INJEC_ENABLE
*\*\          - ADC_ANALOG_WTDG_ALLREG_ENABLE
*\*\          - ADC_ANALOG_WTDG_ALLINJEC_ENABLE
*\*\          - ADC_ANALOG_WTDG_ALLREG_ALLINJEC_ENABLE
*\*\return  none.
**/
void ADC_ConfigAnalogWatchdog1WorkChannelType(ADC_Module* ADCx, uint32_t ADC_AnalogWatchdog)
{
    uint32_t tempreg;

    /* Get the old register value */
    tempreg = ADCx->CTRL1;
    /* Clear AWD1EJCH, AWD1ERCH and AWD1SGLEN bits */
    tempreg &= (~(ADC_CTRL1_AWD1ERCH | ADC_CTRL1_AWD1SGLEN | ADC_CTRL1_AWD1EJCH));
    /* Set the analog watchdog enable mode */
    tempreg |= ADC_AnalogWatchdog;
    /* Store the new register value */
    ADCx->CTRL1 = tempreg;
}
/**
*\*\name    ADC_SetAWDG1FilteringConfig.
*\*\fun     Set ADC analog watchdog filtering configuration.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   FilteringCount :
*\*\          - ADC_AWDG1_FILTERING_NONE
*\*\          - ADC_AWDG1_FILTERING_2SAMPLES
*\*\          - ADC_AWDG1_FILTERING_3SAMPLES
*\*\          - ADC_AWDG1_FILTERING_4SAMPLES
*\*\          - ADC_AWDG1_FILTERING_5SAMPLES
*\*\          - ADC_AWDG1_FILTERING_6SAMPLES
*\*\          - ADC_AWDG1_FILTERING_7SAMPLES
*\*\          - ADC_AWDG1_FILTERING_8SAMPLES
*\*\return  none.
**/
void ADC_SetAWDG1FilteringConfig(ADC_Module *ADCx,  uint32_t FilteringCount)
{
    uint32_t tempreg;

    /* Get the old register value */
    tempreg = ADCx->WDG1LOW;
    /* Clear AWDFIL bits */
    tempreg &= (~ADC_AWDG1_FILTERING_MASK);
    /* Set the AWDFIL bit */
    tempreg |= FilteringCount;
    /* Store the new register value */
    ADCx->WDG1LOW = tempreg;
}
/**
*\*\name    ADC_ConfigAnalogWatchdog1SingleChannel.
*\*\fun     Configures the analog watchdog 1 guarded on single channel.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   ADC_AnalogWatchdog :
*\*\          - ADC_CH_0 : ADC Channel0 selected
*\*\          - ADC_CH_1 : ADC Channel1 selected
*\*\          - ADC_CH_2 : ADC Channel2 selected
*\*\          - ADC_CH_3 : ADC Channel3 selected
*\*\          - ADC_CH_4 : ADC Channel4 selected
*\*\          - ADC_CH_5 : ADC Channel5 selected
*\*\          - ADC_CH_6 : ADC Channel6 selected
*\*\          - ADC_CH_7 : ADC Channel7 selected
*\*\          - ADC_CH_8 : ADC Channel8 selected
*\*\          - ADC_CH_9 : ADC Channel9 selected
*\*\          - ADC_CH_10 : ADC Channel10 selected
*\*\          - ADC_CH_11 : ADC Channel11 selected
*\*\          - ADC_CH_12 : ADC Channel12 selected
*\*\          - ADC_CH_13 : ADC Channel13 selected
*\*\          - ADC_CH_14 : ADC Channel14 selected
*\*\          - ADC_CH_15 : ADC Channel15 selected
*\*\          - ADC_CH_16 : ADC Channel16 selected
*\*\          - ADC_CH_17 : ADC Channel17 selected
*\*\          - ADC_CH_18 : ADC Channel18 selected
*\*\return  none.
**/
void ADC_ConfigAnalogWatchdog1SingleChannel(ADC_Module* ADCx, uint8_t ADC_Channel)
{
    uint32_t tempreg;

    /* Get the old register value */
    tempreg = ADCx->CTRL1;
    /* Clear the Analog watchdog 1 channel select bits */
    tempreg &= (~ADC_CH_MASK);
    /* Set the Analog watchdog channel */
    tempreg |= ((uint32_t)ADC_Channel) << 12;
    /* Store the new register value */
    ADCx->CTRL1 = tempreg;
}
/**
*\*\name    ADC_SetAnalogWatchdog23MonitChannels.
*\*\fun     Set ADC analog watchdog 2/3 monitored channels: a single channel, multiple channels or all channels.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   AWDG_RegEnOffset :
*\*\          - ADC_AWDG2_EN_OFFSET : config analog watchdog 2.
*\*\          - ADC_AWDG3_EN_OFFSET : config analog watchdog 3. 
*\*\param   AWDG_ChannelGroup : channels monitored: flexible on channels monitored, selection is
*\*\          channel wise, from from 1 to all channels. Specificity of this analog watchdog: 
*\*\          Multiple channels can be selected.eg : 0x00000005 mean CH0 and CH2 are monitored.
*\*\          0x00000000 mean this analog watchdog disable.
*\*\return  none.
**/
void ADC_SetAnalogWatchdog23MonitChannels(ADC_Module* ADCx, uint8_t AWDG_RegEnOffset, uint32_t AWDG_ChannelGroup)
{
    uint32_t tempreg,temp;
    /* Get the old register value */
    tempreg = (uint32_t)ADCx;
    tempreg += AWDG_RegEnOffset;
    temp = *(__IO uint32_t*)tempreg;
    /* Clear the Analog watchdog 2/3 channel select bits */
    temp &= (~ADC_AWDG23_EN_MASK);
    /* Set the Analog watchdog channel */
    temp |= AWDG_ChannelGroup;
    /* Store the new register value */
    *(__IO uint32_t*)tempreg = temp;
}
/**
*\*\name    ADC_GetAnalogWatchdog23MonitChannels.
*\*\fun     Get ADC analog watchdog 2/3 monitored channels.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   AWDG_RegEnOffset :
*\*\          - ADC_AWDG2_EN_OFFSET : analog watchdog 2.
*\*\          - ADC_AWDG3_EN_OFFSET : analog watchdog 3. 
*\*\return  channels monitored by this analog watchdog2/3.
**/
uint32_t ADC_GetAnalogWatchdog23MonitChannels(ADC_Module* ADCx, uint8_t AWDG_RegEnOffset)
{
    uint32_t tempreg;

    tempreg = (uint32_t)ADCx;
    tempreg += AWDG_RegEnOffset;
    return ((*(__IO uint32_t*)tempreg) & ADC_AWDG23_EN_MASK);
}
/**
*\*\name    ADC_SetAnalogWatchdog23IntConfig.
*\*\fun     Enable or disable ADC analog watchdog 2/3 monitored channels interrupt.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   AWDG_RegIntEnOffset :
*\*\          - ADC_AWDG2_INTEN_OFFSET : config analog watchdog 2.
*\*\          - ADC_AWDG3_INTEN_OFFSET : config analog watchdog 3. 
*\*\param   AWDG_ChannelEn : channels monitored: flexible on channels monitored, selection is
*\*\          channel wise, from from 1 to all channels. Specificity of this analog watchdog: 
*\*\          Multiple channels can be selected.eg : 0x00000005 mean CH0 and CH2 monitored enable interrupt.
*\*\          0x00000000 mean this analog watchdog disable the interrupt.
*\*\return  none.
**/
void ADC_SetAnalogWatchdog23IntConfig(ADC_Module* ADCx, uint8_t AWDG_RegIntEnOffset, uint32_t AWDG_ChannelEn)
{

    uint32_t tempreg,temp;

    tempreg = (uint32_t)ADCx;
    tempreg += AWDG_RegIntEnOffset;
    temp = *(__IO uint32_t*)tempreg;
    /* Clear the Analog watchdog 2/3 channel select bits */
    temp &= (~ADC_AWDG23_INTEN_MASK);
    /* Set the Analog watchdog channel */
    temp |= AWDG_ChannelEn;
    /* Store the new register value */
    *(__IO uint32_t*)tempreg = temp;
 }

/**
*\*\name    ADC_GetAnalogWatchdog23MonitChannels.
*\*\fun     Get ADC analog watchdog 2/3 monitored channels.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   AWDG_RegEnOffset :
*\*\          - ADC_AWDG2_EN_OFFSET : analog watchdog 2.
*\*\          - ADC_AWDG3_EN_OFFSET : analog watchdog 3. 
*\*\return  channels monitored by this analog watchdog2/3 enable the interrupt or not.
**/
uint32_t ADC_GetAnalogWatchdog23IntConfig(ADC_Module* ADCx, uint8_t AWDG_RegEnOffset)
{
    uint32_t tempreg;

    tempreg = (uint32_t)ADCx;
    tempreg += AWDG_RegEnOffset;
    return ((*(__IO uint32_t*)tempreg) & ADC_AWDG23_INTEN_MASK);
}

/**
*\*\name    ADC_GetAnalogWatchdog23StatusFlag.
*\*\fun     Get ADC analog watchdog 2/3 monitored channels status flag.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   AWDG_RegSTSOffset :
*\*\          - ADC_AWDG2_STS_OFFSET : analog watchdog 2.
*\*\          - ADC_AWDG3_STS_OFFSET : analog watchdog 3. 
*\*\return    channels monitored by this analog watchdog2/3 indicates outside the programmed
*\*\          thresholds or not. 
**/
uint32_t ADC_GetAnalogWatchdog23StatusFlag(ADC_Module* ADCx, uint8_t AWDG_RegSTSOffset)
{
    uint32_t tempreg;

    tempreg = (uint32_t)ADCx;
    tempreg += AWDG_RegSTSOffset;

    return ((*(__IO uint32_t*)tempreg) & ADC_AWDG23_STATUS_MASK);
}

/**
*\*\name    ADC_ClearAnalogWatchdog23StatusFlag.
*\*\fun     Clear ADC analog watchdog 2/3 monitored channels status flag.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   AWDG_RegSTSOffset :
*\*\          - ADC_AWDG2_STS_OFFSET : analog watchdog 2.
*\*\          - ADC_AWDG3_STS_OFFSET : analog watchdog 3. 
*\*\param   AWDG_ChannelFlag : channels monitored flag wil l be cleared.
*\*\          eg : 0x00000005 mean CH0 and CH2 status flag will be cleared.
*\*\return    none. 
**/
void ADC_ClearAnalogWatchdog23StatusFlag(ADC_Module* ADCx, uint8_t AWDG_RegSTSOffset, uint32_t AWDG_ChannelFlag)
{
    uint32_t tempreg;

    tempreg = (uint32_t)ADCx;
    tempreg += AWDG_RegSTSOffset;

    /* Clear the Analog watchdog channel flag */
    *(__IO uint32_t*)tempreg = AWDG_ChannelFlag;
}


/**
*\*\name    ADC_GetFlagStatus.
*\*\fun     Checks whether the specified ADC flag is set or not.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   ADC_FLAG :
*\*\          - ADC_FLAG_ENDC
*\*\          - ADC_FLAG_EOC_ANY
*\*\          - ADC_FLAG_JENDC
*\*\          - ADC_FLAG_JEOC_ANY
*\*\          - ADC_FLAG_AWDG1
*\*\          - ADC_FLAG_ENDC_ERROR
*\*\          - ADC_FLAG_RDY
*\*\          - ADC_FLAG_PDRDY
*\*\          - ADC_FLAG_EOSAMP
*\*\          - ADC_FLAG_TCFLAG
*\*\          - ADC_FLAG_STR
*\*\          - ADC_FLAG_JSTR
*\*\return    The new state of ADC_FLAG (SET or RESET).
**/
FlagStatus ADC_GetFlagStatus(ADC_Module* ADCx, uint16_t ADC_FLAG)
{
    FlagStatus bitstatus ;
    /* Check the status of the specified ADC flag */
    if ((ADCx->STS & ((uint32_t)ADC_FLAG)) != (uint8_t)RESET)
    {
        /* ADC_FLAG is set */
        bitstatus = SET;
    }
    else
    {
        /* ADC_FLAG is reset */
        bitstatus = RESET;
    }
    /* Return the ADC_FLAG status */
    return bitstatus;
}

/**
*\*\name    ADC_ClearFlag.
*\*\fun     Clears pending flags of the specified ADC.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   ADC_FLAG :
*\*\          - ADC_FLAG_ENDC
*\*\          - ADC_FLAG_EOC_ANY
*\*\          - ADC_FLAG_JENDC
*\*\          - ADC_FLAG_JEOC_ANY
*\*\          - ADC_FLAG_AWDG1
*\*\          - ADC_FLAG_ENDC_ERROR
*\*\          - ADC_FLAG_RDY
*\*\          - ADC_FLAG_PDRDY
*\*\          - ADC_FLAG_EOSAMP
*\*\          - ADC_FLAG_TCFLAG
*\*\          - ADC_FLAG_STR
*\*\          - ADC_FLAG_JSTR
*\*\return    none.
**/
void ADC_ClearFlag(ADC_Module* ADCx, uint16_t ADC_FLAG)
{
    /* Clear the selected ADC flags */
    ADCx->STS = ((uint32_t)ADC_FLAG & ADC_FLAG_ALL_MASK) ;
}

/**
*\*\name    ADC_ConfigInt.
*\*\fun     Enables or disables the specified ADC interrupts.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   ADC_IT :
*\*\          - ADC_INT_ENDC
*\*\          - ADC_INT_ENDCA
*\*\          - ADC_INT_JENDC
*\*\          - ADC_INT_JENDCA
*\*\          - ADC_INT_AWD1
*\*\          - ADC_INT_ENDCERR
*\*\          - ADC_INT_RDY
*\*\          - ADC_INT_PDRDY
*\*\          - ADC_INT_EOSAMP
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return    none.
**/
void ADC_ConfigInt(ADC_Module* ADCx, uint16_t ADC_IT, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected ADC interrupts */
        ADCx->INTEN |= (uint32_t)ADC_IT;
    }
    else
    {
        /* Disable the selected ADC interrupts */
        ADCx->INTEN &= (~(uint32_t)ADC_IT);
    }
}
/**
*\*\name    ADC_GetIntStatus.
*\*\fun     Checks whether the specified ADC interrupt has occurred or not.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   ADC_IT : specifies the ADC interrupt source to check.
*\*\          - ADC_INT_ENDC
*\*\          - ADC_INT_ENDCA
*\*\          - ADC_INT_JENDC
*\*\          - ADC_INT_JENDCA
*\*\          - ADC_INT_AWD1
*\*\          - ADC_INT_ENDCERR
*\*\          - ADC_INT_RDY
*\*\          - ADC_INT_PDRDY
*\*\          - ADC_INT_EOSAMP
*\*\return    The new state of ADC_IT (SET or RESET).
**/
INTStatus ADC_GetIntStatus(ADC_Module* ADCx, uint16_t ADC_IT)
{
    INTStatus bitstatus;
    uint32_t enablestatus;

    /* Get the ADC_IT enable bit status */
    enablestatus = (ADCx->INTEN & (uint32_t)ADC_IT);
    /* Check the status of the specified ADC interrupt */
    if(((ADCx->STS & ADC_IT) != 0U) && (enablestatus != 0U))
    {
        /* ADC_IT is set */
        bitstatus = SET;
    }
    else
    {
        /* ADC_IT is reset */
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
*\*\name    ADC_ClearIntPendingBit.
*\*\fun     Clears  interrupt pending bits of the specified ADC.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   ADC_IT :
*\*\          - ADC_INT_ENDC
*\*\          - ADC_INT_ENDCA
*\*\          - ADC_INT_JENDC
*\*\          - ADC_INT_JENDCA
*\*\          - ADC_INT_AWD1
*\*\          - ADC_INT_ENDCERR
*\*\          - ADC_INT_RDY
*\*\          - ADC_INT_PDRDY
*\*\          - ADC_INT_EOSAMP
*\*\return    none.
**/
void ADC_ClearIntPendingBit(ADC_Module* ADCx, uint16_t ADC_IT)
{
    /* Clear the selected ADC interrupt pending bits */
    ADCx->STS = ((uint32_t)ADC_IT & ADC_INTFLAG_ALL_MASK) ;
}


/**
*\*\name    ADC_SetChannelSingleDiff.
*\*\fun     Set mode single-ended or differential input of the selected ADC channel.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   Channel : 
*\*\          - ADC_CH_1
*\*\          - ADC_CH_2
*\*\          - ADC_CH_3
*\*\          - ADC_CH_4 
*\*\          - ADC_CH_5
*\*\          - ADC_CH_6
*\*\          - ADC_CH_7
*\*\          - ADC_CH_8 
*\*\          - ADC_CH_9 
*\*\          - ADC_CH_10
*\*\          - ADC_CH_11
*\*\          - ADC_CH_12
*\*\          - ADC_CH_13
*\*\          - ADC_CH_14
*\*\          - ADC_CH_15
*\*\          - ADC_CH_16
*\*\          - ADC_CH_17
*\*\          - ADC_CH_18
*\*\param   SingleDiff : 
*\*\          - ADC_SINGLE_ENDED
*\*\          - ADC_DIFFERENTIAL_ENDED
*\*\return    none.
*\*\note  Some channels are internally fixed to single-ended inputs: please refer to ADC chapter of user manual.
**/
void ADC_SetChannelSingleDiff(ADC_Module* ADCx, uint32_t Channel, uint32_t SingleDiff)
{
    if (SingleDiff == ADC_DIFFERENTIAL_ENDED)
    {
        ADCx->DIFSEL |= ((uint32_t)0x01 << Channel);
    }
    else
    {
        ADCx->DIFSEL &= (~((uint32_t)0x01 << Channel));
    }
}
/**
*\*\name    ADC_SetCalibrationFactor.
*\*\fun     Set ADC calibration factor in the single-ended or differential mode.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   SingleDiff : 
*\*\          - ADC_SINGLE_ENDED
*\*\          - ADC_DIFFERENTIAL_ENDED
*\*\param   CalibrationFactor : The parameter between Min_Data=0x00 and Max_Data=0x7F
*\*\return    none.
**/
void ADC_SetCalibrationFactor(ADC_Module *ADCx, uint32_t SingleDiff, uint32_t CalibrationFactor)
{
    if (SingleDiff == ADC_DIFFERENTIAL_ENDED)
    {
        ADCx->CALFACT &= (~(ADC_CALFACT_CALFACTD_MASK));
        ADCx->CALFACT |= (CalibrationFactor << 16);
    }
    else
    {
        ADCx->CALFACT &= (~(ADC_CALFACT_CALFACTS_MASK));
        ADCx->CALFACT |= CalibrationFactor;
    }
}
/**
*\*\name    ADC_SetGainCompensation.
*\*\fun     Set ADC gain compensation.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   GainCompensationValue : 
*\*\          when this value is 0, it means gain compensation will be disabled and value set to 0.
*\*\          when this value is 1 ~ 16393, gain compensation will be enabled with specified value.
*\*\return    none.
**/
void ADC_SetGainCompensation(ADC_Module *ADCx, uint32_t GainCompensationValue)
{
    if(GainCompensationValue != 0)
    {
        /*Enables the selected ADC gain compensation mode**/
        ADCx->CTRL2 |= ADC_GAIN_COMPENSATION_EN_MASK; 
    }
    else
    {
        /*Disables the selected ADC gain compensation mode**/
        ADCx->CTRL2 &= (~ADC_GAIN_COMPENSATION_EN_MASK);
    }
    ADCx->GCOMP = (GainCompensationValue & ADC_Gain_Compensation_MASK);
}

/**
*\*\name    ADC_SetConvResultBitNum.
*\*\fun     Set ADC resolution including 12bit,10bit,8bit,6bit .
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   ResultBitNum : 
*\*\          - ADC_DATA_RES_12BIT
*\*\          - ADC_DATA_RES_10BIT
*\*\          - ADC_DATA_RES_8BIT
*\*\          - ADC_DATA_RES_6BIT 
*\*\return    none.
**/
void ADC_SetConvResultBitNum(ADC_Module* ADCx, uint32_t ResultBitNum)
{
    uint32_t tempreg;

    /* Get the old register value */
    tempreg = ADCx->CTRL3;
    /* Clear resolution select bits */
    tempreg &= (~ADC_DATA_RES_MASK);
    /* Set ADC resolution */
    tempreg |= ResultBitNum;
    /* Store the new register value */
    ADCx->CTRL3 = tempreg;
}

/**
*\*\name    ADC_SelectClockMode.
*\*\fun     Set Adc Clock mode from AHB or PLL.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   ClockMode : 
*\*\          - ADC_CLOCK_MODE_PLL
*\*\          - ADC_CLOCK_MODE_AHB
*\*\return    none.
**/
void ADC_SelectClockMode(ADC_Module* ADCx, uint32_t ClockMode)
{
    if(ClockMode == ADC_CLOCK_MODE_PLL)
    {
        ADCx->CTRL3 |= ADC_CLOCK_MODE_PLL; 
    }
    else
    {
        ADCx->CTRL3 &= (~ADC_CLOCK_MODE_PLL); 
    }
}
/**
*\*\name    ADC_SetBypassCalibration.
*\*\fun     Enable or disable ADC calibration bypass mode.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return    none. 
**/
void ADC_SetBypassCalibration(ADC_Module* ADCx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        ADCx->CTRL3 |= ADC_BYPASS_CAL_MASK;
    } 
    else
    {
        ADCx->CTRL3 &= (~ADC_BYPASS_CAL_MASK);
    }
}
/**
*\*\name    ADC_EnableCalibrationAutoLoad.
*\*\fun     Enables or disables the specified ADC calibration value auto load.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ADC_EnableCalibrationAutoLoad(ADC_Module* ADCx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected ADC calibration auto load */
        ADCx->CTRL3 |= ADC_CAL_AUTO_LOAD_MASK;
    }
    else
    {
        /* Disable the selected ADC calibration auto load */
        ADCx->CTRL3 &= (~ADC_CAL_AUTO_LOAD_MASK);
    }
}

/**
*\*\name    ADC_EnableBatteryVoltageMonitor.
*\*\fun     Enables or disables the specified ADC battery voltage monitor.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
*\*\note  if users wants to measure the VBAT/2, they should set this bit first.
**/
void ADC_EnableBatteryVoltageMonitor(ADC_Module* ADCx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected ADC battery voltage monitor */
        ADCx->CTRL3 |= ADC_VOLT_MONITOR_EN_MASK;
    }
    else
    {
        /* Disable the selected ADC battery voltage monitor */
        ADCx->CTRL3 &=  (~ADC_VOLT_MONITOR_EN_MASK);
    }
}

/**
*\*\name    ADC_EnableDeepSleepMode.
*\*\fun     Enables or disables the specified ADC entering deep sleep mode.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ADC_EnableDeepSleepMode(ADC_Module* ADCx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected ADC entering deep sleep mode */
        ADCx->CTRL3 |= ADC_DEEP_SLEEP_MODE_MASK;
    }
    else
    {
        /* Disable the selected ADC entering deep sleep mode */
        ADCx->CTRL3 &=  (~ADC_DEEP_SLEEP_MODE_MASK);
    }
}
/**
*\*\name    ADC_ConfigOverSamplingRatioAndShift.
*\*\fun     Set ADC oversampling rate times and shift bit.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   Ratio : ADC oversampling ratio times 
*\*\          - ADC_OVERSAMPE_RATE_TIMES_1  
*\*\          - ADC_OVERSAMPE_RATE_TIMES_2  
*\*\          - ADC_OVERSAMPE_RATE_TIMES_4   
*\*\          - ADC_OVERSAMPE_RATE_TIMES_8  
*\*\          - ADC_OVERSAMPE_RATE_TIMES_16   
*\*\          - ADC_OVERSAMPE_RATE_TIMES_32 
*\*\          - ADC_OVERSAMPE_RATE_TIMES_64  
*\*\          - ADC_OVERSAMPE_RATE_TIMES_128
*\*\          - ADC_OVERSAMPE_RATE_TIMES_256 
*\*\param   Shift : ADC oversampling data right shift 
*\*\          - ADC_OVERSAMPE_DATA_SHIFT_0 
*\*\          - ADC_OVERSAMPE_DATA_SHIFT_1 
*\*\          - ADC_OVERSAMPE_DATA_SHIFT_2 
*\*\          - ADC_OVERSAMPE_DATA_SHIFT_3  
*\*\          - ADC_OVERSAMPE_DATA_SHIFT_4 
*\*\          - ADC_OVERSAMPE_DATA_SHIFT_5
*\*\          - ADC_OVERSAMPE_DATA_SHIFT_6
*\*\          - ADC_OVERSAMPE_DATA_SHIFT_7 
*\*\          - ADC_OVERSAMPE_DATA_SHIFT_8 
*\*\return  none
**/
void ADC_ConfigOverSamplingRatioAndShift(ADC_Module *ADCx, uint32_t Ratio, uint32_t Shift)
{
    uint32_t tempreg;
    /* Get the old register value */
    tempreg = ADCx->CTRL3;
    /* Clear oversampling ratio and shift select bits */
    tempreg &= (~(ADC_OVERSAMPE_RATE_TIMES_MASK | ADC_OVERSAMPE_DATA_SHIFT_MASK));
    /* Set ADC oversampling ratio and shift bit */
    tempreg |= (Ratio | Shift);
    /* Store the new register value */
    ADCx->CTRL3 = tempreg;
}

/**
*\*\name    ADC_SetOverSamplingScope.
*\*\fun     Set ADC oversampling scope.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   OversampleScope :This parameter can be one of the following values 
*\*\          - ADC_OVERSAMPE_DISABLE  
*\*\          - ADC_OVERSAMPE_REGULAR_CONTINUED  
*\*\          - ADC_OVERSAMPE_REGULAR_RESUMED   
*\*\          - ADC_OVERSAMPE_INJECTED  
*\*\          - ADC_OVERSAMPE_REGULAR_INJECTED   
*\*\return  none
**/
void ADC_SetOverSamplingScope(ADC_Module *ADCx, uint32_t OversampleScope)
{
    uint32_t tempreg;
    /* Get the old register value */
    tempreg = ADCx->CTRL3;
    /* Clear oversampling select bits */
    tempreg &= (~(ADC_OVERSAMPE_REG_EN_MASK | ADC_OVERSAMPE_INJ_EN_MASK | ADC_OVERSAMPE_MODE_MASK));
    /* Set ADC oversampling select bits */
    tempreg |= (OversampleScope);
    /* Store the new register value */
    ADCx->CTRL3 = tempreg;
}

/**
*\*\name    ADC_SetOverSamplingDiscont.
*\*\fun     Set ADC oversampling discontinuous mode (triggered mode).
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ADC_EnableOverSamplingDiscont(ADC_Module *ADCx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        ADCx->CTRL3 |= ADC_OVERSAMPE_TRIG_REG_MASK;
    }
    else
    {
        ADCx->CTRL3 &= (~ADC_OVERSAMPE_TRIG_REG_MASK);
    }
}

/**
*\*\name    ADC_EnableCH1PositiveEndConnetPGA_P.
*\*\fun     enable or disable ADC channel 1 positive end connecting to output of PGAx positive end.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ADC_EnableCH1PositiveEndConnetPGA_P(ADC_Module *ADCx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        ADCx->CTRL3 |= ADC_INP1_SELECTION_MASK;
    }
    else
    {
        ADCx->CTRL3 &= (~ADC_INP1_SELECTION_MASK);
    }
}
/**
*\*\name    ADC_EnableCH1NegtiveEndConnetPGA_N.
*\*\fun     enable or disable ADC channel 2 negtive end connecting to output of PGAx negtive end.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ADC_EnableCH1NegtiveEndConnetPGA_N(ADC_Module *ADCx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        ADCx->CTRL3 |= ADC_INN1_SELECTION_MASK;
    }
    else
    {
        ADCx->CTRL3 &= (~ADC_INN1_SELECTION_MASK);
    }
}

/**
*\*\name    ADC_EnableCH2PositiveEndConnetPGA_N.
*\*\fun     enable or disable ADC channel 2 positive end connecting to output of PGAx negtive end.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void ADC_EnableCH2PositiveEndConnetPGA_N(ADC_Module *ADCx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        ADCx->CTRL3 |= ADC_INP2_SELECTION_MASK;
    }
    else
    {
        ADCx->CTRL3 &= (~ADC_INP2_SELECTION_MASK);
    }
}
/**
*\*\name    ADC_EnableFIFO.
*\*\fun     Enables or disables the specified ADC FIFO.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return    none.
**/
void ADC_EnableFIFO(ADC_Module* ADCx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected ADC FIFO  */
        ADCx->FIFOCFG |= ADC_FIFO_EN_MASK;
    }
    else
    {
        /* Disable the selected ADC FIFO  */
        ADCx->FIFOCFG &= (~ADC_FIFO_EN_MASK);
    }
}
/**
*\*\name    ADC_ClearFIFO.
*\*\fun     Clear the specified ADC FIFO.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\return    none.
**/
void ADC_ClearFIFO(ADC_Module* ADCx)
{
    /* Clear the selected ADC FIFO  */
    ADCx->FIFOCFG |= ADC_FIFO_CLR_MASK;
}

/**
*\*\name    ADC_ConfigFIFOWaterLevel.
*\*\fun     Configures the specified ADC FIFO water level .
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   FIFO_Level : This parameter must be between 1 to 10.
*\*\return    none.
**/
void ADC_ConfigFIFOWaterLevel(ADC_Module* ADCx, uint32_t FIFO_Level)
{
    uint32_t tempreg;
    /* Get the old register value */
    tempreg = ADCx->FIFOCFG;
    /* Clear WL(water level) select bits */
    tempreg &= (~ADC_FIFO_WATER_LEVEL_MASK);
    /* Set ADC WL(water level) select bits */
    tempreg |= (FIFO_Level << 6);
    /* Store the new register value */
    ADCx->FIFOCFG = tempreg;
}
/**
*\*\name    ADC_GetFIFOInvalidedDataCount.
*\*\fun     Get the total counts of invalided data .
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\return    The the total counts of invalided data .This value is between 0 to 12.
**/
uint8_t ADC_GetFIFOInvalidedDataCount(ADC_Module* ADCx)
{
    return (uint8_t)((ADCx->FIFOSTS & (ADC_FIFO_INVALIED_DATA_COUNT_MASK)) >> 5);
}
/**
*\*\name    ADC_GetFIFOFlagStatus.
*\*\fun     Checks whether the specified ADC flag in fifo mode is set or not.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   ADC_FIFOFLAG :
*\*\          - ADC_FIFO_FLAG_RERR
*\*\          - ADC_FIFO_FLAG_WERR
*\*\          - ADC_FIFO_FLAG_FULL
*\*\          - ADC_FIFO_FLAG_EMPTY
*\*\          - ADC_FIFO_FLAG_HALF_FULL
*\*\          - ADC_FIFO_FLAG_NOT_EMPTY
*\*\return    The new state of ADC_FIFOFLAG (SET or RESET).
**/
FlagStatus ADC_GetFIFOFlagStatus(ADC_Module* ADCx, uint16_t ADC_FIFOFLAG)
{
    FlagStatus bitstatus ;
    /* Check the status of the specified ADC flag */
    if ((ADCx->FIFOSTS & ((uint32_t)ADC_FIFOFLAG)) != (uint8_t)RESET)
    {
        /* ADC_FIFOFLAG is set */
        bitstatus = SET;
    }
    else
    {
        /* ADC_FIFOFLAG is reset */
        bitstatus = RESET;
    }
    /* Return the ADC_FIFOFLAG status */
    return bitstatus;
}
/**
*\*\name    ADC_ClearFIFOFlag.
*\*\fun     Clears FIFO status bit of the specified ADC.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   ADC_FIFO_FLAG :
*\*\          - ADC_FIFO_FLAG_RERR
*\*\          - ADC_FIFO_FLAG_WERR
*\*\          - ADC_FIFO_FLAG_FULL
*\*\          - ADC_FIFO_FLAG_EMPTY
*\*\          - ADC_FIFO_FLAG_HALF_FULL
*\*\          - ADC_FIFO_FLAG_NOT_EMPTY
*\*\return    none.
**/
void ADC_ClearFIFOFlag(ADC_Module* ADCx, uint16_t ADC_FIFO_FLAG)
{
    /* Clear the selected ADC FIFO interrupt pending bits */
    ADCx->FIFOSTS = ((uint32_t)ADC_FIFO_FLAG) ;
}
/**
*\*\name    ADC_ConfigFIFOInt.
*\*\fun     Enables or disables the specified ADC interrupts in FIFO mode.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   ADC_FIFO_IT :
*\*\          - ADC_FIFO_INT_RERR
*\*\          - ADC_FIFO_INT_WERR
*\*\          - ADC_FIFO_INT_FULL
*\*\          - ADC_FIFO_INT_EMPTY
*\*\          - ADC_FIFO_INT_HALF_FULL
*\*\          - ADC_FIFO_INT_NOT_EMPTY
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return    none.
**/
void ADC_ConfigFIFOInt(ADC_Module* ADCx, uint16_t ADC_FIFO_IT, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected ADC FIFO interrupts */
        ADCx->FIFOCFG |= (uint32_t)ADC_FIFO_IT;
    }
    else
    {
        /* Disable the selected ADC FIFO interrupts */
        ADCx->FIFOCFG &= (~(uint32_t)ADC_FIFO_IT);
    }
}
/**
*\*\name    ADC_ClearFIFOIntPendingBit.
*\*\fun     Clears FIFO interrupt pending bits of the specified ADC.
*\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
*\*\param   ADC_FIFO_IT :
*\*\          - ADC_FIFO_INT_RERR
*\*\          - ADC_FIFO_INT_WERR
*\*\          - ADC_FIFO_INT_FULL
*\*\          - ADC_FIFO_INT_EMPTY
*\*\          - ADC_FIFO_INT_HALF_FULL
*\*\          - ADC_FIFO_INT_NOT_EMPTY
*\*\return    none.
**/
void ADC_ClearFIFOIntPendingBit(ADC_Module* ADCx, uint16_t ADC_FIFO_IT)
{
    /* Clear the selected ADC FIFO interrupt pending bits */
    ADCx->FIFOSTS |= ((uint32_t)ADC_FIFO_IT) ;
}

/**
 *\*\name   ADC_ConfigRegularExtLineTrigSource.
 *\*\fun    Configurate ADC external line trigger source for regular channel.
 *\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
 *\*\param  ADC_trigger : 
 *\*\          specifies the external line trigger source be configured.
 *\*\          - ADC_TRIG_EXTI_0
 *\*\          - ADC_TRIG_EXTI_1
 *\*\          - ADC_TRIG_EXTI_2
 *\*\          - ADC_TRIG_EXTI_3
 *\*\          - ADC_TRIG_EXTI_4
 *\*\          - ADC_TRIG_EXTI_5
 *\*\          - ADC_TRIG_EXTI_6
 *\*\          - ADC_TRIG_EXTI_7
 *\*\          - ADC_TRIG_EXTI_8
 *\*\          - ADC_TRIG_EXTI_9
 *\*\          - ADC_TRIG_EXTI_10
 *\*\          - ADC_TRIG_EXTI_11
 *\*\          - ADC_TRIG_EXTI_12
 *\*\          - ADC_TRIG_EXTI_13
 *\*\          - ADC_TRIG_EXTI_14
 *\*\          - ADC_TRIG_EXTI_15
 *\*\return none
 */
void ADC_ConfigRegularExtLineTrigSource(ADC_Module* ADCx, uint32_t ADC_trigger)
{
    uint32_t tempreg;
    /* Get the old register value */
    tempreg = ADCx->CTRL4;
    
    /* clear ADC_CTRL4 register ETRRSEL bit */
    tempreg &= (~(ADC_CTRL4_EXTRRSEL_MASK));
    /* Set ETRRSEL select bits */
    tempreg |= (ADC_trigger << 16U);
     /* Store the new register value */
    ADCx->CTRL4 = tempreg;
}

/**
 *\*\name   ADC_ConfigInjectedExtLineTrigSource.
 *\*\fun    Configurate ADC external line trigger source for injected channel.
 *\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
 *\*\param  ADC_trigger : 
 *\*\          specifies the external line trigger source be configured.
 *\*\          - ADC_TRIG_EXTI_0
 *\*\          - ADC_TRIG_EXTI_1
 *\*\          - ADC_TRIG_EXTI_2
 *\*\          - ADC_TRIG_EXTI_3
 *\*\          - ADC_TRIG_EXTI_4
 *\*\          - ADC_TRIG_EXTI_5
 *\*\          - ADC_TRIG_EXTI_6
 *\*\          - ADC_TRIG_EXTI_7
 *\*\          - ADC_TRIG_EXTI_8
 *\*\          - ADC_TRIG_EXTI_9
 *\*\          - ADC_TRIG_EXTI_10
 *\*\          - ADC_TRIG_EXTI_11
 *\*\          - ADC_TRIG_EXTI_12
 *\*\          - ADC_TRIG_EXTI_13
 *\*\          - ADC_TRIG_EXTI_14
 *\*\          - ADC_TRIG_EXTI_15
 *\*\return none
 */
void ADC_ConfigInjectedExtLineTrigSource(ADC_Module* ADCx, uint32_t ADC_trigger)
{
    uint32_t tempreg;

    /* Get the old register value */
    tempreg = ADCx->CTRL4;
    /* clear ADC_CTRL4 register ETRISEL bit */
    tempreg &= (~(ADC_CTRL4_EXTRISEL_MASK));
    /* Set ETRRSEL select bits */
    tempreg |= (ADC_trigger << 20U);
     /* Store the new register value */
    ADCx->CTRL4 = tempreg;
}


/**
 *\*\name   ADC_ConfigADCPowerSupport.
 *\*\fun    Configurate ADC power support ,select the external MR or internal LDO.
 *\*\param   ADCx :
*\*\          - ADC1
*\*\          - ADC2
*\*\          - ADC3
*\*\          - ADC4
 *\*\param  ADC_PowerSupportSel : 
 *\*\          - ADC_EXTERN_POWER_SUPPORT , select MR power support 
 *\*\          - ADC_INTERN_POWER_SUPPORT , select LDO power support 
 *\*\return none
 */
void ADC_ConfigADCPowerSupport(ADC_Module* ADCx, uint32_t ADC_PowerSupportSel)
{
    uint32_t tempreg;

    /* Get the old register value */
    tempreg = ADCx->PCTRL;
    /* clear ADC_PCTRL register EXPEN RANGESEL VREFLDOEN bit */
    tempreg &= (~(ADC_PCTRL_EXPEN_MASK | ADC_PCTRL_RANGESEL_MASK | ADC_PCTRL_VREFLDOEN_MASK));
    /* Set EXPEN RANGESEL VREFLDOEN select bits */
    tempreg |= ADC_PowerSupportSel;
     /* Store the new register value */
    ADCx->PCTRL = tempreg;
}
/**
*\*\name    ADC_ConfigClk.
*\*\fun     Configures the ADCHCLK prescaler.
*\*\param   ADC_ClkMode :
*\*\         - ADC_CTRL3_CKMOD_AHB
*\*\         - ADC_CTRL3_CKMOD_PLL
*\*\param   RCC_ADCHCLKPrescaler : specifies the ADCHCLK prescaler.
*\*\        When ADC_ClkMode = ADC_CTRL3_CKMOD_AHB: RCC_ADCHCLKPrescaler can be on of the following values:
*\*\         - RCC_ADCHCLK_DIV1        
*\*\         - RCC_ADCHCLK_DIV2        
*\*\         - RCC_ADCHCLK_DIV3        
*\*\         - RCC_ADCHCLK_DIV4        
*\*\         - RCC_ADCHCLK_DIV6        
*\*\         - RCC_ADCHCLK_DIV8        
*\*\         - RCC_ADCHCLK_DIV10       
*\*\         - RCC_ADCHCLK_DIV12       
*\*\         - RCC_ADCHCLK_DIV16       
*\*\         - RCC_ADCHCLK_DIV32  
*\*\        When ADC_ClkMode = ADC_CTRL3_CKMOD_PLL: RCC_ADCHCLKPrescaler can be on of the following values:
*\*\         - RCC_ADCPLLCLK_DIV1 
*\*\         - RCC_ADCPLLCLK_DIV2 
*\*\         - RCC_ADCPLLCLK_DIV3 
*\*\         - RCC_ADCPLLCLK_DIV4 
*\*\         - RCC_ADCPLLCLK_DIV6 
*\*\         - RCC_ADCPLLCLK_DIV8 
*\*\         - RCC_ADCPLLCLK_DIV10
*\*\         - RCC_ADCPLLCLK_DIV12
*\*\return    none.
**/
void ADC_ConfigClk(ADC_CTRL3_CKMOD ADC_ClkMode, uint32_t RCC_ADCHCLKPrescaler)
{
    if(ADC_ClkMode == ADC_CTRL3_CKMOD_AHB)
    {
        RCC_ConfigAdcPllClk(RCC_ADCPLLCLK_SRC_PLL, RCC_ADCPLLCLK_DIV1, RCC_ADCPLLCLK_DISABLE);
        RCC_ConfigAdcHclk(RCC_ADCHCLKPrescaler);
        ADC_SelectClockMode(ADC1, ADC_CLOCK_MODE_AHB);
        ADC_SelectClockMode(ADC2, ADC_CLOCK_MODE_AHB);
        ADC_SelectClockMode(ADC3, ADC_CLOCK_MODE_AHB);
        ADC_SelectClockMode(ADC4, ADC_CLOCK_MODE_AHB);
    }
    else
    {
        RCC_ConfigAdcPllClk(RCC_ADCPLLCLK_SRC_PLL,RCC_ADCHCLKPrescaler, RCC_ADCPLLCLK_ENABLE);
        RCC_ConfigAdcHclk(RCC_ADCHCLK_DIV1);
        ADC_SelectClockMode(ADC1, ADC_CLOCK_MODE_PLL);
        ADC_SelectClockMode(ADC2, ADC_CLOCK_MODE_PLL);
        ADC_SelectClockMode(ADC3, ADC_CLOCK_MODE_PLL);
        ADC_SelectClockMode(ADC4, ADC_CLOCK_MODE_PLL);
    }
}




