/*****************************************************************************\
 **                                                                         **
 **  FILE:     offline.graffiti.h                                           **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 1997, Version 0.1                                  **
 **  PURPOSE:  Graffiti wall plugin definitions and stuff.                  **
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
 * Revision 2.0  2004/09/13 19:44:52  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2003/12/27 12:29:39  alexios
 * Adjusted #includes.
 *
 * Revision 1.4  2003/12/25 08:26:20  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.2  1997/11/06 20:06:55  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 10:54:33  alexios
 * First registered revision. Adequate.
 *
 *
 */


#include <libtyphoon/typhoon.h>
#include <mailerplugins.h>


/* offline.news.c */

extern promptblock_t *msg;
extern promptblock_t *mailer_msg;
extern promptblock_t *graffiti_msg;

extern int entrykey;
extern int ovrkey;
extern int maxmsgs;
extern int maxsize;

extern int defwall;
extern int defansi;
extern int deflins;
extern char *wallfil;

extern char *progname;


/* setup.c */

struct prefs {
	int     flags;
	int     numlines;

	char    dummy[60];
};


struct prefs prefs;


#define OGF_YES    0x0001
#define OGF_ANSI   0x0002


void    readprefs (struct prefs *prefs);

void    writeprefs (struct prefs *prefs);

void    setup ();


/* download.c */

int     ogdownload ();


/* setup.c */

void    setup ();


/* upload.c */

int     ogupload ();




/* End of File */
