

#include "hal_uc.h"
#include "bc_iface.h"
#include "prbs.h"

volatile uint8_t rval=0;
lfsr16_t prbs;

int main(void)
{
    volatile uint8_t i;
    
    gpio_conf_output(BOARD_GREEN_LED_PORT,BOARD_GREEN_LED_PIN);
    gpio_conf_output(BOARD_RED_LED_PORT,BOARD_RED_LED_PIN);
    gpio_set_output_high(BOARD_RED_LED_PORT,BOARD_RED_LED_PIN);
    gpio_set_output_low(BOARD_GREEN_LED_PORT,BOARD_GREEN_LED_PIN);
    
    watchdog_hold();
    power_set_full();
    clock_set_default();
    
    global_interrupt_enable();
    
    bc_init();
    lfsr_vInit(&prbs, LFSR_DEFAULT_SEED, LFSR_DEFAULT_TAPS);
    
    i=lfsr_cGetNextByte(&prbs);
    uint8_t res;
    
    while (!rval){
        rval = bc_unhandledrxb();
    }
    res = bc_printchar(0x01, BYTEBUF_TOKEN_SCHAR, 0x01);
    
    gpio_set_output_high(BOARD_RED_LED_PORT,BOARD_RED_LED_PIN);
    gpio_set_output_low(BOARD_GREEN_LED_PORT,BOARD_GREEN_LED_PIN);
    
    while(1){
        res = bc_printchar(i, BYTEBUF_TOKEN_SCHAR, 0x01);
        if(res){   
            i=lfsr_cGetNextByte(&prbs);
        }
    }
    
    return(0);
    
}
