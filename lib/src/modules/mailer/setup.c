/*****************************************************************************\
 **                                                                         **
 **  FILE:     setup.c                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1997, Version 0.1                                    **
 **  PURPOSE:  Setup preferences etc                                        **
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
 * Revision 1.4  2003/12/24 20:12:10  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.8  1999/07/18 21:42:47  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 0.7  1998/12/27 15:45:11  alexios
 * Added autoconf support.
 *
 * Revision 0.6  1998/08/14 11:31:09  alexios
 * No changes.
 *
 * Revision 0.5  1998/08/11 10:11:15  alexios
 * Added code to setup translation for users.
 *
 * Revision 0.4  1998/07/24 10:19:54  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.3  1997/12/02 20:45:35  alexios
 * Switched to using the archiver file instead of locally
 * defined compression/decompression programs.
 *
 * Revision 0.2  1997/11/06 20:06:32  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 10:51:40  alexios
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
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include <megistos/mailer.h>
#include <megistos/mbk_mailer.h>
#define __ARCHIVERS_UNAMBIGUOUS__
#include <megistos/mbk_archivers.h>


#define NUMSEL MAXPLUGINS

const static char sel[NUMSEL] = "1234567890ABCDEFGHIJKLMNOPQRTUVWYZ";


static void
showsetupmenu ()
{
	char    pad[256];
	int     i;

	prompt (SETUPH);

	for (i = 0; i < 254; i += 2)
		pad[i] = '.', pad[i + 1] = ' ';
	pad[255] = 0;

	for (i = 0; i < numplugins; i++) {
		char    line[256];

		if (!(plugins[i].flags & PLF_SETUP))
			continue;
		strcpy (line, &pad[i % 2]);
		strcpy (&line
			[67 -
			 strlen (plugins[i].descr[thisuseracc.language - 1])],
			plugins[i].descr[thisuseracc.language - 1]);
		line[66 -
		     strlen (plugins[i].descr[thisuseracc.language - 1])] = 32;
		prompt (SETUPPL, sel[i], line);
	}

	prompt (SETUPF);
}


static int
setupmenu ()
{
	int     shownmenu = 0;
	char    c;
	char    options[NUMSEL];

	strcpy (options, sel);
	options[numplugins] = 0;

	for (;;) {
		fmt_lastresult = 0;
		if ((c = cnc_more ()) != 0) {
			if (sameas (cnc_nxtcmd, "X"))
				return 0;
			c = cnc_chr ();
			shownmenu = 1;
		} else {
			if (!shownmenu)
				showsetupmenu ();
			else
				prompt (SETUPSH);
			shownmenu = 1;
			inp_get (0);
			cnc_begin ();
			if (cnc_nxtcmd)
				c = cnc_chr ();
		}
		if (!margc) {
			cnc_end ();
			continue;
		}
		if (inp_isX (margv[0])) {
			return 0;
		} else if (margc && (c == '?' || sameas (margv[0], "?"))) {
			shownmenu = 0;
			continue;
		} else if (strchr (options, c) || c == 'S')
			return c;
		else {
			prompt (ERRSEL, c);
			cnc_end ();
			continue;
		}
	}
	return 0;
}


void
defaultvals ()
{
	userqwk.compressor = 0;
	userqwk.decompressor = 0;
	if (defgrk)
		userqwk.flags |= USQ_GREEKQWK;
	strcpy (userqwk.packetname, bbsid);
	saveprefs (USERQWK, sizeof (userqwk), &userqwk);
}


void
setupqwk ()
{
	int     i;
	char    tmp[256];

	if (loadprefs (USERQWK, &userqwk) != 1) {
		defaultvals ();
	}

	msg_set (archivers);
	sprintf (inp_buffer, "%s\n",
		 msg_get (ARCHIVERS_NAME1 + userqwk.compressor * 7));
	sprintf (tmp, "%s\n",
		 msg_get (ARCHIVERS_NAME1 + userqwk.decompressor * 2));
	strcat (inp_buffer, tmp);
	msg_reset ();
	sprintf (tmp, "%s\n%s\n%s\nOK\nCANCEL\n",
		 userqwk.flags & USQ_GREEKQWK ? "on" : "off",
		 userqwk.packetname,
		 msg_get (TR0 + ((userqwk.flags & OMF_TR) >> OMF_SHIFT)));

	if (dialog_run ("mailer", QWKVT, QWKLT, inp_buffer, MAXINPLEN) != 0) {
		error_log ("Unable to run data entry subsystem");
		return;
	}

	dialog_parse (inp_buffer);

	if (sameas (margv[7], "OK") || sameas (margv[7], margv[5])) {
		msg_set (archivers);
		for (i = 0; i < 8; i++) {
			char   *s = margv[i];

			if (i == 0) {
				int     i;

				userqwk.compressor = -1;
				for (i = 0; i < MAXARCHIVERS; i++)
					if (sameas
					    (msg_get (ARCHIVERS_NAME1 + i * 7),
					     s)) {
						userqwk.compressor = i;
						break;
					}
				if (userqwk.compressor < 0) {
					error_fatal
					    ("Bad value \"%s\" for compressor.",
					     s);
				}
			} else if (i == 1) {
				int     i;

				userqwk.decompressor = -1;
				for (i = 0; i < MAXARCHIVERS; i++)
					if (sameas
					    (msg_get (ARCHIVERS_NAME1 + i * 7),
					     s)) {
						userqwk.decompressor = i;
						break;
					}
				if (userqwk.decompressor < 0) {
					error_fatal
					    ("Bad value \"%s\" for decompressor.",
					     s);
				}
			} else if (i == 2) {
				if (sameas ("on", s))
					userqwk.flags |= USQ_GREEKQWK;
				else
					userqwk.flags &= ~USQ_GREEKQWK;
			} else if (i == 3) {
				strcpy (userqwk.packetname, stripspace (s));
			} else if (i == 4) {
				int     n;

				msg_set (mailer_msg);
				for (n = 0; n < NUMXLATIONS; n++) {
					if (sameas (s, msg_get (TR0 + n))) {
						userqwk.flags &= ~OMF_TR;
						userqwk.flags |=
						    n << OMF_SHIFT;
						break;
					}
				}
			}
		}
		msg_set (mailer_msg);

		saveprefs (USERQWK, sizeof (userqwk), &userqwk);
		prompt (SETUPOK);
	} else {
		prompt (SETUPAB);
	}
}


static void
pluginsetup (int n)
{
	char    command[256];

	sprintf (command, "%s --setup", plugins[n].name);
	runcommand (command);
	cnc_end ();
}


void
setup ()
{
	char    c, *cp;

	for (;;)
		switch (c = setupmenu ()) {
		case 0:
			return;
		case 'S':
			setupqwk ();
			break;
		default:
			if ((cp = strchr (sel, c)) == NULL)
				continue;
			pluginsetup ((int) (cp - sel));
		}
}


/* End of File */
