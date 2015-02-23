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
 * @file prbs.h
 * @brief Interface and usage of prbs generators.
 *
 * This library provides generators for psuedo random bit sequences. It is 
 * intended for use in BER and protocol tests and should not be considered
 * crytptographically secure. 
 * 
 * In principle, a shrinking generator can be constructed of these buffers 
 * which has relatively better cryptographic properties. Implementation of 
 * this is deferred to some unspecified point in the future.
 * 
 * 
 * @see prbs.c
 */
#ifndef PRBS_H
#define PRBS_H

#include<stdint.h>

#define LFSR_DEFAULT_SEED 0xACE1
#define LFSR_DEFAULT_TAPS 0xB400

/**
 * @brief Primary 16 bit LFSR struct typedef
 * 
 * The core of PRBS implementation is made of this struct, which represents
 * a 16 bit Linear Feedback Shift Register. While values in the struct should
 * not be used directly, the functions listed in the interface can be used to 
 * operate on the LFSR. 
 * 
 * The LFSR implemented is a binary Galois LFSR.
 */
typedef struct {
    uint16_t _seed;      /**< @brief Seed value for the LFSR */
    uint16_t _taps;      /**< @brief Mask representing the taps in the LFSR */
    uint32_t _period;    /**< @brief Determines the state of the LFSR. Each propagate step increments this */
    uint16_t _lfsr;      /**< @brief The actual LFSR */
} lfsr16_t;

/**
  * Initialize a ::lfsr16_t structure using specified seed and polynomial (taps). Use the 
  * included defines of LFSR_DEFAULT_SEED and LFSR_DEFAULT_TAPS or provide your own.
  * Note that typically the same values of seed and taps must be used at both ends of 
  * the transport.
  * 
  * @param *lfsrp Pointer to the ::lfsr16_t structure to be initialized.
  * @param seed Seed value for the shift register.
  * @param taps Taps for the shift register
  */
void lfsr_vInit(lfsr16_t * lfsrp, uint16_t seed, uint16_t taps);

/**
  * Get the next byte in the pseudo random binary sequency.
  * 
  * @param *lfsrp Pointer to the ::lfsr16_t structure.
  * @return The next byte in the sequence.
  */
uint8_t lfsr_cGetNextByte(lfsr16_t * lfsrp);

/**
  * Get the next bit in the pseudo random binary sequency.
  * 
  * @param *lfsrp Pointer to the ::lfsr16_t structure.
  * @return The next bit in the sequence.
  */
uint8_t lfsr_bGetNextBit(lfsr16_t * lfsrp);

#endif