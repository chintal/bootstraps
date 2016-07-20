/* 
   Copyright 2015 Quazar Technologies Pvt. Ltd.
   Copyright 2015 Chintalagiri Shashank
   
   This file is part of
   Embedded bootstraps : peripheral usage maps : TI Launchpad MSP420F5529
   
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
 * @file uc_map.h
 * @brief uC Peripheral Map for TI MSP430F5529
 *
 * This file contains the peripheral map for the uC. This map was written 
 * in the context of the TI Launchpad based on MSP430F5529.
 */

#ifndef uC_MAP
#define uC_MAP

#include "uc_pum.h"

/**
 * @name Watchdog Configuration
 */
/**@{*/ 
#define uC_HAS_WDT             1
#define uC_WDT_PROVIDER        MSP_WDT_A
/**@}*/ 

/**
 * @name Clock System Configuration
 */
/**@{*/ 
    /**
    * @name System Clock Configuration
    */
    /**@{*/ 
    
    #define uC_FLL_FRQ_HZ        24000000UL
    #define uC_FLL_FRQ_KHZ       (uC_FLL_FRQ_HZ / 1000)
    #define uC_FLL_MULT          (uC_FLL_FRQ_HZ / uC_HF_EXT_CLK_FRQ)
    
    #define uC_MCLK_FRQ_HZ       24000000UL
    #define uC_MCLK_FRQ_KHZ      (uC_MCLK_FRQ_HZ / 1000)
    #define uC_MCLK_FRQ_MHZ      (uC_MCLK_FRQ_KHZ / 1000)
    
    #define uC_SMCLK_FRQ_HZ      24000000UL
    #define uC_SMCLK_FRQ_KHZ     (uC_SMCLK_FRQ_HZ / 1000)
    #define uC_SMCLK_FRQ_MHZ     (uC_SMCLK_FRQ_KHZ / 1000)
    
    #define uC_ACLK_FRQ_HZ       32768UL
    #define uC_ACLK_FRQ_KHZ      (uC_ACLK_FRQ_HZ / 1000)
    
    /**@}*/ 
    
/**@}*/ 

/**
 * @name UART Configuration
 */
/**@{*/ 

    #define uC_AVAILABLE_UARTS     2

    /**
    * @name UART 0 Configuration
    */
    /**@{*/ 
    #define uC_HAS_UART0           1
    /**@}*/ 
    
    /**
    * @name UART 1 Configuration
    */
    /**@{*/ 
    #define uC_HAS_UART1           1
    /**@}*/ 
    
    #if (uC_UART0_ENABLED + uC_UART1_ENABLED) > 0
        #define uC_INCLUDE_UART_IFACE
    #endif
/**@}*/ 

#endif