/*****************************************************************************\
 **                                                                         **
 **  FILE:     stats.c                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, March 95                                                  **
 **  PURPOSE:  Manage statistical files and draw graphs and things          **
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
 * Revision 1.5  2003/12/27 12:29:39  alexios
 * Adjusted #includes.
 *
 * Revision 1.4  2003/12/24 20:12:09  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.5  1998/12/27 16:09:37  alexios
 * Added autoconf support.
 *
 * Revision 0.4  1998/07/24 10:24:24  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.3  1997/11/06 20:05:23  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/09/12 13:28:38  alexios
 * Fixed time displays that caused the stats frames to go out of
 * alignment.
 *
 * Revision 0.1  1997/08/28 11:07:38  alexios
 * First registered revision. Adequate.
 *
 *
 */


static const char rcsinfo[] =
    "$Id$";



#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_UNISTD_H 1
#define WANT_CTYPE_H 1
#define WANT_STRINGS_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_STAT_H 1
#define WANT_TIME_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "mbk_stats.h"
#include "stats.h"


int     dayssince = 1;
char    oldstatsdir[256];
char    everdir[256];
promptblock_t *msg;

char   *statfiles[] =
    { "baudstats", "clsstats", "daystats", "modstats", "ttystats" };


void
drawgraph (int type1, int type2, int type3, int type4)
{
	char    s[256], fname[256], temp[256], label[256], bc, hbc;
	FILE   *fp;
	int     numdays = 1, field[3], i, line = 0, barlen, init = 0;
	int     grwid0, grwid, max = 0, numlen = 0, pass, total = 0;
	struct stat st;
	struct tm *tm;

	if (getenv ("USERID") && strcmp ("", getenv ("USERID")))
		init = INI_ALL;
	else
		init =
		    INI_TTYNUM | INI_OUTPUT | INI_SYSVARS | INI_ERRMSGS |
		    INI_CLASSES;
	mod_init (init);

	msg = msg_open ("stats");
	grwid0 = msg_int (GRWID, 40, 256);
	bc = msg_char (BARCHR);
	hbc = msg_char (HLFCHR);

	strcpy (fname, mkfname (STATDIR));
	strcat (fname, "/");
	switch (type4) {
	case FORTODAY:
		sprintf (temp, "%s", statfiles[type3]);
		break;
	case THISMONTH:
		sprintf (temp, "%ld/%s.month-%02ld", tdyear (today ()),
			 statfiles[type3], tdmonth (today ()) + 1);
		break;
	case THISYEAR:
		sprintf (temp, "%ld/%s", tdyear (today ()), statfiles[type3]);
		break;
	case FOREVER:
		sprintf (temp, "EVER/%s", statfiles[type3]);
		break;
	}
	strcat (fname, temp);

	if ((fp = fopen (fname, "r")) == NULL) {
		prompt (CNTOPN);
		return;
	}

	strcpy (s, msg_get (type3 + BAUD));
	strcat (s, ": ");
	strcat (s, msg_get (AVGCRD + type1 * 3 + type2));
	strcat (s, " ");
	strcat (s, msg_get (type4 + TODAY));
	prompt (HEADER, s);
	prompt (TOP);

	for (pass = 0; pass < 2; pass++) {
		if (type4 != FORTODAY) {
			fscanf (fp, "%d\n", &numdays);
			if (!numdays)
				numdays = 1;
		}

		line = 0;
		while (!feof (fp)) {

			memset (&field, 0, sizeof (field));
			grwid = grwid0;
			label[0] = 0;
			switch (type3) {
			case BAUDSTATS:
				if (fscanf
				    (fp, "%d %d %d %d\n", &i, &field[0],
				     &field[1], &field[2]) == 4) {
					if (pass) {
						sprintf (label, "%6s",
							 channel_baudstg (i));
						grwid -= 6;
					}
				}
				break;
			case CLSSTATS:
				if (fscanf
				    (fp, "%s %d %d\n", temp, &field[0],
				     &field[1]) == 3) {
					if (pass) {
						sprintf (label, "%9s", temp);
						grwid -= 9;
					}
				}
				break;
			case DAYSTATS:
				if (fscanf
				    (fp, "%d %d\n", &field[0],
				     &field[1]) == 2) {
					if (pass) {
						sprintf (label, "%02d", line);
						grwid -= 2;
					}
				}
				break;
			case MODSTATS:
				{
					char    lin[256], *cp;
					int     len, ptr;

					if (!fgets (lin, sizeof (lin), fp))
						continue;
					if (!sscanf (lin, "%d %n", &len, &ptr))
						continue;
					cp = &lin[ptr];
					cp[len] = 0;
					if (pass) {
						strncpy (temp, cp,
							 sizeof (temp));
						temp[16] = 0;
					}
					cp += len + 1;

					if (sscanf
					    (cp, "%d %d\n", &field[0],
					     &field[1]) == 2) {
						if (pass) {
							sprintf (label,
								 "%-16s",
								 temp);
							grwid -= 16;
						}
					}
				}
				break;
			case TTYSTATS:
				if (fscanf
				    (fp, "%s %x %d %d %d\n", temp, &i,
				     &field[0], &field[1], &field[2]) == 5) {
					if (pass) {
						sprintf (label, "%03x", i);
						grwid -= 3;
					}
				}
				break;
			}
			line++;

			barlen = field[type2];
			if (!pass) {
				if (type1 == AVERAGE)
					barlen /= numdays;
				if (barlen > max)
					max = barlen;
			} else {
				if (type1 == AVERAGE)
					barlen /= numdays;
				grwid -= (numlen + 1);
				barlen *= grwid * 2;
				barlen /= max;

				prompt (GRLABEL, label);

				memset (temp, bc, (i = barlen / 2));
				temp[i] = 0;
				if (barlen % 2) {
					temp[(i = strlen (temp))] = hbc;
					temp[i + 1] = 0;
				}
				sprintf (label, "%s", temp);
				prompt (GRBAR, label);
				sprintf (s, "%%-%dd",
					 numlen + grwid - strlen (temp));
				total += field[type2];
				if (type1 == AVERAGE)
					field[type2] /= numdays;
				sprintf (label, s, field[type2]);
				prompt (GRNUM, label);
			}
		}
		if (!max)
			max = 1;
		sprintf (temp, "%d", max);
		numlen = strlen (temp);
		rewind (fp);
	}

	fclose (fp);
	prompt (BOTTOM);

	memset (&st, 0, sizeof (st));
	stat (fname, &st);
	tm = localtime (&st.st_mtime);
	if (!line)
		line = 1;
	prompt (type1 == AVERAGE ? FTRAVG : FTRTOT,
		strdate (makedate
			 (tm->tm_mday, tm->tm_mon + 1, 1900 + tm->tm_year)),
		strtime (maketime (tm->tm_hour, tm->tm_min, tm->tm_sec), 1),
		(type1 == AVERAGE ? (total / line) : total));
	prompt (FTREND);
}


void
demographics ()
{
	FILE   *fp;
	int     i, init = 0;
	struct stat st;
	struct tm *tm;
	int     langstats[NUMLANGUAGES] = { 0 };
	int     ANSIstats = 0;
	int     visualstats = 0;
	int     malestats = 0;
	int     corpstats = 0;
	int     sysaxstats = 0;
	int     suspstats = 0;
	int     exemptstats = 0;
	int     ages[6][9];

	memset (&ages, 0, sizeof (ages));

	if (getenv ("USERID") && strcmp ("", getenv ("USERID")))
		init = INI_ALL;
	else
		init =
		    INI_TTYNUM | INI_OUTPUT | INI_SYSVARS | INI_ERRMSGS |
		    INI_CLASSES;
	mod_init (init);

	stat (mkfname (DEMOSTATFILE), &st);
	tm = localtime (&st.st_mtime);

	if ((fp = fopen (mkfname (DEMOSTATFILE), "r")) != NULL) {
		int     i, j;

		for (i = 0; i < NUMLANGUAGES; i++)
			fscanf (fp, "%d\n", &langstats[i]);
		fscanf (fp, "%d\n", &ANSIstats);
		fscanf (fp, "%d\n", &visualstats);
		fscanf (fp, "%d\n", &malestats);
		fscanf (fp, "%d\n", &corpstats);
		fscanf (fp, "%d\n", &sysaxstats);
		fscanf (fp, "%d\n", &suspstats);
		fscanf (fp, "%d\n", &exemptstats);
		for (j = 0; j < 8; j++) {
			for (i = 0; i < 5; i++) {
				fscanf (fp, "%5d ", &ages[i][j]);
				ages[5][j] += ages[i][j];
				ages[i][8] += ages[i][j];
			}
			fscanf (fp, "\n");
		}
	}
	fclose (fp);
	for (i = 0; i < 5; i++)
		ages[5][8] += ages[i][8];

	msg = msg_open ("stats");
	prompt (AGESTATS,
		strdate (makedate
			 (tm->tm_mday, tm->tm_mon, 1900 + tm->tm_year)),
		strtime (maketime (tm->tm_hour, tm->tm_min, tm->tm_sec), 1),
		ages[0][0], ages[1][0], ages[2][0], ages[3][0], ages[4][0],
		ages[5][0], ages[0][1], ages[1][1], ages[2][1], ages[3][1],
		ages[4][1], ages[5][1], ages[0][2], ages[1][2], ages[2][2],
		ages[3][2], ages[4][2], ages[5][2], ages[0][3], ages[1][3],
		ages[2][3], ages[3][3], ages[4][3], ages[5][3], ages[0][4],
		ages[1][4], ages[2][4], ages[3][4], ages[4][4], ages[5][4],
		ages[0][5], ages[1][5], ages[2][5], ages[3][5], ages[4][5],
		ages[5][5], ages[0][6], ages[1][6], ages[2][6], ages[3][6],
		ages[4][6], ages[5][6], ages[0][7], ages[1][7], ages[2][7],
		ages[3][7], ages[4][7], ages[5][7], ages[0][8], ages[1][8],
		ages[2][8], ages[3][8], ages[4][8], ages[5][8], malestats,
		ANSIstats, visualstats, corpstats, suspstats, exemptstats,
		sysaxstats, langstats[0], langstats[1], langstats[2],
		langstats[3], langstats[4], langstats[5], langstats[6],
		langstats[7], langstats[8], langstats[9]);
}


void
syntax ()
{
	fprintf (stderr, "stats: syntax:\n\n");
	fprintf (stderr, "       -cleanup: regenerate statistics\n");
	fprintf (stderr,
		 "       -[ta][cml][bcdmt][dmye]: Create a graph, as follows:\n");
	fprintf (stderr, "         1. t: Total\n");
	fprintf (stderr, "            a: Average\n");
	fprintf (stderr, "         2. c: Credits\n");
	fprintf (stderr, "            m: Minutes\n");
	fprintf (stderr, "            l: Calls\n");
	fprintf (stderr, "         3. b: BAUD stats\n");
	fprintf (stderr, "            c: Class stats\n");
	fprintf (stderr, "            d: Day (usage) stats\n");
	fprintf (stderr, "            m: Module stats\n");
	fprintf (stderr, "            t: TTY (channel) stats\n");
	fprintf (stderr, "         4. d: Today\n");
	fprintf (stderr, "            m: This month\n");
	fprintf (stderr, "            y: This year\n");
	fprintf (stderr, "            e: Ever\n\n");
	fprintf (stderr,
		 "         eg: -tcbm = BAUD stats: total credits consumed this month\n\n");
	exit (1);
}


int
main (int argc, char **argv)
{
	mod_setprogname (argv[0]);
	if (argc == 2 && !strcmp (argv[1], "-cleanup")) {
		init ();
		getstats ();
		done ();
	} else if (argc == 2 && !strcmp (argv[1], "-demog")) {
		demographics ();
	} else if (argc != 2) {
		syntax ();
	} else {
		char   *cp = argv[1] + 1;
		int     type1 = 0, type2 = 0, type3 = 0, type4 = 0;

		switch (*cp) {
		case 't':
			type1 = TOTAL;
			break;
		case 'a':
			type1 = AVERAGE;
			break;
		default:
			syntax ();
		}
		cp++;
		switch (*cp) {
		case 'c':
			type2 = CREDITS;
			break;
		case 'm':
			type2 = MINUTES;
			break;
		case 'l':
			type2 = CALLS;
			break;
		default:
			syntax ();
		}
		cp++;
		switch (*cp) {
		case 'b':
			type3 = BAUDSTATS;
			break;
		case 'c':
			type3 = CLSSTATS;
			break;
		case 'd':
			type3 = DAYSTATS;
			break;
		case 'm':
			type3 = MODSTATS;
			break;
		case 't':
			type3 = TTYSTATS;
			break;
		default:
			syntax ();
		}
		cp++;
		switch (*cp) {
		case 'd':
			type4 = FORTODAY;
			break;
		case 'm':
			type4 = THISMONTH;
			break;
		case 'y':
			type4 = THISYEAR;
			break;
		case 'e':
			type4 = FOREVER;
			break;
		default:
			syntax ();
		}

		if ((type3 != BAUDSTATS && type3 != TTYSTATS) &&
		    type2 == CALLS) {
			fprintf (stderr,
				 "statd: Impossible combination\n       (only baud- and ttystats provide CALL counts).\n");
			exit (1);
		}

		drawgraph (type1, type2, type3, type4);
	}

	return 0;
}


/* End of File */
