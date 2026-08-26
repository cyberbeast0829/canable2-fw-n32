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
 *\*\file n32h47x_48x_gpio.h
 *\*\author Nations
 *\*\version v1.0.0
 *\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
 **/

#ifndef __N32H47X_48X_GPIO_H__
#define __N32H47X_48X_GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32h47x_48x.h"


/*** GPIO Structure Definition Start ***/

/** GPIO Init Structure Definition **/
typedef struct
{
    uint32_t         Pin;            /* Specifies the GPIO pins to be configured. */
    uint32_t         GPIO_Mode;      /* Specifies the operating mode for the selected pins. */
    uint32_t         GPIO_Pull;      /* Specifies the Pull-up or Pull-Down activation for the selected pins. */
    uint32_t         GPIO_Slew_Rate; /* Specify the reverse speed for the selected pins. */
    uint32_t         GPIO_Current;   /* Driving capability of the select pins. */
    uint32_t         GPIO_Alternate; /* Peripheral to be connected to the selected pins. */
}GPIO_InitType;

/** Bit_SET and Bit_RESET enumeration **/
typedef enum
{
    Bit_RESET = 0,
    Bit_SET
}Bit_OperateType;

/*** GPIO Structure Definition End ***/


/*** GPIO Macro Definition Start ***/
#define GPIO_GET_INDEX(GPIOX_BASE)      (((GPIOX_BASE) - GPIOA_BASE)/0x400UL)

#define GPIO_GET_PERIPH(INDEX)      ((GPIO_Module*)(GPIOA_BASE + (INDEX) * 0x400UL))

/** Bit mask define **/
#define GPIO_PMODE_BIT_MASK                 (GPIO_PMODE_PMODE0)
#define GPIO_PUPD_BIT_MASK                  (GPIO_PUPD_PUPD0)
#define GPIO_AFSEL_BIT_MASK                 (GPIO_AFSEL0_AFSEL0)
#define GPIO_DS_BIT_MASK                    (GPIO_DS_DS0)
#define GPIO_SR_BIT_MASK                    (GPIO_SR_SR0)
#define AFIO_EXTI_BIT_MASK                  (AFIO_EXTI_CFG1_EXTI0)

/** GPIO_mode_define **/
/*     bit[0:1]: IO mode
 *\*\  bit[4]:   Open-drain output mark 
 */
#define GPIO_MODE_OD_MARK                   (GPIO_POTYPE_OPEN_DRAIN << 4)

#define GPIO_MODE_INPUT                     (GPIO_PMODE_INPUT)                          /* Input Floating Mode */
#define GPIO_MODE_OUTPUT_PP                 (GPIO_PMODE_OUTPUT)                         /* Output Push Pull Mode */
#define GPIO_MODE_OUTPUT_OD                 (GPIO_PMODE_OUTPUT | GPIO_MODE_OD_MARK)     /* Output Open Drain Mode */
#define GPIO_MODE_AF_PP                     (GPIO_PMODE_AF_OUTPUT)                      /* Alternate Function Push Pull Mode  */
#define GPIO_MODE_AF_OD                     (GPIO_PMODE_AF_OUTPUT | GPIO_MODE_OD_MARK)  /* Alternate Function Open Drain Mode */
#define GPIO_MODE_ANALOG                    (GPIO_PMODE_ANALOG)                         /* Analog Mode */

/** GPIO pins define **/
#define GPIO_PIN_0                          ((uint16_t)0x0001U)  /* Pin 0 selected    */
#define GPIO_PIN_1                          ((uint16_t)0x0002U)  /* Pin 1 selected    */
#define GPIO_PIN_2                          ((uint16_t)0x0004U)  /* Pin 2 selected    */
#define GPIO_PIN_3                          ((uint16_t)0x0008U)  /* Pin 3 selected    */
#define GPIO_PIN_4                          ((uint16_t)0x0010U)  /* Pin 4 selected    */
#define GPIO_PIN_5                          ((uint16_t)0x0020U)  /* Pin 5 selected    */
#define GPIO_PIN_6                          ((uint16_t)0x0040U)  /* Pin 6 selected    */
#define GPIO_PIN_7                          ((uint16_t)0x0080U)  /* Pin 7 selected    */
#define GPIO_PIN_8                          ((uint16_t)0x0100U)  /* Pin 8 selected    */
#define GPIO_PIN_9                          ((uint16_t)0x0200U)  /* Pin 9 selected    */
#define GPIO_PIN_10                         ((uint16_t)0x0400U)  /* Pin 10 selected   */
#define GPIO_PIN_11                         ((uint16_t)0x0800U)  /* Pin 11 selected   */
#define GPIO_PIN_12                         ((uint16_t)0x1000U)  /* Pin 12 selected   */
#define GPIO_PIN_13                         ((uint16_t)0x2000U)  /* Pin 13 selected   */
#define GPIO_PIN_14                         ((uint16_t)0x4000U)  /* Pin 14 selected   */
#define GPIO_PIN_15                         ((uint16_t)0x8000U)  /* Pin 15 selected   */
#define GPIO_PIN_ALL                        ((uint16_t)0xFFFFU)  /* All pins selected */
#define GPIO_PIN_NONE                       ((uint16_t)0x0000U)  /* None pin selected */


/** GPIO Pull-Up or Pull-Down Activation **/
#define GPIO_NO_PULL                        (GPIO_PUPD_NO_PULL)     /* No Pull-up or Pull-down activation */
#define GPIO_PULL_UP                        (GPIO_PUPD_PULL_UP)     /* Pull-up activation */
#define GPIO_PULL_DOWN                      (GPIO_PUPD_PULL_DOWN)   /* Pull-down activation */

/** GPIO Drive strength config **/
#define GPIO_DC_2mA                         (GPIO_DS_2mA)
#define GPIO_DC_4mA                         (GPIO_DS_4mA)
#define GPIO_DC_8mA                         (GPIO_DS_8mA)
#define GPIO_DC_12mA                        (GPIO_DS_12mA)

/** slew rate config **/
#define GPIO_SLEW_RATE_FAST                 (GPIO_SR_FAST_SLEW)
#define GPIO_SLEW_RATE_SLOW                 (GPIO_SR_SLOW_SLEW)

/** GPIO port sources **/
#define GPIOA_PORT_SOURCE                   ((uint8_t)0x00U)
#define GPIOB_PORT_SOURCE                   ((uint8_t)0x01U)
#define GPIOC_PORT_SOURCE                   ((uint8_t)0x02U)
#define GPIOD_PORT_SOURCE                   ((uint8_t)0x03U)
#define GPIOE_PORT_SOURCE                   ((uint8_t)0x04U)
#define GPIOF_PORT_SOURCE                   ((uint8_t)0x05U)
#define GPIOG_PORT_SOURCE                   ((uint8_t)0x06U)
#define GPIOH_PORT_SOURCE                   ((uint8_t)0x07U)

/** GPIO pin sources **/
#define GPIO_PIN_SOURCE0                    ((uint8_t)0x00U) /* Pin 0 selected    */
#define GPIO_PIN_SOURCE1                    ((uint8_t)0x01U) /* Pin 1 selected    */
#define GPIO_PIN_SOURCE2                    ((uint8_t)0x02U) /* Pin 2 selected    */
#define GPIO_PIN_SOURCE3                    ((uint8_t)0x03U) /* Pin 3 selected    */
#define GPIO_PIN_SOURCE4                    ((uint8_t)0x04U) /* Pin 4 selected    */
#define GPIO_PIN_SOURCE5                    ((uint8_t)0x05U) /* Pin 5 selected    */
#define GPIO_PIN_SOURCE6                    ((uint8_t)0x06U) /* Pin 6 selected    */
#define GPIO_PIN_SOURCE7                    ((uint8_t)0x07U) /* Pin 7 selected    */
#define GPIO_PIN_SOURCE8                    ((uint8_t)0x08U) /* Pin 8 selected    */
#define GPIO_PIN_SOURCE9                    ((uint8_t)0x09U) /* Pin 9 selected    */
#define GPIO_PIN_SOURCE10                   ((uint8_t)0x0AU) /* Pin 10 selected   */
#define GPIO_PIN_SOURCE11                   ((uint8_t)0x0BU) /* Pin 11 selected   */
#define GPIO_PIN_SOURCE12                   ((uint8_t)0x0CU) /* Pin 12 selected   */
#define GPIO_PIN_SOURCE13                   ((uint8_t)0x0DU) /* Pin 13 selected   */
#define GPIO_PIN_SOURCE14                   ((uint8_t)0x0EU) /* Pin 14 selected   */
#define GPIO_PIN_SOURCE15                   ((uint8_t)0x0FU) /* Pin 15 selected   */

/** EXTI line sources **/
#define EXTI_LINE_SOURCE0                   ((uint8_t)0x00U) /* EXTI_line_0  */
#define EXTI_LINE_SOURCE1                   ((uint8_t)0x01U) /* EXTI_line_1  */
#define EXTI_LINE_SOURCE2                   ((uint8_t)0x02U) /* EXTI_line_2  */
#define EXTI_LINE_SOURCE3                   ((uint8_t)0x03U) /* EXTI_line_3  */
#define EXTI_LINE_SOURCE4                   ((uint8_t)0x04U) /* EXTI_line_4  */
#define EXTI_LINE_SOURCE5                   ((uint8_t)0x05U) /* EXTI_line_5  */
#define EXTI_LINE_SOURCE6                   ((uint8_t)0x06U) /* EXTI_line_6  */
#define EXTI_LINE_SOURCE7                   ((uint8_t)0x07U) /* EXTI_line_7  */
#define EXTI_LINE_SOURCE8                   ((uint8_t)0x08U) /* EXTI_line_8  */
#define EXTI_LINE_SOURCE9                   ((uint8_t)0x09U) /* EXTI_line_9  */
#define EXTI_LINE_SOURCE10                  ((uint8_t)0x0AU) /* EXTI_line_10 */
#define EXTI_LINE_SOURCE11                  ((uint8_t)0x0BU) /* EXTI_line_11 */
#define EXTI_LINE_SOURCE12                  ((uint8_t)0x0CU) /* EXTI_line_12 */
#define EXTI_LINE_SOURCE13                  ((uint8_t)0x0DU) /* EXTI_line_13 */
#define EXTI_LINE_SOURCE14                  ((uint8_t)0x0EU) /* EXTI_line_14 */
#define EXTI_LINE_SOURCE15                  ((uint8_t)0x0FU) /* EXTI_line_15 */

/** Alternate function define **/
#define GPIO_NO_AF                          (GPIO_AFSEL_AF0 )
#define GPIO_AF0                            (GPIO_AFSEL_AF0 )
#define GPIO_AF1                            (GPIO_AFSEL_AF1 )
#define GPIO_AF2                            (GPIO_AFSEL_AF2 )
#define GPIO_AF3                            (GPIO_AFSEL_AF3 )
#define GPIO_AF4                            (GPIO_AFSEL_AF4 )
#define GPIO_AF5                            (GPIO_AFSEL_AF5 )
#define GPIO_AF6                            (GPIO_AFSEL_AF6 )
#define GPIO_AF7                            (GPIO_AFSEL_AF7 )
#define GPIO_AF8                            (GPIO_AFSEL_AF8 )
#define GPIO_AF9                            (GPIO_AFSEL_AF9 )
#define GPIO_AF10                           (GPIO_AFSEL_AF10)
#define GPIO_AF11                           (GPIO_AFSEL_AF11)
#define GPIO_AF12                           (GPIO_AFSEL_AF12)
#define GPIO_AF13                           (GPIO_AFSEL_AF13)
#define GPIO_AF14                           (GPIO_AFSEL_AF14)
#define GPIO_AF15                           (GPIO_AFSEL_AF15)
#define GPIO_AF16                           (GPIO_AFSEL_AF16)
#define GPIO_AF17                           (GPIO_AFSEL_AF17)
#define GPIO_AF18                           (GPIO_AFSEL_AF18)
#define GPIO_AF19                           (GPIO_AFSEL_AF19)
#define GPIO_AF20                           (GPIO_AFSEL_AF20)
#define GPIO_AF21                           (GPIO_AFSEL_AF21)
#define GPIO_AF22                           (GPIO_AFSEL_AF22)
#define GPIO_AF23                           (GPIO_AFSEL_AF23)
#define GPIO_AF24                           (GPIO_AFSEL_AF24)
#define GPIO_AF25                           (GPIO_AFSEL_AF25)
#define GPIO_AF26                           (GPIO_AFSEL_AF26)
#define GPIO_AF27                           (GPIO_AFSEL_AF27)
#define GPIO_AF28                           (GPIO_AFSEL_AF28)
#define GPIO_AF29                           (GPIO_AFSEL_AF29)
#define GPIO_AF30                           (GPIO_AFSEL_AF30)
#define GPIO_AF31                           (GPIO_AFSEL_AF31)

/** Pin alternate function define **/
/* MCO1 and MCO2 */
#define GPIO_AF_MCO1_PA7                    (GPIO_AF13)
#define GPIO_AF_MCO1_PA8                    (GPIO_AF10)
#define GPIO_AF_MCO1_PF13                   (GPIO_AF6)
#define GPIO_AF_MCO1_PH6                    (GPIO_AF1)
#define GPIO_AF_MCO2_PA3                    (GPIO_AF15)
#define GPIO_AF_MCO2_PC9                    (GPIO_AF10)
#define GPIO_AF_MCO2_PF14                   (GPIO_AF6)

/* JTAG and SWD */
#define GPIO_AF_JTAG_JTMS_PA13              (GPIO_AF0)
#define GPIO_AF_JTAG_JTCK_PA14              (GPIO_AF0)
#define GPIO_AF_JTAG_JTDI_PA15              (GPIO_AF0)
#define GPIO_AF_JTAG_JTDO_PB3               (GPIO_AF0)
#define GPIO_AF_JTAG_NJTRST_PB4             (GPIO_AF0)
#define GPIO_AF_SWD_SWDIO_PA13              (GPIO_AF0)
#define GPIO_AF_SWD_SWDCLK_PA14             (GPIO_AF0)

/* SHRTIM */
#define GPIO_AF_SHRTIM_CHA1_PA8             (GPIO_AF6)
#define GPIO_AF_SHRTIM_CHA2_PA9             (GPIO_AF6)
#define GPIO_AF_SHRTIM_CHB1_PA10            (GPIO_AF12)
#define GPIO_AF_SHRTIM_CHB2_PA11            (GPIO_AF12)
#define GPIO_AF_SHRTIM_CHC1_PB12            (GPIO_AF10)
#define GPIO_AF_SHRTIM_CHC2_PB13            (GPIO_AF10)
#define GPIO_AF_SHRTIM_CHD1_PB14            (GPIO_AF10)
#define GPIO_AF_SHRTIM_CHD2_PB15            (GPIO_AF10)
#define GPIO_AF_SHRTIM_CHE1_PC8             (GPIO_AF11)
#define GPIO_AF_SHRTIM_CHE2_PC9             (GPIO_AF11)
#define GPIO_AF_SHRTIM_CHF1_PC6             (GPIO_AF11)
#define GPIO_AF_SHRTIM_CHF2_PC7             (GPIO_AF11)
#define GPIO_AF_SHRTIM_SCIN_PB2             (GPIO_AF5)
#define GPIO_AF_SHRTIM_SCIN_PB6             (GPIO_AF9)
#define GPIO_AF_SHRTIM_SCOUT_PB1            (GPIO_AF5)
#define GPIO_AF_SHRTIM_SCOUT_PB3            (GPIO_AF5)
#define GPIO_AF_SHRTIM_FLT1_PA12            (GPIO_AF12)
#define GPIO_AF_SHRTIM_FLT2_PA15            (GPIO_AF12)
#define GPIO_AF_SHRTIM_FLT3_PB10            (GPIO_AF10)
#define GPIO_AF_SHRTIM_FLT4_PB11            (GPIO_AF10)
#define GPIO_AF_SHRTIM_FLT5_PB0             (GPIO_AF5)
#define GPIO_AF_SHRTIM_FLT5_PC7             (GPIO_AF12)
#define GPIO_AF_SHRTIM_FLT6_PC10            (GPIO_AF11)

/* ATIM1 */
#define GPIO_AF_ATIM1_ETR_PA12              (GPIO_AF3)
#define GPIO_AF_ATIM1_ETR_PC4               (GPIO_AF6)
#define GPIO_AF_ATIM1_ETR_PE7               (GPIO_AF2)
#define GPIO_AF_ATIM1_CH1_PA8               (GPIO_AF3)
#define GPIO_AF_ATIM1_CH1_PC0               (GPIO_AF3)
#define GPIO_AF_ATIM1_CH1_PE9               (GPIO_AF3)
#define GPIO_AF_ATIM1_CH2_PA9               (GPIO_AF3)
#define GPIO_AF_ATIM1_CH2_PB13              (GPIO_AF3)
#define GPIO_AF_ATIM1_CH2_PC1               (GPIO_AF3)
#define GPIO_AF_ATIM1_CH2_PE11              (GPIO_AF3)
#define GPIO_AF_ATIM1_CH3_PA10              (GPIO_AF3)
#define GPIO_AF_ATIM1_CH3_PC2               (GPIO_AF3)
#define GPIO_AF_ATIM1_CH3_PD8               (GPIO_AF5)
#define GPIO_AF_ATIM1_CH3_PE13              (GPIO_AF3)
#define GPIO_AF_ATIM1_CH4_PA11              (GPIO_AF3)
#define GPIO_AF_ATIM1_CH4_PC3               (GPIO_AF3)
#define GPIO_AF_ATIM1_CH4_PD2               (GPIO_AF10)
#define GPIO_AF_ATIM1_CH4_PD10              (GPIO_AF5)
#define GPIO_AF_ATIM1_CH4_PE14              (GPIO_AF3)
#define GPIO_AF_ATIM1_BKIN_PA6              (GPIO_AF5)
#define GPIO_AF_ATIM1_BKIN_PA14             (GPIO_AF7)
#define GPIO_AF_ATIM1_BKIN_PA15             (GPIO_AF8)
#define GPIO_AF_ATIM1_BKIN_PB8              (GPIO_AF8)
#define GPIO_AF_ATIM1_BKIN_PB10             (GPIO_AF5)
#define GPIO_AF_ATIM1_BKIN_PB12             (GPIO_AF5)
#define GPIO_AF_ATIM1_BKIN_PC13             (GPIO_AF6)
#define GPIO_AF_ATIM1_BKIN_PE15             (GPIO_AF2)
#define GPIO_AF_ATIM1_BKIN2_PA11            (GPIO_AF7)
#define GPIO_AF_ATIM1_BKIN2_PC3             (GPIO_AF6)
#define GPIO_AF_ATIM1_BKIN2_PE14            (GPIO_AF2)
#define GPIO_AF_ATIM1_CH1N_PA7              (GPIO_AF5)
#define GPIO_AF_ATIM1_CH1N_PA11             (GPIO_AF6)
#define GPIO_AF_ATIM1_CH1N_PB13             (GPIO_AF5)
#define GPIO_AF_ATIM1_CH1N_PC13             (GPIO_AF3)
#define GPIO_AF_ATIM1_CH1N_PE8              (GPIO_AF3)
#define GPIO_AF_ATIM1_CH1N_PE10             (GPIO_AF5)
#define GPIO_AF_ATIM1_CH2N_PA12             (GPIO_AF6)
#define GPIO_AF_ATIM1_CH2N_PB0              (GPIO_AF7)
#define GPIO_AF_ATIM1_CH2N_PB14             (GPIO_AF5)
#define GPIO_AF_ATIM1_CH2N_PE10             (GPIO_AF3)
#define GPIO_AF_ATIM1_CH3N_PB1              (GPIO_AF7)
#define GPIO_AF_ATIM1_CH3N_PB9              (GPIO_AF8)
#define GPIO_AF_ATIM1_CH3N_PB15             (GPIO_AF5)
#define GPIO_AF_ATIM1_CH3N_PD9              (GPIO_AF5)
#define GPIO_AF_ATIM1_CH3N_PE12             (GPIO_AF3)
#define GPIO_AF_ATIM1_CH3N_PH0              (GPIO_AF3)
#define GPIO_AF_ATIM1_CH4N_PC5              (GPIO_AF3)
#define GPIO_AF_ATIM1_CH4N_PD5              (GPIO_AF3)
#define GPIO_AF_ATIM1_CH4N_PE15             (GPIO_AF3)

/* ATIM2 */
#define GPIO_AF_ATIM2_ETR_PA0               (GPIO_AF8)
#define GPIO_AF_ATIM2_ETR_PB4               (GPIO_AF5)
#define GPIO_AF_ATIM2_ETR_PB6               (GPIO_AF8)
#define GPIO_AF_ATIM2_CH1_PA15              (GPIO_AF6)
#define GPIO_AF_ATIM2_CH1_PB6               (GPIO_AF7)
#define GPIO_AF_ATIM2_CH1_PC6               (GPIO_AF3)
#define GPIO_AF_ATIM2_CH1_PD14              (GPIO_AF6)
#define GPIO_AF_ATIM2_CH2_PA14              (GPIO_AF6)
#define GPIO_AF_ATIM2_CH2_PB8               (GPIO_AF5)
#define GPIO_AF_ATIM2_CH2_PC6               (GPIO_AF15)
#define GPIO_AF_ATIM2_CH2_PC7               (GPIO_AF3)
#define GPIO_AF_ATIM2_CH2_PD15              (GPIO_AF6)
#define GPIO_AF_ATIM2_CH3_PB9               (GPIO_AF5)
#define GPIO_AF_ATIM2_CH3_PC8               (GPIO_AF3)
#define GPIO_AF_ATIM2_CH4_PB15              (GPIO_AF3)
#define GPIO_AF_ATIM2_CH4_PC9               (GPIO_AF3)
#define GPIO_AF_ATIM2_CH4_PD1               (GPIO_AF3)
#define GPIO_AF_ATIM2_CH4_PG14              (GPIO_AF11)
#define GPIO_AF_ATIM2_BKIN_PA0              (GPIO_AF6)
#define GPIO_AF_ATIM2_BKIN_PA6              (GPIO_AF6)
#define GPIO_AF_ATIM2_BKIN_PA10             (GPIO_AF7)
#define GPIO_AF_ATIM2_BKIN_PB3              (GPIO_AF11)
#define GPIO_AF_ATIM2_BKIN_PB7              (GPIO_AF6)
#define GPIO_AF_ATIM2_BKIN_PD2              (GPIO_AF5)
#define GPIO_AF_ATIM2_BKIN2_PB6             (GPIO_AF5)
#define GPIO_AF_ATIM2_BKIN2_PC9             (GPIO_AF5)
#define GPIO_AF_ATIM2_BKIN2_PD1             (GPIO_AF5)
#define GPIO_AF_ATIM2_CH1N_PA5              (GPIO_AF6)
#define GPIO_AF_ATIM2_CH1N_PA7              (GPIO_AF6)
#define GPIO_AF_ATIM2_CH1N_PA15             (GPIO_AF7)
#define GPIO_AF_ATIM2_CH1N_PB3              (GPIO_AF6)
#define GPIO_AF_ATIM2_CH1N_PC10             (GPIO_AF5)
#define GPIO_AF_ATIM2_CH1N_PD15             (GPIO_AF7)
#define GPIO_AF_ATIM2_CH2N_PB0              (GPIO_AF6)
#define GPIO_AF_ATIM2_CH2N_PB4              (GPIO_AF7)
#define GPIO_AF_ATIM2_CH2N_PB14             (GPIO_AF6)
#define GPIO_AF_ATIM2_CH2N_PC7              (GPIO_AF15)
#define GPIO_AF_ATIM2_CH2N_PC11             (GPIO_AF5)
#define GPIO_AF_ATIM2_CH2N_PC12             (GPIO_AF10)
#define GPIO_AF_ATIM2_CH3N_PA11             (GPIO_AF9)
#define GPIO_AF_ATIM2_CH3N_PB1              (GPIO_AF6)
#define GPIO_AF_ATIM2_CH3N_PB5              (GPIO_AF7)
#define GPIO_AF_ATIM2_CH3N_PB15             (GPIO_AF6)
#define GPIO_AF_ATIM2_CH3N_PC9              (GPIO_AF12)
#define GPIO_AF_ATIM2_CH3N_PC12             (GPIO_AF5)
#define GPIO_AF_ATIM2_CH3N_PD2              (GPIO_AF6)
#define GPIO_AF_ATIM2_CH4N_PC13             (GPIO_AF5)
#define GPIO_AF_ATIM2_CH4N_PD0              (GPIO_AF3)
#define GPIO_AF_ATIM2_CH4N_PD2              (GPIO_AF7)
#define GPIO_AF_ATIM2_CH4N_PG15             (GPIO_AF2)
#define GPIO_AF_ATIM2_CH4N_PH3              (GPIO_AF6)

/* ATIM3 */
#define GPIO_AF_ATIM3_ETR_PA15              (GPIO_AF13)
#define GPIO_AF_ATIM3_ETR_PD10              (GPIO_AF3)
#define GPIO_AF_ATIM3_ETR_PE0               (GPIO_AF6)
#define GPIO_AF_ATIM3_ETR_PF11              (GPIO_AF3)
#define GPIO_AF_ATIM3_ETR_PG5               (GPIO_AF2)
#define GPIO_AF_ATIM3_CH1_PB2               (GPIO_AF6)
#define GPIO_AF_ATIM3_CH1_PE2               (GPIO_AF3)
#define GPIO_AF_ATIM3_CH1_PF0               (GPIO_AF3)
#define GPIO_AF_ATIM3_CH1_PF12              (GPIO_AF3)
#define GPIO_AF_ATIM3_CH2_PC2               (GPIO_AF6)
#define GPIO_AF_ATIM3_CH2_PC11              (GPIO_AF12)
#define GPIO_AF_ATIM3_CH2_PE3               (GPIO_AF3)
#define GPIO_AF_ATIM3_CH2_PF1               (GPIO_AF3)
#define GPIO_AF_ATIM3_CH2_PF13              (GPIO_AF3)
#define GPIO_AF_ATIM3_CH3_PC8               (GPIO_AF1)
#define GPIO_AF_ATIM3_CH3_PC12              (GPIO_AF12)
#define GPIO_AF_ATIM3_CH3_PF2               (GPIO_AF3)
#define GPIO_AF_ATIM3_CH3_PF14              (GPIO_AF3)
#define GPIO_AF_ATIM3_CH4_PD0               (GPIO_AF5)
#define GPIO_AF_ATIM3_CH4_PD2               (GPIO_AF14)
#define GPIO_AF_ATIM3_CH4_PE1               (GPIO_AF3)
#define GPIO_AF_ATIM3_CH4_PF3               (GPIO_AF3)
#define GPIO_AF_ATIM3_CH4_PF15              (GPIO_AF3)
#define GPIO_AF_ATIM3_BKIN_PC13             (GPIO_AF13)
#define GPIO_AF_ATIM3_BKIN_PF7              (GPIO_AF3)
#define GPIO_AF_ATIM3_BKIN_PF9              (GPIO_AF3)
#define GPIO_AF_ATIM3_BKIN_PG3              (GPIO_AF2)
#define GPIO_AF_ATIM3_BKIN_PG6              (GPIO_AF2)
#define GPIO_AF_ATIM3_BKIN_PH3              (GPIO_AF3)
#define GPIO_AF_ATIM3_BKIN2_PF8             (GPIO_AF3)
#define GPIO_AF_ATIM3_BKIN2_PF10            (GPIO_AF3)
#define GPIO_AF_ATIM3_BKIN2_PG4             (GPIO_AF2)
#define GPIO_AF_ATIM3_CH1N_PE4              (GPIO_AF3)
#define GPIO_AF_ATIM3_CH1N_PF4              (GPIO_AF3)
#define GPIO_AF_ATIM3_CH1N_PG0              (GPIO_AF3)
#define GPIO_AF_ATIM3_CH1N_PH0              (GPIO_AF6)
#define GPIO_AF_ATIM3_CH2N_PE5              (GPIO_AF3)
#define GPIO_AF_ATIM3_CH2N_PF5              (GPIO_AF3)
#define GPIO_AF_ATIM3_CH2N_PG1              (GPIO_AF3)
#define GPIO_AF_ATIM3_CH2N_PH1              (GPIO_AF6)
#define GPIO_AF_ATIM3_CH3N_PA0              (GPIO_AF7)
#define GPIO_AF_ATIM3_CH3N_PC4              (GPIO_AF3)
#define GPIO_AF_ATIM3_CH3N_PE6              (GPIO_AF3)
#define GPIO_AF_ATIM3_CH3N_PG2              (GPIO_AF3)
#define GPIO_AF_ATIM3_CH4N_PA1              (GPIO_AF6)
#define GPIO_AF_ATIM3_CH4N_PE0              (GPIO_AF2)
#define GPIO_AF_ATIM3_CH4N_PG3              (GPIO_AF3)

/* GTIM1 */
#define GPIO_AF_GTIM1_ETR_PA0               (GPIO_AF10)
#define GPIO_AF_GTIM1_ETR_PA5               (GPIO_AF2)
#define GPIO_AF_GTIM1_ETR_PA15              (GPIO_AF15)
#define GPIO_AF_GTIM1_ETR_PD3               (GPIO_AF2)
#define GPIO_AF_GTIM1_CH1_PA0               (GPIO_AF3)
#define GPIO_AF_GTIM1_CH1_PA5               (GPIO_AF3)
#define GPIO_AF_GTIM1_CH1_PA15              (GPIO_AF3)
#define GPIO_AF_GTIM1_CH1_PD3               (GPIO_AF3)
#define GPIO_AF_GTIM1_CH2_PA1               (GPIO_AF3)
#define GPIO_AF_GTIM1_CH2_PB3               (GPIO_AF3)
#define GPIO_AF_GTIM1_CH2_PD4               (GPIO_AF5)
#define GPIO_AF_GTIM1_CH3_PA2               (GPIO_AF3)
#define GPIO_AF_GTIM1_CH3_PA9               (GPIO_AF2)
#define GPIO_AF_GTIM1_CH3_PB10              (GPIO_AF3)
#define GPIO_AF_GTIM1_CH3_PD7               (GPIO_AF5)
#define GPIO_AF_GTIM1_CH4_PA3               (GPIO_AF3)
#define GPIO_AF_GTIM1_CH4_PA10              (GPIO_AF2)
#define GPIO_AF_GTIM1_CH4_PB2               (GPIO_AF8)
#define GPIO_AF_GTIM1_CH4_PB11              (GPIO_AF3)
#define GPIO_AF_GTIM1_CH4_PD6               (GPIO_AF5)

/* GTIM2 */
#define GPIO_AF_GTIM2_ETR_PB3               (GPIO_AF8)
#define GPIO_AF_GTIM2_ETR_PD2               (GPIO_AF3)
#define GPIO_AF_GTIM2_CH1_PA6               (GPIO_AF3)
#define GPIO_AF_GTIM2_CH1_PB4               (GPIO_AF3)
#define GPIO_AF_GTIM2_CH1_PC6               (GPIO_AF6)
#define GPIO_AF_GTIM2_CH1_PE2               (GPIO_AF2)
#define GPIO_AF_GTIM2_CH1_PE10              (GPIO_AF6)
#define GPIO_AF_GTIM2_CH2_PA4               (GPIO_AF3)
#define GPIO_AF_GTIM2_CH2_PA7               (GPIO_AF3)
#define GPIO_AF_GTIM2_CH2_PB5               (GPIO_AF3)
#define GPIO_AF_GTIM2_CH2_PC7               (GPIO_AF6)
#define GPIO_AF_GTIM2_CH2_PE3               (GPIO_AF2)
#define GPIO_AF_GTIM2_CH3_PB0               (GPIO_AF3)
#define GPIO_AF_GTIM2_CH3_PC8               (GPIO_AF6)
#define GPIO_AF_GTIM2_CH3_PE4               (GPIO_AF2)
#define GPIO_AF_GTIM2_CH4_PB1               (GPIO_AF3)
#define GPIO_AF_GTIM2_CH4_PB7               (GPIO_AF7)
#define GPIO_AF_GTIM2_CH4_PC9               (GPIO_AF6)
#define GPIO_AF_GTIM2_CH4_PE5               (GPIO_AF2)

/* GTIM3 */
#define GPIO_AF_GTIM3_ETR_PA8               (GPIO_AF2)
#define GPIO_AF_GTIM3_ETR_PB3               (GPIO_AF7)
#define GPIO_AF_GTIM3_ETR_PE0               (GPIO_AF3)
#define GPIO_AF_GTIM3_CH1_PA11              (GPIO_AF2)
#define GPIO_AF_GTIM3_CH1_PB6               (GPIO_AF3)
#define GPIO_AF_GTIM3_CH1_PD12              (GPIO_AF5)
#define GPIO_AF_GTIM3_CH2_PA12              (GPIO_AF2)
#define GPIO_AF_GTIM3_CH2_PB7               (GPIO_AF3)
#define GPIO_AF_GTIM3_CH2_PD13              (GPIO_AF5)
#define GPIO_AF_GTIM3_CH3_PA13              (GPIO_AF2)
#define GPIO_AF_GTIM3_CH3_PB8               (GPIO_AF3)
#define GPIO_AF_GTIM3_CH3_PD14              (GPIO_AF5)
#define GPIO_AF_GTIM3_CH4_PB9               (GPIO_AF3)
#define GPIO_AF_GTIM3_CH4_PD15              (GPIO_AF5)
#define GPIO_AF_GTIM3_CH4_PF6               (GPIO_AF3)
#define GPIO_AF_GTIM3_CH4_PH2               (GPIO_AF3)

/* GTIM4 */
#define GPIO_AF_GTIM4_ETR_PB12              (GPIO_AF3)
#define GPIO_AF_GTIM4_ETR_PD11              (GPIO_AF2)
#define GPIO_AF_GTIM4_ETR_PF6               (GPIO_AF5)
#define GPIO_AF_GTIM4_CH1_PA0               (GPIO_AF2)
#define GPIO_AF_GTIM4_CH1_PB2               (GPIO_AF3)
#define GPIO_AF_GTIM4_CH1_PF6               (GPIO_AF6)
#define GPIO_AF_GTIM4_CH1_PH4               (GPIO_AF5)
#define GPIO_AF_GTIM4_CH2_PA1               (GPIO_AF2)
#define GPIO_AF_GTIM4_CH2_PC12              (GPIO_AF3)
#define GPIO_AF_GTIM4_CH2_PE7               (GPIO_AF5)
#define GPIO_AF_GTIM4_CH2_PF7               (GPIO_AF6)
#define GPIO_AF_GTIM4_CH3_PA2               (GPIO_AF2)
#define GPIO_AF_GTIM4_CH3_PE8               (GPIO_AF5)
#define GPIO_AF_GTIM4_CH3_PF8               (GPIO_AF6)
#define GPIO_AF_GTIM4_CH4_PA3               (GPIO_AF2)
#define GPIO_AF_GTIM4_CH4_PE9               (GPIO_AF5)
#define GPIO_AF_GTIM4_CH4_PF9               (GPIO_AF6)

/* GTIM5 */
#define GPIO_AF_GTIM5_ETR_PC5               (GPIO_AF8)
#define GPIO_AF_GTIM5_ETR_PG2               (GPIO_AF5)
#define GPIO_AF_GTIM5_CH1_PA2               (GPIO_AF7)
#define GPIO_AF_GTIM5_CH1_PE5               (GPIO_AF5)
#define GPIO_AF_GTIM5_CH1_PF4               (GPIO_AF5)
#define GPIO_AF_GTIM5_CH1_PH3               (GPIO_AF5)
#define GPIO_AF_GTIM5_CH2_PA3               (GPIO_AF7)
#define GPIO_AF_GTIM5_CH2_PD2               (GPIO_AF15)
#define GPIO_AF_GTIM5_CH2_PE6               (GPIO_AF5)
#define GPIO_AF_GTIM5_CH2_PF5               (GPIO_AF5)
#define GPIO_AF_GTIM5_CH3_PH0               (GPIO_AF5)
#define GPIO_AF_GTIM5_CH4_PH1               (GPIO_AF5)

/* GTIM6 */
#define GPIO_AF_GTIM6_ETR_PB2               (GPIO_AF13)
#define GPIO_AF_GTIM6_ETR_PG4               (GPIO_AF5)
#define GPIO_AF_GTIM6_CH1_PB8               (GPIO_AF6)
#define GPIO_AF_GTIM6_CH1_PD5               (GPIO_AF5)
#define GPIO_AF_GTIM6_CH1_PD12              (GPIO_AF2)
#define GPIO_AF_GTIM6_CH1_PF6               (GPIO_AF2)
#define GPIO_AF_GTIM6_CH2_PD13              (GPIO_AF2)
#define GPIO_AF_GTIM6_CH2_PG9               (GPIO_AF5)
#define GPIO_AF_GTIM6_CH3_PD14              (GPIO_AF2)
#define GPIO_AF_GTIM6_CH3_PG14              (GPIO_AF3)
#define GPIO_AF_GTIM6_CH4_PD15              (GPIO_AF2)
#define GPIO_AF_GTIM6_CH4_PG15              (GPIO_AF3)

/* GTIM7 */
#define GPIO_AF_GTIM7_ETR_PD9               (GPIO_AF2)
#define GPIO_AF_GTIM7_CH1_PA4               (GPIO_AF12)
#define GPIO_AF_GTIM7_CH1_PA7               (GPIO_AF12)
#define GPIO_AF_GTIM7_CH1_PB9               (GPIO_AF7)
#define GPIO_AF_GTIM7_CH1_PF7               (GPIO_AF2)
#define GPIO_AF_GTIM7_CH1_PG10              (GPIO_AF3)
#define GPIO_AF_GTIM7_CH2_PA5               (GPIO_AF7)
#define GPIO_AF_GTIM7_CH2_PG0               (GPIO_AF5)
#define GPIO_AF_GTIM7_CH2_PG11              (GPIO_AF3)
#define GPIO_AF_GTIM7_CH3_PC14              (GPIO_AF7)
#define GPIO_AF_GTIM7_CH3_PG1               (GPIO_AF5)
#define GPIO_AF_GTIM7_CH3_PG12              (GPIO_AF3)
#define GPIO_AF_GTIM7_CH4_PC15              (GPIO_AF7)
#define GPIO_AF_GTIM7_CH4_PE12              (GPIO_AF8)
#define GPIO_AF_GTIM7_CH4_PG13              (GPIO_AF3)

/* GTIM8 */
#define GPIO_AF_GTIM8_ETR_PA2               (GPIO_AF14)
#define GPIO_AF_GTIM8_ETR_PF7               (GPIO_AF5)
#define GPIO_AF_GTIM8_CH1_PA2               (GPIO_AF12)
#define GPIO_AF_GTIM8_CH1_PB14              (GPIO_AF3)
#define GPIO_AF_GTIM8_CH1_PD15              (GPIO_AF3)
#define GPIO_AF_GTIM8_CH1_PF9               (GPIO_AF5)
#define GPIO_AF_GTIM8_CH2_PA3               (GPIO_AF12)
#define GPIO_AF_GTIM8_CH2_PB15              (GPIO_AF7)
#define GPIO_AF_GTIM8_CH2_PC7               (GPIO_AF0)
#define GPIO_AF_GTIM8_CH2_PF10              (GPIO_AF5)
#define GPIO_AF_GTIM8_CH3_PA13              (GPIO_AF13)
#define GPIO_AF_GTIM8_CH3_PC9               (GPIO_AF0)
#define GPIO_AF_GTIM8_CH4_PA14              (GPIO_AF13)
#define GPIO_AF_GTIM8_BKIN_PA9              (GPIO_AF7)
#define GPIO_AF_GTIM8_BKIN_PC5              (GPIO_AF6)
#define GPIO_AF_GTIM8_CH1N_PA1              (GPIO_AF8)
#define GPIO_AF_GTIM8_CH1N_PB15             (GPIO_AF2)
#define GPIO_AF_GTIM8_CH1N_PG9              (GPIO_AF3)

/* GTIM9 */
#define GPIO_AF_GTIM9_ETR_PB4               (GPIO_AF11)
#define GPIO_AF_GTIM9_ETR_PD6               (GPIO_AF7)
#define GPIO_AF_GTIM9_CH1_PA6               (GPIO_AF2)
#define GPIO_AF_GTIM9_CH1_PA12              (GPIO_AF7)
#define GPIO_AF_GTIM9_CH1_PB4               (GPIO_AF13)
#define GPIO_AF_GTIM9_CH1_PB8               (GPIO_AF7)
#define GPIO_AF_GTIM9_CH1_PE0               (GPIO_AF1)
#define GPIO_AF_GTIM9_CH1_PE10              (GPIO_AF8)
#define GPIO_AF_GTIM9_CH1_PF8               (GPIO_AF2)
#define GPIO_AF_GTIM9_CH2_PA7               (GPIO_AF7)
#define GPIO_AF_GTIM9_CH2_PB14              (GPIO_AF7)
#define GPIO_AF_GTIM9_CH3_PB12              (GPIO_AF6)
#define GPIO_AF_GTIM9_CH3_PD9               (GPIO_AF3)
#define GPIO_AF_GTIM9_CH3_PH2               (GPIO_AF5)
#define GPIO_AF_GTIM9_CH4_PB8               (GPIO_AF9)
#define GPIO_AF_GTIM9_CH4_PB13              (GPIO_AF7)
#define GPIO_AF_GTIM9_CH4_PC10              (GPIO_AF6)
#define GPIO_AF_GTIM9_CH4_PE7               (GPIO_AF6)
#define GPIO_AF_GTIM9_BKIN_PB5              (GPIO_AF6)
#define GPIO_AF_GTIM9_CH1N_PA13             (GPIO_AF6)
#define GPIO_AF_GTIM9_CH1N_PB6              (GPIO_AF6)

/* GTIM10 */
#define GPIO_AF_GTIM10_ETR_PC11             (GPIO_AF11)
#define GPIO_AF_GTIM10_CH1_PA7              (GPIO_AF2)
#define GPIO_AF_GTIM10_CH1_PB5              (GPIO_AF5)
#define GPIO_AF_GTIM10_CH1_PB9              (GPIO_AF6)
#define GPIO_AF_GTIM10_CH1_PC0              (GPIO_AF6)
#define GPIO_AF_GTIM10_CH1_PD8              (GPIO_AF3)
#define GPIO_AF_GTIM10_CH1_PE1              (GPIO_AF1)
#define GPIO_AF_GTIM10_CH1_PE15             (GPIO_AF1)
#define GPIO_AF_GTIM10_CH1_PF9              (GPIO_AF2)
#define GPIO_AF_GTIM10_CH2_PB13             (GPIO_AF6)
#define GPIO_AF_GTIM10_CH2_PC1              (GPIO_AF6)
#define GPIO_AF_GTIM10_CH2_PD9              (GPIO_AF6)
#define GPIO_AF_GTIM10_CH3_PC2              (GPIO_AF7)
#define GPIO_AF_GTIM10_CH3_PD11             (GPIO_AF3)
#define GPIO_AF_GTIM10_CH4_PC3              (GPIO_AF7)
#define GPIO_AF_GTIM10_CH4_PD14             (GPIO_AF3)
#define GPIO_AF_GTIM10_BKIN_PA10            (GPIO_AF0)
#define GPIO_AF_GTIM10_BKIN_PB4             (GPIO_AF14)
#define GPIO_AF_GTIM10_CH1N_PB7             (GPIO_AF5)
#define GPIO_AF_GTIM10_CH1N_PH4             (GPIO_AF6)

/* LPTIM1 */
#define GPIO_AF_LPTIM1_ETR_PB6              (GPIO_AF14)
#define GPIO_AF_LPTIM1_ETR_PC3              (GPIO_AF5)
#define GPIO_AF_LPTIM1_IN1_PB5              (GPIO_AF14)
#define GPIO_AF_LPTIM1_IN1_PC0              (GPIO_AF5)
#define GPIO_AF_LPTIM1_IN2_PB7              (GPIO_AF14)
#define GPIO_AF_LPTIM1_IN2_PC2              (GPIO_AF5)
#define GPIO_AF_LPTIM1_OUT_PA14             (GPIO_AF10)
#define GPIO_AF_LPTIM1_OUT_PB2              (GPIO_AF9)
#define GPIO_AF_LPTIM1_OUT_PC1              (GPIO_AF5)

/* LPTIM2 */
#define GPIO_AF_LPTIM2_ETR_PC13             (GPIO_AF7)
#define GPIO_AF_LPTIM2_IN1_PB4              (GPIO_AF10)
#define GPIO_AF_LPTIM2_IN1_PE6              (GPIO_AF6)
#define GPIO_AF_LPTIM2_IN1_PH3              (GPIO_AF1)
#define GPIO_AF_LPTIM2_IN2_PA4              (GPIO_AF13)
#define GPIO_AF_LPTIM2_OUT_PC4              (GPIO_AF15)

/* FDCAN1/2/3 */
#define GPIO_AF_FDCAN1_TX                   (GPIO_AF25)
#define GPIO_AF_FDCAN1_RX                   (GPIO_AF26)
#define GPIO_AF_FDCAN2_TX                   (GPIO_AF27)
#define GPIO_AF_FDCAN2_RX                   (GPIO_AF28)
#define GPIO_AF_FDCAN3_TX                   (GPIO_AF29)
#define GPIO_AF_FDCAN3_RX                   (GPIO_AF30)

/* DVP */
#define GPIO_AF_DVP_PIXCLK_PA3              (GPIO_AF10)
#define GPIO_AF_DVP_PIXCLK_PA6              (GPIO_AF10)
#define GPIO_AF_DVP_PIXCLK_PE4              (GPIO_AF6)
#define GPIO_AF_DVP_HSYNC_PA1               (GPIO_AF9)
#define GPIO_AF_DVP_HSYNC_PA4               (GPIO_AF10)
#define GPIO_AF_DVP_HSYNC_PE2               (GPIO_AF6)
#define GPIO_AF_DVP_VSYNC_PA2               (GPIO_AF10)
#define GPIO_AF_DVP_VSYNC_PB7               (GPIO_AF12)
#define GPIO_AF_DVP_VSYNC_PE3               (GPIO_AF6)
#define GPIO_AF_DVP_VSYNC_PG9               (GPIO_AF9)
#define GPIO_AF_DVP_D0_PA4                  (GPIO_AF6)
#define GPIO_AF_DVP_D0_PA9                  (GPIO_AF10)
#define GPIO_AF_DVP_D0_PC6                  (GPIO_AF8)
#define GPIO_AF_DVP_D0_PD6                  (GPIO_AF8)
#define GPIO_AF_DVP_D0_PE5                  (GPIO_AF7)
#define GPIO_AF_DVP_D1_PA5                  (GPIO_AF5)
#define GPIO_AF_DVP_D1_PA10                 (GPIO_AF10)
#define GPIO_AF_DVP_D1_PC7                  (GPIO_AF8)
#define GPIO_AF_DVP_D1_PE6                  (GPIO_AF7)
#define GPIO_AF_DVP_D2_PA6                  (GPIO_AF14)
#define GPIO_AF_DVP_D2_PC0                  (GPIO_AF9)
#define GPIO_AF_DVP_D2_PC8                  (GPIO_AF8)
#define GPIO_AF_DVP_D2_PE0                  (GPIO_AF8)
#define GPIO_AF_DVP_D2_PG10                 (GPIO_AF9)
#define GPIO_AF_DVP_D3_PA7                  (GPIO_AF14)
#define GPIO_AF_DVP_D3_PB2                  (GPIO_AF11)
#define GPIO_AF_DVP_D3_PC9                  (GPIO_AF8)
#define GPIO_AF_DVP_D3_PE1                  (GPIO_AF8)
#define GPIO_AF_DVP_D3_PG11                 (GPIO_AF9)
#define GPIO_AF_DVP_D4_PB10                 (GPIO_AF12)
#define GPIO_AF_DVP_D4_PC4                  (GPIO_AF1)
#define GPIO_AF_DVP_D4_PC11                 (GPIO_AF8)
#define GPIO_AF_DVP_D4_PE4                  (GPIO_AF8)
#define GPIO_AF_DVP_D4_PF12                 (GPIO_AF8)
#define GPIO_AF_DVP_D5_PB6                  (GPIO_AF12)
#define GPIO_AF_DVP_D5_PB11                 (GPIO_AF12)
#define GPIO_AF_DVP_D5_PC5                  (GPIO_AF1)
#define GPIO_AF_DVP_D5_PD3                  (GPIO_AF8)
#define GPIO_AF_DVP_D5_PF13                 (GPIO_AF8)
#define GPIO_AF_DVP_D6_PB0                  (GPIO_AF11)
#define GPIO_AF_DVP_D6_PB8                  (GPIO_AF12)
#define GPIO_AF_DVP_D6_PE5                  (GPIO_AF8)
#define GPIO_AF_DVP_D6_PF14                 (GPIO_AF8)
#define GPIO_AF_DVP_D7_PB1                  (GPIO_AF11)
#define GPIO_AF_DVP_D7_PB9                  (GPIO_AF12)
#define GPIO_AF_DVP_D7_PE6                  (GPIO_AF8)
#define GPIO_AF_DVP_D7_PF15                 (GPIO_AF8)
#define GPIO_AF_DVP_D8_PC10                 (GPIO_AF8)
#define GPIO_AF_DVP_D9_PC12                 (GPIO_AF8)
#define GPIO_AF_DVP_D10_PB5                 (GPIO_AF0)
#define GPIO_AF_DVP_D11_PD2                 (GPIO_AF8)
#define GPIO_AF_DVP_D11_PF10                (GPIO_AF8)
#define GPIO_AF_DVP_D12_PF11                (GPIO_AF8)
#define GPIO_AF_DVP_D12_PG6                 (GPIO_AF9)
#define GPIO_AF_DVP_D12_PH3                 (GPIO_AF7)
#define GPIO_AF_DVP_D13_PB14                (GPIO_AF11)
#define GPIO_AF_DVP_D13_PG7                 (GPIO_AF9)
#define GPIO_AF_DVP_D13_PG15                (GPIO_AF8)
#define GPIO_AF_DVP_D13_PH2                 (GPIO_AF7)
#define GPIO_AF_DVP_D14_PB15                (GPIO_AF9)
#define GPIO_AF_DVP_D14_PF6                 (GPIO_AF13)
#define GPIO_AF_DVP_D15_PC0                 (GPIO_AF12)
#define GPIO_AF_DVP_D15_PF9                 (GPIO_AF8)

/* FEMC */
#define GPIO_AF_FEMC_A0_PF0                 (GPIO_AF10)
#define GPIO_AF_FEMC_A0_PF10                (GPIO_AF10)
#define GPIO_AF_FEMC_A1_PF1                 (GPIO_AF10)
#define GPIO_AF_FEMC_A1_PF7                 (GPIO_AF10)
#define GPIO_AF_FEMC_A2_PF2                 (GPIO_AF10)
#define GPIO_AF_FEMC_A3_PF3                 (GPIO_AF10)
#define GPIO_AF_FEMC_A4_PF4                 (GPIO_AF10)
#define GPIO_AF_FEMC_A5_PF5                 (GPIO_AF10)
#define GPIO_AF_FEMC_A6_PF12                (GPIO_AF10)
#define GPIO_AF_FEMC_A7_PF13                (GPIO_AF10)
#define GPIO_AF_FEMC_A8_PF14                (GPIO_AF10)
#define GPIO_AF_FEMC_A9_PF15                (GPIO_AF10)
#define GPIO_AF_FEMC_A10_PG0                (GPIO_AF10)
#define GPIO_AF_FEMC_A11_PG1                (GPIO_AF10)
#define GPIO_AF_FEMC_A12_PG2                (GPIO_AF10)
#define GPIO_AF_FEMC_A13_PG3                (GPIO_AF10)
#define GPIO_AF_FEMC_A14_PG4                (GPIO_AF10)
#define GPIO_AF_FEMC_A15_PG5                (GPIO_AF10)
#define GPIO_AF_FEMC_A16_PC6                (GPIO_AF14)
#define GPIO_AF_FEMC_A16_PD11               (GPIO_AF10)
#define GPIO_AF_FEMC_A17_PC7                (GPIO_AF14)
#define GPIO_AF_FEMC_A17_PD12               (GPIO_AF10)
#define GPIO_AF_FEMC_A18_PD13               (GPIO_AF10)
#define GPIO_AF_FEMC_A19_PE3                (GPIO_AF10)
#define GPIO_AF_FEMC_A20_PE4                (GPIO_AF10)
#define GPIO_AF_FEMC_A21_PE5                (GPIO_AF10)
#define GPIO_AF_FEMC_A22_PE6                (GPIO_AF10)
#define GPIO_AF_FEMC_A23_PE2                (GPIO_AF10)
#define GPIO_AF_FEMC_A24_PF8                (GPIO_AF10)
#define GPIO_AF_FEMC_A24_PG13               (GPIO_AF10)
#define GPIO_AF_FEMC_A25_PF9                (GPIO_AF10)
#define GPIO_AF_FEMC_A25_PG14               (GPIO_AF10)
#define GPIO_AF_FEMC_D0_PD14                (GPIO_AF10)
#define GPIO_AF_FEMC_D1_PD15                (GPIO_AF10)
#define GPIO_AF_FEMC_D2_PD0                 (GPIO_AF10)
#define GPIO_AF_FEMC_D3_PD1                 (GPIO_AF10)
#define GPIO_AF_FEMC_D4_PE7                 (GPIO_AF10)
#define GPIO_AF_FEMC_D5_PE8                 (GPIO_AF10)
#define GPIO_AF_FEMC_D6_PE9                 (GPIO_AF10)
#define GPIO_AF_FEMC_D7_PE10                (GPIO_AF10)
#define GPIO_AF_FEMC_D8_PE11                (GPIO_AF10)
#define GPIO_AF_FEMC_D9_PE12                (GPIO_AF10)
#define GPIO_AF_FEMC_D10_PE13               (GPIO_AF10)
#define GPIO_AF_FEMC_D11_PE14               (GPIO_AF10)
#define GPIO_AF_FEMC_D11_PB10               (GPIO_AF14)
#define GPIO_AF_FEMC_D12_PE15               (GPIO_AF10)
#define GPIO_AF_FEMC_D12_PB11               (GPIO_AF14)
#define GPIO_AF_FEMC_D13_PD8                (GPIO_AF10)
#define GPIO_AF_FEMC_D14_PD9                (GPIO_AF10)
#define GPIO_AF_FEMC_D15_PD10               (GPIO_AF10)
#define GPIO_AF_FEMC_NE1_PB9                (GPIO_AF0)
#define GPIO_AF_FEMC_NE1_PD7                (GPIO_AF11)
#define GPIO_AF_FEMC_NE2_PB6                (GPIO_AF15)
#define GPIO_AF_FEMC_NE2_PG9                (GPIO_AF10)
#define GPIO_AF_FEMC_NE3_PG8                (GPIO_AF10)
#define GPIO_AF_FEMC_NE3_PG10               (GPIO_AF10)
#define GPIO_AF_FEMC_NE4_PF11               (GPIO_AF10)
#define GPIO_AF_FEMC_NE4_PG12               (GPIO_AF10)
#define GPIO_AF_FEMC_NCE2_PB9               (GPIO_AF9)
#define GPIO_AF_FEMC_NCE2_PD7               (GPIO_AF10)
#define GPIO_AF_FEMC_NCE3_PB6               (GPIO_AF10)
#define GPIO_AF_FEMC_NCE3_PG9               (GPIO_AF11)
#define GPIO_AF_FEMC_NOE_PC9                (GPIO_AF14)
#define GPIO_AF_FEMC_NOE_PD4                (GPIO_AF10)
#define GPIO_AF_FEMC_NWE_PA10               (GPIO_AF15)
#define GPIO_AF_FEMC_NWE_PD5                (GPIO_AF10)
#define GPIO_AF_FEMC_NADV_PB7               (GPIO_AF13)
#define GPIO_AF_FEMC_NWAIT_PB8              (GPIO_AF15)
#define GPIO_AF_FEMC_NWAIT_PD6              (GPIO_AF10)
#define GPIO_AF_FEMC_NBL0_PE0               (GPIO_AF10)
#define GPIO_AF_FEMC_NBL1_PE1               (GPIO_AF10)
#define GPIO_AF_FEMC_ALE_PD12               (GPIO_AF11)
#define GPIO_AF_FEMC_CLE_PD11               (GPIO_AF11)
#define GPIO_AF_FEMC_CLK_PD3                (GPIO_AF10)
#define GPIO_AF_FEMC_INT2_PG6               (GPIO_AF10)
#define GPIO_AF_FEMC_INT3_PG7               (GPIO_AF10)

/* USART1 */
#define GPIO_AF_USART1_TX_PA4               (GPIO_AF15)
#define GPIO_AF_USART1_TX_PA9               (GPIO_AF5)
#define GPIO_AF_USART1_TX_PA15              (GPIO_AF10)
#define GPIO_AF_USART1_TX_PB6               (GPIO_AF1)
#define GPIO_AF_USART1_TX_PC4               (GPIO_AF5)
#define GPIO_AF_USART1_TX_PE0               (GPIO_AF7)
#define GPIO_AF_USART1_TX_PG9               (GPIO_AF8)
#define GPIO_AF_USART1_TX_PH4               (GPIO_AF1)
#define GPIO_AF_USART1_RX_PA5               (GPIO_AF15)
#define GPIO_AF_USART1_RX_PA10              (GPIO_AF5)
#define GPIO_AF_USART1_RX_PB3               (GPIO_AF13)
#define GPIO_AF_USART1_RX_PB7               (GPIO_AF1)
#define GPIO_AF_USART1_RX_PC5               (GPIO_AF5)
#define GPIO_AF_USART1_RX_PE1               (GPIO_AF7)
#define GPIO_AF_USART1_RX_PG15              (GPIO_AF5)
#define GPIO_AF_USART1_RX_PH2               (GPIO_AF1)
#define GPIO_AF_USART1_CK_PA8               (GPIO_AF5)
#define GPIO_AF_USART1_CTS_PA11             (GPIO_AF5)
#define GPIO_AF_USART1_RTS_DE_PA12          (GPIO_AF5)

/* USART2 */
#define GPIO_AF_USART2_TX_PA2               (GPIO_AF5)
#define GPIO_AF_USART2_TX_PA14              (GPIO_AF5)
#define GPIO_AF_USART2_TX_PB3               (GPIO_AF9)
#define GPIO_AF_USART2_TX_PB4               (GPIO_AF8)
#define GPIO_AF_USART2_TX_PC8               (GPIO_AF15)
#define GPIO_AF_USART2_TX_PD5               (GPIO_AF6)
#define GPIO_AF_USART2_TX_PH1               (GPIO_AF2)
#define GPIO_AF_USART2_RX_PA3               (GPIO_AF5)
#define GPIO_AF_USART2_RX_PA15              (GPIO_AF5)
#define GPIO_AF_USART2_RX_PB4               (GPIO_AF9)
#define GPIO_AF_USART2_RX_PB5               (GPIO_AF15)
#define GPIO_AF_USART2_RX_PC9               (GPIO_AF15)
#define GPIO_AF_USART2_RX_PD6               (GPIO_AF6)
#define GPIO_AF_USART2_RX_PH0               (GPIO_AF2)
#define GPIO_AF_USART2_CK_PA4               (GPIO_AF5)
#define GPIO_AF_USART2_CK_PB5               (GPIO_AF9)
#define GPIO_AF_USART2_CK_PD7               (GPIO_AF6)
#define GPIO_AF_USART2_CTS_PA0              (GPIO_AF5)
#define GPIO_AF_USART2_CTS_PA15             (GPIO_AF14)
#define GPIO_AF_USART2_CTS_PC6              (GPIO_AF10)
#define GPIO_AF_USART2_CTS_PD3              (GPIO_AF6)
#define GPIO_AF_USART2_RTS_DE_PA1           (GPIO_AF5)
#define GPIO_AF_USART2_RTS_DE_PB3           (GPIO_AF10)
#define GPIO_AF_USART2_RTS_DE_PC7           (GPIO_AF10)
#define GPIO_AF_USART2_RTS_DE_PD4           (GPIO_AF6)

/* USART3 */
#define GPIO_AF_USART3_TX                   (GPIO_AF17)
#define GPIO_AF_USART3_RX                   (GPIO_AF18)
#define GPIO_AF_USART3_CK_PB12              (GPIO_AF9)
#define GPIO_AF_USART3_CK_PC12              (GPIO_AF6)
#define GPIO_AF_USART3_CK_PD10              (GPIO_AF6)
#define GPIO_AF_USART3_CTS_PA13             (GPIO_AF5)
#define GPIO_AF_USART3_CTS_PB13             (GPIO_AF9)
#define GPIO_AF_USART3_CTS_PD11             (GPIO_AF6)
#define GPIO_AF_USART3_RTS_DE               (GPIO_AF16)

/* USART4 */
#define GPIO_AF_USART4_TX_PA11              (GPIO_AF14)
#define GPIO_AF_USART4_TX_PB0               (GPIO_AF13)
#define GPIO_AF_USART4_TX_PC0               (GPIO_AF10)
#define GPIO_AF_USART4_TX_PC6               (GPIO_AF5)
#define GPIO_AF_USART4_TX_PD11              (GPIO_AF12)
#define GPIO_AF_USART4_TX_PE2               (GPIO_AF7)
#define GPIO_AF_USART4_TX_PE10              (GPIO_AF9)
#define GPIO_AF_USART4_TX_PG14              (GPIO_AF6)
#define GPIO_AF_USART4_RX_PA12              (GPIO_AF14)
#define GPIO_AF_USART4_RX_PB1               (GPIO_AF13)
#define GPIO_AF_USART4_RX_PC1               (GPIO_AF10)
#define GPIO_AF_USART4_RX_PC7               (GPIO_AF5)
#define GPIO_AF_USART4_RX_PE3               (GPIO_AF7)
#define GPIO_AF_USART4_RX_PE11              (GPIO_AF9)
#define GPIO_AF_USART4_RX_PE15              (GPIO_AF5)
#define GPIO_AF_USART4_RX_PG9               (GPIO_AF6)
#define GPIO_AF_USART4_CK_PB14              (GPIO_AF9)
#define GPIO_AF_USART4_CK_PC8               (GPIO_AF5)
#define GPIO_AF_USART4_CK_PG7               (GPIO_AF6)
#define GPIO_AF_USART4_CTS_PG13             (GPIO_AF6)
#define GPIO_AF_USART4_CTS_PG15             (GPIO_AF6)
#define GPIO_AF_USART4_RTS_DE_PG8           (GPIO_AF6)
#define GPIO_AF_USART4_RTS_DE_PG12          (GPIO_AF6)
#define GPIO_AF_USART4_RTS_DE_PH2           (GPIO_AF2)

/* UART5 */
#define GPIO_AF_UART5_TX                    (GPIO_AF20)
#define GPIO_AF_UART5_RX                    (GPIO_AF21)
#define GPIO_AF_UART5_CTS_PB5               (GPIO_AF8)
#define GPIO_AF_UART5_RTS_DE                (GPIO_AF19)

/* UART6 */
#define GPIO_AF_UART6_TX_PA0                (GPIO_AF11)
#define GPIO_AF_UART6_TX_PA13               (GPIO_AF12)
#define GPIO_AF_UART6_TX_PB2                (GPIO_AF12)
#define GPIO_AF_UART6_TX_PC10               (GPIO_AF7)
#define GPIO_AF_UART6_TX_PD0                (GPIO_AF6)
#define GPIO_AF_UART6_RX_PA1                (GPIO_AF11)
#define GPIO_AF_UART6_RX_PA14               (GPIO_AF12)
#define GPIO_AF_UART6_RX_PC11               (GPIO_AF7)
#define GPIO_AF_UART6_RX_PD1                (GPIO_AF6)
#define GPIO_AF_UART6_RX_PE7                (GPIO_AF8)
#define GPIO_AF_UART6_CTS_PB7               (GPIO_AF8)
#define GPIO_AF_UART6_RTS_DE_PA15           (GPIO_AF11)

/* UART7 */
#define GPIO_AF_UART7_TX_PA2                (GPIO_AF11)
#define GPIO_AF_UART7_TX_PB11               (GPIO_AF8)
#define GPIO_AF_UART7_TX_PC1                (GPIO_AF7)
#define GPIO_AF_UART7_TX_PC2                (GPIO_AF13)
#define GPIO_AF_UART7_TX_PC4                (GPIO_AF13)
#define GPIO_AF_UART7_TX_PE8                (GPIO_AF9)
#define GPIO_AF_UART7_TX_PF7                (GPIO_AF12)
#define GPIO_AF_UART7_TX_PG0                (GPIO_AF8)
#define GPIO_AF_UART7_TX_PG7                (GPIO_AF8)
#define GPIO_AF_UART7_RX_PA3                (GPIO_AF11)
#define GPIO_AF_UART7_RX_PB10               (GPIO_AF8)
#define GPIO_AF_UART7_RX_PC0                (GPIO_AF7)
#define GPIO_AF_UART7_RX_PC3                (GPIO_AF13)
#define GPIO_AF_UART7_RX_PC5                (GPIO_AF13)
#define GPIO_AF_UART7_RX_PE7                (GPIO_AF9)
#define GPIO_AF_UART7_RX_PF6                (GPIO_AF12)
#define GPIO_AF_UART7_RX_PG1                (GPIO_AF8)
#define GPIO_AF_UART7_RX_PG8                (GPIO_AF8)
#define GPIO_AF_UART7_CTS_PA6               (GPIO_AF11)
#define GPIO_AF_UART7_CTS_PB13              (GPIO_AF8)
#define GPIO_AF_UART7_CTS_PG5               (GPIO_AF8)
#define GPIO_AF_UART7_RTS_DE_PB1            (GPIO_AF9)
#define GPIO_AF_UART7_RTS_DE_PB12           (GPIO_AF8)
#define GPIO_AF_UART7_RTS_DE_PG6            (GPIO_AF8)

/* UART8 */
#define GPIO_AF_UART8_TX                    (GPIO_AF23)
#define GPIO_AF_UART8_RX                    (GPIO_AF24)
#define GPIO_AF_UART8_CTS_PB15              (GPIO_AF8)
#define GPIO_AF_UART8_CTS_PF0               (GPIO_AF6)
#define GPIO_AF_UART8_CTS_PH3               (GPIO_AF2)
#define GPIO_AF_UART8_RTS_DE                (GPIO_AF22)

/* I2C1 */
#define GPIO_AF_I2C1_SCL_PA9                (GPIO_AF15)
#define GPIO_AF_I2C1_SCL_PA13               (GPIO_AF8)
#define GPIO_AF_I2C1_SCL_PA15               (GPIO_AF9)
#define GPIO_AF_I2C1_SCL_PB6                (GPIO_AF2)
#define GPIO_AF_I2C1_SCL_PB8                (GPIO_AF2)
#define GPIO_AF_I2C1_SCL_PD11               (GPIO_AF5)
#define GPIO_AF_I2C1_SCL_PG14               (GPIO_AF7)
#define GPIO_AF_I2C1_SDA_PA14               (GPIO_AF11)
#define GPIO_AF_I2C1_SDA_PB7                (GPIO_AF2)
#define GPIO_AF_I2C1_SDA_PB9                (GPIO_AF13)
#define GPIO_AF_I2C1_SDA_PD1                (GPIO_AF7)
#define GPIO_AF_I2C1_SDA_PE15               (GPIO_AF9)
#define GPIO_AF_I2C1_SDA_PG15               (GPIO_AF7)
#define GPIO_AF_I2C1_SMBA_PB5               (GPIO_AF12)

/* I2C2 */
#define GPIO_AF_I2C2_SCL_PA4                (GPIO_AF11)
#define GPIO_AF_I2C2_SCL_PA9                (GPIO_AF11)
#define GPIO_AF_I2C2_SCL_PB10               (GPIO_AF7)
#define GPIO_AF_I2C2_SCL_PC4                (GPIO_AF7)
#define GPIO_AF_I2C2_SCL_PF1                (GPIO_AF7)
#define GPIO_AF_I2C2_SCL_PF6                (GPIO_AF7)
#define GPIO_AF_I2C2_SCL_PG2                (GPIO_AF6)
#define GPIO_AF_I2C2_SCL_PH1                (GPIO_AF7)
#define GPIO_AF_I2C2_SDA_PA5                (GPIO_AF11)
#define GPIO_AF_I2C2_SDA_PA8                (GPIO_AF11)
#define GPIO_AF_I2C2_SDA_PA10               (GPIO_AF11)
#define GPIO_AF_I2C2_SDA_PB3                (GPIO_AF12)
#define GPIO_AF_I2C2_SDA_PB11               (GPIO_AF7)
#define GPIO_AF_I2C2_SDA_PC12               (GPIO_AF9)
#define GPIO_AF_I2C2_SDA_PF0                (GPIO_AF7)
#define GPIO_AF_I2C2_SDA_PG3                (GPIO_AF6)
#define GPIO_AF_I2C2_SDA_PH0                (GPIO_AF7)
#define GPIO_AF_I2C2_SMBA_PA8               (GPIO_AF8)
#define GPIO_AF_I2C2_SMBA_PA10              (GPIO_AF8)
#define GPIO_AF_I2C2_SMBA_PB12              (GPIO_AF7)
#define GPIO_AF_I2C2_SMBA_PF2               (GPIO_AF7)

/* I2C3 */
#define GPIO_AF_I2C3_SCL_PA8                (GPIO_AF7)
#define GPIO_AF_I2C3_SCL_PC0                (GPIO_AF8)
#define GPIO_AF_I2C3_SCL_PC4                (GPIO_AF14)
#define GPIO_AF_I2C3_SCL_PC8                (GPIO_AF7)
#define GPIO_AF_I2C3_SCL_PF3                (GPIO_AF7)
#define GPIO_AF_I2C3_SCL_PF4                (GPIO_AF6)
#define GPIO_AF_I2C3_SCL_PG7                (GPIO_AF7)
#define GPIO_AF_I2C3_SDA_PB4                (GPIO_AF12)
#define GPIO_AF_I2C3_SDA_PB5                (GPIO_AF11)
#define GPIO_AF_I2C3_SDA_PC1                (GPIO_AF9)
#define GPIO_AF_I2C3_SDA_PC5                (GPIO_AF14)
#define GPIO_AF_I2C3_SDA_PC9                (GPIO_AF7)
#define GPIO_AF_I2C3_SDA_PC11               (GPIO_AF9)
#define GPIO_AF_I2C3_SDA_PF4                (GPIO_AF7)
#define GPIO_AF_I2C3_SDA_PF5                (GPIO_AF7)
#define GPIO_AF_I2C3_SDA_PG8                (GPIO_AF7)
#define GPIO_AF_I2C3_SMBA_PA9               (GPIO_AF8)
#define GPIO_AF_I2C3_SMBA_PB2               (GPIO_AF7)
#define GPIO_AF_I2C3_SMBA_PG6               (GPIO_AF7)

/* I2C4 */
#define GPIO_AF_I2C4_SCL_PA9                (GPIO_AF13)
#define GPIO_AF_I2C4_SCL_PA13               (GPIO_AF7)
#define GPIO_AF_I2C4_SCL_PC6                (GPIO_AF7)
#define GPIO_AF_I2C4_SCL_PD14               (GPIO_AF9)
#define GPIO_AF_I2C4_SCL_PF14               (GPIO_AF7)
#define GPIO_AF_I2C4_SCL_PG3                (GPIO_AF7)
#define GPIO_AF_I2C4_SDA_PA10               (GPIO_AF6)
#define GPIO_AF_I2C4_SDA_PB7                (GPIO_AF9)
#define GPIO_AF_I2C4_SDA_PC7                (GPIO_AF7)
#define GPIO_AF_I2C4_SDA_PD15               (GPIO_AF9)
#define GPIO_AF_I2C4_SDA_PF15               (GPIO_AF7)
#define GPIO_AF_I2C4_SDA_PG4                (GPIO_AF7)
#define GPIO_AF_I2C4_SMBA_PA14              (GPIO_AF8)
#define GPIO_AF_I2C4_SMBA_PD11              (GPIO_AF9)
#define GPIO_AF_I2C4_SMBA_PF13              (GPIO_AF7)

/* SPI1 */
#define GPIO_AF_SPI1_NSS_PA4                (GPIO_AF1)
#define GPIO_AF_SPI1_NSS_PA15               (GPIO_AF2)
#define GPIO_AF_SPI1_NSS_PB2                (GPIO_AF14)
#define GPIO_AF_SPI1_NSS_PG5                (GPIO_AF1)
#define GPIO_AF_SPI1_SCK_PA5                (GPIO_AF1)
#define GPIO_AF_SPI1_SCK_PB3                (GPIO_AF2)
#define GPIO_AF_SPI1_SCK_PE7                (GPIO_AF1)
#define GPIO_AF_SPI1_SCK_PG2                (GPIO_AF1)
#define GPIO_AF_SPI1_MISO_PA6               (GPIO_AF1)
#define GPIO_AF_SPI1_MISO_PB4               (GPIO_AF2)
#define GPIO_AF_SPI1_MISO_PE8               (GPIO_AF1)
#define GPIO_AF_SPI1_MISO_PG3               (GPIO_AF1)
#define GPIO_AF_SPI1_MOSI_PA7               (GPIO_AF1)
#define GPIO_AF_SPI1_MOSI_PB5               (GPIO_AF2)
#define GPIO_AF_SPI1_MOSI_PE9               (GPIO_AF1)
#define GPIO_AF_SPI1_MOSI_PG4               (GPIO_AF1)

/* SPI2 */
#define GPIO_AF_SPI2_NSS_PA12               (GPIO_AF9)
#define GPIO_AF_SPI2_NSS_PD15               (GPIO_AF1)
#define GPIO_AF_SPI2_NSS_PB9                (GPIO_AF2)
#define GPIO_AF_SPI2_NSS_PB12               (GPIO_AF1)
#define GPIO_AF_SPI2_NSS_PC6                (GPIO_AF13)
#define GPIO_AF_SPI2_NSS_PD1                (GPIO_AF1)
#define GPIO_AF_SPI2_NSS_PE10               (GPIO_AF1)
#define GPIO_AF_SPI2_NSS_PH0                (GPIO_AF1)
#define GPIO_AF_SPI2_SCK_PF9                (GPIO_AF1)
#define GPIO_AF_SPI2_SCK_PF10               (GPIO_AF1)
#define GPIO_AF_SPI2_SCK_PA9                (GPIO_AF12)
#define GPIO_AF_SPI2_SCK_PB10               (GPIO_AF2)
#define GPIO_AF_SPI2_SCK_PB13               (GPIO_AF1)
#define GPIO_AF_SPI2_SCK_PC7                (GPIO_AF13)
#define GPIO_AF_SPI2_SCK_PD3                (GPIO_AF1)
#define GPIO_AF_SPI2_SCK_PE11               (GPIO_AF6)
#define GPIO_AF_SPI2_SCK_PH1                (GPIO_AF1)
#define GPIO_AF_SPI2_MISO_PA10              (GPIO_AF1)
#define GPIO_AF_SPI2_MISO_PB14              (GPIO_AF1)
#define GPIO_AF_SPI2_MISO_PC2               (GPIO_AF1)
#define GPIO_AF_SPI2_MISO_PC8               (GPIO_AF13)
#define GPIO_AF_SPI2_MISO_PE12              (GPIO_AF6)
#define GPIO_AF_SPI2_MISO_PG9               (GPIO_AF7)
#define GPIO_AF_SPI2_MISO_PG14              (GPIO_AF9)
#define GPIO_AF_SPI2_MOSI_PD2               (GPIO_AF11)
#define GPIO_AF_SPI2_MOSI_PG9               (GPIO_AF2)
#define GPIO_AF_SPI2_MOSI_PA11              (GPIO_AF1)
#define GPIO_AF_SPI2_MOSI_PB15              (GPIO_AF1)
#define GPIO_AF_SPI2_MOSI_PC1               (GPIO_AF2)
#define GPIO_AF_SPI2_MOSI_PC3               (GPIO_AF1)
#define GPIO_AF_SPI2_MOSI_PC9               (GPIO_AF13)
#define GPIO_AF_SPI2_MOSI_PE13              (GPIO_AF6)

/* I2S2 */
#define GPIO_AF_I2S2_WS_PB9                 (GPIO_AF2)
#define GPIO_AF_I2S2_WS_PB12                (GPIO_AF1)
#define GPIO_AF_I2S2_WS_PC6                 (GPIO_AF13)
#define GPIO_AF_I2S2_WS_PD1                 (GPIO_AF1)
#define GPIO_AF_I2S2_WS_PE10                (GPIO_AF1)
#define GPIO_AF_I2S2_WS_PH0                 (GPIO_AF1)
#define GPIO_AF_I2S2_CK_PA9                 (GPIO_AF12)
#define GPIO_AF_I2S2_CK_PB10                (GPIO_AF2)
#define GPIO_AF_I2S2_CK_PB13                (GPIO_AF1)
#define GPIO_AF_I2S2_CK_PC7                 (GPIO_AF13)
#define GPIO_AF_I2S2_CK_PD3                 (GPIO_AF1)
#define GPIO_AF_I2S2_CK_PE11                (GPIO_AF6)
#define GPIO_AF_I2S2_CK_PH1                 (GPIO_AF1)
#define GPIO_AF_I2S2_SD_PA11                (GPIO_AF1)
#define GPIO_AF_I2S2_SD_PB15                (GPIO_AF1)
#define GPIO_AF_I2S2_SD_PC1                 (GPIO_AF2)
#define GPIO_AF_I2S2_SD_PC3                 (GPIO_AF1)
#define GPIO_AF_I2S2_SD_PC9                 (GPIO_AF13)
#define GPIO_AF_I2S2_SD_PE13                (GPIO_AF6)
#define GPIO_AF_I2S2_MCK_PA3                (GPIO_AF9)
#define GPIO_AF_I2S2_MCK_PA6                (GPIO_AF12)
#define GPIO_AF_I2S2_MCK_PA8                (GPIO_AF1)
#define GPIO_AF_I2S2_MCK_PC6                (GPIO_AF1)
#define GPIO_AF_I2S2_AUX_SD_PA10            (GPIO_AF13)
#define GPIO_AF_I2S2_AUX_SD_PB14            (GPIO_AF2)
#define GPIO_AF_I2S2_AUX_SD_PC2             (GPIO_AF2)

/* SPI3 */
#define GPIO_AF_SPI3_NSS_PA4                (GPIO_AF2)
#define GPIO_AF_SPI3_NSS_PA15               (GPIO_AF1)
#define GPIO_AF_SPI3_NSS_PC2                (GPIO_AF12)
#define GPIO_AF_SPI3_NSS_PD2                (GPIO_AF1)
#define GPIO_AF_SPI3_NSS_PD8                (GPIO_AF1)
#define GPIO_AF_SPI3_SCK_PG9                (GPIO_AF1)
#define GPIO_AF_SPI3_SCK_PB3                (GPIO_AF1)
#define GPIO_AF_SPI3_SCK_PC3                (GPIO_AF2)
#define GPIO_AF_SPI3_SCK_PC10               (GPIO_AF1)
#define GPIO_AF_SPI3_SCK_PD9                (GPIO_AF1)
#define GPIO_AF_SPI3_MISO_PA0               (GPIO_AF12)
#define GPIO_AF_SPI3_MISO_PB4               (GPIO_AF1)
#define GPIO_AF_SPI3_MISO_PC11              (GPIO_AF1)
#define GPIO_AF_SPI3_MISO_PD11              (GPIO_AF1)
#define GPIO_AF_SPI3_MOSI_PD0               (GPIO_AF2)
#define GPIO_AF_SPI3_MOSI_PA1               (GPIO_AF12)
#define GPIO_AF_SPI3_MOSI_PB0               (GPIO_AF9)
#define GPIO_AF_SPI3_MOSI_PB2               (GPIO_AF1)
#define GPIO_AF_SPI3_MOSI_PB5               (GPIO_AF1)
#define GPIO_AF_SPI3_MOSI_PC1               (GPIO_AF1)
#define GPIO_AF_SPI3_MOSI_PC12              (GPIO_AF1)
#define GPIO_AF_SPI3_MOSI_PD6               (GPIO_AF1)
#define GPIO_AF_SPI3_MOSI_PD12              (GPIO_AF1)

/* I2S3 */
#define GPIO_AF_I2S3_WS_PA4                 (GPIO_AF2)
#define GPIO_AF_I2S3_WS_PA15                (GPIO_AF1)
#define GPIO_AF_I2S3_WS_PC2                 (GPIO_AF12)
#define GPIO_AF_I2S3_WS_PD2                 (GPIO_AF1)
#define GPIO_AF_I2S3_WS_PD8                 (GPIO_AF1)
#define GPIO_AF_I2S3_CK_PB3                 (GPIO_AF1)
#define GPIO_AF_I2S3_CK_PC3                 (GPIO_AF2)
#define GPIO_AF_I2S3_CK_PC10                (GPIO_AF1)
#define GPIO_AF_I2S3_CK_PD9                 (GPIO_AF1)
#define GPIO_AF_I2S3_SD_PA1                 (GPIO_AF12)
#define GPIO_AF_I2S3_SD_PB0                 (GPIO_AF9)
#define GPIO_AF_I2S3_SD_PB2                 (GPIO_AF1)
#define GPIO_AF_I2S3_SD_PB5                 (GPIO_AF1)
#define GPIO_AF_I2S3_SD_PC1                 (GPIO_AF1)
#define GPIO_AF_I2S3_SD_PC12                (GPIO_AF1)
#define GPIO_AF_I2S3_SD_PD6                 (GPIO_AF1)
#define GPIO_AF_I2S3_SD_PD12                (GPIO_AF1)
#define GPIO_AF_I2S3_MCK_PA9                (GPIO_AF1)
#define GPIO_AF_I2S3_MCK_PC7                (GPIO_AF1)
#define GPIO_AF_I2S3_AUX_SD_PB4             (GPIO_AF15)
#define GPIO_AF_I2S3_AUX_SD_PC11            (GPIO_AF3)

/* I2C CKIN */
#define GPIO_I2S_CKIN_PA2                   (GPIO_AF15)
#define GPIO_I2S_CKIN_PA12                  (GPIO_AF1)
#define GPIO_I2S_CKIN_PB11                  (GPIO_AF5)
#define GPIO_I2S_CKIN_PC9                   (GPIO_AF1)

/* SPI4 */
#define GPIO_AF_SPI4_NSS_PB12               (GPIO_AF12)
#define GPIO_AF_SPI4_NSS_PE3                (GPIO_AF1)
#define GPIO_AF_SPI4_NSS_PE4                (GPIO_AF1)
#define GPIO_AF_SPI4_NSS_PE11               (GPIO_AF1)
#define GPIO_AF_SPI4_NSS_PG14               (GPIO_AF8)
#define GPIO_AF_SPI4_SCK_PB13               (GPIO_AF12)
#define GPIO_AF_SPI4_SCK_PE2                (GPIO_AF1)
#define GPIO_AF_SPI4_SCK_PE12               (GPIO_AF1)
#define GPIO_AF_SPI4_SCK_PG11               (GPIO_AF8)
#define GPIO_AF_SPI4_MISO_PA11              (GPIO_AF13)
#define GPIO_AF_SPI4_MISO_PD0               (GPIO_AF1)
#define GPIO_AF_SPI4_MISO_PE5               (GPIO_AF1)
#define GPIO_AF_SPI4_MISO_PE13              (GPIO_AF1)
#define GPIO_AF_SPI4_MISO_PG12              (GPIO_AF8)
#define GPIO_AF_SPI4_MOSI_PA1               (GPIO_AF13)
#define GPIO_AF_SPI4_MOSI_PA12              (GPIO_AF13)
#define GPIO_AF_SPI4_MOSI_PE6               (GPIO_AF1)
#define GPIO_AF_SPI4_MOSI_PE14              (GPIO_AF1)
#define GPIO_AF_SPI4_MOSI_PG13              (GPIO_AF8)

/* SPI5 */
#define GPIO_AF_SPI5_NSS_PB1                (GPIO_AF14)
#define GPIO_AF_SPI5_NSS_PE11               (GPIO_AF5)
#define GPIO_AF_SPI5_NSS_PF6                (GPIO_AF11)
#define GPIO_AF_SPI5_SCK_PB0                (GPIO_AF8)
#define GPIO_AF_SPI5_SCK_PE12               (GPIO_AF5)
#define GPIO_AF_SPI5_SCK_PF7                (GPIO_AF11)
#define GPIO_AF_SPI5_MISO_PE13              (GPIO_AF5)
#define GPIO_AF_SPI5_MISO_PF8               (GPIO_AF11)
#define GPIO_AF_SPI5_MOSI_PA10              (GPIO_AF14)
#define GPIO_AF_SPI5_MOSI_PB8               (GPIO_AF0)
#define GPIO_AF_SPI5_MOSI_PE14              (GPIO_AF5)
#define GPIO_AF_SPI5_MOSI_PF9               (GPIO_AF11)
#define GPIO_AF_SPI5_MOSI_PF11              (GPIO_AF11)

/* SPI6 */
#define GPIO_AF_SPI6_NSS_PA2                (GPIO_AF6)
#define GPIO_AF_SPI6_NSS_PG15               (GPIO_AF1)
#define GPIO_AF_SPI6_SCK_PA1                (GPIO_AF14)
#define GPIO_AF_SPI6_MISO_PA4               (GPIO_AF14)
#define GPIO_AF_SPI6_MOSI_PA5               (GPIO_AF14)

/* SDIO */
#define GPIO_AF_SDIO_D0_PB4                 (GPIO_AF6)
#define GPIO_AF_SDIO_D0_PC8                 (GPIO_AF2)
#define GPIO_AF_SDIO_D0_PE8                 (GPIO_AF2)
#define GPIO_AF_SDIO_D1_PA8                 (GPIO_AF14)
#define GPIO_AF_SDIO_D1_PB0                 (GPIO_AF10)
#define GPIO_AF_SDIO_D1_PC9                 (GPIO_AF2)
#define GPIO_AF_SDIO_D1_PE9                 (GPIO_AF2)
#define GPIO_AF_SDIO_D2_PA9                 (GPIO_AF14)
#define GPIO_AF_SDIO_D2_PB1                 (GPIO_AF10)
#define GPIO_AF_SDIO_D2_PC10                (GPIO_AF2)
#define GPIO_AF_SDIO_D2_PE10                (GPIO_AF2)
#define GPIO_AF_SDIO_D3_PC11                (GPIO_AF2)
#define GPIO_AF_SDIO_D3_PE11                (GPIO_AF2)
#define GPIO_AF_SDIO_D4_PB8                 (GPIO_AF1)
#define GPIO_AF_SDIO_D5_PB9                 (GPIO_AF1)
#define GPIO_AF_SDIO_D6_PC6                 (GPIO_AF2)
#define GPIO_AF_SDIO_D7_PB10                (GPIO_AF1)
#define GPIO_AF_SDIO_D7_PC7                 (GPIO_AF2)
#define GPIO_AF_SDIO_CLK_PB2                (GPIO_AF10)
#define GPIO_AF_SDIO_CLK_PC12               (GPIO_AF2)
#define GPIO_AF_SDIO_CLK_PE12               (GPIO_AF2)
#define GPIO_AF_SDIO_CMD_PA6                (GPIO_AF13)
#define GPIO_AF_SDIO_CMD_PD2                (GPIO_AF2)
#define GPIO_AF_SDIO_CMD_PE13               (GPIO_AF2)

/* xSPI */
#define GPIO_AF_XSPI_NSS0_PA2               (GPIO_AF8)
#define GPIO_AF_XSPI_NSS0_PB11              (GPIO_AF6)
#define GPIO_AF_XSPI_NSS0_PD3               (GPIO_AF9)
#define GPIO_AF_XSPI_NSS0_PE11              (GPIO_AF7)
#define GPIO_AF_XSPI_NSS1_PA4               (GPIO_AF9)
#define GPIO_AF_XSPI_NSS1_PC10              (GPIO_AF13)
#define GPIO_AF_XSPI_NSS1_PF0               (GPIO_AF9)
#define GPIO_AF_XSPI_NSS1_PG8               (GPIO_AF5)
#define GPIO_AF_XSPI_CLK_PA3                (GPIO_AF8)
#define GPIO_AF_XSPI_CLK_PA5                (GPIO_AF9)
#define GPIO_AF_XSPI_CLK_PB10               (GPIO_AF6)
#define GPIO_AF_XSPI_CLK_PC11               (GPIO_AF13)
#define GPIO_AF_XSPI_CLK_PE10               (GPIO_AF7)
#define GPIO_AF_XSPI_CLK_PF1                (GPIO_AF9)
#define GPIO_AF_XSPI_CLK_PF10               (GPIO_AF9)
#define GPIO_AF_XSPI_CLK_PG13               (GPIO_AF5)
#define GPIO_AF_XSPI_IO0_PA5                (GPIO_AF8)
#define GPIO_AF_XSPI_IO0_PA6                (GPIO_AF15)
#define GPIO_AF_XSPI_IO0_PB1                (GPIO_AF2)
#define GPIO_AF_XSPI_IO0_PC12               (GPIO_AF13)
#define GPIO_AF_XSPI_IO0_PE12               (GPIO_AF7)
#define GPIO_AF_XSPI_IO0_PF2                (GPIO_AF9)
#define GPIO_AF_XSPI_IO0_PF8                (GPIO_AF9)
#define GPIO_AF_XSPI_IO0_PG14               (GPIO_AF5)
#define GPIO_AF_XSPI_IO1_PA7                (GPIO_AF15)
#define GPIO_AF_XSPI_IO1_PB0                (GPIO_AF2)
#define GPIO_AF_XSPI_IO1_PD0                (GPIO_AF9)
#define GPIO_AF_XSPI_IO1_PE13               (GPIO_AF7)
#define GPIO_AF_XSPI_IO1_PF3                (GPIO_AF9)
#define GPIO_AF_XSPI_IO1_PF9                (GPIO_AF9)
#define GPIO_AF_XSPI_IO1_PG12               (GPIO_AF5)
#define GPIO_AF_XSPI_IO2_PA7                (GPIO_AF8)
#define GPIO_AF_XSPI_IO2_PC4                (GPIO_AF9)
#define GPIO_AF_XSPI_IO2_PD1                (GPIO_AF9)
#define GPIO_AF_XSPI_IO2_PE14               (GPIO_AF7)
#define GPIO_AF_XSPI_IO2_PF4                (GPIO_AF9)
#define GPIO_AF_XSPI_IO2_PF7                (GPIO_AF9)
#define GPIO_AF_XSPI_IO2_PG10               (GPIO_AF5)
#define GPIO_AF_XSPI_IO3_PA6                (GPIO_AF8)
#define GPIO_AF_XSPI_IO3_PC5                (GPIO_AF9)
#define GPIO_AF_XSPI_IO3_PD2                (GPIO_AF9)
#define GPIO_AF_XSPI_IO3_PE15               (GPIO_AF7)
#define GPIO_AF_XSPI_IO3_PF5                (GPIO_AF9)
#define GPIO_AF_XSPI_IO3_PF6                (GPIO_AF9)
#define GPIO_AF_XSPI_IO3_PG11               (GPIO_AF5)
#define GPIO_AF_XSPI_IO4_PC1                (GPIO_AF8)
#define GPIO_AF_XSPI_IO4_PD4                (GPIO_AF9)
#define GPIO_AF_XSPI_IO5_PB2                (GPIO_AF2)
#define GPIO_AF_XSPI_IO5_PC2                (GPIO_AF8)
#define GPIO_AF_XSPI_IO5_PD5                (GPIO_AF9)
#define GPIO_AF_XSPI_IO6_PC3                (GPIO_AF8)
#define GPIO_AF_XSPI_IO6_PD6                (GPIO_AF9)
#define GPIO_AF_XSPI_IO7_PC4                (GPIO_AF8)
#define GPIO_AF_XSPI_IO7_PD7                (GPIO_AF9)
#define GPIO_AF_XSPI_RXDS_PC0               (GPIO_AF11)
#define GPIO_AF_XSPI_RXDS_PC13              (GPIO_AF8)
#define GPIO_AF_XSPI_RXDS_PD13              (GPIO_AF8)

/* ETH MII */
#define GPIO_AF_ETH_MDC_PC1                 (GPIO_AF11)
#define GPIO_AF_ETH_MDIO_PA2                (GPIO_AF1)
#define GPIO_AF_ETH_PPS_OUT_PB5             (GPIO_AF13)
#define GPIO_AF_ETH_PPS_OUT_PB6             (GPIO_AF13)
#define GPIO_AF_ETH_PPS_OUT_PG8             (GPIO_AF1)
#define GPIO_AF_ETH_MII_TXD3_PB7            (GPIO_AF15)
#define GPIO_AF_ETH_MII_TXD3_PB8            (GPIO_AF13)
#define GPIO_AF_ETH_MII_TXD3_PE2            (GPIO_AF8)
#define GPIO_AF_ETH_MII_TXD2_PC2            (GPIO_AF11)
#define GPIO_AF_ETH_MII_TXD1_PB13           (GPIO_AF13)
#define GPIO_AF_ETH_MII_TXD1_PG14           (GPIO_AF1)
#define GPIO_AF_ETH_MII_TXD0_PB12           (GPIO_AF13)
#define GPIO_AF_ETH_MII_TXD0_PG13           (GPIO_AF1)
#define GPIO_AF_ETH_MII_TX_CLK_PC3          (GPIO_AF11)
#define GPIO_AF_ETH_MII_TX_EN_PB11          (GPIO_AF1)
#define GPIO_AF_ETH_MII_TX_EN_PG11          (GPIO_AF1)
#define GPIO_AF_ETH_MII_RXD3_PB1            (GPIO_AF1)
#define GPIO_AF_ETH_MII_RXD3_PD12           (GPIO_AF8)
#define GPIO_AF_ETH_MII_RXD2_PB0            (GPIO_AF1)
#define GPIO_AF_ETH_MII_RXD2_PD11           (GPIO_AF8)
#define GPIO_AF_ETH_MII_RXD1_PC5            (GPIO_AF11)
#define GPIO_AF_ETH_MII_RXD1_PD10           (GPIO_AF8)
#define GPIO_AF_ETH_MII_RXD0_PC4            (GPIO_AF11)
#define GPIO_AF_ETH_MII_RXD0_PD9            (GPIO_AF8)
#define GPIO_AF_ETH_MII_RX_CLK_PA1          (GPIO_AF1)
#define GPIO_AF_ETH_MII_RX_DV_PA7           (GPIO_AF10)
#define GPIO_AF_ETH_MII_RX_DV_PD8           (GPIO_AF8)
#define GPIO_AF_ETH_MII_RX_ER_PB10          (GPIO_AF13)
#define GPIO_AF_ETH_MII_COL_PA3             (GPIO_AF1)
#define GPIO_AF_ETH_MII_CRS_PA0             (GPIO_AF1)

/* ETH RMII */
#define GPIO_AF_ETH_RMII_TXD1_PB13          (GPIO_AF2)
#define GPIO_AF_ETH_RMII_TXD1_PG14          (GPIO_AF2)
#define GPIO_AF_ETH_RMII_TXD0_PB12          (GPIO_AF2)
#define GPIO_AF_ETH_RMII_TXD0_PG13          (GPIO_AF2)
#define GPIO_AF_ETH_RMII_TX_EN_PB11         (GPIO_AF2)
#define GPIO_AF_ETH_RMII_TX_EN_PG11         (GPIO_AF2)
#define GPIO_AF_ETH_RMII_RXD1_PC5           (GPIO_AF10)
#define GPIO_AF_ETH_RMII_RXD1_PD10          (GPIO_AF9)
#define GPIO_AF_ETH_RMII_RXD0_PC4           (GPIO_AF10)
#define GPIO_AF_ETH_RMII_RXD0_PD9           (GPIO_AF9)
#define GPIO_AF_ETH_RMII_REF_CLK_PA1        (GPIO_AF7)
#define GPIO_AF_ETH_RMII_CRS_DV_PA7         (GPIO_AF11)
#define GPIO_AF_ETH_RMII_CRS_DV_PD8         (GPIO_AF9)

/* RTC */
#define GPIO_AF_RTC_REFIN_PA1               (GPIO_AF10)
#define GPIO_AF_RTC_REFIN_PB15              (GPIO_AF12)
#define GPIO_AF_RTC_TIMESTAMP               (GPIO_AF9)

/* USB HS */
#define GPIO_AF_USB_HS_ID_PB12              (GPIO_AF14)
#define GPIO_AF_USB_HS_SOF_PA4              (GPIO_AF8)

/* EVENT */
#define GPIO_AF_EVNET_OUT                   (GPIO_AF4)

/* COMP1 */
#define GPIO_AF_COMP1_OUT_PA0               (GPIO_AF9)
#define GPIO_AF_COMP1_OUT_PA6               (GPIO_AF9)
#define GPIO_AF_COMP1_OUT_PA11              (GPIO_AF8)
#define GPIO_AF_COMP1_OUT_PB1               (GPIO_AF12)
#define GPIO_AF_COMP1_OUT_PB8               (GPIO_AF11)
#define GPIO_AF_COMP1_OUT_PF4               (GPIO_AF8)

/* COMP2 */
#define GPIO_AF_COMP2_OUT_PA2               (GPIO_AF9)
#define GPIO_AF_COMP2_OUT_PA6               (GPIO_AF7)
#define GPIO_AF_COMP2_OUT_PA7               (GPIO_AF9)
#define GPIO_AF_COMP2_OUT_PA12              (GPIO_AF8)
#define GPIO_AF_COMP2_OUT_PB9               (GPIO_AF11)

/* COMP3 */
#define GPIO_AF_COMP3_OUT_PA2               (GPIO_AF13)
#define GPIO_AF_COMP3_OUT_PA8               (GPIO_AF9)
#define GPIO_AF_COMP3_OUT_PB7               (GPIO_AF11)
#define GPIO_AF_COMP3_OUT_PB10              (GPIO_AF11)
#define GPIO_AF_COMP3_OUT_PB15              (GPIO_AF11)
#define GPIO_AF_COMP3_OUT_PC2               (GPIO_AF9)
#define GPIO_AF_COMP3_OUT_PC8               (GPIO_AF9)
#define GPIO_AF_COMP3_OUT_PC10              (GPIO_AF9)

/* COMP4 */
#define GPIO_AF_COMP4_OUT_PB1               (GPIO_AF8)
#define GPIO_AF_COMP4_OUT_PB6               (GPIO_AF11)
#define GPIO_AF_COMP4_OUT_PB12              (GPIO_AF11)
#define GPIO_AF_COMP4_OUT_PB14              (GPIO_AF12)
#define GPIO_AF_COMP4_OUT_PC5               (GPIO_AF15)
#define GPIO_AF_COMP4_OUT_PC11              (GPIO_AF10)

/* COMP5 */
#define GPIO_AF_COMP5_OUT_PA9               (GPIO_AF9)
#define GPIO_AF_COMP5_OUT_PA11              (GPIO_AF15)
#define GPIO_AF_COMP5_OUT_PB0               (GPIO_AF12)
#define GPIO_AF_COMP5_OUT_PB6               (GPIO_AF0)
#define GPIO_AF_COMP5_OUT_PB11              (GPIO_AF11)
#define GPIO_AF_COMP5_OUT_PC7               (GPIO_AF9)

/* COMP6 */
#define GPIO_AF_COMP6_OUT_PA10              (GPIO_AF9)
#define GPIO_AF_COMP6_OUT_PA12              (GPIO_AF15)
#define GPIO_AF_COMP6_OUT_PB7               (GPIO_AF0)
#define GPIO_AF_COMP6_OUT_PC6               (GPIO_AF9)
#define GPIO_AF_COMP6_OUT_PC9               (GPIO_AF9)

/* COMP7 */
#define GPIO_AF_COMP7_OUT_PA8               (GPIO_AF12)
#define GPIO_AF_COMP7_OUT_PC2               (GPIO_AF10)
#define GPIO_AF_COMP7_OUT_PC8               (GPIO_AF10)
#define GPIO_AF_COMP7_OUT_PD12              (GPIO_AF9)


/** SPI mode definition in AFIO **/
#define AFIO_SPI1_NSS                       (AFIO_RMP_CFG_SPI1_NSS)
#define AFIO_SPI2_NSS                       (AFIO_RMP_CFG_SPI2_NSS)
#define AFIO_SPI3_NSS                       (AFIO_RMP_CFG_SPI3_NSS)
#define AFIO_SPI4_NSS                       (AFIO_RMP_CFG_SPI4_NSS)
#define AFIO_SPI5_NSS                       (AFIO_RMP_CFG_SPI5_NSS)
#define AFIO_SPI6_NSS                       (AFIO_RMP_CFG_SPI6_NSS)
#define AFIO_SPI_NSS_HIGH_IMPEDANCE         ((uint32_t)0x00000000U)
#define AFIO_SPI_NSS_HIGH_LEVEL             (AFIO_RMP_CFG_SPI1_NSS)

/** JTAG-SWD port remap **/
#define GPIO_RMP_SWJ_MARK                   ((uint32_t)0x80000000U)
#define GPIO_RMP_SWJ_JTAG                   (GPIO_RMP_SWJ_MARK)
#define GPIO_RMP_SWJ_JTAG_NO_NJTRST         (AFIO_RMP_CFG_SWJ_CFG_0|GPIO_RMP_SWJ_MARK)
#define GPIO_RMP_SWJ_SWD                    (AFIO_RMP_CFG_SWJ_CFG_1|GPIO_RMP_SWJ_MARK)
#define GPIO_RMP_SWJ_DISABLE                (AFIO_RMP_CFG_SWJ_CFG_2|GPIO_RMP_SWJ_MARK)

/** IO digtal filter definition in AFIO **/
#define AFIO_IO_FILTER_MASK                 (AFIO_RMP_CFG_IO_FILTER)
#define AFIO_IO_FILTER_OFFSET               (REG_BIT17_OFFSET)

/** FEMC NADV pin definition in AFIO  **/
#define AFIO_FEMC_NADV_PIN_USED             ((uint32_t)0x00000000U)
#define AFIO_FEMC_NADV_PIN_NOT_USED         (AFIO_RMP_CFG_FEMC_NADV)

/** EXTI Analog Filter definition in AFIO  **/
#define AFIO_EXTI_FILTER_ENABLE             ((uint32_t)0x00000000U)
#define AFIO_EXTI_FILTER_DISABLE            (AFIO_RMP_CFG_EXTI_FILTER)

/** XSPI XIP big-endian definition during writting **/
#define AFIO_XSPI_XIP_LITTLE_ENDIAN         ((uint32_t)0x00000000U)
#define AFIO_XSPI_XIP_BIG_ENDIAN            (AFIO_RMP_CFG_XSPI_XIP_WR_BE)

/** XSPI half-duplex mode define **/
#define AFIO_XSPI_HALF_DUPLEX_DISABLE       ((uint32_t)0x00000000U)
#define AFIO_XSPI_HALF_DUPLEX_ENABLE        (AFIO_RMP_CFG_XSPI_HALF_DUPLEX)

/** XSPI dual-quad mode define **/
#define AFIO_XSPI_DUAL_QUAD_DISABLE         ((uint32_t)0x00000000U)
#define AFIO_XSPI_DUAL_QUAD_ENABLE          (AFIO_RMP_CFG_XSPI_DUAL_QUAD)

/** ETH mode definition in AFIO **/
#define AFIO_ETH_MODE_MII                   ((uint32_t)0x00000000U)
#define AFIO_ETH_MODE_RMII                  (AFIO_RMP_CFG_ETH_MODE)

/** XSPI flash2 enable in dual-quad mode **/
#define AFIO_XSPI_DUAL_QUAD_FLASH2_DISABLE  ((uint32_t)0x00000000U)
#define AFIO_XSPI_DUAL_QUAD_FLASH2_ENABLE   (AFIO_RMP_CFG_XSPI_FLASH2)

/** XSPI NSS pin input define in master mode **/
#define AFIO_XSPI_NSS_INPUT_DISABLE         ((uint32_t)0x00000000U)
#define AFIO_XSPI_NSS_INPUT_ENABLE          (AFIO_RMP_CFG_XSPI_NSS_IN)

/** XSPI NSS pin input select in master mode **/
#define AFIO_XSPI_NSS_INPUT_NSS0            ((uint32_t)0x00000000U)
#define AFIO_XSPI_NSS_INPUT_NSS1            (AFIO_RMP_CFG_XSPI_NSS_SEL)

/** XSPI RXDS sample delay define  **/
#define AFIO_XSPI_RXDS_DELAY_NONE           ((uint32_t)0x00000000U)
#define AFIO_XSPI_RXDS_DELAY_1HCLK          (AFIO_EMC_CFG_XSPI_RXDS_0)
#define AFIO_XSPI_RXDS_DELAY_2HCLK          (AFIO_EMC_CFG_XSPI_RXDS_1)
#define AFIO_XSPI_RXDS_DELAY_MASK           (AFIO_EMC_CFG_XSPI_RXDS)

/** XSPI big-endian define during writting in non-XIP mode **/
#define AFIO_XSPI_WRITE_LITTLE_ENDIAN       ((uint32_t)0x00000000U)
#define AFIO_XSPI_WRITE_BIG_ENDIAN          (AFIO_EMC_CFG_XSPI_WR_BE)

/** XSPI big-endian define during reading in non-XIP mode **/
#define AFIO_XSPI_READ_LITTLE_ENDIAN        ((uint32_t)0x00000000U)
#define AFIO_XSPI_READ_BIG_ENDIAN           (AFIO_EMC_CFG_XSPI_RD_BE)

/** XSPI setup or hold time extension define **/
#define AFIO_XSPI_NO_TIME_EXTENSION         ((uint32_t)0x00000000U)
#define AFIO_XSPI_SETUP_TIME_EXTENSION      (AFIO_EMC_CFG_XSPI_EXTEND_0)
#define AFIO_XSPI_HOLD_TIME_EXTENSION       (AFIO_EMC_CFG_XSPI_EXTEND_1)
#define AFIO_XSPI_SETUP_HOLD_TIME_EXTENSION (AFIO_EMC_CFG_XSPI_EXTEND)

/** XSPI NSS pin high time when idle **/
#define AFIO_XSPI_NSS_HIGH_1CLK             ((uint32_t)0x00000000U)
#define AFIO_XSPI_NSS_HIGH_2CLK             ((uint32_t)0x00000400U)
#define AFIO_XSPI_NSS_HIGH_3CLK             ((uint32_t)0x00000800U)
#define AFIO_XSPI_NSS_HIGH_4CLK             ((uint32_t)0x00000C00U)
#define AFIO_XSPI_NSS_HIGH_5CLK             ((uint32_t)0x00001000U)
#define AFIO_XSPI_NSS_HIGH_6CLK             ((uint32_t)0x00001400U)
#define AFIO_XSPI_NSS_HIGH_7CLK             ((uint32_t)0x00001800U)
#define AFIO_XSPI_NSS_HIGH_8CLK             ((uint32_t)0x00001C00U)
#define AFIO_XSPI_NSS_HIGH_9CLK             ((uint32_t)0x00002000U)
#define AFIO_XSPI_NSS_HIGH_10CLK            ((uint32_t)0x00002400U)
#define AFIO_XSPI_NSS_HIGH_11CLK            ((uint32_t)0x00002800U)
#define AFIO_XSPI_NSS_HIGH_12CLK            ((uint32_t)0x00002C00U)
#define AFIO_XSPI_NSS_HIGH_13CLK            ((uint32_t)0x00003000U)
#define AFIO_XSPI_NSS_HIGH_14CLK            ((uint32_t)0x00003400U)
#define AFIO_XSPI_NSS_HIGH_15CLK            ((uint32_t)0x00003800U)
#define AFIO_XSPI_NSS_HIGH_16CLK            ((uint32_t)0x00003C00U)

/* SHRTIM EXEV event definition in AFIO */
#define AFIO_SHRTIM_EXEV_1                   ((uint8_t)0x00U)
#define AFIO_SHRTIM_EXEV_2                   ((uint8_t)0x01U)
#define AFIO_SHRTIM_EXEV_3                   ((uint8_t)0x02U)
#define AFIO_SHRTIM_EXEV_4                   ((uint8_t)0x03U)
#define AFIO_SHRTIM_EXEV_5                   ((uint8_t)0x04U)
#define AFIO_SHRTIM_EXEV_6                   ((uint8_t)0x05U)
#define AFIO_SHRTIM_EXEV_7                   ((uint8_t)0x06U)
#define AFIO_SHRTIM_EXEV_8                   ((uint8_t)0x07U)
#define AFIO_SHRTIM_EXEV_9                   ((uint8_t)0x08U)
#define AFIO_SHRTIM_EXEV_10                  ((uint8_t)0x09U)

#define AFIO_SHRTIM_EXEV_BIT_MASK            (AFIO_SHRT_EXEV_CFG1_SHRT1_EXEV1)

/* EMC config */
#define AFIO_EMC_CLAMP1_RST                 (AFIO_EMC_CFG_CLAMP1_RST)
#define AFIO_EMC_CLAMP2_RST                 (AFIO_EMC_CFG_CLAMP2_RST)
#define AFIO_EMC_CLAMP3_RST                 (AFIO_EMC_CFG_CLAMP3_RST)
#define AFIO_EMC_CLAMP4_RST                 (AFIO_EMC_CFG_CLAMP4_RST)
#define AFIO_EMC_GBN1_RST                   (AFIO_EMC_CFG_GBN1_RST  )
#define AFIO_EMC_GBN2_RST                   (AFIO_EMC_CFG_GBN2_RST  )
#define AFIO_EMC_GBN3_RST                   (AFIO_EMC_CFG_GBN3_RST  )
#define AFIO_EMC_GBN4_RST                   (AFIO_EMC_CFG_GBN4_RST  )
#define AFIO_EMC_GB1_RST                    (AFIO_EMC_CFG_GB1_RST   )
#define AFIO_EMC_GB2_RST                    (AFIO_EMC_CFG_GB2_RST   )
#define AFIO_EMC_GB3_RST                    (AFIO_EMC_CFG_GB3_RST   )
#define AFIO_EMC_GB4_RST                    (AFIO_EMC_CFG_GB4_RST   )
#define AFIO_EMC_CLAMP1_DET                 (AFIO_EMC_CFG_CLAMP1_DET)
#define AFIO_EMC_CLAMP2_DET                 (AFIO_EMC_CFG_CLAMP2_DET)
#define AFIO_EMC_CLAMP3_DET                 (AFIO_EMC_CFG_CLAMP3_DET)
#define AFIO_EMC_CLAMP4_DET                 (AFIO_EMC_CFG_CLAMP4_DET)
#define AFIO_EMC_GBN1_DET                   (AFIO_EMC_CFG_GBN1_DET  )
#define AFIO_EMC_GBN2_DET                   (AFIO_EMC_CFG_GBN2_DET  )
#define AFIO_EMC_GBN3_DET                   (AFIO_EMC_CFG_GBN3_DET  )
#define AFIO_EMC_GBN4_DET                   (AFIO_EMC_CFG_GBN4_DET  )
#define AFIO_EMC_GB1_DET                    (AFIO_EMC_CFG_GB1_DET   )
#define AFIO_EMC_GB2_DET                    (AFIO_EMC_CFG_GB2_DET   )
#define AFIO_EMC_GB3_DET                    (AFIO_EMC_CFG_GB3_DET   )
#define AFIO_EMC_GB4_DET                    (AFIO_EMC_CFG_GB4_DET   )

/** GPIO_Exported_Functions **/
void GPIO_DeInit(GPIO_Module* GPIOx);
void GPIO_DeInitPin(GPIO_Module* GPIOx, uint32_t Pin);
void GPIO_AFIOInitDefault(void);

void GPIO_InitPeripheral(GPIO_Module* GPIOx, GPIO_InitType * GPIO_InitStruct);
void GPIO_InitStruct(GPIO_InitType* GPIO_InitStruct);

uint8_t GPIO_ReadInputDataBit(GPIO_Module* GPIOx, uint16_t Pin);
uint16_t GPIO_ReadInputData(GPIO_Module* GPIOx);
uint8_t GPIO_ReadOutputDataBit(GPIO_Module* GPIOx, uint16_t Pin);
uint16_t GPIO_ReadOutputData(GPIO_Module* GPIOx);

void GPIO_SetBits(GPIO_Module* GPIOx, uint16_t Pin);
void GPIO_ResetBits(GPIO_Module* GPIOx, uint16_t Pin);
void GPIO_WriteBits(GPIO_Module* GPIOx, uint16_t Pin, Bit_OperateType BitCmd);
void GPIO_Write(GPIO_Module* GPIOx, uint16_t data_value);
void GPIO_TogglePin(GPIO_Module *GPIOx, uint16_t Pin);
void GPIO_ConfigPinLock(GPIO_Module* GPIOx, uint16_t Pin);

void GPIO_ConfigEXTILine(uint8_t LineSource, uint8_t PortSource, uint8_t PinSource);
void GPIO_ConfigPinRemap(uint8_t PortSource, uint8_t PinSource, uint32_t AlternateFunction);

void AFIO_Config_SPI_NSS_Mode(uint32_t AFIO_SPIx_NSS, uint32_t NSS_Mode);
void AFIO_ConfigIOFilter(uint32_t Filter_Cycle);
void AFIO_Config_FEMC_NADV_Pin(uint32_t NADV_Pin);
void AFIO_Config_EXTI_Filter(uint32_t EXTI_Filter);

void AFIO_Config_XSPI_XIP_BigEndian(uint32_t Endian);
void AFIO_Config_XSPI_HalfDuplexMode(uint32_t HalfDuplex);
void AFIO_Config_XSPI_DualQuadMode(uint32_t DualQuad);
void AFIO_Config_ETH_Mode(uint32_t ETH_Mode);
void AFIO_Config_XSPI_NSS_Input(uint32_t InputEnable, uint32_t InputPin);
void AFIO_Config_XSPI_RXDS_SampleDelay(uint32_t Delay);
void AFIO_Config_XSPI_BigEndian_Read(uint32_t Endian);
void AFIO_Config_XSPI_BigEndian_Write(uint32_t Endian);
void AFIO_Config_XSPI_TimeExtension(uint32_t Extension);
void AFIO_Config_XSPI_NSS_HighTime(uint32_t clk);

void AFIO_ConfigPinTol5V(GPIO_Module* GPIOx, uint32_t Pin,FunctionalState cmd);
void AFIO_ConfigPinFilter(GPIO_Module* GPIOx, uint32_t Pin,FunctionalState cmd);
void AFIO_Config_GPIOC_ReadRegDelay(FunctionalState cmd);
void AFIO_Config_SHRTIM_EXEV_Pin(uint8_t EXEV_Line, uint8_t PortSource, uint8_t PinSource);

void AFIO_Config_EMC_Funtion(uint32_t EMC_fun, FunctionalState cmd);
void AFIO_Set_EMC_Cnt(uint32_t cnt);
uint32_t AFIO_Get_EMC_Cnt(void);

#ifdef __cplusplus
}
#endif

#endif /* __N32H47X_48X_GPIO_H__ */

