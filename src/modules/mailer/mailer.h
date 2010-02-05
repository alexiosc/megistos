/*****************************************************************************\
 **                                                                         **
 **  FILE:     mailer.h                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1997, Version 0.1                                    **
 **  PURPOSE:  Off line mailer, definitions                                 **
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
 * $Id: mailer.h,v 2.0 2004/09/13 19:44:52 alexios Exp $
 *
 * $Log: mailer.h,v $
 * Revision 2.0  2004/09/13 19:44:52  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2003/12/27 12:40:38  alexios
 * Removed rcsinfo. Moved various declarations to mailerplugins.h.
 *
 * Revision 1.4  2003/12/24 20:12:10  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.5  1998/08/14 11:31:09  alexios
 * Added unix2dos() function to translate files to the DOS
 * newline format (CR-NL instead of just NL).
 *
 * Revision 0.4  1998/08/11 10:11:15  alexios
 * Minor cosmetic changes. Added prototypes for translation
 * calls.
 *
 * Revision 0.3  1997/12/02 20:45:35  alexios
 * Switched to using the archiver file instead of locally
 * defined compression/decompression programs.
 *
 * Revision 0.2  1997/11/06 20:06:32  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 10:42:54  alexios
 * First registered revision. Adequate.
 *
 *
 */


#define MAILER_VERSION "0.9"


/* mailer.c */

extern promptblock_t *archivers, *mailer_msg;

extern char *bbsid;
extern char *ctlname[6];
extern int chgdnl;
extern int defgrk;
extern int stpncnf;
extern int qwkuc;
extern int auddnl;
extern int audupl;
extern int uplkey;


/* Mailer plugins */

#ifdef __MAILERPLUGIN__
#error This should not be defined here
#endif
#define __MAILERPLUGIN__
#include "mailerplugins.h"


/* plugindef.c */

struct plugin {
	char    name[NAMELEN];
	char    descr[NUMLANGUAGES][DESCRLEN];
	int     flags;
};


extern struct plugin *plugins;
extern int numplugins;


#define PLF_SETUP    0x01
#define PLF_UPLOAD   0x02
#define PLF_DOWNLOAD 0x04
#define PLF_REQMAN   0x08



#define PLUGINDEFFILE MAILERDIR"/plugins"


void    parseplugindef ();


/* setup.c */

void    defaultvals ();

void    setup ();


/* download.c */

void    download ();


/* upload.c */

void    upload ();

/* cksum.c */

int     cksum (char *file, unsigned long *retcrc, int *retlen);



/* End of File */
