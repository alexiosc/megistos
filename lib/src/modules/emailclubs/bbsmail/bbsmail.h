/*****************************************************************************\
 **                                                                         **
 **  FILE:     bbsmail.h                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: B, May 1995, Version 0.5                                     **
 **            C, July 1995, Version 1.0                                    **
 **            D, August 1996, Version 2.0                                  **
 **  PURPOSE:  Various support functions for bbsmail                        **
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
 * Revision 1.4  2003/12/23 23:20:23  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.4  1999/07/28 23:19:38  alexios
 * Moved run() to its own .c file in anticipation of a united
 * bbsmail/netclub binary.
 *
 * Revision 1.3  1998/12/27 16:31:55  alexios
 * Added autoconf support.
 *
 * Revision 1.2  1997/11/06 20:17:18  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 1.1  1997/11/05 10:45:58  alexios
 * No changes.
 *
 * Revision 1.0  1997/08/28 11:23:40  alexios
 * Initial revision
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
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include <megistos/mbk_emailclubs.h>


/* netmail.c */

void    handlenetmail (struct message *msg, char *srcname);

void    checknetmail (struct message *msg, char *srcname);


/* resolve.c */

void    resolverecipient (char *s, char *by);

void    checkautofw (struct message *msg);


/* utils.c */

void    bbsencrypt (char *buf, int size, int key);

void    addihave (struct message *msg);

void    copyatt (int copymode, struct message *msg, int email,
		 char *attachment);



/* msghdr.c */

void    readmsghdr (char *fname, struct message *msg);

void    writemsghdr (char *fname, struct message *msg);

void    preparemsghdr (struct message *msg, int email);

void    writemessage (char *body, struct message *msg, int email);


/* msgnum.c */

void    getemsgnum (struct message *msg);

void    getcmsgnum (struct message *msg);


/* database.c */

void    addtodb (struct message *msg, int email);


/* bbsmail.c */

extern promptblock_t *msg;
extern int usercaller;
extern char *bbscode;


/* bbsmail_run.c */

void    bbsmail_run (char *fname, char *srcname, int copymode,
		     char *attachment);


/* End of File */
