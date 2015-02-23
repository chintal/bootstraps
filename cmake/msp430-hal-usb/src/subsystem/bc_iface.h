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

#include "board_pum.h"
#include "printf.h"
#include "bytebuf.h"
#include "uc_types.h"

#if BOARD_HAS_BCIFACE == 1

    static inline void bc_init(void);
    static inline BYTEBUF_SIZE_t bc_printf(const char *format, ...);
    BYTEBUF_SIZE_t bc_vprintf(const char *format, va_list * args);
    
        

    #if BOARD_BCIFACE_PROVIDER == BOARD_BCIFACE_PROVIDER_UART1
         
        #include "bc_iface_uart.h"
        
    #elif BOARD_BCIFACE_PROVIDER == BOARD_BCIFACE_PROVIDER_USB

        #include "bc_iface_usb.h"
        
    #else 
    #error Backchannel Interface Provider not Recognized
    #endif

#endif


