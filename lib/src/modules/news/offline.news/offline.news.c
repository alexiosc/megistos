/*****************************************************************************\
 **                                                                         **
 **  FILE:     offline.news.c                                               **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 1997, Version 0.1                                  **
 **  PURPOSE:  Off line mailer, news plugin                                 **
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
 * Revision 1.4  2003/12/25 08:26:20  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.5  1998/12/27 15:53:37  alexios
 * Added autoconf support.
 *
 * Revision 0.4  1998/08/14 11:42:12  alexios
 * Moved to the stable status.
 *
 * Revision 0.3  1998/07/24 10:21:14  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:06:51  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 10:58:05  alexios
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
#include <megistos/offline.news.h>
#include <megistos/../../mailer.h>
#include <megistos/mbk_offline.news.h>

#define __MAILER_UNAMBIGUOUS__
#include <megistos/mbk_mailer.h>

#define __NEWS_UNAMBIGUOUS__
#include <megistos/mbk_news.h>


promptblock_t *msg;
promptblock_t *news_msg;


int     onkey;
int     defnews;
char   *newsfile;

int     sopkey;


char   *progname;

void
init ()
{
	mod_init (INI_ALL);

	news_msg = msg_open ("news");
	sopkey = msg_int (NEWS_SOPKEY, 0, 129);

	msg = msg_open ("offline.news");
	onkey = msg_int (ONKEY, 0, 129);
	defnews = msg_bool (DEFNEWS);
	newsfile = msg_string (NEWSFILE);
	msg_setlanguage (thisuseracc.language);
}


void
done ()
{
	msg_close (msg);
}


void
warn ()
{
	fprintf (stderr, "This is a Mailer plugin. ");
	fprintf (stderr, "It should not be run by the user.\n");
	exit (1);
}


mod_info_t mod_info_offline_news = {
	"offline.news",
	"Mailer Plugin: News Bulletins",
	"Alexios Chouchoulas <alexios@vennea.demon.co.uk>",
	"Packages logon news bulletins.",
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
	progname = mod_info_offline_news.progname;
	mod_setinfo (&mod_info_offline_news);

	if (argc != 2)
		return mod_main (argc, argv);

	if (!strcmp (argv[1], "--setup")) {
		atexit (done);
		init ();
		setup ();
	} else if (!strcmp (argv[1], "--download")) {
		atexit (done);
		init ();
		return ondownload ();
	}

	/* This should only return help, info, etc */
	return mod_main (argc, argv);
}


/* End of File */
