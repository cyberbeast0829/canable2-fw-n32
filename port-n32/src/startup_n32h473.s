/**
  ******************************************************************************
  * @file      startup_n32h473.s
  * @brief     N32H473 vector table for GCC toolchain (GNU as syntax).
  ******************************************************************************
  */

  .syntax unified
  .cpu cortex-m4
  .fpu softvfp
  .thumb

.global g_pfnVectors
.global Default_Handler

.word _sidata
.word _sdata
.word _edata
.word _sbss
.word _ebss

  .section  .text.Reset_Handler
  .weak  Reset_Handler
  .type  Reset_Handler, %function
Reset_Handler:
  ldr   r0, =_estack
  mov   sp, r0

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

  bl  SystemInit
  bl __libc_init_array
  bl  main

LoopForever:
  b LoopForever

.size Reset_Handler, .-Reset_Handler

  .section  .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
  b Infinite_Loop
  .size Default_Handler, .-Default_Handler

  .section  .isr_vector,"a",%progbits
  .type  g_pfnVectors, %object
  .size  g_pfnVectors, .-g_pfnVectors

g_pfnVectors:
  .word _estack
  .word Reset_Handler
  .word NMI_Handler
  .word HardFault_Handler
  .word MemManage_Handler
  .word BusFault_Handler
  .word UsageFault_Handler
  .word 0
  .word 0
  .word 0
  .word 0
  .word SVC_Handler
  .word DebugMon_Handler
  .word 0
  .word PendSV_Handler
  .word SysTick_Handler
  .word WWDG_IRQHandler
  .word PVD_IRQHandler
  .word RTC_TAMPER_IRQHandler
  .word RTC_WKUP_IRQHandler
  .word FLASH_IRQHandler
  .word RCC_IRQHandler
  .word EXTI0_IRQHandler
  .word EXTI1_IRQHandler
  .word EXTI2_IRQHandler
  .word EXTI3_IRQHandler
  .word EXTI4_IRQHandler
  .word DMA1_Channel1_IRQHandler
  .word DMA1_Channel2_IRQHandler
  .word DMA1_Channel3_IRQHandler
  .word DMA1_Channel4_IRQHandler
  .word DMA1_Channel5_IRQHandler
  .word DMA1_Channel6_IRQHandler
  .word DMA1_Channel7_IRQHandler
  .word ADC1_2_IRQHandler
  .word USB_FS_HP_IRQHandler
  .word USB_FS_LP_IRQHandler
  .word FDCAN1_INT0_IRQHandler
  .word FDCAN1_INT1_IRQHandler
  .word EXTI9_5_IRQHandler
  .word ATIM1_BRK_IRQHandler
  .word ATIM1_UP_IRQHandler
  .word ATIM1_TRG_COM_IRQHandler
  .word ATIM1_CC_IRQHandler
  .word GTIM1_IRQHandler
  .word GTIM2_IRQHandler
  .word GTIM3_IRQHandler
  .word I2C1_EV_IRQHandler
  .word I2C1_ER_IRQHandler
  .word I2C2_EV_IRQHandler
  .word I2C2_ER_IRQHandler
  .word SPI1_IRQHandler
  .word SPI2_I2S2_IRQHandler
  .word USART1_IRQHandler
  .word USART2_IRQHandler
  .word USART3_IRQHandler
  .word EXTI15_10_IRQHandler
  .word RTCAlarm_IRQHandler
  .word USB_FS_WKUP_IRQHandler
  .word ATIM2_BRK_IRQHandler
  .word ATIM2_UP_IRQHandler
  .word ATIM2_TRG_COM_IRQHandler
  .word ATIM2_CC_IRQHandler
  .word ADC3_ADC4_IRQHandler
  .word UCDR_IRQHandler
  .word 0
  .word GTIM4_IRQHandler
  .word SPI3_I2S3_IRQHandler
  .word USART4_IRQHandler
  .word UART5_IRQHandler
  .word BTIM1_IRQHandler
  .word BTIM2_IRQHandler
  .word DMA2_Channel1_IRQHandler
  .word DMA2_Channel2_IRQHandler
  .word DMA2_Channel3_IRQHandler
  .word DMA2_Channel4_IRQHandler
  .word DMA2_Channel5_IRQHandler
  .word SRAM_ERR_IRQHandler
  .word COMP4_5_6_IRQHandler
  .word FDCAN2_INT0_IRQHandler
  .word FDCAN2_INT1_IRQHandler
  .word FDCAN3_INT0_IRQHandler
  .word FDCAN3_INT1_IRQHandler
  .word XSPI_IRQHandler
  .word DMA2_Channel6_IRQHandler
  .word DMA2_Channel7_IRQHandler
  .word I2C3_EV_IRQHandler
  .word I2C3_ER_IRQHandler
  .word I2C4_EV_IRQHandler
  .word I2C4_ER_IRQHandler
  .word UART6_IRQHandler
  .word UART7_IRQHandler
  .word DMA1_Channel8_IRQHandler
  .word DMA2_Channel8_IRQHandler
  .word 0
  .word SAC_IRQHandler
  .word SMPU_IRQHandler
  .word COMP1_2_3_IRQHandler
  .word 0
  .word 0
  .word 0
  .word UART8_IRQHandler
  .word SPI4_IRQHandler
  .word 0
  .word 0
  .word GTIM5_IRQHandler
  .word COMP7_IRQHandler
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word 0
  .word ATIM3_BRK_IRQHandler
  .word ATIM3_UP_IRQHandler
  .word ATIM3_TRG_COM_IRQHandler
  .word ATIM3_CC_IRQHandler
  .word GTIM6_IRQHandler
  .word LPTIM1_WKUP_IRQHandler
  .word LPTIM2_WKUP_IRQHandler
  .word FMAC_IRQ_IRQHandler
  .word Cordic_IRQ_IRQHandler
  .word SPI5_IRQHandler
  .word SPI6_IRQHandler
  .word GTIM7_IRQHandler
  .word GTIM8_IRQHandler
  .word GTIM9_IRQHandler
  .word GTIM10_IRQHandler
  .word DAC1_2_3_4_Underflow_IRQHandler
  .word DAC5_6_7_8_Underflow_IRQHandler
  .word 0
  .word FEMC_IRQHandler

  .weak NMI_Handler
  .thumb_set NMI_Handler,Default_Handler
  .weak HardFault_Handler
  .thumb_set HardFault_Handler,Default_Handler
  .weak MemManage_Handler
  .thumb_set MemManage_Handler,Default_Handler
  .weak BusFault_Handler
  .thumb_set BusFault_Handler,Default_Handler
  .weak UsageFault_Handler
  .thumb_set UsageFault_Handler,Default_Handler
  .weak SVC_Handler
  .thumb_set SVC_Handler,Default_Handler
  .weak DebugMon_Handler
  .thumb_set DebugMon_Handler,Default_Handler
  .weak PendSV_Handler
  .thumb_set PendSV_Handler,Default_Handler
  .weak SysTick_Handler
  .thumb_set SysTick_Handler,Default_Handler

  .weak WWDG_IRQHandler
  .thumb_set WWDG_IRQHandler,Default_Handler
  .weak PVD_IRQHandler
  .thumb_set PVD_IRQHandler,Default_Handler
  .weak RTC_TAMPER_IRQHandler
  .thumb_set RTC_TAMPER_IRQHandler,Default_Handler
  .weak RTC_WKUP_IRQHandler
  .thumb_set RTC_WKUP_IRQHandler,Default_Handler
  .weak FLASH_IRQHandler
  .thumb_set FLASH_IRQHandler,Default_Handler
  .weak RCC_IRQHandler
  .thumb_set RCC_IRQHandler,Default_Handler
  .weak EXTI0_IRQHandler
  .thumb_set EXTI0_IRQHandler,Default_Handler
  .weak EXTI1_IRQHandler
  .thumb_set EXTI1_IRQHandler,Default_Handler
  .weak EXTI2_IRQHandler
  .thumb_set EXTI2_IRQHandler,Default_Handler
  .weak EXTI3_IRQHandler
  .thumb_set EXTI3_IRQHandler,Default_Handler
  .weak EXTI4_IRQHandler
  .thumb_set EXTI4_IRQHandler,Default_Handler
  .weak DMA1_Channel1_IRQHandler
  .thumb_set DMA1_Channel1_IRQHandler,Default_Handler
  .weak DMA1_Channel2_IRQHandler
  .thumb_set DMA1_Channel2_IRQHandler,Default_Handler
  .weak DMA1_Channel3_IRQHandler
  .thumb_set DMA1_Channel3_IRQHandler,Default_Handler
  .weak DMA1_Channel4_IRQHandler
  .thumb_set DMA1_Channel4_IRQHandler,Default_Handler
  .weak DMA1_Channel5_IRQHandler
  .thumb_set DMA1_Channel5_IRQHandler,Default_Handler
  .weak DMA1_Channel6_IRQHandler
  .thumb_set DMA1_Channel6_IRQHandler,Default_Handler
  .weak DMA1_Channel7_IRQHandler
  .thumb_set DMA1_Channel7_IRQHandler,Default_Handler
  .weak ADC1_2_IRQHandler
  .thumb_set ADC1_2_IRQHandler,Default_Handler
  .weak USB_FS_HP_IRQHandler
  .thumb_set USB_FS_HP_IRQHandler,Default_Handler
  .weak USB_FS_LP_IRQHandler
  .thumb_set USB_FS_LP_IRQHandler,Default_Handler
  .weak FDCAN1_INT0_IRQHandler
  .thumb_set FDCAN1_INT0_IRQHandler,Default_Handler
  .weak FDCAN1_INT1_IRQHandler
  .thumb_set FDCAN1_INT1_IRQHandler,Default_Handler
  .weak EXTI9_5_IRQHandler
  .thumb_set EXTI9_5_IRQHandler,Default_Handler
  .weak ATIM1_BRK_IRQHandler
  .thumb_set ATIM1_BRK_IRQHandler,Default_Handler
  .weak ATIM1_UP_IRQHandler
  .thumb_set ATIM1_UP_IRQHandler,Default_Handler
  .weak ATIM1_TRG_COM_IRQHandler
  .thumb_set ATIM1_TRG_COM_IRQHandler,Default_Handler
  .weak ATIM1_CC_IRQHandler
  .thumb_set ATIM1_CC_IRQHandler,Default_Handler
  .weak GTIM1_IRQHandler
  .thumb_set GTIM1_IRQHandler,Default_Handler
  .weak GTIM2_IRQHandler
  .thumb_set GTIM2_IRQHandler,Default_Handler
  .weak GTIM3_IRQHandler
  .thumb_set GTIM3_IRQHandler,Default_Handler
  .weak I2C1_EV_IRQHandler
  .thumb_set I2C1_EV_IRQHandler,Default_Handler
  .weak I2C1_ER_IRQHandler
  .thumb_set I2C1_ER_IRQHandler,Default_Handler
  .weak I2C2_EV_IRQHandler
  .thumb_set I2C2_EV_IRQHandler,Default_Handler
  .weak I2C2_ER_IRQHandler
  .thumb_set I2C2_ER_IRQHandler,Default_Handler
  .weak SPI1_IRQHandler
  .thumb_set SPI1_IRQHandler,Default_Handler
  .weak SPI2_I2S2_IRQHandler
  .thumb_set SPI2_I2S2_IRQHandler,Default_Handler
  .weak USART1_IRQHandler
  .thumb_set USART1_IRQHandler,Default_Handler
  .weak USART2_IRQHandler
  .thumb_set USART2_IRQHandler,Default_Handler
  .weak USART3_IRQHandler
  .thumb_set USART3_IRQHandler,Default_Handler
  .weak EXTI15_10_IRQHandler
  .thumb_set EXTI15_10_IRQHandler,Default_Handler
  .weak RTCAlarm_IRQHandler
  .thumb_set RTCAlarm_IRQHandler,Default_Handler
  .weak USB_FS_WKUP_IRQHandler
  .thumb_set USB_FS_WKUP_IRQHandler,Default_Handler
  .weak ATIM2_BRK_IRQHandler
  .thumb_set ATIM2_BRK_IRQHandler,Default_Handler
  .weak ATIM2_UP_IRQHandler
  .thumb_set ATIM2_UP_IRQHandler,Default_Handler
  .weak ATIM2_TRG_COM_IRQHandler
  .thumb_set ATIM2_TRG_COM_IRQHandler,Default_Handler
  .weak ATIM2_CC_IRQHandler
  .thumb_set ATIM2_CC_IRQHandler,Default_Handler
  .weak ADC3_ADC4_IRQHandler
  .thumb_set ADC3_ADC4_IRQHandler,Default_Handler
  .weak UCDR_IRQHandler
  .thumb_set UCDR_IRQHandler,Default_Handler
  .weak GTIM4_IRQHandler
  .thumb_set GTIM4_IRQHandler,Default_Handler
  .weak SPI3_I2S3_IRQHandler
  .thumb_set SPI3_I2S3_IRQHandler,Default_Handler
  .weak USART4_IRQHandler
  .thumb_set USART4_IRQHandler,Default_Handler
  .weak UART5_IRQHandler
  .thumb_set UART5_IRQHandler,Default_Handler
  .weak BTIM1_IRQHandler
  .thumb_set BTIM1_IRQHandler,Default_Handler
  .weak BTIM2_IRQHandler
  .thumb_set BTIM2_IRQHandler,Default_Handler
  .weak DMA2_Channel1_IRQHandler
  .thumb_set DMA2_Channel1_IRQHandler,Default_Handler
  .weak DMA2_Channel2_IRQHandler
  .thumb_set DMA2_Channel2_IRQHandler,Default_Handler
  .weak DMA2_Channel3_IRQHandler
  .thumb_set DMA2_Channel3_IRQHandler,Default_Handler
  .weak DMA2_Channel4_IRQHandler
  .thumb_set DMA2_Channel4_IRQHandler,Default_Handler
  .weak DMA2_Channel5_IRQHandler
  .thumb_set DMA2_Channel5_IRQHandler,Default_Handler
  .weak SRAM_ERR_IRQHandler
  .thumb_set SRAM_ERR_IRQHandler,Default_Handler
  .weak COMP4_5_6_IRQHandler
  .thumb_set COMP4_5_6_IRQHandler,Default_Handler
  .weak FDCAN2_INT0_IRQHandler
  .thumb_set FDCAN2_INT0_IRQHandler,Default_Handler
  .weak FDCAN2_INT1_IRQHandler
  .thumb_set FDCAN2_INT1_IRQHandler,Default_Handler
  .weak FDCAN3_INT0_IRQHandler
  .thumb_set FDCAN3_INT0_IRQHandler,Default_Handler
  .weak FDCAN3_INT1_IRQHandler
  .thumb_set FDCAN3_INT1_IRQHandler,Default_Handler
  .weak XSPI_IRQHandler
  .thumb_set XSPI_IRQHandler,Default_Handler
  .weak DMA2_Channel6_IRQHandler
  .thumb_set DMA2_Channel6_IRQHandler,Default_Handler
  .weak DMA2_Channel7_IRQHandler
  .thumb_set DMA2_Channel7_IRQHandler,Default_Handler
  .weak I2C3_EV_IRQHandler
  .thumb_set I2C3_EV_IRQHandler,Default_Handler
  .weak I2C3_ER_IRQHandler
  .thumb_set I2C3_ER_IRQHandler,Default_Handler
  .weak I2C4_EV_IRQHandler
  .thumb_set I2C4_EV_IRQHandler,Default_Handler
  .weak I2C4_ER_IRQHandler
  .thumb_set I2C4_ER_IRQHandler,Default_Handler
  .weak UART6_IRQHandler
  .thumb_set UART6_IRQHandler,Default_Handler
  .weak UART7_IRQHandler
  .thumb_set UART7_IRQHandler,Default_Handler
  .weak DMA1_Channel8_IRQHandler
  .thumb_set DMA1_Channel8_IRQHandler,Default_Handler
  .weak DMA2_Channel8_IRQHandler
  .thumb_set DMA2_Channel8_IRQHandler,Default_Handler
  .weak SAC_IRQHandler
  .thumb_set SAC_IRQHandler,Default_Handler
  .weak SMPU_IRQHandler
  .thumb_set SMPU_IRQHandler,Default_Handler
  .weak COMP1_2_3_IRQHandler
  .thumb_set COMP1_2_3_IRQHandler,Default_Handler
  .weak UART8_IRQHandler
  .thumb_set UART8_IRQHandler,Default_Handler
  .weak SPI4_IRQHandler
  .thumb_set SPI4_IRQHandler,Default_Handler
  .weak GTIM5_IRQHandler
  .thumb_set GTIM5_IRQHandler,Default_Handler
  .weak COMP7_IRQHandler
  .thumb_set COMP7_IRQHandler,Default_Handler
  .weak ATIM3_BRK_IRQHandler
  .thumb_set ATIM3_BRK_IRQHandler,Default_Handler
  .weak ATIM3_UP_IRQHandler
  .thumb_set ATIM3_UP_IRQHandler,Default_Handler
  .weak ATIM3_TRG_COM_IRQHandler
  .thumb_set ATIM3_TRG_COM_IRQHandler,Default_Handler
  .weak ATIM3_CC_IRQHandler
  .thumb_set ATIM3_CC_IRQHandler,Default_Handler
  .weak GTIM6_IRQHandler
  .thumb_set GTIM6_IRQHandler,Default_Handler
  .weak LPTIM1_WKUP_IRQHandler
  .thumb_set LPTIM1_WKUP_IRQHandler,Default_Handler
  .weak LPTIM2_WKUP_IRQHandler
  .thumb_set LPTIM2_WKUP_IRQHandler,Default_Handler
  .weak FMAC_IRQ_IRQHandler
  .thumb_set FMAC_IRQ_IRQHandler,Default_Handler
  .weak Cordic_IRQ_IRQHandler
  .thumb_set Cordic_IRQ_IRQHandler,Default_Handler
  .weak SPI5_IRQHandler
  .thumb_set SPI5_IRQHandler,Default_Handler
  .weak SPI6_IRQHandler
  .thumb_set SPI6_IRQHandler,Default_Handler
  .weak GTIM7_IRQHandler
  .thumb_set GTIM7_IRQHandler,Default_Handler
  .weak GTIM8_IRQHandler
  .thumb_set GTIM8_IRQHandler,Default_Handler
  .weak GTIM9_IRQHandler
  .thumb_set GTIM9_IRQHandler,Default_Handler
  .weak GTIM10_IRQHandler
  .thumb_set GTIM10_IRQHandler,Default_Handler
  .weak DAC1_2_3_4_Underflow_IRQHandler
  .thumb_set DAC1_2_3_4_Underflow_IRQHandler,Default_Handler
  .weak DAC5_6_7_8_Underflow_IRQHandler
  .thumb_set DAC5_6_7_8_Underflow_IRQHandler,Default_Handler
  .weak FEMC_IRQHandler
  .thumb_set FEMC_IRQHandler,Default_Handler
