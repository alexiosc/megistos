/*****************************************************************************\
 **                                                                         **
 **  FILE:     request_info.c                                               **
 **  AUTHORS:  Alexios                                                      **
 **  PURPOSE:  Meta-daemon for networking/distributing BBSs over networks.  **
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
 * Revision 1.4  2003/12/23 08:22:30  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.2  2000/01/08 12:17:03  alexios
 * Added an alarm() call to set a timeout, just in case.
 *
 * Revision 1.1  1999/07/28 23:16:48  alexios
 * Slight changes of semantics.
 *
 * Revision 1.0  1999/07/18 22:05:10  alexios
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
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

#include "metaservices.h"
#include "metabbs.h"


#define SYSTEM_EXPIRY (6*60)


int
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
try_match (struct hostent *caller, char *tok)
{
	int     i;


	/* Check against main hostname */

#ifdef DEBUG
	fprintf (stderr, "ACL: comparing \"%s\" , \"%s\"\n", caller->h_name,
		 tok);
#endif

	if (sameas (caller->h_name, tok))
		return 1;



	/* Check against aliases */

	for (i = 0; caller->h_aliases[i]; i++) {

#ifdef DEBUG
		fprintf (stderr, "ACL: comparing \"%s\" , \"%s\"\n",
			 caller->h_aliases[i], tok);
#endif

		if (sameas (caller->h_aliases[i], tok))
			return 1;
	}


	/* Check against IP addresses */

	{
		struct in_addr tokaddr;

		if (inet_aton (tok, &tokaddr))
			for (i = 0; caller->h_addr_list[i]; i++) {

#ifdef DEBUG
				char   *a =
				    inet_ntoa (*
					       ((struct in_addr *) caller->
						h_addr_list[i]));
				fprintf (stderr,
					 "ACL: comparing \"%s\" , \"%s\"\n", a,
					 tok);
#endif

				if (!memcmp
				    (&tokaddr, caller->h_addr_list[i],
				     sizeof (tokaddr)))
					return 1;
			}
	}

	return 0;
}



int
match_acl (char *acl, struct sockaddr_in *client, char *codename)
{
	/* Find out exactly who the caller is */

	struct hostent *caller;
	char   *tmp = strdup (acl), *cp;

#ifdef DEBUG
	fprintf (stderr, "Resolving hostname... (addr=%08x)\n",
		 client->sin_addr.s_addr);
#endif

	if ((caller = gethostbyaddr ((char *) &(client->sin_addr),
				     sizeof (struct in_addr),
				     AF_INET)) == NULL) {
#ifdef DEBUG
		int     i = errno;

		fprintf (stderr, "Resolution failed, errno=%d (%s)\n", i,
			 strerror (i));
#endif

		return errno;
	}
#ifdef DEBUG
	fprintf (stderr, "Caller hostent:\n\n");
	fprintf (stderr, "address:  %s\n", inet_ntoa (client->sin_addr));
	fprintf (stderr, "hostname: %s\n", caller->h_name);
	fprintf (stderr, "aliases:  ");
	{
		int     i;

		for (i = 0; caller->h_aliases[i]; i++)
			fprintf (stderr, "%s ", caller->h_aliases[i]);
	}
	fprintf (stderr, "\n");
	fprintf (stderr, "length:   %d\n", caller->h_length);
	fprintf (stderr, "addrs:    ");
	{
		int     i;

		for (i = 0; caller->h_addr_list[i]; i++)
			fprintf (stderr, "%s ",
				 inet_ntoa (*
					    ((struct in_addr *) caller->
					     h_addr_list[i])));
	}
	fprintf (stderr, "\n\nACL=\"%s\"\n", tmp);
#endif


	if ((cp = strtok (tmp, " \t\n\r")) == NULL)
		return -1;	/* Empty */
	do {

		/* Check for HOSTNAME/CODENAME syntax first -- easier to just
		   check codename. If there's a codename part in the token, then
		   if the token codename and the caller codename differ, we can't
		   possibly have a match. Hence we don't even try to compare the
		   hostname parts. */

		char   *cn;

		if ((cn = strchr (tmp, '/')) != NULL) {
			if (!sameas (++cn, codename))
				continue;
			else
				return 1;
		}


		/* Oh well, no effort saved this time. Go on, compare the hostname
		   parts. */

		if (try_match (caller, cp))
			return 1;


	} while ((cp = strtok (NULL, " \t\n\r")) != NULL);
	free (tmp);

	return 0;
}



/* Convert a registration package to an information package by
   omitting some useless (or downright dangerous) fields. The function
   allocates the necessary space and returns a pointer to it. */

static  info_package_p
reg_to_info (struct registration_package_t *bbs)
{
	info_package_p retval =
	    (info_package_p) malloc (sizeof (struct info_package_t));

	bzero (retval, sizeof (struct info_package_t));
	strcpy (retval->codename, bbs->codename);
	strcpy (retval->bbstitle, bbs->bbstitle);
	strcpy (retval->company, bbs->company);
	strcpy (retval->address1, bbs->address1);
	strcpy (retval->address2, bbs->address2);
	strcpy (retval->city, bbs->city);
	strcpy (retval->dataphone, bbs->dataphone);
	strcpy (retval->voicephone, bbs->voicephone);

	retval->hostname = strdup (bbs->hostname);
	retval->port = bbs->port;
	retval->url = strdup (bbs->url);
	retval->email = strdup (bbs->email);
	retval->bbs_ad = strdup (bbs->bbs_ad);
	retval->next = NULL;

	if (bbs->flags & SFL_NON_MEGISTOS) {

		/* Non Megistos systems don't offer an easy way to get these. At the
		   client's end, a <0 check is a legitimate method (and the only one, right
		   now) of detecting whether a package refers to a Megistos BBS or some
		   other system. */

		retval->users_online = -1;
		retval->lines_free = -1;
		retval->lines_max = -1;

		retval->disconnect = ((bbs->flags & SFL_DONT_DISCONNECT) != 0);

	} else {

		retval->users_online = bbs->users_online;
		retval->lines_free = bbs->lines_free;
		retval->lines_max = bbs->lines_max;
		retval->disconnect = 1;
	}

	return retval;
}



/* Cute little recursive function (obsolete, using XDR now) */

#if 0
static void
deallocate (info_package_p p)
{
	if (p != NULL)
		deallocate (p->next);
	free (p);
}
#endif



/* This builds a linked list of all BBS information packs the caller
   is allowed to login to. For this, we require the caller's hostname
   and its BBS codename (passed as an argument). */

info_package_p *
metabbs_request_info_1_svc (char **codename, struct svc_req *req)
{
	static info_package_p retstuff = NULL;
	info_package_p current = retstuff;
	struct sockaddr_in *caller = svc_getcaller (server);
	int     i;
	int     t = time (NULL);


	/* Set a reasonable timeout */

	alarm (60);


	if (retstuff != NULL)
		xdr_free ((xdrproc_t) xdr_info_package_p,
			  (caddr_t) & retstuff);
	/*deallocate(retstuff);  Booh, can't use that cure function now */
	retstuff = NULL;


#ifdef DEBUG
	fprintf (stderr,
		 "Processing request for information from BBS \"%s\"\n",
		 *codename);
	fprintf (stderr, "BBSs running here: %d\n", num_systems);
#endif

	for (i = 0; i < num_systems; i++) {
		register struct registration_package_t *bbs =
		    &registered_systems[i];

#ifdef DEBUG
		fprintf (stderr, "Checking registration for %s (%s)\n",
			 bbs->codename, bbs->bbstitle);
#endif

		/* Has the registration expired? bbsd re-registers every five
		   minutes, so we'll expire after six. */

		if ((t - bbs->regtime) > SYSTEM_EXPIRY)
			continue;


		/* See if there's a match in the "allow" access list (empty means
		   "free for all") */

#ifdef DEBUG
		fprintf (stderr, "CHECKING ALLOW LIST\n");
#endif
		if (match_acl (bbs->access_allow, caller, *codename) == 0)
			continue;


		/* Likewise, check the "deny" list. An empty list has normal
		   semantics here: no site is excluded. */

#ifdef DEBUG
		fprintf (stderr, "CHECKING DENY LIST\n");
#endif
		if (match_acl (bbs->access_deny, caller, *codename) == 1)
			continue;


		/* Is it full? Busy sites aren't reported. */

		if (bbs->lines_free == 0)
			continue;


		/* Has it disabled MetaBBS access? */

		if (bbs->port == 0)
			continue;


		/* Ok, add it to the linked list. */

		if (retstuff == NULL) {
			retstuff = current = reg_to_info (bbs);
		} else {
			info_package_p tmp = reg_to_info (bbs);

			current->next = tmp;
			current = tmp;
		}
	}

	return &retstuff;
}


/* End of File */
