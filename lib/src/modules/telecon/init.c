/*****************************************************************************\
 **                                                                         **
 **  FILE:     init.c                                                       **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 95, Version 0.5                                 **
 **            B, August 96, Version 0.6                                    **
 **  PURPOSE:  Teleconferences, Initialise teleconferences/plugins          **
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
 * Revision 2.0  2004/09/13 19:44:53  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2003/12/27 12:29:39  alexios
 * Adjusted #includes.
 *
 * Revision 1.4  2003/12/24 20:12:09  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.3  1998/12/27 16:10:27  alexios
 * Added autoconf support. One slight bug fix.
 *
 * Revision 0.2  1997/11/06 20:06:11  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 11:08:28  alexios
 * First registered revision. Adequate.
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
#define WANT_SYS_STAT_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_IPC_H 1
#define WANT_SYS_MSG_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "telecon.h"
#include "mbk_telecon.h"


promptblock_t *msg;

int     entrkey;
int     normkey;
int     npaymx;
int     maxcht;
int     lnvcht1;
int     lnvcht2;
int     lnvcht3;
int     tinpsz;
int     msgkey;
int     amsgch;
int     msgchg;
char   *maintopic;
int     defcol;
int     sopkey;
int     chtkey;
int     ichtkey;
int     defint;
int     chatcol1;
int     chatcol2;
char   *stgall1;
char   *stgall2;
char   *stgsec1;
char   *stgsec2;
int     actkey;
int     defact;


void
init ()
{
	mod_init (INI_ALL);

	msg = msg_open ("telecon");
	msg_setlanguage (thisuseracc.language);

	entrkey = msg_int (ENTRKEY, 0, 129);
	normkey = msg_int (NORMKEY, 0, 129);
	npaymx = msg_int (NPAYMX, -1, 32767);
	maxcht = msg_int (MAXCHT, 0, 32767);
	tinpsz = msg_int (TINPSZ, 1, 2047);
	msgkey = msg_int (MSGKEY, 0, 129);
	actkey = msg_int (ACTKEY, 0, 129);
	amsgch = msg_bool (AMSGCH);
	msgchg = msg_int (MSGCHG, -32767, 32767);
	defcol =
	    msg_token (DEFCOL, "DARKBLUE", "DARKGREEN", "DARKCYAN", "DARKRED",
		       "DARKMAGENTA", "BROWN", "GREY", "DARKGREY", "BLUE",
		       "GREEN", "CYAN", "RED", "MAGENTA", "YELLOW", "WHITE");
	sopkey = msg_int (SOPKEY, 0, 129);
	chtkey = msg_int (CHTKEY, 0, 129);
	ichtkey = msg_int (ICHTKEY, 0, 129);
	defint = msg_int (DEFINT, 0, 999);
	defact = msg_bool (DEFACT);
	chatcol1 =
	    msg_token (CHATCOL1, "DARKBLUE", "DARKGREEN", "DARKCYAN",
		       "DARKRED", "DARKMAGENTA", "BROWN", "GREY", "DARKGREY",
		       "BLUE", "GREEN", "CYAN", "RED", "MAGENTA", "YELLOW",
		       "WHITE");
	chatcol2 =
	    msg_token (CHATCOL2, "DARKBLUE", "DARKGREEN", "DARKCYAN",
		       "DARKRED", "DARKMAGENTA", "BROWN", "GREY", "DARKGREY",
		       "BLUE", "GREEN", "CYAN", "RED", "MAGENTA", "YELLOW",
		       "WHITE");
	stgall1 = strdup (msg_get (STGALL1));
	stgall2 = strdup (msg_get (STGALL2));
	stgsec1 = strdup (msg_get (STGSEC1));
	stgsec2 = strdup (msg_get (STGSEC2));

	signal (SIGMAIN, actionhandler);
}


/* End of File */
