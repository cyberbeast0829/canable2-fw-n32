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
*\*\file system_n32h47x_48x.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
 */
#include "n32h47x_48x.h"

/* Uncomment the line corresponding to the desired System clock (SYSCLK)
   frequency (after reset the HSI is used as SYSCLK source)

   IMPORTANT NOTE:
   ==============
   1. After each device reset the HSI is used as System clock source.

   2. Please make sure that the selected System clock doesn't exceed your
   device's maximum frequency.

   3. If none of the define below is enabled, the HSI is used as System clock
    source.

   4. The System clock configuration functions provided within this file assume
   that:
        - For Low, Medium and High density Value line devices an external 8MHz
          crystal is used to drive the System clock.
        - For Low, Medium and High density devices an external 8MHz crystal is
          used to drive the System clock.
        - For Connectivity line devices an external 25MHz crystal is used to
   drive the System clock. If you are using different crystal you have to adapt
   those functions accordingly.
    */

#define SYSCLK_USE_HSI     0
#define SYSCLK_USE_HSE     1
#define SYSCLK_USE_HSI_PLL 2
#define SYSCLK_USE_HSE_PLL 3

#ifndef SYSCLK_FREQ
#if defined (N32H473) || defined (N32H474)
#define SYSCLK_FREQ    240000000
#elif defined (N32H475) || defined (N32H482) || defined (N32H487)     
#define SYSCLK_FREQ    240000000
#else
#error wrong macro definition
#endif  

#endif


#ifndef SYSCLK_SRC
#define SYSCLK_SRC   SYSCLK_USE_HSE_PLL
#endif

#if SYSCLK_SRC == SYSCLK_USE_HSI

#if SYSCLK_FREQ != HSI_VALUE
#error SYSCL_FREQ must be set to HSI_VALUE
#endif

#elif SYSCLK_SRC == SYSCLK_USE_HSE

#ifndef HSE_VALUE
#error HSE_VALUE must be defined!
#endif

#if SYSCLK_FREQ != HSE_VALUE
#error SYSCL_FREQ must be set to HSE_VALUE
#endif

#elif SYSCLK_SRC == SYSCLK_USE_HSI_PLL

#if (SYSCLK_FREQ % HSI_VALUE == 0) && (SYSCLK_FREQ / HSI_VALUE >= 8) && (SYSCLK_FREQ / HSI_VALUE <= 76)           \
       && ((SYSCLK_FREQ / HSI_VALUE) % 2 ==0)
#define PLLSRC_DIV   1
#define PLL_MUL     (SYSCLK_FREQ / HSI_VALUE)
#define PLL_INPRE    1
#define PLL_OUTPRE   1

#elif ((SYSCLK_FREQ % (HSI_VALUE / 2)) == 0) && (SYSCLK_FREQ / (HSI_VALUE / 2) >= 8)                                     \
    && (SYSCLK_FREQ / (HSI_VALUE / 2) <= 76)

#define PLLSRC_DIV   2
#define PLL_MUL     (SYSCLK_FREQ / (HSI_VALUE / 2))
#define PLL_INPRE    1
#define PLL_OUTPRE   1


#else
#error Cannot make a PLL multiply factor to SYSCLK_FREQ.
#endif

#elif SYSCLK_SRC == SYSCLK_USE_HSE_PLL

#ifndef HSE_VALUE
#error HSE_VALUE must be defined!
#endif

#if (SYSCLK_FREQ % HSE_VALUE == 0) && (SYSCLK_FREQ / HSE_VALUE >= 8) && (SYSCLK_FREQ / HSE_VALUE <= 76)        \
        && ((SYSCLK_FREQ / HSE_VALUE) % 2 ==0)

#define PLLSRC_DIV   1
#define PLL_MUL     (SYSCLK_FREQ / HSE_VALUE)
#define PLL_INPRE    1
#define PLL_OUTPRE   1
          
#elif ((SYSCLK_FREQ % (HSE_VALUE / 2)) == 0) && (SYSCLK_FREQ / (HSE_VALUE / 2) >= 8)                                     \
    && (SYSCLK_FREQ / (HSE_VALUE / 2) <= 76) && ((SYSCLK_FREQ / (HSE_VALUE / 2)) % 2 ==0)

#define PLLSRC_DIV   2
#define PLL_MUL     (SYSCLK_FREQ / (HSE_VALUE / 2))
#define PLL_INPRE    1
#define PLL_OUTPRE   1

#elif ((SYSCLK_FREQ % (HSE_VALUE / 3)) == 0) && (SYSCLK_FREQ / (HSE_VALUE / 3) >= 8) 

#define PLLSRC_DIV   1
#define PLL_MUL     (SYSCLK_FREQ / (HSE_VALUE / 6))
#define PLL_INPRE    3
#define PLL_OUTPRE   2

#else
#error Cannot make a PLL multiply factor to SYSCLK_FREQ.
#endif

#else
#error wrong value for SYSCLK_SRC
#endif

/* #define VECT_TAB_SRAM */
#define VECT_TAB_OFFSET 0x0U /*!< Vector Table base offset field. This value must be a multiple of 0x200. */

/* #define start-up voltage */
#define STARTUP_VOLT_2V18    (PWR_CTRL_PLS_LVL0)
#define STARTUP_VOLT_2V28    (PWR_CTRL_PLS_LVL1)
#define STARTUP_VOLT_2V38    (PWR_CTRL_PLS_LVL2)
#define STARTUP_VOLT_2V48    (PWR_CTRL_PLS_LVL3)
#define STARTUP_VOLT_2V58    (PWR_CTRL_PLS_LVL4)
#define STARTUP_VOLT_2V68    (PWR_CTRL_PLS_LVL5)
#define STARTUP_VOLT_2V78    (PWR_CTRL_PLS_LVL6)
#define STARTUP_VOLT_2V88    (PWR_CTRL_PLS_LVL7)

#define STARTUP_VOLT_1V78    (PWR_CTRL_MSB | PWR_CTRL_PLS_LVL0)
#define STARTUP_VOLT_1V88    (PWR_CTRL_MSB | PWR_CTRL_PLS_LVL1)
#define STARTUP_VOLT_1V98    (PWR_CTRL_MSB | PWR_CTRL_PLS_LVL2)
#define STARTUP_VOLT_2V08    (PWR_CTRL_MSB | PWR_CTRL_PLS_LVL3)
#define STARTUP_VOLT_3V28    (PWR_CTRL_MSB | PWR_CTRL_PLS_LVL4)
#define STARTUP_VOLT_3V38    (PWR_CTRL_MSB | PWR_CTRL_PLS_LVL5)
#define STARTUP_VOLT_3V48    (PWR_CTRL_MSB | PWR_CTRL_PLS_LVL6)
#define STARTUP_VOLT_3V58    (PWR_CTRL_MSB | PWR_CTRL_PLS_LVL7)

/** SYSTEM Private Defines **/
#define __SYSTEM_DELAY_US(usec)     do{                                       \
                                    uint32_t delay_end;                   \
                                    CPU_DELAY_INTI();                     \
                                    /* Delay*/                            \
                                    delay_end = DWT_CYCCNT + (usec * (SYSCLK_FREQ/1000000)); \
                                    while(DWT_CYCCNT < delay_end){};      \
                                    CPU_DELAY_DISABLE();                  \
                                  }while(0) 
/*******************************************************************************
 *  Clock Definitions
 *******************************************************************************/
uint32_t SystemCoreClock = SYSCLK_FREQ; /*!< System Clock Frequency (Core Clock) */



static void SetSysClock(void);
static void SetStartupVolt(uint32_t start_volt);

#ifdef DATA_IN_ExtSRAM
extern void SystemInit_ExtMemCtl(void);
#endif /* DATA_IN_ExtSRAM */

/**
 * @brief  Setup the microcontroller system
 *         Initialize the Embedded Flash Interface, the PLL and update the
 *         SystemCoreClock variable.
 * @note   This function should be used only after reset.
 */
void SystemInit(void)
{
    /* FPU settings
     * ------------------------------------------------------------*/
#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    SCB->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2)); /* set CP10 and CP11 Full Access */
#endif

    /* Reset the RCC clock configuration to the default reset state(for debug purpose) */
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

    /* Enable ICACHE and disable Prefetch Buffer */
    FLASH->AC |= (uint32_t)(FLASH_AC_ICAHEN);
    FLASH->AC &= (uint32_t)(~FLASH_AC_PRFTBFEN);

    /* Configure the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers */
    /* Configure the Flash Latency cycles and enable prefetch buffer */
    SetSysClock();

#ifdef VECT_TAB_SRAM
    SCB->VTOR = SRAM_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal SRAM. */
#else
    SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal FLASH. */
#endif
    SetStartupVolt(STARTUP_VOLT_1V78);
    
#ifdef DATA_IN_ExtSRAM
    SystemInit_ExtMemCtl();
#endif /* DATA_IN_ExtSRAM */

}

/**
 * @brief  Update SystemCoreClock variable according to Clock Register Values.
 *         The SystemCoreClock variable contains the core clock (HCLK), it can
 *         be used by the user application to setup the SysTick timer or
 * configure other parameters.
 *
 * @note   Each time the core clock (HCLK) changes, this function must be called
 *         to update SystemCoreClock variable value. Otherwise, any
 * configuration based on this variable will be incorrect.
 *
 * @note   - The system frequency computed by this function is not the real
 *           frequency in the chip. It is calculated based on the predefined
 *           constant and the selected clock source:
 *
 *           - If SYSCLK source is HSI, SystemCoreClock will contain the
 * HSI_VALUE(*)
 *
 *           - If SYSCLK source is HSE, SystemCoreClock will contain the
 * HSE_VALUE(**)
 *
 *           - If SYSCLK source is PLL, SystemCoreClock will contain the
 * HSE_VALUE(**) or HSI_VALUE(*) multiplied by the PLL factors.
 *
 *         (*) HSI_VALUE is a constant defined in n32h47x_48x.h file (default value
 *             8 MHz) but the real value may vary depending on the variations
 *             in voltage and temperature.
 *
 *         (**) HSE_VALUE is a constant defined in N32H47X_48X.h file (default value
 *              8 MHz or 25 MHz, depedning on the product used), user has to
 * ensure that HSE_VALUE is same as the real frequency of the crystal used.
 *              Otherwise, this function may have wrong result.
 *
 *         - The result of this function could be not correct when using
 * fractional value for HSE crystal.
 */
void SystemCoreClockUpdate(void)
{
    uint32_t tmp, pllclk, pllmull, pllpre, plloutdiv, pllsource;
    const uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};

    /* Get SYSCLK source
     * -------------------------------------------------------*/
    tmp = RCC->CFG & RCC_CFG_SCLKSTS;

    switch (tmp)
    {
    case RCC_CFG_SCLKSTS_HSI: /* HSI used as system clock */
        SystemCoreClock = HSI_VALUE;
        break;
    case RCC_CFG_SCLKSTS_HSE: /* HSE used as system clock */
        SystemCoreClock = HSE_VALUE;
        break;
    case RCC_CFG_SCLKSTS_PLL: /* PLL used as system clock */

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
        
        SystemCoreClock = (pllclk / pllpre * pllmull) >> plloutdiv;
        break;

    default:
        SystemCoreClock = HSI_VALUE;
        break;
    }

    /* Compute HCLK clock frequency ----------------*/
    /* Get HCLK prescaler */
    tmp = AHBPrescTable[((RCC->CFG & RCC_CFG_AHBPRES) >> 16)];
    /* HCLK clock frequency */
    SystemCoreClock >>= tmp;
}

/**
 * @brief  Configures the System clock frequency, HCLK, PCLK2 and PCLK1
 * prescalers.
 */
static void SetSysClock(void)
{   
    uint32_t tmpregister, tmpregister1;
    const uint8_t PLLoutpresTable[10] = {0, 0, 1, 1, 2, 2, 2, 2, 3, 3};
    
#if ((SYSCLK_SRC == SYSCLK_USE_HSE) || (SYSCLK_SRC == SYSCLK_USE_HSE_PLL))
    uint32_t HSEStatus;
    uint32_t StartUpCounter = 0;
    /* Enable HSE */
    RCC->CTRL |= ((uint32_t)RCC_CTRL_HSEEN);

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC->CTRL & RCC_CTRL_HSERDF;
        StartUpCounter++;
    } while ((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CTRL & RCC_CTRL_HSERDF) != RCC_CTRL_HSERDF)
    {
        /* If HSE fails to start-up, the application will have wrong clock
         * configuration. User can add here some code to deal with this error */
        SystemCoreClock = HSI_VALUE;
        return;
    }
#endif

    /* Flash wait state
        0: HCLK <= 40M
        1: HCLK <= 80M
        2: HCLK <= 120M
        3: HCLK <= 160M
        4: HCLK <= 200M
        5: HCLK <= 240M
     */
    tmpregister = FLASH->AC;
    tmpregister &= (uint32_t)((uint32_t)~FLASH_AC_LATENCY);
    tmpregister |= (uint32_t)((SYSCLK_FREQ - 1) / 40000000);
    FLASH->AC = tmpregister;
    
    /* HCLK = SYSCLK */
    RCC->CFG |= (uint32_t)RCC_CFG_AHBPRES_DIV1;

    /* PCLK2/PCLK1 max 180M */
    if (SYSCLK_FREQ > 180000000)
    {
        RCC->CFG |= (uint32_t)RCC_CFG_APB2PRES_DIV2;
        RCC->CFG |= (uint32_t)RCC_CFG_APB1PRES_DIV2;
    }
    else
    {
        RCC->CFG |= (uint32_t)RCC_CFG_APB2PRES_DIV1;
        RCC->CFG |= (uint32_t)RCC_CFG_APB1PRES_DIV1;
    }


#if SYSCLK_SRC == SYSCLK_USE_HSE
    tmpregister = RCC->CFG;
     /* Select HSE as system clock source */
    tmpregister &= (uint32_t)((uint32_t) ~(RCC_CFG_SCLKSW));
    tmpregister |= (uint32_t)RCC_CFG_SCLKSW_HSE;
    RCC->CFG = tmpregister;
   
    /* Wait till HSE is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SCLKSTS) != RCC_CFG_SCLKSTS_HSE)
    {
    }
#elif SYSCLK_SRC == SYSCLK_USE_HSI_PLL || SYSCLK_SRC == SYSCLK_USE_HSE_PLL
    
    tmpregister = RCC->CFG;
    tmpregister1 = RCC->PLLCTRL;
    
    /* clear bits */
    tmpregister &= (uint32_t)((uint32_t)~(RCC_CFG_PLLSRC | RCC_CFG_PLLHSEPRES | RCC_CFG_PLLHSIPRES | RCC_CFG_PLLMULFCT));
    tmpregister1 &= (uint32_t)((uint32_t)~(RCC_PLLCTRL_PLLINPRES | RCC_PLLCTRL_PLLOUTPRES | RCC_PLLCTRL_LPFC2| RCC_PLLCTRL_LPFR| RCC_PLLCTRL_LPFC1));
    
    /* set PLL source */
#if SYSCLK_SRC == SYSCLK_USE_HSE_PLL
    tmpregister |= RCC_CFG_PLLSRC;
    tmpregister |= ((PLLSRC_DIV == 1) ? (uint32_t)0x00000000 : RCC_CFG_PLLHSEPRES);
#else
    tmpregister |= ((PLLSRC_DIV == 1) ? (uint32_t)0x00000000 : RCC_CFG_PLLHSIPRES);
#endif

    /* set PLL multiply factor */
    tmpregister |= ((PLL_MUL - 4) / 2) << 3;
    
     /* Set LPFC2[2:0],LPFR[3:0],LPFC1[3:0] bits */
    if((tmpregister&RCC_CFG_PLLMULFCT) <= RCC_CFG_PLLMULFCT24)
    {
        tmpregister1 |= ((uint32_t)0x00006340);
    }
    else if((tmpregister&RCC_CFG_PLLMULFCT) <= RCC_CFG_PLLMULFCT40)
    {
        tmpregister1 |= ((uint32_t)0x00006740);
    }
    else
    {
        tmpregister1 |= ((uint32_t)0x00006C40);
    }
    /* set PLLINPRES[1:0] bits */
    tmpregister1 |= (PLL_INPRE-1)<<16;
    /* set PLLOUTPRES[1:0] bits */
    tmpregister1 |= (uint32_t)PLLoutpresTable[PLL_OUTPRE]<<18;

    RCC->CFG = tmpregister;
    RCC->PLLCTRL = tmpregister1;

    /* Enable PLL */
    RCC->CTRL |= RCC_CTRL_PLLEN;

    /* Wait till PLL is ready */
    while ((RCC->CTRL & RCC_CTRL_PLLRDF) == 0)
    {
    }

    tmpregister = RCC->CFG;
    /* Select PLL as system clock source */
    tmpregister &= (uint32_t)((uint32_t) ~(RCC_CFG_SCLKSW));
    tmpregister |= (uint32_t)RCC_CFG_SCLKSW_PLL;
    RCC->CFG = tmpregister;

    
    /* Wait till PLL is used as system clock source */
    while ((RCC->CFG & (uint32_t)RCC_CFG_SCLKSTS) != RCC_CFG_SCLKSTS_PLL)
    {
        
    }
   
#endif
}

static void SetStartupVolt(uint32_t start_volt)
{
    uint32_t temp_value,i;

    /* Enable PWR clock */
    RCC->APB1PCLKEN |= RCC_APB1PCLKEN_PWREN;

    temp_value = PWR->CTRL;
    /* Clear MSB and PLS[2:0] bits bit */
    temp_value &= (0xFFFFFD1F);
    /* Set MSB and PLS[2:0] bits according to level value */
    temp_value |= start_volt;
    /* Store the new value */
    PWR->CTRL = temp_value;
    /* Enable PVD */
    PWR->CTRL |= PWR_CTRL_PVDEN;
    /* wait VDD go into effect*/
    for(i = 0;i < 2000;i++);
    /* wait PVD out*/
    while(PWR->CTRLSTS & PWR_CTRLSTS_PVDO);
    /* wait VDD stable*/
    __SYSTEM_DELAY_US(1000);
    
    
}

