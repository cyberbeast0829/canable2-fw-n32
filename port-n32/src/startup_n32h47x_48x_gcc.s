/*********************************************************************************************************
     Copyright (c) 2024, Nations Technologies Inc.
 
     All rights reserved.

     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
 referred to as NATIONS). This software, and the product of NATIONS described herein 
 (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
 of the People's Republic of China and other applicable jurisdictions worldwide.

     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
 intellectual property rights. Names and brands of third party may be mentioned or referred 
 thereto (if any) for identification purposes only.

     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
 improvements to this software at any time without notice. Please contact NATIONS and obtain 
 the latest version of this software before placing orders.

     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
 no responsibility for the accuracy and reliability of this software.
 
     It is the responsibility of the user of this software to properly design, program, and test 
 the functionality and safety of any application made of this information and any resulting product. 
 In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
 consequential damages arising in any way out of the use of this software or the Product.

     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
 malfunction or failure of which may cause loss of human life, bodily injury or severe property 
 damage. Such applications are deemed, "Insecure Usage".

     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
 harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
 to any customer's Insecure Usage.

     Any express or implied warranty with regard to this software or the Product, including,but not 
 limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
 are disclaimed to the fullest extent permitted by law.

     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
 or otherwise distribute this software for any purposes, in whole or in part.

     NATIONS products and technologies shall not be used for or incorporated into any products or systems
 whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
 User shall comply with any applicable export control laws and regulations promulgated and administered by 
 the governments of any countries asserting jurisdiction over the parties or transactions.
 ************************************************************************************************************/


  .syntax unified
  .cpu cortex-m4
  .fpu softvfp
  .thumb

.global g_pfnVectors
.global Default_Handler

/* start address for the initialization values of the .data section.
defined in linker script */
.word _sidata
/* start address for the .data section. defined in linker script */
.word _sdata
/* end address for the .data section. defined in linker script */
.word _edata
/* start address for the .bss section. defined in linker script */
.word _sbss
/* end address for the .bss section. defined in linker script */
.word _ebss

  .section .text.Reset_Handler
  .weak Reset_Handler
  .type Reset_Handler, %function
Reset_Handler:
  ldr   r0, =_estack
  mov   sp, r0          /* set stack pointer */

/* Copy the data segment initializers from flash to SRAM */
  ldr r0, =_sdata
  ldr r1, =_edata
  ldr r2, =_sidata
  movs r3, #0
  b LoopCopyDataInit

CopyDataInit:
  ldr r4, [r2, r3]
  str r4, [r0, r3]
  adds r3, r3, #4

LoopCopyDataInit:
  adds r4, r0, r3
  cmp r4, r1
  bcc CopyDataInit
  
/* Zero fill the bss segment. */
  ldr r2, =_sbss
  ldr r4, =_ebss
  movs r3, #0
  b LoopFillZerobss

FillZerobss:
  str  r3, [r2]
  adds r2, r2, #4

LoopFillZerobss:
  cmp r2, r4
  bcc FillZerobss

/* Call the clock system intitialization function.*/
  bl  SystemInit
/* Call static constructors */
  bl __libc_init_array
/* Call the application's entry point.*/
  bl main

LoopForever:
    b LoopForever


.size Reset_Handler, .-Reset_Handler

/**
\*fun      This is the code that gets called when the processor receives an
\*         unexpected interrupt.  This simply enters an infinite loop, preserving
\*         the system state for examination by a debugger.
**/
    .section .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
  b Infinite_Loop
  .size Default_Handler, .-Default_Handler
/**
\* The minimal vector table for a Cortex M0.  Note that the proper constructs
\* must be placed on this to ensure that it ends up at physical address 0x00000000.
**/
   .section .isr_vector,"a",%progbits
  .type g_pfnVectors, %object
  .size g_pfnVectors, .-g_pfnVectors


g_pfnVectors:
  .word  _estack
  .word  Reset_Handler
  .word  NMI_Handler
  .word  HardFault_Handler
  .word  MemManage_Handler
  .word  BusFault_Handler
  .word  UsageFault_Handler
  .word  0
  .word  0
  .word  0
  .word  0
  .word  SVC_Handler
  .word  DebugMon_Handler
  .word  0
  .word  PendSV_Handler
  .word  SysTick_Handler  
  /* External Interrupts */
  .word  WWDG_IRQHandler                  /* Window watchdog interrupt */
  .word  PVD_IRQHandler                   /* PVD through EXTI Line16 detection interrupt */
  .word  RTC_TAMPER_IRQHandler            /* RTC Tamper or LSE-CSS through EXTI Line19 interrupt */
  .word  RTC_WKUP_IRQHandler              /* RTC Wakeup timer through EXTI line 20 interrupt */
  .word  FLASH_IRQHandler                 /* Flash global interrupt */
  .word  RCC_IRQHandler                   /* RCC global interrupt */
  .word  EXTI0_IRQHandler                 /* EXTI Line0 interrupt */
  .word  EXTI1_IRQHandler                 /* EXTI Line1 interrupt */
  .word  EXTI2_IRQHandler                 /* EXTI Line2 interrupt */
  .word  EXTI3_IRQHandler                 /* EXTI Line3 interrupt */
  .word  EXTI4_IRQHandler                 /* EXTI Line4 interrupt */
  .word  DMA1_Channel1_IRQHandler         /* DMA1 Channel1 global interrupt */
  .word  DMA1_Channel2_IRQHandler         /* DMA1 Channel2 global interrupt */
  .word  DMA1_Channel3_IRQHandler         /* DMA1 Channel3 global interrupt */
  .word  DMA1_Channel4_IRQHandler         /* DMA1 Channel4 global interrupt */
  .word  DMA1_Channel5_IRQHandler         /* DMA1 Channel5 global interrupt */
  .word  DMA1_Channel6_IRQHandler         /* DMA1 Channel6 global interrupt */
  .word  DMA1_Channel7_IRQHandler         /* DMA1 Channel7 global interrupt */
  .word  ADC1_2_IRQHandler                /* ADC1 and ADC2 global interrupt */
  .word  USB_FS_HP_IRQHandler             /* USB FS Device High Priority interrupt */
  .word  USB_FS_LP_IRQHandler             /* USB FS Device Low Priority interrupt */
  .word  FDCAN1_INT0_IRQHandler           /* FDCAN1 interrupt LINE 0 */
  .word  FDCAN1_INT1_IRQHandler           /* FDCAN1 interrupt LINE 1 */
  .word  EXTI9_5_IRQHandler               /* EXTI Line[9:5] interrupt */
  .word  ATIM1_BRK_IRQHandler             /* ATIM1 Break interrupt */
  .word  ATIM1_UP_IRQHandler              /* ATIM1 Update interrupt */
  .word  ATIM1_TRG_COM_IRQHandler         /* ATIM1 Trigger and Commutation interrupt */
  .word  ATIM1_CC_IRQHandler              /* ATIM1 Capture Compare interrupt */
  .word  GTIM1_IRQHandler                 /* GTIM1 global interrupt */
  .word  GTIM2_IRQHandler                 /* GTIM2 global interrupt */
  .word  GTIM3_IRQHandler                 /* GTIM3 global interrupt */
  .word  I2C1_EV_IRQHandler               /* I2C1 event interrupt */
  .word  I2C1_ER_IRQHandler               /* I2C1 error interrupt */
  .word  I2C2_EV_IRQHandler               /* I2C2 event interrupt */
  .word  I2C2_ER_IRQHandler               /* I2C2 error interrupt */
  .word  SPI1_IRQHandler                  /* SPI1 global interrupt */
  .word  SPI2_I2S2_IRQHandler             /* SPI2/I2S2 global interrupt */
  .word  USART1_IRQHandler                /* USART1 global interrupt */
  .word  USART2_IRQHandler                /* USART2 global interrupt */
  .word  USART3_IRQHandler                /* USART3 global interrupt */
  .word  EXTI15_10_IRQHandler             /* EXTI Line[15:10] interrupt */
  .word  RTCAlarm_IRQHandler              /* RTC alarm through EXTI line17 interrupt */
  .word  USB_FS_WKUP_IRQHandler           /* USB FS Device wakeup from suspend through EXTI line18 interrupt */
  .word  ATIM2_BRK_IRQHandler             /* ATIM2 Break interrupt */
  .word  ATIM2_UP_IRQHandler              /* ATIM2 Update interrupt */
  .word  ATIM2_TRG_COM_IRQHandler         /* ATIM2 Trigger and Commutation interrupt */
  .word  ATIM2_CC_IRQHandler              /* ATIM2 Capture Compare interrupt */
  .word  ADC3_ADC4_IRQHandler             /* ADC3_ADC4 global interrupt */
  .word  UCDR_IRQHandler                  /* UCDR error interrupt */
  .word  SDIO_IRQHandler                  /* SDIO global interrupt */
  .word  GTIM4_IRQHandler                 /* GTIM4 global interrupt */
  .word  SPI3_I2S3_IRQHandler             /* SPI3/I2S3 global interrupt */
  .word  USART4_IRQHandler                /* USART4 global interrupt */
  .word  UART5_IRQHandler                 /* UART5 global interrupt */
  .word  BTIM1_IRQHandler                 /* BTIM1 global interrupt */
  .word  BTIM2_IRQHandler                 /* BTIM2 global interrupt */
  .word  DMA2_Channel1_IRQHandler         /* DMA2 Channel1 global interrupt */
  .word  DMA2_Channel2_IRQHandler         /* DMA2 Channel2 global interrupt */
  .word  DMA2_Channel3_IRQHandler         /* DMA2 Channel3 global interrupt */
  .word  DMA2_Channel4_IRQHandler         /* DMA2 Channel4 global interrupt */
  .word  DMA2_Channel5_IRQHandler         /* DMA2 Channel5 global interrupt */
  .word  SRAM_ERR_IRQHandler              /* SRAM ECC error */
  .word  COMP4_5_6_IRQHandler            /* COMP4&COMP5&COMP6 through EXTI Line22/30/31 interrupt */
  .word  FDCAN2_INT0_IRQHandler           /* FDCAN2 interrupt 0 */ 
  .word  FDCAN2_INT1_IRQHandler           /* FDCAN2 interrupt 1 */ 
  .word  FDCAN3_INT0_IRQHandler           /* FDCAN3 interrupt 0 */ 
  .word  FDCAN3_INT1_IRQHandler           /* FDCAN3 interrupt 1 */
  .word  XSPI_IRQHandler                  /* XSPI global interrupt */
  .word  DMA2_Channel6_IRQHandler         /* DMA2 Channel6 global interrupt */
  .word  DMA2_Channel7_IRQHandler         /* DMA2 Channel7 global interrupt */
  .word  I2C3_EV_IRQHandler               /* I2C3 event interrupt */
  .word  I2C3_ER_IRQHandler               /* I2C3 error interrupt */
  .word  I2C4_EV_IRQHandler               /* I2C4 event interrupt */
  .word  I2C4_ER_IRQHandler               /* I2C4 error interrupt */
  .word  UART6_IRQHandler                 /* UART6 global interrupt */
  .word  UART7_IRQHandler                 /* UART7 global interrupt */
  .word  DMA1_Channel8_IRQHandler         /* DMA1 Channel8 global interrupt */
  .word  DMA2_Channel8_IRQHandler         /* DMA2 Channel8 global interrupt */
  .word  DVP_IRQHandler                   /* DVP global interrupt */
  .word  SAC_IRQHandler                   /* SAC global interrupt */
  .word  SMPU_IRQHandler                  /* SMPU global interrupt */
  .word  COMP1_2_3_IRQHandler         /* COMP1 & COMP2 & COMP3 through EXTI Line21/28/29 interrupt */  
  .word  USB_HS_EPx_OUT_IRQHandler        /* need check to user manual of exti chapter  USB HS End Point 1 Out global interrupt */
  .word  USB_HS_EPx_IN_IRQHandler         /* need check to user manual of exti chapter  USB HS End Point 1 Inglobal interrupt */
  .word  USB_HS_WKUP_IRQHandler           /* need check to user manual of exti chapter  USB HS wakeup from suspend through EXTI line23 interrupt */
  .word  UART8_IRQHandler                 /* USART8 global interrupt */
  .word  SPI4_IRQHandler                  /* SPI4 global interrupt */
  .word  ETH_IRQHandler                   /* Ethernet global interrupt */
  .word  ETH_WKUP_IRQHandler              /* Ethernet Wakeup through EXTI Line 27 interrupt */
  .word  GTIM5_IRQHandler                 /* GTIM5 global interrupt */
  .word  COMP7_IRQHandler                 /* COMP7 through EXTI Line24 interrupt */
  .word  SHRT1_MST_IRQHandler         /* SHRTIM1 master interrupt */
  .word  SHRT1_TIMA_IRQHandler        /* SHRTIM1 timer A interrupt */
  .word  SHRT1_TIMB_IRQHandler        /* SHRTIM1 Timer B interrupt */
  .word  SHRT1_TIMC_IRQHandler        /* SHRTIM1 Timer C interrupt */
  .word  SHRT1_TIMD_IRQHandler        /* SHRTIM1 Timer D interrupt */
  .word  SHRT1_TIME_IRQHandler        /* SHRTIM1 Timer E interrupt */
  .word  SHRT1_TIMF_IRQHandler        /* SHRTIM1 Timer F interrupt */
  .word  SHRT1_FLT_IRQHandler           /* SHRTIM1 fault  interrupt */
  .word  ATIM3_BRK_IRQHandler             /* ATIM3 Break interrupt */
  .word  ATIM3_UP_IRQHandler              /* ATIM3 Update interrupt */
  .word  ATIM3_TRG_COM_IRQHandler         /* ATIM3 Trigger and Commutation interrupt */
  .word  ATIM3_CC_IRQHandler              /* ATIM3 Capture Compare interrupt */
  .word  GTIM6_IRQHandler                 /* GTIM6 global interrupt */
  .word  LPTIM1_WKUP_IRQHandler           /* LPTIM1 wakeup through EXTI Line 25 interrup interrupt */
  .word  LPTIM2_WKUP_IRQHandler           /* LPTIM2 wakeup through EXTI Line 26 interrup interrupt */
  .word  FMAC_IRQ_IRQHandler              /* FMAC global interrupt */
  .word  Cordic_IRQ_IRQHandler            /* Cordic global interrupt */
  .word  SPI5_IRQHandler                  /* SPI5 global interrupt */
  .word  SPI6_IRQHandler                  /* SPI6 global interrupt */
  .word  GTIM7_IRQHandler                 /* GTIM7 global interrupt */
  .word  GTIM8_IRQHandler                 /* GTIM8 global interrupt */
  .word  GTIM9_IRQHandler                 /* GTIM9 global interrupt */
  .word  GTIM10_IRQHandler                /* GTIM10 global interrupt */
  .word  DAC1_2_3_4_Underflow_IRQHandler  /* DAC1/2/3/4 underflow interrupt */
  .word  DAC5_6_7_8_Underflow_IRQHandler  /* DAC5/6/7/8 underflow interrupt */
  .word  USB_HS_IRQHandler                /* USB HS global interrupt  */
  .word  FEMC_IRQHandler                  /* FEMC nand interrupt */ 
  /* need check to user manual of exti chapter   */

/**
\* Provide weak aliases for each Exception handler to the Default_Handler.
\* As they are weak aliases, any function with the same name will override
\* this definition.
**/

  .weak      NMI_Handler
  .thumb_set NMI_Handler,Default_Handler

  .weak      HardFault_Handler
  .thumb_set HardFault_Handler,Default_Handler

  .weak      MemManage_Handler
  .thumb_set MemManage_Handler,Default_Handler
  
  .weak      BusFault_Handler
  .thumb_set BusFault_Handler,Default_Handler

  .weak      UsageFault_Handler
  .thumb_set UsageFault_Handler,Default_Handler

  .weak      SVC_Handler
  .thumb_set SVC_Handler,Default_Handler

  .weak      DebugMon_Handler
  .thumb_set DebugMon_Handler,Default_Handler

  .weak      PendSV_Handler
  .thumb_set PendSV_Handler,Default_Handler

  .weak      SysTick_Handler
  .thumb_set SysTick_Handler,Default_Handler

  .weak      WWDG_IRQHandler
  .thumb_set WWDG_IRQHandler,Default_Handler

  .weak      PVD_IRQHandler
  .thumb_set PVD_IRQHandler,Default_Handler
  
  .weak      RTC_TAMPER_IRQHandler
  .thumb_set RTC_TAMPER_IRQHandler,Default_Handler
  
  .weak      RTC_WKUP_IRQHandler
  .thumb_set RTC_WKUP_IRQHandler,Default_Handler
  
  .weak      FLASH_IRQHandler
  .thumb_set FLASH_IRQHandler,Default_Handler

  .weak      RCC_IRQHandler
  .thumb_set RCC_IRQHandler,Default_Handler

  .weak      EXTI0_IRQHandler
  .thumb_set EXTI0_IRQHandler,Default_Handler
  
  .weak      EXTI1_IRQHandler
  .thumb_set EXTI1_IRQHandler,Default_Handler
  
  .weak      EXTI2_IRQHandler
  .thumb_set EXTI2_IRQHandler,Default_Handler
  
  .weak      EXTI3_IRQHandler
  .thumb_set EXTI3_IRQHandler,Default_Handler

  .weak      EXTI4_IRQHandler
  .thumb_set EXTI4_IRQHandler,Default_Handler

  .weak      DMA1_Channel1_IRQHandler
  .thumb_set DMA1_Channel1_IRQHandler,Default_Handler
  
  .weak      DMA1_Channel2_IRQHandler
  .thumb_set DMA1_Channel2_IRQHandler,Default_Handler
  
  .weak      DMA1_Channel3_IRQHandler
  .thumb_set DMA1_Channel3_IRQHandler,Default_Handler
  
  .weak      DMA1_Channel4_IRQHandler
  .thumb_set DMA1_Channel4_IRQHandler,Default_Handler
  
  .weak      DMA1_Channel5_IRQHandler
  .thumb_set DMA1_Channel5_IRQHandler,Default_Handler
  
  .weak      DMA1_Channel6_IRQHandler
  .thumb_set DMA1_Channel6_IRQHandler,Default_Handler
  
  .weak      DMA1_Channel7_IRQHandler
  .thumb_set DMA1_Channel7_IRQHandler,Default_Handler
  
  .weak      ADC1_2_IRQHandler
  .thumb_set ADC1_2_IRQHandler,Default_Handler
  
  .weak      USB_FS_HP_IRQHandler
  .thumb_set USB_FS_HP_IRQHandler,Default_Handler
  
  .weak      USB_FS_LP_IRQHandler
  .thumb_set USB_FS_LP_IRQHandler,Default_Handler
  
  .weak      FDCAN1_INT0_IRQHandler
  .thumb_set FDCAN1_INT0_IRQHandler,Default_Handler
  
  .weak      FDCAN1_INT1_IRQHandler
  .thumb_set FDCAN1_INT1_IRQHandler,Default_Handler
  
  .weak      EXTI9_5_IRQHandler
  .thumb_set EXTI9_5_IRQHandler,Default_Handler

  .weak      ATIM1_BRK_IRQHandler
  .thumb_set ATIM1_BRK_IRQHandler,Default_Handler

  .weak      ATIM1_UP_IRQHandler
  .thumb_set ATIM1_UP_IRQHandler,Default_Handler

  .weak      ATIM1_TRG_COM_IRQHandler
  .thumb_set ATIM1_TRG_COM_IRQHandler,Default_Handler
  
  .weak      ATIM1_CC_IRQHandler
  .thumb_set ATIM1_CC_IRQHandler,Default_Handler
  
  .weak      GTIM1_IRQHandler
  .thumb_set GTIM1_IRQHandler,Default_Handler

  .weak      GTIM2_IRQHandler
  .thumb_set GTIM2_IRQHandler,Default_Handler

  .weak      GTIM3_IRQHandler
  .thumb_set GTIM3_IRQHandler,Default_Handler
  
  .weak      I2C1_EV_IRQHandler
  .thumb_set I2C1_EV_IRQHandler,Default_Handler

  .weak      I2C1_ER_IRQHandler
  .thumb_set I2C1_ER_IRQHandler,Default_Handler

  .weak      I2C2_EV_IRQHandler
  .thumb_set I2C2_EV_IRQHandler,Default_Handler

  .weak      I2C2_ER_IRQHandler
  .thumb_set I2C2_ER_IRQHandler,Default_Handler

  .weak      SPI1_IRQHandler
  .thumb_set SPI1_IRQHandler,Default_Handler
  
  .weak      SPI2_I2S2_IRQHandler
  .thumb_set SPI2_I2S2_IRQHandler,Default_Handler

  .weak      USART1_IRQHandler
  .thumb_set USART1_IRQHandler,Default_Handler

  .weak      USART2_IRQHandler
  .thumb_set USART2_IRQHandler,Default_Handler

  .weak      USART3_IRQHandler
  .thumb_set USART3_IRQHandler,Default_Handler
  
  .weak      EXTI15_10_IRQHandler
  .thumb_set EXTI15_10_IRQHandler,Default_Handler
  
  .weak      RTCAlarm_IRQHandler
  .thumb_set RTCAlarm_IRQHandler,Default_Handler
  
  .weak      USB_FS_WKUP_IRQHandler
  .thumb_set USB_FS_WKUP_IRQHandler,Default_Handler

  .weak      ATIM2_BRK_IRQHandler
  .thumb_set ATIM2_BRK_IRQHandler,Default_Handler

  .weak      ATIM2_UP_IRQHandler
  .thumb_set ATIM2_UP_IRQHandler,Default_Handler
  
  .weak      ATIM2_TRG_COM_IRQHandler
  .thumb_set ATIM2_TRG_COM_IRQHandler,Default_Handler
  
  .weak      ATIM2_CC_IRQHandler
  .thumb_set ATIM2_CC_IRQHandler,Default_Handler
  
  .weak      ADC3_ADC4_IRQHandler
  .thumb_set ADC3_ADC4_IRQHandler,Default_Handler
  
  .weak      UCDR_IRQHandler
  .thumb_set UCDR_IRQHandler,Default_Handler

  .weak      SDIO_IRQHandler
  .thumb_set SDIO_IRQHandler,Default_Handler
  
  .weak      GTIM4_IRQHandler
  .thumb_set GTIM4_IRQHandler,Default_Handler
  
  .weak      SPI3_I2S3_IRQHandler
  .thumb_set SPI3_I2S3_IRQHandler,Default_Handler
  
  .weak      USART4_IRQHandler
  .thumb_set USART4_IRQHandler,Default_Handler
  
  .weak      UART5_IRQHandler
  .thumb_set UART5_IRQHandler,Default_Handler
  
  .weak      BTIM1_IRQHandler
  .thumb_set BTIM1_IRQHandler,Default_Handler
  
  .weak      BTIM2_IRQHandler
  .thumb_set BTIM2_IRQHandler,Default_Handler
  
  .weak      DMA2_Channel1_IRQHandler
  .thumb_set DMA2_Channel1_IRQHandler,Default_Handler
  
  .weak      DMA2_Channel2_IRQHandler
  .thumb_set DMA2_Channel2_IRQHandler,Default_Handler
  
  .weak      DMA2_Channel3_IRQHandler
  .thumb_set DMA2_Channel3_IRQHandler,Default_Handler
  
  .weak      DMA2_Channel4_IRQHandler
  .thumb_set DMA2_Channel4_IRQHandler,Default_Handler
  
  .weak      DMA2_Channel5_IRQHandler
  .thumb_set DMA2_Channel5_IRQHandler,Default_Handler
  
  .weak      SRAM_ERR_IRQHandler
  .thumb_set SRAM_ERR_IRQHandler,Default_Handler
  
  .weak      COMP4_5_6_IRQHandler
  .thumb_set COMP4_5_6_IRQHandler,Default_Handler
  
  .weak      FDCAN2_INT0_IRQHandler
  .thumb_set FDCAN2_INT0_IRQHandler,Default_Handler
  
  .weak      FDCAN2_INT1_IRQHandler
  .thumb_set FDCAN2_INT1_IRQHandler,Default_Handler
  
  .weak      FDCAN3_INT0_IRQHandler
  .thumb_set FDCAN3_INT0_IRQHandler,Default_Handler
  
  .weak      FDCAN3_INT1_IRQHandler
  .thumb_set FDCAN3_INT1_IRQHandler,Default_Handler
  
  .weak      XSPI_IRQHandler
  .thumb_set XSPI_IRQHandler,Default_Handler
  
  .weak      DMA2_Channel6_IRQHandler
  .thumb_set DMA2_Channel6_IRQHandler,Default_Handler
  
  .weak      DMA2_Channel7_IRQHandler
  .thumb_set DMA2_Channel7_IRQHandler,Default_Handler
  
  .weak      I2C3_EV_IRQHandler
  .thumb_set I2C3_EV_IRQHandler,Default_Handler
  
  .weak      I2C3_ER_IRQHandler
  .thumb_set I2C3_ER_IRQHandler,Default_Handler
  
  .weak      I2C4_EV_IRQHandler
  .thumb_set I2C4_EV_IRQHandler,Default_Handler
  
  .weak      I2C4_ER_IRQHandler
  .thumb_set I2C4_ER_IRQHandler,Default_Handler
  
  .weak      UART6_IRQHandler
  .thumb_set UART6_IRQHandler,Default_Handler
  
  .weak      UART7_IRQHandler
  .thumb_set UART7_IRQHandler,Default_Handler
  
  .weak      DMA1_Channel8_IRQHandler
  .thumb_set DMA1_Channel8_IRQHandler,Default_Handler
  
  .weak      DMA2_Channel8_IRQHandler
  .thumb_set DMA2_Channel8_IRQHandler,Default_Handler
  
  .weak      DVP_IRQHandler
  .thumb_set DVP_IRQHandler,Default_Handler
  
  .weak      SAC_IRQHandler
  .thumb_set SAC_IRQHandler,Default_Handler
  
  .weak      SMPU_IRQHandler
  .thumb_set SMPU_IRQHandler,Default_Handler
  
   .weak      COMP1_2_3_IRQHandler
  .thumb_set COMP1_2_3_IRQHandler,Default_Handler
  
  .weak      USB_HS_EPx_OUT_IRQHandler
  .thumb_set USB_HS_EPx_OUT_IRQHandler,Default_Handler
  
  .weak      USB_HS_EPx_IN_IRQHandler
  .thumb_set USB_HS_EPx_IN_IRQHandler,Default_Handler
  
  .weak      USB_HS_WKUP_IRQHandler
  .thumb_set USB_HS_WKUP_IRQHandler,Default_Handler
  
  .weak      UART8_IRQHandler
  .thumb_set UART8_IRQHandler,Default_Handler
  
  .weak      SPI4_IRQHandler
  .thumb_set SPI4_IRQHandler,Default_Handler
  
  .weak      ETH_IRQHandler
  .thumb_set ETH_IRQHandler,Default_Handler
  
  .weak      ETH_WKUP_IRQHandler
  .thumb_set ETH_WKUP_IRQHandler,Default_Handler
  
  .weak      GTIM5_IRQHandler
  .thumb_set GTIM5_IRQHandler,Default_Handler
  
  .weak      COMP7_IRQHandler
  .thumb_set COMP7_IRQHandler,Default_Handler
  
  .weak      SHRT1_MST_IRQHandler
  .thumb_set SHRT1_MST_IRQHandler,Default_Handler
  
  .weak      SHRT1_TIMA_IRQHandler
  .thumb_set SHRT1_TIMA_IRQHandler,Default_Handler
  
  .weak      SHRT1_TIMB_IRQHandler
  .thumb_set SHRT1_TIMB_IRQHandler,Default_Handler
  
  .weak      SHRT1_TIMC_IRQHandler
  .thumb_set SHRT1_TIMC_IRQHandler,Default_Handler
  
  .weak      SHRT1_TIMD_IRQHandler
  .thumb_set SHRT1_TIMD_IRQHandler,Default_Handler
  
  .weak      SHRT1_TIME_IRQHandler
  .thumb_set SHRT1_TIME_IRQHandler,Default_Handler
  
  .weak      SHRT1_TIMF_IRQHandler
  .thumb_set SHRT1_TIMF_IRQHandler,Default_Handler
  
  .weak      SHRT1_FLT_IRQHandler
  .thumb_set SHRT1_FLT_IRQHandler,Default_Handler
  
  .weak      ATIM3_BRK_IRQHandler
  .thumb_set ATIM3_BRK_IRQHandler,Default_Handler
  
  .weak      ATIM3_UP_IRQHandler
  .thumb_set ATIM3_UP_IRQHandler,Default_Handler
  
  .weak      ATIM3_TRG_COM_IRQHandler
  .thumb_set ATIM3_TRG_COM_IRQHandler,Default_Handler
  
  .weak      ATIM3_CC_IRQHandler
  .thumb_set ATIM3_CC_IRQHandler,Default_Handler
  
  .weak      GTIM6_IRQHandler
  .thumb_set GTIM6_IRQHandler,Default_Handler
  
  .weak      LPTIM1_WKUP_IRQHandler
  .thumb_set LPTIM1_WKUP_IRQHandler,Default_Handler
  
  .weak      LPTIM2_WKUP_IRQHandler
  .thumb_set LPTIM2_WKUP_IRQHandler,Default_Handler
  
  .weak      FMAC_IRQ_IRQHandler
  .thumb_set FMAC_IRQ_IRQHandler,Default_Handler
  
  .weak      Cordic_IRQ_IRQHandler
  .thumb_set Cordic_IRQ_IRQHandler,Default_Handler
  
  .weak      SPI5_IRQHandler
  .thumb_set SPI5_IRQHandler,Default_Handler
  
  .weak      SPI6_IRQHandler
  .thumb_set SPI6_IRQHandler,Default_Handler
  
  .weak      GTIM7_IRQHandler
  .thumb_set GTIM7_IRQHandler,Default_Handler
  
  .weak      GTIM8_IRQHandler
  .thumb_set GTIM8_IRQHandler,Default_Handler
  
  .weak      GTIM9_IRQHandler
  .thumb_set GTIM9_IRQHandler,Default_Handler
  
  .weak      GTIM10_IRQHandler
  .thumb_set GTIM10_IRQHandler,Default_Handler
  
  .weak      DAC1_2_3_4_Underflow_IRQHandler
  .thumb_set DAC1_2_3_4_Underflow_IRQHandler,Default_Handler
  
  .weak      DAC5_6_7_8_Underflow_IRQHandler
  .thumb_set DAC5_6_7_8_Underflow_IRQHandler,Default_Handler
  
  .weak      USB_HS_IRQHandler
  .thumb_set USB_HS_IRQHandler,Default_Handler
  
  .weak      FEMC_IRQHandler
  .thumb_set FEMC_IRQHandler,Default_Handler

