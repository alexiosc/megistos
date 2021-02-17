/*****************************************************************************\
 **                                                                         **
 **  FILE:     stats.h                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, March 95                                                  **
 **  PURPOSE:  Manage statistical files and draw graphs and things          **
 **  NOTES:    This is currently a -cleanup only module!                    **
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
 * $Id: stats.h,v 2.0 2004/09/13 19:44:53 alexios Exp $
 *
 * $Log: stats.h,v $
 * Revision 2.0  2004/09/13 19:44:53  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2003/12/27 12:34:53  alexios
 * Removed extraneous rcsinfo.
 *
 * Revision 1.4  2003/12/24 20:12:09  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.3  1997/11/06 20:05:23  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/11/05 11:12:54  alexios
 * Declared AUT_ values for the program's two own audit trail
 * entries (all according to the new auditing scheme).
 *
 * Revision 0.1  1997/08/28 11:07:38  alexios
 * First registered revision. Adequate.
 *
 *
 */


/*                   123456789012345678901234567890 */
#define AUS_STATCUB "GENERATING STATISTICS"
#define AUS_STATCUE "END OF STATISTICS CLEANUP"

/*                   1234567890123456789012345678901234567890123456789012... */
#define AUD_STATCUB "%d Day(s) since last statistics cleanup"
#define AUD_STATCUE ""

#define AUT_STATCUB (AUF_EVENT|AUF_INFO)
#define AUT_STATCUE (AUF_EVENT|AUF_INFO)


#define DAYSSINCEFILE "LAST.CLEANUP"
#define MAXCLSS       128
#define MAXTTYS       256
#define MAXBAUDS      32
#define MAXMODS       128

#define AVERAGE       0
#define TOTAL         1

#define CREDITS       0
#define MINUTES       1
#define CALLS         2

#define BAUDSTATS     0
#define CLSSTATS      1
#define DAYSTATS      2
#define MODSTATS      3
#define TTYSTATS      4

#define FORTODAY      0
#define THISMONTH     1
#define THISYEAR      2
#define FOREVER       3


extern int dayssince;
extern char oldstatsdir[256];
extern char everdir[256];
extern promptblock_t *msg;

extern char *statfiles[];


void    init ();
void    getstats ();
void    done ();


/* End of File */
