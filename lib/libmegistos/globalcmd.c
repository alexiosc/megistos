/*****************************************************************************\
 **                                                                         **
 **  FILE:     globalcmd.c                                                  **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 94                                                   **
 **  PURPOSE:  Handle BBS global commands                                   **
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
 * Revision 2.0  2004/09/13 19:44:34  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.9  2004/02/29 17:14:33  alexios
 * Removed the (previously hardwired and absolute) path to the GCS
 * modules, replaced with a parametric value.
 *
 * Revision 1.8  2003/12/24 18:35:08  alexios
 * Fixed #includes.
 *
 * Revision 1.7  2003/12/19 13:24:30  alexios
 * Updated include directives.
 *
 * Revision 1.6  2003/09/30 15:10:18  alexios
 * Changed Dynamic Library hadnling to use libtool's libltdl abstraction
 * layer. This remains untested to date.
 *
 * Revision 1.5  2003/09/28 11:40:07  alexios
 * Ran indent(1) on all C source to improve readability.
 *
 * Revision 1.4  2003/08/15 18:16:22  alexios
 * Rationalised the RCS/CVS ident(1) strings. Stopped including unneeded
 * Registry file (the registry global command moved to the rightful
 * place, the registry module, a long time ago).
 *
 * Revision 1.3  2001/04/22 14:49:04  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.12  2000/01/06 11:34:26  alexios
 * When a user pages the Sysop at the main console (/p sysop when
 * Sysop isn't online), the event is flagged in the user's online
 * record. This allows the console and other programs to monitor
 * pages to the console and notify the operator.
 *
 * Revision 0.11  1999/08/13 16:56:08  alexios
 * Kludged/fixed (pick one) wrong behaviour in gcs_recent() that
 * printed ffffffff (-1) if the channel number couldn't be found.
 * It prints 00 now, which isn't very good if you have a channel
 * by that number. Won't cause problems, though.
 *
 * Revision 0.10  1999/07/28 23:06:34  alexios
 * Remnants of a debugging session caused a new version here.
 *
 * Revision 0.9  1999/07/18 21:01:53  alexios
 * Changed one error_fatal() call to error_fatalsys().
 *
 * Revision 0.8  1998/12/27 14:31:16  alexios
 * Added autoconf support. Various minor fixes. Added support
 * for new channel_getstatus(). Fixed locking for the remsys command.
 * Fixed pipe calls to tac in /recent command so that pipe errors
 * aren't reported to the user.
 *
 * Revision 0.7  1998/07/24 10:08:57  alexios
 * Made use of new error reporting.
 *
 * Revision 0.6  1997/12/02 20:42:14  alexios
 * Fixed slight bug in /audit command.
 *
 * Revision 0.5  1997/11/06 20:03:54  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.4  1997/11/06 16:52:10  alexios
 * Changed USY_AUDITPAGE to USY_PAGEAUDIT.
 *
 * Revision 0.3  1997/11/05 10:58:35  alexios
 * Moved the /r (registry lookup) command to this file.
 * Abolished the registry daemon (regd). As a result, the first
 * registry lookup per user per module may be slightly slower than
 * the rest.
 * Changed gcs_audit() to set severity filtering, not just turn
 * audit notification on and off. Added a help prompt and made sure
 * no mere mortals can access this command (huge bug there, before).
 *
 * Revision 0.2  1997/09/12 12:49:41  alexios
 * Added functionality to the page global command so that the
 * pager's and pagee's sexes are made obvious for languages that
 * need them to form correct sentences.
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
#define WANT_STRINGS_H 1
#define WANT_DIRENT_H 1
#define WANT_LTDL_H 1
#define WANT_SYS_STAT_H 1
#define WANT_SYS_SHM_H 1
#define WANT_TIME_H 1
#include <megistos/bbsinclude.h>

#include <megistos/config.h>
#include <megistos/bbs.h>

#include <mbk/mbk_sysvar.h>

static gcs_t *gcservers = NULL;
static int gcsnum = 0;


void
gcs_add (gcs_t gcs)
{
	gcsnum++;
	if ((gcservers =
	     realloc (gcservers, sizeof (void *) * gcsnum)) == NULL) {
		error_fatal ("Can't allocate global command table space!",
			     NULL);
	}
	gcservers[gcsnum - 1] = gcs;
}


int
soselect (const struct dirent *a)
{
	/*fprintf(stderr, "*** (%s), %d\n", a->d_name, strncmp(a->d_name, "libgcs", 6));*/
	return strncmp (a->d_name, "libgcs", 6) == 0;
}


void
gcs_init ()
{
	struct dirent **d;
	int     i;

	gcsnum = scandir (mkfname (GCSDIR), &d, soselect, alphasort);
	if (gcsnum == 0) return;

	if (lt_dlinit ()) {
		error_fatal (
			"Unable to intialise dynamic loading: %s",
			lt_dlerror ());
	}
	
	gcservers = (gcs_t *) alcmem (sizeof (gcs_t) * gcsnum);

	for (i = 0; i < gcsnum; i++) {
		char         lib[256];
		lt_dlhandle  handle;
		char        *err;

		sprintf (lib, "%s/%s", mkfname (GCSDIR), d[i]->d_name);
		free (d[i]);

		handle = lt_dlopen (lib);

		if (handle == NULL) {
			error_fatal (
				"Unable to open GCS shared object %s (%s)",
				lib, lt_dlerror ());
		}

		gcservers[i] = (gcs_t) lt_dlsym (handle, "__INIT_GCS__");
		err = (char *) lt_dlerror ();

		if (gcservers[i] == NULL) {
			error_fatal ("__INIT_GCS__ not found in %s", lib);
		}

		if (err != NULL) {
			error_fatal
			    ("Unable to access __INIT_GCS__ in %s (%s)", lib,
			     err);
		}
	}

	/* Modules are not dl_close()d here, because we need access to
	 * their symbols throughout the execution of the module. The
	 * reference counts are automatically decremented by the OS
	 * when the module exits. */

	free (d);
}


int
gcs_handle ()
{
	int     i;
	int     (*gcserver) (void);
	promptblock_t *temp;

	temp = msg_cur;
	inp_parsin ();
	for (i = 0; i < gcsnum; i++) {
		gcserver = gcservers[i];
		if (gcserver ()) {
			msg_set (temp);
			return 1;
		}
	}
	msg_set (temp);
	return 0;
}
