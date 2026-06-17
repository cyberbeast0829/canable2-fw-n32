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
*\*\file n32h47x_48x_dma.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/

#ifndef __N32H47X_DMA_H__
#define __N32H47X_DMA_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "n32h47x_48x.h"

/*** DMA Structure Definition Start ***/

/** DMA Init structure definition **/
typedef struct
{
    uint32_t PeriphAddr;     /* Specifies the peripheral base address for DMAy Channelx. */

    uint32_t MemAddr;        /* Specifies the memory base address for DMAy Channelx. */

    uint32_t Direction;      /* Specifies if the peripheral is the source or destination. */

    uint32_t BufSize;        /* Specifies the buffer size, in data unit, of the specified Channel. 
                                The data unit is equal to the configuration set in PeriphDataSize
                                or MemDataSize members depending in the transfer direction. */

    uint32_t PeriphInc;      /* Specifies whether the Peripheral address register is incremented or not. */

    uint32_t MemoryInc;  /* Specifies whether the memory address register is incremented or not. */

    uint32_t PeriphDataSize; /* Specifies the Peripheral data width. */

    uint32_t MemDataSize;    /* Specifies the Memory data width. */

    uint32_t CircularMode;   /* Specifies the operation mode of the DMAy Channelx.
                                *\*\note: The circular buffer mode cannot be used if the memory-to-memory
                                data transfer is configured on the selected Channel */

    uint32_t Priority;       /* Specifies the software priority for the DMAy Channelx. */

    uint32_t Mem2Mem;        /* Specifies if the DMAy Channelx will be used in memory-to-memory transfer. */
                                                                                        
    uint32_t BURST_BYPASS;   /* Specifies the operation statue of the DMA BURST*/
    
    uint32_t BURST_MODE;     /* Specifies the operation mode of the DMA BURST*/ 
    
    uint32_t BURST_LEN;      /* Specifies the operation length of the DMA BURST*/ 
    
}DMA_InitType;

/*** DMA Structure Definition End ***/

/*** DMA Macro Definition Start ***/

/** DMA register bit field mask definition **/
#define DMA_REG_BIT_FIELD_MASK          ((uint32_t)0x00000000U)

/** DMA data transfer direction definition **/
#define DMA_DIR_PERIPH_MASK             (~((uint32_t)DMA_CHCFG1_DIR))
#define DMA_DIR_PERIPH_DST              ((uint32_t)DMA_CHCFG1_DIR)
#define DMA_DIR_PERIPH_SRC              ((uint32_t)DMA_REG_BIT_FIELD_MASK)

/** DMA peripheral incremented mode definition **/
#define DMA_PERIPH_INC_MODE_MASK        (~((uint32_t)DMA_CHCFG1_PINC))
#define DMA_PERIPH_INC_ENABLE           ((uint32_t)DMA_CHCFG1_PINC)
#define DMA_PERIPH_INC_DISABLE          ((uint32_t)DMA_REG_BIT_FIELD_MASK)

/** DMA memory incremented mode definition **/
#define DMA_MEM_INC_MODE_MASK           (~((uint32_t)DMA_CHCFG1_MINC))
#define DMA_MEM_INC_ENABLE              ((uint32_t)DMA_CHCFG1_MINC)
#define DMA_MEM_INC_DISABLE             ((uint32_t)DMA_REG_BIT_FIELD_MASK)

/** DMA peripheral data width definition **/
#define DMA_PERIPH_DATA_WIDTH_MASK      (~((uint32_t)DMA_CHCFG1_PSIZE))
#define DMA_PERIPH_DATA_WIDTH_BYTE       ((uint32_t)(DMA_CHCFG1_PSIZE_0 \
                                                   & DMA_CHCFG1_PSIZE_1))
#define DMA_PERIPH_DATA_WIDTH_HALFWORD   ((uint32_t)(DMA_CHCFG1_PSIZE_0))
#define DMA_PERIPH_DATA_WIDTH_WORD       ((uint32_t)(DMA_CHCFG1_PSIZE_1))


/** DMA memory data width definition **/
#define DMA_MEM_DATA_WIDTH_MASK         (~((uint32_t)DMA_CHCFG1_MSIZE))
#define DMA_MEM_DATA_WIDTH_BYTE         ((uint32_t)(DMA_CHCFG1_MSIZE_0 \
                                                   & DMA_CHCFG1_MSIZE_1))
#define DMA_MEM_DATA_WIDTH_HALFWORD     ((uint32_t)(DMA_CHCFG1_MSIZE_0))
#define DMA_MEM_DATA_WIDTH_WORD         ((uint32_t)(DMA_CHCFG1_MSIZE_1))

/** DMA circulation mode definition **/
#define DMA_CIRCULAR_MODE_MASK          (~((uint32_t)DMA_CHCFG1_CIRC))
#define DMA_MODE_CIRCULAR               ((uint32_t)DMA_CHCFG1_CIRC)
#define DMA_MODE_NORMAL                 ((uint32_t)DMA_REG_BIT_FIELD_MASK)

/** DMA channel priority level definition **/
#define DMA_CH_PRIORITY_MASK            (~((uint32_t)DMA_CHCFG1_PRIOLVL))
#define DMA_PRIORITY_VERY_HIGH          ((uint32_t)(DMA_CHCFG1_PRIOLVL_0 \
                                                  | DMA_CHCFG1_PRIOLVL_1))
#define DMA_PRIORITY_HIGH               ((uint32_t)(DMA_CHCFG1_PRIOLVL_1))
#define DMA_PRIORITY_MEDIUM             ((uint32_t)(DMA_CHCFG1_PRIOLVL_0))
#define DMA_PRIORITY_LOW                ((uint32_t)(DMA_CHCFG1_PRIOLVL_0 \
                                                  & DMA_CHCFG1_PRIOLVL_1))
/** DMA memory to memory mode definition **/
#define DMA_MEM2MEM_MASK                (~((uint32_t)DMA_CHCFG1_MEM2MEM))
#define DMA_M2M_ENABLE                  ((uint32_t)DMA_CHCFG1_MEM2MEM)
#define DMA_M2M_DISABLE                 ((uint32_t)DMA_REG_BIT_FIELD_MASK)

/** DMA channel enable definition **/
#define DMA_CHANNEL_ENABLE              ((uint32_t)DMA_CHCFG1_CHEN)
#define DMA_CHANNEL_DISABLE             (~((uint32_t)DMA_CHCFG1_CHEN))

/** DMA burst mode definition **/
#define DMA_BURST_MODE_MASK             (~(uint32_t)DMA_CHCFG1_BURST_DYNAMIC)
#define DMA_BURST_MODE_ALMOST           ((uint32_t)DMA_CHCFG1_BURST_ALMOST)
#define DMA_BURST_MODE_DYNAMIC          ((uint32_t)DMA_CHCFG1_BURST_DYNAMIC)


/** DMA burst mode enable definition **/
#define DMA_BURST_BYPASS_ENABLE         ((uint32_t)DMA_REG_BIT_FIELD_MASK)
#define DMA_BURST_BYPASS_DISABLE        ((uint32_t)DMA_BURSTEN_BURST_BYPASS)

/** DMA burst len definition **/
#define  DMA_BURST_LEN_MASK             (~DMA_CHCFG1_BURST_BLEN)         
#define  DMA_BURST_LEN_SINGLE           (DMA_REG_BIT_FIELD_MASK)           
#define  DMA_BURST_LEN_1                (DMA_CHCFG1_BURST_BLEN_0     )            
#define  DMA_BURST_LEN_2                (DMA_CHCFG1_BURST_BLEN_1     )            
#define  DMA_BURST_LEN_3                (DMA_CHCFG1_BURST_BLEN_0 | DMA_CHCFG1_BURST_BLEN_1     )            
#define  DMA_BURST_LEN_4                (DMA_CHCFG1_BURST_BLEN_2     )            
#define  DMA_BURST_LEN_5                (DMA_CHCFG1_BURST_BLEN_0 | DMA_CHCFG1_BURST_BLEN_2     )            
#define  DMA_BURST_LEN_6                (DMA_CHCFG1_BURST_BLEN_1 | DMA_CHCFG1_BURST_BLEN_2     )            
#define  DMA_BURST_LEN_7                (DMA_CHCFG1_BURST_BLEN_0 | DMA_CHCFG1_BURST_BLEN_1 | DMA_CHCFG1_BURST_BLEN_2    )            
#define  DMA_BURST_LEN_8                (DMA_CHCFG1_BURST_BLEN     )            

/** DMA interrupts definition **/
#define DMA_INT_TXC  ((uint32_t)DMA_CHCFG1_TXCIE) /* Transfer complete interrupt */
#define DMA_INT_HTX  ((uint32_t)DMA_CHCFG1_HTXIE) /* Half transfer interrupt */
#define DMA_INT_ERR  ((uint32_t)DMA_CHCFG1_ERRIE) /* Transfer error interrupt */

#define DMA_INT_GLB1 ((uint32_t)DMA_INTSTS_GLBF1) /* DMA channel1 global interrupt */
#define DMA_INT_TXC1 ((uint32_t)DMA_INTSTS_TXCF1) /* DMA channel1 transfer complete interrupt */
#define DMA_INT_HTX1 ((uint32_t)DMA_INTSTS_HTXF1) /* DMA channel1 half transfer interrupt */
#define DMA_INT_ERR1 ((uint32_t)DMA_INTSTS_ERRF1) /* DMA channel1 transfer error interrupt */
#define DMA_INT_GLB2 ((uint32_t)DMA_INTSTS_GLBF2) /* DMA channel2 global interrupt */
#define DMA_INT_TXC2 ((uint32_t)DMA_INTSTS_TXCF2) /* DMA channel2 transfer complete interrupt */
#define DMA_INT_HTX2 ((uint32_t)DMA_INTSTS_HTXF2) /* DMA channel2 half transfer interrupt */
#define DMA_INT_ERR2 ((uint32_t)DMA_INTSTS_ERRF2) /* DMA channel2 transfer error interrupt */
#define DMA_INT_GLB3 ((uint32_t)DMA_INTSTS_GLBF3) /* DMA channel3 global interrupt */
#define DMA_INT_TXC3 ((uint32_t)DMA_INTSTS_TXCF3) /* DMA channel3 transfer complete interrupt */
#define DMA_INT_HTX3 ((uint32_t)DMA_INTSTS_HTXF3) /* DMA channel3 half transfer interrupt */
#define DMA_INT_ERR3 ((uint32_t)DMA_INTSTS_ERRF3) /* DMA channel3 transfer error interrupt */
#define DMA_INT_GLB4 ((uint32_t)DMA_INTSTS_GLBF4) /* DMA channel4 global interrupt */
#define DMA_INT_TXC4 ((uint32_t)DMA_INTSTS_TXCF4) /* DMA channel4 transfer complete interrupt */
#define DMA_INT_HTX4 ((uint32_t)DMA_INTSTS_HTXF4) /* DMA channel4 half transfer interrupt */
#define DMA_INT_ERR4 ((uint32_t)DMA_INTSTS_ERRF4) /* DMA channel4 transfer error interrupt */
#define DMA_INT_GLB5 ((uint32_t)DMA_INTSTS_GLBF5) /* DMA channel5 global interrupt */
#define DMA_INT_TXC5 ((uint32_t)DMA_INTSTS_TXCF5) /* DMA channel5 transfer complete interrupt */
#define DMA_INT_HTX5 ((uint32_t)DMA_INTSTS_HTXF5) /* DMA channel5 half transfer interrupt */
#define DMA_INT_ERR5 ((uint32_t)DMA_INTSTS_ERRF5) /* DMA channel5 transfer error interrupt */
#define DMA_INT_GLB6 ((uint32_t)DMA_INTSTS_GLBF6) /* DMA channel6 global interrupt */
#define DMA_INT_TXC6 ((uint32_t)DMA_INTSTS_TXCF6) /* DMA channel6 transfer complete interrupt */
#define DMA_INT_HTX6 ((uint32_t)DMA_INTSTS_HTXF6) /* DMA channel6 half transfer interrupt */
#define DMA_INT_ERR6 ((uint32_t)DMA_INTSTS_ERRF6) /* DMA channel6 transfer error interrupt */
#define DMA_INT_GLB7 ((uint32_t)DMA_INTSTS_GLBF7) /* DMA channel7 global interrupt */
#define DMA_INT_TXC7 ((uint32_t)DMA_INTSTS_TXCF7) /* DMA channel7 transfer complete interrupt */
#define DMA_INT_HTX7 ((uint32_t)DMA_INTSTS_HTXF7) /* DMA channel7 half transfer interrupt */
#define DMA_INT_ERR7 ((uint32_t)DMA_INTSTS_ERRF7) /* DMA channel7 transfer error interrupt */
#define DMA_INT_GLB8 ((uint32_t)DMA_INTSTS_GLBF8) /* DMA channel8 global interrupt */
#define DMA_INT_TXC8 ((uint32_t)DMA_INTSTS_TXCF8) /* DMA channel8 transfer complete interrupt */
#define DMA_INT_HTX8 ((uint32_t)DMA_INTSTS_HTXF8) /* DMA channel8 half transfer interrupt */
#define DMA_INT_ERR8 ((uint32_t)DMA_INTSTS_ERRF8) /* DMA channel8 transfer error interrupt */

/** DMA flags definition **/
#define DMA_FLAG_GL1 ((uint32_t)DMA_INTCLR_CGLBF1) /* DMA Channel1 global flag */
#define DMA_FLAG_TC1 ((uint32_t)DMA_INTCLR_CTXCF1) /* DMA Channel1 transfer complete flag */
#define DMA_FLAG_HT1 ((uint32_t)DMA_INTCLR_CHTXF1) /* DMA Channel1 half transfer flag */
#define DMA_FLAG_TE1 ((uint32_t)DMA_INTCLR_CERRF1) /* DMA Channel1 transfer error flag */
#define DMA_FLAG_GL2 ((uint32_t)DMA_INTCLR_CGLBF2) /* DMA Channel2 global flag */
#define DMA_FLAG_TC2 ((uint32_t)DMA_INTCLR_CTXCF2) /* DMA Channel2 transfer complete flag */
#define DMA_FLAG_HT2 ((uint32_t)DMA_INTCLR_CHTXF2) /* DMA Channel2 half transfer flag */
#define DMA_FLAG_TE2 ((uint32_t)DMA_INTCLR_CERRF2) /* DMA Channel2 transfer error flag */
#define DMA_FLAG_GL3 ((uint32_t)DMA_INTCLR_CGLBF3) /* DMA Channel3 global flag */
#define DMA_FLAG_TC3 ((uint32_t)DMA_INTCLR_CTXCF3) /* DMA Channel3 transfer complete flag */
#define DMA_FLAG_HT3 ((uint32_t)DMA_INTCLR_CHTXF3) /* DMA Channel3 half transfer flag */
#define DMA_FLAG_TE3 ((uint32_t)DMA_INTCLR_CERRF3) /* DMA Channel3 transfer error flag */
#define DMA_FLAG_GL4 ((uint32_t)DMA_INTCLR_CGLBF4) /* DMA Channel4 global flag */
#define DMA_FLAG_TC4 ((uint32_t)DMA_INTCLR_CTXCF4) /* DMA Channel4 transfer complete flag */
#define DMA_FLAG_HT4 ((uint32_t)DMA_INTCLR_CHTXF4) /* DMA Channel4 half transfer flag */
#define DMA_FLAG_TE4 ((uint32_t)DMA_INTCLR_CERRF4) /* DMA Channel4 transfer error flag */
#define DMA_FLAG_GL5 ((uint32_t)DMA_INTCLR_CGLBF5) /* DMA Channel5 global flag */
#define DMA_FLAG_TC5 ((uint32_t)DMA_INTCLR_CTXCF5) /* DMA Channel5 transfer complete flag */
#define DMA_FLAG_HT5 ((uint32_t)DMA_INTCLR_CHTXF5) /* DMA Channel5 half transfer flag */
#define DMA_FLAG_TE5 ((uint32_t)DMA_INTCLR_CERRF5) /* DMA Channel5 transfer error flag */
#define DMA_FLAG_GL6 ((uint32_t)DMA_INTCLR_CGLBF6) /* DMA Channel6 global flag */
#define DMA_FLAG_TC6 ((uint32_t)DMA_INTCLR_CTXCF6) /* DMA Channel6 transfer complete flag */
#define DMA_FLAG_HT6 ((uint32_t)DMA_INTCLR_CHTXF6) /* DMA Channel6 half transfer flag */
#define DMA_FLAG_TE6 ((uint32_t)DMA_INTCLR_CERRF6) /* DMA Channel6 transfer error flag */
#define DMA_FLAG_GL7 ((uint32_t)DMA_INTCLR_CGLBF7) /* DMA Channel7 global flag */
#define DMA_FLAG_TC7 ((uint32_t)DMA_INTCLR_CTXCF7) /* DMA Channel7 transfer complete flag */
#define DMA_FLAG_HT7 ((uint32_t)DMA_INTCLR_CHTXF7) /* DMA Channel7 half transfer flag */
#define DMA_FLAG_TE7 ((uint32_t)DMA_INTCLR_CERRF7) /* DMA Channel7 transfer error flag */
#define DMA_FLAG_GL8 ((uint32_t)DMA_INTCLR_CGLBF8) /* DMA Channel8 global flag */
#define DMA_FLAG_TC8 ((uint32_t)DMA_INTCLR_CTXCF8) /* DMA Channel8 transfer complete flag */
#define DMA_FLAG_HT8 ((uint32_t)DMA_INTCLR_CHTXF8) /* DMA Channel8 half transfer flag */
#define DMA_FLAG_TE8 ((uint32_t)DMA_INTCLR_CERRF8) /* DMA Channel8 transfer error flag */


/** DMA remap channel request definition **/
#define DMA_REMAP_ADC1         ((uint32_t)0x00000000U)
#define DMA_REMAP_ADC2         ((uint32_t)0x00000001U)
#define DMA_REMAP_ADC3         ((uint32_t)0x00000002U)
#define DMA_REMAP_ADC4         ((uint32_t)0x00000003U)
#define DMA_REMAP_USART1_TX    ((uint32_t)0x00000004U)
#define DMA_REMAP_USART1_RX    ((uint32_t)0x00000005U)
#define DMA_REMAP_USART2_TX    ((uint32_t)0x00000006U)
#define DMA_REMAP_USART2_RX    ((uint32_t)0x00000007U)
#define DMA_REMAP_USART3_TX    ((uint32_t)0x00000008U)
#define DMA_REMAP_USART3_RX    ((uint32_t)0x00000009U)
#define DMA_REMAP_USART4_TX    ((uint32_t)0x0000000AU)
#define DMA_REMAP_USART4_RX    ((uint32_t)0x0000000BU)
#define DMA_REMAP_UART5_TX     ((uint32_t)0x0000000CU)
#define DMA_REMAP_UART5_RX     ((uint32_t)0x0000000DU)
#define DMA_REMAP_UART6_TX     ((uint32_t)0x0000000EU)
#define DMA_REMAP_UART6_RX     ((uint32_t)0x0000000FU)
#define DMA_REMAP_UART7_TX     ((uint32_t)0x00000010U)
#define DMA_REMAP_UART7_RX     ((uint32_t)0x00000011U)
#define DMA_REMAP_UART8_TX     ((uint32_t)0x00000012U)
#define DMA_REMAP_UART8_RX     ((uint32_t)0x00000013U)
#define DMA_REMAP_SPI1_TX      ((uint32_t)0x00000014U)
#define DMA_REMAP_SPI1_RX      ((uint32_t)0x00000015U)
#define DMA_REMAP_SPI2_I2S2_TX ((uint32_t)0x00000016U)
#define DMA_REMAP_SPI2_I2S2_RX ((uint32_t)0x00000017U)
#define DMA_REMAP_TTCAN1       ((uint32_t)0x00000018U)
#define DMA_REMAP_TTCAN2       ((uint32_t)0x00000019U)
#define DMA_REMAP_SPI3_I2S3_TX ((uint32_t)0x0000001AU)
#define DMA_REMAP_SPI3_I2S3_RX ((uint32_t)0x0000001BU)
#define DMA_REMAP_TTCAN3       ((uint32_t)0x0000001CU)
#define DMA_REMAP_RES          ((uint32_t)0x0000001DU)
#define DMA_REMAP_SPI4_TX      ((uint32_t)0x0000001EU)
#define DMA_REMAP_SPI4_RX      ((uint32_t)0x0000001FU)
#define DMA_REMAP_SPI5_TX      ((uint32_t)0x00000020U)
#define DMA_REMAP_SPI5_RX      ((uint32_t)0x00000021U)
#define DMA_REMAP_SPI6_TX      ((uint32_t)0x00000022U)
#define DMA_REMAP_SPI6_RX      ((uint32_t)0x00000023U)
#define DMA_REMAP_XSPI_TX      ((uint32_t)0x00000024U)
#define DMA_REMAP_XSPI_RX      ((uint32_t)0x00000025U)
#define DMA_REMAP_I2C1_TX      ((uint32_t)0x00000026U)
#define DMA_REMAP_I2C1_RX      ((uint32_t)0x00000027U)
#define DMA_REMAP_I2C2_TX      ((uint32_t)0x00000028U)
#define DMA_REMAP_I2C2_RX      ((uint32_t)0x00000029U)
#define DMA_REMAP_I2C3_TX      ((uint32_t)0x0000002AU)
#define DMA_REMAP_I2C3_RX      ((uint32_t)0x0000002BU)
#define DMA_REMAP_I2C4_TX      ((uint32_t)0x0000002CU)
#define DMA_REMAP_I2C4_RX      ((uint32_t)0x0000002DU)
#define DMA_REMAP_SDIO_DMA     ((uint32_t)0x0000002EU)
#define DMA_REMAP_DAC1_DMA     ((uint32_t)0x0000002FU)
#define DMA_REMAP_DAC2_DMA     ((uint32_t)0x00000030U)
#define DMA_REMAP_DAC3_DMA     ((uint32_t)0x00000031U)
#define DMA_REMAP_DAC4_DMA     ((uint32_t)0x00000032U)
#define DMA_REMAP_DAC5_DMA     ((uint32_t)0x00000033U)
#define DMA_REMAP_DAC6_DMA     ((uint32_t)0x00000034U)
#define DMA_REMAP_DAC7_DMA     ((uint32_t)0x00000035U)
#define DMA_REMAP_DAC8_DMA     ((uint32_t)0x00000036U)
#define DMA_REMAP_FMAC_WR      ((uint32_t)0x00000037U)
#define DMA_REMAP_FMAC_RD      ((uint32_t)0x00000038U)
#define DMA_REMAP_CORDIC_WR    ((uint32_t)0x00000039U)
#define DMA_REMAP_CORDIC_RD    ((uint32_t)0x0000003AU)
#define DMA_REMAP_BTIM1_UP     ((uint32_t)0x0000003BU)
#define DMA_REMAP_BTIM2_UP     ((uint32_t)0x0000003CU)
#define DMA_REMAP_GTIM1_CH1    ((uint32_t)0x0000003DU)
#define DMA_REMAP_GTIM1_CH2    ((uint32_t)0x0000003EU)
#define DMA_REMAP_GTIM1_CH3    ((uint32_t)0x0000003FU)
#define DMA_REMAP_GTIM1_CH4    ((uint32_t)0x00000040U)
#define DMA_REMAP_GTIM1_UP     ((uint32_t)0x00000041U)
#define DMA_REMAP_GTIM1_TRIG   ((uint32_t)0x00000042U)
#define DMA_REMAP_GTIM2_CH1    ((uint32_t)0x00000043U)
#define DMA_REMAP_GTIM2_CH2    ((uint32_t)0x00000044U)
#define DMA_REMAP_GTIM2_CH3    ((uint32_t)0x00000045U)
#define DMA_REMAP_GTIM2_CH4    ((uint32_t)0x00000046U)
#define DMA_REMAP_GTIM2_UP     ((uint32_t)0x00000047U)
#define DMA_REMAP_GTIM2_TRIG   ((uint32_t)0x00000048U)
#define DMA_REMAP_GTIM3_CH1    ((uint32_t)0x00000049U)
#define DMA_REMAP_GTIM3_CH2    ((uint32_t)0x0000004AU)
#define DMA_REMAP_GTIM3_CH3    ((uint32_t)0x0000004BU)
#define DMA_REMAP_GTIM3_CH4    ((uint32_t)0x0000004CU)
#define DMA_REMAP_GTIM3_UP     ((uint32_t)0x0000004DU)
#define DMA_REMAP_GTIM3_TRIG   ((uint32_t)0x0000004EU)
#define DMA_REMAP_GTIM4_CH1    ((uint32_t)0x0000004FU)
#define DMA_REMAP_GTIM4_CH2    ((uint32_t)0x00000050U)
#define DMA_REMAP_GTIM4_CH3    ((uint32_t)0x00000051U)
#define DMA_REMAP_GTIM4_CH4    ((uint32_t)0x00000052U)
#define DMA_REMAP_GTIM4_UP     ((uint32_t)0x00000053U)
#define DMA_REMAP_GTIM4_TRIG   ((uint32_t)0x00000054U)
#define DMA_REMAP_GTIM5_CH1    ((uint32_t)0x00000055U)
#define DMA_REMAP_GTIM5_CH2    ((uint32_t)0x00000056U)
#define DMA_REMAP_GTIM5_CH3    ((uint32_t)0x00000057U)
#define DMA_REMAP_GTIM5_CH4    ((uint32_t)0x00000058U)
#define DMA_REMAP_GTIM5_UP     ((uint32_t)0x00000059U)
#define DMA_REMAP_GTIM5_TRIG   ((uint32_t)0x0000005AU)
#define DMA_REMAP_GTIM6_CH1    ((uint32_t)0x0000005BU)
#define DMA_REMAP_GTIM6_CH2    ((uint32_t)0x0000005CU)
#define DMA_REMAP_GTIM6_CH3    ((uint32_t)0x0000005DU)
#define DMA_REMAP_GTIM6_CH4    ((uint32_t)0x0000005EU)
#define DMA_REMAP_GTIM6_UP     ((uint32_t)0x0000005FU)
#define DMA_REMAP_GTIM6_TRIG   ((uint32_t)0x00000060U)
#define DMA_REMAP_GTIM7_CH1    ((uint32_t)0x00000061U)
#define DMA_REMAP_GTIM7_CH2    ((uint32_t)0x00000062U)
#define DMA_REMAP_GTIM7_CH3    ((uint32_t)0x00000063U)
#define DMA_REMAP_GTIM7_CH4    ((uint32_t)0x00000064U)
#define DMA_REMAP_GTIM7_UP     ((uint32_t)0x00000065U)
#define DMA_REMAP_GTIM7_TRIG   ((uint32_t)0x00000066U)
#define DMA_REMAP_GTIM8_CH1    ((uint32_t)0x00000067U)
#define DMA_REMAP_GTIM8_CH2    ((uint32_t)0x00000068U)
#define DMA_REMAP_GTIM8_CH3    ((uint32_t)0x00000069U)
#define DMA_REMAP_GTIM8_CH4    ((uint32_t)0x0000006AU)
#define DMA_REMAP_GTIM8_COM    ((uint32_t)0x0000006BU)
#define DMA_REMAP_GTIM8_UP     ((uint32_t)0x0000006CU)
#define DMA_REMAP_GTIM8_TRIG   ((uint32_t)0x0000006DU)
#define DMA_REMAP_GTIM9_CH1    ((uint32_t)0x0000006EU)
#define DMA_REMAP_GTIM9_CH2    ((uint32_t)0x0000006FU)
#define DMA_REMAP_GTIM9_CH3    ((uint32_t)0x00000070U)
#define DMA_REMAP_GTIM9_CH4    ((uint32_t)0x00000071U)
#define DMA_REMAP_GTIM9_COM    ((uint32_t)0x00000072U)
#define DMA_REMAP_GTIM9_UP     ((uint32_t)0x00000073U)
#define DMA_REMAP_GTIM9_TRIG   ((uint32_t)0x00000074U)
#define DMA_REMAP_GTIM10_CH1   ((uint32_t)0x00000075U)
#define DMA_REMAP_GTIM10_CH2   ((uint32_t)0x00000076U)
#define DMA_REMAP_GTIM10_CH3   ((uint32_t)0x00000077U)
#define DMA_REMAP_GTIM10_CH4   ((uint32_t)0x00000078U)
#define DMA_REMAP_GTIM10_COM   ((uint32_t)0x00000079U)
#define DMA_REMAP_GTIM10_UP    ((uint32_t)0x0000007AU)
#define DMA_REMAP_GTIM10_TRIG  ((uint32_t)0x0000007BU)
#define DMA_REMAP_ATIM1_CH1    ((uint32_t)0x0000007CU)
#define DMA_REMAP_ATIM1_CH2    ((uint32_t)0x0000007DU)
#define DMA_REMAP_ATIM1_CH3    ((uint32_t)0x0000007EU)
#define DMA_REMAP_ATIM1_CH4    ((uint32_t)0x0000007FU)
#define DMA_REMAP_ATIM1_COM    ((uint32_t)0x00000080U)
#define DMA_REMAP_ATIM1_UP     ((uint32_t)0x00000081U)
#define DMA_REMAP_ATIM1_TRIG   ((uint32_t)0x00000082U)
#define DMA_REMAP_ATIM2_CH1    ((uint32_t)0x00000083U)
#define DMA_REMAP_ATIM2_CH2    ((uint32_t)0x00000084U)
#define DMA_REMAP_ATIM2_CH3    ((uint32_t)0x00000085U)
#define DMA_REMAP_ATIM2_CH4    ((uint32_t)0x00000086U)
#define DMA_REMAP_ATIM2_COM    ((uint32_t)0x00000087U)
#define DMA_REMAP_ATIM2_UP     ((uint32_t)0x00000088U)
#define DMA_REMAP_ATIM2_TRIG   ((uint32_t)0x00000089U)
#define DMA_REMAP_ATIM3_CH1    ((uint32_t)0x0000008AU)
#define DMA_REMAP_ATIM3_CH2    ((uint32_t)0x0000008BU)
#define DMA_REMAP_ATIM3_CH3    ((uint32_t)0x0000008CU)
#define DMA_REMAP_ATIM3_CH4    ((uint32_t)0x0000008DU)
#define DMA_REMAP_ATIM3_COM    ((uint32_t)0x0000008EU)
#define DMA_REMAP_ATIM3_UP     ((uint32_t)0x0000008FU)
#define DMA_REMAP_ATIM3_TRIG   ((uint32_t)0x00000090U)
#define DMA_REMAP_SHRTIM1_CH1  ((uint32_t)0x00000091U)
#define DMA_REMAP_SHRTIM1_CH2  ((uint32_t)0x00000092U)
#define DMA_REMAP_SHRTIM1_CH3  ((uint32_t)0x00000093U)
#define DMA_REMAP_SHRTIM1_CH4  ((uint32_t)0x00000094U)
#define DMA_REMAP_SHRTIM1_CH5  ((uint32_t)0x00000095U)
#define DMA_REMAP_SHRTIM1_CH6  ((uint32_t)0x00000096U)
#define DMA_REMAP_SHRTIM1_CH7  ((uint32_t)0x00000097U)

/*** DMA Macro Definition End ***/

/** DMA Private Defines **/

/* DMA1 Channelx interrupt pending bit masks */
#define DMA_CH1_INT_MASK    ((uint32_t)(DMA_INTSTS_GLBF1 | DMA_INTSTS_TXCF1 | DMA_INTSTS_HTXF1 | DMA_INTSTS_ERRF1))
#define DMA_CH2_INT_MASK    ((uint32_t)(DMA_INTSTS_GLBF2 | DMA_INTSTS_TXCF2 | DMA_INTSTS_HTXF2 | DMA_INTSTS_ERRF2))
#define DMA_CH3_INT_MASK    ((uint32_t)(DMA_INTSTS_GLBF3 | DMA_INTSTS_TXCF3 | DMA_INTSTS_HTXF3 | DMA_INTSTS_ERRF3))
#define DMA_CH4_INT_MASK    ((uint32_t)(DMA_INTSTS_GLBF4 | DMA_INTSTS_TXCF4 | DMA_INTSTS_HTXF4 | DMA_INTSTS_ERRF4))
#define DMA_CH5_INT_MASK    ((uint32_t)(DMA_INTSTS_GLBF5 | DMA_INTSTS_TXCF5 | DMA_INTSTS_HTXF5 | DMA_INTSTS_ERRF5))
#define DMA_CH6_INT_MASK    ((uint32_t)(DMA_INTSTS_GLBF6 | DMA_INTSTS_TXCF6 | DMA_INTSTS_HTXF6 | DMA_INTSTS_ERRF6))
#define DMA_CH7_INT_MASK    ((uint32_t)(DMA_INTSTS_GLBF7 | DMA_INTSTS_TXCF7 | DMA_INTSTS_HTXF7 | DMA_INTSTS_ERRF7))
#define DMA_CH8_INT_MASK    ((uint32_t)(DMA_INTSTS_GLBF8 | DMA_INTSTS_TXCF8 | DMA_INTSTS_HTXF8 | DMA_INTSTS_ERRF8))


/* DMA CHCFGx registers Masks, MEM2MEM, PRIOLVL, MSIZE, PSIZE, MINC, PINC, CIRC and DIR bits */
#define CHCFG_CLEAR_MASK           ((uint32_t)0xFFF8000FU)
/*** DMA Private Definition End ***/


/*** DMA Driving Functions Declaration ***/
void DMA_DeInit(DMA_ChannelType* DMAChx);
void DMA_Init(DMA_ChannelType* DMAChx, DMA_InitType* DMA_InitParam);
void DMA_StructInit(DMA_InitType* DMA_InitParam);
void DMA_EnableChannel(DMA_ChannelType* DMAChx, FunctionalState Cmd);
void DMA_ConfigInt(DMA_ChannelType* DMAChx, uint32_t DMAInt, FunctionalState Cmd);
void DMA_SetCurrDataCounter(DMA_ChannelType* DMAChx, uint16_t DataNumber); 
uint16_t DMA_GetCurrDataCounter(DMA_ChannelType* DMAChx);
FlagStatus DMA_GetFlagStatus(uint32_t DMAy_Flag, DMA_Module *DMAy);
void DMA_ClearFlag(uint32_t DMAy_FLAG, DMA_Module *DMAy);
INTStatus DMA_GetIntStatus(uint32_t DMAy_Int, DMA_Module *DMAy);
void DMA_ClrIntPendingBit(uint32_t DMAy_Int, DMA_Module *DMAy);
void DMA_RequestRemap(uint32_t DMA_Remap, DMA_ChannelType* DMAChx, FunctionalState Cmd);

#ifdef __cplusplus
}
#endif

#endif /*__N32H47X_DMA_H__ */
