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
*\*\file n32h47x_48x_flash.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/
#ifndef __N32H47X_FLASH_H__
#define __N32H47X_FLASH_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32h47x_48x.h"

/** FLASH Status **/
typedef enum
{
    FLASH_EOP = 1,
    FLASH_BUSY,
    FLASH_ERR_PG,
    FLASH_ERR_WRP,
    FLASH_ERR_PV,
    FLASH_ERR_EV,
    FLASH_ERR_RPADD,
    FLASH_ERR_RDP2,
    FLASH_ERR_ADD,
    FLASH_TIMEOUT
} FLASH_STS;


/** Flash_Latency **/
#define FLASH_LATENCY_0     ((uint32_t)FLASH_AC_LATENCY_0) /* FLASH Zero Latency cycle */
#define FLASH_LATENCY_1     ((uint32_t)FLASH_AC_LATENCY_1) /* FLASH One Latency cycle */
#define FLASH_LATENCY_2     ((uint32_t)FLASH_AC_LATENCY_2) /* FLASH Two Latency cycle */
#define FLASH_LATENCY_3     ((uint32_t)FLASH_AC_LATENCY_3) /* FLASH Three Latency cycle */
#define FLASH_LATENCY_4     ((uint32_t)FLASH_AC_LATENCY_4) /* FLASH Four Latency cycle */
#define FLASH_LATENCY_5     ((uint32_t)FLASH_AC_LATENCY_5) /* FLASH Five Latency cycle */
#define FLASH_LATENCY_MASK  ((uint32_t)FLASH_AC_LATENCY)

/** Flash Access Control Register bits **/
#define FLASH_PRFTBS_MSK                  ((uint32_t)FLASH_AC_PRFTBFSTS)
/** Prefetch_Buffer_Enable_Disable **/
#define FLASH_PrefetchBuf_EN              ((uint32_t)FLASH_AC_PRFTBFEN)            /* FLASH Prefetch Buffer Enable */
#define FLASH_PrefetchBuf_DIS             ((uint32_t)0x00000000U)         		   /* FLASH Prefetch Buffer Disable */
#define FLASH_PrefetchBuf_MSK             (~((uint32_t)FLASH_AC_PRFTBFEN))         /* FLASH Prefetch Buffer mask */


/** iCache_Enable_Disable **/
#define AC_ICAHEN_MSK                ((uint32_t)(~FLASH_AC_ICAHEN))
#define FLASH_iCache_EN              ((uint32_t)FLASH_AC_ICAHEN) /* FLASH iCache Enable */
#define FLASH_iCache_DIS             ((uint32_t)0x00000000U) /* FLASH iCache Disable */

/** FLASH Keys **/
#define FLASH_KEY1   ((uint32_t)0x45670123U)
#define FLASH_KEY2   ((uint32_t)0xCDEF89ABU)

/** CCM Keys **/
#define CCM_KEY1   ((uint32_t)0xCAU)
#define CCM_KEY2   ((uint32_t)0x53U)

/** Flash Control Register bits **/
#define CTRL_Set_LOCK           ((uint32_t)FLASH_CTRL_LOCK)
#define FLASH_CTRL_SET_OPTWE    ((uint32_t)FLASH_CTRL_OPTWE)

#define CTRL_Set_PG             ((uint32_t)FLASH_CTRL_PG)
#define CTRL_Reset_PG           (~((uint32_t)FLASH_CTRL_PG))
#define CTRL_Set_PER            ((uint32_t)FLASH_CTRL_PER)
#define CTRL_Reset_PER          (~((uint32_t)FLASH_CTRL_PER))
#define CTRL_Set_MER            ((uint32_t)FLASH_CTRL_MER)
#define CTRL_Reset_MER          (~((uint32_t)FLASH_CTRL_MER))
#define CTRL_Set_OPTPG          ((uint32_t)FLASH_CTRL_OPTPG)
#define CTRL_Reset_OPTPG        (~((uint32_t)FLASH_CTRL_OPTPG))
#define CTRL_Set_OPTER          ((uint32_t)FLASH_CTRL_OPTER)
#define CTRL_Reset_OPTER        (~((uint32_t)FLASH_CTRL_OPTER))
#define CTRL_Set_START          ((uint32_t)FLASH_CTRL_START)


/** Delay definition **/
#define EraseTimeout      ((uint32_t)0x00100000U)
#define ProgramTimeout    ((uint32_t)0x00002000U)
#define RowProgramTimeout ((uint32_t)0x00010000U)

#define FLASH_WORD_LENGTH   ((uint32_t)0x00000007U)

/** Option_Bytes_RDPx **/
#define FLASH_OB_RDP1_ENABLE            ((uint8_t)0x00U) /* Enable RDP1 */
#define FLASH_OB_RDP1_DISABLE           ((uint8_t)0xA5U) /* DISABLE RDP1 */

#define FLASH_OB_RDP2_ENABLE            ((uint8_t)0xCCU) /* Enable RDP2 */
#define FLASH_OB_RDP2_DISABLE           ((uint8_t)0x00U) /* Disable RDP2 */

/** Option_Bytes_IWatchdog **/
#define FLASH_OB_IWDG_SOFTWARE          ((uint16_t)0x0001U) /* Software IWDG selected */
#define FLASH_OB_IWDG_HARDWARE          ((uint16_t)0x0000U) /* Hardware IWDG selected */

/** Option_Bytes_nRST_STOP **/
#define FLASH_OB_STOP_NORST             ((uint16_t)0x0002U) /* No reset generated when entering in STOP */
#define FLASH_OB_STOP_RST               ((uint16_t)0x0000U) /* Reset generated when entering in STOP */

/** Option_Bytes_nRST_STDBY **/
#define FLASH_OB_STDBY_NORST            ((uint16_t)0x0004U) /* No reset generated when entering in standby */
#define FLASH_OB_STDBY_RST              ((uint16_t)0x0000U) /* Reset generated when entering in standby */

/** Option_Bytes_IWatchdog_STOP **/
#define FLASH_OB_IWDG_STOP_FRZ          ((uint16_t)0x0000U) /* IWDG freeze in stop */
#define FLASH_OB_IWDG_STOP_NOFRZ        ((uint16_t)0x0008U) /* Default no freeze */

/** Option_Bytes_IWatchdog_STDBY **/
#define FLASH_OB_IWDG_STDBY_FRZ         ((uint16_t)0x0000U) /* IWDG freeze in standby */
#define FLASH_OB_IWDG_STDBY_NOFRZ       ((uint16_t)0x0020U) /* Default no freeze */

/** Option_Bytes_IWatchdog_SLEEP **/
#define FLASH_OB_IWDG_SLEEP_FRZ         ((uint16_t)0x0000U) /* IWDG freeze in sleep */
#define FLASH_OB_IWDG_SLEEP_NOFRZ       ((uint16_t)0x0040U) /* Default no freeze */

/** USER2 **/
#define FLASH_OB2_NBOOT0_SET                ((uint8_t)0x01U) /* Set nBOOT0 */
#define FLASH_OB2_NBOOT0_CLR                ((uint8_t)0x00U) /* Clear nBOOT0 */

#define FLASH_OB2_NBOOT1_SET                ((uint8_t)0x02U) /* Set nBOOT1 */
#define FLASH_OB2_NBOOT1_CLR                ((uint8_t)0x00U) /* Clear nBOOT1 */

#define FLASH_OB2_NSWBOOT0_SET              ((uint8_t)0x04U) /* Set nSWBOOT0 */
#define FLASH_OB2_NSWBOOT0_CLR              ((uint8_t)0x00U) /* Clear nSWBOOT0 */

#define FLASH_OB2_FLASHBOOT_SET             ((uint8_t)0x08U) /* Main flash back section boot */
#define FLASH_OB2_FLASHBOOT_CLR             ((uint8_t)0x00U) /* Main flash forward part boot */

#define BOR_LEVEL_1_6V                      ((uint8_t)0x00U) /* Reset level threshold 1.6V (Up 1.66V / Down 1.62V) */
#define BOR_LEVEL_2_0V                      ((uint8_t)0x01U) /* Reset level threshold 2.0V (Up 2.1V / Down 2.0V) */
#define BOR_LEVEL_2_2V                      ((uint8_t)0x02U) /* Reset level threshold 2.2V (Up 2.3V / Down 2.2V) */
#define BOR_LEVEL_2_5V                      ((uint8_t)0x03U) /* Reset level threshold 2.5V (Up 2.6V / Down 2.5V) */
#define BOR_LEVEL_2_8V                      ((uint8_t)0x04U) /* Reset level threshold 2.8V (Up 2.9V / Down 2.8V) */

#define NRST_SEL_0_RSTIO                    ((uint8_t)0x00U) /* NRST select reset inputs and outputs */
#define NRST_SEL_1_RSTIN                    ((uint8_t)0x01U) /* NRST select reset inputs */
#define NRST_SEL_2_GPIO                     ((uint8_t)0x02U) /* NRST select GPIO */
#define NRST_SEL_3_RSTIO                    ((uint8_t)0x03U) /* NRST select reset inputs and outputs */

/** CCMSRAM_RST **/
#define CCMSRAM_RST_NERASE                  ((uint8_t)0x00U) /* CCMSRAM reset not erase */
#define CCMSRAM_RST_ERASE                   ((uint8_t)0xABU) /* CCMSRAM reset erase */

/*data0 and data1*/
#define FLASH_OB_DATA0_MASK             (FLASH_OB_DATA0_MSK)
#define FLASH_OB_DATA1_MASK             (FLASH_OB_DATA1_MSK)
#define FLASH_OB_DATA0_OFFSET           (REG_BIT12_OFFSET)
#define FLASH_OB_DATA1_OFFSET           (REG_BIT20_OFFSET)

/** Option Bytes MASK **/
#define FLASH_OB_MASK                       ((uint32_t)0xFFFFFFFFU)

/** FLASH Mask **/
#define FLASH_RDPRTL1_MSK                   ((uint32_t)FLASH_OB_RDPRT1)
#define FLASH_RDPRTL2_MSK                   ((uint32_t)FLASH_OB_RDPRT2)


/* FLASH_WRP */
#define FLASH_WRP_Pages0to1     ((uint32_t)FLASH_WRP_WRPT_0) /* Write protection of page 0 to 1 */
#define FLASH_WRP_Pages2to3     ((uint32_t)FLASH_WRP_WRPT_1) /* Write protection of page 2 to 3 */
#define FLASH_WRP_Pages4to5     ((uint32_t)FLASH_WRP_WRPT_2) /* Write protection of page 4 to 5 */
#define FLASH_WRP_Pages6to7     ((uint32_t)FLASH_WRP_WRPT_3) /* Write protection of page 6 to 7 */
#define FLASH_WRP_Pages8to9     ((uint32_t)FLASH_WRP_WRPT_4) /* Write protection of page 8 to 9 */
#define FLASH_WRP_Pages10to11   ((uint32_t)FLASH_WRP_WRPT_5) /* Write protection of page 10 to 11 */
#define FLASH_WRP_Pages12to13   ((uint32_t)FLASH_WRP_WRPT_6) /* Write protection of page 12 to 13 */
#define FLASH_WRP_Pages14to15   ((uint32_t)FLASH_WRP_WRPT_7) /* Write protection of page 14 to 15 */
#define FLASH_WRP_Pages16to17   ((uint32_t)FLASH_WRP_WRPT_8) /* Write protection of page 16 to 17 */
#define FLASH_WRP_Pages18to19   ((uint32_t)FLASH_WRP_WRPT_9) /* Write protection of page 18 to 19 */
#define FLASH_WRP_Pages20to21   ((uint32_t)FLASH_WRP_WRPT_10) /* Write protection of page 20 to 21 */
#define FLASH_WRP_Pages22to23   ((uint32_t)FLASH_WRP_WRPT_11) /* Write protection of page 22 to 23 */
#define FLASH_WRP_Pages24to25   ((uint32_t)FLASH_WRP_WRPT_12) /* Write protection of page 24 to 25 */
#define FLASH_WRP_Pages26to27   ((uint32_t)FLASH_WRP_WRPT_13) /* Write protection of page 26 to 27 */
#define FLASH_WRP_Pages28to29   ((uint32_t)FLASH_WRP_WRPT_14) /* Write protection of page 28 to 29 */
#define FLASH_WRP_Pages30to31   ((uint32_t)FLASH_WRP_WRPT_15) /* Write protection of page 30 to 31 */
#define FLASH_WRP_Pages32to33   ((uint32_t)FLASH_WRP_WRPT_16) /* Write protection of page 32 to 33 */
#define FLASH_WRP_Pages34to35   ((uint32_t)FLASH_WRP_WRPT_17) /* Write protection of page 34 to 35 */
#define FLASH_WRP_Pages36to37   ((uint32_t)FLASH_WRP_WRPT_18) /* Write protection of page 36 to 37 */
#define FLASH_WRP_Pages38to39   ((uint32_t)FLASH_WRP_WRPT_19) /* Write protection of page 38 to 39 */
#define FLASH_WRP_Pages40to41   ((uint32_t)FLASH_WRP_WRPT_20) /* Write protection of page 40 to 41 */
#define FLASH_WRP_Pages42to43   ((uint32_t)FLASH_WRP_WRPT_21) /* Write protection of page 42 to 43 */
#define FLASH_WRP_Pages44to45   ((uint32_t)FLASH_WRP_WRPT_22) /* Write protection of page 44 to 45 */
#define FLASH_WRP_Pages46to47   ((uint32_t)FLASH_WRP_WRPT_23) /* Write protection of page 46 to 47 */
#define FLASH_WRP_Pages48to49   ((uint32_t)FLASH_WRP_WRPT_24) /* Write protection of page 48 to 49 */
#define FLASH_WRP_Pages50to51   ((uint32_t)FLASH_WRP_WRPT_25) /* Write protection of page 50 to 51 */
#define FLASH_WRP_Pages52to53   ((uint32_t)FLASH_WRP_WRPT_26) /* Write protection of page 52 to 53 */
#define FLASH_WRP_Pages54to55   ((uint32_t)FLASH_WRP_WRPT_27) /* Write protection of page 54 to 55 */
#define FLASH_WRP_Pages56to57   ((uint32_t)FLASH_WRP_WRPT_28) /* Write protection of page 56 to 57 */
#define FLASH_WRP_Pages58to59   ((uint32_t)FLASH_WRP_WRPT_29) /* Write protection of page 58 to 59 */
#define FLASH_WRP_Pages60to61   ((uint32_t)FLASH_WRP_WRPT_30) /* Write protection of page 60 to 61 */
#define FLASH_WRP_Pages62to63   ((uint32_t)FLASH_WRP_WRPT_31) /* Write protection of page 62 to 63 */
#define FLASH_WRP_AllPages      ((uint32_t)FLASH_WRP_WRPT) /* Write protection of all Pages */

#define FLASH_WRP0_MSK           (FLASH_WRP0_WRP0)
#define FLASH_WRP1_MSK           (FLASH_WRP1_WRP1 >> REG_BIT8_OFFSET)
#define FLASH_WRP2_MSK           (FLASH_WRP2_WRP2 << REG_BIT16_OFFSET)
#define FLASH_WRP3_MSK           (FLASH_WRP3_WRP3 << REG_BIT8_OFFSET)

/** FLASH_Interrupts **/
#define FLASH_INT_EOP      ((uint32_t)FLASH_CTRL_EOPITE)      /* End of FLASH Operation Interrupt source */
#define FLASH_INT_ERR      ((uint32_t)FLASH_CTRL_ERRITE)      /* PGERR WRPERR ERROR interrupt source */
#define FLASH_INT_FERR     ((uint32_t)FLASH_CTRL_FERRITE)     /* EVERR PVERR ERROR interrupt source */
#define FLASH_INT_ECC1     ((uint32_t)FLASH_CTRL_EC1ERRITE)   /* 1 bit ECC error interrupt source */
#define FLASH_INT_JS       ((uint32_t)FLASH_CTRL_JSERRITE)    /* jtag seal error interrupt source */
#define FLASH_INT_ECC2     ((uint32_t)FLASH_CTRL_EC2ERRITE)   /* 2 bit ECC error interrupt source */
#define FLASH_INT_DECC     ((uint32_t)FLASH_CTRL_DECCERRITE)  /* XSPI/FEMC decryption misconfiguration interrupt source */
#define FLASH_INT_RPADD    ((uint32_t)FLASH_CTRL_RPADDERRITE) /* Row programmer address error interrupt source */

/** FLASH_Flags **/
#define FLASH_FLAG_EOP          ((uint32_t)FLASH_STS_EOP)       /* FLASH End of Operation flag */
#define FLASH_FLAG_BUSY         ((uint32_t)FLASH_STS_BUSY)      /* FLASH Busy flag */
#define FLASH_FLAG_PGERR        ((uint32_t)FLASH_STS_PGERR)     /* FLASH Program error flag */
#define FLASH_FLAG_WRPERR       ((uint32_t)FLASH_STS_WRPERR)    /* FLASH Write protected error flag */
#define FLASH_FLAG_PVERR        ((uint32_t)FLASH_STS_PVERR)     /* FLASH Program Verify ERROR flag after program */
#define FLASH_FLAG_EVERR        ((uint32_t)FLASH_STS_EVERR)     /* FLASH Erase Verify ERROR flag after page erase */
#define FLASH_FLAG_ECC1ERR      ((uint32_t)FLASH_STS_ECC1ERR)   /* FLASH 1 bit ECC error flag */
#define FLASH_FLAG_RDKEYERR     ((uint32_t)FLASH_STS_RDKEYERR)  /* read key error flag */
#define FLASH_FLAG_RDXKEYERR    ((uint32_t)FLASH_STS_RDXKEYERR) /* xKEY match error flag */
#define FLASH_FLAG_NRDXKEYEN    ((uint32_t)FLASH_STS_NRDXKEYEN) /* Not allowed to read RTPD_KEY enable flag */
#define FLASH_FLAG_JSERR        ((uint32_t)FLASH_STS_JSERR)     /* JTAG/SRAM access JTAG_SEAL error flag */
#define FLASH_FLAG_RTPKEYERR    ((uint32_t)FLASH_STS_RTPKEYERR) /* read RTPD_KEY error flag */
#define FLASH_FLAG_ECC2ERR      ((uint32_t)FLASH_STS_ECC2ERR)   /* FLASH 2 bit ECC error flag */
#define FLASH_FLAG_DECCRDF      ((uint32_t)FLASH_STS_DECCRDF)   /* XSPI/FEMC Decryption Configuration Completion Flag */
#define FLASH_FLAG_DECCERR      ((uint32_t)FLASH_STS_DECCERR)   /* XSPI/FEMC Decryption Configuration sequences error Flag */
#define FLASH_FLAG_FWORDF       ((uint32_t)FLASH_STS_FWORDF)    /* first word write completion flag */
#define FLASH_FLAG_RPADDERR     ((uint32_t)FLASH_STS_RPADDERR)  /* row programmmer address error */
#define FLASH_FLAG_OBERR        ((uint32_t)FLASH_OB_OBERR)      /* FLASH Option Byte error flag */

#define FLASH_STS_CLRFLAG   (FLASH_FLAG_PGERR | FLASH_FLAG_PVERR |\
                             FLASH_FLAG_WRPERR | FLASH_FLAG_EOP |\
                             FLASH_FLAG_EVERR | FLASH_FLAG_RPADDERR)

/** Option_Bytes_RDPx **/
#define FLASH_ROW_MASK                  ((uint32_t)FLASH_ROWP_RPADD_MASK)  /* row programmer address Mask */
#define FLASH_ROW_RPNUM_MASK            ((uint32_t)~FLASH_ROWP_RPNUM_MASK)  /* row programmer number Mask */
#define FLASH_ROW_ENABLE                ((uint32_t)FLASH_ROWP_RPEN)        /* Enable Row programmer */
#define FLASH_ROW_DISABLE               ((uint32_t)(~FLASH_ROWP_RPEN))     /* Disable Row programmer */
#define FLASH_ROW_SYSTEMMEMORY          ((uint32_t)FLASH_ROWP_RPAREA)        /* Row programmer in system memory */
#define FLASH_ROW_MAINFLASH             ((uint32_t)(~FLASH_ROWP_RPAREA))     /* Row programmer in main flash */

/** CCM **/
#define CCM_ERASE_ENABLE                ((uint32_t)CCM_ERASE_EN)
#define CCM_ERASE_STSMSK                ((uint32_t)CCM_ERASE_BUSY)
#define CCM_MODE_ENABLE                 ((uint32_t)CCM_MODE_EN)
#define XSPI_FEMC_DES_ENABLE            ((uint32_t)XSPI_FEMC_DEN_EN)

#define JTAG_SEAL_ENABLE                ((uint8_t)0x5AU) /* Enable JTAG_SEAL */
#define JTAG_SEAL_DISABLE               ((uint8_t)0x00U) /* DISABLE JTAG_SEAL */

/** FLASH_Exported_Functions **/

void FLASH_SetLatency(uint32_t FLASH_Latency);
uint8_t FLASH_GetLatency(void);
void FLASH_PrefetchBufSet(uint32_t FLASH_PrefetchBuf);
void FLASH_iCacheRST(void);
void FLASH_iCacheCmd(uint32_t FLASH_iCache);
void FLASH_Unlock(void);
void FLASH_Lock(void);
FlagStatus Flash_GetLockStatus(void);
void Option_Bytes_Unlock(void);
void Option_Bytes_Lock(void);
FlagStatus OB_GetLockStatus(void);
FLASH_STS FLASH_EraseOnePage(uint32_t Page_Address);
FLASH_STS FLASH_MassErase(void);
FLASH_STS FLASH_ProgramdoubleWord(uint32_t address, uint32_t data0,uint32_t data1);
void FLASH_RowProgramSet(FunctionalState Cmd);
void FLASH_RowProgramAreaSet(FunctionalState Cmd);
FLASH_STS FLASH_RowProgram(uint32_t address, uint32_t row_num, uint32_t *data);
FLASH_STS FLASH_EraseOB(void);
FLASH_STS FLASH_ProgramOB_RUDD(uint32_t option_byte_rpd1, uint32_t option_byte_iwdg, uint32_t option_byte_stop,\
                               uint32_t option_byte_stdby, uint32_t option_byte_iwdg_stop, uint32_t option_byte_iwdg_stdby,\
                               uint32_t option_byte_iwdg_sleep, uint32_t option_byte_data0, uint32_t option_byte_data1);
uint32_t FLASH_GetOptionBytes_Data0(void);
uint32_t FLASH_GetOptionBytes_Data1(void);
FLASH_STS FLASH_EnWriteProtection(uint32_t FLASH_Pages);
FLASH_STS FLASH_ProgramOB_RU2U3(uint32_t option_byte_rpd2, uint32_t option_byte2_nBOOT0, uint32_t option_byte2_nBOOT1,\
                               uint32_t option_byte2_nSWBOOT0, uint32_t option_byte2_FlashBoot, \
                               uint32_t option_byte2_BOR, uint32_t option_byte3_NRST);
FLASH_STS FLASH_ProgramOB_CCMSRAM(uint32_t option_byte_CCMSRAM);
FLASH_STS FLASH_ReadOutProtectionL1(FunctionalState Cmd);
FLASH_STS FLASH_ReadOutProtectionL2_ENABLE(void);
uint32_t FLASH_GetUserOB(void);
FlagStatus FLASH_GetUser2(uint32_t option_byte_bit);
uint32_t FLASH_GetWriteProtectionSTS(void);
FlagStatus FLASH_GetReadOutProtectionSTS(void);
FlagStatus FLASH_GetReadOutProtectionL2STS(void);
FlagStatus FLASH_GetPrefetchBufSTS(void);
void FLASH_INTConfig(uint32_t FLASH_INT, FunctionalState Cmd);
FlagStatus FLASH_GetFlagSTS(uint32_t FLASH_FLAG);
void FLASH_ClearFlag(uint32_t FLASH_FLAG);
FLASH_STS FLASH_GetSTS(void);
FLASH_STS FLASH_WaitForLastOpt(uint32_t Timeout);
void CCM_EnWriteProtection(uint32_t CCM_Pages);
uint32_t CCM_GetWriteProtectionSTS(void);
void CCM_Earse_Unlock(void);
void CCM_EarseEN(void);
FlagStatus CCM_EarseSTS(void);
void CCM_ModeSet(FunctionalState Cmd);
void XSPI_DESRangeSet(uint32_t start_add,uint32_t end_add);
void FEMC_DESRangeSet(uint32_t start_add,uint32_t end_add);
void RTP_DESKeySet(uint32_t* DES_key);
uint32_t GetRTP_DESKeyWnum(void);
void Jtag_SealSet(FunctionalState Cmd);
void XSPI_FEMC_DESSet(FunctionalState Cmd);
uint32_t Get_XFUID(void);
uint32_t Get_CCMUID(void);

#ifdef __cplusplus
}
#endif

#endif /* __N32H47X_FLASH_H__ */

