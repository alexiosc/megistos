/*****************************************************************************\
 **                                                                         **
 **  FILE:     mkxlation.c                                                  **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, November 97                                               **
 **  PURPOSE:  Compiles and creates binary translation table.               **
 **  NOTES:    Files: /usr/local/bbs/etc/xlation/xlation.[0-9]              **
 **                                                                         **
 **            Format: each file represents one of ten translation table.   **
 **            The existence of each file is optional (though at least one  **
 **            must exist).                                                 **
 **                                                                         **
 **            Each file contains 256 ASCII codes, either as single char-   **
 **            acters, or two-digit hexadecimal numbers. ASCII codes are    **
 **            separated by white space. This implies that white space      **
 **            cannot be specified here, hence hex ASCII codes should be    **
 **            used. The special character '#' designates the rest of the   **
 **            line to be a comment. To specify '#', write its hex ASCII    **
 **            number, 23. The special value of '00' means 'don't trans-    **
 **            late that character' (transparancy).                         **
 **                                                                         **
 **            The way it works: if a character with ASCII value n is       **
 **            to be translated, we look up the (n+1)th character in the    **
 **            table and output the value found there. So, to translate     **
 **            'A' into 'Q', we'd write Q as the 66th ASCII code ('A' is    **
 **            65).                                                         **
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
 * Revision 1.4  2003/12/23 08:14:06  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:08  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.4  1998/12/27 16:39:15  alexios
 * Added autoconf support.
 *
 * Revision 1.3  1998/07/24 10:32:46  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 1.2  1997/11/06 20:19:38  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 1.1  1997/11/03 00:46:03  alexios
 * Added note asking user to cause instances of emud to reload
 * the translation tables from disk. Changed xlate into a two-
 * dimensional array for ease of handling.
 *
 * Revision 1.0  1997/11/02 11:14:39  alexios
 * Initial revision
 *
 *
 */


static const char rcsinfo[] = "$Id$";



#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_UNISTD_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>

#include <megistos/mbk_sysvar.h>


char    xlate[NUMXLATIONS][256];
char    kbdxlate[NUMXLATIONS][256];


void
parse (int n, int kbd)
{
	FILE   *fp;
	char   *fname, line[1024], *cp;
	int     i = 0;
	int     errors = 0;

	if (kbd)
		fname = mkfname (XLATIONDIR "/" KBDXLATIONSRC, n);
	else
		fname = mkfname (XLATIONDIR "/" XLATIONSRC, n);

	if ((fp = fopen (fname, "r")) == NULL) {
		fprintf (stderr,
			 "%s: cannot open (one-to-one mapping assumed).\n",
			 fname);
		for (i = 0; i < 256; i++)
			xlate[n][i] = i;
		return;
	}

	fprintf (stderr, "%s: Reading...\n", fname);

	while (!feof (fp)) {
		if (!fgets (line, sizeof (line), fp))
			break;
		if ((cp = strchr (line, '#')) != NULL)
			*cp = 0;
		for (cp = strtok (line, " \n\r\t"); cp;
		     cp = strtok (NULL, " \n\r\t")) {
			if (strlen (cp) > 2) {
				fprintf (stderr,
					 "  Syntax error for ASCII %d (0x%x,0%o): `%s'\n",
					 i, i, i, cp);
				errors++;
			} else if (strlen (cp) == 1) {
				if (kbd) {
					if (i < 256)
						kbdxlate[n][i] =
						    (*cp) ? *cp : i;
				} else {
					if (i < 256)
						xlate[n][i] = (*cp) ? *cp : i;
				}
				i++;
			} else {
				if (isxdigit (*cp) && isxdigit (*(cp + 1))) {
					int     c;

					sscanf (cp, "%x", &c);
					if (kbd) {
						if (i < 256)
							kbdxlate[n][i] =
							    c ? (c & 0xff) : i;
					} else {
						if (i < 256)
							xlate[n][i] =
							    c ? (c & 0xff) : i;
					}
					i++;
				} else {
					fprintf (stderr,
						 "  Syntax error for ASCII %d (0x%x,0%o): `%s'\n",
						 i, i, i, cp);
				}
			}
		}
	}

	fclose (fp);

	if (errors) {
		fprintf (stderr,
			 "  %d errors detected. Please check the file.\n",
			 errors);
		exit (1);
	} else if (i != 256) {
		fprintf (stderr,
			 "  %d characters specified (was expecting 256)\n", i);
	}
	fprintf (stderr, "  Ok.\n");
}


int
main (int argc, char **argv)
{
	int     i, j;
	FILE   *fp;

	mod_setprogname (argv[0]);
	for (i = 0; i < NUMXLATIONS; i++)
		for (j = 0; j < 256; j++)
			xlate[i][j] = kbdxlate[i][j] = j;

	for (i = 0; i < NUMXLATIONS; i++)
		parse (i, 0);	/* Output mapping */
	for (i = 0; i < NUMXLATIONS; i++)
		parse (i, 1);	/* Keyboard (inp_buffer) mapping */

	if ((fp = fopen (mkfname (XLATIONFILE "~"), "w")) == NULL) {
		fprintf (stderr, "Unable to open %s for writing!\n",
			 mkfname (XLATIONFILE "~"));
		exit (1);
	}

	if (fwrite (xlate, sizeof (xlate), 1, fp) != 1) {
		int     i = errno;

		fprintf (stderr, "Unable to write to %s! (errno=%d)\n",
			 mkfname (XLATIONFILE "~"), i);
		exit (1);
	}

	if (fwrite (kbdxlate, sizeof (kbdxlate), 1, fp) != 1) {
		int     i = errno;

		fprintf (stderr, "Unable to write to %s! (errno=%d)\n",
			 mkfname (XLATIONFILE "~"), i);
		exit (1);
	}

	fclose (fp);
	{
		char    old[2048];

		strcpy (old, mkfname (XLATIONFILE "~"));
		rename (old, mkfname (XLATIONFILE));
	}
	chmod (mkfname (XLATIONFILE), 0660);

	fprintf (stderr, "Tables compiled.\n");
	fprintf (stderr,
		 "NB: if you want your changes to take effect immediately,\n");
	fprintf (stderr,
		 "    consider saying: su -c \"killall -SIGUSR1 emud\"\n");
	fprintf (stderr,
		 "    This will cause any emu daemons running to reload the\n");
	fprintf (stderr, "    translation table from disk.\n");

	return 0;
}


/* End of File */
