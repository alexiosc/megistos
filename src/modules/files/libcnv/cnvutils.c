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
 * $Id: cnvutils.c,v 2.0 2004/09/13 19:44:51 alexios Exp $
 *
 * $Log: cnvutils.c,v $
 * Revision 2.0  2004/09/13 19:44:51  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.4  2003/12/24 20:12:13  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.3  1998/12/27 15:40:03  alexios
 * Added autoconf support.
 *
 * Revision 0.2  1998/04/21 10:13:39  alexios
 * Daily maintenance of the file library.
 *
 * Revision 0.1  1998/04/16 09:27:16  alexios
 * Initial version.
 *
 *
 */


static const char rcsinfo[] =
    "$Id: cnvutils.c,v 2.0 2004/09/13 19:44:51 alexios Exp $";


#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_TIME_H 1
#include <bbsinclude.h>

#include <bbs.h>


int
convert_date (unsigned short int mbbsdate)
{
	int     day = mbbsdate & 0x1f;
	int     month = (mbbsdate >> 5) & 0xf;
	int     year = 1980 + ((mbbsdate >> 9) & 0x7f);

	return makedate (day, month, year);
}


int
convert_time (unsigned short int mbbstime)
{
	int     sec = (mbbstime & 0x1f) << 1;	/* DOS times have a resolution of 2 secs */
	int     min = (mbbstime >> 5) & 0x3f;
	unsigned int hour = (mbbstime >> 11);

	return maketime (hour, min, sec);
}


time_t
convert_timedate (unsigned short int mbbsdate, unsigned short int mbbstime)
{
	struct tm tm;

	tm.tm_mday = mbbsdate & 0x1f;
	tm.tm_mon = ((mbbsdate >> 5) & 0xf);
	tm.tm_year = 80 + ((mbbsdate >> 9) & 0x7f);
	tm.tm_hour = (mbbstime >> 11);
	tm.tm_min = (mbbstime >> 5) & 0x3f;
	tm.tm_sec = (mbbstime & 0x1f) << 1;	/* DOS times have a resolution of 2 secs */
	return mktime (&tm);
}


char   *
stg (char *s)
{
#ifndef ASIS
	static char ret[16386], *cp, *rp;

	for (cp = s, rp = ret; *cp; cp++) {
		if (isprint (*cp))
			*rp++ = *cp;
		else {
			char    tmp[16];

			sprintf (tmp, "\\x%02X", (*cp) & 0xff);
			*rp = 0;
			strcat (rp, tmp);
			rp += 4;
		}
	}
	*rp = 0;
	return ret;
#else
	return s;
#endif
}


/* End of File */
