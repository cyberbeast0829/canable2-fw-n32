/**
 * @file    n32h47x_48x_conf.h
 * @brief   N32H47x_48x HAL Driver configuration for CANable2
 */

#ifndef __N32H47X_48X_CONF_H
#define __N32H47X_48X_CONF_H

/* CMSIS Core */
#include "n32h47x_48x.h"

/* N32 HAL Drivers - only include what we need */
#include "n32h47x_48x_rcc.h"
#include "n32h47x_48x_gpio.h"
#include "n32h47x_48x_fdcan.h"
#include "n32h47x_48x_flash.h"
#include "n32h47x_48x_pwr.h"
#include "n32h47x_48x_dma.h"
#include "n32h47x_48x_exti.h"
#include "n32h47x_48x_misc.h"

/* USB Driver */
#include "usbfsd_lib.h"

/* Exported macro ------------------------------------------------------------*/
#ifdef  USE_FULL_ASSERT
#define assert_param(expr) ((expr) ? (void)0U : assert_failed((uint8_t *)__FILE__, __LINE__))
void assert_failed(uint8_t* file, uint32_t line);
#else
#define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

#endif /* __N32H47X_48X_CONF_H */
