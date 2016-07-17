/* 
   Copyright 2015 Quazar Technologies Pvt. Ltd.
   Copyright 2015 Chintalagiri Shashank
   
   This file is part of
   Embedded bootstraps : Board Support Packages
   
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
 * @file board.h
 * @brief Highest level include for firmware library superstructure.
 *
 * This file acts as a proxy for the specific board include header. Project 
 * firmware code should include this file instead of the board specific 
 * headers. 
 * 
 * Including this file should include all the functional elements, 
 * which could be undesireable behavior. The alternative would be to 
 * selectively include either `hal_uc.h`, which will bring in only the
 * necessary uC functions, or even the relevant `hal_uc_*.h` file, which 
 * will only bring in the necessary modules.
 * 
 * As such, this file should not have any major functional code elements, 
 * and should only redirect to another board-specific file that is responsible
 * for including everything relevant. Various definitions needed for 
 * configuring the lower level modules should be placed in `bsp/uc_pum.h` and
 * it's include chain, so that independent modules can be imported without 
 * needing to include the entire board.h hierarchy.
 */

#ifndef BOARD_H
#define BOARD_H

#include "board_lp5529.h"

#endif