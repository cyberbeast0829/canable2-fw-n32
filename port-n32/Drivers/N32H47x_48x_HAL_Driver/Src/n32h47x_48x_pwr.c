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
*\*\file n32h47x_48x_pwr.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
 */
#include "n32h47x_48x_rcc.h"
#include "n32h47x_48x_pwr.h"


/** RCC Driving Functions Declaration **/ 

/**
*\*\name    PWR_DeInit.
*\*\fun     Deinitializes the PWR peripheral registers to their default reset values.
*\*\param   none
*\*\return  none
**/
void PWR_DeInit(void)
{
    RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_PWR);
}

/**
*\*\name  PWR_BackupAccessEnable.
*\*\fun   Enables or disables access to the RTC and backup registers.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/
void PWR_BackupAccessEnable(FunctionalState Cmd)
{
    /* Check the parameters */
    *(__IO uint32_t*)CTRL_DBKP_BB = (uint32_t)Cmd;
}

/**
*\*\name    PWR_PvdEnable.
*\*\fun     Enables or disables the Power Voltage Detector(PVD).
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/
void PWR_PvdEnable(FunctionalState Cmd)
{
    /* Check the parameters */
    *(__IO uint32_t*)CTRL_PVDEN_BB = (uint32_t)Cmd;
}

/**
*\*\name    PWR_PVDLevelConfig.
*\*\fun     Configures the voltage threshold detected by the Power Voltage Detector(PVD).
*\*\param   level (The input parameters must be the following values):
*\*\          - PWR_PVD_LEVEL_2V18    PVD level is 2.18V
*\*\          - PWR_PVD_LEVEL_2V28    PVD level is 2.28V
*\*\          - PWR_PVD_LEVEL_2V38    PVD level is 2.38V
*\*\          - PWR_PVD_LEVEL_2V48    PVD level is 2.48V
*\*\          - PWR_PVD_LEVEL_2V58    PVD level is 2.58V
*\*\          - PWR_PVD_LEVEL_2V68    PVD level is 2.68V
*\*\          - PWR_PVD_LEVEL_2V78    PVD level is 2.78V
*\*\          - PWR_PVD_LEVEL_2V88    PVD level is 2.88V

*\*\          - PWR_PVD_LEVEL_1V78    PVD level is 1.78V
*\*\          - PWR_PVD_LEVEL_1V88    PVD level is 1.88V
*\*\          - PWR_PVD_LEVEL_1V98    PVD level is 1.98V
*\*\          - PWR_PVD_LEVEL_2V08    PVD level is 2.08V
*\*\          - PWR_PVD_LEVEL_3V28    PVD level is 3.28V
*\*\          - PWR_PVD_LEVEL_3V38    PVD level is 3.38V
*\*\          - PWR_PVD_LEVEL_3V48    PVD level is 3.48V
*\*\          - PWR_PVD_LEVEL_3V58    PVD level is 3.58V
*\*\return  none
**/
void PWR_PVDLevelConfig(uint32_t level)
{
    uint32_t temp_value;

    temp_value = PWR->CTRL;
    /* Clear MSB and PLS[2:0] bits bit */
    temp_value &= PWR_CTRL_PLS_MASK;
    /* Set MSB and PLS[2:0] bits according to level value */
    temp_value |= level;
    /* Store the new value */
    PWR->CTRL = temp_value;
}

/**
*\*\name    PWR_PVDSourceConfig.
*\*\fun     PVD Source selection.
*\*\param   PVD_source (The input parameters must be the following values):
*\*\          - PWR_PVD_VDD      
*\*\          - PWR_PVD_PVDIN   
*\*\return  none
*\*\note    none
**/
void PWR_PVDSourceConfig(uint32_t PVD_source)
{
    if(PVD_source == PWR_PVD_PVDIN)
   {
       /* Set PVDSRC bit */
       PWR->CTRL6 |= PWR_PVD_PVDIN;
   }
   else
   {
       /* Reset PVDSRC bit */
       PWR->CTRL6 &= PWR_PVD_VDD;
   }  
}

/**
*\*\name    PWR_PVDINPinSelect.
*\*\fun     PVD_IN pin selection.
*\*\param   PVD_pin (The input parameters must be the following values):
*\*\          - PVD_IN_PA10      
*\*\          - PVD_IN_PB7   
*\*\return  none
*\*\note    none
**/
void PWR_PVDINPinSelect(PVD_IN_SEL PVD_pin)
{
    if(PVD_pin == PVD_IN_PB7)
   {
       /* Set PVD_IN bit */
       *(uint32_t *)0x40010018 |= 0x1;
   }
   else
   {
       /* Reset PVD_IN bit */
       *(uint32_t *)0x40010018 &= 0xFFFFFFFE;
   }  
}


/**
*\*\name    PWR_WakeUpPinEnable.
*\*\fun     Enables the Wakeup Pin functionality.
*\*\param   pin (The input parameters must be the following values):
*\*\          - WAKEUP_PIN0EN   WKUP0(PE6)
*\*\          - WAKEUP_PIN1EN   WKUP1(PA0)
*\*\          - WAKEUP_PIN2EN   WKUP2(PC13)
*\*\          - WAKEUP_PIN3EN   WKUP3(PA2)
*\*\          - WAKEUP_PIN4EN   WKUP4(PC5)
*\*\          - WAKEUP_PIN5EN   WKUP5(PH6)
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/
void PWR_WakeUpPinEnable(uint32_t pin, FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        /* Set WKUPxEN bit */
        PWR->CTRLSTS |= pin;
    }
    else
    {
        /* Clear WKUPxEN bit*/
        PWR->CTRLSTS &= (~pin);
    }
}

/**
*\*\name    PWR_WakeUpPinPolarity.
*\*\fun     Enables the Wakeup Pin polarity.
*\*\param   pin (The input parameters must be the following values):
*\*\          - WAKEUP_PIN0POL   WKUP0(PE6)
*\*\          - WAKEUP_PIN1POL   WKUP1(PA0)
*\*\          - WAKEUP_PIN2POL   WKUP2(PC13)
*\*\          - WAKEUP_PIN3POL   WKUP3(PA2)
*\*\          - WAKEUP_PIN4POL   WKUP4(PC5)
*\*\param   polarity (The input parameters must be the following values): 
*\*\          - POL_LOW
*\*\          - POL_HIGH
*\*\return  none
**/
void PWR_WakeUpPinPolarity(uint32_t pin, WAKEUP_PIN_POL polarity)
{
    if(polarity == POL_LOW)
    {
        /* Set WKUPxPOL bit */
        PWR->CTRLSTS |= pin;
    }
    else
    {
        /* Clear WKUPxPOL bit*/
        PWR->CTRLSTS &= (~pin);
    }
}

/**
*\*\name    PWR_WakeUpPeriphEnable.
*\*\fun     Enables the Wakeup periph functionality.
*\*\param   periph (The input parameters must be the following values):
*\*\          - WAKEUP_PERIPH0EN   PERIPH0(LPTIM1 and LPTIM2)
*\*\          - WAKEUP_PERIPH1EN   PERIPH1(RTC and LSECSS)
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE 
*\*\return  none
**/
void PWR_WakeUpPeriphEnable(uint32_t periph, FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        /* Set WKUPxEN bit */
        PWR->CTRLSTS |= periph;
    }
    else
    {
        /* Clear WKUPxEN bit*/
        PWR->CTRLSTS &= (~periph);
    }
}

/**
*\*\name    PWR_EnterSLEEPMode.
*\*\fun     Enters SLEEP mode.
*\*\param   status (The input parameters must be the following values):
*\*\          - PWR_SLEEP_ON_EXIT
*\*\          - PWR_SLEEP_NOW
*\*\param   enter_mode (The input parameters must be the following values):
*\*\          - PWR_SLEEPENTRY_WFI    enter SLEEP mode with WFI instruction
*\*\          - PWR_SLEEPENTRY_WFE    enter SLEEP mode with WFE instruction
*\*\return  none
**/
void PWR_EnterSLEEPMode(PWR_SLEEPONEXIT_STATUS SLEEPONEXIT, uint8_t PWR_SLEEPEntry)
{
    /* Clear SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR &= (uint32_t) ~((uint32_t)SCB_SCR_SLEEPDEEP);

    /* Select SLEEPONEXIT mode entry --------------------------------------------------*/
    if (SLEEPONEXIT == PWR_SLEEP_ON_EXIT)
    {
        /* the MCU enters Sleep mode as soon as it exits the lowest priority INTSTS */
        SCB->SCR |= SCB_SCR_SLEEPONEXIT;
    }
    else 
    {
        /* Sleep-now */
        SCB->SCR &= (uint32_t) ~((uint32_t)SCB_SCR_SLEEPONEXIT);
    }
    
      

    /* Select SLEEP mode entry --------------------------------------------------*/
    if (PWR_SLEEPEntry == PWR_SLEEPENTRY_WFI)
    {
        /* Request Wait For Interrupt */
        __WFI();
    }
    else
    {
        /* Request Wait For Event */
        __SEV();
        __WFE();
        __WFE();
    }
}

/**
*\*\name    PWR_EnterSTOPMode.
*\*\fun     Enters STOP mode.
*\*\param   PWR_Regulator (The input parameters must be the following values):
*\*\          - PWR_REGULATOR_NORMAL      STOP mode with regulator in normal mode
*\*\          - PWR_REGULATOR_LOWPOWER    STOP mode with regulator in low power mode
*\*\param   PWR_STOPEntry (The input parameters must be the following values):
*\*\          - PWR_STOPENTRY_WFI    enter STOP mode with WFI instruction
*\*\          - PWR_STOPENTRY_WFE    enter STOP mode with WFE instruction
*\*\return  none
**/
void PWR_EnterSTOPMode(uint32_t PWR_Regulator, uint8_t PWR_STOPEntry)
{
    uint32_t tmpregister;

    /* Select the regulator state in STOP mode ---------------------------------*/
    tmpregister = PWR->CTRL;
    /* Clear PDS and LPS bits */
    tmpregister &= PWR_PDSLPS_MASK;
    /* Set LPS bit according to PWR_Regulator value */
    tmpregister |= PWR_Regulator;
    /* Store the new value */
    PWR->CTRL = tmpregister;

    /* Set SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP;

    /* Select STOP mode entry --------------------------------------------------*/
    if (PWR_STOPEntry == PWR_STOPENTRY_WFI)
    {
        /* Request Wait For Interrupt */
        __WFI();
    }
    else
    {
        /* Request Wait For Event */
        __SEV();
        __WFE();
        __WFE();
    }

    /* Reset SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR &= (uint32_t) ~((uint32_t)SCB_SCR_SLEEPDEEP);
}


/**
*\*\name    PWR_EnterSTANDBYMode.
*\*\fun     Enters STANDBY mode.
*\*\param   none
*\*\return  none
**/
void PWR_EnterSTANDBYMode(void)
{
    uint32_t tmpregister;

    /* Select the regulator state in STOP mode ---------------------------------*/
    tmpregister = PWR->CTRL;
    /* Clear PDS and LPS bits */
    tmpregister &= PWR_PDSLPS_MASK;
    /* Set PDS bit */
    tmpregister |= PWR_PDS_SET;
    /* Store the new value */
    PWR->CTRL = tmpregister;

    /* Set SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP;
/* This option is used to ensure that store operations are completed */
#if defined(__CC_ARM)
    __force_stores();
#endif
    /* Request Wait For Interrupt */
    __WFI();
}

/**
*\*\name   PWR_GetFlagStatus.
*\*\fun    Checks whether the specified PWR flag is set or not.
*\*\param PWR_FLAG (specifies the flag to check):
*\*\      This parameter can be one of the following values:
*\*\       - PWR_FLAG_WKUP0     PE6 Wake Up flag
*\*\       - PWR_FLAG_WKUP1     PA0 Wake Up flag
*\*\       - PWR_FLAG_WKUP2     PC13 Wake Up flag
*\*\       - PWR_FLAG_WKUP3     PA2 Wake Up flag
*\*\       - PWR_FLAG_WKUP4     PC5 Wake Up flag
*\*\       - PWR_FLAG_WKUP5     PH6 Wake Up flag
*\*\       - PWR_FLAG_WKUPP     RTC or LSECSS or LPTIM1  or LPTIM2 Wake Up flag
*\*\       - PWR_FLAG_STANDBY   StandBy mode flag
*\*\       - PWR_FLAG_PVDOUT    PVD Output
*\*\       - PWR_FLAG_VBAT      VBAT mode flag
*\*\return The new state of PWR_FLAG 
*\*\       - SET
*\*\       - RESET
 */
FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG)
{
    FlagStatus bitstatus;
    /* Check the parameters */

    if ((PWR->CTRLSTS & PWR_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    /* Return the flag status */
    return bitstatus;
}

/**
*\*\name   PWR_ClearFlag.
*\*\fun    Clears the PWR's pending flags.
*\*\param  PWR_FLAG (specifies the flag to clear):
*\*\       This parameter can be one of the following values:
*\*\       - PWR_CLR_WKUP0     PE6 Wake Up flag
*\*\       - PWR_CLR_WKUP1     PA0 Wake Up flag
*\*\       - PWR_CLR_WKUP2     PC13 Wake Up flag
*\*\       - PWR_CLR_WKUP3     PA2 Wake Up flag
*\*\       - PWR_CLR_WKUP4     PC5 Wake Up flag
*\*\       - PWR_CLR_WKUP5     PH6 Wake Up flag
*\*\       - PWR_CLR_WKUPP     RTC or LSECSS or LPTIM1  or LPTIM2 Wake Up flag
*\*\       - PWR_CLR_STANDBY   StandBy mode flag
*\*\       - PWR_CLR_VBAT      VBAT mode flag
*\*\return  none
 */
void PWR_ClearFlag(uint32_t PWR_FLAG)
{
    PWR->CTRL |= PWR_FLAG;     
}

/**
*\*\name    PWR_ConfigBKROutput.
*\*\fun     Selects the BKR regulator output level.
*\*\param   voltage_output (The input parameters must be the following values):
*\*\          - PWR_BKR_OUTPUT_0_8V    output 0.8V
*\*\          - PWR_BKR_OUTPUT_0_9V    output 0.9V
*\*\return  none
*\*\note    none
**/
void PWR_ConfigBKROutput(uint32_t voltage_output)
{
    if(voltage_output == PWR_BKR_OUTPUT_0_9V)
   {
       /* Set BKRSEL bit */
       PWR->CTRL3 |= PWR_BKR_OUTPUT_0_9V;
   }
   else
   {
       /* Reset BKRSEL bit */
       PWR->CTRL3 &= PWR_BKR_OUTPUT_0_8V;
   }  
}

/**
*\*\name    PWR_EnableIWDGReset.
*\*\fun     Configure whether to generate a reset request when the IWDG counter reaches 0.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE   
*\*\return  none. 
**/
void PWR_EnableIWDGReset(FunctionalState Cmd)
{ 
   if(Cmd == ENABLE)
   {
       /* Set IWDGRSTEN bit */
       PWR->CTRL2 |= PWR_IWDGRST_ENABLE;
   }
   else
   {
       /* Reset IWDGRSTEN bit */
       PWR->CTRL2 &= (~PWR_IWDGRST_ENABLE);
   }  
}

/**
*\*\name    PWR_EnableBKPSRAMRetainInStandbyMode.
*\*\fun     Enable or disable BKP SRAM retain in standby mode.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE   
*\*\return  none. 
**/
void PWR_EnableBKPSRAMRetainInStandbyMode(FunctionalState Cmd)
{ 
   if(Cmd == ENABLE)
   {
       /* Set BSRSTBRET bit */
       PWR->CTRL2 |= PWR_STBRET_ENABLE;
   }
   else
   {
       /* Reset BSRSTBRET bit */
       PWR->CTRL2 &= (~PWR_STBRET_ENABLE);
   }  
}

/**
*\*\name    PWR_EnableBKPSRAMRetainInVbatMode.
*\*\fun     Enable or disable BKP SRAM retain in Vbat mode.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE   
*\*\return  none. 
**/
void PWR_EnableBKPSRAMRetainInVbatMode(FunctionalState Cmd)
{ 
   if(Cmd == ENABLE)
   {
       /* Set BSRVBRET bit */
       PWR->CTRL2 |= PWR_VBATRET_ENABLE;
   }
   else
   {
       /* Reset BSRVBRET bit */
       PWR->CTRL2 &= (~PWR_VBATRET_ENABLE);
   }  
}

/**
*\*\name    PWR_EnableLSENoiseMitigation.
*\*\fun     Enable or disable LSE noise mitigation.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE   
*\*\return  none
*\*\note    Noise mitigation must be enabled after the RCC_BDCTRL.LSERD set.
**/
void PWR_EnableLSENoiseMitigation(FunctionalState Cmd)
{ 
   if(Cmd == ENABLE)
   {
       /* Set LSENIMEN bit */
       PWR->CTRL4 |= PWR_LSENIM_ENABLE;
   }
   else
   {
       /* Reset LSENIMEN bit */
       PWR->CTRL4 &= (~PWR_LSENIM_ENABLE);
   }  
}

/**
*\*\name    PWR_EnableLSECSSCrystalInt.
*\*\fun     Enable or disable LSE Clock Safety System Interrupt in Crystal Mode.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE   
*\*\return  none
*\*\note    none
**/
void PWR_EnableLSECSSCrystalInt(FunctionalState Cmd)
{ 
   if(Cmd == ENABLE)
   {
       /* Set LSECSSCRYIEN bit */
       PWR->CTRL5 |= PWR_LSECSSCRYINT_ENABLE;
   }
   else
   {
       /* Reset LSECSSCRYIEN bit */
       PWR->CTRL5 &= (~PWR_LSECSSCRYINT_ENABLE);
   }  
}

/**
*\*\name    PWR_ConfigLSECSSBypassHighLimit.
*\*\fun     Configuring the LSE Frequency High Limit for Bypass Mode.
*\*\param   high_limit (The input parameters must be the following values):
*\*\          - PWR_HIGH_LIMIT_1M      
*\*\          - PWR_HIGH_LIMIT_160K   
*\*\return  none
*\*\note    none
**/
void PWR_ConfigLSECSSBypassHighLimit(uint32_t high_limit)
{
    if(high_limit == PWR_HIGH_LIMIT_160K)
   {
       /* Set BKRSEL bit */
       PWR->CTRL6 |= PWR_HIGH_LIMIT_160K;
   }
   else
   {
       /* Reset BKRSEL bit */
       PWR->CTRL6 &= PWR_HIGH_LIMIT_1M;
   }  
}

/**
*\*\name    PWR_EnableLSECSSRTCsourceSwitch.
*\*\fun     Enable or disable switching the RTC clock source 
*\*\        from LSE to LSI when the LSE clock fails.
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE   
*\*\return  none
**/
void PWR_EnableLSECSSRTCsourceSwitch(FunctionalState Cmd)
{ 
   if(Cmd == ENABLE)
   {
       /* Set LSECSSSW bit */
       PWR->CTRL6 |= PWR_LSETOLSI_ENABLE;
   }
   else
   {
       /* Reset LSECSSSW bit */
       PWR->CTRL6 &= (~PWR_LSETOLSI_ENABLE);
   }  
}


/**
*\*\name   PWR_GetLSECSSFlagStatus.
*\*\fun    Checks whether the specified PWR LSECSS flag is set or not.
*\*\param PWR_FLAG (specifies the flag to check):
*\*\      This parameter can be one of the following values:
*\*\       - PWR_FLAG_LSECSSCRYF    LSE Clock Security System Failure in Crystal Mode
*\*\       - PWR_FLAG_LSEFHF        LSE Frequency Exceeds High Limit Flag
*\*\       - PWR_FLAG_LSEFLF        LSE frequency below low limit flag
*\*\       - PWR_FLAG_LSECSSF       LSE Clock Security System Failure flag
*\*\return The new state of PWR_FLAG 
*\*\       - SET
*\*\       - RESET
 */
FlagStatus PWR_GetLSECSSFlagStatus(uint32_t PWR_FLAG)
{
    FlagStatus bitstatus;
    /* Check the parameters */
    if(PWR_FLAG == PWR_FLAG_LSECSSCRYF)
    {
        if ((PWR->CTRL5 & PWR_FLAG) != (uint32_t)RESET)
        {
            bitstatus = SET;
        }
        else
        {
            bitstatus = RESET;
        }
    }
    else
    {
        if ((PWR->CTRL6 & PWR_FLAG) != (uint32_t)RESET)
        {
            bitstatus = SET;
        }
        else
        {
            bitstatus = RESET;
        }
    }
    
    /* Return the flag status */
    return bitstatus;
}

/**
*\*\name    PWR_ClearLSECSSFlag.
*\*\fun     Clears the LSECSS all flags.
*\*\param   none
*\*\return  none
*\*\note  Clear the following flags:
*\*\       - PWR_FLAG_LSECSSCRYF    LSE Clock Security System Failure in Crystal Mode
*\*\       - PWR_FLAG_LSEFHF        LSE Frequency Exceeds High Limit Flag
*\*\       - PWR_FLAG_LSEFLF        LSE frequency below low limit flag
*\*\       - PWR_FLAG_LSECSSF       LSE Clock Security System Failure flag
**/
void PWR_ClearLSECSSFlag(void)
{
    /* Set LSECSSF bit to clear the all flags */
    PWR->CTRL6 |= PWR_FLAG_LSECSSF;
}

/**
*\*\name    PWR_ConfigLco.
*\*\fun     LCO low-speed clock output selection.
*\*\param   LCO_source (The input parameters must be the following values):
*\*\          - PWR_LCO_LSI      
*\*\          - PWR_LCO_LSE   
*\*\return  none
*\*\note    none
**/
void PWR_ConfigLco(uint32_t LCO_source)
{
    if(LCO_source == PWR_LCO_LSE)
   {
       /* Set BKRSEL bit */
       PWR->CTRL6 |= PWR_LCO_LSE;
   }
   else
   {
       /* Reset BKRSEL bit */
       PWR->CTRL6 &= PWR_LCO_LSI;
   }  
}

/**
*\*\name    PWR_EnableLCO.
*\*\fun     Enable or disable low-speed clock output 
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE   
*\*\return  none
**/
void PWR_EnableLCO(FunctionalState Cmd)
{ 
   if(Cmd == ENABLE)
   {
       /* Set LCOEN bit */
       PWR->CTRL6 |= PWR_LCO_ENABLE;
   }
   else
   {
       /* Reset LCOEN bit */
       PWR->CTRL6 &= (~PWR_LCO_ENABLE);
   }  
}

/**
*\*\name   PWR_ConfigNRSTMode.
*\*\fun    Configuring the NRST (PH6) Pin Function.
*\*\param  NRST_mode: 
*\*\        - PWR_NRSTPIN_INPUT       
*\*\        - PWR_NRSTPIN_INPUTOUTPUT    
*\*\        - PWR_NRSTPIN_NORMALGPIO    
*\*\return  none. 
**/
void PWR_ConfigNRSTMode(uint32_t NRST_mode)
{
    uint32_t temp_value;

    temp_value = PWR->CTRL6;
    /* Clear NRSTSEL[1:0] bits */
    temp_value &= PWR_NRST_SEL_MASK;
    /* Set NRSTSEL[1:0] bits according to NRST_mode value */
    temp_value |= NRST_mode;

    /* Store the new value */
    PWR->CTRL6 = temp_value;
}





