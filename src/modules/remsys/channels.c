/*****************************************************************************\
 **                                                                         **
 **  FILE:     channels.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 94, Version 0.05 alpha                               **
 **  PURPOSE:  Commands that toy with channels and enable the sysop to spy  **
 **            on poor, unsuspecting users and then blackmail them.         **
 **  NOTES:    Stalin would have *LOVED* this one!                          **
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
 * $Id: channels.c,v 2.0 2004/09/13 19:44:52 alexios Exp $
 *
 * $Log: channels.c,v $
 * Revision 2.0  2004/09/13 19:44:52  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.6  2004/02/29 16:57:22  alexios
 * Register-* and PID files are now in the run/ directory.
 *
 * Revision 1.5  2003/12/24 21:53:06  alexios
 * Fixed #includes.
 *
 * Revision 1.4  2003/12/24 20:12:09  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.11  2000/01/06 11:42:07  alexios
 * Various small bug fixes. The channel list now flags users who have
 * recently paged the system console.
 *
 * Revision 0.10  1999/08/13 17:02:31  alexios
 * Added status messages for MetaBBS, fixed listing bug for
 * telnet lines.
 *
 * Revision 0.9  1999/07/18 21:48:04  alexios
 * Changed a few error_fatal() calls to error_fatalsys(). Removed some
 * leftover debugging information.
 *
 * Revision 0.8  1998/12/27 16:07:28  alexios
 * Added autoconf support. Added support for new channel_getstatus().
 * New code for the new bbsgetty states and handling. Various
 * fixes, among which is code to generate a warning if the sysop
 * leaves emulation while the emulated user is in chat mode
 * (hence cannot leave on their own).
 *
 * Revision 0.7  1998/08/14 11:44:25  alexios
 * Fixed rsys_monitor() to watch the new monitor format, which
 * displays either a channel or username (if there is one).
 *
 * Revision 0.6  1998/07/24 10:23:31  alexios
 * Moved to stable status. Migrated to bbslib 0.6.
 *
 * Revision 0.5  1997/11/06 20:05:18  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.4  1997/11/05 11:10:55  alexios
 * Added a typecast to emuq to get rid of a warning about
 * volatile being in place.
 *
 * Revision 0.3  1997/09/12 13:24:18  alexios
 * The channel display for rsys_change() doesn't display the
 * actual username of the user on a channel unless the issuer
 * of the command has the required key (option KEYCHU). Fixed
 * rsys_emulate() bug that would cause constant SIGSEGVs. Fixed
 * extra emulation bug that would turn on inp_block() mode and
 * cause the emulate screen to behave abnormally (synchronously).
 * Fixed rsys_send() so it really DOES send stuff.
 *
 * Revision 0.2  1997/08/30 13:01:01  alexios
 * Changed bladcommand() calls to bbsdcommand(). Since bbsd only
 * accepts tty names (blad also allowed usernames), slight
 * adjustments were made at a few points in the code.
 *
 * Revision 0.1  1997/08/28 11:04:28  alexios
 * First registered revision. Adequate.
 *
 *
 */


static const char rcsinfo[] =
    "$Id: channels.c,v 2.0 2004/09/13 19:44:52 alexios Exp $";



#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_UNISTD_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_TERMIOS_H 1
#define WANT_FCNTL_H 1
#define WANT_SYS_SHM_H 1
#define WANT_SYS_STAT_H 1
#define WANT_SYS_IOCTL_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "remsys.h"
#include "mbk_remsys.h"


void
listchannels ()
{
	int     i, showntelnetline = 0, res;
	channel_status_t status;

	prompt (CHNLSTHDR, NULL);

	for (i = 0; i < chan_count; i++) {
		int     ch = channels[i].channel;

		res = channel_getstatus (channels[i].ttyname, &status);

		if (res < 0 || status.result == LSR_LOGOUT) {
			if (channels[i].flags & TTF_TELNET)
				status.result = LSR_OK;
			else
				status.result = -1;	/* Temporarily unknown state */
		}

		if (channels[i].flags & TTF_TELNET && showntelnetline &&
		    (status.result == LSR_OK))
			continue;

		switch (status.result) {
		case LSR_INIT:
			prompt (CHNLSTTBI, ch, channel_states[status.state]);
			break;
		case LSR_RING:
			prompt (CHNLSTTBR, ch);
			break;
		case LSR_ANSWER:
			prompt (CHNLSTTBA, ch);
			break;
#ifdef HAVE_METABBS
		case LSR_METABBS:
			prompt (CHNLSTTBM, ch, channel_baudstg (status.baud),
				status.user);
			break;
#endif
		case LSR_LOGIN:
			prompt (CHNLSTTBL, ch, channel_baudstg (status.baud));
			break;
		case LSR_USER:
			{
				if (usr_insys (status.user, 0)) {
					time_t  t =
					    time (NULL) -
					    othruseronl.lastconsolepage;
					prompt (CHNLSTTBU, ch,
						channel_baudstg (status.baud),
						status.user,
						t >
						pgstmo ? "" :
						msg_getunit (CHNLSTPGS, 1));
				}
				break;
			}
		case LSR_FAIL:
			prompt (CHNLSTTBF, ch, channel_states[status.state]);
			break;
		case LSR_RELOGON:
			prompt (CHNLSTTBL, ch, channel_states[status.state]);
			break;
		case LSR_LOGOUT:
			prompt (CHNLSTTBQ, ch, channel_states[status.state]);
			break;
		case LSR_OK:
			prompt (CHNLSTTBO, ch, channel_states[status.state]);
			showntelnetline = channels[i].flags & TTF_TELNET;
			break;
		default:
			prompt (CHNLSTTBE, ch);
		}
		if (fmt_lastresult == PAUSE_QUIT)
			return;
	}
	prompt (CHNLSTFTR);
}


int
getchanname (char *dev, int msg, int all)
{
	char   *i, c;
	int     channel;

	for (;;) {
		fmt_lastresult = 0;
		if ((c = cnc_more ()) != 0) {
			if (sameas (cnc_nxtcmd, "X"))
				return 0;
			i = cnc_word ();
		} else {
			prompt (msg, NULL);
			inp_get (0);
			cnc_begin ();
			i = cnc_word ();
			if (!margc) {
				cnc_end ();
				continue;
			}
			if (inp_isX (margv[0])) {
				return 0;
			}
		}
		if (all && (sameas (i, "*") || sameas (i, "all"))) {
			strcpy (dev, "*");
			return 1;
		} else if (sameas (i, "?")) {
			listchannels ();
			cnc_end ();
			continue;
		} else if (strstr (i, "tty") == i) {
			if (chan_getnum (i) != -1) {
				strcpy (dev, i);
				return 1;
			} else {
				prompt (GCHANBDV, NULL);
				cnc_end ();
				continue;
			}
		} else if (usr_exists (i)) {
			if (!usr_insys (i, 0)) {
				prompt (GCHANBID, NULL);
				cnc_end ();
				continue;
			} else {
				strcpy (dev, othruseronl.channel);
				return 1;
			}
		} else if (sscanf (i, "%x", &channel) == 1) {
			char   *name = chan_getname (channel);

			if (!name) {
				prompt (GCHANBCH, NULL);
				cnc_end ();
				continue;
			} else {
				strcpy (dev, name);
				return 1;
			}
		} else {
			prompt (GCHANHUH, i);
			cnc_end ();
			continue;
		}
	}
	return 0;
}


void
rsys_change ()
{
	int     st;
	char    tty[32];
	char    opt, bc[64];
	channel_status_t status;

	for (;;) {
		if (!cnc_more ())
			listchannels ();
		for (;;) {
			if (!getchanname (tty, RSCHANGEWHT, 1))
				return;
			if (!strcmp (tty, "*"))
				break;
			channel_getstatus (tty, &status);
			if (status.result == LSR_USER) {
				prompt (RSCHANGEERR);
				cnc_end ();
			} else
				break;
		}
		if (!get_menu (&opt, 1, RSCHANGELMN, RSCHANGESMN, RSCHANGEBAD,
			       "RBNO", 0, 0))
			return;

		strcpy (bc, "RNBO");
		st = strchr (bc, opt) - bc;

		if (strcmp (tty, "*"))
			bbsdcommand ("change", tty, channel_states[st]);
		else {
			int     i;

			for (i = 0; i < chan_count; i++) {
				channel_getstatus (channels[i].ttyname,
						   &status);
				if (status.result != LSR_USER) {
					bbsdcommand ("change",
						     channels[i].ttyname,
						     channel_states[st]);
				}
			}
		}
		prompt (RSCHANGEOK, NULL);
	}
}


int
getchkname (char *checkname, char *tty)
{
	char    s[256];
	FILE   *fp;
	int     pid;

	pid = 0;
	sprintf (s, "%s/register-%s", mkfname (BBSRUNDIR), tty);
	if ((fp = fopen (s, "r")) != NULL) {
		fgets (s, sizeof (s), fp);
		fclose (fp);
		sscanf (s, "%d", &pid);
		sprintf (checkname, "%s/%d", PROCDIR, pid);
	}
	return pid;
}


void
rsys_emulate ()
{
	char    tty[256];
	FILE   *fp;
	struct stat st;
	int     ok, pid;
	char    c;
	char    chkname[256];
	char    devname[256], fname[256];
	struct termios oldkbdtermios;
	struct termios newkbdtermios;
	int     count = 0, stc = 0, err = 0;
	struct emuqueue *emuq;
	int     i, j, shmid;
	char    lock[256];

	lock[0] = 0;
	for (;;) {
		if (!getchanname (tty, RSEMUWHO, 0))
			return;
		if (!strcmp (thisuseronl.channel, tty))
			prompt (RSEMUSLF, NULL);
		else {
			FILE   *fp = NULL;
			int     pid, ok = 0;
			char    s[256];

			sprintf (fname, "%s/emud-%s.pid", mkfname (BBSRUNDIR),
				 tty);
			if ((fp = fopen (fname, "r")) != NULL) {
				if (fscanf (fp, "%d", &pid) == 1) {
					fclose (fp);
					sprintf (fname, "%s/%d/stat", PROCDIR,
						 pid);
					if ((fp = fopen (fname, "r")) != NULL) {
						if ((fscanf
						     (fp, "%d %s", &pid,
						      s) == 2) &&
						    (!strcmp (s, "(emud)")))
							ok = 1;
					}
				}
				fclose (fp);
				fp = NULL;
			}
			if (fp)
				fclose (fp);
			if (!ok) {
				prompt (RSEMUNUS);
				continue;
			} else {
				char    dummy[32];

				sprintf (lock, "LCK-emu-%s-%s", tty,
					 thisuseronl.channel);
				if (lock_check (lock, dummy) > 0) {
					prompt (RSEMUHAHA);
					continue;
				}
				lock_rm (lock);
				sprintf (lock, "LCK-emu-%s-%s",
					 thisuseronl.channel, tty);
				lock_place (lock, "");
				break;
			}
		}
	}

	ok = 0;
	pid = getchkname (chkname, tty);

	if (stat (chkname, &st)) {
		prompt (RSEMUNOE);
		return;
	}

	thisuseronl.flags |= OLF_BUSY;
	prompt (RSEMUGO);

	sprintf (devname, DEVDIR "/%s", tty);

	/* Switch stdin to non blocking mode */

	inp_nonblock ();
	tcgetattr (fileno (stdin), &oldkbdtermios);
	newkbdtermios = oldkbdtermios;
	newkbdtermios.c_lflag = newkbdtermios.c_lflag & ~(ICANON | ECHO);
	tcsetattr (fileno (stdin), TCSAFLUSH, &newkbdtermios);

	/* Begin emulation */

	sprintf (fname, "%s/.shmid-%s", mkfname (EMULOGDIR), tty);

	if ((fp = fopen (fname, "r")) == NULL) {
		error_fatalsys ("Error opening %s\n", fname);
		err = 1;
	}
	if (!fscanf (fp, "%d", &shmid)) {
		error_fatalsys ("Error reading %s\n", fname);
		err = 1;
	}
	fclose (fp);

	if ((emuq = (struct emuqueue *) shmat (shmid, NULL, 0)) == NULL) {
		error_fatalsys
		    ("Error attaching to emulation shared memory\n");
		err = 1;
	}

	sprintf (fname, "%s/.emu-%s", mkfname (EMULOGDIR), tty);
	if ((fp = fopen (fname, "w")) == NULL) {
		error_fatalsys ("Error opening %s\n", fname);
		err = 1;
	}
	inp_nonblock ();

	j = i = emuq->index;
	if (!err) {
		for (;;) {
			usleep (10000);
			count = (count + 1) % 5;
			if (!count) {
				stc = (stc + 1) % 20;

				if (!stc) {
					if (stat (chkname, &st)) {
						pid =
						    getchkname (chkname, tty);
						usleep (5000);
						if (stat (chkname, &st)) {
							prompt (RSEMUNOE);
							break;
						}
					}
				}

				if (emuq->index != i) {
					j = emuq->index;
					do {
						write (0,
						       (char *) &emuq->
						       queue[i], 1);
						i = (i +
						     1) % sizeof (emuq->queue);
					} while (i != j);
				}
			}

			if ((read (fileno (stdin), &c, 1)) == 1) {
				if (c == 17)
					break;
				else if (c == 26) {
					channel_status_t status;

					bbsdcommand ("hangup", tty, "");
					channel_getstatus (tty, &status);
					prompt (RSEMUHUP);
					break;
				} else if (c == 3) {
					bbsdcommand ("chat", tty, "");
				} else {
					fputc (c, fp);
					fflush (fp);
					count = -1;
				}
			}
		}
	}

	/* Switch back to blocking mode, close files, etc */

	inp_block ();
	tcsetattr (fileno (stdin), TCSAFLUSH, &oldkbdtermios);
	fclose (fp);

	shmdt ((char *) emuq);

	prompt (RSEMUEND);
	if (othruseronl.flags & OLF_INSYSCHAT)
		prompt (RSEMUCHT);
	thisuseronl.flags &= ~OLF_BUSY;
	lock_rm (lock);
}


void
rsys_monitor ()
{
	int     c;
	FILE   *fp;
	int     oldmark = 0;

	prompt (RSMONITORHDR, NULL);
	if ((fp = fopen (mkfname (MONITORFILE), "r")) == NULL) {
		prompt (RSMONITORERR, NULL);
		return;
	}
	fclose (fp);

	inp_nonblock ();

	for (c = 0; !(read (fileno (stdin), &c, 1) &&
		      ((c == 13) || (c == 10) || (c == 27) || (c == 15) ||
		       (c == 3)));) {
		fseek (fp, 0, SEEK_SET);

		if (oldmark != monitor->timestamp) {
			char    tmp[64];

			if (monitor->channel[0] != ' ') {
				sprintf (tmp, "%x",
					 chan_getnum ((char *) monitor->
						      channel));
			} else
				strcpy (tmp, &((char *) monitor->channel)[1]);

			prompt (RSMONITORTAB, tmp, monitor->input);
			fmt_resetvpos (0);
			oldmark = monitor->timestamp;
		}

		inp_acceptinjoth ();
		usleep (50000);
	}

	prompt (RSMONITOREND, NULL);
	inp_block ();
}


void
rsys_send ()
{
	char    tty[32];
	char    fname[256], msg[2050], buf[MSGBUFSIZE];
	FILE   *fp;
	channel_status_t status;

	for (;;) {
		if (!getchanname (tty, RSSENDWHO, 1))
			return;
		if (!strcmp (tty, "*"))
			break;
		channel_getstatus (tty, &status);
		if (status.result != LSR_USER) {
			prompt (RSSENDR);
			cnc_end ();
		} else
			break;
	}
	sprintf (fname, TMPDIR "/send-%05d", getpid ());

	editor (fname, 2048);
	memset (msg, 0, sizeof (msg));
	if ((fp = fopen (fname, "r")) != NULL)
		fread (msg, 1, sizeof (msg) - 1, fp);
	fclose (fp);
	unlink (fname);
	if (!msg[0]) {
		prompt (RSSENDCAN);
		return;
	}
	if (strcmp (tty, "*")) {
		if (!usr_insys (status.user, 0)) {
			prompt (RSSENDD);
			return;
		}
		sprompt_other (othrshm, msg_buffer, RSSENDINH, msg);
		if (!usr_injoth (&othruseronl, msg_buffer, 0)) {
			prompt (RSSENDX, othruseronl.userid);
		} else
			prompt (RSSEND1, chan_getnum (tty));
	} else {
		int     i, j, n;

		for (i = j = n = 0; i < chan_count; i++) {
			channel_getstatus (channels[i].ttyname, &status);
			if (status.result != LSR_USER) {
				if (usr_insys (status.user, 0)) {
					sprompt_other (othrshm, buf, RSSENDINH,
						       msg);
					if (usr_insys (status.user, 0)) {
						n++;
						if (!usr_injoth
						    (&othruseronl, buf, 0)) {
							prompt (RSSENDX,
								othruseronl.
								userid);
						} else
							j++;
					}
				}
			}
		}
		if (!j)
			prompt (RSSEND2B);
		else if (n != j)
			prompt (RSSEND2A);
		else
			prompt (RSSEND2);
	}
}





/* End of File */
