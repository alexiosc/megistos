/*****************************************************************************\
 **                                                                         **
 **  FILE:     parse.c                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 94, Version 0.5 alpha                           **
 **  PURPOSE:  Parse config files used by the file transfer module          **
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
 * Revision 1.5  2003/12/24 18:38:43  alexios
 * Fixed #includes.
 *
 * Revision 1.4  2003/12/23 23:20:23  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:08  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.7  1999/07/18 22:09:33  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 0.6  1998/12/27 16:34:28  alexios
 * Added autoconf support.
 *
 * Revision 0.5  1998/11/30 22:06:09  alexios
 * Added code to handle the new "bin" option.
 *
 * Revision 0.4  1998/07/24 10:31:31  alexios
 * Moved to stable status. Migrated to bbslib 0.6.
 *
 * Revision 0.3  1997/12/02 20:47:45  alexios
 * Switched to using the archiver file instead of the viewer
 * file.
 *
 * Revision 0.2  1997/11/06 20:18:32  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 11:25:42  alexios
 * First registered revision. Adequate.
 *
 *
 */


static const char rcsinfo[] =
    "$Id$";




#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_CTYPE_H 1
#define WANT_UNISTD_H 1
#define WANT_TIME_H 1
#define WANT_STRING_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "updown.h"
#include "mbk_archivers.h"


#define PRT_NAME    1
#define PRT_SELECT  2
#define PRT_DIR     3
#define PRT_PROG    4
#define PRT_BREAK   5
#define PRT_BATCH   6
#define PRT_NEEDN   7
#define PRT_BIN     8
#define PRT_END     9


struct directive protdir[] = {
	{"name", PRT_NAME},
	{"select", PRT_SELECT},
	{"dir", PRT_DIR},
	{"prog", PRT_PROG},
	{"break", PRT_BREAK},
	{"batch", PRT_BATCH},
	{"needn", PRT_NEEDN},
	{"bin", PRT_BIN},
	{"end", PRT_END},
	{"\0", 0}
};


#define VEW_STRING  1
#define VEW_TYPE    2
#define VEW_VIEW 3
#define VEW_END     4


struct directive viewdir[] = {
	{"string", VEW_STRING},
	{"type", VEW_TYPE},
	{"view", VEW_VIEW},
	{"end", VEW_END},
	{"\0", 0}
};


void
readprotocols ()
{
	FILE   *fp;
	int     linenum = 0;
	struct protocol prot;

	if ((fp = fopen (mkfname (PROTOCOLFILE), "r")) == NULL) {
		error_fatalsys ("Unable to open %s", mkfname (PROTOCOLFILE));
	}

	memset (&prot, 0, sizeof (prot));
	strcpy (prot.stopkey, "Ctrl-C");
	prot.flags = PRF_NEEDN;

	while (!feof (fp)) {
		char    line[1024], *cp, *sp, keyword[32], *value;
		int     i, directive;

		if (!fgets (line, 1024, fp))
			continue;
		linenum++;

		for (cp = line; *cp; cp++)
			if (*cp == 10 || *cp == 13) {
				*cp = 0;
				break;
			}
		for (cp = line; *cp && isspace (*cp); cp++);
		if (!strlen (cp))
			continue;
		if (*cp == '#')
			continue;
		strncpy (keyword, cp, 31);
		keyword[31] = 0;
		for (sp = keyword; *sp && !isspace (*sp); sp++);
		*sp = 0;
		for (; *cp && !isspace (*cp); cp++);
		for (value = cp; *value && isspace (*value); value++);

		for (directive = 0, i = 0; !directive && protdir[i].name[0];
		     i++) {
			if (sameas (protdir[i].name, keyword))
				directive = protdir[i].code;
		}
		if (!directive) {
			error_fatal ("Unknown directive (%s) in %s (line %d)",
				     keyword, mkfname (PROTOCOLFILE), linenum);
		}

		switch (directive) {
		case PRT_NAME:
			strncpy (prot.name, value, sizeof (prot.name));
			break;
		case PRT_SELECT:
			strncpy (prot.select, value, sizeof (prot.select));
			break;
		case PRT_DIR:
			if ((!sameto ("U", value)) && (!sameto ("D", value))) {
				error_fatal
				    ("Bad value (%s) for DIR directive in %s (line %d)",
				     value, mkfname (PROTOCOLFILE), linenum);
			} else if (sameto ("U", value))
				prot.flags |= PRF_UPLOAD;
			else
				prot.flags &= ~PRF_UPLOAD;
			break;
		case PRT_PROG:
			strncpy (prot.command, value, sizeof (prot.command));
			break;
		case PRT_BREAK:
			strncpy (prot.stopkey, value, sizeof (prot.stopkey));
			break;
		case PRT_BATCH:
			if ((!sameto ("Y", value)) && (!sameto ("N", value))) {
				error_fatal
				    ("Bad value (%s) for BATCH directive in %s (line %d)",
				     value, mkfname (PROTOCOLFILE), linenum);
			} else if (sameto ("Y", value))
				prot.flags |= PRF_BATCH;
			else
				prot.flags &= ~PRF_BATCH;
			break;
		case PRT_NEEDN:
			if ((!sameto ("Y", value)) && (!sameto ("N", value))) {
				error_fatal
				    ("Bad value (%s) for NEEDN directive in %s (line %d)",
				     value, mkfname (PROTOCOLFILE), linenum);
			} else if (sameto ("Y", value))
				prot.flags |= PRF_NEEDN;
			else
				prot.flags &= ~PRF_NEEDN;
			break;
		case PRT_BIN:
			if ((!sameto ("Y", value)) && (!sameto ("N", value))) {
				error_fatal
				    ("Bad value (%s) for BIN directive in %s (line %d)",
				     value, mkfname (PROTOCOLFILE), linenum);
			} else if (sameto ("Y", value))
				prot.flags |= PRF_BINARY;
			else
				prot.flags &= ~PRF_BINARY;
			break;
		case PRT_END:
			if (!prot.name[0]) {
				error_fatal
				    ("Missing NAME directive in %s (line %d)",
				     mkfname (PROTOCOLFILE), linenum);
			}
			if (!prot.select[0]) {
				error_fatal
				    ("Missing SELECT directive in %s (line %d)",
				     mkfname (PROTOCOLFILE), linenum);
			}
			if (!prot.command[0]) {
				error_fatal
				    ("Missing SELECT directive in %s (line %d)",
				     mkfname (PROTOCOLFILE), linenum);
			}

			numprotocols++;
			protocols =
			    realloc (protocols,
				     sizeof (struct protocol) * numprotocols);
			if (!protocols) {
				error_fatal
				    ("Unable to allocate memory for the protocol"
				     "table", NULL);
			} else {
				memcpy (&protocols[numprotocols - 1], &prot,
					sizeof (struct protocol));
				memset (&prot, 0, sizeof (prot));
				strcpy (prot.stopkey, "Ctrl-C");
				prot.flags = PRF_NEEDN;
			}
			break;
		}
	}

	fclose (fp);
}


void
readviewers ()
{
	int     n;
	struct viewer viewer;
	promptblock_t *msg = NULL;

	msg = msg_open ("archivers");

	memset (&viewer, 0, sizeof (viewer));

	for (n = 0; n < MAXARCHIVERS; n++) {
		char   *view = msg_get (VIEW1 + n * 7);

		if (!strlen (view))
			continue;

		strcpy (viewer.string, msg_get (STRING1 + n * 7));
		strcpy (viewer.type, msg_get (TYPE1 + n * 7));
		strcpy (viewer.command, msg_get (VIEW1 + n * 7));

		numviewers++;
		viewers =
		    realloc (viewers, sizeof (struct viewer) * numviewers);
		if (!viewers) {
			error_fatal ("Unable to allocate memory for the viewer"
				     "table", NULL);
		} else {
			memcpy (&viewers[numviewers - 1], &viewer,
				sizeof (struct viewer));
			memset (&viewer, 0, sizeof (viewer));
		}
	}

	msg_close (msg);
	msg_reset ();
}


void
readtransferlist (char *fname, int *count, int flags)
{
	FILE   *fp;
	xfer_item_t *item, *tmp, read;

	if ((fp = fopen (fname, "r")) == NULL)
		return;
	while (!feof (fp)) {

		if (fread (&read, sizeof (read), 1, fp) != 1)
			continue;
		if (read.flags & XFF_TAGGED && read.dir == FXM_TRANSIENT)
			read.flags &= ~XFF_TAGGED;
		memset (&item, 0, sizeof (item));

		(*count)++;
		totalitems++;
		tmp = alcmem (sizeof (xfer_item_t) * totalitems);
		memcpy (tmp, xferlist,
			sizeof (xfer_item_t) * (totalitems - 1));
		xferlist = tmp;
		item = &(xferlist)[totalitems - 1];

		memcpy (item, &read, sizeof (xfer_item_t));

		item->filename = strrchr (item->fullname, '/');
		if (!item->filename)
			item->filename = item->fullname;
		else
			item->filename++;
		item->size = 0;
		item->result = 0;
	}
	fclose (fp);
}




/* End of File */
