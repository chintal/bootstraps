/* 
   Copyright 2015 Quazar Technologies Pvt. Ltd.
   Copyright 2015 Chintalagiri Shashank
   
   This file is part of
   Embedded bootstraps : Peripheral driver implementations : MSP430
   
   This library is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published
   by the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>. 
*/

#include "hal_uc_core.h"

#include "driverlib/MSP430F5xx_6xx/gpio.h"

#if PUM_HAS_WDT == 1
#if PUM_WDT_PROVIDER == PUM_WDT_PROVIDER_MSP_WDT_A 
/**
* @brief Initializes the Watchdog timer.
* 
* Presently just sets the default values. This should be changed to 
* accept some parameter, perhaps interval, and set accordingly.
* 
* @return void
*/
void watchdog_init(void) {
    WDT_A_watchdogTimerInit(WDT_A_BASE,
                            WDT_A_CLOCKSOURCE_SMCLK, 
                            WDT_A_CLOCKDIVIDER_32K);
}
#endif
#endif

/**
* @brief Sets the core voltage to the maximum.
* 
* Presently just sets to level 3. This may be changed to accept 
* some parameter after figuring low power modes and such.
* 
* @return void
*/
void power_set_full(void){
    PMM_setVCore(PMM_CORE_LEVEL_3);
}

/**
* @brief Sets the clock to the default
* 
* Presently sets the lock to 24Mhz on LP5529. This function 
* should be improved, alongwith details added to PUM for more 
* intricate clocking arrangements.
* 
* @return void
*/
void clock_set_default(void){
    
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5, 
                      GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5);
    
    // Assuming both clocks exist. Check for consequence otherwise
    
    // Needed to allow UCS_getCLK calls
    UCS_setExternalClockSource(PUM_LF_EXT_CLK_FRQ,
                               PUM_HF_EXT_CLK_FRQ);
    
    UCS_LFXT1StartWithTimeout(UCS_XT1_DRIVE3,
                                     UCS_XCAP_3,
                                     PUM_LF_EXT_TIMEOUT);
    
    UCS_XT2StartWithTimeout(UCS_XT2DRIVE_4MHZ_8MHZ, 
                                   PUM_HF_EXT_TIMEOUT);
    
    UCS_clockSignalInit(UCS_FLLREF, 
                        UCS_XT2CLK_SELECT,
                        UCS_CLOCK_DIVIDER_1);
    
    UCS_initFLLSettle(PUM_SYSCLK_FRQ_KHZ, 
                      PUM_SYSCLK_RATIO);
    
    UCS_clockSignalInit(UCS_ACLK, 
                        UCS_XT1CLK_SELECT,
                        UCS_CLOCK_DIVIDER_1);
    
    UCS_clockSignalInit(UCS_SMCLK, 
                        UCS_DCOCLK_SELECT,
                        UCS_CLOCK_DIVIDER_1);
    
    UCS_clockSignalInit(UCS_MCLK, 
                        UCS_DCOCLK_SELECT,
                        UCS_CLOCK_DIVIDER_1);
    
    UCS_enableClockRequest(UCS_SMCLK);
    UCS_enableClockRequest(UCS_ACLK);
    UCS_enableClockRequest(UCS_MCLK);
    
    SFR_clearInterrupt(SFR_OSCILLATOR_FAULT_INTERRUPT);
    SFR_enableInterrupt(SFR_OSCILLATOR_FAULT_INTERRUPT);

}