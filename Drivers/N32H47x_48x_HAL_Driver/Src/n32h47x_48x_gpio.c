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
 *\*\file n32h47x_48x_gpio.c
 *\*\author Nations
 *\*\version v1.0.0
 *\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
 **/

#include "n32h47x_48x_gpio.h"
#include "n32h47x_48x_rcc.h"

/**
 *\*\name   GPIO_DeInit.
 *\*\fun    Reset the GPIOx peripheral registers to their default reset values.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\          - GPIOE
 *\*\          - GPIOF
 *\*\          - GPIOG
 *\*\          - GPIOH
 *\*\return none
 */
void GPIO_DeInit(GPIO_Module* GPIOx)
{
    if (GPIOx == GPIOA)
    {
        RCC_EnableAHBPeriphReset(RCC_AHB_PERIPHRST_GPIOA);
    }
    else if (GPIOx == GPIOB)
    {
        RCC_EnableAHBPeriphReset(RCC_AHB_PERIPHRST_GPIOB);
    }
    else if (GPIOx == GPIOC)
    {
        RCC_EnableAHBPeriphReset(RCC_AHB_PERIPHRST_GPIOC);
    }
    else if (GPIOx == GPIOD)
    {
        RCC_EnableAHBPeriphReset(RCC_AHB_PERIPHRST_GPIOD);
    }
    else if (GPIOx == GPIOE)
    {
        RCC_EnableAHBPeriphReset(RCC_AHB_PERIPHRST_GPIOE);
    }
    else if (GPIOx == GPIOF)
    {
        RCC_EnableAHBPeriphReset(RCC_AHB_PERIPHRST_GPIOF);
    }
    else if (GPIOx == GPIOG)
    {
        RCC_EnableAHBPeriphReset(RCC_AHB_PERIPHRST_GPIOG);
    }
    else if (GPIOx == GPIOH)
    {
        RCC_EnableAHBPeriphReset(RCC_AHB_PERIPHRST_GPIOH);
    }
    else
    {
        return;
    }
}

/**
 *\*\name   GPIO_DeInitPin.
 *\*\fun    Deinitializes the GPIOx pin to the default reset state.
*\*\param   GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\          - GPIOE
 *\*\          - GPIOF
 *\*\          - GPIOG
 *\*\          - GPIOH
 *\*\param  Pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\          - GPIO_PIN_ALL
 *\*\return none
 */
void GPIO_DeInitPin(GPIO_Module* GPIOx, uint32_t Pin)
{
    uint32_t pos = 0x00U;
    uint32_t CurrentPin;
    uint32_t BitPos;
    uint32_t tempReg; 
    uint32_t tempAF;
    uint32_t i;

    while((Pin >> pos) != 0U)
    {
        /* Get the IO position */
        CurrentPin = (Pin) & (1UL << pos);
        
        if(CurrentPin != 0UL)
        {
            BitPos     = pos * 2U;
            
            /*------------------------- GPIO Mode Configuration --------------------*/
            /* Configure GPIO as Analog Mode by default,except for the following pins:PA13/PA14/PA15/PB3/PB4(input mode) */
            if( (GPIOA == GPIOx) && (pos>=13UL) && (pos<=15UL) )
            {
                GPIOx->PMODE &= ~(GPIO_PMODE_BIT_MASK << BitPos);
            }
            else if( (GPIOB == GPIOx) && (pos>=3UL) && (pos<=4UL) )
            {
                GPIOx->PMODE &= ~(GPIO_PMODE_BIT_MASK <<BitPos);
            }
            else
            {
                GPIOx->PMODE |= (GPIO_PMODE_ANALOG << BitPos);
            }

            /* Deactivate the Pull-up and Pull-down resistor,except for the following pins:
                PA13/PA15/PB4(Pull-up), PA14(Pull-down)  */
            tempReg  = GPIOx->PUPD;
            tempReg &= ~(GPIO_PUPD_BIT_MASK << BitPos);
            if( (GPIOA == GPIOx) && ((pos==13UL) || (pos==15UL)) )
            {
                tempReg |= (GPIO_PULL_UP << BitPos);
            }
            else if( (GPIOA == GPIOx) && (pos==14UL) )
            {
                tempReg |= (GPIO_PULL_DOWN << BitPos);
            }
            else if( (GPIOB == GPIOx) &&(pos==4UL) )
            {
                tempReg |= (GPIO_PULL_UP << BitPos);
            }
            else
            {

            }

            GPIOx->PUPD = tempReg;

            /* Configure the default value IO Output Type */
            GPIOx->POTYPE &= ~(CurrentPin);
            
            /* Configure the default value for IO Speed */
            GPIOx->SR |= (GPIO_SR_BIT_MASK << pos);

            /* Configure the default value for IO Driver */
            GPIOx->DS &= ~(GPIO_DS_BIT_MASK << BitPos);
            GPIOx->DS |=  (GPIO_DS_8mA << BitPos);

            /* Configure the default value for Alternate Function */
            GPIOx->AFSEL[pos >> 2U] &= ~(GPIO_AFSEL_BIT_MASK << ((pos & 0x03U) * 8U));

            /*------------------------- EXTI Mode Configuration --------------------*/
            /* Clear the External Interrupt or Event for the current IO */
            tempAF = (uint32_t)GPIOx;
            tempAF = GPIO_GET_INDEX(tempAF) + pos*8UL;
            for(i=0; i<16U; i++)
            {
                tempReg = (AFIO->EXTI_CFG[i >> 2UL] >> ((i & 0x03UL) * 8UL)) & AFIO_EXTI_BIT_MASK;
                if( tempReg == tempAF )
                {
                    AFIO->EXTI_CFG[i >> 2UL] &= ~(AFIO_EXTI_BIT_MASK << ((i & 0x03UL) * 8UL));
                    break;
                }
            }

            /* Clear EXTI line configuration */
            EXTI->IMASK &= ~((uint32_t)CurrentPin);
            EXTI->EMASK &= ~((uint32_t)CurrentPin);

            /* Clear Rising Falling edge configuration */
            EXTI->RT_CFG &= ~((uint32_t)CurrentPin);
            EXTI->FT_CFG &= ~((uint32_t)CurrentPin);
        }

        pos++;
    }
}

/**
 *\*\name   GPIO_AFIOInitDefault.
 *\*\fun    Reset the AFIO peripheral registers to their default reset values.
 *\*\param  none
 *\*\return none
 */
void GPIO_AFIOInitDefault(void)
{
    RCC_EnableAPB2PeriphReset(RCC_APB2_PERIPH_AFIO);
}


/**
 *\*\name   GPIO_InitPeripheral.
 *\*\fun    Initialize the GPIOx peripheral with the value of the GPIO_InitStruct structure.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\          - GPIOE
 *\*\          - GPIOF
 *\*\          - GPIOG
 *\*\          - GPIOH
 *\*\param  GPIO_InitStructure :
 *\*\            - Pin
 *\*\               - GPIO_PIN_0
 *\*\               - GPIO_PIN_1
 *\*\               - GPIO_PIN_2
 *\*\               - GPIO_PIN_3
 *\*\               - GPIO_PIN_4
 *\*\               - GPIO_PIN_5
 *\*\               - GPIO_PIN_6
 *\*\               - GPIO_PIN_7
 *\*\               - GPIO_PIN_8
 *\*\               - GPIO_PIN_9
 *\*\               - GPIO_PIN_10
 *\*\               - GPIO_PIN_11
 *\*\               - GPIO_PIN_12
 *\*\               - GPIO_PIN_13
 *\*\               - GPIO_PIN_14
 *\*\               - GPIO_PIN_15
 *\*\               - GPIO_PIN_ALL
 *\*\            - GPIO_Mode
 *\*\               - GPIO_MODE_INPUT
 *\*\               - GPIO_MODE_OUTPUT_PP
 *\*\               - GPIO_MODE_OUTPUT_OD
 *\*\               - GPIO_MODE_AF_PP
 *\*\               - GPIO_MODE_AF_OD
 *\*\               - GPIO_MODE_ANALOG
 *\*\            - GPIO_Pull
 *\*\               - GPIO_NO_PULL
 *\*\               - GPIO_PULL_UP
 *\*\               - GPIO_PULL_DOWN
 *\*\            - GPIO_Slew_Rate
 *\*\               - GPIO_SLEW_RATE_FAST
 *\*\               - GPIO_SLEW_RATE_SLOW
 *\*\            - GPIO_Current
 *\*\               - GPIO_DC_2mA
 *\*\               - GPIO_DC_8mA
 *\*\               - GPIO_DC_4mA
 *\*\               - GPIO_DC_12mA
 *\*\            - GPIO_Alternate
 *\*\               - This parameter can be GPIO_AFx where x can be (0..31)
 *\*\return none
 */
void GPIO_InitPeripheral(GPIO_Module* GPIOx, GPIO_InitType * GPIO_InitStruct)
{
    uint32_t pos = 0x00U;
    uint32_t CurrentPin;
    uint32_t tempReg; 
    uint32_t BitPos;
    uint32_t RegNum;

    while(((GPIO_InitStruct->Pin) >> pos) != 0UL)
    {
        /* Get the IO position */
        CurrentPin = (GPIO_InitStruct->Pin) & (1UL << pos);

        if(CurrentPin != 0UL)
        {
            /* GPIO Alternate function Configuration */
            RegNum = pos >> 2U;
            BitPos = (pos & 0x03U) * 8U;
                
            tempReg = GPIOx->AFSEL[RegNum];
            tempReg &= ~(GPIO_AFSEL_BIT_MASK << BitPos);
            tempReg |= ((GPIO_InitStruct->GPIO_Alternate) << BitPos);
            GPIOx->AFSEL[RegNum] = tempReg;

            /* GPIO output mode Configuration */
            tempReg = GPIOx->POTYPE;

            if((GPIO_InitStruct->GPIO_Mode & GPIO_MODE_OD_MARK) == GPIO_MODE_OD_MARK)
            {
                tempReg |= CurrentPin;
            }
            else
            {
                tempReg &= ~(CurrentPin);
            }
            
            GPIOx->POTYPE = tempReg;

            /* GPIO Mode Configuration */
            BitPos = pos * 2U;
            /* Configure IO Direction mode (Input, Output, Alternate or Analog) */
            tempReg = GPIOx->PMODE;
            tempReg &= ~(GPIO_PMODE_BIT_MASK << BitPos);
            tempReg |= ((GPIO_InitStruct->GPIO_Mode & GPIO_PMODE_BIT_MASK) << BitPos);
            GPIOx->PMODE = tempReg;

            /* Configure pull-down mode */
            tempReg  =  GPIOx->PUPD;
            tempReg &= ~(GPIO_PUPD_BIT_MASK << BitPos);
            tempReg |=  (GPIO_InitStruct->GPIO_Pull << BitPos);
            GPIOx->PUPD  =  tempReg;

            /* Configure slew rate */
            tempReg = GPIOx->SR;
            tempReg &= ~(GPIO_SR_BIT_MASK << pos);
            tempReg |= (GPIO_InitStruct->GPIO_Slew_Rate << pos);
            GPIOx->SR = tempReg;

            /* Configure driver current */
            tempReg = GPIOx->DS;
            tempReg &= ~(GPIO_DS_BIT_MASK << BitPos);
            tempReg |= (GPIO_InitStruct->GPIO_Current << BitPos);
            GPIOx->DS = tempReg;
        }
        pos++;      
    }
}


/**
 *\*\name   GPIO_InitStruct.
 *\*\fun    Assign default values to each InitStruct member.
 *\*\param  InitStruct :
 *\*\           pointer to GPIO_InitType structure.
 *\*\return none
 */
void GPIO_InitStruct(GPIO_InitType* InitStruct)
{
    /* Reset GPIO structure member */
    InitStruct->Pin            = GPIO_PIN_NONE;
    InitStruct->GPIO_Slew_Rate = GPIO_SLEW_RATE_FAST;
    InitStruct->GPIO_Mode      = GPIO_MODE_INPUT;
    InitStruct->GPIO_Alternate = GPIO_NO_AF;
    InitStruct->GPIO_Pull      = GPIO_NO_PULL;
    InitStruct->GPIO_Current   = GPIO_DS_8mA;
}

/**
 *\*\name   GPIO_ReadInputDataBit.
 *\*\fun    Get the pin status on the specified input pin.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\          - GPIOE
 *\*\          - GPIOF
 *\*\          - GPIOG
 *\*\          - GPIOH
 *\*\param  Pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\return the state on the input pin.
 */
uint8_t GPIO_ReadInputDataBit(GPIO_Module* GPIOx, uint16_t Pin)
{
    uint8_t BitStatus;

    if ((GPIOx->PID & Pin) != (uint32_t)Bit_RESET)
    {
        BitStatus = (uint8_t)Bit_SET;
    }
    else
    {
        BitStatus = (uint8_t)Bit_RESET;
    }
    return BitStatus;
}

/**
 *\*\name   GPIO_ReadInputData.
 *\*\fun    Get the input data on the designated GPIO port.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\          - GPIOE
 *\*\          - GPIOF
 *\*\          - GPIOG
 *\*\          - GPIOH
 *\*\return the data value on the GPIO input port.
 */
uint16_t GPIO_ReadInputData(GPIO_Module* GPIOx)
{
    return ((uint16_t)GPIOx->PID);
}


/**
 *\*\name   GPIO_ReadOutputDataBit.
 *\*\fun    Get the pin status on the specified output pin.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\          - GPIOE
 *\*\          - GPIOF
 *\*\          - GPIOG
 *\*\          - GPIOH
 *\*\param  Pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\return the state on the output pin.
 */
uint8_t GPIO_ReadOutputDataBit(GPIO_Module* GPIOx, uint16_t Pin)
{
    uint8_t BitStatus;

    if ((GPIOx->POD & Pin) != (uint32_t)Bit_RESET)
    {
        BitStatus = (uint8_t)Bit_SET;
    }
    else
    {
        BitStatus = (uint8_t)Bit_RESET;
    }
    return BitStatus;
}


/**
 *\*\name   GPIO_ReadOutputData.
 *\*\fun    Get the output data on the designated GPIO port.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\          - GPIOE
 *\*\          - GPIOF
 *\*\          - GPIOG
 *\*\          - GPIOH
 *\*\return the data value on the GPIO output port.
 */
uint16_t GPIO_ReadOutputData(GPIO_Module* GPIOx)
{
    return ((uint16_t)GPIOx->POD);
}


/**
 *\*\name   GPIO_SetBits.
 *\*\fun    Sets the selected data port bits.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\          - GPIOE
 *\*\          - GPIOF
 *\*\          - GPIOG
 *\*\          - GPIOH
 *\*\param  Pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\return none
 */
void GPIO_SetBits(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIOx->PBSC = Pin;
}

/**
 *\*\name   GPIO_ResetBits.
 *\*\fun    Reset the selected data port bits.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\          - GPIOE
 *\*\          - GPIOF
 *\*\          - GPIOG
 *\*\          - GPIOH
 *\*\param  Pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\return none
 */
void GPIO_ResetBits(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIOx->PBC = Pin;
}

/**
 *\*\name   GPIO_WriteBit.
 *\*\fun    Reset the selected data port bits.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\          - GPIOE
 *\*\          - GPIOF
 *\*\          - GPIOG
 *\*\          - GPIOH
 *\*\param  Pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
  *\*\param  BitCmd :
 *\*\          - Bit_RESET
 *\*\          - Bit_SET
 *\*\return none
 */
void GPIO_WriteBits(GPIO_Module* GPIOx, uint16_t Pin, Bit_OperateType BitCmd)
{
    if (BitCmd != Bit_RESET)
    {
        GPIOx->PBSC = Pin;
    }
    else
    {
        GPIOx->PBC = Pin;
    }
}

/**
 *\*\name   GPIO_Write.
 *\*\fun    Write data on the designated GPIO data port.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\          - GPIOE
 *\*\          - GPIOF
 *\*\          - GPIOG
 *\*\          - GPIOH
 *\*\param  data_value :
 *\*\          the value to be written to the port output data register.
 *\*\          - 0~0xFFFF
 *\*\return none
 */
void GPIO_Write(GPIO_Module* GPIOx, uint16_t data_value)
{
    GPIOx->POD = data_value;
}

/**
 *\*\name   GPIO_Pin_Toggle.
 *\*\fun    Toggle the specified port pin level.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\          - GPIOE
 *\*\          - GPIOF
 *\*\          - GPIOG
 *\*\          - GPIOH
 *\*\param  Pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\return none
 */
void GPIO_TogglePin(GPIO_Module *GPIOx, uint16_t Pin)
{
    GPIOx->POD ^= Pin;
}


/**
 *\*\name   GPIO_ConfigPinLock.
 *\*\fun    GPIO port lock register configuration.
 *\*\param  GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\          - GPIOE
 *\*\          - GPIOF
 *\*\          - GPIOG
 *\*\          - GPIOH
 *\*\param  Pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\return none
 */
void GPIO_ConfigPinLock(GPIO_Module* GPIOx, uint16_t Pin)
{
    __IO uint32_t tmp = GPIO_PLOCK_PLOCKK;

    tmp |= Pin;
    /* Set PLOCKK bit */
    GPIOx->PLOCK = tmp;
    /* Reset PLOCKK bit */
    GPIOx->PLOCK = Pin;
    /* Set PLOCKK bit */
    GPIOx->PLOCK = tmp;
    /* Read PLOCKK bit*/
    tmp = GPIOx->PLOCK;
    /* Read PLOCKK bit*/
    tmp = GPIOx->PLOCK;
}


/**
 *\*\name   GPIO_ConfigEXTILine.
 *\*\fun    Selects the GPIO pin used as EXTI Line.
 *\*\param  LineSource :
 *\*\          - EXTI_LINE_SOURCE0
 *\*\          - EXTI_LINE_SOURCE1
 *\*\          - EXTI_LINE_SOURCE2
 *\*\          - EXTI_LINE_SOURCE3
 *\*\          - EXTI_LINE_SOURCE4
 *\*\          - EXTI_LINE_SOURCE5
 *\*\          - EXTI_LINE_SOURCE6
 *\*\          - EXTI_LINE_SOURCE7
 *\*\          - EXTI_LINE_SOURCE8
 *\*\          - EXTI_LINE_SOURCE9
 *\*\          - EXTI_LINE_SOURCE10
 *\*\          - EXTI_LINE_SOURCE11
 *\*\          - EXTI_LINE_SOURCE12
 *\*\          - EXTI_LINE_SOURCE13
 *\*\          - EXTI_LINE_SOURCE14
 *\*\          - EXTI_LINE_SOURCE15
 *\*\param  PortSource :
 *\*\          - GPIOA_PORT_SOURCE
 *\*\          - GPIOB_PORT_SOURCE
 *\*\          - GPIOC_PORT_SOURCE
 *\*\          - GPIOD_PORT_SOURCE
 *\*\          - GPIOE_PORT_SOURCE
 *\*\          - GPIOF_PORT_SOURCE
 *\*\          - GPIOG_PORT_SOURCE
 *\*\          - GPIOH_PORT_SOURCE
 *\*\param  PinSource :
 *\*\          - GPIO_PIN_SOURCE0
 *\*\          - GPIO_PIN_SOURCE1
 *\*\          - GPIO_PIN_SOURCE2
 *\*\          - GPIO_PIN_SOURCE3
 *\*\          - GPIO_PIN_SOURCE4
 *\*\          - GPIO_PIN_SOURCE5
 *\*\          - GPIO_PIN_SOURCE6
 *\*\          - GPIO_PIN_SOURCE7
 *\*\          - GPIO_PIN_SOURCE8
 *\*\          - GPIO_PIN_SOURCE9
 *\*\          - GPIO_PIN_SOURCE10
 *\*\          - GPIO_PIN_SOURCE11
 *\*\          - GPIO_PIN_SOURCE12
 *\*\          - GPIO_PIN_SOURCE13
 *\*\          - GPIO_PIN_SOURCE14
 *\*\          - GPIO_PIN_SOURCE15
 *\*\return none
 */
void GPIO_ConfigEXTILine(uint8_t LineSource, uint8_t PortSource, uint8_t PinSource)
{
    uint32_t RegNum;
    uint32_t BitPos;
    uint32_t tempReg;

    RegNum = (uint32_t)LineSource >> 0x02UL;
    BitPos = ((uint32_t)LineSource & 0x03UL) * 8UL;

    tempReg  = AFIO->EXTI_CFG[RegNum];
    tempReg &= ~(AFIO_EXTI_BIT_MASK << BitPos);
    tempReg |= (((uint32_t)PinSource*8UL + (uint32_t)PortSource) << BitPos);
    AFIO->EXTI_CFG[RegNum] = tempReg;
}

/**
 *\*\name   GPIO_ConfigPinRemap.
 *\*\fun    Pin remapping configuration.
 *\*\param  PortSource :
 *\*\          - GPIOA_PORT_SOURCE
 *\*\          - GPIOB_PORT_SOURCE
 *\*\          - GPIOC_PORT_SOURCE
 *\*\          - GPIOD_PORT_SOURCE
 *\*\          - GPIOE_PORT_SOURCE
 *\*\          - GPIOF_PORT_SOURCE
 *\*\          - GPIOG_PORT_SOURCE
 *\*\          - GPIOH_PORT_SOURCE
 *\*\param  PinSource :
 *\*\          - GPIO_PIN_SOURCE0
 *\*\          - GPIO_PIN_SOURCE1
 *\*\          - GPIO_PIN_SOURCE2
 *\*\          - GPIO_PIN_SOURCE3
 *\*\          - GPIO_PIN_SOURCE4
 *\*\          - GPIO_PIN_SOURCE5
 *\*\          - GPIO_PIN_SOURCE6
 *\*\          - GPIO_PIN_SOURCE7
 *\*\          - GPIO_PIN_SOURCE8
 *\*\          - GPIO_PIN_SOURCE9
 *\*\          - GPIO_PIN_SOURCE10
 *\*\          - GPIO_PIN_SOURCE11
 *\*\          - GPIO_PIN_SOURCE12
 *\*\          - GPIO_PIN_SOURCE13
 *\*\          - GPIO_PIN_SOURCE14
 *\*\          - GPIO_PIN_SOURCE15
 *\*\param  AlternateFunction :
 *\*\          - This parameter can be GPIO_AFx where x can be (0..31)
 *\*\          - This parameter can also be one of the following parameter(PortSource and PinSource is ignored):
 *\*\               - GPIO_RMP_SWJ_JTAG:            Full SWJ Enabled (JTAG-DP + SW-DP)
 *\*\               - GPIO_RMP_SWJ_JTAG_NO_NJTRST:  Full SWJ Enabled (JTAG-DP + SW-DP) but without NJTRST
 *\*\               - GPIO_RMP_SWJ_SWD:   JTAG-DP Disabled and SW-DP Enabled
 *\*\               - GPIO_RMP_SWJ_DISABLE:     Full SWJ Disabled (JTAG-DP + SW-DP)
 *\*\return none
 */
void GPIO_ConfigPinRemap(uint8_t PortSource, uint8_t PinSource, uint32_t AlternateFunction)
{
    uint32_t tempReg;
    uint32_t RegNum;
    uint32_t BitPos; 
    GPIO_Module *GPIOx;

    if(AlternateFunction > GPIO_AF31)
    {
        tempReg = AFIO->RMP_CFG & (~(AFIO_RMP_CFG_SWJ_CFG));
        tempReg |= (AlternateFunction & (~(GPIO_RMP_SWJ_MARK)));
        AFIO->RMP_CFG = tempReg;
    }
    else
    {
        RegNum = (uint32_t)PinSource >> 2UL;
        BitPos = (((uint32_t)PinSource & 0x03UL)) * 8UL;
        
        /*Get Peripheral point*/
        GPIOx = GPIO_GET_PERIPH(PortSource);

        tempReg = GPIOx->AFSEL[RegNum];
        tempReg &= ~(GPIO_AFSEL_BIT_MASK << BitPos);
        tempReg |= (AlternateFunction << BitPos);
        GPIOx->AFSEL[RegNum] = tempReg;
    }
    
}

/**
 *\*\name   AFIO_Config_SPI_NSS_Mode.
 *\*\fun    Configure the SPIx NSS mode during idle.
 *\*\param  AFIO_SPIx_NSS : 
 *\*\          choose which SPI configuration.
 *\*\          - AFIO_SPI1_NSS
 *\*\          - AFIO_SPI2_NSS
 *\*\          - AFIO_SPI3_NSS
 *\*\          - AFIO_SPI4_NSS
 *\*\          - AFIO_SPI5_NSS
 *\*\          - AFIO_SPI6_NSS
 *\*\param  NSS_Mode : 
 *\*\          specifies the SPI_NSS mode to be configured.
 *\*\          - AFIO_SPI_NSS_HIGH_IMPEDANCE
 *\*\          - AFIO_SPI_NSS_HIGH_LEVEL
 *\*\return none
 */
void AFIO_Config_SPI_NSS_Mode(uint32_t AFIO_SPIx_NSS, uint32_t NSS_Mode)
{
    uint32_t tempReg;

    tempReg = AFIO->RMP_CFG | AFIO_RMP_CFG_SWJ_CFG;

    if(NSS_Mode != AFIO_SPI_NSS_HIGH_IMPEDANCE)
    {
        tempReg |= AFIO_SPIx_NSS;
    }
    else 
    {
        tempReg &= ~AFIO_SPIx_NSS;
    }

    AFIO->RMP_CFG = tempReg;
}

/**
 *\*\name   AFIO_ConfigIOFilter.
 *\*\fun    Configure IO filter cycle which is counted in AHB clock.
 *\*\param  Filter_Cycle : 
 *\*\        - 1~64
 *\*\return none
 */
void AFIO_ConfigIOFilter(uint32_t Filter_Cycle)
{
    uint32_t tempReg;
    
    if(0UL == Filter_Cycle)
    {
        return;
    }
    else if(Filter_Cycle > 64UL)
    {
        return;
    }
    else
    {
        Filter_Cycle--;
    }

    tempReg  = AFIO->RMP_CFG | AFIO_RMP_CFG_SWJ_CFG;
    tempReg &= ~AFIO_IO_FILTER_MASK;
    tempReg |= (Filter_Cycle << AFIO_IO_FILTER_OFFSET);
    AFIO->RMP_CFG  = tempReg;
}

/**
 *\*\name   AFIO_Config_FEMC_NADV_Pin.
 *\*\fun    Enable or disable the FEMC NADV pin.
 *\*\param  NADV_Pin : 
 *\*\        - AFIO_FEMC_NADV_PIN_USED
 *\*\        - AFIO_FEMC_NADV_PIN_NOT_USED
 *\*\return none
 */
void AFIO_Config_FEMC_NADV_Pin(uint32_t NADV_Pin)
{
    uint32_t tempReg;

    tempReg = AFIO->RMP_CFG | AFIO_RMP_CFG_SWJ_CFG;

    if(NADV_Pin != AFIO_FEMC_NADV_PIN_USED)
    {
        tempReg |= AFIO_FEMC_NADV_PIN_NOT_USED;
    }
    else 
    {
        tempReg &= ~AFIO_FEMC_NADV_PIN_NOT_USED;
    }

    AFIO->RMP_CFG = tempReg;
}

/**
 *\*\name   AFIO_Config_EXTI_Filter.
 *\*\fun    Enable or disable EXTI analog filter.
 *\*\param  EXTI_Filter : 
 *\*\        - AFIO_EXTI_FILTER_ENABLE
 *\*\        - AFIO_EXTI_FILTER_DISABLE
 *\*\return none
 */
void AFIO_Config_EXTI_Filter(uint32_t EXTI_Filter)
{
    uint32_t tempReg;

    tempReg = AFIO->RMP_CFG | AFIO_RMP_CFG_SWJ_CFG;

    if(EXTI_Filter != AFIO_EXTI_FILTER_ENABLE)
    {
        tempReg |= AFIO_EXTI_FILTER_DISABLE;
    }
    else 
    {
        tempReg &= ~AFIO_EXTI_FILTER_DISABLE;
    }

    AFIO->RMP_CFG = tempReg;
}

/**
 *\*\name   AFIO_Config_XSPI_XIP_BigEndian.
 *\*\fun    Enable or disable the big endian for XSPI XIP mode.
 *\*\param  Endian : 
 *\*\          - AFIO_XSPI_XIP_LITTLE_ENDIAN
 *\*\          - AFIO_XSPI_XIP_BIG_ENDIAN
 *\*\return none
 */
void AFIO_Config_XSPI_XIP_BigEndian(uint32_t Endian)
{
    uint32_t tempReg;

    tempReg = AFIO->RMP_CFG | AFIO_RMP_CFG_SWJ_CFG;

    if(Endian == AFIO_XSPI_XIP_BIG_ENDIAN )
    {
        tempReg |= AFIO_XSPI_XIP_BIG_ENDIAN;
    }
    else
    {
        tempReg &= ~AFIO_XSPI_XIP_BIG_ENDIAN;
    }

    AFIO->RMP_CFG = tempReg;
}

/**
 *\*\name   AFIO_Config_XSPI_HalfDuplexMode.
 *\*\fun    Enable or disable the XSPI Half-Duplex mode.
 *\*\param  HalfDuplex : 
 *\*\          - AFIO_XSPI_HALF_DUPLEX_DISABLE
 *\*\          - AFIO_XSPI_HALF_DUPLEX_ENABLE
 *\*\return none
 */
void AFIO_Config_XSPI_HalfDuplexMode(uint32_t HalfDuplex)
{
    uint32_t tempReg;

    tempReg = AFIO->RMP_CFG | AFIO_RMP_CFG_SWJ_CFG;

    if(HalfDuplex != AFIO_XSPI_HALF_DUPLEX_DISABLE)
    {
        tempReg |= AFIO_XSPI_HALF_DUPLEX_ENABLE;
    }
    else
    {
        tempReg &= ~AFIO_XSPI_HALF_DUPLEX_ENABLE;
    }

    AFIO->RMP_CFG = tempReg;
}

/**
 *\*\name   AFIO_Config_XSPI_DualQuadMode.
 *\*\fun    Enable or disable the XSPI Dual-Quad mode.
 *\*\param  DualQuad : 
 *\*\          - AFIO_XSPI_DUAL_QUAD_DISABLE
 *\*\          - AFIO_XSPI_DUAL_QUAD_ENABLE
 *\*\return none
 */
void AFIO_Config_XSPI_DualQuadMode(uint32_t DualQuad)
{
    uint32_t tempReg;

    tempReg = AFIO->RMP_CFG | AFIO_RMP_CFG_SWJ_CFG;

    if(DualQuad != AFIO_XSPI_DUAL_QUAD_DISABLE)
    {
        tempReg |= (AFIO_XSPI_DUAL_QUAD_ENABLE|AFIO_XSPI_DUAL_QUAD_FLASH2_ENABLE);
    }
    else
    {
        tempReg &= ~(AFIO_XSPI_DUAL_QUAD_ENABLE|AFIO_XSPI_DUAL_QUAD_FLASH2_ENABLE);
    }

    AFIO->RMP_CFG = tempReg;
}

/**
 *\*\name   AFIO_Config_ETH_Mode.
 *\*\fun    Config the ETH interface mode
 *\*\param  ETH_Mode : 
 *\*\          - AFIO_ETH_MODE_MII
 *\*\          - AFIO_ETH_MODE_RMII
 *\*\return none
 */
void AFIO_Config_ETH_Mode(uint32_t ETH_Mode)
{
    uint32_t tempReg;

    tempReg = AFIO->RMP_CFG | AFIO_RMP_CFG_SWJ_CFG;

    if(ETH_Mode != AFIO_ETH_MODE_MII)
    {
        tempReg |= AFIO_ETH_MODE_RMII;
    }
    else
    {
        tempReg &= ~AFIO_ETH_MODE_RMII;
    }

    AFIO->RMP_CFG = tempReg;
}

/**
 *\*\name   AFIO_Config_XSPI_NSS_Input.
 *\*\fun    Enable or disable XSPI NSS input function, and select which NSS pin is used
 *\*\param  InputEnable : 
 *\*\          - AFIO_XSPI_NSS_INPUT_DISABLE
 *\*\          - AFIO_XSPI_NSS_INPUT_ENABLE
 *\*\param  InputPin : 
 *\*\          - AFIO_XSPI_NSS_INPUT_NSS0
 *\*\          - AFIO_XSPI_NSS_INPUT_NSS1
 *\*\return none
 */
void AFIO_Config_XSPI_NSS_Input(uint32_t InputEnable, uint32_t InputPin)
{
    uint32_t tempReg;

    tempReg = AFIO->RMP_CFG | AFIO_RMP_CFG_SWJ_CFG;

    if(InputEnable != AFIO_XSPI_NSS_INPUT_DISABLE)
    {
        tempReg |= AFIO_XSPI_NSS_INPUT_ENABLE;
        if(InputPin != AFIO_XSPI_NSS_INPUT_NSS0)
        {
            tempReg |= AFIO_XSPI_NSS_INPUT_NSS1;
        }
        else
        {
            tempReg &= ~AFIO_XSPI_NSS_INPUT_NSS1;
        }
    }
    else
    {
        tempReg &= ~(AFIO_XSPI_NSS_INPUT_ENABLE|AFIO_XSPI_NSS_INPUT_NSS1);
    }

    AFIO->RMP_CFG = tempReg;
}

/**
 *\*\name   AFIO_Config_XSPI_RXDS_SampleDelay.
 *\*\fun    Config the delay time between RXDS sample point and RXDS rising/falling edge.
 *\*\param  Delay : 
 *\*\          - AFIO_XSPI_RXDS_DELAY_NONE
 *\*\          - AFIO_XSPI_RXDS_DELAY_1HCLK
 *\*\          - AFIO_XSPI_RXDS_DELAY_2HCLK
 *\*\return none
 */
void AFIO_Config_XSPI_RXDS_SampleDelay(uint32_t Delay)
{
    uint32_t tempReg;

    tempReg  = AFIO->EMC_CFG;
    tempReg &= ~AFIO_XSPI_RXDS_DELAY_MASK;
    tempReg |= Delay;
    AFIO->EMC_CFG = tempReg;
}

/**
 *\*\name   AFIO_Config_XSPI_BigEndian_Read.
 *\*\fun    Enable or disable XSPI Big Endian read in normal mode(not XIP)
 *\*\param  Endian : 
 *\*\          - AFIO_XSPI_READ_LITTLE_ENDIAN
 *\*\          - AFIO_XSPI_READ_BIG_ENDIAN
 *\*\return none
 */
void AFIO_Config_XSPI_BigEndian_Read(uint32_t Endian)
{
    if(Endian != AFIO_XSPI_READ_LITTLE_ENDIAN)
    {
        AFIO->EMC_CFG |= AFIO_XSPI_READ_BIG_ENDIAN;
    }
    else
    {
        AFIO->EMC_CFG &= ~AFIO_XSPI_READ_BIG_ENDIAN;
    }
}

/**
 *\*\name   AFIO_Config_XSPI_BigEndian_Write.
 *\*\fun    Enable or disable XSPI Big Endian write in normal mode(not XIP)
 *\*\param  Endian : 
 *\*\          - AFIO_XSPI_WRITE_LITTLE_ENDIAN
 *\*\          - AFIO_XSPI_WRITE_BIG_ENDIAN
 *\*\return none
 */
void AFIO_Config_XSPI_BigEndian_Write(uint32_t Endian)
{
    if(Endian != AFIO_XSPI_WRITE_LITTLE_ENDIAN)
    {
        AFIO->EMC_CFG |= AFIO_XSPI_WRITE_BIG_ENDIAN;
    }
    else
    {
        AFIO->EMC_CFG &= ~AFIO_XSPI_WRITE_BIG_ENDIAN;
    }
}

/**
 *\*\name   AFIO_Config_XSPI_TimeExtension.
 *\*\fun    Enable or disable XSPI time extension funtion for setup time or hold time. 
 *\*\param  Extension : 
 *\*\          - AFIO_XSPI_NO_TIME_EXTENSION
 *\*\          - AFIO_XSPI_SETUP_TIME_EXTENSION
 *\*\          - AFIO_XSPI_HOLD_TIME_EXTENSION
 *\*\          - AFIO_XSPI_SETUP_HOLD_TIME_EXTENSION
 *\*\return none
 */
void AFIO_Config_XSPI_TimeExtension(uint32_t Extension)
{
    uint32_t tempReg;

    tempReg  = AFIO->EMC_CFG;
    tempReg &= ~AFIO_EMC_CFG_XSPI_EXTEND;
    tempReg |= Extension;
    AFIO->EMC_CFG = tempReg;
}

/**
 *\*\name   AFIO_Config_XSPI_NSS_HighTime.
 *\*\fun    Config the high-level time of XSPI NSS pin when XSPI_CTRL0.SSTE bit is set. 
 *\*\param  clk : 
 *\*\          - AFIO_XSPI_NSS_HIGH_1CLK
 *\*\          - AFIO_XSPI_NSS_HIGH_2CLK
 *\*\          - AFIO_XSPI_NSS_HIGH_3CLK
 *\*\          - AFIO_XSPI_NSS_HIGH_4CLK
 *\*\          - AFIO_XSPI_NSS_HIGH_5CLK
 *\*\          - AFIO_XSPI_NSS_HIGH_6CLK
 *\*\          - AFIO_XSPI_NSS_HIGH_7CLK
 *\*\          - AFIO_XSPI_NSS_HIGH_8CLK
 *\*\          - AFIO_XSPI_NSS_HIGH_9CLK
 *\*\          - AFIO_XSPI_NSS_HIGH_10CLK
 *\*\          - AFIO_XSPI_NSS_HIGH_11CLK
 *\*\          - AFIO_XSPI_NSS_HIGH_12CLK
 *\*\          - AFIO_XSPI_NSS_HIGH_13CLK
 *\*\          - AFIO_XSPI_NSS_HIGH_14CLK
 *\*\          - AFIO_XSPI_NSS_HIGH_15CLK
 *\*\          - AFIO_XSPI_NSS_HIGH_16CLK
 *\*\return none
 */
void AFIO_Config_XSPI_NSS_HighTime(uint32_t clk)
{
    uint32_t tempReg;

    tempReg  = AFIO->EMC_CNT;
    tempReg &= ~AFIO_EMC_CNT_XSPI_NSS_HIGH;
    tempReg |= clk;
    AFIO->EMC_CNT = tempReg;
}

/**
 *\*\name   AFIO_ConfigPinTol5V.
 *\*\fun    Enable or disable the 5V tolerance function for GPIOx pin.
 *\*\param   GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\          - GPIOE
 *\*\          - GPIOF
 *\*\          - GPIOG
 *\*\          - GPIOH
 *\*\param  Pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\          - GPIO_PIN_ALL
 *\*\param  cmd :
 *\*\          - DISABLE
 *\*\          - ENABLE
 *\*\note   Most of pins support 5V tolerance,but some pins don't support.
 *\*\return none
 */
void AFIO_ConfigPinTol5V(GPIO_Module* GPIOx, uint32_t Pin,FunctionalState cmd)
{
    uint32_t tempReg;
    uint32_t RegNum;
    uint32_t BitMask;
    uint32_t GPIO_Index;
    
    GPIO_Index = (uint32_t)GPIOx;
    GPIO_Index = GPIO_GET_INDEX(GPIO_Index);

    RegNum = GPIO_Index / 2UL;
    BitMask = Pin << (16UL * (GPIO_Index & 0x1UL));
    tempReg = AFIO->TOL5V_CFG[RegNum];

    if(cmd != DISABLE)
    {
        tempReg |= BitMask;

    }
    else
    {
        tempReg &= ~(BitMask);
    }

    AFIO->TOL5V_CFG[RegNum] = tempReg;
}

/**
 *\*\name   AFIO_ConfigPinFilter.
 *\*\fun    Enable or disable the digital filter function for GPIOx pin.
 *\*\param   GPIOx :
 *\*\          - GPIOA
 *\*\          - GPIOB
 *\*\          - GPIOC
 *\*\          - GPIOD
 *\*\          - GPIOE
 *\*\          - GPIOF
 *\*\          - GPIOG
 *\*\          - GPIOH
 *\*\param  Pin :
 *\*\          - GPIO_PIN_0
 *\*\          - GPIO_PIN_1
 *\*\          - GPIO_PIN_2
 *\*\          - GPIO_PIN_3
 *\*\          - GPIO_PIN_4
 *\*\          - GPIO_PIN_5
 *\*\          - GPIO_PIN_6
 *\*\          - GPIO_PIN_7
 *\*\          - GPIO_PIN_8
 *\*\          - GPIO_PIN_9
 *\*\          - GPIO_PIN_10
 *\*\          - GPIO_PIN_11
 *\*\          - GPIO_PIN_12
 *\*\          - GPIO_PIN_13
 *\*\          - GPIO_PIN_14
 *\*\          - GPIO_PIN_15
 *\*\          - GPIO_PIN_ALL
 *\*\param  cmd :
 *\*\          - DISABLE
 *\*\          - ENABLE
 *\*\return none
 */
void AFIO_ConfigPinFilter(GPIO_Module* GPIOx, uint32_t Pin,FunctionalState cmd)
{
    uint32_t tempReg;
    uint32_t RegNum;
    uint32_t BitMask;
    uint32_t GPIO_Index;
    
    GPIO_Index = (uint32_t)GPIOx;
    GPIO_Index = GPIO_GET_INDEX(GPIO_Index);

    RegNum = GPIO_Index / 2UL;
    BitMask = Pin << (16UL * (GPIO_Index & 0x1UL));
    tempReg = AFIO->FILTER_CFG[RegNum];

    if(cmd != DISABLE)
    {
        tempReg |= BitMask;

    }
    else
    {
        tempReg &= ~(BitMask);
    }

    AFIO->FILTER_CFG[RegNum] = tempReg;
}

/**
 *\*\name   AFIO_Config_GPIOC_ReadRegDelay.
 *\*\fun    Enable or disable back-to-back read delay for GPIOC register.
 *\*\param  cmd :
 *\*\          - DISABLE
 *\*\          - ENABLE
 *\*\return none
 */
void AFIO_Config_GPIOC_ReadRegDelay(FunctionalState cmd)
{
    if(cmd != DISABLE)
    {
        AFIO->EMC_CNT |= AFIO_EMC_CNT_PC_RD_DELAY_EN;
    }
    else
    {
        AFIO->EMC_CNT &= ~AFIO_EMC_CNT_PC_RD_DELAY_EN;
    }
}


/**
 *\*\name   AFIO_Config_SHRTIM_EXEV_Pin.
 *\*\fun    Selects the GPIO pin used as SHRTIM1 EXEVx input source.
 *\*\param  EXEV_Line :
 *\*\          - AFIO_SHRTIM_EXEV_1
 *\*\          - AFIO_SHRTIM_EXEV_2
 *\*\          - AFIO_SHRTIM_EXEV_3
 *\*\          - AFIO_SHRTIM_EXEV_4
 *\*\          - AFIO_SHRTIM_EXEV_5
 *\*\          - AFIO_SHRTIM_EXEV_6
 *\*\          - AFIO_SHRTIM_EXEV_7
 *\*\          - AFIO_SHRTIM_EXEV_8
 *\*\          - AFIO_SHRTIM_EXEV_9
 *\*\          - AFIO_SHRTIM_EXEV_10
 *\*\param  PortSource :
 *\*\          - GPIOA_PORT_SOURCE
 *\*\          - GPIOB_PORT_SOURCE
 *\*\          - GPIOC_PORT_SOURCE
 *\*\          - GPIOD_PORT_SOURCE
 *\*\          - GPIOE_PORT_SOURCE
 *\*\          - GPIOF_PORT_SOURCE
 *\*\          - GPIOG_PORT_SOURCE
 *\*\          - GPIOH_PORT_SOURCE
 *\*\param  PinSource :
 *\*\          - GPIO_PIN_SOURCE0
 *\*\          - GPIO_PIN_SOURCE1
 *\*\          - GPIO_PIN_SOURCE2
 *\*\          - GPIO_PIN_SOURCE3
 *\*\          - GPIO_PIN_SOURCE4
 *\*\          - GPIO_PIN_SOURCE5
 *\*\          - GPIO_PIN_SOURCE6
 *\*\          - GPIO_PIN_SOURCE7
 *\*\          - GPIO_PIN_SOURCE8
 *\*\          - GPIO_PIN_SOURCE9
 *\*\          - GPIO_PIN_SOURCE10
 *\*\          - GPIO_PIN_SOURCE11
 *\*\          - GPIO_PIN_SOURCE12
 *\*\          - GPIO_PIN_SOURCE13
 *\*\          - GPIO_PIN_SOURCE14
 *\*\          - GPIO_PIN_SOURCE15
 *\*\return none
 */
void AFIO_Config_SHRTIM_EXEV_Pin(uint8_t EXEV_Line, uint8_t PortSource, uint8_t PinSource)
{
    uint32_t RegNum;
    uint32_t BitPos;
    uint32_t tempReg;

    RegNum = (uint32_t)EXEV_Line >> 2UL;
    BitPos = ((uint32_t)EXEV_Line & 0x03UL) * 8UL;

    tempReg  = AFIO->SHRT_EXEV_CFG[RegNum];
    tempReg &= ~(AFIO_SHRTIM_EXEV_BIT_MASK << BitPos);
    tempReg |= (((uint32_t)PinSource*8UL + (uint32_t)PortSource) << BitPos);
    AFIO->SHRT_EXEV_CFG[RegNum] = tempReg;
}

/**
 *\*\name   AFIO_Config_EMC_Funtion.
 *\*\fun    Enable or disable some EMC function.
 *\*\param  EMC_fun :
 *\*\          - AFIO_EMC_CLAMP1_RST
 *\*\          - AFIO_EMC_CLAMP2_RST
 *\*\          - AFIO_EMC_CLAMP3_RST
 *\*\          - AFIO_EMC_CLAMP4_RST
 *\*\          - AFIO_EMC_GBN1_RST  
 *\*\          - AFIO_EMC_GBN2_RST  
 *\*\          - AFIO_EMC_GBN3_RST  
 *\*\          - AFIO_EMC_GBN4_RST  
 *\*\          - AFIO_EMC_GB1_RST   
 *\*\          - AFIO_EMC_GB2_RST   
 *\*\          - AFIO_EMC_GB3_RST   
 *\*\          - AFIO_EMC_GB4_RST   
 *\*\          - AFIO_EMC_CLAMP1_DET
 *\*\          - AFIO_EMC_CLAMP2_DET
 *\*\          - AFIO_EMC_CLAMP3_DET
 *\*\          - AFIO_EMC_CLAMP4_DET
 *\*\          - AFIO_EMC_GBN1_DET  
 *\*\          - AFIO_EMC_GBN2_DET  
 *\*\          - AFIO_EMC_GBN3_DET  
 *\*\          - AFIO_EMC_GBN4_DET  
 *\*\          - AFIO_EMC_GB1_DET   
 *\*\          - AFIO_EMC_GB2_DET   
 *\*\          - AFIO_EMC_GB3_DET   
 *\*\          - AFIO_EMC_GB4_DET   
 *\*\param  cmd :
 *\*\          - DISABLE
 *\*\          - ENABLE
 *\*\return none
 */
void AFIO_Config_EMC_Funtion(uint32_t EMC_fun, FunctionalState cmd)
{
    if(cmd != DISABLE)
    {
        AFIO->EMC_CFG |= EMC_fun;
    }
    else
    {
        AFIO->EMC_CFG &= ~EMC_fun;
    }
}

/**
 *\*\name   AFIO_Set_EMC_Cnt.
 *\*\fun    Set the EMC counter value.
 *\*\param  cnt : 
 *\*\        - 0~1023
 *\*\return none
 */
void AFIO_Set_EMC_Cnt(uint32_t cnt)
{
    uint32_t tempReg;

    tempReg  = AFIO->EMC_CNT;
    tempReg &= (~AFIO_EMC_CNT_EMC_CNT);
    tempReg |= cnt;
    AFIO->EMC_CNT = tempReg;
}

/**
 *\*\name   AFIO_Get_EMC_Cnt.
 *\*\fun    Get the EMC counter value.
 *\*\param  none 
 *\*\return Current counter value.
 */
uint32_t AFIO_Get_EMC_Cnt(void)
{
    return (AFIO->EMC_CNT & AFIO_EMC_CNT_EMC_CNT);
}


