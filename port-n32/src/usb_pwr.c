/**
 * @file    usb_pwr.c
 * @brief   USB Power management for CANable2-N32
 *
 * Based on ODrive usb_pwr.c, stripped of FreeRTOS dependencies.
 */

#include "usbfsd_lib.h"
#include "usb_conf.h"
#include "usb_pwr.h"

__IO uint32_t bDeviceState = UNCONNECTED;
__IO bool     fSuspendEnabled  = true;
__IO uint32_t EP[8];

struct
{
    __IO RESUME_STATE eState;
    __IO uint8_t bESOFcnt;
} ResumeS;

__IO uint32_t remotewakeupon = 0;


USB_Result PowerOn(void)
{
    uint16_t wRegVal;

    /* CNTR_PWDN = 0 */
    wRegVal = CTRL_FRST;
    _SetCNTR(wRegVal);

    /* CTRL_FRST = 0 */
    wInterrupt_Mask = 0;
    _SetCNTR(wInterrupt_Mask);

    /* Clear pending interrupts */
    _SetISTR(0);

    /* Set interrupt mask: Reset, Suspend, Wakeup */
    wInterrupt_Mask = CTRL_RSTM | CTRL_SUSPDM | CTRL_WKUPM;
    _SetCNTR(wInterrupt_Mask);

    return Success;
}


USB_Result PowerOff(void)
{
    _SetCNTR(CTRL_FRST);
    _SetISTR(0);
    _SetCNTR(CTRL_FRST + CTRL_PD);
    return Success;
}


void Suspend(void)
{
    uint32_t i;

    uint16_t wCNTR = _GetCNTR();
    wCNTR |= CTRL_FSUSPD;
    _SetCNTR(wCNTR);
    wCNTR = _GetCNTR();
    if (wCNTR & CTRL_FSUSPD)
    {
        ResumeS.eState = RESUME_OFF;
        wCNTR = _GetCNTR();
        wCNTR |= CTRL_LP_MODE;
        _SetCNTR(wCNTR);
        for (i = 0; i < 8; i++)
            EP[i] = _GetENDPOINT(i);
    }
}


void Resume(RESUME_STATE eResumeSetVal)
{
    uint32_t i;

    if (eResumeSetVal != RESUME_ESOF)
        ResumeS.eState = eResumeSetVal;

    switch (ResumeS.eState)
    {
    case RESUME_EXTERNAL:
        Device_Property.Reset();
        ResumeS.eState = RESUME_OFF;
        break;

    case RESUME_INTERNAL:
        Device_Property.Reset();
        ResumeS.eState = RESUME_OFF;
        break;

    case RESUME_LATER:
        ResumeS.bESOFcnt = 2;
        ResumeS.eState = RESUME_WAIT;
        break;

    case RESUME_WAIT:
        ResumeS.bESOFcnt--;
        if (ResumeS.bESOFcnt == 0)
            ResumeS.eState = RESUME_START;
        break;

    case RESUME_START:
        ResumeS.eState = RESUME_ON;
        break;

    case RESUME_ON:
        ResumeS.eState = RESUME_OFF;
        break;

    case RESUME_OFF:
    case RESUME_ESOF:
    default:
        ResumeS.eState = RESUME_OFF;
        break;
    }
}
