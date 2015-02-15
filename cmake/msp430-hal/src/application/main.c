

#include "hal_uc.h"
#include "bc_iface.h"
#include "prbs.h"

volatile uint8_t rval=0;
lfsr16_t prbs;

int main(void)
{
    volatile uint8_t i;
    gpio_conf_output(1,_BV(0));
    gpio_conf_output(4,_BV(7));
    gpio_set_output_low(4,_BV(7));
    gpio_set_output_high(1,_BV(0));
    
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
    res = bc_printchar(0x01, 0x02, 0x01);
    
    gpio_set_output_high(4,_BV(7));
    gpio_set_output_low(1,_BV(0));
    
    while(1){
        res = bc_printchar(i, 0x02, 0x01);
        if(res){   
            i=lfsr_cGetNextByte(&prbs);
        }
    }
    
    return(0);
    
}
