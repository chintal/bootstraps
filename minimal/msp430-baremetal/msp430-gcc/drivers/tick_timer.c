
#include "tick_timer.h"


void vIntervalTimerSetup(void)
{
    TA2CTL = 0x0000;                        // Clear whatever is there, if any
    TA2CCR0 = 31;                           // Interrupt every 1/1024 seconds
    TA2CTL = TASSEL__ACLK +                 // Source Clock from ACLK
        ID__1 +                             // Input Divider
        MC__UP;                             // Count up to TA2CCR0
    TA2CCTL0 = CCIE;                        // Enable Interrupt on Compare Match
    return;
}


void tick_timer_isr(void){
    P1OUT ^= 1 << 0;
    TA2CCTL0 &= ~CCIFG;                     // Clear Interrupt Flag
}


