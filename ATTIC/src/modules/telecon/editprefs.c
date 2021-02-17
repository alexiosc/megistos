/*****************************************************************************\
 **                                                                         **
 **  FILE:     editprefs.c                                                  **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 95, Version 0.5                                 **
 **  PURPOSE:  Teleconferences, preferences etc                             **
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
 * $Id: editprefs.c,v 2.0 2004/09/13 19:44:53 alexios Exp $
 *
 * $Log: editprefs.c,v $
 * Revision 2.0  2004/09/13 19:44:53  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2003/12/27 12:29:39  alexios
 * Adjusted #includes.
 *
 * Revision 1.4  2003/12/24 20:12:09  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.6  1999/07/18 21:48:36  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 0.5  1998/12/27 16:10:27  alexios
 * Added autoconf support.
 *
 * Revision 0.4  1998/07/24 10:24:49  alexios
 * Generic debugging. Migrated to bbslib 0.6.
 *
 * Revision 0.3  1997/11/06 20:06:11  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/11/05 11:14:03  alexios
 * Changed calls to audit so that they take advantage of the
 * new auditing scheme.
 *
 * Revision 0.1  1997/08/28 11:08:28  alexios
 * First registered revision. Adequate.
 *
 *
 */


static const char rcsinfo[] =
    "$Id: editprefs.c,v 2.0 2004/09/13 19:44:53 alexios Exp $";



#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "telecon.h"
#include "mbk_telecon.h"


void
editprefs ()
{
	char    tmp[256];
	int     i, nax = 0, che = 0, chx = 0;
	struct tlcuser temptlcu;

	memcpy (&temptlcu, &tlcu, sizeof (struct tlcuser));

	leavechannel ();
	usermsg (ENTEDIT);

	sprintf (inp_buffer, "%s\n%s\n%s\n",
		 temptlcu.entrystg, temptlcu.exitstg, temptlcu.topic);
	if (temptlcu.flags & TLF_BEGUNINV)
		strcat (inp_buffer, msg_get (CHANST1));
	else if (temptlcu.flags & TLF_BEGINV)
		strcat (inp_buffer, msg_get (CHANST2));
	else
		strcat (inp_buffer, msg_get (CHANST3));
	strcat (inp_buffer, "\n");
	strcat (inp_buffer,
		msg_get (temptlcu.
			 flags & TLF_STARTMAIN ? DEFCHAN1 : DEFCHAN2));
	sprintf (tmp, "\n%d\n%s\n%s\nOK\nCANCEL\n", temptlcu.chatinterval,
		 temptlcu.actions ? "on" : "off",
		 msg_get (temptlcu.colour + COLOUR1 - 1));
	strcat (inp_buffer, tmp);

	if (dialog_run ("telecon", UEDITVT, UEDITLT, inp_buffer, MAXINPLEN) !=
	    0) {
		error_log ("Unable to run data entry subsystem");
		return;
	}

	dialog_parse (inp_buffer);

	if (sameas (margv[10], "OK") || sameas (margv[10], margv[8])) {
		for (i = 0; i < 11; i++) {
			char   *s = margv[i];

			if ((i == 0) && strcmp (s, temptlcu.entrystg)) {
				strcpy (temptlcu.entrystg, s);
				che = 1;
			} else if ((i == 1) && strcmp (s, temptlcu.exitstg)) {
				strcpy (temptlcu.exitstg, s);
				chx = 1;
			} else if (i == 2)
				strcpy (temptlcu.topic, s);
			else if (i == 3) {
				int     j;

				temptlcu.flags &=
				    ~(TLF_BEGUNINV | TLF_BEGINV |
				      TLF_BEGPANEL);
				for (j = 0; j < 3; j++)
					if (!strcmp (msg_get (CHANST1 + j), s)) {
						if (!j)
							temptlcu.flags |=
							    TLF_BEGUNINV;
						else if (j == 1)
							temptlcu.flags |=
							    TLF_BEGINV;
						else
							temptlcu.flags |=
							    TLF_BEGPANEL;
						break;
					}
			} else if (i == 4) {
				if (!strcmp (msg_get (DEFCHAN1), s))
					temptlcu.flags |= TLF_STARTMAIN;
				else
					temptlcu.flags &= ~TLF_STARTMAIN;
			} else if (i == 5) {
				temptlcu.chatinterval = thisuseraux.interval;
				thisuseraux.interval = (temptlcu.chatinterval =
							atoi (s)) * 60;
			} else if (i == 6) {
				if (!key_owns (&thisuseracc, actkey)) {
					temptlcu.actions =
					    thisuseraux.actions = 0;
					prompt (ACTNAX);
				} else
					temptlcu.actions =
					    thisuseraux.actions =
					    sameas (s, "on");
			} else if (i == 7) {
				int     j;

				for (j = 0; j < 15; j++) {
					if (!strcmp (s, msg_get (COLOUR1 + j))) {
						temptlcu.colour = j + 1;
						break;
					}
				}
			}
		}

		prompt (EDITOK);

		if (che) {
			if (!key_owns (&thisuseracc, msgkey)) {
				nax = 1;
				prompt (MSGNAX);
			} else if (!usr_canpay (msgchg)) {
				prompt (MSGNCRE);
			} else {
				usr_chargecredits (msgchg);
				prompt (MSGCHE);
			}

			if (amsgch)
				audit (getenv ("CHANNEL"), AUDIT (CHMSGE),
				       thisuseracc.userid, msgchg);
		}

		if (chx) {
			if (!key_owns (&thisuseracc, msgkey)) {
				if (!nax)
					prompt (MSGNAX);
			} else if (!usr_canpay (msgchg)) {
				prompt (MSGNCRX);
			} else {
				usr_chargecredits (msgchg);
				prompt (MSGCHX);
			}

			if (amsgch)
				audit (getenv ("CHANNEL"), AUDIT (CHMSGX),
				       thisuseracc.userid, msgchg);
		}

		savetlcuser (thisuseracc.userid, &temptlcu);
		if ((i = loadtlcuser (thisuseracc.userid, &tlcu)) == 0) {
			error_fatal ("Unable to re-read tlcuser %s",
				     thisuseracc.userid);
		}

		thisuseraux.interval = temptlcu.chatinterval * 60;
		thisuseraux.colour = tlcu.colour;
	} else
		prompt (EDITCAN);

	curchannel[0] = 0;
	enterchannel (thisuseronl.telechan);
	userent (ENTTLC);
	prompt (INTRO);
	showinfo ();
}




/* End of File */
