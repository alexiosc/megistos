/*****************************************************************************\
 **                                                                         **
 **  FILE:     edit.c                                                       **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1997, Version 0.5                                    **
 **  PURPOSE:  Edit bulletin entries                                        **
 **  NOTES:                                                                 **
 **                                                                         **
\*****************************************************************************/


/*
 * $Id$
 *
 * $Log$
 * Revision 1.5  2003/12/27 12:29:40  alexios
 * Adjusted #includes.
 *
 * Revision 1.4  2003/12/24 20:12:15  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.5  1999/07/18 21:19:18  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
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
    "$Id$";


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


void
bltedt ()
{
	struct bltidx blt;
	int     i;
	char    lock[256];

	/* Get the bulletin */

	if (!getblt (EDTBLT, &blt))
		return;
	if (getaccess (blt.area) < flaxes) {
		prompt (EDTNOAX, blt.area);
		return;
	}

	sprintf (lock, "%s-%s-%s-%s", BLTREADLOCK, thisuseracc.userid,
		 blt.area, blt.fname);
	lock_place (lock, "editing");

	sprintf (inp_buffer, "%s\n%s\nOK\nCancel\n", blt.author, blt.descr);

	if (dialog_run ("bulletins", EBLTVT, EBLTLT, inp_buffer, MAXINPLEN) !=
	    0) {
		error_fatal ("Unable to run data entry subsystem");
	}

	dialog_parse (inp_buffer);

	if (sameas (margv[2], "OK") || sameas (margv[2], margv[4])) {
		for (i = 0; i < 5; i++) {
			char   *s = margv[i];

			if (i == 0)
				strcpy (blt.author, s);
			else if (i == 1)
				strcpy (blt.descr, s);
		}

		if (!usr_uidxref (blt.author, 0)) {
			if (margc && inp_isX (margv[0])) {
				prompt (ABORT);
				lock_rm (lock);
				return;
			}
			cnc_end ();
			prompt (EDTAUTHR, blt.author);
			if (!get_userid
			    (blt.author, EDTAUTH, EDTAUTHR, 0, NULL, 0)) {
				prompt (ABORT);
				lock_rm (lock);
				return;
			}
		}

		if (!dbupdate (&blt)) {
			prompt (EDITERR);
			lock_rm (lock);
			return;
		}

		lock_rm (lock);
		prompt (EDITOK);
		bltinfo (&blt);

		/* Audit it */

		if (audedt)
			audit (thisuseronl.channel, AUDIT (BLTEDT),
			       thisuseracc.userid, blt.fname, blt.area);
	} else {
		prompt (ABORT);
		lock_rm (lock);
	}
}


/* End of File */
