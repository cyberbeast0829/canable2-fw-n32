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
*\*\file n32h47x_48x_flash.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/
#include "n32h47x_48x_flash.h"

/**
*\*\name    FLASH_SetLatency
*\*\fun     Sets the code latency value.
*\*\param   FLASH_Latency :(The input parameters must be the following values)
*\*\            - FLASH_LATENCY_0    FLASH Zero Latency cycle, 0 < HCLK <= 40MHz      
*\*\            - FLASH_LATENCY_1    FLASH One Latency cycle, 40MHz < HCLK<= 80MHz
*\*\            - FLASH_LATENCY_2    FLASH Two Latency cycle, 80MHz < HCLK<= 120MHz
*\*\            - FLASH_LATENCY_3    FLASH Three Latency cycle,120MHz < HCLK<= 160MHz      
*\*\            - FLASH_LATENCY_4    FLASH Four Latency cycle, 160MHz < HCLK<= 200MHz
*\*\            - FLASH_LATENCY_5    FLASH Five Latency cycle, 200MHz < HCLK<= 240MHz
*\*\return  none
*\*\note    The larger the latency, the longer the flash read operation will take. 
*\*\        If not necessary, it is recommended to use a smaller latency.
**/
void FLASH_SetLatency(uint32_t FLASH_Latency)
{
    uint32_t tmpregister;

    /* Read the ACR register */
    tmpregister = FLASH->AC;

    /* Sets the Latency value */
    tmpregister &= (~FLASH_LATENCY_MASK);
    tmpregister |= FLASH_Latency;

    /* Write the ACR register */
    FLASH->AC = tmpregister;
}


/**
*\*\name    FLASH_GetLatency
*\*\fun     Get the code latency value.
*\*\param   none
*\*\return  FLASH_LATENCY :(The input parameters must be the following values)
*\*\            - FLASH_LATENCY_0    FLASH Zero Latency cycle, 0 < HCLK <= 40MHz      
*\*\            - FLASH_LATENCY_1    FLASH One Latency cycle, 40MHz < HCLK<= 80MHz
*\*\            - FLASH_LATENCY_2    FLASH Two Latency cycle, 80MHz < HCLK<= 120MHz
*\*\            - FLASH_LATENCY_3    FLASH Three Latency cycle,120MHz < HCLK<= 160MHz      
*\*\            - FLASH_LATENCY_4    FLASH Four Latency cycle, 160MHz < HCLK<= 200MHz
*\*\            - FLASH_LATENCY_5    FLASH Five Latency cycle, 200MHz < HCLK<= 240MHz
**/
uint8_t FLASH_GetLatency(void)
{
    /* Read the AC register */
    return (uint8_t)(FLASH->AC & FLASH_LATENCY_MASK);
}

/**
*\*\name    FLASH_PrefetchBufSet
*\*\fun     Enables or disables the Prefetch Buffer.
*\*\param   FLASH_PrefetchBuf:(The input parameters must be the following values)
*\*\            - FLASH_PrefetchBuf_EN      
*\*\            - FLASH_PrefetchBuf_DIS
*\*\return  none
**/
void FLASH_PrefetchBufSet(uint32_t FLASH_PrefetchBuf)
{
    /* Enable or disable the Prefetch Buffer */
    FLASH->AC &= FLASH_PrefetchBuf_MSK;
    FLASH->AC |= FLASH_PrefetchBuf;
}


/**
*\*\name    FLASH_iCacheRST
*\*\fun     ICache Reset.
*\*\param   none
*\*\return  none
**/
void FLASH_iCacheRST(void)
{
    /* ICache Reset */
    FLASH->AC |= FLASH_AC_ICAHRST;
}

/**
*\*\name    FLASH_iCacheCmd
*\*\fun     Enables or disables the iCache.
*\*\param   FLASH_PrefetchBuf:(The input parameters must be the following values)
*\*\            - FLASH_iCache_EN FLASH iCache Enable      
*\*\            - FLASH_iCache_DIS FLASH iCache Disable
*\*\return  none
**/
void FLASH_iCacheCmd(uint32_t FLASH_iCache)
{
    /* Enable or disable the iCache */
    FLASH->AC &= AC_ICAHEN_MSK;
    FLASH->AC |= FLASH_iCache;
}


/**
*\*\name   FLASH_Unlock
*\*\fun    Unlocks the FLASH Program Erase Controller.
*\*\param  none
*\*\return none
**/
void FLASH_Unlock(void)
{
    FLASH->KEY = FLASH_KEY1;
    FLASH->KEY = FLASH_KEY2;
}

/**
*\*\name   FLASH_Lock
*\*\fun    Locks the FLASH Program Erase Controller.
*\*\param  none
*\*\return none
**/
void FLASH_Lock(void)
{
    FLASH->CTRL |= CTRL_Set_LOCK;
}

/**
*\*\name   Flash_GetLockStatus
*\*\fun    Get the Flash lock status.
*\*\param  none
*\*\return FlagStatus :
*\*\            - SET     FLASH is in Lock state
*\*\            - RESET   FLASH is in Unlock state
**/
FlagStatus Flash_GetLockStatus(void)
{
    FlagStatus bit_status;
    if ((FLASH->CTRL & CTRL_Set_LOCK) != (uint32_t)RESET)
    {
        bit_status = SET;
    }
    else
    {
        bit_status =  RESET;
    }
    return bit_status;
}

/**
*\*\name   Option_Bytes_Unlock
*\*\fun    Unlocks the Option_Bytes Program Erase Controller.
*\*\param  none
*\*\return none
**/
void Option_Bytes_Unlock(void)
{
    FLASH->OPTKEY = FLASH_KEY1;
    FLASH->OPTKEY = FLASH_KEY2;
}


/**
*\*\name   Option_Bytes_Lock
*\*\fun    Locks the Option_Bytes Program Erase Controller.
*\*\param  none
*\*\return none
**/
void Option_Bytes_Lock(void)
{
    /* Set the FLASH_CTRL_SET_OPTWE Bit to lock */
    FLASH->CTRL &= (~FLASH_CTRL_SET_OPTWE);
}

/**
*\*\name   OB_GetLockStatus
*\*\fun    Get the Option Bytes lock status.
*\*\param  none
*\*\return FlagStatus :
*\*\            - SET     Option byte is in Lock state
*\*\            - RESET   Option byte is in Unlock state
**/
FlagStatus OB_GetLockStatus(void)
{
    FlagStatus bit_status;
    if ((FLASH->CTRL & FLASH_CTRL_SET_OPTWE) != (uint32_t)RESET)
    {
        bit_status = SET;
    }
    else
    {
        bit_status =  RESET;
    }
    return bit_status;
}


/**
*\*\name   FLASH_EraseOnePage
*\*\fun    Erases a specified main FLASH page.
*\*\param  Page_Address :(The input parameters must be the following values)
*\*\            - it ranges from 0x08000000 to 0x0807FFFF, it must be a multiple of 0x2000
*\*\return FLASH_STS : 
*\*\            - FLASH_BUSY     FLASH is busy
*\*\            - FLASH_ERR_PG   FLASH programming error
*\*\            - FLASH_ERR_WRP  FLASH Write protected error
*\*\            - FLASH_EOP      FLASH End of Operation
*\*\            - FLASH_TIMEOUT  FLASH operation timeout
*\*\            - FLASH_ERR_PV   Programmer Verification Error
*\*\            - FLASH_ERR_EV   Erase Verification Error
*\*\            - FLASH_ERR_RPADD   FLASH Row programmer address error
**/
FLASH_STS FLASH_EraseOnePage(uint32_t Page_Address)
{
    FLASH_STS status_value;

    /* Clears the FLASH's pending flags */
    FLASH_ClearFlag(FLASH_STS_CLRFLAG);
    /* Wait for last operation to be completed */
    status_value = FLASH_WaitForLastOpt(EraseTimeout);

    if (status_value == FLASH_EOP)
    {
        /* if the previous operation is completed, proceed to erase the page */
        FLASH->CTRL |= CTRL_Set_PER;
        FLASH->ADD = Page_Address;
        FLASH->CTRL |= CTRL_Set_START;

        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(EraseTimeout);

        /* Disable the PER Bit */
        FLASH->CTRL &= CTRL_Reset_PER;
    }

    /* Return the Erase Status */
    return status_value;
}


/**
*\*\name   FLASH_MassErase
*\*\fun    Erases all main FLASH pages.
*\*\param  none
*\*\return FLASH_STS : 
*\*\            - FLASH_BUSY     FLASH is busy
*\*\            - FLASH_ERR_PG   FLASH programming error
*\*\            - FLASH_ERR_WRP  FLASH Write protected error
*\*\            - FLASH_EOP      FLASH End of Operation
*\*\            - FLASH_TIMEOUT  FLASH operation timeout
*\*\            - FLASH_ERR_PV   Programmer Verification Error
*\*\            - FLASH_ERR_EV   Erase Verification Error
*\*\            - FLASH_ERR_RPADD   FLASH Row programmer address error
**/
FLASH_STS FLASH_MassErase(void)
{
    FLASH_STS status_value;

    /* Clears the FLASH's pending flags */
    FLASH_ClearFlag(FLASH_STS_CLRFLAG);
    /* Wait for last operation to be completed */
    status_value = FLASH_WaitForLastOpt(EraseTimeout);

    if (status_value == FLASH_EOP)
    {
        /* if the previous operation is completed, proceed to erase all pages */
        FLASH->CTRL |= CTRL_Set_MER;
        FLASH->CTRL |= CTRL_Set_START;

        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(EraseTimeout);

        /* Disable the MER Bit */
        FLASH->CTRL &= CTRL_Reset_MER;
    }

    /* Return the Erase Status */
    return status_value;
}


/**
*\*\name   FLASH_ProgramdoubleWord
*\*\fun    Programs two words at a specified address.
*\*\param  address :(The input parameters must be the following values)
*\*\            - main flash, it ranges from 0x08000000 to 0x0807FFFF, it must be a multiple of 0x08
*\*\param  data0 :(The input parameters must be the following values)
*\*\            - It ranges from 0x00000000 to 0xFFFFFFFF
*\*\param  data1 :(The input parameters must be the following values)
*\*\            - It ranges from 0x00000000 to 0xFFFFFFFF
*\*\return FLASH_STS : 
*\*\            - FLASH_BUSY     FLASH is busy
*\*\            - FLASH_ERR_PG   FLASH programming error
*\*\            - FLASH_ERR_WRP  FLASH Write protected error
*\*\            - FLASH_EOP      FLASH End of Operation
*\*\            - FLASH_ERR_PV   Programmer Verification Error
*\*\            - FLASH_ERR_EV   Erase Verification Error
*\*\            - FLASH_ERR_ADD  FLASH address error
*\*\            - FLASH_ERR_RPADD   FLASH Row programmer address error
*\*\            - FLASH_TIMEOUT  FLASH operation timeout
**/
FLASH_STS FLASH_ProgramdoubleWord(uint32_t address, uint32_t data0,uint32_t data1)
{
    FLASH_STS status_value = FLASH_EOP;

    if((address & FLASH_WORD_LENGTH) != (uint32_t)0x00)
    {
        /* The programming address is not a multiple of 8 */
        status_value = FLASH_ERR_ADD;
    }
    else
    {
        /*No process*/
    }

    if(status_value == FLASH_ERR_ADD)
    {
    
    }
    else
    {
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
    }

    if (status_value == FLASH_EOP)
    {
        /* if the previous operation is completed, proceed to program the new word */
        FLASH->CTRL |= CTRL_Set_PG;

        *(__IO uint32_t*)address = (uint32_t)data0;
        *(__IO uint32_t*)(address + (uint32_t)0x4) = (uint32_t)data1;
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);

        /* Disable the PG Bit */
        FLASH->CTRL &= CTRL_Reset_PG;
    }
    else
    {
        /*No process*/
    }

    /* Return the Program status_value */
    return status_value;
}


/**
*\*\name   FLASH_RowProgramSet
*\*\fun    Enables or disables row programmer.
*\*\param  Cmd :(The input parameters must be the following values)
*\*\            - ENABLE  Enable Row programmer
*\*\            - DISABLE Disable Row programmer
*\*\return none
**/
void FLASH_RowProgramSet(FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        FLASH->ROWP |= FLASH_ROW_ENABLE;
    }
    else
    {
        FLASH->ROWP &= FLASH_ROW_DISABLE;
    }
}

/**
*\*\name   FLASH_RowProgramAreaSet
*\*\fun    Configure row programmer area.
*\*\param  Cmd :(The input parameters must be the following values)
*\*\            - ENABLE  Row programmer in system memory
*\*\            - DISABLE Row programmer in main flash
*\*\return none
**/
void FLASH_RowProgramAreaSet(FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        FLASH->ROWP |= FLASH_ROW_SYSTEMMEMORY;
    }
    else
    {
        FLASH->ROWP &= FLASH_ROW_MAINFLASH;
    }
}


/**
*\*\name   FLASH_RowProgram
*\*\fun    Programs x words at a specified address.
*\*\param  address :(The input parameters must be the following values)
*\*\            - main flash, it ranges from 0x08000000 to 0x0807FFFF, it must be a multiple of 0x08
*\*\param  row_num :(The input parameters must be the following values)
*\*\            - It ranges from 0x02 to 0x10,it must be a multiple of 0x02
*\*\param  data[] :(The input parameters must be the following values)
*\*\            - It ranges from 0x00000000 to 0xFFFFFFFF
*\*\return FLASH_STS : 
*\*\            - FLASH_BUSY        FLASH is busy
*\*\            - FLASH_ERR_PG      FLASH programming error
*\*\            - FLASH_ERR_WRP     FLASH Write protected error
*\*\            - FLASH_EOP         FLASH End of Operation
*\*\            - FLASH_ERR_PV      Programmer Verification Error
*\*\            - FLASH_ERR_EV      Erase Verification Error
*\*\            - FLASH_ERR_ADD     FLASH address error
*\*\            - FLASH_ERR_RPADD   FLASH Row programmer address error
*\*\            - FLASH_TIMEOUT     FLASH operation timeout
*\*\            - FLASH_ERR_RPADD   FLASH Row programmer address error
**/
FLASH_STS FLASH_RowProgram(uint32_t address, uint32_t row_num, uint32_t *data)
{
    FLASH_STS status_value = FLASH_EOP;
    uint32_t address_value;
    uint32_t nownum,row_num_temp = 0;

    if((address & FLASH_WORD_LENGTH) != (uint32_t)0x00)
    {
        /* The programming address is not a multiple of 8 */
        status_value = FLASH_ERR_ADD;
    }
    else
    {
        /*No process*/
    }

    if(status_value == FLASH_ERR_ADD)
    {
    
    }
    else
    {
        row_num_temp = (((row_num - 1) & 0x0EU));
        
        address_value = ((address << REG_BIT3_OFFSET) & FLASH_ROW_MASK);
        
        FLASH->ROWP &= FLASH_ROW_RPNUM_MASK;
        FLASH->ROWP &= (~FLASH_ROW_MASK);
    
        FLASH->ROWP |= (address_value | (row_num_temp << REG_BIT1_OFFSET));

        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
    }
    

    if (status_value == FLASH_EOP)
    {
        /* if the previous operation is completed, proceed to program the new word */
        FLASH->CTRL |= CTRL_Set_PG;

        for(nownum=0;nownum<(row_num_temp+2);nownum++)
        {
            *(__IO uint32_t*)(address + (4*nownum)) = data[nownum];
        }
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(RowProgramTimeout);

        /* Disable the PG Bit */
        FLASH->CTRL &= CTRL_Reset_PG;
    }
    else
    {
        /*No process*/
    }

    /* Return the Program status_value */
    return status_value;
}


/**
*\*\name   FLASH_EraseOB
*\*\fun    Erases the FLASH option bytes.
*\*\param  none
*\*\return FLASH_STS : 
*\*\            - FLASH_BUSY     FLASH is busy
*\*\            - FLASH_ERR_PG   FLASH programming error
*\*\            - FLASH_ERR_WRP  FLASH Write protected error
*\*\            - FLASH_EOP      FLASH End of Operation
*\*\            - FLASH_ERR_PV   Programmer Verification Error
*\*\            - FLASH_ERR_EV   Erase Verification Error
*\*\            - FLASH_ERR_RDP2 FLASH is in read protection L2 status
*\*\            - FLASH_TIMEOUT  FLASH operation timeout
*\*\            - FLASH_ERR_RPADD   FLASH Row programmer address error
**/
FLASH_STS FLASH_EraseOB(void)
{
    FLASH_STS status_value = FLASH_EOP;

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status_value = FLASH_ERR_RDP2;
    }
    else
    {
        /*No process*/
    }

    if(status_value == FLASH_ERR_RDP2)
    {

    }
    else
    {
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(EraseTimeout);
    }

    if (status_value == FLASH_EOP)
    {
        Option_Bytes_Unlock();

        /* if the previous operation is completed, proceed to erase the option bytes */
        FLASH->CTRL |= CTRL_Set_OPTER;
        FLASH->CTRL |= CTRL_Set_START;
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(EraseTimeout);

        if (status_value == FLASH_EOP)
        {
            /* Clears the FLASH's pending flags */
            FLASH_ClearFlag(FLASH_STS_CLRFLAG);

            /* if the erase operation is completed, disable the OPTER Bit */
            FLASH->CTRL &= CTRL_Reset_OPTER;
        }
        else
        {
            if (status_value != FLASH_TIMEOUT)
            {
                /* Disable the OPTER Bit */
                FLASH->CTRL &= CTRL_Reset_OPTER;
            }
            else
            {
                /*No process*/
            }
        }
    }
    else
    {
        /*No process*/
    }
    /* Return the erase status_value */
    return status_value;
}


/**
*\*\name   FLASH_ProgramOB_RUDD
*\*\fun    Programs the Option Byte: RDP1/USER/DATA0/DATA1.
*\*\param  option_byte_rpd1 :(The input parameters must be the following values)
*\*\            - FLASH_OB_RDP1_ENABLE   Enable read protection L1
*\*\            - FLASH_OB_RDP1_DISABLE  Disable read protection L1
*\*\param  option_byte_iwdg :(The input parameters must be the following values)
*\*\            - FLASH_OB_IWDG_SOFTWARE Software IWDG selected
*\*\            - FLASH_OB_IWDG_HARDWARE Hardware IWDG selected
*\*\param  option_byte_stop :(The input parameters must be the following values)
*\*\            - FLASH_OB_STOP_NORST No reset generated when entering in STOP
*\*\            - FLASH_OB_STOP_RST Reset generated when entering in STOP
*\*\param  option_byte_stdby :(The input parameters must be the following values)
*\*\            - FLASH_OB_STDBY_NORST No reset generated when entering in standby
*\*\            - FLASH_OB_STDBY_RST Reset generated when entering in standby
*\*\param  option_byte_iwdg_stop :(The input parameters must be the following values)
*\*\            - FLASH_OB_IWDG_STOP_FRZ IWDG freeze in stop
*\*\            - FLASH_OB_IWDG_STOP_NOFRZ Default no freeze
*\*\param  option_byte_iwdg_stdby :(The input parameters must be the following values)
*\*\            - FLASH_OB_IWDG_STDBY_FRZ IWDG freeze in standby
*\*\            - FLASH_OB_IWDG_STDBY_NOFRZ Default no freeze
*\*\param  option_byte_iwdg_sleep :(The input parameters must be the following values)
*\*\            - FLASH_OB_IWDG_SLEEP_FRZ IWDG freeze in sleep
*\*\            - FLASH_OB_IWDG_SLEEP_NOFRZ Default no freeze
*\*\param  option_byte_data0:(The input parameters must be the following values)
*\*\            - 0x00 to 0xFF
*\*\param  option_byte_data1:(The input parameters must be the following values)
*\*\            - 0x00 to 0xFF
*\*\return FLASH_STS : 
*\*\            - FLASH_BUSY     FLASH is busy
*\*\            - FLASH_ERR_PG   FLASH programming error
*\*\            - FLASH_ERR_WRP  FLASH Write protected error
*\*\            - FLASH_EOP      FLASH End of Operation
*\*\            - FLASH_ERR_PV   Programmer Verification Error
*\*\            - FLASH_ERR_EV   Erase Verification Error
*\*\            - FLASH_ERR_RDP2 FLASH is in read protection L2 status
*\*\            - FLASH_TIMEOUT  FLASH operation timeout
*\*\            - FLASH_ERR_RPADD   FLASH Row programmer address error
**/
FLASH_STS FLASH_ProgramOB_RUDD(uint32_t option_byte_rpd1, uint32_t option_byte_iwdg, uint32_t option_byte_stop,\
                               uint32_t option_byte_stdby, uint32_t option_byte_iwdg_stop, uint32_t option_byte_iwdg_stdby,\
                               uint32_t option_byte_iwdg_sleep, uint32_t option_byte_data0, uint32_t option_byte_data1)
{
    FLASH_STS status_value = FLASH_EOP;
    uint32_t  rpd1_user_value;
    uint32_t  data0_data1_value;
    
    rpd1_user_value = option_byte_rpd1 | ((option_byte_iwdg | option_byte_stop | option_byte_stdby |\
                      option_byte_iwdg_stop | option_byte_iwdg_stdby | option_byte_iwdg_sleep) << 16);
    data0_data1_value = option_byte_data0 | (option_byte_data1 << 16);
    
    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status_value = FLASH_ERR_RDP2;
    }
    else
    {
        /*No process*/
    }

    if(status_value == FLASH_ERR_RDP2)
    {
        
    }
    else
    {
        Option_Bytes_Unlock();

        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
    }

    if (status_value == FLASH_EOP)
    {
        /* Enables the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        OBT->USER_RDP = rpd1_user_value;
        OBT->Data1_Data0 = data0_data1_value;

        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
    }
    Option_Bytes_Lock();
    /* Return the Option Byte Data Program Status */
    return status_value;
}


/**
*\*\name   FLASH_EnWriteProtection
*\*\fun    Write protects the desired pages.
*\*\param  FLASH_Pages :(The input parameters must be the following values)
*\*\            - FLASH_WRP_Pages0to1     Write protection of page 0 to 1 
*\*\            - FLASH_WRP_Pages2to3     Write protection of page 2 to 3
*\*\            - FLASH_WRP_Pages4to5     Write protection of page 4 to 5
*\*\            - FLASH_WRP_Pages6to7     Write protection of page 6 to 7
*\*\            - FLASH_WRP_Pages8to9     Write protection of page 8 to 9
*\*\            - FLASH_WRP_Pages10to11   Write protection of page 10 to 11
*\*\            - FLASH_WRP_Pages12to13   Write protection of page 12 to 13
*\*\            - FLASH_WRP_Pages14to15   Write protection of page 14 to 15
*\*\            - FLASH_WRP_Pages16to17   Write protection of page 16 to 17
*\*\            - FLASH_WRP_Pages18to19   Write protection of page 18 to 19
*\*\            - FLASH_WRP_Pages20to21   Write protection of page 20 to 21
*\*\            - FLASH_WRP_Pages22to23   Write protection of page 22 to 23
*\*\            - FLASH_WRP_Pages24to25   Write protection of page 24 to 25
*\*\            - FLASH_WRP_Pages26to27   Write protection of page 26 to 27
*\*\            - FLASH_WRP_Pages28to29   Write protection of page 28 to 29
*\*\            - FLASH_WRP_Pages30to31   Write protection of page 30 to 31
*\*\            - FLASH_WRP_Pages32to33   Write protection of page 32 to 33
*\*\            - FLASH_WRP_Pages34to35   Write protection of page 34 to 35
*\*\            - FLASH_WRP_Pages36to37   Write protection of page 36 to 37
*\*\            - FLASH_WRP_Pages38to39   Write protection of page 38 to 39
*\*\            - FLASH_WRP_Pages40to41   Write protection of page 40 to 41
*\*\            - FLASH_WRP_Pages42to43   Write protection of page 42 to 43
*\*\            - FLASH_WRP_Pages44to45   Write protection of page 44 to 45
*\*\            - FLASH_WRP_Pages46to47   Write protection of page 46 to 47
*\*\            - FLASH_WRP_Pages48to49   Write protection of page 48 to 49
*\*\            - FLASH_WRP_Pages50to51   Write protection of page 50 to 51
*\*\            - FLASH_WRP_Pages52to53   Write protection of page 52 to 53
*\*\            - FLASH_WRP_Pages54to55   Write protection of page 54 to 55
*\*\            - FLASH_WRP_Pages56to57   Write protection of page 56 to 57
*\*\            - FLASH_WRP_Pages58to59   Write protection of page 58 to 59
*\*\            - FLASH_WRP_Pages60to61   Write protection of page 60 to 61
*\*\            - FLASH_WRP_Pages62to63   Write protection of page 62 to 63
*\*\            - FLASH_WRP_AllPages      Write protection of all Pages
*\*\            - ~FLASH_WRP_AllPages     Disable Write protection of all Pages
*\*\return FLASH_STS : 
*\*\            - FLASH_BUSY     FLASH is busy
*\*\            - FLASH_ERR_PG   FLASH programming error
*\*\            - FLASH_ERR_WRP  FLASH Write protected error
*\*\            - FLASH_EOP      FLASH End of Operation
*\*\            - FLASH_ERR_PV   Programmer Verification Error
*\*\            - FLASH_ERR_EV   Erase Verification Error
*\*\            - FLASH_ERR_RDP2 FLASH is in read protection L2 status
*\*\            - FLASH_TIMEOUT  FLASH operation timeout
*\*\            - FLASH_ERR_RPADD   FLASH Row programmer address error
**/
FLASH_STS FLASH_EnWriteProtection(uint32_t FLASH_Pages)
{
    uint16_t WRP0_Data = 0xFF, WRP1_Data = 0xFF, WRP2_Data = 0xFF, WRP3_Data = 0xFF;

    FLASH_STS status_value = FLASH_EOP;
    
    uint32_t FLASH_Pages_temp = FLASH_WRP_AllPages;

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status_value = FLASH_ERR_RDP2;
    }
    else
    {
        /*No process*/
    }

    if(status_value == FLASH_ERR_RDP2)
    {
        
    }
    else
    {
        FLASH_Pages_temp = (uint32_t)(~FLASH_Pages);
        WRP0_Data   = (uint16_t)(FLASH_Pages_temp & FLASH_WRP0_MSK);
        WRP1_Data   = (uint16_t)((FLASH_Pages_temp & FLASH_WRP1_MSK) >> REG_BIT8_OFFSET);
        WRP2_Data   = (uint16_t)((FLASH_Pages_temp & FLASH_WRP2_MSK) >> REG_BIT16_OFFSET);
        WRP3_Data   = (uint16_t)((FLASH_Pages_temp & FLASH_WRP3_MSK) >> REG_BIT24_OFFSET);

        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
    }

    if (status_value == FLASH_EOP)
    {
        /* Authorizes the small information block programming */
        Option_Bytes_Unlock();
        FLASH->CTRL |= CTRL_Set_OPTPG;

        if ((FLASH_Pages_temp != FLASH_WRP_AllPages))
        {
            OBT->WRP1_WRP0 = (((uint32_t)WRP0_Data) | (((uint32_t)WRP1_Data) << REG_BIT16_OFFSET));
            OBT->WRP3_WRP2 = (((uint32_t)WRP2_Data) | (((uint32_t)WRP3_Data) << REG_BIT16_OFFSET));

            /* Wait for last operation to be completed */
            status_value = FLASH_WaitForLastOpt(ProgramTimeout);
        }

        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }

        Option_Bytes_Lock();
    }
    /* Return the write protection operation Status */
    return status_value;
}

/**
*\*\name   FLASH_ProgramOB_RU2U3
*\*\fun    Programs the Option Byte: RDP2/USER2/USER3.
*\*\param  option_byte_rpd2 :(The input parameters must be the following values)
*\*\            - FLASH_OB_RDP2_ENABLE   Enable read protection L2
*\*\            - FLASH_OB_RDP2_DISABLE  Disable read protection L2
*\*\param   option_byte2_nBOOT0 :(The input parameters must be the following values)
*\*\            - FLASH_OB2_NBOOT0_SET Set nBOOT0
*\*\            - FLASH_OB2_NBOOT0_CLR Clear nBOOT0
*\*\param   option_byte2_nBOOT1 :(The input parameters must be the following values)
*\*\            - FLASH_OB2_NBOOT1_SET Set nBOOT1
*\*\            - FLASH_OB2_NBOOT1_CLR Clear nBOOT1
*\*\param   option_byte2_nSWBOOT0 :(The input parameters must be the following values)
*\*\            - FLASH_OB2_NSWBOOT0_SET Set nSWBOOT0
*\*\            - FLASH_OB2_NSWBOOT0_CLR Clear nSWBOOT0
*\*\param   option_byte2_FlashBoot :(The input parameters must be the following values)
*\*\            - FLASH_OB2_FLASHBOOT_SET Main flash forward section boot
*\*\            - FLASH_OB2_FLASHBOOT_CLR Main flash back part boot
*\*\param   option_byte2_BOR :(The input parameters must be the following values)
*\*\            - BOR_LEVEL_1_6V Reset level threshold 1.6V (Up 1.66V / Down 1.62V)
*\*\            - BOR_LEVEL_2_0V Reset level threshold 2.0V (Up 2.1V / Down 2.0V)
*\*\            - BOR_LEVEL_2_2V Reset level threshold 2.2V (Up 2.3V / Down 2.2V)
*\*\            - BOR_LEVEL_2_5V Reset level threshold 2.5V (Up 2.6V / Down 2.5V)
*\*\            - BOR_LEVEL_2_8V Reset level threshold 2.8V (Up 2.9V / Down 2.8V)
*\*\param   option_byte3_NRST :(The input parameters must be the following values)
*\*\            - NRST_SEL_0_RSTIO NRST select reset inputs and outputs
*\*\            - NRST_SEL_1_RSTIN NRST select reset inputs
*\*\            - NRST_SEL_2_GPIO  NRST select GPIO 
*\*\            - NRST_SEL_3_RSTIO NRST select reset inputs and outputs
*\*\return FLASH_STS : 
*\*\            - FLASH_BUSY     FLASH is busy
*\*\            - FLASH_ERR_PG   FLASH programming error
*\*\            - FLASH_ERR_WRP  FLASH Write protected error
*\*\            - FLASH_EOP      FLASH End of Operation
*\*\            - FLASH_ERR_PV   Programmer Verification Error
*\*\            - FLASH_ERR_EV   Erase Verification Error
*\*\            - FLASH_ERR_RDP2 FLASH is in read protection L2 status
*\*\            - FLASH_TIMEOUT  FLASH operation timeout
*\*\            - FLASH_ERR_RPADD   FLASH Row programmer address error
**/
FLASH_STS FLASH_ProgramOB_RU2U3(uint32_t option_byte_rpd2, uint32_t option_byte2_nBOOT0, uint32_t option_byte2_nBOOT1,\
                               uint32_t option_byte2_nSWBOOT0, uint32_t option_byte2_FlashBoot, \
                               uint32_t option_byte2_BOR, uint32_t option_byte3_NRST)
{
    FLASH_STS status_value = FLASH_EOP;
    uint32_t  rpd2_user2_value;
    uint32_t  user3_value;
    
    rpd2_user2_value = option_byte_rpd2 | ((option_byte2_nBOOT0 | option_byte2_nBOOT1 | option_byte2_nSWBOOT0 |\
                       option_byte2_FlashBoot | (option_byte2_BOR << 5)) << 16);
    user3_value = option_byte3_NRST;
    
    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status_value = FLASH_ERR_RDP2;
    }
    else
    {
        /*No process*/
    }

    if(status_value == FLASH_ERR_RDP2)
    {
        
    }
    else
    {
        Option_Bytes_Unlock();

        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
    }

    if (status_value == FLASH_EOP)
    {
        /* Enables the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        OBT->USER2_RDP2 = rpd2_user2_value;
        OBT->USER3 = user3_value;

        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
    }
    Option_Bytes_Lock();
    /* Return the Option Byte Data Program Status */
    return status_value;
}

/**
*\*\name   FLASH_ProgramOB_CCMSRAM
*\*\fun    Programs the Option Byte: CCMSRAM_RST.
*\*\param  option_byte_CCMSRAM :(The input parameters must be the following values)
*\*\            - CCMSRAM_RST_NERASE   CCMSRAM reset not erase
*\*\            - CCMSRAM_RST_ERASE    CCMSRAM reset erase
*\*\return FLASH_STS : (The input parameters must be the following values)
*\*\            - FLASH_BUSY     FLASH is busy
*\*\            - FLASH_ERR_PG   FLASH programming error
*\*\            - FLASH_ERR_WRP  FLASH Write protected error
*\*\            - FLASH_EOP      FLASH End of Operation
*\*\            - FLASH_ERR_PV   Programmer Verification Error
*\*\            - FLASH_ERR_EV   Erase Verification Error
*\*\            - FLASH_ERR_RDP2 FLASH is in read protection L2 status
*\*\            - FLASH_TIMEOUT  FLASH operation timeout
*\*\            - FLASH_ERR_RPADD   FLASH Row programmer address error
**/
FLASH_STS FLASH_ProgramOB_CCMSRAM(uint32_t option_byte_CCMSRAM)
{
    FLASH_STS status_value = FLASH_EOP;
    
    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status_value = FLASH_ERR_RDP2;
    }
    else
    {
        /*No process*/
    }

    if(status_value == FLASH_ERR_RDP2)
    {
        
    }
    else
    {
        Option_Bytes_Unlock();

        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
    }

    if (status_value == FLASH_EOP)
    {
        /* Enables the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        OBT->CCMSRAM_RST = option_byte_CCMSRAM;
        OBT->RESERVED = FLASH_OB_MASK;

        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(ProgramTimeout);
        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
    }
    Option_Bytes_Lock();
    /* Return the Option Byte Data Program Status */
    return status_value;
}


/**
*\*\name   FLASH_ReadOutProtectionL1
*\*\fun    Enables or disables the read out protection.
*\*\param  Cmd:(The input parameters must be the following values)
*\*\            - ENABLE   Enable read protection L1
*\*\            - DISABLE  Disable read protection L1
*\*\return FLASH_STS : (The input parameters must be the following values)
*\*\            - FLASH_BUSY     FLASH is busy
*\*\            - FLASH_ERR_PG   FLASH programming error
*\*\            - FLASH_ERR_WRP  FLASH Write protected error
*\*\            - FLASH_EOP      FLASH End of Operation
*\*\            - FLASH_ERR_PV   Programmer Verification Error
*\*\            - FLASH_ERR_EV   Erase Verification Error
*\*\            - FLASH_ERR_RDP2 FLASH is in read protection L2 status
*\*\            - FLASH_TIMEOUT  FLASH operation timeout
*\*\            - FLASH_ERR_RPADD   FLASH Row programmer address error
*\*\note   If the user has already programmed the other option bytes before calling
*\*\       this function, he must re-program them since this function erases all option bytes.
**/
FLASH_STS FLASH_ReadOutProtectionL1(FunctionalState Cmd)
{
    uint32_t user_rpd1_tmp = 0xFF,data0_data1_tmp = 0xFF,wrp0_wrp1_tmp = 0xFF,wrp2_wrp3_tmp = 0xFF,rdp2_user2_tmp = 0xFF,user3_tmp = 0xFF,CCMSRAM_tmp = 0xFF;
    FLASH_STS status_value = FLASH_EOP;

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status_value = FLASH_ERR_RDP2;
    }
    else
    {
        /*No process*/
    }

    if(status_value == FLASH_ERR_RDP2)
    {
        
    }
    else
    {
        user_rpd1_tmp = (OBT->USER_RDP & 0xFFFF0000U);
        if(Cmd == ENABLE)
        {
            
        }
        else
        {
            user_rpd1_tmp = user_rpd1_tmp | FLASH_OB_RDP1_DISABLE;
        }
        data0_data1_tmp = OBT->Data1_Data0;
        wrp0_wrp1_tmp   = OBT->WRP1_WRP0;
        wrp2_wrp3_tmp   = OBT->WRP3_WRP2;
        rdp2_user2_tmp  = OBT->USER2_RDP2;
        user3_tmp       = OBT->USER3;
        CCMSRAM_tmp     = OBT->CCMSRAM_RST;   

        FLASH_Unlock();
        status_value = FLASH_EraseOB();
    }
    
    if(status_value == FLASH_EOP)
    {
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(EraseTimeout);
    }
    else
    {
        /*No process*/
    }

    if (status_value == FLASH_EOP)
    {
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        OBT->USER_RDP = user_rpd1_tmp;
        OBT->Data1_Data0 = data0_data1_tmp;
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(EraseTimeout);

        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
    }
    else
	{
		/* no process*/
	}
    
    if (status_value == FLASH_EOP)
    {
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        OBT->WRP1_WRP0 = wrp0_wrp1_tmp;
        OBT->WRP3_WRP2 = wrp2_wrp3_tmp;
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(EraseTimeout);

        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
    }
    else
	{
		/* no process*/
	}
    
    if (status_value == FLASH_EOP)
    {
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        OBT->USER2_RDP2 = rdp2_user2_tmp;
        OBT->USER3 = user3_tmp;
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(EraseTimeout);

        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
    }
    else
	{
		/* no process*/
	}
    
    if (status_value == FLASH_EOP)
    {
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        OBT->CCMSRAM_RST = CCMSRAM_tmp;
        OBT->RESERVED = FLASH_OB_MASK;
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(EraseTimeout);

        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
    }
    else
	{
		/* no process*/
	}

    /* Return the protection operation status */
    return status_value;
}


/**
*\*\name   FLASH_ReadOutProtectionL2_ENABLE
*\*\fun    Enables the read out protection L2.
*\*\return FLASH_STS : 
*\*\            - FLASH_BUSY     FLASH is busy
*\*\            - FLASH_ERR_PG   FLASH programming error
*\*\            - FLASH_ERR_WRP  FLASH Write protected error
*\*\            - FLASH_EOP      FLASH End of Operation
*\*\            - FLASH_ERR_PV   Programmer Verification Error
*\*\            - FLASH_ERR_EV   Erase Verification Error
*\*\            - FLASH_ERR_RDP2 FLASH is in read protection L2 status
*\*\            - FLASH_TIMEOUT  FLASH operation timeout
*\*\            - FLASH_ERR_RPADD   FLASH Row programmer address error
*\*\note   If the user has already programmed the other option bytes before calling
*\*\       this function, he must re-program them since this function erases all option bytes.
**/
FLASH_STS FLASH_ReadOutProtectionL2_ENABLE(void)
{
    uint32_t user_rpd1_tmp = 0xFF,data0_data1_tmp = 0xFF,wrp0_wrp1_tmp = 0xFF,wrp2_wrp3_tmp = 0xFF,rdp2_user2_tmp = 0xFF,user3_tmp = 0xFF,CCMSRAM_tmp = 0xFF;
    FLASH_STS status_value = FLASH_EOP;

    /* Get the actual read protection L2 Option Byte value */
    if (FLASH_GetReadOutProtectionL2STS() != RESET)
    {
        status_value = FLASH_ERR_RDP2;
    }
    else
    {
        /*No process*/
    }

    if(status_value == FLASH_ERR_RDP2)
    {
        
    }
    else
    {
        user_rpd1_tmp = OBT->USER_RDP;
        data0_data1_tmp = OBT->Data1_Data0;
        wrp0_wrp1_tmp   = OBT->WRP1_WRP0;
        wrp2_wrp3_tmp   = OBT->WRP3_WRP2;
        rdp2_user2_tmp  = (((OBT->USER2_RDP2) & 0xFFFF0000U) | FLASH_OB_RDP2_ENABLE);
        user3_tmp       = OBT->USER3;
        CCMSRAM_tmp     = OBT->CCMSRAM_RST;   

        FLASH_Unlock();
        status_value = FLASH_EraseOB();
    }

    if (status_value == FLASH_EOP)
    {
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(EraseTimeout);
    }
    else
    {
        /*No process*/
    }  
    
    if (status_value == FLASH_EOP)
    {
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        OBT->USER_RDP = user_rpd1_tmp;
        OBT->Data1_Data0 = data0_data1_tmp;
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(EraseTimeout);

        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
    }
    else
	{
		/* no process*/
	}
    
    if (status_value == FLASH_EOP)
    {
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        OBT->WRP1_WRP0 = wrp0_wrp1_tmp;
        OBT->WRP3_WRP2 = wrp2_wrp3_tmp;
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(EraseTimeout);

        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
    }
    else
	{
		/* no process*/
	}
    
    if (status_value == FLASH_EOP)
    {
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        OBT->USER2_RDP2 = rdp2_user2_tmp;
        OBT->USER3 = user3_tmp;
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(EraseTimeout);

        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
    }
    else
	{
		/* no process*/
	}
    
    if (status_value == FLASH_EOP)
    {
        /* Clears the FLASH's pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);
        /* Enable the Option Bytes Programming operation */
        FLASH->CTRL |= CTRL_Set_OPTPG;
        OBT->CCMSRAM_RST = CCMSRAM_tmp;
        OBT->RESERVED = FLASH_OB_MASK;
        /* Wait for last operation to be completed */
        status_value = FLASH_WaitForLastOpt(EraseTimeout);

        if (status_value != FLASH_TIMEOUT)
        {
            /* if the program operation is completed, disable the OPTPG Bit */
            FLASH->CTRL &= CTRL_Reset_OPTPG;
        }
    }
    else
	{
		/* no process*/
	}

    /* Return the protection operation Status */
    return status_value;
}



/**
*\*\name   FLASH_GetUserOB
*\*\fun    Returns the FLASH User Option Bytes values.
*\*\param  none
*\*\return The FLASH User Option Bytes values:IWDG_SW(Bit0), nRST_STOP(Bit1),
*\*\       nRST_STDBY(Bit2), IWDGSTOPFRZ(Bit3), IWDGSTDBYFRZ(Bit5) and IWDGSLEEPFRZ(Bit6).
**/
uint32_t FLASH_GetUserOB(void)
{
    /* Return the User Option Byte */
    return (uint32_t)((FLASH->OB << REG_BIT23_OFFSET) >> REG_BIT25_OFFSET);
}
/**
*\*\name   FLASH_GetUser2
*\*\fun    Returns the FLASH User2 Option Bytes values.
*\*\param  option_byte_bit: (The input parameters must be the following values)
*\*\            - FLASH_OB2_NBOOT0_SET          nBOOT0 configuration bit
*\*\            - FLASH_OB2_NBOOT1_SET          nBOOT1 configuration bit
*\*\            - FLASH_OB2_NSWBOOT0_SET        nSWBOOT0 configuration bit
*\*\return FlagStatus :
*\*\            - SET      Enter this mode without resetting
*\*\            - RESET    Enter this mode reset
**/
FlagStatus FLASH_GetUser2(uint32_t option_byte_bit)
{
    FlagStatus bit_status;
    if(((FLASH->OB >> REG_BIT28_OFFSET) & option_byte_bit) != (uint32_t)RESET)
    {
        bit_status = SET;
    }
    else
    {
        bit_status = RESET;
    }
    return bit_status;
}

/**
*\*\name   FLASH_GetOptionBytes_Data0
*\*\fun    Returns the FLASH User Option Bytes values.
*\*\param  none
*\*\return data0:
*\*\            - 0x00 to 0xFF.
**/
uint32_t FLASH_GetOptionBytes_Data0(void)
{
    /* Return the User Option Byte2 */
    return (uint32_t)((FLASH->OB & FLASH_OB_DATA0_MASK) >> FLASH_OB_DATA0_OFFSET);
}

/**
*\*\name   FLASH_GetOptionBytes_Data1
*\*\fun    Returns the FLASH User Option Bytes values.
*\*\param  none
*\*\return data1:
*\*\            - 0x00 to 0xFF.
**/
uint32_t FLASH_GetOptionBytes_Data1(void)
{
    /* Return the User Option Byte2 */
    return (uint32_t)((FLASH->OB & FLASH_OB_DATA1_MASK) >> FLASH_OB_DATA1_OFFSET);
}


/**
*\*\name   FLASH_GetWriteProtectionSTS
*\*\fun    Returns the FLASH Write Protection Option Bytes Register value.
*\*\param  none
*\*\return The FLASH Write Protection  Option Bytes Register value :
*\*\            - Bit31 - Bit0 write-protects pages (62~63) - page (0~1) 
**/
uint32_t FLASH_GetWriteProtectionSTS(void)
{
    /* Return the Flash write protection Register value */
    return (uint32_t)(FLASH->WRP);
}


/**
*\*\name   FLASH_GetReadOutProtectionSTS
*\*\fun    Checks whether the FLASH Read Out Protection L1 status_value is set or not.
*\*\param  none
*\*\return FlagStatus :
*\*\        - SET    Read protection L1 enable
*\*\        - RESET  Read protection L1 disable
**/
FlagStatus FLASH_GetReadOutProtectionSTS(void)
{
    FlagStatus readoutstatus;
    if ((FLASH->OB & FLASH_RDPRTL1_MSK) != (uint32_t)RESET)
    {
        readoutstatus = SET;
    }
    else
    {
        readoutstatus = RESET;
    }
    return readoutstatus;
}

/**
*\*\name   FLASH_GetReadOutProtectionL2STS
*\*\fun    Checks whether the FLASH Read Out Protection L2 status_value is set or not.
*\*\param  none
*\*\return FlagStatus :
*\*\        - SET    Read protection L2 enable
*\*\        - RESET  Read protection L2 disable
**/
FlagStatus FLASH_GetReadOutProtectionL2STS(void)
{
    FlagStatus readoutstatus;
    if ((FLASH->OB & FLASH_RDPRTL2_MSK) != (uint32_t)RESET)
    {
        readoutstatus = SET;
    }
    else
    {
        readoutstatus = RESET;
    }
    return readoutstatus;
}


/**
*\*\name   FLASH_GetPrefetchBufSTS
*\*\fun    Checks whether the FLASH Prefetch Buffer status_value is set or not.
*\*\param  none
*\*\return FlagStatus :
*\*\        - SET    Flash prefetch buffer enable
*\*\        - RESET  Flash prefetch buffer disable
**/
FlagStatus FLASH_GetPrefetchBufSTS(void)
{
    FlagStatus bitstatus;

    if ((FLASH->AC & FLASH_PRFTBS_MSK) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    /* Return the new state of FLASH Prefetch Buffer Status (SET or RESET) */
    return bitstatus;
}


/**
*\*\name   FLASH_INTConfig
*\*\fun    Enables or disables the specified FLASH interrupts.
*\*\param  Cmd:(The input parameters must be the following values)
*\*\            - ENABLE
*\*\            - DISABLE 
*\*\param  FLASH_INT :
*\*\            - FLASH_INT_EOP      FLASH end of operation Interrupt
*\*\            - FLASH_INT_ERR      PGERR WRPERR ERROR interrupt source
*\*\            - FLASH_INT_FERR     EVERR PVERR ERROR interrupt source
*\*\            - FLASH_INT_ECC1     1 bit ECC error interrupt source
*\*\            - FLASH_INT_JS       jtag seal error interrupt source 
*\*\            - FLASH_INT_ECC2     2 bit ECC error interrupt source
*\*\            - FLASH_INT_DECC     XSPI/FEMC decryption misconfiguration interrupt source
*\*\            - FLASH_INT_RPADD    Row programmer address error interrupt source
*\*\return none
**/
void FLASH_INTConfig(uint32_t FLASH_INT, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the interrupt sources */
        FLASH->CTRL |= FLASH_INT;
    }
    else
    {
        /* Disable the interrupt sources */
        FLASH->CTRL &= ~(uint32_t)FLASH_INT;
    }
}


/**
*\*\name   FLASH_GetFlagSTS
*\*\fun    Checks whether the specified FLASH flag is set or not. 
*\*\param  FLASH_FLAG :(The input parameters must be the following values)
*\*\            - FLASH_FLAG_EOP        FLASH End of Operation flag
*\*\            - FLASH_FLAG_BUSY       FLASH Busy flag
*\*\            - FLASH_FLAG_PGERR      FLASH Program error flag
*\*\            - FLASH_FLAG_WRPERR     FLASH Write protected error flag
*\*\            - FLASH_FLAG_PVERR      FLASH Program Verify ERROR flag 
*\*\            - FLASH_FLAG_EVERR      FLASH Erase Verify ERROR flag
*\*\            - FLASH_FLAG_ECC1ERR    FLASH 1 bit ECC ERROR flag
*\*\            - FLASH_FLAG_RDKEYERR   read key error flag
*\*\            - FLASH_FLAG_RDXKEYERR  xKEY match error flag
*\*\            - FLASH_FLAG_NRDXKEYEN  Not allowed to read RTPD_KEY enable flag
*\*\            - FLASH_FLAG_JSERR      JTAG/SRAM access JTAG_SEAL error flag
*\*\            - FLASH_FLAG_RTPKEYERR  read RTPD_KEY error flag
*\*\            - FLASH_FLAG_ECC2ERR    FLASH 2 bit ECC error flag
*\*\            - FLASH_FLAG_DECCRDF    XSPI/FEMC Decryption Configuration Completion Flag
*\*\            - FLASH_FLAG_DECCERR    XSPI/FEMC Decryption Configuration sequences error Flag
*\*\            - FLASH_FLAG_FWORDF     first word write completion flag
*\*\            - FLASH_FLAG_RPADDERR   row programmmer address error
*\*\            - FLASH_FLAG_OBERR      FLASH Option Byte error flag
*\*\return none
**/
FlagStatus FLASH_GetFlagSTS(uint32_t FLASH_FLAG)
{
    FlagStatus bitstatus;

    if (FLASH_FLAG == FLASH_FLAG_OBERR)
    {
        if ((FLASH->OB & FLASH_FLAG_OBERR) != (uint32_t)RESET)
        {
            bitstatus = SET;
        }
        else
        {
            bitstatus = RESET;
        }
    }
    else
    {
        if ((FLASH->STS & FLASH_FLAG) != (uint32_t)RESET)
        {
            bitstatus = SET;
        }
        else
        {
            bitstatus = RESET;
        }
    }

    /* Return the new state of FLASH_FLAG (SET or RESET) */
    return bitstatus;
}


/**
*\*\name   FLASH_ClearFlag
*\*\fun    Clears the FLASH's pending flags. 
*\*\param  FLASH_FLAG :(The input parameters must be the following values)
*\*\            - FLASH_FLAG_EOP        FLASH End of Operation flag
*\*\            - FLASH_FLAG_PGERR      FLASH Program error flag
*\*\            - FLASH_FLAG_WRPERR     FLASH Write protected error flag
*\*\            - FLASH_FLAG_PVERR      FLASH Program Verify ERROR flag 
*\*\            - FLASH_FLAG_EVERR      FLASH Erase Verify ERROR flag
*\*\            - FLASH_FLAG_ECC1ERR    FLASH 1 bit ECC ERROR flag
*\*\            - FLASH_FLAG_JSERR      JTAG/SRAM access JTAG_SEAL error flag
*\*\            - FLASH_FLAG_RTPKEYERR  read RTPD_KEY error flag
*\*\            - FLASH_FLAG_ECC2ERR    FLASH 2 bit ECC error flag
*\*\            - FLASH_FLAG_DECCRDF    XSPI/FEMC Decryption Configuration Completion Flag
*\*\            - FLASH_FLAG_DECCERR    XSPI/FEMC Decryption Configuration sequences error Flag
*\*\            - FLASH_FLAG_RPADDERR   row programmmer address error
*\*\return none
**/
void FLASH_ClearFlag(uint32_t FLASH_FLAG)
{
    /* Clear the flags */
    FLASH->STS = FLASH_FLAG;
}

/**
*\*\name   FLASH_GetSTS
*\*\fun    Returns the FLASH Status.
*\*\param  none
*\*\return FLASH_STS : 
*\*\            - FLASH_BUSY     FLASH is busy
*\*\            - FLASH_ERR_PG   FLASH programming error
*\*\            - FLASH_ERR_WRP  FLASH Write protected error
*\*\            - FLASH_EOP      FLASH End of Operation
*\*\            - FLASH_ERR_PV   Programmer Verification Error
*\*\            - FLASH_ERR_EV   Erase Verification Error
*\*\            - FLASH_ERR_RPADD   FLASH Row programmer address error
**/
FLASH_STS FLASH_GetSTS(void)
{
    FLASH_STS flashstatus;

    if ((FLASH->STS & FLASH_FLAG_BUSY) == FLASH_FLAG_BUSY)
    {
        flashstatus = FLASH_BUSY;
    }
    else
    {
        if ((FLASH->STS & FLASH_FLAG_PGERR) != 0)
        {
            flashstatus = FLASH_ERR_PG;
        }
        else
        {
            if ((FLASH->STS & FLASH_FLAG_PVERR) != 0)
            {
                flashstatus = FLASH_ERR_PV;
            }
            else
            {
                if ((FLASH->STS & FLASH_FLAG_WRPERR) != 0)
                {
                    flashstatus = FLASH_ERR_WRP;
                }
                else
                {
                    if ((FLASH->STS & FLASH_FLAG_EVERR) != 0)
                    {
                        flashstatus = FLASH_ERR_EV;
                    }
                    else
                    {
                        if((FLASH->STS & FLASH_FLAG_RPADDERR) != 0)
                        {
                            flashstatus = FLASH_ERR_RPADD;
                        }
                        else
                        {
                            flashstatus = FLASH_EOP;
                        }
                    }
                }
            }
        }
    }

    /* Return the Flash Status */
    return flashstatus;
}


/**
*\*\name   FLASH_WaitForLastOpt
*\*\fun    Waits for a Flash operation to complete or a TIMEOUT to occur.
*\*\param  Timeout:(The input parameters must be the following values)
*\*\            - EraseTimeout
*\*\            - ProgramTimeout
*\*\            - RowProgramTimeout
*\*\return FLASH_STS : 
*\*\            - FLASH_BUSY     FLASH is busy
*\*\            - FLASH_ERR_PG   FLASH programming error
*\*\            - FLASH_ERR_WRP  FLASH Write protected error
*\*\            - FLASH_EOP      FLASH End of Operation
*\*\            - FLASH_ERR_PV   Programmer Verification Error
*\*\            - FLASH_ERR_EV   Erase Verification Error
*\*\            - FLASH_ERR_RPADD   FLASH Row programmer address error
**/
FLASH_STS FLASH_WaitForLastOpt(uint32_t Timeout)
{
    FLASH_STS status_value;
    uint32_t Timeout_temp;
    Timeout_temp = Timeout;

    __NOP();
    __NOP();
    __NOP();
    __NOP();
    /* Check for the Flash Status */
    status_value = FLASH_GetSTS();
    /* Wait for a Flash operation to complete or a TIMEOUT to occur */
    while ((status_value == FLASH_BUSY) && (Timeout_temp != 0x00))
    {
        status_value = FLASH_GetSTS();
        Timeout_temp--;
    }
    if (Timeout_temp == 0x00)
    {
        status_value = FLASH_TIMEOUT;
    }
    /* Return the operation status */
    return status_value;
}

/**
*\*\name   CCM_EnWriteProtection
*\*\fun    Enables write protection CCM x page.
*\*\param  CCM_Pages:(The input parameters must be the following values)
*\*\            - Bit31 - Bit0 write-protects pages (31) - page (0) 
*\*\return none
**/
void CCM_EnWriteProtection(uint32_t CCM_Pages)
{
    FLASH->CCM_WRP1 = CCM_Pages;
}


/**
*\*\name   CCM_GetWriteProtectionSTS
*\*\fun    Returns the CCM Write Protection Option Bytes Register value.
*\*\param  none
*\*\return The CCM Write Protection  Option Bytes Register value :
*\*\            - Bit31 - Bit0 write-protects pages (31) - page (0) 
**/
uint32_t CCM_GetWriteProtectionSTS(void)
{
    /* Return the Flash write protection Register value */
    return (uint32_t)(FLASH->CCM_WRP1);
}

/**
*\*\name   CCM_ERASE_Unlock
*\*\fun    Unlocks the CCM Erase Controller.
*\*\param  none
*\*\return none
**/
void CCM_Earse_Unlock(void)
{
    FLASH->CCM_KEY = CCM_KEY1;
    FLASH->CCM_KEY = CCM_KEY2;
}

/**
*\*\name   CCM_ERASE_EN
*\*\fun    ENABLE CCM Erase.
*\*\param  none
*\*\return none
**/
void CCM_EarseEN(void)
{
    FLASH->CCM_ERASE |= CCM_ERASE_ENABLE;
}

/**
*\*\name   CCM_EarseSTS
*\*\fun    Get CCM Erase Status.
*\*\param  none
*\*\return FlagStatus :
*\*\        - SET    CCM SRAM erase operation
*\*\        - RESET  No CCM SRAM erase operation
**/
FlagStatus CCM_EarseSTS(void)
{
    FlagStatus ccmstatus;
    if((FLASH->CCM_ERASE & CCM_ERASE_STSMSK) == CCM_ERASE_STSMSK)
    {
        ccmstatus = SET;
    }
    else
    {
        ccmstatus = RESET;
    }
    return ccmstatus;
}


/**
*\*\name   CCM_ModeSet
*\*\fun    Enables or disables CCM mode.
*\*\param  Cmd:(The input parameters must be the following values)
*\*\            - ENABLE
*\*\            - DISABLE 
*\*\return none
**/
void CCM_ModeSet(FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        FLASH->CCM_MODE |= CCM_MODE_ENABLE;
    }
    else
    {
        FLASH->CCM_MODE &= (~CCM_MODE_ENABLE);
    }   
}


/**
*\*\name   XSPI_DESRangeSet
*\*\fun    XSPI Decryption address range setting.
*\*\param  start_add:(The input parameters must be the following values)
*\*\            - It ranges from 0x90000000 to 0x9FFFFFFF 
*\*\param  end_add:(The input parameters must be the following values)
*\*\            - It ranges from 0x90000000 to 0x9FFFFFFF 
*\*\return none
**/
void XSPI_DESRangeSet(uint32_t start_add,uint32_t end_add)
{
    FLASH->XSPI_DSTRADD = start_add;
    FLASH->XSPI_DENDADD = end_add;
}

/**
*\*\name   FEMC_DESRangeSet
*\*\fun    FEMC Decryption address range setting.
*\*\param  start_add:(The input parameters must be the following values)
*\*\            - It ranges from 0x60000000 to 0x8FFFFFFF 
*\*\param  end_add:(The input parameters must be the following values)
*\*\            - It ranges from 0x60000000 to 0x8FFFFFFF 
*\*\return none
**/
void FEMC_DESRangeSet(uint32_t start_add,uint32_t end_add)
{
    FLASH->FEMC_DSTRADD = start_add;
    FLASH->FEMC_DENDADD = end_add;
}


/**
*\*\name   RTP_DESKeySet
*\*\fun    128bit RTPD decryption key setting.
*\*\param  DES_key:(The input parameters must be the following values)
*\*\            - A 128-bit key 
*\*\return none
**/
void RTP_DESKeySet(uint32_t* DES_key)
{
    FLASH->RTPD_KEY = DES_key[0];
    FLASH->RTPD_KEY = DES_key[1];
    FLASH->RTPD_KEY = DES_key[2];
    FLASH->RTPD_KEY = DES_key[3];
}

/**
*\*\name   GetRTP_DESKeyWnum
*\*\fun    get RTPD_KEY Write Count.
*\*\param  none
*\*\return CNT:
*\*\            - RTPD_KEY write cnt
**/
uint32_t GetRTP_DESKeyWnum(void)
{
    return (FLASH->RTPD_KEY_WCNT & RTPD_KEY_WCNT_CNT_MASK);
}


/**
*\*\name   Jtag_SealSet
*\*\fun    Enables or disables Jtag_Seal.
*\*\param  Cmd:(The input parameters must be the following values)
*\*\            - ENABLE
*\*\            - DISABLE 
*\*\return none
**/
void Jtag_SealSet(FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        FLASH->JTAG_SEAL = JTAG_SEAL_ENABLE;
    }
    else
    {
        FLASH->JTAG_SEAL = JTAG_SEAL_DISABLE;
    }   
}

/**
*\*\name   XSPI_FEMC_DESSet
*\*\fun    Enables or disables XSPI/FEMC decryption.
*\*\param  Cmd:(The input parameters must be the following values)
*\*\            - ENABLE
*\*\            - DISABLE 
*\*\return none
**/
void XSPI_FEMC_DESSet(FunctionalState Cmd)
{
    if(Cmd == ENABLE)
    {
        FLASH->XSPI_FEMC_DEN = XSPI_FEMC_DES_ENABLE;
    }
    else
    {
        FLASH->XSPI_FEMC_DEN &= (~XSPI_FEMC_DES_ENABLE);
    }   
}


/**
*\*\name   Get_XFUID
*\*\fun    get XSPI/FEMC configure UID.
*\*\param  none
*\*\return UID:
*\*\            - 0x01  BOOT user
*\*\            - 0x02  FLASH user1
*\*\            - 0x04  FLASH user2
*\*\            - 0x08  FLASH user3
*\*\            - 0x10  SRAM user
**/
uint32_t Get_XFUID(void)
{
    return (FLASH->XUID & XFUID_MASK);
}

/**
*\*\name   Get_CCMUID
*\*\fun    get CCM configure UID.
*\*\param  none
*\*\return UID:
*\*\            - 0x01  BOOT user
*\*\            - 0x02  FLASH user1
*\*\            - 0x04  FLASH user2
*\*\            - 0x08  FLASH user3
*\*\            - 0x10  SRAM user
**/
uint32_t Get_CCMUID(void)
{
    return ((FLASH->XUID & CCMUID_MASK) >> 0x05);
}


