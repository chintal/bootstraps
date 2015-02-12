/* 
   Copyright 2015 Quazar Technologies Pvt. Ltd.
   Copyright 2015 Chintalagiri Shashank
    
   This file is part of
   Embedded bootstraps : hal-uC
   
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
 * @file hal_uc_uart.h
 * @brief HAL for UART peripherals
 *
 * This file is the hardware abstraction layer for uC UART interfaces
 * 
 * @see uart_impl.h 
 * @see uart_impl.c
 */

#ifndef HAL_UC_UART_H
#define HAL_UC_UART_H

#include "uc_pum.h"
#include <stdarg.h>
// Set up the API

#if PUM_HAS_UART1 == 1
/**
 * @name UART1 API Functions
 */
/**@{*/ 

/**
 * Initialize UART. Config parameters for the UART are defined in PUM.
 */
void uart1_init(void);

/**
 * @brief Send a single character over UART 1
 * @param byte The character to be sent
 * 
 * This function uses the simplest possible method
 * to send a single byte of data. It should not use 
 * buffers, interrupts, etc.
 * 
 * In a general application, this function would only
 * be used in special circumstances.
 */
static inline void uart1_sendchar(uint8_t byte);

/**
 * @brief Trigger UART 1 Send.
 * 
 * Trigger the transmission of data within the UART 1 
 * send buffer. This buffer would typically be a ::bytebuf,
 * though the implentation could use whatever it wants.
 * 
 * This function should be as optimized as possible.
 * 
 * Buffer preparation should be done by other functions.
 * @see uart1_printstr_buf()
 */
static inline void uart1_send_trigger(void);

/**
 * @brief UART1 interrupt handler
 * 
 * Interrupt handler function for UART1.
 * 
 * In the present design, the same handler handles both TX and 
 * RX interrupts. This should eventually be replaced with a 
 * dispatch. 
 * 
 * @see uart1_send_trigger()
 */

void uart1_irqhandler(void);


/**
 * @brief Recieve a single character from UART 1.
 * 
 * This function uses the simplest possible method
 * to recieve a single byte of data. It should not use 
 * buffers, interrupts, etc.
 * 
 * In a general application, this function would only
 * be used in special circumstances.
 * @return Character recieved
 */
static inline uint8_t uart1_recvchar(void);


/**
 * @brief TX buffer prep function - printf
 * 
 * Print to the UART interface via a printf-like function. 
 * This function should be callable identically to printf. 
 * If only a subset of the format strings are allowed,
 * this should be documented by the implementation.
 * 
 * The implemetation of printf.h can be taken as the  
 * least-common-denominator implementation for the moment.
 * 
 * @note float should perhaps be added to the implementation
 * 
 * @see uart1_send_trigger()
 * @param *format subset of the standard printf format.
 * @param *args pointer to stdarg.h var_list instance.
 * @return 0 for error, number of characters written for success.
 */
uint8_t uart1_vprintf_buf(const char *format, va_list *args);

/**@}*/ 
#endif

// Set up the implentation
#include "uart_impl.h"

#endif

