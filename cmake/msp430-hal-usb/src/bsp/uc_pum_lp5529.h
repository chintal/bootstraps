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
#define PUM_WDT_PROVIDER        PUM_WDT_PROVIDER_MSP_WDT_A
/**@}*/ 

/**
 * @name Clock System Configuration
 */
/**@{*/ 

    /**
    * @name High Frequency External Clock Source
    */
    /**@{*/ 
    #define PUM_HAS_HF_EXT_CLK      1
    #define PUM_HF_EXT_CLK_FRQ      4000000
    #define PUM_HF_EXT_TIMEOUT      50000
    /**@}*/ 
    
    /**
    * @name Low Frequency External Clock Source
    */
    /**@{*/ 
    #define PUM_HAS_LF_EXT_CLK      1
    #define PUM_LF_EXT_CLK_FRQ      32768
    #define PUM_LF_EXT_TIMEOUT      50000
    /**@}*/ 
    
    /**
    * @name System Clock Configuration
    */
    /**@{*/ 
    #define PUM_SYSCLK_FRQ_MHZ      24
    #define PUM_SYSCLK_FRQ_KHZ      24000
    #define PUM_SYSCLK_FRQ_HZ       24000000
    #define PUM_SYSCLK_RATIO        6
    /**@}*/ 
    
/**@}*/ 

/**
 * @name UART Configuration
 */
/**@{*/ 

    /**
    * @name UART 1 Configration
    */
    /**@{*/ 
    #define PUM_HAS_UART1           1
    //UART_1 definitions
    #define PUM_UART1_BAUD          19200
    #define PUM_UART1_TYPE          PUM_UART_TYPE_USCI_A
    #define PUM_UART1_MODNUM        1
    #define PUM_UART1_TXBUF_LEN     200
    #define PUM_UART1_RXBUF_LEN     20
    /**@}*/ 
    
/**@}*/ 

/**
 * @name USB Configuration
 */
/**@{*/ 
#define PUM_HAS_USB             1

// USB DMA Defintions here are only here for information. The actual
// configurations are made from within the USB implementation, which
// does not care about what's kept here. The definitions within the 
// implementation are the canonical configurations and those here 
// should be manually kept in sync with them. For MSP430, these 
// configs originate in the DescriptorTool.
#define PUM_USB_USES_DMA        1
#define PUM_USB_DMA_CHANNEL     0
#define PUM_USB_EP_BUFSIZE      64
/**@}*/ 


#endif