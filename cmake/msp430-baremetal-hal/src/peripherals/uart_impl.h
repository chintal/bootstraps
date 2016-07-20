/* 
   Copyright (c)
     (c) 2015-2016 Chintalagiri Shashank, Quazar Technologies Pvt. Ltd.
   
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
#include "uc_map_impl.h"
#include "uc_types_impl.h"

#include <string.h>
#include <printf/printf.h>
#include <bytebuf/bytebuf.h>

#include "msp430-driverlib/MSP430F5xx_6xx/driverlib.h"

#ifdef uC_INCLUDE_UART_IFACE

#include "uart_handlers.h"

typedef enum {UART_HWIF_USCI_A} UART_HWIF_TYPE;

typedef struct{
    UART_HWIF_TYPE type;
    HAL_ADDRESS_t base;
    HAL_BASE_t vector;
}_UART_HWIF_t;

typedef struct{
    uint8_t triggered;
}UART_STATE_t;

typedef struct{
    const _UART_HWIF_t * hwif;
    UART_STATE_t * state;
    bytebuf * const txbuf;
    bytebuf * const rxbuf;
}UART_IF_t;


#define uC_UART0_TYPE          UART_HWIF_USCI_A
#define uC_UART0_BASE          USCI_A0_BASE
#define uC_UART0_VECTOR        USCI_A0_VECTOR

#define uC_PORTSEL_UART0       GPIO_PORT_P3
#define uC_PINSEL_UART0_TX     GPIO_PIN3
#define uC_PINSEL_UART0_RX     GPIO_PIN4

#define uC_UART1_TYPE          UART_HWIF_USCI_A
#define uC_UART1_BASE          USCI_A1_BASE
#define uC_UART1_VECTOR        USCI_A1_VECTOR

#define uC_PORTSEL_UART1       GPIO_PORT_P4
#define uC_PINSEL_UART1_TX     GPIO_PIN4
#define uC_PINSEL_UART1_RX     GPIO_PIN5

extern const UART_IF_t *const uart_if[];

#if uC_UART0_ENABLED
    extern bytebuf uart0_txbuf;
    extern bytebuf uart0_rxbuf;
    extern const UART_IF_t uart0_if;
    
    void uart0_init(void);
#endif
    
#if uC_UART1_ENABLED
    extern bytebuf uart1_txbuf;
    extern bytebuf uart1_rxbuf;
    extern const UART_IF_t uart1_if;
    
    void uart1_init(void);
#endif

static inline uint8_t uart_putc(uint8_t intfnum, uint8_t byte, uint8_t token, uint8_t handlelock){
    uint8_t stat=1;
    if (handlelock){
        stat = bytebuf_cPushReqLock(uart_if[intfnum]->txbuf, 1, token);
    }
    if (stat){
        stat = bytebuf_cPushByte(uart_if[intfnum]->txbuf, byte, token);
        uart_send_trigger(intfnum);
        return stat;
    }
    return 0;
}

static inline uint8_t uart_write(uint8_t intfnum, void* buffer, uint8_t len, uint8_t token){
    uint8_t rval;
    rval = bytebuf_cPushLen(uart_if[intfnum]->txbuf, buffer, len, token);
    uart_send_trigger(intfnum);
    return rval;
}

static inline uint8_t uart_getc(uint8_t intfnum){
    return bytebuf_cPopByte(uart_if[intfnum]->rxbuf);
}

static inline uint8_t uart_read(uint8_t intfnum, void* buffer, uint8_t len){
    return bytebuf_cPopLen(uart_if[intfnum]->rxbuf, buffer, len);
}
    
static inline uint8_t uart_population_rxb(uint8_t intfnum){
    return bytebuf_cPopulation(uart_if[intfnum]->rxbuf);
}

static inline void uart_discard_rxb(uint8_t intfnum){
    bytebuf_vFlush(uart_if[intfnum]->rxbuf);
}

static inline void uart_send_trigger(uint8_t intfnum){
    if (uart_if[intfnum]->hwif->type == UART_HWIF_USCI_A){
        if (!(uart_if[intfnum]->state->triggered)){
            uart_if[intfnum]->state->triggered = 1;
            HWREG8(uart_if[intfnum]->hwif->base + OFS_UCAxIE) |= UCTXIE;
        }
    }
}

static inline uint8_t uart_reqlock(uint8_t intfnum, uint8_t len, uint8_t token){
    if (len){
        return bytebuf_cPushReqLock(uart_if[intfnum]->txbuf, len, token);
    }
    else{
        return bytebuf_cPushReqBlindLock(uart_if[intfnum]->txbuf, token);
    }
}

static inline uint8_t uart_rellock(uint8_t intfnum, uint8_t token){
    return bytebuf_cPushRelinquishLock(uart_if[intfnum]->txbuf, token);
}

static inline void uart_putc_bare(uint8_t intfnum, uint8_t byte){
    if (uart_if[intfnum]->hwif->type == UART_HWIF_USCI_A){
        USCI_A_UART_transmitData(uart_if[intfnum]->hwif->base, byte);
    }
}

static inline uint8_t uart_getc_bare(uint8_t intfnum){
    if (uart_if[intfnum]->hwif->type == UART_HWIF_USCI_A){
        return USCI_A_UART_receiveData(uart_if[intfnum]->hwif->base);
    }
}    
#endif
#endif