/*****************************************************************************\
 **                                                                         **
 **  FILE:     cookie.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, January 95, Version 1.0                                   **
 **  PURPOSE:  Automatic cookie dispenser and cookie database manager       **
 **  NOTES:    The format of the cookie program is as follows:              **
 **                                                                         **
 **            #This is a simple quotation.                                 **
 **            @This is the person being quoted.                            **
 **            #This is another quotation.                                  **
 **            #And this is another one.                                    **
 **            @Anonymous                                                   **
 **            . . .                                                        **
 **                                                                         **
 **            This program has three functions:                            **
 **                                                                         **
 **            When run with argument -logout it displays a logout cookie.  **
 **            When run with argument -cleanup it re-indexes the database.  **
 **            When run without arguments, it displays an on-line cookie.   **
 **                                                                         **
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
 * Revision 1.4  2003/12/24 20:12:14  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.6  1999/07/18 22:09:11  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 1.5  1998/12/27 16:33:27  alexios
 * Added autoconf support.
 *
 * Revision 1.4  1998/07/24 10:30:16  alexios
 * Migrated to bbslib 0.6.
 * Added support for multiple files, each with an equal chance of
 * having a cookie output from it (regardless of their relative
 * size). We're beginning to look a little like fortune(1).
 *
 * Revision 1.3  1997/11/06 20:17:58  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 1.2  1997/11/06 17:06:30  alexios
 * No changes.
 *
 * Revision 1.1  1997/11/05 10:38:49  alexios
 * Use the new multi-level, flagged auditing facilities.
 *
 * Revision 1.0  1997/08/28 11:25:01  alexios
 * Initial revision
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
#define WANT_DIRENT_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include <megistos/mbk_sysvar.h>


/*                   123456789012345678901234567890 */
#define AUS_CKIECUB "COOKIE CLEANUP"
#define AUS_CKIECUE "END OF COOKIE CLEANUP"

/*                   1234567890123456789012345678901234567890123456789012... */
#define AUD_CKIECUB ""
#define AUD_CKIECUE "%d Quotes in %d database(s)"

#define AUT_CKIECUB (AUF_INFO|AUF_EVENT)
#define AUT_CKIECUE (AUF_INFO|AUF_EVENT)



void
init ()
{
	mod_init (INI_ALL);
	msg_setlanguage (thisuseracc.language);
	fmt_setverticalformat (0);
}


void
cleanup ()
{
	FILE   *qdb, *idx;
	long int offset = 0;
	long int temp = 0;
	long int seekstate = 1;
	long int entries = 0, total = 0;
	int     i, numfiles = 0;
	int     dotcount = 0;
	char    c;

	mod_init (INI_TTYNUM | INI_OUTPUT | INI_SYSVARS | INI_ERRMSGS |
		  INI_CLASSES);

	audit_setfile (mkfname (CLNUPAUDITFILE));
	audit ("CLEANUP", AUDIT (CKIECUB));

	printf ("\nMegistos BBS cookie database index.\n");
	printf ("Cookie (c) 1991 Dennis Kefalinos.\n");
	printf ("This code written by Alexios Chouchoulas.\n\n");

	for (i = 0; i < 100; i++) {
		char    cookiefile[512], cookieidxfile[512];

		entries = 0;

		sprintf (cookiefile, mkfname (COOKIEFILE), i);
		sprintf (cookieidxfile, mkfname (COOKIEIDXFILE), i);

		if ((qdb = fopen (cookiefile, "r")) == NULL) {
			/*fprintf(stderr,"\nError occurred while opening %s\n",cookiefile); */
			/*exit(-1); */
			continue;
		} else
			printf ("Quotation Data Base:  %s\n", cookiefile);
		numfiles++;

		if ((idx = fopen (cookieidxfile, "w")) == NULL) {
			fprintf (stderr, "Error occured while creating %s",
				 cookieidxfile);
			exit (-1);
		} else
			printf ("Quotation index file: %s\n", cookieidxfile);

		printf ("Working");
		fflush (stdout);

		offset = 0;
		fwrite (&offset, sizeof (offset), 1, idx);
		while (!feof (qdb)) {
			switch (c = getc (qdb)) {
			case 13:
			case 10:
				seekstate = 1;
				break;
			case '#':
				if (seekstate == 1) {
					fwrite (&offset, sizeof (temp), 1,
						idx);
					seekstate = 0;
					entries++;
					total++;
				}
				break;
			default:
				seekstate = 0;
			}
			offset++;
			if (!(++dotcount % (1 << 13))) {
				printf (".");
				fflush (stdout);
			}
		}
		rewind (idx);
		fwrite (&entries, sizeof (entries), 1, idx);
		fclose (qdb);
		fclose (idx);
		printf ("Done!\n\n");
	}
	audit ("CLEANUP", AUDIT (CKIECUE), total, numfiles);
	audit_resetfile ();
}


static int
cookiesel (const struct dirent *d)
{
	return strstr (d->d_name, "cookies-") == d->d_name &&
	    strstr (d->d_name, ".idx") != NULL;
}


void
run (int begin, int end)
{
	FILE   *qdb, *idx;
	long int choice, max = 0, idxptr;
	int     newline = 1, mode = 0;
	char    c, *cp, buf[8192], dat[512], idxfn[512];
	struct dirent **d;
	int     n;

	n = scandir (mkfname (COOKIEDIR), &d, cookiesel, alphasort);

	if (n == 0) {
		error_log ("Didn't find any cookie files in %s",
			   mkfname (COOKIEDIR));
	}

	/* Choose a file at random. Every file has an equal chance of being
	   chosen. This means that quotes in smaller databases will appear as often
	   as quotes in huge cookie jars, making things slightly more fair. */

	randomize ();
	choice = rnd (n);

	strcpy (idxfn, mkfname (COOKIEDIR "/%s", d[choice]->d_name));
	strcpy (dat, idxfn);
	{
		char   *cp = strstr (dat, ".idx");

		strcpy (cp, ".dat");
	}

	if ((qdb = fopen (dat, "r")) == NULL) {
		error_logsys ("Unable to open %s", dat);
	}
	if ((idx = fopen (idxfn, "r")) == NULL) {
		error_logsys ("Unable to open %s", idxfn);
	}
	fread (&max, sizeof (max), 1, idx);
	choice = rnd (max) + 1;
	fseek (idx, choice * sizeof (long), SEEK_SET);
	fread (&idxptr, sizeof (long), 1, idx);
	fseek (qdb, idxptr, SEEK_SET);

	msg_set (msg_sys);
	prompt (begin);
	c = getc (qdb);
	cp = buf;
	do {
		c = getc (qdb);
		if (c == '#') {
			newline = 0;
			break;
		} else if (c == '@' && newline) {
			*cp = 0;
			prompt (CKIELN1, buf);
			cp = buf;
			mode = 1;
		} else if (c == 13)
			continue;
		else {
			*(cp++) = c;
			newline = (c == 10);
		}
	} while (!feof (qdb) && (c != '#'));
	*cp = 0;
	prompt (mode ? CKIELN2 : CKIELN1, buf);
	prompt (end);
	fclose (qdb);
	fclose (idx);
}


int
handler_run (int argc, char **argv)
{
	init ();
	run (GCOOKIE, GCKIEEND);
	return 0;
}

int
handler_logout (int argc, char **argv)
{
	init ();
	run (COOKIE, CKIEEND);
	return 0;
}

int
handler_cleanup (int argc, char **argv)
{
	cleanup ();
	return 0;
}



mod_info_t mod_info_cookie = {
	"cookie",
	"Cookie",
	"Alexios Chouchoulas <alexios@vennea.demon.co.uk>",
	"Shows random quotes a la fortune(1) at logout and when /cookie is issued.",
	RCS_VER,
	"2.0",
	{0, NULL}
	,			/* No login handler */
	{0, handler_run}
	,			/* No run handler, this is a simple module */
	{20, handler_logout}
	,			/* Install logout handler */
	{0, NULL}
	,			/* No hangup handler */
	{90, handler_cleanup}
	,			/* Low-priority cleanup handler */
	{0, NULL}		/* No delete user handler, no per-user info */
};


int
main (int argc, char *argv[])
{
	mod_setinfo (&mod_info_cookie);
	return mod_main (argc, argv);
}


/* End of File */
