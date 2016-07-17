
#include <msp430.h>
#include <stdlib.h>

void vIntervalTimerSetup(void);

void tick_timer_isr(void) __attribute__((interrupt(TIMER2_A0_VECTOR)));
