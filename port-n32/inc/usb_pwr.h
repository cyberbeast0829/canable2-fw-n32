/**
 * @file    usb_pwr.h
 * @brief   USB Power management declarations for CANable2-N32
 */

#ifndef __USB_PWR_H
#define __USB_PWR_H

#include "usbfsd_core.h"

typedef enum _RESUME_STATE
{
    RESUME_EXTERNAL,
    RESUME_INTERNAL,
    RESUME_LATER,
    RESUME_WAIT,
    RESUME_START,
    RESUME_ON,
    RESUME_OFF,
    RESUME_ESOF
} RESUME_STATE;

/* Device states */
#define UNCONNECTED  0
#define ATTACHED     1
#define POWERED      2
#define SUSPENDED    3
#define ADDRESSED    4
#define CONFIGURED   5

extern __IO uint32_t bDeviceState;
extern __IO bool     fSuspendEnabled;
extern __IO uint32_t EP[8];

USB_Result PowerOn(void);
USB_Result PowerOff(void);
void Resume(RESUME_STATE eResumeSetVal);
void Suspend(void);

#endif /* __USB_PWR_H */
