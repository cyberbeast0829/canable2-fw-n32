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
*\*\file n32h47x_48x_dvp.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/

#include "n32h47x_48x_dvp.h"
#include "n32h47x_48x_rcc.h"


/**
*\*\name    DVP_EnablePort.
*\*\fun     DVP interface enable. This function is called after DVP
*\*\        initialization is successful to start moving data.
*\*\param  Cmd:(The input parameters must be the following values)
*\*\            - ENABLE
*\*\            - DISABLE 
*\*\return  none
**/   
void DVP_EnablePort(FunctionalState Cmd)
{
    
  if (Cmd != DISABLE)
  {
    /* Enable the DVP by setting ENABLE bit */
    DVP->CTRL |= DVP_ENABLE;
  }
  else
  {
    /* Disable the DVP by clearing ENABLE bit */
    DVP->INTSTS |= DVP_DISABLE;
  }
  
}

/**
*\*\name    DVP_SetCaptureMode.
*\*\fun     Config the capture mode. 
*\*\param  Mode:(The input parameters must be the following values)
*\*\            - DVP_CAPTURE_MODE_CONTINUE
*\*\            - DVP_CAPTURE_MODE_SINGLE 
*\*\return  none
**/ 
void DVP_SetCaptureMode(uint32_t Mode)
{ 
   
  if (Mode != DVP_CAPTURE_MODE_CONTINUE)
  {
    /* Enable the DVP single capture mode*/
    DVP->CTRL |= DVP_CAPTURE_MODE_SINGLE;
  }
  else
  {
    /* Enables the DVP continue capture mode */
    DVP->CTRL &= DVP_CAPTURE_MODE_MASK;
  }
  
}

/**
*\*\name    DVP_EnableCrop.
*\*\fun     DVP crop feature enable. This function should be called 
*\*\        before to enable and start the DVP interface.
*\*\param  Cmd:(The input parameters must be the following values)
*\*\            - ENABLE
*\*\            - DISABLE 
*\*\return  none
**/    
void DVP_EnableCrop(FunctionalState Cmd)
{

  if (Cmd != DISABLE)
  {
    /* Enable the DVP Crop feature */
    DVP->CTRL |= DVP_CROP_MODE;
  }
  else
  {
    /* Disable the DVP Crop feature */
    DVP->CTRL &= DVP_CROP_MODE_MASK;
  }
  
}

/**
*\*\name    DVP_ConfigVBFLT.
*\*\fun     VSYNC blanking glitch filtering control. This function should be called 
*\*\        before to enable and start the DVP interface.
*\*\param  Filt:(The input parameters must be the following values)
*\*\            - 0~0xF
*\*\return  none
**/     
void DVP_ConfigVBlankFilter(uint8_t Filt)
{
    
    uint32_t tmpregister;    
    tmpregister = DVP->CTRL;
    tmpregister = (uint32_t)(tmpregister & (uint32_t)DVP_VBFLT_MASK);
    tmpregister |= (uint32_t)Filt << 28u;
    DVP->CTRL = tmpregister;
    
}

/**
*\*\name    DVP_ConfigInt.
*\*\fun     DVP interrupts enable. 
*\*\param   DVPInt (The input parameters must be the following values):
*\*\          - DVP_INT_M1S    
*\*\          - DVP_INT_M2S    
*\*\          - DVP_INT_M1TC   
*\*\          - DVP_INT_M2TC   
*\*\          - DVP_INT_FO     
*\*\          - DVP_INT_AHBERR 
*\*\          - DVP_INT_MO     
*\*\          - DVP_INT_SKIP   
*\*\          - DVP_INT_CERR   
*\*\          - DVP_INT_SERR   
*\*\          - DVP_INT_FMS    
*\*\param   Cmd:(The input parameters must be the following values)
*\*\            - ENABLE
*\*\            - DISABLE 
*\*\return  none
**/    
void DVP_ConfigInt(uint32_t DVPInt, FunctionalState Cmd)
{

  if (Cmd != DISABLE)
  {
    /* Enable the Interrupt sources */
    DVP->INTEN |= DVPInt;
  }
  else
  {
    /* Disable the Interrupt sources */
    DVP->INTEN &= ~DVPInt;
  }  
  
}

/**
*\*\name    DVP_GetFlagStatus.
*\*\fun     Get DVP flag status. Checks whether the  DVP interface flag is set or not.
*\*\param   DVP_Flag (The input parameters must be the following values):
*\*\           - DVP_FLAG_M1S    
*\*\           - DVP_FLAG_M2S    
*\*\           - DVP_FLAG_M1TC   
*\*\           - DVP_FLAG_M2TC   
*\*\           - DVP_FLAG_M1FO   
*\*\           - DVP_FLAG_M2FO   
*\*\           - DVP_FLAG_AHBERR1
*\*\           - DVP_FLAG_AHBERR2
*\*\           - DVP_FLAG_M1O    
*\*\           - DVP_FLAG_M2O    
*\*\           - DVP_FLAG_SKIP   
*\*\           - DVP_FLAG_CERR   
*\*\           - DVP_FLAG_SERR   
*\*\           - DVP_FLAG_FMS    
*\*\return  SET or RESET.
**/    
FlagStatus DVP_GetFlagStatus(uint32_t DVP_Flag)
{
    
  FlagStatus bitstatus;
  uint32_t tmpregister;

  tmpregister = DVP->INTSTS;

  if ((tmpregister & DVP_Flag) != (uint32_t)RESET )
  {
    bitstatus = SET;
  }
  else
  {
    bitstatus = RESET;
  }
  /* Return the DVP_Flag status */
  return  bitstatus;
  
}

/**
*\*\name    DVP_ClearFlag.
*\*\fun     Clears DVP flag status. 
*\*\param   DVP_Flag (The input parameters must be the following values):
*\*\           - DVP_FLAG_M1S    
*\*\           - DVP_FLAG_M2S    
*\*\           - DVP_FLAG_M1TC   
*\*\           - DVP_FLAG_M2TC   
*\*\           - DVP_FLAG_M1FO   
*\*\           - DVP_FLAG_M2FO   
*\*\           - DVP_FLAG_AHBERR1
*\*\           - DVP_FLAG_AHBERR2
*\*\           - DVP_FLAG_M1O    
*\*\           - DVP_FLAG_M2O    
*\*\           - DVP_FLAG_SKIP   
*\*\           - DVP_FLAG_CERR   
*\*\           - DVP_FLAG_SERR   
*\*\           - DVP_FLAG_FMS    
*\*\return  none.
**/     
void DVP_ClearFlag(uint32_t DVP_Flag)
{
    
  DVP->INTSTS = DVP_Flag;
  
}

/**
*\*\name    DVP_GetIntStatus.
*\*\fun     Get DVP interrupt status. Checks whether the DVP interrupt has occurred or not.
*\*\param   DVP_Int (The input parameters must be the following values):
*\*\           - DVP_INT_M1S   
*\*\           - DVP_INT_M2S   
*\*\           - DVP_INT_M1TC  
*\*\           - DVP_INT_M2TC  
*\*\           - DVP_INT_FO    
*\*\           - DVP_INT_AHBERR
*\*\           - DVP_INT_MO    
*\*\           - DVP_INT_SKIP  
*\*\           - DVP_INT_CERR  
*\*\           - DVP_INT_SERR  
*\*\           - DVP_INT_FMS   
*\*\return  SET or RESET.
**/    
INTStatus DVP_GetIntStatus(uint32_t DVP_Int)
{
    
  INTStatus bitstatus;
  uint32_t intstatus, enablestatus;
  if(DVP_Int == DVP_INT_FO)
  {
      enablestatus = DVP->INTEN & DVP_Int;   
      intstatus = DVP->INTSTS & (DVP_FLAG_M1FO | DVP_FLAG_M2FO); 
  }
  else if(DVP_Int == DVP_INT_AHBERR)
  {
      enablestatus = DVP->INTEN & DVP_Int;   
      intstatus = DVP->INTSTS & (DVP_FLAG_AHBERR1 | DVP_FLAG_AHBERR2);   
  }
  else if(DVP_Int == DVP_INT_MO)
  {
      enablestatus = DVP->INTEN & DVP_Int;   
      intstatus = DVP->INTSTS & (DVP_FLAG_M1O | DVP_FLAG_M2O);   
  }  
  else
  {
      enablestatus = DVP->INTEN & DVP_Int; 
      intstatus = DVP->INTSTS & DVP_Int; 
  }
  if ((intstatus != (uint32_t)RESET) && (enablestatus != (uint32_t)RESET))
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
*\*\name    DVP_ClrIntPendingBit.
*\*\fun     Clear DVP interrupt status bits.
*\*\param   DVP_Int (The input parameters must be the following values):
*\*\           - DVP_INT_M1S   
*\*\           - DVP_INT_M2S   
*\*\           - DVP_INT_M1TC  
*\*\           - DVP_INT_M2TC  
*\*\           - DVP_INT_FO    
*\*\           - DVP_INT_AHBERR
*\*\           - DVP_INT_MO    
*\*\           - DVP_INT_SKIP  
*\*\           - DVP_INT_CERR  
*\*\           - DVP_INT_SERR  
*\*\           - DVP_INT_FMS
*\*\return  none.
**/  
void DVP_ClrIntPendingBit(uint32_t DVP_Int)
{
    
  if(DVP_Int == DVP_INT_FO)
  {
    DVP->INTSTS = (DVP_FLAG_M1FO | DVP_FLAG_M2FO);
  }
  else if(DVP_Int == DVP_INT_AHBERR)
  {
    DVP->INTSTS = (DVP_FLAG_AHBERR1 | DVP_FLAG_AHBERR2);
  }
  else if(DVP_Int == DVP_INT_MO)
  {
    DVP->INTSTS = (DVP_FLAG_M1O | DVP_FLAG_M2O);
  }  
  else
  {
    DVP->INTSTS = DVP_Int;
  }  
  
}

/**
*\*\name    DVP_ConfigPixelClockPolarity.
*\*\fun     DVP port pixel clock polarity control.
*\*\param   PLCK_POL (The input parameters must be the following values):
*\*\           - DVP_PIXEL_POLARITY_RISING    
*\*\           - DVP_PIXEL_POLARITY_FALLING 
*\*\return  none.
**/   
void DVP_ConfigPixelClockPolarity(uint32_t PLCK_POL)
{
    
    uint32_t tmpregister; 
    tmpregister = DVP->PORTCFG;    
    tmpregister &= DVP_PIXEL_POLARITY_MASK;
    tmpregister |= PLCK_POL;
    DVP->PORTCFG = (uint32_t)tmpregister;

}

/**
*\*\name    DVP_ConfigHSyncPolarity.
*\*\fun     DVP HSYNC polarity control.
*\*\param   HSYNC_POL (The input parameters must be the following values):
*\*\           - DVP_HSYNC_POLARITY_HIGH   
*\*\           - DVP_HSYNC_POLARITY_LOW 
*\*\return  none.
**/    
void DVP_ConfigHSyncPolarity(uint32_t HSYNC_POL)
{

    uint32_t tmpregister; 
    tmpregister = DVP->PORTCFG;    
    tmpregister &= DVP_HSYNC_POLARITY_MASK;
    tmpregister |= HSYNC_POL;
    DVP->PORTCFG = (uint32_t)tmpregister;

}

/**
*\*\name    DVP_ConfigVSyncPolarity.
*\*\fun     DVP VSYNC polarity control.
*\*\param   VSYNC_POL (The input parameters must be the following values):
*\*\           - DVP_VSYNC_POLARITY_HIGH   
*\*\           - DVP_VSYNC_POLARITY_LOW 
*\*\return  none.
**/     
void DVP_ConfigVSyncPolarity(uint32_t VSYNC_POL)
{

    uint32_t tmpregister; 
    tmpregister = DVP->PORTCFG;    
    tmpregister &= DVP_VSYNC_POLARITY_MASK;
    tmpregister |= VSYNC_POL;
    DVP->PORTCFG = (uint32_t)tmpregister;

}

/**
*\*\name    DVP_EnableDataInvert.
*\*\fun     DVP data inversion enable. 
*\*\param  Cmd:(The input parameters must be the following values)
*\*\            - ENABLE
*\*\            - DISABLE 
*\*\return  none
**/     
void DVP_EnableDataInvert(FunctionalState Cmd)
{
    
  if (Cmd != DISABLE)
  {
    DVP->PORTCFG |= (uint32_t)DVP_DATA_INVERT;
  }
  else
  {
    DVP->PORTCFG &= DVP_DATA_INVERT_MASK;
  }
  
}

/**
*\*\name    DVP_EnableDataReverse.
*\*\fun     DVP data Reverse enable. 
*\*\param  Cmd:(The input parameters must be the following values)
*\*\            - ENABLE
*\*\            - DISABLE 
*\*\return  none
**/     
void DVP_EnableDataReverse(FunctionalState Cmd)
{

    
  if (Cmd != DISABLE)
  {
    DVP->PORTCFG |= DVP_DATA_REVERSE;
  }
  else
  {
    DVP->PORTCFG &= DVP_DATA_REVERSE_MASK;
  }
}
 
/**
*\*\name    DVP_ConfigEmbSyncPos.
*\*\fun     Embedded Synchronization Code Position.
*\*\param   SYNC_Pos (The input parameters must be the following values):
*\*\           - DVP_EMBSYNC_LSB   
*\*\           - DVP_EMBSYNC_MSB
*\*\return  none.
**/   
void DVP_ConfigEmbSyncPos(uint32_t SYNC_Pos)
{

    uint32_t tmpregister; 
    tmpregister = DVP->PORTCFG;    
    tmpregister &= DVP_EMBSYNC_POS_MASK;
    tmpregister |= SYNC_Pos;
    DVP->PORTCFG = (uint32_t)tmpregister;

}

/**
*\*\name    DVP_ConfigEmbSyncData.
*\*\fun     Embedded Synchronization Code Position.
*\*\param   FrameStartValue/FrameEndValue/LineStartValue/LineEndValue (The input parameters must be the following values):
*\*\           - 0x00 ~ 0xFF  
*\*\return  none.
**/   
void DVP_ConfigEmbSyncData(uint8_t FrameStartValue, uint8_t FrameEndValue, uint8_t LineStartValue, uint8_t LineEndValue)
{
    
    uint32_t temp_value;
    temp_value = ((uint32_t)FrameStartValue | ((uint32_t)FrameEndValue << 8) 
               | ((uint32_t)LineStartValue << 16) | ((uint32_t)LineEndValue << 24));
    DVP->EMSC |= temp_value;

}
/**
*\*\name    DVP_ConfigEmbSyncDataMask.
*\*\fun     Embedded Synchronization Code Position.
*\*\param   FrameStartMask/FrameEndMask/LineStartMask/LineEndMask (The input parameters must be the following values):
*\*\           - 0x00 ~ 0xFF  
*\*\return  none.
**/   
void DVP_ConfigEmbSyncDataMask(uint8_t FrameStartMask, uint8_t FrameEndMask, uint8_t LineStartMask, uint8_t LineEndMask)
{
    
    uint32_t temp_value;
    temp_value = ((uint32_t)FrameStartMask | ((uint32_t)FrameEndMask << 8) 
               | ((uint32_t)LineStartMask << 16) | ((uint32_t)LineEndMask << 24));
    DVP->EMSCM |= temp_value;

}

/**
*\*\name    DVP_EnableEmbSyncMode.
*\*\fun     Embedded Synchronization Mode enable bit.
*\*\param  Cmd:(The input parameters must be the following values)
*\*\            - ENABLE
*\*\            - DISABLE 
*\*\return  none
**/    
void DVP_EnableEmbSyncMode(FunctionalState Cmd)
{
    
  if (Cmd != DISABLE)
  {
    DVP->PORTCFG |= DVP_SYNC_MODE_SOFTWARE;
  }
  else
  {
    DVP->PORTCFG &= DVP_EMBSYNC_MASK;
  }
  
}

/**
*\*\name    DVP_ConfigDataMode.
*\*\fun     Config DVP data port mode.
*\*\param   Mode (The input parameters must be the following values):
*\*\           - DVP_DATA_MODE1 
*\*\           - DVP_DATA_MODE2
*\*\           - DVP_DATA_MODE3
*\*\           - DVP_DATA_MODE4
*\*\           - DVP_DATA_MODE5
*\*\           - DVP_DATA_MODE6
*\*\           - DVP_DATA_MODE7
*\*\           - DVP_DATA_MODE8
*\*\return  none.
**/         
void DVP_ConfigDataMode(uint32_t Mode)
{

    uint32_t tmpregister; 
    tmpregister = DVP->PORTCFG;    
    tmpregister &= DVP_DATA_MODE_MASK;
    tmpregister |= Mode;
    DVP->PORTCFG = (uint32_t)tmpregister;

}

/**
*\*\name    DVP_ConfigPixelByte.
*\*\fun     Config DVP pixel bytes.
*\*\param   Pixel_Byte (The input parameters must be the following values):
*\*\           - DVP_PIXEL_BYTE1   
*\*\           - DVP_PIXEL_BYTE2 
*\*\return  none.
**/   
void DVP_ConfigPixelByte(uint32_t Pixel_Byte)
{

    uint32_t tmpregister; 
    tmpregister = DVP->PORTCFG;    
    tmpregister &= DVP_PIXEL_BYTE_MASK;
    tmpregister |= Pixel_Byte;
    DVP->PORTCFG = (uint32_t)tmpregister;

}

/**
*\*\name    DVP_ConfigDATAByteOrder.
*\*\fun     Config DVP DATA order.
*\*\param   Byte0 (The input parameters must be the following values):
*\*\           - DVP_BYTE0_ORDER1   
*\*\           - DVP_BYTE0_ORDER2 
*\*\           - DVP_BYTE0_ORDER3
*\*\           - DVP_BYTE0_ORDER4
*\*\param   Byte1 (The input parameters must be the following values):
*\*\           - DVP_BYTE1_ORDER1   
*\*\           - DVP_BYTE1_ORDER2 
*\*\           - DVP_BYTE1_ORDER3
*\*\           - DVP_BYTE1_ORDER4
*\*\param   Byte2 (The input parameters must be the following values):
*\*\           - DVP_BYTE2_ORDER1   
*\*\           - DVP_BYTE2_ORDER2 
*\*\           - DVP_BYTE2_ORDER3
*\*\           - DVP_BYTE2_ORDER4
*\*\param   Byte3 (The input parameters must be the following values):
*\*\           - DVP_BYTE3_ORDER1   
*\*\           - DVP_BYTE3_ORDER2 
*\*\           - DVP_BYTE3_ORDER3
*\*\           - DVP_BYTE3_ORDER4
*\*\return  none.
**/     
void DVP_ConfigDATAByteOrder(uint32_t Byte0, uint32_t Byte1, uint32_t Byte2, uint32_t Byte3)
{
    
    uint32_t temp_value;
    temp_value = (Byte0 | Byte1 | Byte2 | Byte3);
    DVP->PORTCFG &= DVP_BYTE_ORDER_MASK;
    DVP->PORTCFG |= temp_value;

}

/**
*\*\name    DVP_ConfigInitSKIP.
*\*\fun     Config Initial Frame Line Skip .
*\*\param   Line (The input parameters must be the following values):
*\*\           - DVP_SKIP_LINE1 
*\*\           - DVP_SKIP_LINE2 
*\*\           - DVP_SKIP_LINE3 
*\*\           - DVP_SKIP_LINE4 
*\*\           - DVP_SKIP_LINE5 
*\*\           - DVP_SKIP_LINE6 
*\*\           - DVP_SKIP_LINE7 
*\*\           - DVP_SKIP_LINE8 
*\*\           - DVP_SKIP_LINE9 
*\*\           - DVP_SKIP_LINE10
*\*\           - DVP_SKIP_LINE11
*\*\           - DVP_SKIP_LINE12
*\*\           - DVP_SKIP_LINE13
*\*\           - DVP_SKIP_LINE14
*\*\           - DVP_SKIP_LINE15
*\*\return  none.
**/
void DVP_ConfigInitSKIP(uint32_t Line)
{
    
    uint32_t temp_value;
    temp_value = (uint32_t)(Line<<24);
    DVP->PORTCFG &= DVP_ISKIP_MASK;
    DVP->PORTCFG |= temp_value;

}

/**
*\*\name    DVP_ConfigRepeatSKIP.
*\*\fun     Config Repeat Frame Line Skip .
*\*\param   Line (The input parameters must be the following values):
*\*\           - DVP_SKIP_LINE1 
*\*\           - DVP_SKIP_LINE2 
*\*\           - DVP_SKIP_LINE3 
*\*\           - DVP_SKIP_LINE4 
*\*\           - DVP_SKIP_LINE5 
*\*\           - DVP_SKIP_LINE6 
*\*\           - DVP_SKIP_LINE7 
*\*\           - DVP_SKIP_LINE8 
*\*\           - DVP_SKIP_LINE9 
*\*\           - DVP_SKIP_LINE10
*\*\           - DVP_SKIP_LINE11
*\*\           - DVP_SKIP_LINE12
*\*\           - DVP_SKIP_LINE13
*\*\           - DVP_ODD_LINE 
*\*\           - DVP_EVEN_LINE
*\*\return  none.
**/
void DVP_ConfigRepeatSKIP(uint32_t Line)
{
    
    uint32_t temp_value;
    temp_value = (uint32_t)(Line<<28);
    DVP->PORTCFG &= DVP_RSKIP_MASK;
    DVP->PORTCFG |= temp_value;

}

/**
*\*\name    DVP_EnableBuffer1.
*\*\fun     Frame Buffer 1 enable.
*\*\param  Cmd:(The input parameters must be the following values)
*\*\            - ENABLE
*\*\            - DISABLE 
*\*\return  none
**/ 
void DVP_EnableBuffer1(FunctionalState Cmd)
{
    
  if (Cmd != DISABLE)
  {
    DVP->FIFOCFG |= DVP_BUFFER1;
  }
  else
  {
    DVP->FIFOCFG &= DVP_BUFFER1_MASK;
  }

}

/**
*\*\name    DVP_SetBuffer1Address.
*\*\fun     Set Frame Buffer 1 Start Address.
*\*\param  Addres:(The input parameters must be the following values)
*\*\            - 0x00000000~0xFFFFFFFF
*\*\return  none
**/ 
void DVP_SetBuffer1Address(uint32_t Addres)
{

    DVP->SMADDR1 = (uint32_t)Addres;

}

/**
*\*\name    DVP_EnableBuffer2.
*\*\fun     Frame Buffer 2 enable.
*\*\param  Cmd:(The input parameters must be the following values)
*\*\            - ENABLE
*\*\            - DISABLE 
*\*\return  none
**/
void DVP_EnableBuffer2(FunctionalState Cmd)
{
    
  if (Cmd != DISABLE)
  {
    DVP->FIFOCFG |= DVP_BUFFER2;
  }
  else
  {
    DVP->FIFOCFG &= DVP_BUFFER2_MASK;
  }

}

/**
*\*\name    DVP_SetBuffer2Address.
*\*\fun     Set Frame Buffer 2 Start Address.
*\*\param  Addres:(The input parameters must be the following values)
*\*\            - 0x00000000~0xFFFFFFFF
*\*\return  none
**/ 
void DVP_SetBuffer2Address(uint32_t Addres)
{

    DVP->SMADDR2 = (uint32_t)Addres;

}

/**
*\*\name    DVP_SetBufferSize.
*\*\fun     Set Frame Buffer Size.
*\*\param  Size:(The input parameters must be the following values)
*\*\            - 0 ~ 4194303
*\*\return  none 
**/ 
void DVP_SetBufferSize(uint32_t Size)
{

    DVP->FBS = (uint32_t)Size;

}

/**
*\*\name    DVP_SetDisplayBufferStatus.
*\*\fun     Set show current frame buffer status.
*\*\param  State_Mode:(The input parameters must be the following values)
*\*\            - DVP_DISPLAY_ADDRESS
*\*\            - DVP_DISPLAY_NUMBER
*\*\return  none
**/ 
void DVP_SetDisplayBufferStatus(uint32_t State_Mode)
{

    uint32_t tmpregister; 
    tmpregister = DVP->FIFOCFG;    
    tmpregister &= DVP_DISPLAY_STATUS_MASK;
    tmpregister |= State_Mode;
    DVP->FIFOCFG = (uint32_t)tmpregister;

}

/**
*\*\name    DVP_GetDisplayBufferStatus1.
*\*\fun     Get current frame buffer 1 status.
*\*\param   none
*\*\return  Frame Buffer 1 address or Number of data bytes
**/ 
uint32_t DVP_GetDisplayBufferStatus1(void)
{

    return DVP->FPBC1;

}

/**
*\*\name    DVP_GetDisplayBufferStatus2.
*\*\fun     Get current frame buffer 2 status.
*\*\param   none
*\*\return  Frame Buffer 2 address or Number of data bytes
**/ 
uint32_t DVP_GetDisplayBufferStatus2(void)
{

    return DVP->FPBC2;

}

/**
*\*\name    DVP_EnableAcross1KBoundary.
*\*\fun     Increamental bursting across 1K boundary is allowed/enabled
*\*\param  Cmd:(The input parameters must be the following values)
*\*\            - ENABLE
*\*\            - DISABLE 
*\*\return  none
**/    
void DVP_EnableAcross1KBoundary(FunctionalState Cmd)
{
    
  if (Cmd != DISABLE)
  {
    DVP->FIFOCFG |= DVP_1K_BOUNDARY_ENABLE;
  }
  else
  {
    DVP->FIFOCFG &= DVP_1K_BOUNDARY_MASK;
  }
  
}

/**
*\*\name    DVP_ConfigCROPStart.
*\*\fun     Config Y-coordinate and X-coordinate of crop image start point.
*\*\param  (X,Y):(The input parameters must be the following values)
*\*\            - (0,0) ~ (2047,2047)
*\*\return  none
**/   
void DVP_ConfigCROPStart(uint16_t X,uint16_t Y)
{
    
    DVP->CSXY = DVP_REG_BIT_FIELD_MASK;
    DVP->CSXY |= X;
    DVP->CSXY |= ((uint32_t)Y << 16);

}

/**
*\*\name    DVP_ConfigCROPEnd.
*\*\fun     Config Y-coordinate and X-coordinate of crop image end point.
*\*\param  (X,Y):(The input parameters must be the following values)
*\*\            - (0,0) ~ (2047,2047)
*\*\return  none
**/
void DVP_ConfigCROPEnd(uint16_t X,uint16_t Y)
{
    
    DVP->CEXY = DVP_REG_BIT_FIELD_MASK;
    DVP->CEXY |= X;
    DVP->CEXY |= ((uint32_t)Y << 16);

}

/**
*\*\name    DVP_DeInit.
*\*\fun     Deinitializes the DVP peripheral registers to their default reset values.
*\*\param   none
*\*\return  none
**/   
void DVP_DeInit(void)
{

    RCC_EnableAHBPeriphReset(RCC_AHB_PERIPHRST_DVP);
    
}

/**
*\*\name    DVP_Init.
*\*\fun     Initializes the DVP peripheral according to the specified
*\*\        parameters in the DVP_InitParam .
*\*\param   DVP_InitParam (The input parameters must be the following values):
*\*\          - CaptureMode
*\*\            - DVP_CAPTURE_MODE_CONTINUE
*\*\            - DVP_CAPTURE_MODE_SINGLE
*\*\          - CropMode
*\*\            - DVP_NORMAL_MODE
*\*\            - DVP_CROP_MODE  
*\*\          - SynchroMode
*\*\            - DVP_SYNC_MODE_SOFTWARE
*\*\            - DVP_SYNC_MODE_HARDWARE
*\*\          - CropStartX
*\*\          - CropStartY
*\*\          - CropEndX
*\*\          - CropEndY
*\*\          - BFilter
*\*\          - PixelClkPolarity
*\*\            - DVP_PIXEL_POLARITY_RISING  
*\*\            - DVP_PIXEL_POLARITY_FALLING
*\*\          - HsyncPolarity
*\*\            - DVP_HSYNC_POLARITY_HIGH 
*\*\            - DVP_HSYNC_POLARITY_LOW 
*\*\          - VsyncPolarity
*\*\            - DVP_VSYNC_POLARITY_HIGH
*\*\            - DVP_VSYNC_POLARITY_LOW 
*\*\          - DataInvert
*\*\            - DVP_DATA_INVERT   
*\*\            - DVP_DATA_NOTINVERT
*\*\          - DataReverse
*\*\            - DVP_DATA_REVERSE   
*\*\            - DVP_DATA_NOTREVERSE
*\*\          - DataMode
*\*\            - DVP_DATA_MODE1
*\*\            - DVP_DATA_MODE2
*\*\            - DVP_DATA_MODE3
*\*\            - DVP_DATA_MODE4
*\*\            - DVP_DATA_MODE5
*\*\            - DVP_DATA_MODE6
*\*\            - DVP_DATA_MODE7
*\*\            - DVP_DATA_MODE8
*\*\          - PixelByte  
*\*\            - DVP_PIXEL_BYTE1
*\*\            - DVP_PIXEL_BYTE2
*\*\return  none
**/
void DVP_Init(DVP_InitType* DVP_InitParam)
{
    uint32_t tmpregister;
    uint32_t tmp;

    if(DVP_InitParam->CropMode == DVP_CROP_MODE){
        /*---------------------------- DVP_CSXY Configuration -----------------------*/
        tmp = ((uint32_t)DVP_InitParam->CropStartY << 16) | DVP_InitParam->CropStartX;
        DVP->CSXY = tmp;        
        /*---------------------------- DVP_CEXY Configuration -----------------------*/
        tmp = ((uint32_t)DVP_InitParam->CropEndY << 16) | DVP_InitParam->CropEndX;
        DVP->CEXY = tmp;               
    } 
    
    /*---------------------------- DVP_CTRL Configuration -----------------------*/
    tmpregister = DVP->CTRL;
    tmpregister = tmpregister & DVP_VBFLT_MASK & DVP_CAPTURE_MODE_MASK & DVP_CROP_MODE_MASK;
    tmpregister |= ((uint32_t)DVP_InitParam->VBFilter << 28) | DVP_InitParam->CaptureMode | DVP_InitParam->CropMode;
    DVP->CTRL = tmpregister;

    /*---------------------------- DVP_PORTCFG Configuration -----------------------*/
    tmp = DVP->PORTCFG; 
    tmp |=  DVP_InitParam->PixelClkPolarity | DVP_InitParam->HsyncPolarity
          | DVP_InitParam->VsyncPolarity    | DVP_InitParam->DataInvert 
          | DVP_InitParam->DataReverse      | DVP_InitParam->DataMode
          | DVP_InitParam->SynchroMode;
    
    if(DVP_InitParam->CropMode == DVP_CROP_MODE){
        tmp |= DVP_InitParam->PixelByte;  
    }
    DVP->PORTCFG = tmp;    
    
}

/**
*\*\name    DVP_StructInit.
*\*\fun     Initializes the structure parameter of type DVP_InitType used to
*\*\        initialize DVP. This function is usually called before initializing
*\*\        a parameter of type DVP_InitType.
*\*\param   DVP_InitParam :
*\*\          - Pointer to the DVP_InitType structure which will be initialized.
*\*\return  none
**/
void DVP_StructInit(DVP_InitType* DVP_InitParam)
{
    /* DVP_InitParam members default value */
    DVP_InitParam->CaptureMode      = DVP_CAPTURE_MODE_CONTINUE;
    DVP_InitParam->CropMode         = DVP_NORMAL_MODE;
    DVP_InitParam->SynchroMode      = DVP_SYNC_MODE_HARDWARE;
    DVP_InitParam->CropStartX       = 0;
    DVP_InitParam->CropStartY       = 0;
    DVP_InitParam->CropEndX         = 0;
    DVP_InitParam->CropEndY         = 0;
    DVP_InitParam->VBFilter         = 8;
    DVP_InitParam->PixelClkPolarity = DVP_PIXEL_POLARITY_RISING;
    DVP_InitParam->HsyncPolarity    = DVP_HSYNC_POLARITY_HIGH;
    DVP_InitParam->VsyncPolarity    = DVP_VSYNC_POLARITY_LOW;
    DVP_InitParam->DataInvert       = DVP_DATA_NOTINVERT;
    DVP_InitParam->DataReverse      = DVP_DATA_NOTREVERSE;
    DVP_InitParam->DataMode         = DVP_DATA_MODE1;
    DVP_InitParam->PixelByte        = DVP_PIXEL_BYTE1;

}
 
/**
*\*\name    DVP_ConfigDma.
*\*\fun     Initializes the structure parameter of type DVP_DMAInitType used to
*\*\        initialize DVP DMA. This function is usually called before initializing
*\*\        a parameter of type DVP_DMAInitType.
*\*\param   DVP_DMAInitType :
*\*\          - FrameBufferNum
*\*\          - FrameBufferAddress1
*\*\          - FrameBufferAddress2
*\*\          - DisplayStatus
*\*\            - DVP_DISPLAY_ADDRESS
*\*\            - DVP_DISPLAY_NUMBER 
*\*\          - BurstSize 
*\*\            - DVP_BURST_SIZE_BYTE_4 
*\*\            - DVP_BURST_SIZE_BYTE_8 
*\*\            - DVP_BURST_SIZE_BYTE_12
*\*\            - DVP_BURST_SIZE_BYTE_16
*\*\            - DVP_BURST_SIZE_BYTE_20
*\*\            - DVP_BURST_SIZE_BYTE_24
*\*\            - DVP_BURST_SIZE_BYTE_28
*\*\            - DVP_BURST_SIZE_BYTE_32
*\*\          - FifoThreshold  
*\*\            - DVP_FIFO_THRSEHOLD_BYTE_4 
*\*\            - DVP_FIFO_THRSEHOLD_BYTE_8 
*\*\            - DVP_FIFO_THRSEHOLD_BYTE_16
*\*\            - DVP_FIFO_THRSEHOLD_BYTE_32
*\*\          - FrameBufferSize
*\*\return  none
**/ 
void DVP_ConfigDma(DVP_DMAInitType* DVP_DMAInitParam)
{
    uint32_t tmpregister;

    /*---------------------------- DVP_FIFOCFG Configuration -----------------------*/
    tmpregister = DVP->FIFOCFG;
    tmpregister &= DVP_DISPLAY_STATUS_MASK & DVP_FIFO_THRSEHOLD_MASK & DVP_BURST_SIZE_MASK;

    tmpregister |= DVP_DMAInitParam->DisplayStatus | DVP_DMAInitParam->FifoThreshold | DVP_DMAInitParam->BurstSize;
    DVP->FIFOCFG = tmpregister;
    
    /*---------------------------- DVP_FBS Configuration -----------------------*/
    DVP->FBS = (uint32_t)DVP_DMAInitParam->FrameBufferSize;
    
    /*---------------------------- DVP_SMADDRx Configuration -----------------------*/
    if(DVP_DMAInitParam->FrameBufferNum == 2u){
        DVP->SMADDR1 = DVP_DMAInitParam->FrameBufferAddress1;
        DVP->SMADDR2 = DVP_DMAInitParam->FrameBufferAddress2;        
    }else{
        DVP->SMADDR1 = DVP_DMAInitParam->FrameBufferAddress1;         
    }

}

/**
*\*\name    DVP_DMAStructInit.
*\*\fun     Initializes the structure parameter of type DVP_DMAInitType used to
*\*\        initialize DVP. This function is usually called before initializing
*\*\        a parameter of type DVP_DMAInitType.
*\*\param   DVP_DMAInitParam :
*\*\          - Pointer to the DVP_DMAInitType structure which will be initialized.
*\*\return  none
**/
void DVP_DMAStructInit(DVP_DMAInitType* DVP_DMAInitParam)
{
    
    /* DVP_DMAInitParam members default value */
    DVP_DMAInitParam->FrameBufferNum      = 1;
    DVP_DMAInitParam->FrameBufferAddress1 = 0;
    DVP_DMAInitParam->FrameBufferAddress2 = 0;
    DVP_DMAInitParam->DisplayStatus       = DVP_DISPLAY_NUMBER;
    DVP_DMAInitParam->BurstSize           = DVP_BURST_SIZE_BYTE_4;
    DVP_DMAInitParam->FifoThreshold       = DVP_FIFO_THRSEHOLD_BYTE_4;
    DVP_DMAInitParam->FrameBufferSize     = 32;

}




