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
 * $Id$
 *
 * $Log$
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


static const char rcsinfo[] =
    "$Id$";


#define VERSION "0.9"


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


/* xlate.c */

extern char kbdxlation[NUMXLATIONS][256];
extern char xlation[NUMXLATIONS][256];
extern int xlationtable;

#define xlate_in(s)    faststgxlate(s,kbdxlation[xlationtable]);
#define xlate_out(s)   faststgxlate(s,xlation[xlationtable]);

void    readxlation ();

/* Specifying source==target does not clobber source. */

void    unix2dos (char *source, char *target);


/* plugindef.c */


#define MAXPLUGINS 34
#define NAMELEN    32
#define DESCRLEN   64

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


/* usr.c */

struct usrtag {
	char    plugin[NAMELEN];
	int     len;
};


#define NUMOLDREP 4

struct usrqwk {
	int     compressor;
	int     decompressor;
	int     flags;
	char    packetname[11];
	unsigned long oldcrc[NUMOLDREP];
	int     oldlen[NUMOLDREP];

	char    dummy[64];
};

#define USQ_GREEKQWK 0x0001

#define OMF_TR0    0x0010
#define OMF_TR1    0x0020
#define OMF_TR2    0x0040
#define OMF_TR3    0x0080

#define OMF_SHIFT  4
#define OMF_TR     (OMF_TR0|OMF_TR1|OMF_TR2|OMF_TR3)

#define USERQWK "userqwk"

extern struct usrqwk userqwk;

int     loadprefs (char *plugin, void *buffer);

void    saveprefs (char *plugin, int len, void *buffer);


/* download.c */

void    download ();


/* upload.c */

void    upload ();

/* cksum.c */

int     cksum (char *file, unsigned long *retcrc, int *retlen);


/* End of File */
