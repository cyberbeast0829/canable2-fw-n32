/**
 * @file    interrupts.c
 * @brief   Interrupt Service Routines for CANable2-N32
 */

#include "n32h47x_48x.h"
#include "n32h47x_48x_conf.h"
#include "interrupts.h"
#include "led.h"

// N32 USB interrupt service routine (application-level, defined in usb_istr.c)
extern void USB_Istr(void);


// System exception handlers

void NMI_Handler(void)
{
    while (1);
}

void HardFault_Handler(void)
{
    while (1)
    {
        // Fault indicator
    }
}

void MemManage_Handler(void)
{
    while (1);
}

void BusFault_Handler(void)
{
    while (1);
}

void UsageFault_Handler(void)
{
    while (1);
}

void SVC_Handler(void)
{
}

void DebugMon_Handler(void)
{
}

void PendSV_Handler(void)
{
}


// USB Full-Speed Low Priority interrupt
void USB_FS_LP_IRQHandler(void)
{
    USB_Istr();
}


// USB Full-Speed Wakeup interrupt
void USB_FS_WKUP_IRQHandler(void)
{
    // Handle USB wakeup from suspend via EXTI Line 18
    if (EXTI_GetITStatus(EXTI_LINE18) != RESET)
    {
        EXTI_ClrITPendBit(EXTI_LINE18);
    }
}
