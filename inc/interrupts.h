/**
 * @file    interrupts.h
 * @brief   Interrupt handler declarations for CANable2-N32
 */

#ifndef _INTERRUPTS_H
#define _INTERRUPTS_H

// Cortex-M4 system exception handlers
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);

// SysTick is handled in system.c

// USB interrupt handlers
void USB_FS_LP_IRQHandler(void);
void USB_FS_WKUP_IRQHandler(void);

#endif
