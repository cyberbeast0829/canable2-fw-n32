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
*\*\file n32h47x_48x_dma.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/
#include "n32h47x_48x_dma.h"
#include "n32h47x_48x_rcc.h"

/** DMA Driving Functions Declaration **/

/**
*\*\name    DMA_DeInit.
*\*\fun     Reset CHCFG, TXNUM, PADDR, MADDR, INTCLR registers of DMA1/DMA2 Channel x
*\*\        to their default reset values.
*\*\param   DMAChx (The input parameters must be the following values):
*\*\          - DMA1_CH1
*\*\          - DMA1_CH2
*\*\          - DMA1_CH3
*\*\          - DMA1_CH4
*\*\          - DMA1_CH5
*\*\          - DMA1_CH6
*\*\          - DMA1_CH7
*\*\          - DMA1_CH8
*\*\          - DMA2_CH1
*\*\          - DMA2_CH2
*\*\          - DMA2_CH3
*\*\          - DMA2_CH4
*\*\          - DMA2_CH5
*\*\          - DMA2_CH6
*\*\          - DMA2_CH7
*\*\          - DMA2_CH8
*\*\return  none
**/
void DMA_DeInit(DMA_ChannelType* DMAChx)
{

    /* Disable the selected DMAy Channelx */
    DMAChx->CHCFG &= DMA_CHANNEL_DISABLE;

    /* Reset DMAy Channelx control register */
    DMAChx->CHCFG  = 0;
 
    /* Reset DMAy Channelx remaining bytes register */
    DMAChx->TXNUM = 0;

    /* Reset DMAy Channelx peripheral address register */
    DMAChx->PADDR  = 0;

    /* Reset DMAy Channelx memory address register */
    DMAChx->MADDR = 0;

    if (DMAChx == DMA1_CH1)
    {
        /* Reset interrupt pending bits for DMA1 Channel1 */
        DMA1->INTCLR |= DMA_CH1_INT_MASK;
    }
    else if (DMAChx == DMA1_CH2)
    {
        /* Reset interrupt pending bits for DMA1 Channel2 */
        DMA1->INTCLR |= DMA_CH2_INT_MASK;
    }
    else if (DMAChx == DMA1_CH3)
    {
        /* Reset interrupt pending bits for DMA1 Channel3 */
        DMA1->INTCLR |= DMA_CH3_INT_MASK;
    }
    else if (DMAChx == DMA1_CH4)
    {
        /* Reset interrupt pending bits for DMA1 Channel4 */
        DMA1->INTCLR |= DMA_CH4_INT_MASK;
    }
    else if (DMAChx == DMA1_CH5)
    {
        /* Reset interrupt pending bits for DMA1 Channel5 */
        DMA1->INTCLR |= DMA_CH5_INT_MASK;
    }
    else if (DMAChx == DMA1_CH6)
    {
        /* Reset interrupt pending bits for DMA1 Channel6 */
        DMA1->INTCLR |= DMA_CH6_INT_MASK;
    }
    else if (DMAChx == DMA1_CH7)
    {
        /* Reset interrupt pending bits for DMA1 Channel7 */
        DMA1->INTCLR |= DMA_CH7_INT_MASK;
    }
    else if (DMAChx == DMA1_CH8)
    {
        /* Reset interrupt pending bits for DMA1 Channel8 */
        DMA1->INTCLR |= DMA_CH8_INT_MASK;
    }
    else if (DMAChx == DMA2_CH1)
    {
        /* Reset interrupt pending bits for DMA2 Channel1 */
        DMA2->INTCLR |= DMA_CH1_INT_MASK;
    }
    else if (DMAChx == DMA2_CH2)
    {
        /* Reset interrupt pending bits for DMA2 Channel2 */
        DMA2->INTCLR |= DMA_CH2_INT_MASK;
    }
    else if (DMAChx == DMA2_CH3)
    {
        /* Reset interrupt pending bits for DMA2 Channel3 */
        DMA2->INTCLR |= DMA_CH3_INT_MASK;
    }
    else if (DMAChx == DMA2_CH4)
    {
        /* Reset interrupt pending bits for DMA2 Channel4 */
        DMA2->INTCLR |= DMA_CH4_INT_MASK;
    }
    else if (DMAChx == DMA2_CH5)
    {
        /* Reset interrupt pending bits for DMA2 Channel5 */
        DMA2->INTCLR |= DMA_CH5_INT_MASK;
    }
    else if (DMAChx == DMA2_CH6)
    {
        /* Reset interrupt pending bits for DMA2 Channel6 */
        DMA2->INTCLR |= DMA_CH6_INT_MASK;
    }
    else if (DMAChx == DMA2_CH7)
    {
        /* Reset interrupt pending bits for DMA2 Channel7 */
        DMA2->INTCLR |= DMA_CH7_INT_MASK;
    }
    else if (DMAChx == DMA2_CH8)
    { 
        /* Reset interrupt pending bits for DMA2 Channel8 */
        DMA2->INTCLR |= DMA_CH8_INT_MASK;
    }else{
    
    }
}

/**
*\*\name    DMA_Init.
*\*\fun     Initializes the DMA Channel x by the structure parameter
*\*\        DMA_InitParam of type DMA_InitType. Includes configuration
*\*\        peripheral/memory address, transmission direction, address
*\*\        increment mode, data bit width, priority, etc.
*\*\param   DMAChx (The input parameters must be the following values):
*\*\          - DMA1_CH1
*\*\          - DMA1_CH2
*\*\          - DMA1_CH3
*\*\          - DMA1_CH4
*\*\          - DMA1_CH5
*\*\          - DMA1_CH6
*\*\          - DMA1_CH7
*\*\          - DMA1_CH8
*\*\          - DMA2_CH1
*\*\          - DMA2_CH2
*\*\          - DMA2_CH3
*\*\          - DMA2_CH4
*\*\          - DMA2_CH5
*\*\          - DMA2_CH6
*\*\          - DMA2_CH7
*\*\          - DMA2_CH8
*\*\param   DMA_InitParam (The input parameters must be the following values):
*\*\          - PeriphAddr
*\*\          - MemAddr
*\*\          - Direction
*\*\            - DMA_DIR_PERIPH_DST
*\*\            - DMA_DIR_PERIPH_SRC
*\*\          - BufSize
*\*\          - PeriphInc
*\*\            - DMA_PERIPH_INC_ENABLE
*\*\            - DMA_PERIPH_INC_DISABLE
*\*\          - MemoryInc
*\*\            - DMA_MEM_INC_ENABLE
*\*\            - DMA_MEM_INC_DISABLE
*\*\          - PeriphDataSize
*\*\            - DMA_PERIPH_DATA_WIDTH_BYTE
*\*\            - DMA_PERIPH_DATA_WIDTH_HALFWORD
*\*\            - DMA_PERIPH_DATA_WIDTH_WORD
*\*\          - MemDataSize
*\*\            - DMA_MEM_DATA_WIDTH_BYTE
*\*\            - DMA_MEM_DATA_WIDTH_HALFWORD
*\*\            - DMA_MEM_DATA_WIDTH_WORD
*\*\          - CircularMode
*\*\            - DMA_MODE_CIRCULAR
*\*\            - DMA_MODE_NORMAL
*\*\          - Priority
*\*\            - DMA_PRIORITY_VERY_HIGH
*\*\            - DMA_PRIORITY_HIGH
*\*\            - DMA_PRIORITY_MEDIUM
*\*\            - DMA_PRIORITY_LOW
*\*\          - Mem2Mem
*\*\            - DMA_M2M_ENABLE
*\*\            - DMA_M2M_DISABLE
*\*\          - BURST_BYPASS
*\*\            - DMA_BURST_BYPASS_ENABLE 
*\*\            - DMA_BURST_BYPASS_DISABLE
*\*\          - BURST_MODE
*\*\            - DMA_BURST_MODE_Almost 
*\*\            - DMA_BURST_MODE_Dynamic
*\*\          - BURST_LEN
*\*\            - DMA_BURST_LEN_single
*\*\            - DMA_BURST_LEN_1     
*\*\            - DMA_BURST_LEN_2     
*\*\            - DMA_BURST_LEN_3     
*\*\            - DMA_BURST_LEN_4     
*\*\            - DMA_BURST_LEN_5     
*\*\            - DMA_BURST_LEN_6     
*\*\            - DMA_BURST_LEN_7     
*\*\            - DMA_BURST_LEN_8       
*\*\return  none
**/
void DMA_Init(DMA_ChannelType* DMAChx, DMA_InitType* DMA_InitParam)
{
    uint32_t tmpregister;

/*--------------------------- DMAy Channelx CHCFG Configuration -----------------*/
    /* Get the DMAChx CHCFG value */
    tmpregister = DMAChx->CHCFG;
    /* Clear MEM2MEM, PRIOLVL, MSIZE, PSIZE, MINC, PINC, CIRC, DIR, BURST_MODE and BLEN bits */
    tmpregister &= CHCFG_CLEAR_MASK;
    /* Configure DMAy Channelx: data transfer, data size, priority level and mode */
    /* Set DIR bit according to Direction value */
    /* Set CIRC bit according to CircularMode value */
    /* Set PINC bit according to PeriphInc value */
    /* Set MINC bit according to MemoryInc value */
    /* Set PSIZE bits according to PeriphDataSize value */
    /* Set MSIZE bits according to MemDataSize value */
    /* Set PRIOLVL bits according to Priority value */
    /* Set the MEM2MEM bit according to Mem2Mem value */
    /*Set the BURST_MODE bit according to BURST_MODE value*/
    /*Set the BLEN bit according to BURST_LEN value*/
    tmpregister |= DMA_InitParam->Direction | DMA_InitParam->CircularMode |
              DMA_InitParam->PeriphInc | DMA_InitParam->MemoryInc |
              DMA_InitParam->PeriphDataSize | DMA_InitParam->MemDataSize |
              DMA_InitParam->Priority | DMA_InitParam->Mem2Mem|
              DMA_InitParam->BURST_MODE | DMA_InitParam->BURST_LEN;

    /* Write to DMAy Channelx CHCFG */
    DMAChx->CHCFG = tmpregister;

    /* DMAy Channelx TXNUM Configuration */
    /* Write to DMAy Channelx TXNUM */
    DMAChx->TXNUM = DMA_InitParam->BufSize;

    /* DMAy Channelx PADDR Configuration */
    /* Write to DMAy Channelx PADDR */
    DMAChx->PADDR = DMA_InitParam->PeriphAddr;

    /* DMAy Channelx MADDR Configuration */
    /* Write to DMAy Channelx MADDR */
    DMAChx->MADDR = DMA_InitParam->MemAddr;

    /* DMA BURST Configuration  */
    /* Write to DMAy DMA BURST Bypass */
    if ((u32)DMAChx < DMA2_BASE){
        DMA1->BURSTEN = DMA_InitParam->BURST_BYPASS;    
    }
    else
    {
        DMA2->BURSTEN = DMA_InitParam->BURST_BYPASS;
    }
}

/**
*\*\name    DMA_StructInit.
*\*\fun     Initializes the structure parameter of type DMA_InitType used to
*\*\        initialize DMA. This function is usually called before initializing
*\*\        a parameter of type DMA_InitType.
*\*\param   DMA_InitParam :
*\*\          - Pointer to the DMA_InitType structure which will be initialized.
*\*\return  none
**/
void DMA_StructInit(DMA_InitType* DMA_InitParam)
{
/*-------------- Reset DMA init structure parameters values ------------------*/
    /* Initialize the PeriphAddr member */
    DMA_InitParam->PeriphAddr = 0;
    /* Initialize the MemAddr member */
    DMA_InitParam->MemAddr = 0;
    /* Initialize the Direction member */
    DMA_InitParam->Direction = DMA_DIR_PERIPH_SRC;
    /* Initialize the BufSize member */
    DMA_InitParam->BufSize = 0;
    /* Initialize the PeriphInc member */
    DMA_InitParam->PeriphInc = DMA_PERIPH_INC_DISABLE;
    /* Initialize the MemoryInc member */
    DMA_InitParam->MemoryInc = DMA_MEM_INC_DISABLE;
    /* Initialize the PeriphDataSize member */
    DMA_InitParam->PeriphDataSize = DMA_PERIPH_DATA_WIDTH_BYTE;
    /* Initialize the MemDataSize member */
    DMA_InitParam->MemDataSize = DMA_MEM_DATA_WIDTH_BYTE;
    /* Initialize the CircularMode member */
    DMA_InitParam->CircularMode = DMA_MODE_NORMAL;
    /* Initialize the Priority member */
    DMA_InitParam->Priority = DMA_PRIORITY_LOW;
    /* Initialize the Mem2Mem member */
    DMA_InitParam->Mem2Mem = DMA_M2M_DISABLE;    
    /* close DMA BURST */
    DMA_InitParam->BURST_BYPASS = DMA_BURST_BYPASS_DISABLE;
    /* BURST mode is almost */
    DMA_InitParam->BURST_MODE = DMA_BURST_MODE_ALMOST;    
    /* BURST length is 0:single mode */
    DMA_InitParam->BURST_LEN = DMA_BURST_LEN_SINGLE;   
    
}

/**
*\*\name    DMA_EnableChannel.
*\*\fun     DMA Channel x Channel enable. This function is called after DMA
*\*\        initialization is successful to start moving data.
*\*\param   DMAChx (The input parameters must be the following values):
*\*\          - DMA1_CH1
*\*\          - DMA1_CH2
*\*\          - DMA1_CH3
*\*\          - DMA1_CH4
*\*\          - DMA1_CH5
*\*\          - DMA1_CH6
*\*\          - DMA1_CH7
*\*\          - DMA1_CH8
*\*\          - DMA2_CH1
*\*\          - DMA2_CH2
*\*\          - DMA2_CH3
*\*\          - DMA2_CH4
*\*\          - DMA2_CH5
*\*\          - DMA2_CH6
*\*\          - DMA2_CH7
*\*\          - DMA2_CH8
*\*\param  Cmd:(The input parameters must be the following values)
*\*\            - ENABLE
*\*\            - DISABLE 
*\*\return  none
**/
void DMA_EnableChannel(DMA_ChannelType* DMAChx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected DMAy Channelx */
        DMAChx->CHCFG |= DMA_CHANNEL_ENABLE;            
    }
    else
    {
        /* Disable the selected DMAy Channelx */
        DMAChx->CHCFG &= DMA_CHANNEL_DISABLE;
    }
}

/**
*\*\name    DMA_ConfigInt.
*\*\fun     DMA Channel x interrupts enable. Before enabling a DMA channel,
*\*\        enabling transfer completion interrupt, half-transfer interrupt
*\*\        or transfer error interrupt will cause an interrupt when the
*\*\        corresponding event occurs.
*\*\param   DMAChx (The input parameters must be the following values):
*\*\          - DMA1_CH1
*\*\          - DMA1_CH2
*\*\          - DMA1_CH3
*\*\          - DMA1_CH4
*\*\          - DMA1_CH5
*\*\          - DMA1_CH6
*\*\          - DMA1_CH7
*\*\          - DMA1_CH8
*\*\          - DMA2_CH1
*\*\          - DMA2_CH2
*\*\          - DMA2_CH3
*\*\          - DMA2_CH4
*\*\          - DMA2_CH5
*\*\          - DMA2_CH6
*\*\          - DMA2_CH7
*\*\          - DMA2_CH8
*\*\param   DMAInt (The input parameters must be the following values):
*\*\          - DMA_INT_TXC
*\*\          - DMA_INT_HTX
*\*\          - DMA_INT_ERR
*\*\param  Cmd:(The input parameters must be the following values)
*\*\            - ENABLE
*\*\            - DISABLE 
*\*\return  none
**/
void DMA_ConfigInt(DMA_ChannelType* DMAChx, uint32_t DMAInt, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected DMA interrupts */
        DMAChx->CHCFG |= DMAInt;
    }
    else
    {
        /* Disable the selected DMA interrupts */
        DMAChx->CHCFG &= ~DMAInt;
    }
}

/**
*\*\name    DMA_SetCurrDataCounter.
*\*\fun     Set the current number of data transfers for DMA Channel x.
*\*\param   DMAChx (The input parameters must be the following values):
*\*\          - DMA1_CH1
*\*\          - DMA1_CH2
*\*\          - DMA1_CH3
*\*\          - DMA1_CH4
*\*\          - DMA1_CH5
*\*\          - DMA1_CH6
*\*\          - DMA1_CH7
*\*\          - DMA1_CH8
*\*\          - DMA2_CH1
*\*\          - DMA2_CH2
*\*\          - DMA2_CH3
*\*\          - DMA2_CH4
*\*\          - DMA2_CH5
*\*\          - DMA2_CH6
*\*\          - DMA2_CH7
*\*\          - DMA2_CH8
*\*\param   DataNumber(The input parameters must be the following values) :
*\*\          - 1~0xFFFF
*\*\return  none
*\*\note    This function can only be used when the DMAChx is disabled.
**/
void DMA_SetCurrDataCounter(DMA_ChannelType* DMAChx, uint16_t DataNumber)
{
    /* Write to DMAy Channelx TXNUM */
    DMAChx->TXNUM = DataNumber;  
}

/**
*\*\name    DMA_GetCurrDataCounter.
*\*\fun     Get the current number of remaining data for DMA Channel x.
*\*\param   DMAChx (The input parameters must be the following values):
*\*\          - DMA1_CH1
*\*\          - DMA1_CH2
*\*\          - DMA1_CH3
*\*\          - DMA1_CH4
*\*\          - DMA1_CH5
*\*\          - DMA1_CH6
*\*\          - DMA1_CH7
*\*\          - DMA1_CH8
*\*\          - DMA2_CH1
*\*\          - DMA2_CH2
*\*\          - DMA2_CH3
*\*\          - DMA2_CH4
*\*\          - DMA2_CH5
*\*\          - DMA2_CH6
*\*\          - DMA2_CH7
*\*\          - DMA2_CH8
*\*\return  Returns the number of bytes remaining to be transferred.
**/
uint16_t DMA_GetCurrDataCounter(DMA_ChannelType* DMAChx)
{
    /* Return the number of remaining data units for DMAy Channelx */
    return ((uint16_t)(DMAChx->TXNUM));
}
/**
*\*\name    DMA_GetFlagStatus.
*\*\fun     Get DMA Channel x flag status. Contains the global flag, transfer
*\*\        completion flag, half-transfer flag, and transfer error flag for
*\*\        the corresponding channel.
*\*\param   DMAFlag (The input parameters must be the following values):
*\*\          - DMA_FLAG_GL1
*\*\          - DMA_FLAG_TC1
*\*\          - DMA_FLAG_HT1
*\*\          - DMA_FLAG_TE1
*\*\          - DMA_FLAG_GL2
*\*\          - DMA_FLAG_TC2
*\*\          - DMA_FLAG_HT2
*\*\          - DMA_FLAG_TE2
*\*\          - DMA_FLAG_GL3
*\*\          - DMA_FLAG_TC3
*\*\          - DMA_FLAG_HT3
*\*\          - DMA_FLAG_TE3
*\*\          - DMA_FLAG_GL4
*\*\          - DMA_FLAG_TC4
*\*\          - DMA_FLAG_HT4
*\*\          - DMA_FLAG_TE4
*\*\          - DMA_FLAG_GL5
*\*\          - DMA_FLAG_TC5
*\*\          - DMA_FLAG_HT5
*\*\          - DMA_FLAG_TE5
*\*\          - DMA_FLAG_GL6
*\*\          - DMA_FLAG_TC6
*\*\          - DMA_FLAG_HT6
*\*\          - DMA_FLAG_TE6
*\*\          - DMA_FLAG_GL7
*\*\          - DMA_FLAG_TC7
*\*\          - DMA_FLAG_HT7
*\*\          - DMA_FLAG_TE7
*\*\          - DMA_FLAG_GL8
*\*\          - DMA_FLAG_TC8
*\*\          - DMA_FLAG_HT8
*\*\          - DMA_FLAG_TE8
*\*\param   DMAy (The input parameters must be the following values):
*\*\          - DMA1
*\*\          - DMA2
*\*\return  SET or RESET.
**/
FlagStatus DMA_GetFlagStatus(uint32_t DMAFlag, DMA_Module *DMAy)
{
    FlagStatus bitstatus;
    uint32_t tmpregister;

    /* Calculate the used DMAy */
    /* Get DMAy INTSTS register value */
    tmpregister = DMAy->INTSTS ;

    /* Check the status of the specified DMAy flag */
    if ((tmpregister & DMAFlag) != (uint32_t)RESET)
    {
        /* DMAFlag is set */
        bitstatus = SET;
    }
    else
    {
        /* DMAFlag is reset */
        bitstatus = RESET;
    }
  
    /* Return the DMAFlag status */
    return  bitstatus;
}
/**
*\*\name    DMA_ClearFlag.
*\*\fun     Clear DMA Channel x flag status. Contains the global flag, transfer
*\*\        completion flag, half-transfer flag, and transfer error flag for the
*\*\        corresponding channel.
*\*\param   DMAFlag (The input parameters must be the following values):
*\*\          - DMA_FLAG_GL1
*\*\          - DMA_FLAG_TC1
*\*\          - DMA_FLAG_HT1
*\*\          - DMA_FLAG_TE1
*\*\          - DMA_FLAG_GL2
*\*\          - DMA_FLAG_TC2
*\*\          - DMA_FLAG_HT2
*\*\          - DMA_FLAG_TE2
*\*\          - DMA_FLAG_GL3
*\*\          - DMA_FLAG_TC3
*\*\          - DMA_FLAG_HT3
*\*\          - DMA_FLAG_TE3
*\*\          - DMA_FLAG_GL4
*\*\          - DMA_FLAG_TC4
*\*\          - DMA_FLAG_HT4
*\*\          - DMA_FLAG_TE4
*\*\          - DMA_FLAG_GL5
*\*\          - DMA_FLAG_TC5
*\*\          - DMA_FLAG_HT5
*\*\          - DMA_FLAG_TE5
*\*\          - DMA_FLAG_GL6
*\*\          - DMA_FLAG_TC6
*\*\          - DMA_FLAG_HT6
*\*\          - DMA_FLAG_TE6
*\*\          - DMA_FLAG_GL7
*\*\          - DMA_FLAG_TC7
*\*\          - DMA_FLAG_HT7
*\*\          - DMA_FLAG_TE7
*\*\          - DMA_FLAG_GL8
*\*\          - DMA_FLAG_TC8
*\*\          - DMA_FLAG_HT8
*\*\          - DMA_FLAG_TE8
*\*\param   DMAy (The input parameters must be the following values):
*\*\          - DMA1
*\*\          - DMA2
*\*\return  none.
**/
void DMA_ClearFlag(uint32_t DMAFlag, DMA_Module *DMAy)
{

    /* Calculate the used DMAy */
    /* Clear the selected DMAy flags */
    DMAy->INTCLR = DMAFlag;
}

/**
*\*\name    DMA_GetIntStatus.
*\*\fun     Get DMA Channel x interrupt status. Contains the global interrupt,
*\*\        transfer completion interrupt, half-transfer interrupt, and transfer
*\*\        error interrupt for the corresponding channel.
*\*\param   DMAy_Int (The input parameters must be the following values):
*\*\          - DMA_INT_GLB1
*\*\          - DMA_INT_TXC1
*\*\          - DMA_INT_HTX1
*\*\          - DMA_INT_ERR1
*\*\          - DMA_INT_GLB2
*\*\          - DMA_INT_TXC2
*\*\          - DMA_INT_HTX2
*\*\          - DMA_INT_ERR2
*\*\          - DMA_INT_GLB3
*\*\          - DMA_INT_TXC3
*\*\          - DMA_INT_HTX3
*\*\          - DMA_INT_ERR3
*\*\          - DMA_INT_GLB4
*\*\          - DMA_INT_TXC4
*\*\          - DMA_INT_HTX4
*\*\          - DMA_INT_ERR4
*\*\          - DMA_INT_GLB5
*\*\          - DMA_INT_TXC5
*\*\          - DMA_INT_HTX5
*\*\          - DMA_INT_ERR5
*\*\          - DMA_INT_GLB6
*\*\          - DMA_INT_TXC6
*\*\          - DMA_INT_HTX6
*\*\          - DMA_INT_ERR6
*\*\          - DMA_INT_GLB7
*\*\          - DMA_INT_TXC7
*\*\          - DMA_INT_HTX7
*\*\          - DMA_INT_ERR7
*\*\          - DMA_INT_GLB8
*\*\          - DMA_INT_TXC8
*\*\          - DMA_INT_HTX8
*\*\          - DMA_INT_ERR8
*\*\param   DMAy (The input parameters must be the following values):
*\*\          - DMA1
*\*\          - DMA2
*\*\return  SET or RESET.
*\*\note    Global interrupt status is the logic or generation of transfer completion
*\*\        interrupt, half-transfer interrupt, transfer error interrupt.
**/
INTStatus DMA_GetIntStatus(uint32_t DMAy_Int, DMA_Module *DMAy)
{
    INTStatus bitstatus;
    uint32_t tmpregister;


    /* Calculate the used DMA */
    /* Get DMAy INTSTS register value */
    tmpregister = DMAy->INTSTS;

    /* Check the status of the specified DMAy interrupt */
    if ((tmpregister & DMAy_Int) != (uint32_t)RESET)
    {
        /* DMAy_IT is set */
        bitstatus = SET;
    }
    else
    {
        /* DMAy_IT is reset */
        bitstatus = RESET;
    }
    /* Return the DMA_IT status */
    return  bitstatus;
}

/**
*\*\name    DMA_ClrIntPendingBit.
*\*\fun     Clear DMA Channel x interrupt status bits. Contains the global interrupt,
*\*\        transfer completion interrupt, half-transfer interrupt, and transfer
*\*\        error interrupt for the corresponding channel.
*\*\param   DMAy_Int (The input parameters must be the following values):
*\*\          - DMA_INT_GLB1
*\*\          - DMA_INT_TXC1
*\*\          - DMA_INT_HTX1
*\*\          - DMA_INT_ERR1
*\*\          - DMA_INT_GLB2
*\*\          - DMA_INT_TXC2
*\*\          - DMA_INT_HTX2
*\*\          - DMA_INT_ERR2
*\*\          - DMA_INT_GLB3
*\*\          - DMA_INT_TXC3
*\*\          - DMA_INT_HTX3
*\*\          - DMA_INT_ERR3
*\*\          - DMA_INT_GLB4
*\*\          - DMA_INT_TXC4
*\*\          - DMA_INT_HTX4
*\*\          - DMA_INT_ERR4
*\*\          - DMA_INT_GLB5
*\*\          - DMA_INT_TXC5
*\*\          - DMA_INT_HTX5
*\*\          - DMA_INT_ERR5
*\*\          - DMA_INT_GLB6
*\*\          - DMA_INT_TXC6
*\*\          - DMA_INT_HTX6
*\*\          - DMA_INT_ERR6
*\*\          - DMA_INT_GLB7
*\*\          - DMA_INT_TXC7
*\*\          - DMA_INT_HTX7
*\*\          - DMA_INT_ERR7
*\*\          - DMA_INT_GLB8
*\*\          - DMA_INT_TXC8
*\*\          - DMA_INT_HTX8
*\*\          - DMA_INT_ERR8
*\*\param   DMAy (The input parameters must be the following values):
*\*\          - DMA1
*\*\          - DMA2
*\*\return  none.
*\*\note    Global interrupt state is the logic or generation of transfer completion
*\*\        interrupt, half-transfer interrupt, transfer error interrupt. In fact,
*\*\        after clearing the three interrupt states, the global interrupt state
*\*\        will also be cleared.
**/
void DMA_ClrIntPendingBit(uint32_t DMAy_Int, DMA_Module *DMAy)
{
    /* Calculate the used DMAy */
    /* Clear the selected DMAy interrupt pending bits */
    DMAy->INTCLR = DMAy_Int;
}

/**
*\*\name    DMA_RequestRemap.
*\*\fun     Set DMA Channel x's remap request. Channel request mapping is flexible,
*\*\        allowing users to map any DMA request to any DMA channel as needed. It
*\*\        is important to note that there can be only one DMA request per DMA
*\*\        channel at a time.
*\*\param   DMA_Remap (The input parameters must be the following values):
*\*\          -DMA_REMAP_ADC1         
*\*\          -DMA_REMAP_ADC2         
*\*\          -DMA_REMAP_ADC3         
*\*\          -DMA_REMAP_ADC4         
*\*\          -DMA_REMAP_USART1_TX    
*\*\          -DMA_REMAP_USART1_RX    
*\*\          -DMA_REMAP_USART2_TX    
*\*\          -DMA_REMAP_USART2_RX    
*\*\          -DMA_REMAP_USART3_TX    
*\*\          -DMA_REMAP_USART3_RX    
*\*\          -DMA_REMAP_USART4_TX    
*\*\          -DMA_REMAP_USART4_RX    
*\*\          -DMA_REMAP_UART5_TX     
*\*\          -DMA_REMAP_UART5_RX     
*\*\          -DMA_REMAP_UART6_TX     
*\*\          -DMA_REMAP_UART6_RX     
*\*\          -DMA_REMAP_UART7_TX     
*\*\          -DMA_REMAP_UART7_RX     
*\*\          -DMA_REMAP_UART8_TX     
*\*\          -DMA_REMAP_UART8_RX     
*\*\          -DMA_REMAP_SPI1_TX      
*\*\          -DMA_REMAP_SPI1_RX      
*\*\          -DMA_REMAP_SPI2_I2S2_TX 
*\*\          -DMA_REMAP_SPI2_I2S2_RX 
*\*\          -DMA_REMAP_TTCAN1       
*\*\          -DMA_REMAP_TTCAN2       
*\*\          -DMA_REMAP_SPI3_I2S3_TX 
*\*\          -DMA_REMAP_SPI3_I2S3_RX 
*\*\          -DMA_REMAP_TTCAN3       
*\*\          -DMA_REMAP_SPI4_TX      
*\*\          -DMA_REMAP_SPI4_RX      
*\*\          -DMA_REMAP_SPI5_TX      
*\*\          -DMA_REMAP_SPI5_RX      
*\*\          -DMA_REMAP_SPI6_TX      
*\*\          -DMA_REMAP_SPI6_RX      
*\*\          -DMA_REMAP_XSPI_TX      
*\*\          -DMA_REMAP_XSPI_RX      
*\*\          -DMA_REMAP_I2C1_TX      
*\*\          -DMA_REMAP_I2C1_RX      
*\*\          -DMA_REMAP_I2C2_TX      
*\*\          -DMA_REMAP_I2C2_RX      
*\*\          -DMA_REMAP_I2C3_TX      
*\*\          -DMA_REMAP_I2C3_RX      
*\*\          -DMA_REMAP_I2C4_TX      
*\*\          -DMA_REMAP_I2C4_RX      
*\*\          -DMA_REMAP_SDIO_DMA     
*\*\          -DMA_REMAP_DAC1_DMA     
*\*\          -DMA_REMAP_DAC2_DMA     
*\*\          -DMA_REMAP_DAC3_DMA     
*\*\          -DMA_REMAP_DAC4_DMA     
*\*\          -DMA_REMAP_DAC5_DMA     
*\*\          -DMA_REMAP_DAC6_DMA     
*\*\          -DMA_REMAP_DAC7_DMA     
*\*\          -DMA_REMAP_DAC8_DMA     
*\*\          -DMA_REMAP_FMAC_WR      
*\*\          -DMA_REMAP_FMAC_RD      
*\*\          -DMA_REMAP_CORDIC_WR    
*\*\          -DMA_REMAP_CORDIC_RD    
*\*\          -DMA_REMAP_BTIM1_UP     
*\*\          -DMA_REMAP_BTIM2_UP     
*\*\          -DMA_REMAP_GTIM1_CH1    
*\*\          -DMA_REMAP_GTIM1_CH2    
*\*\          -DMA_REMAP_GTIM1_CH3    
*\*\          -DMA_REMAP_GTIM1_CH4    
*\*\          -DMA_REMAP_GTIM1_UP     
*\*\          -DMA_REMAP_GTIM1_TRIG   
*\*\          -DMA_REMAP_GTIM2_CH1    
*\*\          -DMA_REMAP_GTIM2_CH2    
*\*\          -DMA_REMAP_GTIM2_CH3    
*\*\          -DMA_REMAP_GTIM2_CH4    
*\*\          -DMA_REMAP_GTIM2_UP     
*\*\          -DMA_REMAP_GTIM2_TRIG   
*\*\          -DMA_REMAP_GTIM3_CH1    
*\*\          -DMA_REMAP_GTIM3_CH2    
*\*\          -DMA_REMAP_GTIM3_CH3    
*\*\          -DMA_REMAP_GTIM3_CH4    
*\*\          -DMA_REMAP_GTIM3_UP     
*\*\          -DMA_REMAP_GTIM3_TRIG   
*\*\          -DMA_REMAP_GTIM4_CH1    
*\*\          -DMA_REMAP_GTIM4_CH2    
*\*\          -DMA_REMAP_GTIM4_CH3    
*\*\          -DMA_REMAP_GTIM4_CH4    
*\*\          -DMA_REMAP_GTIM4_UP     
*\*\          -DMA_REMAP_GTIM4_TRIG   
*\*\          -DMA_REMAP_GTIM5_CH1    
*\*\          -DMA_REMAP_GTIM5_CH2    
*\*\          -DMA_REMAP_GTIM5_CH3    
*\*\          -DMA_REMAP_GTIM5_CH4    
*\*\          -DMA_REMAP_GTIM5_UP     
*\*\          -DMA_REMAP_GTIM5_TRIG   
*\*\          -DMA_REMAP_GTIM6_CH1    
*\*\          -DMA_REMAP_GTIM6_CH2    
*\*\          -DMA_REMAP_GTIM6_CH3    
*\*\          -DMA_REMAP_GTIM6_CH4    
*\*\          -DMA_REMAP_GTIM6_UP     
*\*\          -DMA_REMAP_GTIM6_TRIG   
*\*\          -DMA_REMAP_GTIM7_CH1    
*\*\          -DMA_REMAP_GTIM7_CH2    
*\*\          -DMA_REMAP_GTIM7_CH3    
*\*\          -DMA_REMAP_GTIM7_CH4    
*\*\          -DMA_REMAP_GTIM7_UP     
*\*\          -DMA_REMAP_GTIM7_TRIG   
*\*\          -DMA_REMAP_GTIM8_CH1    
*\*\          -DMA_REMAP_GTIM8_CH2    
*\*\          -DMA_REMAP_GTIM8_CH3    
*\*\          -DMA_REMAP_GTIM8_CH4    
*\*\          -DMA_REMAP_GTIM8_COM    
*\*\          -DMA_REMAP_GTIM8_UP     
*\*\          -DMA_REMAP_GTIM8_TRIG   
*\*\          -DMA_REMAP_GTIM9_CH1    
*\*\          -DMA_REMAP_GTIM9_CH2    
*\*\          -DMA_REMAP_GTIM9_CH3    
*\*\          -DMA_REMAP_GTIM9_CH4    
*\*\          -DMA_REMAP_GTIM9_COM    
*\*\          -DMA_REMAP_GTIM9_UP     
*\*\          -DMA_REMAP_GTIM9_TRIG   
*\*\          -DMA_REMAP_GTIM10_CH1   
*\*\          -DMA_REMAP_GTIM10_CH2   
*\*\          -DMA_REMAP_GTIM10_CH3   
*\*\          -DMA_REMAP_GTIM10_CH4   
*\*\          -DMA_REMAP_GTIM10_COM   
*\*\          -DMA_REMAP_GTIM10_UP    
*\*\          -DMA_REMAP_GTIM10_TRIG  
*\*\          -DMA_REMAP_ATIM1_CH1    
*\*\          -DMA_REMAP_ATIM1_CH2    
*\*\          -DMA_REMAP_ATIM1_CH3    
*\*\          -DMA_REMAP_ATIM1_CH4    
*\*\          -DMA_REMAP_ATIM1_COM    
*\*\          -DMA_REMAP_ATIM1_UP     
*\*\          -DMA_REMAP_ATIM1_TRIG   
*\*\          -DMA_REMAP_ATIM2_CH1    
*\*\          -DMA_REMAP_ATIM2_CH2    
*\*\          -DMA_REMAP_ATIM2_CH3    
*\*\          -DMA_REMAP_ATIM2_CH4    
*\*\          -DMA_REMAP_ATIM2_COM    
*\*\          -DMA_REMAP_ATIM2_UP     
*\*\          -DMA_REMAP_ATIM2_TRIG   
*\*\          -DMA_REMAP_ATIM3_CH1    
*\*\          -DMA_REMAP_ATIM3_CH2    
*\*\          -DMA_REMAP_ATIM3_CH3    
*\*\          -DMA_REMAP_ATIM3_CH4    
*\*\          -DMA_REMAP_ATIM3_COM    
*\*\          -DMA_REMAP_ATIM3_UP     
*\*\          -DMA_REMAP_ATIM3_TRIG   
*\*\          -DMA_REMAP_SHRTIM1_CH1  
*\*\          -DMA_REMAP_SHRTIM1_CH2  
*\*\          -DMA_REMAP_SHRTIM1_CH3  
*\*\          -DMA_REMAP_SHRTIM1_CH4  
*\*\          -DMA_REMAP_SHRTIM1_CH5  
*\*\          -DMA_REMAP_SHRTIM1_CH6  
*\*\          -DMA_REMAP_SHRTIM1_CH7  
*\*\param   DMAChx (The input parameters must be the following values):
*\*\          - DMA1_CH1
*\*\          - DMA1_CH2
*\*\          - DMA1_CH3
*\*\          - DMA1_CH4
*\*\          - DMA1_CH5
*\*\          - DMA1_CH6
*\*\          - DMA1_CH7
*\*\          - DMA1_CH8
*\*\          - DMA2_CH1
*\*\          - DMA2_CH2
*\*\          - DMA2_CH3
*\*\          - DMA2_CH4
*\*\          - DMA2_CH5
*\*\          - DMA2_CH6
*\*\          - DMA2_CH7
*\*\          - DMA2_CH8
*\*\param  Cmd:(The input parameters must be the following values)
*\*\            - ENABLE
*\*\            - DISABLE 
*\*\return  none.
**/
void DMA_RequestRemap(uint32_t DMA_Remap, DMA_ChannelType* DMAChx, FunctionalState Cmd)
{
    
    if (Cmd != DISABLE)
    {
        /* Calculate the used DMAy */
        /* Set the selected DMAy remap request */
        DMAChx->CHSEL = DMA_Remap;
    }
    else
    {
        /* Clear DMAy remap */
        DMAChx->CHSEL = 0;
    }
    
}
