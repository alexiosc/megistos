/*****************************************************************************\
 **                                                                         **
 **  FILE:     metabbs.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, January 99.                                               **
 **  PURPOSE:  Register us with the Meta BBS daemon.                        **
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
 * Revision 2.0  2004/09/13 19:44:53  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.4  2004/02/29 18:25:30  alexios
 * Ran through megistos-config --oh. Various minor changes to account for
 * new directory structure.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.0  1999/07/18 21:59:36  alexios
 * Initial revision
 *
 *
 */


static const char rcsinfo[] =
    "$Id$";


#define WANT_STDIO_H 1
#define WANT_ERRNO_H 1
#include <bbsinclude.h>
#ifdef HAVE_METABBS
#  include <rpc/rpc.h>

#  include "bbs.h"
#  include "bbsd.h"
#  include "metaservices.h"
#  include "mbk_metabbs.h"


int     last_registration_time = 0;

#  define SERVERNAME "127.0.0.1"	/* We always contact the local server */



struct registration_package_t non_megistos[9];



void
init_non_megistos ()
{
	int     i, base;

	bzero (non_megistos, sizeof (non_megistos));

	/* Base is just a little hack that allows us to use
	   base+<first_system_symbol> to get the i-th element of the array from the
	   message block. */

	for (i = 0, base = 0; i < 9; i++, base += (SYS2COD - SYS1COD)) {

		/* Validate this entry first */

		if (!strlen (msg_get (base + SYS1COD)))
			continue;
		if (!strlen (msg_get (base + SYS1HST)))
			continue;


		/* Right, it seems to be valid. Obviously the MetaBBS server has the last
		   word, but we'll keep this one. */

		strcpy (non_megistos[i].codename, msg_string (base + SYS1COD));
		strcpy (non_megistos[i].bbstitle, msg_string (base + SYS1TTL));
		strcpy (non_megistos[i].company, msg_string (base + SYS1CMP));
		strcpy (non_megistos[i].address1, msg_string (base + SYS1AD1));
		strcpy (non_megistos[i].address2, msg_string (base + SYS1AD2));
		strcpy (non_megistos[i].city, msg_string (base + SYS1CTY));
		strcpy (non_megistos[i].voicephone,
			msg_string (base + SYS1VPH));
		strcpy (non_megistos[i].dataphone,
			msg_string (base + SYS1DPH));

		non_megistos[i].users_online = -1;
		non_megistos[i].lines_free = -1;
		non_megistos[i].lines_max = -1;

		non_megistos[i].hostname = msg_string (base + SYS1HST);
		non_megistos[i].port = msg_int (base + SYS1PRT, 0, 65535);
		non_megistos[i].url = msg_string (base + SYS1URL);
		non_megistos[i].email = msg_string (base + SYS1EML);
		non_megistos[i].bbs_ad = msg_string (base + SYS1ADV);
		non_megistos[i].access_allow = msg_string (base + SYS1ALW);
		non_megistos[i].access_deny = msg_string (base + SYS1DNY);

		non_megistos[i].flags = !msg_bool (base + SYS1HUP);
		non_megistos[i].bbs_uid = -1;
		non_megistos[i].bbs_gid = -1;
		non_megistos[i].bbsd_pid = (int) getpid ();
		non_megistos[i].prefix = strdup (mkfname (""));

#  ifdef DEBUG
		fprintf (stderr,
			 "Non-megistos entry #%d: cod=\"%s\" ttl=\"%s\" hst=\"%s\""
			 " port=%d, bbsd_pid=%d\n",
			 i, non_megistos[i].codename, non_megistos[i].bbstitle,
			 non_megistos[i].hostname, non_megistos[i].port,
			 non_megistos[i].bbsd_pid);
#  endif
	}
}



void
register_with_metabbs ()
{
	static CLIENT *cl = NULL;
	struct registration_package_t reg;
	int    *result, i;


#  ifdef DEBUG
	fprintf (stderr, "Time to do METABBS (re-)registration.\n");
#  endif


	if (!telnet_port) {	/* Disabled MetaBBS */
#  ifdef DEBUG
		fprintf (stderr, "MetaBBS is disabled, bailing out.\n");
#  endif
		return;
	}



	/* Create the client */

	if (cl == NULL) {
		cl = clnt_create (SERVERNAME, METABBS_PROG, METABBS_VERS,
				  "tcp");
		if (cl == NULL) {

#  ifdef DEBUG
			fprintf (stderr,
				 "Failed to create client! RPC error follows.\n");
			clnt_pcreateerror (SERVERNAME);
#  endif

			return;
		}
	}



	/* Create our information package */

	bzero (&reg, sizeof (reg));

	strcpy (reg.codename, bbscod);
	strcpy (reg.bbstitle, sysvar->bbstitle);
	strcpy (reg.company, sysvar->company);
	strcpy (reg.address1, sysvar->address1);
	strcpy (reg.address2, sysvar->address2);
	strcpy (reg.city, sysvar->city);
	strcpy (reg.dataphone, sysvar->dataphone);
	strcpy (reg.voicephone, sysvar->voicephone);
	reg.users_online = numusers;
	reg.lines_free = lines_free;
	reg.lines_max = sysvar->tnlmax;
	reg.flags = 0;

	reg.hostname = strdup ("");	/* MetaBBS will overwrite this anyway */
	reg.port = telnet_port;
	reg.url = strdup (url);
	reg.email = strdup (email);
	reg.access_allow = strdup (allow);
	reg.access_deny = strdup (deny);
	reg.bbs_ad = (char *) alcmem (min (8192, strlen (bbsad) + 1));
	strncpy (reg.bbs_ad, bbsad, min (8192, strlen (bbsad) + 1));
	reg.bbs_ad[min (8191, strlen (bbsad))] = 0;

	reg.bbs_uid = bbsuid;
	reg.bbs_gid = bbsgid;
	reg.bbsd_pid = (int) getpid ();
	reg.prefix = strdup (mkfname (""));

	result = metabbs_register_1 (&reg, cl);

	free (reg.url);
	free (reg.email);
	free (reg.access_allow);
	free (reg.access_deny);
	free (reg.bbs_ad);
	free (reg.prefix);

	if (result == NULL) {
#  ifdef DEBUG
		fprintf (stderr, "Failed to register, RPC error below:\n");
		clnt_perror (cl, SERVERNAME);
		return;
#  endif
	} else
		last_registration_time = time (NULL);

#  ifdef DEBUG
	if (*result != 0) {
		fprintf (stderr,
			 "Failed to register, (daemon error, retval=%d)\n",
			 *result);
	} else {
		fprintf (stderr, "Registration ok.\n");
	}

	fprintf (stderr, "Now registering non-Megistos systems:\n");
#  endif


	for (i = 0; i < 9; i++) {
		if (non_megistos[i].codename[0] == 0)
			continue;	/* Empty entry */

#  ifdef DEBUG
		fprintf (stderr, "Entry #%d (%s): (re-)registering...\n",
			 i, non_megistos[i].codename);
#  endif

		non_megistos[i].bbsd_pid = (int) getpid ();	/* Need to update this */

		result =
		    metabbs_register_non_megistos_1 (&non_megistos[i], cl);

#  ifdef DEBUG
		if (result == NULL) {
			fprintf (stderr,
				 "Failed to register, RPC error below:\n");
			clnt_perror (cl, SERVERNAME);
		} else if (*result != 0) {
			fprintf (stderr,
				 "\tEntry #%d (%s): failed to register, (daemon error, retval=%d)\n",
				 i, non_megistos[i].codename, *result);
		} else {
			fprintf (stderr,
				 "\tEntry #%d (%s): Registration ok.\n", i,
				 non_megistos[i].codename);
		}
#  endif

	}

#  ifdef DEBUG
	fprintf (stderr, "Registration(s) done.\n");
#  endif
}


#endif				/* HAVE_METABBS */


/* End of File */
