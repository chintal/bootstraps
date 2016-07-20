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

#include "uc_pum.h"
#include "hal_uc.h"
#include "uart_impl.h"

volatile uint8_t __uart_handler_inclusion;

    #if uC_UART0_ENABLED
    /**
     * @brief UART0 TX interrupt handler
     * 
     * Interrupt handler function for TX Complete on UART0.
     * 
     * Called when UART transmission is complete. Application code may need to change
     * this function.
     * 
     */
    static inline void uart0_handler_tx(void);

    /**
     * @brief UART1 RX interrupt handler
     * 
     * Interrupt handler function for RX Complete on UART1.
     * 
     * Called when UART reception is complete. Application code may need to change
     * this function.
     * 
     */
    static inline void uart0_handler_rx(void);


    #if uC_UART0_TYPE == UART_HWIF_USCI_A
    static inline void uart0_handler_rx(void){
        uint8_t rval; 
        rval = HWREG8(uC_UART0_BASE + OFS_UCAxRXBUF);
        if (bytebuf_cGetFree(&uart1_rxbuf)){
            bytebuf_cPush(&uart1_rxbuf, rval, 0x00);
        }
    }
    
    static inline void uart0_handler_tx(void){
        if (bytebuf_cPopulation(&uart0_txbuf) == 1){
            HWREG8(uC_UART0_BASE + OFS_UCAxIE) &= ~UCTXIE;
            uart0_if.state->triggered = 0;
        }
        HWREG8(uC_UART0_BASE + OFS_UCAxTXBUF) = bytebuf_cPopByte(&uart0_txbuf);
    }

    __attribute__((interrupt(uC_UART0_VECTOR)))
    void _uart0_irqhandler(void){
        uint8_t flagreg = HWREG8(uC_UART0_BASE + OFS_UCAxIFG);
        if ( flagreg & UCRXIFG ){
            uart0_handler_rx();
        }
        else if ( flagreg & UCTXIFG ){
            uart0_handler_tx();
        }
    }
    #endif
    #endif
    
    #if uC_UART1_ENABLED
    
    /**
     * @brief UART1 TX interrupt handler
     * 
     * Interrupt handler function for TX Complete on UART1.
     * 
     * Called when UART transmission is complete. Application code may need to change
     * this function.
     * 
     */
    static inline void uart1_handler_tx(void);

    /**
     * @brief UART1 RX interrupt handler
     * 
     * Interrupt handler function for RX Complete on UART1.
     * 
     * Called when UART reception is complete. Application code may need to change
     * this function.
     * 
     */
    static inline void uart1_handler_rx(void);
    
    
    #if uC_UART1_TYPE == UART_HWIF_USCI_A
    static inline void uart1_handler_rx(void){
        uint8_t rval; 
        rval = HWREG8(uC_UART1_BASE + OFS_UCAxRXBUF);
        if (bytebuf_cGetFree(&uart1_rxbuf)){
            bytebuf_cPush(&uart1_rxbuf, rval, 0x00);
        }
    }
    
    static inline void uart1_handler_tx(void){
        if (bytebuf_cPopulation(&uart1_txbuf) == 1){
            HWREG8(uC_UART1_BASE + OFS_UCAxIE) &= ~UCTXIE;
            uart1_if.state->triggered = 0;
        }
        HWREG8(uC_UART1_BASE + OFS_UCAxTXBUF) = bytebuf_cPopByte(&uart1_txbuf);
    }

    __attribute__((interrupt(uC_UART1_VECTOR)))
    void _uart1_irqhandler(void){
        uint8_t flagreg = HWREG8(uC_UART1_BASE + OFS_UCAxIFG);
        if ( flagreg & UCRXIFG ){
            uart1_handler_rx();
        }
        else if ( flagreg & UCTXIFG ){
            uart1_handler_tx();
        }
    }
    #endif
    #endif  


