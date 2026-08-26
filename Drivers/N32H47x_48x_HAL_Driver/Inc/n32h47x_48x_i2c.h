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
*\*\file n32h47x_48x_i2c.h
*\*\author Nations 
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/
#ifndef __n32h47x_48x_I2C_H__
#define __n32h47x_48x_I2C_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32h47x_48x.h"

/**  n32h47x_48x_StdPeriph_Driver **/

/** I2C Init structure definition **/

typedef struct
{
    uint32_t ClkSpeed; /*!< Specifies the clock frequency.
                                  This parameter must be set to a value lower than 400kHz */

    uint16_t BusMode; /*!< Specifies the I2C mode.
                            This parameter can be a value of @ref I2C_BusMode */

    uint16_t FmDutyCycle; /*!< Specifies the I2C fast mode duty cycle.
                                 This parameter can be a value of @ref I2C_duty_cycle_in_fast_mode */

    uint16_t OwnAddr1; /*!< Specifies the first device own address.
                                   This parameter can be a 7-bit or 10-bit address. */

    uint16_t AckEnable; /*!< Enables or disables the acknowledgement.
                           This parameter can be a value of @ref I2C_acknowledgement */

    uint16_t AddrMode; /*!< Specifies if 7-bit or 10-bit address is acknowledged.
                                           This parameter can be a value of @ref I2C_acknowledged_address */
} I2C_InitType;


/*========================================Below is for analouge and digital filter function==========================================*/

/** I2C Private Defines **/

/** I2C SPE mask **/
#define CTRL1_SPEN_SET   ((uint32_t)0x0001U)
#define CTRL1_SPEN_RESET ((uint32_t)0xFFFEU)

/** I2C START mask **/
#define CTRL1_START_SET   ((uint16_t)0x0080U)
#define CTRL1_START_RESET ((uint16_t)0xFF7FU)

/** I2C STOP mask **/
#define CTRL1_STOP_SET   ((uint16_t)0x0100U)
#define CTRL1_STOP_RESET ((uint16_t)0xFEFFU)

/** I2C ACK mask **/
#define CTRL1_ACK_SET   ((uint16_t)0x0200U)
#define CTRL1_ACK_RESET ((uint16_t)0xFDFFU)

/** I2C ENGC mask **/
#define CTRL1_GCEN_SET   ((uint16_t)0x0020U)
#define CTRL1_GCEN_RESET ((uint16_t)0xFFDFU)

/** I2C SWRST mask **/
#define CTRL1_SWRESET_SET   ((uint16_t)0x2000U)
#define CTRL1_SWRESET_RESET ((uint16_t)0xDFFFU)

/** I2C PEC mask **/
#define CTRL1_PEC_SET   ((uint16_t)0x0800U)
#define CTRL1_PEC_RESET ((uint16_t)0xF7FFU)

/** I2C ENPEC mask **/
#define CTRL1_PECEN_SET   ((uint16_t)0x0010U)
#define CTRL1_PECEN_RESET ((uint16_t)0xFFEFU)

/** I2C ENARP mask **/
#define CTRL1_ARPEN_SET   ((uint16_t)0x0008U)
#define CTRL1_ARPEN_RESET ((uint16_t)0xFFF7U)

/** I2C NOSTRETCH mask **/
#define CTRL1_NOEXTEND_SET   ((uint16_t)0x0040U)
#define CTRL1_NOEXTEND_RESET ((uint16_t)0xFFBFU)

/** I2C FIFOEN mask **/
#define CTRL1_FIFOEN_SET     ((uint32_t)0x00010000U)
#define CTRL1_FIFOEN_RESET   ((uint32_t)0xFFFEFFFFU)
/* I2C CLR mask */
#define CTRL1_CLR_SET        ((uint32_t)0x00020000U)
#define CTRL1_CLR_RESET      ((uint32_t)0xFFFDFFFFU)

/** I2C FIFOCLR mask **/
#define CTRL1_FIFOCLR_SET      ((uint32_t)0x00020000U)
#define CTRL1_FIFOCLR_RESET    ((uint32_t)0xFFFDFFFFU)

/** I2C registers Masks **/
#define I2C_CTRL1_CLR_MASK			 ((uint16_t)0xFDF9U)

/* I2C CLR TX FIFO Threshold Mask */
#define CTRL1_TXFT_Mask          	((uint32_t)0xF8FFFFFF)
/* I2C CLR RX FIFO Threshold Mask */
#define CTRL1_RXFT_Mask          	((uint32_t)0xFF8FFFFF)

/** I2C DMAEN mask **/
#define CTRL2_DMAEN_SET   ((uint16_t)0x8000U)
#define CTRL2_DMAEN_RESET ((uint16_t)0x7FFFU)

/** I2C DMA_FIFO_EN mask **/
#define CTRL2_DMAFIFOEN_SET   ((uint32_t)0x00800000U)
#define CTRL2_DMAFIFOEN_RESET ((uint32_t)0xFF7FFFFFU)

/** I2C TIMEOUT_EN mask **/
#define CTRL2_LOWTMEN_SET   ((uint32_t)0x40000000U)
#define CTRL2_LOWTMEN_RESET ((uint32_t)0xBFFFFFFFU)

#define CTRL2_HIGHTMEN_SET   ((uint32_t)0x20000000U)
#define CTRL2_HIGHTMEN_RESET ((uint32_t)0xDFFFFFFFU)

/** I2C LAST mask **/
#define CTRL2_DMALAST_SET   ((uint16_t)0x0100U)
#define CTRL2_DMALAST_RESET ((uint16_t)0xFEFFU)

/** I2C FREQ mask **/
#define CTRL2_CLKFREQ_RESET ((uint16_t)0xFF00U)

/** I2C ADD0 mask **/
#define OADDR1_ADDR0_SET   ((uint16_t)0x0001U)
#define OADDR1_ADDR0_RESET ((uint16_t)0xFFFEU)

/** I2C ENDUAL mask **/
#define OADDR2_DUALEN_SET   ((uint16_t)0x0001U)
#define OADDR2_DUALEN_RESET ((uint16_t)0xFFFEU)

/** I2C ADD2 mask **/
#define OADDR2_ADDR2_RESET ((uint16_t)0xFF01U)

/** I2C F/S mask **/
#define CLKCTRL_FSMODE_SET ((uint16_t)0x4000U)

/** I2C CHCFG mask **/
#define CLKCTRL_CLKCTRL_SET ((uint16_t)0x0FFFU)

/** I2C FLAG mask **/
#define FLAG_MASK 					((uint32_t)0x03FFFFFFU)

/** I2C Interrupt Enable mask **/
#define INTEN_MASK 					((uint32_t)0x70000000U)

/** I2C Analogue Filter SCL Disenable Mask **/
#define I2C_TMRISE_SCL_AFC_OFF     ((uint32_t)0x00008000U)

/** I2C Analogue Filter SDA Disenable Mask **/
#define I2C_TMRISE_SDA_AFC_OFF     ((uint32_t)0x00000800U)

/** I2C Analogue Filter SCL Width Mask **/
#define SCL_AFC_Mask               ((uint32_t)0x00003000U)

/** I2C Analogue Filter SDA Width Mask **/
#define SDA_AFC_Mask               ((uint32_t)0x00000300U)

/** I2C Digital Filter SCL Width Mask **/
#define SCL_DGC_Mask               ((uint32_t)0x000000F0U)

/** I2C Digital Filter SDA Width Mask **/
#define SDA_DGC_Mask               ((uint32_t)0x0000000FU)

/** I2C BYTENUM mask **/
#define BYTENUM_BTNUMEN_SET     ((uint32_t)0x00008000U)
#define BYTENUM_BTNUMEN_RESET   ((uint32_t)0xFFFF7FFFU)

#define RESTART_PROCESS				((uint32_t)0x00004000U)
#define STOP_PROCESS				((uint32_t)0x00000000U)

/* I2C BYTENUM byte number mask */
#define BYTENUM_Mask              ((uint16_t)0x3FFF)

/* I2C BYTENUM last status mask */
#define BYTENUM_STATUS_Mask		 		((uint16_t)0x4000U)

/** I2C Analog filter mask **/
#define SCL_AFE_SET     ((uint32_t)0x00008000U)
#define SCL_AFE_RESET   ((uint32_t)0xFFFF7FFFU)

#define SDA_AFE_SET     ((uint32_t)0x00000800U)
#define SDA_AFE_RESET   ((uint32_t)0xFFFFF7FFU)

/* I2C GFLTRCTRL mask */
#define I2C_SDADFW_MASK  ((uint32_t)0xFFFFFFF0U)
#define I2C_SCLDFW_MASK  ((uint32_t)0xFFFFFF0FU)
#define I2C_SDAAFW_MASK  ((uint32_t)0xFFFFFCFFU)
#define I2C_SCLAFW_MASK  ((uint32_t)0xFFFFCFFFU)	
			

/** I2C Analogue Filter Width **/

#define I2C_ANALOG_FILTER_WIDTH_5NS    ((uint32_t)0x00000000U)		
#define I2C_ANALOG_FILTER_WIDTH_15NS   ((uint32_t)0x00000100U)			
#define I2C_ANALOG_FILTER_WIDTH_25NS   ((uint32_t)0x00000200U)		
#define I2C_ANALOG_FILTER_WIDTH_35NS   ((uint32_t)0x00000300U)
			
/*===================================================================================================================================*/		


/** I2C_BusMode **/

#define I2C_BUSMODE_I2C       ((uint16_t)0x0000U)
#define I2C_BUSMODE_SMBDEVICE ((uint16_t)0x0002U)
#define I2C_BUSMODE_SMBHOST   ((uint16_t)0x0006U)

/** I2C_duty_cycle_in_fast_mode **/

#define I2C_FMDUTYCYCLE_16_9        ((uint16_t)0x8000U) /*!< I2C fast mode Tlow/Thigh = 16/9 */
#define I2C_FMDUTYCYCLE_2           ((uint16_t)0x7FFFU) /*!< I2C fast mode Tlow/Thigh = 2 */

/** I2C_acknowledgement **/

#define I2C_ACKEN               ((uint16_t)0x0200U)
#define I2C_ACKDIS              ((uint16_t)0x0000U)

/** I2C_transfer_direction **/

#define I2C_DIRECTION_SEND          ((uint8_t)0x00U)
#define I2C_DIRECTION_RECV          ((uint8_t)0x01U)

/** I2C_acknowledged_address **/

#define I2C_ADDR_MODE_7BIT        ((uint16_t)0x0000U)
#define I2C_ADDR_MODE_10BIT       ((uint16_t)0x8000U)

/** I2C_registers **/

#define I2C_REG_CTRL1   				((uint8_t)0x00U)
#define I2C_REG_CTRL2   				((uint8_t)0x04U)
#define I2C_REG_OADDR1  				((uint8_t)0x08U)
#define I2C_REG_OADDR2  				((uint8_t)0x0CU)
#define I2C_REG_DAT     				((uint8_t)0x10U)
#define I2C_REG_STS1    				((uint8_t)0x14U)
#define I2C_REG_STS2   				    ((uint8_t)0x18U)
#define I2C_REG_CLKCTRL 				((uint8_t)0x1CU)
#define I2C_REG_TMRISE  				((uint8_t)0x20U)
#define I2C_REG_BYTENUM    		    	((uint8_t)0x24U)
#define I2C_REG_GFLTRCTRL  		    	((uint8_t)0x28U)
#define I2C_REG_FIFODAT  				((uint8_t)0x2CU)

/** I2C_SMBus_alert_pin_level **/
#define I2C_SMBALERT_LOW        ((uint16_t)0x1000U)
#define I2C_SMBALERT_HIGH       ((uint16_t)0xEFFFU)

/** I2C_PEC_position **/

#define I2C_PEC_POS_NEXT         ((uint16_t)0x0400U)
#define I2C_PEC_POS_CURRENT      ((uint16_t)0xFBFFU)

/** I2C_NCAK_position **/

#define I2C_NACK_POS_NEXT         ((uint16_t)0x0400U)
#define I2C_NACK_POS_CURRENT      ((uint16_t)0xFBFFU)

/** I2C_interrupts_definition **/

#define I2C_INT_BUF        		  ((uint32_t)0x00001000U)
#define I2C_INT_EVENT      		  ((uint32_t)0x00002000U)
#define I2C_INT_ERR        		  ((uint32_t)0x00004000U)
#define I2C_INT_FIFOF    		  ((uint32_t)0x00010000U) /* FIFO full interrupt enable */
#define I2C_INT_FIFOE    		  ((uint32_t)0x00020000U) /* FIFO empty interrupt enable */
#define I2C_INT_FIFOHF    		  ((uint32_t)0x00040000U) /* FIFOHF interrupt enable, when fifo enable */
#define I2C_INT_FIFOHE    		  ((uint32_t)0x00080000U) /* FIFOHE interrupt enable,when fifo enable */
#define I2C_INT_FIFORDEIEN        ((uint32_t)0x00100000U) /* FIFORDEIEN interrupt enable,when fifo enable */
#define I2C_INT_FIFOWREIEN		  ((uint32_t)0x00200000U) /* FIFOWREIEN interrupt enable,when fifo enable */
#define I2C_INT_DMAETOEIEN        ((uint32_t)0x00400000U) /* DMAETOEIEN interrupt enable,when fifo enable */
#define I2C_INT_FIFONE		      ((uint32_t)0x01000000U) /* FIFO not empty interrupt enable */
#define I2C_INT_FIFONF		      ((uint32_t)0x02000000U) /* FIFO not full interrupt enable */
#define I2C_INT_SDATOLIEN		  ((uint32_t)0x04000000U) /* SDA low timeout interrupt enable */
#define I2C_INT_SCLTOHIEN		  ((uint32_t)0x08000000U) /* SCL high timeout interrupt enable */
#define I2C_INT_SCLTOLIEN		  ((uint32_t)0x10000000U) /* SCL low timeout interrupt enable */

/** I2C_interrupts_definition **/

#define I2C_INT_STARTBF  				((uint32_t)0x00000001U) /* Start Bit (Master mode) */
#define I2C_INT_ADDRF    				((uint32_t)0x00000002U) /* Address sent (master mode)/matched (slave mode) */
#define I2C_INT_BSF      				((uint32_t)0x00000004U) /* Byte Transfer Finished */
#define I2C_INT_STOPF    				((uint32_t)0x00000008U) /* Stop detection (Slave mode) */
#define I2C_INT_RXDATNE  				((uint32_t)0x00000010U) /* Data Register not Empty (receivers) */
#define I2C_INT_TXDATE   				((uint32_t)0x00000020U) /* Data Register Empty (transmitters) */
#define I2C_INT_ADDR10F  				((uint32_t)0x00000040U) /* 10-bit header sent (Master mode) */
#define I2C_INT_ACKFAIL  				((uint32_t)0x00000100U) /* Acknowledge Failure */
#define I2C_INT_ARLOST   				((uint32_t)0x00000200U) /* Arbitration Lost (master mode) */
#define I2C_INT_BUSERR   				((uint32_t)0x00000400U) /* Bus Error */
#define I2C_INT_OVERRUN  				((uint32_t)0x00000800U) /* Overrun/Underrun */
#define I2C_INT_PECERR   				((uint32_t)0x00001000U) /* PEC Error in reception */
#define I2C_INT_SMBALERT 				((uint32_t)0x00004000U) /* SMBus Alert */
#define I2C_INT_FIFOF 					((uint32_t)0x00010000U) /* FIFO full */
#define I2C_INT_FIFOE 					((uint32_t)0x00020000U) /* FIFO empty */
#define I2C_INT_FIFOHF 					((uint32_t)0x00040000U) /* FIFO half full */
#define I2C_INT_FIFOHE 					((uint32_t)0x00080000U) /* FIFO half empty */
#define I2C_INT_FIFORDERR 			    ((uint32_t)0x00100000U) /* Read data when FIFO is empty */
#define I2C_INT_FIFOWRERR 			    ((uint32_t)0x00200000U) /* Write data when FIFO is full */
#define I2C_INT_DMAETOERR 			    ((uint32_t)0x00400000U) /* Prove that the DMA transmission is complete but no ETO signal is given */
#define I2C_INT_SDALTO 	    		    ((uint32_t)0x00800000U) /* SDA timeout low error */
#define I2C_INT_SCLHTO      		    ((uint32_t)0x01000000U) /* SCL timeout high error */
#define I2C_INT_SCLLTO 	    		    ((uint32_t)0x02000000U) /* SCL timeout low error */

/** I2C_flags_definition **/

/** STS2 register flags **/

#define I2C_FLAG_SMBHADDR  ((uint32_t)0x00800000U)
#define I2C_FLAG_SMBDADDR  ((uint32_t)0x00400000U)
#define I2C_FLAG_DUALFLAG  ((uint32_t)0x00200000U)
#define I2C_FLAG_GCALLADDR ((uint32_t)0x00100000U)
#define I2C_FLAG_TRF       ((uint32_t)0x00040000U)
#define I2C_FLAG_MSMODE    ((uint32_t)0x00020000U)
#define I2C_FLAG_BUSY      ((uint32_t)0x00010000U)

/** STS1 register flags **/

#define I2C_FLAG_SCLLTO     				((uint32_t)0x12000000U)	  
#define I2C_FLAG_SCLHTO    					((uint32_t)0x11000000U)	  
#define I2C_FLAG_SDALTO     				((uint32_t)0x10800000U)
#define I2C_FLAG_DMAETOERR					((uint32_t)0x10400000U)
#define I2C_FLAG_FIFOWRERR					((uint32_t)0x10200000U)
#define I2C_FLAG_FIFORDERR					((uint32_t)0x10100000U)
#define I2C_FLAG_FIFOHE						((uint32_t)0x10080000U)
#define I2C_FLAG_FIFOHF						((uint32_t)0x10040000U)
#define I2C_FLAG_FIFOE						((uint32_t)0x10020000U)
#define I2C_FLAG_FIFOF						((uint32_t)0x10010000U)
#define I2C_FLAG_SMBALERT 					((uint32_t)0x10004000U)
#define I2C_FLAG_PECERR   					((uint32_t)0x10001000U)
#define I2C_FLAG_OVERRUN  					((uint32_t)0x10000800U)
#define I2C_FLAG_BUSERR   					((uint32_t)0x10000400U)
#define I2C_FLAG_ARLOST   					((uint32_t)0x10000200U)
#define I2C_FLAG_ACKFAIL					((uint32_t)0x10000100U)
#define I2C_FLAG_ADDR10F  					((uint32_t)0x10000040U)
#define I2C_FLAG_TXDATE   					((uint32_t)0x10000020U)
#define I2C_FLAG_RXDATNE  					((uint32_t)0x10000010U)
#define I2C_FLAG_STOPF    					((uint32_t)0x10000008U)
#define I2C_FLAG_BSF     	 				((uint32_t)0x10000004U)
#define I2C_FLAG_ADDRF    					((uint32_t)0x10000002U)
#define I2C_FLAG_STARTBF  					((uint32_t)0x10000001U)

/***  I2C_Events ***/

/** I2C Master Events (Events grouped in order of communication) **/
/**
*\*\brief  Communication start
*\*\       After sending the START condition (I2C_GenerateStart() function) the master
*\*\       has to wait for this event. It means that the Start condition has been correctly
*\*\       released on the I2C bus (the bus is free, no other devices is communicating).
**/

/* Master mode */
#define I2C_ROLE_MASTER ((uint32_t)0x00020000U) /* MSMODE */
/* --EV5 */
#define I2C_EVT_MASTER_MODE_FLAG ((uint32_t)0x00030001U) /* BUSY, MSMODE and STARTBF flag */
/* --EV5_FIFO */
#define  I2C_EVENT_MASTER_FIFO_MODE_SELECT                 ((uint32_t)0x03000001)  /* BUSY, MSL and SB flag */
/**
*\*\brief  Address Acknowledge
*\*\       After checking on EV5 (start condition correctly released on the bus), the
*\*\       master sends the address of the slave(s) with which it will communicate
*\*\       (I2C_SendAddr7bit() function, it also determines the direction of the communication:
*\*\       Master transmitter or Receiver). Then the master has to wait that a slave acknowledges
*\*\       his address. If an acknowledge is sent on the bus, one of the following events will
*\*\       be set:
*\*\       1) In case of Master Receiver (7-bit addressing): the I2C_EVT_MASTER_RXMODE_FLAG
*\*\       event is set.
*\*\       2) In case of Master Transmitter (7-bit addressing): the I2C_EVT_MASTER_TXMODE_FLAG
*\*\       is set
*\*\       3) In case of 10-Bit addressing mode, the master (just after generating the START
*\*\       and checking on EV5) has to send the header of 10-bit addressing mode (I2C_SendData()
*\*\       function). Then master should wait on EV9. It means that the 10-bit addressing
*\*\       header has been correctly sent on the bus. Then master should send the second part of
*\*\       the 10-bit address (LSB) using the function I2C_SendAddr7bit(). Then master
*\*\       should wait for event EV6.
**/

/* --EV6 */
#define I2C_EVT_MASTER_TXMODE_FLAG ((uint32_t)0x00070022U) /* BUSY, MSMODE, ADDRF, TXDATE and TRF flags */
#define I2C_EVT_MASTER_RXMODE_FLAG ((uint32_t)0x00030002U) /* BUSY, MSMODE and ADDRF flags */
/* --EV9 */
#define I2C_EVT_MASTER_MODE_ADDRESS10_FLAG ((uint32_t)0x00030040U) /* BUSY, MSMODE and ADD10RF flags */

/* --EV6_FIFO */
#define  I2C_EVENT_MASTER_FIFO_TRANSMITTER_MODE_SELECTED   ((uint32_t)0x07000002U)  /* BUSY, MSL, ADDR, and TRA flags */
#define  I2C_EVENT_MASTER_FIFO_RECEIVER_MODE_SELECTED      ((uint32_t)0x03000002U)  /* BUSY, MSL and ADDR flags */
/* --EV9_FIFO */
#define  I2C_EVENT_MASTER_FIFO_MODE_ADDRESS10              ((uint32_t)0x03000040U)  /* BUSY, MSL and ADD10 flags */


/**
*\*\brief Communication events
*\*\      If a communication is established (START condition generated and slave address
*\*\      acknowledged) then the master has to check on one of the following events for
*\*\      communication procedures:
*\*\      1) Master Receiver mode: The master has to wait on the event EV7 then to read
*\*\      the data received from the slave (I2C_RecvData() function).
*\*\      2) Master Transmitter mode: The master has to send data (I2C_SendData()
*\*\      function) then to wait on event EV8 or EV8_2.
*\*\      These two events are similar:
*\*\      - EV8 means that the data has been written in the data register and is
*\*\      being shifted out.
*\*\      - EV8_2 means that the data has been physically shifted out and output
*\*\      on the bus.
*\*\      In most cases, using EV8 is sufficient for the application.
*\*\      Using EV8_2 leads to a slower communication but ensure more reliable test.
*\*\      EV8_2 is also more suitable than EV8 for testing on the last data transmission
*\*\      (before Stop condition generation).
*\*\note  In case the  user software does not guarantee that this event EV7 is
*\*\      managed before the current byte end of transfer, then user may check on EV7
*\*\      and BSF flag at the same time (ie. (I2C_EVT_MASTER_DATA_RECVD_FLAG | I2C_FLAG_BYTEF)).
*\*\      In this case the communication may be slower.
**/

/* Master RECEIVER mode -----------------------------*/
/* --EV7 */
#define I2C_EVT_MASTER_DATA_RECVD_FLAG ((uint32_t)0x00030010U) /* BUSY, MSMODE and RXDATNE flags */
/* EV7x shifter register full */
#define I2C_EVT_MASTER_SFT_DATA_RECVD_FLAG ((uint32_t)0x00030014U) /* BUSY, MSMODE, BSF and RXDATNE flags */
/* Master TRANSMITTER mode --------------------------*/
/* --EV8 */
#define I2C_EVT_MASTER_DATA_SENDING ((uint32_t)0x00070020U) /* TRF, BUSY, MSMODE, TXDATE flags */
/* --EV8_2 */
#define I2C_EVT_MASTER_DATA_SENDED ((uint32_t)0x00070024U) /* TRF, BUSY, MSMODE, TXDATE and BSF flags */


/* Master FIFO TRANSMITTER mode --------------------------*/
/* --EV10_FIFO */
#define  I2C_EVENT_MASTER_FIFO_TRANSMITTING   			   ((uint32_t)0x07080000U)  /* TRA, BUSY, MSL, FIFOHE flags */
/* --EV10_FIFO_1 */
#define  I2C_EVENT_MASTER_FIFO_TRANSMITTED                 ((uint32_t)0x000A0004U)  /* FIFOHE, FIFOE, BSF flags */

/* Master FIFO RECEIVER mode -----------------------------*/
/* --EV4_FIFO  */
#define  I2C_EVENT_MASTER_FIFO_STOP_DETECTED                ((uint32_t)0x00000008U)  /* STOPF flag */
/* --EV11_FIFO */
#define  I2C_EVENT_MASTER_FIFO_RECEIVING                    ((uint32_t)0x03040000U)  /* BUSY, MSL and FIFOHF flags */
/* --EV12_FIFO */
#define  I2C_EVENT_MASTER_FIFO_RECEIVED                     ((uint32_t)0x00020000U)  /* FIFOE flags */


/** I2C Slave Events (Events grouped in order of communication)***/

/**
*\*\brief  Communication start events
*\*\       Wait on one of these events at the start of the communication. It means that
*\*\       the I2C peripheral detected a Start condition on the bus (generated by master
*\*\       device) followed by the peripheral address. The peripheral generates an ACK
*\*\       condition on the bus (if the acknowledge feature is enabled through function
*\*\       I2C_ConfigAck()) and the events listed above are set :
*\*\       1) In normal case (only one address managed by the slave), when the address
*\*\       sent by the master matches the own address of the peripheral (configured by
*\*\       OwnAddr1 field) the I2C_EVENT_SLAVE_XXX_ADDRESS_MATCHED event is set
*\*\       (where XXX could be TRANSMITTER or RECEIVER).
*\*\       2) In case the address sent by the master matches the second address of the
*\*\       peripheral (configured by the function I2C_ConfigOwnAddr2() and enabled
*\*\       by the function I2C_EnableDualAddr()) the events I2C_EVENT_SLAVE_XXX_SECONDADDRESS_MATCHED
*\*\       (where XXX could be TRANSMITTER or RECEIVER) are set.
*\*\       3) In case the address sent by the master is General Call (address 0x00) and
*\*\       if the General Call is enabled for the peripheral (using function I2C_EnableGeneralCall())
*\*\       the following event is set I2C_EVT_SLAVE_GCALLADDR_MATCHED.
**/

/* --EV1  (all the events below are variants of EV1) */
/* 1) Case of One Single Address managed by the slave */
#define I2C_EVT_SLAVE_RECV_ADDR_MATCHED					 ((uint32_t)0x00010002U) /* BUSY and ADDRF flags */
#define I2C_EVT_SLAVE_FIFO_RECV_ADDR_MATCHED	   ((uint32_t)0x00010002U) /* BUSY and ADDR flags */
#define I2C_EVT_SLAVE_SEND_ADDR_MATCHED 				 ((uint32_t)0x00050022U) /* TRF, BUSY, TXDATE and ADDRF flags */

/* 2) Case of Dual address managed by the slave */
#define I2C_EVT_SLAVE_RECV_ADDR2_MATCHED 					((uint32_t)0x00210000U) /* DUALF and BUSY flags */
#define I2C_EVT_SLAVE_SEND_ADDR2_MATCHED 					((uint32_t)0x00250020U) /* DUALF, TRF, BUSY and TXDATE flags */

/* 3) Case of General Call enabled for the slave */
#define I2C_EVT_SLAVE_GCALLADDR_MATCHED						((uint32_t)0x00110000U) /* GENCALL and BUSY flags */

/* --EV1_FIFO*/
/* 1) Case of One Single Address managed by the slave fifo mode */
#define  I2C_EVENT_SLAVE_FIFO_RECEIVER_ADDRESS_MATCHED     				((uint32_t)0x01000002U) /* BUSY and ADDR flags */
#define  I2C_EVENT_SLAVE_FIFO_TRANSMITTER_ADDRESS_MATCHED       		((uint32_t)0x05000002U) /* TRA, BUSY, and ADDR flags */


/* 2) Case of Dual address managed by the slave fifo mode*/
#define  I2C_EVENT_SLAVE_FIFO_RECEIVER_SECONDADDRESS_MATCHED    		((uint32_t)0x21000000U)  /* DUALF and BUSY flags */
#define  I2C_EVENT_SLAVE_FIFO_TRANSMITTER_SECONDADDRESS_MATCHED 		((uint32_t)0x25000000U)  /* DUALF, TRA, BUSY and flags */

/* 3) Case of General Call enabled for the slave fifo mode*/
#define  I2C_EVENT_SLAVE_FIFO_GENERALCALLADDRESS_MATCHED        		((uint32_t)0x11000000U)  /* GENCALL and BUSY flags */

/**
*\*\brief  Communication events
*\*\       Wait on one of these events when EV1 has already been checked and:
*\*\       - Slave RECEIVER mode:
*\*\       - EV2: When the application is expecting a data byte to be received.
*\*\       - EV4: When the application is expecting the end of the communication: master
*\*\       sends a stop condition and data transmission is stopped.
*\*\       - Slave Transmitter mode:
*\*\       - EV3: When a byte has been transmitted by the slave and the application is expecting
*\*\       the end of the byte transmission. The two events I2C_EVT_SLAVE_DATA_SENDED and
*\*\       I2C_EVT_SLAVE_DATA_SENDING are similar. The second one can optionally be
*\*\       used when the user software doesn't guarantee the EV3 is managed before the
*\*\       current byte end of transfer.
*\*\       - EV3_2: When the master sends a NACK in order to tell slave that data transmission
*\*\       shall end (before sending the STOP condition). In this case slave has to stop sending
*\*\       data bytes and expect a Stop condition on the bus.
*\*\note   In case the  user software does not guarantee that the event EV2 is
*\*\       managed before the current byte end of transfer, then user may check on EV2
*\*\       and BSF flag at the same time (ie. (I2C_EVT_SLAVE_DATA_RECVD | I2C_FLAG_BYTEF)).
*\*\       In this case the communication may be slower.
**/

/* Slave RECEIVER mode --------------------------*/
/* --EV2 */
#define I2C_EVT_SLAVE_DATA_RECVD ((uint32_t)0x00010010U) /* BUSY and RXDATNE flags */
/* --EV2x */
#define I2C_EVT_SLAVE_DATA_RECVD_NOBUSY ((uint32_t)0x00000010U) /* no BUSY and RXDATNE flags */
/* --EV4  */
#define I2C_EVT_SLAVE_STOP_RECVD ((uint32_t)0x00000008U) /* STOPF flag */

/* Slave TRANSMITTER mode -----------------------*/
/* --EV3 */
#define I2C_EVT_SLAVE_DATA_SENDED  ((uint32_t)0x00050024U) /* TRF, BUSY, TXDATE and BSF flags */
#define I2C_EVT_SLAVE_DATA_SENDING ((uint32_t)0x00050020U) /* TRF, BUSY and TXDATE flags */
/* --EV3_2 */
#define I2C_EVT_SLAVE_ACK_MISS ((uint32_t)0x00000100U) /* AF flag */

/* Slave FIFO RECEIVER mode --------------------------*/
/* --EV4_FIFO  */
#define  I2C_EVENT_SLAVE_FIFO_STOP_DETECTED                ((uint32_t)0x00000008U)  /* STOPF flag */
/* --EV11_FIFO */
#define  I2C_EVENT_SLAVE_FIFO_RECEIVING                    ((uint32_t)0x01040000U)  /* BUSY and FIFOHF flags */
/* --EV12_FIFO */
#define  I2C_EVENT_SLAVE_FIFO_RECEIVED                     ((uint32_t)0x00020000U)  /* FIFOE flags */

/* Slave FIFO TRANSMITTER mode --------------------------*/
/* --EV10_FIFO */
#define  I2C_EVENT_SLAVE_FIFO_TRANSMITTING   			   ((uint32_t)0x05080000U)  /* TRA, BUSY and FIFOHE flags */
/* --EV3_2_FIFO */
#define  I2C_EVENT_SLAVE_FIFO_ACK_FAILURE                  ((uint32_t)0x000A0100U)  /* FIFOHE, FIFOE and AF flag */

/** I2C_own_address1 **/

#define IS_I2C_OWN_ADDR1(ADDRESS1) ((ADDRESS1) <= 0x3FF)


/** I2C_clock_speed **/

#define IS_I2C_CLK_SPEED(SPEED) (((SPEED) >= 0x1) && ((SPEED) <= 1000000))


/** I2C_Exported_Macros **/

/** I2C_Exported_Functions **/

void I2C_DeInit(const I2C_Module* I2Cx);
void I2C_Init( I2C_Module* I2Cx,const I2C_InitType* I2C_InitStruct);
void I2C_InitStruct(I2C_InitType* I2C_InitStruct);
void I2C_Enable(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_EnableDMA(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_EnableDmaLastSend(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_GenerateStart(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_GenerateStop(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_ConfigAck(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_ConfigOwnAddr2(I2C_Module* I2Cx, uint8_t Address);
void I2C_EnableDualAddr(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_EnableGeneralCall(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_ConfigInt(I2C_Module* I2Cx, uint32_t I2C_IT, FunctionalState Cmd);
void I2C_SendData(I2C_Module* I2Cx, uint8_t Data);
uint8_t I2C_RecvData(const I2C_Module* I2Cx);
void I2C_SendAddr7bit(I2C_Module* I2Cx, uint8_t Address, uint8_t I2C_Direction);
void I2C_EnableSoftwareReset(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_ConfigNackLocation(I2C_Module* I2Cx, uint16_t I2C_NACKPosition);
void I2C_ConfigSmbusAlert(I2C_Module* I2Cx, uint16_t I2C_SMBusAlert);
void I2C_SendPEC(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_ConfigPecLocation(I2C_Module* I2Cx, uint16_t I2C_PECPosition);
void I2C_ComputePec(I2C_Module* I2Cx, FunctionalState Cmd);
uint8_t I2C_GetPec(const I2C_Module* I2Cx);
void I2C_EnableArp(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_EnableExtendClk(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_ConfigFastModeDutyCycle(I2C_Module* I2Cx, uint16_t FmDutyCycle);
uint16_t I2C_GetRegister(const I2C_Module* I2Cx, uint8_t I2C_Register);
ErrorStatus I2C_CheckFifoEvent(I2C_Module* I2Cx, uint32_t I2C_FIFO_EVENT);
uint32_t I2C_GetLastFifoEvent(I2C_Module* I2Cx);	
void I2C_ClrFIFO(I2C_Module* I2Cx);
void I2C_EnableFIFO(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_EnableDMAFIFO(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_EnableBYTENUM(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_SetByteNumLastStartStop(I2C_Module* I2Cx, uint16_t LastStatus);
void I2C_SetReceivedDataBytesNum(I2C_Module* I2Cx, uint16_t Number_Of_bytes);
void I2C_SetTxFifoThreshold( I2C_Module* I2Cx, uint8_t TxFifoThreshold );
void I2C_SetRxFifoThreshold( I2C_Module* I2Cx, uint8_t RxFifoThreshold );
void I2C_SetFIFODAT(I2C_Module* I2Cx, uint32_t I2C_BYTENUM);
uint8_t I2C_GetFIFODAT(const I2C_Module* I2Cx);
void I2C_EnableLowTimeout(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_EnableHighTimeout(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_EnableSCLAnalogFilter(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_EnableSDAAnalogFilter(I2C_Module* I2Cx, FunctionalState Cmd);
void I2C_SetSCLAnalogFilterWidth(I2C_Module* I2Cx, uint32_t width);
void I2C_SetSDAAnalogFilterWidth(I2C_Module* I2Cx, uint32_t width);
void I2C_SetSDADigitalFilterWidth(I2C_Module* I2Cx, uint32_t width);
void I2C_SetSCLDigitalFilterWidth(I2C_Module* I2Cx, uint32_t width);

/**
*\*\brief  I2C State Monitoring Functions
*\*\       This I2C driver provides three different ways for I2C state monitoring
*\*\       depending on the application requirements and constraints:
*\*\     1) Basic state monitoring:
*\*\       Using I2C_CheckEvent() function:
*\*\       It compares the status registers (STS1 and STS2) content to a given event
*\*\       (can be the combination of one or more flags).
*\*\       It returns SUCCESS if the current status includes the given flags
*\*\       and returns ERROR if one or more flags are missing in the current status.
*\*\       - When to use:
*\*\         - This function is suitable for most applications as well as for startup
*\*\         activity since the events are fully described in the product reference manual
*\*\         (RM0008).
*\*\         - It is also suitable for users who need to define their own events.
*\*\       - Limitations:
*\*\         - If an error occurs (ie. error flags are set besides to the monitored flags),
*\*\           the I2C_CheckEvent() function may return SUCCESS despite the communication
*\*\           hold or corrupted real state.
*\*\           In this case, it is advised to use error interrupts to monitor the error
*\*\           events and handle them in the interrupt IRQ handler.
*\*\note       For error management, it is advised to use the following functions:
*\*\            - I2C_ConfigInt() to configure and enable the error interrupts (I2C_INT_ERR).
*\*\            - I2Cx_ER_IRQHandler() which is called when the error interrupt occurs.
*\*\              Where x is the peripheral instance (I2C1, I2C2 ...)
*\*\            - I2C_GetFlag() or I2C_GetIntStatus() to be called into I2Cx_ER_IRQHandler()
*\*\              in order to determine which error occurred.
*\*\              and/or I2C_GenerateStop() in order to clear the error flag and source,
*\*\              and return to correct communication status.
*\*\     2) Advanced state monitoring:
*\*\       Using the function I2C_GetLastEvent() which returns the image of both status
*\*\       registers in a single word (uint32_t) (Status Register 2 value is shifted left
*\*\       by 16 bits and concatenated to Status Register 1).
*\*\       - When to use:
*\*\         - This function is suitable for the same applications above but it allows to
*\*\           overcome the limitations of I2C_GetFlag() function (see below).
*\*\           The returned value could be compared to events already defined in the
*\*\           library (n32h47x_48x_i2c.h) or to custom values defined by user.
*\*\         - This function is suitable when multiple flags are monitored at the same time.
*\*\         - At the opposite of I2C_CheckEvent() function, this function allows user to
*\*\         choose when an event is accepted (when all events flags are set and no
*\*\         other flags are set or just when the needed flags are set like
*\*\         I2C_CheckEvent() function).
*\*\       - Limitations:
*\*\         - User may need to define his own events.
*\*\         - Same remark concerning the error management is applicable for this
*\*\           function if user decides to check only regular communication flags (and
*\*\           ignores error flags).
*\*\     3) Flag-based state monitoring:
*\*\       Using the function I2C_GetFlag() which simply returns the status of
*\*\       one single flag (ie. I2C_FLAG_RXDATNE ...).
*\*\       - When to use:
*\*\         - This function could be used for specific applications or in debug phase.
*\*\         - It is suitable when only one flag checking is needed (most I2C events
*\*\           are monitored through multiple flags).
*\*\       - Limitations:
*\*\         - When calling this function, the Status register is accessed. Some flags are
*\*\           cleared when the status register is accessed. So checking the status
*\*\           of one Flag, may clear other ones.
*\*\         - Function may need to be called twice or more in order to monitor one
*\*\           single event.
**/

/** 1) Basic state monitoring **/
ErrorStatus I2C_CheckEvent(const I2C_Module* I2Cx, uint32_t I2C_EVENT);
/** 2) Advanced state monitoring **/
uint32_t I2C_GetLastEvent(const I2C_Module* I2Cx);
/** 3) Flag-based state monitoring **/
FlagStatus I2C_GetFlag(const I2C_Module* I2Cx, uint32_t I2C_FLAG);



void I2C_ClrFlag(I2C_Module* I2Cx, uint32_t I2C_FLAG);
INTStatus I2C_GetIntStatus(const I2C_Module* I2Cx, uint32_t I2C_IT);
void I2C_ClrIntPendingBit(I2C_Module* I2Cx, uint32_t I2C_IT);

#ifdef __cplusplus
}
#endif

#endif /*__n32h47x_48x_I2C_H */

