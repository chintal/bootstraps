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

#ifndef CORE_IMPL_H
#define CORE_IMPL_H

#include "uc_map_impl.h"

#include "msp430-driverlib/MSP430F5xx_6xx/driverlib.h"

static inline void global_interrupt_enable(void){
    __enable_interrupt();
}

static inline void global_interrupt_disable(void){
    __disable_interrupt();
}


#define _uC_MCLK_DIV         (uC_FLL_FRQ_HZ / uC_MCLK_FRQ_HZ)

#if _uC_MCLK_DIV == 1
    #define uC_MCLK_DIV         UCS_CLOCK_DIVIDER_1
#elif _uC_MCLK_DIV == 2
    #define uC_MCLK_DIV         UCS_CLOCK_DIVIDER_2
#elif _uC_MCLK_DIV == 4
    #define uC_MCLK_DIV         UCS_CLOCK_DIVIDER_4
#elif _uC_MCLK_DIV == 8
    #define uC_MCLK_DIV         UCS_CLOCK_DIVIDER_8
#elif _uC_MCLK_DIV == 16
    #define uC_MCLK_DIV         UCS_CLOCK_DIVIDER_16
#else
    #error MCLK of uC_MCLK_FRQ_HZ not viable with system uC_FLL_FRQ_HZ
#endif

#define _uC_SMCLK_DIV         (uC_FLL_FRQ_HZ / uC_SMCLK_FRQ_HZ)

#if _uC_SMCLK_DIV == 1
    #define uC_SMCLK_DIV        UCS_CLOCK_DIVIDER_1
#elif _uC_SMCLK_DIV == 2
    #define uC_SMCLK_DIV        UCS_CLOCK_DIVIDER_2
#elif _uC_SMCLK_DIV == 4
    #define uC_SMCLK_DIV        UCS_CLOCK_DIVIDER_4
#elif _uC_SMCLK_DIV == 8
    #define uC_SMCLK_DIV        UCS_CLOCK_DIVIDER_8
#elif _uC_SMCLK_DIV == 16
    #define uC_SMCLK_DIV        UCS_CLOCK_DIVIDER_16
#else
    #error SMCLK of uC_SMCLK_FRQ_HZ not viable with system uC_FLL_FRQ_HZ
#endif



    
#if uC_HAS_WDT == 1
    #if uC_WDT_PROVIDER == MSP_WDT_A 
        
        static inline void watchdog_hold(void){
            WDT_A_hold(WDT_A_BASE);
        }
        
        static inline void watchdog_start(void){
            WDT_A_start(WDT_A_BASE);
        }
        
        static inline void watchdog_clear(void){
            WDT_A_resetTimer(WDT_A_BASE);
        }
        
    #else
        #error WDT Provider not recognized
    #endif

#else

    static inline void watchdog_hold(){
        NOT_IMPLEMENTED_STUB();
    }
    static inline void watchdog_start(){
        NOT_IMPLEMENTED_STUB();
    }
    static inline void watchdog_clear(){
        NOT_IMPLEMENTED_STUB();
    }
    static inline void watchdog_init(){
        NOT_IMPLEMENTED_STUB();
    }

#endif

#endif