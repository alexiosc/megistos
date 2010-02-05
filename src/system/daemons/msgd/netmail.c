/*****************************************************************************\
 **                                                                         **
 **  FILE:     netmail.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, May 1995, Version 0.1                                     **
 **  PURPOSE:  Read users' /usr/spool/mail files and move their netmail to  **
 **            the BBS mail database.                                       **
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
 * $Id: netmail.c,v 2.0 2004/09/13 19:44:53 alexios Exp $
 *
 * $Log: netmail.c,v $
 * Revision 2.0  2004/09/13 19:44:53  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.4  2004/02/29 16:32:58  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.4  1998/12/27 16:28:24  alexios
 * Added autoconf support.
 *
 * Revision 0.3  1998/07/24 10:27:56  alexios
 * Moved to stable status. Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:16:29  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 11:16:40  alexios
 * First registered revision. Adequate.
 *
 *
 */


static const char rcsinfo[] = "$Id: netmail.c,v 2.0 2004/09/13 19:44:53 alexios Exp $";


#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_DIRENT_H 1
#define WANT_SYS_STAT_H 1
#define WANT_SYS_IOCTL_H 1
#define WANT_TERMIOS_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "msgd.h"


char   *
addhistory (char *h, char *s, int len)
{
	char    temp[1024];

	sprintf (temp, "%s %s", s, h);
	strncpy (h, temp, len);
	return h;
}



void
postmessage (char *userid, char *body)
{
	FILE   *fp;
	message_t msg;
	int     gotaddress = 0, bodylen = 0, x;
	char    command[256], fname[256], attdir[256] = { 0 };

	if ((fp = fopen (body, "r+")) == NULL) {
		return;
	}

	memset (&msg, 0, sizeof (msg));

	strcpy (msg.to, userid);
	addhistory (msg.history, HST_NETMAIL, sizeof (msg.history));

	for (;;) {
		char    line[1024], *cp, field[256], value[256];
		int     pos;

		if (!fgets (line, sizeof (line), fp))
			break;
		if ((cp = strchr (line, 10)) != NULL)
			*cp = 0;
		if (!line[0])
			break;

		if (sscanf (line, "%s %n%s", field, &pos, value) == 2) {
			if (!strcmp ("From:", field) && !gotaddress) {
				get_address_from (line, value);
				strncpy (msg.from, value, sizeof (msg.from));
			} else if (!strcmp ("Reply-To:", field)) {
				get_address_from (line, value);
				strncpy (msg.from, value, sizeof (msg.from));
				gotaddress = 1;
			} else if (!strcmp ("Subject:", field)) {
				strncpy (msg.subject, &line[pos],
					 sizeof (msg.subject));
			} else if (!strcmp ("X-MsgHdr-FileAttached:", field)) {
				if (value[0] && strcmp ("No", value)) {
					strncpy (msg.fatt, value,
						 sizeof (msg.fatt));
					msg.flags |= MSF_FILEATT | MSF_APPROVD;
				}
			} else if (!strcmp ("X-MsgHdr-RRR:", field)) {
				if (sameas ("yes", field))
					msg.flags |= MSF_RECEIPT;
			} else if (!strcmp ("X-MsgLen:", field)) {
				sscanf (value, "%d", &bodylen);
			}
		}
	}

	if (msg.flags & MSF_FILEATT) {
		sprintf (attdir, "%sATT", body);
		sprintf (command,
			 "(mkdir %s; cd %s; dd if=%s skip=%ld bs=1c|uudecode) 2>/dev/null",
			 attdir, attdir, body, ftell (fp) + bodylen - 1);
		x = system (command);

#ifdef DEBUG
		printf ("    system(\"%s\"), exit=%d\n", command, x);
#endif

		ftruncate (fileno (fp), ftell (fp) + bodylen);
		fseek (fp, bodylen, SEEK_CUR);
	}
	fclose (fp);


#ifdef DEBUG
	printf ("    msg.from:    (%s)\n", msg.from);
	printf ("    msg.to:      (%s)\n", msg.to);
	printf ("    msg.subject: (%s)\n", msg.subject);
	printf ("    msg.history: (%s)\n", msg.history);
	printf ("    msg.fatt:    (%s)\n", msg.fatt);
	printf ("    msg.flags:   (%08lx)\n", msg.flags);
#endif


	sprintf (fname, "%sH", body);

	if ((fp = fopen (fname, "w")) == NULL) {
		return;
	}
	fwrite (&msg, 1, sizeof (msg), fp);
	fclose (fp);

	if (!attdir[0]) {
		sprintf (command, "%s %s %s", mkfname (BBSMAILBIN), fname,
			 body);
	} else {
		sprintf (command, "%s %s %s -c %s/*", mkfname (BBSMAILBIN),
			 fname, body, attdir);
	}

	sysvar->incnetmsgs++;

	x = system (command);

#ifdef DEBUG
	printf ("    system(\"%s\"), exit=%d\n", command, x);
#endif

	if (attdir[0]) {
		sprintf (command, "\\rm -rf %s", attdir);
		x = system (command);

#ifdef DEBUG
		printf ("    system(\"%s\"), exit=%d\n", command, x);
#endif
	}

	unlink (fname);
	unlink (body);
}


void
grabmail (char *fname, char *userid)
{
	char    command[256], tempname[256];
	struct stat st;
	int     msgnum = 0, x;

	sprintf (tempname, TMPDIR "/%d%s%08lx", getpid (), userid, time (0));
	sprintf (command, "mv %s %s", fname, tempname);

#ifdef DEBUG
	printf ("  grabmail: system(\"%s\")\n", command);
#endif

	if ((x = system (command)) != 0) {

#ifdef DEBUG
		printf ("  grabmail: system(\"%s\") failed, exit=%d\n",
			command, x);
#endif

		return;
	}

	while (!stat (tempname, &st)) {
		char    bodyname[256];

		msgnum++;
		sprintf (bodyname, TMPDIR "/%d%s%d", getpid (), userid,
			 msgnum);
		sprintf (command,
			 "echo -e 's 1 %s\\nd 1\\nq'|mail -f %s >&/dev/null",
			 bodyname, tempname);

#ifdef DEBUG
		printf ("  grabmail: system(\"%s\").\n", command);
#endif

		if ((x = system (command)) != 0) {

#ifdef DEBUG
			printf
			    ("  grabmail: system(\"%s\") failed, exit=%d.\n",
			     command, x);
#endif

			break;
		}

		postmessage (userid, bodyname);
	}

	for (; msgnum; msgnum--) {
		char    victim[256];

		sprintf (victim, TMPDIR "/%d%s%d", getpid (), userid, msgnum);
		unlink (victim);
	}

#ifdef DEBUG
	printf ("  grabmail: done with file %s, unlinking.\n", tempname);
#endif
	unlink (tempname);
}


void
getnetmail ()
{
	DIR    *dp;
	struct dirent *dir;
	struct stat st;
	char    userid[24], fname[256];

#ifdef DEBUG
	printf ("getnetmail(): Parsing net mail.\n");
#endif

	if ((dp = opendir (NETMAILDIR)) == NULL) {
#ifdef DEBUG
		printf
		    ("getnetmail(): opendir(NETMAIL,\"r\"): failed, errno=%d.\n",
		     errno);
#endif
		return;
	}

	while ((dir = readdir (dp)) != NULL) {
		if (!(strcmp (dir->d_name, ".") && strcmp (dir->d_name, "..")))
			continue;

		strcpy (userid, dir->d_name);
		if (!usr_exists (userid))
			continue;

		sprintf (fname, "%s/%s", NETMAILDIR, dir->d_name);
		if (stat (fname, &st))
			continue;
		if (!st.st_size)
			continue;

#ifdef DEBUG
		printf ("getnetmail(): dir->d_name=%s ", dir->d_name);
		printf ("belongs to: %s\n", userid);
#endif

		grabmail (fname, userid);
	}
	closedir (dp);

#ifdef DEBUG
	printf ("getnetmail(): done.\n");
#endif
}
