/*
    Copyright 2015 Quazar Technologies Pvt. Ltd.
    Copyright 2010, 2011, 2015 Chintalagiri Shashank
    Copyright 2001, 2002 Georges Menie (www.menie.org)
        stdarg version contributed by Christian Ettinger

    This file is part of
    Embedded bootstraps : printf library

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/


/**
 * @file printf.c
 * @brief Pared down printf implementation for embedded use.
 * 
 * See printf.h for usage documentation. Implementation 
 * documentation should be added to this file as some point. 
 * 
 * @see printf.h
 */

#include "printf.h"

/* 
 * putchar() is needed for implementing garden-variety printf(), 
 * and not for anything else. A stub that the compiler should 
 * optimise away is retained here, which should be completed or 
 * removed if putchar() is to be used.
 * 
 * #define putchar(c) outbyte(c) *	
*/
int putchar ( int c ) {
    return 0;
}

static int printchar(void **target, const char ttype, int c)
{
	extern int putchar(int c);
        char **str;
        bytebuf *buf;
	if (ttype == PRINT_TTYPE_STRING){
            str = (char**)target;
            if (str) {
		**str = c;
		++(*str);
            } 
        }
        else if (ttype == PRINT_TTYPE_BYTEBUF){
            buf = *((bytebuf**)target);
            return bytebuf_cPush(buf, c, BYTEBUF_TOKEN_PRINT);
        }
        return putchar(c);
}

#define PAD_RIGHT 1
#define PAD_ZERO 2

static int prints(void **out, const char ttype, const char *string, int width, int pad)
{
	register int pc = 0, padchar = ' ';

	if (width > 0) {
		register int len = 0;
		register const char *ptr;
		for (ptr = string; *ptr; ++ptr) ++len;
		if (len >= width) width = 0;
		else width -= len;
		if (pad & PAD_ZERO) padchar = '0';
	}
	if (!(pad & PAD_RIGHT)) {
		for ( ; width > 0; --width) {
			pc += printchar (out, ttype, padchar);
		}
	}
	for ( ; *string ; ++string) {
		pc += printchar (out, ttype, *string);
		
	}
	for ( ; width > 0; --width) {
		pc += printchar (out, ttype, padchar);
	}

	return pc;
}

static int printl(void **out, const char ttype, long i, int b, int sg, int width, int pad, int letbase)
{
	char print_buf[PRINT_BUF_LEN];
	register char *s;
	register int t, neg = 0, pc = 0;
	register unsigned long u = i;

	if (i == 0) {
		print_buf[0] = '0';
		print_buf[1] = '\0';
		return prints (out, ttype, print_buf, width, pad);
	}

	if (sg && b == 10 && i < 0) {
		neg = 1;
		u = -i;
	}

	s = print_buf + PRINT_BUF_LEN-1;
	*s = '\0';

	while (u) {
		t = u % b;
		if( t >= 10 )
			t += letbase - '0' - 10;
		*--s = t + '0';
		u /= b;
	}

	if (neg) {
		if( width && (pad & PAD_ZERO) ) {
			pc += printchar (out, ttype, '-');
			--width;
		}
		else {
			*--s = '-';
		}
	}

	return pc + prints (out, ttype, s, width, pad);
}

static int printi(void **out, const char ttype, int i, int b, int sg, int width, int pad, int letbase)
{
	char print_buf[PRINT_BUF_LEN];
	register char *s;
	register int t, neg = 0, pc = 0;
	register unsigned int u = i;

	if (i == 0) {
		print_buf[0] = '0';
		print_buf[1] = '\0';
		return prints (out, ttype, print_buf, width, pad);
	}

	if (sg && b == 10 && i < 0) {
		neg = 1;
		u = -i;
	}

	s = print_buf + PRINT_BUF_LEN-1;
	*s = '\0';

	while (u) {
		t = u % b;
		if( t >= 10 )
			t += letbase - '0' - 10;
		*--s = t + '0';
		u /= b;
	}

	if (neg) {
		if( width && (pad & PAD_ZERO) ) {
			pc += printchar (out, ttype, '-');
			--width;
		}
		else {
			*--s = '-';
		}
	}

	return pc + prints (out, ttype, s, width, pad);
}

int print(void **out, const char ttype, const char *format, va_list args )
{
	register int width, pad;
	register int pc = 0;
	char scr[2], lng=0;
        char** outp;
        
	for (; *format != 0; ++format) {
		if (*format == '%') {
			++format;
			width = pad = 0;
			if (*format == '\0') break;
			if (*format == '%') goto out;
			if (*format == '-') {
				++format;
				pad = PAD_RIGHT;
			}
			while (*format == '0') {
				++format;
				pad |= PAD_ZERO;
			}
			for ( ; *format >= '0' && *format <= '9'; ++format) {
				width *= 10;
				width += *format - '0';
			}
                        if( *format == 'l' ) {
                                lng=1;
                                ++format;
                        }
			if( *format == 's' ) {
				register char *s = (char *)va_arg( args, int );
				pc += prints (out, ttype, s?s:"(null)", width, pad);
				continue;
			}
			if( *format == 'd' ) {
				if(!lng)
                                  pc += printi (out, ttype, va_arg( args, int ), 10, 1, width, pad, 'a');
                                else 
                                  pc += printl (out, ttype, va_arg( args, long ), 10, 1, width, pad, 'a');
                                
				continue;
			}
                   
			if( *format == 'x' ) {
				pc += printi (out, ttype, va_arg( args, int ), 16, 0, width, pad, 'a');
				continue;
			}
			if( *format == 'X' ) {
				pc += printi (out, ttype, va_arg( args, int ), 16, 0, width, pad, 'A');
				continue;
			}
			if( *format == 'u' ) {
				pc += printi (out, ttype, va_arg( args, int ), 10, 0, width, pad, 'a');
				continue;
			}
			if( *format == 'c' ) {
				/* char are converted to int then pushed on the stack */
				scr[0] = (char)va_arg( args, int );
				scr[1] = '\0';
				pc += prints (out, ttype, scr, width, pad);
				continue;
			}
		}
		else {
		out:
			pc += printchar (out, ttype, *format);
		}
	}
	if (ttype == PRINT_TTYPE_STRING){
            outp = (char **) out;
            **outp = '\0';
        }
	va_end( args );
	return pc;
}

