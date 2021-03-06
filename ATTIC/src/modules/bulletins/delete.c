/*****************************************************************************\
 **                                                                         **
 **  FILE:     delete.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1997, Version 0.5                                    **
 **  PURPOSE:  Delete bulletins                                             **
 **  NOTES:                                                                 **
 **                                                                         **
\*****************************************************************************/


/*
 * $Id: delete.c,v 2.0 2004/09/13 19:44:50 alexios Exp $
 *
 * $Log: delete.c,v $
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
    "$Id: delete.c,v 2.0 2004/09/13 19:44:50 alexios Exp $";



#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_DIRENT_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "mbk_bulletins.h"
#include "bltidx.h"
#include "bulletins.h"


static struct bltidx *tmpblt;


static int
lockselect (const struct dirent *d)
{
	char    tmp[256];

	if (strncmp (d->d_name, BLTREADLOCK, strlen (BLTREADLOCK)))
		return 0;
	sprintf (tmp, "%s-%s", tmpblt->area, tmpblt->fname);
	if (strcmp (tmp, &(d->d_name[strlen (d->d_name) - strlen (tmp)])))
		return 0;
	return 1;
}


int
checklocks (struct bltidx *blt)
{
	int     i, j;
	struct dirent **d = NULL;

	tmpblt = blt;
	i = scandir (mkfname (LOCKDIR), &d, lockselect, alphasort);
	for (j = 0; j < i; j++)
		free (d[j]);
	free (d);
	return i;
}


void
bltdel ()
{
	char    fname[256];
	struct bltidx blt;
	int     yes = 0, x = 0;

	if (!(club[0] ? dblistfind (club, 1) : dblistfirst ())) {
		if (!club[0])
			prompt (BLTNOBT);
		else
			prompt (CLBNOBT, club);
		return;
	}

	if (!getblt (DELBLT, &blt))
		return;

	if (getaccess (blt.area) < flaxes) {
		prompt (DELNOAX, blt.area);
		return;
	}

	/* Ask for confirmation */

	bltinfo (&blt);

	x = get_bool (&yes, ASKDEL, ASKDELR, 0, 0);
	if (x == 0 || yes == 0) {
		prompt (ABODEL, blt.num);
		return;
	}

	/* Anyone reading this article? */

	if (checklocks (&blt)) {
		prompt (CONFLICT);
		return;
	}

	/* Delete it from the database */

	if (!dbdelete ()) {
		prompt (DBERR);
		return;
	}

	/* Delete the file */

	strcpy (fname,
		mkfname (MSGSDIR "/%s/%s/%s", blt.area, MSGBLTDIR, blt.fname));
	if (unlink (fname)) {
		prompt (DBERR);
		return;
	}

	prompt (DBDELOK);

	/* Audit it */

	if (auddel)
		audit (thisuseronl.channel, AUDIT (BLTDEL),
		       thisuseracc.userid, blt.fname, blt.area);
}


/* End of File */
