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

#ifndef GPIO_IMPL_H
#define GPIO_IMPL_H

#include "uc_types_impl.h"
#include "msp430-driverlib/MSP430F5xx_6xx/driverlib.h"

/* This implementation can be made significantly faster by eliminating 
 * the use of driverlib here entirely. The blocking issue for doing that
 * is figuring out how to use OFS and defining BASE addresses. 
 * 
 * The problem with driverlib is only really that we are linking to it,
 * making the function call required.
 */


static inline void gpio_conf_output(PORTSELECTOR_t port,
                                    PINSELECTOR_t pin){
    GPIO_setAsOutputPin(port, pin);
}

static inline void gpio_conf_input(PORTSELECTOR_t port,
                                   PINSELECTOR_t pin){
    GPIO_setAsInputPin(port, pin);
}

static inline void gpio_conf_periph(PORTSELECTOR_t port,
                                    PINSELECTOR_t pin,
                                    uint8_t periph
                                   ){
    if (periph & 0x80){
        GPIO_setAsPeripheralModuleFunctionOutputPin(port, pin);
    }
    else{
        GPIO_setAsPeripheralModuleFunctionInputPin(port, pin);
    }
}

static inline void gpio_set_output_high(PORTSELECTOR_t port,
                                        PINSELECTOR_t pin){
    GPIO_setOutputHighOnPin(port, pin);
}
static inline void gpio_set_output_low(PORTSELECTOR_t port,
                                       PINSELECTOR_t pin){
    GPIO_setOutputLowOnPin(port, pin);
}
static inline void gpio_set_output_toggle(PORTSELECTOR_t port,
                                          PINSELECTOR_t pin){
    GPIO_toggleOutputOnPin(port, pin);
}

static inline void gpio_conf_input_pullup(PORTSELECTOR_t port,
                                          PINSELECTOR_t pin){
    GPIO_setAsInputPinWithPullUpResistor(port, pin);
}
static inline void gpio_conf_input_pulldown(PORTSELECTOR_t port,
                                            PINSELECTOR_t pin){
    GPIO_setAsInputPinWithPullDownResistor(port, pin);
}
static inline void gpio_conf_input_hiz(PORTSELECTOR_t port,
                                       PINSELECTOR_t pin){
    GPIO_setAsInputPin(port, pin);
}
static inline HAL_BASE_t gpio_get_input(PORTSELECTOR_t port,
                                        PINSELECTOR_t pin){
    return GPIO_getInputPinValue(port, pin);
}

#endif