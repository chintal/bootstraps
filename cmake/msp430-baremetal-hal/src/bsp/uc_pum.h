/* 
   Copyright 2015 Quazar Technologies Pvt. Ltd.
   Copyright 2015 Chintalagiri Shashank
   
   This file is part of
   Embedded bootstraps : peripheral usage maps
   
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
 * @file uc_pum.h
 * @brief Highest level include for firmware uC configuration parmeters.
 *
 * This file, and the file hierarchy that it includes, should define
 * all the parameters necessary for configuring the modules present 
 * within `hal_uc`. This hierarchy should not possess any functional 
 * code within itself, and is to be used only as an in-code configuration
 * store. It should only add preprocessor files and definitions and 
 * should not create any libraries.
 * 
 * The lower level files in this hierarchy should not be included 
 * separately, and the information present in them should be accessed
 * only though this file.
 * 
 * Drivers should include this file to get all the relevant platform 
 * data for setting up the implementation drivers. 
 * 
 * The corresponding HAL include chain is where the libraries
 * and C code should go. 
 */

#ifndef uC_PUM_H
#define uC_PUM_H

/**
 * @name Reusable base macros
 * Simple macros to perform standard tasks. These shouldn't strictly
 * be here, but uc_pum.h is the file that is imported in all the drivers
 * and can safely be imported elsewhere. The presence of the group here
 * should be corrected as overall complexity increases.
 */
/**@{*/
#define NOT_IMPLEMENTED_STUB()

#define _BV(b)          (1 << b)
#define checkbit(r, b)  (r) &  _BV(b)
#define setbit(r, b)    (r) |= _BV(b)
#define clearbit(r, b)  (r) &= ~_BV(b)
#define togglebit(r, b) (r) ^= _BV(b)
/**@}*/
#include "uc_pum_lp5529.h"

#endif