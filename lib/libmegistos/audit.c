/*****************************************************************************\
 **                                                                         **
 **  FILE:     audit.c                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 94                                                 **
 **  PURPOSE:  Implement audit trail functions                              **
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
 * Revision 1.8  2003/12/24 18:35:08  alexios
 * Fixed #includes.
 *
 * Revision 1.7  2003/12/19 13:23:29  alexios
 * Updated include directives; updated some of the directory #defines.
 *
 * Revision 1.6  2003/09/28 11:40:07  alexios
 * Ran indent(1) on all C source to improve readability.
 *
 * Revision 1.5  2003/08/15 18:11:38  alexios
 * Rationalised RCS/CVS ident(1) strings.
 *
 * Revision 1.4  2001/04/22 14:49:04  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.5  1998/12/27 14:31:16  alexios
 * Added autoconf support. Made allowances for new getlinestatus().
 *
 * Revision 0.4  1997/11/06 20:03:54  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.3  1997/11/06 16:51:04  alexios
 * Slight audit filtering bug fix.
 *
 * Revision 0.2  1997/11/05 10:58:35  alexios
 * Audnotify() now accepts a flag field as well. It checks
 * whether the audit entry goes past the operator's auditing
 * filter and only then does it injoth() the entry. Audit()
 * also accepts a flag argument. It outputs it to the audit
 * trail file as well, for further filtering or report
 * generation. Stopped using varargs.h, now using stdargs.h.
 * Easier to use.
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
#define WANT_STDARG_H 1
#define WANT_SYS_SHM_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_STAT_H 1
#include <megistos/bbsinclude.h>

#include <megistos/config.h>
#include <megistos/audit.h>
#include <megistos/useracc.h>
#include <megistos/miscfx.h>
#include <megistos/sysstruct.h>
#include <megistos/output.h>
#include <megistos/prompts.h>
#include <megistos/timedate.h>
#include <megistos/bbsmod.h>
#include <megistos/ttynum.h>
#include <megistos/channels.h>
#include <megistos/security.h>
#include <megistos/miscfx.h>

#include <mbk/mbk_sysvar.h>


static char *auditfile = NULL;
static char *orig_auditfile = NULL;


void
audnotify (flags, channel, summary, detailed)
int     flags;
char   *channel, *summary, *detailed;
{
	int     i;
	struct shmuserrec *ushm = NULL;
	char    buf[MSGBUFSIZE];
	channel_status_t status;

	if (chan_count == 0)
		return;		/* Not initialised yet */

	for (i = 0; i < chan_count; i++) {
		if (!channel_getstatus (channels[i].ttyname, &status)) {
			continue;
		}

		fflush (stdout);
		if (status.result == LSR_USER) {
			if (usr_insystem (status.user, 0, &ushm)) {
				if (!ushm) {
					continue;
				}
				if (ushm->onl.flags & OLF_BUSY) {
					continue;
				}
				if (hassysaxs (&ushm->acc, USY_PAGEAUDIT) &&
				    ((flags & ushm->acc.
				      auditfiltering) & ~AUF_SEVERITY) &&
				    ((flags & ushm->acc.
				      auditfiltering) & AUF_SEVERITY)) {
					msg_set (msg_sys);
					sprompt_other (ushm, buf,
						       AUDINJI +
						       GETSEVERITY (flags),
						       channel, summary,
						       detailed);
					msg_reset ();
					usr_injoth (&ushm->onl, buf, 0);
				}
				shmdt ((char *) ushm);
			}
		}
	}
}


int
audit (char *channel, uint32 flags, char *summary, char *format, ...)
{
	va_list args;

	FILE   *fp;
	char    s[60], chanstr[32];
	char    entry[132] = { 0 };
	int     c;

	if (auditfile == NULL)
		audit_setfile (NULL);

	va_start (args, format);

	if ((fp = fopen (auditfile, "a")) == NULL)
		return 0;

	if (channel == NULL)
		channel = thisuseronl.channel;

	c = chan_getnum (channel);
	if (c != -1)
		sprintf (chanstr, "CHANNEL %02x", c);
	else
		sprintf (chanstr, "%-10s", channel);
	fflush (stdout);

	vsprintf (s, format, args);
	va_end (args);

	sprintf (entry, "%-8s %-9s (%04x) %-10s %-30s %-60s",
		 strtime (now (), 1), strdate (today ()), flags, chanstr,
		 summary, s);
	entry[120] = 0;
	fprintf (fp, "%s\n", entry);
	fclose (fp);
	chmod (auditfile, 0666);

	if (!strcmp (orig_auditfile, auditfile))
		audnotify (flags, chanstr, summary, s);

	return 1;
}


void
audit_setfile (char *s)
{
	if (auditfile == NULL) {
		auditfile = strdup (mkfname (AUDITFILE));
		orig_auditfile = strdup (auditfile);
	}
	free (auditfile);
	auditfile = strdup (s != NULL ? s : orig_auditfile);
}


void
audit_resetfile ()
{
	strcpy (auditfile, orig_auditfile);
}
