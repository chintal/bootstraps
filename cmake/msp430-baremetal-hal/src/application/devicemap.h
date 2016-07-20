/* 
   Copyright (c) 
     (c) 2015-2016 Chintalagiri Shashank, Quazar Technologies Pvt. Ltd.
   
   This file is part of
   Embedded bootstraps : device access maps
   
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
 * @file devicemap.h
 * @brief Map of device configuration and data access parameters.
 *
 * This file, and the file hierarchy that it includes, if any should 
 * define all the configuration and data access parameters that the 
 * device exposes via the ucdm interface. 
 * 
 * All source files operating on the parameters in any way must include 
 * this file and use the appropriate define to perform it's operation at 
 * the correct address within the device map. External interfaces should
 * use the functions of `libucdm` to ensure correct access.
 * 
 * Any lower level files in this hierarchy should not be included 
 * separately, and the information present in them should be accessed
 * only though this file.
 * 
 * @see `libucdm`
 */

#ifndef DEVICEMAP_H
#define DEVICEMAP_H

#include <ucdm/ucdm.h>

#define DMAP_MAX_REGISTERS              64

#define UCDM_MODBUS_BASE_ADDRESS        0

#endif
