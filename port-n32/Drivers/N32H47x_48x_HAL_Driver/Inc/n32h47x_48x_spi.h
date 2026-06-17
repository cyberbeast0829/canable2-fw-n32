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
*\*\file n32h47x_48x_spi.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/

#ifndef __n32h47x_48x_SPI_H__
#define __n32h47x_48x_SPI_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32h47x_48x.h"

/** n32h47x_48x_StdPeriph_Driver **/
 

/**  SPI Init structure definition */

typedef struct
{
    uint16_t DataDirection; /*!< Specifies the SPI unidirectional or bidirectional data mode.
                                 This parameter can be a value of @ref SPI_data_direction */

    uint16_t SpiMode; /*!< Specifies the SPI operating mode.
                            This parameter can be a value of @ref SPI_mode */

    uint16_t DataLen; /*!< Specifies the SPI data size.
                                This parameter can be a value of @ref SPI_data_size */

    uint16_t CLKPOL; /*!< Specifies the serial clock steady state.
                            This parameter can be a value of @ref SPI_Clock_Polarity */

    uint16_t CLKPHA; /*!< Specifies the clock active edge for the bit capture.
                            This parameter can be a value of @ref SPI_Clock_Phase */

    uint16_t NSS; /*!< Specifies whether the NSS signal is managed by
                           hardware (NSS pin) or by software using the SSI bit.
                           This parameter can be a value of @ref SPI_Slave_Select_management */

    uint16_t BaudRatePres; /*!< Specifies the Baud Rate prescaler value which will be
                                         used to configure the transmit and receive SCK clock.
                                         This parameter can be a value of @ref SPI_BaudRate_Prescaler.
                                         @note The communication clock is derived from the master
                                               clock. The slave clock does not need to be set. */

    uint16_t FirstBit; /*!< Specifies whether data transfers start from MSB or LSB bit.
                                This parameter can be a value of @ref SPI_MSB_LSB_transmission */

    uint16_t CRCPoly; /*!< Specifies the polynomial used for the CRC calculation. */
} SPI_InitType;

/** I2S Init structure definition **/

typedef struct
{
    uint16_t I2sMode; /*!< Specifies the I2S operating mode.
                            This parameter can be a value of @ref I2sMode */

    uint16_t Standard; /*!< Specifies the standard used for the I2S communication.
                                This parameter can be a value of @ref Standard */

    uint16_t DataFormat; /*!< Specifies the data format for the I2S communication.
                                  This parameter can be a value of @ref I2S_Data_Format */

    uint16_t MCLKEnable; /*!< Specifies whether the I2S MCLK output is enabled or not.
                                  This parameter can be a value of @ref I2S_MCLK_Output */

    uint32_t AudioFrequency; /*!< Specifies the frequency selected for the I2S communication.
                                 This parameter can be a value of @ref I2S_Audio_Frequency */

    uint16_t CLKPOL; /*!< Specifies the idle state of the I2S clock.
                            This parameter can be a value of @ref I2S_Clock_Polarity */
	  uint32_t ClkSrcFrequency;   /*!< Specifies the I2S clock source frequency in Hz.*/
	  
} I2S_InitType;


/** SPI_Exported_Constants **/

#define IS_SPI_PERIPH(PERIPH) (((PERIPH) == SPI1) || \
															 ((PERIPH) == SPI2) || \
															 ((PERIPH) == SPI3) || \
															 ((PERIPH) == SPI4) || \
															 ((PERIPH) == SPI5) || \
															 ((PERIPH) == SPI6))

#define IS_SPI_2OR3_PERIPH(PERIPH) (((PERIPH) == SPI2) || ((PERIPH) == SPI3))

/** SPI_data_direction **/

#define SPI_DIR_DOUBLELINE_FULLDUPLEX ((uint16_t)0x0000U)
#define SPI_DIR_DOUBLELINE_RONLY      ((uint16_t)0x2000U)
#define SPI_DIR_SINGLELINE_RX         ((uint16_t)0x8000U)
#define SPI_DIR_SINGLELINE_TX         ((uint16_t)0xC000U)
#define IS_SPI_DIR_MODE(MODE)                                                                                          \
    (((MODE) == SPI_DIR_DOUBLELINE_FULLDUPLEX) || ((MODE) == SPI_DIR_DOUBLELINE_RONLY)                                 \
     || ((MODE) == SPI_DIR_SINGLELINE_RX) || ((MODE) == SPI_DIR_SINGLELINE_TX))

/** SPI_mode **/

#define SPI_MODE_MASTER   ((uint16_t)0x0840U)
#define SPI_MODE_SLAVE    ((uint16_t)0x0000U)
#define IS_SPI_MODE(MODE) (((MODE) == SPI_MODE_MASTER) || ((MODE) == SPI_MODE_SLAVE))
 

/** SPI_data_size **/

#define SPI_DATA_SIZE_16BITS      ((uint16_t)0x0100U)
#define SPI_DATA_SIZE_8BITS       ((uint16_t)0x0000U)
#define IS_SPI_DATASIZE(DATASIZE) (((DATASIZE) == SPI_DATA_SIZE_16BITS) || ((DATASIZE) == SPI_DATA_SIZE_8BITS))


/** SPI_Clock_Polarity **/

#define SPI_CLKPOL_LOW      ((uint16_t)0x0000U)
#define SPI_CLKPOL_HIGH     ((uint16_t)0x0010U)
#define IS_SPI_CLKPOL(CPOL) (((CPOL) == SPI_CLKPOL_LOW) || ((CPOL) == SPI_CLKPOL_HIGH))
 

/** SPI_Clock_Phase **/

#define SPI_CLKPHA_FIRST_EDGE  ((uint16_t)0x0000U)
#define SPI_CLKPHA_SECOND_EDGE ((uint16_t)0x0020U)
#define IS_SPI_CLKPHA(CPHA)    (((CPHA) == SPI_CLKPHA_FIRST_EDGE) || ((CPHA) == SPI_CLKPHA_SECOND_EDGE))

/** SPI_Slave_Select_management **/

#define SPI_NSS_SOFT    ((uint16_t)0x1000U)
#define SPI_NSS_HARD    ((uint16_t)0x0000U)
#define IS_SPI_NSS(NSS) (((NSS) == SPI_NSS_SOFT) || ((NSS) == SPI_NSS_HARD))


/** SPI_BaudRate_Prescaler **/

#define SPI_BR_PRESCALER_2   ((uint16_t)0x0000U)
#define SPI_BR_PRESCALER_4   ((uint16_t)0x0001U)
#define SPI_BR_PRESCALER_8   ((uint16_t)0x0002U)
#define SPI_BR_PRESCALER_16  ((uint16_t)0x0003U)
#define SPI_BR_PRESCALER_32  ((uint16_t)0x0004U)
#define SPI_BR_PRESCALER_64  ((uint16_t)0x0005U)
#define SPI_BR_PRESCALER_128 ((uint16_t)0x0006U)
#define SPI_BR_PRESCALER_256 ((uint16_t)0x0007U)
#define IS_SPI_BR_PRESCALER(PRESCALER)                                                                                 \
    (((PRESCALER) == SPI_BR_PRESCALER_2) || ((PRESCALER) == SPI_BR_PRESCALER_4) || ((PRESCALER) == SPI_BR_PRESCALER_8) \
     || ((PRESCALER) == SPI_BR_PRESCALER_16) || ((PRESCALER) == SPI_BR_PRESCALER_32)                                   \
     || ((PRESCALER) == SPI_BR_PRESCALER_64) || ((PRESCALER) == SPI_BR_PRESCALER_128)                                  \
     || ((PRESCALER) == SPI_BR_PRESCALER_256))


/** SPI_MSB_LSB_transmission **/

#define SPI_FB_MSB            ((uint16_t)0x0000U)
#define SPI_FB_LSB            ((uint16_t)0x0080U)
#define IS_SPI_FIRST_BIT(BIT) (((BIT) == SPI_FB_MSB) || ((BIT) == SPI_FB_LSB))

/** I2sMode **/

#define I2S_MODE_SlAVE_TX  ((uint16_t)0x0000U)
#define I2S_MODE_SlAVE_RX  ((uint16_t)0x0010U)
#define I2S_MODE_MASTER_TX ((uint16_t)0x0020U)
#define I2S_MODE_MASTER_RX ((uint16_t)0x0030U)
#define IS_I2S_MODE(MODE)                                                                                              \
    (((MODE) == I2S_MODE_SlAVE_TX) || ((MODE) == I2S_MODE_SlAVE_RX) || ((MODE) == I2S_MODE_MASTER_TX)                  \
     || ((MODE) == I2S_MODE_MASTER_RX))
 
/**  Standard **/

#define I2S_STD_PHILLIPS       ((uint16_t)0x0000U)
#define I2S_STD_MSB_ALIGN      ((uint16_t)0x0004U)
#define I2S_STD_LSB_ALIGN      ((uint16_t)0x0008U)
#define I2S_STD_PCM_SHORTFRAME ((uint16_t)0x000CU)
#define I2S_STD_PCM_LONGFRAME  ((uint16_t)0x020CU)
#define IS_I2S_STANDARD(STANDARD)                                                                                      \
    (((STANDARD) == I2S_STD_PHILLIPS) || ((STANDARD) == I2S_STD_MSB_ALIGN) || ((STANDARD) == I2S_STD_LSB_ALIGN)        \
     || ((STANDARD) == I2S_STD_PCM_SHORTFRAME) || ((STANDARD) == I2S_STD_PCM_LONGFRAME))


/** I2S_Data_Format **/

#define I2S_DATA_FMT_16BITS          ((uint16_t)0x0000U)
#define I2S_DATA_FMT_16BITS_EXTENDED ((uint16_t)0x0100U)
#define I2S_DATA_FMT_24BITS          ((uint16_t)0x0140U)
#define I2S_DATA_FMT_32BITS          ((uint16_t)0x0180U)
#define IS_I2S_DATA_FMT(FORMAT)                                                                                        \
    (((FORMAT) == I2S_DATA_FMT_16BITS) || ((FORMAT) == I2S_DATA_FMT_16BITS_EXTENDED)                                   \
     || ((FORMAT) == I2S_DATA_FMT_24BITS) || ((FORMAT) == I2S_DATA_FMT_32BITS))


/** I2S_MCLK_Output **/

#define I2S_MCLK_ENABLE            ((uint16_t)0x0800U)
#define I2S_MCLK_DISABLE           ((uint16_t)0x0000U)
#define IS_I2S_MCLK_ENABLE(OUTPUT) (((OUTPUT) == I2S_MCLK_ENABLE) || ((OUTPUT) == I2S_MCLK_DISABLE))


/** I2S_Audio_Frequency **/

#define I2S_AUDIO_FREQ_192K    ((uint32_t)192000U)
#define I2S_AUDIO_FREQ_96K     ((uint32_t)96000U)
#define I2S_AUDIO_FREQ_48K     ((uint32_t)48000U)
#define I2S_AUDIO_FREQ_44K     ((uint32_t)44100U)
#define I2S_AUDIO_FREQ_32K     ((uint32_t)32000U)
#define I2S_AUDIO_FREQ_22K     ((uint32_t)22050U)
#define I2S_AUDIO_FREQ_16K     ((uint32_t)16000U)
#define I2S_AUDIO_FREQ_11K     ((uint32_t)11025U)
#define I2S_AUDIO_FREQ_8K      ((uint32_t)8000U)
#define I2S_AUDIO_FREQ_DEFAULT ((uint32_t)2U)

#define IS_I2S_AUDIO_FREQ(FREQ)                                                                                        \
    ((((FREQ) >= I2S_AUDIO_FREQ_8K) && ((FREQ) <= I2S_AUDIO_FREQ_192K)) || ((FREQ) == I2S_AUDIO_FREQ_DEFAULT))


/** I2S_Clock_Polarity **/

#define I2S_CLKPOL_LOW      ((uint16_t)0x0000U)
#define I2S_CLKPOL_HIGH     ((uint16_t)0x0400U)
#define IS_I2S_CLKPOL(CPOL) (((CPOL) == I2S_CLKPOL_LOW) || ((CPOL) == I2S_CLKPOL_HIGH))


/** SPI_I2S_DMA_transfer_requests **/

#define SPI_I2S_DMA_TX         ((uint16_t)0x0004U)
#define SPI_I2S_DMA_RX         ((uint16_t)0x0002U)
#define IS_SPI_I2S_DMA(DMAREQ) ((((DMAREQ) & (uint16_t)0xFFFCU) == 0x00) && ((DMAREQ) != 0x00))
 
/** I2S_EXT_DMA_transfer_requests **/

#define I2S_EXT_DMA_TX         ((uint16_t)0x0004U)
#define I2S_EXT_DMA_RX         ((uint16_t)0x0002U)
 
 
/** SPI_NSS_internal_software_management **/

#define SPI_NSS_HIGH               ((uint16_t)0x0800U)
#define SPI_NSS_LOW                ((uint16_t)0x0000U)
#define IS_SPI_NSS_LEVEL(INTERNAL) (((INTERNAL) == SPI_NSS_HIGH) || ((INTERNAL) == SPI_NSS_LOW))


/** SPI_CRC_Transmit_Receive **/

#define SPI_CRC_TX      ((uint8_t)0x00U)
#define SPI_CRC_RX      ((uint8_t)0x01U)
#define IS_SPI_CRC(CRC) (((CRC) == SPI_CRC_TX) || ((CRC) == SPI_CRC_RX))
 

/** SPI_direction_transmit_receive **/

#define SPI_BIDIRECTION_RX            ((uint16_t)0xBFFFU)
#define SPI_BIDIRECTION_TX            ((uint16_t)0x4000U)
#define IS_SPI_BIDIRECTION(DIRECTION) (((DIRECTION) == SPI_BIDIRECTION_RX) || ((DIRECTION) == SPI_BIDIRECTION_TX))


/** SPI_I2S_interrupts_definition **/

#define SPI_I2S_INT_TE            ((uint8_t)0x40)
#define SPI_I2S_INT_RNE           ((uint8_t)0x51)
#define SPI_I2S_INT_ERR           ((uint8_t)0x60)
#define SPI_I2S_INT_RXONLYC       ((uint8_t)0xEC)
#define SPI_I2S_INT_RXFIFOF       ((uint8_t)0xCB)
#define SPI_I2S_INT_RXFIFOHF      ((uint8_t)0xB9)
#define SPI_I2S_INT_TXFIFOHE      ((uint8_t)0xA8) 
#define SPI_I2S_INT_MODERR        ((uint8_t)0x64)
#define SPI_I2S_INT_CRCERR        ((uint8_t)0x63)
#define SPI_I2S_INT_OVERERR       ((uint8_t)0x65)
#define I2S_I2S_INT_UNDER         ((uint8_t)0x66)
#define IS_SPI_I2S_CONFIG_INT(IT) (((IT) == SPI_I2S_INT_TE) || ((IT) == SPI_I2S_INT_RNE) || 			\
                                  ((IT) == SPI_I2S_INT_RXFIFOF) || ((IT) == SPI_I2S_INT_RXFIFOHF)|| \
                                  ((IT) == SPI_I2S_INT_TXFIFOHE)|| ((IT) == SPI_I2S_INT_RXONLYC) || \
                                  ((IT) == SPI_I2S_INT_ERR))


#define SPI_I2S_INT_OVER          ((uint16_t)0x0065U)
#define SPI_INT_MODERR            ((uint16_t)0x0064U)
#define SPI_INT_CRCERR            ((uint16_t)0x0063U)
#define I2S_INT_UNDER             ((uint16_t)0x0066U)
#define IS_SPI_I2S_CLR_INT(IT)    (((IT) == SPI_INT_CRCERR))
#define IS_SPI_I2S_GET_INT(IT)    (((IT) == SPI_I2S_INT_RNE) || ((IT) == SPI_I2S_INT_TE)		  \
																	|| ((IT) == I2S_INT_UNDER) || ((IT) == SPI_INT_CRCERR)      \
																	|| ((IT) == SPI_INT_MODERR) || ((IT) == SPI_I2S_INT_OVER))


/** I2S_EXT_interrupts_definition **/
#define I2S_EXT_INT_TEINTEN       ((uint16_t)0x0010U)
#define I2S_EXT_INT_RNEINTEN      ((uint16_t)0x0020U)
#define I2S_EXT_INT_ERRINTEN      ((uint16_t)0x0040U)
#define IS_I2S_EXT_GET_INT(IT)    (((IT) == I2S_EXT_INT_TEINTEN) || ((IT) == I2S_EXT_INT_RNEINTEN) || ((IT) == I2S_EXT_INT_ERRINTEN))



/** I2S_EXT_flags_definition **/
#define I2S_EXT_TE_FLAG     			((uint16_t)0x0001U) 
#define I2S_EXT_RNE_FLAG    			((uint16_t)0x0002U) 
#define I2S_EXT_BUSY_FLAG   			((uint16_t)0x0004U) 
#define I2S_EXT_OVER_FLAG   			((uint16_t)0x0020U) 
#define I2S_EXT_UNDER_FLAG  			((uint16_t)0x0040U) 
#define I2S_EXT_CHSIDE_FLAG 			((uint16_t)0x0080U) 
#define IS_I2S_EXT_GET_FLAG(FLAG)   ( \
                                    ((FLAG) == I2S_EXT_TE_FLAG) || ((FLAG) == I2S_EXT_RNE_FLAG) || \
                                    ((FLAG) == I2S_EXT_BUSY_FLAG) || ((FLAG) == I2S_EXT_OVER_FLAG) || \
                                    ((FLAG) == I2S_EXT_UNDER_FLAG) || ((FLAG) == I2S_EXT_CHSIDE_FLAG))


/** SPI_I2S_flags_definition **/
#define SPI_I2S_TE_FLAG           				((uint16_t)0x0001U)
#define SPI_I2S_RNE_FLAG          				((uint16_t)0x0002U)
#define SPI_I2S_BUSY_FLAG         				((uint16_t)0x0004U)
#define SPI_CRCERR_FLAG           				((uint16_t)0x0008U)
#define SPI_MODERR_FLAG           				((uint16_t)0x0010U)
#define SPI_I2S_OVER_FLAG         				((uint16_t)0x0020U)
#define I2S_UNDER_FLAG            				((uint16_t)0x0040U)
#define I2S_CHSIDE_FLAG           				((uint16_t)0x0080U)
#define SPI_I2S_TXFIFOHE_FLAG             ((uint16_t)0x0100U)
#define SPI_I2S_RXFIFOHF_FLAG             ((uint16_t)0x0200U)
#define SPI_I2S_TXFIFOE_FLAG              ((uint16_t)0x0400U)
#define SPI_I2S_RXFIFOF_FLAG              ((uint16_t)0x0800U)
#define SPI_I2S_RXONLYC_FLAG              ((uint16_t)0x1000U)

#define IS_SPI_I2S_CLR_FLAG(FLAG) 	(((FLAG) == SPI_CRCERR_FLAG))
#define IS_SPI_I2S_GET_FLAG(FLAG)   ( \
                                    ((FLAG) == SPI_I2S_BUSY_FLAG) || ((FLAG) == SPI_I2S_OVER_FLAG) || \
                                    ((FLAG) == SPI_MODERR_FLAG) || ((FLAG) == SPI_CRCERR_FLAG) || \
                                    ((FLAG) == I2S_UNDER_FLAG) || ((FLAG) == I2S_CHSIDE_FLAG) || \
                                    ((FLAG) == SPI_I2S_TE_FLAG) || ((FLAG) == SPI_I2S_RNE_FLAG) || \
                                    ((FLAG) == SPI_I2S_RXONLYC_FLAG ) || \
                                    ((FLAG) == SPI_I2S_RXFIFOF_FLAG) || ((FLAG) == SPI_I2S_TXFIFOE_FLAG) || \
                                    ((FLAG) == SPI_I2S_RXFIFOHF_FLAG) || ((FLAG) == SPI_I2S_TXFIFOHE_FLAG))

/** SPI_I2S_FIFO_Ctrl_definition **/

#define SPI_I2S_FIFO_CLR                ((uint16_t)0x0200U)
#define SPI_I2S_FIFO_Enable             ((uint16_t)0x0100U)
#define SPI_I2S_FIFO_Disable            ((uint16_t)0xFEFFU)
#define IS_SPI_I2S_FIFO_CTRL(CTRL) (((CTRL) == SPI_I2S_FIFO_CLR) || ((CTRL) == SPI_I2S_FIFO_Enable) || \
                                   ((CTRL) == SPI_I2S_FIFO_Disable))

/** SPI_RX_FIFO_Level **/

#define SPI_RX_FIF0NUM_7        ((uint16_t)0x0070U)    
#define SPI_RX_FIF0NUM_6        ((uint16_t)0x0060U)    
#define SPI_RX_FIF0NUM_5        ((uint16_t)0x0050U)    
#define SPI_RX_FIF0NUM_4        ((uint16_t)0x0040U)    
#define SPI_RX_FIF0NUM_3        ((uint16_t)0x0030U)    
#define SPI_RX_FIF0NUM_2        ((uint16_t)0x0020U)    
#define SPI_RX_FIF0NUM_1        ((uint16_t)0x0010U)    
#define SPI_RX_FIF0NUM_0        ((uint16_t)0x0000U)    
#define IS_SPI_RX_FIFO_NUM(NUM) (((NSS) == SPI_RX_FIF0NUM_0) || \
																((NSS) == SPI_RX_FIF0NUM_1) || \
																((NSS) == SPI_RX_FIF0NUM_2) || \
																((NSS) == SPI_RX_FIF0NUM_3) || \
																((NSS) == SPI_RX_FIF0NUM_4) || \
																((NSS) == SPI_RX_FIF0NUM_5) || \
																((NSS) == SPI_RX_FIF0NUM_6) || \
																((NSS) == SPI_RX_FIF0NUM_7))

/** SPI_TX_FIFO_Level **/

#define SPI_TX_FIF0NUM_7        ((uint16_t)0x0007U)     
#define SPI_TX_FIF0NUM_6        ((uint16_t)0x0006U)     
#define SPI_TX_FIF0NUM_5        ((uint16_t)0x0005U)     
#define SPI_TX_FIF0NUM_4        ((uint16_t)0x0004U)     
#define SPI_TX_FIF0NUM_3        ((uint16_t)0x0003U)     
#define SPI_TX_FIF0NUM_2        ((uint16_t)0x0002U)     
#define SPI_TX_FIF0NUM_1        ((uint16_t)0x0001U)     
#define SPI_TX_FIF0NUM_0        ((uint16_t)0x0000U)     
#define IS_SPI_TX_FIFO_NUM(NUM) (((NSS) == SPI_TX_FIF0NUM_0) || \
																((NSS) == SPI_TX_FIF0NUM_1) || \
																((NSS) == SPI_TX_FIF0NUM_2) || \
																((NSS) == SPI_TX_FIF0NUM_3) || \
																((NSS) == SPI_TX_FIF0NUM_4) || \
																((NSS) == SPI_TX_FIF0NUM_5) || \
																((NSS) == SPI_TX_FIF0NUM_6) || \
																((NSS) == SPI_TX_FIF0NUM_7))


/** SPI_CRC_polynomial **/

#define IS_SPI_CRC_POLYNOMIAL(POLYNOMIAL) ((POLYNOMIAL) >= 0x1)


/** SPI_Exported_Functions **/

void SPI_I2S_DeInit(const SPI_Module* SPIx);
void SPI_Init(SPI_Module* SPIx,const SPI_InitType* SPI_InitStruct);
void SPI_InitStruct(SPI_InitType* SPI_InitStruct);
void I2S_InitStruct(I2S_InitType* I2S_InitStruct);
void SPI_Enable(SPI_Module* SPIx, FunctionalState Cmd);
void I2S_Enable(SPI_Module* SPIx, FunctionalState Cmd);
void SPI_I2S_EnableInt(SPI_Module* SPIx, uint8_t SPI_I2S_IT, FunctionalState Cmd);
void SPI_I2S_EnableDma(SPI_Module* SPIx, uint16_t SPI_I2S_DMAReq, FunctionalState Cmd);
void SPI_I2S_TransmitData(SPI_Module* SPIx, uint16_t Data);
uint16_t SPI_I2S_ReceiveData(const SPI_Module* SPIx);
void SPI_SetNssLevel(SPI_Module* SPIx, uint16_t SPI_NSSInternalSoft);
void SPI_SSOutputEnable(SPI_Module* SPIx, FunctionalState Cmd);
void SPI_ConfigDataLen(SPI_Module* SPIx, uint16_t DataLen);
void SPI_TransmitCrcNext(SPI_Module* SPIx, FunctionalState Cmd);
void SPI_EnableCalculateCrc(SPI_Module* SPIx, FunctionalState Cmd);
uint16_t SPI_GetCRCDat(const SPI_Module* SPIx, uint8_t SPI_CRC);
uint16_t SPI_GetCRCPoly(const SPI_Module* SPIx);
void SPI_ConfigBidirectionalMode(SPI_Module* SPIx, uint16_t DataDirection);
FlagStatus SPI_I2S_GetStatus(const SPI_Module* SPIx, uint16_t SPI_I2S_FLAG);
void SPI_I2S_ClrCRCErrFlag(SPI_Module* SPIx, uint16_t SPI_I2S_FLAG);
INTStatus SPI_I2S_GetIntStatus(const SPI_Module* SPIx, uint8_t SPI_I2S_IT);
void SPI_I2S_ClrITPendingBit(SPI_Module* SPIx, uint8_t SPI_I2S_IT);

void I2S_Init(SPI_Module* SPIx,const I2S_InitType* I2S_InitStruct);
void SPI_I2S_FIFO_Cmd(SPI_Module* SPIx, FunctionalState NewState);
void SPI_I2S_ClearFIFOBit(SPI_Module* SPIx, uint16_t SPI_I2S_FIFO_Clear);
void SPI_RxFIFOSizeConfig(SPI_Module* SPIx, uint16_t SPI_FIFOSize);
void SPI_TxFIFOSizeConfig(SPI_Module* SPIx, uint16_t SPI_FIFOSize);
uint16_t SPI_RX_FIFO_CNT_GET(const SPI_Module* SPIx);
uint16_t SPI_TX_FIFO_CNT_GET(const SPI_Module* SPIx);
void SPI_TRANSNUM_SET(SPI_Module* SPIx, uint16_t Data);
uint16_t SPI_TRANSNUM_GET(const SPI_Module* SPIx);
void SPI_DELAYTIME_SET(SPI_Module* SPIx, uint16_t Data);
uint16_t SPI_DELAYTIME_GET(const SPI_Module* SPIx);
void SPI_RX_FIFO_SET(SPI_Module* SPIx, uint16_t Data);
uint16_t SPI_RX_FIFO_GET(const SPI_Module* SPIx);

void I2S_EXT_Init(I2S_EXT_Module* I2Sx_EXT,const I2S_InitType* I2S_EXT_InitStruct);
void I2S_EXT_Enable(I2S_EXT_Module* I2Sx_EXT, FunctionalState Cmd);
void I2S_EXT_TransmitData(I2S_EXT_Module* I2Sx, uint16_t Data);
uint16_t I2S_EXT_ReceiveData(const I2S_EXT_Module* I2Sx);
void I2S_EXT_EnableDma(I2S_EXT_Module* I2Sx, uint16_t I2S_EXT_DMAReq, FunctionalState Cmd);
void I2S_EXT_EnableInt(I2S_EXT_Module* I2Sx, uint8_t I2S_EXT_IT, FunctionalState Cmd);
FlagStatus I2S_EXT_GetStatus(const I2S_EXT_Module* I2Sx, uint16_t I2S_EXT_FLAG);
INTStatus I2S_EXT_GetIntStatus(const I2S_EXT_Module* I2Sx, uint8_t I2S_EXT_IT);

#ifdef __cplusplus
}
#endif

#endif /*__n32h47x_48x_SPI_H__ */

