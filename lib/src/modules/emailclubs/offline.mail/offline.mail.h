/*****************************************************************************\
 **                                                                         **
 **  FILE:     offline.mail.h                                               **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1997, Version 0.1                                    **
 **  PURPOSE:  Mail plugin definitions and stuff.                           **
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
 * Revision 1.4  2003/12/25 08:26:20  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.5  1998/12/27 15:48:12  alexios
 * Added autoconf support.
 *
 * Revision 0.4  1998/08/11 10:13:15  alexios
 * Cosmetic changes. Made club sequence case-insensitive.
 *
 * Revision 0.3  1997/11/06 20:06:43  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/09/12 13:16:47  alexios
 * Added two extra fiels in the user's preferences for this
 * plugin. They record the CRC-32 checksums and lengths of the
 * last 128 messages the user has sent to the BBS. These are used
 * to avoid duplicate messages being uploaded.
 *
 * Revision 0.1  1997/08/28 10:55:29  alexios
 * First registered revision. Adequate.
 *
 *
 */


static const char rcsinfo[] =
    "$Id$";


#define WANT_DIRENT_H 1
#include <bbsinclude.h>

#include <megistos/typhoon.h>
#include <megistos/request.h>
#include <megistos/../../../clubs/ecdb.h>


/* offline.mail.c */

extern promptblock_t *mail_msg;
extern promptblock_t *mailer_msg;
extern promptblock_t *emailclubs_msg;

extern char *progname;

extern int sopkey;
extern int wrtkey;
extern int netkey;
extern int rrrkey;
extern int wrtchg;
extern int netchg;
extern int rrrchg;
extern int msglen;
extern char *defclub;

extern char *bbsid;
extern int ansihi;
extern int ansibye;
extern char *hifile;
extern char *byefile;
extern char *ctlname[6];

extern int updqsc;
extern int defatt;
extern int defreq;
extern int defhdr;
extern char *omceml;
extern char *allnam;
extern int usepass;
extern int fixeta;
extern char etaxlt;
extern int prgind;


/* setup.c */

#define NUMOLDMSGS 128

struct prefs {
	uint32  flags;
	uint32  oldcrc[NUMOLDMSGS];
	uint32  oldlen[NUMOLDMSGS];
};


struct prefs prefs;


#define OMF_ATTYES 0x0001
#define OMF_ATTASK 0x0002
#define OMF_ATT    0x0003

#define OMF_REQYES 0x0004
#define OMF_REQASK 0x0008
#define OMF_REQ    0x000c

#define OMF_HEADER 0x0010
#define OMF_QSCOK  0x0020



void    readprefs (struct prefs *prefs);

void    writeprefs (struct prefs *prefs);

void    setup ();


/* qsc.c */

struct emailuser emlu;

struct lastread *ustartqsc (char *uid);

struct lastread *startqsc ();

struct lastread *getqsc ();

struct lastread *nextqsc ();

struct lastread *prevqsc ();

struct lastread *findqsc (char *club);

struct lastread *goqsc (char *club);

struct lastread *resetqsc ();

int     isfirstqsc ();

int     islastqsc ();

void    doneqsc ();

void    usaveqsc (char *uid);

void    saveqsc ();

void    setqsc ();

void    updateqsc ();

int     delqsc (char *club);

void    addqsc (char *club, int lastmsg, int flags);

void    setlastread (char *club, int msg);



/* funcs.c */

extern struct clubheader clubhdr;

int     getclub (char *club, int pr, int err, int all, int email);

void    listclubs ();

unsigned long mkstol (unsigned long x);

unsigned long ltomks (unsigned long x);

char   *qwkdate (int date);

void    startind ();

void    progressind (int i);

void    endind ();

void    goclub (char *club);


/* clubhdr.c */

int     hdrselect (const struct dirent *d);

int     ncsalphasort (const struct dirent *const *,
		      const struct dirent *const *);

int     findclub (char *club);

int     loadclubhdr (char *club);

int     getdefaultax (useracc_t * uacc, char *club);

int     getclubax (useracc_t * uacc, char *club);


/* download.c */

#define QWKSIG "Produced by Qmail...Copyright (c) 1987 by Sparkware.  "\
               "All Rights Reserved"


struct qwkhdr {
	unsigned char status;
	unsigned char number[7];
	unsigned char date[8];
	unsigned char time[5];
	unsigned char whoto[25];
	unsigned char from[25];
	unsigned char subject[25];
	unsigned char password[12];
	unsigned char reference[8];
	unsigned char blocks[6];
	unsigned char active;
	unsigned char conference[2];
	unsigned char msgno[2];
	unsigned char net_tag;
};


struct qwkndx {
	unsigned long blkofs;
	unsigned char sig;
};


#define QWK_ALL "ALL"


#define STATUS_N   ' '
#define STATUS_NR  '-'
#define STATUS_P   '*'
#define STATUS_PR  '+'

#define MSG_ACT    225
#define MSG_INACT  226

#define EOL_GREEKQWK 12
#define EOL_QWK      227

#define EOLCHAR    (greek?EOL_GREEKQWK:EOL_QWK)


int     omdownload ();


/* database.c */

#define BSE_FOUND   1
#define BSE_NFOUND  0
#define BSE_OPEN   -1
#define BSE_LOCK   -2
#define BSE_STAT   -3
#define BSE_READ   -4
#define BSE_WRITE  -5
#define BSE_CAN    -6
#define BSE_END    -7
#define BSE_BEGIN  -8


#define BSD_EQ    1
#define BSD_LT    2
#define BSD_GT    4
/* #define BSD_LE    (BSD_LT|BSD_EQ)
   #define BSD_GE    (BSD_GT|BSD_EQ) */


struct message header;


int     getmsgheader (int msgno, struct message *msg);

int     writemsgheader (struct message *msg);

void    dbrm (struct message *msg);

int     dbgetindex (struct ecidx *idx);

int     dbchkemail (int msgno);

void    setclub (char *club);


/* dbnum.c */

int     findmsgnum (int *msgno, int targetnum, int direction);

int     npmsgnum (int *msgno, int targetnum, int dir);



/* dbto.c */

int     findmsgto (int *msgno, char *whom, int targetnum, int direction);

int     npmsgto (int *msgno, char *whom, int targetnum, int dir);


/* qwkout.c */

int     messagesdat ();

void    outmsg (int clubid, struct message *msg);


/* ../../../clubs/funcs.c */

char   *xlatehist (char *hist);

void    showheader (char *sig, struct message *msg);

int     writeecuser (char *uid, struct emailuser *user);

int     readecuser (char *uid, struct emailuser *user);

void    bbscrypt (char *buf, int size, int key);

int     getnumatt ();

char   *addhistory (char *h, char *s, int len);



/* request.c */

#include <megistos/req.h>

/* attachments.c */

void    doatt ();


/* upload.c */

int     omupload ();

void    skip ();

void    dobody (char *fname);


/* clubid.c */

void    loadclubids ();

void    doneclubids ();

int     getclubid (int id);


/* controlmsg.c */

void    outcontroltypes (FILE * fp);

int     handlecontrolmsg (struct qwkhdr *qwkhdr, struct message *msg);


/* reqman.c */

int     reqman ();


/* cksum.c */

void    cksumstg (char *buf, unsigned long *retcrc, int *retlen);


/* End of File */
