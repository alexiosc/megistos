/*****************************************************************************\
 **                                                                         **
 **  FILE:     offline.mail.c                                               **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1997, Version 0.1                                    **
 **  PURPOSE:  Off line mailer, mail plugin                                 **
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
 * Revision 2.0  2004/09/13 19:44:51  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2003/12/27 12:29:40  alexios
 * Adjusted #includes.
 *
 * Revision 1.4  2003/12/25 08:26:20  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.4  1998/12/27 15:48:12  alexios
 * Added autoconf support.
 *
 * Revision 0.3  1998/07/24 10:20:56  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:06:43  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 10:55:29  alexios
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
#include "offline.mail.h"
#include "mailerplugins.h"
#include "mbk_offline.mail.h"

#define __MAILER_UNAMBIGUOUS__
#include <mbk/mbk_mailer.h>

#define __EMAILCLUBS_UNAMBIGUOUS__
#include <mbk/mbk_emailclubs.h>


promptblock_t *mail_msg;
promptblock_t *emailclubs_msg;
promptblock_t *mailer_msg;

char   *progname;
char   *defclub;

int     sopkey;
int     wrtkey;
int     netkey;
int     rrrkey;
int     wrtchg;
int     netchg;
int     rrrchg;
int     msglen;

char   *bbsid;
int     ansihi;
int     ansibye;
char   *hifile;
char   *byefile;
char   *ctlname[6];
int     qwkuc;

int     updqsc;
int     defatt;
int     defreq;
int     defhdr;
char   *omceml;
char   *allnam;
int     usepass;
int     fixeta;
char    etaxlt;
int     prgind;


void
init ()
{
	int     i;

	mod_init (INI_ALL);

	emailclubs_msg = msg_open ("emailclubs");
	msg_setlanguage (thisuseracc.language);

	sopkey = msg_int (EMAILCLUBS_SOPKEY, 0, 129);
	wrtkey = msg_int (EMAILCLUBS_WRTKEY, 0, 129);
	netkey = msg_int (EMAILCLUBS_NETKEY, 0, 129);
	rrrkey = msg_int (EMAILCLUBS_RRRKEY, 0, 129);
	wrtchg = msg_int (EMAILCLUBS_WRTCHG, -32767, 32767);
	netchg = msg_int (EMAILCLUBS_NETCHG, -32767, 32767);
	rrrchg = msg_int (EMAILCLUBS_RRRCHG, -32767, 32767);
	defclub = msg_string (EMAILCLUBS_DEFCLUB);
	msglen = msg_int (EMAILCLUBS_MSGLEN, 1, 256) << 10;

	mailer_msg = msg_open ("mailer");
	bbsid = msg_string (MAILER_BBSID);
	ansihi = msg_bool (MAILER_ANSIHI);
	ansibye = msg_bool (MAILER_ANSIBYE);
	hifile = msg_string (MAILER_HIFILE);
	byefile = msg_string (MAILER_BYEFILE);
	for (i = 0; i < 6; i++)
		ctlname[i] = msg_string (MAILER_CTLNAME1 + i);
	if ((qwkuc = msg_token (MAILER_QWKUC, "LOWERCASE", "UPPERCASE")) == 0) {
		error_fatal ("Option QWKUC in mailer.msg has bad value.");
	} else
		qwkuc--;

	mail_msg = msg_open ("offline.mail");
	msg_setlanguage (thisuseracc.language);

	if ((defatt = msg_token (DEFATT, "NO", "YES", "ASK")) == 0) {
		error_fatal
		    ("Option DEFATT in offline.mail.msg has bad value.");
	} else
		defatt--;

	if ((defreq = msg_token (DEFREQ, "NO", "YES", "ASK")) == 0) {
		error_fatal
		    ("Option DEFREQ in offline.mail.msg has bad value.");
	} else
		defreq--;

	updqsc = msg_bool (UPDQSC);
	defhdr = msg_bool (DEFHDR);
	omceml = msg_string (OMCEML);
	allnam = msg_string (ALLNAM);
	usepass = msg_bool (USEPASS);
	fixeta = msg_bool (FIXETA);
	etaxlt = msg_char (ETAXLT);
	prgind = msg_bool (PRGIND);
}


void
done ()
{
	msg_close (emailclubs_msg);
	msg_close (mailer_msg);
	msg_close (mail_msg);
}


void
warn ()
{
	fprintf (stderr, "This is a Mailer plugin. ");
	fprintf (stderr, "It should not be run by the user.\n");
	exit (1);
}


mod_info_t mod_info_offline_mail = {
	"offline.mail",
	"Mailer Plugin: Mail and Clubs",
	"Alexios Chouchoulas <alexios@vennea.demon.co.uk>",
	"Packages private and public BBS messages.",
	RCS_VER,
	"1.0",
	{0, NULL},		/* Login handler */
	{0, NULL},		/* Interactive handler */
	{0, NULL},		/* Install logout handler */
	{0, NULL},		/* Hangup handler */
	{0, NULL},		/* Cleanup handler */
	{0, NULL}		/* Delete user handler */
};


int
main (int argc, char *argv[])
{
	progname = mod_info_offline_mail.progname;
	mod_setinfo (&mod_info_offline_mail);

	if (argc != 2)
		return mod_main (argc, argv);

	if (!strcmp (argv[1], "--setup")) {
		atexit (done);
		init ();
		setup ();
	} else if (!strcmp (argv[1], "--download")) {
		atexit (done);
		init ();
		return omdownload ();
	} else if (!strcmp (argv[1], "--upload")) {
		atexit (done);
		init ();
		return omupload ();
	} else if (!strcmp (argv[1], "--reqman")) {
		atexit (done);
		init ();
		return reqman ();
	}

	/* This should only return help, info, etc */
	return mod_main (argc, argv);
}


/* End of File */
