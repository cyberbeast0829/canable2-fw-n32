/**
 * @file    usb_istr.c
 * @brief   USB ISTR events interrupt service routine
 *
 * Based on ODrive/Nations usb_istr.c.  Provides USB_Istr() and the
 * endpoint callback function pointer arrays.
 */

#include "usbfsd_lib.h"
#include "usb_prop.h"
#include "usb_pwr.h"
#include "usb_conf.h"

__IO uint16_t wIstr;
__IO uint8_t  bIntPackSOF   = 0;
__IO uint32_t esof_counter  = 0;
__IO uint32_t wCNTR         = 0;

/* Forward declarations of endpoint callbacks (defined in usb_endp.c) */
extern void EP1_IN_Callback(void);
extern void EP1_OUT_Callback(void);
extern void EP2_IN_Callback(void);

/* endpoint callback arrays */
void (*pEpInt_IN[7])(void) = {
    EP1_IN_Callback,
    EP2_IN_Callback,
    EP3_IN_Callback,
    EP4_IN_Callback,
    EP5_IN_Callback,
    EP6_IN_Callback,
    EP7_IN_Callback,
};

void (*pEpInt_OUT[7])(void) = {
    EP1_OUT_Callback,
    EP2_OUT_Callback,
    EP3_OUT_Callback,
    EP4_OUT_Callback,
    EP5_OUT_Callback,
    EP6_OUT_Callback,
    EP7_OUT_Callback,
};


void USB_Istr(void)
{
    wIstr = _GetISTR();

#if (IMR_MSK & STS_CTRS)
    if (wIstr & STS_CTRS & wInterrupt_Mask)
    {
        USB_CorrectTransferLp();
    }
#endif

#if (IMR_MSK & STS_RST)
    if (wIstr & STS_RST & wInterrupt_Mask)
    {
        _SetISTR((uint16_t)CLR_RST);
        Device_Property.Init();
        Device_Property.Reset();
    }
#endif

#if (IMR_MSK & STS_DOVR)
    if (wIstr & STS_DOVR & wInterrupt_Mask)
    {
        _SetISTR((uint16_t)CLR_DOVR);
    }
#endif

#if (IMR_MSK & STS_ERROR)
    if (wIstr & STS_ERROR & wInterrupt_Mask)
    {
        _SetISTR((uint16_t)CLR_ERROR);
    }
#endif

#if (IMR_MSK & STS_WKUP)
    if (wIstr & STS_WKUP & wInterrupt_Mask)
    {
        _SetISTR((uint16_t)CLR_WKUP);
        Resume(RESUME_EXTERNAL);
    }
#endif

#if (IMR_MSK & STS_SUSPD)
    if (wIstr & STS_SUSPD & wInterrupt_Mask)
    {
        if (fSuspendEnabled)
            Suspend();
        else
            Resume(RESUME_LATER);
        _SetISTR((uint16_t)CLR_SUSPD);
    }
#endif

#if (IMR_MSK & STS_SOF)
    if (wIstr & STS_SOF & wInterrupt_Mask)
    {
        _SetISTR((uint16_t)CLR_SOF);
        bIntPackSOF++;
    }
#endif

#if (IMR_MSK & STS_ESOF)
    {
        uint32_t i = 0;
        __IO uint32_t EP[8];
        if (wIstr & STS_ESOF & wInterrupt_Mask)
        {
            _SetISTR((uint16_t)CLR_ESOF);
            if ((_GetFNR() & FN_RXDP) != 0)
            {
                esof_counter++;
                if ((esof_counter > 3) && ((_GetCNTR() & CTRL_FSUSPD) == 0))
                {
                    wCNTR = _GetCNTR();
                    for (i = 0; i < 8; i++)
                        EP[i] = _GetENDPOINT(i);
                    wCNTR |= CTRL_FRST;
                    _SetCNTR(wCNTR);
                    wCNTR &= ~CTRL_FRST;
                    _SetCNTR(wCNTR);
                    while ((_GetISTR() & STS_RST) == 0);
                    _SetISTR((uint16_t)CLR_RST);
                    Device_Property.Init();
                    Device_Property.Reset();
                }
            }
            else
            {
                esof_counter = 0;
            }
        }
    }
#endif
}
