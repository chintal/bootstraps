/* 
   Copyright 2015 Quazar Technologies Pvt. Ltd.
   Copyright 2009,2010,2011,2013,2015 Chintalagiri Shashank
    
   This file is part of
   Embedded bootstraps : bytebuf library
   
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
 * @file bytebuf.h
 * @brief Interface and usage of bytebuf buffers.
 *
 * This library provides a ::bytebuf structure and associated functions
 * to implement a circular byte buffer. The design of the buffer is intended 
 * to support continuous byte-wide datastreams. A simple locking mechanism
 * for writes is included.
 * 
 * The typical application of such a buffer is when one or more data sources 
 * (producers) are writing to a single sink (consumer). In the general case,
 * the buffer is instantiated at and by the consumer, while the producers 
 * user their respective tokens to write to the buffer. 
 * 
 * While errors are reported, for optimal use implementations should ensure
 * that the buffers are large enough for the consumers to handle all of the 
 * produced data before an overflow occurs. 
 * 
 * A bytebuf buffer can be at-most 255 bytes long. For longer buffers, some 
 * datatypes need to be changed from uint8_t to uint16_t. This will have a
 * performance penalty on uCs with an 8-bit bus.
 * 
 * @see bytebuf.c
 */


#include<stdint.h>

/**
 * @name Generic Write Tokens
 */
/**@{*/ 

#define BYTEBUF_LOCK_OPEN       0
#define BYTEBUF_TOKEN_PRINT     1

/**@}*/ 


/**
 * @brief Primary bytebuf struct typedef
 * 
 * The core of the bytebuf implementation, this type contains bytebuf 
 * metadata and control information. This struct should be created by 
 * instantiating a variable at the consumer of this type, and calling 
 * bytebuf_vInit(). 
 * 
 * This struct does not contain the actual data but has a pointer to 
 * a byte array which should be separately created and contains the 
 * actual data. 
 */
typedef struct {
    uint8_t * _bufp;            /**< @brief Pointer to the start of the underlying buffer. */
    uint8_t * _inp;             /**< @brief Pointer to the current write location. */
    uint8_t * _outp;            /**< @brief Pointer to the current read location. */
    uint8_t _population;        /**< @brief Number of bytes presently in the buffer. */
    uint8_t _size;              /**< @brief Size of buffer. */
    uint8_t _lock;              /**< @brief Token which holds the write lock at present. */
    uint8_t _locklen;           /**< @brief Number of additional bytes for which the lock is valid. */
} bytebuf;

/**
  * Initialize a bytebuf structure using  an externally supplied (and allocated) 
  * memory array. 
  * @param *bufferp Pointer to the array; should be in the heap and not in a task stack.
  * @param size Size of the array. Beware : we have no good way to check this later.
  * @param *bytebufp Pointer to the bytebuf structure to be initialized. 
  */
void bytebuf_vInit(uint8_t * bufferp, uint8_t size, bytebuf * bytebufp);

/**
  * Flush a buffer and reset it to its pristine state.
  * @warning Any locks held on the buffer will disappear and holder is not informed.
  * @warning Any data present in the data will be lost. 
  * @param *bytebufp Pointer to the bytebuf structure.
  */
void bytebuf_vFlush(bytebuf * bytebufp);

/** 
  * Request a write lock on a bytebuf for a specific length.
  * Actual writing is done using other functions. 
  * @see bytebuf_cPush()
  * @see bytebuf_cPushLen()
  * @param *bytebufp Pointer to the bytebuf structure.
  * @param length Number of bytes you want to write.
  * @param token An identifier against which to issue the lock.
  * @return 0 for lock denied, 1 for lock issued.
  */
uint8_t bytebuf_cPushReqLock(bytebuf * bytebufp, uint8_t length, uint8_t token);

/** 
  * Request a write lock on a bytebuf for an unspecified length.
  * Actual writing is done using other functions. 
  * @see bytebuf_cPush()
  * @see bytebuf_cPushLen()
  * @param *bytebufp Pointer to the bytebuf structure.
  * @param token An identifier against which to issue the lock.
  * @return 0 for lock denied, number of characters free for granted.
  */
uint8_t bytebuf_cPushReqBlindLock(bytebuf * bytebufp, uint8_t token);

/** 
  * Relinquish a write lock on a bytebuf.
  * Actual writing is done using other functions. 
  * @see bytebuf_cPushReqLock()
  * @param *bytebufp Pointer to the bytebuf structure.
  * @param token An identifier against which the lock was issued.
  * @return 0 for incorrect token, 1 for lock relinquished, 2 for already open.
  */
uint8_t bytebuf_cPushRelinquishLock(bytebuf * bytebufp, uint8_t token);

/**
  * Push a single byte into the bytebuf.
  * You should already hold the write lock to do this.
  * @see bytebuf_cPushReqLock()
  * @param *bytebufp Pointer to the bytebuf structure.
  * @param byte Byte to be written in.
  * @param token Identifier against which you own the lock.
  * @return 0 for failed write, 1 for successful write.
  */
uint8_t bytebuf_cPush(bytebuf * bytebufp, uint8_t byte, uint8_t token);

/**
  * Push a length of data into a bytebuf. 
  * You should already hold the write lock to do this.
  * @see bytebuf_cPushReqLock()
  * @param *bytebufp Pointer to the bytebuf structure.
  * @param *sp Pointer to the source buffer.
  * @param len Number of bytes to push in.
  * @param token Identifier against which you own the lock.
  * @return 0 for failed write, 1 for successful write.
  */
uint8_t bytebuf_cPushLen(bytebuf * bytebufp, uint8_t * sp, uint8_t len, uint8_t token);

/**
  * Pop a byte from the bytebuf. 
  * You should make sure that there actually is a byte to be read first.
  * @see cbytebuf_population()
  * @param *bytebufp Pointer to the bytebuf structure.
  * @return The byte that got popped, or 0 by default if there wasn't one. 
  * @warning return value of 0 does not necessarily mean an error occured.
  */
uint8_t bytebuf_cPopByte(bytebuf * bytebufp);

/**
  * Return the number of bytes present in the buffer to be read.
  * @param *bytebufp Pointer to the bytebuf structure.
  * @return The number of bytes left in the buffer to be read.
  */
static inline uint8_t cbytebuf_population(bytebuf * bytebufp){
    return (bytebufp->_population);
}

/**
  * Return the number of bytes that can be written into the buffer right now.
  * You still need to acquire a lock if you want to write into it. 
  * @see bytebuf_cPushReqLock()
  * @param *bytebufp Pointer to the bytebuf structure.
  * @return The number of empty bytes left in the buffer.
  */
static inline uint8_t cbytebuf_getfree(bytebuf * bytebufp){
    return (bytebufp->_size - bytebufp->_population);
}
