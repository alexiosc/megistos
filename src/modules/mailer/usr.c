/*****************************************************************************\
 **                                                                         **
 **  FILE:     usr.c                                                        **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1997, Version 0.1                                    **
 **  PURPOSE:  User preference management                                   **
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
 * $Id: usr.c,v 2.0 2004/09/13 19:44:52 alexios Exp $
 *
 * $Log: usr.c,v $
 * Revision 2.0  2004/09/13 19:44:52  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2003/12/27 12:29:39  alexios
 * Adjusted #includes.
 *
 * Revision 1.4  2003/12/24 20:12:10  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.6  1999/07/18 21:42:47  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 0.5  1998/12/27 15:45:11  alexios
 * Added autoconf support.
 *
 * Revision 0.4  1998/08/14 11:31:09  alexios
 * Removed newlines from error_fatal() calls (ouch).
 *
 * Revision 0.3  1998/07/24 10:19:54  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:06:32  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 10:51:40  alexios
 * First registered revision. Adequate.
 *
 *
 */


static const char rcsinfo[] =
    "$Id: usr.c,v 2.0 2004/09/13 19:44:52 alexios Exp $";



#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_SYS_STAT_H 1
#define WANT_ERRNO_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "mailer.h"
#include "mbk_mailer.h"


struct usrqwk userqwk;


int
loadprefs (char *plugin, void *buffer)
{
	FILE   *fp;
	char    fname[256];
	struct stat st;
	struct usrtag tag;

	sprintf (fname, "%s/%s", mkfname (MAILERUSRDIR), thisuseracc.userid);

	if (stat (fname, &st))
		return -1;

	if ((fp = fopen (fname, "r")) == NULL) {
		error_fatalsys ("Unable to open %s for reading", fname);
	}

	while (ftell (fp) < st.st_size) {
		if (!fread (&tag, sizeof (tag), 1, fp)) {
			error_fatalsys ("Unable to read tag from %s", fname);
		}
		if (!strcmp (plugin, tag.plugin)) {
			if (!fread (buffer, tag.len, 1, fp)) {
				error_fatalsys ("Unable to read from %s",
						fname);
			}
			return 1;
		}
		if (fseek (fp, tag.len, SEEK_CUR)) {
			error_fatalsys ("Unable to seek while reading from %s",
					fname);
		}
	}
	fclose (fp);

	return 0;
}


void
saveprefs (char *plugin, int len, void *buffer)
{
	FILE   *fp;
	char    fname[256];
	struct stat st;
	struct usrtag tag;

	sprintf (fname, "%s/%s", mkfname (MAILERUSRDIR), thisuseracc.userid);

	if (!stat (fname, &st)) {
		if ((fp = fopen (fname, "r+")) == NULL) {
			error_fatalsys ("Unable to open %s for writing",
					fname);
		}
	} else {
		if ((fp = fopen (fname, "w+")) == NULL) {
			error_fatalsys ("Unable to create %s", fname);
		}
		st.st_size = 0;
	}

	while (ftell (fp) < st.st_size) {
		if (!fread (&tag, sizeof (tag), 1, fp)) {
			error_fatalsys ("Unable to read tag from %s", fname);
		}
		if (!strcmp (plugin, tag.plugin)) {
			if (tag.len != len) {
				error_fatalsys
				    ("Block length mismatch, %d!=%d.", len,
				     tag.len);
			}
			errno = 0;
			if (!fwrite (buffer, tag.len, 1, fp)) {
				error_fatalsys ("Unable to write to %s",
						fname);
			}
			fclose (fp);
			return;
		}
		if (fseek (fp, tag.len, SEEK_CUR)) {
			error_fatalsys ("Unable to seek while reading from %s",
					fname);
		}
	}

	bzero (&tag, sizeof (tag));
	strcpy (tag.plugin, plugin);
	tag.len = len;
	if (!fwrite (&tag, sizeof (tag), 1, fp)) {
		error_fatalsys ("Unable to write tag to %s", fname);
	}
	if (!fwrite (buffer, tag.len, 1, fp)) {
		error_fatalsys ("Unable to write to %s", fname);
	}
	fclose (fp);
}


/* End of File */
