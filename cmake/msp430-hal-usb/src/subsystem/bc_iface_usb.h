/* 
   Copyright 2015 Quazar Technologies Pvt. Ltd.
   Copyright 2015 Chintalagiri Shashank
   
   This file is part of
   Embedded bootstraps : Subsystem Interfaces
   
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

/**
 * @file bc_iface_usb.h
 * @brief Backchannel Interface API, USB implementation
 *
 * This file is the API for the Backchannel Interface. 
 * 
 * Wherever the interface simply proxies to an underlying implementation 
 * function, a simple inline stub here is sufficient. In case the functions 
 * require additional logic, a declaration may be made here with the definition
 * in bc_iface.c, for subsequent compiling and linking.
 * 
 */

#ifndef BCIFACE_H
#define BCIFACE_H

#include "board_pum.h"

#if BOARD_HAS_BCIFACE == 1

    #if BOARD_BCIFACE_PROVIDER == BOARD_BCIFACE_PROVIDER_USB

        #include "hal_uc_usb.h"
        #include "bytebuf.h"
        
        #define BOARD_BCIFACE_TXBUFFER_LEN (PUM_USB_EP_BUFSIZE * BOARD_BCIFACE_TXBUFFER_LMUL)
        
        //Extra USB specific functions
        extern bytebuf bcif_txbuf;
        void bcusb_init(void);
        void bcusb_send_trigger(void);
        
        /**
         * @brief Initialize the Backchannel Interface.
         */
        static inline void bc_init(void){
            bcusb_init();
        }    
        
        /**
          * @brief Print to backchannel interface.
          * 
          * Print to the backchannel interface via a printf-like 
          * function. This function should be callable identically to
          * printf. If only a subset of the format strings are allowed,
          * this should be documented by the implementation.
          *   
          * @param *format subset of the standard printf format.
          * @return 0 for error, number of characters written for success.
          */
        BYTEBUF_SIZE_t bc_printf(const char *format, ...){
            BYTEBUF_SIZE_t rval;
            va_list args;
            va_start( args, format );
            rval = bc_vprintf(format, &args);
            va_end(args);
            return rval;
        }
        
        /**
          * @brief Print a single character to the backchannel interface
          * 
          * Send a single character via the backchannel interface. The caller
          * should ensure that the lock on the buffer is already held. 
          * 
          * @param byte byte to be sent.
          * @param token token against which buffer lock is held.
          * 
          * @return 0 for error, 1 for success.
          */
        static inline uint8_t bc_printchar(uint8_t byte, uint8_t token);
        
        static inline uint8_t bc_printchar(uint8_t byte, uint8_t token){
            uint8_t stat = bytebuf_cPush(&bcif_txbuf, byte, token);
            if (stat) {
                bcusb_send_trigger();
            }
            return stat;
        }
        
        static inline uint8_t bc_unhandledrxb(void){
           return hal_usb_cdcif_rxwaiting(BOARD_BCIFACE_USB_INTF);
        }
        
        static inline void bc_discardrxb(void){
           hal_usb_cdcif_discardrxb(BOARD_BCIFACE_USB_INTF);
        }

    #else 
    #error Backchannel Interface Provider not Recognized
    #endif

#endif

#endif