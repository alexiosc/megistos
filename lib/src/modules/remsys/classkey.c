/*****************************************************************************\
 **                                                                         **
 **  FILE:     classkey.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 94                                                   **
 **  PURPOSE:  Class and key oriented functions for the remote sysop menu   **
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
 * Revision 1.5  2003/12/24 21:53:06  alexios
 * Fixed #includes.
 *
 * Revision 1.4  2003/12/24 20:12:09  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.5  1998/12/27 16:07:28  alexios
 * Added autoconf support.
 *
 * Revision 0.4  1998/07/24 10:23:31  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.3  1997/11/06 20:05:18  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/11/05 11:10:55  alexios
 * Changed calls to audit() to take into account the new
 * auditing scheme.
 *
 * Revision 0.1  1997/08/28 11:04:28  alexios
 * First registered revision. Adequate.
 *
 *
 */


static const char rcsinfo[] =
    "$Id$";



#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_UNISTD_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>

#include "remsys.h"
#include "mbk_remsys.h"


void
listclasses ()
{
	int     i;

	prompt (CLSLSTHDR, NULL);
	for (i = 0; i < cls_count; i++)
		prompt (CLSLSTTAB, cls_classes[i].name);
	prompt (CLSLSTEND, NULL);
}



int
getclassname (class, msg, existing, err, def, defval)
char   *class, *defval;
int     msg, existing, err, def;
{
	char    newclass[10];
	int     i, ok = 0;

	while (!ok) {
		memset (newclass, 0, 10);
		if (cnc_more ())
			strncpy (newclass, cnc_word (), 10);
		else {
			prompt (msg, NULL);
			if (def) {
				sprintf (out_buffer, msg_get (def), defval);
				print (out_buffer, NULL);
			}
			inp_get (0);
			if (margc)
				strncpy (newclass, margv[0], 10);
			else if (def && !inp_reprompt ()) {
				strncpy (class, defval, 10);
				return 1;
			} else
				cnc_end ();
		}
		if (sameas (newclass, "x"))
			return 0;
		if (newclass[0] == '?') {
			newclass[0] = 0;
			listclasses ();
			continue;
		}
		if (!newclass[0]) {
			cnc_end ();
			continue;
		}
		ok = (existing == 0);
		for (i = 0; newclass[i]; i++)
			newclass[i] = toupper (newclass[i]);
		for (i = 0; i < cls_count; i++) {
			if (sameas (newclass, cls_classes[i].name)) {
				if (existing)
					ok = 1;
				else {
					cnc_end ();
					sprintf (out_buffer, msg_get (err),
						 newclass);
					print (out_buffer);
					ok = 0;
					break;
				}
			}
		}
		if (existing && !ok) {
			sprintf (out_buffer, msg_get (err), newclass);
			print (out_buffer);
			cnc_end ();
		}
	}
	strncpy (class, newclass, 10);
	return 1;
}


int
keyed (long *k)
{
	long    keys[KEYLENGTH];
	int     shown = 0;
	int     key;
	char    c;

	memcpy (keys, k, KEYLENGTH * sizeof (long));
	for (;;) {
		if (!shown) {
			char    s1[65] = { 0 }, s2[65] = {
			0};
			int     i;

			for (i = 0; i < 64; i++) {
				s1[i] =
				    (keys[i / 32] & (1 << (i % 32))) ? 'X' :
				    '-';
				s2[i] =
				    (keys[(i + 64) / 32] &
				     (1 << ((i + 64) % 32))) ? 'X' : '-';
			}
			prompt (RSKEYSTAB, s1, s2, NULL);
			shown = 1;
		}

		key = -1;
		for (;;) {
			if ((c = cnc_more ()) != 0) {
				if (toupper (c) == 'X')
					return 0;
				key = cnc_int ();
			} else {
				prompt (RSKEYSASK, NULL);
				inp_get (0);
				key = atoi (margv[0]);
				if (!margc || inp_reprompt ()) {
					cnc_end ();
					continue;
				} else if (inp_isX (margv[0]))
					return 0;
				else if (sameas (margv[0], "OK")) {
					memcpy (k, keys,
						KEYLENGTH * sizeof (long));
					return 1;
				} else if (sameas (margv[0], "ON")) {
					int     i;

					for (i = 0; i < KEYLENGTH; i++)
						keys[i] = -1L;
					shown = 0;
					key = -1;
					break;
				} else if (sameas (margv[0], "OFF")) {
					int     i;

					for (i = 0; i < KEYLENGTH; i++)
						keys[i] = 0L;
					shown = 0;
					key = -1;
					break;
				} else if (sameas (margv[0], "?")) {
					key = -1;
					shown = 0;
					break;
				}
			}
			if (key < 1 || key > 128) {
				cnc_end ();
				prompt (NUMERR, 1, 128, NULL);
			} else
				break;
		}

		if (key >= 1 && key <= 128) {
			key--;
			keys[key / 32] ^= (1 << (key % 32));
			prompt (RSKEYSON +
				((keys[key / 32] & (1 << (key % 32))) == 0),
				key + 1, NULL);
		}
	}
}


void
rsys_classed ()
{
	char    command[256];

	sprintf (command, "%s/%s", mkfname (BINDIR), "classed");
	runmodule (command);
}


void
rsys_class ()
{
	int     getclassname ();
	char    userid[24], class[10];
	useracc_t usracc, *uacc = &usracc;

	if (!get_userid (userid, RSCLASSWHO, UNKUID, 0, NULL, 0))
		return;

	if (!usr_insys (userid, 0))
		usr_loadaccount (userid, uacc);
	else
		uacc = &othruseracc;

	if (!cnc_more ())
		prompt (RSCLASSREP, uacc->userid, uacc->curclss);

	if (!getclassname (class, RSCLASSCLS, 1, RSCLASSERR, 0, ""))
		return;

	if (!usr_exists (userid)) {
		prompt (RSCLASSDEL, NULL);
		return;
	} else if (!usr_insys (userid, 0)) {
		useracc_t temp;
		char    oldclass[32];

		usr_loadaccount (userid, &temp);

		strcpy (oldclass, temp.curclss);
		strncpy (temp.curclss, class, sizeof (temp.curclss));
		strncpy (temp.tempclss, temp.curclss, sizeof (temp.tempclss));
		temp.classdays = 0;
		audit (getenv ("CHANNEL"), AUDIT (NEWCLSS), temp.userid,
		       oldclass, temp.curclss);

		usr_saveaccount (&temp);
	} else {
		char    oldclass[32];

		strcpy (oldclass, uacc->curclss);
		strncpy (uacc->curclss, class, sizeof (uacc->tempclss));
		strncpy (uacc->tempclss, uacc->curclss,
			 sizeof (uacc->tempclss));
		uacc->classdays = 0;

		audit (getenv ("CHANNEL"), AUDIT (NEWCLSS), uacc->userid,
		       oldclass, uacc->curclss);

		sprompt_other (othrshm, out_buffer, RSCLASSNOT, uacc->curclss);
		if (usr_injoth (&othruseronl, out_buffer, 0))
			prompt (NOTIFIED, uacc->userid);
	}
	prompt (RSCLASSOK, NULL);
}


void
rsys_keys ()
{
	int     keyed ();
	char    userid[24];
	useracc_t usracc, *uacc = &usracc;
	long    keys[KEYLENGTH];

	if (!get_userid (userid, RSKEYSWHO, UNKUID, 0, NULL, 0))
		return;
	if (sameas (userid, SYSOP)) {
		prompt (RSKEYSSYS, NULL);
		return;
	}

	if (!usr_insys (userid, 0))
		usr_loadaccount (userid, uacc);
	else
		uacc = &othruseracc;

	memcpy (keys, uacc->keys, sizeof (keys));
	if (!keyed (keys))
		return;

	if (!usr_exists (userid)) {
		prompt (RSKEYSDEL, NULL);
		return;
	} else if (!usr_insys (userid, 0)) {
		useracc_t temp;

		usr_loadaccount (userid, &temp);
		memcpy (temp.keys, keys, sizeof (temp.keys));
		usr_saveaccount (&temp);
	} else {
		memcpy (uacc->keys, keys, sizeof (uacc->keys));
	}
	prompt (RSKEYSOK, NULL);
}





/* End of File */
