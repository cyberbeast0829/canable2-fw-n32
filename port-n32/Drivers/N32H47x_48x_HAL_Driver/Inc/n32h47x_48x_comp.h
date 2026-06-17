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
 * @file n32h47x_48x_comp.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
 */

#ifndef __N32H47X_COMP_H__
#define __N32H47X_COMP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32h47x_48x.h"
#include <stdbool.h>


/** COMP_Exported_Types **/

typedef enum
{
    COMP1 = 0,
    COMP2 = 1,
    COMP3 = 2,
    COMP4 = 3,
    COMP5 = 4,
    COMP6 = 5,
    COMP7 = 6
} COMPX;


typedef enum {
  COMPX_CTRL_INMSEL_RES          = (0x7U << 1),
  /*comp1 inm sel*/
  COMP1_CTRL_INMSEL_PA0          = (0x0U << 1),
  COMP1_CTRL_INMSEL_PA4          = (0x1U << 1),
  COMP1_CTRL_INMSEL_PA5          = (0x2U << 1),
  COMP1_CTRL_INMSEL_PA6          = (0x3U << 1),
  COMP1_CTRL_INMSEL_DAC1_IOUT    = (0x4U << 1),
  COMP1_CTRL_INMSEL_DAC5_IOUT    = (0x5U << 1),
  COMP1_CTRL_INMSEL_VREF1        = (0x6U << 1),
  /*comp2 inm sel*/
  COMP2_CTRL_INMSEL_PA2          = (0x0U << 1),
  COMP2_CTRL_INMSEL_PA4          = (0x1U << 1),
  COMP2_CTRL_INMSEL_PA5          = (0x2U << 1),
  COMP2_CTRL_INMSEL_PB1          = (0x3U << 1),
  COMP2_CTRL_INMSEL_PE8          = (0x4U << 1),
  COMP2_CTRL_INMSEL_DAC2_IOUT    = (0x5U << 1),
  COMP2_CTRL_INMSEL_DAC6_IOUT    = (0x6U << 1),
  COMP2_CTRL_INMSEL_VREF1        = (0x7U << 1),
  /*comp3 inm sel*/
  COMP3_CTRL_INMSEL_PB14         = (0x0U << 1),
  COMP3_CTRL_INMSEL_PA4          = (0x1U << 1),
  COMP3_CTRL_INMSEL_PA5          = (0x2U << 1),
  COMP3_CTRL_INMSEL_PC0          = (0x3U << 1),
  COMP3_CTRL_INMSEL_PE7          = (0x4U << 1),
  COMP3_CTRL_INMSEL_PB12         = (0x5U << 1),
  COMP3_CTRL_INMSEL_PD15         = (0x6U << 1),
  COMP3_CTRL_INMSEL_PH1          = (0x7U << 1),
  COMP3_CTRL_INMSEL_DAC1_IOUT    = (0x8U << 1),
  COMP3_CTRL_INMSEL_DAC5_IOUT    = (0x9U << 1),
  COMP3_CTRL_INMSEL_VREF2        = (0xAU << 1),
  /*comp4 inm sel*/
  COMP4_CTRL_INMSEL_PB13         = (0x0U << 1),
  COMP4_CTRL_INMSEL_PA4          = (0x1U << 1),
  COMP4_CTRL_INMSEL_PA5          = (0x2U << 1),
  COMP4_CTRL_INMSEL_PC4          = (0x3U << 1),
  COMP4_CTRL_INMSEL_PB2          = (0x4U << 1),
  COMP4_CTRL_INMSEL_PE8          = (0x5U << 1),
  COMP4_CTRL_INMSEL_DAC2_IOUT    = (0x6U << 1),
  COMP4_CTRL_INMSEL_DAC6_IOUT    = (0x7U << 1),
  COMP4_CTRL_INMSEL_VREF2        = (0x8U << 1),
  /*comp5 inm sel*/
  COMP5_CTRL_INMSEL_PA4          = (0x0U << 1),
  COMP5_CTRL_INMSEL_PA5          = (0x1U << 1),
  COMP5_CTRL_INMSEL_PB10         = (0x2U << 1),
  COMP5_CTRL_INMSEL_PD10         = (0x3U << 1),
  COMP5_CTRL_INMSEL_PD13         = (0x4U << 1),
  COMP5_CTRL_INMSEL_DAC3_IOUT    = (0x5U << 1),
  COMP5_CTRL_INMSEL_DAC7_IOUT    = (0x6U << 1),
  COMP5_CTRL_INMSEL_VREF3        = (0x7U << 1),
  /*comp6 inm sel*/
  COMP6_CTRL_INMSEL_PA7          = (0x0U << 1),
  COMP6_CTRL_INMSEL_PA4          = (0x1U << 1),
  COMP6_CTRL_INMSEL_PA5          = (0x2U << 1),
  COMP6_CTRL_INMSEL_PB15         = (0x3U << 1),
  COMP6_CTRL_INMSEL_PD8          = (0x4U << 1),
  COMP6_CTRL_INMSEL_PD10         = (0x5U << 1),
  COMP6_CTRL_INMSEL_DAC4_IOUT    = (0x6U << 1),
  COMP6_CTRL_INMSEL_DAC8_IOUT    = (0x7U << 1),
  COMP6_CTRL_INMSEL_VREF3        = (0x8U << 1),
  /*comp7 inm sel*/
  COMP7_CTRL_INMSEL_PB12         = (0x0U << 1),
  COMP7_CTRL_INMSEL_PA4          = (0x1U << 1),
  COMP7_CTRL_INMSEL_PA5          = (0x2U << 1),
  COMP7_CTRL_INMSEL_PC0          = (0x3U << 1),
  COMP7_CTRL_INMSEL_PD15         = (0x4U << 1),
  COMP7_CTRL_INMSEL_DAC4_IOUT    = (0x5U << 1),
  COMP7_CTRL_INMSEL_DAC7_IOUT    = (0x6U << 1),
  COMP7_CTRL_INMSEL_VREF3        = (0x7U << 1),
}COMP_CTRL_INMSEL;

typedef enum {
  COMPX_CTRL_INPSEL_RES         = (0xFU << 5),
  /*comp1 inp sel*/
  COMP1_CTRL_INPSEL_PF8         = (0x0U << 5),
  COMP1_CTRL_INPSEL_PC1         = (0x1U << 5),
  COMP1_CTRL_INPSEL_PA1         = (0x2U << 5),
  COMP1_CTRL_INPSEL_PB1         = (0x3U << 5),
  COMP1_CTRL_INPSEL_PA7         = (0x4U << 5),
  COMP1_CTRL_INPSEL_DAC1_IOUT   = (0x5U << 5),
  COMP1_CTRL_INPSEL_DAC5_IOUT   = (0x6U << 5),
  COMP1_CTRL_INPSEL_VREF1       = (0x7U << 5),
  COMP1_CTRL_INPSEL_PGA1_IOUT_P = (0x8U << 5),
  COMP1_CTRL_INPSEL_PB10        = (0x9U << 5),
  /*comp2 inp sel*/
  COMP2_CTRL_INPSEL_PB10        = (0x0U << 5),
  COMP2_CTRL_INPSEL_PB11        = (0x1U << 5),
  COMP2_CTRL_INPSEL_PF10        = (0x2U << 5),
  COMP2_CTRL_INPSEL_PC3         = (0x3U << 5),
  COMP2_CTRL_INPSEL_PA3         = (0x4U << 5),
  COMP2_CTRL_INPSEL_PA7         = (0x5U << 5),
  COMP2_CTRL_INPSEL_PB1         = (0x6U << 5),
  COMP2_CTRL_INPSEL_DAC2_IOUT   = (0x7U << 5),
  COMP2_CTRL_INPSEL_DAC6_IOUT   = (0x8U << 5),
  COMP2_CTRL_INPSEL_VREF1       = (0x9U << 5),
  COMP2_CTRL_INPSEL_PGA1_IOUT_N = (0xAU << 5),
  /*comp3 inp sel*/
  COMP3_CTRL_INPSEL_PH1         = (0x0U << 5),
  COMP3_CTRL_INPSEL_PD15        = (0x1U << 5),
  COMP3_CTRL_INPSEL_PC0         = (0x2U << 5),
  COMP3_CTRL_INPSEL_PC1         = (0x3U << 5),
  COMP3_CTRL_INPSEL_PB0         = (0x4U << 5),
  COMP3_CTRL_INPSEL_PB14        = (0x5U << 5),
  COMP3_CTRL_INPSEL_DAC1_IOUT   = (0x6U << 5),
  COMP3_CTRL_INPSEL_DAC5_IOUT   = (0x7U << 5),
  COMP3_CTRL_INPSEL_VREF2       = (0x8U << 5),
  COMP3_CTRL_INPSEL_PGA2_IOUT_P = (0x9U << 5),
  COMP3_CTRL_INPSEL_PA0         = (0xAU << 5),
  /*comp4 inp sel*/
  COMP4_CTRL_INPSEL_PA0         = (0x0U << 5),
  COMP4_CTRL_INPSEL_PB0         = (0x1U << 5),
  COMP4_CTRL_INPSEL_PE7         = (0x2U << 5),
  COMP4_CTRL_INPSEL_PB15        = (0x3U << 5),
  COMP4_CTRL_INPSEL_PC9         = (0x4U << 5),
  COMP4_CTRL_INPSEL_DAC2_IOUT   = (0x5U << 5),
  COMP4_CTRL_INPSEL_DAC6_IOUT   = (0x6U << 5),
  COMP4_CTRL_INPSEL_VREF2       = (0x7U << 5),
  COMP4_CTRL_INPSEL_PGA2_IOUT_N = (0x8U << 5),
  /*comp5 inp sel*/
  COMP5_CTRL_INPSEL_PC3         = (0x0U << 5),
  COMP5_CTRL_INPSEL_PA3         = (0x1U << 5),
  COMP5_CTRL_INPSEL_PC4         = (0x2U << 5),
  COMP5_CTRL_INPSEL_PB13        = (0x3U << 5),
  COMP5_CTRL_INPSEL_DAC3_IOUT   = (0x4U << 5),
  COMP5_CTRL_INPSEL_DAC7_IOUT   = (0x5U << 5),
  COMP5_CTRL_INPSEL_VREF3       = (0x6U << 5),
  COMP5_CTRL_INPSEL_PGA3_IOUT_P = (0x7U << 5),
  COMP5_CTRL_INPSEL_PD12        = (0x8U << 5), 
  /*comp6 inp sel*/
  COMP6_CTRL_INPSEL_PD12        = (0x0U << 5),
  COMP6_CTRL_INPSEL_PD11        = (0x1U << 5),
  COMP6_CTRL_INPSEL_PD9         = (0x2U << 5),
  COMP6_CTRL_INPSEL_PC5         = (0x3U << 5),
  COMP6_CTRL_INPSEL_PB11        = (0x4U << 5),
  COMP6_CTRL_INPSEL_DAC4_IOUT   = (0x5U << 5),
  COMP6_CTRL_INPSEL_DAC8_IOUT   = (0x6U << 5),
  COMP6_CTRL_INPSEL_VREF3       = (0x7U << 5),
  COMP6_CTRL_INPSEL_PGA3_IOUT_N = (0x8U << 5),
  /*comp7 inp sel*/
  COMP7_CTRL_INPSEL_PB14        = (0x0U << 5),
  COMP7_CTRL_INPSEL_PC1         = (0x1U << 5),
  COMP7_CTRL_INPSEL_PD14        = (0x2U << 5),
  COMP7_CTRL_INPSEL_DAC4_IOUT   = (0x3U << 5),
  COMP7_CTRL_INPSEL_DAC7_IOUT   = (0x4U << 5),
  COMP7_CTRL_INPSEL_VREF3       = (0x5U << 5),
  COMP7_CTRL_INPSEL_PGA4_IOUT_P = (0x6U << 5),
  COMP7_CTRL_INPSEL_PGA4_IOUT_N = (0x7U << 5),
}COMP_CTRL_INPSEL;


typedef enum
{
    COMP_CTRL_HYST_NO    = (0x0U << 14),
    COMP_CTRL_HYST_10MV  = (0x1U << 14),
    COMP_CTRL_HYST_20MV  = (0x2U << 14),
    COMP_CTRL_HYST_30MV  = (0x3U << 14),
    COMP_CTRL_HYST_40MV  = (0x4U << 14),
    COMP_CTRL_HYST_50MV  = (0x5U << 14),
    COMP_CTRL_HYST_60MV  = (0x6U << 14),
    COMP_CTRL_HYST_70MV  = (0x7U << 14),
} COMP_CTRL_HYST;


typedef enum
{
    COMP_CTRL_BLKING_NO         = (0x0U << 17),
    COMP_CTRL_BLKING_ATIM1_OC5  = (0x1U << 17),
    COMP_CTRL_BLKING_ATIM2_OC5  = (0x2U << 17),
    COMP_CTRL_BLKING_ATIM3_OC5  = (0x3U << 17),
    COMP_CTRL_BLKING_GTIM8_OC5  = (0x4U << 17),
    COMP_CTRL_BLKING_GTIM9_OC5  = (0x5U << 17),
    COMP_CTRL_BLKING_GTIM10_OC5 = (0x6U << 17),
} COMP_CTRL_BLKING;

/** COMP_Exported_Constants **/

/** COMPx_CTRL **/
#define COMP_CTRL_FLTOUT_MASK                       (COMP1_CTRL_OUT)
#define COMP_CTRL_OUT_MASK                          (COMP1_CTRL_OUT)

#define COMP_CTRL_BLKING_MASK                       (COMP1_CTRL_BLKING)

#define COMP_CTRL_HYST_MASK                         (COMP1_CTRL_HYST)

#define COMP_POL_MASK                               (COMP1_CTRL_POL)
#define COMP_OUTPOL_FLIP                            (COMP1_CTRL_POL)
#define COMP_OUTPOL_NFLIP                           (0x00000000U)

#define COMP_CTRL_INPSEL_MASK                       (COMP1_CTRL_INPSEL) /*MAX INPSEL BIT.*/

#define COMP_CTRL_INMSEL_MASK                       (COMP2_CTRL_INMSEL) /*MAX INMSEL BIT.*/

#define COMP_CTRL_EN_MASK                           (COMP1_CTRL_EN)

/** COMPx_FILC **/
#define COMP_DAC_EN_MASK                            (COMP1_FILC_DACEN) /*using DAC stable value as Comparator's input.*/
#define COMP_FILC_SAMPW_MASK                        (COMP1_FILC_SAMPW) /*Low filter sample window size. Number of samples to monitor is SAMPWIN+1.*/
#define COMP_FILC_THRESH_MASK                       (COMP1_FILC_THRESH)/*For proper operation, the value of THRESH must be greater than SAMPWIN / 2.*/
#define COMP_FILC_FILEN_MASK                        (COMP1_FILC_FILEN) /*Filter enable.*/

/** COMPx_FILP **/
#define COMP_FILCLKCR_CLKPSC_MASK                   (COMP1_FILP_CLKPSC)/*Low filter sample clock prescale. Number of system clocks between samples = CLK_PRE_CYCLE + 1, e.g.*/

/** COMP_WINMODE  **/
#define COMP_WINMODE_CMPMD_MSK                      (COMP_WINMODE_COMP12MD|COMP_WINMODE_COMP34MD |COMP_WINMODE_COMP56MD)
#define COMP_WINMODE_CMP56MD                        (COMP_WINMODE_COMP56MD)/* Comparators 5 and 6 can be used in window mode.*/
#define COMP_WINMODE_CMP34MD                        (COMP_WINMODE_COMP34MD)/* Comparators 3 and 4 can be used in window mode.*/
#define COMP_WINMODE_CMP12MD                        (COMP_WINMODE_COMP12MD)/* Comparators 1 and 2 can be used in window mode.*/

/** COMP_LOCK  **/
#define COMP_LOCK_MSK                               (COMP_LOCK)
#define COMP1_LOCK                                  (COMP_LOCK_CMP1LK)
#define COMP2_LOCK                                  (COMP_LOCK_CMP2LK)
#define COMP3_LOCK                                  (COMP_LOCK_CMP3LK)
#define COMP4_LOCK                                  (COMP_LOCK_CMP4LK)
#define COMP5_LOCK                                  (COMP_LOCK_CMP5LK)
#define COMP6_LOCK                                  (COMP_LOCK_CMP6LK)
#define COMP7_LOCK                                  (COMP_LOCK_CMP7LK)

/** COMP_INTEN  **/
#define COMP_INTIEN_MSK                             (COMP_INTEN)
#define COMP1_INTEN                                 (COMP_INTEN_CMP1IEN) 
#define COMP2_INTEN                                 (COMP_INTEN_CMP2IEN)
#define COMP3_INTEN                                 (COMP_INTEN_CMP3IEN)
#define COMP4_INTEN                                 (COMP_INTEN_CMP4IEN)
#define COMP5_INTEN                                 (COMP_INTEN_CMP5IEN)
#define COMP6_INTEN                                 (COMP_INTEN_CMP6IEN)
#define COMP7_INTEN                                 (COMP_INTEN_CMP7IEN)

/** COMP_INTSTS   **/
#define COMP_INTSTS_MSK                             (COMP_INTSTS)
#define COMP1_INTSTS                                (COMP_INTSTS_COMP1IS) 
#define COMP2_INTSTS                                (COMP_INTSTS_COMP2IS)
#define COMP3_INTSTS                                (COMP_INTSTS_COMP3IS)
#define COMP4_INTSTS                                (COMP_INTSTS_COMP4IS)
#define COMP5_INTSTS                                (COMP_INTSTS_COMP5IS)
#define COMP6_INTSTS                                (COMP_INTSTS_COMP6IS)
#define COMP7_INTSTS                                (COMP_INTSTS_COMP7IS)

/** COMP_VREFSCL   **/
#define COMP_VREFSCL_VV1EN_MSK                      (COMP_VREFSCL_VV1EN)
#define COMP_VREFSCL_VV1TRM_MSK                     (COMP_VREFSCL_VV1TRM) /** Vref1 Voltage scaler triming value. **/ 
#define COMP_VREFSCL_VV2EN_MSK                      (COMP_VREFSCL_VV2EN)
#define COMP_VREFSCL_VV2TRM_MSK                     (COMP_VREFSCL_VV2TRM) /** Vref2 Voltage scaler triming value. **/ 
#define COMP_VREFSCL_VV3EN_MSK                      (COMP_VREFSCL_VV3EN)
#define COMP_VREFSCL_VV3TRM_MSK                     (COMP_VREFSCL_VV3TRM) /** Vref3 Voltage scaler triming value. **/ 

/** COMP_OTIMEN   **/
#define COMP_TIM_EN_MSK                             (COMP_TIM_EN)
#define COMP1_TIM_EN                                (CMP1_TIM_EN) 
#define COMP2_TIM_EN                                (CMP2_TIM_EN)
#define COMP3_TIM_EN                                (CMP3_TIM_EN)
#define COMP4_TIM_EN                                (CMP4_TIM_EN)
#define COMP5_TIM_EN                                (CMP5_TIM_EN)
#define COMP6_TIM_EN                                (CMP6_TIM_EN)
#define COMP7_TIM_EN                                (CMP7_TIM_EN)

/** COMP Init structure definition **/
typedef struct
{
    COMP_CTRL_BLKING Blking; 

    COMP_CTRL_HYST Hyst;

    FunctionalState PolRev; /* out polarity reverse */ 

    COMP_CTRL_INPSEL InpSel;
    COMP_CTRL_INMSEL InmSel;

    FunctionalState En;    /* COMP enable */ 

    /* filter config */
    uint8_t SampWindow;  /* 5bit */
    uint8_t Threshold;     /* 5bit need > SampWindow/2 */
    FunctionalState FilterEn;

    /* filter psc config */
    uint16_t ClkPsc;
} COMP_InitType;


/** COMP_Exported_Functions **/
void COMP_DeInit(void);
void COMP_StructInit(COMP_InitType* COMP_InitStruct);
void COMP_Init(COMPX COMPx, COMP_InitType* COMP_InitStruct);

void COMP_Enable(COMPX COMPx, FunctionalState Cmd);
void COMP_SetInpSel(COMPX COMPx, COMP_CTRL_INPSEL VpSel);
void COMP_SetInmSel(COMPX COMPx, COMP_CTRL_INMSEL VmSel);
void COMP_SetHyst(COMPX COMPx , COMP_CTRL_HYST HYST);
void COMP_SetBlanking(COMPX COMPx , COMP_CTRL_BLKING BLK);

void COMP_SetFilterPrescaler(COMPX COMPx , uint16_t FilPreVal);
void COMP_SetFilterControl(COMPX COMPx , uint8_t FilEn, uint8_t TheresNum , uint8_t SampPW);
void COMP_SetVflagEnable(COMPX COMPx , FunctionalState Cmd);

FlagStatus COMP_GetOutStatus(COMPX COMPx);
FlagStatus COMP_GetFilterOutStatus(COMPX COMPx);

void COMP_WindowModeEnable(uint32_t WinModeEn, FunctionalState Cmd);
void COMP_SetLock(uint32_t Lock);
void COMP_SetIntEn(uint32_t IntEn, FunctionalState Cmd);

FlagStatus COMP_GetIntStsOneComp(COMPX COMPx);
void COMP_ClearIntStsOneComp(COMPX COMPx);

void COMP_SetRefScl(uint8_t Vv3Trim, bool Vv3En, uint8_t Vv2Trim, bool Vv2En, uint8_t Vv1Trim, bool Vv1En); 
void COMP_OutToTimEnable(uint32_t TimEn, FunctionalState Cmd);

#ifdef __cplusplus
}
#endif

#endif /*__N32H47X_COMP_H */


