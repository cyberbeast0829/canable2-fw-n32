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
*\*\file n32h47x_48x_pwr.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32H47X_48X_PWR_H__
#define __N32H47X_48X_PWR_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32h47x_48x.h"

/*** PWR Structure Definition Start ***/	

/** PWR sleep status enmu definition **/
typedef enum
{
    PWR_SLEEP_NOW = 0x0,
    PWR_SLEEP_ON_EXIT = 0x1,
} PWR_SLEEPONEXIT_STATUS; 


/** PWR wakeup PIN polarity enmu definition **/
typedef enum
{
    POL_HIGH = 0x0,
    POL_LOW = 0x1,
} WAKEUP_PIN_POL;

/** PVD_IN pin enmu definition **/
typedef enum
{
    PVD_IN_PA10 = 0x0,
    PVD_IN_PB7  = 0x1,
} PVD_IN_SEL;

/**  PWR registers bit address in the alias region **/
#define PWR_OFFSET (PWR_BASE - PERIPH_BASE)

/**  CTRL Register **/

/** Alias word address of DBKP bit **/
#define CTRL_OFFSET  (PWR_OFFSET + 0x00)
#define DBKP_BITN    0x08
#define CTRL_DBKP_BB (PERIPH_BB_BASE + (CTRL_OFFSET * 32) + (DBKP_BITN * 4))

/** Alias word address of PVDEN bit **/
#define PVDEN_BITN    0x04
#define CTRL_PVDEN_BB (PERIPH_BB_BASE + (CTRL_OFFSET * 32) + (PVDEN_BITN * 4))


/**  PWR registers bit mask  **/

/** register bit mask **/
#define PWR_REG_BIT_MASK        ((uint32_t)0x00000000)

/** low power config **/
#define PWR_PDSLPS_MASK         (~(PWR_CTRL_LPS | PWR_CTRL_PDS))
#define PWR_PDS_SET             (PWR_CTRL_PDS)
#define PWR_REGULATOR_NORMAL    (PWR_REG_BIT_MASK)
#define PWR_REGULATOR_LOWPOWER  (PWR_CTRL_LPS)

/** PVD level config **/
#define PWR_CTRL_PLS_MASK     (~(PWR_CTRL_MSB | PWR_CTRL_PLS))
#define PWR_PVD_LEVEL_2V18    (PWR_CTRL_PLS_LVL0)
#define PWR_PVD_LEVEL_2V28    (PWR_CTRL_PLS_LVL1)
#define PWR_PVD_LEVEL_2V38    (PWR_CTRL_PLS_LVL2)
#define PWR_PVD_LEVEL_2V48    (PWR_CTRL_PLS_LVL3)
#define PWR_PVD_LEVEL_2V58    (PWR_CTRL_PLS_LVL4)
#define PWR_PVD_LEVEL_2V68    (PWR_CTRL_PLS_LVL5)
#define PWR_PVD_LEVEL_2V78    (PWR_CTRL_PLS_LVL6)
#define PWR_PVD_LEVEL_2V88    (PWR_CTRL_PLS_LVL7)

#define PWR_PVD_LEVEL_1V78    (PWR_CTRL_MSB | PWR_CTRL_PLS_LVL0)
#define PWR_PVD_LEVEL_1V88    (PWR_CTRL_MSB | PWR_CTRL_PLS_LVL1)
#define PWR_PVD_LEVEL_1V98    (PWR_CTRL_MSB | PWR_CTRL_PLS_LVL2)
#define PWR_PVD_LEVEL_2V08    (PWR_CTRL_MSB | PWR_CTRL_PLS_LVL3)
#define PWR_PVD_LEVEL_3V28    (PWR_CTRL_MSB | PWR_CTRL_PLS_LVL4)
#define PWR_PVD_LEVEL_3V38    (PWR_CTRL_MSB | PWR_CTRL_PLS_LVL5)
#define PWR_PVD_LEVEL_3V48    (PWR_CTRL_MSB | PWR_CTRL_PLS_LVL6)
#define PWR_PVD_LEVEL_3V58    (PWR_CTRL_MSB | PWR_CTRL_PLS_LVL7)

/** wakeup pin enable **/
#define WAKEUP_PIN0EN    (PWR_CTRLSTS_WKUP0EN)
#define WAKEUP_PIN1EN    (PWR_CTRLSTS_WKUP1EN)
#define WAKEUP_PIN2EN    (PWR_CTRLSTS_WKUP2EN)
#define WAKEUP_PIN3EN    (PWR_CTRLSTS_WKUP3EN)
#define WAKEUP_PIN4EN    (PWR_CTRLSTS_WKUP4EN)
#define WAKEUP_PIN5EN    (PWR_CTRLSTS_WKUP5EN)

/** wakeup pin polarity config **/
#define WAKEUP_PIN0POL    (PWR_CTRLSTS_WKUP0POL)
#define WAKEUP_PIN1POL    (PWR_CTRLSTS_WKUP1POL)
#define WAKEUP_PIN2POL    (PWR_CTRLSTS_WKUP2POL)
#define WAKEUP_PIN3POL    (PWR_CTRLSTS_WKUP3POL)
#define WAKEUP_PIN4POL    (PWR_CTRLSTS_WKUP4POL)

/** wakeup peripheral enable **/
#define WAKEUP_PERIPH0EN    (PWR_CTRLSTS_WKUPP0EN)
#define WAKEUP_PERIPH1EN    (PWR_CTRLSTS_WKUPP1EN)


/** STOP_mode_entry **/
#define PWR_SLEEPENTRY_WFI        ((uint8_t)0x01)
#define PWR_SLEEPENTRY_WFE        ((uint8_t)0x02)

/** STOP_mode_entry **/
#define PWR_STOPENTRY_WFI        ((uint8_t)0x01)
#define PWR_STOPENTRY_WFE        ((uint8_t)0x02)

/** PWR_Flag **/
#define PWR_FLAG_WKUP0      (PWR_CTRLSTS_WKUP0F)
#define PWR_FLAG_WKUP1      (PWR_CTRLSTS_WKUP1F)
#define PWR_FLAG_WKUP2      (PWR_CTRLSTS_WKUP2F)
#define PWR_FLAG_WKUP3      (PWR_CTRLSTS_WKUP3F)
#define PWR_FLAG_WKUP4      (PWR_CTRLSTS_WKUP4F)
#define PWR_FLAG_WKUP5      (PWR_CTRLSTS_WKUP5F)
#define PWR_FLAG_WKUPP      (PWR_CTRLSTS_WKUPPF)
#define PWR_FLAG_STANDBY    (PWR_CTRLSTS_SBF)
#define PWR_FLAG_PVDOUT     (PWR_CTRLSTS_PVDO)
#define PWR_FLAG_VBAT       (PWR_CTRLSTS_VBATF)

/** PWR_Flag clear **/
#define PWR_CLR_WKUP0      (PWR_CTRL_CWKUP0F)
#define PWR_CLR_WKUP1      (PWR_CTRL_CWKUP1F)
#define PWR_CLR_WKUP2      (PWR_CTRL_CWKUP2F)
#define PWR_CLR_WKUP3      (PWR_CTRL_CWKUP3F)
#define PWR_CLR_WKUP4      (PWR_CTRL_CWKUP4F)
#define PWR_CLR_WKUP5      (PWR_CTRL_CWKUP5F)
#define PWR_CLR_WKUPP      (PWR_CTRL_CWKUPPF)
#define PWR_CLR_STANDBY    (PWR_CTRL_CSBVBF)
#define PWR_CLR_VBAT       (PWR_CTRL_CSBVBF)

/** PWR_PVD_SEL **/
#define PWR_PVD_VDD        (~PWR_CTRL6_PVDSRC)   
#define PWR_PVD_PVDIN      (PWR_CTRL6_PVDSRC) 

/** PWR_BKR_OUTPUT **/
#define PWR_BKR_OUTPUT_0_8V  (~PWR_CTRL3_BKRSEL)   
#define PWR_BKR_OUTPUT_0_9V  (PWR_CTRL3_BKRSEL) 

/** PWR_ENABLE **/
#define PWR_IWDGRST_ENABLE       (PWR_CTRL2_IWDGRSTEN) 
#define PWR_STBRET_ENABLE        (PWR_CTRL2_BSRSTBRET) 
#define PWR_VBATRET_ENABLE       (PWR_CTRL2_BSRVBRET) 
#define PWR_LSENIM_ENABLE        (PWR_CTRL4_LSENIMEN) 
#define PWR_LSECSSCRYINT_ENABLE  (PWR_CTRL5_LSECSSIEN) 

/** PWR_LSE_HIGH_LIMIT **/
#define PWR_HIGH_LIMIT_1M        (~PWR_CTRL6_LSEFHTHR)   
#define PWR_HIGH_LIMIT_160K      (PWR_CTRL6_LSEFHTHR)

/** PWR_LSETOLSI_ENABLE **/
#define PWR_LSETOLSI_ENABLE      (PWR_CTRL6_LSECSSSW)

/** PWR_LSECSS_Flag **/
#define PWR_FLAG_LSECSSCRYF       (PWR_CTRL5_LSECSSCRYF) 
#define PWR_FLAG_LSEFHF           (PWR_CTRL6_LSEFHF)
#define PWR_FLAG_LSEFLF           (PWR_CTRL6_LSEFLF)
#define PWR_FLAG_LSECSSF          (PWR_CTRL6_LSECSSF)

/** PWR_LCO **/
#define PWR_LCO_LSI      (~PWR_CTRL6_LCOSEL)   
#define PWR_LCO_LSE      (PWR_CTRL6_LCOSEL)

/** PWR_LCO_ENABLE **/
#define PWR_LCO_ENABLE   (PWR_CTRL6_LCOEN)

/** PWR_NRSTPIN **/
#define PWR_NRST_SEL_MASK          (~PWR_CTRL6_NRSTSEL)
#define PWR_NRSTPIN_INPUT          (PWR_CTRL6_NRSTSEL_0)
#define PWR_NRSTPIN_INPUTOUTPUT    (PWR_REG_BIT_MASK)
#define PWR_NRSTPIN_NORMALGPIO     (PWR_CTRL6_NRSTSEL_1)

void PWR_DeInit(void);
void PWR_BackupAccessEnable(FunctionalState Cmd);
void PWR_PvdEnable(FunctionalState Cmd);
void PWR_PVDLevelConfig(uint32_t level);
void PWR_PVDSourceConfig(uint32_t PVD_source);
void PWR_PVDINPinSelect(PVD_IN_SEL PVD_pin);
void PWR_WakeUpPinEnable(uint32_t pin, FunctionalState Cmd);
void PWR_WakeUpPinPolarity(uint32_t pin, WAKEUP_PIN_POL polarity);
void PWR_WakeUpPeriphEnable(uint32_t periph, FunctionalState Cmd);
void PWR_EnterSLEEPMode(PWR_SLEEPONEXIT_STATUS SLEEPONEXIT, uint8_t PWR_SLEEPEntry);
void PWR_EnterSTOPMode(uint32_t PWR_Regulator, uint8_t PWR_STOPEntry);
void PWR_EnterSTANDBYMode(void);
FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG);
void PWR_ClearFlag(uint32_t PWR_FLAG);
void PWR_ConfigBKROutput(uint32_t voltage_output);
void PWR_EnableIWDGReset(FunctionalState Cmd);
void PWR_EnableBKPSRAMRetainInStandbyMode(FunctionalState Cmd);
void PWR_EnableBKPSRAMRetainInVbatMode(FunctionalState Cmd);
void PWR_EnableLSENoiseMitigation(FunctionalState Cmd);
void PWR_EnableLSECSSCrystalInt(FunctionalState Cmd);
void PWR_ConfigLSECSSBypassHighLimit(uint32_t high_limit);
void PWR_EnableLSECSSRTCsourceSwitch(FunctionalState Cmd);
FlagStatus PWR_GetLSECSSFlagStatus(uint32_t PWR_FLAG);
void PWR_ClearLSECSSFlag(void);
void PWR_ConfigLco(uint32_t LCO_source);
void PWR_EnableLCO(FunctionalState Cmd);
void PWR_ConfigNRSTMode(uint32_t NRST_mode);

#ifdef __cplusplus
}
#endif

#endif /* __N32H47X_48X_PWR_H__ */
       

