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
*\*\file n32h47x_48x_xspi.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/
#include "n32h47x_48x_xspi.h"
#include "n32h47x_48x_rcc.h"

/** N32H47X_48X_StdPeriph_Driver **/

/**
*\*\name    XSPI_DeInit.
*\*\fun     Deinitializes the XSPI peripheral registers to its default reset values.
*\*\return  none
**/
void XSPI_DeInit(void)
{
	  RCC_EnableAHBPeriphReset(RCC_AHB_PERIPHRST_XSPI);
}

/**
*\*\name    XSPIInitConfig.
*\*\fun     Merge configuration from the buffer of XSPI para struct, then write it into related registers.
*\*\param   XSPI_InitStruct :
*\*\          - FRF	
*\*\          - SPIFRF
*\*\          - TMOD
*\*\          - SCPOL	
*\*\          - SCPH
*\*\          - DFS
*\*\          - SSTE
*\*\          - SEN	
*\*\          - CLKDIV
*\*\          - WAITCYCLES	
*\*\          - INST_L	
*\*\          - ADDRL	
*\*\          - NDF	
*\*\          - TXFT	
*\*\          - RXFT	
*\*\          - ENHANCED_WAITCYCLES	
*\*\          - ENHANCED_CLKSTREN	
*\*\          - ENHANCED_ADDR_L	
*\*\          - ENHANCED_INST_L
*\*\          - ENHANCED_TRANSTYPE	
*\*\          - ENHANCED_WRSPIDDREN;
*\*\          - ENHANCED_WRINDDREN;
*\*\          - XIP_FRF
*\*\          - XIP_TRANSTYPE
*\*\          - XIP_ADDRL
*\*\          - XIP_INST_L	
*\*\          - XIP_WAITCYCLES	
*\*\          - XIPDFSHC
*\*\          - XIPINSTEN	
*\*\          - XIPCTEN
*\*\          - XIPINSTEN
*\*\          - XIPMBL
*\*\          - XIP_WRINDDREN
*\*\          - XIP_DDREN
*\*\          - XIPDFSHC
*\*\          - XIPMDBITS
*\*\          - ITOC
*\*\          - WTOC
*\*\          - XTOUT
*\*\          - CFS
*\*\          - MWMOD
*\*\          - MCDIR
*\*\          - MHSEN
*\*\          - TXFN
*\*\          - RXFN
*\*\          - SDCN
*\*\          - SES
*\*\          - TXDE
*\*\return  none
**/
void XSPI_Init(XSPI_InitType* XSPI_InitStruct)
{
  uint32_t tmpregister = 0;  
	
	if((XSPI_InitStruct->SPIFRF) == XSPI_CTRL0_SPIFRF_STANDARD_FORMAT)
	{
    tmpregister |= (uint32_t)(XSPI_InitStruct->MST | XSPI_InitStruct->FRF | XSPI_InitStruct->SPIFRF | XSPI_InitStruct->SSTE 
		| XSPI_InitStruct->TMOD |XSPI_InitStruct->SCPOL |  XSPI_InitStruct->SCPH | XSPI_InitStruct->DFS| XSPI_InitStruct->CFS);  
		
		XSPI->CTRL0 = tmpregister;
		
		tmpregister = (uint32_t)(XSPI_InitStruct->MWMOD | XSPI_InitStruct->MCDIR | XSPI_InitStruct->MHSEN);
		XSPI->MW_CTRL  = tmpregister;
		
		tmpregister = XSPI->CTRL1;
		tmpregister &= XSPI_NDF_MASK;
		tmpregister |= XSPI_InitStruct->NDF;
		XSPI->CTRL1 = tmpregister;
		
        XSPI->BAUD = XSPI_InitStruct->CLKDIV;
        XSPI->TXFT = XSPI_InitStruct->TXFT;
        XSPI->RXFT = XSPI_InitStruct->RXFT;
        XSPI->TXFN = XSPI_InitStruct->TXFN;
        XSPI->RXFN = XSPI_InitStruct->RXFN;
        XSPI->DDR_TXDE  = XSPI_InitStruct->TXDE; 


		tmpregister = (uint32_t)(XSPI_InitStruct->SES | XSPI_InitStruct->SDCN);
		XSPI->RX_DELAY  = tmpregister;
		
		tmpregister = (uint32_t)(XSPI_InitStruct->ENHANCED_CLKSTREN|XSPI_InitStruct->ENHANCED_INST_L
		|XSPI_InitStruct->ENHANCED_ADDR_L|XSPI_InitStruct->ENHANCED_TRANSTYPE | XSPI_InitStruct->ENHANCED_INST_L | XSPI_InitStruct->ENHANCED_WAITCYCLES 
		|XSPI_InitStruct->WAITCYCLES|XSPI_InitStruct->INST_L|XSPI_InitStruct->ADDR_L); 

		
		XSPI->ENH_CTRL0 = tmpregister;
	}
	else if((XSPI_InitStruct->SPIFRF) == XSPI_CTRL0_SPIFRF_DUAL_FORMAT)
	{
    tmpregister |= (uint32_t)(XSPI_InitStruct->MST | XSPI_InitStruct->FRF |XSPI_InitStruct->SPIFRF | XSPI_InitStruct->TMOD 
		| XSPI_InitStruct->SSTE |XSPI_InitStruct->SCPOL |  XSPI_InitStruct->SCPH | XSPI_InitStruct->DFS | XSPI_InitStruct->CFS); 
		
		XSPI->CTRL0 = tmpregister;
		
		tmpregister = XSPI->CTRL1;
		tmpregister &= XSPI_NDF_MASK;
		tmpregister |= XSPI_InitStruct->NDF;
		XSPI->CTRL1 = tmpregister;

		tmpregister = 0;
		tmpregister = (uint32_t)(XSPI_InitStruct->MWMOD | XSPI_InitStruct->MCDIR | XSPI_InitStruct->MHSEN);
		XSPI->MW_CTRL  = tmpregister;

		tmpregister = 0;
		tmpregister = (uint32_t)(XSPI_InitStruct->SES | XSPI_InitStruct->SDCN);
		XSPI->RX_DELAY  = tmpregister;
		
		tmpregister = 0;
		tmpregister |= (uint32_t)(XSPI_InitStruct->ENHANCED_CLKSTREN | XSPI_InitStruct->ENHANCED_ADDR_L | XSPI_InitStruct->ENHANCED_INST_L
		| XSPI_InitStruct->ENHANCED_WAITCYCLES | XSPI_InitStruct->ENHANCED_TRANSTYPE | XSPI_InitStruct->ENHANCED_WRINDDREN
                                | XSPI_InitStruct->ENHANCED_WRSPIDDREN );
		XSPI->ENH_CTRL0 = tmpregister;
		
		tmpregister = 0;
		tmpregister = (uint32_t)(XSPI_InitStruct->XIPMBL | XSPI_InitStruct->XIPCTEN | XSPI_InitStruct->XIPINSTEN | XSPI_InitStruct->XIP_WRINDDREN
														| XSPI_InitStruct->XIP_DDREN | XSPI_InitStruct->XIPDFSHC | XSPI_InitStruct->XIP_WAITCYCLES | XSPI_InitStruct->XIPMDBITS_EN
														| XSPI_InitStruct->XIP_INST_L | XSPI_InitStruct->XIP_ADDRL | XSPI_InitStruct->XIP_TRANSTYPE | XSPI_InitStruct->XIP_FRF | XSPI_InitStruct->XIPPREEN);
		XSPI->XIP_CTRL = tmpregister;
						
		XSPI->XIP_MODE  = XSPI_InitStruct->XIPMDBITS;
		XSPI->XIP_INCR_TOC  = XSPI_InitStruct->ITOC;
		XSPI->XIP_WRAP_TOC  = XSPI_InitStruct->WTOC;
		XSPI->XIP_TOUT  = XSPI_InitStruct->XTOUT;
	}
	else if((XSPI_InitStruct->SPIFRF) == XSPI_CTRL0_SPIFRF_QUAD_FORMAT || (XSPI_InitStruct->SPIFRF) == XSPI_CTRL0_SPIFRF_OCTAL_FORMAT)
	{
		tmpregister |= (uint32_t)(XSPI_InitStruct->MST | XSPI_InitStruct->FRF |XSPI_InitStruct->SPIFRF | XSPI_InitStruct->SSTE  | XSPI_InitStruct->TMOD
		|XSPI_InitStruct->SCPOL |  XSPI_InitStruct->SCPH | XSPI_InitStruct->DFS);  
		
		XSPI->CTRL0 = tmpregister;
		
		tmpregister = XSPI->CTRL1;
		tmpregister &= XSPI_NDF_MASK;
		tmpregister |= XSPI_InitStruct->NDF;
		XSPI->CTRL1 = tmpregister;
			
		tmpregister = 0;
		tmpregister = (uint32_t)(XSPI_InitStruct->MWMOD | XSPI_InitStruct->MCDIR | XSPI_InitStruct->MHSEN);
		XSPI->MW_CTRL  = tmpregister;

		tmpregister = 0;
		tmpregister = (uint32_t)(XSPI_InitStruct->SES | XSPI_InitStruct->SDCN);
		XSPI->RX_DELAY  = tmpregister;
		
		tmpregister = 0;
		tmpregister |= (uint32_t)(XSPI_InitStruct->ENHANCED_CLKSTREN | XSPI_InitStruct->ENHANCED_ADDR_L | XSPI_InitStruct->ENHANCED_INST_L 
		| XSPI_InitStruct->ENHANCED_WAITCYCLES | XSPI_InitStruct->ENHANCED_TRANSTYPE | XSPI_InitStruct->ENHANCED_WRINDDREN
                                | XSPI_InitStruct->ENHANCED_WRSPIDDREN );
		XSPI->ENH_CTRL0 = tmpregister;
		
		tmpregister = 0;
		tmpregister = (uint32_t)(XSPI_InitStruct->XIPMBL | XSPI_InitStruct->XIPCTEN | XSPI_InitStruct->XIPINSTEN | XSPI_InitStruct->XIP_WRINDDREN
														| XSPI_InitStruct->XIP_DDREN | XSPI_InitStruct->XIPDFSHC | XSPI_InitStruct->XIP_WAITCYCLES | XSPI_InitStruct->XIPMDBITS_EN
														| XSPI_InitStruct->XIP_INST_L | XSPI_InitStruct->XIP_ADDRL | XSPI_InitStruct->XIP_TRANSTYPE | XSPI_InitStruct->XIP_FRF | XSPI_InitStruct->XIPPREEN);
		XSPI->XIP_CTRL = tmpregister;
						
		XSPI->XIP_MODE  = XSPI_InitStruct->XIPMDBITS;
		XSPI->XIP_INCR_TOC  = XSPI_InitStruct->ITOC;
		XSPI->XIP_WRAP_TOC  = XSPI_InitStruct->WTOC;
		XSPI->XIP_TOUT  = XSPI_InitStruct->XTOUT;

	}else{}
	
	XSPI->SLAVE_EN = XSPI_InitStruct->SEN;

}

/**
*\*\name    XSPI_StructInit.
*\*\fun     Fills each XSPI_InitStruct member with its default value.
*\*\param   XSPI_InitStruct :
*\*\          - FRF	
*\*\          - SPIFRF
*\*\          - TMOD
*\*\          - SCPOL	
*\*\          - SCPH
*\*\          - DFS
*\*\          - SSTE
*\*\          - SEN	
*\*\          - CLKDIV
*\*\          - WAITCYCLES	
*\*\          - INST_L	
*\*\          - ADDRL	
*\*\          - NDF	
*\*\          - TXFT	
*\*\          - RXFT	
*\*\          - ENHANCED_WAITCYCLES	
*\*\          - ENHANCED_CLKSTREN	
*\*\          - ENHANCED_ADDR_L	
*\*\          - ENHANCED_INST_L
*\*\          - ENHANCED_TRANSTYPE	
*\*\          - ENHANCED_WRSPIDDREN;
*\*\          - ENHANCED_WRINDDREN;
*\*\          - XIP_FRF
*\*\          - XIP_TRANSTYPE
*\*\          - XIP_ADDRL
*\*\          - XIP_INST_L	
*\*\          - XIP_WAITCYCLES	
*\*\          - XIPDFSHC
*\*\          - XIPINSTEN	
*\*\          - XIPCTEN
*\*\          - XIPINSTEN
*\*\          - XIPMBL
*\*\          - XIP_WRINDDREN
*\*\          - XIP_DDREN
*\*\          - XIPDFSHC
*\*\          - XIPMDBITS
*\*\          - ITOC
*\*\          - WTOC
*\*\          - XTOUT
*\*\          - CFS
*\*\          - MWMOD
*\*\          - MCDIR
*\*\          - MHSEN
*\*\          - TXFN
*\*\          - RXFN
*\*\          - SDCN
*\*\          - SES
*\*\          - TXDE
*\*\return  none
**/
void XSPI_StructInit(XSPI_InitType* XSPI_InitStruct)
{
	XSPI_InitStruct->	FRF	=0;	
	XSPI_InitStruct->	SPIFRF	=0;	
	XSPI_InitStruct->	TMOD	=0;	
	XSPI_InitStruct->	SCPOL		=0;	
	XSPI_InitStruct->	SCPH	=0;	
	XSPI_InitStruct->	DFS	=0;	
	XSPI_InitStruct->	SSTE	=0;	
	XSPI_InitStruct->	SEN		=0;	
	XSPI_InitStruct->	CLKDIV	=0;	
	XSPI_InitStruct->	WAITCYCLES	=0;	
	XSPI_InitStruct->	INST_L	=0;	
	XSPI_InitStruct->	ADDR_L	=0;	
	XSPI_InitStruct->	NDF		=0;	
	XSPI_InitStruct->	TXFT	=0;	
	XSPI_InitStruct->	RXFT	=0;	
	XSPI_InitStruct->	ENHANCED_WAITCYCLES		=0;	
	XSPI_InitStruct->	ENHANCED_CLKSTREN		=0;	
	XSPI_InitStruct->	ENHANCED_ADDR_L		=0;	
	XSPI_InitStruct->	ENHANCED_INST_L	=0;	
	XSPI_InitStruct->	ENHANCED_TRANSTYPE		=0;	
	XSPI_InitStruct->	ENHANCED_WRSPIDDREN	=0;	
	XSPI_InitStruct->	ENHANCED_WRINDDREN		=0;
	XSPI_InitStruct->	XIP_FRF	=0;	
	XSPI_InitStruct->	XIP_TRANSTYPE	=0;	
	XSPI_InitStruct->	XIP_ADDRL	=0;	
	XSPI_InitStruct->	XIP_INST_L		=0;	
	XSPI_InitStruct->	XIP_WAITCYCLES		=0;	
	XSPI_InitStruct->	XIPDFSHC	=0;	
	XSPI_InitStruct->	XIPMBL	=0;	
	XSPI_InitStruct->	XIPINSTEN		=0;	
	XSPI_InitStruct->	XIPPREEN	=0;	
	XSPI_InitStruct->	XIPCTEN	=0;	
	XSPI_InitStruct->	XIP_WRINDDREN	=0;	
	XSPI_InitStruct->	XIP_DDREN	=0;	
	XSPI_InitStruct->	XIPMDBITS_EN	=0;			
	XSPI_InitStruct->	XIPMDBITS	=0;	
	XSPI_InitStruct->	ITOC =0;	
	XSPI_InitStruct->	WTOC 	=0;	
	XSPI_InitStruct->	XTOUT 	=0;	
	XSPI_InitStruct->	CFS 	=0;
	XSPI_InitStruct->	MWMOD =0;
	XSPI_InitStruct->	MCDIR =0;
	XSPI_InitStruct->	MHSEN =0;
	XSPI_InitStruct->	TXFN =0;
	XSPI_InitStruct->	RXFN =0;
	XSPI_InitStruct->	SDCN =0;
	XSPI_InitStruct->	SES =0;
	XSPI_InitStruct->	TXDE =0;
}

/**
*\*\name    XSPI_Cmd.
*\*\fun     Control XSPI function switch.
*\*\param   cmd
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void XSPI_Cmd(FunctionalState cmd)
{
    if (cmd != DISABLE)
    {
        XSPI->EN |= XSPI_EN_XSPIEN;
    }
    else
    {
        XSPI->EN &= ~XSPI_EN_XSPIEN;
    }
}

/**
*\*\name    XSPI_XIP_Cmd.
*\*\fun     Control XSPI XIP function switch.
*\*\param   cmd
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void XSPI_XIP_Cmd(FunctionalState cmd)
{
    if (cmd != DISABLE)
    {
        XSPI->XIP_SLAVE_EN |= XSPI_XIP_SLAVE_EN_SEN;
    }
    else
    {
        XSPI->XIP_SLAVE_EN &= ~XSPI_XIP_SLAVE_EN_SEN;
    }
}


/**
*\*\name    XSPI_SetTransType.
*\*\fun     Set the format of address and instruction sending (1/2/4/8 wire mode)
*\*\param   TransType
*\*\          - XSPI_ENH_CTRL0_TRANSTYPE_STANDARD
*\*\          - XSPI_ENH_CTRL0_TRANSTYPE_ADDRESS_BY_FRF
*\*\          - XSPI_ENH_CTRL0_TRANSTYPE_ALL_BY_FRF
*\*\return  none
**/
void XSPI_SetTransType(uint32_t TransType)
{
	XSPI->ENH_CTRL0 &= XSPI_TRANSTYPE_MASK;
	XSPI->ENH_CTRL0 |= TransType;
}


/**
*\*\name    XSPI_SetWaitCycles.
*\*\fun     Set the number of empty instruction cycles to wait
*\*\param   WAITCYCLES:
*\*\          - XSPI_ENH_CTRL0_WAIT_1CYCLES
*\*\          - ...
*\*\          - XSPI_ENH_CTRL0_WAIT_31CYCLES
*\*\return  none
**/
void XSPI_SetWaitCycles(uint32_t WAITCYCLES)
{
	XSPI->ENH_CTRL0 &= XSPI_WAITCYCLES_MASK;
	XSPI->ENH_CTRL0 |= WAITCYCLES;
}

/**
*\*\name    XSPI_SetRXFIFOLevel.
*\*\fun     Set Rx fifo transmission threshold, trigger full interrupt threshold
*\*\param   fifo_len:
*\*\          - 0x0-0xF
*\*\return  none
**/
void XSPI_SetRXFIFOLevel(uint32_t fifo_len)
{
	XSPI->RXFT &= XSPI_RXFTLR_MASK;
	XSPI->RXFT |= fifo_len;
}

/**
*\*\name    XSPI_SetTXFIFOLevel.
*\*\fun     Set the Tx fifo transmission threshold and trigger the interrupt threshold
*\*\param   fifo_len:
*\*\          - 0x0-0xF  
*\*\return  none
**/
void XSPI_SetTXFIFOLevel(uint32_t fifo_len)
{
	XSPI->TXFT &= XSPI_TXFTLITR_MASK;
	XSPI->TXFT |= fifo_len;
}

/**
*\*\name    XSPI_SetTXFIFOStartLevel.
*\*\fun     Set Tx fifo start transmission threshold
*\*\param   fifo_len:
*\*\          - 0x0-0xF 
*\*\return  none
**/
void XSPI_SetTXFIFOStartLevel(uint32_t fifo_len)
{
	XSPI->TXFT &= XSPI_TXFTLR_MASK;
	XSPI->TXFT |= (fifo_len<<16);
}


/**
*\*\name    XSPI_GetRXFIFOLevel.
*\*\fun     Get the amount of data in the Rx fifo 
*\*\return  Amount of data in Rx fifo.
**/
uint8_t XSPI_GetRXFIFOLevel(void)
{
	return XSPI->RXFT;
}

/**
*\*\name    XSPI_GetTXFIFOLevel.
*\*\fun     Get the amount of data in the Tx fifo 
*\*\return  Amount of data in Tx fifo.
**/
uint8_t XSPI_GetTXFIFOLevel(void)
{
	return XSPI->TXFT;
}

/**
*\*\name    XSPIGetDataPointer.
*\*\fun     Get Pointer of XSPI DAT0 register.
*\*\return  The pointer of XSPI DAT0 register.
**/
uint32_t XSPI_GetDataPointer(void)
{
    return (uint32_t)&XSPI->DAT0;
}

/**
*\*\name    XSPI_ReadRxFifoNum.
*\*\fun     Read value from XSPI RXFN register which shows the number of the data from receive fifo.
*\*\return  The number of the data from receive fifo.
**/
uint32_t XSPI_ReadRxFifoNum(void)
{
    return XSPI->RXFN;
}

/**
*\*\name    XSPI_ReadTxFifoNum.
*\*\fun     Read value from XSPI TXFN register which shows the number of the data from tx fifo.
*\*\return  The number of the data from tx fifo.
**/
uint32_t XSPI_ReadTxFifoNum(void)
{
    return XSPI->TXFN;
}

/**
*\*\name    XSPI_SendData.
*\*\fun     Write one data direct to XSPI DAT0 register to send.
*\*\param   SendData:
*\*\          - data to be send
*\*\return  none
**/
void XSPI_SendData(uint32_t SendData)
{
	/* Write in the DAT0 register the data to be sent */
    XSPI->DAT0 = SendData;
}


/**
*\*\name    XSPI_ReceiveData.
*\*\fun     Read one data from XSPI DAT0 register.
*\*\return  The value of XSPI DAT0 register.
**/
uint32_t XSPI_ReceiveData(void)
{
	/* Return the data in the DAT0 register */
    return XSPI->DAT0;
}


/**
*\*\name    XSPI_GetFlagStatus.
*\*\fun     Checks whether the specified XSPI flag is set or not.
*\*\param   XSPI_FLAG:
*\*\          - XSPI_STS_BUSY
*\*\          - XSPI_STS_TXFNF
*\*\          - XSPI_STS_TXFE
*\*\          - XSPI_STS_RXFNE
*\*\          - XSPI_STS_RXFF
*\*\          - XSPI_STS_TXE
*\*\          - XSPI_STS_DCERR
*\*\return  The new state of XSPI_FLAG (SET or RESET).
**/
FlagStatus XSPI_GetFlagStatus(uint32_t XSPI_FLAG)
{
    FlagStatus bitstatus ;

    /* Check the status of the specified XSPI flag */
    if ((XSPI->STS & XSPI_FLAG) != (uint32_t)RESET)
    {
        /* XSPI_FLAG is set */
        bitstatus = SET;
    }
    else
    {
        /* XSPI_FLAG is reset */
        bitstatus = RESET;
    }
    /* Return the XSPI_FLAG status */
    return  bitstatus;
}


/**
*\*\name    XSPI_GetINTStatus.
*\*\fun     Checks whether the specified XSPI interrupt has occurred or not.
*\*\param   FLAG:
*\*\          - XSPI_ISTS_TXFEIS
*\*\          - XSPI_ISTS_TXFOIS
*\*\          - XSPI_ISTS_RXFUIS
*\*\          - XSPI_ISTS_RXFOIS
*\*\          - XSPI_ISTS_RXFFIS
*\*\          - XSPI_ISTS_MMCIS
*\*\          - XSPI_ISTS_XRXOIS
*\*\          - XSPI_ISTS_TXUIS
*\*\return  The new state of XSPI_IT (SET or RESET).
**/
uint16_t XSPI_GetINTStatus(uint16_t FLAG)
{
    uint16_t tmp;
    tmp = XSPI->ISTS & FLAG;
    if (tmp == 1)
        return 1;
    else
        return 0;
}

/**
*\*\name    XSPI_ClearITBit.
*\*\fun     Checks whether the specified XSPI interrupt has occurred or not.
*\*\param   XSPI_IT:
*\*\          - XSPI_IT_TXUIM
*\*\          - XSPI_IT_XRXOIM	
*\*\          - XSPI_IT_MMCIM
*\*\          - XSPI_IT_RXFFIM
*\*\          - XSPI_IT_RXFOIM	
*\*\          - XSPI_IT_RXFUIM	
*\*\          - XSPI_IT_TXFOIM	
*\*\          - XSPI_IT_TXFEIM
*\*\return  none.
**/
void XSPI_ClearITBit(uint16_t XSPI_IT)
{
    uint16_t itpos;
	
    /* Get the SPI IT index */
    itpos = (XSPI_IT & 0x0F);
    /* Clear the selected Error interrupt pending bit */
    if(itpos == 1)
    {
         (void)XSPI->TXEICR_CLR;//Transmit FIFO Error Interrupt Clear
    }
    else if(itpos == 2)
    {
         (void)XSPI->RXFOI_CLR;//Receive FIFO Overflow Interrupt Clear
    }
    else if(itpos == 3)
    {
         (void)XSPI->RXFUI_CLR;//
    }
    else if(itpos == 4)//Receive FIFO Underflow Interrupt Clear
    {
         (void)XSPI->MMCI_CLR;//Multi-Master Interrupt Clear
    }
    else if(itpos == 6)
    {
         (void)XSPI->XIP_RXFOI_CLR;//Clear XIP Receive FIFO Overflow Interrupt.
    }
    else
    {
         (void)XSPI->ICLR;
    }
}

/**
*\*\name    XSPI_ConfigInt.
*\*\fun     Enables or disables the specified XSPI interrupts.
*\*\param   XSPI_IT:
*\*\          - XSPI_IT_TXUIM
*\*\          - XSPI_IT_XRXOIM	
*\*\          - XSPI_IT_MMCIM
*\*\          - XSPI_IT_RXFFIM
*\*\          - XSPI_IT_RXFOIM	
*\*\          - XSPI_IT_RXFUIM	
*\*\          - XSPI_IT_TXFOIM	
*\*\          - XSPI_IT_TXFEIM
*\*\param   Cmd:
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none.
**/
void XSPI_ConfigInt(uint16_t XSPI_IT, FunctionalState Cmd)
{
    uint16_t itpos , itmask;

    /* Get the XSPI IT index */
    itpos = XSPI_IT >> 4;

    /* Set the IT mask */
    itmask = (uint16_t)1 << (uint16_t)itpos;

    if (Cmd != DISABLE)
    {
        /* Enable the selected XSPI interrupt */
        XSPI->IMASK |= itmask;
    }
    else
    {
        /* Disable the selected XSPI interrupt */
        XSPI->IMASK &= (uint16_t)~itmask;
    }
}

/**
*\*\name    XSPI_ConfigDMATxLevel.
*\*\fun     Configuration of XSPI DMA Tx Level.
*\*\param   TxDataLevel(transmit data):
*\*\          - 0~0x1F
*\*\return  none.
**/
void XSPI_ConfigDMATxLevel(uint32_t TxDataLevel)
{  
    XSPI->DMATDL_CTRL = TxDataLevel;         
}


/**
*\*\name    XSPI_ConfigDMARxLevel.
*\*\fun     Configuration of XSPI DMA Rx Level.
*\*\param   RxDataLevel(receive data):
*\*\          - 0~0x1F
*\*\return  none.
**/
void XSPI_ConfigDMARxLevel(uint32_t RxDataLevel)
{   
    XSPI->DMARDL_CTRL = RxDataLevel;
}

/**
*\*\name    XSPI_EnableDMA
*\*\fun     Enables or disables the XSPI's DMA interface.
*\*\param   XSPI_DMAReq (The input parameters must be the following values):
*\*\          - XSPI_DMAREQ_TX    XSPI DMA transmit request
*\*\          - XSPI_DMAREQ_RX    XSPI DMA receive request
*\*\param   Cmd (The input parameters must be the following values):
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
*\*\note  Configured when xSPI_EN.XSPIEN disabled
**/
void XSPI_EnableDMA(uint32_t XSPI_DMAReq, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the DMA transfer for selected requests by setting the DMAT and/or
           DADDR bits in the USART CTRL3 register */
        XSPI->DMA_CTRL |= XSPI_DMAReq;
    }
    else
    {
        /* Disable the DMA transfer for selected requests by clearing the DMAT and/or
           DADDR bits in the USART CTRL3 register */
        XSPI->DMA_CTRL &= (uint32_t)~XSPI_DMAReq;
    }
}

/**
*\*\name    XSPI_GetBusyStatus.
*\*\fun     Get XSPI status,busy or not.
*\*\return  SET:XSPI busy;
*\*\        RESET:XSPI idle.
**/
FlagStatus XSPI_GetBusyStatus(void)
{
    FlagStatus bitstatus;

    if ((XSPI->STS & 0x01) == 0x01)
    {    
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
*\*\name    XSPI_GetTxDataBusyStatus.
*\*\fun     Check transmit fifo full or not.
*\*\return  SET: Transmit fifo full;
*\*\        RESET: Transmit fifo not full.
**/
FlagStatus XSPI_GetTxDataBusyStatus(void)
{
    FlagStatus bitstatus;

    if ((XSPI->STS & 0x02) == 0x00)
    {    
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}


/**
*\*\name    XSPI_GetTxDataEmptyStatus.
*\*\fun     Check transmit fifo empty or not.
*\*\return  SET: Transmit fifo empty;
*\*\        RESET: Transmit fifo not empty.
**/
FlagStatus XSPI_GetTxDataEmptyStatus(void)
{
    FlagStatus bitstatus;

    if ((XSPI->STS & 0x04) == 0x04)
    {    
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
*\*\name    XSPI_GetRxHaveDataStatus.
*\*\fun     Check receive fifo have data or not.
*\*\return  SET:Receive fifo have data;
*\*\        RESET:Receive fifo empty.
**/
FlagStatus XSPI_GetRxHaveDataStatus(void)
{
    FlagStatus bitstatus;

    if ((XSPI->STS & 0x08) == 0x08)
    {    
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
*\*\name    XSPI_GetRxDataFullStatus.
*\*\fun     Check receive fifo full or not.
*\*\return  SET: Receive fifo full;
*\*\        RESET: Receive fifo not full.
**/
FlagStatus XSPI_GetRxDataFullStatus(void)
{
    FlagStatus bitstatus;

    if ((XSPI->STS & 0x10) == 0x10)
    {    
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}


/**
*\*\name    XSPI_GetDataConflictErrorStatus.
*\*\fun     Check data conflict error or not.
*\*\return  SET: Data conflict error;
*\*\        RESET: No data conflict error.
**/
FlagStatus XSPI_GetDataConflictErrorStatus(void)
{
    FlagStatus bitstatus;

    if ((XSPI->STS & 0x40) == 0x40)
    {    
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
*\*\name    ClrFifo.
*\*\fun     Read DAT0 register to clear fifo.
*\*\return  none.
**/
void XSPI_ClrFifo(void)
{
    uint32_t timeout = 0;

    while (XSPI_GetRxHaveDataStatus())
    {
        XSPI_ReceiveData();
        if(++timeout >= 200)
        {
            break;
        }
    }
}
/**
*\*\name    GetFifoData
*\*\fun     Get data from fifo.
*\*\param   pData pointer to buffer of getting fifo data.
*\*\param   Len length of getting fifo data.
*\*\return  XSPI_SUCCESS or XSPI_NULL.
**/
uint32_t XSPI_GetFifoData(uint32_t* pData, uint32_t Len)
{
    uint32_t cnt;
    for (cnt = 0; cnt < Len; cnt++)
    {
        if (XSPI_GetRxHaveDataStatus())
        {
            *pData++ = XSPI_ReceiveData();
        }
        else
        {
            return XSPI_NULL;
        }
    }

    return XSPI_SUCCESS;
}
/**
*\*\name    XSPISendAndGetWords.
*\*\fun     Send words out from source data buffer and get returned datas into destination data buffer.
*\*\param   pSrcData:
*\*\          - pSrcData pointer to buffer of sending datas.
*\*\param   pDstData:
*\*\          - pDstData pointer to buffer of getting returned datas.
*\*\param   cnt:
*\*\          - cnt number of sending datas.
*\*\return  none.
**/
void XSPI_SendAndGetWords(uint32_t* pSrcData, uint32_t* pDstData, uint32_t cnt)
{
    uint32_t num = 0;
    uint32_t timeout = 0;
    
    while (num < cnt)
    {
        XSPI_SendData(*(pSrcData++));
        num++;
    }
    while (!XSPI_GetRxHaveDataStatus())
    {
        if(++timeout >= XSPI_TIME_OUT_CNT)
        {
            break;
        }
    }
    timeout = 0;
    while (XSPI->RXFN < cnt)
    {
        if(++timeout >= XSPI_TIME_OUT_CNT)
        {
            break;
        }
    }
    num = 0;
    while (num < cnt)
    {
        *(pDstData++) = XSPI_ReceiveData();
        num++;
    }
}

/**
*\*\name    XSPISendWordAndGetWords.
*\*\fun     Send one word data and get returned words into destination data buffer.
*\*\param   WrData:
*\*\          - WrData one word to be sent.
*\*\param   pRdData:
*\*\          - pRdData pointer to buffer of getting returned datas.
*\*\param   LastRd:
*\*\          - 1:go on to get returned datas.
*\*\          - 0:end to get returned datas.
*\*\return  none.
**/
uint32_t XSPI_SendWordAndGetWords(uint32_t WrData, uint32_t* pRdData, uint8_t LastRd)
{
    uint32_t    timeout1 = 0;

    XSPI_SendData(WrData);                   //trammit
    *pRdData = XSPI_ReceiveData();  
    if(LastRd != 0)
    {
        while(!XSPI_GetRxHaveDataStatus())   //wait for data
        {
            if(++timeout1 >= XSPI_TIME_OUT_CNT)
            {
                return XSPI_NULL;           //time out
            }
        }

        *pRdData = XSPI_ReceiveData();          //read data 
        return XSPI_SUCCESS;    
    }
    
    return XSPI_NULL;
}


