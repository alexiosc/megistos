/*****************************************************************************\
 **                                                                         **
 **  FILE:     convert.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  PURPOSE:  Convert MBBS 5.31 user accounts to Megistos format.          **
 **  NOTES:    This is NOT guarranteed to work on anything but MajorBBS     **
 **            version 5.31, for which it was written.                      **
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
\*****************************************************************************/


/*
 * $Id: convert.c,v 2.0 2004/09/13 19:44:54 alexios Exp $
 *
 * $Log: convert.c,v $
 * Revision 2.0  2004/09/13 19:44:54  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.4  2003/12/23 08:14:05  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:08  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.2  1999/08/13 17:11:32  alexios
 * Ugly-looking changes to accommodate no-UNIX account policy.
 *
 * Revision 1.1  1998/12/27 16:41:03  alexios
 * Added autoconf support.
 *
 * Revision 1.0  1998/07/10 21:09:25  alexios
 * Initial revision
 *
 *
 */


static const char rcsinfo[] = "$Id: convert.c,v 2.0 2004/09/13 19:44:54 alexios Exp $";



#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_FCNTL_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_STAT_H 1
#define WANT_PWD_H 1
#define WANT_GRP_H 1
#include <bbsinclude.h>

#include <endian.h>
#include <typhoon.h>
#include <megistos/bbs.h>
#include <cnvutils.h>
#include <megistos/mbk_signup.h>
#include <megistos/mbk_sysvar.h>


#define USRACC_RECLEN 252



useracc_t usr;
char   *newclss;
int     pswexp;



#if 0
static int
finduid ()
{
	struct passwd *fott;
	int     unused = beguid;

	while ((fott = getpwuid (++unused)) != NULL);
	return unused;
}
#endif



static void
adduser (char *usrdir, FILE * passwd, FILE * shadow)
{
	FILE   *user;

	/*int uidn=finduid(); */
	char    fname[256];
	char    uid[64], uid2[64];

	/*static int delta=0; */

	strcpy (uid, usr.userid);
	lowerc (uid);


	/* Add the user to .passwd and .shadow, if applicable */

	printf ("Adding %s: ", usr.userid);
	fflush (stdout);

#if 0
	if (passwd) {
		fprintf (passwd, "%s:x:%d:%d:%s:%s/%s:%s\n",
			 uid, uidn + delta++, newgidn, newnam, newhome, uid,
			 newshl);
		fprintf (shadow, "%s:*:9804:0:::::\n", uid);
		printf ("Add UNIX record to .passwd, .shadow. ");
		fflush (stdout);
	} else {
#endif
		/* Run a script with additional user adding commands */

		strcpy (uid2, uid);
		if (strlen (uid2) > 8) {
			uid2[8] = 0;
			printf
			    ("(truncating UNIX username to %s, fix by hand)  ",
			     uid2);
			fflush (stdout);
		}

		printf ("Add UNIX record. ");
		fflush (stdout);
		sprintf (fname, "%s %s", mkfname (USERADDBIN), uid2);
		if (system (fname)) {
			fprintf (stderr, "Failed to add UNIX user %s.", uid);
			exit (1);
		}
#if 0
	}
#endif


	/* Add the user's record */

	printf ("Add BBS record. ");
	fflush (stdout);
	sprintf (fname, "%s/%s", usrdir, usr.userid);
	if ((user = fopen (fname, "w")) == NULL) {
		fprintf (stderr, "Failed to create user account %s", fname);
		exit (1);
	}

	if (fwrite (&usr, sizeof (usr), 1, user) != 1) {
		fprintf (stderr, "Failed to write user account %s", fname);
		exit (1);
	}

	fclose (user);
	/*chown(fname,uidn+delta,newgidn); */
	printf ("Done.\n");
	fflush (stdout);
}


long
majordate (char *datstr)
{
	int     monthlen[12] =
	    { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int     mon, day, year;
	char    c1, c2;

	if (sscanf (datstr, "%d%c%d%c%d", &mon, &c1, &day, &c2, &year) == 5) {
		if ((c1 != c2) || ((c1 != '/') && (c1 != '-')))
			return -1L;
	} else if (sscanf (datstr, "%d%c%d", &day, &c1, &mon) == 3) {
		year = tdyear (now ());
		if ((c1 != '/') && (c1 != '-'))
			return -1L;
	} else
		return -1L;

	if (year < 70)
		year += 2000;
	else if (year < 100)
		year += 1900;
	if (year < 1970 || year > 2225 || mon < 1 || mon > 12)
		return -1L;
	if (__isleap (year))
		monthlen[1]++;
	if (day < 1 || day > monthlen[mon - 1])
		return -1L;

	return makedate (day, mon, year);
}


void
convert (char *arg_usrdir, char *arg_majordir, char *arg_class,
	 int arg_fast, int arg_uid)
{
	FILE   *fp, *passwd = NULL, *shadow = NULL;
	char    rec[16384], c, *fname = rec;
	int     reclen;
	int     num = 0;
	promptblock_t *msg;

	if (arg_fast) {
		if ((passwd = fopen (".passwd", "w")) == NULL) {
			fprintf (stderr, "Unable to create .passwd\n");
			exit (1);
		}
		if ((shadow = fopen (".shadow", "w")) == NULL) {
			fprintf (stderr, "Unable to create .shadow\n");
			exit (1);
		}
	}

	/* Read signup options */

	msg = msg_open ("sysvar");
	pswexp = msg_int (PSWEXP, 0, 360);
	msg_close (msg);

	msg = msg_open ("signup");
	newclss = msg_string (NEWCLSS);
	msg_close (msg);

	/*if(arg_uid>=100)beguid=arg_uid; */


	/* Resolve the bbs GID to its numeric equivalent */

#if 0
	if ((newgidn = atoi (newgid)) == 0) {
		FILE   *fp = fopen ("/etc/group", "r");
		struct group *g;

		if (fp == NULL) {
			fprintf (stderr, "Unable to open /etc/group!\n");
			exit (1);
		}
		while ((g = fgetgrent (fp)) != 0) {
			if (!strcmp (g->gr_name, newgid)) {
				newgidn = g->gr_gid;
				break;
			}
		}
		fclose (fp);
		if (g == NULL) {
			fprintf (stderr,
				 "Group '%s' not found in /etc/group!\n",
				 newgid);
			exit (1);
		}
	}
	if (!newgidn) {
		fprintf (stderr, "Bletch, new users gid is 0. Won't do it.\n");
	}
#endif


	/* Start conversion */

	sprintf (fname, "%s/usracc.txt", arg_majordir ? arg_majordir : ".");
	fp = fopen (fname, "r");
	if (fp == NULL) {
		sprintf (fname, "%s/USRACC.TXT",
			 arg_majordir ? arg_majordir : ".");
		if ((fp = fopen (fname, "r")) == NULL) {
			fprintf (stderr,
				 "usrcnv: convert(): unable to find usracc.txt or USRACC.TXT.\n");
			exit (1);
		}
	}

	while (!feof (fp)) {
		if (fscanf (fp, "%d\n", &reclen) == 0) {
			if (feof (fp))
				break;
			fprintf (stderr,
				 "usrcnv: convert(): unable to parse record length. Corrupted file?\n");
			exit (1);
		}
		if (feof (fp))
			break;
		fgetc (fp);	/* Get rid of the comma after the record length */

		if (reclen != USRACC_RECLEN) {
			fprintf (stderr,
				 "usrcnv: convert(): record length isn't %d. "
				 "Is this a v5.31 file?\n", USRACC_RECLEN);
			exit (1);
		}

		if (fread (rec, reclen, 1, fp) != 1) {
			fprintf (stderr,
				 "usrcnv: convert(): unable to read record around pos=%ld.\n",
				 ftell (fp));
			exit (1);
		}

		bzero (&usr, sizeof (usr));

		/* BASICS */

		strcpy (usr.userid, &rec[0]);	/* User ID */
		strcpy (usr.passwd, &rec[10]);	/* Password */
		strcpy (usr.username, &rec[20]);	/* Real name */
		strcpy (usr.company, &rec[50]);	/* Company name */
		strcpy (usr.address1, &rec[80]);	/* Address line 1 */
		strcpy (usr.address2, &rec[110]);	/* Address line 2 */
		strcpy (usr.phone, &rec[140]);	/* Phone */

		usr.age = rec[160];	/* Age (only LSB matters) */
		usr.sex = rec[162];	/* Sex (compatible as it is) */
		usr.scnwidth = rec[158];	/* Screen width */
		if (usr.scnwidth < 40)
			usr.scnwidth = 80;
		usr.scnheight = rec[159];	/* Screen height */
		if (usr.scnheight > 40)
			usr.scnheight = 23;
		if (usr.scnheight < 10)
			usr.scnheight = 23;
		usr.system = rec[156];
		if (!usr.system)
			usr.system = 8;
		usr.language = 1;
		usr.passexp = pswexp;

		printf ("DATA: SYS=%d\n", rec[156]);


		/* DATES */

		usr.datecre = majordate (&rec[164]);
		usr.datelast = majordate (&rec[174]);
		if (usr.datelast < 0)
			usr.datelast = usr.datecre;


		/* PREFERENCE FLAGS */

		usr.prefs = UPF_ANSIDEF | UPF_TRDEF;
		if (rec[157] & 1)
			usr.prefs |= UPF_ANSION + UPF_VISUAL;
		if (rec[157] & 2)
			usr.prefs &= ~UPF_ANSIDEF;
		if (!rec[159])
			usr.prefs |= UPF_NONSTOP;


		/* GENERAL FLAGS */
		usr.flags = 0;
		if (rec[232] & 1) {
			fprintf (stderr,
				 "SYSAXS:  %s (stripping sysop flags)\n",
				 usr.userid);
		}
		if (rec[232] & 2) {
			usr.flags |= UFL_EXEMPT;
			fprintf (stderr, "EXEMPT:  %s\n", usr.userid);
		}
		if (rec[232] & 4) {
			usr.flags |= UFL_SUSPENDED;
			fprintf (stderr, "SUSPEND: %s\n", usr.userid);
		}


		/* USER CLASS */

		strcpy (usr.tempclss, arg_class);
		strcpy (usr.curclss, arg_class);


		/* COUNTERS */

		usr.credits = *((int *) (&rec[196]));
		usr.totcreds = *((int *) (&rec[184])) + *((int *) (&rec[188]));
		usr.totpaid = *((int *) (&rec[192]));
		usr.totcreds += usr.totpaid;
		usr.timever = usr.totcreds;
		usr.credsever = usr.totcreds;
		usr.pagetime = 1;
		usr.pagestate = PGS_STORE;	/* Store pages */


		/* Now add the user */
		adduser (arg_usrdir, passwd, shadow);


		/* DONE! */
		num++;
		do
			c = fgetc (fp);
		while (c == '\n' || c == '\r' || c == 26);
		ungetc (c, fp);
	}

	if (arg_fast) {
		fclose (passwd);
		fclose (shadow);
	}

	printf ("Created %d users.\n", num);
}


/* End of File */
