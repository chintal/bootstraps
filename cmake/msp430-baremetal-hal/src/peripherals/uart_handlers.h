/* 
   Copyright (c)
    (c) 2016 Chintalagiri Shashank, Quazar Technologies Pvt. Ltd.
      
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

#ifndef UART_HANDLERS_H
#define UART_HANDLERS_H


#include "hal_uc_uart.h"

extern volatile uint8_t __uart_handler_inclusion;

/**
 * @name UART Interrupt Handlers
 */
/**@{*/ 
#if uC_UART0_ENABLED

/**
 * @brief UART0 interrupt handler
 * 
 * Interrupt handler function for UART0.
 * 
 * This function dispatches interrupts to the correct handler function. This will
 * usually not need to be changed.  
 * 
 */
void _uart0_irqhandler(void);
#endif

#if uC_UART1_ENABLED
/**
 * @brief UART1 interrupt handler
 * 
 * Interrupt handler function for UART1.
 * 
 * This function dispatches interrupts to the correct handler function. This will
 * usually not need to be changed.  
 * 
 */
void _uart1_irqhandler(void);
#endif
/**@}*/ 
#endif
