/* 
   Copyright 2015 Quazar Technologies Pvt. Ltd.
   Copyright 2015 Chintalagiri Shashank
   
   This file is part of
   Embedded bootstraps : prbs library
   
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
 * @file prbs.c
 * @brief Implementation of the prbs generators
 * 
 * See prbs.h for usage documentation. Implementation 
 * documentation should be added to this file as some point. 
 * 
 * @see prbs.h
 */

#include "prbs.h"

void lfsr_vInit(lfsr16_t * lfsrp, uint16_t seed, uint16_t taps){
    lfsrp->_period = 0;
    lfsrp->_seed = seed;
    lfsrp->_lfsr = seed;
    lfsrp->_taps = taps;
}

uint8_t lfsr_cGetNextByte(lfsr16_t *lfsrp){
    uint8_t i, bit;
    uint8_t byte=0;
    for (i=0; i<8; i++){
        bit = lfsr_bGetNextBit(lfsrp);
        byte |= bit<<i;
    }
    return byte;
}

uint8_t lfsr_bGetNextBit(lfsr16_t * lfsrp){
    uint8_t lsb = lfsrp->_lfsr & 1;
    (lfsrp->_lfsr) >>= 1;                   /* Shift register */
    if (lsb == 1)                           /* Only apply toggle mask if output bit is 1*/
        (lfsrp->_lfsr) ^= (lfsrp->_taps);   /* Apply toggle mask, value has 1 at bits 
                                               corresponding to taps, 0 elsewhere. */
    ++(lfsrp->_period);
    return lsb;
}
