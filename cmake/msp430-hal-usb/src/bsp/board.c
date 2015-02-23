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
 * @file board.c
 * @brief Board-level management functions
 * 
 * This file provides implementations for board level management functions
 * which are used by the underlying API implementations. These functions 
 * should be re-implemented for each board. 
 * 
 * This file can include whatever header files it needs to achieve this 
 * task. Including `bsp/board.h` will include most of the namespace into 
 * this file, though selectively including the required headers will 
 * probably make for a better maintainable implementation. 
 * 
 */

#include "board_pum.h"
#include "bc_iface.h"

BYTEBUF_SIZE_t bcif_usb_active_chunksize;
uint8_t bcif_handle_txdone, bcif_tx_inprogress;

void board_suspend(void){
    ;
}

void board_resume(void){
    ;
}

void board_iface_reset(void){
    ;
}
