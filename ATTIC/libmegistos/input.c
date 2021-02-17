/*****************************************************************************\
 **                                                                         **
 **  FILE:     input.c                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, June 94                                                   **
 **  PURPOSE:  Handle user input                                            **
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
 * $Id: input.c,v 2.0 2004/09/13 19:44:34 alexios Exp $
 *
 * $Log: input.c,v $
 * Revision 2.0  2004/09/13 19:44:34  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.8  2003/12/24 18:35:08  alexios
 * Fixed #includes.
 *
 * Revision 1.7  2003/12/19 13:24:30  alexios
 * Updated include directives.
 *
 * Revision 1.6  2003/09/28 11:40:07  alexios
 * Ran indent(1) on all C source to improve readability.
 *
 * Revision 1.5  2003/08/15 18:08:45  alexios
 * Rationalised RCS/CVS ident(1) strings.
 *
 * Revision 1.4  2001/06/30 10:34:37  alexios
 * Fixed significant security fault a symptom of which was SF bug #223631. The
 * patch was provided by Lucas Maneos, although I was *sure* I'd already
 * applied one of my own. Hm.
 *
 * Revision 1.3  2001/04/22 14:49:04  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.11  2000/01/06 10:56:23  alexios
 * Changed calls to write(2) to send_out().
 *
 * Revision 0.10  1999/07/28 23:06:34  alexios
 * Added a timeout facility to getinp(), accessible using
 * inp_timeout().
 *
 * Revision 0.9  1999/07/18 21:01:53  alexios
 * Changed a couple of error_fatal() calls to error_fatalsys(). Minor
 * fixes in dealing with global commands while in password
 * entry mode. One minor change to getint() to make it behave
 * better in concatenated mode. One minor fix to get_bool().
 *
 * Revision 0.8  1998/12/27 14:31:16  alexios
 * Added autoconf support. Enhanced terminal setting support to
 * deal with changes forced by new bbsgetty. Moved isX from
 * miscfx.c to input.c. Same for settimeout and resetinactivity().
 *
 * Revision 0.7  1998/08/14 11:27:44  alexios
 * Augmented monitorinput() to record either the user's
 * channel number or their user ID (if it is known).
 *
 * Revision 0.6  1998/07/26 21:05:25  alexios
 * Removed obsolete injothfile variable. Fixed very serious bug
 * that would not accept messages from an injoth() queue with
 * SYSV IPC queue id equal to 0.
 *
 * Revision 0.5  1998/07/24 10:08:57  alexios
 * Made use of new error reporting.
 *
 * Revision 0.4  1997/11/06 20:03:54  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.3  1997/11/03 00:34:41  alexios
 * Changed all calls to xlwrite() to write() since emud now
 * handles all translations itself.
 *
 * Revision 0.2  1997/09/12 12:49:41  alexios
 * Acceptinjoth() now uses an IPC message queue instead of the
 * previous method (using disk files). Added resetblocking() so
 * that the previous state of the terminal blocking may be restored.
 * Functions blocking() and nonblocking() now change this previous
 * sate and resetblocking() changes it back.
 *
 * Revision 0.1  1997/08/26 16:35:17  alexios
 * First registered revision. Adequate.
 *
 *
 */


static const char rcsinfo[] =
    "$Id: input.c,v 2.0 2004/09/13 19:44:34 alexios Exp $";


#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_UNISTD_H 1
#define WANT_STRING_H 1
#define WANT_CTYPE_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_TERMIOS_H 1
#define WANT_FCNTL_H 1
#define WANT_SYS_STAT_H 1
#define WANT_SYS_IPC_H 1
#define WANT_SYS_SHM_H 1
#define WANT_SYS_MSG_H 1
#define WANT_ERRNO_H 1
#define WANT_SEND_OUT 1
#include <megistos/bbsinclude.h>

#include <megistos/config.h>
#include <megistos/errors.h>
#include <megistos/input.h>
#include <megistos/useracc.h>
#include <megistos/miscfx.h>
#include <megistos/prompts.h>
#include <megistos/output.h>
#include <megistos/format.h>
#include <megistos/globalcmd.h>
#include <megistos/sysstruct.h>
#include <megistos/bbsmod.h>
#include <megistos/security.h>
#include <megistos/bots.h>
#define __SYSVAR_UNAMBIGUOUS__
#include <mbk/mbk_sysvar.h>

static struct termios oldkbdtermios;
static struct termios newkbdtermios;
char    inp_del[4] = "\010 \010\0";
char    inp_buffer[MAXINPLEN + 1];
char   *margv[MAXINPLEN / 2];
char   *cnc_nxtcmd = NULL, wordbuf[MAXINPLEN];
int     margc;
static int inp_len;
uint32  inp_flags = 0;
static int oldblocking = 1;
static int newblocking = 1;
static int inptimeout_msecs = 0;
static int inptimeout_intr = 0;

static long oldflags = 0;
static volatile int cancel = 0;
volatile struct monitor *monitor;
static char montty[24];


void
inp_setmonitorid (char *s)
{
	sprintf (montty, " %s", s);
}


static void
initmonitor ()
{
	FILE   *fp;
	int     shmid;

	strcpy (montty, getenv ("CHANNEL"));

	if ((fp = fopen (mkfname (MONITORFILE), "r")) == NULL) {
		error_fatalsys ("Unable to open %s", mkfname (MONITORFILE));
	}

	fscanf (fp, "%d", &shmid);
	fclose (fp);

	if ((monitor = (struct monitor *) shmat (shmid, NULL, 0)) == NULL) {
		error_fatalsys ("Unable to attach to shm block (errno=%d).",
				errno);
	}
}


void
inp_init ()
{
	int     i;

	tcgetattr (0, &oldkbdtermios);
	memcpy (&newkbdtermios, &oldkbdtermios, sizeof (newkbdtermios));
	newkbdtermios.c_lflag =
	    newkbdtermios.c_lflag & ~(ICANON | ECHO | ISIG);
	for (i = 0; i < sizeof (newkbdtermios.c_cc); i++)
		newkbdtermios.c_cc[i] = 0;
	newkbdtermios.c_cc[VTIME] = 0;	/* Cook the tty (medium rare) */
	newkbdtermios.c_cc[VMIN] = 1;
	tcsetattr (0, TCSANOW, &newkbdtermios);
	inp_flags = 0;

	initmonitor ();
}


void
inp_done ()
{
	tcsetattr (0, TCSANOW, &oldkbdtermios);
}


int
inp_acceptinjoth ()
{
	char    dummy[MSGMAX + sizeof (long)];
	struct injoth_buf *buf = (struct injoth_buf *) (&dummy);
	int     i = 0;

	if (thisshm == NULL)
		return 0;
	if (!thisuseronl.userid[0])
		return 0;
	if (thisuseronl.injothqueue < 0)
		return 0;

	for (;;) {
		bzero (dummy, sizeof (dummy));
		errno = 0;
		if (msgrcv
		    (thisuseronl.injothqueue, buf, MSGMAX, 0, IPC_NOWAIT) < 0)
			return i > 0;
		i++;

		switch (buf->mtype) {
		case INJ_MESSAGE:	/* A simple injoth message. */
			if (mod_isbot () ||
			    (thisshm != NULL &&
			     (thisuseronl.flags & OLF_ISBOT))) {
				print
				    ("%03d %d byte injected message follows.\n",
				     BTS_INJECTED_PROMPT,
				     strlen (buf->m.simple));
			}
			print ("%s", buf->m.simple);
			break;

		case INJ_MESSAGE_ACK:	/* Injoth message with acknowledgement */
			if (mod_isbot () ||
			    (thisshm != NULL &&
			     (thisuseronl.flags & OLF_ISBOT))) {
				print
				    ("%03d %d byte injected message follows.\n",
				     BTS_INJECTED_PROMPT,
				     strlen (buf->m.withack.msg));
			}

			print ("%s", buf->m.withack.msg);

			/* We don't use usr_insys() here so as not to clobber any work the caller
			   function is in the process of performing. */

			{
				onlinerec_t onl;

				if (usr_loadonlrec
				    (buf->m.withack.sender, &onl)) {
					char   *ack =
					    &(buf->m.withack.
					      msg[buf->m.withack.ackofs]);
					int     qid = onl.injothqueue;

					if (strlen (ack)) {
						buf->mtype = INJ_MESSAGE;
						strcpy (buf->m.simple, ack);

						/* We don't really care if this goes through or not */
						msgsnd (qid, buf,
							strlen (buf->m.
								simple) + 1,
							IPC_NOWAIT);
					}
				}
			}

			break;

		default:
			error_log ("Invalid injoth message type %d received",
				   buf->mtype);
		}
	}

	return 1;
}



void
inp_readstring (int maxlen)
{
	int     cp = 0, count = 0, tmout;
	unsigned char c;
	struct timeval tv, tvtimeout;
	struct timezone tz;

	if (mod_isbot () ||
	    (thisshm != NULL && (thisuseronl.flags & OLF_ISBOT))) {
		print ("%03d %d Input expected now.\n", BTS_INPUT_EXPECTED,
		       maxlen);
	}

	cancel = 0;
	if (inptimeout_msecs) {
		gettimeofday (&tv, &tz);
		memcpy (&tvtimeout, &tv, sizeof (tv));
		tvtimeout.tv_usec += inptimeout_msecs * 1000;
		tvtimeout.tv_sec += tvtimeout.tv_usec / 1000000;
		tvtimeout.tv_usec = tvtimeout.tv_usec % 1000000;
	}

	tmout = inptimeout_msecs > 0;

	inp_nonblock ();

	inp_flags &= ~(INF_REPROMPT | INF_TIMEOUT);

	if (!maxlen)
		maxlen = MAXINPLEN - 1;
	for (;;) {
		while (read (0, &c, 1) != 1) {
			if (cancel) {
				inp_acceptinjoth ();
				inp_flags |= INF_TIMEOUT | INF_REPROMPT;
				inp_clear ();
				inp_block ();
				return;
			}
			usleep (10000);
			if (tmout && (cp == 0 || inptimeout_intr)) {	/* Handle timeouts */
				gettimeofday (&tv, &tz);
				if ((tv.tv_sec > tvtimeout.tv_sec) ||
				    ((tv.tv_sec == tvtimeout.tv_sec) &&
				     (tv.tv_usec >= tvtimeout.tv_usec))) {
					inptimeout_msecs = 0;
					inptimeout_intr = 0;
					inp_clear ();
					inp_block ();
					return;
				}
			}
			count = (count + 1) % 5;
			if ((inp_flags & INF_NOINJOTH) || cp)
				continue;
			if (inp_acceptinjoth ()) {
				inp_flags |= INF_REPROMPT;
				inp_clear ();
				inp_block ();
				return;
			}
			if (count)
				continue;
		}
		inp_resetidle ();
		switch (c) {
		case 13:
		case 10:
			c = '\n';
			out_send (fileno (stdout), &c, 1);
			fflush (stdout);
			inp_buffer[cp] = 0;
			inp_monitor ();
			inp_block ();
			if (((inp_flags & INF_PASSWD) == 0) && gcs_handle ()) {
				inp_clear ();
				inp_flags |= INF_REPROMPT;
			}
			return;
		case 127:
		case 8:
			if (cp) {
				out_send (fileno (stdout), inp_del, 3);
				cp--;
			}
			break;
		default:
			if (cp < maxlen && (c >= 0x20)) {
				inp_buffer[cp++] = c;
				if (inp_flags & INF_PASSWD)
					c = '*';
				out_send (fileno (stdout), &c, 1);
			}
		}
	}
}


void
inp_parsin ()
{
	char   *cp = inp_buffer;

	margc = 0;
	inp_len = strlen (inp_buffer);

	cp = strtok (inp_buffer, " \t\n\r");
	while (cp) {
		margv[margc++] = cp;
		cp = strtok (NULL, " \t\n\r");
	}
}


void
inp_monitor ()
{
	monitor->timestamp++;
	strcpy ((char *) monitor->channel, montty);
	strcpy ((char *) monitor->input,
		inp_flags & INF_PASSWD ? "<password>" : inp_buffer);
}


char   *
inp_get (int maxlen)
{
	out_setflags (OFL_AFTERINPUT);
	memset (inp_buffer, 0, sizeof (inp_buffer));
	if (fmt_lastresult == PAUSE_QUIT) {
		inp_flags |= INF_REPROMPT;
	} else {
		fmt_resetvpos (0);
		inp_readstring (maxlen);
		inp_len = strlen (inp_buffer);
	}
	inp_clearflags (INF_PASSWD);
	fmt_resetvpos (0);
	cnc_nxtcmd = NULL;
	return margv[0];
}


void
inp_clear ()
{
	inp_buffer[0] = 0;
	inp_len = 0;
	margc = 0;
}


void
inp_raw ()
{
	int     i;

	for (i = 0; i < margc - 1; i++)
		(margv[i][strlen (margv[i])]) = 32;
}


void
cnc_begin ()
{
	cnc_nxtcmd = margv[0];
	inp_raw ();
}


int
cnc_end ()
{
	cnc_nxtcmd = NULL;
	thisuseronl.input[0] = 0;
	inp_parsin ();
/*  if (!margc)return 1;
  strncpy(inp_buffer,cnc_nxtcmd,strlen(cnc_nxtcmd)+1);
  inp_parsin(); */
	return (margc == 0);
}


char
cnc_chr ()
{
	char    c;

	if (cnc_nxtcmd == NULL)
		return 0;
	if ((c = tolatin (toupper (*cnc_nxtcmd))) != 0)
		cnc_nxtcmd++;
	return c;
}


int32
cnc_int ()
{
	int     ofs, d = 0;

	sscanf (cnc_nxtcmd, "%d%n", &d, &ofs);
	cnc_nxtcmd += ofs;
	return d;
}


int64
cnc_long ()
{
	int     ofs;
	long    l = 0L;

	sscanf (cnc_nxtcmd, "%ld%n", &l, &ofs);
	cnc_nxtcmd += ofs;
	return l;
}


char
cnc_yesno ()
{
	char    c;

	switch (c = cnc_chr ()) {
	case 'Y':
#ifdef GREEK
	case -109:
	case -84:
#endif
		c = 'Y';
		break;
	case 'N':
#ifdef GREEK
	case -92:
	case -116:
#endif
		c = 'N';
		break;
	}
	return (c);
}


char   *
cnc_word ()
{
	int     i = 0;
	char    c;

	wordbuf[0] = 0;

	while ((c = *cnc_nxtcmd) != ' ' && c) {
		cnc_nxtcmd++;
		wordbuf[i++] = c;
	}
	wordbuf[i] = 0;
	return wordbuf;
}


char   *
cnc_all ()
{
	char   *s;

	s = cnc_nxtcmd;
	if (s != NULL) {
		cnc_nxtcmd += strlen (cnc_nxtcmd);	/* Move to the terminating null */
		return s[0] ? s : NULL;
	}
	return NULL;
}


char
cnc_more ()
{
	if (!cnc_nxtcmd)
		return 0;
	while (*cnc_nxtcmd == ' ')
		cnc_nxtcmd++;
	return (toupper (*cnc_nxtcmd));
}


uint64
cnc_hex ()
{
	int     i, retval = 0, flag = 0;
	static char hex[6] = { 'A', 'B', 'C', 'D', 'E', 'F' };

	while (1) {
		if (isdigit (*cnc_nxtcmd))
			retval = (retval << 4) + (*cnc_nxtcmd - '0');
		else {
			for (i = 0; i < 6; i++) {
				if (toupper (*cnc_nxtcmd) == hex[i]) {
					retval = (retval << 4) + 10 + i;
					break;
				}
			}
			if (i == 6)
				return (flag ? retval : -1);
		}
		cnc_nxtcmd++;
		flag = 1;
	}
}


char   *
cnc_num ()
{
	int     i = 0;
	static char retval[12];

	if (!cnc_more ())
		return NULL;
	if (*cnc_nxtcmd == '-')
		retval[i++] = *(cnc_nxtcmd++);
	while (isdigit (*cnc_nxtcmd) && i < 11)
		retval[i++] = *(cnc_nxtcmd++);
	retval[i] = '\0';
	return (retval);
}


void
inp_setflags (uint32 n)
{
	inp_flags |= n;
}


void
inp_clearflags (uint32 f)
{
	inp_flags &= ~f;
}


int
inp_isX (char *s)
{
	int     c = toupper (s[0]);
	int     result;

	if (strlen (s) != 1)
		return 0;
	result = (c == 'X');
#ifdef GREEK
	result |= (c == -82 || c == -107);
#endif
	return result;
}


int
get_number (num, msg, min, max, err, def, defval)
int    *num, msg, min, max, err, def, defval;
{
	int     i;
	char    c;

	fmt_lastresult = PAUSE_CONTINUE;
	for (;;) {
		fmt_lastresult = 0;
		if ((c = cnc_more ()) != 0) {
			if (sameas (cnc_nxtcmd, "X"))
				return 0;
			if (sameas (cnc_nxtcmd, "?") && (inp_flags & INF_HELP))
				return -1;
			if (sameas (cnc_nxtcmd, ".") && def) {
				*num = defval;
				return 1;
			}
			i = cnc_int ();
		} else {
			if (msg)
				prompt (msg, min, max);
			if (def) {
				sprintf (out_buffer, msg_get (def), defval);
				print (out_buffer);
			}
			inp_get (0);
			if ((!margc || (margc == 1 && sameas (margv[0], ".")))
			    && def && !inp_reprompt ()) {
				*num = defval;
				return 1;
			} else if (!margc) {
				cnc_end ();
				continue;
			}
			if (inp_isX (margv[0])) {
				return 0;
			}
			if (sameas (margv[0], "?") && (inp_flags & INF_HELP))
				return -1;
			cnc_begin ();
			i = cnc_int ();
		}
		if (i < min || i > max) {
			cnc_end ();
			if (err)
				prompt (err, min, max);
		} else {
			*num = i;
			return 1;
		}
	}
	return 0;
}


int
get_bool (boolean, msg, err, def, defval)
int    *boolean, msg, err, def, defval;
{
	int     c = 0;

	fmt_lastresult = PAUSE_CONTINUE;
	for (;;) {
		fmt_lastresult = 0;
		if (cnc_more ())
			c = cnc_yesno ();
		else {
			if (msg)
				prompt (msg);
			if (def) {
				sprintf (out_buffer, msg_get (def),
					 (defval ? 'Y' : 'N'));
				print (out_buffer);
			}
			inp_get (0);
			if (margc) {
				if (inp_isX (margv[0])) {
					return 0;
				}
				if (sameas (margv[0], "?") &&
				    (inp_flags & INF_HELP))
					return -1;
			} else
			    if ((!margc ||
				 (margc == 1 && sameas (margv[0], "."))) && def
				&& !inp_reprompt ()) {
				*boolean = defval;
				return 1;
			}
			cnc_begin ();
			c = cnc_chr ();
		}
		switch (c = toupper (c)) {
#ifdef GREEK
		case -109:
		case -84:
#endif
		case 'Y':
			*boolean = 1;
			return 1;
#ifdef GREEK
		case -92:
		case -116:
#endif
		case 'N':
			*boolean = 0;
			return 1;
		case 0:
			cnc_end ();
			continue;
		case '?':
			if (inp_flags & INF_HELP)
				return -1;
			break;
		default:
			cnc_end ();
			if (err)
				prompt (err, c);
		}
	}
	return 0;
}


int
get_userid (uid, msg, err, def, defval, online)
char   *uid, *defval;
int     msg, err, def, online;
{
	char   *i;
	char    c;

	fmt_lastresult = PAUSE_CONTINUE;
	for (;;) {
		fmt_lastresult = 0;
		if ((c = cnc_more ()) != 0) {
			if (sameas (cnc_nxtcmd, "X"))
				return 0;
			if (sameas (cnc_nxtcmd, "?") && (inp_flags & INF_HELP))
				return -1;
			if (sameas (cnc_nxtcmd, ".") && def) {
				strcpy (uid, defval);
				return 1;
			}
			i = cnc_word ();
		} else {
			if (msg)
				prompt (msg);
			if (def) {
				sprintf (out_buffer, msg_get (def), defval);
				print (out_buffer);
			}
			inp_get (0);
			cnc_begin ();
			i = cnc_word ();
			if ((!margc || (margc == 1 && sameas (margv[0], ".")))
			    && def && !inp_reprompt ()) {
				strcpy (uid, defval);
				return 1;
			} else if (!margc) {
				cnc_end ();
				continue;
			}
			if (inp_isX (margv[0])) {
				return 0;
			}
			if (sameas (margv[0], "?") && (inp_flags & INF_HELP))
				return -1;
		}
		if (!usr_uidxref (i, online)) {
			cnc_end ();
			if (err)
				prompt (err, i);
		} else {
			strcpy (uid, i);
			return 1;
		}
	}
	return 0;
}


int
get_menu (option, show, lmenu, smenu, err, opts, def, defval)
char   *option, defval, *opts;
int     show, lmenu, smenu, err, def;
{
	int     shownmenu = !show;
	char    c;

	fmt_lastresult = PAUSE_CONTINUE;
	for (;;) {
		fmt_lastresult = 0;
		if ((c = cnc_more ()) != 0) {
			if (sameas (cnc_nxtcmd, "X"))
				return 0;
			c = cnc_chr ();
			shownmenu = 1;
		} else {
			if (!shownmenu && lmenu)
				prompt (lmenu);
			shownmenu = 1;
			if (smenu)
				prompt (smenu);
			if (def) {
				sprintf (out_buffer, msg_get (def), defval);
				print (out_buffer);
			}
			inp_get (0);
			cnc_begin ();
			c = cnc_chr ();
		}
		if ((!margc || (margc == 1 && sameas (margv[0], "."))) && def
		    && !inp_reprompt ()) {
			*option = defval;
			return 1;
		} else if (!margc) {
			cnc_end ();
			continue;
		}
		if (inp_isX (margv[0])) {
			return 0;
		} else if (margc && (c == '?' || sameas (margv[0], "?"))) {
			if (inp_flags & INF_HELP)
				return -1;
			shownmenu = 0;
			continue;
		} else if (strchr (opts, c)) {
			*option = c;
			return 1;
		} else {
			if (err)
				prompt (err, c);
			cnc_end ();
			continue;
		}
	}
	return 0;
}


void
inp_cancel ()
{
	cancel = 1;
}


void
inp_nonblock ()
{
	oldblocking = newblocking;
	newblocking = 0;
	oldflags = fcntl (fileno (stdin), F_GETFL) & ~O_NONBLOCK;
	fcntl (0, F_SETFL, oldflags | O_NONBLOCK);
}


void
inp_block ()
{
	oldblocking = newblocking;
	newblocking = 1;
	oldflags = fcntl (fileno (stdin), F_GETFL) & ~O_NONBLOCK;
	fcntl (0, F_SETFL, oldflags);
}


void
inp_resetblocking ()
{
	if (oldblocking)
		inp_block ();
	else
		inp_nonblock ();
}


void
inp_setidle (int i)
{
	int     ovr = 0, usy = 0, force = 0;

	usy = hassysaxs (&thisuseracc, USY_MASTERKEY);
	force = (thisuseronl.flags & OLF_FORCEIDLE) != 0;
	if ((!usy && !ovr) || force)
		thisuseronl.idlezap = i;
	else
		thisuseronl.idlezap = 0;
}


void
inp_resetidle ()
{
	if (thisshm)
		thisuseronl.timeoutticks = 0;
}


void
inp_timeout (int msecs, int intrusive)
{
	inptimeout_msecs = msecs;
	inptimeout_intr = intrusive;
}


int
inp_reprompt ()
{
	return inp_flags & INF_REPROMPT;
}
