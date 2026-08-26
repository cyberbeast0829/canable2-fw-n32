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
*\*\file n32h47x_48x_crc.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/
#include "n32h47x_48x_crc.h"

/** CRC Private Defines **/


/** CRC Driving Functions Declaration **/

/**
*\*\name    CRC32_ResetCrc.
*\*\fun     Resets the CRC Data register (DAT).
*\*\param   none
*\*\return  none
**/
void CRC32_ResetCrc(void)
{
    /* Reset CRC generator */
    CRC->CRC32CTRL = CRC32_CTRL_RESET;
}

/**
*\*\name    CRC32_CalcCrc.
*\*\fun     Computes the 32-bit CRC of a given data word(32-bit).
*\*\param   Data :
*\*\          - data word(32-bit) to compute its CRC
*\*\return  32-bit CRC
**/
uint32_t CRC32_CalcCrc(uint32_t Data)
{
		/* Write data to the CRC32DAT register */
    CRC->CRC32DAT = Data;
		/* Returns the computed CRC result */
    return (CRC->CRC32D);
}

/**
*\*\name    CRC32_CalcBufCrc.
*\*\fun     Computes the 32-bit CRC of a given buffer of data word(32-bit).
*\*\param   pBuffer :
*\*\          - pointer to the buffer containing the data to be computed
*\*\param   BufferLength :
*\*\          - length of the buffer to be computed
*\*\return  32-bit CRC
**/
uint32_t CRC32_CalcBufCrc(const uint32_t pBuffer[],  uint32_t BufferLength)
{
    uint32_t index;

    for (index = 0; index < BufferLength; index++)
    {
				/* Write data to the CRC32DAT register */
        CRC->CRC32DAT = pBuffer[index];
    }
		/* Returns the computed CRC result */
    return (CRC->CRC32D);
}

/**
*\*\name    CRC32_GetCrc.
*\*\fun     Returns the current CRC value.
*\*\param   none
*\*\return  32-bit CRC
**/
uint32_t CRC32_GetCrc(void)
{
	/* Returns the computed CRC result */
    return (CRC->CRC32D);
}

/**
*\*\name    CRC32_SetIDat.
*\*\fun     Stores a 8-bit data in the Independent Data(ID) register.
*\*\param   IDValue :
*\*\          - 8-bit value to be stored in the ID register
*\*\return  none
**/
void CRC32_SetIDat(uint8_t IDValue)
{
	 /* storage of 8-bit data */
    CRC->CRC32IDAT = IDValue;
}

/**
*\*\name    CRC32_GetIDat.
*\*\fun     Returns the 8-bit data stored in the Independent Data(ID) register.
*\*\param   none
*\*\return  8-bit value of the ID register
**/
uint8_t CRC32_GetIDat(void)
{
		/* Returns the 8-bit data */
    return (CRC->CRC32IDAT);
}

/**
*\*\name    __CRC16_SetLittleEndianFmt.
*\*\fun     Set the calculate data to little endian format.
*\*\param   none
*\*\return  none
**/
void __CRC16_SetLittleEndianFmt(void)
{
    CRC->CRC16CTRL = CRC16_CTRL_LITTLE | CRC->CRC16CTRL;
}

/**
*\*\name    __CRC16_SetBigEndianFmt.
*\*\fun     Set the calculate data to big endian format.
*\*\param   none
*\*\return  none
**/
void __CRC16_SetBigEndianFmt(void)
{
    CRC->CRC16CTRL = CRC16_CTRL_BIG & CRC->CRC16CTRL;
}

/**
*\*\name    __CRC16_SetCleanEnable.
*\*\fun     Enable Clean CRC16 value.
*\*\param   none
*\*\return  none
**/
void __CRC16_SetCleanEnable(void)
{
    CRC->CRC16CTRL = CRC16_CTRL_RESET | CRC->CRC16CTRL;
}

/**
*\*\name    __CRC16_SetCleanDisable.
*\*\fun     Disable Clean CRC16 value.
*\*\param   none
*\*\return  none
**/
void __CRC16_SetCleanDisable(void)
{
    CRC->CRC16CTRL = CRC16_CTRL_NO_RESET & CRC->CRC16CTRL;
}
/**
*\*\name    __CRC16_CalcCrc.
*\*\fun     Computes the 16-bit CRC of a given data word(8-bit).
*\*\param   Data :
*\*\          - data word(8-bit) to compute its CRC
*\*\return  16-bit CRC
**/
uint16_t __CRC16_CalcCrc(uint8_t Data)
{
		/* Write data to the CRC16DAT register */
    CRC->CRC16DAT = Data;
	 /* Returns the computed CRC16 result */
    return (CRC->CRC16D);
}

/**
*\*\name    __CRC16_SetCrc.
*\*\fun     write a 8-bit data in the 16-bit CRC Data register.
*\*\param   Data :
*\*\          - 8-bit data value to be writed in the 16-bit CRC Data register
*\*\return  none
**/
void __CRC16_SetCrc(uint8_t Data)
{
		/* Writes 8-bit data to the CRC16DAT register */
    CRC->CRC16DAT = Data;
}
/**
*\*\name    __CRC16_GetCrc.
*\*\fun     Returns the current CRC value.
*\*\param   none
*\*\return  16-bit CRC
**/
uint16_t __CRC16_GetCrc(void)
{
		/* Returns the CRC16 calculation result */
    return (CRC->CRC16D);
}

/**
*\*\name    __CRC16_SetLRC.
*\*\fun     Write LRC initial value.
*\*\param   Data :
*\*\          - 8-bit data
*\*\return  none
**/
void __CRC16_SetLRC(uint8_t Data)
{
		/* Write LRC to verify the initial value */
    CRC->LRC = Data;
}

/**
*\*\name    __CRC16_GetLRC.
*\*\fun     Returns the current LRC value.
*\*\param   none
*\*\return  8-bit LRC
**/
uint8_t __CRC16_GetLRC(void)
{
		/* Returns the LRC check value */
    return (CRC->LRC);
}

/**
*\*\name    CRC16_CalcBufCrc.
*\*\fun     Computes the 16-bit CRC of a given buffer of data word(8-bit).
*\*\param   pBuffer :
*\*\          - pointer to the buffer containing the data to be computed
*\*\param   BufferLength :
*\*\          - length of the buffer to be computed
*\*\return  16-bit CRC
**/
uint16_t CRC16_CalcBufCrc(const uint8_t pBuffer[], uint32_t BufferLength)
{
    uint32_t index;

    CRC->CRC16D = 0x00;
    for (index = 0; index < BufferLength; index++)
    {
			/* Write data to the CRC16DAT register */
        CRC->CRC16DAT = pBuffer[index];
    }
		/* Returns the computed CRC16 result */
    return (CRC->CRC16D);
}


