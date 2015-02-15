/* 
   Copyright 2015 Quazar Technologies Pvt. Ltd.
   Copyright 2015 Chintalagiri Shashank
   
   This file is part of
   Embedded bootstraps : peripheral usage maps : TI Launchpad MSP420F5529
   
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
 * @file board_pum_lp5529.h
 * @brief Board PUM for TI Launchpad based on MSP430F5529
 *
 * This file contains the map for the various subsystems in the context
 * of TI Launchpad based on MSP430F5529.
 */

#ifndef BOARD_PUM_SPECIFIC_H
#define BOARD_PUM_SPECIFIC_H

// Configure available subsystems.

/**
 * @name Backchannel Interface Configuration
 */
/**@{*/ 

    #define BOARD_HAS_BCIFACE         1
    #define BOARD_BCIFACE_PROVIDER    UART1
    
/**@}*/ 

/**
 * @name LED Configuration
 * 
 * For use with standard GPIO functions. Special functions
 * to deal with LEDs can be written, but probably more work
 * than is justified.
 */
/**@{*/ 

    #define BOARD_HAS_RED_LED         1
    #define BOARD_RED_LED_PORT        1
    #define BOARD_RED_LED_PIN         _BV(0)
    #define BOARD_RED_LED_POLARITY    1
    
    #define BOARD_HAS_GREEN_LED       1
    #define BOARD_GREEN_LED_PORT      4
    #define BOARD_GREEN_LED_PIN       _BV(7)
    #define BOARD_GREEN_LED_POLARITY  1
    
    
/**@}*/ 


#endif