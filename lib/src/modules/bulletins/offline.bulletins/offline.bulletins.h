/*****************************************************************************\
 **                                                                         **
 **  FILE:     offline.bulletins.h                                          **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 1997, Version 0.1                                  **
 **  PURPOSE:  Bulletins plugin definitions and stuff.                      **
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
 * Revision 1.5  2003/12/27 12:29:40  alexios
 * Adjusted #includes.
 *
 * Revision 1.4  2003/12/25 08:26:21  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.2  1997/11/06 20:06:59  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 10:53:22  alexios
 * First registered revision. Adequate.
 *
 *
 */


#include <libtyphoon/typhoon.h>
#include "../bltidx.h"


/* offline.news.c */

extern promptblock_t *msg;
extern promptblock_t *bulletins_msg;
extern promptblock_t *emailclubs_msg;

extern int defblt;
extern int defansi;
extern char *bltidfn;

extern int sopkey;

extern char *progname;


/* setup.c */

struct prefs {
	int     flags;

	char    dummy[60];
};


struct prefs prefs;


#define OBF_INDEX  0x01
#define OBF_ANSI   0x02
#define OBF_REQIDX 0x04


void    readprefs (struct prefs *prefs);

void    writeprefs (struct prefs *prefs);

void    setup ();


/* download.c */

int     obdownload ();


/* setup.c */

void    setup ();


/* upload.c */

int     obupload ();



/* db.c */

void    dbopen ();

void    dbclose ();

int     dbgetfirst ();

int     dbgetlast ();

int     dbins (struct bltidx *blt);

int     dbexists (char *area, char *fname);

void    dbget (struct bltidx *blt);

int     dblistfind (char *club, int num);

int     dbfound ();

int     dblistfirst ();

int     dblistnext ();

int     dblistlast ();

int     dblistprev ();

int     dbnumexists (int num);

int     dbchkambiguity (char *fname);

int     dbupdate (struct bltidx *blt);

int     dbdelete ();


/* clubhdr.c */

int     findclub (char *club);

int     loadclubhdr (char *club);

int     getdefaultax (useracc_t * uacc, char *club);

int     getclubax (useracc_t * uacc, char *club);


/* End of File */
