/*****************************************************************************\
 **                                                                         **
 **  FILE:     list.c                                                       **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1999.                                                **
 **  PURPOSE:  List remote clubs.                                           **
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
#include <bbsinclude.h>
#include <bbs.h>
#include <megistos/netclub.h>
#include <megistos/metaservices.h>



#if 0
#endif


void
list_clubs (char *fname, char *sysname)
{
	CLIENT *cl = NULL;
	struct club_list_request_t bbs;
	club_list_item_p p;
	club_list *result;
	char    tmp[256], *cp;


	/* Separate the hostname from the codename */

	strcpy (tmp, sysname);
	if ((cp = strchr (tmp, '/')) == NULL) {
		fprintf (stderr, "System \"%s\" has invalid name!\n", sysname);
		return;
	}

	*cp++ = 0;		/* tmp=hostname, cp=codename */


	/* Make the connection */

	if (debug)
		fprintf (stderr, "Creating RPC client for host %s\n", tmp);
	if ((cl =
	     clnt_create (tmp, METABBS_PROG, METABBS_VERS, "tcp")) == NULL) {
		clnt_pcreateerror (tmp);
		return;
	}


	/* Call the procedure */

	strcpy (bbs.codename, bbscode);
	strcpy (bbs.targetname, cp);
	if (debug)
		fprintf (stderr, "Sending club list request to %s/%s\n", tmp,
			 cp);
	if ((result = distclub_request_list_1 (&bbs, cl)) == NULL) {
		clnt_perror (cl, tmp);
		clnt_destroy (cl);
		fprintf (stderr, "RPC request wasn't answered by %s", tmp);
		return;
	}
	clnt_destroy (cl);

	if (debug || (result->result_code != 0)) {
		int     i = result->result_code;

		fprintf (stderr, "Server returns result %d (%s)\n", i,
			 i > 0 ? strerror (i) : clr_errorlist[-i]);
	}
	if (result->result_code)
		return;

	p = result->club_list_u.clubs;
	printf ("System: %s/%s\n\nClub list:\n\n", tmp, cp);
	printf ("Club name        Description\n");
	printf
	    ("-------------------------------------------------------------------------------\n");
	while (p) {
		printf ("%-16.16s %s\n", p->club, p->descr);
		p = p->next;
	}
	printf
	    ("-------------------------------------------------------------------------------\n\n");



	/* Unless this is a dry run, this is a good time to update our stored list of
	   remote clubs. */

	if (!dryrun) {
		FILE   *fp, *out;
		char    fname2[512];

		sprintf (fname2, "%s~", fname2);

		if ((fp = fopen (fname, "r")) == NULL) {
			perror ("netclub: club_list: fopen(in):");
			exit (1);
		}
		if ((out = fopen (fname2, "w")) == NULL) {
			perror ("netclub: club_list: fopen(out):");
			exit (1);
		}

		/* Copy all the non-club: entries over */

		while (!feof (fp)) {
			char    line[512];

			if (!fgets (line, sizeof (line), fp))
				break;
			if (!sameto ("club: ", line))
				fprintf (out, "%s", line);
		}

		/* Now dump the new club: entries */

		p = result->club_list_u.clubs;
		while (p) {
			fprintf (out, "club: %s %s\n", p->club, p->descr);
			p = p->next;
		}
		fclose (fp);
		fclose (out);
		if (rename (fname2, fname) < 0) {
			int     i = errno;

			fprintf (stderr,
				 "Unable to rename the import point file! errno=%d (%s)\n",
				 i, strerror (i));
		}
	}

	xdr_free ((xdrproc_t) xdr_club_list, (caddr_t) result);
}


/* End of File */
