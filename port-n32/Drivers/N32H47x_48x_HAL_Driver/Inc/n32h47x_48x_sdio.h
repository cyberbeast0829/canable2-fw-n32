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
 *\*\file n32h47x_48x_sdio.h
 *\*\author Nations
 *\*\version v1.0.0
 *\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
 **/

#ifndef __N32H47X_48X_SDIO_H__
#define __N32H47X_48X_SDIO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32h47x_48x.h"

/** SDIO Init Structure Definition **/
typedef struct
{
    uint32_t ClkEdge;           /* Specifies the clock transition on which edge the bit capture is made.
                                    This parameter must be one of the following values:
                                    - SDIO_CLK_EDGE_RISING 
                                    - SDIO_CLK_EDGE_FALLING             */
    uint32_t ClkBypass;         /* Specifies whether the SDIO Clock divider bypass is enabled or disabled.
                                    This parameter must be one of the following values:
                                    - SDIO_CLK_BYPASS_DISABLE
                                    - SDIO_CLK_BYPASS_ENABLE            */
    uint32_t ClkPwrSave;        /* Specifies whether SDIO Clock output is enabled or disabled when the bus is idle.
                                    This parameter must be one of the following values:
                                    - SDIO_CLK_POWER_SAVE_DISABLE
                                    - SDIO_CLK_POWER_SAVE_ENABLE           */
    uint32_t BusWidth;          /* Specifies the SDIO bus width.
                                    This parameter must be one of the following values:
                                    - SDIO_BUS_WIDTH_1B
                                    - SDIO_BUS_WIDTH_4B
                                    - SDIO_BUS_WIDTH_8B      */
    uint32_t HardwareClkCtrl;   /* Specifies whether the SDIO hardware flow control is enabled or disabled.
                                    This parameter must be one of the following values:
                                    - SDIO_HARDWARE_CLKCTRL_DISABLE
                                    - SDIO_HARDWARE_CLKCTRL_ENABLE          */
    uint32_t ClkDiv;            /* Specifies the clock frequency of the SDIO controller.
                                    This parameter must be a value between 0x00 and 0x1FF. */

} SDIO_InitType;

/** SDIO command Structure Definition **/
typedef struct
{
    uint32_t CmdArgument;   /* Specifies the SDIO command argument which is sent
                                to a card as part of a command message. If a command
                                contains an argument, it must be loaded into this register
                                before writing the command to the command register */
    uint32_t CmdIndex;      /* Specifies the SDIO command index. It must be lower than 0x40. */
    uint32_t ResponseType;  /* Specifies the SDIO response type.
                                This parameter must be one of the following values:
                                - SDIO_RESP_NO 
                                - SDIO_RESP_SHORT
                                - SDIO_RESP_LONG            */
    uint32_t WaitType;      /* Specifies whether SDIO wait-for-interrupt request is enabled or disabled.
                                This parameter must be one of the following values: 
                                - SDIO_WAIT_NO    
                                - SDIO_WAIT_INT   
                                - SDIO_WAIT_PEND            */
    uint32_t CPSMConfig;    /* Specifies whether SDIO Command path state machine (CPSM) is enabled or disabled.
                                This parameter must be one of the following values: 
                                - SDIO_CPSM_DISABLE
                                - SDIO_CPSM_ENABLE          */
} SDIO_CmdInitType;

/** SDIO data Structure Definition **/
typedef struct
{
    uint32_t DatTimeout;        /* Specifies the data timeout period in card bus clock periods. */
    uint32_t DatLen;            /* Specifies the number of data bytes to be transferred. 
                                    This parameter must be a value between 0x0 and 0x01FFFFFF. */
    uint32_t DatBlkSize;        /* Specifies the data block size for block transfer.
                                    This parameter must be one of the following values: 
                                    - SDIO_DATBLK_SIZE_1B    
                                    - SDIO_DATBLK_SIZE_2B    
                                    - SDIO_DATBLK_SIZE_4B    
                                    - SDIO_DATBLK_SIZE_8B    
                                    - SDIO_DATBLK_SIZE_16B   
                                    - SDIO_DATBLK_SIZE_32B   
                                    - SDIO_DATBLK_SIZE_64B   
                                    - SDIO_DATBLK_SIZE_128B  
                                    - SDIO_DATBLK_SIZE_256B  
                                    - SDIO_DATBLK_SIZE_512B  
                                    - SDIO_DATBLK_SIZE_1024B 
                                    - SDIO_DATBLK_SIZE_2048B 
                                    - SDIO_DATBLK_SIZE_4096B 
                                    - SDIO_DATBLK_SIZE_8192B 
                                    - SDIO_DATBLK_SIZE_16384B  */
    uint32_t TransferDirection; /* Specifies the data transfer direction, whether the transfer is a read or write.
                                    This parameter must be one of the following values: 
                                    - SDIO_TRANSDIR_TOCARD    
                                    - SDIO_TRANSDIR_TOSDIO     */
    uint32_t TransferMode;      /* Specifies whether data transfer is in stream or block mode.
                                    This parameter must be one of the following values: 
                                    - SDIO_TRANSMODE_BLOCK         
                                    - SDIO_TRANSMODE_STREAM     */
    uint32_t DPSMConfig;        /* Specifies whether SDIO Data path state machine (DPSM) is enabled or disabled.
                                    This parameter can be a value of @ref SDIO_DPSM_State 
                                    - SDIO_DPSM_DISABLE
                                    - SDIO_DPSM_ENABLE              */  
} SDIO_DataInitType;

/*** SDIO registers bit band address define in the alias region ***/
/** SDIO register base offset **/
#define SDIO_OFFSET                 (SDIO_BASE - PERIPH_BASE)

/** Bit band base for SDIO_CLKCTRL register **/
#define SDIO_CLKCTRL_OFFSET         (SDIO_OFFSET + 0x04U)
#define SDIO_CLKCTRL_BB_BASE        (PERIPH_BB_BASE + (SDIO_CLKCTRL_OFFSET * 32U))

/* CLKEN bit */
#define SDIO_CLKEN_BIT_NUMBER       (13U)
#define SDIO_CLKEN_BB               (SDIO_CLKCTRL_BB_BASE + (SDIO_CLKEN_BIT_NUMBER * 4U))

/** Bit band base for SDIO_CMDCTRL register **/
#define SDIO_CMDCTRL_OFFSET         (SDIO_OFFSET + 0x0CU)
#define SDIO_CMDCTRL_BB_BASE        (PERIPH_BB_BASE + (SDIO_CMDCTRL_OFFSET * 32U))

/* ENCMDF bit */
#define SDIO_ENCMDF_BIT_NUMBER      (3U)
#define SDIO_ENCMDF_BB              (SDIO_CMDCTRL_BB_BASE + (SDIO_ENCMDF_BIT_NUMBER * 4U))

/* SUSPEND bit */
#define SDIO_SUSPEND_BIT_NUMBER     (4U)
#define SDIO_SUSPEND_BB             (SDIO_CMDCTRL_BB_BASE + (SDIO_SUSPEND_BIT_NUMBER * 4U))

/** Bit band base for SDIO_DATCTRL register **/
#define SDIO_DATCTRL_OFFSET         (SDIO_OFFSET + 0x2CU)
#define SDIO_DATCTRL_BB_BASE        (PERIPH_BB_BASE + (SDIO_DATCTRL_OFFSET * 32U))

/* DMAEN bit */
#define SDIO_DMAEN_BIT_NUMBER       (3U)
#define SDIO_DMAEN_BB               (SDIO_DATCTRL_BB_BASE + (SDIO_DMAEN_BIT_NUMBER * 4U))

/* RWAITEN bit */
#define SDIO_RWAITEN_BIT_NUMBER     (4U)
#define SDIO_RWAITEN_BB             (SDIO_DATCTRL_BB_BASE + (SDIO_RWAITEN_BIT_NUMBER * 4U))

/* RWAITMOD bit */
#define SDIO_RWAITMOD_BIT_NUMBER    (5U)
#define SDIO_RWAITMOD_BB            (SDIO_DATCTRL_BB_BASE + (SDIO_RWAITMOD_BIT_NUMBER * 4U))

/* RWAITSTOP bit */
#define SDIO_RWAITSTOP_BIT_NUMBER   (6U)
#define SDIO_RWAITSTOP_BB           (SDIO_DATCTRL_BB_BASE + (SDIO_RWAITSTOP_BIT_NUMBER * 4U))

/* SDIOEN bit */
#define SDIO_SDIOEN_BIT_NUMBER      (7U)
#define SDIO_SDIOEN_BB              (SDIO_DATCTRL_BB_BASE + (SDIO_SDIOEN_BIT_NUMBER * 4U))

/*** SDIO register function define ***/
/** SDIO power control define **/
#define SDIO_POWER_CTRL_OFF         ((uint32_t)0x00000000U)     /* SDIO power off, and the clock to card is stopped */
#define SDIO_POWER_CTRL_UP          (SDIO_PWRCTRL_PWRCTRL_1)    /* SDIO power up, and the clock to card is stopped  */
#define SDIO_POWER_CTRL_ON          (SDIO_PWRCTRL_PWRCTRL)      /* SDIO power on, and the card is clocked   */

/** SDIO hardware flow control define **/
#define SDIO_HARDWARE_CLKCTRL_DISABLE   ((uint32_t)0x00000000U)     /* Hardware flow control disable */
#define SDIO_HARDWARE_CLKCTRL_ENABLE    (SDIO_CLKCTRL_HWCLKEN)      /* Hardware flow control enable  */

/** SDIO clock dephasing selection define **/
#define SDIO_CLK_EDGE_RISING        ((uint32_t)0x00000000U)     /* SDIO_CLK generated on the rising edge of the master clock SDIOCLK  */
#define SDIO_CLK_EDGE_FALLING       (SDIO_CLKCTRL_CLKEDGE)      /* SDIO_CLK generated on the falling edge of the master clock SDIOCLK */

/** SDIO power saving configuration define **/
#define SDIO_CLK_POWER_SAVE_DISABLE ((uint32_t)0x00000000U)     /* Power saving disable, SDIO_CLK is always enabled */
#define SDIO_CLK_POWER_SAVE_ENABLE  (SDIO_CLKCTRL_PWRCFG)       /* Power saving enable, SDIO_CLK is only enabled when the bus is active  */

/** SDIO clock divider bypass selection define **/
#define SDIO_CLK_BYPASS_DISABLE     ((uint32_t)0x00000000U)     /* Clock diveder is enable  */
#define SDIO_CLK_BYPASS_ENABLE      (SDIO_CLKCTRL_CLKBYP)       /* Clock diveder is bypass  */

/** SDIO clock control define **/
#define SDIO_CLK_DISABLE            ((uint32_t)0x00000000U)     /* SDIO_CLK disable */
#define SDIO_CLK_ENABLE             (SDIO_CLKCTRL_CLOCKEN)      /* SDIO_CLK enable  */

/** SDIO bus width define **/
#define SDIO_BUS_WIDTH_1B           ((uint32_t)0x00000000U)     /* Card bus width is 1 bit */
#define SDIO_BUS_WIDTH_4B           (SDIO_CLKCTRL_BUSMODE_0)    /* Card bus width is 4 bit */
#define SDIO_BUS_WIDTH_8B           (SDIO_CLKCTRL_BUSMODE_1)    /* Card bus width is 8 bit */

/** SDIO CPSM control define **/
#define SDIO_CPSM_DISABLE           ((uint32_t)0x00000000U)     /* CPSM disable */
#define SDIO_CPSM_ENABLE            (SDIO_CMDCTRL_CPSMEN)       /* CPSM enable  */

/** SDIO wait control define **/
#define SDIO_WAIT_NO                ((uint32_t)0x00000000U)     /* SDIO no Wait, TimeOut is enabled */
#define SDIO_WAIT_PEND              (SDIO_CMDCTRL_WDATEND)      /* SDIO wait for the end of transfer */
#define SDIO_WAIT_INT               (SDIO_CMDCTRL_WINTREQ)      /* SDIO wait for interrupt Request */

/** SDIO command completion control define **/
#define SDIO_CMD_COMPLETE_DISABLE   ((uint32_t)0x00000000U)     /* SDIO command completion signal disable */
#define SDIO_CMD_COMPLETE_ENABLE    (SDIO_CMDCTRL_ENCMDF)       /* SDIO command completion signal enable  */

/** SDIO suspend control define, only used for SDIO card **/
#define SDIO_SUSPEND_DISABLE        ((uint32_t)0x00000000U)     /* The command to be sent is not a suspend command */
#define SDIO_SUSPEND_ENABLE         (SDIO_CMDCTRL_SUSPEND)      /* The command to be sent is a suspend command     */

/** SDIO wait for response control define **/
#define SDIO_RESP_NO                ((uint32_t)0x00000000U)     /* No response, expect CMDSEND flag */
#define SDIO_RESP_SHORT             (SDIO_CMDCTRL_CMDRESP_0)    /* Short response, expect CMDRESPRECV or CCRCERR flag  */
#define SDIO_RESP_LONG              (SDIO_CMDCTRL_CMDRESP)      /* Long response, expect CMDRESPRECV or CCRCERR flag   */

/** SDIO command index bit offset define **/
#define SDIO_CMDCTRL_CMDIDX_OFFSET  (REG_BIT8_OFFSET)

/* SDIO response registers postion define */
#define SDIO_RESPONSE_1             ((uint32_t)0x00000000U)     /* SDIO response register 1 */
#define SDIO_RESPONSE_2             ((uint32_t)0x00000004U)     /* SDIO response register 2 */
#define SDIO_RESPONSE_3             ((uint32_t)0x00000008U)     /* SDIO response register 3 */
#define SDIO_RESPONSE_4             ((uint32_t)0x0000000CU)     /* SDIO response register 4 */

/* SDIO data transfer control define */
#define SDIO_DPSM_DISABLE           ((uint32_t)0x00000000U)     /* Data transfer disable */
#define SDIO_DPSM_ENABLE            (SDIO_DATCTRL_DATEN)        /* Data transfer enable  */

/* SDIO data transfer mode selection define */
#define SDIO_TRANSMODE_BLOCK        ((uint32_t)0x00000000U)     /* Block data transfer  */
#define SDIO_TRANSMODE_STREAM       (SDIO_DATCTRL_TRANSMOD)     /* Stream or SDIO multibyte data transfer */

/* SDIO data transfer direction define */
#define SDIO_TRANSDIR_TOCARD        ((uint32_t)0x00000000U)     /* Data transfer from SDIO controller to card */
#define SDIO_TRANSDIR_TOSDIO        (SDIO_DATCTRL_DATDIR)       /* Data transfer form card to SDIO controller */

/* SDIO DMA control define */
#define SDIO_DMA_DISABLE            ((uint32_t)0x00000000U)     /* DMA disable */
#define SDIO_DMA_ENABLE             (SDIO_DATCTRL_DMAEN)        /* DMA enable  */

/* SDIO read wait control define */
#define SDIO_READ_WAIT_DISABLE      ((uint32_t)0x00000000U)     /* Read wait operation stop  */
#define SDIO_READ_WAIT_ENABLE       (SDIO_DATCTRL_RWAITEN)      /* Read wait operation start */

/* SDIO read wait mode define */
#define SDIO_RDWAIT_MODE_CLK        ((uint32_t)0x00000000U)     /* Read Wait control using SDIO_CK */
#define SDIO_RDWAIT_MODE_DAT2       ((uint32_t)0x00000001U)     /* Read Wait control stopping SDIO_DAT2 */

/* SDIO read wait stop define */
#define SDIO_READ_WAIT_IN_PROGRESS  ((uint32_t)0x00000000U)     /* Read wait in progress if RWAITEN bit is set */
#define SDIO_READ_WAIT_STOP         (SDIO_DATCTRL_RWAITSTOP)    /* Enable for read wait stop if RWAITEN bit is set */

/* SDIO I/O control define */
#define SDIO_IOCARD_DISABLE         ((uint32_t)0x00000000U)     /* SD I/O-card-specific operation disable */
#define SDIO_IOCARD_ENABLE          (SDIO_DATCTRL_SDIOEN)       /* SD I/O-card-specific operation enable */

/** SDIO data block size define **/
#define SDIO_DATBLK_SIZE_1B         (SDIO_DATCTRL_BLKSIZE_1    )  /* Data block size is 1 byte     */
#define SDIO_DATBLK_SIZE_2B         (SDIO_DATCTRL_BLKSIZE_2    )  /* Data block size is 2 byte     */
#define SDIO_DATBLK_SIZE_4B         (SDIO_DATCTRL_BLKSIZE_4    )  /* Data block size is 4 byte     */
#define SDIO_DATBLK_SIZE_8B         (SDIO_DATCTRL_BLKSIZE_8    )  /* Data block size is 8 byte     */
#define SDIO_DATBLK_SIZE_16B        (SDIO_DATCTRL_BLKSIZE_16   )  /* Data block size is 16 byte    */
#define SDIO_DATBLK_SIZE_32B        (SDIO_DATCTRL_BLKSIZE_32   )  /* Data block size is 32 byte    */
#define SDIO_DATBLK_SIZE_64B        (SDIO_DATCTRL_BLKSIZE_64   )  /* Data block size is 64 byte    */
#define SDIO_DATBLK_SIZE_128B       (SDIO_DATCTRL_BLKSIZE_128  )  /* Data block size is 128 byte   */
#define SDIO_DATBLK_SIZE_256B       (SDIO_DATCTRL_BLKSIZE_256  )  /* Data block size is 256 byte   */
#define SDIO_DATBLK_SIZE_512B       (SDIO_DATCTRL_BLKSIZE_512  )  /* Data block size is 512 byte   */
#define SDIO_DATBLK_SIZE_1024B      (SDIO_DATCTRL_BLKSIZE_1024 )  /* Data block size is 1024 byte  */
#define SDIO_DATBLK_SIZE_2048B      (SDIO_DATCTRL_BLKSIZE_2048 )  /* Data block size is 2048 byte  */
#define SDIO_DATBLK_SIZE_4096B      (SDIO_DATCTRL_BLKSIZE_4096 )  /* Data block size is 4096 byte  */
#define SDIO_DATBLK_SIZE_8192B      (SDIO_DATCTRL_BLKSIZE_8192 )  /* Data block size is 8192 byte  */
#define SDIO_DATBLK_SIZE_16384B     (SDIO_DATCTRL_BLKSIZE_16384)  /* Data block size is 16384 byte */

/** SDIO DMA direction define **/
#define SDIO_DMA_DEVICE_DATA_IN     ((uint32_t)0x00000000U)     /* Data input from external device in DMA mode */
#define SDIO_DMA_DATA_TO_DEVICE     (SDIO_DATCTRL_DMADIR)       /* Data output to external device in DMA mode  */

/** SDIO status flag define **/
#define SDIO_FLAG_CCRCERR           (SDIO_STS_CCRCERR    )      /* Command response received, and CRC check failed */
#define SDIO_FLAG_DCRCERR           (SDIO_STS_DCRCERR    )      /* Data block sent or received, and CRC check failed */
#define SDIO_FLAG_CMDTIMEOUT        (SDIO_STS_CMDTIMEOUT )      /* Command response timeout */
#define SDIO_FLAG_DATTIMEOUT        (SDIO_STS_DATTIMEOUT )      /* Data timeout */
#define SDIO_FLAG_TXURERR           (SDIO_STS_TXURERR    )      /* Transmit FIFO underrun error */
#define SDIO_FLAG_RXORERR           (SDIO_STS_RXORERR    )      /* Received FIFO overrun error */
#define SDIO_FLAG_CMDRESPRECV       (SDIO_STS_CMDRESPRECV)      /* Command response received, and CRC check passed */
#define SDIO_FLAG_CMDSEND           (SDIO_STS_CMDSEND    )      /* Command sent, and no response required */
#define SDIO_FLAG_DATEND            (SDIO_STS_DATEND     )      /* Data end (data counter register SDIDCOUNT is zero) */
#define SDIO_FLAG_SBERR             (SDIO_STS_SBERR      )      /* Start bit not detected on all data signals in wide bus mode */
#define SDIO_FLAG_DATBLKEND         (SDIO_STS_DATBLKEND  )      /* Data block sent/received, and CRC check passed */
#define SDIO_FLAG_CMDRUN            (SDIO_STS_CMDRUN     )      /* Command transfer in progress */
#define SDIO_FLAG_TXRUN             (SDIO_STS_TXRUN      )      /* Data transmit in progress */
#define SDIO_FLAG_RXRUN             (SDIO_STS_RXRUN      )      /* Data receive in progress */
#define SDIO_FLAG_TFIFOE            (SDIO_STS_TFIFOE     )      /* Transmit FIFO empty */
#define SDIO_FLAG_TFIFOHE           (SDIO_STS_TFIFOHE    )      /* Transmit FIFO half empty: at least 8 words can be written into the FIFO */
#define SDIO_FLAG_TFIFOF            (SDIO_STS_TFIFOF     )      /* Transmit FIFO full */
#define SDIO_FLAG_TDATVALID         (SDIO_STS_TDATVALID  )      /* Data available in transmit FIFO */
#define SDIO_FLAG_RFIFOE            (SDIO_STS_RFIFOE     )      /* Receive FIFO empty */
#define SDIO_FLAG_RFIFOHF           (SDIO_STS_RFIFOHF    )      /* Receive FIFO half full: there are at least 8 words in the FIFO */
#define SDIO_FLAG_RFIFOF            (SDIO_STS_RFIFOF     )      /* Receive FIFO full */
#define SDIO_FLAG_RDATVALID         (SDIO_STS_RDATVALID  )      /* Data available in receive FIFO */
#define SDIO_FLAG_SDIOINT           (SDIO_STS_SDIOINT    )      /* SDIO interrupt received */

#define SDIO_STATIC_FLAGS           ( SDIO_FLAG_CCRCERR     | SDIO_FLAG_DCRCERR     \
                                    | SDIO_FLAG_CMDTIMEOUT  | SDIO_FLAG_DATTIMEOUT  \
                                    | SDIO_FLAG_TXURERR     | SDIO_FLAG_RXORERR     \
                                    | SDIO_FLAG_CMDRESPRECV | SDIO_FLAG_CMDSEND     \
                                    | SDIO_FLAG_DATEND      | SDIO_FLAG_DATBLKEND   \
                                    | SDIO_FLAG_SDIOINT     | SDIO_FLAG_SBERR   )

#define SDIO_STATIC_CMD_FLAGS       ( SDIO_FLAG_CCRCERR     | SDIO_FLAG_CMDTIMEOUT  \
                                    | SDIO_FLAG_CMDRESPRECV | SDIO_FLAG_CMDSEND )

#define SDIO_STATIC_DATA_FLAGS      ( SDIO_FLAG_DCRCERR     | SDIO_FLAG_DATTIMEOUT  \
                                    | SDIO_FLAG_TXURERR     | SDIO_FLAG_RXORERR     \
                                    | SDIO_FLAG_DATEND      | SDIO_FLAG_DATBLKEND   \
                                    | SDIO_FLAG_SBERR   )
                                    
/** SDIO interrupt control define **/
#define SDIO_INT_CCRCERR            (SDIO_INTEN_CCRCERREN    )  /* Command CRC fail interrupt */
#define SDIO_INT_DCRCERR            (SDIO_INTEN_DCRCERREN    )  /* Data CRC fail interrupt */
#define SDIO_INT_CMDTIMEOUT         (SDIO_INTEN_CMDTIMEOUTEN )  /* Command timeout interrupt */
#define SDIO_INT_DATTIMEOUT         (SDIO_INTEN_DATTIMEOUTEN )  /* Data timeout interrupt */
#define SDIO_INT_TXURERR            (SDIO_INTEN_TXURERREN    )  /* Transmit FIFO underrun error interrupt */
#define SDIO_INT_RXORERR            (SDIO_INTEN_RXORERREN    )  /* Received FIFO overrun error interrupt */
#define SDIO_INT_CMDRESPRECV        (SDIO_INTEN_CMDRESPRECVEN)  /* Command response received interrupt */
#define SDIO_INT_CMDSEND            (SDIO_INTEN_CMDSENDEN    )  /* Command sent interrupt */
#define SDIO_INT_DATEND             (SDIO_INTEN_DATENDEN     )  /* Data end interrupt */
#define SDIO_INT_SBERR              (SDIO_INTEN_SBERREN      )  /* Start bit error interrupt */
#define SDIO_INT_DATBLKEND          (SDIO_INTEN_DATBLKENDEN  )  /* Data block end interrupt */
#define SDIO_INT_CMDRUN             (SDIO_INTEN_CMDRUNEN     )  /* Command acting interrupt */
#define SDIO_INT_TXRUN              (SDIO_INTEN_TXRUNEN      )  /* Data transmit acting interrupt */
#define SDIO_INT_RXRUN              (SDIO_INTEN_RXRUNEN      )  /* Data receive acting interrupt */
#define SDIO_INT_TFIFOE             (SDIO_INTEN_TFIFOEEN     )  /* Transmit FIFO empty interrupt */
#define SDIO_INT_TFIFOHE            (SDIO_INTEN_TFIFOHEEN    )  /* Transmit FIFO half empty interrupt */
#define SDIO_INT_TFIFOF             (SDIO_INTEN_TFIFOFEN     )  /* Transmit FIFO full interrupt */
#define SDIO_INT_TDATVALID          (SDIO_INTEN_TDATVALIDEN  )  /* Data available in transmit FIFO interrupt */
#define SDIO_INT_RFIFOE             (SDIO_INTEN_RFIFOEEN     )  /* Receive FIFO empty interrupt */
#define SDIO_INT_RFIFOHF            (SDIO_INTEN_RFIFOHFEN    )  /* Receive FIFO half full interrupt */
#define SDIO_INT_RFIFOF             (SDIO_INTEN_RFIFOFEN     )  /* Receive FIFO full interrupt */
#define SDIO_INT_RDATVALID          (SDIO_INTEN_RDATVALIDEN  )  /* Data available in receive FIFO interrupt */
#define SDIO_INT_SDIOINT            (SDIO_INTEN_SDIOINTEN    )  /* SDIO mode interrupt received interrupt */

/*** SDMMC card operation error define ***/
#define SDMMC_ERROR_NONE                            ( 0U) /* No error                                                           */
#define SDMMC_ERROR_CMD_CRC_FAIL                    ( 1U) /* Command response received (but CRC check failed)                   */
#define SDMMC_ERROR_DATA_CRC_FAIL                   ( 2U) /* Data bock sent/received (CRC check Failed)                         */
#define SDMMC_ERROR_CMD_RSP_TIMEOUT                 ( 3U) /* Command response timeout                                           */
#define SDMMC_ERROR_DATA_TIMEOUT                    ( 4U) /* Data time out                                                      */
#define SDMMC_ERROR_TX_UNDERRUN                     ( 5U) /* Transmit DATFIFO under-run                                         */
#define SDMMC_ERROR_RX_OVERRUN                      ( 6U) /* Receive DATFIFO over-run                                           */
#define SDMMC_ERROR_START_BIT_ERR                   ( 7U) /* Start bit not detected on all data signals in wide bus mode        */
#define SDMMC_ERROR_CMD_OUT_OF_RANGE                ( 8U) /* CMDCTRL's argument was out of range.                               */
#define SDMMC_ERROR_ADDR_MISALIGNED                 ( 9U) /* Misaligned address                                                 */
#define SDMMC_ERROR_BLOCK_LEN_ERR                   (10U) /* Transferred block length is not allowed for the card or the        \
                                                           number of transferred  bytes does not match the block length       */
#define SDMMC_ERROR_ERASE_SEQ_ERR                   (11U) /* An error in the sequence of erase command occurs.                  */
#define SDMMC_ERROR_BAD_ERASE_PARAM                 (12U) /* An Invalid selection for erase groups                              */
#define SDMMC_ERROR_WRITE_PROT_VIOLATION            (13U) /* Attempt to program a write protect block                           */
#define SDMMC_ERROR_LOCK_UNLOCK_FAILED              (14U) /* Sequence or password error has been detected in unlock command     \
                                                             or if there was an attempt to access a locked card                 */
#define SDMMC_ERROR_COM_CRC_FAILED                  (15U) /* CRC check of the previous command failed                           */
#define SDMMC_ERROR_ILLEGAL_CMD                     (16U) /* Command is not legal for the card state                            */
#define SDMMC_ERROR_CARD_ECC_FAILED                 (17U) /* Card internal ECC was applied but failed to correct the data       */
#define SDMMC_ERROR_CC_ERROR                        (18U) /* Internal card controller error                                     */
#define SDMMC_ERROR_GENERAL_UNKNOWN_ERROR           (19U) /* General or Unknown error                                           */
#define SDMMC_ERROR_STREAM_READ_UNDERRUN            (20U) /* The card could not sustain data transfer in stream read operation. */
#define SDMMC_ERROR_STREAM_WRITE_OVERRUN            (21U) /* The card could not sustain data programming in stream mode         */
#define SDMMC_ERROR_CID_CSD_OVERWRITE               (22U) /* CID/CSD overwrite error                                            */
#define SDMMC_ERROR_WP_ERASE_SKIP                   (23U) /* only partial address space was erased                              */
#define SDMMC_ERROR_CARD_ECC_DISABLED               (24U) /* Command has been executed without using internal ECC               */
#define SDMMC_ERROR_ERASE_RESET                     (25U) /* Erase sequence was cleared before executing because an out of      \
                                                           erase sequence command was received                                */
#define SDMMC_ERROR_AKE_SEQ_ERROR                   (26U) /* Error in sequence of authentication.                               */
#define SDMMC_ERROR_INVALID_VOLTRANGE               (27U) /* Error in case of invalid voltage range                             */
#define SDMMC_ERROR_ADDR_OUT_OF_RANGE               (28U) /* Error when addressed block is out of range                         */
#define SDMMC_ERROR_SWITCH_ERROR                    (29U) /* Card mode is not swtited as required                               */
#define SDMMC_ERROR_SDIO_DISABLED                   (30U) /* SDIO card is disabled                                              */
#define SDMMC_ERROR_SDIO_FUNCTION_BUSY              (31U) /* SDIO card is busy                                                  */
#define SDMMC_ERROR_SDIO_FUNCTION_FAILED            (32U) /* SDIO card operation failed                                         */
#define SDMMC_ERROR_SDIO_UNKNOWN_FUNCTION           (33U) /* SDIO card operation is not insupported                             */
#define SDMMC_ERROR_INTERNAL_ERROR                  (34U) /* Internal error                                                     */
#define SDMMC_ERROR_NOT_CONFIGURED                  (35U) /* Card is not active                                                 */
#define SDMMC_ERROR_REQUEST_PENDING                 (36U) /* Error when command request pending                                 */
#define SDMMC_ERROR_REQUEST_NOT_APPLICABLE          (37U) /* Error when command request is not applicable                       */
#define SDMMC_ERROR_INVALID_PARAMETER               (38U) /* the used parameter is not valid                                    */
#define SDMMC_ERROR_UNSUPPORTED_FEATURE             (39U) /* Error when feature is not insupported                              */
#define SDMMC_ERROR_UNSUPPORTED_HW                  (40U) /* Error when hardware device is not insupported                      */
#define SDMMC_ERROR_BUSY                            (41U) /* Error when transfer process is busy                                */
#define SDMMC_ERROR_DMA                             (42U) /* Error while DMA transfer                                           */
#define SDMMC_ERROR_TIMEOUT                         (43U) /* Timeout error                                                      */

/*** SDMMC Commands Index ***/
#define SDMMC_CMD_GO_IDLE_STATE                     ( 0U) /* Resets the SD memory card.                                                                 */
#define SDMMC_CMD_SEND_OP_COND                      ( 1U) /* Sends host capacity support information and activates the card's initialization process.   */
#define SDMMC_CMD_ALL_SEND_CID                      ( 2U) /* Asks any card connected to the host to send the CID numbers on the CMD line.               */
#define SDMMC_CMD_SET_REL_ADDR                      ( 3U) /* Asks the card to publish a new relative address (RCA).                                     */
#define SDMMC_CMD_SET_DSR                           ( 4U) /* Programs the DSR of all cards.                                                             */
#define SDMMC_CMD_SDIO_SEN_OP_COND                  ( 5U) /* Sends host capacity support information (HCS) and asks the accessed card to send           \
                                                             its operating condition register (OCR) content in the response on the CMD line.            */
#define SDMMC_CMD_HS_SWITCH                         ( 6U) /* Checks switchable function (mode 0) and switch card function (mode 1).                     */
#define SDMMC_CMD_SEL_DESEL_CARD                    ( 7U) /* Selects the card by its own relative address and gets deselected by any other address      */
#define SDMMC_CMD_SEND_IF_COND                      ( 8U) /* verify SD card interface operating condition */  
#define SDMMC_CMD_HS_SEND_EXT_CSD                   ( 8U) /* Sends SD Memory Card interface condition, which includes host supply voltage information   \
                                                             and asks the card whether card supports voltage.                                           */
#define SDMMC_CMD_SEND_CSD                          ( 9U) /* Addressed card sends its card specific data (CSD) on the CMD line.                         */
#define SDMMC_CMD_SEND_CID                          (10U) /* Addressed card sends its card identification (CID) on the CMD line.                        */
#define SDMMC_CMD_READ_DAT_UNTIL_STOP               (11U) /* SD card doesn't support it.                                                                */
#define SDMMC_CMD_STOP_TRANSMISSION                 (12U) /* Forces the card to stop transmission.                                                      */
#define SDMMC_CMD_SEND_STATUS                       (13U) /* Addressed card sends its status register.                                                  */
#define SDMMC_CMD_HS_BUSTEST_READ                   (14U) /* Reserved                                                                                   */
#define SDMMC_CMD_GO_INACTIVE_STATE                 (15U) /* Sends an addressed card into the inactive state.                                           */
#define SDMMC_CMD_SET_BLOCKLEN                      (16U) /* Sets the block length (in bytes for SDSC) for all following block commands(read, write,    \
                                                             lock). Default block length is fixed to 512 Bytes. Not effective for SDHS and SDXC.        */
#define SDMMC_CMD_READ_SINGLE_BLOCK                 (17U) /* Reads single block of size selected by SET_BLOCKLEN in case of SDSC, and a block of fixed  \
                                                             512 bytes in case of SDHC and SDXC.                                                        */
#define SDMMC_CMD_READ_MULT_BLOCK                   (18U) /* Continuously transfers data blocks from card to host until interrupted by                  \
                                                             STOP_TRANSMISSION command.                                                                 */
#define SDMMC_CMD_HS_BUSTEST_WRITE                  (19U) /* 64 bytes tuning pattern is sent for SDR50 and SDR104.                                      */
#define SDMMC_CMD_WRITE_DAT_UNTIL_STOP              (20U) /* Speed class control command.                                                               */
#define SDMMC_CMD_SET_BLOCK_COUNT                   (23U) /* Specify block count for CMD18 and CMD25.                                                   */
#define SDMMC_CMD_WRITE_SINGLE_BLOCK                (24U) /* Writes single block of size selected by SET_BLOCKLEN in case of SDSC, and a block of fixed \
                                                             bytes in case of SDHC and SDXC.                                                            */
#define SDMMC_CMD_WRITE_MULT_BLOCK                  (25U) /* Continuously writes blocks of data until a STOP_TRANSMISSION follows.                      */
#define SDMMC_CMD_PROG_CID                          (26U) /* Reserved for manufacturers.                                                                */
#define SDMMC_CMD_PROG_CSD                          (27U) /* Programming of the programmable bits of the CSD.                                           */
#define SDMMC_CMD_SET_WRITE_PROT                    (28U) /* Sets the write protection bit of the addressed group.                                      */
#define SDMMC_CMD_CLR_WRITE_PROT                    (29U) /* Clears the write protection bit of the addressed group.                                    */
#define SDMMC_CMD_SEND_WRITE_PROT                   (30U) /* Asks the card to send the status of the write protection bits.                             */
#define SDMMC_CMD_SD_ERASE_GRP_START                (32U) /* Sets the address of the first write block to be erased.(For SD card only).                 */
#define SDMMC_CMD_SD_ERASE_GRP_END                  (33U) /* Sets the address of the last write block of the continuous range to be erased.             */
#define SDMMC_CMD_ERASE_GRP_START                   (35U) /* Sets the address of the first write block to be erased. Reserved for each command system   \
                                                             by switch function command (CMD6).                                                         */
#define SDMMC_CMD_ERASE_GRP_END                     (36U) /* Sets the address of the last write block of the continuous range to be erased.Reserved for \
                                                             command system set by switch function command (CMD6).                                      */
#define SDMMC_CMD_ERASE                             (38U) /* Reserved for SD security applications.                                                     */
#define SDMMC_CMD_FAST_IO                           (39U) /* SD card doesn't support it (Reserved).                                                     */
#define SDMMC_CMD_GO_IRQ_STATE                      (40U) /* SD card doesn't support it (Reserved).                                                     */
#define SDMMC_CMD_LOCK_UNLOCK                       (42U) /* Sets/resets the password or lock/unlock the card. The size of the data block is set by     \
                                                             the SET_BLOCK_LEN command.                                                                 */
#define SDMMC_CMD_APP_CMD                           (55U) /* Indicates to the card that the next command is an application specific command rather than \
                                                             a standard command.                                                                        */
#define SDMMC_CMD_GEN_CMD                           (56U) /* Used either to transfer a data block to the card or to get a data block from the card for  \
                                                             general purpose/application specific commands.                                             */
#define SDMMC_CMD_NO_CMD                            (64U) /* No command                                                                                 */

/** Following commands are SD Card Specific commands.
    SDIO_APP_CMD :CMD55 should be sent before sending these commands. **/
#define SDMMC_CMD_APP_SD_SET_BUSWIDTH               ( 6U) /* (ACMD6) Defines the data bus width to be used for data transfer. The allowed data bus      \
                                                             widths are given in SCR register.                                                          */
#define SDMMC_CMD_SD_APP_STATUS                     (13U) /* (ACMD13) Sends the SD status.                                                              */
#define SDMMC_CMD_SD_APP_SEND_NUM_WRITE_BLOCKS      (22U) /* (ACMD22) Sends the number of the written (without errors) write blocks. Responds with      \
                                                             32bit+CRC data block.                                                                      */
#define SDMMC_CMD_SD_APP_OP_COND                    (41U) /* (ACMD41) Sends host capacity support information (HCS) and asks the accessed card to send  \
                                                             its operating condition register (OCR) content in the response on the CMD line.            */
#define SDMMC_CMD_SD_APP_SET_CLR_CARD_DETECT        (42U) /* (ACMD42) Connect/Disconnect the 50 KOhm pull-up resistor on CD/DAT3 (pin 1) of the card    */
#define SDMMC_CMD_SD_APP_SEND_SCR                   (51U) /* Reads the SD Configuration Register (SCR).                                                 */
#define SDMMC_CMD_SDIO_RW_DIRECT                    (52U) /* For SD I/O card only, reserved for security specification.                                 */
#define SDMMC_CMD_SDIO_RW_EXTENDED                  (53U) /* For SD I/O card only, reserved for security specification.                                 */

/** Following commands are SD Card Specific security commands.
    SDIO_APP_CMD should be sent before sending these commands. **/
#define SDMMC_CMD_SD_APP_GET_MKB                        (43U) /* For SD Card only */
#define SDMMC_CMD_SD_APP_GET_MID                        (44U) /* For SD Card only */
#define SDMMC_CMD_SD_APP_SET_CER_RN1                    (45U) /* For SD Card only */
#define SDMMC_CMD_SD_APP_GET_CER_RN2                    (46U) /* For SD Card only */
#define SDMMC_CMD_SD_APP_SET_CER_RES2                   (47U) /* For SD Card only */
#define SDMMC_CMD_SD_APP_GET_CER_RES1                   (48U) /* For SD Card only */
#define SDMMC_CMD_SD_APP_SECURE_READ_MULTIPLE_BLOCK     (18U) /* For SD Card only */
#define SDMMC_CMD_SD_APP_SECURE_WRITE_MULTIPLE_BLOCK    (25U) /* For SD Card only */
#define SDMMC_CMD_SD_APP_SECURE_ERASE                   (38U) /* For SD Card only */
#define SDMMC_CMD_SD_APP_CHANGE_SECURE_AREA             (49U) /* For SD Card only */
#define SDMMC_CMD_SD_APP_SECURE_WRITE_MKB               (48U) /* For SD Card only */

/*** SDMMC card register bits and some constant define ***/
/** Card Status bits (R1 response) define **/
#define SDMMC_R1_ADDR_OUT_OF_RANGE                  (0x80000000U)
#define SDMMC_R1_ADDR_MISALIGNED                    (0x40000000U)
#define SDMMC_R1_BLOCK_LEN_ERR                      (0x20000000U)
#define SDMMC_R1_ERASE_SEQ_ERR                      (0x10000000U)
#define SDMMC_R1_BAD_ERASE_PARAM                    (0x08000000U)
#define SDMMC_R1_WRITE_PROT_VIOLATION               (0x04000000U)
#define SDMMC_R1_CARD_LOCKED                        (0x02000000U)
#define SDMMC_R1_LOCK_UNLOCK_FAILED                 (0x01000000U)
#define SDMMC_R1_COM_CRC_FAILED                     (0x00800000U)
#define SDMMC_R1_ILLEGAL_CMD                        (0x00400000U)
#define SDMMC_R1_CARD_ECC_FAILED                    (0x00200000U)
#define SDMMC_R1_CC_ERROR                           (0x00100000U)
#define SDMMC_R1_GENERAL_UNKNOWN_ERROR              (0x00080000U)
#define SDMMC_R1_STREAM_READ_UNDERRUN               (0x00040000U)
#define SDMMC_R1_STREAM_WRITE_OVERRUN               (0x00020000U)
#define SDMMC_R1_CID_CSD_OVERWRITE                  (0x00010000U)
#define SDMMC_R1_WP_ERASE_SKIP                      (0x00008000U)
#define SDMMC_R1_CARD_ECC_DISABLED                  (0x00004000U)
#define SDMMC_R1_ERASE_RESET                        (0x00002000U)
#define SDMMC_R1_CARD_CURRENT_STATE                 (0x00001E00U)
#define SDMMC_R1_CARD_READY_FOR_DATA                (0x00000100U)
#define SDMMC_R1_CARD_UNKNOWN_ERROR                 (0x00000080U)
#define SDMMC_R1_APP_CMD                            (0x00000020U)
#define SDMMC_R1_AKE_SEQ_ERROR                      (0x00000008U)
#define SDMMC_R1_ERRORBITS                          (0xFDFFE008U)

/** SDMMC Card current state define **/
#define SDMMC_CARD_READY                            (0x00000001U) /* Card state is ready                        */
#define SDMMC_CARD_IDENTIFICATION                   (0x00000002U) /* Card is in identification state            */
#define SDMMC_CARD_STANDBY                          (0x00000003U) /* Card is in standby state                   */
#define SDMMC_CARD_TRANSFER                         (0x00000004U) /* Card is in transfer state                  */
#define SDMMC_CARD_SENDING                          (0x00000005U) /* Card is sending an operation               */
#define SDMMC_CARD_RECEIVING                        (0x00000006U) /* Card is receiving operation information    */
#define SDMMC_CARD_PROGRAMMING                      (0x00000007U) /* Card is in programming state               */
#define SDMMC_CARD_DISCONNECTED                     (0x00000008U) /* Card is disconnected                       */
#define SDMMC_CARD_ERROR                            (0x000000FFU) /* Card response Error                        */

/** Published RCA (R6 response) define **/
#define SDMMC_R6_GENERAL_UNKNOWN_ERROR              (0x00002000U)
#define SDMMC_R6_ILLEGAL_CMD                        (0x00004000U)
#define SDMMC_R6_COM_CRC_FAILED                     (0x00008000U)
#define SDMMC_R6_RCA                                (0xFFFF0000U)

/** OCR register (R3 response) define **/
#define SDMMC_VOLTAGE_WINDOW_SD                     (0x80100000U)
#define SDMMC_VOLTAGE_WINDOW_SD                     (0x80100000U)
#define SDMMC_VOLTAGE_WINDOW_MMC                    (0x00FF8000U)
#define SDMMC_CARD_POWER_UP                         (0x80000000U)
#define SDMMC_HIGH_CAPACITY                         (0x40000000U)
#define SDMMC_STD_CAPACITY                          (0x00000000U)
#define SD_SWITCH_1_8V_CAPACITY                     (0x01000000U)

/** Card interface condition (R7 response) define **/
#define SDMMC_CHECK_PATTERN                         (0x000001AAU)

/** SCR register high word define **/
#define SDMMC_SINGLE_BUS_SUPPORT                    (0x00010000U)
#define SDMMC_WIDE_BUS_SUPPORT                      (0x00040000U)
#define SDMMC_SECRRITY_VERSION                      (0x00700000U)
#define SDMMC_DATA_STAT_AFTER_ERASE                 (0x00800000U)
#define SDMMC_SD_SPEC_VERSION                       (0x0F000000U)

/** Command Class supported **/
#define SDIO_CCCC_LOCK_UNLOCK                       (0x00000080U)
#define SDIO_CCCC_WRITE_PROT                        (0x00000040U)
#define SDIO_CCCC_ERASE                             (0x00000020U)

/** SDIO constant define **/
#define SDMMC_MAX_VOLT_TRIAL                        (0x0000FFFFU)
#define SDMMC_MAX_TRIAL                             (0x0000FFFFU)
#define SDMMC_ALLZERO                               (0x00000000U)

#define SDMMC_0TO7BITS                              (0x000000FFU)
#define SDMMC_8TO15BITS                             (0x0000FF00U)
#define SDMMC_16TO23BITS                            (0x00FF0000U)
#define SDMMC_24TO31BITS                            (0xFF000000U)
#define SDMMC_MAX_DATA_LENGTH                       (0x01FFFFFFU)

/** SDMMC Lock/Unlock operation Byte0 define **/
#define SDMMC_LOCK_DATA_ERASE                       (0x08U)
#define SDMMC_LOCK_DATA_LOCK_UNLOCK                 (0x04U)
#define SDMMC_LOCK_DATA_CLR_PWD                     (0x02U)
#define SDMMC_LOCK_DATA_SET_PWD                     (0x01U)

/** SDMMC timeout define **/
#define SDMMC_CMDTIMEOUT                            (5000U)         /* Command send and response timeout */
#define SDMMC_DATATIMEOUT                           (0xFFFFFFF0U)
#define SDMMC_MAXERASETIMEOUT                       (63000U)     /* Max erase Timeout 63 s            */
#define SDMMC_STOPTRANSFERTIMEOUT                   (100000U)    /* Timeout for STOP TRANSMISSION command */

/** MMC Extended CSD regitter define **/
#define MMC_EXT_CSD_PWR_CL_26_INDEX                 (203U)
#define MMC_EXT_CSD_PWR_CL_52_INDEX                 (202U)
#define MMC_EXT_CSD_PWR_CL_DDR_52_INDEX             (239U)
#define MMC_EXT_CSD_PWR_CL_26_POS                   (24U)
#define MMC_EXT_CSD_PWR_CL_52_POS                   (16U)
#define MMC_EXT_CSD_PWR_CL_DDR_52_POS               (24U)


void SDIO_DeInit(void);
void SDIO_Init(SDIO_InitType* InitStruct);
void SDIO_InitStruct(SDIO_InitType* InitStruct);

void SDIO_EnableClock(FunctionalState Cmd);
void SDIO_SetPower(uint32_t PowerState);
uint32_t SDIO_GetPower(void);
void SDIO_ConfigInt(uint32_t Int, FunctionalState Cmd);
void SDIO_DMACmd(FunctionalState Cmd);

void SDIO_SendCmd(SDIO_CmdInitType* CmdInitStruct);
void SDIO_InitCmdStruct(SDIO_CmdInitType* CmdInitStruct);
uint8_t SDIO_GetCmdResp(void);
uint32_t SDIO_GetResp(uint32_t SDIO_RESP);

void SDIO_ConfigData(SDIO_DataInitType* DataInitStruct);
void SDIO_InitDataStruct(SDIO_DataInitType* DataInitStruct);
uint32_t SDIO_GetDataCountValue(void);
uint32_t SDIO_ReadData(void);
void SDIO_WriteData(uint32_t Data);
uint32_t SDIO_GetFifoCounter(void);

void SDIO_EnableReadWait(FunctionalState Cmd);
void SDIO_EnableReadWaitMode(uint32_t ReadWaitMode);
void SDIO_StartReadWait(void);
void SDIO_StopReadWait(void);
void SDIO_EnableSdioOperation(FunctionalState Cmd);
void SDIO_EnableSendSdioSuspend(FunctionalState Cmd);
void SDIO_EnableCommandCompletion(FunctionalState Cmd);

FlagStatus SDIO_GetFlag(uint32_t Flag);
void SDIO_ClrFlag(uint32_t FlagClr);
INTStatus SDIO_GetIntStatus(uint32_t Int);

uint32_t SDIO_CmdShortResponse1(uint8_t Cmd, uint32_t Arg, uint32_t timeout);
uint32_t SDIO_CmdShortResponse3(uint8_t Cmd, uint32_t Arg);
uint32_t SDIO_CmdLongResponse2(uint8_t Cmd, uint32_t Arg);

uint32_t SDIO_CmdBlockLength(uint32_t BlockSize);
uint32_t SDIO_CmdBlockCount(uint32_t BlockCnt);
uint32_t SDIO_CmdReadSingleBlock(uint32_t ReadAdd);
uint32_t SDIO_CmdReadMultiBlock(uint32_t ReadAdd);
uint32_t SDIO_CmdWriteSingleBlock(uint32_t WriteAdd);
uint32_t SDIO_CmdWriteMultiBlock(uint32_t WriteAdd);
uint32_t SDIO_CmdSDEraseStartAdd(uint32_t StartAdd);
uint32_t SDIO_CmdSDEraseEndAdd(uint32_t EndAdd);
uint32_t SDIO_CmdEraseStartAdd(uint32_t StartAdd);
uint32_t SDIO_CmdEraseEndAdd(uint32_t EndAdd);
uint32_t SDIO_CmdErase(void);
uint32_t SDIO_CmdLockUnlock(uint32_t Arg);
uint32_t SDIO_CmdStopTransfer(void);
uint32_t SDIO_CmdSelDesel(uint16_t RCA);
uint32_t SDIO_CmdGoIdleState(void);
uint32_t SDIO_CmdOperCond(void);
uint32_t SDIO_CmdAppCommand(uint32_t Arg);
uint32_t SDIO_CmdAppOperCommand(uint32_t Arg);
uint32_t SDIO_CmdBusWidth(uint32_t BusWidth);
uint32_t SDIO_CmdSendSCR(void);
uint32_t SDIO_CmdAllSendCID(void);
uint32_t SDIO_CmdSendCID(uint16_t RCA);
uint32_t SDIO_CmdSendCSD(uint16_t RCA);
uint32_t SDIO_CmdSetRelAdd(uint16_t *pRCA);
uint32_t SDIO_CmdSetRelAddMmc(uint16_t RCA);
uint32_t SDIO_CmdSendStatus(uint32_t Arg);
uint32_t SDIO_CmdStatusRegister(void);
uint32_t SDIO_CmdOpCondition(uint32_t Arg);
uint32_t SDIO_CmdSwitch(uint32_t Arg);
uint32_t SDIO_CmdSendEXTCSD(uint32_t Arg);

uint32_t SDIO_GetCmdResp1(uint8_t Cmd, uint32_t Timeout);
uint32_t SDIO_GetCmdResp2(void);
uint32_t SDIO_GetCmdResp3(void);
uint32_t SDIO_GetCmdResp6(uint8_t Cmd, uint16_t *pRCA);
uint32_t SDIO_GetCmdResp7(void);

#ifdef __cplusplus
}
#endif

#endif /* __N32H47X_48X_SDIO_H__ */


