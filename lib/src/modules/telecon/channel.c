/*****************************************************************************\
 **                                                                         **
 **  FILE:     channel.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 95, Version 0.5                                 **
 **  PURPOSE:  Teleconferences, channel handling functions                  **
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
 * Revision 1.5  2003/12/27 12:29:39  alexios
 * Adjusted #includes.
 *
 * Revision 1.4  2003/12/24 20:12:09  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.8  1999/07/18 21:48:36  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 0.7  1998/12/27 16:10:27  alexios
 * Added autoconf support. Added support for new channel_getstatus().
 * Other slight fixes.
 *
 * Revision 0.6  1998/08/14 11:51:24  alexios
 * Removed the "DONE" markers from updated functions.
 *
 * Revision 0.5  1998/08/14 11:45:25  alexios
 * Rewrote channel engine to use directories for channels and
 * files for the header and user records. This makes sure no
 * strange filing bugs show up like before.
 *
 * Revision 0.4  1998/08/11 10:21:33  alexios
 * Moved chanscan() here.
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



#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_DIRENT_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "telecon.h"
#include "mbk_telecon.h"


char    curchannel[256];

struct chanhdr chanhdr;
struct chanusr chanusr;

int				/* DONE */
getaccess (char *chan)
{
	if (usr_exists (chan)) {
		static struct tlcuser usr;

		if (!loadtlcuser (chan, &usr)) {
			error_fatal ("Can't load user record for %s", chan);
		}
		if (usr.flags & TLF_BEGUNINV)
			return CHF_PRIVATE;
		else if (usr.flags & TLF_BEGPANEL)
			return CHF_READONLY;
	} else if (chan[0] == '/') {
		int     clubax = getclubax (&thisuseracc, chan);

		if (clubax <= CAX_ZERO)
			return CHF_PRIVATE;
		else if (clubax <= CAX_READ)
			return CHF_READONLY;
		else if (clubax <= CAX_UPLOAD)
			return CHF_OPEN;
		else
			return CHF_MODERATED;
	}
	return CHF_OPEN;
}


int
enterchannel (char *channel)
{
	char    fname[256], lock[256], header[256];
	int     new;
	struct chanusr usr;
	struct stat st;

	if (sameas (channel, curchannel))
		return -1;

	if (*channel == '.')
		return -2;

	sprintf (fname, "%s/%s", mkfname (TELEDIR), mkchfn (channel));

	sprintf (lock, CHANLOCK, mkchfn (channel));
	lock_wait (lock, 10);
	lock_place (lock, "entering");

	mkdir (fname, 0770);

	if (stat (fname, &st)) {
		int     i = errno;

		lock_rm (lock);
		errno = i;
		error_fatalsys ("Unable to open/create channel directory %s",
				fname);
	}

	sprintf (header, "%s/.header", fname);
	new = (stat (header, &st) != 0);

	if (new) {
		memset (&chanhdr, 0, sizeof (struct chanhdr));

		moderate (channel, thisuseracc.userid, chanhdr.moderator);

		strcpy (chanhdr.topic, gettopic (channel));
		chanhdr.flags = getaccess (channel);

		writechanhdr (channel, &chanhdr);

		memcpy (&usr,
			makechanusr (thisuseracc.userid,
				     getdefusrax (channel,
						  thisuseracc.userid)),
			sizeof (struct chanusr));

		usr.flags |= CUF_PRESENT;

		writechanusr (channel, &usr);

		strcpy (thisuseronl.telechan, channel);
		strcpy (curchannel, channel);
		thisuseraux.access = usr.flags;

		lock_rm (lock);
	} else {
		int     ax;

		ax = getusrax (channel, thisuseracc.userid);

		if (ax & CUF_MODERATOR) {
			struct chanhdr *h = readchanhdr (channel);

			if (h == NULL) {
				error_fatal
				    ("Unable to read channel header for channel %s",
				     channel);
			}
			memcpy (&chanhdr, h, sizeof (chanhdr));
			moderate (channel, thisuseracc.userid,
				  chanhdr.moderator);
			writechanhdr (channel, &chanhdr);
		}

		lock_rm (lock);

		ax |=
		    (thisuseronl.
		     flags & OLF_TLCUNLIST ? CUF_UNLISTED : 0) | CUF_PRESENT;
		thisuseraux.access = ax;

		setusrax (channel, thisuseracc.userid, thisuseracc.sex, ax,
			  -1);

		strcpy (thisuseronl.telechan, channel);
		strcpy (curchannel, channel);
	}
	return 0;
}



void
leavechannel ()
{
	if (!curchannel[0])
		return;
	chanusrflags (thisuseracc.userid, curchannel, 0, CUF_PRESENT);
}


void
killpersonalchannel ()
{
	struct chanhdr *hdr;
	struct chanusr *usr;

	if ((hdr = begscan (thisuseracc.userid, TSM_PRESENT)) == NULL)
		return;
	while ((usr = getscan ()) != NULL) {
		if (usr_insys (usr->userid, 0)) {
			sprompt_other (othrshm, out_buffer, DISCDROP,
				       msg_getunitl (SEXM1,
						     thisuseracc.sex ==
						     USX_MALE,
						     othruseracc.language - 1),
				       thisuseracc.userid);

			usr_injoth (&othruseronl, out_buffer, 0);

			sendmain (othruseronl.userid);
		}
	}
	endscan ();
}


void
leavechannels ()
{
	char    fname[256], rmname[256], lock[256];

	struct dirent **channels;
	int     i, j;

	sprintf (fname, "%s/%s", mkfname (TELEDIR), thisuseracc.userid);
	unlink (fname);

	i = scandir (mkfname (TELEDIR), &channels, chanselect, alphasort);

	for (j = 0; j < i; j++) {
		int     k;
		struct dirent **tmp;

		sprintf (fname, "%s/%s", mkfname (TELEDIR),
			 channels[j]->d_name);

		sprintf (lock, CHANLOCK, channels[j]->d_name);
		lock_wait (lock, 10);
		lock_place (lock, "logout");

		sprintf (rmname, "%s/%s+", fname, thisuseracc.userid);
		unlink (rmname);
		sprintf (rmname, "%s/%s-", fname, thisuseracc.userid);
		unlink (rmname);

		k = scandir (fname, &tmp, chanselect, alphasort);

		/* Remove the channel directory altogether, if it's empty */

		rmdir (fname);


		lock_rm (lock);
		for (; k; k--)
			free (tmp[k - 1]);
		free (tmp);
	}

	for (j = 0; j < i; j++)
		free (channels[i]);
	free (channels);
}


struct chanhdr *
readchanhdr (char *channel)
{
	static struct chanhdr c;
	char    lock[256], fname[256];
	FILE   *fp;

	sprintf (lock, CHANLOCK, mkchfn (channel));
	lock_wait (lock, 10);
	lock_place (lock, "reading");

	sprintf (fname, "%s/%s/.header", mkfname (TELEDIR), mkchfn (channel));

	if ((fp = fopen (fname, "r")) == NULL) {
		lock_rm (lock);
		fclose (fp);
		return NULL;
	}

	if (fread (&c, sizeof (c), 1, fp) != 1) {
		int     i = errno;

		lock_rm (lock);
		fclose (fp);
		errno = i;
		error_fatalsys ("Unable to read channel file %s", fname);
	}

	lock_rm (lock);

	return &c;
}


void
writechanhdr (char *channel, struct chanhdr *c)
{
	char    lock[256], fname[256];
	FILE   *fp;
	struct stat st;

	sprintf (lock, CHANLOCK, mkchfn (channel));
	lock_wait (lock, 10);
	lock_place (lock, "writing");

	/* Make the directory */

	sprintf (fname, "%s/%s", mkfname (TELEDIR), mkchfn (channel));
	mkdir (fname, 0770);
	if (stat (fname, &st)) {
		int     i = errno;

		lock_rm (lock);
		errno = i;
		error_fatalsys ("Unable to open/create channel directory %s",
				fname);
	}

	/* Make the header file */

	strcat (fname, "/.header");
	if ((fp = fopen (fname, "w")) == NULL) {
		int     i = errno;

		lock_rm (lock);
		fclose (fp);
		errno = i;
		error_fatalsys ("Unable to open channel header %s", fname);
	}
	if (fwrite (c, sizeof (struct chanhdr), 1, fp) != 1) {
		int     i = errno;

		lock_rm (lock);
		fclose (fp);
		errno = i;
		error_fatal ("Unable to write channel header %s", fname);
	}
	fclose (fp);
	lock_rm (lock);
}


int
makechannel (char *channel, char *userid)
{
	char    fname[256];
	struct stat st;
	struct chanhdr chanhdr;

	sprintf (fname, "%s/%s/.header", mkfname (TELEDIR), mkchfn (channel));
	if (!stat (fname, &st))
		return 0;

	memset (&chanhdr, 0, sizeof (chanhdr));
	moderate (channel, userid, chanhdr.moderator);
	strcpy (chanhdr.topic, gettopic (channel));
	chanhdr.flags = getaccess (channel);

	writechanhdr (channel, &chanhdr);
	return 1;
}


void
setchanax (int ax)
{
	struct chanhdr *c;

	makechannel (thisuseracc.userid, thisuseracc.userid);	/* just in case */

	if ((c = readchanhdr (thisuseracc.userid)) == NULL) {
		error_fatal ("Unable to read channel %s", thisuseracc.userid);
	}

	c->flags &= ~CHF_ACCESS;
	c->flags |= ax;

	writechanhdr (thisuseracc.userid, c);
}


void
chanscan ()
{
	struct dirent **channels;
	int     i =
	    scandir (mkfname (TELEDIR), &channels, chanselect, alphasort), j;

	prompt (SCANHDR);

	for (j = 0; j < i; j++) {
		struct chanhdr *hdr;
		struct chanusr *usr;

		hdr = begscan (channels[j]->d_name, TSM_ALL);

		if (channels[j]->d_name[0] == '_')
			channels[j]->d_name[0] = '/';

		if (hdr) {
			while ((usr = getscan ()) != NULL) {
				if (usr->flags & CUF_UNLISTED &&
				    !key_owns (&thisuseracc, sopkey))
					continue;

				if (!(usr->flags & CUF_PRESENT)) {
					usr_insys (usr->userid, 0);

					if (usr->flags & CUF_CHATTING) {
						prompt (SCANTAB1A,
							usr->userid);
						usr_insys (othruseraux.
							   chatparty, 0);
						prompt (othruseracc.sex ==
							USX_MALE ? SCANCHTM :
							SCANCHTF,
							othruseracc.userid);
						prompt (SCANTABE);
						continue;
					}

					if ((sameas
					     (usr->userid, thisuseracc.userid)
					     || sameas (channels[j]->d_name,
							thisuseracc.userid))
					    && (usr->flags & CUF_EXPLICIT)) {

						int     pr;

						pr = sameas (channels[j]->
							     d_name,
							     thisuseracc.
							     userid) ? SCANAX2
						    : SCANACC;

						prompt (strcmp
							(usr->userid,
							 thisuseracc.
							 userid) ? SCANTAB1B :
							SCANTAB1A,
							usr->userid);

						if (usr->flags & CUF_ACCESS) {
							prompt (pr,
								msg_getunit
								(usr->
								 flags &
								 CUF_READONLY ?
								 SCANRM :
								 SCANIM,
								 thisuseracc.
								 sex ==
								 USX_MALE));
						} else {
							prompt (pr,
								msg_getunit
								(SCANUM,
								 thisuseracc.
								 sex ==
								 USX_MALE));
						}

						if (pr == SCANAX2) {
							prompt (SCANINVY);
						} else
						    if (usr_insys
							(channels[j]->d_name,
							 0)) {
							prompt (othruseracc.
								sex ==
								USX_MALE ?
								SCANINVM :
								SCANINVF,
								othruseracc.
								userid);
						} else if (channels[j]->
							   d_name[0] == '/') {
							prompt (SCANINVC,
								channels[j]->
								d_name);
						} else
							prompt (SCANINVO,
								channels[j]->
								d_name);

						prompt (SCANTABE);
					}
					continue;
				}

				prompt (strcmp
					(usr->userid,
					 thisuseracc.
					 userid) ? SCANTAB1B : SCANTAB1A,
					usr->userid);

				prompt (strcmp
					(channels[j]->d_name,
					 thisuseronl.
					 telechan) ? SCANOTHCH : SCANTHSCH);

				if (usr_insys (channels[j]->d_name, 0)) {
					prompt (othruseracc.sex ==
						USX_MALE ? SCANPRVM : SCANPRVF,
						othruseracc.userid);
				} else if (channels[j]->d_name[0] == '/') {
					prompt (SCANCLUB, channels[j]->d_name);
				} else
					prompt (SCANOTHR, channels[j]->d_name);

				if (usr->flags & CUF_UNLISTED)
					prompt (SCANUNL);
				if (usr->flags & CUF_READONLY)
					prompt (SCANRO);

				if (sameas (hdr->moderator, usr->userid)) {
					if (hdr->topic[0])
						prompt (SCANTPC, hdr->topic);
				}

				prompt (SCANTABE);
			}
		}

		endscan ();
		free (channels[j]);
	}
	free (channels);

	prompt (SCANFTR);
}


/* End of File */
