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
 * @file n32h47x_48x_pga.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32H47X_PGA_H__
#define __N32H47X_PGA_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32h47x_48x.h"
#include <stdbool.h>

/** PGA_Exported_Types **/

typedef enum
{
    PGA1 = 0,
    PGA2 = 1,
    PGA3 = 2,
    PGA4 = 3,
} PGAX;

typedef enum
{
    PGA_Channel1 = 0,
    PGA_Channel2 = 1,
} PGA_CHANNEL;

typedef enum
{
    PGAX_CTRL_VMSSEL_RES        = (0x00U << 24),
    /*PGA1 VMSSEL*/
    PGA1_CTRL_VMSSEL_PF8        = (0x00U << 24),
    PGA1_CTRL_VMSSEL_PF10       = (0x01U << 24),
    PGA1_CTRL_VMSSEL_PC3        = (0x02U << 24),
    PGA1_CTRL_VMSSEL_PA2        = (0x03U << 24),
    PGA1_CTRL_VMSSEL_PA3        = (0x04U << 24),
    PGA1_CTRL_VMSSEL_PA5        = (0x05U << 24),
    PGA1_CTRL_VMSSEL_PC5        = (0x06U << 24),
    PGA1_CTRL_VMSSEL_DAC2_IOUT  = (0x07U << 24),
    PGA1_CTRL_VMSSEL_DAC6_IOUT  = (0x08U << 24),

    /*PGA2 VMSSEL*/
    PGA2_CTRL_VMSSEL_PB0        = (0x00U << 24),
    PGA2_CTRL_VMSSEL_PF9        = (0x01U << 24),
    PGA2_CTRL_VMSSEL_PF10       = (0x02U << 24),
    PGA2_CTRL_VMSSEL_PA2        = (0x03U << 24),
    PGA2_CTRL_VMSSEL_PA3        = (0x04U << 24),
    PGA2_CTRL_VMSSEL_PA5        = (0x05U << 24),
    PGA2_CTRL_VMSSEL_PC5        = (0x06U << 24),
    PGA2_CTRL_VMSSEL_PB15       = (0x07U << 24),
    PGA2_CTRL_VMSSEL_DAC2_IOUT  = (0x08U << 24),
    PGA2_CTRL_VMSSEL_DAC6_IOUT  = (0x09U << 24),

    /*PGA3 VMSSEL*/
    PGA3_CTRL_VMSSEL_PF10       = (0x00U << 24),
    PGA3_CTRL_VMSSEL_PC1        = (0x01U << 24),
    PGA3_CTRL_VMSSEL_PA2        = (0x02U << 24),
    PGA3_CTRL_VMSSEL_PA5        = (0x03U << 24),
    PGA3_CTRL_VMSSEL_PC4        = (0x04U << 24),
    PGA3_CTRL_VMSSEL_PB2        = (0x05U << 24),
    PGA3_CTRL_VMSSEL_PB10       = (0x06U << 24),
    PGA3_CTRL_VMSSEL_DAC2_IOUT  = (0x07U << 24),
    PGA3_CTRL_VMSSEL_DAC6_IOUT  = (0x08U << 24),
    /*PGA4 VMSSEL*/
    PGA4_CTRL_VMSSEL_PF10       = (0x00U << 24),
    PGA4_CTRL_VMSSEL_PA1        = (0x01U << 24),
    PGA4_CTRL_VMSSEL_PB1        = (0x02U << 24),
    PGA4_CTRL_VMSSEL_PB10       = (0x03U << 24),
    PGA4_CTRL_VMSSEL_PD8        = (0x04U << 24),
    PGA4_CTRL_VMSSEL_PC9        = (0x05U << 24),
    PGA4_CTRL_VMSSEL_DAC2_IOUT  = (0x06U << 24),
    PGA4_CTRL_VMSSEL_DAC6_IOUT  = (0x07U << 24),
} PGA_CTRL_VMSSEL;

typedef enum
{   
    PGAX_CTRL_VPSSEL_RES        = (0x00U << 20),
    /*PGA1 VPSSEL*/
    PGA1_CTRL_VPSSEL_PF7        = (0x00U << 20),
    PGA1_CTRL_VPSSEL_PC2        = (0x01U << 20),
    PGA1_CTRL_VPSSEL_PA1        = (0x02U << 20),
    PGA1_CTRL_VPSSEL_PA3        = (0x03U << 20),
    PGA1_CTRL_VPSSEL_PA5        = (0x04U << 20),
    PGA1_CTRL_VPSSEL_PA7        = (0x05U << 20),
    PGA1_CTRL_VPSSEL_PB1        = (0x06U << 20),
    PGA1_CTRL_VPSSEL_DAC1_IOUT  = (0x07U << 20),
    PGA1_CTRL_VPSSEL_DAC5_IOUT  = (0x08U << 20),
    /*PGA2 VPSSEL*/
    PGA2_CTRL_VPSSEL_PF7        = (0x00U << 20),
    PGA2_CTRL_VPSSEL_PC3        = (0x01U << 20),
    PGA2_CTRL_VPSSEL_PA1        = (0x02U << 20),
    PGA2_CTRL_VPSSEL_PA2        = (0x03U << 20),
    PGA2_CTRL_VPSSEL_PA4        = (0x04U << 20),
    PGA2_CTRL_VPSSEL_PA7        = (0x05U << 20),
    PGA2_CTRL_VPSSEL_PB0        = (0x06U << 20),
    PGA2_CTRL_VPSSEL_PE8        = (0x07U << 20),
    PGA2_CTRL_VPSSEL_PB14       = (0x08U << 20),
    PGA2_CTRL_VPSSEL_PD12       = (0x09U << 20),
    PGA2_CTRL_VPSSEL_PD14       = (0x0AU << 20),
    PGA2_CTRL_VPSSEL_DAC1_IOUT  = (0x0BU << 20),
    PGA2_CTRL_VPSSEL_DAC5_IOUT  = (0x0CU << 20),
    /*PGA3 VPSSEL*/    
    PGA3_CTRL_VPSSEL_PF7        = (0x00U << 20),
    PGA3_CTRL_VPSSEL_PC0        = (0x01U << 20),
    PGA3_CTRL_VPSSEL_PC3        = (0x02U << 20),
    PGA3_CTRL_VPSSEL_PA1        = (0x03U << 20),
    PGA3_CTRL_VPSSEL_PA5        = (0x04U << 20),
    PGA3_CTRL_VPSSEL_PA6        = (0x05U << 20),
    PGA3_CTRL_VPSSEL_PB0        = (0x06U << 20),
    PGA3_CTRL_VPSSEL_PB13       = (0x07U << 20),
    PGA3_CTRL_VPSSEL_PC9        = (0x08U << 20),
    PGA3_CTRL_VPSSEL_DAC1_IOUT  = (0x09U << 20),
    PGA3_CTRL_VPSSEL_DAC5_IOUT  = (0x0AU << 20),
    /*PGA4 VPSSEL*/
    PGA4_CTRL_VPSSEL_PC3        = (0x00U << 20),
    PGA4_CTRL_VPSSEL_PA4        = (0x01U << 20),
    PGA4_CTRL_VPSSEL_PC5        = (0x02U << 20),
    PGA4_CTRL_VPSSEL_PB11       = (0x03U << 20),
    PGA4_CTRL_VPSSEL_PB12       = (0x04U << 20),
    PGA4_CTRL_VPSSEL_PB13       = (0x05U << 20),
    PGA4_CTRL_VPSSEL_PD9        = (0x06U << 20),
    PGA4_CTRL_VPSSEL_PD11       = (0x07U << 20),
    PGA4_CTRL_VPSSEL_DAC1_IOUT  = (0x08U << 20),
    PGA4_CTRL_VPSSEL_DAC5_IOUT  = (0x09U << 20),
} PGA_CTRL_VPSSEL;

typedef enum
{
    PGAX_CTRL_VMSEL_RES        = (0x00U << 16),
    /*PGA1 VMSEL*/
    PGA1_CTRL_VMSEL_PF8        = (0x00U << 16),
    PGA1_CTRL_VMSEL_PF10       = (0x01U << 16),
    PGA1_CTRL_VMSEL_PC3        = (0x02U << 16),
    PGA1_CTRL_VMSEL_PA2        = (0x03U << 16),
    PGA1_CTRL_VMSEL_PA3        = (0x04U << 16),
    PGA1_CTRL_VMSEL_PA5        = (0x05U << 16),
    PGA1_CTRL_VMSEL_PC5        = (0x06U << 16),
    PGA1_CTRL_VMSEL_DAC2_IOUT  = (0x07U << 16),
    PGA1_CTRL_VMSEL_DAC6_IOUT  = (0x08U << 16),

    /*PGA2 VMSEL*/
    PGA2_CTRL_VMSEL_PB0        = (0x00U << 16),
    PGA2_CTRL_VMSEL_PF9        = (0x01U << 16),
    PGA2_CTRL_VMSEL_PF10       = (0x02U << 16),
    PGA2_CTRL_VMSEL_PA2        = (0x03U << 16),
    PGA2_CTRL_VMSEL_PA3        = (0x04U << 16),
    PGA2_CTRL_VMSEL_PA5        = (0x05U << 16),
    PGA2_CTRL_VMSEL_PC5        = (0x06U << 16),
    PGA2_CTRL_VMSEL_PB15       = (0x07U << 16),
    PGA2_CTRL_VMSEL_DAC2_IOUT  = (0x08U << 16),
    PGA2_CTRL_VMSEL_DAC6_IOUT  = (0x09U << 16),

    /*PGA3 VMSEL*/
    PGA3_CTRL_VMSEL_PF10       = (0x00U << 16),
    PGA3_CTRL_VMSEL_PC1        = (0x01U << 16),
    PGA3_CTRL_VMSEL_PA2        = (0x02U << 16),
    PGA3_CTRL_VMSEL_PA5        = (0x03U << 16),
    PGA3_CTRL_VMSEL_PC4        = (0x04U << 16),
    PGA3_CTRL_VMSEL_PB2        = (0x05U << 16),
    PGA3_CTRL_VMSEL_PB10       = (0x06U << 16),
    PGA3_CTRL_VMSEL_DAC2_IOUT  = (0x07U << 16),
    PGA3_CTRL_VMSEL_DAC6_IOUT  = (0x08U << 16),
    /*PGA4 VMSEL*/
    PGA4_CTRL_VMSEL_PF10       = (0x00U << 16),
    PGA4_CTRL_VMSEL_PA1        = (0x01U << 16),
    PGA4_CTRL_VMSEL_PB1        = (0x02U << 16),
    PGA4_CTRL_VMSEL_PB10       = (0x03U << 16),
    PGA4_CTRL_VMSEL_PD8        = (0x04U << 16),
    PGA4_CTRL_VMSEL_PC9        = (0x05U << 16),
    PGA4_CTRL_VMSEL_DAC2_IOUT  = (0x06U << 16),
    PGA4_CTRL_VMSEL_DAC6_IOUT  = (0x07U << 16),
} PGA_CTRL_VMSEL;

typedef enum
{   
    PGAX_CTRL_VPSEL_RES        = (0x00U << 12),
    /*PGA1 VPSEL*/
    PGA1_CTRL_VPSEL_PF7        = (0x00U << 12),
    PGA1_CTRL_VPSEL_PC2        = (0x01U << 12),
    PGA1_CTRL_VPSEL_PA1        = (0x02U << 12),
    PGA1_CTRL_VPSEL_PA3        = (0x03U << 12),
    PGA1_CTRL_VPSEL_PA5        = (0x04U << 12),
    PGA1_CTRL_VPSEL_PA7        = (0x05U << 12),
    PGA1_CTRL_VPSEL_PB1        = (0x06U << 12),
    PGA1_CTRL_VPSEL_DAC1_IOUT  = (0x07U << 12),
    PGA1_CTRL_VPSEL_DAC5_IOUT  = (0x08U << 12),
    /*PGA2 VPSEL*/
    PGA2_CTRL_VPSEL_PF7        = (0x00U << 12),
    PGA2_CTRL_VPSEL_PC3        = (0x01U << 12),
    PGA2_CTRL_VPSEL_PA1        = (0x02U << 12),
    PGA2_CTRL_VPSEL_PA2        = (0x03U << 12),
    PGA2_CTRL_VPSEL_PA4        = (0x04U << 12),
    PGA2_CTRL_VPSEL_PA7        = (0x05U << 12),
    PGA2_CTRL_VPSEL_PB0        = (0x06U << 12),
    PGA2_CTRL_VPSEL_PE8        = (0x07U << 12),
    PGA2_CTRL_VPSEL_PB14       = (0x08U << 12),
    PGA2_CTRL_VPSEL_PD12       = (0x09U << 12),
    PGA2_CTRL_VPSEL_PD14       = (0x0AU << 12),
    PGA2_CTRL_VPSEL_DAC1_IOUT  = (0x0BU << 12),
    PGA2_CTRL_VPSEL_DAC5_IOUT  = (0x0CU << 12),
    /*PGA3 VPSEL*/    
    PGA3_CTRL_VPSEL_PF7        = (0x00U << 12),
    PGA3_CTRL_VPSEL_PC0        = (0x01U << 12),
    PGA3_CTRL_VPSEL_PC3        = (0x02U << 12),
    PGA3_CTRL_VPSEL_PA1        = (0x03U << 12),
    PGA3_CTRL_VPSEL_PA5        = (0x04U << 12),
    PGA3_CTRL_VPSEL_PA6        = (0x05U << 12),
    PGA3_CTRL_VPSEL_PB0        = (0x06U << 12),
    PGA3_CTRL_VPSEL_PB13       = (0x07U << 12),
    PGA3_CTRL_VPSEL_PC9        = (0x08U << 12),
    PGA3_CTRL_VPSEL_DAC1_IOUT  = (0x09U << 12),
    PGA3_CTRL_VPSEL_DAC5_IOUT  = (0x0AU << 12),
    /*PGA4 VPSEL*/
    PGA4_CTRL_VPSEL_PC3        = (0x00U << 12),
    PGA4_CTRL_VPSEL_PA4        = (0x01U << 12),
    PGA4_CTRL_VPSEL_PC5        = (0x02U << 12),
    PGA4_CTRL_VPSEL_PB11       = (0x03U << 12),
    PGA4_CTRL_VPSEL_PB12       = (0x04U << 12),
    PGA4_CTRL_VPSEL_PB13       = (0x05U << 12),
    PGA4_CTRL_VPSEL_PD9        = (0x06U << 12),
    PGA4_CTRL_VPSEL_PD11       = (0x07U << 12),
    PGA4_CTRL_VPSEL_DAC1_IOUT  = (0x08U << 12),
    PGA4_CTRL_VPSEL_DAC5_IOUT  = (0x09U << 12),
} PGA_CTRL_VPSEL;


typedef enum
{
    PGA_CTRL_CH2GAIN_1_DIFF_2   = (0x00U << 8),
    PGA_CTRL_CH2GAIN_2_DIFF_4   = (0x01U << 8),
    PGA_CTRL_CH2GAIN_4_DIFF_8   = (0x02U << 8),
    PGA_CTRL_CH2GAIN_8_DIFF_16  = (0x03U << 8),
    PGA_CTRL_CH2GAIN_12_DIFF_24 = (0x04U << 8),
    PGA_CTRL_CH2GAIN_16_DIFF_32 = (0x05U << 8),
    PGA_CTRL_CH2GAIN_24_DIFF_48 = (0x06U << 8),
    PGA_CTRL_CH2GAIN_32_DIFF_64 = (0x07U << 8),
} PGA_CTRL_CH2GAIN;

typedef enum
{
    PGA_CTRL_CH1GAIN_1_DIFF_2   = (0x00U <<4),
    PGA_CTRL_CH1GAIN_2_DIFF_4   = (0x01U <<4),
    PGA_CTRL_CH1GAIN_4_DIFF_8   = (0x02U <<4),
    PGA_CTRL_CH1GAIN_8_DIFF_16  = (0x03U <<4),
    PGA_CTRL_CH1GAIN_12_DIFF_24 = (0x04U <<4),
    PGA_CTRL_CH1GAIN_16_DIFF_32 = (0x05U <<4),
    PGA_CTRL_CH1GAIN_24_DIFF_48 = (0x06U <<4),
    PGA_CTRL_CH1GAIN_32_DIFF_64 = (0x07U <<4),
} PGA_CTRL_CH1GAIN;


/** PGA_Exported_Constants **/
               
/** PGAx_CTRL **/
#define PGA_CTRL_TRIMEN_MASK                        (PGA1_TRIMEN)
#define PGA_CTRL_VMSSEL_MASK                        (PGA1_VMSSEL)
#define PGA_CTRL_VPSSEL_MASK                        (PGA1_VPSSEL)

#define PGA_CTRL_VMSEL_MASK                         (PGA1_VMSEL)
#define PGA_CTRL_VPSEL_MASK                         (PGA1_VPSEL)

#define PGA_CTRL_CH2GAIN_MASK                       (PGA1_CH2GAIN)
#define PGA_CTRL_CH1GAIN_MASK                       (PGA1_CH1GAIN)

#define PGA_CTRL_TCMEN_MASK                         (PGA1_TCMEN)
#define PGA_CTRL_DIFFEN_MASK                        (PGA1_DIFFEN)
#define PGA_CTRL_CH2EN_MASK                         (PGA1_CH2EN)
#define PGA_CTRL_CH1EN_MASK                         (PGA1_CH1EN)

/**  PGAx_TRIM **/
#define PGA_TRIM_TRIMCH1P_MASK                      (PGA1_TRIMCH1P)
#define PGA_TRIM_TRIMCH1N_MASK                      (PGA1_TRIMCH1N)
#define PGA_TRIM_TRIMCH2P_MASK                      (PGA1_TRIMCH2P)
#define PGA_TRIM_TRIMCH2N_MASK                      (PGA1_TRIMCH2N)
#define PGA_TRIM_TRIMCH1FLAG_MASK                   (PGA1_TRIMCH1FLAG)
#define PGA_TRIM_TRIMCH2FLAG_MASK                   (PGA1_TRIMCH2FLAG)

/**  PGA_LOCK **/
#define PGA_LOCK_MASK                               (PGA_LOCK)
#define PGA1_LOCK                                   (PGA_LOCK_PGA1LK)
#define PGA2_LOCK                                   (PGA_LOCK_PGA2LK)
#define PGA3_LOCK                                   (PGA_LOCK_PGA3LK)
#define PGA4_LOCK                                   (PGA_LOCK_PGA4LK)

/**  PGA_IBIAS_EN **/
#define PGA_IBIAS_EN_MASK                           (PGA_IBIAS_EN)


/** PGA Init structure definition **/
typedef struct
{
    FunctionalState TimeAutoMuxEn; /*call ENABLE or DISABLE */

    PGA_CTRL_CH2GAIN Gain2; /*pga channel2 gain factor */
    PGA_CTRL_CH1GAIN Gain1; /*pga channel1 gain factor */

    PGA_CTRL_VPSEL Vpsel;
    PGA_CTRL_VMSEL Vmsel;

    PGA_CTRL_VPSSEL Vpssel;
    PGA_CTRL_VMSSEL Vmssel;

    FunctionalState DiffModeEn;  /* work in differential mode or not  */

    FunctionalState En1;  /* pga channel1 ENABLE or DISABLE */
    FunctionalState En2;  /* pga channel2 ENABLE or DISABLE */
} PGA_InitType;



/** PGA_Exported_Functions **/
void PGA_DeInit(void);
void PGA_StructInit(PGA_InitType* PGA_InitStruct);
void PGA_Init(PGAX PGAx, PGA_InitType* PGA_InitStruct);
void PGA_Enable(PGAX PGAx, PGA_CHANNEL ch, FunctionalState Cmd);

void PGA_SetPgaGain(PGAX PGAx, PGA_CTRL_CH1GAIN Gain1, PGA_CTRL_CH2GAIN Gain2);
void PGA_SetVpSecondSel(PGAX PGAx, PGA_CTRL_VPSSEL VpSSel);
void PGA_SetVmSecondSel(PGAX PGAx, PGA_CTRL_VMSSEL VmSSel);
void PGA_SetVpSel(PGAX PGAx, PGA_CTRL_VPSEL VpSel);
void PGA_SetVmSel(PGAX PGAx, PGA_CTRL_VMSEL VmSel);

void PGA_DiffModeEnable(PGAX PGAx, FunctionalState Cmd);
void PGA_TimControlMuxEnable(PGAX PGAx, FunctionalState Cmd);

/* functions related to triming  */
void PGA_TrimEnable(PGAX PGAx, FunctionalState Cmd);
void PGA_TrimValueSet(PGAX PGAx, PGA_CHANNEL ch, uint8_t PTrimValue, uint8_t NTrimValue);
FlagStatus PGA_TrimStatusGet(PGAX PGAx, PGA_CHANNEL ch);

void PGA_SetLock(uint32_t Lock);
void PGA_EnableIBIAS(FunctionalState Cmd);

#ifdef __cplusplus
}
#endif

#endif /*__N32H47X_PGA_H */

