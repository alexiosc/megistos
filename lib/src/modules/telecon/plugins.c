/*****************************************************************************\
 **                                                                         **
 **  FILE:     plugins.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 96, Version 0.5                                    **
 **  PURPOSE:  Teleconferences, plugin support.                             **
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
 * Revision 2.0  2004/09/13 19:44:53  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.6  2004/02/29 17:59:45  alexios
 * Minor permission/file location issues fixed to account for the new infrastructure.
 *
 * Revision 1.5  2003/12/27 12:38:06  alexios
 * Adjusted #includes. Switched to using struct msgbuf for IPC.
 *
 * Revision 1.4  2003/12/24 20:12:08  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.8  1999/08/13 17:03:06  alexios
 * Various bug fixes and improvements of the interface between
 * the teleconference module and its plugins.
 *
 * Revision 0.7  1999/08/07 02:19:04  alexios
 * Optimised runmodule().
 *
 * Revision 0.6  1999/07/28 23:13:16  alexios
 * Added some debugging info. Loads of bug fixes and changes
 * to make this more viable in preparation for some actual
 * plugins.
 *
 * Revision 0.5  1999/07/18 21:48:36  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 0.4  1998/12/27 16:10:27  alexios
 * Added autoconf support.
 *
 * Revision 0.3  1998/07/24 10:24:49  alexios
 * Generic debugging. Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:06:11  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 11:08:28  alexios
 * First registered revision. Adequate.
 *
 *
 */


static const char rcsinfo[] =
    "$Id$";



#define __TELEPLUGIN__


#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_SYS_STAT_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_IPC_H 1
#define WANT_SYS_MSG_H 1
#define WANT_SYS_IOCTL_H 1
#define WANT_TERMIO_H 1
#define WANT_WAIT_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include <telecon.h>
#include <teleconplugins.h>


/*
#define DEBUG 1
*/

#ifdef DEBUG
#define debug(s...) print("PLUGIN DEBUG: "##s)
#else
#define debug(s...) ;
#endif


static int numplugins;
static struct plugin *plugins = NULL;


static int
plugincmp (const void *A, const void *B)
{
	const struct plugin *a = A, *b = B;

	return strcmp (a->keyword, b->keyword);
}


void
initplugins ()
{
	FILE   *fp;

	if ((fp = fopen (mkfname (TELEPLUGINFILE), "r")) == NULL) {
		error_fatalsys ("Unable to open %s", mkfname (TELEPLUGINFILE));
	}
	if (!fread (&numplugins, sizeof (int), 1, fp)) {
		error_fatalsys ("Unable to read %s", mkfname (TELEPLUGINFILE));
	}

	if (plugins)
		free (plugins);
	plugins = alcmem (sizeof (struct plugin) * numplugins);

	if (fread (plugins, sizeof (struct plugin), numplugins, fp) !=
	    numplugins) {
		error_fatalsys ("Unable to read plugins from %s",
				mkfname (TELEPLUGINFILE));
	}
	fclose (fp);
}


void
listplugins ()
{
	int     shownheader = 0, i;

	for (i = 0; i < numplugins; i++) {
		if (!key_owns (&thisuseracc, plugins[i].key))
			continue;
		if (!shownheader) {
			shownheader = 1;
			prompt (PINTABL1);
		}
		prompt (PINTABL2, plugins[i].keyword,
			plugins[i].descr[thisuseracc.language - 1]);
	}
	if (!shownheader) {
		prompt (PINNONE);
		return;
	} else
		prompt (PINTABL3);
}


int
qexists ()
{
	struct msqid_ds buf;

	debug ("thisuseraux.pluginq=%d\n", thisuseraux.pluginq);
	return msgctl (thisuseraux.pluginq, IPC_STAT, &buf) == 0;
}


int
getid (char *plugin, char *channel, int *pid)
{
	char    qname[256];
	FILE   *fp;
	int     id;

	*pid = -1;
	strcpy (thisuseraux.plugin, plugin);
	sprintf (qname, mkfname (PLUGINQ, plugin, curchannel));
	debug ("plugin queue = (%s)\n", qname);
	if ((fp = fopen (qname, "r")) == NULL)
		return -1;
	debug ("plugin queue opened\n");
	if (!fscanf (fp, "%d %d", &id, pid)) {
		fclose (fp);
		return -1;
	} else
		fclose (fp);
	debug ("plugin queue id=%d, pid=%d", id, pid);
	thisuseraux.pluginq = id;
	if (!qexists ())
		return -1;
	debug ("plugin queue exists\n");
	return thisuseraux.pluginq;
}


void
makequeue (char *keyword, char *channel)
{
	int     id = msgget (IPC_PRIVATE, IPC_CREAT | IPC_EXCL | 0664);
	FILE   *fp;
	char    qname[256];

	if (id < 0) {
		error_fatal ("Unable to create IPC message queue (errno=%d).",
			     errno);
	}

	thisuseraux.pluginq = id;

	sprintf (qname, mkfname (PLUGINQ, keyword, channel));
	if ((fp = fopen (qname, "w")) == NULL) {
		error_fatalsys ("Unable to create %s", qname);
	}
	fprintf (fp, "%d -1\n", id);
	fclose (fp);
	chmod (qname, 0666);
}


void
runplugin (struct plugin *p)
{
	char    tmp [256], tmp2 [256];
	int     pid, status;

	debug ("running.\n");

	switch (pid = fork ()) {
	case 0:
#if 0
		if (s != NULL && strlen (s)) {
			strcpy (thisuseronl.input, s);
			thisuseronl.flags |= OLF_MMCONCAT;
		} else
			thisuseronl.flags &= ~OLF_MMCONCAT;

#endif
		/*mod_done (INI_ALL);*/

		sprintf (tmp, "%d", thisuseraux.pluginq);
		sprintf (tmp2, "%s/%s", mkfname(TELEPLUGINBIN), p->exec);
		execlp (tmp2, p->exec, p->keyword, curchannel,
			thisuseracc.userid, tmp, NULL);
		error_fatalsys ("Unable to execlp() teleplugin %s (%s)", p->exec, tmp2);

	case -1:
		error_fatalsys ("Unable to fork and run teleplugin!");

	default:
		waitpid (pid, &status, 0);
		mod_regpid (thisuseronl.channel);
		thisuseronl.flags &= ~(OLF_BUSY | OLF_NOTIMEOUT);
		inp_resetidle ();
		if (thisuseronl.flags & OLF_MMGCDGO)
			exit (0);
	}

#if 0
	sprintf (command, "%s %s %s %s %d",
		 p->exec,
		 p->keyword,
		 curchannel, thisuseracc.userid, thisuseraux.pluginq);
	runcommand (command);
#endif
}


int
pluginrunning (int pid)
{
	debug ("pluginrunning: PID=%d\n", pid);
	if (pid < 0)
		return 0;
	else {
		char    fname[256];
		struct stat st;

		sprintf (fname, "%s/%d", PROCDIR, pid);
		return stat (fname, &st) == 0;
	}
	return 0;
}


void
plugin (struct plugin *p, char *command)
{
	int     pid = -1;
	char    lock[256];
	struct pluginmsg msg;

	msg.mtype = MTYPE_COMMAND;
	strcpy (msg.userid, thisuseracc.userid);
	strcpy (msg.text, command);

	pid = -1;

	if (qexists ()) {
		if (getid (p->keyword, curchannel, &pid) == -1) {
			error_fatal ("Unable to read plugin queue file!");
		}
	} else {
		debug ("couldn't send\n");

		sprintf (lock, LCKPIN, p->keyword, curchannel);
		lock_wait (lock, 60);

		if (getid (p->keyword, curchannel, &pid) == -1) {
			debug ("making\n");
			lock_place (lock, "making");
			makequeue (p->keyword, curchannel);
			lock_rm (lock);
		}
	}

	if (command != NULL && strlen (command)) {
		debug ("sending %d bytes.\n", SIZE (command));
		msgsnd (thisuseraux.pluginq,
			(struct msgbuf *) &msg,
			SIZE (command), 0);
	}

	debug ("is plugin running?\n");
	if (!pluginrunning (pid)) {
		debug ("running plugin with command (%s)\n", command);
		lock_place (lock, "running");
		runplugin (p);
		lock_rm (lock);
	}
}


int
handleplugins (char *s)
{
	struct plugin *p, key;
	char    tmp[2048];
	int     n = strlen (s) + 1, i;

	if (*s == '/')
		return 0;

	if (!sscanf (s, "%s %n", tmp, &n))
		return 0;
	if (strlen (tmp) > 15)
		return 0;

	for (i = 0; tmp[i]; i++)
		tmp[i] = toupper (tmp[i]);

	strcpy (key.keyword, tmp);

	if ((p =
	     bsearch (&key, plugins, numplugins, sizeof (struct plugin),
		      plugincmp)) == NULL)
		return 0;

	if (!key_owns (&thisuseracc, p->key)) {
		prompt (PINNAX, p->keyword);
		return 1;
	}

	if (!qexists ()) {
		thisuseraux.plugin[0] = 0;
		thisuseraux.pluginq = -1;
	}

	if ((thisuseraux.plugin[0]) &&
	    (!sameas (thisuseraux.plugin, p->keyword))) {
		prompt (PINALR, thisuseraux.plugin, thisuseraux.plugin);
		return 1;
	}

	plugin (p, &s[n]);

	return 1;
}


/* Stuff required by plugins */

/*****************************************************************************/


char   *keyword, *channel, *userid;
int     qid;


void
writepid ()
{
	char    fname[256];
	FILE   *fp;

	sprintf (fname, mkfname (PLUGINQ, keyword, channel));
	if ((fp = fopen (fname, "w")) == NULL) {
		error_fatalsys ("Plugin %s: Unable to create %s", keyword,
				fname);
	}

	fprintf (fp, "%d %d\n", qid, getpid ());
	fclose (fp);
	chmod (fname, 0666);
}


void
initplugin (int argc, char **argv)
{
	struct stat st;
	char    fname[256];
	struct pluginmsg p;
	int     n;

	atexit (doneplugin);

	error_setnotify (0);

	init ();

	if (argc != 5) {
		error_fatal ("Plugin %s called with bad arguments.", argv[0]);
	}
	keyword = argv[1];
	channel = argv[2];
	userid = argv[3];
	qid = atoi (argv[4]);

	/* Sanity checks */

	sprintf (fname, "%s/%s", mkfname (TELEDIR), channel);
	if (stat (fname, &st)) {
		error_fatalsys ("Plugin %s: channel %s doesn't exist.",
				keyword, channel);
	}

	if (!usr_insys (userid, 0)) {
		error_fatal ("Plugin %s: user %s not on-line.", keyword,
			     userid);
	}

	mod_init (INI_USER);
	n = msgrcv (qid, (struct msgbuf *) &p, sizeof (p) - sizeof (long), 0,
		    IPC_NOWAIT);
	if (n > 0) {
		strcpy (thisuseronl.input, p.text);
		thisuseronl.flags |= OLF_MMCONCAT;
	}

	writepid ();
}


void
becomeserver ()
{
	/*mod_done(INI_ALL); */

	if (fork ())
		exit (0);

	atexit (doneserver);

	writepid ();

	ioctl (0, TIOCNOTTY, NULL);

	close (0);
	close (1);
	close (2);
}


void
doneplugin ()
{
}


void
doneserver ()
{
	struct msqid_ds buf;
	int     i = msgctl (qid, IPC_RMID, &buf);
	static int circular = 0;
	char    fname[256];

	debug ("doneserver...\n");

	if (i && !circular) {
		circular = 1;
		error_fatalsys ("Plugin %s: couldn't destroy msg queue id=%d.",
				keyword, qid);
	}
	sprintf (fname, mkfname (PLUGINQ, keyword, channel));
	unlink (fname);
}


/* End of File */
