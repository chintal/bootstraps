
#include <msp430.h>
#include <stdlib.h>

void vBackChannelUARTSetup(void);
void vBackChannelTXchar(uint8_t byte);
uint8_t cBackChannelRXchar(void);
