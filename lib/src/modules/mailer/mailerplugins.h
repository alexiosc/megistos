/*****************************************************************************\
 **                                                                         **
 **  FILE:     mailerplugins.h                                              **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1997, Version 0.1                                    **
 **  PURPOSE:  Request definitions, to be included by other plugins.        **
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
 * Revision 1.5  2003/12/27 12:40:55  alexios
 * Moved various declarations from mailer.h to this file.
 *
 * Revision 1.4  2003/12/25 08:26:20  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.2  1997/11/06 20:06:43  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 10:55:29  alexios
 * First registered revision. Adequate.
 *
 *
 */


#ifndef __MAILERPLUGINS_H
#define __MAILERPLUGINS_H


#ifdef __MAILERPLUGIN__


#include "request.h"


/* plugindef.c (partial) */


#define MAXPLUGINS 34
#define NAMELEN    32
#define DESCRLEN   64


/* request.c */


#define RQF_POSTPONE 0x01
#define RQF_ATT      0x02
#define RQF_INVIS    0x04
#define RQF_CTLMSG   0x08
#define RQF_BULLETIN 0x10

#define RQP_POSTPONE  1
#define RQP_ATT       2
#define RQP_ATTREQ    3
#define RQP_OTHER     4
#define RQP_CTLMSG   99

void    openreqdb ();

int     mkrequest (char *area, char *dosfname, char *fname,
		   int msgno, int priority, int flags);

int     getfirstreq (struct reqidx *idx);

int     getnextreq (struct reqidx *idx);

int     rmrequest (struct reqidx *idx);

int     updrequest (struct reqidx *idx);


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


/* xlate.c */

extern char kbdxlation[NUMXLATIONS][256];
extern char xlation[NUMXLATIONS][256];
extern int xlationtable;

#define xlate_in(s)    faststgxlate(s,kbdxlation[xlationtable]);
#define xlate_out(s)   faststgxlate(s,xlation[xlationtable]);

void    readxlation ();

/* Specifying source==target does not clobber source. */

void    unix2dos (char *source, char *target);



#else
#  error mailerplugins.h file should only be included by mailer plugins.
#endif /* __MAILERPLUGIN__ */


#endif /* __MAILERPLUGINS_H */


/* End of File */
