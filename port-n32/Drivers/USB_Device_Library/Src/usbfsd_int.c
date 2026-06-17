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
*\*\file usbfsd_int.c
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/

#include "usbfsd_lib.h"

__IO uint16_t SaveRState;
__IO uint16_t SaveTState;

extern void (*pEpInt_IN[7])(void);  /*  Handles IN  interrupts   */
extern void (*pEpInt_OUT[7])(void); /*  Handles OUT interrupts   */

/**
*\*\name    USB_CorrectTransferLp.
*\*\fun     Low priority Endpoint Correct Transfer interrupt's service routine.
*\*\param   none
*\*\return  none
**/
void USB_CorrectTransferLp(void)
{
    __IO uint16_t wEPVal = 0;
    /* stay in loop while pending interrupts */
    while (((wIstr = _GetISTR()) & STS_CTRS) != 0)
    {
        /* extract highest priority endpoint number */
        EPindex = (uint8_t)((wIstr & STS_EP_ID) >> 8);
        if (EPindex == 0)
        {
            /* Decode and service control endpoint interrupt */
            /* calling related service routine */
            /* (USB_ProcessSetup0, USB_ProcessIn0, USB_ProcessOut0) */

            /* save RX & TX status */
            /* and set both to NAK */

            SaveRState = _GetENDPOINT(ENDP0);
            SaveTState = SaveRState & EPTX_STS;
            SaveRState &= EPRX_STS;
            _SetEPRxTxStatus(ENDP0, EP_RX_NAK, EP_TX_NAK);

            /* DIR bit = origin of the interrupt */

            if ((wIstr & STS_DIR) == 0)
            {
                /* DIR = 0 */

                /* DIR = 0      => IN  int */
                /* DIR = 0 implies that (EP_CTRS_TX = 1) always  */

                _ClearEP_CTR_TX(ENDP0);
                USB_ProcessIn0();

                /* before terminate set Tx & Rx status */

                _SetEPRxTxStatus(ENDP0, SaveRState, SaveTState);
                return;
            }
            else
            {
                /* DIR = 1 */

                /* DIR = 1 & CTR_RX       => SETUP or OUT int */
                /* DIR = 1 & (CTR_TX | CTR_RX) => 2 int pending */

                wEPVal = _GetENDPOINT(ENDP0);

                if ((wEPVal & EP_SETUP) != 0)
                {
                    _ClearEP_CTR_RX(ENDP0); /* SETUP bit kept frozen while CTR_RX = 1 */
                    USB_ProcessSetup0();
                    /* before terminate set Tx & Rx status */

                    _SetEPRxTxStatus(ENDP0, SaveRState, SaveTState);
                    return;
                }

                else if ((wEPVal & EP_CTRS_RX) != 0)
                {
                    _ClearEP_CTR_RX(ENDP0);
                    USB_ProcessOut0();
                    /* before terminate set Tx & Rx status */

                    _SetEPRxTxStatus(ENDP0, SaveRState, SaveTState);
                    return;
                }
            }
        } /* if(EPindex == 0) */
        else
        {
            /* Decode and service non control endpoints interrupt  */

            /* process related endpoint register */
            wEPVal = _GetENDPOINT(EPindex);
            if ((wEPVal & EP_CTRS_RX) != 0)
            {
                /* clear int flag */
                _ClearEP_CTR_RX(EPindex);

                /* call OUT service function */
                (*pEpInt_OUT[EPindex - 1])();

            } /* if((wEPVal & EP_CTRS_RX) */

            if ((wEPVal & EP_CTRS_TX) != 0)
            {
                /* clear int flag */
                _ClearEP_CTR_TX(EPindex);

                /* call IN service function */
                (*pEpInt_IN[EPindex - 1])();
            } /* if((wEPVal & EP_CTRS_TX) != 0) */

        } /* if(EPindex == 0) else */

    } /* while(...) */
}

/**
*\*\name    USB_CorrectTransferHp.
*\*\fun     High Priority Endpoint Correct Transfer interrupt's service routine.
*\*\param   none
*\*\return  none
**/
void USB_CorrectTransferHp(void)
{
    uint32_t wEPVal = 0;

    while (((wIstr = _GetISTR()) & STS_CTRS) != 0)
    {
        _SetISTR((uint16_t)CLR_CTRS); /* clear CTR flag */
        /* extract highest priority endpoint number */
        EPindex = (uint8_t)((wIstr & STS_EP_ID) >> 8);
        /* process related endpoint register */
        wEPVal = _GetENDPOINT(EPindex);
        if ((wEPVal & EP_CTRS_RX) != 0)
        {
            /* clear int flag */
            _ClearEP_CTR_RX(EPindex);

            /* call OUT service function */
            (*pEpInt_OUT[EPindex - 1])();

        } /* if((wEPVal & EP_CTRS_RX) */
        else if ((wEPVal & EP_CTRS_TX) != 0)
        {
            /* clear int flag */
            _ClearEP_CTR_TX(EPindex);

            /* call IN service function */
            (*pEpInt_IN[EPindex - 1])();

        } /* if((wEPVal & EP_CTRS_TX) != 0) */

    } /* while(...) */
}
