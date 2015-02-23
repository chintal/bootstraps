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
 * @file bytebuf.c
 * @brief Implementation of the bytebuf interface
 * 
 * See bytebuf.h for usage documentation. Implementation 
 * documentation should be added to this file as some point. 
 * 
 * @see bytebuf.h
 */

#include "bytebuf.h"
#include<string.h>

static inline void bytebuf_vIncInp( bytebuf * bytebufp ){
        if (bytebufp -> _inp == bytebufp -> _bufp + bytebufp -> _size)
        {
            bytebufp -> _inp = bytebufp -> _bufp;
        }
        else
        {
            bytebufp -> _inp++;
        }
        return;
}

static inline void bytebuf_vIncOutp( bytebuf * bytebufp ){
        if(bytebufp -> _outp == bytebufp-> _bufp + bytebufp -> _size)
        {
            bytebufp -> _outp = bytebufp -> _bufp;
        }
        else
        {
            bytebufp -> _outp++;
        }
        return;
}


void bytebuf_vInit( uint8_t * bufferp, BYTEBUF_SIZE_t size, bytebuf * bytebufp )
{
    bytebufp -> _bufp = bufferp;
    bytebufp -> _size = size;
    bytebuf_vFlush( bytebufp );
    return;
}

void bytebuf_vFlush( bytebuf * bytebufp )
{
    bytebufp -> _inp = bytebufp -> _bufp;
    bytebufp -> _outp = bytebufp -> _bufp;
    bytebufp -> _population = 0;
    bytebufp -> _lock = BYTEBUF_LOCK_OPEN;
    bytebufp -> _locklen = 0;
    return;
}

uint8_t bytebuf_cPushReqLock( bytebuf * bytebufp, BYTEBUF_SIZE_t length, uint8_t token )
{
    if ( bytebufp -> _lock == BYTEBUF_LOCK_OPEN )
    {
        if ( bytebuf_cGetFree( bytebufp ) >= length )
        {
            bytebufp -> _lock = token;
            bytebufp -> _locklen = length;
            return 1;
        }
    }
    return 0; 
}

BYTEBUF_SIZE_t bytebuf_cPushReqBlindLock( bytebuf * bytebufp, uint8_t token )
{
    BYTEBUF_SIZE_t avail;
    if ( bytebufp -> _lock == BYTEBUF_LOCK_OPEN || bytebufp -> _lock == token )
    {
        avail = bytebuf_cGetFree( bytebufp );
        if ( avail > 0 )
        {
            bytebufp -> _lock = token;
            bytebufp -> _locklen = avail;
            return avail;
        }
    }
    return 0; 
}

uint8_t bytebuf_cPushRelinquishLock(bytebuf * bytebufp, uint8_t token){
    if ( bytebufp -> _lock == token){
        bytebufp -> _lock = BYTEBUF_LOCK_OPEN;
        return 1;
    }
    else if ( bytebufp -> _lock == BYTEBUF_LOCK_OPEN){
        return 2;
    }
    return 0;
}

uint8_t bytebuf_cPush( bytebuf * bytebufp, uint8_t byte, uint8_t token )
{
    if ( bytebufp -> _lock == token )
    {
        *( bytebufp -> _inp ) = byte;
        bytebuf_vIncInp( bytebufp );
        bytebufp -> _locklen--;
        if ( !(bytebufp -> _locklen) )
        {
            bytebufp -> _lock = BYTEBUF_LOCK_OPEN;
        }
        bytebufp -> _population++;
        return 1;
    }
    return 0;
}

uint8_t bytebuf_cPushLen( bytebuf * bytebufp, uint8_t * sp, BYTEBUF_SIZE_t len, uint8_t token )
{
    if ( bytebufp -> _lock == token && ( (bytebufp -> _locklen) >= len ) )
    {
        bytebufp -> _population += len;
        bytebufp -> _locklen -= len;
        //Check for buffer boundary.
        if ( (bytebufp -> _bufp + bytebufp -> _size) <= (bytebufp -> _inp + len)){
            uint8_t len1 = (bytebufp -> _bufp + bytebufp -> _size - bytebufp -> _inp);
            memcpy((void *)(bytebufp->_inp), (void *)(sp), len1);
            uint8_t len2 = len - len1;
            if (len2) {
                memcpy((void *)(bytebufp->_bufp), (void *)(sp + len1), (len2));
            }
            bytebufp -> _inp = bytebufp -> _bufp + (len2);
        }
        else {
            memcpy((void *)(bytebufp -> _inp), (void *)(sp), len);
            bytebufp -> _inp += len;
        }
        if (!(bytebufp -> _locklen)){
            bytebufp -> _lock = BYTEBUF_LOCK_OPEN;
        }
        return 1;
    }
    return 0;
}

uint8_t bytebuf_cPopByte( bytebuf * bytebufp )
{
    if (bytebufp -> _population){
        uint8_t rval = *(bytebufp -> _outp);
        bytebuf_vIncOutp(bytebufp);
        bytebufp->_population--;
        return rval;
    }
    return 0;
}

BYTEBUF_SIZE_t bytebuf_cPopChunk(bytebuf * bytebufp, BYTEBUF_SIZE_t len){
    BYTEBUF_SIZE_t pop = bytebufp->_population;
    BYTEBUF_SIZE_t lend = bytebufp -> _bufp + bytebufp -> _size - bytebufp -> _outp + 1;
    BYTEBUF_SIZE_t lwrap;
    if (pop >= len){
        // There are enough bytes in the buffer to pop.
        if (len >= lend){
            // Popping that many bytes needs a rollover
            lwrap = len - lend;
            bytebufp -> _outp = bytebufp->_bufp + lwrap;
        }
        else{
            // Popping that many bytes does not need a rollover
            bytebufp -> _outp += len;
        }
        bytebufp -> _population -= len;
        return len;
    }
    else{
        // There aren't enough bytes in the buffer to pop the requested length.
        if (pop >= lend){
        // Popping that many bytes needs a rollover
            lwrap = pop - lend;
            bytebufp -> _outp = bytebufp->_bufp + lwrap;
        }
        else{
            // Popping that many bytes does not need a rollover
            bytebufp -> _outp += pop;
        }
        bytebufp -> _population -= pop;
        return pop;
    }
}
