/*****************************************************************************\
 **                                                                         **
 **  FILE:     listdownload.c                                               **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 1997, Version 1.0 (and that's it!)              **
 **  PURPOSE:  Handle 'List' downloads                                      **
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
 * Revision 1.4  2003/12/23 06:38:04  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.0  1997/08/28 11:29:05  alexios
 * Initial revision
 *
 *
 */


static const char rcsinfo[] = "$Id$";




#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>


int
main (int argc, char **argv)
{
	int     i;

	mod_setprogname (argv[0]);
	if (argc < 2)
		exit (1);

	mod_init (INI_ALL);

	fmt_lastresult = PAUSE_CONTINUE;
	for (i = 1; i < argc; i++) {
		if (fmt_lastresult != PAUSE_QUIT)
			out_printfile (argv[i]);
		unlink (argv[i]);
	}

	exit (0);
}


/* End of File */
