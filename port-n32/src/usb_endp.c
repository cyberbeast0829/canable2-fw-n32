/**
 * @file    usb_endp.c
 * @brief   USB Endpoint callbacks for CANable2-N32 (CDC ACM)
 *
 * Called from the N32 USB interrupt handler (USB_Istr -> USB_CorrectTransferLp).
 * These handle data transfer on the CDC bulk endpoints.
 */

#include "usbfsd_lib.h"
#include "usb_desc.h"
#include "usbfsd_mem.h"

/* External: CDC receive callback in usbd_cdc_if.c */
extern void CDC_EP1_OUT_Callback(void);


/**
 * @brief  EP1 IN callback — called when a bulk IN transfer completes.
 *         EP1 IN is used for CDC data device->host.
 */
void EP1_IN_Callback(void)
{
    /* Set NAK to signal we're done with this transfer */
    SetEPTxStatus(ENDP1, EP_TX_NAK);
}


/**
 * @brief  EP1 OUT callback — called when bulk OUT data arrives from host.
 *         EP1 OUT is used for CDC data host->device.
 */
void EP1_OUT_Callback(void)
{
    CDC_EP1_OUT_Callback();
}


/**
 * @brief  EP2 IN callback — called when interrupt IN transfer completes.
 *         EP2 IN is used for CDC serial state notifications.
 */
void EP2_IN_Callback(void)
{
    SetEPTxStatus(ENDP2, EP_TX_NAK);
}
