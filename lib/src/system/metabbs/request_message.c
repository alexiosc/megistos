/*****************************************************************************\
 **                                                                         **
 **  FILE:     request_message.c                                            **
 **  AUTHORS:  Alexios                                                      **
 **  PURPOSE:  Ask for a specific message.                                  **
 **  NOTES:    Purposes:                                                    **
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
 * Revision 2.0  2004/09/13 19:44:54  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.4  2003/12/23 08:22:30  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.1  2000/01/08 12:17:03  alexios
 * Added an alarm() call to set a timeout, just in case.
 *
 * Revision 1.0  1999/07/28 23:15:45  alexios
 * Initial revision
 *
 *
 */


static const char rcsinfo[] =
    "$Id$";


#define WANT_SOCKET_H 1
#define WANT_DIRENT_H 1
#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_ERRNO_H 1
#define WANT_STAT_H 1
#define WANT_TYPES_H 1
#define WANT_FCNTL_H 1
#define WANT_UNISTD_H 1
#define WANT_ZLIB_H 1
#include <bbsinclude.h>

#include <rpc/rpc.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <typhoon.h>

#include <megistos/config.h>
#include "metaservices.h"
#include "metabbs.h"
#include <megistos/mail.h>
#include <megistos/ihavedb.h>


#ifdef HAVE_ZLIB

static void
try_compress (char **source, int *len)
{
	char   *tmp;
	unsigned long outlen;

	/* Allocating much more than the buffer required by zlib. Surely, it's
	   not going to allow a bytestring to *grow* by 10% instead of
	   shrinking? :-) */

	tmp = malloc (outlen = (*len + (*len / 10) + 12));
	if (tmp == NULL)
		return;		/* Failed, let's return. Zlib can read
				   uncompressed bytestrings as easily as
				   compressed ones. */

	if (compress (tmp, &outlen, *source, *len) != Z_OK) {
		free (tmp);	/* We're about to die anyway, so who cares? */
		return;
	}

	/* Excellent, we have nicely compressed output! */

	*source = tmp;
	*len = outlen;
}

#endif	/* HAVE_ZLIB */


/* Given a starting date (and the usual bbscodes), produce and yield a list of
   IHAVE entries after and including that time. */

struct club_message *
distclub_request_message_1_svc (message_request_t * msgreq,
				struct svc_req *req)
{
	static struct club_message retstuff;
	char    fname[512];
	int     fd;
	struct stat st;
	int     i;
	struct sockaddr_in *caller = svc_getcaller (server);
	message_t msg;

	bzero (&retstuff, sizeof (retstuff));


#ifdef DEBUG
	fprintf (stderr,
		 "Msg request for %s/%d by BBS %s from BBS %s (cmp=%d)",
		 msgreq->targetclub, msgreq->msgno, msgreq->codename,
		 msgreq->targetname, msgreq->compression);
#endif


	/* A reasonable timeout */

	alarm (60);


	/* Right. Is the targetted BBS registered with us? */

	if ((i = find_system (msgreq->targetname)) < 0) {
		retstuff.result_code = CLR_UNKNOWNCLUB;
		return &retstuff;
	}


	/* It is indeed. But is it really a Megistos BBS? */

	if (registered_systems[i].users_online < 0) {
		retstuff.result_code = CLR_NOTMEGISTOS;
		return &retstuff;
	}


	/* Ok, check club access. */

	this_system = &registered_systems[i];
	if (!loadclubhdr (msgreq->targetclub)) {
		retstuff.result_code = CLR_UNKNOWNCLUB;
		return &retstuff;
	}


	/* Is this guy allowed to see the club? */

	if (!getclubaccess (caller, msgreq->codename)) {
		retstuff.result_code = CLR_UNKNOWNCLUB;
		return &retstuff;
	}


	/* Strategy: we're given the local club name and message number. We'll read
	   the message in, compress it (if zlib is available) and build the reply
	   structure. Same for any attachment. */

	sprintf (fname, "%s/%s/" MESSAGEFILE, mkfname (MSGSDIR),
		 msgreq->targetclub, (long) msgreq->msgno);
	if (stat (fname, &st)) {
		retstuff.result_code = errno;
		return &retstuff;
	}
#ifdef DEBUG
	fprintf (stderr, "Yielding message %s/%d (fname=%s, size=%d)\n",
		 msgreq->targetclub, msgreq->msgno, fname, (int) st.st_size);
#endif

	if ((fd = open (fname, O_RDONLY)) < 0) {
		retstuff.result_code = errno;
		return &retstuff;
	}


	/* Read the header */

	if (read (fd, &msg, sizeof (msg)) != sizeof (msg)) {
		retstuff.result_code = CLR_CORRUPTMSG;
		return &retstuff;
	}


	/* We return an error for messages with an attachment that's not been
	   approved yet. This way, the message comes up again for distribution next
	   time round. Hopefully, but that time its attachment might be
	   approved (and the horse might learn to sing). */

	if ((msg.flags & (MSF_APPROVD | MSF_FILEATT)) == MSF_FILEATT) {
		retstuff.result_code = CLR_NOTAPPROVED;
		return &retstuff;
	}



	/* Read the body, one 386 page at a time (on other platforms, 4k is just a
	   reasonable blocking size. Loads of repetition here. Just substitute 'spam'
	   for 'message' and it'll all look very familiar. */

	retstuff.club_message_u.message.message.message_len =
	    st.st_size - sizeof (msg);
	retstuff.club_message_u.message.message.message_val =
	    malloc (st.st_size - sizeof (msg));

	i = 0;
	while (i < retstuff.club_message_u.message.message.message_len) {
		int     bytes_read;

		bytes_read =
		    read (fd,
			  &retstuff.club_message_u.message.message.
			  message_val[i], 4096);

		i += bytes_read;
		if (!bytes_read)
			break;
	}

	if (i < retstuff.club_message_u.message.message.message_len) {
		retstuff.result_code = CLR_CORRUPTMSG;
		return &retstuff;
	}

	close (fd);


	/* Build the returned header subset */

	strcpy (retstuff.club_message_u.message.from, msg.from);
	strcpy (retstuff.club_message_u.message.to, msg.to);
	strcpy (retstuff.club_message_u.message.subject, msg.subject);
	strcpy (retstuff.club_message_u.message.fatt, msg.fatt);
	retstuff.club_message_u.message.flags = msg.flags;
	retstuff.club_message_u.message.orgtime = msg.crtime;
	retstuff.club_message_u.message.orgdate = msg.crdate;


	/* Do we have to read in an attachment as well? */

	if (msg.flags & MSF_FILEATT) {
		strcpy (fname, mkfname ("%s/%s/" MSGATTDIR "/%d.att", MSGSDIR,
					msgreq->targetclub, msgreq->msgno));
		if (stat (fname, &st)) {
			retstuff.result_code = errno;
			return &retstuff;
		}

		if ((fd = open (fname, O_RDONLY)) < 0) {
			retstuff.result_code = errno;
			return &retstuff;
		}


		/* Now, read the attachment. The width of these lines isn't getting any
		   smaller. All hail 144-column framebuffer devices. Just to be nice to all
		   those 80-columners out there, I'll wrap these round. */

		retstuff.club_message_u.message.attachment.attachment_len =
		    st.st_size - sizeof (msg);
		retstuff.club_message_u.message.attachment.attachment_val =
		    malloc (st.st_size - sizeof (msg));

		i = 0;
		while (i <
		       retstuff.club_message_u.message.attachment.
		       attachment_len) {
			int     bytes_read;

			bytes_read =
			    read (fd,
				  &retstuff.club_message_u.message.attachment.
				  attachment_val[i], 4096);

			i += bytes_read;
			if (!bytes_read)
				break;
		}

		if (i <
		    retstuff.club_message_u.message.attachment.
		    attachment_len) {
			retstuff.result_code = CLR_CORRUPTMSG;
			return &retstuff;
		}

		close (fd);
	}


	/* Ok, we have both message header, message body and optional attachment read
	   into our reply structure. Now let's see if we can compress them. */

#ifdef HAVE_ZLIB
	if (msgreq->compression) {

		/* Notify the caller of our updated output format and uncompressed body and
		   attachment lengths. */

		retstuff.club_message_u.message.comp_result.compression = 1;
		retstuff.club_message_u.message.comp_result.compr_u.compr.
		    orig_msg_len =
		    retstuff.club_message_u.message.message.message_len;
		retstuff.club_message_u.message.comp_result.compr_u.compr.
		    orig_att_len =
		    retstuff.club_message_u.message.attachment.attachment_len;


		/* And now do the actual compression */

		try_compress (&retstuff.club_message_u.message.message.
			      message_val,
			      &retstuff.club_message_u.message.message.
			      message_len);
		try_compress (&retstuff.club_message_u.message.attachment.
			      attachment_val,
			      &retstuff.club_message_u.message.attachment.
			      attachment_len);
	}
#endif	/* HAVE_ZLIB */


	/* Fine, that's it. Return the message and be done with it. */


	retstuff.result_code = 0;
	return &retstuff;
}


/* End of File */
