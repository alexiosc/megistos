/*****************************************************************************\
 **                                                                         **
 **  FILE:     attach-to-email.c                                            **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, November 1998, Version 1.0 (and that's it!)               **
 **  PURPOSE:  Handle 'Edit' uploads                                        **
 **  NOTES:    Attaches a single file to an email message as an indirect    **
 **            means of downloading it.                                     **
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
 * $Id: attach-to-email.c,v 2.0 2004/09/13 19:44:54 alexios Exp $
 *
 * $Log: attach-to-email.c,v $
 * Revision 2.0  2004/09/13 19:44:54  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2004/02/29 17:46:31  alexios
 * One slight change in structure naming to account for the new library.
 *
 * Revision 1.4  2003/12/23 06:38:04  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.0  1998/12/27 16:29:34  alexios
 * Initial revision
 *
 *
 */


static const char rcsinfo[] = "$Id: attach-to-email.c,v 2.0 2004/09/13 19:44:54 alexios Exp $";




#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>


int
main (int argc, char **argv)
{
	FILE      *fp;
	int        res;
	message_t  msg;
	char       command[1024], header[256], body[256];

	if (argc != 2) {
		fprintf (stderr, "%s: syntax: %s filename\n", argv[0],
			 argv[0]);
		exit (1);
	}

	if (!getenv ("USERID")) {
		fprintf (stderr, "%s: must be running in BBS user context!\n",
			 argv[0]);
		exit (2);
	}

	memset (&msg, 0, sizeof (msg));
	strcpy (msg.from, getenv ("USERID"));
	strcpy (msg.to, msg.from);
	strcpy (msg.subject, argv[1]);
	strcpy (msg.fatt, msg.subject);
	msg.flags |= MSF_FILEATT | MSF_APPROVD;

	/* Write an empty body */

	sprintf (body, "/tmp/attb-%d", getpid ());
	if ((fp = fopen (body, "w")) == NULL) {
		fprintf (stderr, "%s: Unable to create %s\n", argv[0], body);
		exit (3);
	}
	fclose (fp);


	/* Write the header */

	sprintf (header, "/tmp/atth-%d", getpid ());
	if ((fp = fopen (header, "w")) == NULL) {
		fprintf (stderr, "%s: Unable to create %s\n", argv[0], header);
		exit (4);
	}
	if (fwrite (&msg, sizeof (msg), 1, fp) != 1) {
		fprintf (stderr, "%s: Unable to write %s\n", argv[0], header);
		exit (4);
	}
	fclose (fp);


	/* Send the message */

	sprintf (command, "%s %s %s -c %s", mkfname (BBSMAILBIN), header, body,
		 msg.fatt);
	res = system (command);


	/* Re-read the header to get the message number */

	sprintf (header, "/tmp/atth-%d", getpid ());
	if ((fp = fopen (header, "r")) == NULL) {
		fprintf (stderr, "%s: Unable to create %s\n", argv[0], header);
		exit (4);
	}
	if (fread (&msg, sizeof (msg), 1, fp) != 1) {
		fprintf (stderr, "%s: Unable to read from %s\n", argv[0],
			 header);
		exit (4);
	}
	fclose (fp);


	/* Notify the user (primitive for the time being) */

	fprintf (stderr, "%s -> Email/%d: OK!\n", msg.fatt, msg.msgno);


	/* Clean up */
	unlink (header);
	unlink (body);
	if (!res)
		unlink (msg.fatt);


	/* And exit nicely */
	return res;
}


/* End of File */
