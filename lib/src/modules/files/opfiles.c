/*****************************************************************************\
 **                                                                         **
 **  FILE:     opfiles.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, January 1999                                              **
 **  PURPOSE:  Execute the UNIX file(1) command in a library                **
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


void
op_files ()
{
	FILE   *pp;
	char    command[512];

	sprintf (command, "cd %s; file -L *", library.dir);
	if ((pp = popen (command, "r")) == NULL) {
		fclose (pp);
		error_logsys ("Unable to popen(\"%s\",\"r\").", command);
		return;
	}

	prompt (OFILHD);
	inp_nonblock ();
	while (!feof (pp)) {
		char    line[8192], *type;

		if (!fgets (line, sizeof (line), pp))
			break;
		if ((type = strstr (line, ": ")) == NULL)
			continue;
		type++;
		while (*type == 32)
			type++;
		*(type - 1) = 0;
		prompt (OFILLN, line, type);
		if (fmt_lastresult == PAUSE_QUIT)
			break;
	}
	inp_block ();
	if (fmt_lastresult != PAUSE_QUIT)
		prompt (OFILFT);
	pclose (pp);
}


/* End of File */
