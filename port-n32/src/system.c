/**
 * @file    system.c
 * @brief   System clock initialization for N32H473CEU7
 * 
 * Clock configuration:
 *   HSE (8MHz) → PLL → SYSCLK = 240MHz (8M /1 *60 /2)
 *   HCLK = 240MHz, PCLK1 = 120MHz, PCLK2 = 120MHz
 *   USB: PLL → /5 → 48MHz (configured in usb_device.c)
 *   FDCAN: PLL → /6 → 40MHz (configured in can.c)
 */

#include "n32h47x_48x.h"
#include "n32h47x_48x_conf.h"
#include "system.h"

// HSE crystal frequency
#ifndef HSE_VALUE
#define HSE_VALUE 8000000
#endif

// SystemCoreClock variable (required by CMSIS)
uint32_t SystemCoreClock = 240000000;

// System tick counter (incremented every 1ms by SysTick ISR)
static volatile uint32_t system_ticks = 0;

// Private functions
static void __option_byte_config(void);


/**
 * @brief  SystemInit - called from startup before main().
 *         Minimal hardware initialization: FPU, cache, vector table.
 */
void SystemInit(void)
{
    // Enable FPU
    #if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
    SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2));  // Full access to CP10/CP11
    #endif

    // Set interrupt priority grouping: 4 bits preemption, 0 bits subpriority
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

    // Configure vector table offset (Flash base)
    SCB->VTOR = FLASH_BASE;

    // Enable SRAM clock for ECC
    RCC->AHB1PCLKEN |= RCC_AHB_PERIPHEN_SRAM;
}


/**
 * @brief  Initialize system clocks for N32H473CEU7.
 *         Called from main() after C runtime initialization.
 */
void system_init(void)
{
    // Enable HSE
    RCC_ConfigHse(RCC_HSE_ENABLE);

    // Wait for HSE ready
    while (RCC_GetFlagStatus(RCC_FLAG_HSERDF) == RESET);

    // Configure PLL: HSE /1 *60 /2 = 240MHz
    RCC_ConfigPll(RCC_PLL_SRC_HSE, RCC_PLL_PRE_1, RCC_PLL_MUL_60, RCC_PLLOUT_DIV_2);

    // Enable PLL
    RCC_EnablePll(ENABLE);

    // Wait for PLL ready
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDF) == RESET);

    // Configure Flash latency for 240MHz
    FLASH_SetLatency(FLASH_LATENCY_5);

    // Configure AHB, APB1, APB2 prescalers
    RCC_ConfigHclk(RCC_SYSCLK_DIV1);   // HCLK = SYSCLK = 240MHz
    RCC_ConfigPclk1(RCC_HCLK_DIV2);    // PCLK1 = HCLK/2 = 120MHz
    RCC_ConfigPclk2(RCC_HCLK_DIV2);    // PCLK2 = HCLK/2 = 120MHz

    // Select PLL as SYSCLK source
    RCC_ConfigSysclk(RCC_SYSCLK_SRC_PLL);

    // Enable peripheral clocks for common GPIO ports
    RCC_EnableAHB1PeriphClk(RCC_AHB_PERIPHEN_GPIOA |
                            RCC_AHB_PERIPHEN_GPIOB |
                            RCC_AHB_PERIPHEN_GPIOC,
                            ENABLE);

    // Update SystemCoreClock variable
    SystemCoreClock = 240000000;

    // Configure SysTick: 1ms tick
    SysTick_Config(SystemCoreClock / 1000);

    // Set SysTick priority
    NVIC_SetPriority(SysTick_IRQn, 0);

    // Configure option bytes
    __option_byte_config();
}


// SysTick interrupt handler - increment tick counter
void SysTick_Handler(void)
{
    system_ticks++;
}


// Get current system tick count (ms)
uint32_t system_get_ticks(void)
{
    return system_ticks;
}


// Blocking delay in milliseconds
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


// Convert a 32-bit value to an ascii hex value
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


// Configure option bytes
static void __option_byte_config(void)
{
    FLASH_Unlock();
    // Configure user option bytes if needed for your hardware
    FLASH_Lock();
}
