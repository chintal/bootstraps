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

#endif