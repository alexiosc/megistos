/*****************************************************************************\
 **                                                                         **
 **  FILE:     interface.c                                                  **
 **  AUTHORS:  Alexios                                                      **
 **  PURPOSE:                                                               **
 **  NOTES:                                                                 **
 **                                                                         **
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
 * Revision 1.5  2003/12/23 08:18:08  alexios
 * Corrected minor #include discrepancies.
 *
 * Revision 1.4  2003/12/22 17:23:36  alexios
 * Ran through megistos-config --oh to beautify source.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.0  2000/01/23 20:46:33  alexios
 * Initial revision
 *
 * Revision 1.0  2000/01/22 19:28:08  alexios
 * Initial revision
 *
 *
 */


static const char rcsinfo[] = "$Id$";


#define __METABBSD__ 1
#define WANT_SYS_STAT_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_SOCKET_H 1
#define WANT_ARPA_TELNET_H 1
#define WANT_SYS_UN_H 1
#define WANT_VARARGS_H 1
#define WANT_FCNTL_H 1
#define WANT_PWD_H 1
#include <bbsinclude.h>
#include <bbs.h>
#include "metabbs-server.h"



#define NUMTRIES 3

#define KEYWORD(x) {#x,KEY_##x}

#define LOCALLINE    ((chan_last->flags&(TTF_SERIAL|TTF_CONSOLE))!=0)

#define KEY_QUIT 0
#define KEY_BYE  0
#define KEY_EXIT 0
#define KEY_HELP 1
#define KEY_BBOT 2
#define KEY_CINF 3
#define KEY_CLST 4
#define KEY_SYNC 5

struct keyword {
	char   *keyword;
	int     index;
};

struct keyword keywords[] = {
	KEYWORD (BBOT),
	KEYWORD (BYE),
	KEYWORD (CINF),
	KEYWORD (CLST),
	KEYWORD (EXIT),
	KEYWORD (HELP),
	KEYWORD (QUIT),
	KEYWORD (SYNC),
	{"", -1}
};

#if 0
-c List remote clubs. - g (Go)
Synchronise remote
    clubs. -
    I
    clubname
    Get
    info
    on
    remote
club (best used with - s).
#endif
static char userid[256];

static useracc_t uacc;


#define reply_printf(code,fmt...) \
  print("%03d ",(code&0x1ff)%999); \
  print(##fmt); \
  print("\n")



static void
setchannelstate (int result, char *user)
{
	channel_status_t status;

	channel_getstatus (tty, &status);
	status.result = result;
	status.baud = baud;
	strcpy (status.user, user);
	channel_setstatus (tty, &status);
}


static int
authenticate ()
{
	channel_status_t linestatus;
	int     i;

	/* Much of this code is from bbslogin. */


	/* Clear any remaining remsys locks -- this is obviously a kludge */

	sprintf (filename, "LCK-remsys-%s", tty);
	lock_rm (filename);


	/* Make sure this line is open */

	if (!channel_getstatus (tty, &linestatus)) {
		error_fatal ("Unable to get line status for %s\n", tty);
	}
	if ((linestatus.state == LST_BUSYOUT) ||
	    (linestatus.state == LST_NOANSWER)
	    || (linestatus.state == LST_OFFLINE)) {
		reply_printf (RET_ERR_LINEDOWN,
			      "This line is not available right now.");
		sleep (1);
		return 0;
	}


	/* Make sure we don't violate the maximum user count */

	if (chan_last->flags & TTF_TELNET &&
	    (chan_telnetlinecount () > sysvar->tnlmax)) {
		reply_printf (RET_ERR_TOOMANY,
			      "Too many users logged in right now.");
		sleep (1);
		return 0;
	}

	/* Set the line state */

	setchannelstate (LSR_LOGIN, "[NO-USER]");





	reply_printf (RET_INF_HELLO, "%s metabbsd (%s)", host_name, rcs_ver);

	for (i = 0; i < NUMTRIES; i++) {
		reply_printf (RET_ASK_LOGIN, "Please identify yourself.");
		inp_get (0);
		strncpy (userid, inp_buffer, sizeof (userid));
		userid[sizeof (userid) - 1] = 0;

		reply_printf (RET_ASK_PASSWORD, "Enter password.");
		inp_setflags (INF_PASSWD);
		inp_get (0);
		inp_clearflags (INF_PASSWD);

		if (usr_exists (userid) && usr_loadaccount (userid, &uacc)) {
			if (sameas (uacc.passwd, inp_buffer)) {
				reply_printf (RET_INF_LOGGEDIN,
					      "Welcome, %s. What can we do for you?",
					      userid);
				return 1;
			}
		}

		reply_printf (RET_ERR_LOGIN, "Login incorrect.");
	}



	return 0;
}


static void
become_bot ()
{
	reply_printf (RET_INF_MISC, "Becoming bot...");
}



static void
help ()
{
	int     i;

	reply_printf (RET_INF_HELP, "I understand the following commands:");
	for (i = 0; keywords[i].index >= 0; i++) {
		reply_printf (RET_INF_HELP, "%s", keywords[i].keyword);
	}
}


void
mainloop ()
{
	if (authenticate ())
		for (;;) {
			char   *command;
			int     i;

			reply_printf (RET_ASK_COMMAND, "Enter command.");
			inp_get (0);

			if (!margc)
				continue;

			command = stripspace (margv[0]);
#ifdef DEBUG
			reply_printf (RET_INF_MISC, "Input: (%s)",
				      stripspace (margv[0]));
#endif

			for (i = 0; keywords[i].index >= 0; i++) {
				if (sameas (command, keywords[i].keyword))
					break;
			}

			switch (keywords[i].index) {
			case KEY_QUIT:
				goto end_session;	/* No other practical way to do this in here, sorry */

			case KEY_HELP:
				help ();
				break;

			case KEY_BBOT:
				become_bot ();
				break;

			default:
				reply_printf (RET_ERR_COMMAND, "Huh?");
				continue;
			}
		}

      end_session:
	reply_printf (RET_INF_GOODBYE, "Goodbye.");

#ifdef DEBUG
	fprintf (stderr, "*** Leaving handleconnection().\n");
#endif
}


/* End of File */
