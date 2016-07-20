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
 * @file bc_iface.h
 * @brief Backchannel Interface API
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

#include"board_pum.h"

#if BOARD_HAS_BCIFACE == 1
    static inline void bc_init(void);
    
    static inline uint8_t bc_reqlock(uint8_t len, uint8_t token);
    static inline uint8_t bc_putc(uint8_t byte, uint8_t token, uint8_t handlelock);
    static inline uint8_t bc_printf(const char *format, ...);
    
    static inline uint8_t bc_getc(void);
    static inline uint8_t bc_unhandled_rxb(void);
    static inline void bc_discard_rxb(void);

    #if BOARD_BCIFACE_TYPE == BCI_UART

        #include "hal_uc_uart.h"
        
        /**
         * @brief Initialize the Backchannel Interface.
         */
        static inline void bc_init(void){
            uart_init(BOARD_BCIFACE_INTFNUM);
        }    
        
        static inline uint8_t bc_reqlock(uint8_t len, uint8_t token){
            return uart_reqlock(BOARD_BCIFACE_INTFNUM, len, token);
        }
        
        static inline uint8_t bc_rellock(uint8_t token){
            return uart_rellock(BOARD_BCIFACE_TYPE, token);
        }
        
        /**
          * @brief Print a single character to the backchannel interface
          * 
          * Send a single character via the backchannel interface
          * 
          * @param byte byte to be sent.
          * @param token token against which buffer lock should be obtained 
          *              and/or used.
          * @param handlelock If 1, the function will deal with interacting
          *              with the underlying locking mechanism. If not, it
          *              assumes you already hold the necessary locks.
          * @warning If the locking is left to this function, it will give up
          *          immediately if the lock is held elsewhere. You should 
          *          check the return value of the function if the send is 
          *          critical.
          * @return 0 for error, 1 for success.
          */
        static inline uint8_t bc_putc(uint8_t byte, uint8_t token, uint8_t handlelock){
            return uart_putc(BOARD_BCIFACE_INTFNUM, byte, token, handlelock);
        }
        
        static inline uint8_t bc_write(void *buffer, uint8_t len, uint8_t token){
            return uart_write(BOARD_BCIFACE_INTFNUM, buffer, len, token);
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
        static inline uint8_t bc_printf(const char *format, ...){
            uint8_t rval;
            va_list args;
            va_start( args, format );
            rval = uart_vprintf_buf(BOARD_BCIFACE_INTFNUM, format, &args);
            va_end(args);
            return rval;
        }
        
        static inline uint8_t bc_unhandled_rxb(void){
            return uart_population_rxb(BOARD_BCIFACE_INTFNUM);
        }
        
        static inline uint8_t bc_getc(void){            
            return uart_getc(BOARD_BCIFACE_INTFNUM);
        }
        
        static inline uint8_t bc_read(void *buffer, uint8_t len){
            return uart_read(BOARD_BCIFACE_INTFNUM, buffer, len);
        }
        
        static inline void bc_discard_rxb(){
            uart_discard_rxb(BOARD_BCIFACE_INTFNUM);
        }

    #else 
    #error Backchannel Interface Provider not Recognized
    #endif

#endif

#endif