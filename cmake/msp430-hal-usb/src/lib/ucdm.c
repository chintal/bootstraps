/* 
   Copyright 2015 Quazar Technologies Pvt. Ltd.
   Copyright 2015 Chintalagiri Shashank
   
   This file is part of
   Embedded bootstraps : ucdm library
   
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
 * @file ucdm.c
 * @brief Implementation the Unified Configuration and Data Manager.
 *
 * See ucdm.h for usage documentation. Implementation 
 * documentation should be added to this file as some point. 
 * 
 * @see ucdm.h
 */

#include "ucdm.h"

uint16_t ucdm_registers[DMAP_MAXREGS];
uint8_t ucdm_acctype[DMAP_MAXREGS];
void * ucdm_rw_handlers[DMAP_MAXREGS];
void * ucdm_bw_handlers[DMAP_MAXREGS];

void ucdm_install_regw_handler(uint8_t addr, void *fptr){
    ucdm_rw_handlers[addr] = fptr;
    ucdm_acctype[addr] |= UCDM_AT_REGW_HF;
}

void ucdm_install_bitw_handler(uint8_t addr, void *fptr){
    ucdm_bw_handlers[addr] = fptr;
    ucdm_acctype[addr] |= UCDM_AT_BITW_HF;
}

uint8_t ucdm_set_register(uint8_t addr, uint16_t value){
    if (addr > DMAP_MAXREGS){
        return 1;
    }
    if (ucdm_acctype[addr] & UCDM_AT_REGW){
        ucdm_registers[addr] = value;
        if (ucdm_acctype[addr] & UCDM_AT_REGW_HF){
            ucdm_rw_handlers[addr]();
        }
        return 0;
    }
    return 1;
}

uint16_t ucdm_get_register(uint8_t addr){
    if (addr > DMAP_MAXREGS){
        return 0xFFFF;
    }
    return ucdm_registers[addr];
}

uint8_t ucdm_set_bit(uint16_t addrb){
    if (addrb > DMAP_MAXBITS){
        return 1;
    }
    uint8_t addr;
    uint16_t mask;
    ucdm_get_bit_addr(addrb, &addr, &mask);
    if (ucdm_acctype[addr] & UCDM_AT_BITW){
        ucdm_registers[addr] |= mask;
        if (ucdm_acctype[addr] & UCDM_AT_BITW_HF){
            ucdm_bw_handlers[addr](mask);
        }
        else if (ucdm_acctype[addr] & UCDM_AT_REGW_HF){
            ucdm_rw_handlers[addr]();
        }
        return 0;
    }
    return 1;
}

uint8_t ucdm_clear_bit(uint16_t addrb){
    if (addrb > DMAP_MAXBITS){
        return 1;
    }
    uint8_t addr;
    uint16_t mask;
    ucdm_get_bit_addr(addrb, &addr, &mask);
    if (ucdm_acctype[addr] & UCDM_AT_BITW){
        ucdm_registers[addr] &= ~mask;
        if (ucdm_acctype[addr] & UCDM_AT_BITW_HF){
            ucdm_bw_handlers[addr](mask);
        }
        else if (ucdm_acctype[addr] & UCDM_AT_REGW_HF){
            ucdm_rw_handlers[addr]();
        }
        return 0;
    }
    return 1;
}

uint8_t ucdm_get_bit(uint16_t addrb){
    if (addrb > DMAP_MAXBITS){
        return 1;
    }
    uint8_t addr;
    uint16_t mask;
    ucdm_get_bit_addr(addrb, &addr, &mask);
    return (ucdm_registers[addr] & mask); 
    
}