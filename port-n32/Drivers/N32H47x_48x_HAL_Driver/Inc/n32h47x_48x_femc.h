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
*\*\file n32h47x_48x_femc.H
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/
#ifndef __N32H47X_FEMC_H__
#define __N32H47X_FEMC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32h47x_48x.h"


/** Timing parameters For NOR/SRAM Banks **/
typedef struct
{
    uint32_t AddrSetTime;       /* Defines the number of HCLK cycles to configure
                                    the duration of the address setup time.
                                    This parameter can be a value between 0 and 0xF.
                                    @note: It is not used with synchronous NOR Flash memories. */

    uint32_t AddrHoldTime;      /* Defines the number of HCLK cycles to configure
                                    the duration of the address hold time.
                                    This parameter can be a value between 0 and 0xF.
                                    @note: It is not used with synchronous NOR Flash memories.*/

    uint32_t DataSetTime;       /* Defines the number of HCLK cycles to configure
                                    the duration of the data setup time.
                                    This parameter can be a value between 1 and 0xFF.
                                    @note: It is used for SRAMs, ROMs and asynchronous multiplexed NOR Flash memories. */

    uint32_t BusRecoveryCycle;  /* Defines the number of HCLK cycles to configure 
                                    the duration of the bus turnaround.
                                    This parameter can be a value between 0 and 0xF.
                                    @note: It is only used for multiplexed NOR Flash memories. */

    uint32_t ClkDiv;            /* Defines the period of CLK clock output signal, expressed in number of HCLK cycles.
                                    This parameter can be a value between 1 and 0xF.
                                    @note: This parameter is not used for asynchronous NOR Flash, SRAM or ROM accesses. */

    uint32_t DataHoldTime;      /* Defines the number of memory clock cycles to issue
                                    to the memory before getting the first data.
                                    The value of this parameter depends on the memory type as shown below:
                                    - It must be set to 0 in case of a CRAM
                                    - It is don't care in asynchronous NOR, SRAM or ROM accesses
                                    - It may assume a value between 0 and 0xF in NOR Flash memories
                                      with synchronous burst mode enable */

    uint32_t AccMode;           /* Specifies the asynchronous access mode.
                                    This parameter can be a value of FEMC_Access_Mode */
} FEMC_NorSramTimingInitType;

/** @brief  FEMC NOR/SRAM Init structure definition **/
typedef struct
{
    FEMC_SN_Bank_Block *Block;  /* Specifies the NOR/SRAM memory bank block that will be used. */

    uint32_t DataAddrMux;       /* Specifies whether the address and data values are
                                    multiplexed on the databus or not.
                                    This parameter can be a value of FEMC_Data_Address_Bus_Multiplexing */

    uint32_t MemType;           /* Specifies the type of external memory attached to
                                    the corresponding memory bank.
                                    This parameter can be a value of FEMC_Memory_Type */

    uint32_t MemDataWidth;      /* Specifies the external memory device width.
                                    This parameter can be a value of FEMC_Data_Width */

    uint32_t BurstAccMode;      /* Enables or disables the burst access mode for Flash memory,
                                    valid only with synchronous burst Flash memories.
                                    This parameter can be a value of FEMC_Burst_Access_Mode */

    uint32_t AsynchroWait;      /* Enables or disables wait signal during asynchronous transfers,
                                    valid only with asynchronous Flash memories.
                                    This parameter can be a value of AsynchroWait */

    uint32_t WaitSigPolarity;   /* Specifies the wait signal polarity, valid only when accessing
                                    the Flash memory in burst mode.
                                    This parameter can be a value of FEMC_Wait_Signal_Polarity */

    uint32_t WrapMode;          /* Enables or disables the Wrapped burst access mode for Flash
                                    memory, valid only when accessing Flash memories in burst mode.
                                    This parameter can be a value of FEMC_Wrap_Mode */

    uint32_t WaitSigConfig;     /* Specifies if the wait signal is asserted by the memory one
                                    clock cycle before the wait state or during the wait state,
                                    valid only when accessing memories in burst mode.
                                    This parameter can be a value of FEMC_Wait_Timing */

    uint32_t WriteEnable;       /* Enables or disables the write operation in the selected bank by the FEMC.
                                    This parameter can be a value of FEMC_Write_Operation */

    uint32_t WaitSigEnable;     /* Enables or disables the wait-state insertion via wait
                                    signal, valid for Flash memory access in burst mode.
                                    This parameter can be a value of FEMC_Wait_Signal */

    uint32_t ExtModeEnable;     /* Enables or disables the extended mode.
                                    This parameter can be a value of FEMC_Extended_Mode */

    uint32_t WriteBurstEnable;  /* Enables or disables the write burst operation.
                                    This parameter can be a value of FEMC_Write_Burst */
                                    
    uint32_t CramPageSize;      /* Configure page size, support CRAM only */
    
    uint32_t NadvPolarity;      /* Specifies the NADV signal polarity */

    FEMC_NorSramTimingInitType* RWTimingStruct; /* Timing Parameters for write and read access 
                                                        if the  ExtendedMode is not used*/

    FEMC_NorSramTimingInitType* WTimingStruct;  /* Timing Parameters for write access if the  
                                                        ExtendedMode is used*/
} FEMC_NorSramInitType;

/** @brief  Timing parameters For FEMC NAND and PCCARD Banks **/
typedef struct
{
    uint32_t SetTime;       /* Defines the number of HCLK cycles to setup address before
                                the command assertion for NAND-Flash read or write access
                                to common/Attribute or I/O memory space (depending on
                                the memory space timing to be configured).
                                This parameter can be a value between 0 and 0xFF.*/

    uint32_t WaitSetTime;   /* Defines the minimum number of HCLK cycles to assert the
                                command for NAND-Flash read or write access to
                                common/Attribute or I/O memory space (depending on the
                                memory space timing to be configured).
                                This parameter can be a number between 0x00 and 0xFF */

    uint32_t HoldSetTime;   /* Defines the number of HCLK clock cycles to hold address
                                (and data for write access) after the command deassertion
                                for NAND-Flash read or write access to common/Attribute
                                or I/O memory space (depending on the memory space timing
                                to be configured).
                                This parameter can be a number between 0x00 and 0xFF */

    uint32_t HiZSetTime;    /* Defines the number of HCLK clock cycles during which the
                                databus is kept in HiZ after the start of a NAND-Flash
                                write access to common/Attribute or I/O memory space (depending
                                on the memory space timing to be configured).
                                This parameter can be a number between 0x00 and 0xFF */
} FEMC_NandTimingInitType;

/** FEMC NAND Init structure definition **/
typedef struct
{
    FEMC_NAND_Bank *Bank;   /* Specifies the NAND memory bank that will be used.
                                    This parameter can be FEMC_BANK2 or FEMC_BANK3 */

    uint32_t WaitFeatureEnable; /* Enables or disables the Wait feature for the NAND Memory Bank.
                                    This parameter can be any value of FEMC_Wait_feature */

    uint32_t MemDataWidth;      /* Specifies the external memory device width.
                                    This parameter can be any value of FEMC_Data_Width */

    uint32_t EccEnable;         /* Enables or disables the ECC computation.
                                    This parameter can be any value of FEMC_Ecc */

    uint32_t EccPageSize;       /* Defines the page size for the extended ECC.
                                    This parameter can be any value of FEMC_ECC_Page_Size */

    uint32_t TCLRSetTime;       /* Defines the number of HCLK cycles to configure the
                                    delay between CLE low and RE low.
                                    This parameter can be a value between 0 and 0xFF. */

    uint32_t TARSetTime;        /* Defines the number of HCLK cycles to configure the
                                    delay between ALE low and RE low.
                                    This parameter can be a number between 0x0 and 0xFF */

    FEMC_NandTimingInitType* CommSpaceTimingStruct; /* FEMC Common Space Timing */

    FEMC_NandTimingInitType* AttrSpaceTimingStruct; /* FEMC Attribute Space Timing */
} FEMC_NandInitType;

#define FEMC_NOR_SRAM_CTRL_RESET            ((uint32_t)0x00001276U)
#define FEMC_NOR_SRAM_TCFG_RESET            ((uint32_t)0x0FFFFFFFU)
#define FEMC_NOR_SRAM_WTCFG_RESET           ((uint32_t)0x0FFFFFFFU)

/** FEMC_Memory_Type **/
#define FEMC_MEM_TYPE_SRAM                  ((uint32_t)0x00000000U)
#define FEMC_MEM_TYPE_PSRAM                 (FEMC_SNCTRL_MTYPE_0)
#define FEMC_MEM_TYPE_NOR                   (FEMC_SNCTRL_MTYPE_1)

/** FEMC_Data_Width **/
#define FEMC_NOR_SRAM_DATA_WIDTH_8B         ((uint32_t)0x00000000U)
#define FEMC_NOR_SRAM_DATA_WIDTH_16B        (FEMC_SNCTRL_MDBW_0)

/** FEMC_NAND_Bank23_Reg_ResetValue **/
#define FEMC_NAND_CTRL_RESET                ((uint32_t)0x00000004U)
#define FEMC_NAND_STS_RESET                 ((uint32_t)0x00000040U)
#define FEMC_NAND_CMEMTM_RESET              ((uint32_t)0xFCFCFCFCU)
#define FEMC_NAND_ATTMEMTM_RESET            ((uint32_t)0xFCFCFCFCU)

/** FEMC_NOR_SRAM_BANK_Enable **/
#define FEMC_NOR_SRAM_DISABLE               ((uint32_t)0x000FFFEFU)
#define FEMC_NOR_SRAM_ENABLE                (FEMC_SNCTRL_MBEN)

/** FEMC_Write_Operation **/
#define FEMC_NOR_SRAM_WRITE_DISABLE         ((uint32_t)0x00000000U)
#define FEMC_NOR_SRAM_WRITE_ENABLE          (FEMC_SNCTRL_WREN)

/** FEMC_Flash_Access_Enable **/
#define FEMC_NOR_SRAM_ACC_DISABLE           ((uint32_t)0x00000000U)
#define FEMC_NOR_SRAM_ACC_ENABLE            (FEMC_SNCTRL_ACCEN)

/** FEMC_Extended_Mode **/
#define FEMC_NOR_SRAM_EXTENDED_DISABLE      ((uint32_t)0x00000000U)
#define FEMC_NOR_SRAM_EXTENDED_ENABLE       (FEMC_SNCTRL_EXTEN)

/** AsynchroWait **/
#define FEMC_NOR_SRAM_ASYNC_NWAIT_DISABLE   ((uint32_t)0x00000000U)
#define FEMC_NOR_SRAM_ASYNC_NWAIT_ENABLE    (FEMC_SNCTRL_WAITASYNC)

/** FEMC_Data_Address_Bus_Multiplexing **/
#define FEMC_NOR_SRAM_MUX_DISABLE           ((uint32_t)0x00000000U)
#define FEMC_NOR_SRAM_MUX_ENABLE            (FEMC_SNCTRL_MUXEN)

/** FEMC_Burst_Access_Mode **/
#define FEMC_NOR_SRAM_BURST_MODE_DISABLE    ((uint32_t)0x00000000U)
#define FEMC_NOR_SRAM_BURST_MODE_ENABLE     (FEMC_SNCTRL_BURSTEN)

/** FEMC_Wrap_Mode **/
#define FEMC_NOR_SRAM_WRAP_DISABLE          ((uint32_t)0x00000000U)
#define FEMC_NOR_SRAM_WRAP_ENABLE           (FEMC_SNCTRL_WRAPEN)

/** FEMC_Wait_Signal **/
#define FEMC_NOR_SRAM_NWAIT_DISABLE         ((uint32_t)0x00000000U)
#define FEMC_NOR_SRAM_NWAIT_ENABLE          (FEMC_SNCTRL_WAITEN)

/** FEMC_Wait_Signal_Polarity **/
#define FEMC_NOR_SRAM_WAIT_SIGNAL_LOW       ((uint32_t)0x00000000U)
#define FEMC_NOR_SRAM_WAIT_SIGNAL_HIGH      (FEMC_SNCTRL_WAITDIR)

/** FEMC_Wait_Timing **/
#define FEMC_NOR_SRAM_NWAIT_BEFORE_STATE    ((uint32_t)0x00000000U)
#define FEMC_NOR_SRAM_NWAIT_DURING_STATE    (FEMC_SNCTRL_WCFG)

/** FEMC_Write_Burst **/
#define FEMC_NOR_SRAM_BURST_WRITE_DISABLE   ((uint32_t)0x00000000U)
#define FEMC_NOR_SRAM_BURST_WRITE_ENABLE    (FEMC_SNCTRL_BURSTWREN)

/** FEMC_CRAM_Burst_Page_Size **/
#define FEMC_CRAM_BURST_PAGE_SIZE_0         ((uint32_t)0x00000000U)
#define FEMC_CRAM_BURST_PAGE_SIZE_128       (FEMC_SNCTRL_PGSIZE_0)
#define FEMC_CRAM_BURST_PAGE_SIZE_256       (FEMC_SNCTRL_PGSIZE_1)
#define FEMC_CRAM_BURST_PAGE_SIZE_512       (FEMC_SNCTRL_PGSIZE_0 | FEMC_SNCTRL_PGSIZE_1)
#define FEMC_CRAM_BURST_PAGE_SIZE_1024      (FEMC_SNCTRL_PGSIZE_2)

/** FEMC_NADV_Polarity **/
#define FEMC_NOR_SRAM_NADV_SIGNAL_LOW       ((uint32_t)0x00000000)
#define FEMC_NOR_SRAM_NADV_SIGNAL_HIGH      (FEMC_SNCTRL_NADVDIR)

#define FEMC_NOR_SRAM_ADDBLD_SHIFT              (0)
#define FEMC_NOR_SRAM_ADDHLD_SHIFT              (4)
#define FEMC_NOR_SRAM_DATABLD_SHIFT             (8)
#define FEMC_NOR_SRAM_DATAHLD_SHIFT             (16)
#define FEMC_NOR_SRAM_BUSRECOVERY_SHIFT         (20)
#define FEMC_NOR_SRAM_CLKDIV_SHIFT              (24)
#define FEMC_NOR_SRAM_ACCMODE_SHIFT             (28)



/** NOR_SRAM_Time_Control **/
/** FEMC_Address_Setup_Time **/
#define FEMC_NOR_SRAM_ADDR_SETUP_TIME_1HCLK         (0x0UL << FEMC_NOR_SRAM_ADDBLD_SHIFT)
#define FEMC_NOR_SRAM_ADDR_SETUP_TIME_2HCLK         (0x1UL << FEMC_NOR_SRAM_ADDBLD_SHIFT)
#define FEMC_NOR_SRAM_ADDR_SETUP_TIME_3HCLK         (0x2UL << FEMC_NOR_SRAM_ADDBLD_SHIFT)
#define FEMC_NOR_SRAM_ADDR_SETUP_TIME_4HCLK         (0x3UL << FEMC_NOR_SRAM_ADDBLD_SHIFT)
#define FEMC_NOR_SRAM_ADDR_SETUP_TIME_5HCLK         (0x4UL << FEMC_NOR_SRAM_ADDBLD_SHIFT)
#define FEMC_NOR_SRAM_ADDR_SETUP_TIME_6HCLK         (0x5UL << FEMC_NOR_SRAM_ADDBLD_SHIFT)
#define FEMC_NOR_SRAM_ADDR_SETUP_TIME_7HCLK         (0x6UL << FEMC_NOR_SRAM_ADDBLD_SHIFT)
#define FEMC_NOR_SRAM_ADDR_SETUP_TIME_8HCLK         (0x7UL << FEMC_NOR_SRAM_ADDBLD_SHIFT)
#define FEMC_NOR_SRAM_ADDR_SETUP_TIME_9HCLK         (0x8UL << FEMC_NOR_SRAM_ADDBLD_SHIFT)
#define FEMC_NOR_SRAM_ADDR_SETUP_TIME_10HCLK        (0x9UL << FEMC_NOR_SRAM_ADDBLD_SHIFT)
#define FEMC_NOR_SRAM_ADDR_SETUP_TIME_11HCLK        (0xAUL << FEMC_NOR_SRAM_ADDBLD_SHIFT)
#define FEMC_NOR_SRAM_ADDR_SETUP_TIME_12HCLK        (0xBUL << FEMC_NOR_SRAM_ADDBLD_SHIFT)
#define FEMC_NOR_SRAM_ADDR_SETUP_TIME_13HCLK        (0xCUL << FEMC_NOR_SRAM_ADDBLD_SHIFT)
#define FEMC_NOR_SRAM_ADDR_SETUP_TIME_14HCLK        (0xDUL << FEMC_NOR_SRAM_ADDBLD_SHIFT)
#define FEMC_NOR_SRAM_ADDR_SETUP_TIME_15HCLK        (0xEUL << FEMC_NOR_SRAM_ADDBLD_SHIFT)
#define FEMC_NOR_SRAM_ADDR_SETUP_TIME_16HCLK        (0xFUL << FEMC_NOR_SRAM_ADDBLD_SHIFT)

/** FEMC_Address_Hold_Time **/
#define FEMC_NOR_SRAM_ADDR_HOLD_TIME_2HCLK          (0x1UL << FEMC_NOR_SRAM_ADDHLD_SHIFT)
#define FEMC_NOR_SRAM_ADDR_HOLD_TIME_3HCLK          (0x2UL << FEMC_NOR_SRAM_ADDHLD_SHIFT)
#define FEMC_NOR_SRAM_ADDR_HOLD_TIME_4HCLK          (0x3UL << FEMC_NOR_SRAM_ADDHLD_SHIFT)
#define FEMC_NOR_SRAM_ADDR_HOLD_TIME_5HCLK          (0x4UL << FEMC_NOR_SRAM_ADDHLD_SHIFT)
#define FEMC_NOR_SRAM_ADDR_HOLD_TIME_6HCLK          (0x5UL << FEMC_NOR_SRAM_ADDHLD_SHIFT)
#define FEMC_NOR_SRAM_ADDR_HOLD_TIME_7HCLK          (0x6UL << FEMC_NOR_SRAM_ADDHLD_SHIFT)
#define FEMC_NOR_SRAM_ADDR_HOLD_TIME_8HCLK          (0x7UL << FEMC_NOR_SRAM_ADDHLD_SHIFT)
#define FEMC_NOR_SRAM_ADDR_HOLD_TIME_9HCLK          (0x8UL << FEMC_NOR_SRAM_ADDHLD_SHIFT)
#define FEMC_NOR_SRAM_ADDR_HOLD_TIME_10HCLK         (0x9UL << FEMC_NOR_SRAM_ADDHLD_SHIFT)
#define FEMC_NOR_SRAM_ADDR_HOLD_TIME_11HCLK         (0xAUL << FEMC_NOR_SRAM_ADDHLD_SHIFT)
#define FEMC_NOR_SRAM_ADDR_HOLD_TIME_12HCLK         (0xBUL << FEMC_NOR_SRAM_ADDHLD_SHIFT)
#define FEMC_NOR_SRAM_ADDR_HOLD_TIME_13HCLK         (0xCUL << FEMC_NOR_SRAM_ADDHLD_SHIFT)
#define FEMC_NOR_SRAM_ADDR_HOLD_TIME_14HCLK         (0xDUL << FEMC_NOR_SRAM_ADDHLD_SHIFT)
#define FEMC_NOR_SRAM_ADDR_HOLD_TIME_15HCLK         (0xEUL << FEMC_NOR_SRAM_ADDHLD_SHIFT)
#define FEMC_NOR_SRAM_ADDR_HOLD_TIME_16HCLK         (0xFUL << FEMC_NOR_SRAM_ADDHLD_SHIFT)

/** FEMC_Data_Setup_Time **/
#define FEMC_NOR_SRAM_DATA_SETUP_TIME_MIN           (0x01UL << FEMC_NOR_SRAM_DATABLD_SHIFT)
#define FEMC_NOR_SRAM_DATA_SETUP_TIME_MAX           (0xFFUL << FEMC_NOR_SRAM_DATABLD_SHIFT)
#define FEMC_NOR_SRAM_DATA_SETUP_TIME(x)            ((x) << FEMC_NOR_SRAM_DATABLD_SHIFT)

/** FEMC_Data_Hold_Time **/
#define FEMC_NOR_SRAM_DATA_HOLD_TIME_2HCLK          (0x0UL << FEMC_NOR_SRAM_DATAHLD_SHIFT)
#define FEMC_NOR_SRAM_DATA_HOLD_TIME_3HCLK          (0x1UL << FEMC_NOR_SRAM_DATAHLD_SHIFT)
#define FEMC_NOR_SRAM_DATA_HOLD_TIME_4HCLK          (0x2UL << FEMC_NOR_SRAM_DATAHLD_SHIFT)
#define FEMC_NOR_SRAM_DATA_HOLD_TIME_5HCLK          (0x3UL << FEMC_NOR_SRAM_DATAHLD_SHIFT)
#define FEMC_NOR_SRAM_DATA_HOLD_TIME_6HCLK          (0x4UL << FEMC_NOR_SRAM_DATAHLD_SHIFT)
#define FEMC_NOR_SRAM_DATA_HOLD_TIME_7HCLK          (0x5UL << FEMC_NOR_SRAM_DATAHLD_SHIFT)
#define FEMC_NOR_SRAM_DATA_HOLD_TIME_8HCLK          (0x6UL << FEMC_NOR_SRAM_DATAHLD_SHIFT)
#define FEMC_NOR_SRAM_DATA_HOLD_TIME_9HCLK          (0x7UL << FEMC_NOR_SRAM_DATAHLD_SHIFT)
#define FEMC_NOR_SRAM_DATA_HOLD_TIME_10HCLK         (0x8UL << FEMC_NOR_SRAM_DATAHLD_SHIFT)
#define FEMC_NOR_SRAM_DATA_HOLD_TIME_11HCLK         (0x9UL << FEMC_NOR_SRAM_DATAHLD_SHIFT)
#define FEMC_NOR_SRAM_DATA_HOLD_TIME_12HCLK         (0xAUL << FEMC_NOR_SRAM_DATAHLD_SHIFT)
#define FEMC_NOR_SRAM_DATA_HOLD_TIME_13HCLK         (0xBUL << FEMC_NOR_SRAM_DATAHLD_SHIFT)
#define FEMC_NOR_SRAM_DATA_HOLD_TIME_14HCLK         (0xCUL << FEMC_NOR_SRAM_DATAHLD_SHIFT)
#define FEMC_NOR_SRAM_DATA_HOLD_TIME_15HCLK         (0xDUL << FEMC_NOR_SRAM_DATAHLD_SHIFT)
#define FEMC_NOR_SRAM_DATA_HOLD_TIME_16HCLK         (0xEUL << FEMC_NOR_SRAM_DATAHLD_SHIFT)
#define FEMC_NOR_SRAM_DATA_HOLD_TIME_17HCLK         (0xFUL << FEMC_NOR_SRAM_DATAHLD_SHIFT)

/** FEMC_CLK_Division **/
#define FEMC_NOR_SRAM_CLK_DIV_2                     (0x1UL << FEMC_NOR_SRAM_CLKDIV_SHIFT)
#define FEMC_NOR_SRAM_CLK_DIV_3                     (0x2UL << FEMC_NOR_SRAM_CLKDIV_SHIFT)
#define FEMC_NOR_SRAM_CLK_DIV_4                     (0x3UL << FEMC_NOR_SRAM_CLKDIV_SHIFT)
#define FEMC_NOR_SRAM_CLK_DIV_5                     (0x4UL << FEMC_NOR_SRAM_CLKDIV_SHIFT)
#define FEMC_NOR_SRAM_CLK_DIV_6                     (0x5UL << FEMC_NOR_SRAM_CLKDIV_SHIFT)
#define FEMC_NOR_SRAM_CLK_DIV_7                     (0x6UL << FEMC_NOR_SRAM_CLKDIV_SHIFT)
#define FEMC_NOR_SRAM_CLK_DIV_8                     (0x7UL << FEMC_NOR_SRAM_CLKDIV_SHIFT)
#define FEMC_NOR_SRAM_CLK_DIV_9                     (0x8UL << FEMC_NOR_SRAM_CLKDIV_SHIFT)
#define FEMC_NOR_SRAM_CLK_DIV_10                    (0x9UL << FEMC_NOR_SRAM_CLKDIV_SHIFT)
#define FEMC_NOR_SRAM_CLK_DIV_11                    (0xAUL << FEMC_NOR_SRAM_CLKDIV_SHIFT)
#define FEMC_NOR_SRAM_CLK_DIV_12                    (0xBUL << FEMC_NOR_SRAM_CLKDIV_SHIFT)
#define FEMC_NOR_SRAM_CLK_DIV_13                    (0xCUL << FEMC_NOR_SRAM_CLKDIV_SHIFT)
#define FEMC_NOR_SRAM_CLK_DIV_14                    (0xDUL << FEMC_NOR_SRAM_CLKDIV_SHIFT)
#define FEMC_NOR_SRAM_CLK_DIV_15                    (0xEUL << FEMC_NOR_SRAM_CLKDIV_SHIFT)
#define FEMC_NOR_SRAM_CLK_DIV_16                    (0xFUL << FEMC_NOR_SRAM_CLKDIV_SHIFT)

/** FEMC_Access_Mode **/    
#define FEMC_NOR_SRAM_ACC_MODE_A                    ((uint32_t)0x00000000)
#define FEMC_NOR_SRAM_ACC_MODE_B                    (0x1UL << FEMC_NOR_SRAM_ACCMODE_SHIFT)
#define FEMC_NOR_SRAM_ACC_MODE_C                    (0x2UL << FEMC_NOR_SRAM_ACCMODE_SHIFT)
#define FEMC_NOR_SRAM_ACC_MODE_D                    (0x3UL << FEMC_NOR_SRAM_ACCMODE_SHIFT)

/** FEMC_Bus_Recovery_Time **/
#define FEMC_NOR_SRAM_BUSRECOVERY_TIME_1HCLK        (0x0UL <<  FEMC_NOR_SRAM_BUSRECOVERY_SHIFT)
#define FEMC_NOR_SRAM_BUSRECOVERY_TIME_2HCLK        (0x1UL <<  FEMC_NOR_SRAM_BUSRECOVERY_SHIFT)
#define FEMC_NOR_SRAM_BUSRECOVERY_TIME_3HCLK        (0x2UL <<  FEMC_NOR_SRAM_BUSRECOVERY_SHIFT)
#define FEMC_NOR_SRAM_BUSRECOVERY_TIME_4HCLK        (0x3UL <<  FEMC_NOR_SRAM_BUSRECOVERY_SHIFT)
#define FEMC_NOR_SRAM_BUSRECOVERY_TIME_5HCLK        (0x4UL <<  FEMC_NOR_SRAM_BUSRECOVERY_SHIFT)
#define FEMC_NOR_SRAM_BUSRECOVERY_TIME_6HCLK        (0x5UL <<  FEMC_NOR_SRAM_BUSRECOVERY_SHIFT)
#define FEMC_NOR_SRAM_BUSRECOVERY_TIME_7HCLK        (0x6UL <<  FEMC_NOR_SRAM_BUSRECOVERY_SHIFT)
#define FEMC_NOR_SRAM_BUSRECOVERY_TIME_8HCLK        (0x7UL <<  FEMC_NOR_SRAM_BUSRECOVERY_SHIFT)
#define FEMC_NOR_SRAM_BUSRECOVERY_TIME_9HCLK        (0x8UL <<  FEMC_NOR_SRAM_BUSRECOVERY_SHIFT)
#define FEMC_NOR_SRAM_BUSRECOVERY_TIME_10HCLK       (0x9UL <<  FEMC_NOR_SRAM_BUSRECOVERY_SHIFT)
#define FEMC_NOR_SRAM_BUSRECOVERY_TIME_11HCLK       (0xAUL <<  FEMC_NOR_SRAM_BUSRECOVERY_SHIFT)
#define FEMC_NOR_SRAM_BUSRECOVERY_TIME_12HCLK       (0xBUL <<  FEMC_NOR_SRAM_BUSRECOVERY_SHIFT)
#define FEMC_NOR_SRAM_BUSRECOVERY_TIME_13HCLK       (0xCUL <<  FEMC_NOR_SRAM_BUSRECOVERY_SHIFT)
#define FEMC_NOR_SRAM_BUSRECOVERY_TIME_14HCLK       (0xDUL <<  FEMC_NOR_SRAM_BUSRECOVERY_SHIFT)
#define FEMC_NOR_SRAM_BUSRECOVERY_TIME_15HCLK       (0xEUL <<  FEMC_NOR_SRAM_BUSRECOVERY_SHIFT)
#define FEMC_NOR_SRAM_BUSRECOVERY_TIME_16HCLK       (0xFUL <<  FEMC_NOR_SRAM_BUSRECOVERY_SHIFT)

/** NAND_Controller **/

#define FEMC_NCTRL_CRDLY_SHIFT      (5)
#define FEMC_NCTRL_ARDLY_SHIFT      (9)
#define FEMC_NCTRL_ECCPGS_SHIFT     (14)
#define FEMC_NCTRL_ECCPGS_MASK      (FEMC_SNCTRL_PGSIZE)

/** FEMC_Nand_Enable **/
#define FEMC_NAND_BANK_DISABLE      ((uint32_t)0x00000000U)
#define FEMC_NAND_BANK_ENABLE       (FEMC_NCTRL_BANKEN)

/** FEMC_Bus_Width **/
#define FEMC_NAND_BUS_WIDTH_8B      ((uint32_t)0x00000000U)
#define FEMC_NAND_BUS_WIDTH_16B     (FEMC_NCTRL_BUSWID_0)

/** FEMC_Wait_feature **/
#define FEMC_NAND_NWAIT_DISABLE     ((uint32_t)0x00000000U)
#define FEMC_NAND_NWAIT_ENABLE      (FEMC_NCTRL_WAITEN)

/** FEMC_CLE_RE_Delay **/
#define FEMC_NAND_CLE_DELAY_1HCLK       (0x0UL << FEMC_NCTRL_CRDLY_SHIFT)
#define FEMC_NAND_CLE_DELAY_2HCLK       (0x1UL << FEMC_NCTRL_CRDLY_SHIFT)
#define FEMC_NAND_CLE_DELAY_3HCLK       (0x2UL << FEMC_NCTRL_CRDLY_SHIFT)
#define FEMC_NAND_CLE_DELAY_4HCLK       (0x3UL << FEMC_NCTRL_CRDLY_SHIFT)
#define FEMC_NAND_CLE_DELAY_5HCLK       (0x4UL << FEMC_NCTRL_CRDLY_SHIFT)
#define FEMC_NAND_CLE_DELAY_6HCLK       (0x5UL << FEMC_NCTRL_CRDLY_SHIFT)
#define FEMC_NAND_CLE_DELAY_7HCLK       (0x6UL << FEMC_NCTRL_CRDLY_SHIFT)
#define FEMC_NAND_CLE_DELAY_8HCLK       (0x7UL << FEMC_NCTRL_CRDLY_SHIFT)
#define FEMC_NAND_CLE_DELAY_9HCLK       (0x8UL << FEMC_NCTRL_CRDLY_SHIFT)
#define FEMC_NAND_CLE_DELAY_10HCLK      (0x9UL << FEMC_NCTRL_CRDLY_SHIFT)
#define FEMC_NAND_CLE_DELAY_11HCLK      (0xAUL << FEMC_NCTRL_CRDLY_SHIFT)
#define FEMC_NAND_CLE_DELAY_12HCLK      (0xBUL << FEMC_NCTRL_CRDLY_SHIFT)
#define FEMC_NAND_CLE_DELAY_13HCLK      (0xCUL << FEMC_NCTRL_CRDLY_SHIFT)
#define FEMC_NAND_CLE_DELAY_14HCLK      (0xDUL << FEMC_NCTRL_CRDLY_SHIFT)
#define FEMC_NAND_CLE_DELAY_15HCLK      (0xEUL << FEMC_NCTRL_CRDLY_SHIFT)
#define FEMC_NAND_CLE_DELAY_16HCLK      (0xFUL << FEMC_NCTRL_CRDLY_SHIFT)

/** FEMC_ALE_RE_Delay **/
#define FEMC_NAND_ALE_DELAY_1HCLK       (0x0UL << FEMC_NCTRL_ARDLY_SHIFT)
#define FEMC_NAND_ALE_DELAY_2HCLK       (0x1UL << FEMC_NCTRL_ARDLY_SHIFT)
#define FEMC_NAND_ALE_DELAY_3HCLK       (0x2UL << FEMC_NCTRL_ARDLY_SHIFT)
#define FEMC_NAND_ALE_DELAY_4HCLK       (0x3UL << FEMC_NCTRL_ARDLY_SHIFT)
#define FEMC_NAND_ALE_DELAY_5HCLK       (0x4UL << FEMC_NCTRL_ARDLY_SHIFT)
#define FEMC_NAND_ALE_DELAY_6HCLK       (0x5UL << FEMC_NCTRL_ARDLY_SHIFT)
#define FEMC_NAND_ALE_DELAY_7HCLK       (0x6UL << FEMC_NCTRL_ARDLY_SHIFT)
#define FEMC_NAND_ALE_DELAY_8HCLK       (0x7UL << FEMC_NCTRL_ARDLY_SHIFT)
#define FEMC_NAND_ALE_DELAY_9HCLK       (0x8UL << FEMC_NCTRL_ARDLY_SHIFT)
#define FEMC_NAND_ALE_DELAY_10HCLK      (0x9UL << FEMC_NCTRL_ARDLY_SHIFT)
#define FEMC_NAND_ALE_DELAY_11HCLK      (0xAUL << FEMC_NCTRL_ARDLY_SHIFT)
#define FEMC_NAND_ALE_DELAY_12HCLK      (0xBUL << FEMC_NCTRL_ARDLY_SHIFT)
#define FEMC_NAND_ALE_DELAY_13HCLK      (0xCUL << FEMC_NCTRL_ARDLY_SHIFT)
#define FEMC_NAND_ALE_DELAY_14HCLK      (0xDUL << FEMC_NCTRL_ARDLY_SHIFT)
#define FEMC_NAND_ALE_DELAY_15HCLK      (0xEUL << FEMC_NCTRL_ARDLY_SHIFT)
#define FEMC_NAND_ALE_DELAY_16HCLK      (0xFUL << FEMC_NCTRL_ARDLY_SHIFT)

/** FEMC_Ecc **/
#define FEMC_NAND_ECC_DISABLE           ((uint32_t)0x00000000U)
#define FEMC_NAND_ECC_ENABLE            (FEMC_NCTRL_ECCEN)

/** FEMC_ECC_Page_Size **/
#define FEMC_NAND_ECC_PAGE_256BYTES         (0x0UL << FEMC_NCTRL_ECCPGS_SHIFT)
#define FEMC_NAND_ECC_PAGE_512BYTES         (0x1UL << FEMC_NCTRL_ECCPGS_SHIFT)
#define FEMC_NAND_ECC_PAGE_1024BYTES        (0x2UL << FEMC_NCTRL_ECCPGS_SHIFT)
#define FEMC_NAND_ECC_PAGE_2048BYTES        (0x3UL << FEMC_NCTRL_ECCPGS_SHIFT)
#define FEMC_NAND_ECC_PAGE_4096BYTES        (0x4UL << FEMC_NCTRL_ECCPGS_SHIFT)
#define FEMC_NAND_ECC_PAGE_8192BYTES        (0x5UL << FEMC_NCTRL_ECCPGS_SHIFT)


/** FEMC_StatusFlag **/
#define FEMC_NAND_FLAG_FIFO_EMPTY           (FEMC_STS_FIFOEMPT)

/** FEMC_Interrupt_StatusFlag **/
#define FEMC_NAND_INT_FLAG_HIGH_LEVEL       (FEMC_NSTS_IHLF)
#define FEMC_NAND_INT_FLAG_RASING_EDGE      (FEMC_NSTS_IRLF)
#define FEMC_NAND_INT_FLAG_FALLING_EDGE     (FEMC_NSTS_IFEF)

/** FEMC_Interrupt_Enable **/
#define FEMC_NAND_INT_HIGH_LEVEL            (FEMC_NSTS_IHLEN)
#define FEMC_NAND_INT_RASING_EDGE           (FEMC_NSTS_IREEN)
#define FEMC_NAND_INT_FALLING_EDGE          (FEMC_NSTS_IFEEN)


/** FEMC_TimeController **/
#define FEMC_NAND_HOLD_TIME_SHIFT       (0)
#define FEMC_NAND_HIZ_TIME_SHIFT        (8)
#define FEMC_NAND_SETUP_TIME_SHIFT      (16)
#define FEMC_NAND_WAIT_TIME_SHIFT       (24)

/** FEMC_Hold_Time **/
#define FEMC_NAND_HOLD_TIME_MIN         (0x00000001U)
#define FEMC_NAND_HOLD_TIME_MAX         (0x000000FFU)
#define FEMC_NAND_HOLD_TIME_DEFAULT     (0x000000FCU)
#define FEMC_NAND_HOLD_TIME(x)          ((x) << FEMC_NAND_HOLD_TIME_SHIFT)

/** FEMC_HiZ_Time **/
#define FEMC_NAND_HIZ_TIME_MIN          (0x00000000U)
#define FEMC_NAND_HIZ_TIME_MAX          (0x000000FFU)
#define FEMC_NAND_HIZ_TIME_DEFAULT      (0x000000FCU)
#define FEMC_NAND_HIZ_TIME(x)           ((x) << FEMC_NAND_HIZ_TIME_SHIFT)

/** FEMC_Setup_Time **/
#define FEMC_NAND_SETUP_TIME_MIN        (0x00000000U)
#define FEMC_NAND_SETUP_TIME_MAX        (0x000000FFU)
#define FEMC_NAND_SETUP_TIME_DEFAULT    (0x000000FCU)
#define FEMC_NAND_SETUP_TIME(x)         ((x) << FEMC_NAND_SETUP_TIME_SHIFT)

/** FEMC_Wait_Time **/
#define FEMC_NAND_WAIT_TIME_MIN         (0x00000001U)
#define FEMC_NAND_WAIT_TIME_MAX         (0x000000FFU)
#define FEMC_NAND_WAIT_TIME_DEFAULT     (0x000000FCU)
#define FEMC_NAND_WAIT_TIME(x)          ((x) << FEMC_NAND_WAIT_TIME_SHIFT)


/** FEMC_Exported_Functions **/
void FEMC_DeInitNorSram(FEMC_SN_Bank_Block *Block);
void FEMC_DeInitNand(FEMC_NAND_Bank *Bank);
void FEMC_InitNorSram(FEMC_NorSramInitType* FEMC_NORSRAMInitStruct);
void FEMC_InitNand(FEMC_NandInitType* FEMC_NANDInitStruct);
void FEMC_InitNorSramStruct(FEMC_NorSramInitType* FEMC_NORSRAMInitStruct);
void FEMC_InitNandStruct(FEMC_NandInitType* FEMC_NANDInitStruct);
void FEMC_EnableNorSram( FEMC_SN_Bank_Block *Block, FunctionalState Cmd);
void FEMC_EnableNand(FEMC_NAND_Bank *Bank, FunctionalState Cmd);
void FEMC_EnableNandEcc(FEMC_NAND_Bank *Bank, FunctionalState Cmd);
void FEMC_RestartNandEcc(FEMC_NAND_Bank *Bank);
uint32_t FEMC_GetEcc(FEMC_NAND_Bank *Bank);
void FEMC_ConfigInt(FEMC_NAND_Bank *Bank, uint32_t FEMC_INT, FunctionalState Cmd);
FlagStatus FEMC_GetFlag(FEMC_NAND_Bank *Bank, uint32_t FEMC_FLAG);
void FEMC_ClrFlag(FEMC_NAND_Bank *Bank, uint32_t FEMC_FLAG);
FlagStatus FEMC_GetITFlag(FEMC_NAND_Bank *Bank, uint32_t FEMC_FLAG);
void FEMC_ClrITFlag(FEMC_NAND_Bank *Bank, uint32_t FEMC_FLAG);

#ifdef __cplusplus
}
#endif

#endif /*__N32H47X_FEMC_H__ */

