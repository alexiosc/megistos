/*****************************************************************************\
 **                                                                         **
 **  FILE:     bulletins.c                                                  **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 1996, Version 0.5                               **
 **  PURPOSE:  Bulletin (article) reader for the clubs                      **
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
 * Revision 1.5  2003/12/27 12:32:18  alexios
 * Adjusted #includes. Removed bltcnv. Minor cosmetic changes.
 *
 * Revision 1.4  2003/12/24 20:12:15  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.4  1999/07/28 23:10:22  alexios
 * Added a command to download a bulletin.
 *
 * Revision 0.3  1998/12/27 15:27:54  alexios
 * Added legalese (how did we miss this file?). Added auto-
 * conf support, plus code to allow entry to the Bulletins
 * module from the Clubs module.
 *
 * Revision 0.2  1998/07/24 10:14:42  alexios
 * Migrated to bbslib 0.6. Added support for conversion of
 * Major BBS-based bulletin database.
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


promptblock_t *msg, *clubmsg;

int     entrykey;
int     sopkey;
int     flaxes;
int     audins;
int     auddel;
int     audedt;
int     audrd;
int     askdef;
int     indsel;
int     indspd;
int     ainsdef;
char   *dnldesc;


void
init ()
{
	mod_init (INI_ALL);
	clubmsg = msg_open ("emailclubs");
	msg = msg_open ("bulletins");
	msg_setlanguage (thisuseracc.language);

	initbltsubstvars ();

	entrykey = msg_int (ENTRYKEY, 0, 129);
	sopkey = msg_int (SOPKEY, 0, 129);
	if ((flaxes =
	     msg_token (FLAXES, "CO-OPS", "CLUBOP", "PRIVILEGED") - 1) < 0) {
		error_fatal
		    ("LEVEL2 option FLAXES (bulletins.msg) has bad value.");
	}
	audins = msg_bool (AUDINS);
	auddel = msg_bool (AUDDEL);
	audedt = msg_bool (AUDEDT);
	audrd = msg_bool (AUDRD);
	askdef = msg_bool (ASKDEF);
	ainsdef = msg_bool (AINSDEF);
	indsel = msg_bool (INDSEL);
	indspd = msg_int (INDSPD, 1, 500);
	dnldesc = msg_string (DNLDESC);

	dbopen ();
}


void
about ()
{
	prompt (ABOUT);
}


void
run ()
{
	int     shownmenu = 0, ax;
	char    c = 0;

	if (thisuseronl.flags & OLF_JMP2BLT) {
		strcpy (club, thisuseracc.lastclub);
		thisuseronl.flags &= ~OLF_JMP2BLT;
	}

	if (!key_owns (&thisuseracc, entrykey)) {
		prompt (NOAXES);
		return;
	}

	for (;;) {
		ax = getaccess (club) >= flaxes;
		thisuseronl.flags &= ~OLF_BUSY;
		if (!
		    (thisuseronl.flags & OLF_MMCALLING &&
		     thisuseronl.input[0])) {
			if (!shownmenu) {
				prompt (ax ? SMENU : MENU);
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
					if (club[0])
						prompt (CURSIG, club);
					prompt (ax ? SSHMENU : SHMENU);
				} else
					shownmenu = 1;
				inp_get (0);
				cnc_begin ();
			}
		}

		if ((c = cnc_more ()) != 0) {
			cnc_chr ();
			switch (c) {
			case 'H':
				about ();
				break;
			case 'S':
				selectclub ();
				thisuseronl.flags &= ~OLF_MMCONCAT;
				if (!cnc_more ())
					cnc_end ();
				break;
			case 'I':
				if (getaccess (club) >= flaxes)
					insertblt ();
				else {
					prompt (ERRSEL, c);
					cnc_end ();
					continue;
				}
				break;
			case 'P':
				if (getaccess (club) >= flaxes)
					bltdel ();
				else {
					prompt (ERRSEL, c);
					cnc_end ();
					continue;
				}
				break;
			case 'E':
				if (getaccess (club) >= flaxes)
					bltedt ();
				else {
					prompt (ERRSEL, c);
					cnc_end ();
					continue;
				}
				break;
			case 'A':
				if (getaccess (club) >= flaxes)
					autoins ();
				else {
					prompt (ERRSEL, c);
					cnc_end ();
					continue;
				}
				break;
			case 'L':
				list (0);
				break;
			case 'F':
				list (1);
				break;
			case 'R':
				bltread ();
				break;
			case 'D':
				bltdnl ();
				break;
			case 'K':
				keysearch ();
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
	dbclose ();
}


#if 0
int     bltcnv_main (int argc, char *argv[]);
#endif


int
handler_run (int argc, char *argv[])
{
	atexit (done);
	init ();
	run ();
	return 0;
}



mod_info_t mod_info_bulletins = {
	"bulletins",
	"Bulletin reader",
	"Alexios Chouchoulas <alexios@vennea.demon.co.uk>",
	"Permanent archive of interesting club articles et al",
	RCS_VER,
	"1.0",
	{50, login},		/* Login handler */
	{0,  handler_run},	/* Interactive handler */
	{0,  NULL},		/* Install logout handler */
	{0,  NULL},		/* Hangup handler */
	{50, cleanup},		/* Cleanup handler */
	{0,  NULL}		/* Delete user handler */
};


int
main (int argc, char *argv[])
{
#if 0
	if (strstr (argv[0], "bltcnv"))
		return bltcnv_main (argc, argv);
#endif
	if (argc == 3 && !strcmp (argv[1], "--insert")) {
		init ();
		return extins (argv[2]);
	}

	mod_setinfo (&mod_info_bulletins);
	return mod_main (argc, argv);
}


/* End of File */


/* End of File */
