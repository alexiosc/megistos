/*****************************************************************************\
 **                                                                         **
 **  FILE:     opapprove.c                                                  **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, January 1999                                              **
 **  PURPOSE:  Approve files                                                **
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
 * Revision 1.4  2003/12/24 20:12:12  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.0  1999/07/18 21:27:24  alexios
 * Initial revision
 *
 *
 */


static const char rcsinfo[] =
    "$Id$";


#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_STRING_H 1
#define WANT_CTYPE_H 1
#define WANT_UNISTD_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_STAT_H 1
#define WANT_FCNTL_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include <megistos/files.h>
#include <megistos/mbk/mbk_files.h>


static int filesapproved = 0;


static void
approvekeywords (struct libidx *l, struct fileidx *f)
{
	struct filekey k;
	int     morekeys, keys = 0;
	char    keystg[8192];

	keystg[0] = 0;
	morekeys = keyfilefirst (l->libnum, f->fname, 0, &k);
	while (morekeys) {
		char    tmp[32];

		keys++;
		sprintf (tmp, "%s ", k.keyword);
		strcat (keystg, tmp);
		morekeys = keyfilenext (l->libnum, f->fname, 0, &k);
	}
	if (keys) {
		char    k[8192], *cp;

		strcpy (k, keystg);
		for (cp = strtok (k, " "); cp; cp = strtok (NULL, " ")) {
			deletekeyword (l->libnum, f->fname, 0, cp);
		}
		addkeywords (keystg, 1, f);
	}
}


static int
approvefile (struct libidx *l, char *fname)
{
	struct fileidx f;
	char    c, fn[1024];
	struct stat st;

	/* Read the file and ask whether the user wants it approved or not */

	filesapproved++;
	if (!fileread (l->libnum, fname, 0, &f))
		return 1;

	for (;;) {
		int     res;

		fileinfo (l, &f);
	      nohelp:
		inp_setflags (INF_HELP);
		res = get_menu (&c, 0, 0, OAPPASK, OAPPERR, "YND", 0, 0);
		inp_clearflags (INF_HELP);
		if (res < 0)
			continue;
		else if (!res)
			return 0;

		if (c == 'N')
			return 1;
		else if (c == 'D') {
			struct libidx tmp;

			memcpy (&tmp, &library, sizeof (library));
			download (fname);
			memcpy (&library, &tmp, sizeof (library));
			goto nohelp;
		} else if (c == 'Y')
			break;
	}


	/* Ok, let's approve it then. First re-read the file. */

	if (!fileread (l->libnum, fname, 0, &f))
		return 1;
	filedelete (&f);	/* This is needed to properly update the approved field */
	f.approved = 1;
	strcpy (f.approved_by, thisuseracc.userid);
	filecreate (&f);
	prompt (OAPPOK);


	/* Now we have to approve its keywords, one by one. */

	approvekeywords (l, &f);


	/* Finally, update the library */

	{
		struct libidx lib;

		if (libreadnum (l->libnum, &lib)) {
			sprintf (fn, "%s/%s", lib.dir, fname);
			if (!stat (fn, &st)) {
				lib.numbytes += st.st_size;
				lib.bytesunapp -= st.st_size;
			}
			lib.numfiles++;
			lib.numunapp--;

			libupdate (&lib);
		}
	}

	return 1;
}


static int
approveall ()
{
	int     i;
	struct fileidx f;
	char    c;

	i = filegetfirst (library.libnum, &f, 0);
	if (!i || f.flibnum != library.libnum)
		return 1;
	inp_nonblock ();

	while (i) {
		if (read (fileno (stdin), &c, 1) &&
		    ((c == 13) || (c == 10) || (c == 27) || (c == 15) ||
		     (c == 3)))
			break;
		if (fmt_lastresult == PAUSE_QUIT)
			break;

		if (f.approved)
			continue;
		if (f.flibnum != library.libnum)
			break;

		inp_block ();
		approvefile (&library, f.fname);
		inp_nonblock ();

		i = filegetnext (library.libnum, &f);
	}
	inp_block ();

	return fmt_lastresult != PAUSE_QUIT;
}


static int
traverseapprove (struct libidx *l)
{
	char    c;

	if (read (fileno (stdin), &c, 1) &&
	    ((c == 13) || (c == 10) || (c == 27) || (c == 15) || (c == 3)))
		return 0;
	if (fmt_lastresult == PAUSE_QUIT)
		return 0;

	if (!islibop (&library))
		return 1;
	else {
		struct libidx child, otherchild;
		struct fileidx f;
		int     res;

		/* Check if there are any unapproved files in the library. We
		   don't even mention libraries without unapproved files here. */

		if (filegetfirst (l->libnum, &f, 0)) {
			struct libidx tmp;

			memcpy (&tmp, &library, sizeof (tmp));
			memcpy (&library, l, sizeof (library));
			prompt (OAPPSCN);
			res = approveall ();
			memcpy (&library, &tmp, sizeof (library));
			if (!res)
				return 0;
			inp_nonblock ();	/* approveall() restores blocking mode */
		}

		res = libgetchild (l->libnum, "", &otherchild);
		while (res) {
			memcpy (&child, &otherchild, sizeof (child));
			res =
			    libgetchild (l->libnum, child.keyname,
					 &otherchild);
			if (!traverseapprove (&child))
				return 0;
		}
	}

	return 1;
}


static char *
getfilename ()
{
	static char fn[256];

	for (;;) {
		if (cnc_more ()) {
			strcpy (fn, cnc_word ());
		} else {
			prompt (OAPPQ);
			inp_get (sizeof (fn) - 1);
			strcpy (fn, inp_buffer);
		}

		if (inp_isX (fn))
			return NULL;
		else if (!strlen (fn))
			return ".";
		else if (!strcmp (fn, "."))
			return ".";

		if (!fileexists (library.libnum, fn, 0)) {
			cnc_end ();
			prompt (OAPPR);
			continue;
		} else
			break;
	}
	return fn;
}


void
op_approve ()
{
	char   *fn = getfilename ();

	if (fn == NULL)
		return;
	filesapproved = 0;
	if (strcmp (fn, ".")) {
		approvefile (&library, fn);
	} else {
		inp_nonblock ();
		traverseapprove (&library);
		inp_block ();
	}
	if (!filesapproved)
		prompt (OAPPNUN);
}


/* End of File */
