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
*\*\file n32h47x_48x_rcc.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
 */
#include "n32h47x_48x_rcc.h"
#include <math.h>

/** RCC Private Defines **/
#define __RCC_DELAY_US(usec)     do{                                       \
                                    uint32_t delay_end;                   \
                                    CPU_DELAY_INTI();                     \
                                    /* Delay*/                            \
                                    delay_end = DWT_CYCCNT + (usec * (240000000/1000000)); \
                                    while(DWT_CYCCNT < delay_end){};      \
                                    CPU_DELAY_DISABLE();                  \
                                  }while(0) 



/** RCC Driving Functions Declaration **/ 

/**
*\*\name    RCC_DeInit.
*\*\fun     Reset the RCC registers.
*\*\param   none 
*\*\return  none 
**/
void RCC_DeInit(void)
{
     /* Set HSIEN bit */
    RCC->CTRL |= (uint32_t)0x00000004;

    /* Reset SCLKSW, AHBPRE, APB1PRES, APB2PRES and MCOPLLSEL bits */
    RCC->CFG &= (uint32_t)0x33F001FFU;

    /* Reset HSEEN, HSECSSEN, HSEBP and PLLEN bits */
    RCC->CTRL &= (uint32_t)0xFFFFFF2EU;
  
    /* Reset PLLMULFCT, PLLHSEPRES, PLLHSIPRES and PLLSRC bits */
    RCC->CFG &= (uint32_t)0xFFFFFE00U;
    
    /* Reset PLLINPRES, PLLOUTPRES and SCLKPLLSEL bits */
    RCC->PLLCTRL &= (uint32_t)0xFFC0FFFFU;

    /* Reset CFG2 register */
    RCC->CFG2 = 0x00007000;
    
    /* Reset CFG3 register */
    RCC->CFG3 = 0x00000071;

    /* Disable all interrupts and clear pending bits  */
    RCC->CLKINT = 0x01FF0000;
    
    /* Reset MCOCFG register */
    RCC->MCOCFG = 0x00000000;
}


/**
*\*\name    RCC_ConfigHse.
*\*\fun     Configures the External High Speed oscillator (HSE).
*\*\param   RCC_HSE :
*\*\          - RCC_HSE_DISABLE    HSE oscillator OFF 
*\*\          - RCC_HSE_ENABLE     HSE oscillator ON
*\*\          - RCC_HSE_BYPASS     HSE oscillator bypassed with external clock
*\*\return  none:
*\*\note    HSE can not be stopped if it is used directly or through the PLL as system clock
**/
void RCC_ConfigHse(uint32_t RCC_HSE)
{
    uint32_t temp_value;
    
    temp_value = RCC->CTRL;
    /* Reset HSEEN bit */
    temp_value &= (~RCC_HSE_ENABLE);
    /* Reset HSEBP bit */
    temp_value &= (~RCC_HSE_BYPASS);
    /* Configure HSE (RC_HSE_DISABLE is already covered by the code section above) */
    if(RCC_HSE == RCC_HSE_ENABLE)
    {
        /* Set HSEEN bit */
        temp_value |= RCC_HSE_ENABLE;
    }   
    else if (RCC_HSE == RCC_HSE_BYPASS)
    {
        /* Set HSEBP and HSEEN bits */
        temp_value |= RCC_HSE_BYPASS | RCC_HSE_ENABLE;
    }
    else
    {
        /* No process */
    }

    RCC->CTRL = temp_value;

}
 
/**
*\*\name    RCC_WaitHseStable.
*\*\fun     Waits for HSE start-up.
*\*\param   none
*\*\return  ErrorStatus:
 *\*\         - SUCCESS    HSE oscillator is stable and ready to use
 *\*\         - ERROR      HSE oscillator not yet ready
**/
ErrorStatus RCC_WaitHseStable(void)
{
    __IO uint32_t counter_value = 0;
    uint32_t timeout_value;  
    FlagStatus status_value;
	RCC_ClocksType sysclk_value;
    ErrorStatus bitstatus;

	RCC_GetClocksFreqValue(&sysclk_value);
	timeout_value = (HSE_STARTUP_TIMEOUT/((uint32_t)240000000/sysclk_value.SysclkFreq));
	
    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        status_value = RCC_GetFlagStatus(RCC_FLAG_HSERDF);
        counter_value++;
    } while ((counter_value != timeout_value) && (status_value == RESET));
    
    if (RCC_GetFlagStatus(RCC_FLAG_HSERDF) != RESET)
    {
        bitstatus = SUCCESS;
    }
    else
    {
        bitstatus = ERROR;
    }
    return bitstatus;
}


/**
*\*\name    RCC_EnableHSEClockSecuritySystem.
*\*\fun     Enables the HSE Clock Security System.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE     
*\*\return  none. 
**/
void RCC_EnableHSEClockSecuritySystem(FunctionalState Cmd)
{
     if (Cmd != DISABLE)
    {
        RCC->CTRL |= RCC_HSECSS_ENABLE;
    }
    else
    {
        RCC->CTRL &= (~RCC_HSECSS_ENABLE);
    }
}

/**
*\*\name    RCC_EnableHSECSSChktype.
*\*\fun     Enable different HSE CSS detection type .
*\*\param   Chk_type :
*\*\         - RCC_CSSEN_HSEPOEN     HSE phase shift out of range enable
*\*\         - RCC_CSSEN_HSEFHEN     HSE frequency out of high limit enable
*\*\         - RCC_CSSEN_HSEFLEN     HSE frequency out of low limit enable
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE       
*\*\return none. 
**/
void RCC_EnableHSECSSChk(uint32_t Chk_type, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->CSSCTRL |= Chk_type;
    }
    else
    {
        RCC->CSSCTRL &= ~Chk_type;
    }
    
}

/**
*\*\name    RCC_SetHSECSSPhaseOffsetLimit.
*\*\fun     Adjusts HSE Phase Offset Limit value.
*\*\param   limit_value(the Limit value):
*\*\        This parameter must be a number between 0x0 and 0xF
*\*\return  none
*\*\note    Error when phase offset Δt is greater than (tHSI*limit_value/32)us
**/ 
void RCC_SetHSECSSPhaseOffsetLimit(uint8_t limit_value) 
{
    uint32_t temp_value;

    temp_value = RCC->CSSCTRL;
    /* Clear HSEPOTHR[3:0] bits */
    temp_value &= RCC_HSEPOTHR_MASK;
    /* Set the HSEPOTHR[3:0] bits according to limit_value value */
    temp_value |= ((uint32_t)limit_value << 8); 
    /* Store the new value */
    RCC->CSSCTRL = temp_value;
}

/**
*\*\name    RCC_SetHSECSSFrequencyHighLimit.
*\*\fun     Adjusts HSE Frequency High Limit value.
*\*\param   limit_value(the Limit value):
*\*\        This parameter must be a number between 0x0 and 0xF
*\*\return  none
*\*\note    Error when the frequency is greater than (2*32/limit_value)MHz
**/ 
void RCC_SetHSECSSFrequencyHighLimit(uint8_t limit_value) 
{
    uint32_t temp_value;

    temp_value = RCC->CSSCTRL;
    /* Clear HSEFHTHR[3:0] bits */
    temp_value &= RCC_HSEFHTHR_MASK;
    /* Set the HSEFHTHR[3:0] bits according to limit_value value */
    temp_value |= ((uint32_t)limit_value << 4); 
    /* Store the new value */
    RCC->CSSCTRL = temp_value;
}

/**
*\*\name    RCC_SetHSECSSFrequencyLowLimit.
*\*\fun     Adjusts HSE Frequency Low Limit value.
*\*\param   limit_value(the Limit value):
*\*\        This parameter must be a number between 0x0 and 0xF
*\*\return  none
*\*\note    Error when the frequency is less than (32/limit_value)MHz
**/ 
void RCC_SetHSECSSFrequencyLowLimit(uint8_t limit_value) 
{
    uint32_t temp_value;

    temp_value = RCC->CSSCTRL;
    /* Clear HSEFLTHR[3:0] bits */
    temp_value &= RCC_HSEFLTHR_MASK;
    /* Set the HSEFLTHR[3:0] bits according to limit_value value */
    temp_value |= (uint32_t)limit_value; 
    /* Store the new value */
    RCC->CSSCTRL = temp_value;
}

/**
*\*\name    RCC_GetHSECSSStatus.
*\*\fun     Checks whether the specified HSE CSS flag has occurred or not.
*\*\param   interrupt_flag(RCC interrupt source to check):
*\*\         - RCC_CSSFLAG_HSEPOF     HSE phase shift out of range flag
*\*\         - RCC_CSSFLAG_HSEFHF     HSE frequency out of high limit flag
*\*\         - RCC_CSSFLAG_HSEFLF     HSE frequency out of low limit flag
*\*\return  FlagStatus:    
*\*\      	  - SET 
*\*\  	      - RESET
**/
FlagStatus RCC_GetHSECSSStatus(uint32_t interrupt_flag)
{
    FlagStatus bitstatus;
    /* Check the status of the specified RCC interrupt */
    if ((RCC->CSSCTRL & interrupt_flag) != (uint32_t)RESET)
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
*\*\name    RCC_SetHsiCalibValue.
*\*\fun     Adjusts the Internal High Speed oscillator (HSI) calibration value.
*\*\param   calibration_value(the calibration trimming value):
*\*\        This parameter must be a number between 0 and 0x7F
*\*\return  none
**/ 
void RCC_SetHsiCalibValue(uint8_t calibration_value) 
{
    uint32_t temp_value;

    temp_value = RCC->CTRL;
    /* Clear HSITRIM[6:0] bits */
    temp_value &= RCC_HSITRIM_MASK;
    /* Set the HSITRIM[6:0] bits according to HSICalibrationValue value */
    temp_value |= (uint32_t)calibration_value << RCC_CTRL_HSITRIM_OFFSET; 
    /* Store the new value */
    RCC->CTRL = temp_value;
}

/**
*\*\name    RCC_EnableHsi.
*\*\fun     Enables the Internal High Speed oscillator (HSI).
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE  
*\*\return  none
*\*\note   HSI can not be stopped if it is used directly or through the PLL as system clock.
**/ 
void RCC_EnableHsi(FunctionalState Cmd)
{
    if(Cmd == ENABLE)
   {
       /* Set HSIEN bit */
       RCC->CTRL |= RCC_HSI_ENABLE;
   }
   else
   {
       /* Reset HSIEN bit */
       RCC->CTRL &= (~RCC_HSI_ENABLE);
   }
}
 
/**
*\*\name    RCC_WaitHsiStable.
*\*\fun     Waits for HSI start-up.
*\*\param   none
*\*\return  ErrorStatus:
 *\*\         - SUCCESS    HSI oscillator is stable and ready to use
 *\*\         - ERROR      HSI oscillator not yet ready
**/
ErrorStatus RCC_WaitHsiStable(void)
{
    __IO uint32_t counter_value = 0;
    uint32_t timeout_value;  
    FlagStatus status_value;
	RCC_ClocksType sysclk_value;
    ErrorStatus bitstatus;

	RCC_GetClocksFreqValue(&sysclk_value);
	timeout_value = (HSI_STARTUP_TIMEOUT/((uint32_t)240000000/sysclk_value.SysclkFreq));

    /* Wait till HSI is ready and if Time out is reached exit */
    do
    {
        status_value = RCC_GetFlagStatus(RCC_FLAG_HSIRDF);
        counter_value++;
    } while ((counter_value != timeout_value) && (status_value == RESET));
    
    if (RCC_GetFlagStatus(RCC_FLAG_HSIRDF) != RESET)
    {
        bitstatus = SUCCESS;
    }
    else
    {
        bitstatus = ERROR;
    }
    return bitstatus;
}

/**
*\*\name    RCC_EnableHSIClockSecuritySystem.
*\*\fun     Enables the HSI Clock Security System.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE     
*\*\return  none. 
**/
void RCC_EnableHSIClockSecuritySystem(FunctionalState Cmd)
{
     if (Cmd != DISABLE)
    {
        RCC->CSSCTRL |= RCC_HSICSS_ENABLE;
    }
    else
    {
        RCC->CSSCTRL &= (~RCC_HSICSS_ENABLE);
    }
}

/**
*\*\name    RCC_ConfigPll.
*\*\fun     Configures the PLL clock source and multiplication factor.
*\*\param   PLL_source(PLL entry clock source):
*\*\   		  - RCC_PLL_SRC_HSI         HSI oscillator clock selected as PLL clock entry
*\*\   		  - RCC_PLL_SRC_HSI_DIV2    HSI oscillator divider 2 clock selected as PLL clock entry
*\*\   		  - RCC_PLL_SRC_HSE         HSE oscillator clock selected as PLL clock entry
*\*\   		  - RCC_PLL_SRC_HSE_DIV2    HSE oscillator divider 2 clock selected as PLL clock entry
*\*\param   PLL_prescaler(PLL input divider):
*\*\	      - RCC_PLL_PRE_1 
*\*\	      - RCC_PLL_PRE_2
*\*\	      - RCC_PLL_PRE_3 
*\*\	      - RCC_PLL_PRE_4 
*\*\param   PLL_multiplication(PLL multiplication factor):
*\*\	      - RCC_PLL_MUL_8  
*\*\	      - RCC_PLL_MUL_10 
*\*\	      - RCC_PLL_MUL_12 
*\*\	      - RCC_PLL_MUL_14 
*\*\	      - RCC_PLL_MUL_16 
*\*\	      - RCC_PLL_MUL_18 
*\*\	      - RCC_PLL_MUL_20 
*\*\	      - RCC_PLL_MUL_22 
*\*\	      - RCC_PLL_MUL_24 
*\*\	      - RCC_PLL_MUL_26 
*\*\	      - RCC_PLL_MUL_28 
*\*\	      - RCC_PLL_MUL_30
*\*\	      - RCC_PLL_MUL_32
*\*\	      - RCC_PLL_MUL_34
*\*\	      - RCC_PLL_MUL_36
*\*\	      - RCC_PLL_MUL_38 
*\*\	      - RCC_PLL_MUL_40 
*\*\	      - RCC_PLL_MUL_42 
*\*\	      - RCC_PLL_MUL_44 
*\*\	      - RCC_PLL_MUL_46 
*\*\	      - RCC_PLL_MUL_48 
*\*\	      - RCC_PLL_MUL_50 
*\*\	      - RCC_PLL_MUL_52 
*\*\	      - RCC_PLL_MUL_54 
*\*\	      - RCC_PLL_MUL_56
*\*\	      - RCC_PLL_MUL_58
*\*\	      - RCC_PLL_MUL_60
*\*\	      - RCC_PLL_MUL_62
*\*\	      - RCC_PLL_MUL_64 
*\*\	      - RCC_PLL_MUL_66 
*\*\	      - RCC_PLL_MUL_68 
*\*\	      - RCC_PLL_MUL_70 
*\*\	      - RCC_PLL_MUL_72 
*\*\	      - RCC_PLL_MUL_74 
*\*\	      - RCC_PLL_MUL_76 
*\*\param   PLL_outdivider(PLL out divider):
*\*\	      - RCC_PLLOUT_DIV_1 
*\*\	      - RCC_PLLOUT_DIV_2
*\*\	      - RCC_PLLOUT_DIV_4 
*\*\	      - RCC_PLLOUT_DIV_8 
*\*\return  none
*\*\note    This function must be used only when the PLL is disabled. 
*\*\note    Fin frequency requirement is in the range of 4MHz ~ 50MHz,
*\*\	    Fref frequency requirement is in the range of 4MHz ~ 25MHz,
*\*\	    Fvco frequency requirement is in the range of 64MHz ~ 500MHz. 
**/
void RCC_ConfigPll(uint32_t PLL_source, uint32_t  PLL_prescaler, uint32_t PLL_multiplication, uint32_t PLL_outdivider)
{
    uint32_t temp_value1,temp_value2;  
    
    /* get the pll value */
    temp_value1 = RCC->CFG;
    temp_value2 = RCC->PLLCTRL;

    /* Clear PLLSRC, PLLHSEPRES, PLLHSIPRES and PLLMULFCT[5:0] bits */
    temp_value1 &= RCC_PLL_CFG_MASK;
    /* Clear PLLINPRES[1:0], PLLOUTPRES[1:0],LPFC2[2:0],LPFR[3:0],LPFC1[3:0] bits */
    temp_value2 &= RCC_PLL_PLLCTRL_MASK;

    /* Set PLLSRC, PLLHSEPRES, PLLHSIPRES and PLLMULFCT[5:0] bits */
    temp_value1 |= (PLL_source | PLL_multiplication);
    /* Set PLLINPRES[1:0], PLLOUTPRES[1:0],LPFC2[2:0],LPFR[3:0],LPFC1[3:0] bits */
    if(PLL_multiplication <= RCC_PLL_MUL_24)
    {
        temp_value2 |= (PLL_prescaler | PLL_outdivider | ((uint32_t)0x00006340));
    }
    else if(PLL_multiplication <= RCC_PLL_MUL_40)
    {
        temp_value2 |= (PLL_prescaler | PLL_outdivider | ((uint32_t)0x00006740));
    }
    else
    {
        temp_value2 |= (PLL_prescaler | PLL_outdivider | ((uint32_t)0x00006C40));
    }
    

    /* Store the new value */
    RCC->CFG  = temp_value1;
    RCC->PLLCTRL  = temp_value2;
}

/**
*\*\name    RCC_EnablePll.
*\*\fun     Enables the PLL.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/ 
void RCC_EnablePll(FunctionalState Cmd)
{
    if(Cmd == ENABLE)
   {
       /* Set PLLEN bit */
       RCC->CTRL |= RCC_PLL_ENABLE;
   }
   else
   {
       /* Reset PLLEN bit */
       RCC->CTRL &= (~RCC_PLL_ENABLE);
   }
}

/**
*\*\name    RCC_ConfigSHRTPll.
*\*\fun     Configures the SHRTPLL clock source and multiplication factor.
*\*\param   SHRTPLL_source(SHRTPLL entry clock source):
*\*\   		  - RCC_SHRTPLL_SRC_HSI         HSI oscillator clock selected as SHRTPLL clock entry
*\*\   		  - RCC_SHRTPLL_SRC_HSE         HSE oscillator clock selected as SHRTPLL clock entry
*\*\param   fin(SHRTPLL input frequency):
*\*\         1000000 ~ 50000000 (Hz)
*\*\param   fout(SHRTPLL output frequency):
*\*\         75000000 ~ 250000000 (Hz)
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  ErrorStatus:
 *\*\         - SUCCESS    
 *\*\         - ERROR     
*\*\note    SHRTPLL = SHRTPLL_source*(CLKF[25:0]/16384)/(CLKR[5:0] +1)/4
**/
ErrorStatus RCC_ConfigSHRTPll(uint32_t SHRTPLL_source, uint64_t fin, uint64_t fout, FunctionalState Cmd)
{
    uint32_t temp_value1,temp_value2,temp_value3;  
    ErrorStatus status;
    uint64_t err_t;
    uint32_t nr_t;
    uint32_t nf_all;
    uint32_t nf_int;
    uint64_t expect_fout;

    uint64_t err = (uint64_t)0xFFFFFFFFU;
    uint32_t nr = 0;
    uint32_t nf = 0;
    uint32_t wb = 0;
    
    if(Cmd == DISABLE)
    {
        /* Reset SHRTPLL */
        RCC_EnableAHBPeriphReset(RCC_AHB_PERIPHRST_SHRTPLL);
        /* Configure the work mode to Power-down */
        RCC->SHRTPLLCTRL1 |= RCC_SHRTPLLMODE_PD;
        /* Disable SHRTPLL module power */
        RCC->SHRTPLLCTRL3 &= (~RCC_SHRTPLL_ENABLE);
        status = SUCCESS;        
    }
    else
    {   
        /* get NR NF WB parameter */
        expect_fout = (fout*4);
        if ((fin > REF_MAX) || (fin < REF_MIN) || (expect_fout > VCO_MAX) || (expect_fout < VCO_MIN)) 
        {
            status = ERROR;
        } 
        else 
        {
            for ( nr_t = NR_MAX; nr_t >= NR_MIN; nr_t--) 
            {
                nf_all = (uint32_t)floor(expect_fout * nr_t * 256 / fin);
                nf_int = nf_all / 256;
                if ((nf_int > NF_MAX) || (nf_int < NF_MIN)) 
                {
                    continue;
                }
                if((fin * nf_all / nr_t / 256) > expect_fout)
                {
                    err_t = ((fin * nf_all / nr_t / 256) - expect_fout);
                }
                else
                {
                    err_t = (expect_fout - (fin * nf_all / nr_t / 256));
                }
                if (err_t <= err) 
                {
                    err = err_t;
                    nr = nr_t;
                    nf = nf_all;
                }
                else
                {
                    /* In other cases, the cycle continues*/
                }
            }
            wb = (uint32_t)floor((nf / 2 / 256) - 1);
            if(wb > 2047)
            {
                wb = 2047;
            }
            nr = nr - 1;
            nf = nf * 64;
            status = SUCCESS;       
        }
        
        if(status == SUCCESS)
        {
            /* Enable SHRTPLL module power */
            RCC->SHRTPLLCTRL3 |= RCC_SHRTPLL_ENABLE;
            /* Select Clock Source */
            temp_value3 = RCC->SHRTPLLCTRL3;
            temp_value3 &= RCC_SHRTPLL_SRC_MASK;
            temp_value3 |= SHRTPLL_source;
            RCC->SHRTPLLCTRL3 = temp_value3;
            /* Configure the work mode to normal */
            RCC->SHRTPLLCTRL1 &= (~RCC_SHRTPLLMODE_PD);
            /* Enable Saturation and fraction accumulation function */
            RCC->SHRTPLLCTRL1 |= (RCC_SHRTPLL_SATEN|RCC_SHRTPLL_FRACEN);
            
            /* get the SHRTPLL value */
            temp_value1 = RCC->SHRTPLLCTRL1;
            temp_value2 = RCC->SHRTPLLCTRL2;
            temp_value3 = RCC->SHRTPLLCTRL3;

            /* Clear CLKF[25:0] bits */
            temp_value1 &= RCC_SHRTPLL_CLKF_MASK;
            /* Clear CLKR[5:0] bits */
            temp_value2 &= RCC_SHRTPLL_CLKR_MASK;
            /* Clear BWTRIM[11:0] bits */
            temp_value3 &= RCC_SHRTPLL_BWTRIM_MASK;

            /* Set CLKF[25:0] bits */
            temp_value1 |= (uint32_t)nf;
            /* Set CLKR[5:0] bits */
            temp_value2 |= ((uint32_t)nr<<26);
            /* Set BWTRIM[11:0] bits */
            temp_value3 |= ((uint32_t)wb<<12);

            /* Store the new value */
            RCC->SHRTPLLCTRL1  = temp_value1;
            RCC->SHRTPLLCTRL2  = temp_value2;
            RCC->SHRTPLLCTRL3  = temp_value3;
            
            /* Reset SHRTPLL */
            RCC_EnableAHBPeriphReset(RCC_AHB_PERIPHRST_SHRTPLL);

        }
                    
    }
    return status;
}



/**
*\*\name    RCC_ConfigSysclk.
*\*\fun     Configures the system clock (SYSCLK).
*\*\param   sysclk_source(clock source used as system clock):
*\*\	     - RCC_SYSCLK_SRC_HSI           HSI selected as system clock
*\*\	     - RCC_SYSCLK_SRC_HSE           HSE selected as system clock
*\*\	     - RCC_SYSCLK_SRC_PLL           PLL selected as system clock
*\*\	     - RCC_SYSCLK_SRC_SHRTPLL       SHRPLL selected as system clock
*\*\	     - RCC_SYSCLK_SRC_USBHS240M    USBHS240M selected as system clock
*\*\return  none
**/
void RCC_ConfigSysclk(uint32_t sysclk_source)
{
    uint32_t temp_value,temp_value1;
    
    temp_value = RCC->CFG;
    /* Clear SCLKSW[1:0] bits */
    temp_value &= RCC_SYSCLK_SRC_CFG_MASK;

    if((sysclk_source&0x80000000U) == 0x80000000U)
    {
        /* Set SCLKSW[1:0] bits in CFG register */
        temp_value |= (sysclk_source&RCC_CFG_SCLKSW);
        
    }
    else
    {
         temp_value1 = RCC->PLLCTRL;
        /* Clear SCLKPLLSEL[1:0] bits */
        temp_value1 &= RCC_SYSCLK_SRC_PLLCTRL_MASK;

        /* Set SCLKPLLSEL[1:0] bits in PLLCTRL register */
        temp_value1 |= sysclk_source;
        /* Store the new value */
        RCC->PLLCTRL = temp_value1;

        /* Set SCLKSW[1:0] bits in CFG register */
        temp_value |= RCC_SYSCLK_SRC_CFG_PLLSEL;
    }
   
    /* Store the new value */
    RCC->CFG = temp_value;
    
}

/**
*\*\name    RCC_GetSysclkSrc.
*\*\fun     Returns the clock source used as system clock.
*\*\param   none
*\*\return  (The clock source used as system clock):
*\*\         - RCC_CFG_SCLKSTS_HSI    HSI used as system clock  
*\*\         - RCC_CFG_SCLKSTS_HSE    HSE used as system clock
*\*\         - RCC_CFG_SCLKSTS_PLL    PLL used as system clock
**/
uint32_t RCC_GetSysclkSrc(void)  
{  
    return ((uint32_t)(RCC->CFG & RCC_SYSCLK_STS_MASK));
}

/**
*\*\name    RCC_ConfigHclk.
*\*\fun     Configures the AHB clock (HCLK).
*\*\param   sysclk_div(AHB clock is derived from the system clock (SYSCLK)):
*\*\         - RCC_SYSCLK_DIV1      AHB clock = SYSCLK
*\*\         - RCC_SYSCLK_DIV2      AHB clock = SYSCLK/2
*\*\         - RCC_SYSCLK_DIV4      AHB clock = SYSCLK/4
*\*\         - RCC_SYSCLK_DIV8      AHB clock = SYSCLK/8
*\*\         - RCC_SYSCLK_DIV16     AHB clock = SYSCLK/16
*\*\         - RCC_SYSCLK_DIV64     AHB clock = SYSCLK/64
*\*\         - RCC_SYSCLK_DIV128    AHB clock = SYSCLK/128
*\*\         - RCC_SYSCLK_DIV256    AHB clock = SYSCLK/256
*\*\         - RCC_SYSCLK_DIV512    AHB clock = SYSCLK/512
*\*\return  none
**/
void RCC_ConfigHclk(uint32_t sysclk_div)
{
    uint32_t temp_value;
    temp_value = RCC->CFG;
    /* Clear AHBPRES[3:0] bits */
    temp_value &= RCC_SYSCLK_DIV_MASK;
    /* Set AHBPRES[3:0] bits according to rcc_sysclk value */
    temp_value |= sysclk_div;
    /* Store the new value */
    RCC->CFG = temp_value;
}

/**
*\*\name    RCC_ConfigPclk1.
*\*\fun     Configures the Low Speed APB clock (PCLK1).
*\*\param   hclk_div(APB1 clock is derived from the AHB clock (HCLK)):
*\*\         - RCC_HCLK_DIV1     APB1 clock = HCLK
*\*\         - RCC_HCLK_DIV2     APB1 clock = HCLK/2
*\*\         - RCC_HCLK_DIV4     APB1 clock = HCLK/4
*\*\         - RCC_HCLK_DIV8     APB1 clock = HCLK/8
*\*\         - RCC_HCLK_DIV16    APB1 clock = HCLK/16
*\*\return  none
**/
void RCC_ConfigPclk1(uint32_t hclk_div)
{
    uint32_t temp_value;
    temp_value = RCC->CFG;
    /* Clear APB1PRES[2:0] bits */
    temp_value &= RCC_APB1_DIV_MASK;
    /* Set APB1PRES[2:0] bits according to hclk_div value */
    temp_value |= hclk_div;
    /* Store the new value */
    RCC->CFG = temp_value;
}

/**
*\*\name    RCC_ConfigPclk2.
*\*\fun     Configures the High Speed APB clock (PCLK2).
*\*\param   hclk_div(APB2 clock is derived from the AHB clock (HCLK)):
*\*\         - RCC_HCLK_DIV1     APB2 clock = HCLK
*\*\         - RCC_HCLK_DIV2     APB2 clock = HCLK/2
*\*\         - RCC_HCLK_DIV4     APB2 clock = HCLK/4
*\*\         - RCC_HCLK_DIV8     APB2 clock = HCLK/8
*\*\         - RCC_HCLK_DIV16    APB2 clock = HCLK/16
*\*\return  none
**/
void RCC_ConfigPclk2(uint32_t hclk_div)
{
    uint32_t temp_value;
    temp_value = RCC->CFG;
    /* Clear APB2PRES[2:0] bits */
    temp_value &= RCC_APB2_DIV_MASK;
    /* Set APB2PRES[2:0] bits according to hclk_div value */
    temp_value |= hclk_div << RCC_APB2PRES_OFFSET; 
    /* Store the new value */
    RCC->CFG = temp_value;
}

/**
*\*\name    RCC_ConfigInt.
*\*\fun     Enables the specified RCC interrupts.
*\*\param   Interrupt(the RCC interrupt sources to be enabled):
*\*\         - RCC_INT_LSIRDIF     LSI ready interrupt
*\*\         - RCC_INT_LSERDIF     LSI ready interrupt
*\*\         - RCC_INT_HSIRDIF     HSI ready interrupt
*\*\         - RCC_INT_HSERDIF     HSE ready interrupt
*\*\         - RCC_INT_PLLRDIF     PLL ready interrupt
*\*\         - RCC_INT_LSECSSIF    LSE CSS interrupt 
*\*\         - RCC_INT_HSECSSIF    HSE CSS interrupt 
*\*\         - RCC_INT_HSICSSIF    HSI CSS interrupt 
*\*\         - RCC_INT_BORIF       BOR interrupt 
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/
void RCC_ConfigInt(uint32_t Interrupt, FunctionalState Cmd)
{
    if(Interrupt == RCC_INT_HSICSSIF)
    {
        if (Cmd != DISABLE)
        {
            RCC->CLKINT |= (((uint32_t)Interrupt) >> 4);
        }
        else
        {
            RCC->CLKINT &= (~(((uint32_t)Interrupt) >> 4));
        }
    }
    else
    {
        if (Cmd != DISABLE)
        {
            RCC->CLKINT |= (((uint32_t)Interrupt) << 8);
        }
        else
        {
            RCC->CLKINT &= (~(((uint32_t)Interrupt) << 8));
        }
    }

}

/**
*\*\name    RCC_ConfigATimClk.
*\*\fun     Configures the ATIM1/2/3 clock source(ATIMCLK).
*\*\param   timer_clksrc(ATIM clock source):
*\*\         - RCC_ATIM_CLKSRC_SYSCLK
*\*\         - RCC_ATIM_CLKSRC_HCLK  
*\*\return  none
**/
void RCC_ConfigATimClk(uint32_t timer_clksrc)  
{
    uint32_t temp_value;

    temp_value = RCC->CFG2;
    /* Clear TIMCLK_SEL bits */
    temp_value &= RCC_ATIM_CLKSRC_MASK;
    /* Set TIMCLK_SEL bits according to timer_clksrc value */
    temp_value |= timer_clksrc;

    /* Store the new value */
    RCC->CFG2 = temp_value;
}

/**
*\*\name    RCC_ConfigGTimClk.
*\*\fun     Configures the GTIM8/9/10 clock source(GTIMCLK).
*\*\param   timer_clksrc(GTIM clock source):
*\*\        - RCC_GTIM_CLKSRC_PCLK   
*\*\        - RCC_GTIM_CLKSRC_SYSCLK
*\*\return  none
**/
void RCC_ConfigGTimClk(uint32_t timer_clksrc)  
{
    uint32_t temp_value;

    temp_value = RCC->CFG2;
    /* Clear TIMCLK_SEL bits */
    temp_value &= RCC_GTIM_CLKSRC_MASK;
    /* Set TIMCLK_SEL bits according to timer_clksrc value */
    temp_value |= timer_clksrc;

    /* Store the new value */
    RCC->CFG2 = temp_value;
}

/**
*\*\name    RCC_ConfigI2S3Clk_.
*\*\fun     Configures the I2S3 clock source(I2S3CLK).
*\*\param   I2S_clksrc(I2S3 clock source):
*\*\         - RCC_I2S3_CLKSRC_SYSCLK  
*\*\         - RCC_I2S3_CLKSRC_SHRTPLL
*\*\         - RCC_I2S3_CLKSRC_CLKIN   
*\*\         - RCC_I2S3_CLKSRC_HSI    
*\*\return  none
**/
void RCC_ConfigI2S3Clk(uint32_t I2S_clksrc)  
{
    uint32_t temp_value;

    temp_value = RCC->CFG3;
    /* Clear I2S3SEL bits */
    temp_value &= RCC_I2S3_CLKSRC_MASK;
    /* Set I2S3SEL bits according to I2S_clksrc value */
    temp_value |= I2S_clksrc;

    /* Store the new value */
    RCC->CFG3 = temp_value;
}

/**
*\*\name    RCC_ConfigI2S2Clk_.
*\*\fun     Configures the I2S2 clock source(I2S2CLK).
*\*\param   I2S_clksrc(I2S2 clock source):
*\*\         - RCC_I2S2_CLKSRC_SYSCLK  
*\*\         - RCC_I2S2_CLKSRC_SHRTPLL
*\*\         - RCC_I2S2_CLKSRC_CLKIN   
*\*\         - RCC_I2S2_CLKSRC_HSI    
*\*\return  none
**/
void RCC_ConfigI2S2Clk(uint32_t I2S_clksrc)  
{
    uint32_t temp_value;

    temp_value = RCC->CFG3;
    /* Clear I2S2SEL bits */
    temp_value &= RCC_I2S2_CLKSRC_MASK;
    /* Set I2S2SEL bits according to I2S_clksrc value */
    temp_value |= I2S_clksrc;

    /* Store the new value */
    RCC->CFG3 = temp_value;
}

/**
*\*\name    RCC_ConfigRngcClk.
*\*\fun     Configures the RNGCCLK prescaler.
*\*\param   RNG_prescaler (specifies the RNGCCLK prescaler):
*\*\        - RCC_RNGCCLK_SYSCLK_DIV1     SYSCLK Divided By 1 
*\*\        - RCC_RNGCCLK_SYSCLK_DIV2     SYSCLK Divided By 2 
*\*\        - RCC_RNGCCLK_SYSCLK_DIV3     SYSCLK Divided By 3 
*\*\        - RCC_RNGCCLK_SYSCLK_DIV4     SYSCLK Divided By 4 
*\*\        - RCC_RNGCCLK_SYSCLK_DIV5     SYSCLK Divided By 5 
*\*\        - RCC_RNGCCLK_SYSCLK_DIV6     SYSCLK Divided By 6 
*\*\        - RCC_RNGCCLK_SYSCLK_DIV7     SYSCLK Divided By 7 
*\*\        - RCC_RNGCCLK_SYSCLK_DIV8     SYSCLK Divided By 8 
*\*\        - RCC_RNGCCLK_SYSCLK_DIV9     SYSCLK Divided By 9 
*\*\        - RCC_RNGCCLK_SYSCLK_DIV10    SYSCLK Divided By 10
*\*\        - RCC_RNGCCLK_SYSCLK_DIV11    SYSCLK Divided By 11
*\*\        - RCC_RNGCCLK_SYSCLK_DIV12    SYSCLK Divided By 12
*\*\        - RCC_RNGCCLK_SYSCLK_DIV13    SYSCLK Divided By 13
*\*\        - RCC_RNGCCLK_SYSCLK_DIV14    SYSCLK Divided By 14
*\*\        - RCC_RNGCCLK_SYSCLK_DIV15    SYSCLK Divided By 15
*\*\        - RCC_RNGCCLK_SYSCLK_DIV16    SYSCLK Divided By 16
*\*\        - RCC_RNGCCLK_SYSCLK_DIV17    SYSCLK Divided By 17
*\*\        - RCC_RNGCCLK_SYSCLK_DIV18    SYSCLK Divided By 18
*\*\        - RCC_RNGCCLK_SYSCLK_DIV19    SYSCLK Divided By 19
*\*\        - RCC_RNGCCLK_SYSCLK_DIV20    SYSCLK Divided By 20
*\*\        - RCC_RNGCCLK_SYSCLK_DIV21    SYSCLK Divided By 21
*\*\        - RCC_RNGCCLK_SYSCLK_DIV22    SYSCLK Divided By 22
*\*\        - RCC_RNGCCLK_SYSCLK_DIV23    SYSCLK Divided By 23
*\*\        - RCC_RNGCCLK_SYSCLK_DIV24    SYSCLK Divided By 24
*\*\        - RCC_RNGCCLK_SYSCLK_DIV25    SYSCLK Divided By 25
*\*\        - RCC_RNGCCLK_SYSCLK_DIV26    SYSCLK Divided By 26
*\*\        - RCC_RNGCCLK_SYSCLK_DIV27    SYSCLK Divided By 27
*\*\        - RCC_RNGCCLK_SYSCLK_DIV28    SYSCLK Divided By 28
*\*\        - RCC_RNGCCLK_SYSCLK_DIV29    SYSCLK Divided By 29
*\*\        - RCC_RNGCCLK_SYSCLK_DIV30    SYSCLK Divided By 30
*\*\        - RCC_RNGCCLK_SYSCLK_DIV31    SYSCLK Divided By 31
*\*\        - RCC_RNGCCLK_SYSCLK_DIV32    SYSCLK Divided By 32
*\*\return  none
**/
void RCC_ConfigRngcClk(uint32_t RNG_prescaler)
{
    uint32_t temp_value;

    temp_value = RCC->CFG2;
    /* Clear RNGCPRE[4:0] bits */
    temp_value &= RCC_RNGCCLK_SYSCLK_DIV_MASK;
    /* Set RNGCPRE[4:0] bits according to RNG_prescaler value */
    temp_value |= RNG_prescaler;

    /* Store the new value */
    RCC->CFG2 = temp_value;
}

/**
*\*\name    RCC_ConfigTrng1mClk.
*\*\fun     Configures the TRNG 1M clock .
*\*\param   TRNG1M_clksrc(TRNG 1M clock source):
*\*\         - RCC_TRNG1MCLK_SRC_HSI
*\*\         - RCC_TRNG1MCLK_SRC_HSE
*\*\param   TRNG1M_prescaler(TRNG 1M clock prescaler):
*\*\         - RCC_TRNG1MCLK_DIV2 
*\*\         - RCC_TRNG1MCLK_DIV4 
*\*\         - RCC_TRNG1MCLK_DIV6 
*\*\         - RCC_TRNG1MCLK_DIV8 
*\*\         - RCC_TRNG1MCLK_DIV10
*\*\         - RCC_TRNG1MCLK_DIV12
*\*\         - RCC_TRNG1MCLK_DIV14
*\*\         - RCC_TRNG1MCLK_DIV16
*\*\         - RCC_TRNG1MCLK_DIV18
*\*\         - RCC_TRNG1MCLK_DIV20
*\*\         - RCC_TRNG1MCLK_DIV22
*\*\         - RCC_TRNG1MCLK_DIV24
*\*\         - RCC_TRNG1MCLK_DIV26
*\*\         - RCC_TRNG1MCLK_DIV28
*\*\         - RCC_TRNG1MCLK_DIV30
*\*\         - RCC_TRNG1MCLK_DIV32
*\*\return  none
**/
void RCC_ConfigTrng1mClk(uint32_t TRNG1M_clksrc, uint32_t TRNG1M_prescaler)
{
    uint32_t temp_value;

    temp_value = RCC->CFG3;
    /* Clear TRNG1MSEL and TRNG1MPRE[3:0] bits */
    temp_value &= RCC_TRNG1MCLK_SRC_MASK;
    temp_value &= RCC_TRNG1MCLK_DIV_MASK;
    /* Set TRNG1MSEL bits according to TRNG1M_clksrc value */
    temp_value |= TRNG1M_clksrc;
    /* Set TRNG1MPRE[3:0] bits according to TRNG1M_prescaler value */
    temp_value |= TRNG1M_prescaler;

    /* Store the new value */
    RCC->CFG3 = temp_value;
}

/**
*\*\name    RCC_EnableTrng1mClk.
*\*\fun     Enables or disable the TRNGCLK.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/
void RCC_EnableTrng1mClk(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->CFG3 |= RCC_TRNG1M_ENABLE;
    }
    else
    {
        RCC->CFG3 &= (~RCC_TRNG1M_ENABLE);
    }
}

/**
*\*\name    RCC_EnableBORReset.
*\*\fun     Enables or disable the BOR reset.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/
void RCC_EnableBORReset(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->CFG3 |= RCC_BOR_ENABLE;
    }
    else
    {
        RCC->CFG3 &= (~RCC_BOR_ENABLE);
    }
}

/**
*\*\name    RCC_EnableSHRTPLLPHAReset.
*\*\fun     Enables or disable the SHRTPLLPHA reset.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/
void RCC_EnableSHRTPLLPHAReset(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->AHBPRST |= RCC_AHB_PERIPHRST_SHRTPLLPHA;
    }
    else
    {
        RCC->AHBPRST &= (~RCC_AHB_PERIPHRST_SHRTPLLPHA);
    }
}

/**
*\*\name    RCC_ConfigFDCANPllClk.
*\*\fun     Configures the FDCAN PLL clock prescaler.
*\*\param   FDCAN_prescaler (specifies the CANCCLK prescaler):
*\*\        - RCC_FDCAN_PLLSRC_DIV1     FDCAN PLL clock source Divided By 1 
*\*\        - RCC_FDCAN_PLLSRC_DIV2     FDCAN PLL clock source Divided By 2 
*\*\        - RCC_FDCAN_PLLSRC_DIV3     FDCAN PLL clock source Divided By 3 
*\*\        - RCC_FDCAN_PLLSRC_DIV4     FDCAN PLL clock source Divided By 4 
*\*\        - RCC_FDCAN_PLLSRC_DIV5     FDCAN PLL clock source Divided By 5 
*\*\        - RCC_FDCAN_PLLSRC_DIV6     FDCAN PLL clock source Divided By 6 
*\*\        - RCC_FDCAN_PLLSRC_DIV7     FDCAN PLL clock source Divided By 7 
*\*\        - RCC_FDCAN_PLLSRC_DIV8     FDCAN PLL clock source Divided By 8 
*\*\        - RCC_FDCAN_PLLSRC_DIV9     FDCAN PLL clock source Divided By 9 
*\*\        - RCC_FDCAN_PLLSRC_DIV10    FDCAN PLL clock source Divided By 10
*\*\        - RCC_FDCAN_PLLSRC_DIV11    FDCAN PLL clock source Divided By 11
*\*\        - RCC_FDCAN_PLLSRC_DIV12    FDCAN PLL clock source Divided By 12
*\*\        - RCC_FDCAN_PLLSRC_DIV13    FDCAN PLL clock source Divided By 13
*\*\        - RCC_FDCAN_PLLSRC_DIV14    FDCAN PLL clock source Divided By 14
*\*\        - RCC_FDCAN_PLLSRC_DIV15    FDCAN PLL clock source Divided By 15
*\*\return  none
**/
void RCC_ConfigFDCANPllClk(uint32_t FDCAN_prescaler)
{
    uint32_t temp_value;

    temp_value = RCC->CFG3;
    /* Clear FDCANPLLPRES[3:0] bits */
    temp_value &= RCC_FDCAN_PLLSRC_DIV_MASK;
    /* Set FDCANPLLPRES[3:0] bits according to FDCAN_prescaler value */
    temp_value |= FDCAN_prescaler;

    /* Store the new value */
    RCC->CFG3 = temp_value;
}

/**
*\*\name    RCC_ConfigFDCANClksrc.
*\*\fun     Configures the FDCAN clock source(CANCLK).
*\*\param   FDCAN_clksrc(FDCAN clock source):
*\*\         - RCC_FDCAN_CLKSRC_PLL    
*\*\         - RCC_FDCAN_CLKSRC_SHRTPLL
*\*\         - RCC_FDCAN_CLKSRC_HSE    
*\*\return  none
*\*\note  The divider needs to be configured first when selecting the PLL or SHRTPLL
**/
void RCC_ConfigFDCANClksrc(uint32_t FDCAN_clksrc)  
{
    uint32_t temp_value;

    temp_value = RCC->CFG3;
    /* Clear FDCANSEL bits */
    temp_value &= RCC_FDCAN_CLKSRC_MASK;
    /* Set FDCANSEL bits according to FDCAN_clksrc value */
    temp_value |= FDCAN_clksrc;

    /* Store the new value */
    RCC->CFG3 = temp_value;
}

/**
*\*\name    RCC_ConfigTraceClk.
*\*\fun     Configures the Trace clock prescaler.
*\*\param   TRACE_prescaler (specifies the prescaler):
*\*\        - RCC_TRACECLK_DIV1     HCLK Divided By 1
*\*\        - RCC_TRACECLK_DIV2     HCLK Divided By 2
*\*\        - RCC_TRACECLK_DIV4     HCLK Divided By 4
*\*\        - RCC_TRACECLK_DIV8     HCLK Divided By 8
*\*\return  none
**/
void RCC_ConfigTraceClk(uint32_t TRACE_prescaler)
{
    uint32_t temp_value;

    temp_value = RCC->CFG3;
    /* Clear TRACEPRES[1:0] bits */
    temp_value &= RCC_TRACECLK_DIV_MASK;
    /* Set TRACEPRES[1:0] bits according to TRACE_prescaler value */
    temp_value |= TRACE_prescaler;

    /* Store the new value */
    RCC->CFG3 = temp_value;
}

/**
*\*\name    RCC_ConfigUSBPLLPresClk.
*\*\fun     Configures the USB PLL clock (USBPLLCLK).
*\*\param   USBPLL_clksrc(USBPLL clock source):
*\*\         - RCC_USBPLLCLK_SRC_PLL
*\*\         - RCC_USBPLLCLK_SRC_SHRTPLL
*\*\param   USBPLL_prescaler(USBPLL clock prescaler):
*\*\         - RCC_USBPLLCLK_DIV1 
*\*\         - RCC_USBPLLCLK_DIV2 
*\*\         - RCC_USBPLLCLK_DIV3 
*\*\         - RCC_USBPLLCLK_DIV4 
*\*\         - RCC_USBPLLCLK_DIV5 
*\*\         - RCC_USBPLLCLK_DIV6 
*\*\         - RCC_USBPLLCLK_DIV7 
*\*\         - RCC_USBPLLCLK_DIV8 
*\*\         - RCC_USBPLLCLK_DIV9 
*\*\         - RCC_USBPLLCLK_DIV10
*\*\         - RCC_USBPLLCLK_DIV11
*\*\         - RCC_USBPLLCLK_DIV12
*\*\         - RCC_USBPLLCLK_DIV13
*\*\         - RCC_USBPLLCLK_DIV14
*\*\         - RCC_USBPLLCLK_DIV15
*\*\return  none
**/
void RCC_ConfigUSBPLLPresClk(uint32_t USBPLL_clksrc, uint32_t USBPLL_prescaler)
{
    uint32_t temp_value;

    temp_value = RCC->CFG3;
    /* Clear USBPLLSEL and USBPLLPRE[4:0] bits */
    temp_value &= RCC_USBPLLCLK_SRC_MASK;
    temp_value &= RCC_USBPLLCLK_DIV_MASK;
    /* Set USBPLLSEL bits according to USBPLL_clksrc value */
    temp_value |= USBPLL_clksrc;
    /* Set USBPLLPRE[4:0] bits according to USBPLL_prescaler value */
    temp_value |= USBPLL_prescaler;

    /* Store the new value */
    RCC->CFG3 = temp_value;
}

/**
*\*\name    RCC_ConfigUSBFSClk_.
*\*\fun     Configures the USBFS clock source(USBFSCLK).
*\*\param   USBFS_clksrc(USBFS clock source):
*\*\         - RCC_USBFS_CLKSRC_UCDR     
*\*\         - RCC_USBFS_CLKSRC_PLLPRES  
*\*\         - RCC_USBFS_CLKSRC_USBHS48M
*\*\return  none
*\*\note  The PLL clock source and prescaler are first configured 
*\*\      by RCC_ConfigUSBPLLPresClk() function when selecting the RCC_USBFS_CLKSRC_PLLPRES.
**/
void RCC_ConfigUSBFSClk(uint32_t USBFS_clksrc)  
{
    uint32_t temp_value;

    temp_value = RCC->CFG3;
    /* Clear USBFSSEL bits */
    temp_value &= RCC_USBFS_CLKSRC_MASK;
    /* Set USBFSSEL bits according to USBFS_clksrc value */
    temp_value |= USBFS_clksrc;

    /* Store the new value */
    RCC->CFG3 = temp_value;
}

/**
*\*\name    RCC_ConfigUSBHSClk_.
*\*\fun     Configures the USBHS clock source(USBHSCLK).
*\*\param   USBHS_clksrc(USBHS clock source):
*\*\         - RCC_USBHS_CLKSRC_HSE     
*\*\         - RCC_USBHS_CLKSRC_PLLPRES 
*\*\return  none
*\*\note  The PLL clock source and prescaler are first configured 
*\*\      by RCC_ConfigUSBPLLPresClk() function when selecting the RCC_USBHS_CLKSRC_PLLPRES.
*\*\note  The input clock frequency must be ensured to be 16M/19.2M/20M/24M/26M/32M.
**/
void RCC_ConfigUSBHSClk(uint32_t USBHS_clksrc)  
{
    uint32_t temp_value;

    temp_value = RCC->USBHSCTRL1;
    /* Clear USBHSSEL bits */
    temp_value &= RCC_USBHS_CLKSRC_MASK;
    /* Set USBHSSEL bits according to USBHS_clksrc value */
    temp_value |= USBHS_clksrc;

    /* Store the new value */
    RCC->USBHSCTRL1 = temp_value;
}

/**
*\*\name    RCC_ConfigUSBHSClk_.
*\*\fun     Configures the USBHS clock source(USBHSCLK).
*\*\param   USBHS_bw(USBHS band width):
*\*\         - RCC_USBHS_BW_16M    Select this bit when input clock frequency is 16M     
*\*\         - RCC_USBHS_BW_OTHER  Select this bit when input clock frequency is 19.2M/20M/24M/26M/32M
*\*\return  none
*\*\note    none 
*\*\      
**/
void RCC_ConfigUSBHSBandwidth(uint32_t USBHS_bw)  
{
    uint32_t temp_value;

    temp_value = RCC->USBHSCTRL1;
    /* Clear USBHSSEL bits */
    temp_value &= RCC_USBHS_BW_MASK;
    /* Set USBHSSEL bits according to USBHS_clksrc value */
    temp_value |= USBHS_bw;

    /* Store the new value */
    RCC->USBHSCTRL1 = temp_value;
}

/**
*\*\name    RCC_ConfigUSBHSFrequency.
*\*\fun     Configures the USBHS clock source(USBHSCLK).
*\*\param   USBHS_bw(USBHS band width):
*\*\         - RCC_USBHS_FREQ_19_2M      Select this bit when input clock frequency is 19.2M     
*\*\         - RCC_USBHS_FREQ_20M        Select this bit when input clock frequency is 20M
*\*\         - RCC_USBHS_FREQ_24M        Select this bit when input clock frequency is 24M
*\*\         - RCC_USBHS_FREQ_16_OR_32M  Select this bit when input clock frequency is16 or 32M
*\*\         - RCC_USBHS_FREQ_26M        Select this bit when input clock frequency is 26M
*\*\return  none
*\*\note    none
*\*\      
**/
void RCC_ConfigUSBHSFrequency(uint32_t USBHS_freq)  
{
    uint32_t temp_value;

    temp_value = RCC->USBHSCTRL1;
    /* Clear USBHSSEL bits */
    temp_value &= RCC_USBHS_FREQ_MASK;
    /* Set USBHSSEL bits according to USBHS_clksrc value */
    temp_value |= USBHS_freq;

    /* Store the new value */
    RCC->USBHSCTRL1 = temp_value;
}

/**
*\*\name    RCC_ConfigAdc1mClk.
*\*\fun     Configures the ADCx 1M clock (ADC1MCLK).
*\*\param   ADC1M_clksrc(ADC1M clock source):
*\*\         - RCC_ADC1MCLK_SRC_HSI
*\*\         - RCC_ADC1MCLK_SRC_HSE
*\*\param   ADC1M_prescaler(ADC1M clock prescaler):
*\*\         - RCC_ADC1MCLK_DIV1 
*\*\         - RCC_ADC1MCLK_DIV2 
*\*\         - RCC_ADC1MCLK_DIV3 
*\*\         - RCC_ADC1MCLK_DIV4 
*\*\         - RCC_ADC1MCLK_DIV5 
*\*\         - RCC_ADC1MCLK_DIV6 
*\*\         - RCC_ADC1MCLK_DIV7 
*\*\         - RCC_ADC1MCLK_DIV8 
*\*\         - RCC_ADC1MCLK_DIV9 
*\*\         - RCC_ADC1MCLK_DIV10
*\*\         - RCC_ADC1MCLK_DIV11
*\*\         - RCC_ADC1MCLK_DIV12
*\*\         - RCC_ADC1MCLK_DIV13
*\*\         - RCC_ADC1MCLK_DIV14
*\*\         - RCC_ADC1MCLK_DIV15
*\*\         - RCC_ADC1MCLK_DIV16
*\*\         - RCC_ADC1MCLK_DIV17
*\*\         - RCC_ADC1MCLK_DIV18
*\*\         - RCC_ADC1MCLK_DIV19
*\*\         - RCC_ADC1MCLK_DIV20
*\*\         - RCC_ADC1MCLK_DIV21
*\*\         - RCC_ADC1MCLK_DIV22
*\*\         - RCC_ADC1MCLK_DIV23
*\*\         - RCC_ADC1MCLK_DIV24
*\*\         - RCC_ADC1MCLK_DIV25
*\*\         - RCC_ADC1MCLK_DIV26
*\*\         - RCC_ADC1MCLK_DIV27
*\*\         - RCC_ADC1MCLK_DIV28
*\*\         - RCC_ADC1MCLK_DIV29
*\*\         - RCC_ADC1MCLK_DIV30
*\*\         - RCC_ADC1MCLK_DIV31
*\*\         - RCC_ADC1MCLK_DIV32
*\*\return  none
**/
void RCC_ConfigAdc1mClk(uint32_t ADC1M_clksrc, uint32_t ADC1M_prescaler)
{
    uint32_t temp_value;

    temp_value = RCC->CFG2;
    /* Clear ADC1MSEL and ADC1MPRE[4:0] bits */
    temp_value &= RCC_ADC1MCLK_SRC_MASK;
    temp_value &= RCC_ADC1MCLK_DIV_MASK;
    /* Set ADC1MSEL bits according to ADC1M_clksrc value */
    temp_value |= ADC1M_clksrc;
    /* Set ADC1MPRE[4:0] bits according to ADC1M_prescaler value */
    temp_value |= ADC1M_prescaler;

    /* Store the new value */
    RCC->CFG2 = temp_value;
}

/**
*\*\name    RCC_ConfigAdcPllClk.
*\*\fun     Configures the ADC clock source(ADCCLK).
*\*\param   ADC_PLLsource(ADC PLL clock source):
*\*\         - RCC_ADCPLLCLK_SRC_PLL       
*\*\         - RCC_ADCPLLCLK_SRC_USBHS240M
*\*\param   ADC_PLLprescaler(ADC PLLCLK prescaler):
*\*\         - RCC_ADCPLLCLK_DIV1 
*\*\         - RCC_ADCPLLCLK_DIV2 
*\*\         - RCC_ADCPLLCLK_DIV3 
*\*\         - RCC_ADCPLLCLK_DIV4 
*\*\         - RCC_ADCPLLCLK_DIV6 
*\*\         - RCC_ADCPLLCLK_DIV8 
*\*\         - RCC_ADCPLLCLK_DIV10
*\*\         - RCC_ADCPLLCLK_DIV12
*\*\param   ADC_PLLenable: 
*\*\          - RCC_ADCPLLCLK_DISABLE  
*\*\          - RCC_ADCPLLCLK_ENABLE 
*\*\return  none
**/
void RCC_ConfigAdcPllClk(uint32_t ADC_PLLsource, uint32_t ADC_PLLprescaler, uint32_t ADC_PLLenable)
{
    uint32_t temp_value;

    temp_value = RCC->CFG2;

    /* Clear ADCOTGPLLPRES[2:0], ADCOTGPLLSEL, ADCOTGPLLEN bits */
    temp_value &= RCC_ADCPLLCLK_MASK;
    /* Set ADCOTGPLLPRES[2:0], ADCOTGPLLSEL, ADCOTGPLLEN bits*/
    temp_value |= (ADC_PLLsource | ADC_PLLprescaler | ADC_PLLenable);

    /* Store the new value */
    RCC->CFG2 = temp_value;

}


/**
*\*\name    RCC_ConfigAdcHclk.
*\*\fun     Configures the ADCHCLK prescaler.
*\*\param   ADC_hclk_prescaler(ADCHCLK prescaler):
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
*\*\return  none
**/
void RCC_ConfigAdcHclk(uint32_t ADC_hclk_prescaler)
{
    uint32_t temp_value;

    temp_value = RCC->CFG2;
    /* Clear ADCHPRE[3:0] bits */
    temp_value &= RCC_ADCHCLK_DIV_MASK;
    /* Set ADCHPRE[3:0] bits according to ADC_hclk_prescaler value */
    temp_value |= ADC_hclk_prescaler;

    /* Store the new value */
    RCC->CFG2 = temp_value;
}


/**
*\*\name    RCC_EnableLsi.
*\*\fun     Enables the Internal Low Speed oscillator (LSI).
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/
void RCC_EnableLsi(FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        /* Set LSIEN bit */
        RCC->CTRLSTS |= RCC_LSI_ENABLE;
    }
    else
    {
        /* Reset PLLEN bit */
        RCC->CTRLSTS &= (~RCC_LSI_ENABLE);
    }
     
}

/**
*\*\name    RCC_WaitLsiStable.
*\*\fun     Waits for LSI start-up.
*\*\param   none
*\*\return  ErrorStatus:
 *\*\         - SUCCESS    LSI oscillator is stable and ready to use
 *\*\         - ERROR      LSI oscillator not yet ready
**/
ErrorStatus RCC_WaitLsiStable(void)
{
    __IO uint32_t counter_value = 0;
    uint32_t timeout_value;   
    FlagStatus status_value;
	RCC_ClocksType sysclk_value;
    ErrorStatus bitstatus;

	RCC_GetClocksFreqValue(&sysclk_value);
	timeout_value = (LSI_STARTUP_TIMEOUT/((uint32_t)240000000/sysclk_value.SysclkFreq));

    /* Wait till LSI is ready and if Time out is reached exit */
    do
    {
        status_value = RCC_GetFlagStatus(RCC_FLAG_LSIRDF);
        counter_value++;
    } while ((counter_value != timeout_value) && (status_value == RESET));
    
    if (RCC_GetFlagStatus(RCC_FLAG_LSIRDF) != RESET)
    {
        bitstatus = SUCCESS;
    }
    else
    {
        bitstatus = ERROR;
    }
    return bitstatus;
}

/**
*\*\name    RCC_ConfigLse.
*\*\fun     Configures the External High Speed oscillator (LSE).
*\*\param   RCC_LSE :
*\*\          - RCC_LSE_DISABLE    LSE oscillator OFF 
*\*\          - RCC_LSE_ENABLE     LSE oscillator ON
*\*\          - RCC_LSE_BYPASS     LSE oscillator bypassed with external clock
*\*\return  none:
*\*\note BDCTRL is protected, you need to enable the PWR clock first, 
*\*\     then configure PWR_CTRL.DBKP to 1 to change it.   
**/
void RCC_ConfigLse(uint32_t RCC_LSE)
{
    uint32_t temp_value;
    
    temp_value = RCC->BDCTRL;
    /* Reset LSEEN bit */
    temp_value &= (~RCC_LSE_ENABLE);
    /* Reset LSEBP bit */
    temp_value &= (~RCC_LSE_BYPASS);
    /* Configure LSE (RC_LSE_DISABLE is already covered by the code section above) */
    if(RCC_LSE == RCC_LSE_ENABLE)
    {
        /* Set LSEEN bit */
        temp_value |= RCC_LSE_ENABLE;
    }   
    else if (RCC_LSE == RCC_LSE_BYPASS)
    {
        /* Set LSEBP and LSEEN bits */
        temp_value |= RCC_LSE_BYPASS | RCC_LSE_ENABLE;
    }
    else
    {
        /* No process */
    }

    RCC->BDCTRL = temp_value;

}

/**
*\*\name    RCC_EnableLSEClockSecuritySystem.
*\*\fun     Enables the LSE Clock Security System.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE     
*\*\return  none
*\*\note BDCTRL is protected, you need to enable the PWR clock first, 
*\*\     then configure PWR_CTRL.DBKP to 1 to change it.
**/
void RCC_EnableLSEClockSecuritySystem(FunctionalState Cmd)
{
     if (Cmd != DISABLE)
    {
        RCC->BDCTRL |= RCC_LSECSS_ENABLE;
    }
    else
    {
        RCC->BDCTRL &= (~RCC_LSECSS_ENABLE);
    }
}


/**
*\*\name    RCC_WaitLseStable.
*\*\fun     Waits for LSE start-up.
*\*\param   none
*\*\return  ErrorStatus:
 *\*\         - SUCCESS    LSE oscillator is stable and ready to use
 *\*\         - ERROR      LSE oscillator not yet ready
**/
ErrorStatus RCC_WaitLseStable(void)
{
    __IO uint32_t counter_value = 0;
    uint32_t timeout_value;   
    FlagStatus status_value;
	RCC_ClocksType sysclk_value;
    ErrorStatus bitstatus;
    

	RCC_GetClocksFreqValue(&sysclk_value);
	timeout_value = (LSE_STARTUP_TIMEOUT/((uint32_t)64000000/sysclk_value.SysclkFreq));

    /* Wait till LSE is ready and if Time out is reached exit */
    do
    {
        status_value = RCC_GetFlagStatus(RCC_FLAG_LSERDF);
        counter_value++;
    } while ((counter_value != timeout_value) && (status_value == RESET));
    
    if (RCC_GetFlagStatus(RCC_FLAG_LSERDF) != RESET)
    {
        bitstatus = SUCCESS;
    }
    else
    {
        bitstatus = ERROR;
    }
    return bitstatus;
}


/**
*\*\name    RCC_ConfigRtcClk.
*\*\fun     Configures the RTC clock (RTCCLK).
*\*\param   rtcclk_source(the RTC clock source):
*\*\         - RCC_RTCCLK_SRC_LSE           LSE selected as RTC clock
*\*\         - RCC_RTCCLK_SRC_LSI           LSI selected as RTC clock
*\*\         - RCC_RTCCLK_SRC_HSE_DIV128    HSE clock divided by 128 selected as RTC clock
*\*\return  none
*\*\note    Once the RTC clock is selected it can't be changed unless the Backup domain is reset.
*\*\note    BDCTRL is protected, you need to enable the PWR clock first, 
*\*\       then configure PWR_CTRL.DBKP to 1 to change it.
**/
void RCC_ConfigRtcClk(uint32_t rtcclk_source)
{
    uint32_t temp_value;

    temp_value = RCC->BDCTRL;

    /* Clear the RTC clock source */
    temp_value &= RCC_RTCCLK_SRC_MASK;
    /* Select the RTC clock source */
    temp_value |= rtcclk_source;

    RCC->BDCTRL = temp_value;
}

/**
*\*\name    RCC_EnableRtcClk.
*\*\fun     Enables the RTC clock.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
*\*\note    This function must be used only after the RTC clock was selected 
*\*\        using the RCC_ConfigRtcClk function.
*\*\note    BDCTRL is protected, you need to enable the PWR clock first, 
*\*\        then configure PWR_CTRL.DBKP to 1 to change it.
**/
void RCC_EnableRtcClk(FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        RCC->BDCTRL |= RCC_RTC_ENABLE;
    }
    else
    {
        RCC->BDCTRL &= (~RCC_RTC_ENABLE);
    }
}

/**
*\*\name  RCC_ConfigLPTIM1Clk.
*\*\fun   Configures the LPTIM1 clock (LPTIMCLK).
*\*\param clock_source  (specifies the LPTIM1 clock source).
*\*\     - RCC_LPTIMCLK_SRC_LSI   LSI selected as LPTIM1 clock
*\*\     - RCC_LPTIMCLK_SRC_LSE   LSE selected as LPTIM1 clock
*\*\     - RCC_LPTIMCLK_SRC_HSI   HSI selected as LPTIM1 clock
*\*\     - RCC_LPTIMCLK_SRC_HSE   HSE selected as LPTIM1 clock
*\*\     - RCC_LPTIMCLK_SRC_PCLK1 PLCK1 clock selected as LPTIM1 clock
*\*\return  none
*\*\note BDCTRL is protected, you need to enable the PWR clock first, 
*\*\     then configure PWR_CTRL.DBKP to 1 to change it.
**/
void RCC_ConfigLPTIM1Clk(uint32_t clock_source)
{
    uint32_t temp_value;

    temp_value = RCC->BDCTRL;

    /* Clear the LPTIM1 clock source */
    temp_value &= RCC_LPTIM1CLK_SRC_MASK;
    
    if((clock_source == RCC_LPTIMCLK_SRC_LSI)||(clock_source == RCC_LPTIMCLK_SRC_LSE))
    {
        if (((DBG->ID & 0x000000FFU) > 0x10 ) && ((DBG->ID & 0x000000FFU) != 0xFF)) /* B version chip */
        {
            /* Select the LPTIM1 clock source */
            temp_value |= clock_source;
        }
        else /* A version chip */
        {
            /* Select the LPTIM1 clock source */
            temp_value |= (clock_source - 0x00600000U);
        }
    }
    else
    {
        /* Select the LPTIM1 clock source */
            temp_value |= clock_source;
    }

    RCC->BDCTRL = temp_value;
}

/**
*\*\name  RCC_ConfigLPTIM2Clk.
*\*\fun   Configures the LPTIM2 clock (LPTIMCLK).
*\*\param clock_source  (specifies the LPTIM2 clock source).
*\*\     - RCC_LPTIMCLK_SRC_LSI   LSI selected as LPTIM2 clock
*\*\     - RCC_LPTIMCLK_SRC_LSE   LSE selected as LPTIM2 clock
*\*\     - RCC_LPTIMCLK_SRC_HSI   HSI selected as LPTIM2 clock
*\*\     - RCC_LPTIMCLK_SRC_HSE   HSE selected as LPTIM2 clock
*\*\     - RCC_LPTIMCLK_SRC_PCLK1 PLCK1 clock selected as LPTIM2 clock
*\*\return  none
*\*\note BDCTRL is protected, you need to enable the PWR clock first, 
*\*\     then configure PWR_CTRL.DBKP to 1 to change it.
**/
void RCC_ConfigLPTIM2Clk(uint32_t clock_source)
{
    uint32_t temp_value;

    temp_value = RCC->BDCTRL;

    /* Clear the LPTIM2 clock source */
    temp_value &= RCC_LPTIM2CLK_SRC_MASK;

    if((clock_source == RCC_LPTIMCLK_SRC_LSI)||(clock_source == RCC_LPTIMCLK_SRC_LSE))
    {
        if (((DBG->ID & 0x000000FFU) > 0x10 ) && ((DBG->ID & 0x000000FFU) != 0xFF)) /* B version chip */
        {
            /* Select the LPTIM2 clock source */
            temp_value |= (clock_source << 4);
        }
        else /* A version chip */
        {
            /* Select the LPTIM2 clock source */
            temp_value |= ((clock_source - 0x00600000U) << 4);
        }
    }
    else
    {
        /* Select the LPTIM2 clock source */
    temp_value |= (clock_source << 4);
    }
    

    RCC->BDCTRL = temp_value;
}

/**
*\*\name    RCC_EnableLPTIMPeriphClk.
*\*\fun     Enables the LPTIM1 and LPTIM2 clock.
*\*\param   LPTIM_periph (LPTIM peripheral to gates its clock):
*\*\        - RCC_LPTIM1_PERIPH_EN     
*\*\        - RCC_LPTIM2_PERIPH_EN    
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE       
*\*\return none. 
*\*\note    BDCTRL is protected, you need to enable the PWR clock first, 
*\*\        then configure PWR_CTRL.DBKP to 1 to change it.
**/
void RCC_EnableLPTIMPeriphClk(uint32_t LPTIM_periph, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->BDCTRL |= LPTIM_periph;
    }
    else
    {
        RCC->BDCTRL &= ~LPTIM_periph;
    }
    
}

/**
*\*\name    RCC_EnableLPTIMPeriphReset.
*\*\fun     LPTIM1 and LPTIM2 clock reset.
*\*\param   LPTIM_periph specifies the LPTIM peripheral to reset.
*\*\        - RCC_LPTIM1_PERIPH_RST     
*\*\        - RCC_LPTIM2_PERIPH_RST    
*\*\return none. 
*\*\note    BDCTRL is protected, you need to enable the PWR clock first, 
*\*\        then configure PWR_CTRL.DBKP to 1 to change it.
**/
void RCC_EnableLPTIMPeriphReset(uint32_t LPTIM_periph)
{
    RCC->BDCTRL |= LPTIM_periph;
    RCC->BDCTRL &= ~LPTIM_periph;
}


/**
*\*\name    RCC_EnableBackupReset.
*\*\fun     Reset Backup domain .
*\*\param   none  
*\*\return  none. 
*\*\note    BDCTRL is protected, you need to enable the PWR clock first, 
*\*\        then configure PWR_CTRL.DBKP to 1 to change it.
**/
void RCC_EnableBackupReset(void)
{ 
    RCC->BDCTRL |= (RCC_BKUP_RESET);
    RCC->BDCTRL &= (~RCC_BKUP_RESET);
}

/**
*\*\name    RCC_GetClocksFreqValue.
*\*\fun     Returns the frequencies of different on chip clocks.
*\*\param   RCC_clocks pointer to a RCC_ClocksType structure which will hold
*\*\        the clocks frequencies.
*\*\return  none
*\*\note    The result of this function could be not correct when using
*\*\        fractional value for HSE crystal.  
**/
void RCC_GetClocksFreqValue(RCC_ClocksType* RCC_clocks)
{
    uint32_t temp, pllclk, pllmull, pllpre, plloutdiv, pllsource, presc;
    FlagStatus pllsel = RESET;
    const uint8_t ApbAhbPresTable[16]    = {0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9};
    const uint8_t AdcHclkPresTable[16]   = {1, 2, 3, 4, 6, 8, 10, 12, 16, 32, 32, 32, 32, 32, 32, 32};
    const uint16_t AdcPllClkPresTable[8] = {1, 2, 3, 4, 6, 8, 10, 12};

    /* Get SHRTPLL clock source, multiplier, divider*/
    pllmull   = (RCC->SHRTPLLCTRL1 & RCC_SHRTPLLCTRL1_CLKF);
    pllpre    = ((RCC->SHRTPLLCTRL2 & RCC_SHRTPLLCTRL2_CLKR)>>26);
    pllsource = ((RCC->SHRTPLLCTRL3 & RCC_SHRTPLLCTRL3_SHRTPLLSRC)>>26);

    if (pllsource == 0x00)
    { 
        /* HSI selected as PLL clock entry */
        pllclk = (uint32_t)(((uint64_t)HSI_VALUE * (pllmull >> 14)) / (pllpre + 1) / 4);
    }
    else
    {
        /* HSE selected as PLL clock entry */
        pllclk = (uint32_t)(((uint64_t)HSE_VALUE * (pllmull >> 14)) / (pllpre + 1) / 4);
    }
    RCC_clocks->ShrtpllFreq = pllclk;

    /* Get SYSCLK source -------------------------------------------------------*/
    temp = RCC->CFG & RCC_CFG_SCLKSTS;

    if(temp == RCC_CFG_SCLKSTS_HSE)
    {
        /* HSE used as system clock */
        RCC_clocks->SysclkFreq = HSE_VALUE;
    }
    else if(temp == RCC_CFG_SCLKSTS_HSI)
    {
        /* HSI used as system clock */
        RCC_clocks->SysclkFreq = HSI_VALUE;
    }
    else if(temp == RCC_CFG_SCLKSTS_PLL)
    {
        if((RCC->PLLCTRL & RCC_PLLCTRL_SCLKPLLSEL) == RCC_PLLCTRL_SCLKPLLSEL_SHRTPLL)
        {
            /* SHRTPLL used as system clock */
            RCC_clocks->SysclkFreq = pllclk;
        }
        else if((RCC->PLLCTRL & RCC_PLLCTRL_SCLKPLLSEL) == RCC_PLLCTRL_SCLKPLLSEL_USBHS240M)
        {
            /* USBHS240M used as system clock */
            RCC_clocks->SysclkFreq = 240000000;
        }
        else
        {
            /* PLL used as system clock */
            pllsel = SET;
        }
    }
    else
    {
        /* HSI used as system clock */
        RCC_clocks->SysclkFreq = HSI_VALUE;
    }
    
    if(pllsel == SET)
    {  
        /* Get PLL clock source, PLL Pre-Divider, PLL out div and multiplication factor ----------------------*/
        pllmull   = (((RCC->CFG & RCC_CFG_PLLMULFCT) >> 3) * 2) + 4;
        pllpre    = ((RCC->PLLCTRL & RCC_PLLCTRL_PLLINPRES) >> 16) + 1;
        plloutdiv = ((RCC->PLLCTRL & RCC_PLLCTRL_PLLOUTPRES) >> 18);
        pllsource = RCC->CFG & RCC_CFG_PLLSRC;

        if (pllsource == 0x00)
        { 
            /* HSI selected as PLL clock entry */
            pllclk = HSI_VALUE >> ((RCC->CFG & RCC_CFG_PLLHSIPRES) >> 2);
        }
        else
        {
            /* HSE selected as PLL clock entry */
            pllclk = HSE_VALUE >> ((RCC->CFG & RCC_CFG_PLLHSEPRES) >> 1);
        }
        
        pllclk = (pllclk / pllpre * pllmull) >> plloutdiv;
    
    
        /* PLL used as system clock */
        RCC_clocks->SysclkFreq = pllclk;
    }
    
    /* Compute HCLK, PCLK1, PCLK2 and ADCCLK clocks frequencies ----------------*/
    /* Get HCLK prescaler */
    temp   = RCC->CFG & RCC_CFG_AHBPRES;
    temp   = temp >> 16;
    if(temp < 0x8)
    {
        temp = 0;
    }
    presc = ApbAhbPresTable[temp];
    /* HCLK clock frequency */
    RCC_clocks->HclkFreq = RCC_clocks->SysclkFreq >> presc;
    /* Get PCLK1 prescaler */
    temp   = RCC->CFG & RCC_CFG_APB1PRES;
    temp   = temp >> 9;
    presc = ApbAhbPresTable[temp];
    /* PCLK1 clock frequency */
    RCC_clocks->Pclk1Freq = RCC_clocks->HclkFreq >> presc;
    /* Get PCLK2 prescaler */
    temp   = RCC->CFG & RCC_CFG_APB2PRES;
    temp   = temp >> 12;
    presc = ApbAhbPresTable[temp];
    /* PCLK2 clock frequency */
    RCC_clocks->Pclk2Freq = RCC_clocks->HclkFreq >> presc;

    /* Get ADCHCLK prescaler */
    temp   = RCC->CFG2 & RCC_CFG2_ADCHPRES;
    presc = AdcHclkPresTable[temp];
    /* ADCHCLK clock frequency */
    RCC_clocks->AdcHclkFreq = RCC_clocks->HclkFreq / presc;
    /* Get ADCPLLCLK prescaler */
    temp   = RCC->CFG2 & RCC_CFG2_ADCOTGPLLPRES;
    temp   = temp >> 4;
    presc = AdcPllClkPresTable[temp]; 
    /* ADCPLLCLK clock frequency */
    if((RCC->CFG2 & RCC_CFG2_ADCOTGPLLSEL) == RCC_CFG2_ADCOTGPLLSEL)
    {
         /* USBHS 240M selected as ADC PLL clock entry */
        RCC_clocks->AdcPllClkFreq = 240000000 / presc;
    }
    else
    {
         /* PLL selected as ADC PLL clock entry */
        RCC_clocks->AdcPllClkFreq = pllclk / presc;
    }
    
}

/**
*\*\name    RCC_EnableFDCANOffRequest.
*\*\fun     Sending a off request to the FDCAN module when enabled.
*\*\param   FDCAN_sel :
*\*\        -RCC_OFFEN_FDCAN1
*\*\        -RCC_OFFEN_FDCAN2
*\*\        -RCC_OFFEN_FDCAN3
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE    
*\*\return  none
*\*\note    Hardware clears this bit after receiving a shutdown answer from the CAN module
**/
void RCC_EnableFDCANOffRequest(uint32_t FDCAN_sel, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->APB1PCLKEN |= FDCAN_sel;
    }
    else
    {
        RCC->APB1PCLKEN &= ~FDCAN_sel;
    }
    
}

/**
*\*\name    RCC_EnableAHBPeriphClk.
*\*\fun     Enables the AHB peripheral clock.
*\*\param   AHB_periph (AHB peripheral to gates its clock):
*\*\        - RCC_AHB_PERIPHEN_SHRTIM    
*\*\        - RCC_AHB_PERIPHEN_ATIM3   
*\*\        - RCC_AHB_PERIPHEN_ATIM2   
*\*\        - RCC_AHB_PERIPHEN_ATIM1     
*\*\        - RCC_AHB_PERIPHEN_DVP       
*\*\        - RCC_AHB_PERIPHEN_CORDIC   
*\*\        - RCC_AHB_PERIPHEN_FMAC      
*\*\        - RCC_AHB_PERIPHEN_USBHS   
*\*\        - RCC_AHB_PERIPHEN_ETH     
*\*\        - RCC_AHB_PERIPHEN_CRC       
*\*\        - RCC_AHB_PERIPHEN_DMA2      
*\*\        - RCC_AHB_PERIPHEN_DMA1    
*\*\        - RCC_AHB_PERIPHEN_SDIO      
*\*\        - RCC_AHB_PERIPHEN_XSPI     
*\*\        - RCC_AHB_PERIPHEN_RNGC    
*\*\        - RCC_AHB_PERIPHEN_BKPSRAM   
*\*\        - RCC_AHB_PERIPHEN_FEMC      
*\*\        - RCC_AHB_PERIPHEN_FLITF   
*\*\        - RCC_AHB_PERIPHEN_SRAM    
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE    
*\*\return  none
**/
void RCC_EnableAHBPeriphClk(uint32_t AHB_periph, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->AHBPCLKEN |= AHB_periph;
    }
    else
    {
        RCC->AHBPCLKEN &= ~AHB_periph;
    }
    
}

/**
*\*\name    RCC_EnableAHB1PeriphClk.
*\*\fun     Enables the AHB peripheral clock.
*\*\param   AHB_periph (AHB peripheral to gates its clock):
*\*\        -RCC_AHB_PERIPHEN_SAC  
*\*\        -RCC_AHB_PERIPHEN_DAC78 
*\*\        -RCC_AHB_PERIPHEN_DAC56 
*\*\        -RCC_AHB_PERIPHEN_ADC4 
*\*\        -RCC_AHB_PERIPHEN_ADC3 
*\*\        -RCC_AHB_PERIPHEN_ADC2 
*\*\        -RCC_AHB_PERIPHEN_ADC1 
*\*\        -RCC_AHB_PERIPHEN_GPIOH
*\*\        -RCC_AHB_PERIPHEN_GPIOG
*\*\        -RCC_AHB_PERIPHEN_GPIOF
*\*\        -RCC_AHB_PERIPHEN_GPIOE
*\*\        -RCC_AHB_PERIPHEN_GPIOD
*\*\        -RCC_AHB_PERIPHEN_GPIOC
*\*\        -RCC_AHB_PERIPHEN_GPIOB
*\*\        -RCC_AHB_PERIPHEN_GPIOA
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE    
*\*\return  none
**/
void RCC_EnableAHB1PeriphClk(uint32_t AHB_periph, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->AHB1PCLKEN |= AHB_periph;
    }
    else
    {
        RCC->AHB1PCLKEN &= ~AHB_periph;
    }
    
}

/**
*\*\name    RCC_EnableAPB2PeriphClk.
*\*\fun     Enables the High Speed APB (APB2) peripheral clock.
*\*\param   APB2_periph (APB2 peripheral to gates its clock):
*\*\        - RCC_APB2_PERIPH_USART4  
*\*\        - RCC_APB2_PERIPH_COMPFILT 
*\*\        - RCC_APB2_PERIPH_PGA      
*\*\        - RCC_APB2_PERIPH_COMP     
*\*\        - RCC_APB2_PERIPH_GTIM10   
*\*\        - RCC_APB2_PERIPH_GTIM9   
*\*\        - RCC_APB2_PERIPH_GTIM8   
*\*\        - RCC_APB2_PERIPH_UART7   
*\*\        - RCC_APB2_PERIPH_UART6   
*\*\        - RCC_APB2_PERIPH_USART1  
*\*\        - RCC_APB2_PERIPH_SPI1    
*\*\        - RCC_APB2_PERIPH_SPI4    
*\*\        - RCC_APB2_PERIPH_SPI5    
*\*\        - RCC_APB2_PERIPH_SPI6    
*\*\        - RCC_APB2_PERIPH_AFIO    
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return none. 
**/
void RCC_EnableAPB2PeriphClk(uint32_t APB2_periph, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->APB2PCLKEN |= APB2_periph;
    }
    else
    {
        RCC->APB2PCLKEN &= ~APB2_periph;
    }
    
}


/**
*\*\name    RCC_EnableAPB1PeriphClk.
*\*\fun     Enables the High Speed APB (APB1) peripheral clock.
*\*\param   APB1_periph (APB1 peripheral to gates its clock):
*\*\        - RCC_APB1_PERIPH_DAC34       
*\*\        - RCC_APB1_PERIPH_DAC12       
*\*\        - RCC_APB1_PERIPH_WWDG       
*\*\        - RCC_APB1_PERIPH_I2C4   
*\*\        - RCC_APB1_PERIPH_I2C3       
*\*\        - RCC_APB1_PERIPH_BTIM2     
*\*\        - RCC_APB1_PERIPH_BTIM1    
*\*\        - RCC_APB1_PERIPH_FDCAN3      
*\*\        - RCC_APB1_PERIPH_FDCAN2      
*\*\        - RCC_APB1_PERIPH_FDCAN1       
*\*\        - RCC_APB1_PERIPH_USBFS      
*\*\        - RCC_APB1_PERIPH_UCDR       
*\*\        - RCC_APB1_PERIPH_GTIM7      
*\*\        - RCC_APB1_PERIPH_GTIM6   
*\*\        - RCC_APB1_PERIPH_GTIM5      
*\*\        - RCC_APB1_PERIPH_GTIM4      
*\*\        - RCC_APB1_PERIPH_GTIM3      
*\*\        - RCC_APB1_PERIPH_GTIM2  
*\*\        - RCC_APB1_PERIPH_GTIM1      
*\*\        - RCC_APB1_PERIPH_SPI3      
*\*\        - RCC_APB1_PERIPH_SPI2      
*\*\        - RCC_APB1_PERIPH_I2C2      
*\*\        - RCC_APB1_PERIPH_I2C1      
*\*\        - RCC_APB1_PERIPH_UART5      
*\*\        - RCC_APB1_PERIPH_UART8      
*\*\        - RCC_APB1_PERIPH_USART3     
*\*\        - RCC_APB1_PERIPH_USART2     
*\*\        - RCC_APB1_PERIPH_BKP    
*\*\        - RCC_APB1_PERIPH_PWR      
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE       
*\*\return none. 
**/
void RCC_EnableAPB1PeriphClk(uint32_t APB1_periph, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        RCC->APB1PCLKEN |= APB1_periph;
    }
    else
    {
        RCC->APB1PCLKEN &= ~APB1_periph;
    }
    
}

/**
*\*\name    RCC_EnableAHBPeriphReset.
*\*\fun     AHB peripheral reset.
*\*\param   AHB_periph specifies the AHB peripheral to reset.    
*\*\        - RCC_AHB_PERIPHRST_ETH      
*\*\        - RCC_AHB_PERIPHRST_USBHS    
*\*\        - RCC_AHB_PERIPHRST_FMAC      
*\*\        - RCC_AHB_PERIPHRST_CORDIC     
*\*\        - RCC_AHB_PERIPHRST_ATIM3     
*\*\        - RCC_AHB_PERIPHRST_ATIM2    
*\*\        - RCC_AHB_PERIPHRST_ATIM1    
*\*\        - RCC_AHB_PERIPHRST_DVP      
*\*\        - RCC_AHB_PERIPHRST_DAC78     
*\*\        - RCC_AHB_PERIPHRST_DAC56     
*\*\        - RCC_AHB_PERIPHRST_ADC4     
*\*\        - RCC_AHB_PERIPHRST_ADC3     
*\*\        - RCC_AHB_PERIPHRST_ADC2     
*\*\        - RCC_AHB_PERIPHRST_ADC1     
*\*\        - RCC_AHB_PERIPHRST_GPIOH     
*\*\        - RCC_AHB_PERIPHRST_GPIOG    
*\*\        - RCC_AHB_PERIPHRST_GPIOF     
*\*\        - RCC_AHB_PERIPHRST_GPIOE     
*\*\        - RCC_AHB_PERIPHRST_GPIOD     
*\*\        - RCC_AHB_PERIPHRST_GPIOC     
*\*\        - RCC_AHB_PERIPHRST_GPIOB    
*\*\        - RCC_AHB_PERIPHRST_GPIOA    
*\*\        - RCC_AHB_PERIPHRST_FEMC     
*\*\        - RCC_AHB_PERIPHRST_SDIO     
*\*\        - RCC_AHB_PERIPHRST_USBHSPHY
*\*\        - RCC_AHB_PERIPHRST_XSPI     
*\*\        - RCC_AHB_PERIPHRST_RNGC     
*\*\        - RCC_AHB_PERIPHRST_SAC 
*\*\        - RCC_AHB_PERIPHRST_SHRTPLL   
*\*\        - RCC_AHB_PERIPHRST_SHRTIM   
*\*\return none.
**/
void RCC_EnableAHBPeriphReset(uint32_t AHB_periph)
{
    if(AHB_periph == RCC_AHB_PERIPHRST_SHRTPLL)
    {
        RCC->AHBPRST |= AHB_periph;
        __RCC_DELAY_US(5);
        RCC->AHBPRST &= ~AHB_periph;
    }
    else
    {
        RCC->AHBPRST |= AHB_periph;
        RCC->AHBPRST &= ~AHB_periph;
    }
    
}

/**
*\*\name    RCC_EnableAPB2PeriphReset.
*\*\fun     High Speed APB (APB2) peripheral reset.
*\*\param   APB2_periph specifies the APB2 peripheral to reset.
*\*\        - RCC_APB2_PERIPH_USART4  
*\*\        - RCC_APB2_PERIPH_PGA      
*\*\        - RCC_APB2_PERIPH_COMP     
*\*\        - RCC_APB2_PERIPH_GTIM10   
*\*\        - RCC_APB2_PERIPH_GTIM9   
*\*\        - RCC_APB2_PERIPH_GTIM8   
*\*\        - RCC_APB2_PERIPH_UART7   
*\*\        - RCC_APB2_PERIPH_UART6   
*\*\        - RCC_APB2_PERIPH_USART1  
*\*\        - RCC_APB2_PERIPH_SPI1    
*\*\        - RCC_APB2_PERIPH_SPI4    
*\*\        - RCC_APB2_PERIPH_SPI5    
*\*\        - RCC_APB2_PERIPH_SPI6    
*\*\        - RCC_APB2_PERIPH_AFIO     
*\*\return none.
**/
void RCC_EnableAPB2PeriphReset(uint32_t APB2_periph)
{
    RCC->APB2PRST |= APB2_periph;
    RCC->APB2PRST &= ~APB2_periph;
}

/**
*\*\name    RCC_EnableAPB1PeriphReset.
*\*\fun     Low Speed APB (APB1) peripheral reset.
*\*\param   APB1_periph specifies the APB1 peripheral to reset.
*\*\        - RCC_APB1_PERIPH_DAC34       
*\*\        - RCC_APB1_PERIPH_DAC12       
*\*\        - RCC_APB1_PERIPH_WWDG       
*\*\        - RCC_APB1_PERIPH_I2C4   
*\*\        - RCC_APB1_PERIPH_I2C3       
*\*\        - RCC_APB1_PERIPH_BTIM2     
*\*\        - RCC_APB1_PERIPH_BTIM1    
*\*\        - RCC_APB1_PERIPH_FDCAN3      
*\*\        - RCC_APB1_PERIPH_FDCAN2      
*\*\        - RCC_APB1_PERIPH_FDCAN1       
*\*\        - RCC_APB1_PERIPH_USBFS      
*\*\        - RCC_APB1_PERIPH_UCDR       
*\*\        - RCC_APB1_PERIPH_GTIM7      
*\*\        - RCC_APB1_PERIPH_GTIM6   
*\*\        - RCC_APB1_PERIPH_GTIM5      
*\*\        - RCC_APB1_PERIPH_GTIM4      
*\*\        - RCC_APB1_PERIPH_GTIM3      
*\*\        - RCC_APB1_PERIPH_GTIM2  
*\*\        - RCC_APB1_PERIPH_GTIM1      
*\*\        - RCC_APB1_PERIPH_SPI3      
*\*\        - RCC_APB1_PERIPH_SPI2      
*\*\        - RCC_APB1_PERIPH_I2C2      
*\*\        - RCC_APB1_PERIPH_I2C1      
*\*\        - RCC_APB1_PERIPH_UART5      
*\*\        - RCC_APB1_PERIPH_UART8      
*\*\        - RCC_APB1_PERIPH_USART3     
*\*\        - RCC_APB1_PERIPH_USART2     
*\*\        - RCC_APB1_PERIPH_BKP    
*\*\        - RCC_APB1_PERIPH_PWR           
*\*\return none. 
**/
void RCC_EnableAPB1PeriphReset(uint32_t APB1_periph)
{
    RCC->APB1PRST |= APB1_periph;
    RCC->APB1PRST &= ~APB1_periph;
}

/**
*\*\name   RCC_ConfigMcoClkPre.
*\*\fun    Configures the MCO PLL clock prescaler.
*\*\param  MCO_PLL_prescaler(MCO PLL clock prescaler): 
*\*\        - RCC_MCO_PLLCLK_DIV2 
*\*\        - RCC_MCO_PLLCLK_DIV3 
*\*\        - RCC_MCO_PLLCLK_DIV4 
*\*\        - RCC_MCO_PLLCLK_DIV5 
*\*\        - RCC_MCO_PLLCLK_DIV6 
*\*\        - RCC_MCO_PLLCLK_DIV7 
*\*\        - RCC_MCO_PLLCLK_DIV8 
*\*\        - RCC_MCO_PLLCLK_DIV9 
*\*\        - RCC_MCO_PLLCLK_DIV10
*\*\        - RCC_MCO_PLLCLK_DIV11
*\*\        - RCC_MCO_PLLCLK_DIV12
*\*\        - RCC_MCO_PLLCLK_DIV13
*\*\        - RCC_MCO_PLLCLK_DIV14
*\*\        - RCC_MCO_PLLCLK_DIV15 
*\*\return  none. 
**/
void RCC_ConfigMcoClkPre(uint32_t MCO_PLL_prescaler)
{
    uint32_t temp_value;

    temp_value = RCC->CFG;
    /* Clear MCOPRE[3:0] bits */
    temp_value &= RCC_MCO_PLLCLK_DIV_MASK;
    /* Set MCOPRE[3:0] bits according to MCO_PLL_prescaler value */
    temp_value |= MCO_PLL_prescaler;

    /* Store the new value */
    RCC->CFG = temp_value;
}

/**
*\*\name   RCC_ConfigMco1.
*\*\fun    Selects the clock source to output on MCO pin.
*\*\param  MCO_source(clock source to output): 
*\*\     - RCC_MCO_NOCLK          
*\*\     - RCC_MCO_SYSCLK         
*\*\     - RCC_MCO_HSI            
*\*\     - RCC_MCO_HSE            
*\*\     - RCC_MCO_PLL_PRES       
*\*\     - RCC_MCO_SHRTPLL_PRES   
*\*\     - RCC_MCO_USBHS240M_PRES
*\*\     - RCC_MCO_LSI            
*\*\     - RCC_MCO_LSE        
*\*\return  none. 
**/
void RCC_ConfigMco1(uint32_t MCO_source)
{
   uint32_t temp_value, temp_value1;

   temp_value = RCC->MCOCFG;
   /* Clear MCO1[3:0] bits */
   temp_value &= RCC_MCO1_MCOCFG_MASK;

    if((MCO_source & 0x01U) == 0x01U) /*RCC_MCO_PLL_PRES, RCC_MCO_SHRTPLL_PRES, RCC_MCO_USBHS240M_PRES */
    {
        temp_value1 = RCC->CFG;
        /* Clear MCOPLLSEL[1:0] bits */
        temp_value1 &= RCC_MCO_CFG_MASK;

        /* Set MCOPLLSEL[1:0] bits in CFG register */
        temp_value1 |= (MCO_source & RCC_CFG_MCOPLLSEL);
        /* Store the new value */
        RCC->CFG = temp_value1;

        /* Set MCO1[3:0] bits is PLL in MCOCFG register */
        temp_value |= (RCC_MCO_MCOCFG_PLL >> 4);
    }
    else
    {
        /* Set MCO1[3:0] bits in MCOCFG register */
        temp_value |= (MCO_source >> 4);
        
    }

   /* Store the new value */
   RCC->MCOCFG = temp_value;
}

/**
*\*\name   RCC_ConfigMco2.
*\*\fun    Selects the clock source to output on MCO pin.
*\*\param  MCO_source(clock source to output): 
*\*\     - RCC_MCO_NOCLK          
*\*\     - RCC_MCO_SYSCLK         
*\*\     - RCC_MCO_HSI            
*\*\     - RCC_MCO_HSE            
*\*\     - RCC_MCO_PLL_PRES       
*\*\     - RCC_MCO_SHRTPLL_PRES   
*\*\     - RCC_MCO_USBHS240M_PRES
*\*\     - RCC_MCO_LSI            
*\*\     - RCC_MCO_LSE     
*\*\return  none. 
**/
void RCC_ConfigMco2(uint32_t MCO_source)
{
   uint32_t temp_value, temp_value1;

   temp_value = RCC->MCOCFG;
   /* Clear MCO2[3:0] bits */
   temp_value &= RCC_MCO2_MCOCFG_MASK;

    if((MCO_source & 0x01U) == 0x01U) /*RCC_MCO_PLL_PRES, RCC_MCO_SHRTPLL_PRES, RCC_MCO_USBHS240M_PRES */
    {
        temp_value1 = RCC->CFG;
        /* Clear MCOPLLSEL[1:0] bits */
        temp_value1 &= RCC_MCO_CFG_MASK;

        /* Set MCOPLLSEL[1:0] bits in CFG register */
        temp_value1 |= (MCO_source & RCC_CFG_MCOPLLSEL);;
        /* Store the new value */
        RCC->CFG = temp_value1;

        /* Set MCO2[3:0] bits is PLL in MCOCFG register */
        temp_value |= RCC_MCO_MCOCFG_PLL;
    }
    else
    {
        /* Set MCO2[3:0] bits in MCOCFG register */
        temp_value |= MCO_source;
        
    }

   /* Store the new value */
   RCC->MCOCFG = temp_value;
}

/**
*\*\name    RCC_EnableRemap.
*\*\fun     Enables the system remap.
*\*\param   none
*\*\return  none
**/
void RCC_EnableRemap(void)
{
    uint32_t temp_value;

    temp_value = RCC->BOOTREMAP;

    /* clear REMAPKEY[7:0] bit */
    temp_value &= RCC_REMAP_MASK;
    /* Set REMAPKEY[7:0] bit is 0xCC*/
    temp_value |= RCC_REMAP_KEY;

    RCC->BOOTREMAP = temp_value;    
}

/**
*\*\name   RCC_ConfigRemapMode.
*\*\fun    Remap boot mode selection.
*\*\param  Remap_mode: 
*\*\        - RCC_REMAP_SYS       boot from system memory 
*\*\        - RCC_REMAP_BFLASH    boot from bank before flash main
*\*\        - RCC_REMAP_AFLASH    boot from bank after flash main
*\*\        - RCC_REMAP_SRAM      boot from SRAM 
*\*\        - RCC_REMAP_FEMC      boot from FEMC 
*\*\        - RCC_REMAP_XSPI      boot from XSPI
*\*\return  none. 
**/
void RCC_ConfigRemapMode(uint32_t Remap_mode)
{
    uint32_t temp_value;

    temp_value = RCC->BOOTREMAP;
    /* Clear REMAPSEL[2:0] bits */
    temp_value &= RCC_REMAP_SEL_MASK;
    /* Set REMAPSEL[2:0] bits according to Remap_mode value */
    temp_value |= Remap_mode;

    /* Store the new value */
    RCC->BOOTREMAP = temp_value;
}


/**
*\*\name    RCC_GetFlagStatus.
*\*\fun     Checks whether the specified RCC flag is set or not.
*\*\param   RCC_flag:
*\*\	      - RCC_FLAG_PLLRDF        PLL clock ready
*\*\	      - RCC_FLAG_HSIRDF        HSI oscillator clock ready
*\*\          - RCC_FLAG_HSERDF        HSE oscillator clock ready
*\*\	      - RCC_FLAG_RPINTF        LSI oscillator clock ready
*\*\	      - RCC_FLAG_LSECSSF       LSE Clock Safety System flag
*\*\	      - RCC_FLAG_HSECSSF       HSE Clock Safety System flag
*\*\	      - RCC_FLAG_HSICSSF       HSI Clock Safety System flag
*\*\	      - RCC_FLAG_LSIRDF        LSI oscillator clock ready
*\*\	      - RCC_FLAG_BORRSTF       BOR reset flag
*\*\	      - RCC_FLAG_MAINEMCF       MAIN_EMC reset flag
*\*\	      - RCC_FLAG_BKPEMCF       BKP_EMC reset flag 
*\*\	      - RCC_FLAG_RAMERSTF      RAM parity or ECC error reset flag
*\*\	      - RCC_FLAG_SMPURSTF       SMPU reset flag 
*\*\	      - RCC_FLAG_PINRSTF       Pin reset flag
*\*\	      - RCC_FLAG_PORRSTF       POR/PDR reset flag
*\*\	      - RCC_FLAG_SFTRSTF       Software reset flag
*\*\	      - RCC_FLAG_IWDGRSTF      Independent Watchdog reset flag
*\*\	      - RCC_FLAG_WWDGRSTF      Window Watchdog reset flag
*\*\	      - RCC_FLAG_LPWRRSTF      Low Power reset flag
*\*\	      - RCC_FLAG_LSERDF        LSE oscillator clock ready
*\*\	      - RCC_FLAG_HSEFLF        HSE frequency out of low limit flag
*\*\	      - RCC_FLAG_HSEFHF        HSE frequency out of high limit flag
*\*\	      - RCC_FLAG_HSEPOF        HSE phase shift out of range flag
*\*\	      - RCC_FLAG_SHRTPLLRDF    SHRTPLL clock ready
*\*\return  FlagStatus:    
*\*\      	  - SET 
*\*\  	      - RESET
**/
FlagStatus RCC_GetFlagStatus(uint8_t RCC_flag)
{
    uint32_t temp_value;
    uint32_t reg_value;
    FlagStatus bitstatus;

    /* Get the RCC register index */
    temp_value = (uint32_t)RCC_flag >> RCC_FLAG_OFFSET;
    switch(temp_value)
    {
        case 1: /* The flag to check is in CTRL register */
            reg_value = RCC->CTRL;
            break;
        case 2: /* The flag to check is in CFG3 register */
            reg_value = RCC->CFG3;
            break;
        case 3:/* The flag to check is in CLKINT register */
            reg_value = RCC->CLKINT;
            break;
        case 4:/* The flag to check is in CTRLSTS register */
            reg_value = RCC->CTRLSTS;
            break;
        case 5:/* The flag to check is in BDCTRL register */
            reg_value = RCC->BDCTRL;
            break;
        case 6:/* The flag to check is in CSSCTRL register */
            reg_value = RCC->CSSCTRL;
            break;
        default:/* The flag to check is in SHRTPLLCTRL3 register */
            reg_value = RCC->SHRTPLLCTRL3;
            break;
    }

    /* Get the flag position */
    temp_value = (uint32_t)RCC_flag & RCC_FLAG_MASK;
    if ((reg_value & ((uint32_t)1 << temp_value)) != (uint32_t)RESET)
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
*\*\name    RCC_ClearResetFlag.
*\*\fun     Clears the RCC reset flags.
*\*\param   none
*\*\return  none
*\*\note  Clear the following flags:
*\*\	      - RCC_FLAG_BORRSTF       BOR reset flag
*\*\	      - RCC_FLAG_MAINEMCF      MAIN_EMC reset flag
*\*\	      - RCC_FLAG_BKPEMCF       BKP_EMC reset flag 
*\*\	      - RCC_FLAG_RAMERSTF      RAM parity or ECC error reset flag
*\*\	      - RCC_FLAG_SMPURSTF      SMPU reset flag 
*\*\	      - RCC_FLAG_PINRSTF       Pin reset flag
*\*\	      - RCC_FLAG_PORRSTF       POR/PDR reset flag
*\*\	      - RCC_FLAG_SFTRSTF       Software reset flag
*\*\	      - RCC_FLAG_IWDGRSTF      Independent Watchdog reset flag
*\*\	      - RCC_FLAG_WWDGRSTF      Window Watchdog reset flag
*\*\	      - RCC_FLAG_LPWRRSTF      Low Power reset flag
**/
void RCC_ClearResetFlag(void)
{
    /* Set RMRSTF bit to clear the reset flags */
    RCC->CTRLSTS |= RCC_REMOVE_RESET_FLAG;
    /* RMRSTF bit should be reset */
    RCC->CTRLSTS &= ~RCC_REMOVE_RESET_FLAG;
}

/**
*\*\name    RCC_GetIntStatus.
*\*\fun     Checks whether the specified RCC interrupt has occurred or not.
*\*\param   interrupt_flag(RCC interrupt source to check):
*\*\         - RCC_INT_LSIRDIF     LSI ready interrupt
*\*\         - RCC_INT_LSERDIF     LSI ready interrupt
*\*\         - RCC_INT_HSIRDIF     HSI ready interrupt
*\*\         - RCC_INT_HSERDIF     HSE ready interrupt
*\*\         - RCC_INT_PLLRDIF     PLL ready interrupt
*\*\         - RCC_INT_LSECSSIF    LSE CSS interrupt 
*\*\         - RCC_INT_HSECSSIF    HSE CSS interrupt 
*\*\         - RCC_INT_HSICSSIF    HSI CSS interrupt 
*\*\         - RCC_INT_BORIF       BOR interrupt 
*\*\return  The new state of RccInt 
*\*\         - SET
*\*\         - RESET
**/
INTStatus RCC_GetIntStatus(uint32_t interrupt_flag)
{
    INTStatus bitstatus;

    /* Check the status of the specified RCC interrupt */
    if ((RCC->CLKINT & interrupt_flag) != (uint32_t)RESET)
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
*\*\name    RCC_ClrIntPendingBit.
*\*\fun     Clears the RCC's interrupt pending bits.
*\*\param   interrupt_clear(interrupt pending bit to clear):
*\*\         - RCC_CLR_LSIRDIF     LSI ready interrupt
*\*\         - RCC_CLR_LSERDIF     LSI ready interrupt
*\*\         - RCC_CLR_HSIRDIF     HSI ready interrupt
*\*\         - RCC_CLR_HSERDIF     HSE ready interrupt
*\*\         - RCC_CLR_PLLRDIF     PLL ready interrupt
*\*\         - RCC_CLR_LSECSSIF    LSE CSS interrupt 
*\*\         - RCC_CLR_HSECSSIF    HSE CSS interrupt 
*\*\         - RCC_CLR_HSICSSIF    HSE CSS interrupt 
*\*\         - RCC_CLR_BORIF       BOR interrupt 
*\*\return  none
**/
void RCC_ClrIntPendingBit(uint32_t interrupt_clear)
{
    /* Software set this bit to clear INT flag. */
    RCC->CLKINT |= interrupt_clear;
}




