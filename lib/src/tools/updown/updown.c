/*****************************************************************************\
 **                                                                         **
 **  FILE:     updown.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: B, May 95, Version 0.6                                       **
 **  PURPOSE:  Upload and Download files                                    **
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
 * Revision 1.4  2003/12/23 23:20:23  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:08  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.7  1999/07/18 22:09:33  alexios
 * Changed a few error_fatal() calls to error_fatalsys(). Minor bug fixes
 * related to the handling of transient files.
 *
 * Revision 0.6  1998/12/27 16:35:21  alexios
 * Added autoconf support. Slight beautification work.
 *
 * Revision 0.5  1998/11/30 22:06:09  alexios
 * Removed useless code.
 *
 * Revision 0.4  1998/07/24 10:31:31  alexios
 * Moved to stable status. Migrated to bbslib 0.6.
 *
 * Revision 0.3  1997/11/06 20:18:32  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/09/12 13:40:19  alexios
 * Refrained from auditing logouts here -- instead flagged the
 * user as OLF_LOGGEDOUT so that bbsd will audit the proper
 * message (a natural disconnection).
 *
 * Revision 0.1  1997/08/28 11:25:42  alexios
 * First registered revision. Adequate.
 *
 *
 */


static const char rcsinfo[] =
    "$Id$";




#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_CTYPE_H 1
#define WANT_UNISTD_H 1
#define WANT_TIME_H 1
#define WANT_STRING_H 1
#define WANT_DIRENT_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include <megistos/updown.h>
#include <megistos/mbk_updown.h>


int     maxtag;
int     peffic;
char   *vprsel;
int     dissec;
int     lnkkey;
char   *lnksel;
int     refnd;
int     refper;


promptblock_t *msg;
struct protocol *protocols = NULL;
int     numprotocols = 0;
struct viewer *viewers = NULL;
int     numviewers = 0;
char   *xferlistname = NULL;
xfer_item_t *xferlist = NULL;
int     totalitems = 0;
int     numitems = 0;
char   *taglistname = NULL;
int     numtagged = 0;
int     xfertagged = 0;
int     taggedsize = 0;
int     autodis = 0;
int     logout = 0;


void
init ()
{
	mod_init (INI_ALL);
	msg = msg_open ("updown");
	msg_setlanguage (thisuseracc.language);

	peffic = msg_int (PEFFIC, 1, 100);
	vprsel = msg_string (VPRSEL);
	dissec = msg_int (DISSEC, 1, 32767);
	lnkkey = msg_int (LNKKEY, 0, 129);
	lnksel = msg_string (LNKSEL);
	refnd = msg_bool (REFND);
	refper = msg_int (REFPER, 0, 100);

	readprotocols ();
	readviewers ();
	readtransferlist (xferlistname, &numitems, 0);
	readtransferlist (taglistname, &numtagged, XFF_TAGGED);

	if (!totalitems) {
		prompt (NOFILES);
		exit (0);
	} else {
		extraprotocols ();
	}
}


void
writetagfile ()
{
	FILE   *fp;
	int     i;

	if ((fp = fopen (taglistname, "w")) == NULL) {
		error_logsys ("Unable to write tag file %s", taglistname);
		return;
	}
	for (i = 0; i < totalitems; i++) {
		if (xferlist[i].flags & XFF_KILLED)
			continue;
		if (xferlist[i].flags & XFF_TAGGED) {
			fwrite (&xferlist[i], sizeof (xfer_item_t), 1, fp);
		}
	}
	fclose (fp);

	if ((fp = fopen (xferlistname, "w")) == NULL) {
		error_logsys ("Unable to write xferlist file %s", taglistname);
		return;
	}
	fwrite (xferlist, sizeof (xfer_item_t), totalitems, fp);
	fclose (fp);
}


void
returncharges ()
{
	int     i, refund = 0;
	classrec_t *class = cls_find (thisuseracc.curclss);

	if (refnd == 0 || refper == 0)
		return;

	for (i = 0; i < totalitems; i++) {
		if ((xferlist[i].flags & (XFF_TAGGED | XFF_SUCCESS)) == 0) {
			refund += xferlist[i].refund;
		}
	}
	refund = (refund * refper) / 100;
	if (refund && ((class->flags & CLF_NOCHRGE) == 0)) {
		prompt (REFUND, refund, msg_getunit (CRDSNG, refund));
		usr_postcredits (thisuseracc.userid, refund, 0);
	}
}


void
done ()
{
	if (xferlist[firstentry].dir == FXM_DOWNLOAD ||
	    xferlist[firstentry].dir == FXM_TRANSIENT) {
		writetagfile ();
		returncharges ();
	}
	msg_close (msg);
	exit (0);
}


void
autodisconnect ()
{
	int     i;
	char    c;

	inp_nonblock ();

	prompt (DISCON);
	for (i = dissec - 1; i >= 0; i--) {
		prompt (COUNTDN, i);
		sleep (1);
		c = 0;
		if ((read (0, &c, 1) == 1) &&
		    (c == 27 || c == 13 || c == 10 || c == 32)) {
			prompt (ADABORT);
			inp_block ();
			return;
		}
	}

	inp_block ();
	print ("\n\n\n\n");
	thisuseronl.flags |= OLF_LOGGEDOUT;
	channel_disconnect (thisuseronl.emupty);
}


void
run ()
{
	switch (xferlist[0].dir) {
	case FXM_DOWNLOAD:
	case FXM_TRANSIENT:
		downloadrun ();
		break;
	case FXM_UPLOAD:
		uploadrun ();
		break;
	default:
		error_fatal ("Invalid transfer mode \"%c\"", xferlist[0].dir);
	}
}


int
main (int argc, char *argv[])
{
	mod_setprogname (argv[0]);
	if (argc != 3 && argc != 4) {
		fprintf (stderr,
			 "syntax: %s xferlist-file taglist-file [-logout]\n\n",
			 argv[0]);
		exit (-1);
	} else {
		xferlistname = argv[1];
		taglistname = argv[2];
		if (argc == 4 && (!strcmp (argv[3], "-logout")))
			logout = 1;
		else
			logout = 0;
	}

	init ();
	run ();
	done ();

	return 0;
}


/* End of File */
