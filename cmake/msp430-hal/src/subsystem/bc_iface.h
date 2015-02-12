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

    #if BOARD_BCIFACE_PROVIDER == UART1

        #include "hal_uc_uart.h"
        
        /**
         * @brief Initialize the Backchannel Interface.
         */
        static inline void bc_init(void){
            uart1_init();
        }    
        
        /**
         * @brief Send a single character over the backchannel interface
         * @param byte The character to be sent
         * 
         * This function uses the simplest possible method
         * to send a single byte of data. If possible, it 
         * should not use buffers, interrupts, etc.
         * 
         * In a general application, this function would only
         * be used in special circumstances.
         */
        static inline void bc_sendchar(uint8_t byte){
            uart1_sendchar(byte);   
        }

        /**
          * @brief Recieve a single character from UART 1.
          * 
          * This function uses the simplest possible method
          * to recieve a single byte of data. If possible, it 
          * should not use buffers, interrupts, etc.
          * 
          * In a general application, this function would only
          * be used in special circumstances.
          * @return Character recieved
          */
        static inline uint8_t bc_recvchar(void){
            return uart1_recvchar();
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
            rval = uart1_vprintf_buf(format, &args);
            va_end(args);
            return rval;
        }

    #else 
    #error Backchannel Interface Provider not Recognized
    #endif

#endif

#endif