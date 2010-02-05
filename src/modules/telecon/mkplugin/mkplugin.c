/*****************************************************************************\
 **                                                                         **
 **  FILE:     mkplugin.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 96, Version 1.0                                    **
 **  PURPOSE:  Teleconferences, compile the plugin definition file.         **
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
 * $Id: mkplugin.c,v 2.0 2004/09/13 19:44:53 alexios Exp $
 *
 * $Log: mkplugin.c,v $
 * Revision 2.0  2004/09/13 19:44:53  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2003/12/27 12:29:38  alexios
 * Adjusted #includes.
 *
 * Revision 1.4  2003/12/24 20:12:08  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.5  1999/07/28 23:13:16  alexios
 * Made main() return an int, as required.
 *
 * Revision 0.4  1998/12/27 16:10:27  alexios
 * Added autoconf support.
 *
 * Revision 0.3  1998/07/24 10:24:49  alexios
 * Generic debugging. Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:06:11  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 11:08:28  alexios
 * First registered revision. Adequate.
 *
 *
 */


static const char rcsinfo[] =
    "$Id: mkplugin.c,v 2.0 2004/09/13 19:44:53 alexios Exp $";




#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include <telecon.h>
#include <teleconplugins.h>


struct plugin *plugins = NULL;
int     numplugins = 0;


int
keycmp (const void *A, const void *B)
{
	const struct keyword *a = A, *b = B;

	return strcmp (a->keyword, b->keyword);
}


int
plugincmp (const void *A, const void *B)
{
	const struct plugin *a = A, *b = B;

	return strcmp (a->keyword, b->keyword);
}


void
check (struct plugin *p)
{
	if (!p->exec[0]) {
		fprintf (stderr, "Plugin '%s' has no 'exec' keyword.\n",
			 p->keyword);
		exit (1);
	} else if (!p->descr[0]) {
		fprintf (stderr, "Plugin '%s' has no 'descr' keyword.\n",
			 p->keyword);
		exit (1);
	}
}


void
addtolist (struct plugin *p)
{
	struct plugin *tmp;

	tmp = alcmem (++numplugins * sizeof (struct plugin));
	memcpy (tmp, plugins, (numplugins - 1) * sizeof (struct plugin));
	memcpy (&tmp[numplugins - 1], p, sizeof (struct plugin));
	if (plugins)
		free (plugins);
	plugins = tmp;
}


int
pluginexists (char *keyword)
{
	int     i;

	for (i = 0; i < numplugins; i++)
		if (sameas (plugins[i].keyword, keyword))
			return 1;
	return 0;
}


int
main (int argc, char *argv[])
{
	FILE   *fin, *fout;
	char    line[2048], *cp, keyword[256], *data, tmp[2048];
	int     num = 0, i, n, nkeywords = 0, first = 1;
	struct keyword *k;
	struct plugin p;

	mod_setprogname (argv[0]);
	if ((fin = fopen (mkfname (TELEPISRCFILE), "r")) == NULL) {
		fprintf (stderr, "%s: Unable to open %s\n", argv[0],
			 mkfname (TELEPISRCFILE));
		exit (1);
	}

	if ((fout = fopen (mkfname (TELEPLUGINFILE), "w")) == NULL) {
		fprintf (stderr, "%s: Unable to create %s\n", argv[0],
			 mkfname (TELEPLUGINFILE));
		exit (1);
	}

	printf ("\nParsing %s\n", mkfname (TELEPISRCFILE));

	for (i = 0; keywords[i].code >= 0; i++)
		nkeywords++;

	while (!feof (fin)) {
		if (!fgets (line, sizeof (line), fin))
			break;
		num++;

		if ((cp = strrchr (line, '\n')) != NULL)
			for (; (*cp == '\n') || (*cp == '\r') || isspace (*cp);
			     cp--)
				*cp = 0;
		for (cp = line; isspace (*cp); cp++);
		if (*cp == '#')
			continue;
		if (!strlen (cp))
			continue;

		if ((sscanf (cp, "%s %n", keyword, &n) != 1))
			continue;

		data = &cp[n];

		if ((k =
		     bsearch (keyword, keywords, nkeywords,
			      sizeof (struct keyword), keycmp)) == NULL) {
			fprintf (stderr, "Line %d: unknown keyword '%s'.\n",
				 num, keyword);
			exit (1);
		}

		switch (k->code) {
		case CODE_PLUGIN:
			if (!first) {
				check (&p);
				addtolist (&p);
				fflush (stdout);
			}
			first = 0;
			memset (&p, 0, sizeof (p));
			if (sscanf (data, "%s", tmp) != 1) {
				fprintf (stderr,
					 "Line %d: bad format for 'plugin'.\n",
					 num);
				exit (1);
			} else if (pluginexists (tmp)) {
				fprintf (stderr,
					 "Line %d: duplicate plugin '%s'.\n",
					 num, tmp);
				exit (1);
			} else {
				int     i;

				for (i = 0; tmp[i]; i++)
					tmp[i] = toupper (tmp[i]);
			}
			strncpy (p.keyword, tmp, sizeof (p.keyword));
			p.keyword[sizeof (p.keyword) - 1] = 0;
			break;

		case CODE_DESCR:
			{
				int     n;

				for (n = 0; n < ML && (p.descr[n][0] != 0);
				     n++);
				if (n >= ML) {
					fprintf (stderr,
						 "Line %d: more than %d 'descr' lines in this def.\n",
						 num, ML);
					exit (1);
				} else {
					strncpy (p.descr[n], data, 64);
					p.descr[n][63] = 0;
				}
			}
			break;

		case CODE_EXEC:
			strncpy (p.exec, data, sizeof (p.exec));
			p.exec[sizeof (p.exec) - 1] = 0;
			break;

		case CODE_KEY:
			if (sscanf (data, "%d", &p.key) != 1) {
				fprintf (stderr,
					 "Line %d: bad format for 'key'.\n",
					 num);
				exit (1);
			} else if (p.key < 0 || p.key > 129) {
				fprintf (stderr,
					 "Line %d: key must be 0-129.\n", num);
				exit (1);
			}
			break;
		}
	}

	fclose (fin);

	check (&p);
	addtolist (&p);

	printf ("Sorting.\n\n");
	qsort (plugins, numplugins, sizeof (struct plugin), plugincmp);

	for (i = 0; i < numplugins; i++) {
		printf ("KEYWORD          KEY  EXEC\n");
		printf
		    ("--------------------------------------------------------------\n");
		printf ("%-15s  %3d  %s\n", plugins[i].keyword, plugins[i].key,
			plugins[i].exec);
	}

	printf ("\n%s is %d line(s) long and defines %d plugins(s).\n\n",
		mkfname (TELEPISRCFILE), num, numplugins);

	printf ("Writing compiled file to %s\n", mkfname (TELEPLUGINFILE));

	fwrite (&numplugins, sizeof (int), 1, fout);
	fwrite (plugins, sizeof (struct plugin), numplugins, fout);
	fclose (fout);

	exit (0);
}


/* End of File */
