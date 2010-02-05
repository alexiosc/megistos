/*****************************************************************************\
 **                                                                         **
 **  FILE:     metabbs-client.c                                             **
 **  AUTHORS:  Alexios                                                      **
 **  PURPOSE:  Initiate telnet connections to remote systems at login.      **
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
\*****************************************************************************/


/*
 * $Id: metabbs-client.c,v 2.0 2004/09/13 19:44:54 alexios Exp $
 *
 * $Log: metabbs-client.c,v $
 * Revision 2.0  2004/09/13 19:44:54  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2003/12/22 22:14:05  alexios
 * Brought over to the new source tree.
 *
 * Revision 1.4  2003/12/22 17:23:36  alexios
 * Ran through megistos-config --oh to beautify source.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 *
 */


static const char rcsinfo[] = "$Id: metabbs-client.c,v 2.0 2004/09/13 19:44:54 alexios Exp $";



#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_STRING_H 1
#define WANT_CTYPE_H 1
#define WANT_UNISTD_H 1
#define WANT_TIME_H 1
#define WANT_FCNTL_H 1
#define WANT_SYS_IOCTL_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_STAT_H 1
#define WANT_SYS_IPC_H 1
#define WANT_SYS_MSG_H 1
#define WANT_SYS_WAIT_H 1
#define WANT_PWD_H 1
#define WANT_GRP_H 1
#define WANT_UTMP_H 1
#define WANT_SIGNAL_H 1
#define WANT_TERMIOS_H 1
#include <bbsinclude.h>
#include <rpc/rpc.h>

#include <megistos/bbs.h>
#include <mbk/mbk_sysvar.h>
#include <mbk/mbk_metabbs-client.h>
#define __METABBS_UNAMBIGUOUS__ 1
#include <mbk/mbk_metabbs.h>
#include "../daemons/rpc.metabbs/metaservices.h"


extern int errno;

promptblock_t *msg;
int     mode;			/* 1: add the local BBS as system 0 */
int     usrlrm;
int     qrylrm;
int     showlocal;
char   *hosts;
char   *bbscod;
char   *tty;



void
setchannelstate (int result, char *user)
{
	channel_status_t status;

	channel_getstatus (tty, &status);
	status.result = result;
	strcpy (status.user, user);
	channel_setstatus (tty, &status);
}


/* We don't expect *that* many BBSs on the same system, so we'll be
   doing dynamic allocation but naive sequential searches. */

struct info_package_t *systems = NULL;
int     num_systems = 0;


/* The local system's info package, if any. */

struct info_package_t local;


/* This is a sequential search. It's disgrace against Knuth, but with
   two or three systems on the same machine, it's more convenient,
   less memory-hungry *and* faster than a bsearch() */

int
find_system (char *codename)
{
	int     i;

	for (i = 0; codename[i]; i++)
		codename[i] = tolower (codename[i]);
	for (i = 0; i < num_systems; i++) {
		if (!strcmp (codename, systems[i].codename))
			return i;
	}
	return -1;		/* Not found */
}


/* Make some space in the dynamic array of information packs. The caller is
   expected to have established that the information package isn't already in
   the array. make_space() returns the index (0-based, of course) of the new
   package. */

int
make_space ()
{
	int     i;

	if (!num_systems) {

		/* New info_pack_t */

		num_systems = 1;
		systems = (struct info_package_t *)
		    malloc (sizeof (struct info_package_t));
		i = 0;
	} else {
		struct info_package_t *tmp;


		/* Make some space */

		num_systems++;

		tmp = (struct info_package_t *)
		    malloc (num_systems * sizeof (struct info_package_t));

		memcpy (tmp,
			systems,
			sizeof (struct info_package_t) * (num_systems - 1));

		free (systems);
		systems = tmp;

		i = num_systems - 1;
	}

	return i;
}



/* Return 1 if sys is better than existing in terms of quality. Better packages
   are those that generally offer more information. */


#define score(weight,field) \
score_a+=(weight)*(strlen(sys->field)!=0);\
score_b+=(weight)*(strlen(existing->field)!=0);

int
better (struct info_package_t *sys, struct info_package_t *existing)
{
	int     score_a = 0, score_b = 0;

	/* If we're in add-local mode, then the local system's entry is always better
	   than any remote ones. New entries for the local BBS always overwrite older
	   ones, so they get a higher score (asymmetric scoring). */

	if ((strlen (sys->hostname) == 0) && (sys->port < 0))
		score_a += 20000000;
	if ((strlen (existing->hostname) == 0) && (existing->port < 0))
		score_b += 10000000;

	/* The most important one is the existence of bbstitle and bbs_sd */

	score (6, bbstitle);
	score (3, bbs_ad);


	/* Then, check addresses etc */

	score (1, company);
	score (1, address1);
	score (1, address2);
	score (1, city);
	score (1, dataphone);
	score (1, voicephone);
	score (1, url);
	score (1, email);


	return score_a > score_b;
}


static int
count_users_online ()
{
	int     n = 0, i;
	channel_status_t status;

	for (i = 0; i < chan_count; i++) {
		if (!channel_getstatus (channels[i].ttyname, &status))
			continue;
		if (status.result == LSR_USER)
			n++;
	}
	return n;
}



/* Add a system to the list. */

void
add_system (struct info_package_t *sys)
{
	int     i;

	if ((i = find_system (sys->codename)) < 0)
		i = make_space ();
	else {

		/* If we already have a package for this system, we only keep this one if
		   it's better than the one we already have. 'Quality' is judged by
		   better(). */

		if (!better (sys, &systems[i]))
			return;
	}
	memcpy (&systems[i], sys, sizeof (struct info_package_t));

	/* We need to make local copies of a few fields */
	systems[i].hostname = strdup (systems[i].hostname);
	systems[i].url = strdup (systems[i].url);
	systems[i].email = strdup (systems[i].email);
	systems[i].bbs_ad = strdup (systems[i].bbs_ad);
}


int
syscmp (const void *a, const void *b)
{
	return strcmp (((struct info_package_t *) a)->codename,
		       ((struct info_package_t *) b)->codename);
}



void
init ()
{
	char   *cp;

	mod_init (INI_TTYNUM | INI_OUTPUT | INI_SYSVARS | INI_ERRMSGS |
		  INI_INPUT | INI_SIGNALS | INI_CLASSES | INI_LANGS |
		  INI_ATEXIT);

	if ((tty = getenv ("CHANNEL")) == NULL) {
		error_fatal ("CHANNEL variable is undefined.");
	}

	if (chan_getnum (tty) < 0) {
		error_fatal ("%s has not been registered in %s",
			     tty, mkfname (CHANDEFFILE));
	}

	msg = msg_open ("metabbs-client");	/* We need this before anything else */
	showlocal = msg_bool (LOCAL);
	msg_close (msg);

	msg = msg_open ("sysvar");
	bbscod = msg_string (BBSCOD);

	if (mode || showlocal) {
		strcpy (local.codename, bbscod);
		strcpy (local.bbstitle, msg_get (BBSTTL));
		strcpy (local.company, msg_get (COMPANY));
		strcpy (local.address1, msg_get (ADDRES1));
		strcpy (local.address2, msg_get (ADDRES2));
		strcpy (local.city, msg_get (CITY));
		strcpy (local.dataphone, msg_get (DATAPH));
		strcpy (local.voicephone, msg_get (VOICEPH));
		local.users_online = count_users_online ();
		local.lines_free =
		    max (0, sysvar->tnlmax - chan_telnetlinecount ());
		local.lines_max = sysvar->tnlmax;
		local.hostname = strdup ("");	/* These two lines indicate that... */
		local.port = -1;	/* ...this is the local BBS entry */

		msg_close (msg);
		msg = msg_open ("metabbs");
		local.url = msg_string (METABBS_URL);
		local.email = msg_string (METABBS_EMAIL);
		local.bbs_ad = msg_string (METABBS_BBSAD);
	}
	msg_close (msg);


	msg = msg_open ("metabbs-client");


	/* Set the default language, or maybe get it from what bbslogin tells us. */

	msg_setlanguage (chan_last->lang >
			 0 ? chan_last->lang : -chan_last->lang);
	if ((cp = getenv ("LANG")) != NULL) {
		if (atoi (cp) > 0)
			msg_setlanguage (atoi (cp));
	}

	usrlrm = msg_int (USRLRM, 0, 60) * 60;
	qrylrm = msg_int (QRYLRM, 0, 3600);
	hosts = msg_string (HOSTS);
}



void
timeout (int signal)
{
	prompt (KICKOUT);
	sleep (1);
	exit (1);
}



static void
gather ()
{
	static char *tmphosts = NULL;
	char   *host;
	info_package_p *result;
	CLIENT *cl = NULL;
	static int set_timeout = 0;

	if (tmphosts == NULL)
		tmphosts = strdup (hosts);	/* Allocate space */

	/* Free any old list of systems */

	if (num_systems != 0) {
		int     i;

		for (i = 0; i < num_systems; i++) {
			free (systems[i].hostname);
			free (systems[i].email);
			free (systems[i].url);
			free (systems[i].bbs_ad);
		}
		free (systems);
		systems = NULL;
		num_systems = 0;
	}


	if (!mode)
		prompt (BEGIN);

	strcpy (tmphosts, hosts);	/* Copy the host list once more */


	/* Do every host in the list */

	for (host = strtok (tmphosts, " \n\r\t"); host;
	     host = strtok (NULL, " \n\r\t")) {
		if (!mode)
			prompt (LOOKUP, host);


		/* Create the RPM client for this host */

		if ((cl =
		     clnt_create (host, METABBS_PROG, METABBS_VERS,
				  "tcp")) == NULL) {
			prompt (DNSFAIL);	/* The name's a bit misleading... */
			clnt_destroy (cl);
			continue;
#if 0
			printf ("Failed to create server.\n");
			clnt_pcreateerror (server);
#endif
		}


		/* Set client timeout to QRYLRM */

		if (!mode)
			prompt (SENDREQ);
		{
			struct timeval t;

			t.tv_sec = qrylrm;
			t.tv_usec = 0;
			clnt_control (cl, CLSET_TIMEOUT, (char *) &t);
		}



		/* Now send the request to the server */

		if ((result = metabbs_request_info_1 (&bbscod, cl)) == NULL) {
			prompt (SENDERR);
			clnt_destroy (cl);
			continue;
#if 0
			clnt_perror (cl, server);
#endif
		}


		/* Add the results */

		if (!mode)
			prompt (SENDOK);
		if (*result != NULL) {
			info_package_p cp = *result;

			while (cp) {
				add_system (cp);
				cp = cp->next;
			}
		}

		if (mode || showlocal) {	/* Add the local system too, if required */
			local.users_online = count_users_online ();
			local.lines_free =
			    max (0, sysvar->tnlmax - chan_telnetlinecount ());
			local.lines_max = sysvar->tnlmax;
			add_system (&local);
		}

		clnt_destroy (cl);
	}

	qsort (systems, num_systems, sizeof (struct info_package_t), syscmp);

	if (!num_systems) {	/* No systems found despite our efforts */
		prompt (NOSYS);
		exit (0);
	} else if (num_systems == 1) {
		if (!mode)
			prompt (SYSCOUNT1);
	} else if (!mode)
		prompt (SYSCOUNT, num_systems);


	/* Timeout? If so, set it up and warn the l^Huser */

	if (usrlrm && !set_timeout) {
		set_timeout = 1;
		if (!mode)
			prompt (WARNTIME, usrlrm / 60,
				msg_getunit (MINSNG, usrlrm / 60));
		signal (SIGALRM, timeout);
		alarm (usrlrm);
	}

#if 0
	/* Test code for distclubs -- should normally be #ifdeffed out */
	if ((cl =
	     clnt_create ("vennea", METABBS_PROG, METABBS_VERS,
			  "tcp")) == NULL) {
		prompt (DNSFAIL);	/* The name's a bit misleading... */
		clnt_destroy (cl);
	}
	{
		struct club_header_request_t bbs;
		club_header *result;

		strcpy (bbs.codename, "ACRO");
		strcpy (bbs.targetname, "ACRO");
		strcpy (bbs.club, "LANGUAGE");
		if ((result = distclub_request_header_1 (&bbs, cl)) == NULL) {
			print ("oops!\n");
		}
		print
		    ("--- RESULT=%d %-16.16s %s %s\n\n\n----------------------\n%s",
		     result->result_code, result->club_header_u.club.club,
		     result->club_header_u.club.descr,
		     result->club_header_u.club.clubop,
		     result->club_header_u.club.banner);
	}
#endif


#if 0
	/* Test code for distclubs -- should normally be #ifdeffed out */
	if ((cl =
	     clnt_create ("vennea", METABBS_PROG, METABBS_VERS,
			  "tcp")) == NULL) {
		prompt (DNSFAIL);	/* The name's a bit misleading... */
		clnt_destroy (cl);
	}
	{
		struct ihave_request_t bbs;
		struct ihave_list *result;

		strcpy (bbs.codename, "ACRO");
		strcpy (bbs.targetname, "ACRO");
		strcpy (bbs.club, "language");
		bbs.since_time = 0;
		if ((result = distclub_request_ihave_1 (&bbs, cl)) == NULL) {
			print ("oops!\n");
		} else {
			ihave_list_p p = result->ihave_list_u.ihave_list;

			while (p) {
				print ("--- %s/%s/%s\n", p->codename,
				       p->orgclub, p->msgid);
				p = p->next;
			}
		}
	}
#endif

#if 0
	/* Test code for distclubs -- should normally be #ifdeffed out */
	if ((cl =
	     clnt_create ("vennea", METABBS_PROG, METABBS_VERS,
			  "tcp")) == NULL) {
		prompt (DNSFAIL);	/* The name's a bit misleading... */
		clnt_destroy (cl);
	}
	{
		message_request_t bbs;
		struct club_message *result;

		strcpy (bbs.codename, "ACRO");
		strcpy (bbs.targetname, "ACRO");
		strcpy (bbs.targetclub, "acro");
		bbs.compression = 0;
		bbs.msgno = 5;
		if ((result = distclub_request_message_1 (&bbs, cl)) == NULL) {
			print ("oops!\n");
		} else {
			printf ("return code: %d\n", result->result_code);
			printf ("from:        %s\n",
				result->club_message_u.message.from);
			printf ("to:          %s\n",
				result->club_message_u.message.to);
			printf ("subject:     %s\n",
				result->club_message_u.message.subject);
			printf ("compression: %d\n",
				result->club_message_u.message.comp_result.
				compression);
			printf ("body len:    %d\n",
				result->club_message_u.message.message.
				message_len);
			printf ("uncomp:      %d\n",
				result->club_message_u.message.comp_result.
				compr_u.compr.orig_msg_len);
			printf ("\nbody:\n");
			fflush (stdout);
			if (!result->club_message_u.message.comp_result.
			    compression) {
				write (1,
				       result->club_message_u.message.message.
				       message_val,
				       result->club_message_u.message.message.
				       message_len);
			} else {
				char   *tmp;
				int     i =
				    result->club_message_u.message.comp_result.
				    compr_u.compr.orig_msg_len;
				tmp = alcmem (i);
				uncompress (tmp,
					    &i,
					    result->club_message_u.message.
					    message.message_val,
					    result->club_message_u.message.
					    message.message_len);
				write (1, tmp, i);
			}
			printf ("<EOF>\n");
			fflush (stdout);
			printf ("-----------------------\n");
		}
	}
#endif
}


static void
list_systems ()
{
	int     i;

	prompt (SYSTBLH);
	for (i = 0; i < num_systems; i++) {
		if (systems[i].users_online >= 0) {
			prompt (SYSTBLL,
				i + 1,
				systems[i].bbstitle,
				systems[i].users_online,
				systems[i].lines_free);
		} else {
			prompt (SYSTBLN, i + 1, systems[i].bbstitle);
		}
	}
	prompt (SYSTBLF);
}


void
show_info (int i)
{
	struct info_package_t *p = &systems[i];

	if (p->users_online >= 0) {
		prompt (BBSINFO, i + 1,
			p->bbstitle,
			p->codename,
			p->company,
			p->address1, strlen (p->address1) ? ", " : "",
			p->address2, strlen (p->address2) ? ", " : "", p->city,
			p->dataphone,
			p->voicephone,
			p->email != NULL ? p->email : "",
			p->url != NULL ? p->url : "",
			p->users_online, p->lines_free, p->lines_max,
			p->hostname, p->port);
	} else {
		prompt (BBSINFN, i + 1,
			p->bbstitle,
			p->codename,
			p->company,
			p->address1, strlen (p->address1) ? ", " : "",
			p->address2, strlen (p->address2) ? ", " : "", p->city,
			p->dataphone,
			p->voicephone,
			p->email != NULL ? p->email : "",
			p->url != NULL ? p->url : "", p->hostname, p->port);
	}

	if (strlen (p->bbs_ad))
		prompt (BBSAD, p->bbs_ad);
}


static int
connect_with (int i)
{
	char    tmp[256];
	int     pid, status;
	struct info_package_t *p = &systems[i];


	/* Is this the local system? */

	if (strlen (p->hostname) == 0 && p->port < 0) {
		exit (0);
	}

	prompt (RUNTEL);

	/* Kill the alarm, the user's made a choice */

	alarm (0);


	/* Telnet exports the DISPLAY variable to the remote system. Since we're not
	   going to be using X anytime soon now, we can kludge things and use the
	   DISPLAY variable to pass information to the remote system (eg the fact
	   that we're not just any J. Random Telnetter, we're using MetaBBS). */

	sprintf (tmp, "MetaBBS:%s:%s:%s",
		 getenv ("SPEED") != NULL ? getenv ("SPEED") : 0,
		 getenv ("TERM") != NULL ? getenv ("TERM") : "", bbscod);
	setenv ("DISPLAY", tmp, 1);


	/* Right, now attempt to use telnet to connect to the remote system */

	switch (pid = fork ()) {
	case 0:


		/* Set the line status */

		sprintf (tmp, "%s:%d/%s", p->hostname, p->port, p->codename);
		setchannelstate (LSR_METABBS, tmp);


		/* Call the telnet client */

		sprintf (tmp, "%d", p->port);
		execl ("/usr/bin/telnet", "/usr/bin/telnet", "-8E",
		       p->hostname, tmp, NULL);

	case -1:

		/* Oops, didn't work, fall over very ungracefully. */

		error_fatalsys
		    ("Unable to spawn telnet, dying in burning agony");

		break;		/* Not really needed */
	}


	/* Only the parent process gets to this point */

	waitpid (pid, &status, 0);



	/* Clear the screen afterwards -- it'll cause a nice pause, which is
	   sometimes necessary to see error messages, goodbye messages, etc */

	print ("\n\n\007\e[0m\e[2J");



	pid = WIFEXITED (status);	/* Bogus call: just need to call WIFEXITED() */
	if (WEXITSTATUS (status)) {	/* Looks like telnet died immediately */

		setchannelstate (LSR_LOGIN, "[NO-USER]");
		return 0;	/* Give the user a break in this case */
	}

	if (p->disconnect == 0)
		setchannelstate (LSR_LOGIN, "[NO-USER]");
	return p->disconnect;
}



int
run ()
{
	int     shown_list = 0;

	for (;;) {
		int     opt;
		char    c;

		if (!shown_list) {
			list_systems ();
			shown_list = 1;
		}

		prompt (SYSMNU, num_systems, num_systems);

		inp_get (0);
		if (!strlen (inp_buffer))
			continue;

		cnc_begin ();

		if (sscanf (cnc_nxtcmd, "%d", &opt) == 1) {
			if (opt < 1 || opt > num_systems) {
				prompt (ERROPT);
				continue;
			}
			return connect_with (opt - 1);
		}

		if (inp_isX (cnc_nxtcmd))
			break;

		switch (c = tolower (cnc_chr ())) {
		case 'i':
			if (sscanf (cnc_nxtcmd, "%d", &opt) == 1) {
				if (opt < 1 || opt > num_systems) {
					prompt (ERROPT);
					continue;
				}
				show_info (opt - 1);
				continue;
			} else {
				prompt (ERROPT);
				continue;
			}
			break;

		case 'r':
			gather ();

		case '?':
			shown_list = 0;
			continue;
		}

		prompt (ERROPT);
	}

	return 0;
}


int
main (int argc, char **argv)
{
	mode = sameas (argv[2], "--addlocal");
	init ();
	gather ();
	return run ();
}


/* End of File */
