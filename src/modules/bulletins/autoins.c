/*****************************************************************************\
 **                                                                         **
 **  FILE:     autoins.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1997, Version 0.5                                    **
 **  PURPOSE:  Automatically insert bulletins                               **
 **  NOTES:                                                                 **
 **                                                                         **
\*****************************************************************************/


/*
 * $Id: autoins.c,v 2.0 2004/09/13 19:44:50 alexios Exp $
 *
 * $Log: autoins.c,v $
 * Revision 2.0  2004/09/13 19:44:50  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2003/12/27 12:32:00  alexios
 * Adjusted #includes. Changed struct message to message_t.
 *
 * Revision 1.4  2003/12/24 20:12:15  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.5  1999/07/18 21:19:18  alexios
 * One minor change to a scandir() call to ensure a cleaner
 * compile.
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
    "$Id: autoins.c,v 2.0 2004/09/13 19:44:50 alexios Exp $";


#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_STAT_H 1
#define WANT_DIRENT_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "mbk_bulletins.h"
#include "bltidx.h"
#include "bulletins.h"


int
attsel (const struct dirent *d)
{
	return !strcmp (&(d->d_name[strlen (d->d_name) - 4]), ".att");
}


int
numsort (const struct dirent **a, const struct dirent **b)
{
	int     A = 0, B = 0;

	sscanf ((*a)->d_name, "%d", &A);
	sscanf ((*b)->d_name, "%d", &B);
	return A - B;
}


void
autoins ()
{
	char    insclub[64], dir[256];
	int     i, j, abort = 0;
	struct dirent **files;

	prompt (AUTOINS);

	if (getaccess (club) < flaxes)
		return;

	if (!club[0]) {
		if (!getclub (insclub, AISIG, AISIGR,
			      thisuseracc.lastclub[0] ? AIDEF : 0,
			      thisuseracc.lastclub)) {
			prompt (BLTCAN);
			return;
		}
	} else
		strcpy (insclub, club);
	prompt (BGNAINS, insclub);

	strcpy (dir, mkfname (MSGSDIR "/%s/" MSGATTDIR, insclub));
	i = scandir (dir, &files, attsel, numsort);

	if (i < 0) {
		prompt (AIDIRR, insclub);
		return;
	} else if (!i) {
		prompt (NOFILES);
		return;
	}

	for (j = 0; j < i; free (files[j]), j++) {
		struct stat st;
		char    fname[256];
		message_t msg;
		int     msgno = 0;

		if (abort)
			continue;

		sprintf (fname, "%s/%s", dir, files[j]->d_name);
		if (stat (fname, &st))
			continue;

		prompt (FNDFILE,
			files[j]->d_name, st.st_size, msg_getunit (BYTESNG,
								   st.
								   st_size));

		strncpy (fname, files[j]->d_name,
			 strlen (files[j]->d_name) - 4);
		fname[strlen (files[j]->d_name) - 4] = 0;
		strcat (fname, ".blt");

		if (dbexists (insclub, fname)) {
			prompt (ALREXS);
			continue;
		}

		sscanf (fname, "%d", &msgno);
		if (!getmsgheader (insclub, msgno, &msg)) {
			prompt (MSGDEL);
			continue;
		}

		{
			struct bltidx blt;
			int     yes = 0;

			prompt (AIINFO);

			bzero (&blt, sizeof (struct bltidx));
			blt.num = dbgetlast () + 1;
			blt.date = today ();
			sprintf (blt.fname, "%d.blt", msgno);
			strcpy (blt.area, insclub);
			strncpy (blt.author, msg.from, sizeof (blt.author));
			strcpy (blt.descr, msg.subject);

			bltinfo (&blt);

			if (!get_bool
			    (&yes, ASKINS, ASKERR, DEFLTC,
			     ainsdef ? 'Y' : 'N')) {
				prompt (ABORT);
				abort = 1;
				continue;
			} else if (yes) {
				char    source[256], target[256];

				/* Link or copy the file */

				strcpy (source,
					mkfname (MSGSDIR "/%s/%s/%d.att",
						 insclub, MSGATTDIR, msgno));
				strcpy (target,
					mkfname (MSGSDIR "/%s/%s/%s", insclub,
						 MSGBLTDIR, blt.fname));

				if (link (source, target) < 0) {
					if (fcopy (source, target) < 0) {
						prompt (NBCPR);
						abort = 1;
						continue;
					}
				}

				/* Insert it into the database */

				blt.num = dbgetlast () + 1;	/* Just in case */
				if (!dbins (&blt)) {
					prompt (AIERR);
					abort = 1;
					continue;
				} else
					prompt (AIOK);


				/* Update the club header */

				loadclubhdr (club);
				clubhdr.nblts++;
				saveclubhdr (&clubhdr);


				/* Audit it */

				if (audins)
					audit (thisuseronl.channel,
					       AUDIT (BLTINS),
					       thisuseracc.userid, blt.fname,
					       blt.area);
			}
		}
	}

	free (files);
	prompt (ENDAINS);
}


/* End of File */


/* End of File */
