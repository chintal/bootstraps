

#include<prbs/prbs.h>
#include<bytebuf/bytebuf.h>
#include "hal_uc.h"
#include "bc_iface.h"

volatile uint8_t rval=0;
lfsr16_t prbs;


static void deferred_exec(void);

static void deferred_exec(void){
    ;
}


static void _initialize_interrupts(void);

static void _initialize_interrupts(void){
    __uart_handler_inclusion = 1;
}


int main(void)
{
    volatile uint8_t i;
    
    _initialize_interrupts();
    
    gpio_conf_output(BOARD_GREEN_LED_PORT,BOARD_GREEN_LED_PIN);
    gpio_conf_output(BOARD_RED_LED_PORT,BOARD_RED_LED_PIN);
    gpio_set_output_high(BOARD_RED_LED_PORT,BOARD_RED_LED_PIN);
    gpio_set_output_low(BOARD_GREEN_LED_PORT,BOARD_GREEN_LED_PIN);
    
    watchdog_hold();
    power_set_full();
    clock_set_default();
    
    global_interrupt_enable();
    
    bc_init();
        
    //Block on Backchannel Interface
    rval = 0;
    while (!rval){
        rval = bc_unhandled_rxb();
    }
    uint8_t cmd;
    cmd = bc_getc();
    bc_discard_rxb();
    
    if (cmd == 'a'){
        // Throughput test. Only byte transmission rate is important. 
        // Error rate is in principle measurable, and easily so. This test is
        // intended to stress test the interface without other firmware 
        // bottlenecks, given the environment within which the firmware is 
        // expected to run (including the buffers, drivers, and USB stack).
        if(bc_reqlock(1, BYTEBUF_TOKEN_SCHAR)){
            bc_putc('a', BYTEBUF_TOKEN_SCHAR, 0);
        }   
        gpio_set_output_low(BOARD_RED_LED_PORT, BOARD_RED_LED_PIN);
        gpio_set_output_high(BOARD_GREEN_LED_PORT, BOARD_GREEN_LED_PIN);
        i = '0';
        while(1){
            if(bc_reqlock(1, BYTEBUF_TOKEN_SCHAR)){
                bc_putc(i, BYTEBUF_TOKEN_SCHAR, 0);
                if (i != 'z'){
                    i ++;
                }
                else{
                    i = '0';
                }
            }
            deferred_exec();
        }
    }
    else if (cmd == 'b'){
        // PRBS BER test. This is not a very useful test, since generation 
        // of the PRBS seems to be the bottleneck. However, the general idea is 
        // to ensure glitch-free transmission under real-ish data loads. 
        // It may be noted that in real use cases, the need to generate the 
        // data may present similar if not narrower bottlenecks.
        
        // Intialize PRBS generator
        lfsr_vInit(&prbs, LFSR_DEFAULT_SEED, LFSR_DEFAULT_TAPS);
        if(bc_reqlock(1, BYTEBUF_TOKEN_SCHAR)){
            bc_putc('b', BYTEBUF_TOKEN_SCHAR, 0);
        }
        gpio_set_output_low(BOARD_RED_LED_PORT, BOARD_RED_LED_PIN);
        gpio_set_output_high(BOARD_GREEN_LED_PORT, BOARD_GREEN_LED_PIN);
        while(1){
            if(bc_reqlock(1, BYTEBUF_TOKEN_SCHAR)){
                bc_putc(lfsr_cGetNextByte(&prbs), BYTEBUF_TOKEN_SCHAR, 0);
            }
            deferred_exec();
        }
    } 
    else if (cmd == 'c'){
        // Raw Throughput test. Actual physical interface capability (along 
        // with USB stack only). No buffering, locking, etc. Whenever it is 
        // possible to send some data, just fill the USB stack buffer and 
        // send it along.
        uart_putc(BOARD_BCIFACE_INTFNUM, 'c');
        gpio_set_output_low(BOARD_RED_LED_PORT, BOARD_RED_LED_PIN);
        gpio_set_output_high(BOARD_GREEN_LED_PORT, BOARD_GREEN_LED_PIN);
        i = '0';
        while(1){
            uart_putc(BOARD_BCIFACE_INTFNUM, i);
            if (i != 'z'){
                i ++;
            }
            else{
                i = '0';
            }
            deferred_exec();
        }
    }
    else{
        while(1);
    }
    
    return(0);
}
