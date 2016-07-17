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

#include "msp430-driverlib/MSP430F5xx_6xx/driverlib.h"

#if uC_HAS_WDT == 1
#if uC_WDT_PROVIDER == MSP_WDT_A 
/**
* @brief Initializes the Watchdog timer.
* 
* Presently just sets the default values. This should be changed to 
* accept some parameter, perhaps interval, and set accordingly.
* 
* @return void
*/
void watchdog_init(void) {
    WDT_A_initWatchdogTimer(WDT_A_BASE,
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
* Sets the MCLK to uC_MCLK_FRQ_KHZ defined in uc_map_impl.h, given the 
* presence of external timing elements defined in uc_pum.h of the board
* support package. 
* 
* For this implementation, 
* 
*  - uC_MCLK_FRQ must be an integer multiple of uC_HF_EXT_CLK_FRQ
*  - uC_SMCLK_FRQ must be MCLK/(1,2,4,8,16)
* 
* @return void
*/
void clock_set_default(void){
    
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5, 
                      GPIO_PIN2|GPIO_PIN3|GPIO_PIN4|GPIO_PIN5);
    
    // Assuming both clocks exist. Check for consequence otherwise
    
    // Needed to allow UCS_getCLK calls
    UCS_setExternalClockSource(uC_LF_EXT_CLK_FRQ,
                               uC_HF_EXT_CLK_FRQ);
    
    UCS_turnOnLFXT1WithTimeout(UCS_XT1_DRIVE_3,
                               UCS_XCAP_3,
                               uC_LF_EXT_TIMEOUT);
    
    UCS_turnOnXT2WithTimeout(UCS_XT2_DRIVE_4MHZ_8MHZ, 
                             uC_HF_EXT_TIMEOUT);
    
    UCS_initClockSignal(UCS_FLLREF, 
                        UCS_XT2CLK_SELECT,
                        UCS_CLOCK_DIVIDER_1);
    
    UCS_initFLLSettle((uint16_t)uC_FLL_FRQ_KHZ, 
                      uC_FLL_MULT);
    
    UCS_initClockSignal(UCS_ACLK, 
                        UCS_XT1CLK_SELECT,
                        UCS_CLOCK_DIVIDER_1);
    
    UCS_initClockSignal(UCS_SMCLK, 
                        UCS_DCOCLK_SELECT,
                        uC_SMCLK_DIV);
    
    UCS_initClockSignal(UCS_MCLK, 
                        UCS_DCOCLK_SELECT,
                        uC_MCLK_DIV);
    
    UCS_enableClockRequest(UCS_SMCLK);
    UCS_enableClockRequest(UCS_ACLK);
    UCS_enableClockRequest(UCS_MCLK);
    
    SFR_clearInterrupt(SFR_OSCILLATOR_FAULT_INTERRUPT);
    SFR_enableInterrupt(SFR_OSCILLATOR_FAULT_INTERRUPT);

}