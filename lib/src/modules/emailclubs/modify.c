/*****************************************************************************\
 **                                                                         **
 **  FILE:     modify.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, June 1995, Version 0.5                                    **
 **  PURPOSE:  Modify email/club messages                                   **
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
 * Revision 1.4  2003/12/24 20:12:13  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.5  1999/07/18 21:21:38  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 0.4  1998/12/27 15:33:03  alexios
 * Added autoconf support.
 *
 * Revision 0.3  1998/07/24 10:17:37  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:05:26  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 10:21:30  alexios
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
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include <megistos/mbk_emailclubs.h>
#include <megistos/email.h>


static int
modifybody (struct message *msg)
{
	struct message dummy;
	FILE   *fp, *fp2;
	char    fname[1024], modfn[256];
	struct stat st;
	int     truncpos;

#ifdef USE_LIBZ
	decompress (msg);
#endif

	sprintf (fname, "%s/%s/" MESSAGEFILE, mkfname (MSGSDIR),
		 msg->club[0] ? msg->club : EMAILDIRNAME, msg->msgno);

	if ((fp = fopen (fname, "r")) == NULL) {
		fclose (fp);
#ifdef USE_LIBC
		unlink (fname);
#endif
		return 0;
	}
	sprintf (modfn, TMPDIR "/mod%05d", getpid ());

	if ((fp2 = fopen (modfn, "w")) == NULL) {
		fclose (fp);
		fclose (fp2);
#ifdef USE_LIBC
		unlink (fname);
#endif
		return 0;
	}

	if (fread (&dummy, sizeof (struct message), 1, fp) != 1) {
		fclose (fp);
		fclose (fp2);
#ifdef USE_LIBC
		unlink (fname);
#endif
		return 0;
	}

	while (!feof (fp)) {
		char    buffer[1025] = { 0 }, *cp, *ep;
		int     bytes = 0;

		bytes = fread (buffer, 1, sizeof (buffer) - 1, fp);
		if (!bytes)
			break;
		else
			buffer[bytes] = 0;

		if (msg->cryptkey)
			bbscrypt (buffer, bytes, dummy.cryptkey);

		cp = buffer;
		while (*cp) {
			if ((ep = strchr (cp, '\n')) == NULL) {
				fprintf (fp2, "%s", cp);
				break;
			} else {
				*ep = 0;
				fprintf (fp2, "%s\n", cp);
				cp = ep + 1;
			}
		}
	}

	fclose (fp);
	fclose (fp2);


	if (editor (modfn, msglen) || stat (modfn, &st)) {
		unlink (modfn);
#ifdef USE_LIBC
		unlink (fname);
#endif
		return 0;
	}


	if ((fp = fopen (fname, "r+")) == NULL) {
		fclose (fp);
#ifdef USE_LIBC
		unlink (fname);
#endif
		unlink (modfn);
		return 0;
	}
	fseek (fp, sizeof (struct message), SEEK_SET);
	if ((fp2 = fopen (modfn, "r")) == NULL) {
		fclose (fp);
		fclose (fp2);
		unlink (modfn);
#ifdef USE_LIBC
		unlink (fname);
#endif
		return 0;
	}

	while (!feof (fp2)) {
		char    buffer[1025] = { 0 };
		int     bytes = 0;

		bytes = fread (buffer, 1, sizeof (buffer) - 1, fp2);
		if (!bytes)
			break;

		if (msg->cryptkey)
			bbscrypt (buffer, bytes, dummy.cryptkey);

		fwrite (buffer, 1, bytes, fp);
	}
	truncpos = ftell (fp);
	fclose (fp);
	fclose (fp2);
	truncate (fname, truncpos);
	unlink (modfn);

	return 1;
}


void
modifymail ()
{
	int     msgno;
	int     i, j, ok = 0;
	char    fname[256];
	struct stat st;
	struct message msg;

	if (!cnc_more ())
		prompt (MMINFO);

	setclub (NULL);
	do {
		if (!get_number
		    (&msgno, MMASK, 1, sysvar->emessages, MMERR3, 0, 0))
			return;

		j = findmsgfrom (&i, thisuseracc.userid, msgno, BSD_GT);
		if ((j != BSE_FOUND) || (msgno != i))
			ok = 0;
		else
			ok = 1;

		/* Be paranoid about it, check if the mail itself exists, too. */

		if (ok) {
			strcpy (fname,
				mkfname (EMAILDIR "/" MESSAGEFILE, msgno));
			ok = (stat (fname, &st) == 0);
		}

		if (!ok)
			prompt (MMERR1, msgno);
	} while (!ok);

	getmsgheader (msgno, &msg);

	if (msg.flags & MSF_CANTMOD &&
	    (!hassysaxs (&thisuseracc, USY_MASTERKEY))) {
		prompt (MMERR2);
		return;
	}

	if (!checklocks (&msg)) {
		prompt (USING);
		return;
	}

	sprintf (inp_buffer, "%s\n%s\n%s\nEDIT\nOK\nCANCEL\n",
		 msg.subject,
		 msg.flags & MSF_FILEATT ? msg.fatt : "",
		 msg.flags & MSF_RECEIPT ? "on" : "off");

	if (dialog_run ("emailclubs", MMVT, MMLT, inp_buffer, MAXINPLEN) != 0) {
		error_log ("Unable to run data entry subsystem");
		return;
	}

	dialog_parse (inp_buffer);

	if (sameas (margv[6], "OK") ||
	    sameas (margv[6], margv[3]) || sameas (margv[6], margv[4])) {

		/* Editing message? */
		if (sameas (margv[6], margv[4])) {
			if (!modifybody (&msg)) {
				prompt (MMCAN);
				return;
			}
		}


		/* Update the message */

		getmsgheader (msgno, &msg);

		bzero (msg.subject, sizeof (msg.subject));
		strncpy (msg.subject, margv[0], sizeof (msg.subject) - 1);

		if (strlen (margv[1])) {
			if (!(msg.flags & MSF_FILEATT)) {
				if (strcmp (msg.subject, margv[1]))
					prompt (MMWARN1);
			} else {
				int     warn = 0;
				char   *s = margv[1];

				for (i = 0; s[i]; i++)
					if (!strchr (FNAMECHARS, s[i])) {
						warn = 1;
						s[i] = '_';
					}
				if (warn)
					prompt (MMWARN2, margv[1]);
			}
		} else
			sprintf (msg.fatt, "%d.att", msg.msgno);

		{
			char   *s = margv[2];
			int     current = (msg.flags & MSF_RECEIPT) != 0;
			int     rrr = sameas (s, "ON");

			if (rrr != current) {
				if (rrr) {
					if (!key_owns (&thisuseracc, rrrkey))
						prompt (MMWARN3);
					else if (!usr_canpay (rrrchg))
						prompt (MMWARN4);
					else {
						msg.flags |= MSF_RECEIPT;
						usr_chargecredits (rrrchg);
						prompt (MMINFO1, rrrchg,
							msg_getunit (CRDSING,
								     rrrchg));
					}
				}
			}
		}

		writemsgheader (&msg);

	} else {
		prompt (MMCAN);
	}
}


void
modifyclubmsg (struct message *orig)
{
	int     i;
	struct message msg;

	getmsgheader (orig->msgno, &msg);

	if (!checklocks (&msg)) {
		prompt (USING);
		return;
	}

	sprintf (inp_buffer, "%s\n%s\nEDIT\nOK\nCANCEL",
		 msg.subject, msg.flags & MSF_FILEATT ? msg.fatt : "");

	if (dialog_run ("emailclubs", MCMVT, MCMLT, inp_buffer, MAXINPLEN) !=
	    0) {
		error_log ("Unable to run data entry subsystem");
		return;
	}

	dialog_parse (inp_buffer);

	if (sameas (margv[5], "OK") ||
	    sameas (margv[5], margv[2]) || sameas (margv[5], margv[3])) {

		/* Edit the message's body? */

		if (sameas (margv[5], margv[2])) {
			if (!modifybody (&msg)) {
				prompt (MMCAN);
				return;
			}
		}

		/* OK, make the changes */

		getmsgheader (orig->msgno, &msg);

		bzero (msg.subject, sizeof (msg.subject));
		strncpy (msg.subject, margv[0], sizeof (msg.subject) - 1);
		if (strlen (margv[1])) {
			if (!(msg.flags & MSF_FILEATT)) {
				if (strcmp (msg.subject, margv[1]))
					prompt (MMWARN1);
			} else {
				int     warn = 0;
				char   *s = margv[0];

				for (i = 0; s[i]; i++)
					if (!strchr (FNAMECHARS, s[i])) {
						warn = 1;
						s[i] = '_';
					}
				if (warn)
					prompt (MMWARN2, s);
			}
		} else
			sprintf (msg.fatt, "%d.att", msg.msgno);

		writemsgheader (&msg);
	} else {
		prompt (MMCAN);
	}
}


void
clubopmodify (struct message *orig)
{
	struct message msg;

	memcpy (&msg, orig, sizeof (msg));
	getmsgheader (orig->msgno, &msg);

	if (!checklocks (&msg)) {
		prompt (USING);
		return;
	}

	sprintf (inp_buffer, "%s\n%s\n%s\n%s\n%d\nEDIT\nOK\nCANCEL\n",
		 msg.subject,
		 msg.flags & MSF_FILEATT ? msg.fatt : "",
		 msg.flags & MSF_APPROVD ? "on" : "off",
		 msg.flags & MSF_EXEMPT ? "on" : "off", msg.period);

	if (dialog_run ("emailclubs", COPMVT, COPMLT, inp_buffer, MAXINPLEN) !=
	    0) {
		error_log ("Unable to run data entry subsystem");
		return;
	}

	dialog_parse (inp_buffer);

	if (sameas (margv[8], "OK") ||
	    sameas (margv[8], margv[6]) || sameas (margv[8], margv[5])) {

		/* Edit the message? */

//    if(sameas(margv[5],margv[6])){    // patch by Valis

		if (sameas (margv[8], margv[5])) {
			if (!modifybody (&msg)) {
				prompt (MMCAN);
			}
		}

		/* Make the changes to the message header */

		getmsgheader (orig->msgno, &msg);

		bzero (msg.subject, sizeof (msg.subject));
		strncpy (msg.subject, margv[0], sizeof (msg.subject) - 1);

		if (strlen (margv[1])) {
			if (!(msg.flags & MSF_FILEATT)) {
				if (strcmp (msg.subject, margv[1]))
					prompt (MMWARN1);
			} else {
				int     warn = 0, i;
				char   *s = margv[1];

				for (i = 0; s[i]; i++)
					if (!strchr (FNAMECHARS, s[i])) {
						warn = 1;
						s[i] = '_';
					}
				if (warn)
					prompt (MMWARN2, s);
			}
		} else
			sprintf (msg.fatt, "%d.att", msg.msgno);

		{
			int     i = (msg.flags & MSF_APPROVD) != 0;
			int     j = sameas (margv[2], "on");

			if ((msg.flags & MSF_FILEATT) && (i != j)) {
				msg.flags ^= MSF_APPROVD;
				prompt (msg.
					flags & MSF_APPROVD ? COPOK1 : COPOK2);
			} else if (i != j)
				prompt (COPMW1);
		}

		{
			int     j = (msg.flags & MSF_EXEMPT) != 0;
			int     k = sameas (margv[3], "on");

			if (j != k) {
				msg.flags ^= MSF_EXEMPT;
				prompt (msg.
					flags & MSF_EXEMPT ? COPOK3 : COPOK4);
			}
		}

		{
			int     j;
			int     k = msg.period;

			if (sscanf (margv[4], "%d", &j)) {
				if (j != k) {
					msg.period = j;
					if (msg.period)
						prompt (COPOK5,
							msg.period,
							msg_getunit (DAYSNG,
								     msg.
								     period));
					else
						prompt (COPOK6);
				}
			}
		}

		writemsgheader (&msg);
	} else {
		prompt (MMCAN);
	}
}


/* End of File */
