
#include "bc_uart.h"

void vBackChannelUARTSetup(void)
{

    UCA1CTL1 |= UCSWRST;                    // Reset UCA1 for config
    UCA1CTL0 = 0x00;                        // Configure for UART, No Parity, LSB First, 8 bit
    UCA1CTL1 = UCSSEL__SMCLK;               // Source from SMCLK
    UCA1BRW = 625;                          // 19200 with 12 MHz clock
    UCA1MCTL = 0;                           // No modulation, Oversampling disabled
    UCA1IE = 0;                             // Interrupts Disabled

    P4SEL |= (BIT4 + BIT5);

    UCA1CTL1 &= ~UCSWRST;                    // Reset UCA1 for config
}

void vBackChannelTXchar(uint8_t byte){
    while(UCA1STAT & UCBUSY){};
    UCA1TXBUF = byte;
    return;
}

uint8_t cBackChannelRXchar(void){
    while(UCA1STAT & UCBUSY){};
    return(UCA1RXBUF);
}


