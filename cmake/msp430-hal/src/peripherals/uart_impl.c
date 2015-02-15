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

#include "hal_uc_uart.h"

#include "driverlib/MSP430F5xx_6xx/gpio.h"


#if PUM_UART1_TYPE == USCI_A

#include "driverlib/MSP430F5xx_6xx/usci_a_uart.h"

uint8_t uart1_txbuffer[PUM_UART1_TXBUF_LEN+5];
uint8_t uart1_rxbuffer[PUM_UART1_RXBUF_LEN+5];
bytebuf uart1_txbuf;
bytebuf uart1_rxbuf;
uint8_t uart1_triggered = 0;

static void _uart1_buffer_init(void);

static void _uart1_buffer_init(void){
    bytebuf_vInit(uart1_txbuffer, PUM_UART1_TXBUF_LEN, &uart1_txbuf);
    bytebuf_vInit(uart1_rxbuffer, PUM_UART1_RXBUF_LEN, &uart1_rxbuf);
}

void uart1_init(void){
    _uart1_buffer_init();
    
    GPIO_setAsPeripheralModuleFunctionInputPin(
        GPIO_PORT_P4,
        GPIO_PIN4 | GPIO_PIN5);
    USCI_A_UART_initParam param = {0};
    param.selectClockSource =   USCI_A_UART_CLOCKSOURCE_SMCLK;
    param.clockPrescalar =      1250;
    param.firstModReg =         0;
    param.secondModReg =        0;
    param.parity =              USCI_A_UART_NO_PARITY;
    param.msborLsbFirst =       USCI_A_UART_LSB_FIRST;
    param.numberofStopBits =    USCI_A_UART_ONE_STOP_BIT;
    param.uartMode =            USCI_A_UART_MODE;
    param.overSampling =        USCI_A_UART_LOW_FREQUENCY_BAUDRATE_GENERATION;
    
    USCI_A_UART_init(UART1_BASE, &param);
    USCI_A_UART_enable(UART1_BASE);  
    USCI_A_UART_clearInterruptFlag(UART1_BASE, USCI_A_UART_RECEIVE_INTERRUPT);
    USCI_A_UART_enableInterrupt(UART1_BASE, USCI_A_UART_RECEIVE_INTERRUPT);
}

uint8_t uart1_vprintf_buf(const char *format, va_list * args){
        
        uint8_t stat, lstat;
        stat = bytebuf_cPushReqBlindLock(&uart1_txbuf, BYTEBUF_TOKEN_PRINT);
        if (stat){
            
            stat = vbprintf(&uart1_txbuf, format, *args);
            
            lstat = bytebuf_cPushRelinquishLock(&uart1_txbuf, BYTEBUF_TOKEN_PRINT);
            uart1_send_trigger();
            if (lstat){
                return stat;
            }
            else{
                return 0;
            }
        }
        else{
            return 0;
        }
}

uint8_t uart1_population_rxbuf(void){
        return bytebuf_cPopulation(&uart1_rxbuf);
}

ATTR_INTERRUPT_VECTOR_UART1
void uart1_irqhandler(void){
    uint8_t flagreg = REGISTER_UART1_INTERRUPT_FLAG;
    if ( flagreg & BIT_UART1_RX_IF ){
        if (bytebuf_cPushReqLock(&uart1_rxbuf, 0x01, 0x03)){
            bytebuf_cPush(&uart1_rxbuf, UART1_RXBUF, 0x03);
        }
        else{
            UART1_RXBUF;
        }
    }
    else if ( flagreg & BIT_UART1_TX_IF ){
        if (uart1_txbuf._population == 1){
            REGISTER_UART1_INTERRUPT_ENABLE &= ~BIT_UART1_TX_IE;
            uart1_triggered = 0;
        }
        UART1_TXBUF = bytebuf_cPopByte(&uart1_txbuf);
    }
}


#else
#error UART Type not recognized.
#endif