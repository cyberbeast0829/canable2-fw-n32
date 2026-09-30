/**
 * @file    usb_endp.c
 * @brief   USB Endpoint callbacks for CANable2-N32 (gs_usb vendor class)
 *
 * Called from the N32 USB interrupt handler (USB_Istr -> USB_CorrectTransferLp).
 *   EP1 IN  (0x81) Bulk — CAN frames device -> host
 *   EP2 OUT (0x02) Bulk — CAN frames host -> device
 */

#include "usbfsd_lib.h"
#include "usb_desc.h"
#include "usbfsd_mem.h"
#include "usb_conf.h"
#include "gs_usb.h"


/**
 * @brief  EP1 IN callback — a bulk IN (device -> host) transfer completed.
 */
void EP1_IN_Callback(void)
{
    gs_usb_ep_in_cb();
}


/**
 * @brief  EP2 OUT callback — bulk OUT data arrived from the host.
 *         Copy it into the gs_usb RX staging buffer and let the protocol
 *         layer handle it; the layer re-arms the endpoint.
 */
void EP2_OUT_Callback(void)
{
    uint32_t len = USB_SilRead(GSUSB_ENDPOINT_OUT,
                               (uint8_t *)gs_usb_rx_buffer());

    if (len > 0 && len <= CAN_DATA_MAX_PACKET_SIZE)
    {
        gs_usb_ep_out_cb(len);
    }
    else
    {
        /* Malformed/oversized: just re-arm. */
        SetEPRxStatus(ENDP2, EP_RX_VALID);
    }
}
