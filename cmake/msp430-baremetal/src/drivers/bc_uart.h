
#include <msp430.h>
#include <stdint.h>

void vBackChannelUARTSetup(void);
void vBackChannelTXchar(uint8_t byte);
uint8_t cBackChannelRXchar(void);
