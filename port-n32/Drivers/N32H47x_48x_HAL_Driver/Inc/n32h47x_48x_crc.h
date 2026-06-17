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
*\*\file n32h47x_48x_crc.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/
#ifndef __N32H47X_CRC_H__
#define __N32H47X_CRC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32h47x_48x.h"

/*** CRC Structure Definition Start ***/

/*** CRC Structure Definition End ***/

/*** CRC Macro Definition Start ***/

/** CRC CRC32 reset definition **/

/** CRC clear the CRC16 check value definition **/

/** CRC little-endian and big-endian definition **/

/*** CRC Macro Definition End ***/

/*** CRC Driving Functions Declaration ***/

void CRC32_ResetCrc(void);
uint32_t CRC32_CalcCrc(uint32_t Data);
uint32_t CRC32_CalcBufCrc(const uint32_t pBuffer[],  uint32_t BufferLength);
uint32_t CRC32_GetCrc(void);
void CRC32_SetIDat(uint8_t IDValue);
uint8_t CRC32_GetIDat(void);
void __CRC16_SetLittleEndianFmt(void);
void __CRC16_SetBigEndianFmt(void);
void __CRC16_SetCleanEnable(void);
void __CRC16_SetCleanDisable(void);
uint16_t __CRC16_CalcCrc(uint8_t Data);
void __CRC16_SetCrc(uint8_t Data);
uint16_t __CRC16_GetCrc(void);
void __CRC16_SetLRC(uint8_t Data);
uint8_t __CRC16_GetLRC(void);
uint16_t CRC16_CalcBufCrc(const uint8_t pBuffer[], uint32_t BufferLength);

#ifdef __cplusplus
}
#endif

#endif /* __n32h47x_48x_CRC_H__ */

