/*****************************************************************************\
 **                                                                         **
 **  FILE:     miscfx.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, June 94                                                   **
 **  PURPOSE:  Implement various useful functions                           **
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
 * Revision 1.7  2003/12/24 18:35:08  alexios
 * Fixed #includes.
 *
 * Revision 1.6  2003/12/19 13:26:23  alexios
 * Updated include directories; changed behaviour of mkfname() to reflect
 * new build structure.
 *
 * Revision 1.5  2003/09/28 11:40:07  alexios
 * Ran indent(1) on all C source to improve readability.
 *
 * Revision 1.4  2003/08/15 18:15:36  alexios
 * Rationalised the RCS/CVS ident(1) strings. Updated usage of variable
 * argument functions. Changed default, fall-back prefix to BASEDIR
 * instead of __BASEDIR.
 *
 * Revision 1.3  2001/04/22 14:49:05  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.11  1999/07/28 23:06:34  alexios
 * No changes, effectively.
 *
 * Revision 0.10  1998/12/27 14:31:16  alexios
 * Added autoconf support. Added emulation of usleep() call for
 * systems that don't support it. Removed various functions to
 * other files to reduce the load on miscfx.c.
 *
 * Revision 0.9  1998/08/11 10:01:10  alexios
 * Added stripspace() to strip white space surrounding a token.
 *
 * Revision 0.8  1998/07/24 10:08:57  alexios
 * Made use of new error reporting.
 *
 * Revision 0.7  1997/11/06 20:03:54  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.6  1997/11/03 00:34:41  alexios
 * Optimised stgxlate for speed. Added a new function,
 * faststgxlate() that is suitable for very fast applications
 * where a complete translation table is available. This is
 * used by emud to translate text on the fly.
 *
 * Revision 0.5  1997/09/12 12:52:28  alexios
 * Added lowerc() and upperc() to convert strings to lower and
 * upper case respectively. Changed injoth() so it uses the
 * injoth IPC message queue instead of its previous method of
 * creating temporary disk files.
 *
 * Revision 0.4  1997/09/01 10:26:52  alexios
 * Fixed erroneous check to ANSI enable flag.
 *
 * Revision 0.3  1997/08/30 12:57:20  alexios
 * Removed bladcommand(). Replaced it with bbsdcommand(). The
 * daemon commands have not changed, though the daemon itself
 * has. The function syntax is different, though.
 *
 * Revision 0.2  1997/08/28 12:48:47  alexios
 * Fixed bug in uidxref cache that would refuse to retrieve
 * user Abc if user Abcd had been retrieved earlier.
 *
 * Revision 0.1  1997/08/26 16:35:17  alexios
 * First registered revision. Adequate.
 *
 *
 */


static const char rcsinfo[] =
    "$Id$";


#define MISCFX_O


#define WANT_SYS_SHM_H 1
#define WANT_SYS_MSG_H 1
#define WANT_TERMIOS_H 1
#define WANT_SYS_IOCTL_H 1
#define WANT_DIRENT_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_STAT_H 1
#define WANT_FCNTL_H 1
#define WANT_VARARGS_H 1
#include <megistos/bbsinclude.h>

#include <megistos/config.h>
#include <megistos/bbs.h>
#include <megistos/menuman.h>

#include <mbk/mbk_sysvar.h>



/* Whoops, MSGMAX (max length of IPC message) not defined. Guess wildly */
#ifndef MSGMAX
#  define MSGMAX 4096
#endif



void   *
alcmem (size_t size)
{
	void   *ptr = malloc (size);

	if (ptr)
		return ptr;
	error_fatal ("Failed to allocate %08d bytes", size);
	return NULL;		/* Get rid of warning -- we're not returning anyway */
}


static char *bbsprefix = NULL;


char   *
mkfname (char *fmt, ...)
{
	va_list args;
	char    tmp[2048];
	static char buf[2048];

	/* Find out our prefix */

	if (bbsprefix == NULL) {
		if (getenv ("BBSPREFIX"))
			bbsprefix = strdup (getenv ("BBSPREFIX"));
		else if (getenv ("PREFIX"))
			bbsprefix = strdup (getenv ("PREFIX"));
		else
			perror ("Neither BBSPREFIX nor PREFIX are set, bailing out.");
		/*bbsprefix = strdup (BASEDIR);*/
		/* There is no longer a hardwired fallback prefix. */
	}

	/* Prepend the prefix to the format. Chop double slashes */

	strcpy (tmp, bbsprefix);
	if (tmp[strlen (tmp) - 1] == '/')
		tmp[strlen (tmp) - 1] = 0;
	strcat (tmp, "/");
	if (fmt[0] == '/')
		strcat (tmp, &(fmt[1]));
	else
		strcat (tmp, fmt);

	/* And format the string */

	va_start (args, fmt);
	vsprintf (buf, tmp, args);
	va_end (args);

	return buf;
}


char   *
lowerc (char *s)
{
	char   *cp;

	for (cp = s; *cp; cp++)
		*cp = tolower (*cp);
	return s;
}


char   *
upperc (char *s)
{
	char   *cp;

	for (cp = s; *cp; cp++)
		*cp = toupper (*cp);
	return s;
}


char   *
stripspace (char *s)
{
	char   *cp, *ep;
	int     i = strspn (s, " \n\t\r");

	cp = &s[i];
	for (ep = &cp[strlen (cp) - 1]; ep > cp
	     && (isspace (*ep) || (*ep == '\n') || (*ep == '\t') ||
		 (*ep == '\r')); ep--)
		*ep = 0;
	return cp;
}


int
sameto (char *shorts, char *longs)
{
	while (*shorts != '\0') {
		if (tolower (*shorts) != tolower (*longs)) {
			return 0;
		}
		shorts++;
		longs++;
	}
	return 1;
}


int
sameas (char *stg1, char *stg2)
{
	while (*stg1 != '\0') {
		if (tolower (*stg1) != tolower (*stg2)) {
			return (0);
		}
		stg1++;
		stg2++;
	}
	return (*stg2 == '\0');
}


char   *
zeropad (char *s, int count)
{
	int     i;

	for (i = 1; i < count; i++)
		if (!s[i - 1])
			s[i] = 0;
	return s;
}


int
bbsdcommand (char *command, char *tty, char *arg)
{
	FILE   *fp;
	char    fname[256];

	sprintf (fname, mkfname (BBSDPIPEFILE));
	if ((fp = fopen (fname, "w")) == NULL) {
		return 0;
	}
	fprintf (fp, "%s %s %s\n", command, tty, strlen (arg) ? arg : ".");
	fclose (fp);
	return 1;
}


void
dialog_parse (char *s)
{
	char   *cp = s;

	cnc_nxtcmd = NULL;
	margc = 0;
	margv[0] = s;

	for (margc = 0, margv[0] = s; *cp; cp++) {
		if (*cp == '\n') {
			*cp = 0;
			margv[++margc] = cp + 1;
		}
	}
}


int
dialog_run (char *msg, int visual, int linear, char *data, size_t len)
{
	char    fname[256], command[512];
	int     result, fd;

	/* Write the data */

	sprintf (fname, TMPDIR "/form%05d", (int) getpid ());
	unlink (fname);		/* Just in case */
	if ((fd = open (fname, O_WRONLY | O_CREAT, 0600)) < 0) {
		error_logsys ("Unable to create data entry file %s", fname);
		return -1;
	}
	if (write (fd, data, strlen (data)) != strlen (data)) {
		close (fd);
		error_logsys ("Unable to write to data entry file %s", fname);
		return -1;
	}
	close (fd);


	/* Run the dialogue */

	sprintf (command, "%s %s %d %d %s",
		 mkfname (BBSDIALOGBIN), msg, visual, linear, fname);
	result = runcommand (command);


	/* Read back the results */

	if ((fd = open (fname, O_RDONLY)) < 0) {
		error_logsys ("Unable to open data entry file %s", fname);
		return -1;
	}

	memset (data, 0, len);
	if (read (fd, data, len) <= 0) {
		error_logsys ("Error reading data entry file %s", fname);
		return -1;
	}

	close (fd);
	if (unlink (fname) < 0) {
		error_logsys ("unlink(\"%s\") failed", fname);
		return -1;
	}

	return result;
}


inline char *
stgxlate (char *s, char *t)
{
	register char *table = t;
	register unsigned char *cp;

	for (cp = s; *cp; cp++)
		if (table[(int) *cp])
			*cp = table[(int) *cp];
	return s;
}


inline char *
faststgxlate (char *s, char *t)
{
	register char *table = t;
	register unsigned char *cp;

	for (cp = s; *cp; cp++)
		*cp = table[(int) *cp];
	return s;
}


int
search (char *string, char *keywords)
{
	char   *cp, *sp;

	for (cp = keywords; *cp; cp = sp + 1) {
		if ((sp = strchr (cp, 32)) != NULL)
			*sp = 0;
		else
			sp = cp + strlen (cp) - 1;
		if (*cp && strstr (string, cp))
			return 1;
	}
	return 0;
}


int
runmodule (char *s)
{
	char    cmd[1024];

	sprintf (cmd, "%s --run", s);
	return runcommand (cmd);
}


int
runcommand (char *s)
{
	int     res;

	mod_done (INI_INPUT | INI_SIGNALS);
	if (cnc_nxtcmd && *cnc_nxtcmd) {
		strcpy (thisuseronl.input, cnc_nxtcmd);
		thisuseronl.flags |= OLF_MMCONCAT;
	} else
		thisuseronl.flags &= ~OLF_MMCONCAT;
	res = system (s);
	thisuseronl.flags &= ~OLF_MMCONCAT;
	mod_init (INI_INPUT | INI_SIGNALS);
	thisuseronl.flags &= ~(OLF_BUSY | OLF_NOTIMEOUT);
	inp_resetidle ();
	if (thisuseronl.flags & OLF_MMGCDGO)
		exit (0);
	return res;
}


int
editor (char *fname, int limit)
{
	char    command[256];

	if (thisuseracc.prefs & UPF_VISUAL && thisuseronl.flags & OLF_ANSION) {
		sprintf (command, "%s %s %d", mkfname (VISEDBIN), fname,
			 limit);
		return runcommand (command);
	} else {
		sprintf (command, "%s %s %d", mkfname (LINEDBIN), fname,
			 limit);
		return runcommand (command);
	}
}


static void
_gopage (char *s, int is_menuman)
{
	union menumanpage p;
	FILE   *fp;
	int     found = 0;

	if (thisuseronl.flags & OLF_INHIBITGO) {
		msg_set (msg_sys);
		prompt (CANTGO);
		msg_reset ();
		return;
	}

	if ((fp = fopen (MENUMANPAGES, "r")) == NULL)
		return;
	while (!feof (fp)) {
		if (fread (&p, sizeof (union menumanpage), 1, fp) != 1) {
			fclose (fp);
			msg_set (msg_sys);
			prompt (GONAX, s);
			msg_reset ();
			return;
		} else if (sameas (s, p.m.name)) {
			found = 1;
			break;
		}
	}
	fclose (fp);
	if (!found) {
		msg_set (msg_sys);
		prompt (GONAX, s);
		msg_reset ();
		return;
	}

	found = 0;
	if (hassysaxs (&thisuseracc, USY_MASTERKEY))
		found = 1;
	if (p.m.class[0] && !sameas (p.m.class, thisuseracc.curclss))
		found = 0;
	if (!key_owns (&thisuseracc, p.m.key))
		found = 0;
	else
		found = 1;

	if (!found) {
		msg_set (msg_sys);
		prompt (GONAX, s);
		msg_reset ();
		return;
	}

	strncpy (thisuseronl.prevpage, p.m.prev, 15);
	strncpy (thisuseronl.curpage, p.m.name, 15);
	thisuseronl.curpage[15] = 0;
	thisuseronl.flags |= OLF_MMGCDGO;
	thisuseronl.flags &= ~OLF_MMCALLING;
	fflush (stdout);

	/* patched by Valis */
	if ( /*! */ is_menuman)
		execl (mkfname (BINDIR "/menuman"), "menuman", NULL);

	exit (0);		/* Do it the slow, ugly way if execl() fails */
}


void
mmgopage (char *s)
{
	_gopage (s, 1);
}


void
gopage (char *s)
{
	_gopage (s, 0);
}


int
fcopy (char *source, char *target)
{
	FILE   *s, *t;
	int     br, bw, tr, tw;
	char    buf[8192];

	if ((s = fopen (source, "r")) == NULL)
		return -1;
	if ((t = fopen (target, "w")) == NULL) {
		fclose (s);
		return -1;
	}

	for (br = bw = tr = tw = 0; br == bw;) {
		br = read (fileno (s), buf, sizeof (buf));
		if (br < 0) {
			fclose (s);
			fclose (t);
			unlink (target);
			return -1;
		}
		if (!br)
			break;
		bw = write (fileno (t), buf, br);
		if (bw < 0) {
			fclose (s);
			fclose (t);
			unlink (target);
			return -1;
		}
		tr += br;
		tw += bw;
	}
	fclose (s);
	fclose (t);
	if (tr != tw) {
		unlink (target);
		return -1;
	}
	return 0;
}



#ifndef HAVE_USLEEP
#  ifndef HAVE_SELECT
#    error "This system lacks both usleep() and select() -- unable to proceed."
#  endif

int
usleep (int microseconds)
{
	struct timeval t;

	t.ts_sec = microseconds / 1000000;
	t.ts_usec = microseconds % 1000000;
	select (1, 0, 0, &t);
	return 1;
}

#endif
