/*****************************************************************************\
 **                                                                         **
 **  FILE:     misc.c                                                       **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 1996, Version 0.5                               **
 **  PURPOSE:  Miscellaneous functions                                      **
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
 * Revision 0.3  1998/12/27 15:27:54  alexios
 * Added autoconf support.
 *
 * Revision 0.2  1998/07/24 10:14:42  alexios
 * Migrated to bbslib 0.6.
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


int
getclub (char *club, int pr, int err, int def, char *defval)
{
	char   *i;
	char    c;

	for (;;) {
		fmt_lastresult = 0;
		if ((c = cnc_more ()) != 0) {
			if (sameas (cnc_nxtcmd, "X"))
				return 0;
			if (sameas (cnc_nxtcmd, "?")) {
				listclubs ();
				cnc_end ();
				continue;
			}
			i = cnc_word ();
		} else {
			if (pr)
				prompt (pr);
			if (def)
				prompt (def, defval);
			inp_get (0);
			cnc_begin ();
			i = cnc_word ();
			if (!margc || (margc == 1 && sameas (margv[0], "."))) {
				if (defval && defval[0])
					strcpy (i, defval);
				else {
					cnc_end ();
					continue;
				}
				break;
			} else if (inp_isX (margv[0]))
				return 0;
			if (sameas (margv[0], "?")) {
				listclubs ();
				cnc_end ();
				continue;
			}
		}

		if (*i == '/')
			i++;

		if (!i[0] || sameas (i, ".")) {
			if (defval && defval[0])
				strcpy (i, defval);
			else {
				cnc_end ();
				continue;
			}
			break;
		} else if (!findclub (i)) {
			if (err)
				prompt (err, i);
			cnc_end ();
			continue;
		} else
			break;
	}

	strcpy (club, i);
	return 1;
}


int
getaccess (char *club)
{
	int     ax;

	if (key_owns (&thisuseracc, sopkey))
		return FLA_PRIVILEGED;
	if (!club[0])
		return FLA_NONE;

	ax = getclubax (&thisuseracc, club);
	if (ax < CAX_COOP)
		return FLA_NONE;
	else if (ax == CAX_COOP)
		return FLA_COOP;
	else if (ax > CAX_COOP)
		return FLA_CLUBOP;
	return FLA_NONE;
}


int
getdescr (char *s, int pr)
{
	char   *i;

	cnc_end ();
	for (;;) {
		if (cnc_more ()) {
			i = cnc_nxtcmd;
			inp_raw ();
		} else {
			if (pr)
				prompt (pr, s);
			inp_get (DESCR_LEN - 1);
			cnc_begin ();
			if (!margc)
				continue;
			i = inp_buffer;
			inp_raw ();
		}

		if (!i[0])
			continue;
		else if (inp_isX (i))
			return 0;
		else {
			strcpy (s, i);
			while (s[strlen (s) - 1] == 32)
				s[strlen (s) - 1] = 0;
			return 1;
		}
	}
}


void
bltinfo (struct bltidx *blt)
{
	prompt (BLTINFO,
		blt->num,
		blt->fname,
		blt->descr,
		blt->area,
		blt->author,
		blt->timesread, msg_getunit (TIMESSNG, blt->timesread));
}


/* End of File */
