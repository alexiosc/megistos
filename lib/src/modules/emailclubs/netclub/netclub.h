/*****************************************************************************\
 **                                                                         **
 **  FILE:     netclub.h                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1999                                                 **
 **  PURPOSE:  Synchronise BBS clubs by interfacing to the MetaBBS daemon   **
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
 * Revision 2.0  2004/09/13 19:44:51  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.4  2003/12/23 23:20:23  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:08  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 *
 */


static const char rcsinfo[] =
    "$Id$";



#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_FCNTL_H 1
#define WANT_SYS_STAT_H 1
#define WANT_RPC_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>


#define MODE_SYNC       0
#define MODE_LISTCLUBS  1
#define MODE_REPORT     2
#define MODE_CLUBINFO   3
#define MODE_NOP       -1


extern char *bbscode;
extern int mode;
extern int debug;		/* Debugging mode */
extern int force;
extern int dryrun;		/* Dry run */
extern char *sys;
extern char *clubname;


void    iterate ();

void    print_report (char *fname, char *sysname);

void    list_clubs (char *fname, char *cp);

void    club_info (char *fname, char *cp, char *clubname);

void    club_sync (char *fname, char *cp);



/* End of File */
