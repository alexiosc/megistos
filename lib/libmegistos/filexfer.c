/*****************************************************************************\
 **                                                                         **
 **  FILE:     filexfer.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: B, May 95                                                    **
 **  PURPOSE:  Download and upload files using the updown interface.        **
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
 * Revision 1.6  2003/12/19 13:24:05  alexios
 * Updated include directives.
 *
 * Revision 1.5  2003/09/28 11:40:07  alexios
 * Ran indent(1) on all C source to improve readability.
 *
 * Revision 1.4  2003/08/15 18:08:45  alexios
 * Rationalised RCS/CVS ident(1) strings.
 *
 * Revision 1.3  2001/04/22 14:49:04  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.7  1999/07/18 21:01:53  alexios
 * Fixed broken TRANSIENT bits.
 *
 * Revision 0.6  1998/12/27 14:31:16  alexios
 * Added support for autoconf.
 *
 * Revision 0.5  1998/08/11 10:01:10  alexios
 * Added "transient" mode to file transfers to indicate files
 * that a module will download immediately and so cannot be
 * tagged for later download.
 *
 * Revision 0.4  1998/07/26 21:05:25  alexios
 * Added a facility for shell commands to be executed when a
 * file is (un)successfully up/downloaded.
 *
 * Revision 0.3  1997/11/06 20:03:54  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/11/06 16:52:10  alexios
 * Upgraded to the new auditing scheme. This required a couple
 * of new variables and two new arguments to setaudit().
 *
 * Revision 0.1  1997/08/26 16:35:17  alexios
 * First registered revision. Adequate.
 *
 *
 */


static const char rcsinfo[] =
    "$Id$";



#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_UNISTD_H 1
#define WANT_STRING_H 1
#define WANT_STAT_H 1
#include <megistos/bbsinclude.h>

#include <megistos/config.h>
#include <megistos/useracc.h>
#include <megistos/filexfer.h>
#include <megistos/input.h>
#include <megistos/miscfx.h>
#include <megistos/audit.h>


static int fok = (AUF_TRANSFER | AUF_INFO);
static int ffail = (AUF_TRANSFER | AUF_INFO);
static char auditsok[80] = { 0 };
static char auditdok[80] = { 0 };
static char auditsfail[80] = { 0 };
static char auditdfail[80] = { 0 };
static char cmdok[80] = { 0 };
static char cmdfail[80] = { 0 };


void
xfer_setaudit (uint32 flok, char *sok, char *dok,
	       uint32 flfail, char *sfail, char *dfail)
{
	fok = flok;
	ffail = flfail;
	strcpy (auditsok, sok ? sok : "");
	strcpy (auditdok, dok ? dok : "");
	strcpy (auditsfail, sfail ? sfail : "");
	strcpy (auditdfail, dfail ? dfail : "");
}


void
xfer_setcmd (char *ok, char *fail)
{
	strcpy (cmdok, ok ? ok : "");
	strcpy (cmdfail, fail ? fail : "");
}


int
xfer_add (char mode, char *file, char *description, int refund,
	  int credspermin)
{
	char    fname[256];
	struct stat st;
	xfer_item_t xferitem;
	FILE   *fp;

	memset (&xferitem, 0, sizeof (xferitem));

	if ((mode == FXM_DOWNLOAD || mode == FXM_TRANSIENT) &&
	    stat (file, &st))
		return 0;

	strncpy ((char *) &xferitem.magic, XFER_ITEM_MAGIC,
		 sizeof (xferitem.magic));
	xferitem.dir = mode;
	xferitem.auditfok = fok;
	xferitem.auditffail = ffail;
	strcpy (xferitem.fullname, file);
	strcpy (xferitem.description, description);
	strcpy (xferitem.auditsok, auditsok);
	strcpy (xferitem.auditdok, auditdok);
	strcpy (xferitem.auditsfail, auditsfail);
	strcpy (xferitem.auditdfail, auditdfail);
	strcpy (xferitem.cmdok, cmdok);
	strcpy (xferitem.cmdfail, cmdfail);
	xferitem.refund = refund;
	xferitem.credspermin = credspermin;

	sprintf (fname, XFERLIST, getpid ());
	if ((fp = fopen (fname, "a")) == NULL) {
		return 0;
	}
	fwrite (&xferitem, sizeof (xferitem), 1, fp);
	fclose (fp);
	return 1;
}


int
xfer_addwild (char mode, char *filespec, char *description, int refund,
	      int credspermin)
{
	char    command[1024], *dir = filespec, *wc = filespec;
	FILE   *pipe;
	int     i = 0;

	if ((wc = strrchr (filespec, '/')) != NULL)
		*(wc++) = 0;

	sprintf (command, "(find %s/ -name '%s' -maxdepth 1 -type f -print "
		 "|tr \" \" \"\\012\") 2>/dev/null", wc ? dir : ".",
		 wc ? wc : filespec);
	if ((pipe = popen (command, "r")) == NULL)
		return 0;
	while (!feof (pipe)) {
		if (fgets (command, sizeof (command), pipe)) {
			if ((wc = strchr (command, '\n')) != NULL)
				*wc = 0;
			i++;
			xfer_add (mode, command, description, refund,
				  credspermin);
		}
	}
	fclose (pipe);
	return i;
}


int
xfer_run ()
{
	char    command[256];
	int     res;

	if (cnc_more ()) {
		thisuseronl.flags |= OLF_MMCALLING;
		strcpy (thisuseronl.input, cnc_nxtcmd);
	} else
		thisuseronl.input[0] = 0;

	strcpy (command, mkfname (UPDOWNBIN " " XFERLIST " " TAGLIST,
				  getpid (), thisuseronl.userid,
				  thisuseronl.channel));

	res = runcommand (command);
	system (STTYBIN " -echo start undef stop undef intr undef susp undef");
	return res;
}


int
xfer_kill_list ()
{
	char    fname[256];

	sprintf (fname, XFERLIST, getpid ());
	return unlink (fname);
}


int
xfer_kill_taglist ()
{
	char    fname[256];

	sprintf (fname, TAGLIST, thisuseronl.userid, thisuseronl.channel);
	return unlink (fname);
}
