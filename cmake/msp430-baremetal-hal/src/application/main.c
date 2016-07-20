
#include<bytebuf/bytebuf.h>
#include<prbs/prbs.h>
#include<ucdm/ucdm.h>
#include<modbus/modbus.h>

#include "uc_pum.h"
#include "hal_uc.h"
#include "bc_iface.h"
#include "devicemap.h"

volatile uint8_t rval=0;
lfsr16_t prbs;

const char test_str[] = "0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz";
uint8_t c;
uint8_t tbuffer[20];

uint8_t DMAP_MAXREGS = DMAP_MAX_REGISTERS;
uint16_t ucdm_register[DMAP_MAX_REGISTERS];
uint8_t  ucdm_acctype[DMAP_MAX_REGISTERS];
void ( *ucdm_rw_handler[DMAP_MAX_REGISTERS] )(uint8_t);
void ( *ucdm_bw_handler[DMAP_MAX_REGISTERS] )(uint8_t, uint16_t);

const uint8_t ucdm_modbus_base_address = UCDM_MODBUS_BASE_ADDRESS;


static void deferred_exec(void);

static void deferred_exec(void){
    ;
}


static void _bc_init(void);

static void _bc_init(void)
{
    bc_init();
}


static void _ucdm_init(void);

static void _ucdm_init(void)
{
    ucdm_init();
}


static void _modbus_init(void);

static void _modbus_init(void)
{
    modbus_init();
}


static void _initialize_interrupts(void);

static void _initialize_interrupts(void){
    // Needed to ensure linker includes interrupt handlers 
    // in the output.
    __uart_handler_inclusion = 1;
}


static void _main_serial_test(void);

static void _main_serial_test(void){
    volatile uint8_t i;
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
        
        while(1){
            if(bc_reqlock(75, BYTEBUF_TOKEN_SCHAR)){
                bc_write((void *)(&test_str[0]), 75, BYTEBUF_TOKEN_SCHAR);
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
        // with USB stack only, if CDC). No buffering, locking, etc. Whenever 
        // it is possible to send some data, just fill the interface buffer 
        // and send it along.
        uart_putc_bare(BOARD_BCIFACE_INTFNUM, 'c');
        gpio_set_output_low(BOARD_RED_LED_PORT, BOARD_RED_LED_PIN);
        gpio_set_output_high(BOARD_GREEN_LED_PORT, BOARD_GREEN_LED_PIN);
        i = '0';
        while(1){
            uart_putc_bare(BOARD_BCIFACE_INTFNUM, i);
            if (i != 'z'){
                i ++;
            }
            else{
                i = '0';
            }
            deferred_exec();
        }
    }
    else if (cmd == 'd'){
        // Round Trip test. Ensure glitch-free round trip transmission under 
        // real-ish data loads using a simple per-byte echo like approach to
        // return all data recieved as is.
        if(bc_reqlock(1, BYTEBUF_TOKEN_SCHAR)){
            bc_putc('d', BYTEBUF_TOKEN_SCHAR, 0);
        }
        gpio_set_output_low(BOARD_RED_LED_PORT, BOARD_RED_LED_PIN);
        gpio_set_output_high(BOARD_GREEN_LED_PORT, BOARD_GREEN_LED_PIN);
        
        while(1){
            rval = 0;
            while (!rval){
                if (bc_unhandled_rxb()){
                   c = bc_getc();
                   rval = 1;
                }
            }
            rval = 0;
            while (!rval){
                if(bc_reqlock(1, BYTEBUF_TOKEN_SCHAR)){
                    bc_putc(c, BYTEBUF_TOKEN_SCHAR, 0);
                    rval = 1;
                }
            }
        }
    }
    else if (cmd == 'e'){
        // Chunked Round Trip test. Ensure glitch-free round trip transmission 
        // under real-ish data loads using the interface's chunked RX/TX API.
        // Return all data recieved as is. Note that for this test to work with 
        // the current naive serial-test implementation, length of each test 
        // vector should be an integer multiple of the chunk size.
        #define STE_CHUNK_SIZE 5
        if(bc_reqlock(1, BYTEBUF_TOKEN_SCHAR)){
            bc_putc('e', BYTEBUF_TOKEN_SCHAR, 0);
        }
        gpio_set_output_low(BOARD_RED_LED_PORT, BOARD_RED_LED_PIN);
        gpio_set_output_high(BOARD_GREEN_LED_PORT, BOARD_GREEN_LED_PIN);
        
        while(1){
            rval = 0;
            while (rval < STE_CHUNK_SIZE){
                rval = bc_unhandled_rxb();
            }
            bc_read( (void*)&tbuffer, STE_CHUNK_SIZE );
            rval = 0;
            while (!rval){
                rval = bc_reqlock( STE_CHUNK_SIZE, BYTEBUF_TOKEN_SCHAR );
            }
            bc_write( (void*)&tbuffer, STE_CHUNK_SIZE, BYTEBUF_TOKEN_SCHAR );
        }
    }
    else{
        while(1);
    }
}

int main(void)
{   
    // Pre-init, and assoicated Housekeeping
    _initialize_interrupts();
    
    gpio_conf_output(BOARD_GREEN_LED_PORT,BOARD_GREEN_LED_PIN);
    gpio_conf_output(BOARD_RED_LED_PORT,BOARD_RED_LED_PIN);
    gpio_set_output_high(BOARD_RED_LED_PORT,BOARD_RED_LED_PIN);
    gpio_set_output_low(BOARD_GREEN_LED_PORT,BOARD_GREEN_LED_PIN);
    
    // uC Core Initialization
    watchdog_hold();
    power_set_full();
    clock_set_default();
    
    global_interrupt_enable();
    
    // Subsystems Initialization
    _bc_init();
    _ucdm_init();
    _modbus_init();
        
    // Application
    _main_serial_test();
    
    return(0);
}
