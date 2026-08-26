/**
 * @file    usb_prop.h
 * @brief   USB Device Property declarations for CANable2-N32
 */

#ifndef __USB_PROP_H
#define __USB_PROP_H

#include "stdint.h"
#include "usbfsd_core.h"

/* Line Coding structure (CDC ACM) */
typedef struct
{
    uint32_t bitrate;
    uint8_t  format;
    uint8_t  paritytype;
    uint8_t  datatype;
} LINE_CODING;

/* USB Property callback declarations */
void Virtual_Com_Port_init(void);
void Virtual_Com_Port_Reset(void);
void Virtual_Com_Port_Status_In(void);
void Virtual_Com_Port_Status_Out(void);
USB_Result Virtual_Com_Port_Data_Setup(uint8_t RequestNo);
USB_Result Virtual_Com_Port_NoData_Setup(uint8_t RequestNo);
USB_Result Virtual_Com_Port_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting);
uint8_t *Virtual_Com_Port_GetDeviceDescriptor(uint16_t Length);
uint8_t *Virtual_Com_Port_GetConfigDescriptor(uint16_t Length);
uint8_t *Virtual_Com_Port_GetStringDescriptor(uint16_t Length);
uint8_t *Virtual_Com_Port_GetLineCoding(uint16_t Length);
uint8_t *Virtual_Com_Port_SetLineCoding(uint16_t Length);

void Virtual_Com_Port_GetConfiguration(void);
void Virtual_Com_Port_SetConfiguration(void);
void Virtual_Com_Port_GetInterface(void);
void Virtual_Com_Port_SetInterface(void);
void Virtual_Com_Port_GetStatus(void);
void Virtual_Com_Port_ClearFeature(void);
void Virtual_Com_Port_SetEndPointFeature(void);
void Virtual_Com_Port_SetDeviceFeature(void);
void Virtual_Com_Port_SetDeviceAddress(void);

#endif /* __USB_PROP_H */
