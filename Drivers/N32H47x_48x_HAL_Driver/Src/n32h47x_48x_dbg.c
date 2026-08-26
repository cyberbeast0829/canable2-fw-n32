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
*\*\file n32h47x_48x_dbg.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/
#include "n32h47x_48x_dbg.h"

#define IDCODE_DEVID_MASK ((uint32_t)0x00000FFF)

/**
*\*\name    GetUCID.
*\*\fun     get unique customer id.
*\*\param   UCIDbuf
*\*\return  none
**/
void GetUCID(uint8_t *UCIDbuf)
{
    uint8_t num;
    __IO uint32_t *ucid_addr;
    __IO uint32_t temp;
        
    if (0xFFFFFFFFU == *(__IO uint32_t *)(0x1FFFF260U))
    {
        ucid_addr = (__IO uint32_t *)UCID_BASE;
    }
    else
    {
        ucid_addr = (__IO uint32_t *)(0x1FFFF260U);
    }
    
    for (num = 0; num < UCID_LENGTH; num++)
    {
        temp = *(__IO uint32_t *)ucid_addr;
        ucid_addr++;
        UCIDbuf[num] = (uint8_t)temp;
        num++;
        UCIDbuf[num] = (uint8_t)(temp >> 8);
        num++;
        UCIDbuf[num] = (uint8_t)(temp >> 16);
        num++;
        UCIDbuf[num] = (uint8_t)(temp >> 24);
    }
}

/**
*\*\name    GetUID.
*\*\fun     get unique device id.
*\*\param   UIDbuf
*\*\return  none
**/
void GetUID(uint8_t *UIDbuf)
{
    uint8_t num;
    __IO uint32_t* uid_addr;
    __IO uint32_t temp;

    if (0xFFFFFFFFU == *(uint32_t*)(0x1FFFF270))
    {
        uid_addr = (uint32_t*)UID_BASE;
    }
    else
    {
        uid_addr = (uint32_t*)(0x1FFFF270);
    }
        
    for (num = 0; num < UID_LENGTH; num++)
    {
        temp = *(__IO uint32_t *)uid_addr;
        uid_addr++;
        UIDbuf[num] = (uint8_t)temp;
        num++;
        UIDbuf[num] = (uint8_t)(temp >> 8);
        num++;
        UIDbuf[num] = (uint8_t)(temp >> 16);
        num++;
        UIDbuf[num] = (uint8_t)(temp >> 24);
    }
}

/**
 * @brief  Returns the DBGMCU_ID.
 * @return DBGMCU_ID
 */

void GetDBGMCU_ID(uint8_t *DBGMCU_IDbuf)
{
    uint8_t num;
    __IO uint32_t* dbgid_addr;
    __IO uint32_t temp;
    
    dbgid_addr = (uint32_t*)DBGMCU_ID_BASE;
    for (num = 0; num < DBGMCU_ID_LENGTH; num++)
    {
        temp = *(__IO uint32_t *)(dbgid_addr);
        dbgid_addr++;
        DBGMCU_IDbuf[num] = (uint8_t)temp;
        num++;
        DBGMCU_IDbuf[num] = (uint8_t)(temp >> 8);
        num++;
        DBGMCU_IDbuf[num] = (uint8_t)(temp >> 16);
        num++;
        DBGMCU_IDbuf[num] = (uint8_t)(temp >> 24);
    }
}

/**
*\*\name    DBG_GetRevNum.
*\*\fun     get the revision number.
*\*\param   none
*\*\return  revision number
**/
uint32_t DBG_GetRevNum(void)
{
    return (DBG->ID & 0x000000FFU);
}

/**
*\*\name    DBG_GetDevNum.
*\*\fun     get the device identifer.
*\*\param   none
*\*\return  Device identifier
**/
uint32_t DBG_GetDevNum(void)
{
    uint32_t id = DBG->ID;
    return ((id & 0x00F00000U) >> 20) | ((id & 0x0000FF00U) >> 4);
}

/**
*\*\name    DBG_ConfigPeriph.
*\*\fun     Configures the specified peripheral run or stop when the MCU under Debug mode.
*\*\param   DBG_Periph :
                - DBG_SLEEP             \* Keep debugger connection during SLEEP mode *\
                - DBG_STOP              \* Keep debugger connection during STOP mode *\
                - DBG_STANDBY           \* Keep debugger connection during STANDBY mode *\
                - DBG_IWDG_STOP         \* IWDG stopped when Core is halted. *\
                - DBG_WWDG_STOP         \* WWDG stopped when Core is halted. *\
                - DBG_I2C1SMBUS_TIMEOUT \* I2C1 SMBUS timeout mode stopped when Core is halted *\
                - DBG_I2C2SMBUS_TIMEOUT \* I2C2 SMBUS timeout mode stopped when Core is halted *\
                - DBG_I2C3SMBUS_TIMEOUT \* I2C3 SMBUS timeout mode stopped when Core is halted *\
                - DBG_I2C4SMBUS_TIMEOUT \* I2C4 SMBUS timeout mode stopped when Core is halted *\
                - DBG_ATIM1_STOP        \* ATIM1 counter stopped when core is halted *\
                - DBG_ATIM2_STOP        \* ATIM2 counter stopped when core is halted *\
                - DBG_ATIM3_STOP        \* ATIM3 counter stopped when core is halted *\
                - DBG_BTIM1_STOP        \* BTIM1 counter stopped when core is halted *\
                - DBG_BTIM2_STOP        \* BTIM2 counter stopped when core is halted *\
                - DBG_GTIM1_STOP        \* GTIM1 counter stopped when core is halted *\
                - DBG_GTIM2_STOP        \* GTIM2 counter stopped when core is halted *\
                - DBG_GTIM3_STOP        \* GTIM3 counter stopped when core is halted *\
                - DBG_GTIM4_STOP        \* GTIM4 counter stopped when core is halted *\
                - DBG_GTIM5_STOP        \* GTIM5 counter stopped when core is halted *\
                - DBG_GTIM6_STOP        \* GTIM6 counter stopped when core is halted *\
                - DBG_GTIM7_STOP        \* GTIM7 counter stopped when core is halted *\
                - DBG_GTIM8_STOP        \* GTIM8 counter stopped when core is halted *\
                - DBG_GTIM9_STOP        \* GTIM9 counter stopped when core is halted *\
                - DBG_GTIM10_STOP       \* GTIM10 counter stopped when core is halted *\
                - DBG_SHRTIM1_STOP      \* SHRTIM1 counter stopped when core is halted *\  
*\*\param   Cmd: 
*\*\          - ENABLE  
*\*\          - DISABLE      
*\*\return  none
**/
void DBG_ConfigPeriph(uint32_t DBG_Periph, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        DBG->CTRL |= DBG_Periph;
    }
    else
    {
        DBG->CTRL &= ~DBG_Periph;
    }
}

/**
*\*\name    DBG_GetFlashSize.
*\*\fun     Get FLASH size of this chip.
*\*\param   none
*\*\return  FLASH size in bytes.
**/
uint32_t DBG_GetFlashSize(void)
{
    return (uint32_t)((DBG->ID & 0x000F0000U)>>6);
}

/**
*\*\name    DBG_GetSramSize.
*\*\fun     Get SRAM size of this chip.
*\*\param   none
*\*\return  SRAM size in bytes.
**/
uint32_t DBG_GetSramSize(void)
{
    return (uint32_t)(((DBG->ID & 0xF0000000U) >> 28)) << 10;
}
