/*****************************************************************************\
 **                                                                         **
 **  FILE:     upload.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, November 94, Version 0.5 alpha                            **
 **  PURPOSE:  Upload files                                                 **
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
 * Revision 2.0  2004/09/13 19:44:54  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.6  2004/05/17 12:39:34  alexios
 * Worked around segmentation fault when re-initialising output subsystem
 * after a file transfer.
 *
 * Revision 1.5  2003/12/24 18:38:43  alexios
 * Fixed #includes.
 *
 * Revision 1.4  2003/12/23 23:20:23  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:08  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.8  1998/12/27 16:35:21  alexios
 * Added autoconf support.
 *
 * Revision 0.7  1998/11/30 22:06:09  alexios
 * Temporarily disables character translation for viewers and
 * protocols with the PRF_BINARY (bin yes) option set. This
 * fixes a serious design bug that mangled up binary protocol
 * file transfers when people were using character translation.
 *
 * Revision 0.6  1998/07/26 21:50:23  alexios
 * Added support for per-file ok/fail shell commands.
 *
 * Revision 0.5  1998/07/24 10:31:31  alexios
 * Moved to stable status. Migrated to bbslib 0.6.
 *
 * Revision 0.4  1997/12/02 20:47:45  alexios
 * Switched to using the archiver file instead of the viewer
 * file.
 *
 * Revision 0.3  1997/11/06 20:18:32  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/11/06 17:06:53  alexios
 * Switched to the new auditing scheme().
 *
 * Revision 0.1  1997/08/28 11:25:42  alexios
 * First registered revision. Adequate.
 *
 *
 */


static const char rcsinfo[] =
    "$Id$";




#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_CTYPE_H 1
#define WANT_UNISTD_H 1
#define WANT_TIME_H 1
#define WANT_STRING_H 1
#define WANT_DIRENT_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "updown.h"
#include "mbk_updown.h"


static void
showmenu ()
{
	int     i, pos = 0;

	prompt (UPLHDR);

	for (i = 0; i < numprotocols; i++) {
		if ((protocols[i].flags & PRF_UPLOAD) &&
		    (NUMFILES == 1 || protocols[i].flags & PRF_BATCH)) {
			char    flush[80];
			int     j = (i / 2) % 2 + 1;

			sprintf (flush, "%33s", protocols[i].name);
			while (flush[j] == 32 && flush[j + 1] == 32) {
				flush[j] = '.';
				j += 2;
			}
			prompt (PROTLIN1 + pos, protocols[i].select, flush);
			pos = (pos + 1) % 2;
		}
	}
	if (pos)
		prompt (PROTLIN2, "", "");
	prompt (UPLFTR);
}


int
dolink ()
{
	char   *s, c;
	struct stat st;

	for (;;) {
		if ((c = cnc_more ()) != 0) {
			if (sameas (cnc_nxtcmd, "X"))
				return 0;
			s = cnc_word ();
		} else {
			prompt (LNKASK);
			inp_get (0);
			s = margv[0];
			if (!margc) {
				cnc_end ();
				continue;
			}
			if (inp_isX (margv[0])) {
				return 1;
			}
		}

		if (stat (s, &st)) {
			cnc_end ();
			prompt (LNKERR, s);
		} else {
			char    s1[256], fname[256];

			getcwd (s1, 256);
			sprintf (fname, "%s/%08lx", s1, time (0));
			symlink (s, fname);
			prompt (LINKOK, s);

			return 0;
		}
	}
	return 0;
}


int
upload (char *prot)
{
	int     i, f = -1, result = 1, retry = 0;
	char    fname[256], command[256], cwd[256];

	for (i = 0; i < numprotocols; i++) {
		if ((protocols[i].flags & PRF_UPLOAD) &&
		    (NUMFILES == 1 || protocols[i].flags & PRF_BATCH) &&
		    (sameas (protocols[i].select, prot))) {
			f = i;
			break;
		}
	}
	if (f == -1) {
		prompt (ERRSEL, prot);
		return -1;
	}

	sprintf (fname, TMPDIR "/upl%05d", getpid ());
	sprintf (command, "rm -rf %s &>/dev/null", fname);
	system (command);
	mkdir (fname, 0777);

	sprintf (fname, TMPDIR "/upl%05d", getpid ());
	getcwd (cwd, sizeof (cwd));
	chdir (fname);

	if (!(protocols[f].flags & PRF_LINK)) {
		sprintf (command, "umask 007; %s %s; chmod 660 *",
			 protocols[f].command,
			 protocols[f].flags & PRF_NEEDN ? xferlist[firstentry].
			 fullname : "");

		{
			char    s1[80], s2[80];

			strncpy (s1, msg_get (SUPLOAD), 80);
			strncpy (s2, msg_getunit (SSINGLE, NUMFILES), 80);

			prompt (XFERBEG, s1, s2, protocols[f].name,
				protocols[f].stopkey);
		}

		thisuseronl.flags |= OLF_BUSY;
		
		/* Turn off translation if the protocol is binary */
		if (protocols[f].flags & PRF_BINARY)
			out_setxlation (XLATION_OFF);
		/* Commented out to work around a segmentation fault issue.
		   msg_close (msg_sys);
		   msg_sys = NULL;
		*/
		mod_done (INI_OUTPUT | INI_INPUT | INI_SIGNALS);
		
		system (STTYBIN " sane intr 0x03");
		result = system (command);
		system (STTYBIN
			" -echo start undef stop undef intr undef susp undef");
		mod_init (INI_OUTPUT | INI_INPUT | INI_SIGNALS);
		/* Commented out to work around a segmentation fault issue.
		   msg_sys = msg_open ("sysvar");
		*/
		msg_set (msg);

		/* Turn translation back on if necessary */
		if (protocols[f].flags & PRF_BINARY)
			out_setxlation (XLATION_ON);
		mod_regpid (thisuseronl.channel);
		thisuseronl.flags &= ~OLF_BUSY;
	} else
		result = dolink ();

	chdir (cwd);

	retry = 0;
	if (result) {
		autodis = 0;
		prompt (UPLFAIL);
		if (!get_bool (&retry, URETRY, 0, 0, 0))
			retry = 0;
		if (!retry) {
			sprintf (fname, TMPDIR "/upl%05d", getpid ());
			sprintf (command, "rm -rf %s &>/dev/null", fname);
			system (command);
		}
	}

	if (!result && !retry) {
		FILE   *tsibouki;
		int     total = 0;

		if (xferlist[firstentry].auditsok[0] &&
		    xferlist[firstentry].auditdok[0]) {
			audit (thisuseronl.channel,
			       xferlist[firstentry].auditfok,
			       xferlist[firstentry].auditsok,
			       xferlist[firstentry].auditdok,
			       thisuseracc.userid,
			       xferlist[firstentry].fullname);
		}

		if (xferlist[firstentry].cmdok[0]) {
			char    command[4096];

			sprintf (command, "%s %d '%s'",
				 xferlist[firstentry].cmdok,
				 i, xferlist[firstentry].fullname);
			system (command);
		}

		sprintf (fname, TMPDIR "/upl%05d", getpid ());
		sprintf (command,
			 "(echo %s `find %s \\( -type f -or -type l \\)` "
			 "|tr '\\040' '\\012') 2>/dev/null >%s",
			 fname, fname, xferlistname);
		system (command);

		if (!(protocols[f].flags & PRF_LINK)) {
			sprintf (command,
				 "du `find %s -print -maxdepth 1` -bD |cut -f 1",
				 fname);
			if ((tsibouki = popen (command, "r")) != NULL) {
				int     i;

				if (fscanf (tsibouki, " %d \n", &i)) {
					total += i;
					thisuseracc.filesupl++;
					if (sysvar)
						sysvar->filesupl++;
				}
			}
			pclose (tsibouki);
			thisuseracc.bytesupl += total;
			if (sysvar)
				sysvar->bytesupl += (total / 100);
		}
	} else if (result && !retry) {
		if (xferlist[firstentry].auditsfail[0] &&
		    xferlist[firstentry].auditdfail[0]) {
			audit (thisuseronl.channel,
			       xferlist[firstentry].auditffail,
			       xferlist[firstentry].auditsfail,
			       xferlist[firstentry].auditdfail,
			       thisuseracc.userid,
			       xferlist[firstentry].fullname);
		}
		if (xferlist[i].cmdfail[0]) {
			char    command[4096];

			sprintf (command, "%s %d '%s'",
				 xferlist[firstentry].cmdfail,
				 i, xferlist[firstentry].fullname);
			system (command);
		}
		sprintf (command, "\\rm -rf %s %s", fname, xferlistname);
		system (command);
	}

	return !retry;
}


void
uploadrun ()
{
	int     shownmenu = 0;
	char   *s;

	for (;;) {
		if (!
		    (thisuseronl.flags & OLF_MMCALLING &&
		     thisuseronl.input[0])) {
			if (!shownmenu) {
				showmenu ();
				shownmenu = 1;
			}
		} else
			shownmenu = 1;
		if (thisuseronl.flags & OLF_MMCALLING && thisuseronl.input[0]) {
			thisuseronl.input[0] = 0;
		} else {
			if (!cnc_nxtcmd) {
				if (thisuseronl.flags & OLF_MMCONCAT) {
					thisuseronl.flags &= ~OLF_MMCONCAT;
					return;
				}
				if (!shownmenu) {
					showmenu ();
					shownmenu = 1;
				}
				prompt (SHORT);
				inp_get (0);
				cnc_begin ();
			}
		}

		if (margc)
			s = cnc_word ();
		else
			continue;
		if (sameas (s, "?"))
			shownmenu = 0;
		else if (inp_isX (s)) {
			char    command[256];

			if (xferlist[firstentry].auditsfail[0] &&
			    xferlist[firstentry].auditdfail[0]) {
				audit (thisuseronl.channel,
				       xferlist[firstentry].auditffail,
				       xferlist[firstentry].auditsfail,
				       xferlist[firstentry].auditdfail,
				       thisuseracc.userid,
				       xferlist[firstentry].fullname);
			}
			sprintf (command, "\\rm -rf /tmp/upl%05d %s",
				 getpid (), xferlistname);
			system (command);
			return;
		} else if (!margc || inp_reprompt ())
			cnc_end ();
		else {
			char   *excl = NULL;

			inp_raw ();
			excl = strchr (s, '!');
			if (excl ||
			    ((excl = strchr (cnc_nxtcmd, '!')) != NULL)) {
				autodis = 1;
				if (excl)
					*excl = 0;
			}

			switch (upload (s)) {
			case 0:
				shownmenu = 0;
				break;
			case -1:
				cnc_end ();
				break;
			case 1:
				if (autodis)
					autodisconnect ();
				return;
			default:
				shownmenu = 0;
			}
		}
		cnc_end ();
	}
}


/* End of File */
