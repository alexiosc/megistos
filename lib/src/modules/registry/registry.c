/*****************************************************************************\
 **                                                                         **
 **  FILE:     registry.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: B, November 94, Version 2.0                                  **
 **  PURPOSE:  Implement the Users' Registry a second time                  **
 **  NOTES:    (The first revision was lost in an accident involving a      **
 **            make-clean and 35 points of IQ).                             **
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
 * Revision 2.1  2004/09/13 19:55:34  alexios
 * Changed email addresses.
 *
 * Revision 2.0  2004/09/13 19:44:52  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.7  2004/05/17 12:39:05  alexios
 * Fixed weird-looking buffer overrun error.
 *
 * Revision 1.6  2004/02/29 16:46:08  alexios
 * Fixed the ls|grep command spawned to list registries, so no errors are
 * issued when the registry directory is empty.
 *
 * Revision 1.5  2003/12/29 07:51:56  alexios
 * Adjusted #includes.
 *
 * Revision 1.4  2003/12/24 20:12:09  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 2.5  1999/07/18 21:47:54  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 2.4  1998/12/27 16:07:17  alexios
 * Added autoconf support.
 *
 * Revision 2.3  1998/07/24 10:23:17  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 2.2  1997/11/06 20:14:10  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 2.1  1997/09/12 13:21:02  alexios
 * Phonetic search was broken beyond belief. Fixed it.
 *
 * Revision 2.0  1997/08/28 11:03:31  alexios
 * Initial revision.
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
#include "mbk_registry.h"
#include "registry.h"


promptblock_t *msg;

int     entrykey;
int     syskey;
int     crkey;
int     template[3][30];

struct registry registry;


int
loadregistry (char *userid)
{
	FILE   *fp;
	char    fname[256];

	memset (&registry, 0, sizeof (registry));
	sprintf (fname, "%s/%s", mkfname (REGISTRYDIR), userid);
	if ((fp = fopen (fname, "r")) == NULL)
		return -1;
	if (fread (&registry, sizeof (struct registry), 1, fp) != 1) {
		error_fatalsys ("Unable to read registry %s", fname);
	}
	registry.template = registry.template % 3;
	fclose (fp);
	return 0;
}


int
saveregistry (char *userid)
{
	FILE   *fp;
	char    fname[256];

	sprintf (fname, "%s/%s", mkfname (REGISTRYDIR), userid);
	if ((fp = fopen (fname, "w")) == NULL)
		return -1;
	if (fwrite (&registry, sizeof (struct registry), 1, fp) != 1) {
		error_fatalsys ("Unable to write registry %s", fname);
	}
	fclose (fp);
	return 0;
}


void
init ()
{
	int     i, j;

	mod_init (INI_ALL);
	msg = msg_open ("registry");
	msg_setlanguage (thisuseracc.language);

	entrykey = msg_int (ENTRYKEY, 0, 129);
	syskey = msg_int (SYSKEY, 0, 129);
	crkey = msg_int (CRKEY, 0, 129);
	for (i = 0; i < 3; i++)
		for (j = 0; j < 30; j++)
			template[i][j] = msg_int (T1F1 + i * 30 + j, 0, 255);
}


void
login ()
{
	if (key_owns (&thisuseracc, entrykey) &&
	    loadregistry (thisuseracc.userid)) {
		prompt (REGPLS);
	}
}


void
directory ()
{
	int     shownhelp = 0;
	char    c, command[256];
	FILE   *pipe;

	for (;;) {
		fmt_lastresult = 0;
		if ((c = cnc_more ()) != 0) {
			c = cnc_chr ();
			shownhelp = 1;
		} else {
			if (!shownhelp)
				prompt (DINTRO);
			prompt (DLETTER);
			shownhelp = 1;
			inp_get (0);
			cnc_begin ();
			c = cnc_chr ();
		}
		if (!margc && !inp_reprompt ())
			return;
		else if (!margc && inp_reprompt ()) {
			cnc_end ();
			continue;
		}
		if (margc && sameas (margv[0], "?")) {
			shownhelp = 0;
			continue;
		} else if (isalpha (c)) {
			break;
		} else {
			prompt (DIRERR, c);
			cnc_end ();
			continue;
		}
	}

	inp_nonblock ();
	thisuseronl.flags |= OLF_BUSY;

	prompt (DIRHDR);

	sprintf (command, "\\ls %s 2>/dev/null |grep -i \"^[%c-Z]\" 2>/dev/null",
		 mkfname (REGISTRYDIR), c);
	if ((pipe = popen (command, "r")) == NULL) {
		error_fatalsys ("Unable to spawn ls|grep pipe for %s",
				mkfname (REGISTRYDIR));
	}

	for (;;) {
		char    line[256], c;

		if (fscanf (pipe, "%s", line) != 1)
			break;
		if (fmt_lastresult == PAUSE_QUIT) {
			prompt (DIRCAN);
			break;
		}
		if (read (0, &c, 1) == 1)
			if (c == 3 || c == 10 || c == 13) {
				prompt (DIRCAN);
				break;
			}
		loadregistry (line);
		prompt (DIRLIN, line, registry.summary);
	}
	prompt (DIRFTR);
	pclose (pipe);
	inp_block ();
}


void
scan ()
{
	int     shownhelp = 0;
	char    c, command[256];
	FILE   *pipe;

	for (;;) {
		fmt_lastresult = 0;
		if ((c = cnc_more ()) != 0) {
			c = cnc_chr ();
			shownhelp = 1;
		} else {
			if (!shownhelp)
				prompt (SINTRO);
			prompt (SLETTER);
			shownhelp = 1;
			inp_get (0);
			cnc_begin ();
			c = cnc_chr ();
		}
		if (!margc && !inp_reprompt ())
			return;
		else if (!margc && inp_reprompt ()) {
			cnc_end ();
			continue;
		}
		if (margc && sameas (margv[0], "?")) {
			shownhelp = 0;
			continue;
		} else if (isalpha (c)) {
			break;
		} else {
			prompt (DIRERR, c);
			cnc_end ();
			continue;
		}
	}

	shownhelp = 0;
	for (;;) {
		fmt_lastresult = 0;
		if (!cnc_more ()) {
			if (!shownhelp)
				prompt (SCANKW);
			prompt (GETKEYW);
			shownhelp = 1;
			inp_get (0);
			cnc_begin ();
		}
		if (!margc) {
			cnc_end ();
			continue;
		} else if (inp_isX (cnc_nxtcmd)) {
			return;
		} else if (sameas (margv[0], "?")) {
			shownhelp = 0;
			cnc_end ();
			continue;
		} else
			break;
	}

	phonetic (cnc_nxtcmd);

	inp_nonblock ();
	thisuseronl.flags |= OLF_BUSY;
	prompt (DIRHDR);

	sprintf (command, "\\ls %s 2>/dev/null |grep -i \"^[%c-Z]\" 2>/dev/null",
		 mkfname (REGISTRYDIR), c);
	if ((pipe = popen (command, "r")) == NULL) {
		error_fatalsys ("Unable to spawn ls|grep pipe for %s",
				mkfname (REGISTRYDIR));
	}

	for (;;) {
		char    line[256], c, summary[80];
		int     i, pos, found;

		if (fscanf (pipe, "%s", line) != 1)
			break;
		if (fmt_lastresult == PAUSE_QUIT) {
			prompt (DIRCAN);
			break;
		}
		if (read (0, &c, 1) == 1)
			if (c == 3 || c == 10 || c == 13) {
				prompt (DIRCAN);
				break;
			}
		loadregistry (line);

		for (found = i = pos = 0; i < 30;
		     pos += template[registry.template][i++] + 1) {
			char    tmp[1024];

			bzero (tmp, sizeof (tmp));
			strncpy (tmp, &registry.registry[pos],
				 sizeof (tmp) - 1);
			phonetic (tmp);
			if (search (tmp, cnc_nxtcmd)) {
				found = 1;
				break;
			}
		}
		if (!found) {
			char    tmp[1024];

			bzero (tmp, sizeof (tmp));
			strncpy (tmp, registry.summary, sizeof (tmp) - 1);
			phonetic (tmp);
			strcpy (summary, registry.summary);
			found = search (tmp, cnc_nxtcmd);
			strcpy (registry.summary, summary);
		}
		if (found)
			prompt (DIRLIN, line, registry.summary);
	}

	prompt (DIRFTR);
	pclose (pipe);
	inp_block ();
}


void
lookup ()
{
	char    userid[128], *format[33], buf[8192];
	int     i, j, pos;

	for (;;) {
		if (!get_userid (userid, LKUPWHO, UIDERR, 0, 0, 0))
			return;
		if (loadregistry (userid)) {
			cnc_end ();
			prompt (UIDERR);
		} else
			break;
	}

	format[0] = userid;
	for (i = pos = 0, j = 1; i < 30;
	     pos += template[registry.template][i++] + 1) {
		if (template[registry.template][i])
			format[j++] = &registry.registry[pos];
	}
	format[j++] = registry.summary;
	format[j] = NULL;
	vsprintf (buf, msg_get (T1LOOKUP + registry.template), format);
	print ("%s", buf);
}


void
edit (char *userid)
{
	int i, pos;
	char dialogspec [32768];

	loadregistry (userid);

	dialogspec[0] = 0;
	for (i = pos = 0; i < 30; pos += template[registry.template][i++] + 1) {
		if (!template[registry.template][i])
			break;
		strcat (dialogspec, &registry.registry[pos]);
		strcat (dialogspec, "\n");
	}
	strcat (dialogspec, registry.summary);
	strcat (dialogspec, "\nOK\nCANCEL\n");
	fprintf (stderr, "----- len=%d (%d)\n", strlen(dialogspec), sizeof (dialogspec));

	if (dialog_run ("registry", T1VISUAL + registry.template,
			T1LINEAR + 31 * registry.template, dialogspec,
			MAXINPLEN) != 0) {
		error_log ("Unable to run data entry subsystem");
		return;
	}

	dialog_parse (dialogspec);

	for (i = pos = 0; i < 30; pos += template[registry.template][i++] + 1) {
		char   *s = margv[i];

		if (!template[registry.template][i])
			break;
		strcpy (&registry.registry[pos], s);
	}

	strcpy (registry.summary, margv[i]);
	if (sameas (margv[i + 3], "CANCEL") ||
	    sameas (margv[i + 2], margv[i + 3])) {
		prompt (EDITCAN);
		return;
	} else
		prompt (EDITOK);

	saveregistry (userid);
}


void
editother ()
{
	char    userid[128];

	if (!get_userid (userid, EDITWHO, EDITERR, 0, 0, 0))
		return;
	edit (userid);
}


void
change ()
{
	char    opt;

	if (!get_menu (&opt, 1, CHINFO, CHANGE, CHERR, "123", 0, 0)) {
		prompt (NOCHANGE);
		return;
	} else
		opt -= '1';

	if (loadregistry (thisuseracc.userid)) {
		prompt (REGCR);
		registry.template = opt;
	} else {
		if (registry.template == opt) {
			prompt (NONCHANGE);
			return;
		} else {
			registry.template = opt;
			memset (registry.registry, 0,
				sizeof (registry.registry));
			prompt (TMPLCH);
		}
	}
	saveregistry (thisuseracc.userid);
}


void
run ()
{
	int     shownmenu = 0;
	char    c;

	if (!key_owns (&thisuseracc, entrykey)) {
		prompt (NOENTRY);
		return;
	}

	for (;;) {
		thisuseronl.flags &= ~OLF_BUSY;
		if (!
		    (thisuseronl.flags & OLF_MMCALLING &&
		     thisuseronl.input[0])) {
			if (!shownmenu) {
				prompt (key_owns (&thisuseracc, syskey) ?
					REGSMNU : REGMNU);
				prompt (VSHMENU);
				shownmenu = 2;
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
				if (shownmenu == 1) {
					prompt (key_owns (&thisuseracc, syskey)
						? SHSMENU : SHMENU);
				} else
					shownmenu = 1;
				inp_get (0);
				cnc_begin ();
			}
		}

		if ((c = cnc_more ()) != 0) {
			cnc_chr ();
			switch (c) {
			case 'A':
				prompt (ABOUT);
				break;
			case 'D':
				directory ();
				break;
			case 'E':
				if (key_owns (&thisuseracc, syskey))
					editother ();
				else {
					prompt (ERRSEL, c);
					cnc_end ();
					continue;
				}
				break;
			case 'L':
				lookup ();
				break;
			case 'S':
				scan ();
				break;
			case 'Y':
				if (key_owns (&thisuseracc, crkey))
					edit (thisuseracc.userid);
				else {
					prompt (EDITNAX);
					cnc_end ();
					continue;
				}
				break;
			case 'C':
				change ();
				break;
			case 'X':
				prompt (LEAVE);
				return;
			case '?':
				shownmenu = 0;
				break;
			default:
				prompt (ERRSEL, c);
				cnc_end ();
				continue;
			}
		}
		if (fmt_lastresult == PAUSE_QUIT)
			fmt_resetvpos (0);
		cnc_end ();
	}
}


void
done ()
{
	msg_close (msg);
	exit (0);
}


int
handler_run (int argc, char *argv[])
{
	init ();
	run ();
	done ();
	return 0;
}


int
handler_login (int argc, char *argv[])
{
	init ();
	login ();
	done ();
	return 0;
}


int
handler_userdel (int argc, char **argv)
{
	char   *victim = argv[2], fname[1024];

	if (strcmp (argv[1], "--userdel") || argc != 3) {
		fprintf (stderr, "User deletion handler: syntax error\n");
		return 1;
	}

	if (!usr_exists (victim)) {
		fprintf (stderr,
			 "User deletion handler: user %s does not exist\n",
			 victim);
		return 1;
	}

	sprintf (fname, "%s/%s", mkfname (REGISTRYDIR), victim);
	unlink (fname);

	return 0;
}


mod_info_t mod_info_registry = {
	"registry",
	"Registry of Users",
	"Alexios Chouchoulas <alexios@bedroomlan.org>",
	"Allows users to describe themselves to other users.",
	RCS_VER,
	"2.0",
	{80, handler_login}
	,			/* Login handler */
	{0, handler_run}
	,			/* Interactive handler */
	{0, NULL}
	,			/* Logout handler */
	{0, NULL}
	,			/* Hangup handler */
	{0, NULL}
	,			/* Cleanup handler */
	{50, handler_userdel}	/* Delete user handler */
};


int
main (int argc, char *argv[])
{
	mod_setinfo (&mod_info_registry);
	return mod_main (argc, argv);
}


/* End of File */
