/*****************************************************************************\
 **                                                                         **
 **  FILE:     asciiupload.c                                                **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, November 1994, Version 1.0 (and that's it!)               **
 **  PURPOSE:  Handle 'ASCII' uploads                                       **
 **  NOTES:    Enables termination of the upload in a number of intuitive   **
 **            ways, including EOF (ctrl-d), X (exit), /s (save), OK, etc   **
 **                                                                         **
 **            Its output has to be redirected to the desired file.         **
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
 * Revision 1.4  2003/12/23 06:38:04  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.3  1998/12/27 16:28:54  alexios
 * Added autoconf support.
 *
 * Revision 1.2  1998/07/24 10:28:35  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 1.1  1997/11/06 20:05:08  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 1.0  1997/08/28 11:28:27  alexios
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


#ifdef GREEK
char    s1[5], s2[5], s3[5], s4[5], s5[5], s6[5], s7[5], s8[5];
#endif


int
chkterm (char *line)
{
	char   *cp;
	char    s[8192];

	strcpy (s, line);
	if ((cp = strchr (s, 10)) != NULL)
		*cp = 0;
	if ((cp = strchr (s, 13)) != NULL)
		*cp = 0;
	return !(strcasecmp (s, "OK") && strcasecmp (s, "/S") &&
		 strcasecmp (s, ".S")
		 && strcasecmp (s, "OK") && strcasecmp (s, "X")
#ifdef GREEK
		 && strcmp (s, s1) && strcmp (s, s2) && strcmp (s, s3) &&
		 strcmp (s, s4)
		 && strcmp (s, s5) && strcmp (s, s6) && strcmp (s, s7) &&
		 strcmp (s, s8)
#endif
	    );
}


int
main ()
{

#ifdef GREEK
	sprintf (s1, "%c%c", -90, -95);	/* OK in capital greek letters */
	sprintf (s2, "%c%c", -114, -119);	/* OK in lower case greek letters */
	sprintf (s3, "%c", -107);	/* X in capital greek letters */
	sprintf (s4, "%c", -82);	/* X in lower case greek letters */
	sprintf (s5, "/%c", -111);	/* /S in capital greek letters */
	sprintf (s6, "/%c", -87);	/* /s in lower case greek letters */
	sprintf (s7, ".%c", -111);	/* .S in capital greek letters */
	sprintf (s8, ".%c", -87);	/* .s in lower case greek letters */
#endif

	while (!feof (stdin)) {
		char    line[8192];

		if (fgets (line, sizeof (line), stdin)) {
			if (chkterm (line))
				break;
			fputs (line, stdout);
		}
	}
	return 0;
}



/* End of File */
