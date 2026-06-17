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
 *\*\file n32h47x_48x_sdio.c
 *\*\author Nations
 *\*\version v1.0.0
 *\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
 **/

#include "n32h47x_48x_sdio.h"
#include "n32h47x_48x_rcc.h"

static uint32_t SDIO_GetCmdError(void);

/**
 *\*\name   SDIO_DeInit.
 *\*\fun    Reset the SDIO peripheral registers to their default reset values.
 *\*\param  none
 *\*\return none
 */
void SDIO_DeInit(void)
{
    RCC_EnableAHBPeriphReset(RCC_AHB_PERIPHRST_SDIO);
}

/**
 *\*\name   SDIO_Init.
 *\*\fun    Initializes the SDIO peripheral according to the specified
 *\*\       parameters in the InitStruct.
 *\*\param  InitStruct pointer to a SDIO_InitType structure.
 *\*\       The input parameters must be the following values:
 *\*\          - ClkEdge: 
 *\*\               - SDIO_CLK_EDGE_RISING 
 *\*\               - SDIO_CLK_EDGE_FALLING
 *\*\          - ClkBypass:  
 *\*\               - SDIO_CLK_BYPASS_DISABLE
 *\*\               - SDIO_CLK_BYPASS_ENABLE 
 *\*\          - ClkPwrSave:  
 *\*\               - SDIO_CLK_POWER_SAVE_DISABLE
 *\*\               - SDIO_CLK_POWER_SAVE_ENABLE 
 *\*\          - BusWidth:  
 *\*\               - SDIO_BUS_WIDTH_1B
 *\*\               - SDIO_BUS_WIDTH_4B
 *\*\               - SDIO_BUS_WIDTH_8B
 *\*\          - HardwareClkCtrl:  
 *\*\               - SDIO_HARDWARE_CLKCTRL_DISABLE
 *\*\               - SDIO_HARDWARE_CLKCTRL_ENABLE 
 *\*\          - ClkDiv: Must be a value between 0x00 and 0x1FF.
 *\*\return none
 */
void SDIO_Init(SDIO_InitType* InitStruct)
{
    uint32_t tempReg;

    /* Enable SDIO_CLK edge configuration */
    SDIO->RESERVED1[1] = 0x0000000D;
    
    /* Get the SDIO CLKCTRL value */
    tempReg = SDIO->CLKCTRL;

    /* Clear DIV, BUSMODE, CLKBYP, PWRCFG, CLKEDGE, HWCLKEN bits */
    tempReg &= ~( SDIO_CLKCTRL_DIV      \
                | SDIO_CLKCTRL_BUSMODE  \
                | SDIO_CLKCTRL_CLKBYP   \
                | SDIO_CLKCTRL_PWRCFG   \
                | SDIO_CLKCTRL_CLKEDGE  \
                | SDIO_CLKCTRL_HWCLKEN  );

    /* Set DIV, BUSMODE, CLKBYP, PWRCFG, CLKEDGE, HWCLKEN bits */
    tempReg |= (  InitStruct->ClkDiv       \
                | InitStruct->ClkPwrSave   \
                | InitStruct->ClkBypass    \
                | InitStruct->BusWidth     \
                | InitStruct->ClkEdge      \
                | InitStruct->HardwareClkCtrl  );

    /* Write SDIO CLKCTRL */
    SDIO->CLKCTRL = tempReg;
}

/**
 *\*\name   SDIO_InitStruct.
 *\*\fun    Fills each InitStruct member with its default value.
 *\*\param  InitStruct pointer to an SDIO_InitType structure which will be initialized.
 *\*\return none
 */
void SDIO_InitStruct(SDIO_InitType* InitStruct)
{
    InitStruct->ClkDiv          = 0x00U;
    InitStruct->ClkEdge         = SDIO_CLK_EDGE_RISING;
    InitStruct->ClkBypass       = SDIO_CLK_BYPASS_DISABLE;
    InitStruct->ClkPwrSave      = SDIO_CLK_POWER_SAVE_DISABLE;
    InitStruct->BusWidth        = SDIO_BUS_WIDTH_1B;
    InitStruct->HardwareClkCtrl = SDIO_HARDWARE_CLKCTRL_DISABLE;
}

/**
 *\*\name   SDIO_EnableClock.
 *\*\fun    Enables or disables the SDIO Clock.
 *\*\param  Cmd new state of the SDIO Clock.
 *\*\           This parameter must be one of the following values:
 *\*\               - ENABLE 
 *\*\               - DISABLE
 *\*\return none
 */
void SDIO_EnableClock(FunctionalState Cmd)
{
    *(__IO uint32_t*)SDIO_CLKEN_BB = (uint32_t)Cmd;
}

/**
 *\*\name   SDIO_SetPower.
 *\*\fun    Sets the power status of the controller.
 *\*\param  PowerState new state of the Power state.
 *\*\           This parameter must be one of the following values:
 *\*\               - SDIO_POWER_CTRL_OFF 
 *\*\               - SDIO_POWER_CTRL_ON
 *\*\return none
 */
void SDIO_SetPower(uint32_t PowerState)
{
    uint32_t tempReg;

    /* Get SDIO_PWRCTRL register value and clear PWRCTRL bits */
    tempReg  = SDIO->PWRCTRL & (~SDIO_PWRCTRL_PWRCTRL);

    /* Set PWRCTRL bits withe new value */
    tempReg |= PowerState;

    /* Write SDIO_PWRCTRL register */
    SDIO->PWRCTRL = tempReg;
}

/**
 *\*\name   SDIO_GetPower.
 *\*\fun    Gets the power status of the controller.
 *\*\param  none
 *\*\return Current Power status,the value can be:
 *\*\           - SDIO_POWER_CTRL_OFF  
 *\*\           - SDIO_POWER_CTRL_UP
 *\*\           - SDIO_POWER_CTRL_ON   
 */
uint32_t SDIO_GetPower(void)
{
    return (SDIO->PWRCTRL & SDIO_PWRCTRL_PWRCTRL);
}


/**
 *\*\name   SDIO_ConfigInt.
 *\*\fun    Enables or disables the SDIO interrupts.
 *\*\param  Int specifies the SDIO interrupt sources to be enabled or disabled.
 *\*\           This parameter must be a value or combination of the following values:
 *\*\               - SDIO_INT_CCRCERR    
 *\*\               - SDIO_INT_DCRCERR    
 *\*\               - SDIO_INT_CMDTIMEOUT 
 *\*\               - SDIO_INT_DATTIMEOUT 
 *\*\               - SDIO_INT_TXURERR    
 *\*\               - SDIO_INT_RXORERR    
 *\*\               - SDIO_INT_CMDRESPRECV
 *\*\               - SDIO_INT_CMDSEND    
 *\*\               - SDIO_INT_DATEND     
 *\*\               - SDIO_INT_SBERR      
 *\*\               - SDIO_INT_DATBLKEND  
 *\*\               - SDIO_INT_CMDRUN     
 *\*\               - SDIO_INT_TXRUN      
 *\*\               - SDIO_INT_RXRUN      
 *\*\               - SDIO_INT_TFIFOE     
 *\*\               - SDIO_INT_TFIFOHE    
 *\*\               - SDIO_INT_TFIFOF     
 *\*\               - SDIO_INT_TDATVALID  
 *\*\               - SDIO_INT_RFIFOE     
 *\*\               - SDIO_INT_RFIFOHF    
 *\*\               - SDIO_INT_RFIFOF     
 *\*\               - SDIO_INT_RDATVALID  
 *\*\               - SDIO_INT_SDIOINT    
 *\*\param  Cmd new state of the specified SDIO interrupts.Must be one of one of the following values:
 *\*\               - ENABLE 
 *\*\               - DISABLE
 *\*\return none
 */
void SDIO_ConfigInt(uint32_t Int, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the SDIO interrupts */
        SDIO->INTEN |= Int;
    }
    else
    {
        /* Disable the SDIO interrupts */
        SDIO->INTEN &= ~Int;
    }
}

/**
 *\*\name   SDIO_DMACmd.
 *\*\fun    Enables or disables the SDIO DMA request.
 *\*\param  Cmd new state of the SDIO DMA request.
 *\*\           This parameter must be one of the following values: 
 *\*\               - ENABLE 
 *\*\               - DISABLE
 *\*\return none
 */
void SDIO_DMACmd(FunctionalState Cmd)
{
    *(__IO uint32_t*)SDIO_DMAEN_BB = (uint32_t)Cmd;
}

/**
 *\*\name   SDIO_SendCmd.
 *\*\fun    Initializes the SDIO Command according to the specified
 *\*\       parameters in the CmdInitStruct and send the command.
 *\*\param  CmdInitStruct pointer to a SDIO_CmdInitType structure.
 *\*\       The input parameters must be the following values:
 *\*\          - CmdArgument: Optional SDIO command argument.
 *\*\          - CmdIndex: SDIO command index, must be lower than 0x40.
 *\*\          - ResponseType:  
 *\*\               - SDIO_RESP_NO 
 *\*\               - SDIO_RESP_SHORT
 *\*\               - SDIO_RESP_LONG 
 *\*\          - WaitType:  
 *\*\               - SDIO_WAIT_NO  
 *\*\               - SDIO_WAIT_INT 
 *\*\               - SDIO_WAIT_PEND
 *\*\          - CPSMConfig:  
 *\*\               - SDIO_CPSM_DISABLE
 *\*\               - SDIO_CPSM_ENABLE  
 *\*\return none
 */
void SDIO_SendCmd(SDIO_CmdInitType* CmdInitStruct)
{
    uint32_t tempReg;

    /* Set the SDIO Argument value */
    SDIO->CMDARG = CmdInitStruct->CmdArgument;

    /* Get the SDIO CMDCTRL value */
    tempReg = SDIO->CMDCTRL;

    /* Clear CPSMEN, WDATEND, WINTREQ, CMDRESP, CMDIDX  bits */
    tempReg &= ~( SDIO_CMDCTRL_CPSMEN   \
                | SDIO_CMDCTRL_WDATEND  \
                | SDIO_CMDCTRL_WINTREQ  \
                | SDIO_CMDCTRL_CMDRESP  \
                | SDIO_CMDCTRL_CMDIDX   \
                | SDIO_CMDCTRL_SUSPEND  );
    
    /* Set CPSMEN, WDATEND, WINTREQ, CMDRESP, CMDIDX  bits with new value */
    tempReg |=    (CmdInitStruct->CmdIndex << SDIO_CMDCTRL_CMDIDX_OFFSET)     \
                | CmdInitStruct->ResponseType  \
                | CmdInitStruct->WaitType      \
                | CmdInitStruct->CPSMConfig;

    /* Write to SDIO CMDCTRL */
    SDIO->CMDCTRL = tempReg;
}

/**
 *\*\name   SDIO_InitCmdStruct.
 *\*\fun    Fills each CmdInitStruct member with its default value.
 *\*\param  CmdInitStruct pointer to a SDIO_CmdInitType structure.
 *\*\return none
 */
void SDIO_InitCmdStruct(SDIO_CmdInitType* CmdInitStruct)
{
    /* SDIO_CmdInitStruct members default value */
    CmdInitStruct->CmdArgument  = 0x00;
    CmdInitStruct->CmdIndex     = 0x00;
    CmdInitStruct->ResponseType = SDIO_RESP_NO;
    CmdInitStruct->WaitType     = SDIO_WAIT_NO;
    CmdInitStruct->CPSMConfig   = SDIO_CPSM_DISABLE;
}

/**
 *\*\name   SDIO_GetCmdResp.
 *\*\fun    Returns command index of last command for which response received.
 *\*\param  none
 *\*\return Command index of the last command response received
 */
uint8_t SDIO_GetCmdResp(void)
{
    return ((uint8_t)(SDIO->CMDRESP));
}

/**
 *\*\name   SDIO_GetResp.
 *\*\fun    Returns response received from the card for the last command.
 *\*\param  SDIO_RESP Specifies the SDIO response register. 
 *\*\       This parameter must be one of the following values:
 *\*\           - SDIO_RESPONSE_1
 *\*\           - SDIO_RESPONSE_2
 *\*\           - SDIO_RESPONSE_3
 *\*\           - SDIO_RESPONSE_4
 *\*\return The Corresponding response register value.
 */
uint32_t SDIO_GetResp(uint32_t SDIO_RESP)
{
    uint32_t temp;

    temp = (uint32_t)(&(SDIO->RESPONSE1)) + SDIO_RESP;

    return (*(__IO uint32_t*)temp);
}

/**
 *\*\name   SDIO_ConfigData.
 *\*\fun    Initializes the SDIO data path according to the specified
 *\*\       parameters in the DataInitStruct.
 *\*\param  DataInitStruct pointer to a SDIO_DataInitType structure.
 *\*\       The input parameters must be the following values:
 *\*\          - DatTimeout: data timeout period.
 *\*\          - DatLen: Number of data bytes to be transferred,
 *\*\                   must be a value between 0x0 and 0x01FFFFFF
 *\*\          - DatBlkSize: 
 *\*\               - SDIO_DATBLK_SIZE_1B    
 *\*\               - SDIO_DATBLK_SIZE_2B    
 *\*\               - SDIO_DATBLK_SIZE_4B    
 *\*\               - SDIO_DATBLK_SIZE_8B    
 *\*\               - SDIO_DATBLK_SIZE_16B   
 *\*\               - SDIO_DATBLK_SIZE_32B   
 *\*\               - SDIO_DATBLK_SIZE_64B   
 *\*\               - SDIO_DATBLK_SIZE_128B  
 *\*\               - SDIO_DATBLK_SIZE_256B  
 *\*\               - SDIO_DATBLK_SIZE_512B  
 *\*\               - SDIO_DATBLK_SIZE_1024B 
 *\*\               - SDIO_DATBLK_SIZE_2048B 
 *\*\               - SDIO_DATBLK_SIZE_4096B 
 *\*\               - SDIO_DATBLK_SIZE_8192B 
 *\*\               - SDIO_DATBLK_SIZE_16384B
 *\*\          - TransferDirection:  
 *\*\               - SDIO_TRANSDIR_TOCARD
 *\*\               - SDIO_TRANSDIR_TOSDIO
 *\*\          - TransferMode:  
 *\*\               - SDIO_TRANSMODE_BLOCK 
 *\*\               - SDIO_TRANSMODE_STREAM
 *\*\          - DPSMConfig:  
 *\*\               - SDIO_DPSM_DISABLE
 *\*\               - SDIO_DPSM_ENABLE 
 *\*\return none
 */
void SDIO_ConfigData(SDIO_DataInitType* DataInitStruct)
{
    uint32_t tempReg;

    /* Set the SDIO Data TimeOut value */
    SDIO->DTIMER = DataInitStruct->DatTimeout;

    /* Set the SDIO DataLength value */
    SDIO->DATLEN = DataInitStruct->DatLen;

    /* Get the SDIO DATCTRL value */
    tempReg = SDIO->DATCTRL;

    /* Clear DATEN, TRANSMOD, DATDIR, BLKSIZE and DMADIR bits */
    tempReg &= ~( SDIO_DATCTRL_DATEN
                | SDIO_DATCTRL_TRANSMOD
                | SDIO_DATCTRL_DATDIR
                | SDIO_DATCTRL_BLKSIZE
                | SDIO_DATCTRL_DMADIR  );
    
    /* Set DATEN, TRANSMOD, DATDIR and BLKSIZE bits with new value */
    tempReg |=    DataInitStruct->DatBlkSize 
                | DataInitStruct->TransferDirection
                | DataInitStruct->TransferMode 
                | DataInitStruct->DPSMConfig;
                   
    /* Set DMADIR bits if nessarry */
    if(SDIO_TRANSDIR_TOCARD == DataInitStruct->TransferDirection)
    {
        tempReg |= SDIO_DMA_DATA_TO_DEVICE;
    }              

    /* Write SDIO_DATCTRL */
    SDIO->DATCTRL = tempReg;
}

/**
 *\*\name   SDIO_InitDataStruct.
 *\*\fun    Fills each DataInitStruct member with its default value.
 *\*\param  DataInitStruct pointer to a SDIO_DataInitType structure.
 *\*\return none
 */
void SDIO_InitDataStruct(SDIO_DataInitType* SDIO_DataInitStruct)
{
    SDIO_DataInitStruct->DatTimeout        = 0xFFFFFFFF;
    SDIO_DataInitStruct->DatLen            = 0x00;
    SDIO_DataInitStruct->DatBlkSize        = SDIO_DATBLK_SIZE_1B;
    SDIO_DataInitStruct->TransferDirection = SDIO_TRANSDIR_TOCARD;
    SDIO_DataInitStruct->TransferMode      = SDIO_TRANSMODE_BLOCK;
    SDIO_DataInitStruct->DPSMConfig        = SDIO_DPSM_DISABLE;
}

/**
 *\*\name   SDIO_GetDataCountValue.
 *\*\fun    Returns number of remaining data bytes to be transferred.
 *\*\param  none
 *\*\return Number of remaining data bytes to be transferred.
 */
uint32_t SDIO_GetDataCountValue(void)
{
    return (SDIO->DATCOUNT);
}

/**
 *\*\name   SDIO_ReadData.
 *\*\fun    Read one data word from Rx DATFIFO.
 *\*\param  none
 *\*\return Data received.
 */
uint32_t SDIO_ReadData(void)
{
    return (SDIO->DATFIFO);
}

/**
 *\*\name   SDIO_WriteData.
 *\*\fun    Write one data word to Tx DATFIFO.
 *\*\param  Data 32-bit data word to write.
 *\*\return none
 */
void SDIO_WriteData(uint32_t Data)
{
    SDIO->DATFIFO = Data;
}

/**
 *\*\name   SDIO_GetFifoCounter.
 *\*\fun    Returns the number of words left to be written to or read from DATFIFO.
 *\*\param  none
 *\*\return Remaining number of words in the FIFO.
 */
uint32_t SDIO_GetFifoCounter(void)
{
    return (SDIO->FIFOCOUNT);
}

/**
 *\*\name   SDIO_EnableReadWait.
 *\*\fun    Enable the SD I/O Read Wait operation.
 *\*\param  Cmd new state of the read wait operation.
 *\*\           This parameter must be one of the following values: 
 *\*\               - ENABLE 
 *\*\               - DISABLE
 *\*\return none
 */
void SDIO_EnableReadWait(FunctionalState Cmd)
{
    *(__IO uint32_t*)SDIO_RWAITEN_BB = Cmd;
}

/**
 *\*\name   SDIO_EnableSdioReadWaitMode.
 *\*\fun    Sets one of the two options of inserting read wait interval.
 *\*\param  ReadWaitMode SD I/O Read Wait operation mode.
 *\*\           This parameter must be one of the following values:
 *\*\               - SDIO_RDWAIT_MODE_CLK 
 *\*\               - SDIO_RDWAIT_MODE_DAT2
 *\*\return none
 */
void SDIO_EnableReadWaitMode(uint32_t ReadWaitMode)
{
   *(__IO uint32_t*)SDIO_RWAITMOD_BB = ReadWaitMode;
}

/**
 *\*\name   SDIO_StartReadWait.
 *\*\fun    Start the SD I/O Read Wait operation when RWAITEN bit is set.
 *\*\param  none
 *\*\return none
 */
void SDIO_StartReadWait(void)
{
    *(__IO uint32_t*)SDIO_RWAITSTOP_BB = 0U;
}

/**
 *\*\name   SDIO_StopReadWait.
 *\*\fun    Stop the SD I/O Read Wait operation when RWAITEN bit is set.
 *\*\param  none
 *\*\return none
 */
void SDIO_StopReadWait(void)
{
    *(__IO uint32_t*)SDIO_RWAITSTOP_BB = 1U;
}

/**
 *\*\name   SDIO_EnableSdioOperation.
 *\*\fun    Enables the SD I/O Mode Operation.
 *\*\param  Cmd new state of the SD I/O Mode Operation.
 *\*\           This parameter must be one of the following values: 
 *\*\               - ENABLE 
 *\*\               - DISABLE
 *\*\return none
 */
void SDIO_EnableSdioOperation(FunctionalState Cmd)
{
    *(__IO uint32_t*)SDIO_SDIOEN_BB = Cmd;
}

/**
 *\*\name   SDIO_EnableSendSdioSuspend.
 *\*\fun    Enables the SD I/O Mode suspend command sending.
 *\*\param  Cmd new state of the SD I/O Mode suspend command sending.
 *\*\           This parameter must be one of the following values: 
 *\*\               - ENABLE 
 *\*\               - DISABLE
 *\*\return none
 */
void SDIO_EnableSendSdioSuspend(FunctionalState Cmd)
{
    *(__IO uint32_t*)SDIO_SUSPEND_BB = Cmd;
}

/**
 *\*\name   SDIO_EnableCommandCompletion.
 *\*\fun    Enables the command completion signal.
 *\*\param  Cmd new state of the command completion signal.
 *\*\           This parameter must be one of the following values: 
 *\*\               - ENABLE 
 *\*\               - DISABLE
 *\*\return none
 */
void SDIO_EnableCommandCompletion(FunctionalState Cmd)
{
    *(__IO uint32_t*)SDIO_ENCMDF_BB = Cmd;
}

/**
 *\*\name   SDIO_GetFlag.
 *\*\fun    Checks whether the specified SDIO flag is set or not.
 *\*\param  Flag specifies the flag to check.
 *\*\           This parameter must be one of the following values:
 *\*\               - SDIO_FLAG_CCRCERR    
 *\*\               - SDIO_FLAG_DCRCERR    
 *\*\               - SDIO_FLAG_CMDTIMEOUT 
 *\*\               - SDIO_FLAG_DATTIMEOUT 
 *\*\               - SDIO_FLAG_TXURERR    
 *\*\               - SDIO_FLAG_RXORERR    
 *\*\               - SDIO_FLAG_CMDRESPRECV
 *\*\               - SDIO_FLAG_CMDSEND    
 *\*\               - SDIO_FLAG_DATEND     
 *\*\               - SDIO_FLAG_SBERR      
 *\*\               - SDIO_FLAG_DATBLKEND  
 *\*\               - SDIO_FLAG_CMDRUN     
 *\*\               - SDIO_FLAG_TXRUN      
 *\*\               - SDIO_FLAG_RXRUN      
 *\*\               - SDIO_FLAG_TFIFOE     
 *\*\               - SDIO_FLAG_TFIFOHE    
 *\*\               - SDIO_FLAG_TFIFOF     
 *\*\               - SDIO_FLAG_TDATVALID  
 *\*\               - SDIO_FLAG_RFIFOE     
 *\*\               - SDIO_FLAG_RFIFOHF    
 *\*\               - SDIO_FLAG_RFIFOF     
 *\*\               - SDIO_FLAG_RDATVALID  
 *\*\               - SDIO_FLAG_SDIOINT    
 *\*\return FlagStatus:
 *\*\           - SET
 *\*\           - RESET
 */
FlagStatus SDIO_GetFlag(uint32_t Flag)
{
    if ((SDIO->STS & Flag) != (uint32_t)RESET)
    {
        return (SET);
    }
    else
    {
        return (RESET);
    }
}

/**
 *\*\name   SDIO_ClrFlag.
 *\*\fun    Clears the SDIO's pending flags.
 *\*\param  FlagClr specifies the flag to clear.
 *\*\           This parameter must be one of the following values:
 *\*\               - SDIO_FLAG_CCRCERR    
 *\*\               - SDIO_FLAG_DCRCERR    
 *\*\               - SDIO_FLAG_CMDTIMEOUT 
 *\*\               - SDIO_FLAG_DATTIMEOUT 
 *\*\               - SDIO_FLAG_TXURERR    
 *\*\               - SDIO_FLAG_RXORERR    
 *\*\               - SDIO_FLAG_CMDRESPRECV
 *\*\               - SDIO_FLAG_CMDSEND    
 *\*\               - SDIO_FLAG_DATEND     
 *\*\               - SDIO_FLAG_SBERR      
 *\*\               - SDIO_FLAG_DATBLKEND  
 *\*\               - SDIO_FLAG_SDIOINT    
 *\*\return none
 */
void SDIO_ClrFlag(uint32_t FlagClr)
{
    SDIO->INTCLR = FlagClr;
}

/**
 *\*\name   SDIO_GetIntStatus.
 *\*\fun    Checks whether the specified SDIO interrupt has occurred or not.
 *\*\param  Int specifies the SDIO interrupt source to check.
 *\*\           This parameter must be one of the following values:
 *\*\               - SDIO_INT_CCRCERR    
 *\*\               - SDIO_INT_DCRCERR    
 *\*\               - SDIO_INT_CMDTIMEOUT 
 *\*\               - SDIO_INT_DATTIMEOUT 
 *\*\               - SDIO_INT_TXURERR    
 *\*\               - SDIO_INT_RXORERR    
 *\*\               - SDIO_INT_CMDRESPRECV
 *\*\               - SDIO_INT_CMDSEND    
 *\*\               - SDIO_INT_DATEND     
 *\*\               - SDIO_INT_SBERR      
 *\*\               - SDIO_INT_DATBLKEND  
 *\*\               - SDIO_INT_CMDRUN     
 *\*\               - SDIO_INT_TXRUN      
 *\*\               - SDIO_INT_RXRUN      
 *\*\               - SDIO_INT_TFIFOE     
 *\*\               - SDIO_INT_TFIFOHE    
 *\*\               - SDIO_INT_TFIFOF     
 *\*\               - SDIO_INT_TDATVALID  
 *\*\               - SDIO_INT_RFIFOE     
 *\*\               - SDIO_INT_RFIFOHF    
 *\*\               - SDIO_INT_RFIFOF     
 *\*\               - SDIO_INT_RDATVALID  
 *\*\               - SDIO_INT_SDIOINT    
 *\*\return INTStatus:
 *\*\           - SET
 *\*\           - RESET
 */
INTStatus SDIO_GetIntStatus(uint32_t Int)
{
    /* Check whether the specified interrupt is enable or not. */
    if((SDIO->INTEN & Int) != Int )
    {
        return (RESET);
    }

    /* Check whether the specified interrupt flag is set or not. */
    if((SDIO->STS & Int) != Int )
    {
        return RESET;
    }

    return SET;
}

/**
 *\*\name   SDIO_CmdShortResponse1.
 *\*\fun    Send command with argument and check R1 response with timeout.
 *\*\param  Cmd specifies the command index to be sent.
 *\*\param  Arg specifies the command argument.
 *\*\param  timeout timeout value for response, can not be 0.
 *\*\return SDIO error state
 */
uint32_t SDIO_CmdShortResponse1(uint8_t Cmd, uint32_t Arg, uint32_t timeout)
{
    SDIO_CmdInitType  CmdPara;

    /* Send command */
    CmdPara.CmdArgument     = Arg;
    CmdPara.CmdIndex        = Cmd;
    CmdPara.ResponseType    = SDIO_RESP_SHORT;
    CmdPara.WaitType        = SDIO_WAIT_NO;
    CmdPara.CPSMConfig      = SDIO_CPSM_ENABLE;
    SDIO_SendCmd(&CmdPara);

    /* Check for error conditions */
    return (SDIO_GetCmdResp1(Cmd, timeout));
}

/**
 *\*\name   SDIO_CmdShortResponse3.
 *\*\fun    Send command with argument and check R3 response.
 *\*\param  Cmd specifies the command index to be sent.
 *\*\param  Arg specifies the command argument.
 *\*\return SDIO error state
 */
uint32_t SDIO_CmdShortResponse3(uint8_t Cmd, uint32_t Arg)
{
    SDIO_CmdInitType  CmdPara;

    /* Send command */
    CmdPara.CmdArgument     = Arg;
    CmdPara.CmdIndex        = Cmd;
    CmdPara.ResponseType    = SDIO_RESP_SHORT;
    CmdPara.WaitType        = SDIO_WAIT_NO;
    CmdPara.CPSMConfig      = SDIO_CPSM_ENABLE;
    SDIO_SendCmd(&CmdPara);

    /* Check for error conditions */
    return (SDIO_GetCmdResp3());
}

/**
 *\*\name   SDIO_CmdLongResponse2.
 *\*\fun    Send command with argument and check the R2 response.
 *\*\param  Cmd specifies the command index to be sent.
 *\*\param  Arg specifies the command argument.
 *\*\return SDIO error state
 */
uint32_t SDIO_CmdLongResponse2(uint8_t Cmd, uint32_t Arg)
{
    SDIO_CmdInitType  CmdPara;

    /* Send command */
    CmdPara.CmdArgument     = Arg;
    CmdPara.CmdIndex        = Cmd;
    CmdPara.ResponseType    = SDIO_RESP_LONG;
    CmdPara.WaitType        = SDIO_WAIT_NO;
    CmdPara.CPSMConfig      = SDIO_CPSM_ENABLE;
    SDIO_SendCmd(&CmdPara);

    /* Check for error conditions */
    return (SDIO_GetCmdResp2());
}

/**
 *\*\name   SDIO_CmdBlockLength.
 *\*\fun    Send the Data Block Length command and check the response
 *\*\param  BlockSize specifies the SDIO data block length.
 *\*\return SDIO error state
 */
uint32_t SDIO_CmdBlockLength(uint32_t BlockSize)
{
    return (SDIO_CmdShortResponse1(SDMMC_CMD_SET_BLOCKLEN,BlockSize,SDMMC_CMDTIMEOUT));
}

/**
 *\*\name   SDIO_CmdBlockCount.
 *\*\fun    Send the Set Data Block Count command and check the response
 *\*\param  BlockCnt specifies the SDIO block count.
 *\*\return SDIO error state
 */
uint32_t SDIO_CmdBlockCount(uint32_t BlockCnt)
{
    return (SDIO_CmdShortResponse1(SDMMC_CMD_SET_BLOCK_COUNT,BlockCnt,SDMMC_CMDTIMEOUT));
}

/**
 *\*\name   SDIO_CmdReadSingleBlock.
 *\*\fun    Send the Read Single Block command and check the response
 *\*\param  ReadAdd specifies the start address for reading.
 *\*\return SDIO error state
 */
uint32_t SDIO_CmdReadSingleBlock(uint32_t ReadAdd)
{
    return (SDIO_CmdShortResponse1(SDMMC_CMD_READ_SINGLE_BLOCK,ReadAdd,SDMMC_CMDTIMEOUT));
}

/**
 *\*\name   SDIO_CmdReadMultiBlock.
 *\*\fun    Send the Read Multi Block command and check the response
 *\*\param  ReadAdd specifies the start address for reading.
 *\*\return SDIO error state
 */
uint32_t SDIO_CmdReadMultiBlock(uint32_t ReadAdd)
{
    return (SDIO_CmdShortResponse1(SDMMC_CMD_READ_MULT_BLOCK,ReadAdd,SDMMC_CMDTIMEOUT));
}

/**
 *\*\name   SDIO_CmdWriteSingleBlock.
 *\*\fun    Send the Write Single Block command and check the response
 *\*\param  WriteAdd specifies the start address for writing.
 *\*\return SDIO error state
 */
uint32_t SDIO_CmdWriteSingleBlock(uint32_t WriteAdd)
{
    return (SDIO_CmdShortResponse1(SDMMC_CMD_WRITE_SINGLE_BLOCK,WriteAdd,SDMMC_CMDTIMEOUT));
}

/**
 *\*\name   SDIO_CmdWriteMultiBlock.
 *\*\fun    Send the Write Multi Block command and check the response
 *\*\param  WriteAdd specifies the start address for writing.
 *\*\return SDIO error state
 */
uint32_t SDIO_CmdWriteMultiBlock(uint32_t WriteAdd)
{
    return (SDIO_CmdShortResponse1(SDMMC_CMD_WRITE_MULT_BLOCK,WriteAdd,SDMMC_CMDTIMEOUT));
}

/**
 *\*\name   SDIO_CmdSDEraseStartAdd.
 *\*\fun    Send the Start Address Erase command for SD and check the response
 *\*\param  StartAdd specifies the start address for erasing.
 *\*\return SDIO error state
 */
uint32_t SDIO_CmdSDEraseStartAdd(uint32_t StartAdd)
{
    return (SDIO_CmdShortResponse1(SDMMC_CMD_SD_ERASE_GRP_START,StartAdd,SDMMC_CMDTIMEOUT));
}

/**
 *\*\name   SDIO_CmdSDEraseEndAdd.
 *\*\fun    Send the End Address Erase command for SD and check the response
 *\*\param  EndAdd specifies the end address for erasing.
 *\*\return SDIO error state
 */
uint32_t SDIO_CmdSDEraseEndAdd(uint32_t EndAdd)
{
    return (SDIO_CmdShortResponse1(SDMMC_CMD_SD_ERASE_GRP_END,EndAdd,SDMMC_CMDTIMEOUT));
}

/**
 *\*\name   SDIO_CmdEraseStartAdd.
 *\*\fun    Send the Start Address Erase command and check the response
 *\*\param  StartAdd specifies the start address for erasing.
 *\*\return SDIO error state
 */
uint32_t SDIO_CmdEraseStartAdd(uint32_t StartAdd)
{
    return (SDIO_CmdShortResponse1(SDMMC_CMD_ERASE_GRP_START,StartAdd,SDMMC_CMDTIMEOUT));
}

/**
 *\*\name   SDIO_CmdEraseEndAdd.
 *\*\fun    Send the End Address Erase command and check the response
 *\*\param  StartAdd specifies the start address for erasing.
 *\*\return SDIO error state
 */
uint32_t SDIO_CmdEraseEndAdd(uint32_t EndAdd)
{
    return (SDIO_CmdShortResponse1(SDMMC_CMD_ERASE_GRP_END,EndAdd,SDMMC_CMDTIMEOUT));
}

/**
 *\*\name   SDIO_CmdErase.
 *\*\fun    Send the Erase command and check the response
 *\*\param  none
 *\*\return SDIO error state
 */
uint32_t SDIO_CmdErase(void)
{
    return (SDIO_CmdShortResponse1(SDMMC_CMD_ERASE,0U,SDMMC_MAXERASETIMEOUT));
}

/**
 *\*\name   SDIO_CmdLockUnlock.
 *\*\fun    Send the lock/unlock command and check the response
 *\*\param  none
 *\*\return SDIO error state
 */
uint32_t SDIO_CmdLockUnlock(uint32_t arg)
{
    return (SDIO_CmdShortResponse1(SDMMC_CMD_LOCK_UNLOCK,arg,SDMMC_CMDTIMEOUT));
}

/**
 *\*\name   SDIO_CmdStopTransfer.
 *\*\fun    Send the Stop Transfer command and check the response.
 *\*\param  none
 *\*\return SDIO error state
 */
uint32_t SDIO_CmdStopTransfer(void)
{
    return (SDIO_CmdShortResponse1(SDMMC_CMD_STOP_TRANSMISSION,0U,SDMMC_STOPTRANSFERTIMEOUT));
}

/**
 *\*\name   SDIO_CmdSelDesel.
 *\*\fun    Send the Select Deselect command and check the response.
 *\*\param  RCA: Address of the card to be selected
 *\*\return SDIO error state
 */
uint32_t SDIO_CmdSelDesel(uint16_t RCA)
{
    return (SDIO_CmdShortResponse1(SDMMC_CMD_SEL_DESEL_CARD,((uint32_t)RCA << 16U),SDMMC_CMDTIMEOUT));
}

/**
 *\*\name   SDIO_CmdGoIdleState.
 *\*\fun    Send the Go Idle State command and check the response.
 *\*\param  none
 *\*\return SDIO error state
 */
uint32_t SDIO_CmdGoIdleState(void)
{
    SDIO_CmdInitType  CmdPara;

    CmdPara.CmdArgument     = 0U;
    CmdPara.CmdIndex        = SDMMC_CMD_GO_IDLE_STATE;
    CmdPara.ResponseType    = SDIO_RESP_NO;
    CmdPara.WaitType        = SDIO_WAIT_NO;
    CmdPara.CPSMConfig      = SDIO_CPSM_ENABLE;
    SDIO_SendCmd(&CmdPara);

    /* Check for error conditions */
    return (SDIO_GetCmdError());
}

/**
 *\*\name   SDIO_CmdOperCond.
 *\*\fun    Send the Operating Condition command and check the response.
 *\*\param  none
 *\*\return SDIO error state
 */
uint32_t SDIO_CmdOperCond(void)
{
    SDIO_CmdInitType  CmdPara;

    /* Send CMD8 to verify SD card interface operating condition */
    /* Argument: - [31:12]: Reserved (shall be set to '0')
    - [11:8]: Supply Voltage (VHS) 0x1 (Range: 2.7-3.6 V)
    - [7:0]: Check Pattern (recommended 0xAA) */
    /* CMD Response: R7 */
    CmdPara.CmdArgument     = SDMMC_CHECK_PATTERN;
    CmdPara.CmdIndex        = SDMMC_CMD_SEND_IF_COND;
    CmdPara.ResponseType    = SDIO_RESP_SHORT;
    CmdPara.WaitType        = SDIO_WAIT_NO;
    CmdPara.CPSMConfig      = SDIO_CPSM_ENABLE;
    SDIO_SendCmd(&CmdPara);

    /* Check for error conditions */
    return (SDIO_GetCmdResp7());
}

/**
 *\*\name   SDIO_CmdAppCommand.
 *\*\fun    Send the Application command to verify that that the next command 
 *\*\       is an application specific com-mand rather than a standard command
 *\*\       and check the response.
 *\*\param  Arg: Command Argument 
 *\*\return SDIO error state
 */
uint32_t SDIO_CmdAppCommand(uint32_t Arg)
{
    return (SDIO_CmdShortResponse1(SDMMC_CMD_APP_CMD,Arg,SDMMC_CMDTIMEOUT));
}

/**
 *\*\name   SDIO_CmdAppOperCommand.
 *\*\fun    Send the command asking the accessed card to send its operating 
 *\*\       condition register (OCR)
 *\*\param  Arg: Command Argument 
 *\*\return SDIO error state
 */
uint32_t SDIO_CmdAppOperCommand(uint32_t Arg)
{
    return (SDIO_CmdShortResponse3(SDMMC_CMD_SD_APP_OP_COND,Arg));
}

/**
 *\*\name   SDIO_CmdBusWidth.
 *\*\fun    Send the Bus Width command and check the response.
 *\*\param  BusWidth: Bus width 
 *\*\return SDIO error state
 */
uint32_t SDIO_CmdBusWidth(uint32_t BusWidth)
{
    return (SDIO_CmdShortResponse1(SDMMC_CMD_APP_SD_SET_BUSWIDTH,BusWidth,SDMMC_CMDTIMEOUT));
}

/**
 *\*\name   SDIO_CmdSendSCR.
 *\*\fun    Send the Send SCR command and check the response.
 *\*\param  none
 *\*\return SDIO error state
 */
uint32_t SDIO_CmdSendSCR(void)
{
    return (SDIO_CmdShortResponse1(SDMMC_CMD_SD_APP_SEND_SCR,0U,SDMMC_CMDTIMEOUT));
}

/**
 *\*\name   SDIO_CmdAllSendCID.
 *\*\fun    Send the Send all CID command and check the response.
 *\*\param  none
 *\*\return SDIO error state
 */
uint32_t SDIO_CmdAllSendCID(void)
{
    return (SDIO_CmdLongResponse2(SDMMC_CMD_ALL_SEND_CID,0U));
}

/**
 *\*\name   SDIO_CmdSendCID.
 *\*\fun    Send the Send CID command and check the response.
 *\*\param  RCA: Card RCA 
 *\*\return SDIO error state
 */
uint32_t SDIO_CmdSendCID(uint16_t RCA)
{
    return (SDIO_CmdLongResponse2(SDMMC_CMD_SEND_CID,((uint32_t)RCA << 16U)));
}

/**
 *\*\name   SDIO_CmdSendCSD.
 *\*\fun    Send the Send CSD command and check the response.
 *\*\param  RCA: Card RCA 
 *\*\return SDIO error state
 */
uint32_t SDIO_CmdSendCSD(uint16_t RCA)
{
    return (SDIO_CmdLongResponse2(SDMMC_CMD_SEND_CSD,((uint32_t)RCA << 16U)));
}

/**
 *\*\name   SDIO_CmdSetRelAdd.
 *\*\fun    Send the Set Relative Address command.
 *\*\param  pRCA: pointer to the Card RCA 
 *\*\return SDIO error state
 */
uint32_t SDIO_CmdSetRelAdd(uint16_t *pRCA)
{
    SDIO_CmdInitType  CmdPara;

    /* Send CMD3 SD_CMD_SET_REL_ADDR */
    CmdPara.CmdArgument     = 0U;
    CmdPara.CmdIndex        = SDMMC_CMD_SET_REL_ADDR;
    CmdPara.ResponseType    = SDIO_RESP_SHORT;
    CmdPara.WaitType        = SDIO_WAIT_NO;
    CmdPara.CPSMConfig      = SDIO_CPSM_ENABLE;
    SDIO_SendCmd(&CmdPara);

    /* Check for error conditions */
    return (SDIO_GetCmdResp6(SDMMC_CMD_SET_REL_ADDR,pRCA));
}

/**
 *\*\name   SDIO_CmdSetRelAddMmc.
 *\*\fun    Send the Set Relative Address command to MMC card (not SD card).
 *\*\param  RCA: Card RCA 
 *\*\return SDIO error state
 */
uint32_t SDIO_CmdSetRelAddMmc(uint16_t RCA)
{
    return (SDIO_CmdShortResponse1(SDMMC_CMD_SET_REL_ADDR,((uint32_t)RCA << 16U),SDMMC_CMDTIMEOUT));
}

/**
 *\*\name   SDIO_CmdSendStatus.
 *\*\fun    Send the Status command and check the response.
 *\*\param  Arg: command argument
 *\*\return SDIO error state
 */
uint32_t SDIO_CmdSendStatus(uint32_t Arg)
{
    return (SDIO_CmdShortResponse1(SDMMC_CMD_SEND_STATUS,Arg,SDMMC_CMDTIMEOUT));
}

/**
 *\*\name   SDIO_CmdStatusRegister.
 *\*\fun     Send the Status register command and check the response.
 *\*\param  none
 *\*\return SDIO error state
 */
uint32_t SDIO_CmdStatusRegister(void)
{
    return (SDIO_CmdShortResponse1(SDMMC_CMD_SD_APP_STATUS,0U,SDMMC_CMDTIMEOUT));
}

/**
 *\*\name   SDIO_CmdOpCondition.
 *\*\fun    Sends host capacity support information and activates the card's 
 *\*\       initialization process by send SDMMC_CMD_SEND_OP_COND command.
 *\*\param  Arg: command argument
 *\*\return SDIO error state
 */
uint32_t SDIO_CmdOpCondition(uint32_t Arg)
{
    return (SDIO_CmdShortResponse3(SDMMC_CMD_SEND_OP_COND,Arg));
}

/**
 *\*\name   SDIO_CmdSwitch.
 *\*\fun    Checks switchable function and switch card function. SDMMC_CMD_HS_SWITCH command
 *\*\param  Arg: command argument
 *\*\return SDIO error state
 */
uint32_t SDIO_CmdSwitch(uint32_t Arg)
{
    return (SDIO_CmdShortResponse1(SDMMC_CMD_HS_SWITCH,Arg,SDMMC_CMDTIMEOUT));
}

/**
 *\*\name   SDIO_CmdSendEXTCSD.
 *\*\fun    Send the Send EXT_CSD command and check the response.
 *\*\param  Arg: command argument
 *\*\return SDIO error state
 */
uint32_t SDIO_CmdSendEXTCSD(uint32_t Arg)
{
    return (SDIO_CmdShortResponse1(SDMMC_CMD_HS_SEND_EXT_CSD,Arg,SDMMC_CMDTIMEOUT));
}

/**
 *\*\name   SDIO_GetCmdResp1.
 *\*\fun    Checks for error conditions for R1 response.
 *\*\param  Cmd: The sent command index  
 *\*\param  Timeout: timeout value， can not be 0.
 *\*\return SDIO error state
 */
uint32_t SDIO_GetCmdResp1(uint8_t Cmd, uint32_t Timeout)
{
    uint32_t response_r1;
    uint32_t sts_reg;
    uint32_t timeout;
  
    /* 8 is the number of required instructions cycles for the below loop statement.
    The Timeout is expressed in ms */
    timeout = Timeout * (SystemCoreClock / 8U /1000U);
  
    while(1)
    {
        if(0U == timeout)
        {
            return SDMMC_ERROR_TIMEOUT;
        }
        else
        {
            timeout--;
        }

        sts_reg = SDIO->STS;

        if(sts_reg & SDIO_FLAG_CMDRUN)
        {
            continue;
        }

        if(sts_reg & (SDIO_FLAG_CCRCERR | SDIO_FLAG_CMDRESPRECV | SDIO_FLAG_CMDTIMEOUT))
        {
            break;
        }
    }
    
    if(SDIO_GetFlag(SDIO_FLAG_CMDTIMEOUT))
    {
        SDIO_ClrFlag(SDIO_FLAG_CMDTIMEOUT);
        return SDMMC_ERROR_CMD_RSP_TIMEOUT;
    }
    else if(SDIO_GetFlag(SDIO_FLAG_CCRCERR))
    {
        SDIO_ClrFlag(SDIO_FLAG_CCRCERR);
        
        return SDMMC_ERROR_CMD_CRC_FAIL;
    }
    else
    {
        /* Nothing to do */
    }
    
    /* Clear all the static flags */
    SDIO_ClrFlag(SDIO_STATIC_CMD_FLAGS);
    
    /* Check response received is of desired command */
    if(SDIO_GetCmdResp() != Cmd)
    {
        return SDMMC_ERROR_CMD_CRC_FAIL;
    }
    
    /* We have received response, retrieve it for analysis  */
    response_r1 = SDIO_GetResp(SDIO_RESPONSE_1);
    
    if((response_r1 & SDMMC_R1_ERRORBITS) == SDMMC_ALLZERO)
    {
        return SDMMC_ERROR_NONE;
    }
    else if((response_r1 & SDMMC_R1_ADDR_OUT_OF_RANGE) == SDMMC_R1_ADDR_OUT_OF_RANGE)
    {
        return SDMMC_ERROR_ADDR_OUT_OF_RANGE;
    }
    else if((response_r1 & SDMMC_R1_ADDR_MISALIGNED) == SDMMC_R1_ADDR_MISALIGNED)
    {
        return SDMMC_ERROR_ADDR_MISALIGNED;
    }
    else if((response_r1 & SDMMC_R1_BLOCK_LEN_ERR) == SDMMC_R1_BLOCK_LEN_ERR)
    {
        return SDMMC_ERROR_BLOCK_LEN_ERR;
    }
    else if((response_r1 & SDMMC_R1_ERASE_SEQ_ERR) == SDMMC_R1_ERASE_SEQ_ERR)
    {
        return SDMMC_ERROR_ERASE_SEQ_ERR;
    }
    else if((response_r1 & SDMMC_R1_BAD_ERASE_PARAM) == SDMMC_R1_BAD_ERASE_PARAM)
    {
        return SDMMC_ERROR_BAD_ERASE_PARAM;
    }
    else if((response_r1 & SDMMC_R1_WRITE_PROT_VIOLATION) == SDMMC_R1_WRITE_PROT_VIOLATION)
    {
        return SDMMC_ERROR_WRITE_PROT_VIOLATION;
    }
    else if((response_r1 & SDMMC_R1_LOCK_UNLOCK_FAILED) == SDMMC_R1_LOCK_UNLOCK_FAILED)
    {
        return SDMMC_ERROR_LOCK_UNLOCK_FAILED;
    }
    else if((response_r1 & SDMMC_R1_COM_CRC_FAILED) == SDMMC_R1_COM_CRC_FAILED)
    {
        return SDMMC_ERROR_COM_CRC_FAILED;
    }
    else if((response_r1 & SDMMC_R1_ILLEGAL_CMD) == SDMMC_R1_ILLEGAL_CMD)
    {
        return SDMMC_ERROR_ILLEGAL_CMD;
    }
    else if((response_r1 & SDMMC_R1_CARD_ECC_FAILED) == SDMMC_R1_CARD_ECC_FAILED)
    {
        return SDMMC_ERROR_CARD_ECC_FAILED;
    }
    else if((response_r1 & SDMMC_R1_CC_ERROR) == SDMMC_R1_CC_ERROR)
    {
        return SDMMC_ERROR_CC_ERROR;
    }
    else if((response_r1 & SDMMC_R1_STREAM_READ_UNDERRUN) == SDMMC_R1_STREAM_READ_UNDERRUN)
    {
        return SDMMC_ERROR_STREAM_READ_UNDERRUN;
    }
    else if((response_r1 & SDMMC_R1_STREAM_WRITE_OVERRUN) == SDMMC_R1_STREAM_WRITE_OVERRUN)
    {
        return SDMMC_ERROR_STREAM_WRITE_OVERRUN;
    }
    else if((response_r1 & SDMMC_R1_CID_CSD_OVERWRITE) == SDMMC_R1_CID_CSD_OVERWRITE)
    {
        return SDMMC_ERROR_CID_CSD_OVERWRITE;
    }
    else if((response_r1 & SDMMC_R1_WP_ERASE_SKIP) == SDMMC_R1_WP_ERASE_SKIP)
    {
        return SDMMC_ERROR_WP_ERASE_SKIP;
    }
    else if((response_r1 & SDMMC_R1_CARD_ECC_DISABLED) == SDMMC_R1_CARD_ECC_DISABLED)
    {
        return SDMMC_ERROR_CARD_ECC_DISABLED;
    }
    else if((response_r1 & SDMMC_R1_ERASE_RESET) == SDMMC_R1_ERASE_RESET)
    {
        return SDMMC_ERROR_ERASE_RESET;
    }
    else if((response_r1 & SDMMC_R1_AKE_SEQ_ERROR) == SDMMC_R1_AKE_SEQ_ERROR)
    {
        return SDMMC_ERROR_AKE_SEQ_ERROR;
    }
    else
    {
        return SDMMC_ERROR_GENERAL_UNKNOWN_ERROR;
    }
}

/**
 *\*\name   SDIO_GetCmdResp2.
 *\*\fun    Checks for error conditions for R2 (CID or CSD) response.
 *\*\param  none
 *\*\return SDIO error state
 */
uint32_t SDIO_GetCmdResp2(void)
{
    uint32_t sts_reg;
    uint32_t timeout;
  
    /* 8 is the number of required instructions cycles for the below loop statement.
    The SDMMC_CMDTIMEOUT is expressed in ms */
    timeout = SDMMC_CMDTIMEOUT * (SystemCoreClock / 8U /1000U);
  
    while(1)
    {
        if(0U == timeout)
        {
            return SDMMC_ERROR_TIMEOUT;
        }
        else
        {
            timeout--;
        }

        sts_reg = SDIO->STS;

        if(sts_reg & SDIO_FLAG_CMDRUN)
        {
            continue;
        }

        if(sts_reg & (SDIO_FLAG_CCRCERR | SDIO_FLAG_CMDRESPRECV | SDIO_FLAG_CMDTIMEOUT))
        {
            break;
        }
    }
   
    if (SDIO_GetFlag(SDIO_FLAG_CMDTIMEOUT))
    {
        SDIO_ClrFlag(SDIO_FLAG_CMDTIMEOUT);
        return SDMMC_ERROR_CMD_RSP_TIMEOUT;
    }
    else if (SDIO_GetFlag(SDIO_FLAG_CCRCERR))
    {
        SDIO_ClrFlag(SDIO_FLAG_CCRCERR);
        return SDMMC_ERROR_CMD_CRC_FAIL;
    }
    else
    {
        /* No error flag set */
        /* Clear all the static flags */
        SDIO_ClrFlag(SDIO_STATIC_CMD_FLAGS);
    }

    return SDMMC_ERROR_NONE;
}

/**
 *\*\name   SDIO_GetCmdResp3.
 *\*\fun    Checks for error conditions for R3 (OCR) response.
 *\*\param  none
 *\*\return SDIO error state
 */
uint32_t SDIO_GetCmdResp3(void)
{
    uint32_t sts_reg;
    uint32_t timeout;
  
    /* 8 is the number of required instructions cycles for the below loop statement.
    The SDMMC_CMDTIMEOUT is expressed in ms */
    timeout = SDMMC_CMDTIMEOUT * (SystemCoreClock / 8U /1000U);

    while(1)
    {
        if(0U == timeout)
        {
            return SDMMC_ERROR_TIMEOUT;
        }
        else
        {
            timeout--;
        }

        sts_reg = SDIO->STS;

        if(sts_reg & SDIO_FLAG_CMDRUN)
        {
            continue;
        }

        if(sts_reg & (SDIO_FLAG_CCRCERR | SDIO_FLAG_CMDRESPRECV | SDIO_FLAG_CMDTIMEOUT))
        {
            break;
        }
    }
    
    if(SDIO_GetFlag(SDIO_FLAG_CMDTIMEOUT))
    {
        SDIO_ClrFlag(SDIO_FLAG_CMDTIMEOUT);
        return (SDMMC_ERROR_CMD_RSP_TIMEOUT);
    }
    else
    {  
        /* Clear all the static flags */
        SDIO_ClrFlag(SDIO_STATIC_CMD_FLAGS);
    }

    return (SDMMC_ERROR_NONE);
}

/**
 *\*\name   SDIO_GetCmdResp6
 *\*\fun    Checks for error conditions for R6 (RCA) response.
 *\*\param  Cmd: The sent command index  
 *\*\param  pRCA: Pointer to the variable that will contain the SD card relative address RCA   
 *\*\return SDIO error state
 */
uint32_t SDIO_GetCmdResp6(uint8_t Cmd, uint16_t *pRCA)
{
    uint32_t response_r1;
    uint32_t sts_reg;
    uint32_t timeout;
  
    /* 8 is the number of required instructions cycles for the below loop statement.
    The SDMMC_CMDTIMEOUT is expressed in ms */
    timeout = SDMMC_CMDTIMEOUT * (SystemCoreClock / 8U /1000U);
  
    while(1)
    {
        if(0U == timeout)
        {
            return SDMMC_ERROR_TIMEOUT;
        }
        else
        {
            timeout--;
        }

        sts_reg = SDIO->STS;

        if(sts_reg & SDIO_FLAG_CMDRUN)
        {
            continue;
        }

        if(sts_reg & (SDIO_FLAG_CCRCERR | SDIO_FLAG_CMDRESPRECV | SDIO_FLAG_CMDTIMEOUT))
        {
            break;
        }
    }
    
    if(SDIO_GetFlag(SDIO_FLAG_CMDTIMEOUT))
    {
        SDIO_ClrFlag(SDIO_FLAG_CMDTIMEOUT);
        return SDMMC_ERROR_CMD_RSP_TIMEOUT;
    }
    else if(SDIO_GetFlag(SDIO_FLAG_CCRCERR))
    {
        SDIO_ClrFlag(SDIO_FLAG_CCRCERR);
        
        return SDMMC_ERROR_CMD_CRC_FAIL;
    }
    else
    {
        /* Nothing to do */
    }

    /* Check response received is of desired command */
    if(SDIO_GetCmdResp() != Cmd)
    {
        return SDMMC_ERROR_CMD_CRC_FAIL;
    }
    
    /* Clear all the static flags */
    SDIO_ClrFlag(SDIO_STATIC_CMD_FLAGS);

    /* We have received response, retrieve it for analysis  */
    response_r1 = SDIO_GetResp(SDIO_RESPONSE_1);
    
    if((response_r1 & SDMMC_R6_ILLEGAL_CMD) == SDMMC_R6_ILLEGAL_CMD)
    {
        return (SDMMC_ERROR_ILLEGAL_CMD);
    }
    else if((response_r1 & SDMMC_R6_COM_CRC_FAILED) == SDMMC_R6_COM_CRC_FAILED)
    {
        return (SDMMC_ERROR_COM_CRC_FAILED);
    }
    else if((response_r1 & SDMMC_R6_GENERAL_UNKNOWN_ERROR) == SDMMC_R6_GENERAL_UNKNOWN_ERROR)
    {
        return (SDMMC_ERROR_GENERAL_UNKNOWN_ERROR);
    }
    else
    {
        *pRCA = (uint16_t) (response_r1 >> 16);
        return SDMMC_ERROR_NONE;
    }
}

/**
 *\*\name   SDIO_GetCmdResp7
 *\*\fun    Checks for error conditions for R7 response.
 *\*\param  none
 *\*\return SDIO error state
 */
uint32_t SDIO_GetCmdResp7(void)
{
    uint32_t sts_reg;
    uint32_t timeout;
  
    /* 8 is the number of required instructions cycles for the below loop statement.
    The SDMMC_CMDTIMEOUT is expressed in ms */
    timeout = SDMMC_CMDTIMEOUT * (SystemCoreClock / 8U /1000U);
  
    while(1)
    {
        if(0U == timeout)
        {
            return SDMMC_ERROR_TIMEOUT;
        }
        else
        {
            timeout--;
        }

        sts_reg = SDIO->STS;

        if(sts_reg & SDIO_FLAG_CMDRUN)
        {
            continue;
        }

        if(sts_reg & (SDIO_FLAG_CCRCERR | SDIO_FLAG_CMDRESPRECV | SDIO_FLAG_CMDTIMEOUT))
        {
            break;
        }
    }
    
    if(SDIO_GetFlag(SDIO_FLAG_CMDTIMEOUT))
    {
        SDIO_ClrFlag(SDIO_FLAG_CMDTIMEOUT);
        return SDMMC_ERROR_CMD_RSP_TIMEOUT;
    }
    else if(SDIO_GetFlag(SDIO_FLAG_CCRCERR))
    {
        SDIO_ClrFlag(SDIO_FLAG_CCRCERR);
        
        return SDMMC_ERROR_CMD_CRC_FAIL;
    }
    else
    {
        /* Nothing to do */
    }

    if(SDIO_GetFlag(SDIO_FLAG_CMDRESPRECV))
    {
        /* Card is SD V2.0 compliant */
        SDIO_ClrFlag(SDIO_FLAG_CMDRESPRECV);
    }
  
    return SDMMC_ERROR_NONE;
}

/**
 *\*\name   SDIO_GetCmdError
 *\*\fun    Checks for error conditions for CMD0.
 *\*\param  none
 *\*\return SDIO error state
 */
static uint32_t SDIO_GetCmdError(void)
{
    uint32_t timeout;
  
    /* 8 is the number of required instructions cycles for the below loop statement.
    The SDMMC_CMDTIMEOUT is expressed in ms */
    timeout = SDMMC_CMDTIMEOUT * (SystemCoreClock / 8U /1000U);
  
    while(SDIO_GetFlag(SDIO_FLAG_CMDSEND) != RESET)
    {
        if(0U == timeout)
        {
            return SDMMC_ERROR_TIMEOUT;
        }
        else
        {
            timeout--;
        }
    }
  
    /* Clear all the static flags */
    SDIO_ClrFlag(SDIO_STATIC_CMD_FLAGS);
  
    return SDMMC_ERROR_NONE;
}



