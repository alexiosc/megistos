/*****************************************************************************\
 **                                                                         **
 **  FILE:     clubs.c                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1995, Version 0.5                                    **
 **            B, August 1996, Version 0.6                                  **
 **  PURPOSE:  Main module for the Clubs (SIGs)                             **
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
 * Revision 1.5  2003/12/25 13:33:28  alexios
 * Fixed #includes. Changed instances of struct message to
 * message_t. Other minor changes.
 *
 * Revision 1.4  2003/12/24 20:12:14  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.6  1999/07/18 21:21:38  alexios
 * Added support for the network manager menu.
 *
 * Revision 0.5  1998/12/27 15:33:03  alexios
 * Added autoconf support. Added code to enter bulletins from
 * within the main club menu (at last).
 *
 * Revision 0.4  1998/08/11 10:03:22  alexios
 * Added msg parameters to set the default accesses for new
 * clubs.
 *
 * Revision 0.3  1998/07/24 10:17:37  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:05:26  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 10:21:30  alexios
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
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "mbk_emailclubs.h"

#define __CLUBS_C
#include "clubs.h"
#include "email.h"


promptblock_t *msg;


int     entrykey;
int     sopkey;
int     wrtkey;
int     netkey;
int     rrrkey;
int     attkey;
int     dnlchg;
int     wrtchg;
int     netchg;
int     rrrchg;
int     attchg;
int     mkaudd;
int     mkaudu;
int     maxccs;
int     emllif;
int     msglen;
char   *eattupl;
int     sigbmax;
int     siglmax;
int     sigckey;
int     sigchg;
int     afwkey;
int     dlkey;
int     maxdlm;
int     msskey;
int     tlckey;
int     bltkey;
char   *tlcpag;
char   *bltpag;
int     addnew;
int     drdaxkey;
int     ddlaxkey;
int     dwraxkey;
int     dulaxkey;

int     defaultrate;



void
init ()
{
	mod_init (INI_ALL);
	msg = msg_open ("emailclubs");
	msg_setlanguage (thisuseracc.language);

	defaultrate = thisuseronl.credspermin;
	strcpy (inclublock, "dummy");

	entrykey = msg_int (ENTRYKEY, 0, 129);
	sopkey = msg_int (SOPKEY, 0, 129);
	wrtkey = msg_int (WRTKEY, 0, 129);
	netkey = msg_int (NETKEY, 0, 129);
	rrrkey = msg_int (RRRKEY, 0, 129);
	attkey = msg_int (ATTKEY, 0, 129);
	dnlchg = msg_int (DNLCHG, -32767, 32767);
	wrtchg = msg_int (WRTCHG, -32767, 32767);
	netchg = msg_int (NETCHG, -32767, 32767);
	rrrchg = msg_int (RRRCHG, -32767, 32767);
	attchg = msg_int (ATTCHG, -32767, 32767);
	mkaudd = msg_bool (MKAUDD);
	mkaudu = msg_bool (MKAUDU);
	emllif = msg_int (EMLLIF, -1, 32767);
	maxccs = msg_int (MAXCCS, 0, 32767);
	msglen = msg_int (MSGLEN, 1, 256) << 10;
	eattupl = msg_string (EATTUPL);
	sigbmax = msg_int (SIGBMAX, 16, 1024);
	siglmax = msg_int (SIGLMAX, 1, 32);
	sigckey = msg_int (SIGCKEY, 0, 129);
	sigchg = msg_int (SIGCHG, -32767, 32767);
	afwkey = msg_int (AFWKEY, 0, 129);
	dlkey = msg_int (DLKEY, 0, 129);
	maxdlm = msg_int (MAXDLM, 2, 256);
	msskey = msg_int (MSSKEY, 0, 129);
	tlckey = msg_int (TLCKEY, 0, 129);
	bltkey = msg_int (BLTKEY, 0, 129);
	tlcpag = msg_string (TLCPAG);
	bltpag = msg_string (BLTPAG);

	clntrkey = msg_int (CLNTRKEY, 0, 129);
	clsopkey = msg_int (CLSOPKEY, 0, 129);
	tlckey = msg_int (TLCKEY, 0, 129);
	bltkey = msg_int (BLTKEY, 0, 129);
	clbwchg = msg_int (CLBWCHG, -32767, 32767);
	clbuchg = msg_int (CLBUCHG, -32767, 32767);
	clbdchg = msg_int (CLBDCHG, -32767, 32767);
	clblif = msg_int (CLBLIF, 0, 32767);
	cdnlaud = msg_bool (CDNLAUD);
	cuplaud = msg_bool (CUPLAUD);
	defclub = msg_string (DEFCLUB);
	bzero (defaultclub, sizeof (defaultclub));
	strncpy (defaultclub, defclub, sizeof (defaultclub));
	if (*defclub == '/')
		defclub++;
	modaxkey = msg_int (MODAXKEY, 0, 129);
	modchkey = msg_int (MODCHKEY, 0, 129);
	modhdkey = msg_int (MODHDKEY, 0, 129);
	drdaxkey = msg_int (DRDAXKEY, 0, 129);
	ddlaxkey = msg_int (DDLAXKEY, 0, 129);
	dwraxkey = msg_int (DWRAXKEY, 0, 129);
	dulaxkey = msg_int (DULAXKEY, 0, 129);
	addnew = msg_bool (ADDNEW);

	initlist ();
	initecsubstvars ();
}


void
about ()
{
	prompt (CLABOUT);
}


void
information ()
{
	showbanner ();
	prompt (CLINFO);
}



int
selectclub ()
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
			prompt (SCASK);
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

		if (!findclub (i)) {
			prompt (SCERR);
			cnc_end ();
			continue;
		} else
			break;
	}

	strcpy (thisuseracc.lastclub, i);
	enterdefaultclub ();
	return 1;
}


void
run ()
{
	int     shownmenu = 0;
	int     shownbanner = 0;
	int     access = CAX_ZERO;
	char    c = 0;

	if (!key_owns (&thisuseracc, clntrkey)) {
		prompt (CLNONTR);
		return;
	}

	if (!thisuseracc.lastclub[0])
		strcpy (thisuseracc.lastclub, defclub);
	if (!findclub (defclub)) {
		error_fatal ("Default club %s does not exist!", defclub);
	}

	rmlocks ();

	for (;;) {
		enterdefaultclub ();
		access = getclubax (&thisuseracc, clubhdr.club);

		thisuseronl.flags &= ~OLF_BUSY;
		if (!
		    (thisuseronl.flags & OLF_MMCALLING &&
		     thisuseronl.input[0])) {
			if (!shownbanner) {
				showbanner ();
				shownbanner = 1;
			}
			if (!shownmenu) {
				switch (access) {
				case CAX_SYSOP:
				case CAX_CLUBOP:
					prompt (CLMNU3, clubhdr.nfunapp);
					break;
				case CAX_COOP:
					prompt (CLMNU2, clubhdr.nfunapp);
					break;
				default:
					prompt (CLMNU1, clubhdr.nfunapp);
					break;
				}
				shownmenu = 2;
			}
		} else
			shownmenu = 1;
		if (thisuseronl.flags & OLF_MMCALLING && thisuseronl.input[0]) {
			thisuseronl.input[0] = 0;
		} else {
			if (cnc_nxtcmd == NULL) {
				if (thisuseronl.flags & OLF_MMCONCAT) {
					thisuseronl.flags &= ~OLF_MMCONCAT;
					return;
				}
				if (shownmenu == 1) {
					switch (access) {
					case CAX_SYSOP:
					case CAX_CLUBOP:
						prompt (SHCLMNU3);
						break;
					case CAX_COOP:
						prompt (SHCLMNU2);
						break;
					default:
						prompt (SHCLMNU1);
						break;
					}
				} else
					shownmenu = 1;
				inp_get (0);
				cnc_begin ();
			}
		}

		if ((c = cnc_more ()) != 0) {
			cnc_chr ();
			shownbanner = 1;
			switch (c) {
			case 'H':
				about ();
				cnc_end ();
				break;
			case 'I':
				information ();
				cnc_end ();
				break;
			case 'S':
				if (selectclub ())
					shownbanner = 0;
				thisuseronl.flags &= ~OLF_MMCONCAT;
				if (!cnc_more ())
					cnc_end ();
				break;
			case 'L':
				longlistclubs ();
				cnc_end ();
				break;
			case 'W':
				clubwrite ();
				cnc_end ();
				break;
			case 'R':
				clubread (0);
				cnc_end ();
				break;
			case 'D':
				clubread (1);
				cnc_end ();
				break;
			case 'A':
				if (access >= CAX_COOP)
					fileapp ();
				else
					prompt (ERRSEL, c);
				cnc_end ();
				break;
			case 'O':
				if (access >= CAX_CLUBOP)
					operations ();
				else
					prompt (ERRSEL, c);
				cnc_end ();
				break;
#ifdef HAVE_METABBS
			case 'N':
				if (access >= CAX_CLUBOP)
					networking ();
				else
					prompt (ERRSEL, c);
				cnc_end ();
				break;
#endif
			case 'T':
				if (key_owns (&thisuseracc, tlckey)) {
					sprintf (thisuseronl.telechan, "/%s",
						 clubhdr.club);
					gopage (tlcpag);
				} else
					prompt (TLCNAX);
				cnc_end ();
				break;
			case 'B':
				if (key_owns (&thisuseracc, bltkey)) {
					thisuseronl.flags |= OLF_JMP2BLT;
					gopage (bltpag);
				} else
					prompt (BLTNAX);
				cnc_end ();
				break;
			case 'X':
				prompt (CLLEAVE);
				return;
			case '?':
				shownmenu = 0;
				cnc_end ();
				break;
			default:
				prompt (ERRSEL, c);
				cnc_end ();
				continue;
			}
		}
		if (fmt_lastresult == PAUSE_QUIT)
			fmt_resetvpos (0);
		if (!cnc_more ())
			cnc_end ();
	}
}


void
done ()
{
	if (uqsc)
		saveqsc ();
	lock_rm (inclublock);
	rmlocks ();
}


int
handler_run (int argc, char *argv[])
{
	atexit (done);
	init ();
	run ();
	return 0;
}



/* The Clubs module lacks a few handlers because they are implemented
   by its sister-module, Email. */

mod_info_t mod_info_clubs = {
	"clubs",
	"Discussion groups",
	"Alexios Chouchoulas <alexios@vennea.demon.co.uk>",
	"Read/write public (`club') BBS messages organised by topic.",
	RCS_VER,
	"1.0",
	{0, NULL}
	,			/* Login handler */
	{0, handler_run}
	,			/* Interactive handler */
	{0, NULL}
	,			/* Install logout handler */
	{0, NULL}
	,			/* Hangup handler */
	{0, NULL}
	,			/* Cleanup handler */
	{0, NULL}		/* Delete user handler */
};


int
main (int argc, char *argv[])
{

#if 0
	if (strstr (argv[0], "msgcnv"))
		return msgcnv_main (argc, argv);
#endif

	mod_setinfo (&mod_info_clubs);
	return mod_main (argc, argv);
}


/* End of File */
