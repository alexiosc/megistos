/*****************************************************************************\
 **                                                                         **
 **  FILE:     mailfixup.c                                                  **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, May 1995, Version 0.1                                     **
 **            B, August 1996, Version 0.2                                  **
 **  PURPOSE:  Reindex/rethread message areas                               **
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
 * Revision 1.4  2003/12/23 08:14:06  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:08  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.5  1998/12/27 16:37:59  alexios
 * Added autoconf support. Fixed slight bugs.
 *
 * Revision 0.4  1998/08/14 12:02:48  alexios
 * One slight cosmetic change.
 *
 * Revision 0.3  1998/07/24 10:32:15  alexios
 * Moved to stable status. Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:05:14  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 11:30:40  alexios
 * First registered revision. Adequate.
 *
 *
 */


static const char rcsinfo[] = "$Id$";




#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_ERRNO_H 1
#define WANT_DIRENT_H 1
#define WANT_SYS_STAT_H 1
#define WANT_SYS_IOCTL_H 1
#define WANT_TERMIOS_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include <megistos/ecdbase.h>
#include <megistos/typhoon.h>


static int
msgselect (const struct dirent *d)
{
	if (!strcmp (d->d_name, "lost+found"))
		return 0;
	return (int) (d->d_name[0] != '.');
}



static struct clubheader clubhdr;



int
loadclubhdr (char *club)
{
	FILE   *fp;
	char   *fname;
	struct stat st;

	if (*club == '/')
		club++;
	fname = mkfname ("%s/h%s", mkfname (CLUBHDRDIR), club);
	if (stat (fname, &st)) {
		return 0;
	}

	if ((fp = fopen (fname, "r")) == NULL) {
		return 0;
	}

	if (fread (&clubhdr, sizeof (clubhdr), 1, fp) != 1) {
		fclose (fp);
		return 0;
	}
	fclose (fp);

	return 1;
}



int
saveclubhdr (struct clubheader *hdr)
{
	char   *fname = mkfname ("%s/h%s", mkfname (CLUBHDRDIR), hdr->club);
	FILE   *fp;

	if ((fp = fopen (fname, "w")) == NULL)
		return 0;
	fwrite (hdr, sizeof (struct clubheader), 1, fp);
	fclose (fp);
	return 1;
}



static void
doindex (char *clubname, char *clubdir)
{
	int     email = !strcmp (clubname, EMAILCLUBNAME);
	struct dirent **msgs = NULL;
	int     i, j, status;
	char    dir[256], fname[256], lock[256], s[32];
	char    command[256];
	FILE   *fp;
	struct message msg;
	struct ecidx idx;
	int     exempt = 0, fileatt = 0, approved = 0, nmsgs = 0, periodic = 0;

	printf ("Reindexing %s%s.\n", email ? "" : "/", clubname);

	/* Set directory */

	if (!email)
		strcpy (dir, mkfname ("%s/%s", mkfname (MSGSDIR), clubdir));
	else
		strcpy (dir, clubdir);


	/* Wait for club to become available and lock it */

	sprintf (lock, CLUBLOCK, clubname);
	if (lock_check (lock, s) > 0) {
		printf ("Waiting for lock...\n");
		lock_wait (lock, 9999);
	}
	lock_place (lock, "indexing");


	/* Open the database */

	sprintf (fname, "\\rm -f %s/%s/[A-Z]* >&/dev/null", dir, DBDIR);
	system (fname);
	/*sync(); */
	sprintf (fname, "%s/%s", dir, DBDIR);
	mkdir (fname, 0777);
	d_dbfpath (fname);
	d_dbdpath (mkfname (DBDDIR));
	if (d_open (".ecdb", "s") != S_OKAY) {
		fprintf (stderr,
			 "Cannot open database for %s (db_status %d)\n",
			 clubname, db_status);
		return;
	}


	/* Delete all records */

	status = d_keyfrst (NUM);
	i = 0;
	while (status == S_OKAY) {
		i++;
		d_delete ();
		status = d_keynext (NUM);
	}
	/*  printf("%d message(s) in this area. Re-adding them.\n",i); */


	/* Read all message files */

	i = scandir (dir, &msgs, msgselect, alphasort);

	for (j = 0; j < i; free (msgs[j]), j++) {
		sprintf (fname, "%s/%s", dir, msgs[j]->d_name);

		if ((fp = fopen (fname, "rw")) == NULL) {
			printf ("Unable to open %s\n", msgs[j]->d_name);
			fclose (fp);
			continue;
		}

		if (fread (&msg, sizeof (msg), 1, fp) != 1) {
			printf ("Unable to read %s\n", msgs[j]->d_name);
			fclose (fp);
			continue;
		}

		if ((email == 0) && strcmp (msg.club, clubname)) {
			strcpy (msg.club, clubname);
			print ("Message %s/%s has wrong club name, fixing.\n",
			       clubname, msgs[j]->d_name);
			rewind (fp);
			if (ftell (fp) == 0)
				fwrite (&msg, sizeof (msg), 1, fp);
		} else if (email && msg.club[0]) {
			strcpy (msg.club, "");
			print ("Message %s/%s has wrong club name, fixing.\n",
			       clubname, msgs[j]->d_name);
			rewind (fp);
			if (ftell (fp) == 0)
				fwrite (&msg, sizeof (msg), 1, fp);
		}

		fclose (fp);

		exempt += (msg.flags & MSF_EXEMPT) != 0;
		fileatt += (msg.flags & MSF_FILEATT) != 0;
		approved += (msg.flags & MSF_APPROVD) != 0;
		periodic += msg.period != 0;
		nmsgs++;

		bzero (&idx, sizeof (idx));
		idx.num = msg.msgno;
		strcpy (idx.from, msg.from);
		strcpy (idx.to, msg.to);
		strcpy (idx.subject, msg.subject);
		idx.flags = msg.flags;
		/*printf("%6d, club=%-10s (%s), from=%-10s, to=%-10s\n",idx.num,msg.club,clubname,idx.from,idx.to); */
		d_fillnew (ECIDX, &idx);
	}


	/* Make sure the club header is sane. */

	if (msg.club[0]) {
		loadclubhdr (msg.club);
		/*fprintf(stderr,"---> club=%s (%s), clubhdr.msgno=%u, msg.msgno=%u, "
		   "fix=%d\n",
		   clubhdr.club,clubhdr.descr,clubhdr.msgno,msg.msgno,
		   clubhdr.msgno<msg.msgno); */

		if (clubhdr.msgno < msg.msgno) {
			clubhdr.msgno = msg.msgno + 1;
			printf
			    ("Fixing club header (club msgno=%d, actual=%d).\n",
			     clubhdr.msgno, msg.msgno);
			saveclubhdr (&clubhdr);
		}
	}


	/* Free the dirent structure block */

	if (msgs)
		free (msgs);


	/* Close the database */

	d_close ();


	/* Adjust ownership and permissions of the files */

	sprintf (command, "chown -R bbs.bbs %s 2>/dev/null >/dev/null", dir);
	system (command);
	sprintf (command, "chmod -R ug+rw,o-rwx %s 2>/dev/null >/dev/null",
		 dir);
	system (command);


	/* Remove the lock */

	lock_rm (lock);


	/* Show info */

	printf ("\n");
	printf ("Number of messages: %5d\n", nmsgs);
	printf ("Exempt messages:    %5d\n", exempt);
	printf ("File attachments:   %5d\n", fileatt);
	printf ("Approved files:     %5d\n", approved);
	printf ("Periodic messages:  %5d\n", periodic);
	printf ("\n\n");
}


int
main (int argc, char **argv)
{
	struct dirent **clubs;
	int     i, j;

	mod_setprogname (argv[0]);
	doindex (EMAILCLUBNAME, mkfname (EMAILDIR));

	i = scandir (mkfname (MSGSDIR), &clubs, msgselect, alphasort);

	for (j = 0; j < i; j++) {
		doindex (clubs[j]->d_name, clubs[j]->d_name);
		free (clubs[j]);
	}
	free (clubs);
	return 0;
}



/* End of File */
