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
*\*\file n32h47x_48x_fmac.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/
 
#include "n32h47x_48x_fmac.h"
#include "n32h47x_48x_rcc.h"


/**
*\*\name    FMAC_DeInit.
*\*\fun     Deinitializes the FMAC peripheral registers to their default reset values
*\*\param   none
*\*\
*\*\return  none
**/
void FMAC_DeInit(void)
{
    /* Enable FMAC reset state */
    RCC_EnableAHBPeriphReset(RCC_AHB_PERIPHRST_FMAC);
}

/**
*\*\name    FMAC_StructInit.
*\*\fun     Initialize the FMAC filter parameter struct with the default values
*\*\param   FMAC_InitStruct: fmac parameter struct
*\*\return  none
**/
void FMAC_StructInit(FMAC_InitType * FMAC_InitStruct)
{
    FMAC_InitStruct->InputBufBaseAddress       = 0U;
    FMAC_InitStruct->InputBufSize              = 0U;
    FMAC_InitStruct->InputBufThreshold         = 0U;
    FMAC_InitStruct->CoeffBufBaseAddress       = 0U;
    FMAC_InitStruct->CoeffBufSize              = 0U;
    FMAC_InitStruct->OutBufBaseAddress         = 0U;
    FMAC_InitStruct->OutBufSize                = 0U;
    FMAC_InitStruct->OutBufThreshold           = 0U;
    FMAC_InitStruct->Limit                     = 0U;
    FMAC_InitStruct->Func                      = 0U;
    FMAC_InitStruct->P                         = 0U;
    FMAC_InitStruct->Q                         = 0U;
    FMAC_InitStruct->R                         = 0U;
}

/**
*\*\name    FMAC_PreLoadStructInit.
*\*\fun     Initialize the FMAC Preload struct with the default values
*\*\param   FMAC_PreloadStruct: fmac preload struct
*\*\return  none
**/
void FMAC_PreLoadStructInit(FMAC_PreLoadType * FMAC_PreloadStruct)
{
    FMAC_PreloadStruct->pInputData          = 0U;
    FMAC_PreloadStruct->InputDataSize       = 0U;
    FMAC_PreloadStruct->pCoeffA             = 0U;
    FMAC_PreloadStruct->CoeffASize          = 0U;
    FMAC_PreloadStruct->pCoeffB             = 0U;
    FMAC_PreloadStruct->CoeffBSize          = 0U;
    FMAC_PreloadStruct->pOutputData         = 0U;
    FMAC_PreloadStruct->OutputDataSize      = 0U;
}

/**
*\*\name    FMAC_Init.
*\*\fun     Initialize the FMAC peripheral
*\*\param   FMAC_InitStruct :
*\*\            - InputBufBaseAddress 
*\*\                - 0...255 
*\*\            - InputBufSize 
*\*\                - 0...255 
*\*\            - InputBufThreshold 
*\*\                - FMAC_THRESHOLD1
*\*\                - FMAC_THRESHOLD2
*\*\                - FMAC_THRESHOLD4
*\*\                - FMAC_THRESHOLD8
*\*\            - CoeffBufBaseAddress 
*\*\                - 0...255 
*\*\            - CoeffBufSize 
*\*\                - 0...255 
*\*\            - OutBufBaseAddress 
*\*\                - 0...255 
*\*\            - OutBufSize
*\*\                - 0...255 
*\*\            - OutBufThreshold 
*\*\                - FMAC_THRESHOLD1
*\*\                - FMAC_THRESHOLD2
*\*\                - FMAC_THRESHOLD4
*\*\                - FMAC_THRESHOLD8
*\*\            - Limit 
*\*\                - FMAC_LIMIT_ENABLE
*\*\                - FMAC_LIMIT_DISABLE
*\*\            - Func 
*\*\                - FMAC_FUNC_LOADX1
*\*\                - FMAC_FUNC_LOADX2
*\*\                - FMAC_FUNC_LOADY
*\*\                - FMAC_FUNC_CONVO_FIR
*\*\                - FMAC_FUNC_IIR_DIRECT_FORM_1
*\*\            - P.
*\*\                - 0...255 
*\*\            - Q.
*\*\                - 0...255 
*\*\            - R.
*\*\                - 0...255 
*\*\return  none
**/
void FMAC_Init(FMAC_InitType * FMAC_InitStruct)
{
    /* configure the input buffer parameter  */
    FMAC->X1BUFCFG = ((((uint32_t)FMAC_InitStruct->InputBufBaseAddress) & FMAC_X1BUFCFG_X1BASE) | \
              ((((uint32_t)FMAC_InitStruct->InputBufSize) << 8U) & FMAC_X1BUFCFG_X1BUFSIZE));

    /* configure the threshold of input buffer */ 
    FMAC->X1BUFCFG |= (FMAC_InitStruct->InputBufThreshold & FMAC_X1BUFCFG_X1BUFWM);

    /* configure the coefficient parameter */
    FMAC->X2BUFCFG = ((((uint32_t)FMAC_InitStruct->CoeffBufBaseAddress) & FMAC_X2BUFCFG_X2BASE) | \
              ((((uint32_t)FMAC_InitStruct->CoeffBufSize) << 8U) & FMAC_X2BUFCFG_X2BUFSIZE));

    /* configure the output buffer parameter  */
    FMAC->YBUFCFG = ((((uint32_t)FMAC_InitStruct->OutBufBaseAddress) & FMAC_YBUFCFG_YBASE) | \
             ((((uint32_t)FMAC_InitStruct->OutBufSize) << 8U) & FMAC_YBUFCFG_YBUFSIZE));

    /* configure the threshold of output buffer */ 
    FMAC->YBUFCFG |= (FMAC_InitStruct->OutBufThreshold & FMAC_YBUFCFG_YBUFWM);

    /* configure the state of limit */
    FMAC->CTRL &= ~FMAC_CTRL_LIMITEN;
    FMAC->CTRL |= (FMAC_InitStruct->Limit & FMAC_CTRL_LIMITEN);
}

/**
*\*\name    FMAC_PreLoadData.
*\*\fun     Preload data
*\*\param   size :
*\*\            - 0~255  size of data 
*\*\param   array[]:
*\*\            - pointer to the buffer containing the data to be computed
*\*\return  none
**/
void FMAC_PreLoadData(uint8_t size, int16_t array[])
{
    uint8_t i;
    for(i = 0U; i < size; i++)
    {
        FMAC->WDAT = (uint16_t)array[i] & FMAC_WDAT_WDAT;
    }
}

/**
*\*\name    FMAC_PreloadBufferData.
*\*\fun     Preload three buffer data
*\*\param   FMAC_PreloadStruct :
*\*\            - pInputData : 
*\*\                - pointer to the input buffer containing the data to be computed
*\*\            - InputDataSize :
*\*\                - 0..255
*\*\            - pCoeffA :
*\*\                - pointer to the buffer containing the data to be computed
*\*\            - CoeffASize : 
*\*\                - 0..255
*\*\            - pCoeffB :
*\*\                - pointer to the buffer containing the data to be computed
*\*\            - CoeffBSize : 
*\*\                - 0..255
*\*\            - pOutputData :
*\*\                - pointer to the output buffer containing the data to be computed
*\*\            - OutputDataSize : 
*\*\                - 0..255
*\*\return  none
**/
void FMAC_PreloadBufferData(FMAC_PreLoadType * FMAC_PreloadStruct)
{
    /* configure parameter of filter preload */
    FMAC->PARAMCFG = ((uint32_t)(FMAC_PreloadStruct->InputDataSize) & FMAC_PARAMCFG_P) | \
                     FMAC_FUNC_LOADX1 | FMAC_PARAMCFG_START;
    /* load the X1 buffer for input data */
    FMAC_PreLoadData(FMAC_PreloadStruct->InputDataSize, FMAC_PreloadStruct->pInputData);
    /* configure parameter of filter preload */
    FMAC->PARAMCFG = (((uint32_t)FMAC_PreloadStruct->CoeffBSize) & FMAC_PARAMCFG_P) | \
                  ((((uint32_t)FMAC_PreloadStruct->CoeffASize) << 8) & FMAC_PARAMCFG_Q) | \
                  FMAC_FUNC_LOADX2 | FMAC_PARAMCFG_START;
    /* load the X2 buffer for cofficientB */
    FMAC_PreLoadData(FMAC_PreloadStruct->CoeffBSize, FMAC_PreloadStruct->pCoeffB);
    /* load the x2 buffer for cofficientA */
    if((NULL != FMAC_PreloadStruct->pCoeffA) && (0U != FMAC_PreloadStruct->CoeffASize)) 
    {
        /* Load the buffer into the internal memory */
        FMAC_PreLoadData(FMAC_PreloadStruct->CoeffASize, FMAC_PreloadStruct->pCoeffA);
    }
    /* configure to preload output buffer */
    if((NULL != FMAC_PreloadStruct->pOutputData) && (0U != FMAC_PreloadStruct->OutputDataSize)) 
    {
        FMAC->PARAMCFG = ((uint32_t)FMAC_PreloadStruct->OutputDataSize & FMAC_PARAMCFG_P) |  \
                          FMAC_FUNC_LOADY | FMAC_PARAMCFG_START;
        /* load the Y buffer for input data */
        FMAC_PreLoadData(FMAC_PreloadStruct->OutputDataSize, FMAC_PreloadStruct->pOutputData);
    }
}

/**
*\*\name    FMAC_ConfigParam.
*\*\fun     Configure FMAC parameter
*\*\param   FMAC_ParamStruct :
*\*\            - Func 
*\*\                - FMAC_FUNC_CONVO_FIR 
*\*\                - FMAC_FUNC_IIR_DIRECT_FORM_1
*\*\            - P 
*\*\                - 0..255
*\*\            - Q 
*\*\                - 0..255
*\*\            - R 
*\*\                - 0..255
*\*\return  none
**/
void FMAC_ConfigParam(FMAC_InitType* FMAC_ParamStruct)
{
    /* set function */
    FMAC->PARAMCFG &= (~FMAC_PARAMCFG_FUNC);
    FMAC->PARAMCFG |= FMAC_ParamStruct->Func;
    /* set filter parameter */
    FMAC->PARAMCFG &= ~(FMAC_PARAMCFG_P | FMAC_PARAMCFG_Q | FMAC_PARAMCFG_R);
    FMAC->PARAMCFG |= ((uint32_t)FMAC_ParamStruct->P) | (((uint32_t)FMAC_ParamStruct->Q) << 8U) | \
                        (((uint32_t)FMAC_ParamStruct->R) << 16U);
}

/**
*\*\name    FMAC_Reset.
*\*\fun     Reset FMAC, reset write and read pointers. the internal control logic,FAC_STS register and the FAC_PARAMCFG register is reset.
*\*\param   none
*\*\return  none
**/
void FMAC_Reset(void)
{
    /* Reset FMAC peripheral */
    FMAC->CTRL |= FMAC_RESET;
}

/**
*\*\name    FMAC_Enable.
*\*\fun     Enable or disable FMAC start execution.
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void FMAC_Enable(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected FMAC peripheral */
        FMAC->PARAMCFG |= FMAC_PARAMCFG_START;
    }
    else
    {
        /* Disable the selected FMAC peripheral */
        FMAC->PARAMCFG  &= ~FMAC_PARAMCFG_START;
    }
}

/**
*\*\name    FMAC_ConfigX1.
*\*\fun     Configuration X1 paramer.
*\*\        Baseaddr 
*\*\          - 0...255 
*\*\        Bufsize 
*\*\          - 0...255 
*\*\        Threshold 
*\*\          - FMAC_THRESHOLD1
*\*\          - FMAC_THRESHOLD2
*\*\          - FMAC_THRESHOLD4
*\*\          - FMAC_THRESHOLD8
*\*\return  none
**/
void FMAC_ConfigX1(uint8_t Baseaddr, uint8_t Bufsize, uint32_t Threshold)
{
    /* Set base address */
    FMAC->X1BUFCFG &= ~FMAC_X1BUFCFG_X1BASE;
    FMAC->X1BUFCFG |= Baseaddr;
    
    /* Set buffer size */
    FMAC->X1BUFCFG &= ~FMAC_X1BUFCFG_X1BUFSIZE;
    FMAC->X1BUFCFG |= (Bufsize << 8);
    
    /* Set Threshold */
    FMAC->X1BUFCFG &= ~FMAC_X1BUFCFG_X1BUFWM;
    FMAC->X1BUFCFG |= Threshold;
}

/**
*\*\name    FMAC_ConfigX2.
*\*\fun     Configuration X2 paramer.
*\*\        Baseaddr 
*\*\          - 0...255 
*\*\        Bufsize 
*\*\          - 0...255 
*\*\return  none
**/
void FMAC_ConfigX2(uint8_t Baseaddr, uint8_t Bufsize)
{
    /* Set base address */
    FMAC->X2BUFCFG &= ~FMAC_X2BUFCFG_X2BASE;
    FMAC->X2BUFCFG |= Baseaddr;
    
    /* Set buffer size */
    FMAC->X2BUFCFG &= ~FMAC_X2BUFCFG_X2BUFSIZE;
    FMAC->X2BUFCFG |= (Bufsize << 8);
}

/**
*\*\name    FMAC_ConfigY.
*\*\fun     Configuration Y paramer.
*\*\        Baseaddr 
*\*\          - 0...255 
*\*\        Bufsize 
*\*\          - 0...255 
*\*\        Threshold 
*\*\          - FMAC_THRESHOLD1
*\*\          - FMAC_THRESHOLD2
*\*\          - FMAC_THRESHOLD4
*\*\          - FMAC_THRESHOLD8
*\*\return  none
**/
void FMAC_ConfigY(uint8_t Baseaddr, uint8_t Bufsize, uint32_t Threshold)
{
    /* Set base address */
    FMAC->YBUFCFG &= ~FMAC_YBUFCFG_YBASE;
    FMAC->YBUFCFG |= Baseaddr;
    
    /* Set buffer size */
    FMAC->YBUFCFG &= ~FMAC_YBUFCFG_YBUFSIZE;
    FMAC->YBUFCFG |= (Bufsize << 8);
    
    /* Set Threshold */
    FMAC->YBUFCFG &= ~FMAC_YBUFCFG_YBUFWM;
    FMAC->YBUFCFG |= Threshold;
}

/**
*\*\name    FMAC_WriteData
*\*\fun     Write data
*\*\param   none 
*\*\return  16-bit data
**/
void FMAC_WriteData(int16_t data)
{
    FMAC->WDAT = (uint32_t)data;
}

/**
*\*\name    FMAC_ReadData
*\*\fun     Read output data
*\*\param   none 
*\*\return  16-bit data
**/
int16_t FMAC_ReadData(void)
{
    int16_t value;
    value = (int16_t)FMAC->RDAT;
    return value;
}

/**
*\*\name    FMAC_EnableLimit
*\*\fun     Enable or disable fmac limit
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void FMAC_EnableLimit(FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        FMAC->CTRL |= FMAC_LIMIT_ENABLE;
    }
    else
    {
        FMAC->CTRL &= ~FMAC_LIMIT_ENABLE;
    }
}

/**
*\*\name    FMAC_EnableDma
*\*\fun     Enable or disable fmac dma
*\*\param   dma_req :
*\*\            - FMAC_DMA_READ: read buffer dma 
*\*\            - FMAC_DMA_WRITE: write buffer dma
*\*\param   Cmd :
*\*\            - ENABLE
*\*\            - DISABLE
*\*\return  none
**/
void FMAC_EnableDMA(uint32_t dma_req, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        FMAC->CTRL |= dma_req;
    }
    else 
    {
        FMAC->CTRL &= ~dma_req;
    }
}

/**
*\*\name    FMAC_EnableINT
*\*\fun     Enable or disable fmac interrupt
*\*\param   interrupt :
*\*\            - FMAC_INT_READ: Read buffer interrupt 
*\*\            - FMAC_INT_WRITE: Write buffer interrupt
*\*\            - FMAC_INT_OV: Overflow error interrupt
*\*\            - FMAC_INT_UN: Underflow error interrupt
*\*\            - FMAC_INT_SAT: Saturation error interrupt
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void FMAC_ConfigInt(uint32_t interrupt, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        FMAC->CTRL |= interrupt;
    }
    else
    {
        FMAC->CTRL &= ~interrupt;
    }
}

/**
*\*\name    FMAC_FinishCalculate.
*\*\fun     finish the filter calculate
*\*\param   none
*\*\return  none
**/
void FMAC_FinishCalculate(void)
{ 
    /* clear start */
    FMAC->PARAMCFG  &= ~FMAC_START;
    /* disable read and write interrupt */
    FMAC_ConfigInt(FMAC_INT_READ | FMAC_INT_WRITE, DISABLE);
    /* disable read and write dma */
    FMAC_EnableDMA(FMAC_DMA_READ | FMAC_DMA_WRITE, DISABLE);
    /* reset register and pointer */
    FMAC->CTRL |= FMAC_RESET;
}

/**
*\*\name    FMAC_GetInterruptFlag
*\*\fun     FMAC interrupt flag status
*\*\param   interrupt :
*\*\            - FMAC_INT_FLAG_YBUFEF: Read buffer interrupt 
*\*\            - FMAC_INT_FLAG_X1BUFFF: Write buffer interrupt
*\*\            - FMAC_INT_FLAG_OVF: Overflow error interrupt
*\*\            - FMAC_INT_FLAG_UNF: Underflow error interrupt
*\*\            - FMAC_INT_FLAG_SATF: Saturation error interrupt
*\*\return  none
**/
FlagStatus FMAC_GetIntStatus(uint8_t FMAC_INT)
{
    FlagStatus bitstatus = RESET;
    uint32_t reg1 = FMAC->CTRL;
    uint32_t reg2 = FMAC->STS;

    switch(FMAC_INT) 
    {
        /*  Y buffer read interrupt */
        case FMAC_INT_FLAG_YBUFEF:
            reg1 = reg1 & FMAC_INT_READ;
            reg2 = (((reg2 & FMAC_FLAG_YBUFEF) == 0U)?FMAC_FLAG_YBUFEF:0U);
            break;
        /* X0 buffer write interrupt */
        case FMAC_INT_FLAG_X1BUFFF:
            reg1 = reg1 & FMAC_INT_WRITE;
            reg2 = (((reg2 & FMAC_FLAG_X1BUFFF) == 0U)?FMAC_FLAG_X1BUFFF:0U);
            break;
        /* overflow error interrupt */
        case FMAC_INT_FLAG_OVF:
            reg1 = reg1 & FMAC_INT_OV;
            reg2 = reg2 & FMAC_FLAG_OVF;
            break;
        /* underflow error interrupt */
        case FMAC_INT_FLAG_UNF:
            reg1 = reg1 & FMAC_INT_UN;
            reg2 = reg2 & FMAC_FLAG_UNF;
            break;
        /* saturation error interrupt */
        case FMAC_INT_FLAG_SATF:
            reg1 = reg1 & FMAC_INT_SAT;
            reg2 = reg2 & FMAC_FLAG_SATF;
            break;
        /* saturation error interrupt */
        default :
            break;
    }
    /*get FAC interrupt flag status */
    if((reg1 != (uint32_t)RESET) && (reg2 != (uint32_t)RESET)) 
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
*\*\name    FMAC_GetFlagStatus
*\*\fun     Get FMAC flag status
*\*\param   interrupt :
*\*\            - FMAC_FLAG_YBUFEF: Read buffer interrupt 
*\*\            - FMAC_FLAG_X1BUFFF: Write buffer interrupt
*\*\            - FMAC_FLAG_OVF: Overflow error interrupt
*\*\            - FMAC_FLAG_UNF: Underflow error interrupt
*\*\            - FMAC_FLAG_SATF: Saturation error interrupt
*\*\return  FlagStatus: 
*\*\            - SET
*\*\            - RESET
**/
FlagStatus FMAC_GetFlagStatus(uint32_t FMAC_FLAG)
{
    FlagStatus bitstatus = RESET;
    
    if ((FMAC->STS & FMAC_FLAG) != (uint32_t)RESET) 
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}
