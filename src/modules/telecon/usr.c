/*****************************************************************************\
 **                                                                         **
 **  FILE:     usr.c                                                        **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 95, Version 0.5                                 **
 **  PURPOSE:  Teleconferences, user handling functions                     **
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
 * $Id: usr.c,v 2.0 2004/09/13 19:44:53 alexios Exp $
 *
 * $Log: usr.c,v $
 * Revision 2.0  2004/09/13 19:44:53  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2003/12/27 12:29:38  alexios
 * Adjusted #includes.
 *
 * Revision 1.4  2003/12/24 20:12:08  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.5  1999/07/18 21:48:36  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 0.4  1998/12/27 16:10:27  alexios
 * Added autoconf support.
 *
 * Revision 0.3  1998/07/24 10:24:49  alexios
 * Generic debugging. Migrated to bbslib 0.6.
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
    "$Id: usr.c,v 2.0 2004/09/13 19:44:53 alexios Exp $";



#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "telecon.h"
#include "mbk_telecon.h"


struct tlcuser tlcu;


int
loadtlcuser (char *userid, struct tlcuser *tlc)
{
	char    fname[256];
	FILE   *fp;

	sprintf (fname, "%s/%s", mkfname (TELEUSRDIR), userid);
	if ((fp = fopen (fname, "r")) == NULL)
		return 0;
	if (fread (tlc, sizeof (struct tlcuser), 1, fp) != 1) {
		fclose (fp);
		return 0;
	}
	fclose (fp);
	return 1;
}


int
savetlcuser (char *userid, struct tlcuser *tlc)
{
	char    fname[256];
	FILE   *fp;

	sprintf (fname, "%s/%s", mkfname (TELEUSRDIR), userid);
	if ((fp = fopen (fname, "w")) == NULL)
		return 0;
	if (fwrite (tlc, sizeof (struct tlcuser), 1, fp) != 1) {
		error_fatalsys ("Unable to save telecon user %s", userid);
	}
	fclose (fp);
	return 1;
}


void
makenewuser ()
{
	memset (&tlcu, 0, sizeof (tlcu));
	tlcu.colour = defcol;
	tlcu.flags = TLF_STARTMAIN | TLF_BEGUNINV;
	tlcu.flags = defint;
	tlcu.actions = defact;
	savetlcuser (thisuseracc.userid, &tlcu);
}


/* End of File */
