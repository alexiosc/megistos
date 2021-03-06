/*****************************************************************************\
 **                                                                         **
 **  FILE:     ttynum.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 94                                                   **
 **  PURPOSE:  Number ttys so they look like MajorBBS channels.             **
 **  NOTES:    Tty numbering is defined in /bbs/channel.defs/CHANNELS.      **
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
 * $Id: ttynum.c,v 2.0 2004/09/13 19:44:34 alexios Exp $
 *
 * $Log: ttynum.c,v $
 * Revision 2.0  2004/09/13 19:44:34  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.6  2003/12/19 13:25:18  alexios
 * Updated include directives.
 *
 * Revision 1.5  2003/09/28 11:40:07  alexios
 * Ran indent(1) on all C source to improve readability.
 *
 * Revision 1.4  2003/08/15 18:08:45  alexios
 * Rationalised RCS/CVS ident(1) strings.
 *
 * Revision 1.3  2001/04/22 14:49:05  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.5  1999/07/18 21:01:53  alexios
 * Changed a few error_fatal() calls to error_fatalsys(). Fixed a slight
 * oversight in telnetlinecount().
 *
 * Revision 0.4  1998/12/27 14:31:16  alexios
 * Added autoconf support. Added code to recognise the channel
 * file by magic number and choke if it isn't there. Altered
 * code to use the new channel_getstatus().
 *
 * Revision 0.3  1998/07/24 10:08:57  alexios
 * Made use of new error reporting.
 *
 * Revision 0.2  1997/11/06 20:03:54  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/26 16:35:17  alexios
 * First registered revision. Adequate.
 *
 *
 */


static const char rcsinfo[] =
    "$Id: ttynum.c,v 2.0 2004/09/13 19:44:34 alexios Exp $";



#define TTYNUM_C 1
#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#include <megistos/bbsinclude.h>

#include <megistos/bbs.h>


struct channeldef *channels = NULL;
struct channeldef *chan_last = NULL;
int     chan_count = 0;


int
chancmp (const void *a, const void *b)
{
	return ((struct channeldef *) a)->channel -
	    ((struct channeldef *) b)->channel;
}


void
chan_init ()
{
	FILE   *fp;
	char    magic[256];

	if ((fp = fopen (mkfname (CHANDEFFILE), "r")) == NULL) {
		error_fatalsys ("Unable to open %s", mkfname (CHANDEFFILE));
	}

	/* Check the magic number */
	bzero (magic, sizeof (magic));
	if (fread (magic, strlen (CHANNEL_MAGIC), 1, fp) != 1) {
		error_fatalsys ("Unable to read magic number from %s",
				mkfname (CHANDEFFILE));
	}
	if (strcmp (magic, CHANNEL_MAGIC)) {
		error_fatal
		    ("Corrupted channel table file (%s), use mkchan to recreate it.",
		     mkfname (CHANDEFFILE));
	}

	if (channels) {
		free (channels);
		chan_count = 0;
	}
	if (fread (&chan_count, sizeof (chan_count), 1, fp) != 1) {
		error_fatalsys ("Unable to read %s", mkfname (CHANDEFFILE));
	}

	if ((channels =
	     alcmem (sizeof (struct channeldef) * chan_count)) == NULL) {
		error_fatalsys ("Unable to allocate memory for channel table.",
				mkfname (CHANDEFFILE));
	}

	if (fread (channels, sizeof (struct channeldef), chan_count, fp) !=
	    chan_count) {
		error_fatalsys ("Unable to read %s", mkfname (CHANDEFFILE));
	}

	fclose (fp);
	chan_last = channels;
}


uint32
chan_getnum (char *tty)
{
	int     i;

	if (chan_last && !strcmp (chan_last->ttyname, tty))
		return chan_last->channel;
	for (i = 0; i < chan_count; i++) {
		if (!strcmp (channels[i].ttyname, tty)) {
			chan_last = &channels[i];
			return channels[i].channel;
		}
	}
	return -1;
}


uint32
chan_getindex (char *tty)
{
	int     i;

	for (i = 0; i < chan_count; i++) {
		if (!strcmp (channels[i].ttyname, tty)) {
			chan_last = &channels[i];
			return i;
		}
	}
	return -1;
}


char   *
chan_getname (uint32 num)
{
	struct channeldef *temp, key;

	key.channel = num;
	if (chan_last && chan_last->channel == num)
		return chan_last->ttyname;
	temp =
	    bsearch (&key, channels, chan_count, sizeof (struct channeldef),
		     chancmp);
	if (!temp)
		return NULL;
	chan_last = temp;
	return temp->ttyname;
}


uint32
chan_telnetlinecount ()
{
	int     i, retval;

	for (i = 0, retval = 0; i < chan_count; i++) {
		if (channels[i].flags & TTF_TELNET) {
			channel_status_t status;

			channel_getstatus (channels[i].ttyname, &status);
			if (strcmp (status.user, "[NO-USER]") ||
			    (status.result != LSR_INIT &&
			     status.result != LSR_OK &&
			     status.result != LSR_FAIL &&
			     status.result != LSR_LOGOUT &&
			     status.result != LSR_FAIL))
				retval++;
		}
	}
	return retval;
}
