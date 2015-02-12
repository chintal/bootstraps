

#include "bc_iface.h"
#include "hal_uc.h"

int l;

int main(void)
{
    
    gpio_conf_output(1,_BV(0));
    gpio_conf_output(4,_BV(7));
    gpio_set_output_low(4,_BV(7));
    gpio_set_output_high(1,_BV(0));
    
    watchdog_hold();
    power_set_full();
    clock_set_default();
    
    global_interrupt_enable();
    
    bc_init();
    
    gpio_set_output_high(4,_BV(7));
    gpio_set_output_low(1,_BV(0));
    volatile int i = -10;
    
    l = bc_printf("%d 0x%x 0X%X, %ld, %c, %%, %%",100, 100, 100, 165536, 'c');
    bc_printf("  :::: %d", l);
    
    while(1){
        
    }
    
    return(0);
    
}
