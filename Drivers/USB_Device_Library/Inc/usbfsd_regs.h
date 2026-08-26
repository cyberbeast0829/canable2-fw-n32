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
*\*\file usbfsd_regs.h
*\*\author Nations
*\*\version v1.0.0
*\*\copyright Copyright (c) 2023, Nations Technologies Inc. All rights reserved.
**/

#ifndef __USBFSD_REGS_H__
#define __USBFSD_REGS_H__

#include "n32h47x_48x.h"


typedef enum _EP_DBUF_DIR
{
    /* double buffered endpoint direction */
    EP_DBUF_ERR,
    EP_DBUF_OUT,
    EP_DBUF_IN
} EP_DBUF_DIR;

/* endpoint buffer number */
enum EP_BUF_NUM
{
    EP_NOBUF,
    EP_BUF0,
    EP_BUF1
};

#define RegBase (0x40004800U) /* USB_IP Peripheral Registers base address */
#define PMAAddr (0x40004C00U) /* USB_IP Packet Memory Area base address   */

/** General registers **/

/* Control register */
#define USB_CTRL ((__IO unsigned*)(RegBase + 0x40))
/* Interrupt status register */
#define USB_STS ((__IO unsigned*)(RegBase + 0x44))
/* Buffer Table address register */
#define USB_BUFTAB ((__IO unsigned*)(RegBase + 0x48))
/* Frame number register */
#define USB_FN ((__IO unsigned*)(RegBase + 0x4C))
/* Device address register */
#define USB_ADDR ((__IO unsigned*)(RegBase + 0x50))


#define _EnPortPullup()  (*USB_CTRL = (*USB_CTRL) | 0x2000);
#define _DisPortPullup() (*USB_CTRL = (*USB_CTRL) & 0xFFFFDFFF);

/** Endpoint registers **/

#define EP0REG ((__IO unsigned*)(RegBase)) /* endpoint 0 register address */

/* Endpoint Addresses (w/direction) */
#define EP0_OUT ((uint8_t)0x00)
#define EP0_IN  ((uint8_t)0x80)
#define EP1_OUT ((uint8_t)0x01)
#define EP1_IN  ((uint8_t)0x81)
#define EP2_OUT ((uint8_t)0x02)
#define EP2_IN  ((uint8_t)0x82)
#define EP3_OUT ((uint8_t)0x03)
#define EP3_IN  ((uint8_t)0x83)
#define EP4_OUT ((uint8_t)0x04)
#define EP4_IN  ((uint8_t)0x84)
#define EP5_OUT ((uint8_t)0x05)
#define EP5_IN  ((uint8_t)0x85)
#define EP6_OUT ((uint8_t)0x06)
#define EP6_IN  ((uint8_t)0x86)
#define EP7_OUT ((uint8_t)0x07)
#define EP7_IN  ((uint8_t)0x87)

/** endpoints enumeration **/
#define ENDP0   ((uint8_t)0x00)
#define ENDP1   ((uint8_t)0x01)
#define ENDP2   ((uint8_t)0x02)
#define ENDP3   ((uint8_t)0x03)
#define ENDP4   ((uint8_t)0x04)
#define ENDP5   ((uint8_t)0x05)
#define ENDP6   ((uint8_t)0x06)
#define ENDP7   ((uint8_t)0x07)


/** USB_STS interrupt events **/

#define STS_CTRS     (0x0040)    /* Correct TRansfer (clear-only bit) */
#define STS_DOVR     (0x0080)    /* DMA OVeR/underrun (clear-only bit) */
#define STS_ERROR    (0x0020)    /* ERRor (clear-only bit) */
#define STS_WKUP     (0x0010)    /* WaKe UP (clear-only bit) */
#define STS_SUSPD    (0x0008)    /* SUSPend (clear-only bit) */
#define STS_RST      (0x0004)    /* RESET (clear-only bit) */
#define STS_SOF      (0x0002)    /* Start Of Frame (clear-only bit) */
#define STS_ESOF     (0x0001)    /* Expected Start Of Frame (clear-only bit) */
       
#define STS_DIR      (USB_STS_DIR)     /* DIRection of transaction (read-only bit)  */
#define STS_EP_ID    (USB_STS_EP_ID)   /* EndPoint IDentifier (read-only bit)  */
       
#define CLR_CTRS     (~STS_CTRS)       /* clear Correct TRansfer bit */
#define CLR_DOVR     (~STS_DOVR)       /* clear DMA OVeR/underrun bit*/
#define CLR_ERROR    (~STS_ERROR)      /* clear ERRor bit */
#define CLR_WKUP     (~STS_WKUP)       /* clear WaKe UP bit     */
#define CLR_SUSPD    (~STS_SUSPD)      /* clear SUSPend bit     */
#define CLR_RST      (~STS_RST)        /* clear RESET bit      */
#define CLR_SOF      (~STS_SOF)        /* clear Start Of Frame bit   */
#define CLR_ESOF     (~STS_ESOF)       /* clear Expected Start Of Frame bit */


/** USB_CTRL control register bits definitions **/
#define CTRL_CTRSM   (0x0040)    /* Correct TRansfer Mask */
#define CTRL_DOVRM   (0x0080)    /* DMA OVeR/underrun Mask */
#define CTRL_ERRORM  (0x0020)    /* ERRor Mask */
#define CTRL_WKUPM   (0x0010)    /* WaKe UP Mask */
#define CTRL_SUSPDM  (0x0008)    /* SUSPend Mask */
#define CTRL_RSTM    (0x0004)    /* RESET Mask   */
#define CTRL_SOFM    (0x0002)    /* Start Of Frame Mask */
#define CTRL_ESOFM   (0x0001)    /* Expected Start Of Frame Mask */

#define CTRL_PU_RES  (USB_CTRL_PU)      /*d+ 1.5K Pull up Resister*/
#define CTRL_RESUM   (USB_CTRL_RESUM)   /* RESUME request */
#define CTRL_FSUSPD  (USB_CTRL_FSUSPD)  /* Force SUSPend */
#define CTRL_LP_MODE (USB_CTRL_LP_MODE) /* Low-power MODE */
#define CTRL_PD      (USB_CTRL_PD)      /* Power DoWN */
#define CTRL_FRST    (USB_CTRL_FRST)    /* Force USB RESet */

/** USB_FN Frame Number Register bit definitions **/
#define FN_RXDP      (USB_FN_RXDP_STS)  /* status of D+ data line */
#define FN_RXDM      (USB_FN_RXDM_STS)  /* status of D- data line */
#define FN_LCK       (USB_FNR_LOCK)     /* LoCKed */
#define FN_LSOF      (USB_FN_LSTSOF)    /* Lost SOF */
#define FN_FNUM      (USB_FN_FNUM)      /* Frame Number */

/** USB_ADDR Device ADDRess bit definitions **/
#define ADDR_EFUC    (USB_ADDR_EFUC)
#define ADDR_ADDR    (USB_ADDR_ADDR)

/** Endpoint register **/

/** bit positions */
#define EP_CTRS_RX   (USB_EP_CTRS_RX)   /* EndPoint Correct TRansfer RX */
#define EP_DATTOG_RX (USB_EP_DATTOG_RX) /* EndPoint Data TOGGLE RX */
#define EPRX_STS     (USB_EP_STS_RX)    /* EndPoint RX STATus bit field */
#define EP_SETUP     (USB_EP_SETUP)     /* EndPoint SETUP */
#define EP_T_FIELD   (USB_EP_EP_TYPE)   /* EndPoint TYPE */
#define EP_KIND      (USB_EP_EP_KIND)   /* EndPoint KIND */
#define EP_CTRS_TX   (USB_EP_CTRS_TX)   /* EndPoint Correct TRansfer TX */
#define EP_DATTOG_TX (USB_EP_DATTOG_TX) /* EndPoint Data TOGGLE TX */
#define EPTX_STS     (USB_EP_STS_TX)    /* EndPoint TX STATus bit field */
#define EPADDR_FIELD (USB_EP_EPADDR)    /* EndPoint ADDRess FIELD */

/** EndPoint REGister INTEN (no toggle fields) **/
#define EPREG_MASK (EP_CTRS_RX | EP_SETUP | EP_T_FIELD | EP_KIND | EP_CTRS_TX | EPADDR_FIELD)

/** EP_TYPE[1:0] EndPoint TYPE **/
#define EP_TYPE_MASK   (USB_EP_EP_TYPE) /* EndPoint TYPE Mask */
#define EP_BULK        (0x0000) /* EndPoint BULK */
#define EP_CONTROL     (USB_EP_EP_TYPE_0) /* EndPoint CONTROL */
#define EP_ISOCHRONOUS (USB_EP_EP_TYPE_1) /* EndPoint ISOCHRONOUS */
#define EP_INTERRUPT   (USB_EP_EP_TYPE_0 | USB_EP_EP_TYPE_1) /* EndPoint INTERRUPT */
#define EP_T_MASK      (~EP_T_FIELD & EPREG_MASK)

/** EP_KIND EndPoint KIND **/
#define EPKIND_MASK (~EP_KIND & EPREG_MASK)

/** STAT_TX[1:0] STATus for TX transfer **/
#define EP_TX_DIS       (0x0000) /* EndPoint TX DISabled */
#define EP_TX_STALL     (USB_EP_STS_TX_0)   /* EndPoint TX STALLed */
#define EP_TX_NAK       (USB_EP_STS_TX_1)   /* EndPoint TX NAKed */
#define EP_TX_VALID     (USB_EP_STS_TX_0 | USB_EP_STS_TX_1)     /* EndPoint TX VALID */
#define EPTX_DATTOG1    (USB_EP_STS_TX_0)   /* EndPoint TX Data TOGgle bit1 */
#define EPTX_DATTOG2    (USB_EP_STS_TX_1)   /* EndPoint TX Data TOGgle bit2 */
#define EPTX_DATTOGMASK (EPTX_STS | EPREG_MASK)

/** STAT_RX[1:0] STATus for RX transfer **/
#define EP_RX_DIS       (0x0000) /* EndPoint RX DISabled */
#define EP_RX_STALL     (USB_EP_STS_RX_0)   /* EndPoint RX STALLed */
#define EP_RX_NAK       (USB_EP_STS_RX_1)   /* EndPoint RX NAKed */
#define EP_RX_VALID     (USB_EP_STS_RX_0 | USB_EP_STS_RX_1) /* EndPoint RX VALID */
#define EPRX_DATTOG1    (USB_EP_STS_RX_0)   /* EndPoint RX Data TOGgle bit1 */
#define EPRX_DATTOG2    (USB_EP_STS_RX_1)   /* EndPoint RX Data TOGgle bit1 */
#define EPRX_DATTOGMASK (EPRX_STS | EPREG_MASK)

/* USB_SetCtrl */
#define _SetCNTR(wRegValue) (*USB_CTRL = (uint16_t)wRegValue)

/* USB_SetSts */
#define _SetISTR(wRegValue) (*USB_STS = (uint16_t)wRegValue)

/* USB_SetAddr */
#define _SetDADDR(wRegValue) (*USB_ADDR = (uint16_t)wRegValue)

/* USB_SetBuftab */
#define _SetBTABLE(wRegValue) (*USB_BUFTAB = (uint16_t)(wRegValue & 0xFFF8))

/* USB_GetCtrl */
#define _GetCNTR() ((uint16_t)*USB_CTRL)

/* USB_GetSts */
#define _GetISTR() ((uint16_t)*USB_STS)

/* USB_GetFn */
#define _GetFNR() ((uint16_t)*USB_FN)

/* USB_GetAddr */
#define _GetDADDR() ((uint16_t)*USB_ADDR)

/* USB_GetBTABLE */
#define _GetBTABLE() ((uint16_t)*USB_BUFTAB)

/* USB_SetEndPoint */
#define _SetENDPOINT(bEpNum, wRegValue) (*(EP0REG + bEpNum) = (uint16_t)wRegValue)

/* USB_GetEndPoint */
#define _GetENDPOINT(bEpNum) ((uint16_t)(*(EP0REG + bEpNum)))

/**
*\*\name    _SetEPType
*\*\fun     sets the type in the endpoint register(bits EP_TYPE[1:0])
*\*\param   bEpNum: Endpoint Number.
*\*\param   wType
*\*\return  none
**/
#define _SetEPType(bEpNum, wType) (_SetENDPOINT(bEpNum, ((_GetENDPOINT(bEpNum) & EP_T_MASK) | wType)))

/**
*\*\name    _GetEPType
*\*\fun     gets the type in the endpoint register(bits EP_TYPE[1:0])
*\*\param   bEpNum: Endpoint Number.
*\*\return  Endpoint Type
**/
#define _GetEPType(bEpNum) (_GetENDPOINT(bEpNum) & EP_T_FIELD)

/**
*\*\name    _SetEPTxStatus
*\*\fun     sets the status for tx transfer (bits STAT_TX[1:0]).
*\*\param   bEpNum: Endpoint Number.
*\*\param   wState: new state
*\*\return  none
**/
#define _SetEPTxStatus(bEpNum, wState)                                                                                 \
    {                                                                                                                  \
        register uint16_t _wRegVal;                                                                                    \
        _wRegVal = _GetENDPOINT(bEpNum) & EPTX_DATTOGMASK;                                                             \
        /* toggle first bit ? */                                                                                       \
        if ((EPTX_DATTOG1 & wState) != 0)                                                                              \
            _wRegVal ^= EPTX_DATTOG1;                                                                                  \
        /* toggle second bit ?  */                                                                                     \
        if ((EPTX_DATTOG2 & wState) != 0)                                                                              \
            _wRegVal ^= EPTX_DATTOG2;                                                                                  \
        _SetENDPOINT(bEpNum, (_wRegVal | EP_CTRS_RX | EP_CTRS_TX));                                                    \
    } /* _SetEPTxStatus */

/**
*\*\name    _SetEPRxStatus
*\*\fun     sets the status for rx transfer (bits STAT_TX[1:0])
*\*\param   bEpNum: Endpoint Number.
*\*\param   wState: new state
*\*\return  none
**/
#define _SetEPRxStatus(bEpNum, wState)                                                                                 \
    {                                                                                                                  \
        register uint16_t _wRegVal;                                                                                    \
                                                                                                                       \
        _wRegVal = _GetENDPOINT(bEpNum) & EPRX_DATTOGMASK;                                                             \
        /* toggle first bit ? */                                                                                       \
        if ((EPRX_DATTOG1 & wState) != 0)                                                                              \
            _wRegVal ^= EPRX_DATTOG1;                                                                                  \
        /* toggle second bit ? */                                                                                      \
        if ((EPRX_DATTOG2 & wState) != 0)                                                                              \
            _wRegVal ^= EPRX_DATTOG2;                                                                                  \
        _SetENDPOINT(bEpNum, (_wRegVal | EP_CTRS_RX | EP_CTRS_TX));                                                    \
    } /* _SetEPRxStatus */

/**
*\*\name    _SetEPRxTxStatus
*\*\fun     sets the status for rx & tx (bits STAT_TX[1:0] & STAT_RX[1:0])
*\*\param   bEpNum: Endpoint Number.
*\*\param   wStaterx: new state.
*\*\param   wStatetx: new state.
*\*\return  none
**/
#define _SetEPRxTxStatus(bEpNum, wStaterx, wStatetx)                                                                   \
    {                                                                                                                  \
        register uint32_t _wRegVal;                                                                                    \
                                                                                                                       \
        _wRegVal = _GetENDPOINT(bEpNum) & (EPRX_DATTOGMASK | EPTX_STS);                                                \
        /* toggle first bit ? */                                                                                       \
        if ((EPRX_DATTOG1 & wStaterx) != 0)                                                                            \
            _wRegVal ^= EPRX_DATTOG1;                                                                                  \
        /* toggle second bit ? */                                                                                      \
        if ((EPRX_DATTOG2 & wStaterx) != 0)                                                                            \
            _wRegVal ^= EPRX_DATTOG2;                                                                                  \
        /* toggle first bit ? */                                                                                       \
        if ((EPTX_DATTOG1 & wStatetx) != 0)                                                                            \
            _wRegVal ^= EPTX_DATTOG1;                                                                                  \
        /* toggle second bit ?  */                                                                                     \
        if ((EPTX_DATTOG2 & wStatetx) != 0)                                                                            \
            _wRegVal ^= EPTX_DATTOG2;                                                                                  \
        _SetENDPOINT(bEpNum, _wRegVal | EP_CTRS_RX | EP_CTRS_TX);                                                      \
    } /* _SetEPRxTxStatus */

/**
*\*\name    _GetEPTxStatus/_GetEPRxStatus
*\*\fun     gets the status for tx/rx transfer (bits STAT_TX[1:0]/STAT_RX[1:0])
*\*\param   bEpNum: Endpoint Number.
*\*\return  status
**/
#define _GetEPTxStatus(bEpNum) ((uint16_t)_GetENDPOINT(bEpNum) & EPTX_STS)

#define _GetEPRxStatus(bEpNum) ((uint16_t)_GetENDPOINT(bEpNum) & EPRX_STS)

/**
*\*\name    _SetEPTxValid/_SetEPRxValid
*\*\fun     sets directly the VALID tx/rx-status into the enpoint register
*\*\param   bEpNum: Endpoint Number.
*\*\return  status
**/
#define _SetEPTxValid(bEpNum) (_SetEPTxStatus(bEpNum, EP_TX_VALID))

#define _SetEPRxValid(bEpNum) (_SetEPRxStatus(bEpNum, EP_RX_VALID))

/**
*\*\name    _GetTxStallStatus/_GetRxStallStatus
*\*\fun     checks stall condition in an endpoint.
*\*\param   bEpNum: Endpoint Number.
*\*\return  TRUE = endpoint in stall condition.
**/
#define _GetTxStallStatus(bEpNum) (_GetEPTxStatus(bEpNum) == EP_TX_STALL)
#define _GetRxStallStatus(bEpNum) (_GetEPRxStatus(bEpNum) == EP_RX_STALL)

/**
*\*\name    _SetEP_KIND/_ClearEP_KIND
*\*\fun     set & clear EP_KIND bit.
*\*\param   bEpNum: Endpoint Number.
*\*\return  none
**/
#define _SetEP_KIND(bEpNum)                                                                                            \
    (_SetENDPOINT(bEpNum, (EP_CTRS_RX | EP_CTRS_TX | ((_GetENDPOINT(bEpNum) | EP_KIND) & EPREG_MASK))))
#define _ClearEP_KIND(bEpNum) (_SetENDPOINT(bEpNum, (EP_CTRS_RX | EP_CTRS_TX | (_GetENDPOINT(bEpNum) & EPKIND_MASK))))

/**
*\*\name    _Set_Status_Out/_Clear_Status_Out
*\*\fun     Sets/clears directly STATUS_OUT bit in the endpoint register.
*\*\param   bEpNum: Endpoint Number.
*\*\return  none
**/
#define _Set_Status_Out(bEpNum)   _SetEP_KIND(bEpNum)
#define _Clear_Status_Out(bEpNum) _ClearEP_KIND(bEpNum)

/**
*\*\name    _SetEPDoubleBuff/_ClearEPDoubleBuff
*\*\fun     Sets/clears directly EP_KIND bit in the endpoint register.
*\*\param   bEpNum: Endpoint Number.
*\*\return  none
**/
#define _SetEPDoubleBuff(bEpNum)   _SetEP_KIND(bEpNum)
#define _ClearEPDoubleBuff(bEpNum) _ClearEP_KIND(bEpNum)

/**
*\*\name    _ClearEP_CTR_RX/_ClearEP_CTR_TX
*\*\fun     Clears bit CTR_RX / CTR_TX in the endpoint register.
*\*\param   bEpNum: Endpoint Number.
*\*\return  none
**/
#define _ClearEP_CTR_RX(bEpNum) (_SetENDPOINT(bEpNum, _GetENDPOINT(bEpNum) & 0xFEFF & EPREG_MASK))
#define _ClearEP_CTR_TX(bEpNum) (_SetENDPOINT(bEpNum, _GetENDPOINT(bEpNum) & 0xEFFF & EPREG_MASK))

/**
*\*\name    _ToggleDTOG_RX/_ToggleDTOG_TX
*\*\fun     Toggles DTOG_RX / DTOG_TX bit in the endpoint register.
*\*\param   bEpNum: Endpoint Number.
*\*\return  none
**/
#define _ToggleDTOG_RX(bEpNum)                                                                                         \
    (_SetENDPOINT(bEpNum, EP_CTRS_RX | EP_CTRS_TX | EP_DATTOG_RX | (_GetENDPOINT(bEpNum) & EPREG_MASK)))
#define _ToggleDTOG_TX(bEpNum)                                                                                         \
    (_SetENDPOINT(bEpNum, EP_CTRS_RX | EP_CTRS_TX | EP_DATTOG_TX | (_GetENDPOINT(bEpNum) & EPREG_MASK)))

/**
*\*\name    _ClearDTOG_RX/_ClearDTOG_TX
*\*\fun     Clears DTOG_RX / DTOG_TX bit in the endpoint register.
*\*\param   bEpNum: Endpoint Number.
*\*\return  none
**/
#define _ClearDTOG_RX(bEpNum)                                                                                          \
    if ((_GetENDPOINT(bEpNum) & EP_DATTOG_RX) != 0)                                                                    \
    _ToggleDTOG_RX(bEpNum)
#define _ClearDTOG_TX(bEpNum)                                                                                          \
    if ((_GetENDPOINT(bEpNum) & EP_DATTOG_TX) != 0)                                                                    \
    _ToggleDTOG_TX(bEpNum)

/**
*\*\name    _SetEPAddress
*\*\fun     Sets address in an endpoint register.
*\*\param   bEpNum: Endpoint Number.
*\*\param   bAddr: Address.
*\*\return  none
**/
#define _SetEPAddress(bEpNum, bAddr)                                                                                   \
    _SetENDPOINT(bEpNum, EP_CTRS_RX | EP_CTRS_TX | (_GetENDPOINT(bEpNum) & EPREG_MASK) | bAddr)

/**
*\*\name    _GetEPAddress
*\*\fun     Gets address in an endpoint register.
*\*\param   bEpNum: Endpoint Number.
*\*\return  none
**/
#define _GetEPAddress(bEpNum) ((uint8_t)(_GetENDPOINT(bEpNum) & EPADDR_FIELD))

#define _pEPTxAddr(bEpNum)  ((uint32_t*)((_GetBTABLE() + bEpNum * 8) * 2 + PMAAddr))
#define _pEPTxCount(bEpNum) ((uint32_t*)((_GetBTABLE() + bEpNum * 8 + 2) * 2 + PMAAddr))
#define _pEPRxAddr(bEpNum)  ((uint32_t*)((_GetBTABLE() + bEpNum * 8 + 4) * 2 + PMAAddr))
#define _pEPRxCount(bEpNum) ((uint32_t*)((_GetBTABLE() + bEpNum * 8 + 6) * 2 + PMAAddr))

/**
*\*\name    _SetEPTxAddr/_SetEPRxAddr
*\*\fun     sets address of the tx/rx buffer.
*\*\param   bEpNum: Endpoint Number.
*\*\param   wAddr: address to be set (must be word aligned).
*\*\return  none
**/
#define _SetEPTxAddr(bEpNum, wAddr) (*_pEPTxAddr(bEpNum) = ((wAddr >> 1) << 1))
#define _SetEPRxAddr(bEpNum, wAddr) (*_pEPRxAddr(bEpNum) = ((wAddr >> 1) << 1))

/**
*\*\name    _GetEPTxAddr/_GetEPRxAddr
*\*\fun     Gets address of the tx/rx buffer.
*\*\param   bEpNum: Endpoint Number.
*\*\param   wAddr: address to be set (must be word aligned).
*\*\return  address of the buffer.
**/
#define _GetEPTxAddr(bEpNum) ((uint16_t)*_pEPTxAddr(bEpNum))
#define _GetEPRxAddr(bEpNum) ((uint16_t)*_pEPRxAddr(bEpNum))


/**
*\*\name    _SetEpCntRxReg.
*\*\fun     Sets counter of rx buffer with no. of blocks.
*\*\param   dwReg: pointer to counter.
*\*\param   wCount: Counter.
*\*\return  none
**/
#define _BlocksOf32(dwReg, wCount, wNBlocks)                                                                           \
    {                                                                                                                  \
        wNBlocks = wCount >> 5;                                                                                        \
        if ((wCount & 0x1f) == 0)                                                                                      \
            wNBlocks--;                                                                                                \
        *pdwReg = (uint32_t)((wNBlocks << 10) | 0x8000);                                                               \
    } /* _BlocksOf32 */

#define _BlocksOf2(dwReg, wCount, wNBlocks)                                                                            \
    {                                                                                                                  \
        wNBlocks = wCount >> 1;                                                                                        \
        if ((wCount & 0x1) != 0)                                                                                       \
            wNBlocks++;                                                                                                \
        *pdwReg = (uint32_t)(wNBlocks << 10);                                                                          \
    } /* _BlocksOf2 */

#define _SetEPCountRxReg(dwReg, wCount)                                                                                \
    {                                                                                                                  \
        uint16_t wNBlocks;                                                                                             \
        if (wCount > 62)                                                                                               \
        {                                                                                                              \
            _BlocksOf32(dwReg, wCount, wNBlocks);                                                                      \
        }                                                                                                              \
        else                                                                                                           \
        {                                                                                                              \
            _BlocksOf2(dwReg, wCount, wNBlocks);                                                                       \
        }                                                                                                              \
    } /* _SetEPCountRxReg */

#define _SetEPRxDblBuf0Count(bEpNum, wCount)                                                                           \
    {                                                                                                                  \
        uint32_t* pdwReg = _pEPTxCount(bEpNum);                                                                        \
        _SetEPCountRxReg(pdwReg, wCount);                                                                              \
    }

/**
*\*\name    _SetEPTxCount/_SetEPRxCount
*\*\fun     sets counter for the tx/rx buffer.
*\*\param   bEpNum: endpoint number.
*\*\param   wCount: Counter value.
*\*\return  none
**/
#define _SetEPTxCount(bEpNum, wCount) (*_pEPTxCount(bEpNum) = wCount)
#define _SetEPRxCount(bEpNum, wCount)                                                                                  \
    {                                                                                                                  \
        uint32_t* pdwReg = _pEPRxCount(bEpNum);                                                                        \
        _SetEPCountRxReg(pdwReg, wCount);                                                                              \
    }

/**
*\*\name    _GetEPTxCount/_GetEPRxCount
*\*\fun     gets counter of the tx buffer.
*\*\param   bEpNum: endpoint number.
*\*\return  Counter value.
**/
#define _GetEPTxCount(bEpNum) ((uint16_t)(*_pEPTxCount(bEpNum)) & 0x3ff)
#define _GetEPRxCount(bEpNum) ((uint16_t)(*_pEPRxCount(bEpNum)) & 0x3ff)

/**
*\*\name    _SetEPDblBuf0Addr/_SetEPDblBuf1Addr
*\*\fun     Sets buffer 0/1 address in a double buffer endpoint.
*\*\param   bEpNum: endpoint number.
*\*\param   wBuf0Addr: buffer 0 address.
*\*\return  none
**/
#define _SetEPDblBuf0Addr(bEpNum, wBuf0Addr)                                                                           \
    {                                                                                                                  \
        _SetEPTxAddr(bEpNum, wBuf0Addr);                                                                               \
    }
#define _SetEPDblBuf1Addr(bEpNum, wBuf1Addr)                                                                           \
    {                                                                                                                  \
        _SetEPRxAddr(bEpNum, wBuf1Addr);                                                                               \
    }

/**
*\*\name    _SetEPDblBuffAddr
*\*\fun     Sets addresses in a double buffer endpoint.
*\*\param   bEpNum: endpoint number.
*\*\param   wBuf0Addr: buffer 0 address.
*\*\param   wBuf1Addr = buffer 1 address.
*\*\return  none
**/
#define _SetEPDblBuffAddr(bEpNum, wBuf0Addr, wBuf1Addr)                                                                \
    {                                                                                                                  \
        _SetEPDblBuf0Addr(bEpNum, wBuf0Addr);                                                                          \
        _SetEPDblBuf1Addr(bEpNum, wBuf1Addr);                                                                          \
    } /* _SetEPDblBuffAddr */

/**
*\*\name    _GetEPDblBuf0Addr/_GetEPDblBuf1Addr
*\*\fun     Gets buffer 0/1 address of a double buffer endpoint.
*\*\param   bEpNum: endpoint number.
*\*\return  none
**/
#define _GetEPDblBuf0Addr(bEpNum) (_GetEPTxAddr(bEpNum))
#define _GetEPDblBuf1Addr(bEpNum) (_GetEPRxAddr(bEpNum))

/**
*\*\name    _SetEPDblBuf0Count/_SetEPDblBuf1Count/_SetEPDblBuffCount
*\*\fun     Gets buffer 0/1 address of a double buffer endpoint.
*\*\param   bEpNum: endpoint number.
*\*\param   bDir: endpoint dir  EP_DBUF_OUT = OUT  EP_DBUF_IN  = IN
*\*\param   wCount: Counter value
*\*\return  none
**/
#define _SetEPDblBuf0Count(bEpNum, bDir, wCount)                                                                       \
    {                                                                                                                  \
        if (bDir == EP_DBUF_OUT)                                                                                       \
        /* OUT endpoint */                                                                                             \
        {                                                                                                              \
            _SetEPRxDblBuf0Count(bEpNum, wCount);                                                                      \
        }                                                                                                              \
        else if (bDir == EP_DBUF_IN)                                                                                   \
            /* IN endpoint */                                                                                          \
            *_pEPTxCount(bEpNum) = (uint32_t)wCount;                                                                   \
    } /* USB_SetEpDblBuf0Cnt*/

#define _SetEPDblBuf1Count(bEpNum, bDir, wCount)                                                                       \
    {                                                                                                                  \
        if (bDir == EP_DBUF_OUT)                                                                                       \
        /* OUT endpoint */                                                                                             \
        {                                                                                                              \
            _SetEPRxCount(bEpNum, wCount);                                                                             \
        }                                                                                                              \
        else if (bDir == EP_DBUF_IN)                                                                                   \
            /* IN endpoint */                                                                                          \
            *_pEPRxCount(bEpNum) = (uint32_t)wCount;                                                                   \
    } /* USB_SetEpDblBuf1Cnt */

#define _SetEPDblBuffCount(bEpNum, bDir, wCount)                                                                       \
    {                                                                                                                  \
        _SetEPDblBuf0Count(bEpNum, bDir, wCount);                                                                      \
        _SetEPDblBuf1Count(bEpNum, bDir, wCount);                                                                      \
    } /* _SetEPDblBuffCount  */

/**
*\*\name    _GetEPDblBuf0Count/_GetEPDblBuf1Count
*\*\fun     Gets buffer 0/1 rx/tx counter for double buffering.
*\*\param   bEpNum: endpoint number.
*\*\return  none
**/
#define _GetEPDblBuf0Count(bEpNum) (_GetEPTxCount(bEpNum))
#define _GetEPDblBuf1Count(bEpNum) (_GetEPRxCount(bEpNum))

extern __IO uint16_t wIstr; /* USB_STS register last read value */

void USB_SetCtrl(uint16_t wRegValue);
void USB_SetSts(uint16_t wRegValue);
void USB_SetAddr(uint16_t wRegValue);
void USB_SetBuftab(uint16_t wRegValue);
uint16_t USB_GetCtrl(void);
uint16_t USB_GetSts(void);
uint16_t USB_GetFn(void);
uint16_t USB_GetAddr(void);
uint16_t USB_GetBTABLE(void);
void USB_SetEndPoint(uint8_t bEpNum, uint16_t wRegValue);
uint16_t USB_GetEndPoint(uint8_t bEpNum);
void USB_SetEpType(uint8_t bEpNum, uint16_t wType);
uint16_t USB_GetEpType(uint8_t bEpNum);
void SetEPTxStatus(uint8_t bEpNum, uint16_t wState);
void SetEPRxStatus(uint8_t bEpNum, uint16_t wState);
void USB_SetDouBleBuferEpStall(uint8_t bEpNum, uint8_t bDir);
uint16_t USB_GetEpTxSts(uint8_t bEpNum);
uint16_t USB_GetEpRxSts(uint8_t bEpNum);
void USB_SetEpTxValid(uint8_t bEpNum);
void USB_SetEpRxValid(uint8_t bEpNum);
uint16_t USB_GetTxStallSts(uint8_t bEpNum);
uint16_t USB_GetRxStallSts(uint8_t bEpNum);
void USB_SetEpKind(uint8_t bEpNum);
void USB_ClrEpKind(uint8_t bEpNum);
void USB_SetStsOut(uint8_t bEpNum);
void USB_ClrStsOut(uint8_t bEpNum);
void USB_SetEpDoubleBufer(uint8_t bEpNum);
void USB_ClrEpDoubleBufer(uint8_t bEpNum);
void USB_ClrEpCtrsRx(uint8_t bEpNum);
void USB_ClrEpCtrsTx(uint8_t bEpNum);
void USB_DattogRx(uint8_t bEpNum);
void USB_DattogTx(uint8_t bEpNum);
void USB_ClrDattogRx(uint8_t bEpNum);
void USB_ClrDattogTx(uint8_t bEpNum);
void USB_SetEpAddress(uint8_t bEpNum, uint8_t bAddr);
uint8_t USB_GetEpAddress(uint8_t bEpNum);
void USB_SetEpTxAddr(uint8_t bEpNum, uint16_t wAddr);
void USB_SetEpRxAddr(uint8_t bEpNum, uint16_t wAddr);
uint16_t USB_GetEpTxAddr(uint8_t bEpNum);
uint16_t USB_GetEpRxAddr(uint8_t bEpNum);
void USB_SetEpCntRxReg(uint32_t* pdwReg, uint16_t wCount);
void USB_SetEpTxCnt(uint8_t bEpNum, uint16_t wCount);
void USB_SetEpRxCnt(uint8_t bEpNum, uint16_t wCount);
uint16_t USB_GetEpTxCnt(uint8_t bEpNum);
uint16_t USB_GetEpRxCnt(uint8_t bEpNum);
void USB_SetEpDblBuf0Addr(uint8_t bEpNum, uint16_t wBuf0Addr);
void USB_SetEpDblBuf1Addr(uint8_t bEpNum, uint16_t wBuf1Addr);
void USB_SetEpDblBuferAddr(uint8_t bEpNum, uint16_t wBuf0Addr, uint16_t wBuf1Addr);
uint16_t USB_GetEpDblBuf0Addr(uint8_t bEpNum);
uint16_t USB_GetEpDblBuf1Addr(uint8_t bEpNum);
void USB_SetEpDblBuferCnt(uint8_t bEpNum, uint8_t bDir, uint16_t wCount);
void USB_SetEpDblBuf0Cnt(uint8_t bEpNum, uint8_t bDir, uint16_t wCount);
void USB_SetEpDblBuf1Cnt(uint8_t bEpNum, uint8_t bDir, uint16_t wCount);
uint16_t USB_GetEpDblBuf0Cnt(uint8_t bEpNum);
uint16_t USB_GetEpDblBuf1Cnt(uint8_t bEpNum);
EP_DBUF_DIR GetEPDblBufDir(uint8_t bEpNum);
void USB_FreeUserBuf(uint8_t bEpNum, uint8_t bDir);
uint16_t USB_ToWord(uint8_t bh, uint8_t bl);
uint16_t USB_ByteSwap(uint16_t wSwW);

#endif /* __USBFSD_REGS_H__ */
