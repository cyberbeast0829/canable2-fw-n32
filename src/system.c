/**
 * @file    system.c
 * @brief   System clock initialization for N32H473CEU7
 *
 * Rewritten based on ODrive SystemClock_Config() reference.
 *
 * Clock tree:
 *   HSE -> PLL -> SYSCLK = 240MHz
 *   HCLK  = SYSCLK / 1 = 240MHz
 *   PCLK2 = HCLK   / 2 = 120MHz (APB2)
 *   PCLK1 = HCLK   / 4 = 60MHz  (APB1)
 *
 * For different HSE crystal frequencies, PLL is configured as:
 *   8MHz:  /1 * 60 / 2 = 240MHz
 *  16MHz:  /2 * 30 / 1 = 240MHz
 *  24MHz:  /4 * 40 / 1 = 240MHz
 */

#include "n32h47x_48x.h"
#include "n32h47x_48x_conf.h"
#include "system.h"


// System tick counter (incremented every 1ms by SysTick ISR)
static volatile uint32_t system_ticks = 0;

// Private functions
static void __option_byte_config(void);

/**
 * @brief  System clock configuration — modelled after ODrive SystemClock_Config().
 *
 * Critical ordering:
 *   1. RCC_DeInit()          — reset all clock registers to default
 *   2. Disable LSE
 *   3. Enable HSE, wait stable (RCC_WaitHseStable)
 *   4. Configure bus dividers — BEFORE enabling PLL
 *   5. Configure PLL
 *   6. Enable PLL, wait ready
 *   7. Switch SYSCLK to PLL
 *   8. Wait until PLL confirmed as active SYSCLK
 *   9. SysTick init
 */
void system_init(void)
{
    ErrorStatus status;

    /* ---- 1. Reset RCC to defaults ---- */
    RCC_DeInit();

    /* ---- 2. Disable LSE (not used) ---- */
    RCC_ConfigLse(RCC_LSE_DISABLE);

    /* ---- 3. Enable HSE and wait for stable ---- */
    RCC_ConfigHse(RCC_HSE_ENABLE);
    status = RCC_WaitHseStable();
    if (status != SUCCESS) {
        // HSE failed — trap here (or fall back to HSI)
        while (1);
    }

    /* ---- 4. Configure bus prescalers BEFORE PLL ---- */
    // HCLK = SYSCLK / 1 = 240MHz
    RCC_ConfigHclk(RCC_SYSCLK_DIV1);
    // PCLK2 = HCLK / 2 = 120MHz (APB2)
    RCC_ConfigPclk2(RCC_HCLK_DIV2);
    // PCLK1 = HCLK / 4 = 60MHz  (APB1)
    RCC_ConfigPclk1(RCC_HCLK_DIV4);

    /* ---- 5. Configure PLL ---- */
    // PLL = HSE / PRE * MUL / OUTDIV = 240MHz
#if HSE_VALUE == 8000000
    //  8MHz / 1 * 60 / 2 = 240MHz
    RCC_ConfigPll(RCC_PLL_SRC_HSE, RCC_PLL_PRE_1, RCC_PLL_MUL_60, RCC_PLLOUT_DIV_2);
#elif HSE_VALUE == 16000000
    // 16MHz / 2 * 30 / 1 = 240MHz
    RCC_ConfigPll(RCC_PLL_SRC_HSE, RCC_PLL_PRE_2, RCC_PLL_MUL_30, RCC_PLLOUT_DIV_1);
#elif HSE_VALUE == 24000000
    // 24MHz / 4 * 40 / 1 = 240MHz (same as ODrive)
    RCC_ConfigPll(RCC_PLL_SRC_HSE, RCC_PLL_PRE_4, RCC_PLL_MUL_40, RCC_PLLOUT_DIV_1);
#else
#warning "Unknown HSE_VALUE — using generic /1*30/1 PLL config"
    // Generic: HSE / 1 * 30 / 1 — adjust for your crystal!
    RCC_ConfigPll(RCC_PLL_SRC_HSE, RCC_PLL_PRE_1, RCC_PLL_MUL_30, RCC_PLLOUT_DIV_1);
#endif

    /* ---- 6. Enable PLL and wait for lock ---- */
    RCC_EnablePll(ENABLE);
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDF) == RESET);

    /* ---- 7. Switch SYSCLK to PLL ---- */
    RCC_ConfigSysclk(RCC_SYSCLK_SRC_PLL);

    /* ---- 8. Wait until PLL is confirmed as active SYSCLK ---- */
    while (RCC_GetSysclkSrc() != RCC_CFG_SCLKSTS_PLL);

    /* ---- 9. Update global SystemCoreClock ---- */
    // SystemCoreClock = 240000000;

    /* ---- 10. Enable common GPIO clocks ---- */
    RCC_EnableAHB1PeriphClk(RCC_AHB_PERIPHEN_GPIOA |
                            RCC_AHB_PERIPHEN_GPIOB |
                            RCC_AHB_PERIPHEN_GPIOC,
                            ENABLE);

    /* ---- 11. Configure SysTick (HCLK source, 1ms interval) ---- */
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
    SysTick_Config(SystemCoreClock / 1000);
    NVIC_SetPriority(SysTick_IRQn, 0);

    /* ---- 12. Option bytes ---- */
    __option_byte_config();
}


// SysTick interrupt handler — increment 1ms counter
void SysTick_Handler(void)
{
    system_ticks++;
}


uint32_t system_get_ticks(void)
{
    return system_ticks;
}


void system_delay(uint32_t ms)
{
    uint32_t start = system_ticks;
    while ((system_ticks - start) < ms);
}


void system_irq_disable(void)
{
    __disable_irq();
    __DSB();
    __ISB();
}


void system_irq_enable(void)
{
    __enable_irq();
}


void system_hex32(char *out, uint32_t val)
{
    char *p = out + 8;
    *p-- = 0;
    while (p >= out) {
        uint8_t nybble = val & 0x0F;
        if (nybble < 10)
            *p = '0' + nybble;
        else
            *p = 'A' + nybble - 10;
        val >>= 4;
        p--;
    }
}


static void __option_byte_config(void)
{
    FLASH_Unlock();
    // TODO: configure user option bytes for your hardware if needed
    FLASH_Lock();
}
