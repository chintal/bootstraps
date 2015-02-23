

#include "hal_uc.h"
#include "bc_iface.h"
#include "prbs.h"

volatile uint16_t rval=0;
lfsr16_t prbs;

void deferred_exec(void);

void deferred_exec(void)
{
    if (bcif_handle_txdone){
        if (bcif_usb_active_chunksize){
            bytebuf_cPopChunk(&bcif_txbuf, 
                                bcif_usb_active_chunksize);
            bcif_usb_active_chunksize = 0;
        }
        bcif_handle_txdone = 0;
        bcif_tx_inprogress = 0;
    }
}

int main(void)
{
    
    gpio_conf_output(BOARD_GREEN_LED_PORT, BOARD_GREEN_LED_PIN);
    gpio_conf_output(BOARD_RED_LED_PORT, BOARD_RED_LED_PIN);
    gpio_set_output_high(BOARD_RED_LED_PORT, BOARD_RED_LED_PIN);
    gpio_set_output_low(BOARD_GREEN_LED_PORT, BOARD_GREEN_LED_PIN);
    
    watchdog_hold();
    power_set_full();
    clock_set_default();
    
    hal_usb_setup();
    
    bc_init();
    
    global_interrupt_enable();
    
    while(hal_usb_status() != HUSB_ST_ACTIVE){
        ;
    }
    
    lfsr_vInit(&prbs, LFSR_DEFAULT_SEED, LFSR_DEFAULT_TAPS);
    
    gpio_set_output_high(BOARD_RED_LED_PORT, BOARD_RED_LED_PIN);
    gpio_set_output_high(BOARD_GREEN_LED_PORT, BOARD_GREEN_LED_PIN);
    
    
    rval = 0;
    while (!rval){
        rval = bc_unhandledrxb();
    } 
    bc_discardrxb();
    
    volatile uint16_t i,j;
    
    gpio_set_output_low(BOARD_RED_LED_PORT, BOARD_RED_LED_PIN);
    gpio_set_output_high(BOARD_GREEN_LED_PORT, BOARD_GREEN_LED_PIN);
    
    uint8_t r;
    j = 0;
    
    if(bytebuf_cPushReqLock(&bcif_txbuf, 1, BYTEBUF_TOKEN_SCHAR)){
        bc_printchar(0x01, BYTEBUF_TOKEN_SCHAR);
    }
    
    while(1){
        deferred_exec();
        if(bytebuf_cPushReqLock(&bcif_txbuf, 1, BYTEBUF_TOKEN_SCHAR)){
            bc_printchar(lfsr_cGetNextByte(&prbs), BYTEBUF_TOKEN_SCHAR);
        }
        else{
            bcusb_send_trigger();
        }
    }

//     while(1){
//         for (i=0; i<5; i++){
//             r = 0;
//             while (!r){
//                 //bcusb_send_trigger();
//                 deferred_exec();
//                 r = bytebuf_cPushReqLock(&bcif_txbuf, 8, BYTEBUF_TOKEN_PRINT);
//             }
//             bc_printf("%06u ", j);
//             j++;
//         }
//         bc_printf("  \r\n", j);
//     }
    
//     while(1){
//         j = 'a';
//         r = 0;
//         while (!r){
//             bcusb_send_trigger();
//             deferred_exec();
//             r = bytebuf_cPushReqLock(&bcif_txbuf, 28, BYTEBUF_TOKEN_SCHAR);
//         }
//         bc_printchar(j, BYTEBUF_TOKEN_SCHAR);
//         while(j != 'z'){
//             j++;
//             bc_printchar(j, BYTEBUF_TOKEN_SCHAR);
//         }
//         bc_printchar('\r', BYTEBUF_TOKEN_SCHAR);
//         bc_printchar('\n', BYTEBUF_TOKEN_SCHAR);
//         bytebuf_cPushRelinquishLock(&bcif_txbuf, BYTEBUF_TOKEN_SCHAR);
//     }
    
    return(0);
}
