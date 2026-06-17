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
 * @file n32h47x_48x_comp.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
 */
#include "n32h47x_48x_comp.h"
#include "n32h47x_48x_rcc.h"

/** COMP Driving Functions Declaration **/ 

/**
*\*\name    COMP_DeInit.
*\*\fun     Reset the COMP registers.
*\*\return  none
**/
void COMP_DeInit(void)
{
    RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_COMP);
}
/**
*\*\name    COMP_StructInit.
*\*\fun     Fills all COMP_initstruct member with default value.
*\*\param   COMP_initstruct :
*\*\          - Blking
*\*\          - Hyst
*\*\          - PolRev
*\*\          - InpSel
*\*\          - InmSel
*\*\          - FilterEn
*\*\          - ClkPsc
*\*\          - SampWindow
*\*\          - Threshold
*\*\          - En
*\*\return  none
**/
void COMP_StructInit(COMP_InitType* COMP_InitStruct)
{
    /* Initialize the Blking */
    COMP_InitStruct->Blking     = COMP_CTRL_BLKING_NO; 
    /* Initialize the Hyst */
    COMP_InitStruct->Hyst       = COMP_CTRL_HYST_NO; 
    /* Initialize the PolRev */
    COMP_InitStruct->PolRev     = DISABLE; 
    /* Initialize the InpSel */ 
    COMP_InitStruct->InpSel     = COMPX_CTRL_INPSEL_RES;
    /* Initialize the InmSel */
    COMP_InitStruct->InmSel     = COMPX_CTRL_INMSEL_RES;
    /* Initialize the FilterEn */
    COMP_InitStruct->FilterEn   = DISABLE;
    /* Initialize the ClkPsc */
    COMP_InitStruct->ClkPsc     = 0;
    /* Initialize the SampWindow */
    COMP_InitStruct->SampWindow = 0;
    /* Initialize the Threshold */
    COMP_InitStruct->Threshold  = 0;
    /* Initialize the En */
    COMP_InitStruct->En         = DISABLE;
}
/**
*\*\name    COMP_Initializes.
*\*\fun     Initializes the COMPx according to COMP_initstruct.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\          - COMP4
*\*\          - COMP5
*\*\          - COMP6
*\*\          - COMP7
*\*\param   COMP_initstruct :
*\*\          - Blking
*\*\            - COMP_CTRL_BLKING_NO
*\*\            - COMP_CTRL_BLKING_ATIM1_OC5
*\*\            - COMP_CTRL_BLKING_ATIM2_OC5
*\*\            - COMP_CTRL_BLKING_ATIM3_OC5
*\*\            - COMP_CTRL_BLKING_GTIM8_OC5
*\*\            - COMP_CTRL_BLKING_GTIM9_OC5
*\*\            - COMP_CTRL_BLKING_GTIM10_OC5
*\*\          - Hyst
*\*\            - COMP_CTRL_HYST_NO   
*\*\            - COMP_CTRL_HYST_10MV:   10mV-level
*\*\            - COMP_CTRL_HYST_20MV:   20mV-level
*\*\            - COMP_CTRL_HYST_30MV:   30mV-level   
*\*\            - COMP_CTRL_HYST_40MV:   40mV-level   
*\*\            - COMP_CTRL_HYST_50MV:   50mV-level   
*\*\            - COMP_CTRL_HYST_60MV:   60mV-level   
*\*\            - COMP_CTRL_HYST_70MV:   70mV-level   
*\*\          - PolRev
*\*\            - ENABLE
*\*\            - DISABLE                        
*\*\          - vpsel
*\*\            comp1 inp sel 
*\*\            - COMP1_CTRL_INPSEL_PF8    
*\*\            - COMP1_CTRL_INPSEL_PC1    
*\*\            - COMP1_CTRL_INPSEL_PA1     
*\*\            - COMP1_CTRL_INPSEL_PB1     
*\*\            - COMP1_CTRL_INPSEL_PA7     
*\*\            - COMP1_CTRL_INPSEL_DAC1_IOUT    
*\*\            - COMP1_CTRL_INPSEL_DAC5_IOUT    
*\*\            - COMP1_CTRL_INPSEL_VREF1   
*\*\            - COMP1_CTRL_INPSEL_PGA1_IOUT_P  
*\*\            - COMP1_CTRL_INPSEL_PB10    
*\*\            comp2 inp sel 
*\*\            - COMP2_CTRL_INPSEL_PB10   
*\*\            - COMP2_CTRL_INPSEL_PB11   
*\*\            - COMP2_CTRL_INPSEL_PF10    
*\*\            - COMP2_CTRL_INPSEL_PC3     
*\*\            - COMP2_CTRL_INPSEL_PA3     
*\*\            - COMP2_CTRL_INPSEL_PA7     
*\*\            - COMP2_CTRL_INPSEL_PB1     
*\*\            - COMP2_CTRL_INPSEL_DAC2_IOUT    
*\*\            - COMP2_CTRL_INPSEL_DAC6_IOUT    
*\*\            - COMP2_CTRL_INPSEL_VREF1   
*\*\            - COMP2_CTRL_INPSEL_PGA1_IOUT_N  
*\*\            comp3 inp sel 
*\*\            - COMP3_CTRL_INPSEL_PH1    
*\*\            - COMP3_CTRL_INPSEL_PD15   
*\*\            - COMP3_CTRL_INPSEL_PC0     
*\*\            - COMP3_CTRL_INPSEL_PC1     
*\*\            - COMP3_CTRL_INPSEL_PB0     
*\*\            - COMP3_CTRL_INPSEL_PB14    
*\*\            - COMP3_CTRL_INPSEL_DAC1_IOUT    
*\*\            - COMP3_CTRL_INPSEL_DAC5_IOUT    
*\*\            - COMP3_CTRL_INPSEL_VREF2   
*\*\            - COMP3_CTRL_INPSEL_PGA2_IOUT_P  
*\*\            - COMP3_CTRL_INPSEL_PA0          
*\*\            comp4 inp sel 
*\*\            - COMP4_CTRL_INPSEL_PA0    
*\*\            - COMP4_CTRL_INPSEL_PB0    
*\*\            - COMP4_CTRL_INPSEL_PE7     
*\*\            - COMP4_CTRL_INPSEL_PB15    
*\*\            - COMP4_CTRL_INPSEL_PC9     
*\*\            - COMP4_CTRL_INPSEL_DAC2_IOUT    
*\*\            - COMP4_CTRL_INPSEL_DAC6_IOUT    
*\*\            - COMP4_CTRL_INPSEL_VREF2   
*\*\            - COMP4_CTRL_INPSEL_PGA2_IOUT_N  
*\*\            comp5 inp sel 
*\*\            - COMP5_CTRL_INPSEL_PC3    
*\*\            - COMP5_CTRL_INPSEL_PA3    
*\*\            - COMP5_CTRL_INPSEL_PC4     
*\*\            - COMP5_CTRL_INPSEL_PB13    
*\*\            - COMP5_CTRL_INPSEL_DAC3_IOUT    
*\*\            - COMP5_CTRL_INPSEL_DAC7_IOUT    
*\*\            - COMP5_CTRL_INPSEL_VREF3   
*\*\            - COMP5_CTRL_INPSEL_PGA3_IOUT_P  
*\*\            - COMP5_CTRL_INPSEL_PD12     
*\*\            comp6 inp sel 
*\*\            - COMP6_CTRL_INPSEL_PD12   
*\*\            - COMP6_CTRL_INPSEL_PD11   
*\*\            - COMP6_CTRL_INPSEL_PD9     
*\*\            - COMP6_CTRL_INPSEL_PC5     
*\*\            - COMP6_CTRL_INPSEL_PB11    
*\*\            - COMP6_CTRL_INPSEL_DAC4_IOUT    
*\*\            - COMP6_CTRL_INPSEL_DAC8_IOUT    
*\*\            - COMP6_CTRL_INPSEL_VREF3   
*\*\            - COMP6_CTRL_INPSEL_PGA3_IOUT_N  
*\*\            comp7 inp sel 
*\*\            - COMP7_CTRL_INPSEL_PB14   
*\*\            - COMP7_CTRL_INPSEL_PC1    
*\*\            - COMP7_CTRL_INPSEL_PD14    
*\*\            - COMP7_CTRL_INPSEL_DAC4_IOUT    
*\*\            - COMP7_CTRL_INPSEL_DAC7_IOUT    
*\*\            - COMP7_CTRL_INPSEL_VREF3   
*\*\            - COMP7_CTRL_INPSEL_PGA4_IOUT_P  
*\*\            - COMP7_CTRL_INPSEL_PGA4_IOUT_N                         
*\*\          - InmSel
*\*\            comp1 inm sel 
*\*\            - COMP1_CTRL_INMSEL_PA0
*\*\            - COMP1_CTRL_INMSEL_PA4
*\*\            - COMP1_CTRL_INMSEL_PA5
*\*\            - COMP1_CTRL_INMSEL_PA6
*\*\            - COMP1_CTRL_INMSEL_DAC1_IOUT    
*\*\            - COMP1_CTRL_INMSEL_DAC5_IOUT    
*\*\            - COMP1_CTRL_INMSEL_VREF1        
*\*\            comp2 inm sel 
*\*\            - COMP2_CTRL_INMSEL_PA2,
*\*\            - COMP2_CTRL_INMSEL_PA4
*\*\            - COMP2_CTRL_INMSEL_PA5
*\*\            - COMP2_CTRL_INMSEL_PB1
*\*\            - COMP2_CTRL_INMSEL_PE8
*\*\            - COMP2_CTRL_INMSEL_DAC2_IOUT    
*\*\            - COMP2_CTRL_INMSEL_DAC6_IOUT    
*\*\            - COMP2_CTRL_INMSEL_VREF1        
*\*\            comp3 inm sel 
*\*\            - COMP3_CTRL_INMSEL_PB14         
*\*\            - COMP3_CTRL_INMSEL_PA4
*\*\            - COMP3_CTRL_INMSEL_PA5
*\*\            - COMP3_CTRL_INMSEL_PC0
*\*\            - COMP3_CTRL_INMSEL_PE7
*\*\            - COMP3_CTRL_INMSEL_PB12
*\*\            - COMP3_CTRL_INMSEL_PD15         
*\*\            - COMP3_CTRL_INMSEL_PH1          
*\*\            - COMP3_CTRL_INMSEL_DAC1_IOUT    
*\*\            - COMP3_CTRL_INMSEL_DAC5_IOUT    
*\*\            - COMP3_CTRL_INMSEL_VREF2
*\*\            comp4 inm sel 
*\*\            - COMP4_CTRL_INMSEL_PB13         
*\*\            - COMP4_CTRL_INMSEL_PA4
*\*\            - COMP4_CTRL_INMSEL_PA5
*\*\            - COMP4_CTRL_INMSEL_PC4
*\*\            - COMP4_CTRL_INMSEL_PB2
*\*\            - COMP4_CTRL_INMSEL_PE8
*\*\            - COMP4_CTRL_INMSEL_DAC2_IOUT    
*\*\            - COMP4_CTRL_INMSEL_DAC6_IOUT    
*\*\            - COMP4_CTRL_INMSEL_VREF2        
*\*\            comp5 inm sel 
*\*\            - COMP5_CTRL_INMSEL_PA4
*\*\            - COMP5_CTRL_INMSEL_PA5
*\*\            - COMP5_CTRL_INMSEL_PB10
*\*\            - COMP5_CTRL_INMSEL_PD10
*\*\            - COMP5_CTRL_INMSEL_PD13
*\*\            - COMP5_CTRL_INMSEL_DAC3_IOUT    
*\*\            - COMP5_CTRL_INMSEL_DAC7_IOUT    
*\*\            - COMP5_CTRL_INMSEL_VREF3        
*\*\            comp6 inm sel 
*\*\            - COMP6_CTRL_INMSEL_PA7,
*\*\            - COMP6_CTRL_INMSEL_PA4
*\*\            - COMP6_CTRL_INMSEL_PA5
*\*\            - COMP6_CTRL_INMSEL_PB15
*\*\            - COMP6_CTRL_INMSEL_PD8
*\*\            - COMP6_CTRL_INMSEL_PD10
*\*\            - COMP6_CTRL_INMSEL_DAC4_IOUT    
*\*\            - COMP6_CTRL_INMSEL_DAC8_IOUT    
*\*\            - COMP6_CTRL_INMSEL_VREF3        
*\*\            comp7 inm sel 
*\*\            - COMP7_CTRL_INMSEL_PB12         
*\*\            - COMP7_CTRL_INMSEL_PA4
*\*\            - COMP7_CTRL_INMSEL_PA5
*\*\            - COMP7_CTRL_INMSEL_PC0
*\*\            - COMP7_CTRL_INMSEL_PD15
*\*\            - COMP7_CTRL_INMSEL_DAC4_IOUT    
*\*\            - COMP7_CTRL_INMSEL_DAC7_IOUT    
*\*\            - COMP7_CTRL_INMSEL_VREF3                                         
*\*\          - En
*\*\            - ENABLE
*\*\            - DISABLE
*\*\          - SampWindow
*\*\            - SampWindow Value ranges from 0~31. 
*\*\          - Threshold
*\*\            - Threshold Value need > SampWindow/2.
*\*\          - FilterEn
*\*\            - ENABLE
*\*\            - DISABLE
*\*\          - ClkPsc
*\*\            - ClkPsc Value ranges from 0~65535. 
*\*\return  none
**/
void COMP_Init(COMPX COMPx, COMP_InitType* COMP_InitStruct)
{
    COMP_SingleType* pCS = &COMP->Cmp[COMPx];
    __IO uint32_t temp = 0;

    // filter register 
    temp = pCS->FILC;

    temp  = ( ((uint32_t)COMP_InitStruct->SampWindow) << 6 ) & COMP_FILC_SAMPW_MASK;
    temp += ( ((uint32_t)COMP_InitStruct->Threshold)  << 1 ) & COMP_FILC_THRESH_MASK;
    temp += ( (uint32_t)COMP_InitStruct->FilterEn )& COMP_FILC_FILEN_MASK;

    pCS->FILC = temp;
    // filter psc
    pCS->FILP = COMP_InitStruct->ClkPsc;

    // ctrl
    temp = pCS->CTRL;
    /* Clear Bit Mask */
    temp &= (~(COMP_CTRL_BLKING_MASK | COMP_CTRL_HYST_MASK | COMP_POL_MASK | COMP_CTRL_INPSEL_MASK | COMP_CTRL_INMSEL_MASK | COMP_CTRL_EN_MASK));
    temp |= ((uint32_t)COMP_InitStruct->Blking | (uint32_t)COMP_InitStruct->Hyst | \
             (uint32_t)COMP_InitStruct->InpSel | (uint32_t)COMP_InitStruct->InmSel);
             
    if(COMP_InitStruct->PolRev != DISABLE)
    {
        temp |= COMP_OUTPOL_FLIP ;
    }
    else
    {
        temp &= (~COMP_OUTPOL_FLIP);
    }

    if(COMP_InitStruct->En != DISABLE)
    {
        temp |= COMP_CTRL_EN_MASK ;
    }
    else
    {
        temp &= (~COMP_CTRL_EN_MASK);
    }

    pCS->CTRL = temp;
}
/**
*\*\name    COMP_Enable.
*\*\fun     Configures COMPx enable or disable.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\          - COMP4
*\*\          - COMP5
*\*\          - COMP6
*\*\          - COMP7
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void COMP_Enable(COMPX COMPx, FunctionalState Cmd)
{
    if(Cmd != DISABLE)
    {
        COMP->Cmp[COMPx].CTRL |= COMP_CTRL_EN_MASK;
    }
    else
    {
        COMP->Cmp[COMPx].CTRL &= (~COMP_CTRL_EN_MASK);
    }
}
/**
*\*\name    COMP_SetInpSel.
*\*\fun     Select COMPx Non-inverting input.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\          - COMP4
*\*\          - COMP5
*\*\          - COMP6
*\*\          - COMP7
*\*\param   vpsel :
*\*\         comp1 inp sel 
*\*\            - COMP1_CTRL_INPSEL_PF8    
*\*\            - COMP1_CTRL_INPSEL_PC1    
*\*\            - COMP1_CTRL_INPSEL_PA1     
*\*\            - COMP1_CTRL_INPSEL_PB1     
*\*\            - COMP1_CTRL_INPSEL_PA7     
*\*\            - COMP1_CTRL_INPSEL_DAC1_IOUT    
*\*\            - COMP1_CTRL_INPSEL_DAC5_IOUT    
*\*\            - COMP1_CTRL_INPSEL_VREF1   
*\*\            - COMP1_CTRL_INPSEL_PGA1_IOUT_P  
*\*\            - COMP1_CTRL_INPSEL_PB10    
*\*\         comp2 inp sel 
*\*\            - COMP2_CTRL_INPSEL_PB10   
*\*\            - COMP2_CTRL_INPSEL_PB11   
*\*\            - COMP2_CTRL_INPSEL_PF10    
*\*\            - COMP2_CTRL_INPSEL_PC3     
*\*\            - COMP2_CTRL_INPSEL_PA3     
*\*\            - COMP2_CTRL_INPSEL_PA7     
*\*\            - COMP2_CTRL_INPSEL_PB1     
*\*\            - COMP2_CTRL_INPSEL_DAC2_IOUT    
*\*\            - COMP2_CTRL_INPSEL_DAC6_IOUT    
*\*\            - COMP2_CTRL_INPSEL_VREF1   
*\*\            - COMP2_CTRL_INPSEL_PGA1_IOUT_N  
*\*\         comp3 inp sel 
*\*\            - COMP3_CTRL_INPSEL_PH1    
*\*\            - COMP3_CTRL_INPSEL_PD15   
*\*\            - COMP3_CTRL_INPSEL_PC0     
*\*\            - COMP3_CTRL_INPSEL_PC1     
*\*\            - COMP3_CTRL_INPSEL_PB0     
*\*\            - COMP3_CTRL_INPSEL_PB14    
*\*\            - COMP3_CTRL_INPSEL_DAC1_IOUT    
*\*\            - COMP3_CTRL_INPSEL_DAC5_IOUT    
*\*\            - COMP3_CTRL_INPSEL_VREF2   
*\*\            - COMP3_CTRL_INPSEL_PGA2_IOUT_P  
*\*\            - COMP3_CTRL_INPSEL_PA0          
*\*\         comp4 inp sel 
*\*\            - COMP4_CTRL_INPSEL_PA0    
*\*\            - COMP4_CTRL_INPSEL_PB0    
*\*\            - COMP4_CTRL_INPSEL_PE7     
*\*\            - COMP4_CTRL_INPSEL_PB15    
*\*\            - COMP4_CTRL_INPSEL_PC9     
*\*\            - COMP4_CTRL_INPSEL_DAC2_IOUT    
*\*\            - COMP4_CTRL_INPSEL_DAC6_IOUT    
*\*\            - COMP4_CTRL_INPSEL_VREF2   
*\*\            - COMP4_CTRL_INPSEL_PGA2_IOUT_N  
*\*\         comp5 inp sel 
*\*\            - COMP5_CTRL_INPSEL_PC3    
*\*\            - COMP5_CTRL_INPSEL_PA3    
*\*\            - COMP5_CTRL_INPSEL_PC4     
*\*\            - COMP5_CTRL_INPSEL_PB13    
*\*\            - COMP5_CTRL_INPSEL_DAC3_IOUT    
*\*\            - COMP5_CTRL_INPSEL_DAC7_IOUT    
*\*\            - COMP5_CTRL_INPSEL_VREF3   
*\*\            - COMP5_CTRL_INPSEL_PGA3_IOUT_P  
*\*\            - COMP5_CTRL_INPSEL_PD12     
*\*\         comp6 inp sel 
*\*\            - COMP6_CTRL_INPSEL_PD12   
*\*\            - COMP6_CTRL_INPSEL_PD11   
*\*\            - COMP6_CTRL_INPSEL_PD9     
*\*\            - COMP6_CTRL_INPSEL_PC5     
*\*\            - COMP6_CTRL_INPSEL_PB11    
*\*\            - COMP6_CTRL_INPSEL_DAC4_IOUT    
*\*\            - COMP6_CTRL_INPSEL_DAC8_IOUT    
*\*\            - COMP6_CTRL_INPSEL_VREF3   
*\*\            - COMP6_CTRL_INPSEL_PGA3_IOUT_N  
*\*\         comp7 inp sel 
*\*\            - COMP7_CTRL_INPSEL_PB14   
*\*\            - COMP7_CTRL_INPSEL_PC1    
*\*\            - COMP7_CTRL_INPSEL_PD14    
*\*\            - COMP7_CTRL_INPSEL_DAC4_IOUT    
*\*\            - COMP7_CTRL_INPSEL_DAC7_IOUT    
*\*\            - COMP7_CTRL_INPSEL_VREF3   
*\*\            - COMP7_CTRL_INPSEL_PGA4_IOUT_P  
*\*\            - COMP7_CTRL_INPSEL_PGA4_IOUT_N                             
*\*\return  none
**/
void COMP_SetInpSel(COMPX COMPx, COMP_CTRL_INPSEL VpSel)
{
    __IO uint32_t tmp = COMP->Cmp[COMPx].CTRL;
    tmp &= (~COMP_CTRL_INPSEL_MASK);
    tmp |= (uint32_t)VpSel;
    COMP->Cmp[COMPx].CTRL = tmp;
}
/**
*\*\name    COMP_SetInmSel.
*\*\fun     Select COMPx inverting input.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\          - COMP4
*\*\          - COMP5
*\*\          - COMP6
*\*\          - COMP7
*\*\param   vmsel :
*\*\         comp1 inm sel 
*\*\            - COMP1_CTRL_INMSEL_PA0
*\*\            - COMP1_CTRL_INMSEL_PA4
*\*\            - COMP1_CTRL_INMSEL_PA5
*\*\            - COMP1_CTRL_INMSEL_PA6
*\*\            - COMP1_CTRL_INMSEL_DAC1_IOUT    
*\*\            - COMP1_CTRL_INMSEL_DAC5_IOUT    
*\*\            - COMP1_CTRL_INMSEL_VREF1        
*\*\         comp2 inm sel 
*\*\            - COMP2_CTRL_INMSEL_PA2,
*\*\            - COMP2_CTRL_INMSEL_PA4
*\*\            - COMP2_CTRL_INMSEL_PA5
*\*\            - COMP2_CTRL_INMSEL_PB1
*\*\            - COMP2_CTRL_INMSEL_PE8
*\*\            - COMP2_CTRL_INMSEL_DAC2_IOUT    
*\*\            - COMP2_CTRL_INMSEL_DAC6_IOUT    
*\*\            - COMP2_CTRL_INMSEL_VREF1        
*\*\         comp3 inm sel 
*\*\            - COMP3_CTRL_INMSEL_PB14         
*\*\            - COMP3_CTRL_INMSEL_PA4
*\*\            - COMP3_CTRL_INMSEL_PA5
*\*\            - COMP3_CTRL_INMSEL_PC0
*\*\            - COMP3_CTRL_INMSEL_PE7
*\*\            - COMP3_CTRL_INMSEL_PB12
*\*\            - COMP3_CTRL_INMSEL_PD15         
*\*\            - COMP3_CTRL_INMSEL_PH1          
*\*\            - COMP3_CTRL_INMSEL_DAC1_IOUT    
*\*\            - COMP3_CTRL_INMSEL_DAC5_IOUT    
*\*\            - COMP3_CTRL_INMSEL_VREF2
*\*\         comp4 inm sel 
*\*\            - COMP4_CTRL_INMSEL_PB13         
*\*\            - COMP4_CTRL_INMSEL_PA4
*\*\            - COMP4_CTRL_INMSEL_PA5
*\*\            - COMP4_CTRL_INMSEL_PC4
*\*\            - COMP4_CTRL_INMSEL_PB2
*\*\            - COMP4_CTRL_INMSEL_PE8
*\*\            - COMP4_CTRL_INMSEL_DAC2_IOUT    
*\*\            - COMP4_CTRL_INMSEL_DAC6_IOUT    
*\*\            - COMP4_CTRL_INMSEL_VREF2        
*\*\         comp5 inm sel 
*\*\            - COMP5_CTRL_INMSEL_PA4
*\*\            - COMP5_CTRL_INMSEL_PA5
*\*\            - COMP5_CTRL_INMSEL_PB10
*\*\            - COMP5_CTRL_INMSEL_PD10
*\*\            - COMP5_CTRL_INMSEL_PD13
*\*\            - COMP5_CTRL_INMSEL_DAC3_IOUT    
*\*\            - COMP5_CTRL_INMSEL_DAC7_IOUT    
*\*\            - COMP5_CTRL_INMSEL_VREF3        
*\*\         comp6 inm sel 
*\*\            - COMP6_CTRL_INMSEL_PA7,
*\*\            - COMP6_CTRL_INMSEL_PA4
*\*\            - COMP6_CTRL_INMSEL_PA5
*\*\            - COMP6_CTRL_INMSEL_PB15
*\*\            - COMP6_CTRL_INMSEL_PD8
*\*\            - COMP6_CTRL_INMSEL_PD10
*\*\            - COMP6_CTRL_INMSEL_DAC4_IOUT    
*\*\            - COMP6_CTRL_INMSEL_DAC8_IOUT    
*\*\            - COMP6_CTRL_INMSEL_VREF3        
*\*\         comp7 inm sel 
*\*\            - COMP7_CTRL_INMSEL_PB12         
*\*\            - COMP7_CTRL_INMSEL_PA4
*\*\            - COMP7_CTRL_INMSEL_PA5
*\*\            - COMP7_CTRL_INMSEL_PC0
*\*\            - COMP7_CTRL_INMSEL_PD15
*\*\            - COMP7_CTRL_INMSEL_DAC4_IOUT    
*\*\            - COMP7_CTRL_INMSEL_DAC7_IOUT    
*\*\            - COMP7_CTRL_INMSEL_VREF3                                
*\*\return  none
**/
void COMP_SetInmSel(COMPX COMPx, COMP_CTRL_INMSEL VmSel)
{
    __IO uint32_t tmp = COMP->Cmp[COMPx].CTRL;
    tmp &= (~COMP_CTRL_INMSEL_MASK);
    tmp |= (uint32_t)VmSel;
    COMP->Cmp[COMPx].CTRL = tmp;
}


/**
*\*\name    COMP_SetLock.
*\*\fun     Configures which COMPx will be Locked.
*\*\param   Lock :
*\*\          - COMP1_LOCK
*\*\          - COMP2_LOCK
*\*\          - COMP3_LOCK
*\*\          - COMP4_LOCK
*\*\          - COMP5_LOCK
*\*\          - COMP6_LOCK
*\*\          - COMP7_LOCK
*\*\return  none
**/
void COMP_SetLock(uint32_t Lock)
{
    COMP->LOCK = Lock;
}

/**
*\*\name    COMP_SetIntEn.
*\*\fun     Configures COMPx interrupt enable or disable.
*\*\param   IntEn :
*\*\          - COMP1_INTEN
*\*\          - COMP2_INTEN
*\*\          - COMP3_INTEN
*\*\          - COMP4_INTEN
*\*\          - COMP5_INTEN
*\*\          - COMP6_INTEN
*\*\          - COMP7_INTEN
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void COMP_SetIntEn(uint32_t IntEn, FunctionalState Cmd)
{
    if(Cmd != DISABLE)
    {
        COMP->INTEN |= IntEn;
    }   
    else
    {
        COMP->INTEN &= ~IntEn;
    }
}

/**
*\*\name    COMP_WindowModeEnable.
*\*\fun     Configures COMPx window mode enable or disable.
*\*\param   WinModeEn :
*\*\          - COMP_WINMODE_CMP12MD
*\*\          - COMP_WINMODE_CMP34MD
*\*\          - COMP_WINMODE_CMP56MD
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void COMP_WindowModeEnable(uint32_t WinModeEn, FunctionalState Cmd)
{
    if(Cmd != DISABLE)
    {
        COMP->WINMODE |= WinModeEn;
    }
    else
    {
        COMP->WINMODE &= (~WinModeEn);
    }
}
/**
*\*\name    COMP_SetRefScl.
*\*\fun     Configures the COMP reference voltage. 
*\*\param   Vv3Trim :
*\*\          - Value can be set from 0 to 63.
*\*\param   Vv3En :
*\*\          - false
*\*\          - true
*\*\param   Vv2Trim :
*\*\          - Value can be set from 0 to 63.
*\*\param   Vv2En :
*\*\          - false
*\*\          - true
*\*\param   Vv1Trim :
*\*\           - Value can be set from 0 to 63.     
*\*\param   Vv1En :
*\*\          - false
*\*\          - true
*\*\return  none
**/
void COMP_SetRefScl(uint8_t Vv3Trim, bool Vv3En, uint8_t Vv2Trim, bool Vv2En, uint8_t Vv1Trim, bool Vv1En)
{
    __IO uint32_t temp = 0;

    temp = COMP->INVREF;
    temp &= (~(COMP_VREFSCL_VV1EN_MSK | COMP_VREFSCL_VV1TRM_MSK | COMP_VREFSCL_VV2EN_MSK | \
              COMP_VREFSCL_VV2TRM_MSK | COMP_VREFSCL_VV3EN_MSK  | COMP_VREFSCL_VV3TRM_MSK) );

    temp =  (uint32_t)(Vv1En?1:0) + ((uint32_t)Vv1Trim << 1 )+ ((uint32_t)(Vv2En?1:0) << 7 ) + ((uint32_t)Vv2Trim << 8 ) + \
            ((uint32_t)(Vv3En?1:0) << 14 ) + ((uint32_t)Vv3Trim << 15 ) ;

    COMP->INVREF = temp;
}
/**
*\*\name    COMP_GetOutStatus.
*\*\fun     Get COMPx output status.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\          - COMP4
*\*\          - COMP5
*\*\          - COMP6
*\*\          - COMP7
*\*\return  FlagStatus:
*\*\          - SET
*\*\          - RESET
**/
FlagStatus COMP_GetOutStatus(COMPX COMPx)
{
    return ((COMP->Cmp[COMPx].CTRL & COMP_CTRL_OUT_MASK)!= 0U) ? SET : RESET;
}

/**
*\*\name    COMP_GetFilterOutStatus.
*\*\fun     Get COMPx output status of filtering.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\          - COMP4
*\*\          - COMP5
*\*\          - COMP6
*\*\          - COMP7
*\*\return  FlagStatus:
*\*\          - SET
*\*\          - RESET
**/
FlagStatus COMP_GetFilterOutStatus(COMPX COMPx)
{
    return ((COMP->Cmp[COMPx].CTRL & COMP_CTRL_FLTOUT_MASK) != 0U) ? SET : RESET;
}
/**
*\*\name    COMP_GetIntStsOneComp.
*\*\fun     Get COMPx interrupt Status.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\          - COMP4
*\*\          - COMP5
*\*\          - COMP6
*\*\          - COMP7
*\*\return 
*\*\          - RESET : COMPx Interrupt status is reset;
*\*\          - SET   : COMPx Interrupt status is set;
**/
FlagStatus COMP_GetIntStsOneComp(COMPX COMPx)
{
    return ((COMP->INTSTS & ((uint32_t)0x01U << COMPx)) != 0U) ? SET : RESET;
}

/**
*\*\name    COMP_ClearIntStsOneComp.
*\*\fun     Clear COMPx interrupt Status.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\          - COMP4
*\*\          - COMP5
*\*\          - COMP6
*\*\          - COMP7
*\*\return  none
**/
void COMP_ClearIntStsOneComp(COMPX COMPx)
{
    COMP->INTSTS &= ((~(0x01U << COMPx )));
}

/**
*\*\name    COMP_OutToTimEnable.
*\*\fun     Enable or disable the output channel to timer .
*\*\param   TimEn :
*\*\          - COMP1_TIM_EN
*\*\          - COMP2_TIM_EN
*\*\          - COMP3_TIM_EN
*\*\          - COMP4_TIM_EN
*\*\          - COMP5_TIM_EN
*\*\          - COMP6_TIM_EN
*\*\          - COMP7_TIM_EN
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void COMP_OutToTimEnable(uint32_t TimEn, FunctionalState Cmd)
{
    if(Cmd != DISABLE)
    {
        COMP->OTIMEN |= TimEn;
    }
    else
    {
        COMP->OTIMEN &= (~TimEn);
    }
}

/**
*\*\name    COMP_SetFilterPrescaler.
*\*\fun     Set the COMP filter clock Prescaler value.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\          - COMP4
*\*\          - COMP5
*\*\          - COMP6
*\*\          - COMP7    
*\*\param   FilPreVal :
*\*\          -  Value can be set from 0 to 65535.
*\*\return  none
**/
void COMP_SetFilterPrescaler(COMPX COMPx , uint16_t FilPreVal)
{
    COMP->Cmp[COMPx].FILP = FilPreVal;
}

/**
*\*\name    COMP_SetFilterControl.
*\*\fun     Configures the COMP filter control value.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\          - COMP4
*\*\          - COMP5
*\*\          - COMP6
*\*\          - COMP7
*\*\param   FilEn :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\param   TheresNum :
*\*\          - Threshold Value need > SampWindow/2.      
*\*\param   SampPW :
*\*\          -  Value can be set from 0 to 31.
*\*\return  none
**/
void COMP_SetFilterControl(COMPX COMPx , uint8_t FilEn, uint8_t TheresNum , uint8_t SampPW)
{
    COMP->Cmp[COMPx].FILC = (uint32_t)(FilEn&COMP_FILC_FILEN_MASK)+(((uint32_t)TheresNum << 1)&COMP_FILC_THRESH_MASK)+(((uint32_t)SampPW << 6)& COMP_FILC_SAMPW_MASK);
}

/**
*\*\name    COMP_SetVflagEnable.
*\*\fun     Enable or disable using DAC stable value as Comparator's input.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\          - COMP4
*\*\          - COMP5
*\*\          - COMP6
*\*\          - COMP7    
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void COMP_SetVflagEnable(COMPX COMPx , FunctionalState Cmd)
{
    if(Cmd != DISABLE)
    {
        COMP->Cmp[COMPx].FILC |= COMP_DAC_EN_MASK;
    }
    else
    {
        COMP->Cmp[COMPx].FILC &= (~COMP_DAC_EN_MASK);
    }
}


/**
*\*\name    COMP_SetHyst.
*\*\fun     Configures COMPx hysteresis level.
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\          - COMP4
*\*\          - COMP5
*\*\          - COMP6
*\*\          - COMP7
*\*\param   HYST :
*\*\          - COMP_HYST_NO   
*\*\          - COMP_CTRL_HYST_10MV:   10mV-level
*\*\          - COMP_CTRL_HYST_20MV:   20mV-level
*\*\          - COMP_CTRL_HYST_30MV:   30mV-level   
*\*\          - COMP_CTRL_HYST_40MV:   40mV-level   
*\*\          - COMP_CTRL_HYST_50MV:   50mV-level   
*\*\          - COMP_CTRL_HYST_60MV:   60mV-level   
*\*\          - COMP_CTRL_HYST_70MV:   70mV-level   
*\*\return  none
**/
void COMP_SetHyst(COMPX COMPx , COMP_CTRL_HYST HYST)
{
    uint32_t temp;

    temp  = COMP->Cmp[COMPx].CTRL;
    temp &= (~COMP_CTRL_HYST_MASK);
    temp |= (uint32_t)HYST;

    COMP->Cmp[COMPx].CTRL = temp;
}

/**
*\*\name    COMP_SetBlanking.
*\*\fun     Configures which TIMx output signal to control COMPx Blking. 
*\*\param   COMPx :
*\*\          - COMP1
*\*\          - COMP2
*\*\          - COMP3
*\*\          - COMP4
*\*\          - COMP5
*\*\          - COMP6
*\*\          - COMP7
*\*\param   BLK :
*\*\          - COMP_CTRL_BLKING_NO
*\*\          - COMP_CTRL_BLKING_ATIM1_OC5
*\*\          - COMP_CTRL_BLKING_ATIM2_OC5
*\*\          - COMP_CTRL_BLKING_ATIM3_OC5
*\*\          - COMP_CTRL_BLKING_GTIM8_OC5
*\*\          - COMP_CTRL_BLKING_GTIM9_OC5
*\*\          - COMP_CTRL_BLKING_GTIM10_OC5
*\*\return  none
**/
void COMP_SetBlanking(COMPX COMPx , COMP_CTRL_BLKING BLK)
{
    uint32_t temp;
    
    temp  = COMP->Cmp[COMPx].CTRL;
    temp &= (~COMP_CTRL_BLKING_MASK);
    temp |= (uint32_t)BLK;
    COMP->Cmp[COMPx].CTRL = temp;
}

