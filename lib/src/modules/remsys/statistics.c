/*****************************************************************************\
 **                                                                         **
 **  FILE:     statistics.c                                                 **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, April 95                                                  **
 **  PURPOSE:  Statistics for the remote sysop menu                         **
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
 * Revision 1.5  2003/12/24 21:53:06  alexios
 * Fixed #includes.
 *
 * Revision 1.4  2003/12/24 20:12:09  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.6  1999/08/07 02:18:29  alexios
 * Slight optimisation in calling df(1) in rsys_linstats().
 *
 * Revision 0.5  1998/12/27 16:07:28  alexios
 * Added autoconf support.
 *
 * Revision 0.4  1998/07/24 10:23:31  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.3  1997/11/06 20:05:18  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/09/12 13:24:18  alexios
 * Fixed swap space display. Updated RAM display to be more
 * Linux-2.x like by including separate Buffers and Cache
 * columns. Added colour-coding to the disk space part of
 * rsys_linstats() so that disks will appear yellow and then
 * red as their disk space decreases. Rsys_linstats() now
 * produces a line of totals (disk space, space taken, space
 * free).
 *
 * Revision 0.1  1997/08/28 11:05:52  alexios
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
#define WANT_STRING_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "remsys.h"

#include <mbk/mbk_sysvar.h>
#undef CRDSING
#undef CRDPLUR
#include "mbk_remsys.h"



void
rsys_agestats ()
{
	char    command[256];

	sprintf (command, "%s -demog", mkfname (STATSBIN));
	system (command);
}


void
rsys_clsstats ()
{
	char    fname[256];
	struct stat st;
	FILE   *fp;
	classrec_t *class;
	int     dummy;

	sprintf (fname, "%s/EVER/clsstats", mkfname (STATDIR));
	if (stat (fname, &st)) {
		sprintf (fname, "%s/%ld/clsstats", mkfname (STATDIR),
			 tdyear (today ()));
		if (stat (fname, &st)) {
			prompt (RSCLSSTR);
			return;
		}
	}

	if ((fp = fopen (fname, "r")) == NULL) {
		prompt (RSCLSSTR);
		return;
	}

	inp_nonblock ();

	prompt (RSCLSST1);

	fscanf (fp, "%d\n", &dummy);
	while (!feof (fp)) {
		char    name[80], c;
		int     creds, mins;

		if (read (0, &c, 1))
			if (c == 13 || c == 10 || c == 27 || c == 15 || c == 3)
				break;
		if (fmt_lastresult == PAUSE_QUIT)
			break;

		if (fscanf (fp, "%s %d %d\n", name, &creds, &mins) == 3) {
			if ((class = cls_find (name)) != NULL) {
				prompt (RSCLSST2, name, class->users, creds,
					mins);
			}
		}
	}
	fclose (fp);
	prompt (RSCLSST3);
	inp_block ();
}


void
rsys_modstats ()
{
	char    fname[256];
	struct stat st;
	FILE   *fp;
	int     dummy, pass;
	int     tcreds = 0, tmins = 0;

	sprintf (fname, "%s/EVER/modstats", mkfname (STATDIR));
	if (stat (fname, &st)) {
		sprintf (fname, "%s/%ld/modstats", mkfname (STATDIR),
			 tdyear (today ()));
		if (stat (fname, &st)) {
			prompt (RSMODSTR);
			return;
		}
	}

	if ((fp = fopen (fname, "r")) == NULL) {
		prompt (RSMODSTR);
		return;
	}

	inp_nonblock ();

	prompt (RSMODST1);

	for (pass = 0; pass < 2; pass++) {
		fscanf (fp, "%d\n", &dummy);
		while (!feof (fp)) {
			char    lin[1024], *cp, name[80], c;
			int     creds, mins, ptr, len;

			if (read (0, &c, 1))
				if (c == 13 || c == 10 || c == 27 || c == 15 ||
				    c == 3)
					break;
			if (fmt_lastresult == PAUSE_QUIT)
				break;

			if (!fgets (lin, sizeof (lin), fp))
				continue;
			if (!sscanf (lin, "%d %n", &len, &ptr))
				continue;
			cp = &lin[ptr];
			cp[len] = 0;
			if (pass)
				strncpy (name, cp, sizeof (name));
			cp += len + 1;

			if (sscanf (cp, "%d %d\n", &creds, &mins) == 2) {
				if (!pass) {
					tcreds += creds;
					tmins += mins;
				} else {
					prompt (RSMODST2, name,
						creds,
						(float) (100.0 *
							 (float) ((float) creds
								  /
								  (float)
								  tcreds)),
						mins,
						(float) (100.0 *
							 (float) ((float) mins
								  /
								  (float)
								  tmins)));
				}
			}
		}

		rewind (fp);
	}
	fclose (fp);
	prompt (RSMODST3);

	inp_block ();
}


void
rsys_systats ()
{
	prompt (RSSYSTATS,
		chan_count,
		sysvar->tcreds, sysvar->tcredspaid, sysvar->timever,
		sysvar->connections, sysvar->filesupl, sysvar->bytesupl / 10,
		sysvar->filesdnl, sysvar->bytesdnl / 10, sysvar->sigmessages,
		sysvar->clubmsgslive, sysvar->emessages, sysvar->emsgslive,
		sysvar->nmessages, sysvar->incnetmsgs);
}


void
rsys_linstats ()
{
	char   *cp;
	FILE   *fp;
	char    hostname[256] = { 0 };
	char    version[256] = { 0 };
	char    cpu[80] = { 0 }, cpu_vendor[80] = {
	0}, bogomips[80] = {
	0};
	int     uptime;
	char    load[80] = { 0 };
	int     m[9];


	if ((fp = popen ("hostname", "r")) == NULL) {
		pclose (fp);
		return;
	}
	fgets (hostname, sizeof (hostname), fp);
	if ((cp = strchr (hostname, '\n')) != NULL)
		*cp = 0;
	pclose (fp);


	if ((fp = fopen (PROCDIR "/version", "r")) == NULL) {
		fclose (fp);
		return;
	}
	fgets (version, sizeof (version), fp);
	if ((cp = strchr (version, '\n')) != NULL)
		*cp = 0;
	fclose (fp);


	if ((fp = fopen (PROCDIR "/cpuinfo", "r")) == NULL) {
		fclose (fp);
		return;
	}
	while (!feof (fp)) {
		int     n;
		char    label[80], *data;
		char    line[256];

		fgets (line, sizeof (line), fp);
		if ((data = strchr (line, '\n')) != NULL)
			*data = 0;
		if (sscanf (line, "%s : %n\n", label, &n) == 1) {
			data = &line[n];
			if (sameas ("MODEL", label))
				strcpy (cpu, data);
			else if (sameas ("VENDOR_ID", label))
				strcpy (cpu_vendor, data);
			else if (sameas ("BOGOMIPS", label))
				strcpy (bogomips, data);
		}
	}
	fclose (fp);


	if ((fp = fopen (PROCDIR "/uptime", "r")) == NULL) {
		fclose (fp);
		return;
	} else {
		int     d1, d2, d3;

		fscanf (fp, "%d.%d %d.%d\n", &uptime, &d1, &d2, &d3);
	}
	fclose (fp);


	if ((fp = fopen (PROCDIR "/loadavg", "r")) == NULL) {
		fclose (fp);
		return;
	}
	fgets (load, sizeof (load), fp);
	if ((cp = strchr (load, ' ')) != NULL)
		*cp = 0;
	fclose (fp);


	bzero (m, sizeof (m));
	if ((fp = fopen (PROCDIR "/meminfo", "r")) == NULL) {
		fclose (fp);
		return;
	} else {
		char    dummy[80];
		int     i;

		fgets (dummy, sizeof (dummy), fp);
		fscanf (fp, "%*s %d %d %d %d %d %d %*s %d %d %d\n",
			&m[0], &m[1], &m[2], &m[3], &m[4], &m[5], &m[6], &m[7],
			&m[8]);
		for (i = 0; i < 9; i++)
			m[i] >>= 10;
	}
	fclose (fp);


	prompt (RSLINST1, hostname, version, cpu_vendor, cpu, bogomips,
		uptime / 3600, (uptime % 3600) / 60, uptime % 60,
		load, m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7], m[8]);

	prompt (RSLINSTW);


	if ((fp = popen ("exec df 2>/dev/null", "r")) == NULL) {
		pclose (fp);
		return;
	} else {
		char    dummy[1024];
		unsigned long int s1 = 0, s2 = 0, s3 = 0;

		inp_nonblock ();

		fgets (dummy, sizeof (dummy), fp);
		prompt (RSLINST2);
		while (!feof (fp)) {
			unsigned long d1, d2, d3, perc;
			char    dev[256], mp[256], c;

			if (read (0, &c, 1))
				if (c == 13 || c == 10 || c == 27 || c == 15 ||
				    c == 3)
					break;
			if (fmt_lastresult == PAUSE_QUIT)
				break;

			if (fscanf
			    (fp, "%s %ld %ld %ld %*s %s\n", dev, &d1, &d2, &d3,
			     mp) == 5) {
				if (d1)
					perc = d2 * 100 / d1;
				else
					perc = 0;
				if (perc >= dfcrit)
					strcpy (dummy, msg_get (RSLINST7));
				else if (perc >= dfwarn)
					strcpy (dummy, msg_get (RSLINST6));
				else
					strcpy (dummy, msg_get (RSLINST5));
				s1 += d1;
				s2 += d2;
				s3 += d3;
				prompt (RSLINST3, dummy, dev, dummy, d1, dummy,
					d2, dummy, d3, dummy, mp);
			}
		}
		inp_block ();
		if (feof (fp))
			prompt (RSLINST4, s1, s2, s3);
		pclose (fp);
	}
}


void
rsys_genstats ()
{
	char    opts[5] = { 0 }, command[256];
	int     state = 0, i;

	for (;;) {
		switch (state) {
		case 0:
			if (!get_menu
			    (&opts[0], 1, 0, RSGENST1, 0, "TA", 0, 0))
				return;
			else
				state = 1;
			break;
		case 1:
			if (!get_menu
			    (&opts[1], 1, 0, RSGENST2, 0, "CML", 0, 0))
				state = 0;
			else
				state = 2;
			break;
		case 2:
			if (!get_menu
			    (&opts[2], 1, 0, RSGENST3, 0, "BCDMT", 0, 0))
				state = 1;
			else if (!strchr ("BT", opts[2]) && opts[1] == 'L') {
				prompt (RSGENSTR);
				cnc_end ();
			} else
				state = 3;
			break;
		case 3:
			if (!get_menu
			    (&opts[3], 1, 0, RSGENST4, 0, "DMYE", 0, 0))
				state = 2;
			else
				state = 4;
		}
		if (state == 4)
			break;
	}
	for (i = 0; i < 4; i++)
		opts[i] = tolower (opts[i]);
	sprintf (command, "%s -%s", mkfname (STATSBIN), opts);
	print ("\n");
	system (command);
}


void
rsys_top ()
{
	char   *fnames[] = {

		/* user top charts */

		"top-numconnections",
		"top-oldestsignups",
		"top-credits",
		"top-paidcreds",
		"top-credsspend",
		"top-timespent",
		"top-msgswritten",
		"top-filesupl",
		"top-bytesupl",
		"top-filesdnl",
		"top-bytesdnl",

		/* club top charts */

		"top-club-messages",
		"top-club-files",
		"top-club-bulletins",
		"top-club-readings",
		"top-club-downloads",

		"end"
	};

	char    fname[256], s[256], opts[64];
	FILE   *fp;
	int     i;
	int     opt;
	char    c;
	int     count;

	for (count = 0; strcmp (fnames[count], "end"); count++);

	strcpy (opts, "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
	opts[count] = 0;

	if (!get_menu (&c, 1, RSTOPSM, RSTOPSS, 0, opts, 0, 0))
		return;
	opt = c;

	if (isalpha (opt))
		opt -= 'A';
	else if (isdigit (opt))
		opt = opt - '0' + 26;

	sprintf (fname, "%s/%s", mkfname (STATDIR), fnames[opt]);
	if ((fp = fopen (fname, "r")) == NULL) {
		fclose (fp);
		return;
	}

	inp_nonblock ();

	strcpy (s, msg_get (RSTOPSTA + opt));
	prompt (RSTOPS1, s);

	i = 1;
	while (!feof (fp)) {
		char    value[20], userid[25], c;

		if (read (0, &c, 1))
			if (c == 13 || c == 10 || c == 27 || c == 15 || c == 3)
				break;
		if (fmt_lastresult == PAUSE_QUIT)
			break;

		if (fscanf (fp, "%s %s", value, userid) == 2) {
			prompt (RSTOPS2, i, value, userid);
			i++;
		}
	}
	if (feof (fp))
		prompt (RSTOPS3);
	fclose (fp);
	inp_block ();
}



/* End of File */
