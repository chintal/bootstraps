
#include <msp430.h>

/* Standard includes. */
#include <stdlib.h>

/* Library Includes */

/* MSP430 Peripheral Drivers */
#include "core_init.h"
#include "bc_uart.h"
#include "tick_timer.h"
/* Application Includes */





void vIOSetup(void);

void vIOSetup(void)
{
    P1DIR |= BIT0;
    P1OUT |= BIT0;

    P4DIR |= BIT7;
    P4OUT |= BIT7;
    return;
}


int main(void)
{
    vHardwareCoreSetup();
    vIntervalTimerSetup();
    vBackChannelUARTSetup();
    vIOSetup();
    __enable_interrupt();
    while(1){
        vBackChannelTXchar('a');
    }
    return(0);
}
