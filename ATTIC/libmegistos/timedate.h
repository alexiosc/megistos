/** @file    timedate.h
    @brief   Time and date operations.
    @author  Alexios

    This header file includes functions for obtaining and operating on times
    and dates. This was the first interface I specified for Megistos, while I
    was still a UNIX-newbie in 1994. As such, it could be suitable for a
    16-bit, DOS-based BBS system, but it's exceptionally bad for a 32- or
    64-bit modern operating system. Expect these functions to go away in the
    near future. Here's the plan:

    - Kludge API to obtain and deal with proper, <tt>time_t</tt>-based dates
      and times. It should still try to deal with the existing 16-bit
      ones. This should be easy, as the 16-bit values are all less that 65535
      and all dates past 6pm on the 1st of January, 1970 are greater than
      65535. Both time formats should be accepted, but only the proper
      (<tt>time_t</tt>) format should be written.

    - Make conversion scripts for times/dates in existing modules.

    - Do away with the original function names to avoid modules calling them
      and assuming the wrong assumptions. Write new, (<tt>time_t</tt>)-only
      API.

    - Correct all subsystems and modules that will no longer compile.

    - Document new API.

    Original banner, legalese and change history follow.

    @par
    @verbatim

 *****************************************************************************
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
 *****************************************************************************

 *
 * $Id: timedate.h,v 2.0 2004/09/13 19:44:34 alexios Exp $
 *
 * $Log: timedate.h,v $
 * Revision 2.0  2004/09/13 19:44:34  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2003/12/19 13:25:18  alexios
 * Updated include directives.
 *
 * Revision 1.4  2003/09/27 20:32:21  alexios
 * Documented more of the file and moved existing documentation from
 * doc++ to doxygen format.
 *
 * Revision 1.3  2001/04/22 14:49:04  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
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
 *

@endverbatim
*/

/*@{*/


#ifndef RCS_VER 
#define RCS_VER "$Id: timedate.h,v 2.0 2004/09/13 19:44:34 alexios Exp $"
#endif



#ifndef TIMEDATE_H
#define TIMEDATE_H


/** @defgroup timedate Time and Date handling

    This module is populated mostly by horrible legacy functions originally
    meant to provide a modicum of Major BBS compatibility in time
    calculations. UNIX, of course, does not separate time and date functions
    like MS-DOS (and the Major BBS), which is why the functions here are so
    bletcherous. Thankfully, they can be replaced by more modern equivalent
    functions @e and retain their kludgy old functionality.

    Currently, the functions here are not documented, and they will become
    deprecated soon enough.

@{*/


/* We include this preemptively so that compilers don't complain about
   already defined __isleap() or isleap() when people later include
   time.h (or whatever WANT_TIME_H includes). */

#define WANT_TIME_H 1
#include <megistos/bbsinclude.h>


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

/*@}*/
/*
LocalWords: timedate Alexios doc Megistos newbie BBS API tt pm legalese
LocalWords: otnotesize alexios Exp bbs getdow GPL ifndef VER endif isleap
LocalWords: bbsinclude undef tdhour tdmin tdsec tdday tdmonth tdyear int
LocalWords: maketime makedate strtime secstoo strdate scandate datstr
LocalWords: scantime timstr cofdate dateofc
*/
