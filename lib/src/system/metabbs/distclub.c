/*****************************************************************************\
 **                                                                         **
 **  FILE:     distclub.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  PURPOSE:  Distributed club stuff.                                      **
 **  NOTES:    Purposes:                                                    **
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
 * Revision 2.0  2004/09/13 19:44:54  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.4  2003/12/23 08:22:05  alexios
 * Ran through megistos-config --oh. Reinstated use of mkfname().
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.0  1999/07/28 23:15:45  alexios
 * Initial revision
 *
 *
 */


static const char rcsinfo[] =
    "$Id$";


#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <sys/stat.h>
#include <rpc/rpc.h>
#include <netdb.h>
#include <sys/socket.h>
#include <dirent.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdarg.h>

#include <megistos/config.h>
#include <megistos/mail.h>
#include "metaservices.h"
#include "metabbs.h"


static struct clubheader clubhdr;



char   *
apply_prefix (char *fname)
{
	static char buf[1024];
	char   *sans_prefix;

	if (this_system == NULL || fname == NULL) {
#ifdef DEBUG
		fprintf (stderr,
			 "apply_prefix: This_system is null, returning fname\n");
#endif
		return fname;
	}

	sans_prefix=&fname [strlen (mkfname(""))];

	/* Now prepend this_system's prefix (an extra slash won't hurt) */
	sprintf (buf, "%s/%s", this_system->prefix, sans_prefix);

#ifdef DEBUG
	fprintf (stderr, "apply_prefix: fname in=(%s) sans=(%s) out=(%s)\n",
		 fname, sans_prefix, buf);
#endif
	return buf;
}



static int
sameas (char *stg1, char *stg2)
{
	while (*stg1 != '\0') {
		if (tolower (*stg1) != tolower (*stg2)) {
			return (0);
		}
		stg1++;
		stg2++;
	}
	return (*stg2 == '\0');
}


int
getclubaccess (struct sockaddr_in *caller, char *codename)
{
	int     has_access = 0, j, in_accept = 1;
	char    tmp[512], tmp2[512], *cp;

	strcpy (tmp, clubhdr.export_access_list);

	if (!strcmp (tmp, "*")) {	/* Club is open to all systems */
		has_access = 1;
	} else if ((tmp[0] == 0) ||	/* Local club */
		   (strcmp (tmp, "- *") == 0)) {
		has_access = 0;
	} else {
		in_accept = 1;
		j = 0;
		for (cp = strtok (tmp, " "); cp; cp = strtok (NULL, " ")) {
			if (!strcmp (cp, "-"))
				if (in_accept) {
					in_accept = 0;

					/* We just finished with the ACCEPT part -- make sure we match it */
					if (j > 0) {
						has_access = has_access ||
						    (match_acl
						     (tmp2, caller,
						      codename) == 1);
					} else {
						has_access = 1;	/* Prepare for the reverse semantics of the DENY part */
					}
					j = 0;
				}

			strcpy (tmp2, cp);
			strcat (tmp2, " ");
			j++;
		}

		/* Still in the ACCEPT part? */

		if (in_accept) {
			if (j > 0) {
				has_access = has_access ||
				    (match_acl (tmp2, caller, codename) == 1);
			} else
				has_access = 1;
		}

		/* Nope, must be in the DENY bit */

		else if ((in_accept == 0) && (j > 1)) {
			has_access = has_access &&
			    (match_acl (tmp2, caller, codename) == 0);
		}
	}
	return has_access;
}


int
findclub (char *club)
{
	DIR    *dp;
	struct dirent *dir;

	if (!isalpha (*club))
		return 0;

	if ((dp = opendir (apply_prefix (CLUBHDRDIR))) == NULL)
		return 0;
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


int
loadclubhdr (char *club)
{
	FILE   *fp;
	char    fname[256];
	struct stat st;

	if (*club == '/')
		club++;
	if (!findclub (club))
		return 0;
	sprintf (fname, "%s/h%s", apply_prefix (CLUBHDRDIR), club);
	if (stat (fname, &st))
		return 0;

	if ((fp = fopen (fname, "r")) == NULL)
		return 0;

	if (fread (&clubhdr, sizeof (clubhdr), 1, fp) != 1) {
		fclose (fp);
		return 0;
	}
	fclose (fp);

	return 1;
}


static int
ncsalphasort (const struct dirent **A, const struct dirent **B)
{
	register char *a = (*A)->d_name;
	register char *b = (*B)->d_name;
	register char ca;
	register char cb;

      again:
	ca = toupper (*a);
	cb = toupper (*b);
	if (ca != cb)
		return ca - cb;
	if (!*a)
		return 0;
	a++, b++;
	goto again;
}


static int
hdrselect (const struct dirent *d)
{
	return d->d_name[0] == 'h';
}


/* This builds a linked list of all BBS clubs information packs the caller
   is allowed to login to. */

club_list *
distclub_request_list_1_svc (struct club_list_request_t * bbs,
			     struct svc_req * req)
{
	static club_list retstuff;
	static int need_deallocation = 0;
	struct dirent **clubs;
	int     i, n;
	struct sockaddr_in *caller = svc_getcaller (server);
	club_list_item_p clubitem = NULL;

	bzero (&retstuff, sizeof (retstuff));


	if (need_deallocation)
		xdr_free ((xdrproc_t) xdr_club_list, (caddr_t) & retstuff);
	need_deallocation = 0;


#ifdef DEBUG
	fprintf (stderr, "Club list request from BBS \"%s\" for BBS \"%s\"\n",
		 bbs->codename, bbs->targetname);
#endif

	/* Right. Is the targetted BBS registered with us? */

	need_deallocation = 1;
	if ((i = find_system (bbs->targetname)) < 0) {
		retstuff.result_code = CLR_UNKNOWN;
		return &retstuff;
	}


	/* It is indeed. But is it really a Megistos BBS? */

	if (registered_systems[i].users_online < 0) {
		retstuff.result_code = CLR_NOTMEGISTOS;
		return &retstuff;
	}


	/* Ok, there's no escaping this request. :-)  Form the club list. */

	this_system = &registered_systems[i];

	n = scandir (apply_prefix (CLUBHDRDIR), &clubs, hdrselect, ncsalphasort);
	for (i = 0; i < n; free (clubs[i]), i++) {
		char   *cp = &clubs[i]->d_name[1];

		if (!loadclubhdr (cp))
			continue;
		if (getclubaccess (caller, bbs->codename)) {

#ifdef DEBUG
			fprintf (stderr, "OK: %-16.16s %-10.10s %-40.40s %s\n",
				 clubhdr.club, clubhdr.clubop,
				 clubhdr.descr, clubhdr.export_access_list);
#endif

			if (clubitem == NULL) {
				clubitem = retstuff.club_list_u.clubs =
				    (club_list_item_p)
				    malloc (sizeof (club_list_item_t));
			} else {
				clubitem->next =
				    (club_list_item_p)
				    malloc (sizeof (club_list_item_t));
				clubitem = clubitem->next;
			}
			bzero (clubitem, sizeof (club_list_item_t));
			strcpy (clubitem->club, clubhdr.club);
			strcpy (clubitem->descr, clubhdr.descr);
		}
	}
	free (clubs);

	retstuff.result_code = 0;
	return &retstuff;
}



/* Same as previous procedure, but this one returns a long version of
   the header of one club. Security checks are the same, though, due
   to the stateless form of the server. */

struct club_header *
distclub_request_header_1_svc (club_header_request_t * clubreq,
			       struct svc_req *req)
{
	static struct club_header retstuff;
	int     i;
	struct sockaddr_in *caller = svc_getcaller (server);
	struct stat st;
	char    fname[256];


	bzero (&retstuff, sizeof (retstuff));


#ifdef DEBUG
	fprintf (stderr,
		 "Club \"%s\" header request from BBS \"%s\" for BBS \"%s\"\n",
		 clubreq->club, clubreq->codename, clubreq->targetname);
#endif


	/* Right. Is the targetted BBS registered with us? */

	if ((i = find_system (clubreq->targetname)) < 0) {
		retstuff.result_code = CLR_UNKNOWNCLUB;
		return &retstuff;
	}


	/* It is indeed. But is it really a Megistos BBS? */

	if (registered_systems[i].users_online < 0) {
		retstuff.result_code = CLR_NOTMEGISTOS;
		return &retstuff;
	}


	/* Ok, check club access. */

	this_system = &registered_systems[i];
	if (!loadclubhdr (clubreq->club)) {
		retstuff.result_code = CLR_UNKNOWNCLUB;	/* This should never happen */
		return &retstuff;
	}


	/* Is this guy allowed to see the club? */

	if (!getclubaccess (caller, clubreq->codename)) {
		retstuff.result_code = CLR_UNKNOWNCLUB;	/* This should never happen */
		return &retstuff;
	}


	/* Ok, start forming the header */

	bzero (&(retstuff.club_header_u.club), sizeof (struct club_header_t));
	strcpy (retstuff.club_header_u.club.club, clubhdr.club);
	strcpy (retstuff.club_header_u.club.descr, clubhdr.descr);
	strcpy (retstuff.club_header_u.club.clubop, clubhdr.clubop);
	retstuff.club_header_u.club.crdate = clubhdr.crdate;
	retstuff.club_header_u.club.crtime = clubhdr.crtime;

	retstuff.club_header_u.club.nmsgs = clubhdr.nmsgs;
	retstuff.club_header_u.club.nper = clubhdr.nper;
	retstuff.club_header_u.club.nblts = clubhdr.nblts;
	retstuff.club_header_u.club.nfiles = clubhdr.nfiles;
	retstuff.club_header_u.club.nfunapp = clubhdr.nfunapp;

	retstuff.club_header_u.club.msglife = clubhdr.msglife;


	/* Now we need to load the club banner. It should be smallish, so
	   we'll read it straight off and put it in a string. */

	sprintf (fname, "%s/b%s", apply_prefix (CLUBHDRDIR), clubhdr.club);
	if (stat (fname, &st)) {
		retstuff.club_header_u.club.banner = strdup ("");
	} else {
		FILE   *fp;

		if ((fp = fopen (fname, "r")) == NULL) {
			retstuff.club_header_u.club.banner = strdup ("");
		} else {
			retstuff.club_header_u.club.banner =
			    (char *) malloc (st.st_size + 1);
			retstuff.club_header_u.club.banner[0] = 0;
			fread (retstuff.club_header_u.club.banner, st.st_size,
			       1, fp);
			retstuff.club_header_u.club.banner[st.st_size] = 0;
			fclose (fp);
		}
	}

	retstuff.result_code = 0;
	return &retstuff;
}


static char *bbsprefix = NULL;


char   *
mkfname (char *fmt, ...)
{
	va_list args;
	char    tmp[2048];
	static char buf[2048];

	/* Find out our prefix */

	if (bbsprefix == NULL) {
		if (getenv ("BBSPREFIX"))
			bbsprefix = strdup (getenv ("BBSPREFIX"));
		else if (getenv ("PREFIX"))
			bbsprefix = strdup (getenv ("PREFIX"));
		else
			perror ("Neither BBSPREFIX nor PREFIX are set, bailing out.");
		/*bbsprefix = strdup (BASEDIR);*/
		/* There is no longer a hardwired fallback prefix. */
	}

	/* Prepend the prefix to the format. Chop double slashes */

	strcpy (tmp, bbsprefix);
	if (tmp[strlen (tmp) - 1] == '/')
		tmp[strlen (tmp) - 1] = 0;
	strcat (tmp, "/");
	if (fmt[0] == '/')
		strcat (tmp, &(fmt[1]));
	else
		strcat (tmp, fmt);

	/* And format the string */

	va_start (args, fmt);
	vsprintf (buf, tmp, args);
	va_end (args);

	return buf;
}


/* End of File */
