/*****************************************************************************\
 **                                                                         **
 **  FILE:     miscfuncs.c                                                  **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 94                                                   **
 **  PURPOSE:  Miscellaneous functions for the remote sysop menu            **
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
 * Revision 2.0  2004/09/13 19:44:52  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.6  2004/05/03 05:38:39  alexios
 * Fixed the generation of full path names based on TTYINFOFILE, which
 * contains a format specifier.
 *
 * Revision 1.5  2003/12/24 21:53:06  alexios
 * Fixed #includes.
 *
 * Revision 1.4  2003/12/24 20:12:09  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.7  1999/07/18 21:48:04  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 0.6  1998/12/27 16:07:28  alexios
 * Added autoconf support.
 *
 * Revision 0.5  1998/08/11 10:19:45  alexios
 * Migrated file transfer calls to the new format.
 *
 * Revision 0.4  1998/07/24 10:23:31  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.3  1997/11/06 20:05:18  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/11/06 16:59:23  alexios
 * Made the AUDIT command take into account the new format of
 * the audit trail. The command now colour-codes entries acc-
 * ording to their severity. Implemented the PAGEAUDIT command
 * to configure filters for global auditing. Wrote a function
 * filter_audit() to look for specific keywords and/or flags
 * in the audit trail. Added a command FILTAUD to work as an
 * interface to filter_audit(). Commands SECURITY and SIGNUPS
 * work as macros to filter_audit(), looking for certain things.
 *
 * Revision 0.1  1997/08/28 11:05:52  alexios
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
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>
#include <megistos/bbs.h>

#include "remsys.h"
#include <mbk/mbk_sysvar.h>

#undef CRDSING
#undef CRDPLUR

#include "mbk_remsys.h"


void
rsys_event ()
{
	char    command[256];

	sprintf (command, "%s/%s", mkfname (BINDIR), "eventman");
	runmodule (command);
}


static void
download ()
{
	char    c, spec[256];

	for (;;) {
		if ((c = cnc_more ()) != 0) {
			if (sameas (cnc_nxtcmd, "X"))
				return;
		} else {
			prompt (RSXFERWHD);
			inp_get (0);
			cnc_nxtcmd = inp_buffer;
			if (!margc) {
				cnc_end ();
				continue;
			}
			if (inp_isX (margv[0])) {
				return;
			}
		}
		xfer_kill_list ();
		strcpy (spec, cnc_word ());
		if (xfer_addwild (FXM_DOWNLOAD, spec, sxfdesc, 0, -1)) {
			xfer_run ();
			xfer_kill_list ();
			break;
		} else {
			prompt (RSXFERERR, cnc_nxtcmd);
			cnc_end ();
			continue;
		}
	}
}


static void
upload ()
{
	char    fname[256], command[256], *cp;
	FILE   *fp;
	int     count = -1;

	xfer_add (FXM_UPLOAD, "NAMELESS", sxfdesc, 0, 0);
	xfer_run ();

	sprintf (fname, XFERLIST, getpid ());

	if ((fp = fopen (fname, "r")) == NULL) {
		prompt (RSXFERER3);
		goto kill;
	}

	while (!feof (fp)) {
		char    line[1024];

		if (fgets (line, sizeof (line), fp))
			if (!++count)
				strcpy (fname, line);
	}
	if ((cp = strchr (fname, '\n')) != NULL)
		*cp = 0;
	fclose (fp);

	if (!count)
		goto kill;

	for (;;) {
		struct stat st;

		prompt (RSXFERWHU, count);
		inp_get (0);
		cnc_nxtcmd = inp_buffer;
		if (!margc) {
			cnc_end ();
			continue;
		}
		if (inp_isX (margv[0])) {
			goto kill;
		}
		if (stat (inp_buffer, &st))
			prompt (RSXFERERR, inp_buffer);
		else if (!(st.st_mode & S_IFDIR))
			prompt (RSXFERER2, inp_buffer);
		else
			break;
	}

	sprintf (command, "mv %s/* %s", fname, inp_buffer);
	system (command);

      kill:
	if (count >= 0) {
		sprintf (command, "rm -rf %s", fname);
		system (command);
	}
	xfer_kill_list ();
}


void
rsys_transfer ()
{
	char    opt;

	if (!get_menu (&opt, 1, RSXFERDIR, RSXFERSHRT, RSXFERRSEL, "UD", 0, 0))
		return;

	if (opt == 'D')
		download ();
	else
		upload ();
}


void
rsys_invis ()
{
	thisuseronl.flags ^= OLF_INVISIBLE;
	msg_set (msg_sys);
	prompt ((thisuseronl.flags & OLF_INVISIBLE) ? INVON : INVOFF);
	msg_reset ();
}


void
rsys_gdet ()
{
	prompt (RSGDET);
}


void
rsys_sysop ()
{
	void    showmenu ();
	char    userid[24];
	char   *word;
	int     shownmenu = 1;
	useracc_t uacc;

	if (!sameas (thisuseracc.userid, SYSOP)) {
		prompt (RSSYSOPNSY, NULL);
		return;
	}
	if (!get_userid (userid, RSSYSOPWHO, UNKUID, 0, NULL, 0))
		return;
	if (sameas (userid, SYSOP)) {
		prompt (RSSYSOPSOP, NULL);
		return;
	}

	if (!usr_insys (userid, 0))
		usr_loadaccount (userid, &uacc);
	else
		memcpy (uacc.sysaxs, othruseracc.sysaxs, sizeof (uacc.sysaxs));

	cnc_end ();
	for (;;) {
		if (!shownmenu) {
			prompt (RSSYSOPHDR, userid);
			showmenu (uacc.sysaxs, 1);
			shownmenu = 1;
		}
		if (cnc_more ()) {
			word = cnc_word ();
		} else {
			prompt (RSSYSOPMNU, NULL);
			inp_get (0);
			word = inp_buffer;
		}

		if (!margc || inp_reprompt ()) {
			cnc_end ();
			continue;
		} else if (inp_isX (word)) {
			break;
		} else if (sameas (word, "?")) {
			cnc_end ();
			shownmenu = 0;
		} else if (sameas (word, "on")) {
			int     i;

			for (i = 0; i < 4; i++)
				uacc.sysaxs[i] = -1L;
			shownmenu = 0;
		} else if (sameas (word, "off")) {
			int     i;

			for (i = 0; i < 4; i++)
				uacc.sysaxs[i] = 0L;
			shownmenu = 0;
		} else {
			int     i, found = 0, matches = 0;

			for (i = 0; i < COMMANDS; i++) {
				if (sameto (word, commands[i].command)) {
					found = i;
					matches++;
					break;
				}
			}
			if (!matches) {
				prompt (ERRCOM);
			} else if (matches > 1) {
				prompt (MORCHR, word);
				cnc_end ();
			} else {
				int     j = commands[found].accessflag;

				uacc.sysaxs[j / 32] ^= (1 << (j % 32));
				prompt (HASAXS (uacc.sysaxs, j) ? RSSYSOPON :
					RSSYSOPOFF, commands[i].command);
			}
		}
	}

	if (!usr_exists (userid)) {
		prompt (RSSYSOPDEL, NULL);
		return;
	} else if (!usr_insys (userid, 0)) {
		useracc_t temp;

		usr_loadaccount (userid, &temp);
		memcpy (temp.sysaxs, uacc.sysaxs, sizeof (temp.sysaxs));
		usr_saveaccount (&temp);
	} else {
		memcpy (othruseracc.sysaxs, uacc.sysaxs,
			sizeof (othruseracc.sysaxs));
		if (usr_injoth
		    (&othruseronl,
		     sprompt_other (othrshm, out_buffer, RSSYSOPNOT), 0))
			prompt (NOTIFIED, othruseracc.userid);
	}
	prompt (RSSYSOPUPD, NULL);
}


void
showlog (char *fname, int p1, int p2, int p3, int err)
{
	char    opt;
	char    command[256];
	FILE   *fp;

	if (!get_menu (&opt, 1, p1, 0, err, "BE", 0, 0))
		return;
	if (opt == 'B')
		sprintf (command, "cat %s", fname);
	else
		sprintf (command, "tac %s", fname);

	if ((fp = popen (command, "r")) == NULL)
		return;

	inp_nonblock ();

	prompt (p2);
	while (!feof (fp)) {
		char    line[1024], *cp, s1[80], *s2, c;
		int     flags, sev;

		if (read (0, &c, 1))
			if (c == 13 || c == 10 || c == 27 || c == 15 || c == 3) {
				prompt (p3);
				break;
			}
		if (fmt_lastresult == PAUSE_QUIT) {
			prompt (p3);
			break;
		}

		if (!fgets (line, sizeof (line), fp))
			break;
		if ((cp = strchr (line, '\n')) != NULL)
			*cp = 0;
		if (sscanf (&line[20], "%04x", &flags) != 1)
			continue;

		if (flags & AUF_EMERGENCY)
			sev = 2;
		else if (flags & AUF_CAUTION)
			sev = 1;
		else
			sev = 0;

		strncpy (s1, line, 68);
		s1[68] = 0;
		s2 = &line[68];
		prompt (RSAUDITI + sev, s1, s2);
	}
	inp_block ();
	fclose (fp);
	return;
}


void
rsys_audit ()
{
	showlog (mkfname (AUDITFILE), RSAUDIT1, RSAUDIT2, RSAUDIT3, RSAUDITR);
}


void
rsys_cleanup ()
{
	showlog (mkfname (CLNUPAUDITFILE), RSCLEANUP1, RSCLEANUP2, RSCLEANUP3,
		 RSCLEANUPR);
}


void
rsys_logon ()
{
	char   *i, c, dev[32], fname[256];
	int     channel;
	struct stat st;

	if (!cnc_more ())
		prompt (RSLOGONH);
	for (;;) {
		fmt_lastresult = 0;
		if ((c = cnc_more ()) != 0) {
			if (sameas (cnc_nxtcmd, "X"))
				return;
			i = cnc_word ();
		} else {
			prompt (RSLOGONP);
			inp_get (0);
			cnc_begin ();
			i = cnc_word ();
			if (!margc) {
				cnc_end ();
				continue;
			}
			if (inp_isX (margv[0])) {
				return;
			}
		}
		if ((sameas (i, "*") || sameas (i, "all"))) {
			strcpy (dev, "*");
			break;
		} else if (sameas (i, "?")) {
			int     i;

			prompt (RSLOGONL1);
			if (!stat (mkfname (LOGINMSGFILE), &st))
				prompt (RSLOGONL2A, st.st_size);
			for (i = 0; i < chan_count; i++) {
			        char tmp[512];
				sprintf (tmp, TTYINFOFILE, 
					 channels[i].ttyname);
				strcpy (fname, mkfname (tmp));
				if (!stat (fname, &st))
					prompt (RSLOGONL2B,
						channels[i].channel,
						st.st_size);
			}
			prompt (RSLOGONL3);
			cnc_end ();
			continue;
		} else if (strstr (i, "tty") == i) {
			if (chan_getnum (i) != -1) {
				strcpy (dev, i);
				break;
			} else {
				prompt (GCHANBDV, NULL);
				cnc_end ();
				continue;
			}
		} else if (sscanf (i, "%x", &channel) == 1) {
			char   *name = chan_getname (channel);

			if (!name) {
				prompt (GCHANBCH, NULL);
				cnc_end ();
				continue;
			} else {
				strcpy (dev, name);
				break;
			}
		} else {
			prompt (GCHANHUH, i);
			cnc_end ();
			continue;
		}
	}

	if (sameas (dev, "*"))
		strcpy (fname, mkfname (LOGINMSGFILE));
	else {
		char tmp [512];
		sprintf (tmp, mkfname (TTYINFOFILE), dev);
		strcpy (fname, mkfname (tmp));
	}

	if (!stat (fname, &st)) {
		char    opt;

		if (!get_menu (&opt, 1, 0, RSLOGOND, RSLOGONDR, "ED", 0, 'E'))
			return;
		if (opt == 'D') {
			unlink (fname);
			prompt (RSLOGONDD);
		} else if (opt == 'E') {
			char    temp[256];
			struct stat st;

			sprintf (temp, TMPDIR "/remsys%05d", getpid ());
			symlink (fname, temp);

			if (editor (temp, 2048) || stat (temp, &st)) {
				unlink (temp);
				return;
			}
			unlink (temp);
		}
	} else
		editor (fname, 2048);
}


void
rsys_pageaudit ()
{
	int     filtering = thisuseracc.auditfiltering, i;

	i = GETSEVERITY (thisuseracc.auditfiltering);

	if (filtering & AUF_INFO)
		i = SEVI;
	else if (filtering & AUF_CAUTION)
		i = SEVC;
	else if (filtering & AUF_EMERGENCY)
		i = SEVE;
	else
		i = SEVO;

	sprintf (inp_buffer, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\nOK\nCANCEL\n",
		 msg_get (i),
		 (filtering & AUF_ACCOUNTING) ? "on" : "off",
		 (filtering & AUF_EVENT) ? "on" : "off",
		 (filtering & AUF_OPERATION) ? "on" : "off",
		 (filtering & AUF_SECURITY) ? "on" : "off",
		 (filtering & AUF_TRANSFER) ? "on" : "off",
		 (filtering & AUF_USERLOG) ? "on" : "off",
		 (filtering & AUF_OTHER) ? "on" : "off");

	if (dialog_run ("remsys", RSAPGVT, RSAPGLT, inp_buffer, MAXINPLEN) !=
	    0) {
		error_log ("Unable to run data entry subsystem.");
	}

	dialog_parse (inp_buffer);

	filtering = -1;
	for (i = 0; i < 11; i++) {
		char   *s = margv[i];

		if (i == 0) {
			filtering &= ~AUF_SEVERITY;
			if (!strcmp (s, msg_get (SEVE)))
				filtering |= AUF_EMERGENCY;
			else if (!strcmp (s, msg_get (SEVC)))
				filtering |= AUF_EMERGENCY | AUF_CAUTION;
			else if (!strcmp (s, msg_get (SEVI)))
				filtering |= AUF_SEVERITY;
		} else if (i == 1 && sameas (s, "OFF"))
			filtering &= ~AUF_ACCOUNTING;
		else if (i == 2 && sameas (s, "OFF"))
			filtering &= ~AUF_EVENT;
		else if (i == 3 && sameas (s, "OFF"))
			filtering &= ~AUF_OPERATION;
		else if (i == 4 && sameas (s, "OFF"))
			filtering &= ~AUF_SECURITY;
		else if (i == 5 && sameas (s, "OFF"))
			filtering &= ~AUF_TRANSFER;
		else if (i == 6 && sameas (s, "OFF"))
			filtering &= ~AUF_USERLOG;
		else if (i == 7 && sameas (s, "OFF"))
			filtering &= ~AUF_OTHER;
	}

	if (sameas (margv[10], "CANCEL") || sameas (margv[9], margv[10])) {
		prompt (RSAPGCAN);
		return;
	}
	prompt (RSAPGOK);
	thisuseracc.auditfiltering = filtering;
}


void
filter_audit (char *keyword, int filtering, int reverse)
{
	FILE   *fp;
	char    lookfor[256];
	int     found = 0;

	lookfor[0] = 0;
	if (keyword)
		strcpy (lookfor, keyword);
	phonetic (lookfor);

	/* Open the file, in reverse if required */

	if (!reverse) {
		if ((fp = fopen (mkfname (AUDITFILE), "r")) == NULL) {
			error_logsys ("Unable to open Audit Trail!");
			return;
		}
	} else {
		char    cmd[2048];

		strcpy (cmd, "tac 2>/dev/null ");
		strcat (cmd, mkfname (AUDITFILE));
		if ((fp = popen (cmd, "r")) == NULL) {
			error_logsys
			    ("Unable to popen() Audit Trail with tac!");
			return;
		}
	}


	/* Start searching */

	inp_nonblock ();

	while (!feof (fp)) {
		char    line[1024], *cp, s1[80], *s2, c;
		int     flags, sev;

		if (read (0, &c, 1))
			if (c == 13 || c == 10 || c == 27 || c == 15 || c == 3) {
				prompt (AUDSCAN);
				goto done;
			}
		if (fmt_lastresult == PAUSE_QUIT) {
			prompt (AUDSCAN);
			goto done;
		}

		if (!fgets (line, sizeof (line), fp))
			continue;
		if ((cp = strchr (line, '\n')) != NULL)
			*cp = 0;

		if (sscanf (&line[20], "%04x", &flags) != 1)
			continue;
		if (((flags & filtering) & AUF_SEVERITY) == 0 ||
		    ((flags & filtering) & ~AUF_SEVERITY) == 0)
			continue;

		if (lookfor[0]) {
			char    tmp[1024];

			strcpy (tmp, line);
			phonetic (tmp);
			if (!strstr (tmp, lookfor))
				continue;
		}

		if (!found)
			prompt (AUDSRCH);
		found |= 1;
		strncpy (s1, line, 68);
		s1[68] = 0;
		s2 = &line[68];

		if (flags & AUF_EMERGENCY)
			sev = 2;
		else if (flags & AUF_CAUTION)
			sev = 1;
		else
			sev = 0;

		prompt (RSAUDITI + sev, s1, s2);
	}

	prompt (found ? AUDSEND : AUDNF);

      done:
	inp_nonblock ();
	if (!reverse)
		fclose (fp);
	else
		pclose (fp);
}


void
rsys_filtaud ()
{
	int     filtering = -1, reverse = 1, i;
	char    keyword[256];

	strcpy (inp_buffer,
		"\non\non\non\non\non\non\non\non\non\non\non\nOK\nCANCEL\n");

	if (dialog_run ("remsys", RSFLTVT, RSFLTLT, inp_buffer, MAXINPLEN) !=
	    0) {
		error_log ("Unable to run data entry subsystem");
		return;
	}

	dialog_parse (inp_buffer);

	for (i = 0; i < 15; i++) {
		char   *s = margv[i];

		if (i == 0)
			strcpy (keyword, s);
		else if (i == 1 && sameas (s, "OFF"))
			filtering &= ~AUF_INFO;
		else if (i == 2 && sameas (s, "OFF"))
			filtering &= ~AUF_CAUTION;
		else if (i == 3 && sameas (s, "OFF"))
			filtering &= ~AUF_EMERGENCY;
		else if (i == 4 && sameas (s, "OFF"))
			filtering &= ~AUF_ACCOUNTING;
		else if (i == 5 && sameas (s, "OFF"))
			filtering &= ~AUF_EVENT;
		else if (i == 6 && sameas (s, "OFF"))
			filtering &= ~AUF_OPERATION;
		else if (i == 7 && sameas (s, "OFF"))
			filtering &= ~AUF_SECURITY;
		else if (i == 8 && sameas (s, "OFF"))
			filtering &= ~AUF_TRANSFER;
		else if (i == 9 && sameas (s, "OFF"))
			filtering &= ~AUF_USERLOG;
		else if (i == 10 && sameas (s, "OFF"))
			filtering &= ~AUF_OTHER;
		else if (i == 11 && sameas (s, "OFF"))
			reverse = 0;
	}
	if (sameas (margv[14], "CANCEL") || sameas (margv[13], margv[14]))
		return;
	filter_audit (keyword, filtering, reverse);
}


void
rsys_security ()
{
	filter_audit ("", AUF_SEVERITY | AUF_SECURITY, 1);
}


void
rsys_signups ()
{
	filter_audit (AUS_SIGNUP, -1, 1);
}




/* End of File */
