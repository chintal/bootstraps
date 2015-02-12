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

#include "uc_pum.h"

#include "driverlib/MSP430F5xx_6xx/sfr.h"

static inline void global_interrupt_enable(void){
        __enable_interrupt();
}

#if PUM_HAS_WDT == 1
    #if PUM_WDT_PROVIDER == MSP_WDT_A 
        #include "driverlib/MSP430F5xx_6xx/wdt_a.h"
        
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

#include "driverlib/MSP430F5xx_6xx/pmm.h"
#include "driverlib/MSP430F5xx_6xx/ucs.h"

#endif