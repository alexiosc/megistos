/*****************************************************************************\
 **                                                                         **
 **  FILE:     attachments.c                                                **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1997, Version 0.1                                    **
 **  PURPOSE:  Inserting file attachments into QWK packets                  **
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
 * Revision 1.5  2003/12/27 12:33:53  alexios
 * Adjusted #includes. Changed struct message to message_t.
 *
 * Revision 1.4  2003/12/25 08:26:20  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.5  1999/08/07 02:17:20  alexios
 * Fixed easy but annoying bug that caused endless loops while
 * downloading file attachments.
 *
 * Revision 0.4  1998/12/27 15:48:12  alexios
 * Added autoconf support.
 *
 * Revision 0.3  1998/07/24 10:20:56  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:06:43  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 10:55:29  alexios
 * First registered revision. Adequate.
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
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "offline.mail.h"
#include <mailerplugins.h>
#include "mbk_offline.mail.h"

#define __MAILER_UNAMBIGUOUS__
#include <mbk/mbk_mailer.h>

#define __EMAILCLUBS_UNAMBIGUOUS__
#include <mbk/mbk_emailclubs.h>



static char
attmenu ()
{
	char    c;

	cnc_end ();
	for (;;) {
		fmt_lastresult = 0;
		inp_get (1);
		if (!margc)
			return 0;
		cnc_begin ();
		c = toupper (cnc_chr ());
		cnc_end ();
		if (margc && inp_isX (margv[0]))
			return 'X';
		else if (margc && (c == '?' || sameas (margv[0], "?"))) {
			return '?';
		} else if (strchr ("YNAOPM", c))
			return toupper (c);
		else {
			prompt (QWKCPER);
			return 0;
		}
	}
	return 0;
}


void
previewheader (struct reqidx *idx)
{
	message_t msg;

	goclub (sameas (idx->reqarea, EMAILCLUBNAME) ? NULL : idx->reqarea);
	getmsgheader (idx->msgno, &msg);
	prompt (QWKCPHH);
	msg_set (emailclubs_msg);
	showheader (idx->reqarea, &msg);
	msg_set (mail_msg);
	prompt (QWKCPHF);
	prompt (QWKCPHD);
}


void
doatt ()
{
	struct reqidx idx;
	int     res;
	int     p = -1;
	int     warn = 0;
	int     lock = 0;
	int     shown = 0;
	char    opt;

	res = getfirstreq (&idx);

	while (res) {
		struct stat st;

		if (idx.reqflags & RQF_INVIS)
			goto next;

		if (!shown) {
			shown = 1;
			prompt (QWKCOPY);
		}

		if (p != idx.priority) {
			switch (p = idx.priority) {
			case RQP_POSTPONE:
				prompt (QWKCPPPN);
				break;
			case RQP_ATT:
				prompt (QWKCPATT);
				break;
			case RQP_ATTREQ:
				prompt (QWKCPREQ);
				break;
			default:
				prompt (QWKCPOTH);
			}
			prompt (QWKCPHD);
		}
		if (idx.priority != RQP_ATT)
			warn++;


		/* Stat the file and report size if found */

		if (stat (idx.reqfname, &st)) {
			prompt (QWKCPTB, idx.dosfname, idx.reqarea, 0);
			prompt (QWKCPNF);
			goto next;
		}

		/* Insert attachment into the packet */

		opt = 0;
		if (idx.priority == RQP_ATT) {
			if (prefs.flags & OMF_ATTASK)
				opt = 0;
			else if (prefs.flags & OMF_ATTYES)
				opt = 'Y';
			else
				opt = 'I';
		} else {
			if (prefs.flags & OMF_REQASK)
				opt = 0;
			else if (prefs.flags & OMF_REQYES)
				opt = 'Y';
			else
				opt = 'I';
		}
		if (lock)
			opt = lock == 'A' ? 'Y' : 'N';

		if (opt)
			prompt (QWKCPTB, idx.dosfname, idx.reqarea,
				st.st_size);

		/* Ask user about what to do with file */

		else if (!opt)
			for (;;) {
				prompt (QWKCPTB, idx.dosfname, idx.reqarea,
					st.st_size);
				prompt (QWKCPAC);

				opt = attmenu ();
				if (opt == '?') {
					prompt (QWKASKH);
					prompt (QWKCPHD);
					continue;
				} else if (!opt) {
					prompt (QWKCPER);
					continue;
				} else if (opt == 'M')
					previewheader (&idx);
				else if (opt == 'X')
					abort ();
				else
					break;
			}

		if (opt == 'A' || opt == 'O') {
			lock = opt;
			opt = lock == 'A' ? 'Y' : 'N';
		}

		switch (opt) {

			/* Copying files to the QWK packet */

		case 'Y':

			/* Enter the club and check for download permissions */

			if (sameas (idx.reqarea, EMAILCLUBNAME)) {
				goclub (NULL);
			} else {
				goclub (idx.reqarea);
				if (getclubax (&thisuseracc, idx.reqarea) <
				    CAX_DNLOAD) {
					prompt (QWKCPNA);
					break;
				} else {
					message_t msg;

					/* Check if the file is approved */

					bzero (&msg, sizeof (msg));
					getmsgheader (idx.msgno, &msg);
					if ((msg.flags & MSF_APPROVD) == 0 &&
					    getclubax (&thisuseracc,
						       msg.club) < CAX_COOP) {
						prompt (QWKCPAP);
						break;
					}
				}
			}

			/* Copy the file into the packet */

			prompt (QWKCPCP);
			if (fcopy (idx.reqfname, idx.dosfname))
				prompt (QWKCPIO);
			prompt (QWKCPOK);

			/* Remove the current request from the database */

			if (!rmrequest (&idx)) {
				error_fatal
				    ("Unable to remove request %d from the database.",
				     idx.reqnum);
			}
			break;


			/* Aborting files */

		case 'N':

			if (!rmrequest (&idx)) {
				error_fatal
				    ("Unable to remove request %d from the database.",
				     idx.reqnum);
			}
			prompt (QWKCPCA);
			break;


			/* Postponing files  */

		default:

			/* Just change the priority and update the record */

			idx.reqflags |= RQF_POSTPONE;
			if (idx.priority == RQP_ATT)
				idx.priority = RQP_POSTPONE;
			if (!updrequest (&idx)) {
				error_fatal ("Unable to update request %d.",
					     idx.reqnum);
			}
			prompt (QWKCPPO);
		}


		/* Process next request */

	      next:
		res = getnextreq (&idx);
	}

	if (warn && (prefs.flags & OMF_REQ) == 0)
		prompt (ATTLEFT);
}


/* End of File */
