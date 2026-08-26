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
*\*\file n32h47x_48x_xspi.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/
#ifndef __n32h47x_48x_XSPI_H__
#define __n32h47x_48x_XSPI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32h47x_48x.h"
#include <stdbool.h>
#include "n32h47x_48x_rcc.h"
#include "n32h47x_48x_gpio.h"

/** n32h47x_48x_StdPeriph_Driver **/

/**  XSPI driver modules **/
////////////////////////////////////////////////////////////////////////////////////////////////////
#define XSPI_WAITCYCLES_MASK      ((uint32_t)~0x0000f800U)
#define XSPI_SPIFRF_MASK          ((uint32_t)~0x00c00000U)
#define XSPI_TRANSTYPE_MASK       ((uint32_t)~0x00000003U)
#define XSPI_DFS_MASK              ((uint32_t)~0x0000001fU)
#define XSPI_ADDRL_MASK           ((uint32_t)~0x0000003cU)
#define XSPI_INST_L_MASK           ((uint32_t)~0x00000300U)
#define XSPI_NDF_MASK              ((uint32_t)~0x0000ffffU)
#define XSPI_TMOD_MASK             ((uint32_t)~0x00000c00U)
#define XSPI_RXFTLR_MASK           ((uint32_t)~0x0000001fU)
#define XSPI_TXFTLR_MASK           ((uint32_t)~0x001f0000U)
#define XSPI_TXFTLITR_MASK         ((uint32_t)~0x0000001fU)

#define STANDRD_SPI_FORMAT               ((uint32_t)0x00000000)
#define DUAL_SPI_FORMAT                  ((uint32_t)0x00400000)
#define QUAD_SPI_FORMAT                  ((uint32_t)0x00800000)
#define OCTAL_SPI_FORMAT                 ((uint32_t)0x00C00000)


#define QSPI_Mode_Master                 ((uint32_t)0x80000000)
#define QSPI_Mode_Slave                  ((uint32_t)0x00000000)

typedef enum
{
    TX_AND_RX = 0,
    TX_ONLY,
    RX_ONLY
} XSPI_DATA_DIR;


typedef enum
{
    XSPI_NULL = 0,
    XSPI_SUCCESS,
} XSPI_STATUS;
////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{		
	uint32_t WAITCYCLES;
    uint32_t INST_L;
    uint32_t ADDR_L;
	
    /*XSPI_CTRL0*/
	uint32_t MST;
    uint32_t DFS;
    uint32_t FRF;						
    uint32_t SCPH;
    uint32_t SCPOL;
    uint32_t TMOD;
    uint32_t SSTE;
    uint32_t CFS;
    uint32_t SPIFRF;
    
    /*XSPI_CTRL1*/
    uint32_t NDF;

    /*XSPI_MW_CTRL*/
    uint32_t MWMOD;
    uint32_t MCDIR;
    uint32_t MHSEN;
		
    /*XSPI_SLAVE_EN*/
    uint32_t SEN;

    /*XSPI_BAUD*/
    uint32_t CLKDIV;

    /*XSPI_TXFT*/
    uint32_t TXFT;

    /*XSPI_RXFT*/
    uint32_t RXFT;

    /*XSPI_TXFN*/
    uint32_t TXFN;

    /*XSPI_RXFN*/
    uint32_t RXFN;

    /*XSPI_RS_DELAY*/
    uint32_t SDCN;
    uint32_t SES;

    /*XSPI_ENH_CTRL0*/
    uint32_t ENHANCED_TRANSTYPE;
    uint32_t ENHANCED_ADDR_L;
    uint32_t ENHANCED_INST_L;
    uint32_t ENHANCED_WAITCYCLES;
    uint32_t ENHANCED_WRSPIDDREN;
    uint32_t ENHANCED_WRINDDREN;
    uint32_t ENHANCED_CLKSTREN;
    
    /*XSPI_DDR_TXDE*/
    uint32_t TXDE;

    /*XSPI_XIP_MODE*/
    uint32_t XIPMDBITS;

    /*XSPI_XIP_INCR_TOC*/
    uint32_t ITOC;

    /*XSPI_XIP_WRAP_TOC*/
    uint32_t WTOC;
    
    /*XSPI_XIP_CTRL*/
    uint32_t XIP_FRF;
    uint32_t XIP_TRANSTYPE;
    uint32_t XIP_ADDRL;
    uint32_t XIP_INST_L;
    uint32_t XIPMDBITS_EN;
    uint32_t XIP_WAITCYCLES;
    uint32_t XIPDFSHC;
    uint32_t XIP_DDREN;
    uint32_t XIP_WRINDDREN;
    uint32_t XIPINSTEN;
    uint32_t XIPCTEN;
    uint32_t XIPMBL;
    uint32_t XIPPREEN;

    /*XSPI_XIP_TOUT*/
    uint32_t XTOUT;

} XSPI_InitType;
////////////////////////////////////////////////////////////////////////////////////////////////////
#define XSPI_TIME_OUT_CNT           200

/** XSPI_mode **/

#define XSPI_Mode_Master                 ((uint32_t)0x80000000U)
#define XSPI_Mode_Slave                  ((uint32_t)0x00000000U)

/** XSPI_Address_instruction_transfer_format. **/
#define TRANS_TYPE_STANDRD                  ((uint32_t)0x00000000)
#define TRANS_TYPE_STANDRD_FRF              ((uint32_t)0x00000001)
#define TRANS_TYPE_FRF                      ((uint32_t)0x00000002)

/** QSPI_data_size **/

#define DFS_04_BIT                 ((uint32_t)0x00000003U)
#define DFS_08_BIT                 ((uint32_t)0x00000007U)
#define DFS_16_BIT                 ((uint32_t)0x0000000fU)
#define DFS_24_BIT                 ((uint32_t)0x00000017U)
#define DFS_32_BIT                 ((uint32_t)0x0000001fU)

//sets the number of data frames to be continuously received by the XSPI
#define CTRL1_NDF_CNT 			1024
#define CTRL1_NDF_0 			0
#define CTRL1_NDF_1 			1
#define CTRL1_NDF_8 			8
#define CTRL1_NDF_16 			16
#define CTRL1_NDF_63 			63
#define CTRL1_NDF_127 			127
#define CTRL1_NDF_255 			255
#define IS_XSPI_NDF(NDF) (((NDF) <= 0xFFFF))

/** SPI_BaudRate_Prescaler **/
//Fsclk_out = Fssi_clk/BAUD,BAUD = {SCKDV*2}
#define CLOCK_DIVI_MAX 			0XFFFE
#define CLOCK_DIVIDER 			0X1f
#define XSPI_SCLKOUT_DISABLE    ((uint32_t)0x00000000U)

#define XSPI_IT_FLAG_TYPE_M			((uint8_t)0x01U)
#define XSPI_IT_FLAG_TYPE_S			((uint8_t)0x02U)
#define XSPI_IT_FLAG_TYPE_R			((uint8_t)0x03U)
														 
#define XSPI_IT_TXUIM	((uint16_t)0X0071U)
#define XSPI_IT_XRXOIM	((uint16_t)0X0066U)
#define XSPI_IT_MMCIM	((uint16_t)0X0054U)
#define XSPI_IT_RXFFIM	((uint16_t)0X0045U)
#define XSPI_IT_RXFOIM	((uint16_t)0X0032U)
#define XSPI_IT_RXFUIM	((uint16_t)0X0023U)
#define XSPI_IT_TXFOIM	((uint16_t)0X0011U)
#define XSPI_IT_TXFEIM	((uint16_t)0X0005U)

#define XSPI_DMAREQ_TX 0x02
#define XSPI_DMAREQ_RX 0x01


////////////////////////////////////////////////////////////////////////////////////////////////////
void XSPI_DeInit(void);
void XSPI_Init(XSPI_InitType* XSPI_InitStruct);
void XSPI_StructInit(XSPI_InitType* XSPI_InitStruct);
void XSPI_Cmd(FunctionalState cmd);
void XSPI_XIP_Cmd(FunctionalState cmd);
void XSPI_SetTransType(uint32_t TransType);
void XSPI_SetWaitCycles(uint32_t WAITCYCLES);
void XSPI_SetRXFIFOLevel(uint32_t fifo_len);
void XSPI_SetTXFIFOLevel(uint32_t fifo_len);
void XSPI_SetTXFIFOStartLevel(uint32_t fifo_len);
uint8_t XSPI_GetRXFIFOLevel(void);
uint8_t XSPI_GetTXFIFOLevel(void);
uint32_t XSPI_GetDataPointer(void);
uint32_t XSPI_ReadRxFifoNum(void);
uint32_t XSPI_ReadTxFifoNum(void);
void XSPI_SendData(uint32_t SendData);
uint32_t XSPI_ReceiveData(void);
FlagStatus XSPI_GetFlagStatus(uint32_t XSPI_FLAG);
uint16_t XSPI_GetINTStatus(uint16_t FLAG);
void XSPI_ClearITBit(uint16_t XSPI_IT);
void XSPI_ConfigInt(uint16_t XSPI_IT, FunctionalState Cmd);
void XSPI_ConfigDMATxLevel(uint32_t TxDataLevel);
void XSPI_ConfigDMARxLevel(uint32_t RxDataLevel);
void XSPI_EnableDMA(uint32_t XSPI_DMAReq, FunctionalState Cmd);
FlagStatus XSPI_GetBusyStatus(void);
FlagStatus XSPI_GetTxDataBusyStatus(void);
FlagStatus XSPI_GetTxDataEmptyStatus(void);
FlagStatus XSPI_GetRxHaveDataStatus(void);
FlagStatus XSPI_GetRxDataFullStatus(void);
FlagStatus XSPI_GetDataConflictErrorStatus(void);
void XSPI_ClrFifo(void);
uint32_t XSPI_GetFifoData(uint32_t* pData, uint32_t Len);
void XSPI_SendAndGetWords(uint32_t* pSrcData, uint32_t* pDstData, uint32_t cnt);
uint32_t XSPI_SendWordAndGetWords(uint32_t WrData, uint32_t* pRdData, uint8_t LastRd);


#ifdef __cplusplus
}
#endif

#endif /*__n32h47x_48x_XSPI_H__ */

