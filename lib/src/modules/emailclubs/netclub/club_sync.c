/*****************************************************************************\
 **                                                                         **
 **  FILE:     club_sync.c                                                  **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1999.                                                **
 **  PURPOSE:  Call on a remote MetaBBS server to import club messages.     **
 **  NOTES:    See syntax() function for the syntax of this program.        **
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
 * Revision 2.0  2004/09/13 19:44:51  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.4  2003/12/23 23:20:23  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:08  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
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
#define WANT_SYS_STAT_H 1
#define WANT_DIRENT_H 1
#define WANT_TIME_H 1
#define WANT_ZLIB_H 1
#include <bbsinclude.h>
#include <bbs.h>
#include <typhoon.h>

#include <megistos/netclub.h>
#include <megistos/metaservices.h>
#include <megistos/ihavedb.h>



static char iterated_local_club[16];



static int
findclub (char *club)
{
	DIR    *dp;
	struct dirent *dir;

	if (*club == '/')
		club++;
	if (!isalpha (*club))
		return 0;

	if ((dp = opendir (mkfname (CLUBHDRDIR))) == NULL) {
		error_fatalsys ("Unable to open directory %s",
				mkfname (CLUBHDRDIR));
	}
	while ((dir = readdir (dp)) != NULL) {
		if (dir->d_name[0] != 'h')
			continue;
		if (sameas (&(dir->d_name[1]), club)) {
			strcpy (club, &(dir->d_name[1]));
			closedir (dp);
			return 1;
		}
	}
	closedir (dp);
	return 0;
}




static int
do_message (CLIENT * cl, char *host, char *codename, char *club,
	    ihave_list_p p)
{
	struct netqueryc q;
	message_request_t msgreq;
	struct club_message *result;
	struct club_message_t *netmsg;
	struct message hdr;
	int     fd;
	char    fname_h[256], fname_b[256], fname_a[256];
	char    command[1024];


	/* First we need to check if we already have this message */

	bzero (&q, sizeof (q));
	strcpy (q.bbs, p->codename);
	strcpy (q.orgclub, p->orgclub);
	strcpy (q.msgid, p->msgid);

	/* Query our local IHAVE database */

	switch (d_keyfind (NETQUERYC, &q)) {
	case S_OKAY:
		return 0;	/* Already have it, thanks anyway */
	case S_NOTFOUND:
		break;		/* We want this message! */
	default:
		fprintf (stderr, "Typhoon error in IHAVE lookup: %d\n",
			 db_status);
		return 0;
	}


	/* Ok, it seems we want this message after all */

	printf ("    Importing %s/%s/%s (%s/%d)\n",
		p->codename, p->orgclub, p->msgid, club, p->msgno);


	/* Call the procedure */

	bzero (&msgreq, sizeof (msgreq));
	strcpy (msgreq.codename, bbscode);
	strcpy (msgreq.targetname, codename);
	strcpy (msgreq.targetclub, club);
	msgreq.msgno = p->msgno;
#ifdef HAVE_ZLIB
	msgreq.compression = 1;
#else
	msgreq.compression = 0;
#endif

	if ((result = distclub_request_message_1 (&msgreq, cl)) == NULL) {
		clnt_perror (cl, host);
		clnt_destroy (cl);
		fprintf (stderr, "RPC request wasn't answered by %s", host);
		return 0;
	}

	if (debug || (result->result_code != 0)) {
		int     i = result->result_code;

		fprintf (stderr, "    Server returns result %d (%s)\n", i,
			 i > 0 ? strerror (i) : clr_errorlist[-i]);
	}
	if (result->result_code)
		return 0;

	netmsg = &(result->club_message_u.message);
	if (debug) {
		fprintf (stderr, "    from:        %s\n", netmsg->from);
		fprintf (stderr, "    to:          %s\n", netmsg->to);
		fprintf (stderr, "    subject:     %s\n", netmsg->subject);
		fprintf (stderr, "    compression: %d\n",
			 netmsg->comp_result.compression);
		fprintf (stderr, "    body len:    %d\n",
			 netmsg->message.message_len);
		fprintf (stderr, "    uncomp:      %d\n",
			 netmsg->comp_result.compr_u.compr.orig_msg_len);
	}


	/* Re-create the message header */

	bzero (&hdr, sizeof (hdr));
	strcpy (hdr.from, netmsg->from);
	strcpy (hdr.to, netmsg->to);
	strcpy (hdr.subject, netmsg->subject);
	sprintf (hdr.history, "%s %s/%s/%s/%d", HST_NET, host, codename, club,
		 p->msgno);
	hdr.flags = (netmsg->flags & MSF_NETMASK) | MSF_NET;
	hdr.crdate = netmsg->orgdate;
	hdr.crtime = netmsg->orgtime;
	strcpy (hdr.club, iterated_local_club);
	findclub (hdr.club);
	strcpy (hdr.origbbs, p->codename);
	strcpy (hdr.origclub, p->orgclub);
	strcpy (hdr.msgid, p->msgid);

	/* KLUDGE ALERT!!!

	   The sender/recipient are treated specially. If the message comes from a
	   BBS with the same codename, it's assumed to be a friendly system and user
	   names are copied verbatim. This implies that two BBSs with the same
	   codenames are considered to have the same users. This is NOT a security
	   risk: it's only there so that the sysstem shows personal (NOT private, we
	   only deal in clubs) messages to the 'right' users.

	   Anyway, this is the strategy: if the remote system's codename is the same
	   as ours, then user 'Sysop' on either systems is assumed to be the same
	   person. Club messages sent to Sysop will be shown to both Sysop accounts
	   when they're looking for public mail addressed to them.

	   Otherwise, a nice simple space is appended to the username. This is
	   invisible to other programs, quite transparent (excuse the pun) and
	   ensures that "Sysop" from host/SYSTEM won't be shown messages addressed to
	   all the other "Sysop"s at different systems. 

	   This is TEMPORARY only. The stubs are already there in struct message:
	   usernames will soon have to be augmented by the originating BBS' codename
	   to make the system behave in a more modern manner. */

	if (!sameas (bbscode, p->codename)) {
		strcat (hdr.from, " ");
		strcat (hdr.to, " ");
	}



	/* If we're only doing a dry run, this where we get off */

	if (dryrun)
		return 1;



	/* Ok, write the header out to a file for bbsmail. */

	sprintf (fname_h, "/tmp/netclubh-%x%x", (int) getpid (),
		 (int) time (NULL));
	if ((fd = open (fname_h, O_CREAT | O_WRONLY | O_TRUNC, 0660)) < 0) {
		int     i = errno;

		fprintf (stderr, "Unable to create %s: %s\n", fname_h,
			 strerror (i));
		return 1;
	}
	if (write (fd, &hdr, sizeof (hdr)) != sizeof (hdr)) {
		int     i = errno;

		fprintf (stderr, "Unable to write to %s: %s\n", fname_h,
			 strerror (i));
		return 1;
	}
	close (fd);


	/* Step two: write the main body as another file. */

	sprintf (fname_b, "/tmp/netclubb-%x%x", (int) getpid (),
		 (int) time (NULL));
	if ((fd = open (fname_b, O_CREAT | O_WRONLY | O_TRUNC, 0660)) < 0) {
		int     i = errno;

		fprintf (stderr, "Unable to create %s: %s\n", fname_b,
			 strerror (i));
		return 1;
	}

	if (!netmsg->comp_result.compression) {
		int     b =
		    write (1, netmsg->message.message_val,
			   netmsg->message.message_len);
		if (b != netmsg->message.message_len) {
			int     i = errno;

			fprintf (stderr, "FATAL: unable to write to %s: %s\n",
				 fname_b, strerror (i));
			exit (1);
		}
	} else {
#ifdef HAVE_ZLIB
		char   *tmp;
		long    i = netmsg->comp_result.compr_u.compr.orig_msg_len;

		tmp = alcmem (i);
		uncompress (tmp, &i, netmsg->message.message_val,
			    netmsg->message.message_len);
		if (write (fd, tmp, i) != i) {
			int     i = errno;

			fprintf (stderr, "FATAL: unable to write to %s: %s\n",
				 fname_b, strerror (i));
			exit (1);
		}
		free (tmp);
#else
		fprintf (stderr,
			 "FATAL: we didn't ask for compressed messages!\n");
		exit (1);
#endif
	}

	close (fd);



	/* Step three: if there is an attachment, write it to yet another file. */

	if (hdr.flags & MSF_FILEATT) {
		sprintf (fname_a, "/tmp/netcluba-%x%x", (int) getpid (),
			 (int) time (NULL));
		if ((fd =
		     open (fname_a, O_CREAT | O_WRONLY | O_TRUNC, 0660)) < 0) {
			int     i = errno;

			fprintf (stderr, "Unable to create %s: %s\n", fname_a,
				 strerror (i));
			return 1;
		}

		if (!netmsg->comp_result.compression) {
			int     b =
			    write (1, netmsg->attachment.attachment_val,
				   netmsg->attachment.attachment_len);

			if (b != netmsg->attachment.attachment_len) {
				int     i = errno;

				fprintf (stderr,
					 "FATAL: unable to write to %s: %s\n",
					 fname_a, strerror (i));
				exit (1);
			}
		} else {
#ifdef HAVE_ZLIB
			char   *tmp;
			long    i =
			    netmsg->comp_result.compr_u.compr.orig_msg_len;

			tmp = alcmem (i);
			uncompress (tmp, &i, netmsg->attachment.attachment_val,
				    netmsg->attachment.attachment_len);
			if (write (fd, tmp, i) != i) {
				int     i = errno;

				fprintf (stderr,
					 "FATAL: unable to write to %s: %s\n",
					 fname_a, strerror (i));
				exit (1);
			}
			free (tmp);
#else
			fprintf (stderr,
				 "FATAL: we didn't ask for compressed messages!\n");
			exit (1);
#endif
		}

		close (fd);
	}


	/* Final step: call bbsmail to file the message */

	if ((hdr.flags & MSF_FILEATT) == 0) {
		sprintf (command, "%s %s %s", mkfname (BBSMAILBIN), fname_h,
			 fname_b);
	} else {
		sprintf (command, "%s %s %s -c %s", mkfname (BBSMAILBIN),
			 fname_h, fname_b, fname_a);
	}
	system (command);


	/* clean up */

	unlink (fname_h);
	unlink (fname_b);
	unlink (fname_a);

	return 1;
}



static int
do_club (char *sysname, char *rem, char *loc, int ihavedate)
{
	CLIENT *cl = NULL;
	char    tmp[256], *cp, *cp2;
	struct ihave_request_t ihavereq;
	ihave_list *result;
	ihave_list_p p;
	int     offered = 0, taken = 0;

	printf ("  Importing %s -> /%s\n", rem, loc);
	if (debug)
		fprintf (stderr, "  rem=(%s), loc=(%s), ihavedate=(%d)\n",
			 rem, loc, ihavedate);


	/* Separate the hostname from the codename */

	strcpy (tmp, rem);
	if ((cp = strchr (tmp, '/')) == NULL) {
		fprintf (stderr, "System \"%s\" has invalid name!\n", sysname);
		return ihavedate;
	}

	*cp++ = 0;		/* tmp=hostname, cp=codename */

	if ((cp2 = strchr (cp, '/')) == NULL) {
		fprintf (stderr, "System \"%s\" has invalid name!\n", sysname);
		return ihavedate;
	}

	*cp2++ = 0;		/* cp2=remote club name */


	/* Make the connection */

	if (debug)
		fprintf (stderr, "Creating RPC client for host %s\n", tmp);
	if ((cl =
	     clnt_create (tmp, METABBS_PROG, METABBS_VERS, "tcp")) == NULL) {
		clnt_pcreateerror (tmp);
		return ihavedate;
	}


	/* Call the procedure */

	strcpy (ihavereq.codename, bbscode);
	strcpy (ihavereq.targetname, cp);
	strcpy (ihavereq.club, cp2);
	ihavereq.since_time = ihavedate;


	if (debug)
		fprintf (stderr,
			 "Sending IHAVE list request for club %s/%s/%s\n", tmp,
			 cp, cp2);

	if ((result = distclub_request_ihave_1 (&ihavereq, cl)) == NULL) {
		clnt_perror (cl, tmp);
		clnt_destroy (cl);
		fprintf (stderr, "RPC request wasn't answered by %s", tmp);
		return ihavedate;
	}

	if (debug || (result->result_code != 0)) {
		int     i = result->result_code;

		fprintf (stderr, "Server returns result %d (%s)\n", i,
			 i > 0 ? strerror (i) : clr_errorlist[-i]);
	}
	if (result->result_code)
		return ihavedate;

	p = result->ihave_list_u.ihave_list;
	while (p) {
		if (debug)
			fprintf (stderr,
				 "IHAVE RECORD: ID=%s/%s/%s TIME=%d MSGNO=%d\n",
				 p->codename, p->orgclub, p->msgid, p->time,
				 p->msgno);

		taken += do_message (cl, tmp, cp, cp2, p);

		p = p->next;
		offered++;
	}

	printf ("\n    Messages offered: %d\n", offered);
	printf ("    Messages taken:   %d\n\n", taken);

	xdr_free ((xdrproc_t) xdr_ihave_list, (caddr_t) result);

	return ihavedate;
}



void
club_sync (char *fname, char *sysname)
{
	FILE   *fp;
	int     delta = 0, lastsync = 0, ihavedate = 0;
	int     first = 1, mindate = 0;


	/* Get the necessary information */

	if ((fp = fopen (fname, "r")) == NULL) {
		perror ("netclub: club_sync: fopen(read):");
		exit (1);
	}

	while (!feof (fp)) {
		char    line[512], key[512];
		int     x;

		if (!fgets (line, sizeof (line), fp))
			break;
		if (sscanf (line, "%s %d", key, &x) == 2) {
			if (sameas (key, "delta:"))
				delta = x;
			else if (sameas (key, "last-update:"))
				lastsync = x;
			else if (sameas (key, "last-ihave-time:"))
				ihavedate = x;
		}
	}



	/* Should we sync now? */

	if (force) {
		printf ("Syncing system %s: forced sync.\n", sysname);
	} else if (lastsync + delta > time (NULL)) {
		printf ("Syncing system %s: no need to sync yet.\n", sysname);
		fclose (fp);
		return;
	} else {
		printf
		    ("Syncing system %s: sync time elapsed, importing messages.\n",
		     sysname);
	}



	/* Ok, go through the clubs one by one, calling do_club() to do the dirty
	   work. do_club returns the date of the last ihave entry received. Of all
	   such final_ihavedates received, we keep the minimum one -- it's the
	   earliest one, which is the logical choice for our next sync. We don't
	   re-request messages we already have, anyway. */

	rewind (fp);
	while (!feof (fp)) {
		char    line[512], key[512], rem[512], loc[512];

		if (!fgets (line, sizeof (line), fp))
			break;
		if (sscanf (line, "%s %s %s", key, rem, loc) == 3) {
			if (sameas (key, "import:")) {
				int     final_ihavedate;

				strcpy (iterated_local_club, loc);
				final_ihavedate =
				    do_club (sysname, rem, loc, ihavedate);
				if (first)
					mindate = final_ihavedate;
				else if (final_ihavedate < mindate)
					mindate = final_ihavedate;
			}
		}
	}
}


/* End of File */
