/*****************************************************************************\
 **                                                                         **
 **  FILE:     funcs.c                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1997, Version 0.1                                    **
 **  PURPOSE:  Various functions                                            **
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
 * Revision 1.5  2003/12/27 12:34:06  alexios
 * Adjusted #includes.
 *
 * Revision 1.4  2003/12/25 08:26:20  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.4  1998/12/27 15:48:12  alexios
 * Added autoconf support.
 *
 * Revision 0.3  1998/08/11 10:13:15  alexios
 * Moved hdrselect() to this file.
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
#define WANT_DIRENT_H 1
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


static int oldverticalformat;
static int ind = 0;

struct clubheader clubhdr;


int
getclub (char *club, int pr, int err, int all, int email)
{
	char   *i;
	char    c;

	for (;;) {
		fmt_lastresult = 0;
		if ((c = cnc_more ()) != 0) {
			if (sameas (cnc_nxtcmd, "X"))
				return 0;
			if (sameas (cnc_nxtcmd, "?")) {
				listclubs ();
				cnc_end ();
				continue;
			}
			i = cnc_word ();
		} else {
			prompt (pr);
			inp_get (0);
			cnc_begin ();
			i = cnc_word ();
			if (!margc) {
				cnc_end ();
				continue;
			} else if (inp_isX (margv[0]))
				return 0;
			if (sameas (margv[0], "?")) {
				listclubs ();
				cnc_end ();
				continue;
			}
		}

		if (*i == '/')
			i++;

		if (sameas (i, "ALL") & all) {
			strcpy (club, "ALL");
			return 1;
		} else if (sameas (i, omceml) && email) {
			strcpy (club, omceml);
			return 1;
		}
		if (!findclub (i)) {
			prompt (err);
			cnc_end ();
			continue;
		} else
			break;
		return 1;
	}

	strcpy (club, i);
	return 1;
}


void
listclubs ()
{
	struct dirent **clubs;
	int     n, i;

	msg_set (emailclubs_msg);
	n = scandir (mkfname (CLUBHDRDIR), &clubs, hdrselect, alphasort);
	prompt (EMAILCLUBS_LCHDR);
	for (i = 0; i < n; free (clubs[i]), i++) {
		char   *cp = &clubs[i]->d_name[1];

		if (!loadclubhdr (cp))
			continue;
		if (fmt_lastresult == PAUSE_QUIT)
			break;
		if (getclubax (&thisuseracc, cp) == CAX_ZERO)
			continue;
		prompt (EMAILCLUBS_LCTAB, clubhdr.club, clubhdr.clubop,
			clubhdr.descr);
	}
	free (clubs);
	if (fmt_lastresult == PAUSE_QUIT) {
		msg_set (mail_msg);
		return;
	}
	prompt (EMAILCLUBS_LCFTR);
	msg_set (mail_msg);
}


unsigned long
mkstol (unsigned long x)
{
	return (((x & ~0xff000000) | 0x00800000) >> (24 - ((x >> 24) & 0x7f)));
}


unsigned long
ltomks (unsigned long x)
{
	int     exp;

	exp = 0;
	if (!x)
		exp = 0x80 + 24;
	else if (x >= 0x01000000) {
		while (x & 0xff000000) {
			x >>= 1;
			exp--;
		}
	} else {
		while (!(x & 0x00800000)) {
			x <<= 1;
			exp++;
		}
	}
	return ((x & ~0x00800000) | ((24L - exp + 0x80) << 24));
}


char   *
qwkdate (int date)
{
	static char buff[32] = { 0 };
	struct tm dt = { 0 };

	dt.tm_mday = tdday (date);
	dt.tm_mon = tdmonth (date);
	dt.tm_year = tdyear (date);
	/* Two-digit year intentional -- unfortunately */
	strftime (buff, 32, "%m-%d-%y", &dt);
	return buff;
}


void
startind ()
{
	if (!prgind)
		return;
	oldverticalformat = fmt_verticalformat;
	fmt_setverticalformat (0);
	prompt (OMDLIND0);
	ind = 0;
}


void
progressind (int i)
{
	if (!prgind)
		return;
	prompt (OMDLIND1 + ind, i);
	ind = (ind + 1) % 8;
}


void
endind ()
{
	if (!prgind)
		return;
	fmt_setverticalformat (oldverticalformat);
	prompt (OMDLINDE);
}


static char inclublock[256];


void
goclub (char *club)
{
	lock_rm (inclublock);
	if (club) {
		sprintf (inclublock, INCLUBLOCK, thisuseronl.channel, club);
		lock_place (inclublock, "reading");
	}
	setclub (club);
}


void
abort ()
{
	inp_block ();
	thisuseronl.flags &= ~(OLF_BUSY | OLF_NOTIMEOUT);
	msg_set (mailer_msg);
	prompt (MAILER_ABORT);
	exit (2);
}


/* End of File */
