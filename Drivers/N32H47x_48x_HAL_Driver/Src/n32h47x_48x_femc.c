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
*\*\file n32h47x_48x_femc.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/

#include "n32h47x_48x_femc.h"
#include "n32h47x_48x_rcc.h"
#include "stdio.h"


/**
*\*\name    FEMC_DeInitNorSram.
*\*\fun     Deinitializes the FEMC SRAM/NOR Banks registers to their default reset values.
*\*\param   Block: FEMC_SN_Bank pointer to SRAM/NorFlash bank block which will beinitialized. 
*\*\            - FEMC_SN_BANK_BLOCK1   FEMC SRAM/NOR Bank Block1
*\*\            - FEMC_SN_BANK_BLOCK2   FEMC SRAM/NOR Bank Block2
*\*\            - FEMC_SN_BANK_BLOCK3   FEMC SRAM/NOR Bank Block3
*\*\            - FEMC_SN_BANK_BLOCK4   FEMC SRAM/NOR Bank Block4
*\*\return  none
**/
void FEMC_DeInitNorSram(FEMC_SN_Bank_Block *Block)
{
    /*  FEMC_SN_BANK */
    Block->CTRL   = FEMC_NOR_SRAM_CTRL_RESET;
    Block->TCFG   = FEMC_NOR_SRAM_TCFG_RESET;
    Block->WTCFG  = FEMC_NOR_SRAM_WTCFG_RESET;
}

/**
*\*\name    FEMC_DeInitNand.
*\*\fun     Deinitializes the FEMC NAND Banks registers to their default reset values.
*\*\param   Bank: FEMC_NAND_Bank pointer to NAND bank which will beinitialized. 
*\*\            - FEMC_NAND_BANK2 FEMC Bank2 NAND
*\*\            - FEMC_NAND_BANK3 FEMC Bank3 NAND
*\*\return  none
**/
void FEMC_DeInitNand(FEMC_NAND_Bank *Bank)
{
    Bank->CTRL     = FEMC_NAND_CTRL_RESET;
    Bank->STS      = FEMC_NAND_STS_RESET;
    Bank->CMEMTM   = FEMC_NAND_CMEMTM_RESET;
    Bank->ATTMEMTM = FEMC_NAND_ATTMEMTM_RESET;
}

/**
*\*\name    FEMC_InitNorSram.
*\*\fun     Initializes the FEMC NOR/SRAM Bank Blocks according to the specified parameters in the FEMC_NORSRAMInitStruct.
*\*\param   FEMC_NORSRAMInitStruct : pointer to a FEMC_NorSramInitType
*\*\        structure that contains the configuration information for
*\*\        the FEMC NOR/SRAM specified Bank Blocks.
*\*\return  none
**/
void FEMC_InitNorSram(FEMC_NorSramInitType* FEMC_NORSRAMInitStruct)
{
    /* Bank NOR/SRAM control register configuration */
    FEMC_NORSRAMInitStruct->Block->CTRL = FEMC_NORSRAMInitStruct->DataAddrMux
                                        | FEMC_NORSRAMInitStruct->MemType
                                        | FEMC_NORSRAMInitStruct->MemDataWidth 
                                        | FEMC_NORSRAMInitStruct->BurstAccMode
                                        | FEMC_NORSRAMInitStruct->AsynchroWait 
                                        | FEMC_NORSRAMInitStruct->WaitSigPolarity
                                        | FEMC_NORSRAMInitStruct->WrapMode 
                                        | FEMC_NORSRAMInitStruct->WaitSigConfig 
                                        | FEMC_NORSRAMInitStruct->WriteEnable
                                        | FEMC_NORSRAMInitStruct->WaitSigEnable 
                                        | FEMC_NORSRAMInitStruct->ExtModeEnable
                                        | FEMC_NORSRAMInitStruct->WriteBurstEnable
                                        | FEMC_NORSRAMInitStruct->CramPageSize
                                        | FEMC_NORSRAMInitStruct->NadvPolarity;

    if (FEMC_NORSRAMInitStruct->MemType == FEMC_MEM_TYPE_NOR)
    {
        FEMC_NORSRAMInitStruct->Block->CTRL |= (uint32_t)FEMC_NOR_SRAM_ACC_ENABLE;
    }

    /* Bank Block NOR/SRAM timing register configuration */
    FEMC_NORSRAMInitStruct->Block->TCFG =  FEMC_NORSRAMInitStruct->RWTimingStruct->AddrSetTime
                                        | FEMC_NORSRAMInitStruct->RWTimingStruct->AddrHoldTime
                                        | FEMC_NORSRAMInitStruct->RWTimingStruct->DataSetTime
                                        | FEMC_NORSRAMInitStruct->RWTimingStruct->BusRecoveryCycle
                                        | FEMC_NORSRAMInitStruct->RWTimingStruct->ClkDiv
                                        | FEMC_NORSRAMInitStruct->RWTimingStruct->DataHoldTime
                                        | FEMC_NORSRAMInitStruct->RWTimingStruct->AccMode;

    /* Bank Block NOR/SRAM timing register for write configuration, if extended mode is used */
    if (FEMC_NORSRAMInitStruct->ExtModeEnable == FEMC_NOR_SRAM_EXTENDED_ENABLE)
    {
        FEMC_NORSRAMInitStruct->Block->WTCFG = FEMC_NORSRAMInitStruct->WTimingStruct->AddrSetTime
                                        | FEMC_NORSRAMInitStruct->WTimingStruct->AddrHoldTime
                                        | FEMC_NORSRAMInitStruct->WTimingStruct->DataSetTime
                                        | (FEMC_NORSRAMInitStruct->RWTimingStruct->BusRecoveryCycle >> 4)
                                        | FEMC_NORSRAMInitStruct->WTimingStruct->AccMode;
    }
    else
    {
        FEMC_NORSRAMInitStruct->Block->WTCFG = FEMC_NOR_SRAM_WTCFG_RESET;
    }
}

/**
*\*\name    FEMC_InitNand.
*\*\fun     Initializes the FEMC NAND Banks according to the specified parameters in the FEMC_NANDInitStruct.
*\*\param   FEMC_NANDInitStruct pointer to a FEMC_NandInitType
*\*\        structure that contains the configuration information for the FEMC NAND specified Banks.
*\*\return  none
**/
void FEMC_InitNand(FEMC_NandInitType* FEMC_NANDInitStruct)
{
    uint32_t tmppcr, tmppmem, tmppatt;

    /* Set the tmppcr value according to FEMC_NANDInitStruct parameters */
    tmppcr = FEMC_NANDInitStruct->WaitFeatureEnable 
            | FEMC_NANDInitStruct->MemDataWidth
            | FEMC_NANDInitStruct->EccEnable
            | FEMC_NANDInitStruct->EccPageSize
            | FEMC_NANDInitStruct->TCLRSetTime
            | FEMC_NANDInitStruct->TARSetTime;

    /* Set tmppmem value according to FEMC_CommonSpaceTimingStructure parameters */
    tmppmem = (FEMC_NANDInitStruct->CommSpaceTimingStruct->SetTime)
              | (FEMC_NANDInitStruct->CommSpaceTimingStruct->WaitSetTime)
              | (FEMC_NANDInitStruct->CommSpaceTimingStruct->HoldSetTime)
              | (FEMC_NANDInitStruct->CommSpaceTimingStruct->HiZSetTime);

    /* Set tmppatt value according to FEMC_AttributeSpaceTimingStructure parameters */
    tmppatt = (FEMC_NANDInitStruct->AttrSpaceTimingStruct->SetTime)
              | (FEMC_NANDInitStruct->AttrSpaceTimingStruct->WaitSetTime)
              | (FEMC_NANDInitStruct->AttrSpaceTimingStruct->HoldSetTime)
              | (FEMC_NANDInitStruct->AttrSpaceTimingStruct->HiZSetTime);

    FEMC_NANDInitStruct->Bank->CTRL        = tmppcr;
    FEMC_NANDInitStruct->Bank->CMEMTM      = tmppmem;
    FEMC_NANDInitStruct->Bank->ATTMEMTM    = tmppatt;
}

/**
*\*\name    FEMC_InitNorSramStruct.
*\*\fun     Fills each FEMC_NORSRAMInitStruct member with its default value.
*\*\param   FEMC_NORSRAMInitStruct pointer to a FEMC_NorSramInitType structure which will be initialized.
*\*\return  none
**/
void FEMC_InitNorSramStruct(FEMC_NorSramInitType* FEMC_NORSRAMInitStruct)
{
    /* Reset NOR/SRAM Init structure parameters values */
    FEMC_NORSRAMInitStruct->Block                            = FEMC_SN_BANK_BLOCK1;
    FEMC_NORSRAMInitStruct->DataAddrMux                      = FEMC_NOR_SRAM_MUX_ENABLE;
    FEMC_NORSRAMInitStruct->MemType                          = FEMC_MEM_TYPE_SRAM;
    FEMC_NORSRAMInitStruct->MemDataWidth                     = FEMC_NOR_SRAM_DATA_WIDTH_8B;
    FEMC_NORSRAMInitStruct->BurstAccMode                     = FEMC_NOR_SRAM_BURST_MODE_DISABLE;
    FEMC_NORSRAMInitStruct->AsynchroWait                     = FEMC_NOR_SRAM_ASYNC_NWAIT_DISABLE;
    FEMC_NORSRAMInitStruct->WaitSigPolarity                  = FEMC_NOR_SRAM_WAIT_SIGNAL_LOW;
    FEMC_NORSRAMInitStruct->WrapMode                         = FEMC_NOR_SRAM_WRAP_DISABLE;
    FEMC_NORSRAMInitStruct->WaitSigConfig                    = FEMC_NOR_SRAM_NWAIT_BEFORE_STATE;
    FEMC_NORSRAMInitStruct->WriteEnable                      = FEMC_NOR_SRAM_WRITE_ENABLE;
    FEMC_NORSRAMInitStruct->WaitSigEnable                    = FEMC_NOR_SRAM_NWAIT_ENABLE;
    FEMC_NORSRAMInitStruct->ExtModeEnable                    = FEMC_NOR_SRAM_EXTENDED_DISABLE;
    FEMC_NORSRAMInitStruct->WriteBurstEnable                 = FEMC_NOR_SRAM_BURST_WRITE_DISABLE;
    FEMC_NORSRAMInitStruct->CramPageSize                     = FEMC_CRAM_BURST_PAGE_SIZE_0;
    FEMC_NORSRAMInitStruct->NadvPolarity                     = FEMC_NOR_SRAM_NADV_SIGNAL_LOW;
    
    FEMC_NORSRAMInitStruct->RWTimingStruct = NULL;
    FEMC_NORSRAMInitStruct->WTimingStruct = NULL;

}

/**
*\*\name    FEMC_InitNandStruct.
*\*\fun     Fills each FEMC_NANDInitStruct member with its default value.
*\*\param   FEMC_NANDInitStruct pointer to a FEMC_NandInitType structure which will be initialized.
*\*\return  none
**/
void FEMC_InitNandStruct(FEMC_NandInitType* FEMC_NANDInitStruct)
{
    /* Reset NAND Init structure parameters values */
    FEMC_NANDInitStruct->Bank                               = FEMC_NAND_BANK2;
    FEMC_NANDInitStruct->WaitFeatureEnable                  = FEMC_NAND_NWAIT_DISABLE;
    FEMC_NANDInitStruct->MemDataWidth                       = FEMC_NAND_BUS_WIDTH_8B;
    FEMC_NANDInitStruct->EccEnable                          = FEMC_NAND_ECC_DISABLE;
    FEMC_NANDInitStruct->EccPageSize                        = FEMC_NAND_ECC_PAGE_256BYTES;
    FEMC_NANDInitStruct->TCLRSetTime                        = FEMC_NAND_CLE_DELAY_1HCLK;
    FEMC_NANDInitStruct->TARSetTime                         = FEMC_NAND_ALE_DELAY_1HCLK;
    FEMC_NANDInitStruct->CommSpaceTimingStruct = NULL;
    FEMC_NANDInitStruct->AttrSpaceTimingStruct = NULL;
}

/**
*\*\name    FEMC_EnableNorSram.
*\*\fun     Enables or disables the specified NOR/SRAM Memory Bank.
*\*\param   Block specifies the NOR/SRAM Bank Block to be used
*\*\          - FEMC_SN_BANK_BLOCK1
*\*\          - FEMC_SN_BANK_BLOCK2
*\*\          - FEMC_SN_BANK_BLOCK3
*\*\          - FEMC_SN_BANK_BLOCK4
*\*\param  Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void FEMC_EnableNorSram(FEMC_SN_Bank_Block *Block, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected NOR/SRAM Bank */
        Block->CTRL |= FEMC_NOR_SRAM_ENABLE;
    }
    else
    {
        /* Disable the selected NOR/SRAM Bank */
        Block->CTRL &= ~FEMC_NOR_SRAM_ENABLE;
    }
}

/**
*\*\name    FEMC_EnableNand.
*\*\fun     Enables or disables the specified NAND Memory Bank.
*\*\param   Bank specifies the NAND Bank to be used
*\*\          - FEMC_NAND_BANK2
*\*\          - FEMC_NAND_BANK3
*\*\param  Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void FEMC_EnableNand(FEMC_NAND_Bank *Bank, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected NAND Bank */
        Bank->CTRL |= FEMC_NAND_BANK_ENABLE;
    }
    else
    {
        /* Disable the selected NAND Bank */
        Bank->CTRL &= ~FEMC_NAND_BANK_ENABLE;
    }
}

/**
*\*\name    FEMC_EnableNandEcc.
*\*\fun     Enables or disables the FEMC NAND ECC feature.
*\*\param   Bank specifies the NAND Bank to be used
*\*\          - FEMC_NAND_BANK2
*\*\          - FEMC_NAND_BANK3
*\*\param  Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void FEMC_EnableNandEcc(FEMC_NAND_Bank *Bank, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected NAND Bank ECC function */
        Bank->CTRL |= FEMC_NAND_ECC_ENABLE;
    }
    else
    {
        /* Disable the selected NAND Bank ECC function */
        Bank->CTRL &= ~FEMC_NAND_ECC_ENABLE;
    }
}

/**
*\*\name    FEMC_RestartNandEcc.
*\*\fun     Clear ECC result and start a new ECC process.
*\*\param   Bank specifies the NAND Bank to be used
*\*\          - FEMC_NAND_BANK2
*\*\          - FEMC_NAND_BANK3
*\*\return  none
**/
void FEMC_RestartNandEcc(FEMC_NAND_Bank *Bank)
{
    Bank->CTRL &= ~FEMC_NAND_ECC_ENABLE;
    Bank->CTRL |= FEMC_NAND_ECC_ENABLE;
}

/**
*\*\name    FEMC_GetEcc.
*\*\fun     Returns the error correction code register value.
*\*\param   Bank specifies the NAND Bank to be used
*\*\          - FEMC_NAND_BANK2
*\*\          - FEMC_NAND_BANK3
*\*\return  The Error Correction Code (ECC) value.
**/
uint32_t FEMC_GetEcc(FEMC_NAND_Bank *Bank)
{
    uint32_t tEccPageSize,tECC = 0;
    
    tEccPageSize = Bank->CTRL & FEMC_NCTRL_ECCPGS_MASK;

    switch(tEccPageSize)
    {
        case FEMC_NAND_ECC_PAGE_256BYTES:
                tECC = Bank->ECC & FEMC_ECC_PAGE_256BYTE_MASK;
                break;
        case FEMC_NAND_ECC_PAGE_512BYTES:
                tECC = Bank->ECC & FEMC_ECC_PAGE_512BYTE_MASK;
                break;
        case FEMC_NAND_ECC_PAGE_1024BYTES:
                tECC = Bank->ECC & FEMC_ECC_PBAE_1024BYTE_MASK;
                break;
        case FEMC_NAND_ECC_PAGE_2048BYTES:
                tECC = Bank->ECC & FEMC_ECC_PBAE_2048BYTE_MASK;
                break;
        case FEMC_NAND_ECC_PAGE_4096BYTES:
                tECC = Bank->ECC & FEMC_ECC_PBAE_4096BYTE_MASK;
                break;
        case FEMC_NAND_ECC_PAGE_8192BYTES:
                tECC = Bank->ECC & FEMC_ECC_PBAE_8192BYTE_MASK;
                break;
        default:
                break;
    }
    
    /* Return the error correction code value */
    return (tECC);
}

/**
*\*\name    FEMC_ConfigInt.
*\*\fun     Enables or disables the specified RTC interrupts.
*\*\param   Bank specifies the NAND Bank to be used
*\*\          - FEMC_NAND_BANK2
*\*\          - FEMC_NAND_BANK3
*\*\param   FEMC_INT specifies the NAND flag
*\*\          - FEMC_NAND_INT_HIGH_LEVEL
*\*\          - FEMC_NAND_INT_RASING_EDGE
*\*\          - FEMC_NAND_INT_FALLING_EDGE
*\*\param  Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void FEMC_ConfigInt(FEMC_NAND_Bank *Bank, uint32_t FEMC_INT, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Configure the Interrupts */
        Bank->STS |= FEMC_INT;
    }
    else
    {
        /* Configure the Interrupts */
        Bank->STS &= ~FEMC_INT;
    }
}

/**
*\*\name    FEMC_GetFlag.
*\*\fun     Checks whether the specified NAND flag is set or not.
*\*\param   Bank specifies the NAND Bank to be used
*\*\          - FEMC_NAND_BANK2
*\*\          - FEMC_NAND_BANK3
*\*\param   FEMC_FLAG specifies the NAND flag
*\*\          - FEMC_NAND_FLAG_FIFO_EMPTY
*\*\return  FlagStatus
*\*\          - SET   : the flag is set
*\*\          - RESET : the flag is reset   
**/
FlagStatus FEMC_GetFlag(FEMC_NAND_Bank *Bank, uint32_t FEMC_FLAG)
{
    FlagStatus bitstatus = RESET;
    
    /* Get the flag status */
    if ((Bank->STS & FEMC_FLAG) != (uint16_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    /* Return the flag status */
    return bitstatus;
}

/**
*\*\name    FEMC_ClrFlag.
*\*\fun     Clears the FEMC's pending flags.
*\*\param   Bank specifies the NAND Bank to be used
*\*\          - FEMC_NAND_BANK2
*\*\          - FEMC_NAND_BANK3
*\*\param   FEMC_FLAG specifies the NAND flag
*\*\          - FEMC_NAND_FLAG_FIFO_EMPTY

*\*\return  none
**/
void FEMC_ClrFlag(FEMC_NAND_Bank *Bank, uint32_t FEMC_FLAG)
{
    Bank->STS &= ~FEMC_FLAG;
}

/**
*\*\name    FEMC_GetFlag.
*\*\fun     Checks whether the specified NAND interrupt flag is set or not.
*\*\param   Bank specifies the NAND Bank to be used
*\*\          - FEMC_NAND_BANK2
*\*\          - FEMC_NAND_BANK3
*\*\param   FEMC_FLAG specifies the NAND flag
*\*\          - FEMC_NAND_INT_FLAG_HIGH_LEVEL
*\*\          - FEMC_NAND_INT_FLAG_RASING_EDGE
*\*\          - FEMC_NAND_INT_FLAG_FALLING_EDGE
*\*\return  FlagStatus
*\*\          - SET   : the flag is set
*\*\          - RESET : the flag is reset   
**/
FlagStatus FEMC_GetITFlag(FEMC_NAND_Bank *Bank, uint32_t FEMC_FLAG)
{
    FlagStatus bitstatus = RESET;
    
    /* Get the flag status */
    if ((Bank->STS & FEMC_FLAG) != (uint16_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    /* Return the flag status */
    return bitstatus;
}

/**
*\*\name    FEMC_ClrITFlag.
*\*\fun     Clears the FEMC's interrupt pending flags.
*\*\param   Bank specifies the NAND Bank to be used
*\*\          - FEMC_NAND_BANK2
*\*\          - FEMC_NAND_BANK3
*\*\param   FEMC_FLAG specifies the NAND flag
*\*\          - FEMC_NAND_INT_FLAG_HIGH_LEVEL
*\*\          - FEMC_NAND_INT_FLAG_RASING_EDGE
*\*\          - FEMC_NAND_INT_FLAG_FALLING_EDGE
*\*\return  none
**/
void FEMC_ClrITFlag(FEMC_NAND_Bank *Bank, uint32_t FEMC_FLAG)
{
    Bank->STS &= ~FEMC_FLAG;
}
