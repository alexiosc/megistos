/*****************************************************************************\
 **                                                                         **
 **  FILE:     reqman.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 1997, Version 0.1                                  **
 **  PURPOSE:  Clean up any unsatisfied leftover foreign requests           **
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
 * $Id: reqman.c,v 2.0 2004/09/13 19:44:51 alexios Exp $
 *
 * $Log: reqman.c,v $
 * Revision 2.0  2004/09/13 19:44:51  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2003/12/27 12:29:39  alexios
 * Adjusted #includes.
 *
 * Revision 1.4  2003/12/25 08:26:20  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.4  1998/12/27 15:48:12  alexios
 * Added autoconf support.
 *
 * Revision 0.3  1998/07/24 10:20:56  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:06:43  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 10:55:29  alexios
 * First registered revision. Adequate.
 *
 *
 */


static const char rcsinfo[] =
    "$Id: reqman.c,v 2.0 2004/09/13 19:44:51 alexios Exp $";



#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "offline.mail.h"
#include <mailerplugins.h>
#include "mbk_offline.mail.h"



int
reqman ()
{
	struct reqidx idx;
	int     res, shown = 0;

	openreqdb ();
	res = getfirstreq (&idx);

	for (res = getfirstreq (&idx); res; res = getnextreq (&idx)) {
		if (idx.priority != RQP_CTLMSG)
			continue;

		if (!shown) {
			shown = 1;
			prompt (RQMUNS);
		}

		/* Remove the current request from the database */

		prompt (RQMTAB, ctlname[0], idx.reqarea, idx.reqfname);

		unlink (idx.dosfname);
		if (!rmrequest (&idx)) {
			error_fatal
			    ("Unable to remove request %d from the database.",
			     idx.reqnum);
		}
	}

	if (shown)
		prompt (ENDRQM);
	return 0;
}


/* End of File */
