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
*\*\file n32h47x_48x_i2c.c
*\*\author Nations 
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/
#include "n32h47x_48x_i2c.h"
#include "n32h47x_48x_rcc.h"

/** I2C Driving Functions Declaration **/


/**
*\*\name    I2C_DeInit.
*\*\fun     Deinitializes the I2Cx peripheral registers to their default reset values.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\return  none
**/
void I2C_DeInit(const I2C_Module* I2Cx)
{
    if (I2Cx == I2C1)
    {
        /* Enable I2C1 reset state */
        RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_I2C1);
    }
    else if (I2Cx == I2C2)
    {
        /* Enable I2C2 reset state */
        RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_I2C2);
    }
    else if (I2Cx == I2C3)
    {
        /* Enable I2C3 reset state */
        RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_I2C3);
    }
    else if (I2Cx == I2C4)
    {
        /* Enable I2C4 reset state */
        RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_I2C4);
    }else{}

}


/**
*\*\name    I2C_Init.
*\*\fun     Initializes the I2Cx peripheral according to the specified parameters in the I2C_InitStruct.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   I2C_InitStruct :
*\*\          - ClkSpeed(common speed:100000(100KHz) - 400000(400KHz) - 1000000(1MHz)):
*\*\            - between 1 to 1000000 
*\*\          - BusMode:
*\*\            - I2C_BUSMODE_I2C
*\*\            - I2C_BUSMODE_SMBDEVICE
*\*\            - I2C_BUSMODE_SMBHOST
*\*\          - FmDutyCycle: 
*\*\            - I2C_FMDUTYCYCLE_16_9
*\*\            - I2C_FMDUTYCYCLE_2
*\*\          - OwnAddr1:
*\*\            - between 0 to 0x3FF 
*\*\          - AckEnable:
*\*\            - I2C_ACKEN
*\*\            - I2C_ACKDIS
*\*\          - AddrMode:
*\*\            - I2C_ADDR_MODE_7BIT
*\*\            - I2C_ADDR_MODE_10BIT
*\*\return  none
**/
void I2C_Init(I2C_Module* I2Cx,const I2C_InitType* I2C_InitStruct)
{
    uint32_t tmpregister, freqrange;
    uint16_t result;
    uint32_t pclk;
    RCC_ClocksType rcc_clocks;

    /*---------------------------- I2Cx CTRL2 Configuration ------------------------*/
    /* Get the I2Cx CTRL2 value */
    tmpregister = I2Cx->CTRL2;
    /* Clear frequency FREQ[7:0] bits */
    tmpregister &= CTRL2_CLKFREQ_RESET;
    /* Get APB1/2 frequency value */
    RCC_GetClocksFreqValue(&rcc_clocks);
    
		pclk = rcc_clocks.Pclk1Freq;

    /* Set frequency bits depending on pclk1 value */
    freqrange = (uint16_t)(pclk / 1000000);

    /* Write to I2Cx CTRL2 */
    tmpregister |= freqrange;
    I2Cx->CTRL2 = tmpregister;

    /*---------------------------- I2Cx CHCFG Configuration ------------------------*/
    /* Disable the selected I2C peripheral to configure TMRISE */
#ifndef		I2C_FILTER_TEST   
	 I2Cx->CTRL1 &= CTRL1_SPEN_RESET;
#endif
    /* Reset tmpregister value */
    /* Clear F/S, DUTY and CHCFG[11:0] bits */
    tmpregister = 0;

    /* Configure speed in standard mode */
    if (I2C_InitStruct->ClkSpeed <= 100000)
    {
        /* Standard mode speed calculate */
        result = (uint16_t)(pclk / (I2C_InitStruct->ClkSpeed << 1));
        /* Test if CHCFG value is under 0x4*/
        if (result < 0x04)
        {
            /* Set minimum allowed value */
            result = 0x04;
        }
        /* Set speed value for standard mode */
        tmpregister |= result;
				
#ifndef		I2C_FILTER_TEST
        /* Set Maximum Rise Time for standard mode */
        I2Cx->TMRISE = freqrange + 1;
#else
	      I2Cx->TMRISE = (I2Cx->TMRISE & 0xFFFFFFC0) |((freqrange + 1)&(0x3F));			
#endif
    }
    /* Configure speed in fast mode */
    /* Configure speed in fast mode */
    else if (( I2C_InitStruct->ClkSpeed > 100000 ) && ( I2C_InitStruct->ClkSpeed <= 400000 ) )/*(I2C_InitStruct->ClkSpeed <= 400000)*/
    {
        if ( I2C_InitStruct->FmDutyCycle == I2C_FMDUTYCYCLE_2 )
        {
            /* Fast mode speed calculate: Tlow/Thigh = 2 */
            result = ( uint16_t )( pclk / ( I2C_InitStruct->ClkSpeed * 3 ) );
        }
        else /*I2C_InitStruct->FmDutyCycle == I2C_DutyCycle_16_9*/
        {
            /* Fast mode speed calculate: Tlow/Thigh = 16/9 */
            result = ( uint16_t )( pclk / ( I2C_InitStruct->ClkSpeed * 25 ) );
            /* Set DUTY bit */
            result |= I2C_FMDUTYCYCLE_16_9;
        }

        /* Test if CCR value is under 0x1*/
        if (( result & CLKCTRL_CLKCTRL_SET ) == 0 )
        {
            /* Set minimum allowed value */
            result |= ( uint16_t )0x0001;
        }

        /* Set speed value and set F/S bit for fast mode */
        tmpregister |= ( uint16_t )( result | CLKCTRL_FSMODE_SET );

        /* Set Maximum Rise Time for fast mode */
#ifndef		I2C_FILTER_TEST				
        I2Cx->TMRISE = ( uint16_t )((( freqrange * ( uint16_t )300 ) / ( uint16_t )1000 ) + ( uint16_t )1 );
#else
	      I2Cx->TMRISE = (I2Cx->TMRISE & 0xFFFFFFC0) |(((( freqrange * ( uint16_t )300 ) / ( uint16_t )1000 ) + ( uint16_t )1 )&(0x3F));			
#endif				
    }
    else
    {
        /* Standard mode speed calculate */
        result = ( uint16_t )( pclk / ( I2C_InitStruct->ClkSpeed << 1 ) );
        /* Test if CCR value is under 0x4*/

        if ( result < 0x04 )
        {
            /* Set minimum allowed value */
            result = 0x04;
        }

        /* Set speed value for standard mode */
        tmpregister |= result;

        /* Set Maximum Rise Time for fast-plus mode */
#ifndef		I2C_FILTER_TEST					
        I2Cx->TMRISE = ( uint16_t )((( freqrange * ( uint16_t )300 ) / ( uint16_t )1000 ) + ( uint16_t )1 );
#else
	      I2Cx->TMRISE = (I2Cx->TMRISE & 0xFFFFFFC0) |(((( freqrange * ( uint16_t )300 ) / ( uint16_t )1000 ) + ( uint16_t )1 )&(0x3F));			
#endif				
    }
    /* Write to I2Cx CHCFG */
    I2Cx->CLKCTRL = tmpregister;
    /* Enable the selected I2C peripheral */
    I2Cx->CTRL1 |= CTRL1_SPEN_SET;

    /*---------------------------- I2Cx CTRL1 Configuration ------------------------*/
    /* Get the I2Cx CTRL1 value */
    tmpregister = I2Cx->CTRL1;
    /* Clear ACK, SMBTYPE and  SMMODE bits */
    tmpregister &= I2C_CTRL1_CLR_MASK;
    /* Configure I2Cx: mode and acknowledgement */
    /* Set SMBTYPE and SMMODE bits according to BusMode value */
    /* Set ACK bit according to AckEnable value */
    tmpregister |= (uint16_t)((uint32_t)I2C_InitStruct->BusMode | I2C_InitStruct->AckEnable);
    /* Write to I2Cx CTRL1 */
    I2Cx->CTRL1 = tmpregister;

    /*---------------------------- I2Cx OADDR1 Configuration -----------------------*/
    /* Set I2Cx Own Address1 and acknowledged address */
    I2Cx->OADDR1 = (I2C_InitStruct->AddrMode | I2C_InitStruct->OwnAddr1);
}


/**
*\*\name    I2C_InitStruct.
*\*\fun     Fills each I2C_InitStruct member with its default value.
*\*\param   I2C_InitStruct :
*\*\          - ClkSpeed
*\*\          - BusMode
*\*\          - FmDutyCycle
*\*\          - OwnAddr1
*\*\          - AckEnable
*\*\          - AddrMode
*\*\return  none
**/
void I2C_InitStruct(I2C_InitType* I2C_InitStruct)
{
    /*---------------- Reset I2C init structure parameters values ----------------*/
    /* initialize the ClkSpeed member */
    I2C_InitStruct->ClkSpeed = 5000;
    /* Initialize the BusMode member */
    I2C_InitStruct->BusMode = I2C_BUSMODE_I2C;
    /* Initialize the FmDutyCycle member */
    I2C_InitStruct->FmDutyCycle = I2C_FMDUTYCYCLE_2;
    /* Initialize the OwnAddr1 member */
    I2C_InitStruct->OwnAddr1 = 0;
    /* Initialize the AckEnable member */
    I2C_InitStruct->AckEnable = I2C_ACKDIS;
    /* Initialize the AddrMode member */
    I2C_InitStruct->AddrMode = I2C_ADDR_MODE_7BIT;
}


/**
*\*\name    I2C_Enable.
*\*\fun     Enables or disables the specified I2C peripheral.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   Cmd :
*\*\          - ENABLE 
*\*\          - DISABLE
*\*\return  none
**/
void I2C_Enable(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected I2C peripheral */
        I2Cx->CTRL1 |= CTRL1_SPEN_SET;
    }
    else
    {
        /* Disable the selected I2C peripheral */
        I2Cx->CTRL1 &= CTRL1_SPEN_RESET;
    }
}

/**
*\*\name    I2C_EnableDMA.
*\*\fun     Enables or disables the specified I2C DMA requests.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   Cmd :
*\*\          - ENABLE 
*\*\          - DISABLE
*\*\return  none
**/
void I2C_EnableDMA(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected I2C DMA requests */
        I2Cx->CTRL2 |= CTRL2_DMAEN_SET;
    }
    else
    {
        /* Disable the selected I2C DMA requests */
        I2Cx->CTRL2 &= CTRL2_DMAEN_RESET;
    }
}


/**
*\*\name    I2C_EnableDmaLastSend.
*\*\fun     Specifies if the next DMA transfer will be the last one.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   Cmd :
*\*\          - ENABLE 
*\*\          - DISABLE
*\*\return  none
**/
void I2C_EnableDmaLastSend(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Next DMA transfer is the last transfer */
        I2Cx->CTRL2 |= CTRL2_DMALAST_SET;
    }
    else
    {
        /* Next DMA transfer is not the last transfer */
        I2Cx->CTRL2 &= CTRL2_DMALAST_RESET;
    }
}


/**
*\*\name    I2C_GenerateStart.
*\*\fun     Generates I2Cx communication START condition.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   Cmd :
*\*\          - ENABLE 
*\*\          - DISABLE
*\*\return  none
**/
void I2C_GenerateStart(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Generate a START condition */
        I2Cx->CTRL1 |= CTRL1_START_SET;
    }
    else
    {
        /* Disable the START condition generation */
        I2Cx->CTRL1 &= CTRL1_START_RESET;
    }
}

/**
*\*\name    I2C_GenerateStop.
*\*\fun     Generates I2Cx communication STOP condition.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   Cmd :
*\*\          - ENABLE 
*\*\          - DISABLE
*\*\return  none
**/
void I2C_GenerateStop(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Generate a STOP condition */
        I2Cx->CTRL1 |= CTRL1_STOP_SET;
    }
    else
    {
        /* Disable the STOP condition generation */
        I2Cx->CTRL1 &= CTRL1_STOP_RESET;
    }
}


/**
*\*\name    I2C_ConfigAck.
*\*\fun     Enables or disables the specified I2C acknowledge feature.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   Cmd :
*\*\          - ENABLE 
*\*\          - DISABLE
*\*\return  none
**/
void I2C_ConfigAck(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the acknowledgement */
        I2Cx->CTRL1 |= CTRL1_ACK_SET;
    }
    else
    {
        /* Disable the acknowledgement */
        I2Cx->CTRL1 &= CTRL1_ACK_RESET;
    }
}


/**
*\*\name    I2C_ConfigOwnAddr2.
*\*\fun     Configures the specified I2C own address2.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   Address
*\*\          - 7bit I2C own address2
*\*\return  none
**/
void I2C_ConfigOwnAddr2(I2C_Module* I2Cx, uint8_t Address)
{
    uint32_t tmpregister;

    /* Get the old register value */
    tmpregister = I2Cx->OADDR2;

    /* Reset I2Cx Own address2 bit [7:1] */
    tmpregister &= OADDR2_ADDR2_RESET;

    /* Set I2Cx Own address2 */
    tmpregister |= (uint16_t)((uint16_t)Address & (uint16_t)0x00FE);

    /* Store the new register value */
    I2Cx->OADDR2 = tmpregister;
}


/**
*\*\name    I2C_EnableDualAddr.
*\*\fun     Enables or disables the specified I2C dual addressing mode.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   Cmd :
*\*\          - ENABLE 
*\*\          - DISABLE
*\*\return  none
**/
void I2C_EnableDualAddr(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable dual addressing mode */
        I2Cx->OADDR2 |= OADDR2_DUALEN_SET;
    }
    else
    {
        /* Disable dual addressing mode */
        I2Cx->OADDR2 &= OADDR2_DUALEN_RESET;
    }
}


/**
*\*\name    I2C_EnableGeneralCall.
*\*\fun     Enables or disables the specified I2C general call feature.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   Cmd :
*\*\          - ENABLE 
*\*\          - DISABLE
*\*\return  none
**/
void I2C_EnableGeneralCall(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable generall call */
        I2Cx->CTRL1 |= CTRL1_GCEN_SET;
    }
    else
    {
        /* Disable generall call */
        I2Cx->CTRL1 &= CTRL1_GCEN_RESET;
    }
}


/**
*\*\name    I2C_SendData.
*\*\fun     Sends a data byte through the I2Cx peripheral.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   Data
*\*\return  none
**/
void I2C_SendData(I2C_Module* I2Cx, uint8_t Data)
{
    /* Write in the DAT register the data to be sent */
    I2Cx->DAT = Data;
}

/**
*\*\name    I2C_RecvData.
*\*\fun     Returns the most recent received data by the I2Cx peripheral.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\return  The value of the received data
**/
uint8_t I2C_RecvData(const I2C_Module* I2Cx)
{
    /* Return the data in the DAT register */
    return (uint8_t)I2Cx->DAT;
}


/**
*\*\name    I2C_SendAddr7bit.
*\*\fun     Transmits the address byte to select the slave device.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   Address
*\*\param   I2C_Direction :
*\*\          - I2C_DIRECTION_SEND Transmitter mode
*\*\          - I2C_DIRECTION_RECV Receiver mode
*\*\return  none
**/
void I2C_SendAddr7bit(I2C_Module* I2Cx, uint8_t Address, uint8_t I2C_Direction)
{
    /* Test on the direction to set/reset the read/write bit */
    if (I2C_Direction != I2C_DIRECTION_SEND)
    {
        /* Set the address bit0 for read */
        Address |= OADDR1_ADDR0_SET;
    }
    else
    {
        /* Reset the address bit0 for write */
        Address &= OADDR1_ADDR0_RESET;
    }
    /* Send the address */
    I2Cx->DAT = Address;
}


/**
*\*\name    I2C_GetRegister.
*\*\fun     Reads the specified I2C register and returns its value.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   I2C_Register :
*\*\          - I2C_REG_CTRL1 CTRL1 register
*\*\          - I2C_REG_CTRL2 CTRL2 register
*\*\          - I2C_REG_OADDR1 OADDR1 register
*\*\          - I2C_REG_OADDR2 OADDR2 register
*\*\          - I2C_REG_DAT DAT register
*\*\          - I2C_REG_STS1 STS1 register
*\*\          - I2C_REG_STS2 STS2 register
*\*\          - I2C_REG_CLKCTRL CLKCTRL register
*\*\          - I2C_REG_TMRISE TMRISE register
*\*\          - I2C_REG_BYTENUM   
*\*\          - I2C_REG_GFLTRCTRL
*\*\return  none
**/
uint16_t I2C_GetRegister(const I2C_Module* I2Cx, uint8_t I2C_Register)
{
    __IO uint32_t tmp;

    tmp = (uint32_t)I2Cx;
    tmp += I2C_Register;

    /* Return the selected register value */
    return (*(__IO uint32_t*)tmp);
}


/**
*\*\name    I2C_EnableSoftwareReset.
*\*\fun     Enables or disables the specified I2C software reset.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   Cmd :
*\*\          - ENABLE 
*\*\          - DISABLE
*\*\return  none
**/
void I2C_EnableSoftwareReset(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Peripheral under reset */
        I2Cx->CTRL1 |= CTRL1_SWRESET_SET;
    }
    else
    {
        /* Peripheral not under reset */
        I2Cx->CTRL1 &= CTRL1_SWRESET_RESET;
    }
}


/**
*\*\name    I2C_ConfigNackLocation.
*\*\fun     Selects the specified I2C NACK position in master receiver mode.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   I2C_NACKPosition :
*\*\          - I2C_NACK_POS_NEXT 
*\*\          - I2C_NACK_POS_CURRENT
*\*\return  none
**/
void I2C_ConfigNackLocation(I2C_Module* I2Cx, uint16_t I2C_NACKPosition)
{
    /* Check the input parameter */
    if (I2C_NACKPosition == I2C_NACK_POS_NEXT)
    {
        /* Next byte in shift register is the last received byte */
        I2Cx->CTRL1 |= I2C_NACK_POS_NEXT;
    }
    else
    {
        /* Current byte in shift register is the last received byte */
        I2Cx->CTRL1 &= I2C_NACK_POS_CURRENT;
    }
}


/**
*\*\name    I2C_ConfigSmbusAlert.
*\*\fun     Drives the SMBusAlert pin high or low for the specified I2C.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   I2C_SMBusAlert :
*\*\          - I2C_SMBALERT_LOW 
*\*\          - I2C_SMBALERT_HIGH
*\*\return  none
**/
void I2C_ConfigSmbusAlert(I2C_Module* I2Cx, uint16_t I2C_SMBusAlert)
{
    if (I2C_SMBusAlert == I2C_SMBALERT_LOW)
    {
        /* Drive the SMBusAlert pin Low */
        I2Cx->CTRL1 |= I2C_SMBALERT_LOW;
    }
    else
    {
        /* Drive the SMBusAlert pin High  */
        I2Cx->CTRL1 &= I2C_SMBALERT_HIGH;
    }
}


/**
*\*\name    I2C_SendPEC.
*\*\fun    	Enables or disables the specified I2C PEC transfer.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   Cmd :
*\*\          - ENABLE 
*\*\          - DISABLE
*\*\return  none
**/
void I2C_SendPEC(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected I2C PEC transmission */
        I2Cx->CTRL1 |= CTRL1_PEC_SET;
    }
    else
    {
        /* Disable the selected I2C PEC transmission */
        I2Cx->CTRL1 &= CTRL1_PEC_RESET;
    }
}


/**
*\*\name    I2C_ConfigPecLocation.
*\*\fun    	Selects the specified I2C PEC position.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   I2C_PECPosition :
*\*\          - I2C_PEC_POS_NEXT 
*\*\          - I2C_PEC_POS_CURRENT
*\*\return  none
**/
void I2C_ConfigPecLocation(I2C_Module* I2Cx, uint16_t I2C_PECPosition)
{
    if (I2C_PECPosition == I2C_PEC_POS_NEXT)
    {
        /* Next byte in shift register is PEC */
        I2Cx->CTRL1 |= I2C_PEC_POS_NEXT;
    }
    else
    {
        /* Current byte in shift register is PEC */
        I2Cx->CTRL1 &= I2C_PEC_POS_CURRENT;
    }
}


/**
*\*\name    I2C_ComputePec.
*\*\fun    	Enables or disables the PEC value calculation of the transferred bytes.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   Cmd :
*\*\          - ENABLE 
*\*\          - DISABLE
*\*\return  none
**/
void I2C_ComputePec(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected I2C PEC calculation */
        I2Cx->CTRL1 |= CTRL1_PECEN_SET;
    }
    else
    {
        /* Disable the selected I2C PEC calculation */
        I2Cx->CTRL1 &= CTRL1_PECEN_RESET;
    }
}


/**
*\*\name    I2C_GetPec.
*\*\fun    	Enables or disables the PEC value calculation of the transferred bytes.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\return  none
**/
uint8_t I2C_GetPec(const I2C_Module* I2Cx)
{
    /* Return the selected I2C PEC value */
    return (uint8_t)((I2Cx->STS2) >> 8);
}


/**
*\*\name    I2C_EnableArp.
*\*\fun    	Enables or disables the specified I2C ARP.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   Cmd :
*\*\          - ENABLE 
*\*\          - DISABLE
*\*\return  none
**/
void I2C_EnableArp(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected I2C ARP */
        I2Cx->CTRL1 |= CTRL1_ARPEN_SET;
    }
    else
    {
        /* Disable the selected I2C ARP */
        I2Cx->CTRL1 &= CTRL1_ARPEN_RESET;
    }
}


/**
*\*\name    I2C_EnableExtendClk.
*\*\fun    	Enables or disables the specified I2C Clock stretching.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   Cmd :
*\*\          - ENABLE 
*\*\          - DISABLE
*\*\return  none
**/
void I2C_EnableExtendClk(I2C_Module* I2Cx, FunctionalState Cmd)
{
    if (Cmd == DISABLE)
    {
        /* Enable the selected I2C Clock stretching */
        I2Cx->CTRL1 |= CTRL1_NOEXTEND_SET;
    }
    else
    {
        /* Disable the selected I2C Clock stretching */
        I2Cx->CTRL1 &= CTRL1_NOEXTEND_RESET;
    }
}


/**
*\*\name    I2C_ConfigFastModeDutyCycle.
*\*\fun    	Selects the specified I2C fast mode duty cycle.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   FmDutyCycle :
*\*\          - I2C_FMDUTYCYCLE_16_9 
*\*\          - I2C_FMDUTYCYCLE_2
*\*\return  none
**/
void I2C_ConfigFastModeDutyCycle(I2C_Module* I2Cx, uint16_t FmDutyCycle)
{
    if (FmDutyCycle != I2C_FMDUTYCYCLE_16_9)
    {
        /* I2C fast mode Tlow/Thigh=2 */
        I2Cx->CLKCTRL &= I2C_FMDUTYCYCLE_2;
    }
    else
    {
        /* I2C fast mode Tlow/Thigh=16/9 */
        I2Cx->CLKCTRL |= I2C_FMDUTYCYCLE_16_9;
    }
}

/**
*\*\name    I2C_ClrFIFO.
*\*\fun    	Clear the I2C's FIFO.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\return  none
**/
void I2C_ClrFIFO(I2C_Module* I2Cx)
{
		I2Cx->CTRL1 |= CTRL1_FIFOCLR_SET;
		I2Cx->CTRL1 &= CTRL1_FIFOCLR_RESET;
}

/**
*\*\name    I2C_EnableFIFO.
*\*\fun    	Enables or disables the FIFO.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   Cmd :
*\*\          - ENABLE 
*\*\          - DISABLE
*\*\return  none
**/
void I2C_EnableFIFO(I2C_Module* I2Cx, FunctionalState Cmd)
{

	if( Cmd == DISABLE)
	{
		I2Cx->CTRL1 &= ~CTRL1_FIFOEN_RESET;
	}
	else
	{
		I2Cx->CTRL1 |= CTRL1_FIFOEN_SET;
	}
}
/**
*\*\name    I2C_EnableDMAFIFO.
*\*\fun    	Enables or disables the DMA FIFO.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   Cmd :
*\*\          - ENABLE 
*\*\          - DISABLE
*\*\return  none
**/
void I2C_EnableDMAFIFO(I2C_Module* I2Cx, FunctionalState Cmd)
{
	if( Cmd == DISABLE)
	{
		I2Cx->CTRL2 &= ~CTRL2_DMAFIFOEN_RESET;
	}
	else
	{
		I2Cx->CTRL2 |= CTRL2_DMAFIFOEN_SET;
	}
}

/**
*\*\name    I2C_SetTxFifoThreshold.
*\*\fun    	Sets the Tx FIFO threshold of I2C.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   TxFifoThreshold: Tx FIFO threshold of I2C.
*\*\return  none
**/
void I2C_SetTxFifoThreshold( I2C_Module* I2Cx, uint8_t TxFifoThreshold )
{

    /* Clear the I2C Tx FIFO threshold */
    I2Cx->CTRL1 &= CTRL1_TXFT_Mask;
    /* Set the I2C Tx FIFO threshold */
    I2Cx->CTRL1 |= TxFifoThreshold << 24;
}

/**
*\*\name    I2C_SetRxFifoThreshold.
*\*\fun    	Sets the Rx FIFO threshold of I2C.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   RxFifoThreshold: Rx FIFO threshold of I2C.
*\*\return  none
**/
void I2C_SetRxFifoThreshold( I2C_Module* I2Cx, uint8_t RxFifoThreshold )
{

    /* Clear the I2C Rx FIFO threshold */
    I2Cx->CTRL1 &= CTRL1_RXFT_Mask;
    /* Set the I2C Rx FIFO threshold */
    I2Cx->CTRL1 |= RxFifoThreshold << 20;
}

/**
*\*\name    I2C_CheckEvent.
*\*\fun    	Checks whether the last I2Cx Event is equal to the one passed as parameter.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   I2C_EVENT :
*\*\          - I2C_EVT_SLAVE_SEND_ADDR_MATCHED           							: EV1
*\*\          - I2C_EVT_SLAVE_RECV_ADDR_MATCHED              						: EV1
*\*\          - I2C_EVT_SLAVE_SEND_ADDR2_MATCHED     										: EV1
*\*\          - I2C_EVT_SLAVE_RECV_ADDR2_MATCHED        								: EV1
*\*\          - I2C_EVT_SLAVE_GCALLADDR_MATCHED            							: EV1
*\*\          - I2C_EVT_SLAVE_DATA_RECVD                         				: EV2
*\*\          - (I2C_EVT_SLAVE_DATA_RECVD | I2C_FLAG_DUALFLAG)      		: EV2
*\*\          - (I2C_EVT_SLAVE_DATA_RECVD | I2C_FLAG_GCALLADDR)    			: EV2
*\*\          - I2C_EVENT_SLAVE_BYTE_TRANSMITTED                      	: EV3
*\*\          - (I2C_EVENT_SLAVE_BYTE_TRANSMITTED | I2C_FLAG_DUALFLAG)  : EV3
*\*\          - (I2C_EVENT_SLAVE_BYTE_TRANSMITTED | I2C_FLAG_GCALLADDR) : EV3
*\*\          - I2C_EVT_SLAVE_ACK_MISS                           				: EV3_2
*\*\          - I2C_EVT_SLAVE_STOP_RECVD                         				: EV4
*\*\          - I2C_EVT_MASTER_MODE_FLAG                          			: EV5
*\*\          - I2C_EVT_MASTER_TXMODE_FLAG            									: EV6
*\*\          - I2C_EVT_MASTER_RXMODE_FLAG               								: EV6
*\*\          - I2C_EVT_MASTER_DATA_RECVD_FLAG                        	: EV7
*\*\          - I2C_EVT_MASTER_DATA_SENDING                    					: EV8
*\*\          - I2C_EVT_MASTER_DATA_SENDED                     					: EV8_2
*\*\          - I2C_EVT_MASTER_MODE_ADDRESS10_FLAG                      : EV9
*\*\note    For detailed description of Events, please refer to section
*\*\        I2C_Events in n32h47x_48x_i2c.h file.
*\*\return  SUCCESS or ERROR
**/
ErrorStatus I2C_CheckEvent(const I2C_Module* I2Cx, uint32_t I2C_EVENT)
{
    uint32_t lastevent;
    uint32_t flag1, flag2 ;
    ErrorStatus status;

    /* Read the I2Cx status register */
    flag1 = I2Cx->STS1;
    flag2 = I2Cx->STS2;
    flag2 = flag2 << 16;

    /* Get the last event value from I2C status register */
    lastevent = ((uint16_t)flag1 | flag2) & FLAG_MASK;

    /* Check whether the last event contains the I2C_EVENT */
    if ((lastevent & I2C_EVENT) == I2C_EVENT)
    {
        /* SUCCESS: last event is equal to I2C_EVENT */
        status = SUCCESS;
    }
    else
    {
        /* ERROR: last event is different from I2C_EVENT */
        status = ERROR;
    }
    /* Return status */
    return status;
}

/**
*\*\name    I2C_GetLastEvent.
*\*\fun     Returns the last I2Cx Event.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\note    For detailed description of Events, please refer to section
*\*\        I2C_Events in n32h47x_48x_i2c.h file.
*\*\return  The last event
**/
uint32_t I2C_GetLastEvent(const I2C_Module* I2Cx)
{	
    uint32_t lastevent;
    uint32_t flag1, flag2;

    /* Read the I2Cx status register */
	flag1 = (I2Cx->STS1 << 16) >> 16;
    flag2 = I2Cx->STS2;
    flag2 = flag2 << 16;

    /* Get the last event value from I2C status register */
    lastevent = ( flag1 | flag2 ) & FLAG_MASK;

    /* Return status */
    return lastevent;
}
/**
*\*\name    I2C_CheckFifoEvent.
*\*\fun    	Checks whether the last I2Cx FIFO Event is equal to the one passed as parameter.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   I2C_EVENT :
*\*\          - I2C_EVT_SLAVE_SEND_ADDR_MATCHED           							: EV1
*\*\          - I2C_EVT_SLAVE_RECV_ADDR_MATCHED              						: EV1
*\*\          - I2C_EVT_SLAVE_SEND_ADDR2_MATCHED     										: EV1
*\*\          - I2C_EVT_SLAVE_RECV_ADDR2_MATCHED        								: EV1
*\*\          - I2C_EVT_SLAVE_GCALLADDR_MATCHED            							: EV1
*\*\          - I2C_EVT_SLAVE_DATA_RECVD                         				: EV2
*\*\          - (I2C_EVT_SLAVE_DATA_RECVD | I2C_FLAG_DUALFLAG)      		: EV2
*\*\          - (I2C_EVT_SLAVE_DATA_RECVD | I2C_FLAG_GCALLADDR)    			: EV2
*\*\          - I2C_EVENT_SLAVE_BYTE_TRANSMITTED                      	: EV3
*\*\          - (I2C_EVENT_SLAVE_BYTE_TRANSMITTED | I2C_FLAG_DUALFLAG)  : EV3
*\*\          - (I2C_EVENT_SLAVE_BYTE_TRANSMITTED | I2C_FLAG_GCALLADDR) : EV3
*\*\          - I2C_EVT_SLAVE_ACK_MISS                           				: EV3_2
*\*\          - I2C_EVT_SLAVE_STOP_RECVD                         				: EV4
*\*\          - I2C_EVT_MASTER_MODE_FLAG                          			: EV5
*\*\          - I2C_EVT_MASTER_TXMODE_FLAG            									: EV6
*\*\          - I2C_EVT_MASTER_RXMODE_FLAG               								: EV6
*\*\          - I2C_EVT_MASTER_DATA_RECVD_FLAG                        	: EV7
*\*\          - I2C_EVT_MASTER_DATA_SENDING                    					: EV8
*\*\          - I2C_EVT_MASTER_DATA_SENDED                     					: EV8_2
*\*\          - I2C_EVT_MASTER_MODE_ADDRESS10_FLAG                      : EV9
*\*\note    For detailed description of Events, please refer to section
*\*\        I2C_Events in n32h47x_48x_i2c.h file.
*\*\return  SUCCESS or ERROR
**/
ErrorStatus I2C_CheckFifoEvent(I2C_Module* I2Cx, uint32_t I2C_FIFO_EVENT)
{
    uint32_t lastevent ;
    uint32_t flag1 , flag2 ;
    ErrorStatus status = ERROR;

    /* Read the I2Cx status register */
    flag1 = I2Cx->STS1;
    flag2 = I2Cx->STS2;
    flag2 = flag2 << 24;

    /* Get the last event value from I2C status register */
    lastevent = flag1 | flag2 ;

    /* Check whether the last event contains the I2C_FIFO_EVENT */

    if (( lastevent & I2C_FIFO_EVENT ) == I2C_FIFO_EVENT )
    {
        /* SUCCESS: last event is equal to I2C_FIFO_EVENT */
        status = SUCCESS;
    }
    else
    {
        /* ERROR: last event is different from I2C_FIFO_EVENT */
        status = ERROR;
    }

    /* Return status */
    return status;
}
/**
*\*\name    I2C_GetLastFifoEvent.
*\*\fun     Returns the last I2Cx FIFO Event.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\note    For detailed description of FIFO Events, please refer to section
*\*\        I2C_Events in n32h47x_48x_i2c.h file.
*\*\return  The last event
**/
uint32_t I2C_GetLastFifoEvent(I2C_Module* I2Cx)
{
    uint32_t lastevent;
    uint32_t flag1, flag2 ;

    /* Read the I2Cx FIFO status register */
    flag1 = I2Cx->STS1;
    flag2 = I2Cx->STS2;
    flag2 = flag2 << 24;

    /* Get the last event value from I2C FIFO status register */
    lastevent = flag1 | flag2;

    /* Return status */
    return lastevent;
}

/**
*\*\name    I2C_GetFlag.
*\*\fun     Checks whether the specified I2C flag is set or not.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   I2C_FLAG :
*\*\          - I2C_FLAG_DUALFLAG     		Dual flag (Slave mode)
*\*\          - I2C_FLAG_SMBHADDR     		SMBus host header (Slave mode)
*\*\          - I2C_FLAG_SMBDADDR     		SMBus default header (Slave mode)
*\*\          - I2C_FLAG_GCALLADDR    		General call header flag (Slave mode)
*\*\          - I2C_FLAG_TRF          		Transmitter/Receiver flag
*\*\          - I2C_FLAG_BUSY        		  Bus busy flag
*\*\          - I2C_FLAG_MSMODE       		Master/Slave flag
*\*\          - I2C_FLAG_SMBALERT     		SMBus Alert flag
*\*\          - I2C_FLAG_PECERR       		PEC error in reception flag
*\*\          - I2C_FLAG_OVERRUN      		Overrun/Underrun flag (Slave mode)
*\*\          - I2C_FLAG_ACKFAIL      		Acknowledge failure flag
*\*\          - I2C_FLAG_ARLOST       		Arbitration lost flag (Master mode)
*\*\          - I2C_FLAG_BUSERR       		Bus error flag
*\*\          - I2C_FLAG_TXDATE       		Data register empty flag (Transmitter)
*\*\          - I2C_FLAG_RXDATNE      		Data register not empty (Receiver) flag
*\*\          - I2C_FLAG_STOPF        		Stop detection flag (Slave mode)
*\*\          - I2C_FLAG_ADDR10F      		10-bit header sent flag (Master mode)
*\*\          - I2C_FLAG_BSF       				Byte transfer finished flag
*\*\          - I2C_FLAG_ADDRF        		Address sent flag (Master mode) "ADSL"
*\*\                                  		Address matched flag (Slave mode)"ENDA"
*\*\          - I2C_FLAG_STARTBF      		Start bit flag (Master mode)
*\*\          - I2C_FLAG_SCLLTO   				SCL timeout low error flag
*\*\          - I2C_FLAG_SCLHTO  					SCL timeout high error flag
*\*\          - I2C_FLAG_SDALTO   				SDA timeout low error flag
*\*\          - I2C_FLAG_DMAETOERR				DMA ETO error in reception flag
*\*\          - I2C_FLAG_FIFOWRERR				Write data when FIFO is full
*\*\          - I2C_FLAG_FIFORDERR				Read data when FIFO is empty
*\*\          - I2C_FLAG_FIFOHE						FIFO half empty flag
*\*\          - I2C_FLAG_FIFOHF						FIFO half full flag
*\*\          - I2C_FLAG_FIFOE						FIFO empty flag
*\*\          - I2C_FLAG_FIFOF	 					FIFO full flag
*\*\return  SET or RESET
**/
FlagStatus I2C_GetFlag(const I2C_Module* I2Cx, uint32_t I2C_FLAG)
{
    FlagStatus bitstatus;
    __IO uint32_t i2creg = 0, i2cxbase = 0;

    /* Get the I2Cx peripheral base address */
    i2cxbase = (uint32_t)I2Cx;

    /* Read flag register index */
    i2creg = I2C_FLAG >> 28;

    /* Get bit[23:0] of the flag */
    I2C_FLAG &= FLAG_MASK;

    if (i2creg != 0)
    {
        /* Get the I2Cx STS1 register address */
        i2cxbase += 0x14;
    }
    else
    {
        /* Flag in I2Cx STS2 Register */
        I2C_FLAG = (uint32_t)(I2C_FLAG >> 16);
        /* Get the I2Cx STS2 register address */
        i2cxbase += 0x18;
    }

    if (((*(__IO uint32_t*)i2cxbase) & I2C_FLAG) != (uint32_t)RESET)
    {
        /* I2C_FLAG is set */
        bitstatus = SET;
    }
    else
    {
        /* I2C_FLAG is reset */
        bitstatus = RESET;
    }

    /* Return the I2C_FLAG status */
    return bitstatus;
		
}


/**
*\*\name    I2C_ClrFlag.
*\*\fun     Clears the I2Cx's pending flags.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   I2C_FLAG :
*\*\          - I2C_FLAG_SCLLTO   			SCL timeout low error flag
*\*\          - I2C_FLAG_SCLHTO  				SCL timeout high error flag
*\*\          - I2C_FLAG_SDALTO   			SDA timeout low error flag
*\*\          - I2C_FLAG_FIFORDERR 			Read data when FIFO is empty
*\*\          - I2C_FLAG_FIFOWRERR 			Write data when FIFO is full
*\*\          - I2C_FLAG_DMAETOERR 			Prove that the DMA transmission is complete but no ETO signal is given
*\*\          - I2C_FLAG_SMBALERT 			SMBus Alert flag
*\*\          - I2C_FLAG_PECERR 				PEC error in reception flag
*\*\          - I2C_FLAG_OVERRUN 				Overrun/Underrun flag (Slave mode)
*\*\          - I2C_FLAG_ACKFAIL 				Acknowledge failure flag
*\*\          - I2C_FLAG_ARLOST 				Arbitration lost flag (Master mode)
*\*\          - I2C_FLAG_BUSERR 				Bus error flag
*\*\@note 	- STOPF (STOP detection) is cleared by software sequence: a read operation
*\*\          to I2C_STS1 register (I2C_GetFlag()) followed by a write operation
*\*\          to I2C_CTRL1 register (I2C_Enable() to re-enable the I2C peripheral).
*\*\ 				- ADD10F (10-bit header sent) is cleared by software sequence: a read
*\*\          operation to I2C_STS1 (I2C_GetFlag()) followed by writing the
*\*\          second byte of the address in DAT register.
*\*\ 				- BSF (Byte Transfer Finished) is cleared by software sequence: a read
*\*\          operation to I2C_STS1 register (I2C_GetFlag()) followed by a
*\*\          read/write to I2C_DAT register (I2C_SendData()).
*\*\ 				- ADDRF (Address sent) is cleared by software sequence: a read operation to
*\*\          I2C_STS1 register (I2C_GetFlag()) followed by a read operation to
*\*\          I2C_STS2 register ((void)(I2Cx->STS2)).
*\*\ 				- STARTBF (Start Bit) is cleared software sequence: a read operation to I2C_STS1
*\*\          register (I2C_GetFlag()) followed by a write operation to I2C_DAT
*\*\          register  (I2C_SendData()).
*\*\return  none
**/
void I2C_ClrFlag(I2C_Module* I2Cx, uint32_t I2C_FLAG)
{
    uint32_t flagpos;
	
    /* Get the I2C flag position */
    flagpos = I2C_FLAG & FLAG_MASK;
    /* Clear the selected I2C flag */
    I2Cx->STS1 = (uint16_t)~flagpos;
}


/**
*\*\name    I2C_ConfigInt.
*\*\fun     Enables or disables the specified I2C interrupts.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   I2C_IT :
*\*\          - I2C_INT_BUF 
*\*\          - I2C_INT_EVENT
*\*\          - I2C_INT_ERR
*\*\          - I2C_INT_BUF        		
*\*\          - I2C_INT_EVENT      			
*\*\          - I2C_INT_ERR        		
*\*\          - I2C_INT_FIFOF    	
*\*\          - I2C_INT_FIFOE    	
*\*\          - I2C_INT_FIFOHF    
*\*\          - I2C_INT_FIFOHE    		
*\*\          - I2C_INT_FIFORDEIEN     
*\*\          - I2C_INT_FIFOWREIEN			
*\*\          - I2C_INT_DMAETOEIEN      
*\*\          - I2C_INT_FIFONE		   
*\*\          - I2C_INT_FIFONF		  
*\*\          - I2C_INT_SDATOLIEN		   
*\*\          - I2C_INT_SCLTOHIEN		    
*\*\          - I2C_INT_SCLTOLIEN
*\*\param   Cmd :
*\*\          - ENABLE 
*\*\          - DISABLE
*\*\return  none
**/
void I2C_ConfigInt(I2C_Module* I2Cx, uint32_t I2C_IT, FunctionalState Cmd)
{
    if (Cmd != DISABLE)
    {
        /* Enable the selected I2C interrupts */
        I2Cx->CTRL2 |= I2C_IT;
    }
    else
    {
        /* Disable the selected I2C interrupts */
        I2Cx->CTRL2 &= (uint32_t)~I2C_IT;
    }
}


/**
*\*\name    I2C_GetIntStatus.
*\*\fun     Checks whether the specified I2C interrupt has occurred or not.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   I2C_IT :
*\*\          - I2C_INT_STARTBF  				Start Bit (Master mode) 
*\*\          - I2C_INT_ADDRF    				Address sent (master mode)/matched (slave mode) 
*\*\          - I2C_INT_BSF      				Byte Transfer Finished 
*\*\          - I2C_INT_STOPF    				Stop detection (Slave mode) 
*\*\          - I2C_INT_RXDATNE  				Data Register not Empty (receivers) 
*\*\          - I2C_INT_TXDATE   				Data Register Empty (transmitters)  
*\*\          - I2C_INT_ADDR10F  				10-bit header sent (Master mode)  
*\*\          - I2C_INT_ACKFAIL  				Acknowledge Failure  
*\*\          - I2C_INT_ARLOST   				Arbitration Lost (master mode)  
*\*\          - I2C_INT_BUSERR   				Bus Error  
*\*\          - I2C_INT_OVERRUN  				Overrun/Underrun  
*\*\          - I2C_INT_PECERR   				PEC Error in reception  
*\*\          - I2C_INT_SMBALERT 				SMBus Alert  
*\*\          - I2C_INT_FIFOF 					FIFO full  
*\*\          - I2C_INT_FIFOE 					FIFO empty  
*\*\          - I2C_INT_FIFOHF 					FIFO half full  
*\*\          - I2C_INT_FIFOHE 					FIFO half empty  
*\*\          - I2C_INT_FIFORDERR 			Read data when FIFO is empty  
*\*\          - I2C_INT_FIFOWRERR 			Write data when FIFO is full  
*\*\          - I2C_INT_DMAETOERR 			Prove that the DMA transmission is complete but no ETO signal is given  
*\*\          - I2C_INT_SDALTO 	    		SDA timeout low error  
*\*\          - I2C_INT_SCLHTO      		SCL timeout high error  
*\*\          - I2C_INT_SCLLTO 	    		SCL timeout low error  
*\*\return  SET or RESET
**/
INTStatus I2C_GetIntStatus(const I2C_Module* I2Cx, uint32_t I2C_IT)
{		
		INTStatus bitstatus;
    uint32_t tmpregister;

    /* Get I2Cx I2C_IT register value */
    tmpregister = I2Cx->STS1;

    /* Check the status of the specified I2Cx interrupt */
    if ((tmpregister & I2C_IT) != (uint32_t)RESET)
    {
        /* I2C_IT is set */
        bitstatus = SET;
    }
    else
    {
        /* I2C_IT is reset */
        bitstatus = RESET;
    }
    /* Return the I2C_IT status */
    return  bitstatus;
}


/**
*\*\name    I2C_ClrIntPendingBit.
*\*\fun     Clears the I2Cx's interrupt pending bits.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   Interrupt :
*\*\          - I2C_INT_SCLLTO   		SCL timeout low error flag
*\*\          - I2C_INT_SCLHTO  		SCL timeout high error flag
*\*\          - I2C_INT_SDALTO   		SDA timeout low error flag
*\*\          - I2C_INT_FIFORDERR 	Read data when FIFO is empty
*\*\          - I2C_INT_FIFOWRERR 	Write data when FIFO is full
*\*\          - I2C_INT_DMAETOERR 	Prove that the DMA transmission is complete but no ETO signal is given
*\*\          - I2C_INT_SMBALERT    SMBus Alert flag
*\*\          - I2C_INT_PECERR      PEC error in reception flag
*\*\          - I2C_INT_OVERRUN     Overrun/Underrun flag (Slave mode)
*\*\          - I2C_INT_ACKFAIL     Acknowledge failure flag
*\*\          - I2C_INT_ARLOST      Arbitration lost flag (Master mode)
*\*\          - I2C_INT_BUSERR      Bus error flag
*\*\note    - STOPF (STOP detection) is cleared by software sequence: a read operation
*\*\         	to I2C_STS1 register (I2C_GetIntStatus()) followed by a write operation to
*\*\         	I2C_CTRL1 register (I2C_Enable() to re-enable the I2C peripheral).
*\*\    		- ADD10F (10-bit header sent) is cleared by software sequence: a read
*\*\         	operation to I2C_STS1 (I2C_GetIntStatus()) followed by writing the second
*\*\         	byte of the address in I2C_DAT register.
*\*\    		- BSF (Byte Transfer Finished) is cleared by software sequence: a read
*\*\         	operation to I2C_STS1 register (I2C_GetIntStatus()) followed by a
*\*\         	read/write to I2C_DAT register (I2C_SendData()).
*\*\    		- ADDRF (Address sent) is cleared by software sequence: a read operation to
*\*\         	I2C_STS1 register (I2C_GetIntStatus()) followed by a read operation to
*\*\         	I2C_STS2 register ((void)(I2Cx->STS2)).
*\*\    		- STARTBF (Start Bit) is cleared by software sequence: a read operation to
*\*\         	I2C_STS1 register (I2C_GetIntStatus()) followed by a write operation to
*\*\         	I2C_DAT register (I2C_SendData()).
*\*\return  none
**/
void I2C_ClrIntPendingBit(I2C_Module* I2Cx, uint32_t I2C_IT)
{
    uint32_t flagpos;

    /* Get the I2C flag position */
    flagpos = I2C_IT & FLAG_MASK;
    /* Clear the selected I2C flag */
    I2Cx->STS1 = (uint16_t)~flagpos;
}



/**
*\*\name    I2C_EnableBYTENUM.
*\*\fun    	Enables or disables host receive byte count function.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   Cmd :
*\*\          - ENABLE 
*\*\          - DISABLE
*\*\return  none
**/
void I2C_EnableBYTENUM(I2C_Module* I2Cx, FunctionalState Cmd)
{
	if( Cmd == DISABLE)
	{
		I2Cx->BYTENUM &= ~BYTENUM_BTNUMEN_RESET;
	}
	else
	{
		I2Cx->BYTENUM |= BYTENUM_BTNUMEN_SET;
	}
}

/**
*\*\name    I2C_SetByteNumLastStartStop.
*\*\fun     Configure the last status after master have finished sending the required data bytes.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   LastStatus
*\*\          - RESTART_PROCESS
*\*\          - STOP_PROCESS
*\*\return  none
*\*\note    Send STOP process by default.
**/
void I2C_SetByteNumLastStartStop(I2C_Module* I2Cx, uint16_t LastStatus)
{
    I2Cx->BYTENUM &= (uint16_t)~((uint16_t)BYTENUM_STATUS_Mask);
    I2Cx->BYTENUM |= (uint16_t)( LastStatus);	

}

/**
*\*\name    I2C_SetReceivedDataBytesNum.
*\*\fun     Set the number of data bytes that will be received by receiver of I2C peripheral.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   Number_Of_bytes: the number of data bytes.
*\*\return  none
*\*\note    The number of bytes is greater than or equal to 2.
**/
void I2C_SetReceivedDataBytesNum(I2C_Module* I2Cx, uint16_t Number_Of_bytes)
{												
    I2Cx->BYTENUM &= (uint16_t)~((uint16_t)BYTENUM_Mask);
    I2Cx->BYTENUM |= (uint16_t)( Number_Of_bytes);					

}

/**
*\*\name    I2C_GetBYTENUM.
*\*\fun     Returns the number of bytes the host will receive.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\return  Returns the number of bytes the host will receive.
**/
uint8_t I2C_GetBYTENUM(const I2C_Module* I2Cx)
{
    /* Return the data in the BYTENUM bit */
    return ((uint8_t)(I2Cx->BYTENUM & 0x3FFFU));
}

/**
*\*\name    I2C_SetFIFODAT.
*\*\fun     Sets FIFO data volume.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   Data
*\*\return  none
**/
void I2C_SetFIFODAT(I2C_Module* I2Cx, uint32_t Data)
{
    /* Write in the FIFODAT register the data to be sent */
    I2Cx->FIFODAT = Data;
}

/**
*\*\name    I2C_GetFIFODAT.
*\*\fun     Returns FIFO data.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\return  FIFO data.
**/
uint8_t I2C_GetFIFODAT(const I2C_Module* I2Cx)
{
    /* Return the data in the FIFODAT register */
    return ((uint8_t)(I2Cx->FIFODAT));
}


/**
*\*\name    I2C_EnableLowTimeout.
*\*\fun    	Enable or disable low timeout.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   Cmd :
*\*\          - ENABLE 
*\*\          - DISABLE
*\*\return  none
**/
void I2C_EnableLowTimeout(I2C_Module* I2Cx, FunctionalState Cmd)
{
	if( Cmd == DISABLE)
	{
		I2Cx->CTRL2 &= ~CTRL2_LOWTMEN_RESET;
	}
	else
	{
		I2Cx->CTRL2 |= CTRL2_LOWTMEN_SET;
	}
}
/**
*\*\name    I2C_EnableHighTimeout.
*\*\fun    	Enable or disable high timeout.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   Cmd :
*\*\          - ENABLE 
*\*\          - DISABLE
*\*\return  none
**/
void I2C_EnableHighTimeout(I2C_Module* I2Cx, FunctionalState Cmd)
{
	if( Cmd == DISABLE)
	{
		I2Cx->CTRL2 &= ~CTRL2_HIGHTMEN_RESET;
	}
	else
	{
		I2Cx->CTRL2 |= CTRL2_HIGHTMEN_SET;
	}
}





/*==============Below is for analouge and digital filter function===========================*/

/**
*\*\name    I2C_EnableSCLAnalogFilter.
*\*\fun    	Enables or disables SCL Analog Filter.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   Cmd :
*\*\          - ENABLE 
*\*\          - DISABLE
*\*\return  none
**/
void I2C_EnableSCLAnalogFilter(I2C_Module* I2Cx, FunctionalState Cmd)
{
	if( Cmd == DISABLE)
	{
		I2Cx->GFLTRCTRL |= SCL_AFE_SET;
	}
	else
	{
        I2Cx->GFLTRCTRL &= SCL_AFE_RESET;
	}
}
/**
*\*\name    I2C_EnableSDAAnalogFilter.
*\*\fun    	Enables or disables SDA Analog Filter.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   Cmd :
*\*\          - ENABLE 
*\*\          - DISABLE
*\*\return  none
**/
void I2C_EnableSDAAnalogFilter(I2C_Module* I2Cx, FunctionalState Cmd)
{
	if( Cmd == DISABLE)
	{
        I2Cx->GFLTRCTRL |= SDA_AFE_SET;
	}
	else
	{
		I2Cx->GFLTRCTRL &= SDA_AFE_RESET;
	}
}


/**
*\*\name    I2C_SetSCLAnalogFilterWidth.
*\*\fun     SCL analog filter width selection.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   width :
*\*\        - I2C_ANALOG_FILTER_WIDTH_5NS   
*\*\        - I2C_ANALOG_FILTER_WIDTH_15NS  
*\*\        - I2C_ANALOG_FILTER_WIDTH_25NS  
*\*\        - I2C_ANALOG_FILTER_WIDTH_35NS  
*\*\return  none
**/
void I2C_SetSCLAnalogFilterWidth(I2C_Module* I2Cx, uint32_t width)
{
    uint32_t temp_value;

    temp_value = I2Cx->GFLTRCTRL;
    /* Clear SCLAFW[1:0] bits */
    temp_value &= I2C_SCLAFW_MASK;
    /* Set SCLAFW[1:0] bits according to width value */
    temp_value |= ((uint32_t)width << 4);
    /* Store the new value */
    I2Cx->GFLTRCTRL = temp_value;
    
}


/**
*\*\name    I2C_SetSDAAnalogFilterWidth.
*\*\fun     SDA analog filter width selection.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   width :
*\*\        - I2C_ANALOG_FILTER_WIDTH_5NS   
*\*\        - I2C_ANALOG_FILTER_WIDTH_15NS  
*\*\        - I2C_ANALOG_FILTER_WIDTH_25NS  
*\*\        - I2C_ANALOG_FILTER_WIDTH_35NS  
*\*\return  none
**/
void I2C_SetSDAAnalogFilterWidth(I2C_Module* I2Cx, uint32_t width)
{
    uint32_t temp_value;

    temp_value = I2Cx->GFLTRCTRL;
    /* Clear SDAAFW[1:0] bits */
    temp_value &= I2C_SDAAFW_MASK;
    /* Set SDAAFW[1:0] bits according to width value */
		temp_value |= width;
    /* Store the new value */
    I2Cx->GFLTRCTRL = temp_value;
    
}


/**
*\*\name    I2C_SetSCLDigitalFilterWidth.
*\*\fun     SCL digital filter width selection.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   width :
*\*\          - 0x00            Disable the digital filter.
*\*\          - 0x01 ~ 0x0F     The numbers of pclk cycles.
*\*\return  none
**/
void I2C_SetSCLDigitalFilterWidth(I2C_Module* I2Cx, uint32_t width)
{
    uint32_t temp_value;

    temp_value = I2Cx->GFLTRCTRL;
    /* Clear SCLDFW[3:0] bits */
    temp_value &= I2C_SCLDFW_MASK;
    /* Set SCLDFW[3:0] bits according to width value */
    temp_value |= ((uint32_t)width << 4);
    /* Store the new value */
    I2Cx->GFLTRCTRL = temp_value;
    
}


/**
*\*\name    I2C_Digital_Filter_Width_Set.
*\*\fun     SDA digital filter width selection.
*\*\param   I2Cx :
*\*\          - I2C1
*\*\          - I2C2
*\*\          - I2C3
*\*\          - I2C4
*\*\param   width :
*\*\          - 0x00            Disable the digital filter.
*\*\          - 0x01 ~ 0x0F     The numbers of pclk cycles.
*\*\return  none
**/
void I2C_SetSDADigitalFilterWidth(I2C_Module* I2Cx, uint32_t width)
{
    uint32_t temp_value;

    temp_value = I2Cx->GFLTRCTRL;
    /* Clear SDADFW[3:0] bits */
    temp_value &= I2C_SDADFW_MASK;
    /* Set SDADFW[3:0] bits according to width value */
    temp_value |= (uint32_t)width ;
    /* Store the new value */
    I2Cx->GFLTRCTRL = temp_value;
    
}


