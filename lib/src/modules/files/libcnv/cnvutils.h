/*****************************************************************************\
 **                                                                         **
 **  FILE:     utils.c                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  PURPOSE:  Utility functions for conversions.                           **
 **  NOTES:                                                                 **
 **  LEGALESE:                                                              **
 **                                                                         **
 **  This program is free software; you  can redistribute it and/or modify  **
 **  it under the terms of the GNU  General Public License as published by  **
 **  the Free Software Foundation; either version 2 of the License, or (at  **
 **  your option) any later version.                                        **
 **                                                                         **
 **  This program is distributed  in the hope  that it will be useful, but  **
 **  WITHOUT    ANY WARRANTY;   without  even  the    implied warranty  of  **
 **  MERCHANTABILITY or  FITNESS FOR  A PARTICULAR  PURPOSE.   See the GNU  **
 **  General Public License for more details.                               **
 **                                                                         **
 **  You  should have received a copy   of the GNU  General Public License  **
 **  along with    this program;  if   not, write  to  the   Free Software  **
 **  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.              **
\*****************************************************************************/


/*
 * $Id$
 *
 * $Log$
 * Revision 1.2  2001/04/16 21:56:32  alexios
 * Completed 0.99.2 API, dragged all source code to that level (not as easy as
 * it sounds).
 *
 * Revision 0.2  1998/12/27 15:40:03  alexios
 * Added autoconf support.
 *
 * Revision 0.1  1998/04/16 09:27:16  alexios
 * Initial version.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif


#define WANT_TIME_H 1
#include <bbsinclude.h>



#define stg2short(s) (*((unsigned short int*)s))
#define stg2int(s)   (*((unsigned int*)s))


#if (__BYTE_ORDER==__LITTLE_ENDIAN)

#define convshort(x) ((((x)&0xff)<<8)|(((x)&0xff00)>>8))
#define convint(x)   ((convshort((x)&0xffff)<<16)|convshort(((x)&0xffff0000)>>16))

#else /* We'll just assume this isn't running on a PDP machine, ok? */

#define convshort(x) (x)
#define convint(x)   (x)

#endif


int convert_date(unsigned short int mbbsdate);

int convert_time(short int mbbstime);

time_t convert_timedate(unsigned short int mbbsdate,
			unsigned short int mbbstime);

char *lcase(char *s);

char *stg(char *s);

char *leafname(char *s);

