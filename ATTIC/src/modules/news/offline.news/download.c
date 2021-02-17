/*****************************************************************************\
 **                                                                         **
 **  FILE:     offline.news.c                                               **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 1997, Version 0.1                                  **
 **  PURPOSE:  News plugin, download                                        **
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
 * $Id: download.c,v 2.0 2004/09/13 19:44:52 alexios Exp $
 *
 * $Log: download.c,v $
 * Revision 2.0  2004/09/13 19:44:52  alexios
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
 * Revision 0.6  1999/07/18 21:46:06  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 0.5  1998/12/27 15:53:37  alexios
 * Added autoconf support.
 *
 * Revision 0.4  1998/08/14 11:42:12  alexios
 * Added auto-translation to user's character set and to the
 * DOS newline scheme (CRNL).
 *
 * Revision 0.3  1998/07/24 10:21:14  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:06:51  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 10:58:05  alexios
 * First registered revision. Adequate.
 *
 *
 */


static const char rcsinfo[] =
    "$Id: download.c,v 2.0 2004/09/13 19:44:52 alexios Exp $";



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
#include "../news.h"
#include "offline.news.h"
#include <mailerplugins.h>
#include "mbk_offline.news.h"

#define __MAILER_UNAMBIGUOUS__
#include <mbk/mbk_mailer.h>

#define __NEWS_UNAMBIGUOUS__
#include "../mbk_news.h"


#define sop key_owns(&thisuseracc,sopkey)


static int
bltcmp (const void *a, const void *b)
{
	const struct newsbulletin *ba = a;
	const struct newsbulletin *bb = b;
	int     i;

	if ((i = bb->priority - ba->priority) != 0)
		return i;
	if ((i = bb->date - ba->date) != 0)
		return i;
	if ((i = bb->time - ba->time) != 0)
		return i;
	if ((i = bb->num - ba->num) != 0)
		return i;
	return 0;
}


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


int
ondownload ()
{
	DIR    *dp;
	FILE   *fp;
	FILE   *out;
	char    fname[256];
	struct dirent *dirent;
	struct newsbulletin blt, *showlist = NULL, *tmp;
	int     numblt = 0, i, shownheader = 0;

	if (!loadprefs (USERQWK, &userqwk)) {
		error_fatal ("Unable to read user mailer preferences for %s",
			     thisuseracc.userid);
	}

	readxlation ();
	xlationtable = (userqwk.flags & OMF_TR) >> OMF_SHIFT;

	readprefs (&prefs);

	if (!(prefs.flags & ONF_YES))
		return 0;

	if (!key_owns (&thisuseracc, onkey)) {
		prompt (ONDHDR);
		prompt (ONDNAX);
		return 0;
	}

	if ((dp = opendir (mkfname (NEWSDIR))) == NULL) {
		error_fatalsys ("Unable to opendir %s", mkfname (NEWSDIR));
	}

	while ((dirent = readdir (dp)) != NULL) {
		if (!sameto ("hdr-", dirent->d_name))
			continue;
		sprintf (fname, "%s/%s", mkfname (NEWSDIR), dirent->d_name);

		if ((fp = fopen (fname, "r")) == NULL)
			continue;
		if (fread (&blt, sizeof (blt), 1, fp) != 1) {
			fclose (fp);
			continue;
		}
		fclose (fp);

		if (!blt.enabled)
			continue;
		if (!key_owns (&thisuseracc, sopkey)) {
			if (!key_owns (&thisuseracc, blt.key))
				continue;
			if (blt.class[0] &&
			    !sameas (thisuseracc.curclss, blt.class))
				continue;
		}

		numblt++;
		tmp = alcmem (numblt * sizeof (blt));
		if (numblt)
			memcpy (tmp, showlist, (numblt - 1) * sizeof (blt));
		memcpy (&tmp[numblt - 1], &blt, sizeof (blt));
		if (showlist)
			free (showlist);
		showlist = tmp;
	}
	closedir (dp);

	qsort (showlist, numblt, sizeof (blt), bltcmp);

	prompt (ONDHDR);

	if (!numblt) {
		prompt (ONDMT);
		free (showlist);
		return 0;
	}

	msg_set (news_msg);

	if ((out = fopen (newsfile, "w")) == NULL) {
		error_fatalsys ("Unable to create news file %s", newsfile);
	}

	for (i = 0; i < numblt; i++) {
		if (showlist[i].info) {
			char    hdr[256] = { 0 };

			switch (showlist[i].info) {
			case 1:
				sprintf (hdr, "%s",
					 strdate (showlist[i].date));
				break;
			case 2:
				sprintf (hdr, "%s",
					 strtime (showlist[i].time, 1));
				break;
			case 3:
				sprintf (hdr, "%s %s",
					 strdate (showlist[i].date),
					 strtime (showlist[i].time, 1));
				break;
			}
			if (thisuseracc.datelast <= showlist[i].date) {
				if (!shownheader) {
					shownheader = 1;
					fprintf (out, msg_get (NEWS_RDNEWS));
				}
				fprintf (out, msg_get (NEWS_HEADER), hdr,
					 msg_getunit (NEWS_NEWBLT, 1));
			} else {
				if (!shownheader) {
					shownheader = 1;
					fprintf (out, msg_get (NEWS_RDNEWS));
				}
				fprintf (out, msg_get (NEWS_HEADER), hdr, "");
			}
		} else if (thisuseracc.datelast <= showlist[i].date)
			fprintf (out, msg_get (NEWS_NEWBLT));

		sprintf (fname, NEWSFNAME, showlist[i].num);
		fprintf (out, "\n");
		appendfile (fname, out);
		fprintf (out, msg_get (NEWS_BLTDIV));
	}
	free (showlist);

	fclose (out);
	unix2dos (newsfile, newsfile);

	msg_reset ();
	prompt (ONDOK);

	return 0;
}


/* End of File */
