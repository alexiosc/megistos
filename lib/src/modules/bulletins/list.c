/*****************************************************************************\
 **                                                                         **
 **  FILE:     list.c                                                       **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 1996, Version 0.5                               **
 **  PURPOSE:  List the bulletins                                           **
 **  NOTES:                                                                 **
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
 * Revision 1.4  2003/12/24 20:12:15  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.5  1999/07/28 23:10:22  alexios
 * Fixed slight but that wouldn't show the 'no bulletins' message,
 * even when there *were* no bulletins available.
 *
 * Revision 0.4  1998/12/27 15:27:54  alexios
 * Added autoconf support.
 *
 * Revision 0.3  1998/07/24 10:14:42  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/09/12 13:03:45  alexios
 * Fixed bug where listing bulletins would display list footers
 * for clubs the user has no access to.
 *
 * Revision 0.1  1997/08/28 10:07:31  alexios
 * First registered revision, adequate.
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
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "mbk_bulletins.h"
#include "bltidx.h"
#include "bulletins.h"
#include <libtyphoon/typhoon.h>


void
list (int full)
{
	struct bltidx blt;
	char    oldclub[16] = { 0 }, c;
	int     i = 0, skip = 0;
	int     first = 1;

	if (!(club[0] ? dblistfind (club, 1) : dblistfirst ())) {
		if (!club[0])
			prompt (BLTNOBT);
		else
			prompt (CLBNOBT, club);
		return;
	}

	inp_nonblock ();
	do {
		dbget (&blt);

		if (read (fileno (stdin), &c, 1) &&
		    ((c == 13) || (c == 10) || (c == 27) || (c == 15) ||
		     (c == 3)))
			fmt_lastresult = PAUSE_QUIT;

		if (club[0] && strcmp (blt.area, club))
			break;

		if (strcmp (oldclub, blt.area)) {
			first = 0;
			if (i && oldclub[0])
				prompt (full ? LSTEND2 : LSTEND);
			skip = getclubax (&thisuseracc, blt.area) < CAX_READ;
			i = 0;
			if (!skip) {
				prompt ((full ? BLTLSHD2 : BLTLSHD), blt.area);
				strcpy (oldclub, blt.area);
			}
		}

		if (fmt_lastresult == PAUSE_QUIT) {
			prompt (LSTCAN);
			inp_block ();
			return;
		}

		if (skip)
			continue;

		i++;
		if (full) {
			prompt (BLTLST2, blt.num, blt.fname, blt.author,
				blt.descr, blt.timesread);
		} else {
			prompt (BLTLST, blt.num, blt.author, blt.descr);
		}
		if (fmt_lastresult == PAUSE_QUIT) {
			prompt (LSTCAN);
			inp_block ();
			return;
		}
	} while (dblistnext ());

	if (fmt_lastresult != PAUSE_QUIT && first == 1) {
		if (!club[0])
			prompt (BLTNOBT);
		else
			prompt (CLBNOBT, club);
	}

	inp_block ();
	if (i)
		prompt (full ? LSTEND2 : LSTEND);
}


int
bltcmp (const void *a, const void *b)
{
	struct bltidx *A = (struct bltidx *) a;
	struct bltidx *B = (struct bltidx *) b;

	return strcmp (A->area, B->area);
}


void
listambiguous (char *fname)
{
	struct fnamec key;
	struct bltidx *blt = NULL, *tmp = NULL, x;
	int     num = 0, i;

	strcpy (key.fname, fname);
	strcpy (key.area, "");

	d_keyfind (FNAMEC, &key);
	if (db_status != S_OKAY)
		d_keynext (FNAMEC);

	do {
		d_recread (&x);
		if (!sameas (fname, x.fname))
			continue;
		if (getclubax (&thisuseracc, x.area) < CAX_READ)
			continue;
		num++;
		tmp = alcmem (num * sizeof (struct bltidx));
		memcpy (tmp, blt, (num - 1) * sizeof (struct bltidx));
		if (blt)
			free (blt);
		blt = tmp;
		memcpy (&blt[num - 1], &x, sizeof (struct bltidx));
		d_keynext (FNAMEC);
	} while (db_status == S_OKAY && sameas (fname, tmp->fname));

	qsort (blt, num, sizeof (struct bltidx), bltcmp);

	prompt (AMBLSHD);
	for (i = 0; i < num; i++) {
		tmp = &blt[i];
		prompt (AMBLST, tmp->num, tmp->area, tmp->descr);
	}
	free (blt);
	prompt (AMBEND);
}


/* End of File */
