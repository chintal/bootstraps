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

#ifndef UART_IMPL_H
#define UART_IMPL_H

#include "uc_pum.h"
#include "printf.h"

#if PUM_UART1_TYPE == PUM_UART_TYPE_USCI_A
    #include "driverlib/MSP430F5xx_6xx/usci_a_uart.h"
     
    #if PUM_UART1_MODNUM == 1
        #define UART1_BASE    USCI_A1_BASE
        #define UART1_VECT    USCI_A1_VECTOR
    #endif
    
    #define ATTR_INTERRUPT_VECTOR_UART1 __attribute__((interrupt(UART1_VECT)))
    
    #define REGISTER_UART1_INTERRUPT_ENABLE  UCA1IE
    #define BIT_UART1_TX_IE                  _BV(1)
    #define BIT_UART1_RX_IE                  _BV(0)

    #define REGISTER_UART1_INTERRUPT_FLAG    UCA1IFG
    #define BIT_UART1_TX_IF                  _BV(1)
    #define BIT_UART1_RX_IF                  _BV(0)

    #define UART1_TXBUF                      UCA1TXBUF
    #define UART1_RXBUF                      UCA1RXBUF
    
    extern bytebuf uart1_txbuf;
    extern bytebuf uart1_rxbuf;
    extern uint8_t uart1_triggered;
    
    static inline void uart1_sendchar(uint8_t byte){
        USCI_A_UART_transmitData(UART1_BASE, byte);
    }

    static inline void uart1_send_trigger(void){
        if (!uart1_triggered){
            uart1_triggered = 1;
            REGISTER_UART1_INTERRUPT_ENABLE |= BIT_UART1_TX_IE;
        }
    }
    
    static inline uint8_t uart1_sendchar_buf(uint8_t byte, uint8_t token, uint8_t handlelock){
        uint8_t stat=1;
        if (handlelock){
            stat = bytebuf_cPushReqLock(&uart1_txbuf, 1, token);
        }
        if (stat){
            stat = bytebuf_cPush(&uart1_txbuf, byte, token);
            uart1_send_trigger();
            return stat;
        }
        return 0;
    }
    
    static inline uint8_t uart1_recvchar(void){
        return USCI_A_UART_receiveData(UART1_BASE);
    }
    
#else
    #error UART Type Unrecognized
#endif

#endif