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
 * @file uc_pum_lp5529.h
 * @brief uC PUM for TI Launchpad based on MSP430F5529
 *
 * This file contains the peripheral usage map for the uC in the context
 * of TI Launchpad based on MSP430F5529.
 */

#ifndef uC_PUM_SPECIFIC_H
#define uC_PUM_SPECIFIC_H

/**
 * @name Watchdog Configuration
 */
/**@{*/ 
#define PUM_HAS_WDT             1
#define PUM_WDT_PROVIDER        MSP_WDT_A
/**@}*/ 

/**
 * @name Clock System Configuration
 */
/**@{*/ 

    /**
    * @name High Frequency External Clock Source
    * 
    * This clock frequency should be chosen for each board to be able to 
    * provide the master clock frequency defined / required by the peripheral 
    * implementation. See the clock system configuration implementation for 
    * the target in hal_uc_core.h and core_impl.c and the uC peripherals 
    * library configuration in uc_map_impl.h to determine what the 
    * allowed values are.
    */
    /**@{*/ 
    #define uC_HAS_HF_EXT_CLK      1
    #define uC_HF_EXT_CLK_FRQ      4000000
    #define uC_HF_EXT_TIMEOUT      50000
    /**@}*/ 
    
    /**
    * @name Low Frequency External Clock Source
    */
    /**@{*/ 
    #define uC_HAS_LF_EXT_CLK      1
    #define uC_LF_EXT_CLK_FRQ      32768
    #define uC_LF_EXT_TIMEOUT      50000
    /**@}*/ 
    
/**@}*/ 

/**
 * @name UART Configuration
 */
/**@{*/ 

    /**
    * @name UART 0 Configuration
    */
    /**@{*/ 
    #define uC_UART0_ENABLED       1
    #define uC_UART0_BAUD          19200
    #define uC_UART0_TXBUF_LEN     10
    #define uC_UART0_RXBUF_LEN     10
    #define uC_UART0_FWIF_DEFINED
    /**@}*/ 
    
    /**
    * @name UART 1 Configuration
    */
    /**@{*/ 
    #define uC_UART1_ENABLED       1
    #define uC_UART1_BAUD          256000
    #define uC_UART1_TXBUF_LEN     200
    #define uC_UART1_RXBUF_LEN     100
    #define uC_UART1_FWIF_DEFINED
    /**@}*/ 
    
/**@}*/ 

#endif