/*****************************************************************************\
 **                                                                         **
 **  FILE:    sublib.c                                                      **
 **  AUTHORS: Alexios                                                       **
 **  PURPOSE: Collect arrays of all sub-libraries of a library              **
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
 * $Id$
 *
 * $Log$
 * Revision 1.5  2003/12/27 08:59:39  alexios
 * Adjusted #includes.
 *
 * Revision 1.4  2003/12/24 20:12:10  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.3  1999/07/18 21:29:45  alexios
 * Fixed rx.h inclusion problem.
 *
 * Revision 0.2  1998/12/27 15:40:03  alexios
 * Added autoconf support.
 *
 * Revision 0.1  1998/04/21 10:12:53  alexios
 * Initial revision.
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
#define WANT_FCNTL_H 1
#define WANT_SYS_STAT_H 1
#define WANT_REGEX_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "files.h"
#include "mbk_files.h"


#define DELTA 10


static int oldlibnum = -1;
static int numchildren = 0;
static int currentchild = 0;
static int arraysize = 0;
static int *children = NULL;


void
reset_childarray ()
{
	numchildren = 0;
}


int
firstchild ()
{
	if (numchildren == 0)
		return -1;	/* Should never happen */
	currentchild = 1;
	return children[0];
}


int
nextchild ()
{
	if (currentchild >= numchildren)
		return -1;
	return children[currentchild++];
}


static void
grow_array ()
{
	if (children == NULL || numchildren >= arraysize) {
		int    *tmp;

		arraysize += DELTA;
		tmp = alcmem (arraysize * sizeof (int));
		bzero (tmp, sizeof (tmp));
		if (children != NULL) {
			memcpy (tmp, children, sizeof (int) * numchildren);
			free (children);
		}
		children = tmp;
	}
}


static void
add_child (int libnum)
{
	grow_array ();
	children[numchildren++] = libnum;
}


static int
add_subtree (int libnum)
{
	struct libidx l;

	if (!libreadnum (libnum, &l))
		return 0;
	else if (!getlibaccess (&l, ACC_VISIBLE))
		return 0;
	else {
		int     res;
		struct libidx child, otherchild;

		res = libgetchild (l.libnum, "", &otherchild);
		while (res) {
			memcpy (&child, &otherchild, sizeof (child));
			add_child (child.libnum);
			res =
			    libgetchild (l.libnum, child.keyname, &otherchild);
			if (!add_subtree (child.libnum))
				return 0;
		}
	}
	return 1;
}


void
get_children ()
{
	/* Don't recalculate the list of children unless necessary */

	if (oldlibnum == library.libnum && children != NULL && numchildren > 0)
		return;
	reset_childarray ();

	/* Add *this* library as well. Not exactly consistent with the term
	   'children', but we need it. */

	add_child (library.libnum);

	/* Now add the actual children */

	add_subtree (library.libnum);
	oldlibnum = library.libnum;
}


/* End of File */
