/*****************************************************************************\
 **                                                                         **
 **  FILE:     read.c                                                       **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 1996, Version 0.5                               **
 **  PURPOSE:  Read bulletins                                               **
 **  NOTES:                                                                 **
 **                                                                         **
\*****************************************************************************/


/*
 * $Id: read.c,v 2.0 2004/09/13 19:44:50 alexios Exp $
 *
 * $Log: read.c,v $
 * Revision 2.0  2004/09/13 19:44:50  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2003/12/27 12:29:40  alexios
 * Adjusted #includes.
 *
 * Revision 1.4  2003/12/24 20:12:14  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.5  1999/07/28 23:10:22  alexios
 * Added support for downloading bulletins.
 *
 * Revision 0.4  1998/12/27 15:27:54  alexios
 * Added autoconf support.
 *
 * Revision 0.3  1998/07/24 10:14:42  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/05 11:22:37  alexios
 * Changed calls to audit() so they take advantage of the new
 * auditing scheme.
 *
 * Revision 0.1  1997/08/28 10:07:31  alexios
 * First registered revision, adequate.
 *
 *
 */


static const char rcsinfo[] =
    "$Id: read.c,v 2.0 2004/09/13 19:44:50 alexios Exp $";



#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "mbk_bulletins.h"
#include "bltidx.h"
#include "bulletins.h"


int
fnamexref (char *fname)
{				/* Not much of an xref function yet */
	int     res;

	if (club[0])
		return dbexists (club, fname);
	if ((res = dbchkambiguity (fname)) == 2) {
		prompt (BLTAMB, fname);
		listambiguous (fname);
	}
	return res;
}


int
getblt (int pr, struct bltidx *blt)
{
	char   *i;
	char    c;

      again:
	for (;;) {
		fmt_lastresult = 0;
		if ((c = cnc_more ()) != 0) {
			if (sameas (cnc_nxtcmd, "X"))
				return 0;
			if (sameas (cnc_nxtcmd, "?")) {
				list (0);
				cnc_end ();
				continue;
			}
			i = cnc_word ();
		} else {
			prompt (pr);
			inp_get (0);
			cnc_begin ();
			i = cnc_word ();
			if (!margc || (margc == 1 && sameas (margv[0], "."))) {
				cnc_end ();
				continue;
			} else if (inp_isX (margv[0]))
				return 0;
			if (sameas (margv[0], "?")) {
				list (0);
				cnc_end ();
				continue;
			}
		}

		if (!i[0] || sameas (i, ".")) {
			cnc_end ();
			continue;
		} else if (dbnumexists (atoi (i))) {
			break;
		} else {
			int     res = fnamexref (i);

			if (res == 1)
				break;
			else if (!res) {
				if (club[0])
					prompt (UNKBLTC, club);
				else
					prompt (UNKBLT);
			}
			cnc_end ();
			continue;
		}
	}
	dbget (blt);
	if ((club[0] && strcmp (club, blt->area)) ||
	    getclubax (&thisuseracc, blt->area) < CAX_READ) {
		prompt (UNKBLTC, club);
		cnc_end ();
		goto again;
	}
	return 1;
}



void
bltread ()
{
	struct bltidx blt;

	if (!(club[0] ? dblistfind (club, 1) : dblistfirst ())) {
		if (!club[0])
			prompt (BLTNOBT);
		else
			prompt (CLBNOBT, club);
		return;
	}

	if (!getblt (READBLT, &blt))
		return;

	bltinfo (&blt);

	showblt (&blt);
}



static void
offerblt (struct bltidx *blt)
{
	char    fname[256], lock[256];
	char    a[256];

	prompt (BLTHDR);

	strcpy (fname,
		mkfname (MSGSDIR "/%s/%s/%s", blt->area, MSGBLTDIR,
			 blt->fname));
	sprintf (lock, "%s-%s-%s-%s", BLTREADLOCK, thisuseracc.userid,
		 blt->area, blt->fname);

	lock_place (lock, "downloading");
	fmt_lastresult = PAUSE_CONTINUE;

	sprintf (a, AUD_BLTDNL, thisuseracc.userid, blt->fname, blt->area);
	xfer_setaudit (AUT_BLTDNL, AUS_BLTDNL, a, 0, NULL, NULL);

	if (xfer_add (FXM_DOWNLOAD, fname, dnldesc, 0, -1)) {
		xfer_run ();
		xfer_kill_list ();
	}

	blt->timesread++;
	dbupdate (blt);
	lock_rm (lock);
}



void
bltdnl ()
{
	struct bltidx blt;

	if (!(club[0] ? dblistfind (club, 1) : dblistfirst ())) {
		if (!club[0])
			prompt (BLTNOBT);
		else
			prompt (CLBNOBT, club);
		return;
	}

	if (!getblt (DNLBLT, &blt))
		return;

	bltinfo (&blt);

	offerblt (&blt);
}



void
showblt (struct bltidx *blt)
{
	char    fname[256], lock[256];

	prompt (BLTHDR);

	strcpy (fname,
		mkfname (MSGSDIR "/%s/%s/%s", blt->area, MSGBLTDIR,
			 blt->fname));
	sprintf (lock, "%s-%s-%s-%s", BLTREADLOCK, thisuseracc.userid,
		 blt->area, blt->fname);

	thisuseronl.flags |= OLF_BUSY;
	lock_place (lock, "reading");
	fmt_lastresult = PAUSE_CONTINUE;
	if (!out_catfile (fname)) {
		prompt (PANIC1, blt->fname);
		lock_rm (lock);
		thisuseronl.flags &= ~OLF_BUSY;
		return;
	}
	if (fmt_lastresult == PAUSE_QUIT) {
		prompt (ABORT);
		lock_rm (lock);
		thisuseronl.flags &= ~OLF_BUSY;
		return;
	}
	prompt (ENDBLT);
	thisuseronl.flags &= ~OLF_BUSY;

	blt->timesread++;
	dbupdate (blt);
	lock_rm (lock);


	/* Audit it */

	if (audrd)
		audit (thisuseronl.channel, AUDIT (BLTRD),
		       thisuseracc.userid, blt->fname, blt->area);
}


/* End of File */
