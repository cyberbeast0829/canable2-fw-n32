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
*\*\file n32h47x_48x_spi.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/
#include "n32h47x_48x_spi.h"
#include "n32h47x_48x_rcc.h"

/* SPI Driving Functions Declaration */

/* SPI_Private_Defines  */

/* SPI SPE mask */
#define CTRL2_SPIEN_ENABLE  ((uint16_t)0x0001U)
#define CTRL2_SPIEN_DISABLE ((uint16_t)0xFFFEU)

/* I2S I2SE mask */
#define I2SCFG_I2SEN_ENABLE  ((uint16_t)0x0001U)
#define I2SCFG_I2SEN_DISABLE ((uint16_t)0xFFFEU)

/* SPI CRCNext mask */
#define CTRL1_CRCNEXT_ENABLE ((uint16_t)0x0200U)

/* SPI CRCEN mask */
#define CTRL2_CRCEN_ENABLE  ((uint16_t)0x0008U)
#define CTRL2_CRCEN_DISABLE ((uint16_t)0xFFF7U)

/* SPI SSOE mask */
#define CTRL1_SSOEN_ENABLE  ((uint16_t)0x0400U)
#define CTRL1_SSOEN_DISABLE ((uint16_t)0xFBFFU)

/* SPI registers Masks */
#define CTRL1_CLR_MASK  			((uint16_t)0xF9F7U)
#define I2SCFG_CLR_MASK 			((uint16_t)0x05FCU)
#define I2SPR_CLEAR_Mask      ((uint16_t)0x0FFFU)

/* SPI or I2S mode selection masks */
#define SPI_MODE_ENABLE ((uint16_t)0xFFFDU)
#define I2S_MODE_ENABLE ((uint16_t)0x0002U)

/**
*\*\name    SPI_I2S_DeInit.
*\*\fun     Deinitializes the SPIx peripheral registers to their default reset values (Affects also the I2Ss)
*\*\param   SPIx :
*\*\				 - 1, 2, 3, 4, 5 or 6 
*\*\return  none
**/
void SPI_I2S_DeInit(const SPI_Module* SPIx)
{

    if (SPIx == SPI1)
    {
        /* Enable SPI1 reset state */
        RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_SPI1);
    }
    else if (SPIx == SPI2)
    {
        /* Enable SPI2 reset state */
        RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_SPI2);
    }
		 else if(SPIx == SPI3)
    {
				/* Enable SPI3 reset state */
				RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_SPI3);
    }    
    else if (SPIx == SPI4)
    {
        /* Enable SPI4 reset state */
        RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_SPI4);
    }   
    else if (SPIx == SPI5)
    {
        /* Enable SPI5 reset state */
        RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_SPI5);
    }
    else if (SPIx == SPI6)
    {
        /* Enable SPI6 reset state */
        RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_SPI6);
    }else{}    
}


/**
*\*\name    SPI_Init.
*\*\fun     Initializes the SPIx peripheral according to the specified parameters in the SPI_InitStruct.
*\*\param   SPIx :
*\*\				 - 1, 2, 3, 4, 5 or 6 
*\*\param   SPI_InitStruct :
*\*\          - DataDirection
*\*\            - SPI_DIR_DOUBLELINE_FULLDUPLEX
*\*\            - SPI_DIR_DOUBLELINE_RONLY     
*\*\            - SPI_DIR_SINGLELINE_RX        
*\*\            - SPI_DIR_SINGLELINE_TX 
*\*\          - SpiMode
*\*\            - SPI_MODE_MASTER
*\*\            - SPI_MODE_SLAVE
*\*\          - DataLen
*\*\            - SPI_DATA_SIZE_16BITS
*\*\            - SPI_DATA_SIZE_8BITS
*\*\          - CLKPOL
*\*\            - SPI_CLKPOL_LOW 
*\*\            - SPI_CLKPOL_HIGH
*\*\          - CLKPHA
*\*\            - SPI_CLKPHA_FIRST_EDGE 
*\*\            - SPI_CLKPHA_SECOND_EDGE
*\*\          - NSS
*\*\            - SPI_NSS_SOFT
*\*\            - SPI_NSS_HARD
*\*\          - BaudRatePres
*\*\            - SPI_BR_PRESCALER_2  
*\*\            - SPI_BR_PRESCALER_4  
*\*\            - SPI_BR_PRESCALER_8  
*\*\            - SPI_BR_PRESCALER_16 
*\*\            - SPI_BR_PRESCALER_32 
*\*\            - SPI_BR_PRESCALER_64 
*\*\            - SPI_BR_PRESCALER_128
*\*\            - SPI_BR_PRESCALER_256
*\*\          - FirstBit
*\*\            - SPI_FB_MSB
*\*\            - SPI_FB_LSB
*\*\          - CRCPoly					default 0x0007, max 0xffff 
*\*\return  none
**/
void SPI_Init(SPI_Module* SPIx,const SPI_InitType* SPI_InitStruct)
{
    uint16_t tmpregister;

    /*---------------------------- SPIx CTRL1 Configuration ------------------------*/
    /* Get the SPIx CTRL1 value */
    tmpregister = SPIx->CTRL1;
    /* Clear BIDIMode, BIDIOE, RxONLY, SSM, SSI, LSBFirst, BR, MSTR, CPOL and CPHA bits */
    tmpregister &= CTRL1_CLR_MASK;
    /* Configure SPIx: direction, NSS management, first transmitted bit, BaudRate prescaler
       master/salve mode, CPOL and CPHA */
    /* Set BIDImode, BIDIOE and RxONLY bits according to DataDirection value */
    /* Set SSM, SSI and MSTR bits according to SpiMode and NSS values */
    /* Set LSBFirst bit according to FirstBit value */
    /* Set BR bits according to BaudRatePres value */
    /* Set CPOL bit according to CLKPOL value */
    /* Set CPHA bit according to CLKPHA value */
    tmpregister |= (uint16_t)((uint32_t)SPI_InitStruct->DataDirection | SPI_InitStruct->SpiMode
                              | SPI_InitStruct->DataLen | SPI_InitStruct->CLKPOL | SPI_InitStruct->CLKPHA
                              | SPI_InitStruct->NSS | SPI_InitStruct->BaudRatePres | SPI_InitStruct->FirstBit);
    /* Write to SPIx CTRL1 */
    SPIx->CTRL1 = tmpregister;

    /* Activate the SPI mode (Reset I2SMOD bit in SPI_I2S_CFGR register) */
    SPIx->SPI_I2S_CFGR &= SPI_MODE_ENABLE;

    /*---------------------------- SPIx CRCPOLY Configuration --------------------*/
    /* Write to SPIx CRCPOLY */
    SPIx->CRCPOLY = SPI_InitStruct->CRCPoly;
}



/**
*\*\name    I2S_Init.
*\*\fun     Initializes the SPIx peripheral according to the specified parameters in the I2S_InitStruct.
*\*\param   SPIx :
*\*\          - SPI2
*\*\          - SPI3
*\*\param   I2S_InitStruct :
*\*\          - I2sMode
*\*\           - I2S_MODE_SlAVE_TX 
*\*\           - I2S_MODE_SlAVE_RX 
*\*\           - I2S_MODE_MASTER_TX
*\*\           - I2S_MODE_MASTER_RX
*\*\          - Standard
*\*\           - I2S_STD_PHILLIPS      
*\*\           - I2S_STD_MSB_ALIGN     
*\*\           - I2S_STD_LSB_ALIGN     
*\*\           - I2S_STD_PCM_SHORTFRAME
*\*\           - I2S_STD_PCM_LONGFRAME 
*\*\          - DataFormat
*\*\           - I2S_DATA_FMT_16BITS          
*\*\           - I2S_DATA_FMT_16BITS_EXTENDED 
*\*\           - I2S_DATA_FMT_24BITS          
*\*\           - I2S_DATA_FMT_32BITS          
*\*\          - MCLKEnable
*\*\           - I2S_MCLK_ENABLE 
*\*\           - I2S_MCLK_DISABLE
*\*\          - AudioFrequency
*\*\           - I2S_AUDIO_FREQ_192K   
*\*\           - I2S_AUDIO_FREQ_96K    
*\*\           - I2S_AUDIO_FREQ_48K    
*\*\           - I2S_AUDIO_FREQ_44K    
*\*\           - I2S_AUDIO_FREQ_32K    
*\*\           - I2S_AUDIO_FREQ_22K    
*\*\           - I2S_AUDIO_FREQ_16K    
*\*\           - I2S_AUDIO_FREQ_11K    
*\*\           - I2S_AUDIO_FREQ_8K     
*\*\           - I2S_AUDIO_FREQ_DEFAULT
*\*\          - CLKPOL
*\*\           - I2S_CLKPOL_LOW 
*\*\           - I2S_CLKPOL_HIGH
*\*\          - ClkSrcFrequency
*\*\           - RCC_Clocks.SysclkFreq
*\*\           - RCC_Clocks.HclkFreq
*\*\           - RCC_Clocks.Pclk1Freq
*\*\           - RCC_Clocks.Pclk2Freq
*\*\           - RCC_Clocks.AdcPllClkFreq
*\*\           - RCC_Clocks.AdcHclkFreq
*\*\           - RCC_Clocks.ShrtpllFreq
*\*\           - user defined
**/
void I2S_Init(SPI_Module* SPIx,const I2S_InitType* I2S_InitStruct)
{
    uint16_t tmpregister, i2sdiv, i2sodd, packetlength;
    uint32_t tmp;
    uint32_t sourceclock;

    /*----------------------- SPIx SPI_I2S_CFGR & I2SPREDIV Configuration -----------------*/
    /* Clear I2SMOD, I2SE, MODCFG, PCMSYNC, STDSEL, CLKPOL, TDATLEN and CHLEN bits */
    SPIx->SPI_I2S_CFGR &= I2SCFG_CLR_MASK;
    SPIx->I2SPREDIV = 0x0002;

    /* Get the SPI_I2S_CFGR register value */
    tmpregister = SPIx->SPI_I2S_CFGR;

    /* If the default value has to be written, reinitialize i2sdiv and i2sodd*/
    if (I2S_InitStruct->AudioFrequency == I2S_AUDIO_FREQ_DEFAULT)
    {
        i2sodd = (uint16_t)0;
        i2sdiv = (uint16_t)2;
    }
    /* If the requested audio frequency is not the default, compute the prescaler */
    else
    {
        /* Check the frame length (For the Prescaler computing) */
        if (I2S_InitStruct->DataFormat == I2S_DATA_FMT_16BITS)
        {
            /* Packet length is 16 bits */
            packetlength = 1;
        }
        else
        {
            /* Packet length is 32 bits */
            packetlength = 2;
        }

        /* I2S Clock source is System clock: Get System Clock frequency */
        //RCC_GetClocksFreqValue(&RCC_Clocks);

        /* Get the source clock value: based on System Clock value */
			  sourceclock = I2S_InitStruct->ClkSrcFrequency;
				
        /* Compute the Real divider depending on the MCLK output state with a floating point */
        if (I2S_InitStruct->MCLKEnable == I2S_MCLK_ENABLE)
        {
            /* MCLK output is enabled */
            tmp = (uint16_t)(((((sourceclock / 256) * 10) / I2S_InitStruct->AudioFrequency)) + 5);
        }
        else
        {
            /* MCLK output is disabled */
            tmp = (uint16_t)(((((sourceclock / (32 * packetlength)) * 10) / I2S_InitStruct->AudioFrequency)) + 5);
        }

        /* Remove the floating point */
        tmp = tmp / 10;

        /* Check the parity of the divider */
        i2sodd = (uint16_t)(tmp & (uint16_t)0x0001);

        /* Compute the i2sdiv prescaler */
        i2sdiv = (uint16_t)((tmp - i2sodd) / 2);

        /* Get the Mask for the Odd bit (SPI_I2SPREDIV[10]) register */
        i2sodd = (uint16_t)(i2sodd << 10);
    }

    /* Test if the divider is 1 or 0 or greater than 0xFF */
    if ((i2sdiv < 2) || (i2sdiv > 0x3FF))
    {
        /* Set the default values */
        i2sdiv = 2;
        i2sodd = 0;
    }

    /* Write to SPIx I2SPREDIV register the computed value */
    SPIx->I2SPREDIV = (uint16_t)(i2sdiv | (uint16_t)(i2sodd | (uint16_t)I2S_InitStruct->MCLKEnable));

    /* Configure the I2S with the SPI_InitStruct values */
    tmpregister |= (uint16_t)(
        I2S_MODE_ENABLE
        | (uint16_t)(I2S_InitStruct->I2sMode
                     | (uint16_t)(I2S_InitStruct->Standard
                                  | (uint16_t)(I2S_InitStruct->DataFormat | (uint16_t)I2S_InitStruct->CLKPOL))));

    /* Write to SPIx SPI_I2S_CFGR */
    SPIx->SPI_I2S_CFGR = tmpregister;
}

/**
*\*\name    SPI_InitStruct.
*\*\fun     Fills each SPI_InitStruct member with its default value.
*\*\param   SPI_InitStruct :
*\*\          - DataDirection
*\*\          - SpiMode
*\*\          - DataLen
*\*\          - CLKPOL
*\*\          - CLKPHA
*\*\          - NSS      
*\*\          - BaudRatePres     
*\*\          - FirstBit      
*\*\          - CRCPoly
*\*\return  none
**/
void SPI_InitStruct(SPI_InitType* SPI_InitStruct)
{
    /*--------------- Reset SPI init structure parameters values -----------------*/
    /* Initialize the DataDirection member */
    SPI_InitStruct->DataDirection = SPI_DIR_DOUBLELINE_FULLDUPLEX;
    /* initialize the SpiMode member */
    SPI_InitStruct->SpiMode = SPI_MODE_SLAVE;
    /* initialize the DataLen member */
    SPI_InitStruct->DataLen = SPI_DATA_SIZE_8BITS;
    /* Initialize the CLKPOL member */
    SPI_InitStruct->CLKPOL = SPI_CLKPOL_LOW;
    /* Initialize the CLKPHA member */
    SPI_InitStruct->CLKPHA = SPI_CLKPHA_FIRST_EDGE;
    /* Initialize the NSS member */
    SPI_InitStruct->NSS = SPI_NSS_HARD;
    /* Initialize the BaudRatePres member */
    SPI_InitStruct->BaudRatePres = SPI_BR_PRESCALER_2;
    /* Initialize the FirstBit member */
    SPI_InitStruct->FirstBit = SPI_FB_MSB;
    /* Initialize the CRCPoly member */
    SPI_InitStruct->CRCPoly = 7;
}

/**
*\*\name    I2S_InitStruct.
*\*\fun     Fills each I2S_InitStruct member with its default value.
*\*\param   I2S_InitStruct :
*\*\          - I2sMode
*\*\          - Standard
*\*\          - DataFormat
*\*\          - MCLKEnable
*\*\          - AudioFrequency
*\*\          - CLKPOL      
*\*\return  none
**/
void I2S_InitStruct(I2S_InitType* I2S_InitStruct)
{
    /*--------------- Reset I2S init structure parameters values -----------------*/
    /* Initialize the I2sMode member */
    I2S_InitStruct->I2sMode = I2S_MODE_SlAVE_TX;

    /* Initialize the Standard member */
    I2S_InitStruct->Standard = I2S_STD_PHILLIPS;

    /* Initialize the DataFormat member */
    I2S_InitStruct->DataFormat = I2S_DATA_FMT_16BITS;

    /* Initialize the MCLKEnable member */
    I2S_InitStruct->MCLKEnable = I2S_MCLK_DISABLE;

    /* Initialize the AudioFrequency member */
    I2S_InitStruct->AudioFrequency = I2S_AUDIO_FREQ_DEFAULT;

    /* Initialize the CLKPOL member */
    I2S_InitStruct->CLKPOL = I2S_CLKPOL_LOW;
}


/**
*\*\name    SPI_Enable.
*\*\fun     Enables or disables the specified SPI peripheral.
*\*\param   SPIx :
*\*\				 - 1, 2, 3, 4, 5 or 6 
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void SPI_Enable(SPI_Module* SPIx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected SPI peripheral */
        SPIx->CTRL2 |= CTRL2_SPIEN_ENABLE;
    }
    else
    {
        /* Disable the selected SPI peripheral */
        SPIx->CTRL2 &= CTRL2_SPIEN_DISABLE;
    }
}

/**
*\*\name    I2S_Enable.
*\*\fun     Enables or disables the specified SPI peripheral (in I2S mode).
*\*\param   SPIx :
*\*\          - SPI2
*\*\          - SPI3
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void I2S_Enable(SPI_Module* SPIx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected SPI peripheral (in I2S mode) */
        SPIx->SPI_I2S_CFGR |= I2SCFG_I2SEN_ENABLE;
    }
    else
    {
        /* Disable the selected SPI peripheral (in I2S mode) */
        SPIx->SPI_I2S_CFGR &= I2SCFG_I2SEN_DISABLE;
    }
}



/**
*\*\name    SPI_I2S_EnableInt.
*\*\fun     Enables or disables the specified SPI/I2S interrupts.
*\*\param   SPIx :
*\*\				 - 1, 2, 3, 4, 5 or 6 in SPI mode
*\*\				 - 2 or 3 in I2S mode
*\*\param   SPI_I2S_IT :
*\*\         - SPI_I2S_INT_TE           
*\*\         - SPI_I2S_INT_RNE           
*\*\      	 - SPI_I2S_INT_ERR          
*\*\      	 - SPI_I2S_INT_RXONLYC       
*\*\      	 - SPI_I2S_INT_RXFIFOF      
*\*\      	 - SPI_I2S_INT_RXFIFOHF   
*\*\      	 - SPI_I2S_INT_TXFIFOHE
*\*\param   Cmd :
*\*\         - ENABLE
*\*\         - DISABLE
*\*\return  none
**/
void SPI_I2S_EnableInt(SPI_Module* SPIx, uint8_t SPI_I2S_IT, FunctionalState Cmd)
{
    uint16_t itpos,itmask;

    /* Get the SPI/I2S IT index */
    itpos = SPI_I2S_IT >> 4;

    /* Set the IT mask */
    itmask = (uint16_t)1 << (uint16_t)itpos;

    if (Cmd != DISABLE)
    {
        /* Enable the selected SPI/I2S interrupt */
        SPIx->CTRL2 |= itmask;
    }
    else
    {
        /* Disable the selected SPI/I2S interrupt */
        SPIx->CTRL2 &= (uint16_t)~itmask;
    }
}


/**
*\*\name    SPI_I2S_EnableDma.
*\*\fun     Enables or disables the SPIx/I2Sx DMA interface.
*\*\param   SPIx :
*\*\				 - 1, 2, 3, 4, 5 or 6 in SPI mode
*\*\				 - 2 or 3 in I2S mode
*\*\param   SPI_I2S_DMAReq :
*\*\         - SPI_I2S_DMA_TX           
*\*\         - SPI_I2S_DMA_RX            
*\*\param   Cmd :
*\*\         - ENABLE
*\*\         - DISABLE
*\*\return  none
**/
void SPI_I2S_EnableDma(SPI_Module* SPIx, uint16_t SPI_I2S_DMAReq, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected SPI/I2S DMA requests */
        SPIx->CTRL2 |= SPI_I2S_DMAReq;
    }
    else
    {
        /* Disable the selected SPI/I2S DMA requests */
        SPIx->CTRL2 &= (uint16_t)~SPI_I2S_DMAReq;
    }
}


/**
*\*\name    SPI_I2S_TransmitData.
*\*\fun     Transmits a Data through the SPIx/I2Sx peripheral.
*\*\param   SPIx :
*\*\				 - 1, 2, 3, 4, 5 or 6 in SPI mode
*\*\				 - 2 or 3 in I2S mode            
*\*\param   Data 			\* Data to be transmitted *\
*\*\return  none
**/
void SPI_I2S_TransmitData(SPI_Module* SPIx, uint16_t Data)
{
    /* Write in the DAT register the data to be sent */
    SPIx->DAT = Data;
}


/**
*\*\name    SPI_I2S_ReceiveData.
*\*\fun     Returns the most recent received data by the SPIx/I2Sx peripheral.
*\*\param   SPIx :
*\*\				 - 1, 2, 3, 4, 5 or 6 in SPI mode
*\*\				 - 2 or 3 in I2S mode            
*\*\return  The data in the SPI_DAT register.
**/
uint16_t SPI_I2S_ReceiveData(const SPI_Module* SPIx)
{
    /* Return the data in the DAT register */
    return SPIx->DAT;
}


/**
*\*\name    SPI_SetNssLevel.
*\*\fun     Configures internally by software the NSS pin for the selected SPI.
*\*\param   SPIx :
*\*\				 - 1, 2, 3, 4, 5 or 6  
*\*\param   SPI_NSSInternalSoft :
*\*\				 - SPI_NSS_HIGH 
*\*\				 - SPI_NSS_LOW 
*\*\return  none
**/
void SPI_SetNssLevel(SPI_Module* SPIx, uint16_t SPI_NSSInternalSoft)
{
    if (SPI_NSSInternalSoft != SPI_NSS_LOW)
    {
        /* Set NSS pin internally by software */
        SPIx->CTRL1 |= SPI_NSS_HIGH;
    }
    else
    {
        /* Reset NSS pin internally by software */
        SPIx->CTRL1 &= SPI_NSS_LOW;
    }
}


/**
*\*\name    SPI_SSOutputEnable.
*\*\fun     Enables or disables the SS output for the selected SPI.
*\*\param   SPIx :
*\*\				 - 1, 2, 3, 4, 5 or 6  
*\*\param   Cmd :
*\*\				 - ENABLE 
*\*\				 - DISABLE 
*\*\return  none
**/
void SPI_SSOutputEnable(SPI_Module* SPIx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected SPI SS output */
        SPIx->CTRL1 |= CTRL1_SSOEN_ENABLE;
    }
    else
    {
        /* Disable the selected SPI SS output */
        SPIx->CTRL1 &= CTRL1_SSOEN_DISABLE;
    }
}

/**
*\*\name    SPI_ConfigDataLen.
*\*\fun     Configures the data size for the selected SPI.
*\*\param   SPIx :
*\*\				 - 1, 2, 3, 4, 5 or 6  
*\*\param   DataLen :
*\*\				 - SPI_DATA_SIZE_16BITS 
*\*\				 - SPI_DATA_SIZE_8BITS 
*\*\return  none
**/
void SPI_ConfigDataLen(SPI_Module* SPIx, uint16_t DataLen)
{
    /* Clear DFF bit */
    SPIx->CTRL1 &= (uint16_t)~SPI_DATA_SIZE_16BITS;
    /* Set new DFF bit value */
    SPIx->CTRL1 |= DataLen;
}


/**
*\*\name    SPI_TransmitCrcNext.
*\*\fun     Transmit the SPIx CRC value.
*\*\param   SPIx :
*\*\				 - 1, 2, 3, 4, 5 or 6 
*\*\param   Cmd :
*\*\				 - ENABLE 
*\*\				 - DISABLE 
*\*\return  none
**/
void SPI_TransmitCrcNext(SPI_Module* SPIx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected SPI CRC transmission */
				SPIx->CTRL1 |= CTRL1_CRCNEXT_ENABLE;
    }
    else
    {
        /* Disable the selected SPI CRC transmission */
        SPIx->CTRL1 &= (~CTRL1_CRCNEXT_ENABLE);
    }
}


/**
*\*\name    SPI_EnableCalculateCrc.
*\*\fun     Enables or disables the CRC value calculation of the transferred bytes.
*\*\param   SPIx :
*\*\				 - 1, 2, 3, 4, 5 or 6  
*\*\param   Cmd :
*\*\				 - ENABLE 
*\*\				 - DISABLE 
*\*\return  none
**/
void SPI_EnableCalculateCrc(SPI_Module* SPIx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected SPI CRC calculation */
        SPIx->CTRL2 |= CTRL2_CRCEN_ENABLE;
    }
    else
    {
        /* Disable the selected SPI CRC calculation */
        SPIx->CTRL2 &= CTRL2_CRCEN_DISABLE;
    }
}

/**
*\*\name    SPI_GetCRCDat.
*\*\fun     Returns the transmit or the receive CRC register value for the specified SPI.
*\*\param   SPIx :
*\*\				 - 1, 2, 3, 4, 5 or 6  
*\*\param   Cmd :
*\*\				 - SPI_CRC_TX 
*\*\				 - SPI_CRC_RX 
*\*\return  Tx/Rx CRC register value.
**/
uint16_t SPI_GetCRCDat(const SPI_Module* SPIx, uint8_t SPI_CRC)
{
    uint16_t crcreg;

    if (SPI_CRC != SPI_CRC_RX)
    {
        /* Get the Tx CRC register */
        crcreg = SPIx->CRCTDAT;
    }
    else
    {
        /* Get the Rx CRC register */
        crcreg = SPIx->CRCRDAT;
    }
    /* Return the selected CRC register */
    return crcreg;
}

/**
*\*\name    SPI_GetCRCPoly.
*\*\fun     Returns the CRC Polynomial register value for the specified SPI.
*\*\param   SPIx :
*\*\				 - 1, 2, 3, 4, 5 or 6   
*\*\return  The CRC Polynomial register value.
**/
uint16_t SPI_GetCRCPoly(const SPI_Module* SPIx)
{
    /* Return the CRC polynomial register */
    return SPIx->CRCPOLY;
}

/**
*\*\name    SPI_ConfigBidirectionalMode.
*\*\fun     Selects the data transfer direction in bi-directional mode for the specified SPI.
*\*\param   SPIx :
*\*\				 - 1, 2, 3, 4, 5 or 6  
*\*\param   DataDirection :
*\*\				 - SPI_BIDIRECTION_TX
*\*\				 - SPI_BIDIRECTION_RX
*\*\return  none.
**/
void SPI_ConfigBidirectionalMode(SPI_Module* SPIx, uint16_t DataDirection)
{
    if (DataDirection == SPI_BIDIRECTION_TX)
    {
        /* Set the Tx only mode */
        SPIx->CTRL1 |= SPI_BIDIRECTION_TX;
    }
    else
    {
        /* Set the Rx only mode */
        SPIx->CTRL1 &= SPI_BIDIRECTION_RX;
    }
}

/**
*\*\name    SPI_I2S_GetStatus.
*\*\fun     Checks whether the specified SPI/I2S flag is set or not.
*\*\param   SPIx :
*\*\				 - 1, 2, 3, 4, 5 or 6 in SPI mode
*\*\				 - 2 or 3 in I2S mode 
*\*\param   SPI_I2S_FLAG :
*\*\				 - SPI_I2S_BUSY_FLAG
*\*\				 - SPI_I2S_OVER_FLAG
*\*\				 - SPI_MODERR_FLAG
*\*\				 - SPI_CRCERR_FLAG
*\*\				 - I2S_UNDER_FLAG
*\*\				 - I2S_CHSIDE_FLAG
*\*\				 - SPI_I2S_TE_FLAG
*\*\				 - SPI_I2S_RNE_FLAG
*\*\				 - SPI_I2S_RXONLYC_FLAG
*\*\				 - SPI_I2S_RXFIFOF_FLAG
*\*\				 - SPI_I2S_TXFIFOE_FLAG
*\*\				 - SPI_I2S_RXFIFOHF_FLAG
*\*\				 - SPI_I2S_TXFIFOHE_FLAG
*\*\return  The new state of SPI_I2S_FLAG (SET or RESET).
**/
FlagStatus SPI_I2S_GetStatus(const SPI_Module* SPIx, uint16_t SPI_I2S_FLAG)
{
    FlagStatus bitstatus;

    /* Check the status of the specified SPI/I2S flag */
    if ((SPIx->STS & SPI_I2S_FLAG) != (uint16_t)RESET)
    {
        /* SPI_I2S_FLAG is set */
        bitstatus = SET;
    }
    else
    {
        /* SPI_I2S_FLAG is reset */
        bitstatus = RESET;
    }
    /* Return the SPI_I2S_FLAG status */
    return bitstatus;
}

/**
*\*\name    SPI_I2S_ClrCRCErrFlag.
*\*\fun     Clears the SPIx CRC Error (CRCERR) flag.
*\*\param   SPIx :
*\*\				 - 1, 2, 3, 4, 5 or 6 
*\*\param   SPI_I2S_FLAG :
*\*\				 - SPI_CRCERR_FLAG
*\*\return  none.
**/
void SPI_I2S_ClrCRCErrFlag(SPI_Module* SPIx, uint16_t SPI_I2S_FLAG)
{
    /* Clear the selected SPI CRC Error (CRCERR) flag */
    SPIx->STS = (uint16_t)~SPI_I2S_FLAG;
}

/**
*\*\name    SPI_I2S_GetIntStatus.
*\*\fun     Checks whether the specified SPI/I2S interrupt has occurred or not.
*\*\param   SPIx :
*\*\				 - 1, 2, 3, 4, 5 or 6 in SPI mode
*\*\				 - 2 or 3 in I2S mode 
*\*\param   SPI_I2S_IT :         
*\*\         - SPI_I2S_INT_TE 
*\*\         - SPI_I2S_INT_RNE
*\*\         - SPI_I2S_INT_RXONLYC
*\*\         - SPI_I2S_INT_RXFIFOF
*\*\         - SPI_I2S_INT_RXFIFOHF
*\*\         - SPI_I2S_INT_TXFIFOHE
*\*\         - SPI_I2S_INT_CRCERR
*\*\         - SPI_I2S_INT_MODERR
*\*\         - SPI_I2S_INT_OVERERR
*\*\         - I2S_I2S_INT_UNDER
*\*\return  The new state of SPI_I2S_IT (SET or RESET).
**/

INTStatus SPI_I2S_GetIntStatus(const SPI_Module* SPIx, uint8_t SPI_I2S_IT)
{
    INTStatus bitstatus = RESET;
    uint16_t itpos = 0, itmask = 0 , enablestatus = 0;

    /* Get the SPI/I2S IT index */
    itpos = 0x01 << (SPI_I2S_IT & 0x0F);

    /* Get the SPI/I2S IT mask */
    itmask = SPI_I2S_IT >> 4;

    /* Set the IT mask */
    itmask = 0x01 << itmask;

    /* Get the SPI_I2S_IT enable bit status */
    enablestatus = (SPIx->CTRL2 & itmask);

    /* Check the status of the specified SPI/I2S interrupt */
    if (((SPIx->STS & itpos) != (uint16_t)RESET) && enablestatus)
    {
        /* SPI_I2S_IT is set */
        bitstatus = SET;
    }
    else
    {
        /* SPI_I2S_IT is reset */
        bitstatus = RESET;
    }
    /* Return the SPI_I2S_IT status */
    return bitstatus;
}

/**
*\*\name    SPI_I2S_ClrITPendingBit.
*\*\fun     Clears the SPIx CRC Error (CRCERR) interrupt pending bit.
*\*\param   SPIx :
*\*\				 - 1, 2, 3, 4, 5 or 6 in SPI mode
*\*\				 - 2 or 3 in I2S mode 
*\*\param   SPI_I2S_IT :
*\*\				 - SPI_INT_CRCERR
*\*\return  none.
**/
void SPI_I2S_ClrITPendingBit(SPI_Module* SPIx, uint8_t SPI_I2S_IT)
{
    uint16_t itpos;

    /* Get the SPI IT index */
    itpos = 0x0001 << (SPI_I2S_IT & 0x0F);

    /* Clear the selected SPI CRC Error (CRCERR) interrupt pending bit */
    SPIx->STS = (uint16_t)~itpos;
}

/**
*\*\name    SPI_I2S_FIFO_Cmd.
*\*\fun     Enables or disables the FIFO (in SPI/I2S mode).
*\*\param   SPIx :
*\*\				 - 1, 2, 3, 4, 5 or 6 in SPI mode
*\*\				 - 2 or 3 in I2S mode  
*\*\param   Cmd :
*\*\				 - ENABLE 
*\*\				 - DISABLE 
*\*\return  none.
**/
void SPI_I2S_FIFO_Cmd(SPI_Module* SPIx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the FIFO (in SPI/I2S mode) */
        SPIx->CTRL2 |= SPI_I2S_FIFO_Enable;
    }
    else
    {
        /* Disable the FIFO (in SPI/I2S mode) */
        SPIx->CTRL2 &= SPI_I2S_FIFO_Disable;
    }
}

/**
*\*\name    SPI_I2S_ClearFIFOBit.
*\*\fun     Clears the SPIx FIFO bit.
*\*\param   SPIx :
*\*\				 - 1, 2, 3, 4, 5 or 6 in SPI mode
*\*\				 - 2 or 3 in I2S mode   
*\*\param   SPI_I2S_FIFO_Clear :
*\*\				 - SPI_I2S_FIFO_CLR 
*\*\return  none.
**/
void SPI_I2S_ClearFIFOBit(SPI_Module* SPIx, uint16_t SPI_I2S_FIFO_Clear)
{
    /* Clear the FIFO bit */
    SPIx->CTRL2 |= SPI_I2S_FIFO_Clear;
    SPIx->CTRL2 &= ~SPI_I2S_FIFO_Clear;
}

/**
*\*\name    SPI_RxFIFOSizeConfig.
*\*\fun     Configures the Rx FIFO size for the selected SPI.
*\*\param   SPIx :
*\*\				 - 1, 2, 3, 4, 5 or 6 in SPI mode
*\*\				 - 2 or 3 in I2S mode   
*\*\param   SPI_FIFOSize :
*\*\				 - SPI_RX_FIF0NUM_7 
*\*\				 - SPI_RX_FIF0NUM_6
*\*\				 - SPI_RX_FIF0NUM_5
*\*\				 - SPI_RX_FIF0NUM_4
*\*\				 - SPI_RX_FIF0NUM_3
*\*\				 - SPI_RX_FIF0NUM_2
*\*\				 - SPI_RX_FIF0NUM_1
*\*\				 - SPI_RX_FIF0NUM_0
*\*\return  none.
**/
void SPI_RxFIFOSizeConfig(SPI_Module* SPIx, uint16_t SPI_FIFOSize)
{
    /* Clear DFF bit */
    SPIx->FIFONUM &= (uint16_t)~SPI_RX_FIF0NUM_7;
    /* Set new DFF bit value */
    SPIx->FIFONUM |= SPI_FIFOSize;
}

/**
*\*\name    SPI_TxFIFOSizeConfig.
*\*\fun     Configures the Tx FIFO size for the selected SPI.
*\*\param   SPIx :
*\*\				 - 1, 2, 3, 4, 5 or 6 in SPI mode
*\*\				 - 2 or 3 in I2S mode   
*\*\param   SPI_FIFOSize :
*\*\				 - SPI_TX_FIF0NUM_7 
*\*\				 - SPI_TX_FIF0NUM_6
*\*\				 - SPI_TX_FIF0NUM_5
*\*\				 - SPI_TX_FIF0NUM_4
*\*\				 - SPI_TX_FIF0NUM_3
*\*\				 - SPI_TX_FIF0NUM_2
*\*\				 - SPI_TX_FIF0NUM_1
*\*\				 - SPI_TX_FIF0NUM_0
*\*\return  none.
**/
void SPI_TxFIFOSizeConfig(SPI_Module* SPIx, uint16_t SPI_FIFOSize)
{
    /* Clear DFF bit */
    SPIx->FIFONUM &= (uint16_t)~SPI_TX_FIF0NUM_7;
    /* Set new DFF bit value */
    SPIx->FIFONUM |= SPI_FIFOSize;
}


/**
*\*\name    SPI_RX_FIFO_SET.
*\*\fun     In FIFIO mode, write the data in the receiving FIFO.
*\*\param   SPIx :
*\*\				 - 1, 2, 3, 4, 5 or 6 in SPI mode
*\*\				 - 2 or 3 in I2S mode   
*\*\param   Data 								\* Data to be transmitted *\
*\*\return  none.
**/
void SPI_RX_FIFO_SET(SPI_Module* SPIx, uint16_t Data)
{
    /* Write in the RX_FIFO register the data to be sent */
    SPIx->RX_FIFO = Data;
}

/**
*\*\name    SPI_RX_FIFO_GET.
*\*\fun     In FIFIO mode, read the data in the receiving FIFO.
*\*\param   SPIx :
*\*\				 - 1, 2, 3, 4, 5 or 6 in SPI mode
*\*\				 - 2 or 3 in I2S mode   
*\*\return  Receive data in FIFO.
**/
uint16_t SPI_RX_FIFO_GET(const SPI_Module* SPIx)
{
    /* Return the data in the receive FIFO */
    return SPIx->RX_FIFO;
}

/**
*\*\name    SPI_RX_FIFO_CNT_GET.
*\*\fun     In FIFO mode, the current number of valid FIFOs.
*\*\param   SPIx :
*\*\				 - 1, 2, 3, 4, 5 or 6 in SPI mode
*\*\				 - 2 or 3 in I2S mode   
*\*\return  Current effective number of FIFOs.
**/
uint16_t SPI_RX_FIFO_CNT_GET(const SPI_Module* SPIx)
{
    /* Return The RX  Data Count in FIFO*/
    return ((uint8_t)((SPIx->FIFOCNT & 0x00F0U) >> 4));
}

/**
*\*\name    SPI_TX_FIFO_CNT_GET.
*\*\fun     In FIFO mode, the current number of valid FIFOs.
*\*\param   SPIx :
*\*\				 - 1, 2, 3, 4, 5 or 6 in SPI mode
*\*\				 - 2 or 3 in I2S mode   
*\*\return  Current effective number of FIFOs.
**/
uint16_t SPI_TX_FIFO_CNT_GET(const SPI_Module* SPIx)
{
    /* Return the TX  Data Count in FIFO*/
    return  ((uint8_t)(SPIx->FIFOCNT & 0x000FU));
}

/**
*\*\name    SPI_TRANSNUM_SET.
*\*\fun     When in FIFO mode with CRC function, 
*\*\				the user needs to write the number of data to be transmitted in advance.
*\*\param   SPIx :
*\*\				 - 1, 2, 3, 4, 5 or 6 in SPI mode
*\*\				 - 2 or 3 in I2S mode   
*\*\param   Data 								\* Data to be transmitted *\
*\*\return  none.
**/
void SPI_TRANSNUM_SET(SPI_Module* SPIx, uint16_t Data)
{
    /* Write in the TRANSNUM register the data to be sent */
    SPIx->TRANSNUM = Data;
}

/**
*\*\name    SPI_TRANSNUM_GET.
*\*\fun     When in FIFO mode with CRC function, 
*\*\				the user write the number of data to be transmitted in advance.
*\*\param   SPIx :
*\*\				 - 1, 2, 3, 4, 5 or 6 in SPI mode
*\*\				 - 2 or 3 in I2S mode  
*\*\return  The number of data transferred.
**/
uint16_t SPI_TRANSNUM_GET(const SPI_Module* SPIx)
{
    /* Return the number of data transferred. */
		return  SPIx->TRANSNUM;
}

/**
*\*\name    SPI_DELAYTIME_SET.
*\*\fun     SPI master clock delay time configuration.
*\*\param   SPIx :
*\*\				 - 1, 2, 3, 4, 5 or 6 in SPI mode
*\*\param   Data 								\* Data to be transmitted *\
*\*\return  none.
**/
void SPI_DELAYTIME_SET(SPI_Module* SPIx, uint16_t Data)
{
    /* Write in the CR3 register the data to be sent */
    SPIx->CR3 = Data;
}

/**
*\*\name    SPI_DELAYTIME_GET.
*\*\fun     Get SPI master clock delay time.
*\*\param   SPIx :
*\*\				 - 1, 2, 3, 4, 5 or 6 in SPI mode
*\*\return  The clock delay time.
**/
uint16_t SPI_DELAYTIME_GET(const SPI_Module* SPIx)
{
    /* Return clock delay time. */
		return  SPIx->CR3;
}




/* I2S_EXT  */
/**
*\*\name    I2S_EXT_Init.
*\*\fun     Initializes the I2Sx_EXT peripheral according to the specified parameters in the I2S_EXT_InitStruct.
*\*\param   I2Sx_EXT :
*\*\          - I2S2_EXT
*\*\          - I2S3_EXT
*\*\param   I2S_InitStruct:
*\*\          - I2sMode
*\*\           - I2S_MODE_SlAVE_TX 
*\*\           - I2S_MODE_SlAVE_RX 
*\*\           - I2S_MODE_MASTER_TX
*\*\           - I2S_MODE_MASTER_RX
*\*\          - Standard
*\*\           - I2S_STD_PHILLIPS      
*\*\           - I2S_STD_MSB_ALIGN     
*\*\           - I2S_STD_LSB_ALIGN     
*\*\           - I2S_STD_PCM_SHORTFRAME
*\*\           - I2S_STD_PCM_LONGFRAME  
*\*\          - DataFormat
*\*\           - I2S_DATA_FMT_16BITS          
*\*\           - I2S_DATA_FMT_16BITS_EXTENDED 
*\*\           - I2S_DATA_FMT_24BITS          
*\*\           - I2S_DATA_FMT_32BITS          
*\*\          - CLKPOL
*\*\           - I2S_CLKPOL_LOW 
*\*\           - I2S_CLKPOL_HIGH
*\*\return  none
**/
void I2S_EXT_Init(I2S_EXT_Module* I2Sx_EXT,const I2S_InitType* I2S_EXT_InitStruct)
{
	uint16_t tmpregister;
    RCC_ClocksType RCC_Clocks;

    /*----------------------- I2Sx_EXT I2S_CFGR Configuration -----------------*/
    /* Clear I2SMOD, I2SE, MODCFG, PCMSYNC, STDSEL, CLKPOL, TDATLEN and CHLEN bits */
    I2Sx_EXT->I2S_CFGR &= I2SCFG_CLR_MASK;

    /* Get the SPI_I2S_CFGR register value */
    tmpregister = I2Sx_EXT->I2S_CFGR;



		/* I2S Clock source is System clock: Get System Clock frequency */
		RCC_GetClocksFreqValue(&RCC_Clocks);



    /* Configure the I2S with the SPI_InitStruct values */
    tmpregister |= (uint16_t)(
        I2S_MODE_ENABLE
        | (uint16_t)(I2S_EXT_InitStruct->I2sMode
                     | (uint16_t)(I2S_EXT_InitStruct->Standard
                                  | (uint16_t)(I2S_EXT_InitStruct->DataFormat | (uint16_t)I2S_EXT_InitStruct->CLKPOL))));

    /* Write to I2Sx_EXT SPI_I2S_CFGR */
    I2Sx_EXT->I2S_CFGR = tmpregister;
}


/**
*\*\name    I2S_EXT_InitStruct.
*\*\fun     Fills each I2S_EXT_InitStruct member with its default value.
*\*\param   I2S_EXT_InitStruct :
*\*\          - I2sMode
*\*\          - Standard
*\*\          - DataFormat
*\*\          - CLKPOL      
*\*\return  none
**/
void I2S_EXT_InitStruct(I2S_InitType* I2S_EXT_InitStruct)
{
    /*--------------- Reset I2S init structure parameters values -----------------*/
    /* Initialize the I2sMode member */
    I2S_EXT_InitStruct->I2sMode = I2S_MODE_SlAVE_TX;

    /* Initialize the Standard member */
    I2S_EXT_InitStruct->Standard = I2S_STD_PHILLIPS;

    /* Initialize the DataFormat member */
    I2S_EXT_InitStruct->DataFormat = I2S_DATA_FMT_16BITS;

    /* Initialize the CLKPOL member */
    I2S_EXT_InitStruct->CLKPOL = I2S_CLKPOL_LOW;
}



/**
*\*\name    I2S_EXT_Enable.
*\*\fun     Enables or disables the specified I2S EXT peripheral.
*\*\param   I2Sx_EXT :
*\*\          - I2S2_EXT
*\*\          - I2S3_EXT
*\*\param   Cmd :
*\*\          - ENABLE
*\*\          - DISABLE
*\*\return  none
**/
void I2S_EXT_Enable(I2S_EXT_Module* I2Sx_EXT, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected I2S_EXT peripheral */
        I2Sx_EXT->I2S_CFGR |= I2SCFG_I2SEN_ENABLE;
    }
    else
    {
        /* Disable the selected I2S_EXT peripheral */
        I2Sx_EXT->I2S_CFGR &= I2SCFG_I2SEN_DISABLE;
    }
}

/**
*\*\name    I2S_EXT_TransmitData.
*\*\fun     Transmits a Data through the I2Sx_EXT peripheral.
*\*\param   I2Sx :
*\*\				 - I2S2_EXT
*\*\				 - I2S3_EXT
*\*\param   Data 			\* Data to be transmitted *\
*\*\return  none
**/
void I2S_EXT_TransmitData(I2S_EXT_Module* I2Sx, uint16_t Data)
{
    /* Write in the DAT register the data to be sent */
    I2Sx->I2S_DAT = Data;
}


/**
*\*\name    I2S_EXT_ReceiveData.
*\*\fun     Returns the most recent received data by the I2Sx_EXT peripheral.
*\*\param   I2Sx :
*\*\				 - I2S2_EXT
*\*\				 - I2S3_EXT          
*\*\return  The data in the I2S_DAT register.
**/
uint16_t I2S_EXT_ReceiveData(const I2S_EXT_Module* I2Sx)
{
    /* Return the data in the DAT register */
    return I2Sx->I2S_DAT;
}


/**
*\*\name    I2S_EXT_EnableDma.
*\*\fun     Enables or disables the I2Sx DMA interface.
*\*\param   I2Sx :
*\*\				 - I2S2_EXT
*\*\				 - I2S3_EXT
*\*\param   I2S_EXT_DMAReq :
*\*\         - I2S_EXT_DMA_TX           
*\*\         - I2S_EXT_DMA_RX            
*\*\param   Cmd :
*\*\         - ENABLE
*\*\         - DISABLE
*\*\return  none
**/
void I2S_EXT_EnableDma(I2S_EXT_Module* I2Sx, uint16_t I2S_EXT_DMAReq, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected I2S_EXT DMA requests */
        I2Sx->I2S_CTRL2 |= I2S_EXT_DMAReq;
    }
    else
    {
        /* Disable the selected I2S_EXT DMA requests */
        I2Sx->I2S_CTRL2 &= (uint16_t)~I2S_EXT_DMAReq;
    }
}

/**
*\*\name    I2S_EXT_EnableInt.
*\*\fun     Enables or disables the specified I2S_EXT interrupts.
*\*\param   I2Sx :
*\*\				 - I2S2_EXT
*\*\				 - I2S3_EXT
*\*\param   I2S_EXT_IT : 
*\*\      	 - I2S_EXT_INT_TEINTEN        
*\*\      	 - I2S_EXT_INT_RNEINTEN      
*\*\      	 - I2S_EXT_INT_ERRINTEN  
*\*\param   Cmd :
*\*\         - ENABLE
*\*\         - DISABLE
*\*\return  none
**/
void I2S_EXT_EnableInt(I2S_EXT_Module* I2Sx, uint8_t I2S_EXT_IT, FunctionalState Cmd)
{
    uint16_t itmask;

    /* Set the IT mask */
    itmask = I2S_EXT_IT;

    if (Cmd != DISABLE)
    {
        /* Enable the selected I2S interrupt */
        I2Sx->I2S_CTRL2 |= itmask;
    }
    else
    {
        /* Disable the selected I2S interrupt */
        I2Sx->I2S_CTRL2 &= (uint16_t)~itmask;
    }
}

/**
*\*\name    I2S_EXT_GetStatus.
*\*\fun     Checks whether the specified I2S_EXT flag is set or not.
*\*\param   I2Sx :
*\*\				 - I2S2_EXT
*\*\				 - I2S3_EXT
*\*\param   I2S_EXT_FLAG :
*\*\				 - I2S_EXT_BUSY_FLAG
*\*\				 - I2S_EXT_OVER_FLAG
*\*\				 - I2S_EXT_UNDER_FLAG
*\*\				 - I2S_EXT_CHSIDE_FLAG
*\*\				 - I2S_EXT_TE_FLAG
*\*\				 - I2S_EXT_RNE_FLAG
*\*\return  The new state of I2S_EXT_FLAG (SET or RESET).
**/
FlagStatus I2S_EXT_GetStatus(const I2S_EXT_Module* I2Sx, uint16_t I2S_EXT_FLAG)
{
    FlagStatus bitstatus;

    /* Check the status of the specified I2S_EXT flag */
    if ((I2Sx->I2S_STS & I2S_EXT_FLAG) != (uint16_t)RESET)
    {
        /* I2S_EXT_FLAG is set */
        bitstatus = SET;
    }
    else
    {
        /* I2S_EXT_FLAG is reset */
        bitstatus = RESET;
    }
    /* Return the I2S_EXT_FLAG status */
    return bitstatus;
}

/**
*\*\name    I2S_EXT_GetIntStatus.
*\*\fun     Checks whether the specified I2S_EXT interrupt has occurred or not.
*\*\param   I2Sx :
*\*\				 - I2S2_EXT
*\*\				 - I2S3_EXT
*\*\param   I2S_EXT_IT :
*\*\      	 - I2S_EXT_TE_FLAG        
*\*\      	 - I2S_EXT_RNE_FLAG      
*\*\      	 - I2S_EXT_BUSY_FLAG  
*\*\      	 - I2S_EXT_OVER_FLAG
*\*\      	 - I2S_EXT_UNDER_FLAG
*\*\      	 - I2S_EXT_CHSIDE_FLAG
*\*\return  The new state of I2S_EXT_IT (SET or RESET).
**/

INTStatus I2S_EXT_GetIntStatus(const I2S_EXT_Module* I2Sx, uint8_t I2S_EXT_IT)
{
    INTStatus bitstatus ;
    uint32_t tmpregister;

    /* Get I2Sx I2S_STS register value */
    tmpregister = I2Sx->I2S_STS;

    /* Check the status of the specified I2Sx interrupt */
    if ((tmpregister & I2S_EXT_IT) != (uint32_t)RESET)
    {
        /* I2S_EXT_IT is set */
        bitstatus = SET;
    }
    else
    {
        /* I2S_EXT_IT is reset */
        bitstatus = RESET;
    }
    /* Return the I2S_EXT_IT status */
    return  bitstatus;
		
}





