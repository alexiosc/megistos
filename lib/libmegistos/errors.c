/*****************************************************************************\
 **                                                                         **
 **  FILE:     errors.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, June 94                                                   **
 **  PURPOSE:  Handle fatal errors, near-fatal errors,                      **
 **            it's-just-a-flesh-wound errors, I've-had-worse-errors, and   **
 **            Run-away! errors (sorry, couldn't help that).                **
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
 * Revision 1.7  2003/12/19 13:24:01  alexios
 * Updated include directives.
 *
 * Revision 1.6  2003/09/28 11:40:07  alexios
 * Ran indent(1) on all C source to improve readability.
 *
 * Revision 1.5  2003/08/15 20:09:13  alexios
 * Fixed code to remove warnings.
 *
 * Revision 1.4  2003/08/15 18:16:46  alexios
 * Rationalised the RCS/CVS ident(1) strings. Fixed vararg.h issues.
 *
 * Revision 1.3  2001/04/22 14:49:04  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.6  1998/12/27 14:31:16  alexios
 * Added autoconf support. Added functions with 'sys' suffix
 * to report system errors by concatenating the user supplied
 * message and a suffix reporting the last system error.
 *
 * Revision 0.5  1998/07/26 21:04:40  alexios
 * Fixed serious bug that caused a SIGSEGV when an error
 * occured and the CHANNEL environment variable wasn't set.
 *
 * Revision 0.4  1998/07/24 10:08:57  alexios
 * Error reporting now knows and reports the binary name, the
 * source code file where the error occured and the line
 * number of the error report call.
 *
 * Revision 0.3  1997/11/06 20:03:54  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/11/05 10:58:35  alexios
 * Reporting errors now generates an audit trail entry with
 * appropriate severity.
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
#define WANT_CTYPE_H 1
#define WANT_TIME_H 1
#define WANT_VARARGS_H 1
#include <megistos/bbsinclude.h>
#include <megistos/config.h>
#include <megistos/output.h>
#include <megistos/audit.h>
#include <megistos/bbsmod.h>
#include <megistos/errorprompts.h>

#define FATAL 1

static int errormessageflag;
static int circular = 0;
static char *chan_unknown = "[no channel]";

char   *mkfname (char *fmt, ...);

static void
bbserror (file, line, reason, format, parmlist)
char   *file, *reason, *format;
int     line;
void   *parmlist;
{
	struct tm *dt;
	time_t  t;
	char    datetime[64];
	FILE   *fp;

	if ((fp = fopen (mkfname (ERRORFILE), "a")) == NULL)
		return;
	t = time (0);
	dt = localtime (&t);
	strftime (datetime, sizeof (datetime), "%d/%m/%Y %H:%M:%S", dt);
	fprintf (fp, "%s %s (%s:%d): %s, ", datetime, __module.progname, file,
		 line, reason);
	vfprintf (fp, format, parmlist);
	fputc ('\n', fp);
	fclose (fp);
}


void
_interror (char *file, int line, char *format, ...)
{
	char   *chan;
	va_list args;

	va_start (args, format);
	bbserror (file, line, "ERROR", format, args);
	if (circular == 0) {
		circular = 1;
		if ((chan = getenv ("CHANNEL")) != NULL)
			audit (chan, AUDIT (ERROR));
		else
			audit (chan_unknown, AUDIT (ERROR));
		circular = 0;
	}
	va_end (args);
}


void
_logerror (char *file, int line, char *format, ...)
{
	char   *chan;
	va_list args;

	va_start (args, format);
	bbserror (file, line, "ERROR", format, args);
	va_end (args);
	if (circular == 0) {
		circular = 1;
		if ((chan = getenv ("CHANNEL")) != NULL)
			audit (chan, AUDIT (ERROR));
		else
			audit (chan_unknown, AUDIT (ERROR));
		circular = 0;
		if (errormessageflag)
			print (ERRORMESSAGE);
	}
}


void
_fatal (char *file, int line, char *format, ...)
{
	char   *chan;
	va_list args;

	va_start (args, format);
	bbserror (file, line, "FATAL", format, args);
	va_end (args);
	if (circular == 0) {
		circular = 1;
		if (errormessageflag)
			print (FATALMESSAGE);
		if ((chan = getenv ("CHANNEL")) != NULL)
			audit (chan, AUDIT (FATAL));
		else
			audit (chan_unknown, AUDIT (FATAL));
		circular = 0;
	}
	exit (FATAL);
}


void
error_setnotify (int state)
{
	errormessageflag = state;
}


/* Versions of _interror, _logerror and _fatal that report the value
   of errno appended to the error. If strerror() is defined on this
   system, we'll use it to generate the string form of the system
   error, too. */

void
_interrorsys (char *file, int line, int err, char *format, ...)
{
	char   *chan;
	char    fmt[512];
	va_list args;

	va_start (args, format);
#ifdef HAVE_STRERROR
	sprintf (fmt, "%s (errno=%d, %s)", format, err, strerror (err));
#else
	sprintf (fmt, "%s (errno=%d)", format, err);
#endif
	bbserror (file, line, "ERROR", fmt, args);
	if (circular == 0) {
		circular = 1;
		if ((chan = getenv ("CHANNEL")) != NULL)
			audit (chan, AUDIT (ERROR));
		else
			audit (chan_unknown, AUDIT (ERROR));
		circular = 0;
	}
	va_end (args);
}


void
_logerrorsys (char *file, int line, int err, char *format, ...)
{
	char   *chan;
	char    fmt[512];
	va_list args;

	va_start (args, format);
#ifdef HAVE_STRERROR
	sprintf (fmt, "%s (errno=%d, %s)", format, err, strerror (err));
#else
	sprintf (fmt, "%s (errno=%d)", format, err);
#endif
	bbserror (file, line, "ERROR", fmt, args);
	va_end (args);
	if (circular == 0) {
		circular = 1;
		if ((chan = getenv ("CHANNEL")) != NULL)
			audit (chan, AUDIT (ERROR));
		else
			audit (chan_unknown, AUDIT (ERROR));
		circular = 0;
		if (errormessageflag)
			print (ERRORMESSAGE);
	}
}


void
_fatalsys (char *file, int line, int err, char *format, ...)
{
	char    fmt[512];
	char   *chan;
	va_list args;

	va_start (args, format);
#ifdef HAVE_STRERROR
	sprintf (fmt, "%s (errno=%d, %s)", format, err, strerror (err));
#else
	sprintf (fmt, "%s (errno=%d)", format, err);
#endif
	bbserror (file, line, "FATAL", fmt, args);
	va_end (args);
	if (circular == 0) {
		circular = 1;
		if (errormessageflag)
			print (FATALMESSAGE);
		if ((chan = getenv ("CHANNEL")) != NULL)
			audit (chan, AUDIT (FATAL));
		else
			audit (chan_unknown, AUDIT (FATAL));
		circular = 0;
	}
	exit (FATAL);
}
