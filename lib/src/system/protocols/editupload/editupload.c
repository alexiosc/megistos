/*****************************************************************************\
 **                                                                         **
 **  FILE:     editupload.c                                                 **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 1996, Version 1.0 (and that's it!)                 **
 **  PURPOSE:  Handle 'Edit' uploads                                        **
 **  NOTES:    Calls the editor as a means of uploading a file.             **
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
 * Revision 1.3  1998/12/27 16:29:48  alexios
 * Added autoconf support.
 *
 * Revision 1.2  1998/07/24 10:28:44  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 1.1  1997/11/06 20:05:11  alexios
 * Added GPL legalese to the top of this file.
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
	FILE   *fp;

	mod_setprogname (argv[0]);
	if (argc != 2)
		exit (1);

	if ((fp = fopen (argv[1], "w")) == NULL)
		exit (1);
	fclose (fp);

	system (STTYBIN " -echo start undef stop undef intr undef susp undef");
	mod_init (INI_ALL);
	print ("\033[0m");
	exit (editor (argv[1], 512 << 10));
}


/* End of File */
