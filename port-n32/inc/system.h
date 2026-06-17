/**
 * @file    system.h
 * @brief   System initialization and utilities for CANable2-N32
 */

#ifndef _SYSTEM_H
#define _SYSTEM_H

#include <stdint.h>

// Prototypes
void system_init(void);
void system_irq_enable(void);
void system_irq_disable(void);
void system_hex32(char *out, uint32_t val);
uint32_t system_get_ticks(void);
void system_delay(uint32_t ms);

// Compatibility macros for STM32 HAL style API
#define HAL_GetTick()    system_get_ticks()
#define HAL_Delay(ms)    system_delay(ms)

#endif
