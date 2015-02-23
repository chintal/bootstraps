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
 * @file ucdm.h
 * @brief Interface and usage of the Unified Configuration and Data Manager.
 *
 * This library provides a the structures and related functions for 
 * implementing a unified configuration and data manager. This design is 
 * based on the MODBUS data model and is intended to interface seamlessly
 * with MODBUS and derivative protocols. 
 * 
 * The basic configuration type is uint16_t, and the number of configuration 
 * / data registers supported is configurable from within the `bsp`, 
 * specifically from within `bsp/devicemap.h` and it's children, if any. 
 * 
 * Each register can be configured to set allowed access type to one or more
 * of the following : 
 * - Read-Only Register (always allowed)            (modbus: Input Registers)
 * - Read-Write Register (optional)                 (modbus: Holding Registers)
 * - 16 Read-Only Discrete Bits (always allowed)    (modbus: Input Discrete)
 * - 16 Read-Write Discrete Bits (optional)         (modbus: Coils)
 * 
 * Additionally, each set operation can be used to trigger the execution of 
 * a handler function. This function must be defined and the appropriate bits 
 * must be set in the register's access type variable by the subsystem that 
 * deals with this register. This implementation allows two kind of handler 
 * functions to be used : 
 * - Register Write Handler, of type `void(void)`, if `UCDM_AT_REGW_HF`
 * - Bit Write Handler, of type `void(uint16_t mask)`, if `UCDM_AT_BITW_HF`
 * 
 * Bit Write Handlers are only called in response to a successful bit write 
 * operation. Register Write Handlers are called in response to a successful
 * Register Write operation as well as a successful Bit Write operation for 
 * which a Bit Write Handler is not defined, but a Register Write Handler is.
 * 
 * The mapping between the register address and function, as well as the 
 * mapping between address and access types, are application specific, and 
 * should be defined in `bsp/devicemap.h`
 * 
 * The application should internally just set the appropriate varaibles within
 * the configuration and data buffer directly. The access exposed to the 
 * interface will always be more restrictive than that the application itself 
 * will require. When they are being accessed via the UCDM, the functions 
 * provided by this library ensure the access is done correctly. 
 * 
 * For additional details about the MODBUS model, see the MODBUS documentation.
 * 
 * @see <http://www.modbus.org/docs/Modbus_Application_Protocol_V1_1b3.pdf>
 * @see ucdm.c
 */

#ifndef UCDM_H
#define UCDM_H

#include "devicemap.h"
#include <stdint.h>

#define UCDM_AT_REGW    0x01
#define UCDM_AT_BITW    0x02
#define UCDM_AT_REGW_HF 0x10
#define UCDM_AT_BITW_HF 0x20

extern uint16_t ucdm_registers[DMAP_MAXREGS];
extern uint8_t ucdm_acctype[DMAP_MAXREGS];
extern void * ucdm_rw_handlers[DMAP_MAXREGS];
extern void * ucdm_bw_handlers[DMAP_MAXREGS];

/**
 * @name UCDM Setup Functions
 */
/**@{*/ 

/** 
  * \brief Install a Register Write Handler for a UCDM register.
  * 
  * \warning This will overwrite any handler previously installed.
  * 
  * @param addr Address/identifier of the register.
  * @param *fptr Pointer to the handler function.
  */
void ucdm_install_regw_handler(uint8_t addr, void *fptr);

/** 
  * \brief Install a Bit Write Handler for a UCDM register.
  * 
  * \warning This will overwrite any handler previously installed.
  * 
  * @param addr Address/identifier of the register.
  * @param *fptr Pointer to the handler function.
  */
void ucdm_install_bitw_handler(uint8_t addr, void *fptr);
/**@}*/ 

/**
 * @name UCDM Register Access Functions
 */
/**@{*/ 
/** 
  * \brief Set the value of a UCDM register from protocol.
  * 
  * @param addr Address/identifier of the register
  * @param value The value to be set
  * @return 1 for register set, 0 for access error.
  */
uint8_t ucdm_set_register(uint8_t addr, uint16_t value);

/** 
  * \brief Get the value of a UCDM register from protocol.
  * 
  * @param addr Address/identifier of the register
  * @return Value of the register, or 0xFFFF if address is invalid.
  */
uint16_t ucdm_get_register(uint8_t addr);
/**@}*/ 


/**
 * @name UCDM Bit Access Functions
 */
/**@{*/ 
/** 
  * \brief Get the address of a UCDM bit from the identifier
  * 
  * @param addrb Identifier of the bit
  * @param *addr Pointer to where the register address should be stored
  * @param *mask Pointer to where the bitmask should be stored
  */
static inline void ucdm_get_bit_addr(uint16_t addrb, uint8_t * addr, uint16_t * mask);

static inline void ucdm_get_bit_addr(uint16_t addrb, 
                                     uint8_t * addrp, 
                                     uint16_t * maskp){
    *addrp = (uint8_t)(addrb >> 4);
    *maskp = (1 << (addrb & 15));
}

/** 
  * \brief Set a UCDM bit from protocol.
  * 
  * @param addrb Address/identifier of the bit
  * @return 1 for bit set, 0 for access error.
  */
uint8_t ucdm_set_bit(uint16_t addrb);

/** 
  * \brief Clear a UCDM bit from protocol.
  * 
  * @param addrb Address/identifier of the bit.
  * @return 1 for bit cleared, 0 for access error.
  */
uint8_t ucdm_clear_bit(uint16_t addrb);

/** 
  * \brief Get the value of a UCDM bit from protocol.
  * 
  * @param addrb Address/identifier of the bit
  * @return Non-zero for bit is set, 0 for bit is cleared, 2 for address invalid
  */
uint8_t ucdm_get_bit(uint16_t addrb);
/**@}*/ 

#endif