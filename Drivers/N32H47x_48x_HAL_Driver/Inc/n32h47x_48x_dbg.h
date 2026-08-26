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
*\*\file n32h47x_48x_dbg.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/
#ifndef __N32H47X_DBG_H__
#define __N32H47X_DBG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32h47x_48x.h"

#define DBG_SLEEP             (DBG_CTRL_SLEEP)
#define DBG_STOP              (DBG_CTRL_STOP)
#define DBG_STANDBY           (DBG_CTRL_STDBY)
#define DBG_IWDG_STOP         (DBG_CTRL_IWDG_STOP)
#define DBG_WWDG_STOP         (DBG_CTRL_WWDG_STOP)
#define DBG_I2C1SMBUS_TIMEOUT (DBG_CTRL_I2C1SMBUS_TO)
#define DBG_I2C2SMBUS_TIMEOUT (DBG_CTRL_I2C2SMBUS_TO)
#define DBG_I2C3SMBUS_TIMEOUT (DBG_CTRL_I2C3SMBUS_TO)
#define DBG_I2C4SMBUS_TIMEOUT (DBG_CTRL_I2C4SMBUS_TO)
#define DBG_ATIM1_STOP        (DBG_CTRL_ATIM1_STOP)
#define DBG_ATIM2_STOP        (DBG_CTRL_ATIM2_STOP)
#define DBG_ATIM3_STOP        (DBG_CTRL_ATIM3_STOP)
#define DBG_BTIM1_STOP        (DBG_CTRL_BTIM1_STOP)
#define DBG_BTIM2_STOP        (DBG_CTRL_BTIM2_STOP)
#define DBG_GTIM1_STOP        (DBG_CTRL_GTIM1_STOP)
#define DBG_GTIM2_STOP        (DBG_CTRL_GTIM2_STOP)
#define DBG_GTIM3_STOP        (DBG_CTRL_GTIM3_STOP)
#define DBG_GTIM4_STOP        (DBG_CTRL_GTIM4_STOP)
#define DBG_GTIM5_STOP        (DBG_CTRL_GTIM5_STOP)
#define DBG_GTIM6_STOP        (DBG_CTRL_GTIM6_STOP)
#define DBG_GTIM7_STOP        (DBG_CTRL_GTIM7_STOP)
#define DBG_GTIM8_STOP        (DBG_CTRL_GTIM8_STOP)
#define DBG_GTIM9_STOP        (DBG_CTRL_GTIM9_STOP)
#define DBG_GTIM10_STOP       (DBG_CTRL_GTIM10_STOP)
#define DBG_SHRTIM1_STOP      (DBG_CTRL_SHRTIM1_STOP)


void GetUCID(uint8_t *UCIDbuf);
void GetUID(uint8_t *UIDbuf);
void GetDBGMCU_ID(uint8_t *DBGMCU_IDbuf);
uint32_t DBG_GetRevNum(void);
uint32_t DBG_GetDevNum(void);
void DBG_ConfigPeriph(uint32_t DBG_Periph, FunctionalState Cmd);

uint32_t DBG_GetFlashSize(void);
uint32_t DBG_GetSramSize(void);

#ifdef __cplusplus
}
#endif

#endif /* __N32H47X_DBG_H__ */

