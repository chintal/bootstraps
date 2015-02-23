/* 
   Copyright 2015 Quazar Technologies Pvt. Ltd.
   Copyright 2015 Chintalagiri Shashank
   
   This file is part of
   Embedded bootstraps : Peripheral driver implementations : MSP430
   
   This library is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published
   by the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>. 
*/

#ifndef USB_IMPL_H
#define USB_IMPL_H

#include "board_pum.h"

#include "USB_config/descriptors.h"
#include "USB_API/USB_Common/device.h"
#include "USB_API/USB_Common/usb.h"
#include "USB_API/USB_CDC_API/UsbCdc.h"
#include "USB_API/USB_HID_API/UsbHid.h"
#include "USB_app/usbConstructs.h"


static inline void hal_usb_setup(void){
    USB_setup(TRUE, TRUE);
}

static inline void hal_usb_enable(void){
    USB_enable();
}

static inline void hal_usb_disable(void){
    USB_disable();
}

static inline void hal_usb_connect(void){
    USB_connect();
}

static inline void hal_usb_disconnect(void){
    USB_disconnect();
}

/**
 * @name USB Connection Statuses 
 */
/**@{*/ 

/** \brief USB Host is not connected */
#define HUSB_ST_DISCONNECTED            ST_PHYS_DISCONNECTED

/** \brief USB Host is connected but not enumerated */
#define HUSB_ST_NOTENUMERATED           ST_PHYS_CONNECTED_NOENUM

/** \brief USB Enumeration in progress */
#define HUSB_ST_ENUMERATING             ST_ENUM_IN_PROGRESS

/** \brief USB is ready for use */
#define HUSB_ST_ACTIVE                  ST_ENUM_ACTIVE

/** \brief Host has placed the device in suspend */
#define HUSB_ST_SUSPENDED               ST_ENUM_SUSPENDED

/** \brief Device suspended before enumeration */
#define HUSB_ST_NOENUM_SUSPENDED        ST_PHYS_CONNECTED_NOENUM_SUSP

/**@}*/ 

static inline uint8_t hal_usb_status(void){
    return USB_connectionState();
}

static inline uint8_t hal_usb_cdcif_txready(uint8_t intfNum){
    uint16_t bytesSent, bytesRecieved;
    uint8_t st;
   
    st = USBCDC_intfStatus(intfNum, &bytesSent, &bytesRecieved);
        
    if ((st & kUSBCDC_busNotAvailable) || (st & kUSBCDC_waitingForSend)){
            return 0;
    }
    return 1;
}

static inline uint8_t hal_usb_cdcif_rxwaiting(uint8_t intfNum){
    return USBCDC_bytesInUSBBuffer(intfNum);
}

static inline void hal_usb_cdcif_discardrxb(uint8_t intfNum){
    USBCDC_rejectData(intfNum);
}


static inline void hal_usb_event_suspend(void){
    board_suspend();
}

static inline void hal_usb_event_resume(void){
    board_resume();
}

static inline void hal_usb_event_reset(void){
    ;
}

static inline void hal_usb_event_CDC_txdone(uint8_t intfNum){
    board_iface_USBCDC_txdhandler(intfNum);
}

#endif