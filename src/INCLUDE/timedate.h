/*****************************************************************************\
 **                                                                         **
 **  FILE:     timedate.h                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 94                                                   **
 **  PURPOSE:  Various time & date handling functions                       **
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
 **                                                                         **
\*****************************************************************************/


/*
 * $Id$
 *
 * $Log$
 * Revision 1.1  2001/04/16 14:48:56  alexios
 * Initial revision
 *
 * Revision 0.3  1998/12/27 15:19:19  alexios
 * Made sure Megistos is Y2K compliant (it is, but you can
 * never be too careful). Added function getdow() to return
 * the day of the week that corresponds to a certain date.
 *
 * Revision 0.2  1997/11/06 20:03:39  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/26 15:48:53  alexios
 * First registered revision. Adequate.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif



#ifndef TIMEDATE_H
#define TIMEDATE_H


/* We include this preemptively so that compilers don't complain about
   already defined __isleap() or isleap() when people later include
   time.h (or whatever WANT_TIME_H includes). */

#define WANT_TIME_H 1
#include <bbsinclude.h>


/* Y2K compliant isleap(). Forced redefinition in case this system
   already has a (broken) version of it. */

#ifndef isleap
#  define isleap(year) __isleap(year)
#endif
#undef __isleap
#define __isleap(year) ((year)%4==0&&((year)%100!=0||(year)%400==0))


#define tdhour(t) ((t>>16)&0x1f)
#define tdmin(t) ((t>>8)&0x3f)
#define tdsec(t) (t&0x3f)

#define tdday(d) (d&0x1f)
#define tdmonth(d) ((d>>8)&0x0f)
#define tdyear(d) (((d>>16)&0xff)+1970)

long maketime(int h, int m, int s);

long makedate(int d, int m, int y);

long today();

long now();

char *strtime(long time,int secstoo);

char *strdate(long date);

long scandate(char *datstr);

int scantime(char *timstr);

long cofdate(long date);

long dateofc(long count);

int getdow(int date);


#endif /* TIMEDATE_H */
