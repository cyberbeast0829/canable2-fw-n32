/**
 * @file    usb_init.c
 * @brief   USB FS peripheral initialization for CANable2-N32
 *
 * Brings up the USB FS device peripheral (clock, pins, interrupts, core).
 * The gs_usb protocol is implemented in gs_usb.c / usb_prop.c / usb_endp.c.
 */

#include "n32h47x_48x.h"
#include "n32h47x_48x_conf.h"
#include "usbfsd_lib.h"
#include "usb_conf.h"
#include "usb_init.h"


// USB device initialization (clock, pins, interrupts, core)
void usb_init(void)
{
    NVIC_InitType nvic;
    EXTI_InitType exti;
    GPIO_InitType gpio;

    // Configure USB clock: PLL output → /5 → 48MHz for USB FS
    RCC_ConfigUSBFSClk(RCC_USBFS_CLKSRC_PLLPRES);
    RCC_ConfigUSBPLLPresClk(RCC_USBPLLCLK_SRC_PLL, RCC_USBPLLCLK_DIV5);
    RCC->CFG3 |= RCC_CFG3_USBFSTM;

    // Enable USB clock
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_USBFS, ENABLE);

    // Enable AFIO and GPIO clocks
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
    RCC_EnableAHB1PeriphClk(RCC_AHB_PERIPHEN_GPIOA, ENABLE);

    // Configure USB pins: PA11=DM, PA12=DP, AF10
    GPIO_InitStruct(&gpio);
    gpio.Pin = GPIO_PIN_11 | GPIO_PIN_12;
    gpio.GPIO_Mode = GPIO_MODE_AF_PP;
    gpio.GPIO_Alternate = GPIO_AF10;
    gpio.GPIO_Pull = GPIO_NO_PULL;
    gpio.GPIO_Slew_Rate = GPIO_SLEW_RATE_FAST;
    gpio.GPIO_Current = GPIO_DC_12mA;
    GPIO_InitPeripheral(GPIOA, &gpio);

    // Enable USB LP interrupt
    nvic.NVIC_IRQChannel = USB_FS_LP_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 6;
    nvic.NVIC_IRQChannelSubPriority = 0;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);

    // Enable USB Wakeup interrupt
    nvic.NVIC_IRQChannel = USB_FS_WKUP_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 9;
    nvic.NVIC_IRQChannelSubPriority = 0;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);

    // Configure EXTI line 18 for USB wakeup
    EXTI_ClrITPendBit(EXTI_LINE18);
    exti.EXTI_Line = EXTI_LINE18;
    exti.EXTI_Mode = EXTI_Mode_Interrupt;
    exti.EXTI_Trigger = EXTI_Trigger_Rising;
    exti.EXTI_LineCmd = ENABLE;
    EXTI_InitPeripheral(&exti);

    // Initialize USB core (descriptors registered via usb_prop.c)
    USB_Init();
}
