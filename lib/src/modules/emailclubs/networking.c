/*****************************************************************************\
 **                                                                         **
 **  FILE:     networking.c                                                 **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: July 1999                                                    **
 **  PURPOSE:  Controlling the distribution of club messsages over a net.   **
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
 * Revision 1.5  2003/12/25 13:33:28  alexios
 * Fixed #includes. Changed instances of struct message to
 * message_t. Other minor changes.
 *
 * Revision 1.4  2003/12/24 20:12:13  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.2  2000/01/06 11:41:02  alexios
 * Small bug fixes.
 *
 * Revision 1.1  1999/07/28 23:11:36  alexios
 * rsysselect() now skips files ending in a tilde (~), so as
 * to ignore any backup files after editing the import specs.
 *
 * Revision 1.0  1999/07/18 21:20:51  alexios
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
#define WANT_DIRENT_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#ifdef HAVE_METABBS

#include <megistos/bbs.h>
#include "mbk_emailclubs.h"
#include "email.h"
#include "clubs.h">



static int
rsysselect (const struct dirent *d)
{
	if (d->d_name[strlen (d->d_name) - 1] == '~')
		return 0;
	return d->d_name[0] != '.';
}


static void
list_import_points ()
{
	FILE   *fp;
	struct dirent **systems;
	char    fname[512];
	int     n, i, numexp, delta = 0;

	prompt (DIPLSTH);
	n = scandir (mkfname (MSGSDIR "/..netimport"), &systems, rsysselect,
		     alphasort);
	for (i = 0; i < n; free (systems[i]), i++) {
		char   *cp = systems[i]->d_name;

		sprintf (fname, mkfname (MSGSDIR "/..netimport/%s", cp));
		if ((fp = fopen (fname, "r")) == NULL) {
			error_logsys ("Unable to open %s", fname);
			continue;
		}

		numexp = 0;
		while (!feof (fp)) {
			char    line[512], key[512];
			int     x;

			if (!fgets (line, sizeof (line), fp))
				break;
			if (sscanf (line, "%s %d", key, &x) == 2) {
				if (sameas (key, "delta:"))
					delta = x;
			} else if (sscanf (line, "%s %*s %*s", key) == 1) {
				if (sameas (key, "import:"))
					numexp++;
			}
		}
		fclose (fp);

		{
			int     mi, hi, di;
			char    m[10], h[10], d[10];

			di = delta / 86400;
			hi = (delta % 86400) / 3600;
			mi = (delta % 3600) / 60;
			sprintf (d, "%d", di);
			sprintf (h, "%d", hi);
			sprintf (m, "%d", mi);
			*(strrchr (cp, ':')) = '/';
			sprintf (fname, "%d", delta);	/* Reusing the fname variable to save space */
			prompt (DIPLSTL, cp, di ? d : "", hi ? h : "",
				mi ? m : "", numexp);
		}
	}
	free (systems);
	prompt (DIPLSTF);
}



static int
getaddr (char *addr, int pr)
{
	int     error;
	char   *s, *slash;

	fmt_lastresult = PAUSE_CONTINUE;
	for (;;) {
		fmt_lastresult = 0;
		if (cnc_more () != 0) {
			if (sameas (cnc_nxtcmd, "X"))
				return 0;
			if (sameas (cnc_nxtcmd, "?")) {
				list_import_points ();
				cnc_end ();
				continue;
			}
			s = cnc_word ();
		} else {
			prompt (pr);
			inp_get (0);
			if (!margc) {
				cnc_end ();
				continue;
			}
			if (inp_isX (margv[0])) {
				return 0;
			}
			if (sameas (margv[0], "?")) {
				list_import_points ();
				cnc_end ();
				continue;
			}
			cnc_begin ();
			s = cnc_word ();
		}

		/* Check the inp_buffer. */

		slash = strchr (s, '/');
		error = (slash == NULL);
		if (slash != NULL) {
			error += (slash == s);
			error += (*(slash + 1) == 0);
			error += (strchr (slash + 1, '/') != NULL);
			error += (!isalnum (*s));
			error += (!isalnum (*(slash + 1)));
		}
		if (error) {
			prompt (DIPADR);
			continue;
		} else {
			char   *cp;

			for (cp = s; *cp != '/'; cp++)
				*cp = tolower (*cp);
			for (cp = slash + 1; *cp; cp++)
				*cp = toupper (*cp);
			strcpy (addr, s);
			return 1;
		}
	}
}


static int
getremclub (char *remclub, int pr)
{
	int     error;
	char   *s, *slash, *club;

	fmt_lastresult = PAUSE_CONTINUE;
	for (;;) {
		fmt_lastresult = 0;
		if (cnc_more () != 0) {
			if (sameas (cnc_nxtcmd, "X"))
				return 0;
			s = cnc_word ();
		} else {
			prompt (pr);
			inp_get (0);
			if (!margc) {
				cnc_end ();
				continue;
			}
			if (inp_isX (margv[0])) {
				return 0;
			}
			cnc_begin ();
			s = cnc_word ();
		}

		/* Check the inp_buffer. */

		slash = strchr (s, '/');
		error = (slash == NULL);
		if (slash != NULL) {
			club = strchr (slash + 1, '/');
			error = (club == NULL);
			if (club != NULL) {
				error += (slash == s);
				error += (club == slash);
				error += (*(slash + 1) == 0);
				error += (*(club + 1) == 0);
				error += (strchr (club + 1, '/') != NULL);
				error += (!isalnum (*s));
				error += (!isalnum (*(slash + 1)));
				error += (!isalnum (*(club + 1)));
			}
		}
		if (error) {
			prompt (IMPCLBR);
			continue;
		} else {
			char   *cp;

			for (cp = s; *cp != '/'; cp++)
				*cp = tolower (*cp);
			for (cp = slash + 1; *cp != '/'; cp++)
				*cp = toupper (*cp);
			strcpy (remclub, s);
			return 1;
		}
	}
}


static int
gettime (int *t, int pr, int def, int defval)
{
	for (;;) {
		if (!get_number (t, pr, 1, 24000, 0, def, defval))
			return 0;
		if (cnc_more ()) {
			switch (tolower (cnc_chr ())) {
			case 'm':
				*t *= 60;
				break;
			case 'h':
				*t *= 3600;
				break;
			default:
				prompt (DIPADTR);
				continue;
			}
		} else
			*t *= 86400;
		break;
	}
	return 1;
}


static int
import_point_exists (char *sys)
{
	char    fname[512];
	struct stat st;

	strcpy (fname, mkfname (MSGSDIR "/..netimport/%s", sys));
	*(strrchr (fname, '/')) = ':';
	return stat (fname, &st) == 0;
}



static void
add_import_point ()
{
	char    addr[256], fname[512], *cp;
	int     delta;
	FILE   *fp;

	for (;;) {
		if (!getaddr (addr, DIPADD))
			return;
		if (import_point_exists (addr))
			prompt (DIPADX, addr);
		else
			break;
	}
	if (!gettime (&delta, DIPADT, 0, 0))
		return;


	if ((cp = strchr (addr, '/')) == NULL) {
		error_fatal ("Address sanity check failed.");
	} else
		*cp = ':';

	strcpy (fname, mkfname (MSGSDIR "/..netimport/%s", addr));
	if ((fp = fopen (fname, "w")) == NULL)
		error_fatalsys ("Unable to create %s", fname);
	fprintf (fp, "delta: %d\nlast-update: %ld\nlast-ihave-time: %ld\n",
		 delta, time (0), time (0));
	fclose (fp);

	*(strrchr (addr, ':')) = '/';
	prompt (DIPADDOK, addr, delta);
}


static void
del_import_point ()
{
	char    addr[256], fname[512], *cp;

	for (;;) {
		if (!getaddr (addr, DIPDEL))
			return;
		if (!import_point_exists (addr))
			prompt (DIPDELX, addr);
		else
			break;
	}

	if ((cp = strchr (addr, '/')) == NULL) {
		error_fatal ("Address sanity check failed.");
	} else
		*cp = ':';

	strcpy (fname, mkfname (MSGSDIR "/..netimport/%s", addr));
	if (unlink (fname) < 0)
		error_fatalsys ("Unable to unlink() %s", fname);

	*(strrchr (addr, ':')) = '/';
	prompt (DIPDELOK, addr);
}


static void
mod_import_point ()
{
	char    addr[256], fname[512], fname2[512], *cp;
	int     delta;
	FILE   *fp, *out;


	/* Get the name of the system to modify */

	for (;;) {
		if (!getaddr (addr, DIPMOD))
			return;
		if (!import_point_exists (addr))
			prompt (DIPMODX, addr);
		else
			break;
	}
	if ((cp = strchr (addr, '/')) == NULL) {
		error_fatal ("Address sanity check failed.");
	} else
		*cp = ':';


	/* Open the file */

	strcpy (fname, mkfname (MSGSDIR "/..netimport/%s", addr));
	*(strrchr (addr, ':')) = '/';
	if ((fp = fopen (fname, "r")) == NULL)
		error_fatalsys ("Unable to open %s", fname);


	/* Read the delta */

	while (!feof (fp)) {
		char    line[512], key[512];
		int     x;

		if (!fgets (line, sizeof (line), fp))
			break;
		if (sscanf (line, "%s %d", key, &x) == 2) {
			if (sameas (key, "delta:"))
				delta = x;
		}
	}


	/* Display the current delta and ask for the new value */

	prompt (DIPMODT, addr, delta / 86400, (delta % 86400) / 3600,
		(delta % 3600) / 60);
	if (!gettime (&delta, 0, DIPMODA, -1)) {
		fclose (fp);
		return;
	}
	if (delta <= 0) {
		fclose (fp);
		return;
	}


	/* Modify the file */
	sprintf (fname2, "%s~", fname);
	if ((out = fopen (fname2, "w")) == NULL)
		error_fatalsys ("Unable to create %s", fname2);
	rewind (fp);
	while (!feof (fp)) {
		char    line[512], key[512];

		if (!fgets (line, sizeof (line), fp))
			break;
		if (sscanf (line, "%s %*d", key) == 1) {
			if (sameas (key, "delta:")) {
				fprintf (out, "delta: %d\n", delta);
				continue;
			}
		}
		fprintf (out, "%s", line);
	}
	fclose (fp);
	fclose (out);

	if (unlink (fname) < 0) {
		unlink (fname2);	/* Hope this works */
		error_fatalsys ("Unable to unlink() %s", fname);
	}
	if (rename (fname2, fname) < 0)
		error_fatalsys ("Unable to rename %s to %s", fname2, fname);

	prompt (DIPMODOK, addr);
}


static void
define_import_point ()
{
	char    opt;
	int     res;

	inp_setflags (INF_HELP);
	for (;;) {
		res = get_menu (&opt, 0, 0, DIPMNU, ERRSEL, "MAD", 0, 0);
		inp_clearflags (INF_HELP);
		if (!res)
			return;
		if (res < 0)
			opt = '?';
		switch (opt) {
		case 'A':
			add_import_point ();
			return;
		case 'D':
			del_import_point ();
			return;
		case 'M':
			mod_import_point ();
			return;
		case '?':
			list_import_points ();
		}
	}
}



static void
import_club ()
{
	FILE   *fp, *out;
	char    remclub[256], addr[256], localclub[16], oldclub[16], *cp;
	char    fname[256], fname2[256];
	int     found = 0;

	for (;;) {
		if (!getremclub (remclub, IMPCLUB))
			return;
		strcpy (addr, remclub);
		if ((cp = strrchr (addr, '/')) == NULL) {
			error_fatal
			    ("Sanity check failed (addr=%s). Nyaaargh nyaaargh!",
			     addr);
		} else
			*cp = 0;
		if (!import_point_exists (addr))
			prompt (IMPCLBS, addr);
		else
			break;
	}

	if (!getclub (localclub, IMPLOCC, IMPLOCR, 1))
		return;


	/* Fine, add this to the import spec */

	*(strrchr (addr, '/')) = ':';
	strcpy (fname, mkfname (MSGSDIR "/..netimport/%s", addr));
	sprintf (fname2, "%s~", fname);
	*(strrchr (addr, ':')) = '/';
	if ((fp = fopen (fname, "r")) == NULL)
		error_fatalsys ("Unable to open %s", fname);
	if ((out = fopen (fname2, "w")) == NULL)
		error_fatalsys ("Unable to create %s", fname2);

	/* Modify the file */
	while (!feof (fp)) {
		char    line[512], key[512], rem[128], loc[128];

		if (!fgets (line, sizeof (line), fp))
			break;
		if (sscanf (line, "%s %s %s", key, rem, loc) == 3) {
			if (sameas (key, "import:")) {
				if (sameas (rem, remclub)) {
					if (!sameas (loc, localclub)) {
						found = 2;
						strcpy (oldclub, loc);
					} else
						found = 1;
					fprintf (out, "import: %s %s\n",
						 remclub, localclub);
					continue;
				}
			}
		}
		fprintf (out, "%s", line);
	}

	if (!found)
		fprintf (out, "import: %s %s\n", remclub, localclub);

	fclose (fp);
	fclose (out);

	if (unlink (fname) < 0) {
		unlink (fname2);	/* Hope this works */
		error_fatalsys ("Unable to unlink() %s", fname);
	}
	if (rename (fname2, fname) < 0)
		error_fatalsys ("Unable to rename %s to %s", fname2, fname);

	if (found != 2)
		prompt (IMPOK, remclub, localclub);
	else
		prompt (IMPDISP, remclub, localclub, oldclub);
}



static void
listexports ()
{
	struct dirent **clubs;
	int     n, i, j, in_accept = 1;
	char    tmp[512], tmp2[512], *cp;

	n = scandir (mkfname (CLUBHDRDIR), &clubs, hdrselect, ncsalphasort);
	prompt (EXPLSTH);
	for (i = 0; i < n; free (clubs[i]), i++) {
		cp = &clubs[i]->d_name[1];
		if (!loadclubhdr (cp))
			continue;
		if (fmt_lastresult == PAUSE_QUIT)
			break;
		if (getclubax (&thisuseracc, cp) == CAX_ZERO)
			continue;
		prompt (EXPLSTL, clubhdr.club);
		strcpy (tmp, clubhdr.export_access_list);

		if (sameas (tmp, "*")) {
			prompt (EXPLSTL3);
		} else if (sameas (tmp, "") || sameas (tmp, "- *")) {
			prompt (EXPLSTL2);
		} else {
			in_accept = 1;
			j = 0;
			tmp2[0] = 0;
			for (cp = strtok (tmp, " "); cp;
			     cp = strtok (NULL, " ")) {
				if (sameas (cp, "-"))
					if (in_accept) {
						in_accept = 0;
						if (j > 0)
							prompt (EXPLSTL4,
								tmp2);
						j = 0;
					}

				if (j > 0)
					strcat (tmp2, " ");
				strcat (tmp2, cp);
				j++;
			}
			if (in_accept)
				prompt (EXPLSTL4, tmp2);
			else if (j > 1)
				prompt (EXPLSTL5, tmp2);
			prompt (EXPLSTL6);
		}
	}
	free (clubs);
	if (fmt_lastresult == PAUSE_QUIT)
		return;
	prompt (EXPLSTF);
}



static int
getexportclub (char *club, int pr, int err)
{
	char   *i;
	char    c;

	for (;;) {
		fmt_lastresult = 0;
		if ((c = cnc_more ()) != 0) {
			if (sameas (cnc_nxtcmd, "X"))
				return 0;
			if (sameas (cnc_nxtcmd, "?")) {
				listexports ();
				cnc_end ();
				continue;
			}
			i = cnc_word ();
		} else {
			prompt (pr);
			inp_get (0);
			cnc_begin ();
			i = cnc_word ();
			if (!margc) {
				cnc_end ();
				continue;
			} else if (inp_isX (margv[0]))
				return 0;
			if (sameas (margv[0], "?")) {
				listexports ();
				cnc_end ();
				continue;
			}
		}

		if (*i == '/')
			i++;

		if (sameas (i, "*") || sameas (i, "ALL")) {
			strcpy (club, "ALL");
			return 1;
		}
		if (!findclub (i)) {
			prompt (err);
			cnc_end ();
			continue;
		} else
			break;
		return 1;
	}

	strcpy (club, i);
	return 1;
}



static void
export_club ()
{
	char    clubname[16];
	char    spec[256];
	char    lock[256];

	if (!getexportclub (clubname, EXPASK, EXPCLBR))
		return;

	for (;;) {
		fmt_lastresult = 0;
		if (cnc_more () != 0) {
			if (sameas (cnc_nxtcmd, "X")) {
				cnc_end ();
				return;
			}
			if (sameas (cnc_nxtcmd, "?")) {
				listexports ();
				cnc_end ();
				continue;
			}
		} else {
			prompt (EXPSPEC);
			inp_get (127);
			cnc_begin ();
			if (!margc) {
				cnc_end ();
				continue;
			} else if (inp_isX (margv[0])) {
				cnc_end ();
				return;
			}
			if (sameas (margv[0], "?")) {
				listexports ();
				cnc_end ();
				continue;
			} else if (margc == 1 && sameas (margv[0], "-")) {
				strcpy (spec, "");
				break;
			} else if (margc == 1 && sameas (margv[0], "+")) {
				strcpy (spec, "*");
				break;
			}
			if (margc > 1 && sameas (margv[0], "-")) {
				strcpy (spec, inp_buffer);
				break;
			}
			if (strlen (margv[0]) > 1 && margv[0][0] == '-') {
				sprintf (spec, "- %s", &margv[0][1]);
				break;
			}
			strcpy (spec, "do me! :-)");
		}
		break;
	}

	cnc_end ();


	/* Right, now let's pack the spec up to save space */

	if (spec[0] && !sameas (spec, "*")) {
		char    tmp[128];
		int     i;

		tmp[0] = 0;

		for (i = 0; i < margc; i++) {
			if (margv[i][0] == '-') {
				if (strlen (margv[i]) > 1) {
					strcat (tmp, "- ");
					strcat (tmp, &(margv[i][1]));
				} else
					strcat (tmp, "-");
			} else
				strcat (tmp, margv[i]);
			if (i + 1 < margc)
				strcat (tmp, " ");
		}
		strcpy (spec, tmp);
	}


	/* Ok, update the club header(s) */

	if (sameas (clubname, "ALL")) {
		struct dirent **clubs;
		int     n, i;

		n = scandir (mkfname (CLUBHDRDIR), &clubs, hdrselect,
			     ncsalphasort);
		for (i = 0; i < n; free (clubs[i]), i++) {
			char   *cp = &clubs[i]->d_name[1];

			if (!loadclubhdr (cp))
				continue;
			strcpy (clubhdr.export_access_list, spec);
			sprintf (lock, CLUBLOCK, cp);
			if (lock_wait (lock, 10) == LKR_TIMEOUT)
				continue;
			lock_place (lock, "updating");
			saveclubhdr (&clubhdr);
			lock_rm (lock);
		}
		free (clubs);
	} else if (loadclubhdr (clubname)) {
		strcpy (clubhdr.export_access_list, spec);
		sprintf (lock, CLUBLOCK, clubname);
		if (lock_wait (lock, 10) == LKR_TIMEOUT)
			return;
		lock_place (lock, "updating");
		saveclubhdr (&clubhdr);
		lock_rm (lock);
	}
}



static void
club_status ()
{
	FILE   *fp;
	struct dirent **systems;
	char    fname[512];
	int     n, i;

	prompt (NETST1);

	n = scandir (mkfname (MSGSDIR "/..netimport"), &systems, rsysselect,
		     alphasort);
	for (i = 0; i < n; free (systems[i]), i++) {
		char   *cp = systems[i]->d_name;

		sprintf (fname, mkfname (MSGSDIR "/..netimport/%s", cp));
		if ((fp = fopen (fname, "r")) == NULL) {
			error_logsys ("Unable to open %s", fname);
			continue;
		}

		*(strrchr (cp, ':')) = '/';
		prompt (NETST2, cp);

		while (!feof (fp)) {
			char    line[512], key[512], rem[512], loc[512];

			if (!fgets (line, sizeof (line), fp))
				break;
			if (sscanf (line, "%s %s %s", key, rem, loc) == 3) {
				if (sameas (key, "import:"))
					prompt (NETST3, rem, loc);
			}
		}
		fclose (fp);
		prompt (NETST4);
	}
	free (systems);
}



void
networking ()
{
	char    opt;
	int     show = 1;
	int     access;

	for (;;) {
		enterdefaultclub ();
		access = getclubax (&thisuseracc, clubhdr.club);
		if (!get_menu
		    (&opt, show, NETMNU, SHNETMNU, ERRSEL, "HDIES", 0, 0))
			return;

		show = 0;
		switch (opt) {
		case 'H':
			prompt (NETHELP);
			continue;
		case 'D':
			if (access >= CAX_SYSOP)
				define_import_point ();
			else
				prompt (NOAXES, opt);
			continue;
		case 'I':
			if (access >= CAX_SYSOP)
				import_club ();
			else
				prompt (NOAXES, opt);
			continue;
		case 'E':
			if (access >= CAX_SYSOP)
				export_club ();
			else
				prompt (NOAXES, opt);
			continue;
		case 'S':
			if (access >= CAX_COOP)
				club_status ();
			else
				prompt (NOAXES, opt);
			continue;
		}
	}
}



#endif				/* HAVE_METABBS */


/* End of File */
