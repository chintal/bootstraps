

#include "bc_iface.h"
#include "hal_uc_usb.h"

uint8_t bcif_txbuffer[BOARD_BCIFACE_TXBUFFER_LEN + 5];
bytebuf bcif_txbuf;


//USB will take care of it's own initialization. Here we only init the
//necessary functions and structures to interact with it.            
void bcusb_init(void){
    bcif_tx_inprogress = 0;
    bytebuf_vInit(bcif_txbuffer, BOARD_BCIFACE_TXBUFFER_LEN, &bcif_txbuf);
    return;
}

void bcusb_send_trigger(void)
{
    //If USB transfer already is progress, do nothing. If it isnt, transmit 
    //whatever is in the buffer.
    if (!bcif_tx_inprogress){
        BYTEBUF_SIZE_t calcl=0;
        uint8_t flag;
        BYTEBUF_SIZE_t size = bytebuf_cGetChunkLen(&bcif_txbuf, &flag);
        
        if (!size) {
            //nothing to do 
            return;
        }
        if (flag){
            //We're straddling a rollover. Send whatever you can.
            bcif_usb_active_chunksize = size;
        }
        else{
            //Normal buffer alignment calculations.
            if (size < PUM_USB_EP_BUFSIZE){
                // Wait for more data to come in
                return;
            }
            while ((size - calcl) >= PUM_USB_EP_BUFSIZE){
                // Send as many integral ep buffer lengths as possible.
                calcl += PUM_USB_EP_BUFSIZE;
            }
            bcif_usb_active_chunksize = calcl-1;
        }
        bcif_tx_inprogress = 1;
        USBCDC_sendData(bcif_txbuf._outp, 
                        bcif_usb_active_chunksize, 
                        BOARD_BCIFACE_USB_INTF);
        // Reporting the transmit to the buffer is left to the event handler 
        // function, called via 
        //     Underlying API call :: USBCDC_handleSendCompleted ->
        //                HAL call :: hal_usb_event_CDC_txdone (inline) ->
        //                BSP call :: board_iface_USBCDC_txdhandler ->
        //      Deferred Exec call :: via main(), if bcif_handle_txdone
    }
}

BYTEBUF_SIZE_t bc_vprintf(const char *format, va_list * args){
        BYTEBUF_SIZE_t stat;
        uint8_t lstat;
        stat = bytebuf_cPushReqBlindLock(&bcif_txbuf, BYTEBUF_TOKEN_PRINT);
        if (stat){    
            stat = vbprintf(&bcif_txbuf, format, *args);
            lstat = bytebuf_cPushRelinquishLock(&bcif_txbuf, BYTEBUF_TOKEN_PRINT);
            bcusb_send_trigger();
            if (lstat){
                return stat;
            }
            else{
                return 0;
            }
        }
        else{
            return 0;
        }
}
