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
 * @file n32h47x_48x_pga.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
 */
#include "n32h47x_48x_pga.h"
#include "n32h47x_48x_rcc.h"

/** PGA Driving Functions Declaration **/ 

/**
*\*\name    PGA_DeInit.
*\*\fun     Reset the PGA registers.
*\*\return  none
**/
void PGA_DeInit(void)
{
    RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_PGA);
}

/**
*\*\name    PGA_StructInit.
*\*\fun     Fills all PGA_InitStruct member with default value.
*\*\param   PGA_InitStruct :
*\*\          - Vmsel
*\*\          - Vpsel
*\*\          - Vmssel
*\*\          - Vpssel
*\*\          - Gain1
*\*\          - Gain2
*\*\          - TimeAutoMuxEn
*\*\          - DiffModeEn
*\*\          - En2
*\*\          - En1
*\*\return  none
**/
void PGA_StructInit(PGA_InitType* PGA_InitStruct)
{
    /* Initialize the Vmsel��Vpsel��Vmssel��Vpssel*/
    PGA_InitStruct->Vmsel            = PGAX_CTRL_VMSEL_RES;
    PGA_InitStruct->Vpsel            = PGAX_CTRL_VPSEL_RES;
    PGA_InitStruct->Vmssel           = PGAX_CTRL_VMSSEL_RES;
    PGA_InitStruct->Vpssel           = PGAX_CTRL_VPSSEL_RES;

    /* Initialize the PGA Channel 1 Gain*/
    PGA_InitStruct->Gain1            = PGA_CTRL_CH1GAIN_1_DIFF_2;

    /* Initialize the PGA Channel 2 Gain*/
    PGA_InitStruct->Gain2            = PGA_CTRL_CH2GAIN_1_DIFF_2;

    /* Disable the timer control mux mode  */
    PGA_InitStruct->TimeAutoMuxEn    = DISABLE;

    /* Disable PGA differential mode  */
    PGA_InitStruct->DiffModeEn       = DISABLE;

    /* Disable the PGA Channel 1 and 2 */
    PGA_InitStruct->En2              = DISABLE;
    PGA_InitStruct->En1              = DISABLE;
}

/**
*\*\name    PGA_Init.
*\*\fun     Initializes the PGAx according to PGA_InitStruct.
*\*\param   PGAx :
*\*\          - PGA1
*\*\          - PGA2
*\*\          - PGA3
*\*\          - PGA4
*\*\param   PGA_InitStruct :
*\*\          - Vmsel
*\*\             PGA1 VMSEL
*\*\             - PGA1_CTRL_VMSEL_PF8
*\*\             - PGA1_CTRL_VMSEL_PF10       
*\*\             - PGA1_CTRL_VMSEL_PC3        
*\*\             - PGA1_CTRL_VMSEL_PA2        
*\*\             - PGA1_CTRL_VMSEL_PA3        
*\*\             - PGA1_CTRL_VMSEL_PA5        
*\*\             - PGA1_CTRL_VMSEL_PC5        
*\*\             - PGA1_CTRL_VMSEL_DAC2_IOUT  
*\*\             - PGA1_CTRL_VMSEL_DAC6_IOUT  
*\*\             PGA2 VMSEL
*\*\             - PGA2_CTRL_VMSEL_PB0        
*\*\             - PGA2_CTRL_VMSEL_PF9        
*\*\             - PGA2_CTRL_VMSEL_PF10       
*\*\             - PGA2_CTRL_VMSEL_PA2        
*\*\             - PGA2_CTRL_VMSEL_PA3        
*\*\             - PGA2_CTRL_VMSEL_PA5        
*\*\             - PGA2_CTRL_VMSEL_PC5        
*\*\             - PGA2_CTRL_VMSEL_PB15       
*\*\             - PGA2_CTRL_VMSEL_DAC2_IOUT  
*\*\             - PGA2_CTRL_VMSEL_DAC6_IOUT  
*\*\             PGA3 VMSEL
*\*\             - PGA3_CTRL_VMSEL_PF10       
*\*\             - PGA3_CTRL_VMSEL_PC1        
*\*\             - PGA3_CTRL_VMSEL_PA2        
*\*\             - PGA3_CTRL_VMSEL_PA5        
*\*\             - PGA3_CTRL_VMSEL_PC4        
*\*\             - PGA3_CTRL_VMSEL_PB2        
*\*\             - PGA3_CTRL_VMSEL_PB10       
*\*\             - PGA3_CTRL_VMSEL_DAC2_IOUT  
*\*\             - PGA3_CTRL_VMSEL_DAC6_IOUT  
*\*\             PGA4 VMSEL
*\*\             - PGA4_CTRL_VMSEL_PF10       
*\*\             - PGA4_CTRL_VMSEL_PA1        
*\*\             - PGA4_CTRL_VMSEL_PB1        
*\*\             - PGA4_CTRL_VMSEL_PB10       
*\*\             - PGA4_CTRL_VMSEL_PD8        
*\*\             - PGA4_CTRL_VMSEL_PC9        
*\*\             - PGA4_CTRL_VMSEL_DAC2_IOUT  
*\*\             - PGA4_CTRL_VMSEL_DAC6_IOUT
*\*\          - Vpsel
*\*\             PGA1 VPSEL
*\*\             - PGA1_CTRL_VPSEL_PF7        
*\*\             - PGA1_CTRL_VPSEL_PC2        
*\*\             - PGA1_CTRL_VPSEL_PA1        
*\*\             - PGA1_CTRL_VPSEL_PA3        
*\*\             - PGA1_CTRL_VPSEL_PA5        
*\*\             - PGA1_CTRL_VPSEL_PA7        
*\*\             - PGA1_CTRL_VPSEL_PB1        
*\*\             - PGA1_CTRL_VPSEL_DAC1_IOUT  
*\*\             - PGA1_CTRL_VPSEL_DAC5_IOUT  
*\*\             PGA2 VPSEL
*\*\             - PGA2_CTRL_VPSEL_PF7        
*\*\             - PGA2_CTRL_VPSEL_PC3        
*\*\             - PGA2_CTRL_VPSEL_PA1        
*\*\             - PGA2_CTRL_VPSEL_PA2        
*\*\             - PGA2_CTRL_VPSEL_PA4        
*\*\             - PGA2_CTRL_VPSEL_PA7        
*\*\             - PGA2_CTRL_VPSEL_PB0        
*\*\             - PGA2_CTRL_VPSEL_PE8        
*\*\             - PGA2_CTRL_VPSEL_PB14       
*\*\             - PGA2_CTRL_VPSEL_PD12       
*\*\             - PGA2_CTRL_VPSEL_PD14       
*\*\             - PGA2_CTRL_VPSEL_DAC1_IOUT  
*\*\             - PGA2_CTRL_VPSEL_DAC5_IOUT  
*\*\             PGA3 VPSEL
*\*\             - PGA3_CTRL_VPSEL_PF7        
*\*\             - PGA3_CTRL_VPSEL_PC0        
*\*\             - PGA3_CTRL_VPSEL_PC3        
*\*\             - PGA3_CTRL_VPSEL_PA1        
*\*\             - PGA3_CTRL_VPSEL_PA5        
*\*\             - PGA3_CTRL_VPSEL_PA6        
*\*\             - PGA3_CTRL_VPSEL_PB0        
*\*\             - PGA3_CTRL_VPSEL_PB13       
*\*\             - PGA3_CTRL_VPSEL_PC9        
*\*\             - PGA3_CTRL_VPSEL_DAC1_IOUT  
*\*\             - PGA3_CTRL_VPSEL_DAC5_IOUT  
*\*\             PGA4 VPSEL
*\*\             - PGA4_CTRL_VPSEL_PC3        
*\*\             - PGA4_CTRL_VPSEL_PA4        
*\*\             - PGA4_CTRL_VPSEL_PC5        
*\*\             - PGA4_CTRL_VPSEL_PB11       
*\*\             - PGA4_CTRL_VPSEL_PB12       
*\*\             - PGA4_CTRL_VPSEL_PB13       
*\*\             - PGA4_CTRL_VPSEL_PD9        
*\*\             - PGA4_CTRL_VPSEL_PD11       
*\*\             - PGA4_CTRL_VPSEL_DAC1_IOUT  
*\*\             - PGA4_CTRL_VPSEL_DAC5_IOUT
*\*\          - Vmssel
*\*\             PGA1 VMSSEL
*\*\             - PGA1_CTRL_VMSSEL_PF8
*\*\             - PGA1_CTRL_VMSSEL_PF10       
*\*\             - PGA1_CTRL_VMSSEL_PC3        
*\*\             - PGA1_CTRL_VMSSEL_PA2        
*\*\             - PGA1_CTRL_VMSSEL_PA3        
*\*\             - PGA1_CTRL_VMSSEL_PA5        
*\*\             - PGA1_CTRL_VMSSEL_PC5        
*\*\             - PGA1_CTRL_VMSSEL_DAC2_IOUT  
*\*\             - PGA1_CTRL_VMSSEL_DAC6_IOUT  
*\*\             PGA2 VMSSEL
*\*\             - PGA2_CTRL_VMSSEL_PB0        
*\*\             - PGA2_CTRL_VMSSEL_PF9        
*\*\             - PGA2_CTRL_VMSSEL_PF10       
*\*\             - PGA2_CTRL_VMSSEL_PA2        
*\*\             - PGA2_CTRL_VMSSEL_PA3        
*\*\             - PGA2_CTRL_VMSSEL_PA5        
*\*\             - PGA2_CTRL_VMSSEL_PC5        
*\*\             - PGA2_CTRL_VMSSEL_PB15       
*\*\             - PGA2_CTRL_VMSSEL_DAC2_IOUT  
*\*\             - PGA2_CTRL_VMSSEL_DAC6_IOUT  
*\*\             PGA3 VMSSEL
*\*\             - PGA3_CTRL_VMSSEL_PF10       
*\*\             - PGA3_CTRL_VMSSEL_PC1        
*\*\             - PGA3_CTRL_VMSSEL_PA2        
*\*\             - PGA3_CTRL_VMSSEL_PA5        
*\*\             - PGA3_CTRL_VMSSEL_PC4        
*\*\             - PGA3_CTRL_VMSSEL_PB2        
*\*\             - PGA3_CTRL_VMSSEL_PB10       
*\*\             - PGA3_CTRL_VMSSEL_DAC2_IOUT  
*\*\             - PGA3_CTRL_VMSSEL_DAC6_IOUT  
*\*\             PGA4 VMSSEL
*\*\             - PGA4_CTRL_VMSSEL_PF10       
*\*\             - PGA4_CTRL_VMSSEL_PA1        
*\*\             - PGA4_CTRL_VMSSEL_PB1        
*\*\             - PGA4_CTRL_VMSSEL_PB10       
*\*\             - PGA4_CTRL_VMSSEL_PD8        
*\*\             - PGA4_CTRL_VMSSEL_PC9        
*\*\             - PGA4_CTRL_VMSSEL_DAC2_IOUT  
*\*\             - PGA4_CTRL_VMSSEL_DAC6_IOUT
*\*\          - Vpssel
*\*\             PGA1 VPSSEL
*\*\             - PGA1_CTRL_VPSSEL_PF7        
*\*\             - PGA1_CTRL_VPSSEL_PC2        
*\*\             - PGA1_CTRL_VPSSEL_PA1        
*\*\             - PGA1_CTRL_VPSSEL_PA3        
*\*\             - PGA1_CTRL_VPSSEL_PA5        
*\*\             - PGA1_CTRL_VPSSEL_PA7        
*\*\             - PGA1_CTRL_VPSSEL_PB1        
*\*\             - PGA1_CTRL_VPSSEL_DAC1_IOUT  
*\*\             - PGA1_CTRL_VPSSEL_DAC5_IOUT  
*\*\             PGA2 VPSSEL
*\*\             - PGA2_CTRL_VPSSEL_PF7        
*\*\             - PGA2_CTRL_VPSSEL_PC3        
*\*\             - PGA2_CTRL_VPSSEL_PA1        
*\*\             - PGA2_CTRL_VPSSEL_PA2        
*\*\             - PGA2_CTRL_VPSSEL_PA4        
*\*\             - PGA2_CTRL_VPSSEL_PA7        
*\*\             - PGA2_CTRL_VPSSEL_PB0        
*\*\             - PGA2_CTRL_VPSSEL_PE8        
*\*\             - PGA2_CTRL_VPSSEL_PB14       
*\*\             - PGA2_CTRL_VPSSEL_PD12       
*\*\             - PGA2_CTRL_VPSSEL_PD14       
*\*\             - PGA2_CTRL_VPSSEL_DAC1_IOUT  
*\*\             - PGA2_CTRL_VPSSEL_DAC5_IOUT  
*\*\             PGA3 VPSSEL
*\*\             - PGA3_CTRL_VPSSEL_PF7        
*\*\             - PGA3_CTRL_VPSSEL_PC0        
*\*\             - PGA3_CTRL_VPSSEL_PC3        
*\*\             - PGA3_CTRL_VPSSEL_PA1        
*\*\             - PGA3_CTRL_VPSSEL_PA5        
*\*\             - PGA3_CTRL_VPSSEL_PA6        
*\*\             - PGA3_CTRL_VPSSEL_PB0        
*\*\             - PGA3_CTRL_VPSSEL_PB13       
*\*\             - PGA3_CTRL_VPSSEL_PC9        
*\*\             - PGA3_CTRL_VPSSEL_DAC1_IOUT  
*\*\             - PGA3_CTRL_VPSSEL_DAC5_IOUT  
*\*\             PGA4 VPSSEL
*\*\             - PGA4_CTRL_VPSSEL_PC3        
*\*\             - PGA4_CTRL_VPSSEL_PA4        
*\*\             - PGA4_CTRL_VPSSEL_PC5        
*\*\             - PGA4_CTRL_VPSSEL_PB11       
*\*\             - PGA4_CTRL_VPSSEL_PB12       
*\*\             - PGA4_CTRL_VPSSEL_PB13       
*\*\             - PGA4_CTRL_VPSSEL_PD9        
*\*\             - PGA4_CTRL_VPSSEL_PD11       
*\*\             - PGA4_CTRL_VPSSEL_DAC1_IOUT  
*\*\             - PGA4_CTRL_VPSSEL_DAC5_IOUT
*\*\          - Gain1
*\*\             - PGA_CTRL_CH1GAIN_1_DIFF_2
*\*\             - PGA_CTRL_CH1GAIN_2_DIFF_4 
*\*\             - PGA_CTRL_CH1GAIN_4_DIFF_8
*\*\             - PGA_CTRL_CH1GAIN_8_DIFF_16
*\*\             - PGA_CTRL_CH1GAIN_12_DIFF_24 
*\*\             - PGA_CTRL_CH1GAIN_16_DIFF_32
*\*\             - PGA_CTRL_CH1GAIN_24_DIFF_48 
*\*\             - PGA_CTRL_CH1GAIN_32_DIFF_64
*\*\          - Gain2
*\*\             - PGA_CTRL_CH2GAIN_1_DIFF_2   
*\*\             - PGA_CTRL_CH2GAIN_2_DIFF_4   
*\*\             - PGA_CTRL_CH2GAIN_4_DIFF_8   
*\*\             - PGA_CTRL_CH2GAIN_8_DIFF_16  
*\*\             - PGA_CTRL_CH2GAIN_12_DIFF_24
*\*\             - PGA_CTRL_CH2GAIN_16_DIFF_32
*\*\             - PGA_CTRL_CH2GAIN_24_DIFF_48
*\*\             - PGA_CTRL_CH2GAIN_32_DIFF_64
*\*\          - TimeAutoMuxEn
*\*\             - ENABLE
*\*\             - DISABLE
*\*\          - DiffModeEn
*\*\             - ENABLE
*\*\             - DISABLE
*\*\          - En2
*\*\             - ENABLE
*\*\             - DISABLE
*\*\          - En1
*\*\             - ENABLE
*\*\             - DISABLE
*\*\return  none
**/
void PGA_Init(PGAX PGAx, PGA_InitType* PGA_InitStruct)
{
    PGA_SingleType* pCs = &PGA->Pga[PGAx];
    __IO uint32_t temp  = pCs->CTRL;
    
    /*enable bias current source */
    PGA->IBIASEN |= PGA_IBIAS_EN_MASK;

    temp &= (~(PGA_CTRL_CH1EN_MASK   | PGA_CTRL_CH2EN_MASK | PGA_CTRL_DIFFEN_MASK | PGA_CTRL_TCMEN_MASK | \
               PGA_CTRL_CH1GAIN_MASK | PGA_CTRL_CH2GAIN_MASK | PGA_CTRL_VPSEL_MASK | PGA_CTRL_VMSEL_MASK | \
               PGA_CTRL_VPSSEL_MASK | PGA_CTRL_VMSSEL_MASK ));
    temp |= ((uint32_t)PGA_InitStruct->Gain1 | (uint32_t)PGA_InitStruct->Gain2 | (uint32_t)PGA_InitStruct->Vmsel | \
             (uint32_t)PGA_InitStruct->Vpsel | (uint32_t)PGA_InitStruct->Vmssel | (uint32_t)PGA_InitStruct->Vpssel );

    if(PGA_InitStruct->TimeAutoMuxEn == ENABLE)
    {
        temp |= PGA_CTRL_TCMEN_MASK;
    }
    else
    {
        temp &= (~PGA_CTRL_TCMEN_MASK);
    }

    if(PGA_InitStruct->DiffModeEn  != DISABLE)
    {
        temp |= PGA_CTRL_DIFFEN_MASK;
    }
    else
    {
        temp &= (~PGA_CTRL_DIFFEN_MASK);
    }
    
    if(PGA_InitStruct->En1  != DISABLE)
    {
        temp |= PGA_CTRL_CH1EN_MASK;
    }
    else
    {
        temp &= (~PGA_CTRL_CH1EN_MASK);
    }

    if(PGA_InitStruct->En2 != DISABLE)
    {
        temp |= PGA_CTRL_CH2EN_MASK;
    }
    else
    {
        temp &= (~PGA_CTRL_CH2EN_MASK);
    }
    
    pCs->CTRL = temp;
}

/**
*\*\name    PGA_Enable.
*\*\fun     Configures PGAx channel 1 or 2 enable or disable.
*\*\param   PGAx :
*\*\          - PGA1
*\*\          - PGA2
*\*\          - PGA3
*\*\          - PGA4
*\*\param   ch :
*\*\          - PGA_Channel1
*\*\          - PGA_Channel2
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void PGA_Enable(PGAX PGAx, PGA_CHANNEL ch, FunctionalState Cmd)
{
    PGA_SingleType* pCs = &PGA->Pga[PGAx];
    if (Cmd != DISABLE)
    {
        pCs->CTRL |= (PGA_CTRL_CH1EN_MASK << ch);
    }
    else
    {
        pCs->CTRL &= (~(PGA_CTRL_CH1EN_MASK << ch));
    }
}
/**
*\*\name    PGA_SetPgaGain.
*\*\fun     Configures PGAx channel 1 or 2 gain factor.
*\*\param   PGAx :
*\*\          - PGA1
*\*\          - PGA2
*\*\          - PGA3
*\*\          - PGA4
*\*\param   Gain1 :
*\*\          - PGA_CTRL_CH1GAIN_1_DIFF_2
*\*\          - PGA_CTRL_CH1GAIN_2_DIFF_4 
*\*\          - PGA_CTRL_CH1GAIN_4_DIFF_8
*\*\          - PGA_CTRL_CH1GAIN_8_DIFF_16
*\*\          - PGA_CTRL_CH1GAIN_12_DIFF_24 
*\*\          - PGA_CTRL_CH1GAIN_16_DIFF_32
*\*\          - PGA_CTRL_CH1GAIN_24_DIFF_48 
*\*\          - PGA_CTRL_CH1GAIN_32_DIFF_64
*\*\param   Gain2 :
*\*\          - PGA_CTRL_CH2GAIN_1_DIFF_2   
*\*\          - PGA_CTRL_CH2GAIN_2_DIFF_4   
*\*\          - PGA_CTRL_CH2GAIN_4_DIFF_8   
*\*\          - PGA_CTRL_CH2GAIN_8_DIFF_16  
*\*\          - PGA_CTRL_CH2GAIN_12_DIFF_24
*\*\          - PGA_CTRL_CH2GAIN_16_DIFF_32
*\*\          - PGA_CTRL_CH2GAIN_24_DIFF_48
*\*\          - PGA_CTRL_CH2GAIN_32_DIFF_64
*\*\return  none
**/
void PGA_SetPgaGain(PGAX PGAx, PGA_CTRL_CH1GAIN Gain1, PGA_CTRL_CH2GAIN Gain2)
{
    PGA_SingleType* pCs = &PGA->Pga[PGAx];
    __IO uint32_t temp  = pCs->CTRL;

    temp &= (~(PGA_CTRL_CH1GAIN_MASK | PGA_CTRL_CH2GAIN_MASK));
    temp |= ((uint32_t)Gain1 | (uint32_t)Gain2);
    pCs->CTRL = temp;
}

/**
*\*\name    PGA_SetVpSel.
*\*\fun     Configures PGAx  Non-inverted input selection.
*\*\param   PGAx :
*\*\          - PGA1
*\*\          - PGA2
*\*\          - PGA3
*\*\          - PGA4
*\*\param   VpSel :
*\*\         PGA1 VPSEL
*\*\          - PGA1_CTRL_VPSEL_PF7 
*\*\          - PGA1_CTRL_VPSEL_PC2        
*\*\          - PGA1_CTRL_VPSEL_PA1        
*\*\          - PGA1_CTRL_VPSEL_PA3        
*\*\          - PGA1_CTRL_VPSEL_PA5        
*\*\          - PGA1_CTRL_VPSEL_PA7        
*\*\          - PGA1_CTRL_VPSEL_PB1        
*\*\          - PGA1_CTRL_VPSEL_DAC1_IOUT  
*\*\          - PGA1_CTRL_VPSEL_DAC5_IOUT  
*\*\         PGA2 VPSEL
*\*\          - PGA2_CTRL_VPSEL_PF7        
*\*\          - PGA2_CTRL_VPSEL_PC3        
*\*\          - PGA2_CTRL_VPSEL_PA1        
*\*\          - PGA2_CTRL_VPSEL_PA2        
*\*\          - PGA2_CTRL_VPSEL_PA4        
*\*\          - PGA2_CTRL_VPSEL_PA7        
*\*\          - PGA2_CTRL_VPSEL_PB0        
*\*\          - PGA2_CTRL_VPSEL_PE8        
*\*\          - PGA2_CTRL_VPSEL_PB14       
*\*\          - PGA2_CTRL_VPSEL_PD12       
*\*\          - PGA2_CTRL_VPSEL_PD14       
*\*\          - PGA2_CTRL_VPSEL_DAC1_IOUT  
*\*\          - PGA2_CTRL_VPSEL_DAC5_IOUT  
*\*\         PGA3 VPSEL
*\*\          - PGA3_CTRL_VPSEL_PF7        
*\*\          - PGA3_CTRL_VPSEL_PC0        
*\*\          - PGA3_CTRL_VPSEL_PC3        
*\*\          - PGA3_CTRL_VPSEL_PA1        
*\*\          - PGA3_CTRL_VPSEL_PA5        
*\*\          - PGA3_CTRL_VPSEL_PA6        
*\*\          - PGA3_CTRL_VPSEL_PB0        
*\*\          - PGA3_CTRL_VPSEL_PB13       
*\*\          - PGA3_CTRL_VPSEL_PC9        
*\*\          - PGA3_CTRL_VPSEL_DAC1_IOUT  
*\*\          - PGA3_CTRL_VPSEL_DAC5_IOUT  
*\*\         PGA4 VPSEL
*\*\          - PGA4_CTRL_VPSEL_PC3        
*\*\          - PGA4_CTRL_VPSEL_PA4        
*\*\          - PGA4_CTRL_VPSEL_PC5        
*\*\          - PGA4_CTRL_VPSEL_PB11       
*\*\          - PGA4_CTRL_VPSEL_PB12       
*\*\          - PGA4_CTRL_VPSEL_PB13       
*\*\          - PGA4_CTRL_VPSEL_PD9        
*\*\          - PGA4_CTRL_VPSEL_PD11       
*\*\          - PGA4_CTRL_VPSEL_DAC1_IOUT  
*\*\          - PGA4_CTRL_VPSEL_DAC5_IOUT
*\*\return  none
**/
void PGA_SetVpSel(PGAX PGAx, PGA_CTRL_VPSEL VpSel)
{
    PGA_SingleType* pCs = &PGA->Pga[PGAx];
    __IO uint32_t temp  = pCs->CTRL;

    temp &= (~PGA_CTRL_VPSEL_MASK);
    temp |= (uint32_t)VpSel;
    pCs->CTRL = temp;
}
/**
*\*\name    PGA_SetVmSel.
*\*\fun     Configures PGAx Inverted input selection.
*\*\param   PGAx :
*\*\          - PGA1
*\*\          - PGA2
*\*\          - PGA3
*\*\          - PGA4
*\*\param   VmSel :
*\*\         PGA1 VPSEL
*\*\          - PGA1_CTRL_VMSEL_PF8
*\*\          - PGA1_CTRL_VMSEL_PF10       
*\*\          - PGA1_CTRL_VMSEL_PC3        
*\*\          - PGA1_CTRL_VMSEL_PA2        
*\*\          - PGA1_CTRL_VMSEL_PA3        
*\*\          - PGA1_CTRL_VMSEL_PA5        
*\*\          - PGA1_CTRL_VMSEL_PC5        
*\*\          - PGA1_CTRL_VMSEL_DAC2_IOUT  
*\*\          - PGA1_CTRL_VMSEL_DAC6_IOUT  
*\*\         PGA2 VMSEL
*\*\          - PGA2_CTRL_VMSEL_PB0        
*\*\          - PGA2_CTRL_VMSEL_PF9        
*\*\          - PGA2_CTRL_VMSEL_PF10       
*\*\          - PGA2_CTRL_VMSEL_PA2        
*\*\          - PGA2_CTRL_VMSEL_PA3        
*\*\          - PGA2_CTRL_VMSEL_PA5        
*\*\          - PGA2_CTRL_VMSEL_PC5        
*\*\          - PGA2_CTRL_VMSEL_PB15       
*\*\          - PGA2_CTRL_VMSEL_DAC2_IOUT  
*\*\          - PGA2_CTRL_VMSEL_DAC6_IOUT  
*\*\         PGA3 VMSEL
*\*\          - PGA3_CTRL_VMSEL_PF10       
*\*\          - PGA3_CTRL_VMSEL_PC1        
*\*\          - PGA3_CTRL_VMSEL_PA2        
*\*\          - PGA3_CTRL_VMSEL_PA5        
*\*\          - PGA3_CTRL_VMSEL_PC4        
*\*\          - PGA3_CTRL_VMSEL_PB2        
*\*\          - PGA3_CTRL_VMSEL_PB10       
*\*\          - PGA3_CTRL_VMSEL_DAC2_IOUT  
*\*\          - PGA3_CTRL_VMSEL_DAC6_IOUT  
*\*\         PGA4 VMSEL
*\*\          - PGA4_CTRL_VMSEL_PF10       
*\*\          - PGA4_CTRL_VMSEL_PA1        
*\*\          - PGA4_CTRL_VMSEL_PB1        
*\*\          - PGA4_CTRL_VMSEL_PB10       
*\*\          - PGA4_CTRL_VMSEL_PD8        
*\*\          - PGA4_CTRL_VMSEL_PC9        
*\*\          - PGA4_CTRL_VMSEL_DAC2_IOUT  
*\*\          - PGA4_CTRL_VMSEL_DAC6_IOUT
*\*\return  none
**/
void PGA_SetVmSel(PGAX PGAx, PGA_CTRL_VMSEL VmSel)
{
    PGA_SingleType* pCs = &PGA->Pga[PGAx];
    __IO uint32_t temp  = pCs->CTRL;

    temp &= (~PGA_CTRL_VMSEL_MASK);
    temp |= (uint32_t)VmSel;
    pCs->CTRL = temp;
}
/**
*\*\name    PGA_SetVpSecondSel.
*\*\fun     Configures PGAx None-inverted secondary input selection.
*\*\param   PGAx :
*\*\          - PGA1
*\*\          - PGA2
*\*\          - PGA3
*\*\          - PGA4
*\*\param   VpSSel :
*\*\         PGA1 VPSSEL
*\*\          - PGA1_CTRL_VPSSEL_PF7
*\*\          - PGA1_CTRL_VPSSEL_PC2        
*\*\          - PGA1_CTRL_VPSSEL_PA1        
*\*\          - PGA1_CTRL_VPSSEL_PA3        
*\*\          - PGA1_CTRL_VPSSEL_PA5        
*\*\          - PGA1_CTRL_VPSSEL_PA7        
*\*\          - PGA1_CTRL_VPSSEL_PB1        
*\*\          - PGA1_CTRL_VPSSEL_DAC1_IOUT  
*\*\          - PGA1_CTRL_VPSSEL_DAC5_IOUT  
*\*\         PGA2 VPSSEL
*\*\          - PGA2_CTRL_VPSSEL_PF7        
*\*\          - PGA2_CTRL_VPSSEL_PC3        
*\*\          - PGA2_CTRL_VPSSEL_PA1        
*\*\          - PGA2_CTRL_VPSSEL_PA2        
*\*\          - PGA2_CTRL_VPSSEL_PA4        
*\*\          - PGA2_CTRL_VPSSEL_PA7        
*\*\          - PGA2_CTRL_VPSSEL_PB0        
*\*\          - PGA2_CTRL_VPSSEL_PE8        
*\*\          - PGA2_CTRL_VPSSEL_PB14       
*\*\          - PGA2_CTRL_VPSSEL_PD12       
*\*\          - PGA2_CTRL_VPSSEL_PD14       
*\*\          - PGA2_CTRL_VPSSEL_DAC1_IOUT  
*\*\          - PGA2_CTRL_VPSSEL_DAC5_IOUT  
*\*\         PGA3 VPSSEL
*\*\          - PGA3_CTRL_VPSSEL_PF7        
*\*\          - PGA3_CTRL_VPSSEL_PC0        
*\*\          - PGA3_CTRL_VPSSEL_PC3        
*\*\          - PGA3_CTRL_VPSSEL_PA1        
*\*\          - PGA3_CTRL_VPSSEL_PA5        
*\*\          - PGA3_CTRL_VPSSEL_PA6        
*\*\          - PGA3_CTRL_VPSSEL_PB0        
*\*\          - PGA3_CTRL_VPSSEL_PB13       
*\*\          - PGA3_CTRL_VPSSEL_PC9        
*\*\          - PGA3_CTRL_VPSSEL_DAC1_IOUT  
*\*\          - PGA3_CTRL_VPSSEL_DAC5_IOUT  
*\*\         PGA4 VPSSEL
*\*\          - PGA4_CTRL_VPSSEL_PC3        
*\*\          - PGA4_CTRL_VPSSEL_PA4        
*\*\          - PGA4_CTRL_VPSSEL_PC5        
*\*\          - PGA4_CTRL_VPSSEL_PB11       
*\*\          - PGA4_CTRL_VPSSEL_PB12       
*\*\          - PGA4_CTRL_VPSSEL_PB13       
*\*\          - PGA4_CTRL_VPSSEL_PD9        
*\*\          - PGA4_CTRL_VPSSEL_PD11       
*\*\          - PGA4_CTRL_VPSSEL_DAC1_IOUT  
*\*\          - PGA4_CTRL_VPSSEL_DAC5_IOUT
*\*\return  none
**/
void PGA_SetVpSecondSel(PGAX PGAx, PGA_CTRL_VPSSEL VpSSel)
{
    PGA_SingleType* pCs = &PGA->Pga[PGAx];
    __IO uint32_t temp  = pCs->CTRL;

    temp &= (~PGA_CTRL_VPSSEL_MASK);
    temp |= (uint32_t)VpSSel;
    pCs->CTRL = temp;
}
/**
*\*\name    PGA_SetVmSecondSel.
*\*\fun     Configures PGAx Inverted secondary input selection.
*\*\param   PGAx :
*\*\          - PGA1
*\*\          - PGA2
*\*\          - PGA3
*\*\          - PGA4
*\*\param   VmSSel :
*\*\         PGA1 VMSSEL
*\*\          - PGA1_CTRL_VMSSEL_PF8
*\*\          - PGA1_CTRL_VMSSEL_PF10       
*\*\          - PGA1_CTRL_VMSSEL_PC3        
*\*\          - PGA1_CTRL_VMSSEL_PA2        
*\*\          - PGA1_CTRL_VMSSEL_PA3        
*\*\          - PGA1_CTRL_VMSSEL_PA5        
*\*\          - PGA1_CTRL_VMSSEL_PC5        
*\*\          - PGA1_CTRL_VMSSEL_DAC2_IOUT  
*\*\          - PGA1_CTRL_VMSSEL_DAC6_IOUT  
*\*\         PGA2 VMSSEL
*\*\          - PGA2_CTRL_VMSSEL_PB0        
*\*\          - PGA2_CTRL_VMSSEL_PF9        
*\*\          - PGA2_CTRL_VMSSEL_PF10       
*\*\          - PGA2_CTRL_VMSSEL_PA2        
*\*\          - PGA2_CTRL_VMSSEL_PA3        
*\*\          - PGA2_CTRL_VMSSEL_PA5        
*\*\          - PGA2_CTRL_VMSSEL_PC5        
*\*\          - PGA2_CTRL_VMSSEL_PB15       
*\*\          - PGA2_CTRL_VMSSEL_DAC2_IOUT  
*\*\          - PGA2_CTRL_VMSSEL_DAC6_IOUT  
*\*\         PGA3 VMSSEL
*\*\          - PGA3_CTRL_VMSSEL_PF10       
*\*\          - PGA3_CTRL_VMSSEL_PC1        
*\*\          - PGA3_CTRL_VMSSEL_PA2        
*\*\          - PGA3_CTRL_VMSSEL_PA5        
*\*\          - PGA3_CTRL_VMSSEL_PC4        
*\*\          - PGA3_CTRL_VMSSEL_PB2        
*\*\          - PGA3_CTRL_VMSSEL_PB10       
*\*\          - PGA3_CTRL_VMSSEL_DAC2_IOUT  
*\*\          - PGA3_CTRL_VMSSEL_DAC6_IOUT  
*\*\         PGA4 VMSSEL
*\*\          - PGA4_CTRL_VMSSEL_PF10       
*\*\          - PGA4_CTRL_VMSSEL_PA1        
*\*\          - PGA4_CTRL_VMSSEL_PB1        
*\*\          - PGA4_CTRL_VMSSEL_PB10       
*\*\          - PGA4_CTRL_VMSSEL_PD8        
*\*\          - PGA4_CTRL_VMSSEL_PC9        
*\*\          - PGA4_CTRL_VMSSEL_DAC2_IOUT  
*\*\          - PGA4_CTRL_VMSSEL_DAC6_IOUT
*\*\return  none
**/
void PGA_SetVmSecondSel(PGAX PGAx, PGA_CTRL_VMSSEL VmSSel)
{
    PGA_SingleType* pCs = &PGA->Pga[PGAx];
    __IO uint32_t temp  = pCs->CTRL;

    temp &= (~PGA_CTRL_VMSSEL_MASK);
    temp |= (uint32_t)VmSSel;
    pCs->CTRL = temp;
}
/**
*\*\name    PGA_DiffModeEnable.
*\*\fun     Configures PGAx differential mode enable or disable.
*\*\param   PGAx :
*\*\          - PGA1
*\*\          - PGA2
*\*\          - PGA3
*\*\          - PGA4
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void PGA_DiffModeEnable(PGAX PGAx, FunctionalState Cmd)
{
    PGA_SingleType* pCs = &PGA->Pga[PGAx];
    if(Cmd != DISABLE)
    {
        pCs->CTRL |= PGA_CTRL_DIFFEN_MASK;
    }
    else
    {
        pCs->CTRL &= (~PGA_CTRL_DIFFEN_MASK);
    }
}

/**
*\*\name    PGA_TimControlMuxEnable.
*\*\fun     Configures PGAx Timer controlled mux mode enable or disable.
*\*\param   PGAx :
*\*\          - PGA1
*\*\          - PGA2
*\*\          - PGA3
*\*\          - PGA4
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void PGA_TimControlMuxEnable(PGAX PGAx, FunctionalState Cmd)
{
    PGA_SingleType* pCs = &PGA->Pga[PGAx];
    if(Cmd != DISABLE)
    {
        pCs->CTRL |= PGA_CTRL_TCMEN_MASK;
    }
    else
    {
        pCs->CTRL &= (~PGA_CTRL_TCMEN_MASK);
    }
}

/**
*\*\name    PGA_TrimEnable.
*\*\fun     Configures PGAx trim enable or disable.
*\*\param   PGAx :
*\*\          - PGA1
*\*\          - PGA2
*\*\          - PGA3
*\*\          - PGA4
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void PGA_TrimEnable(PGAX PGAx, FunctionalState Cmd)
{
    PGA_SingleType* pCs = &PGA->Pga[PGAx];
    if(Cmd != DISABLE)
    {
        pCs->CTRL |= PGA_CTRL_TRIMEN_MASK;
    }
    else
    {
        pCs->CTRL &= (~PGA_CTRL_TRIMEN_MASK);
    }
}


/**
*\*\name    PGA_TrimStatusGet.
*\*\fun     Get PGAx triming status.
*\*\param   COMPx :
*\*\          - PGA1
*\*\          - PGA2
*\*\          - PGA3
*\*\          - PGA4
*\*\param   ch :
*\*\          - PGA_Channel1
*\*\          - PGA_Channel2
*\*\return  FlagStatus:
*\*\          - SET   : triming complete
*\*\          - RESET : triming conplete
**/
FlagStatus PGA_TrimStatusGet(PGAX PGAx, PGA_CHANNEL ch)
{
    FlagStatus flag;
    PGA_SingleType* pCs = &PGA->Pga[PGAx];

    if(ch == PGA_Channel1)
    {
        flag = ((pCs->TRIM & PGA_TRIM_TRIMCH1FLAG_MASK) != 0U)? SET : RESET;
    }
    else
    {
        flag = ((pCs->TRIM & PGA_TRIM_TRIMCH2FLAG_MASK) != 0U)? SET : RESET;
    }
    return flag;
}

/**
*\*\name    PGA_TrimValueSet.
*\*\fun     Configures PGAx channel 1 or 2 triming value.
*\*\param   PGAx :
*\*\          - PGA1
*\*\          - PGA2
*\*\          - PGA3
*\*\          - PGA4
*\*\param   ch :
*\*\          - PGA_Channel1
*\*\          - PGA_Channel2
*\*\param   PTrimValue :
*\*\          -  Value can be set from 0 to 63.
*\*\param   NTrimValue :
*\*\          -  Value can be set from 0 to 63.
*\*\return  none
**/
void PGA_TrimValueSet(PGAX PGAx, PGA_CHANNEL ch, uint8_t PTrimValue, uint8_t NTrimValue)
{
    PGA_SingleType* pCs = &PGA->Pga[PGAx];
    __IO uint32_t temp  = pCs->TRIM;

    if(ch == PGA_Channel1)
    {
        temp &= (~(PGA_TRIM_TRIMCH1P_MASK | PGA_TRIM_TRIMCH1N_MASK));
        temp |= ((uint32_t)PTrimValue  | ( ((uint32_t)NTrimValue)<<6) );
    }
    else
    {
        temp &= (~(PGA_TRIM_TRIMCH2P_MASK | PGA_TRIM_TRIMCH2N_MASK));
        temp |= ( ( ((uint32_t)PTrimValue)<< 12)  | ( ((uint32_t)NTrimValue)<< 18) );
    }
    pCs->TRIM = temp;
}

/**
*\*\name    PGA_SetLock.
*\*\fun     Configures which PGAx will be Locked.
*\*\param   Lock :
*\*\          - PGA1_LOCK
*\*\          - PGA2_LOCK
*\*\          - PGA3_LOCK
*\*\          - PGA4_LOCK
*\*\return  none
**/
void PGA_SetLock(uint32_t Lock)
{
   PGA->LOCK |= Lock;
}

/**
*\*\name    PGA_EnableIBIAS.
*\*\fun     Enable or disable bias current source.
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void PGA_EnableIBIAS(FunctionalState Cmd)
{
    if(Cmd != DISABLE)
    {
        PGA->IBIASEN |= PGA_IBIAS_EN_MASK;
    }
    else
    {
        PGA->IBIASEN &= (~PGA_IBIAS_EN_MASK);
    }
}


