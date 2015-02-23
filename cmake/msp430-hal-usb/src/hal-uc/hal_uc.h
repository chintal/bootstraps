/* 
   Copyright 2015 Quazar Technologies Pvt. Ltd.
   Copyright 2015 Chintalagiri Shashank
    
   This file is part of
   Embedded bootstraps : hal-uC
   
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

/**
 * @file hal_uc.h
 * @brief Highest level include for uC HAL.
 *
 * This file is the header that should be used to obtain the functions to control 
 * the microcontroller and it's peripherals, whose peripheral map is defined by 
 * `uc_pum.h`. HAL_uC brings in the underlying drivers provided by the base libraries 
 * (preferably manufacturer provided) and provides wrappers around it to form a 
 * controlled interface. The definitions within `uc_pum.h` and it's include chain
 * determine which underlying implementation can be used to provide the defined
 * interfaces.
 * 
 * General applications can include the bsp/board.h instead, which will use the
 * this file to provide access to low level uC peripheral drivers. The controlled 
 * HAL_uC interface should be preferred over the underlying driver APIs (such as 
 * `driverlib` for MSP430), even though both versions exist in the namespace. 
 * This will allow easier migration and code-sharing with other ICs and/or platforms.
 * 
 * The `hal_uc` folder should ideally be portable across all implementations. MCU 
 * specific implementation goes into `peripherals` and should be portable to the 
 * entire MCU family, taking resource information from the `bsp`. 
 * 
 * Some graceful way to bow out should be found when these functions are not 
 * provided by a certain uC. The mapping from the HAL layer to the implementation 
 * layer is determined by the `(module)_impl.h` and `(module)_impl.c` files within 
 * the implementation layer (the `perpherals` folder)
 */
 

#ifndef HAL_uC_H
#define HAL_uC_H


/* 
 * Include all the drivers. Each of these header files will then go on to 
 * inclde the corresponding implementation files for the platform that is being built. 
 * The implementation files should be within the predefined include paths. Recommended 
 * location is `peripherals/<driver>_impl.h`
 */

#include "hal_uc_core.h"
#include "hal_uc_gpio.h"
#include "hal_uc_uart.h"
#include "hal_uc_usb.h"

#endif
