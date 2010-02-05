/*****************************************************************************\
 **                                                                         **
 **  FILE:     bbsdialog.c                                                  **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: B, November 94, Version 1.1                                  **
 **            C, July 95, Version 1.2                                      **
 **  PURPOSE:  Manage BBS dialog boxes/data entry sessions.                 **
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
 * $Id: bbsdialog.c,v 2.0 2004/09/13 19:44:54 alexios Exp $
 *
 * $Log: bbsdialog.c,v $
 * Revision 2.0  2004/09/13 19:44:54  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.6  2004/05/22 19:29:45  alexios
 * Added a workaround for a TERMIOS bug that corrupts the TERMIOS when
 * field help is shown.
 *
 * Revision 1.5  2003/12/24 18:32:08  alexios
 * Fixed #includes.
 *
 * Revision 1.4  2003/12/23 23:20:24  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.6  1999/07/18 22:07:30  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 0.5  1998/12/27 16:30:50  alexios
 * Added autoconf support.
 *
 * Revision 0.4  1998/07/24 10:29:41  alexios
 * Moved to stable status. Migrated to bbslib 0.6.
 *
 * Revision 0.3  1997/11/06 20:02:58  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/09/12 13:35:04  alexios
 * Fixed broken check for ANSI capabilities that only checked the
 * user's preferences, not their actual terminal's capability.
 *
 * Revision 0.1  1997/08/28 11:21:38  alexios
 * First registered revision. Adequate.
 *
 *
 */


static const char rcsinfo[] =
    "$Id: bbsdialog.c,v 2.0 2004/09/13 19:44:54 alexios Exp $";



#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_NCURSES_H 1
#define WANT_TERMIOS_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "bbsdialog.h"
#include "mbk_bbsdialog.h"



union object *object = NULL;
int     numobjects = 0;
promptblock_t *msg = NULL;
promptblock_t *templates = NULL;
int     mode;
char   *mbkname = NULL;
int     vtnum = 0;
int     ltnum = 0;
char   *dfname = NULL;

struct termios oldtermios;


void
endsession (char *event)
{
	FILE   *fp;
	int     i;

	if (mode == VISUAL) {
		thisuseronl.flags &= ~(OLF_BUSY | OLF_NOTIMEOUT);
		inp_resetidle ();
		attrset (A_NORMAL);
		clear ();
		wrefresh (stdscr);
		refresh ();
		endwin ();
	}

	if ((fp = fopen (dfname, "w")) == NULL) {
		error_fatalsys ("Unable to write data file %s", dfname);
	}

	for (i = 0; i < numobjects; i++) {
		switch (object[i].s.type) {
		case OBJ_STRING:
			fprintf (fp, "%s\n", object[i].s.data);
			break;
		case OBJ_NUM:
			fprintf (fp, "%s\n", object[i].n.data);
			break;
		case OBJ_LIST:
			fprintf (fp, "%s\n", object[i].l.data);
			break;
		case OBJ_TOGGLE:
			fprintf (fp, "%s\n", object[i].t.data ? "on" : "off");
			break;
		case OBJ_BUTTON:
			fprintf (fp, "%s\n", object[i].b.label);
			break;
		}
	}
	fprintf (fp, "%s\n", event);
	fclose (fp);

	if (strcasecmp (event, "Linear"))
		exit (0);
	else {
		char    format[20];

		sprintf (format, "%d", ltnum);
		execl (mkfname (BBSDIALOGBIN), "bbsdialog", mbkname, "-1",
		       format, dfname, NULL);
	}
}


void
usage ()
{
	printf
	    ("syntax: bbsdialog mbk_name vtemplate ltemplate data_file\n\n");
	printf
	    ("mbk_name:  name of a message block file containing the templates.\n");
	printf ("vtemplate: prompt # of the visual template.\n");
	printf
	    ("ltemplate: prompt # of the linear template. The mbk file should have\n");
	printf
	    ("           N (N=number of fields) prompts right after (ltemplate).\n");
	printf
	    ("           These prompts are the data entry prompts for each field,\n");
	printf ("           in order of definition.\n");
	printf
	    ("data_file: file containing default values and data (one line/field).\n\n");
	exit (-1);
}


int
main (int argc, char *argv[])
{
	mod_setprogname (argv[0]);
	if (argc != 5) {
		usage ();
	} else {
		mbkname = argv[1];
		vtnum = atoi (argv[2]);
		ltnum = atoi (argv[3]);
		dfname = argv[4];
	}

	mod_init (INI_ALL);
	tcgetattr (0, &oldtermios);

	msg = msg_open ("bbsdialog");
	msg_setlanguage (thisuseracc.language);
	templates = msg_open (mbkname);
	msg_setlanguage (thisuseracc.language);

	if (vtnum >= 0 && thisuseracc.prefs & UPF_VISUAL &&
	    thisuseronl.flags & OLF_ANSION) {
		mode = VISUAL;
		runvisual ();
	} else {
		mode = LINEAR;
		runlinear ();
	}

	return 0;
}


/* End of File */
