/*****************************************************************************\
 **                                                                         **
 **  FILE:     offline.bulletins.c                                          **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 1997, Version 0.1                                  **
 **  PURPOSE:  Bulletins plugin, download                                   **
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
 * Revision 2.0  2004/09/13 19:44:50  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2003/12/27 12:29:40  alexios
 * Adjusted #includes.
 *
 * Revision 1.4  2003/12/25 08:26:21  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.6  1999/07/18 21:43:59  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 0.5  1998/12/27 15:46:41  alexios
 * Added autoconf support.
 *
 * Revision 0.4  1998/08/14 11:35:14  alexios
 * Arranged for automatic translation to user's character set.
 * Also translated all output to the DOS newline scheme (CRNL).
 *
 * Revision 0.3  1998/07/24 10:20:15  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:06:59  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 10:53:22  alexios
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
#define WANT_TIME_H 1
#define WANT_SYS_STAT_H 1
#define WANT_DIRENT_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "offline.bulletins.h"
#include <mailerplugins.h>
#include "mbk_offline.bulletins.h"
#include "../bulletins/bulletins.h"

#define __MAILER_UNAMBIGUOUS__
#include <mbk/mbk_mailer.h>

#define __BULLETINS_UNAMBIGUOUS__
#include "../mbk_bulletins.h"


static void
appendfile (char *fname, FILE * out)
{
	FILE   *fp;

	if ((fp = fopen (fname, "r")) != NULL) {
		while (!feof (fp)) {
			char    line[MSGBUFSIZE];
			int     num = fread (line, 1, sizeof (line) - 1, fp);

			line[num] = 0;
			if (num)
				fwrite (line, num, 1, out);
		}
		fclose (fp);
	}
}


static int
addtodoorid ()
{
	FILE   *fp;

	if ((fp = fopen ("door.id", "a")) == NULL) {
		fclose (fp);
		return 1;
	}
	fprintf (fp, "CONTROLTYPE = BLT-REQ\r\n");
	fprintf (fp, "CONTROLTYPE = BLT-IDX\r\n");
	fprintf (fp, "BLTIDXFILE = %s\r\n", bltidfn);
	fclose (fp);
	return 0;
}


static int serial = 0;


static int
process (char *area, char *name)
{
	struct bltidx idx;
	char    fname[256], lock[256], outname[256];
	FILE   *out;
	int     oldansi;

	if (serial < 9999) {
		sprintf (outname, "blt-%d", ++serial);
	} else {
		++serial;
		sprintf (outname, "blt-04%d.%03d", serial % 10000,
			 serial / 10000);
	}

	if ((out = fopen (outname, "w")) == NULL) {
		prompt (OBDLIO, area, name);
		return 0;
	}

	if (!dbexists (area, name)) {
		prompt (OBDLUB, area, name);
		return 0;
	} else
		dbget (&idx);

	oldansi = out_flags & OFL_ANSIENABLE;
	out_setansiflag (0);
	{
		char    buf[8192];

		sprompt (buf, OBDLCR);
		fputs (buf, out);
	}
	out_setansiflag (oldansi);

	strcpy (fname,
		mkfname (MSGSDIR "/%s/%s/%s", idx.area, MSGBLTDIR, idx.fname));
	sprintf (lock, "%s-%s-%s-%s", BLTREADLOCK, thisuseracc.userid,
		 idx.area, idx.fname);
	lock_place (lock, "reading");
	appendfile (fname, out);
	lock_rm (lock);
	unix2dos (outname, outname);
	prompt (OBDLOK, area, name, outname);

	return 0;
}


int
mkindex ()
{
	FILE   *out;
	struct bltidx blt;
	char    oldclub[16] = { 0 }, buf[8192];
	int     i = 0, skip = 0;
	int     oldansi;

	prefs.flags &= ~OBF_REQIDX;
	writeprefs (&prefs);

	prompt (OBDL);

	if (!dblistfirst ()) {
		prompt (OBDLMT);
		return 0;
	} else
		prompt (OBDLMK);

	if ((out = fopen (bltidfn, "w")) == NULL) {
		error_fatalsys ("Unable to create bulletin index %s", bltidfn);
	}

	oldansi = out_flags & OFL_ANSIENABLE;
	out_setansiflag (prefs.flags & OBF_ANSI);

	sprompt (buf, OBDLPR, strtime (now (), 1), strdate (today ()));
	fputs (buf, out);

	msg_set (bulletins_msg);

	do {
		dbget (&blt);

		if (strcmp (oldclub, blt.area)) {
			if (oldclub[0]) {
				sprompt (buf, BULLETINS_LSTEND2);
				fputs (buf, out);
			}
			if ((skip =
			     getclubax (&thisuseracc,
					blt.area) < CAX_READ) == 0) {
				sprompt (buf, BULLETINS_BLTLSHD2, blt.area);
				fputs (buf, out);
				strcpy (oldclub, blt.area);
			}
		}
		if (skip)
			continue;

		i++;
		sprompt (buf, BULLETINS_BLTLST2,
			 blt.num,
			 blt.fname, blt.author, blt.descr, blt.timesread);
		fputs (buf, out);
	} while (dblistnext ());

	if (i) {
		sprompt (buf, BULLETINS_LSTEND2);
		fputs (buf, out);
	}

	msg_reset ();
	sprompt (buf, OBDLFT);
	fputs (buf, out);

	fclose (out);
	unix2dos (bltidfn, bltidfn);
	out_setansiflag (oldansi);
	return 0;
}


int
obdownload ()
{
	struct reqidx idx;
	int     res, stop = 0;
	int     bltdb;

	if (!loadprefs (USERQWK, &userqwk)) {
		error_fatal ("Unable to read user mailer preferences for %s",
			     thisuseracc.userid);
	}

	readxlation ();
	xlationtable = (userqwk.flags & OMF_TR) >> OMF_SHIFT;

	readprefs (&prefs);
	dbopen ();
	d_dbget (&bltdb);

	if (addtodoorid ())
		return 1;
	if (prefs.flags & (OBF_INDEX | OBF_REQIDX))
		if (mkindex ())
			return 1;

	openreqdb ();
	res = getfirstreq (&idx);

	for (res = getfirstreq (&idx); res; res = getnextreq (&idx)) {
		if (!(idx.reqflags & RQF_BULLETIN))
			continue;
		if (!sameas (idx.dosfname, "BULLETIN"))
			continue;

		d_dbset (bltdb);
		stop = !process (idx.reqarea, idx.reqfname);

		/* Remove the current request from the database */

		unlink (idx.dosfname);
		if (!rmrequest (&idx)) {
			error_fatal
			    ("Unable to remove request %d from the database.",
			     idx.reqnum);
		}

		if (stop)
			break;
	}

	return 0;
}


/* End of File */
