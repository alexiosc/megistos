/*****************************************************************************\
 **                                                                         **
 **  FILE:     email.h                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1995, Version 0.5                                    **
 **  PURPOSE:  Header file for the email/clubs modules                      **
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
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.6  1999/07/18 21:21:38  alexios
 * Redeclared ncsalphasort() to have the right type of args.
 *
 * Revision 0.5  1998/12/27 15:33:03  alexios
 * Added autoconf support.
 *
 * Revision 0.4  1998/08/11 10:03:22  alexios
 * Club listings are now case insensitive. Added parameters to
 * set default accesses for new clubs.
 *
 * Revision 0.3  1998/07/24 10:17:37  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:05:26  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 10:21:30  alexios
 * First registered revision. Adequate.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif




#define WANT_DIRENT_H 1
#include <bbsinclude.h>
#include "ecdbase.h"

extern promptblock_t *msg;


/* email stuff */

extern int  entrykey;
extern int  sopkey;
extern int  wrtkey;
extern int  netkey;
extern int  rrrkey;
extern int  attkey;
extern int  dnlchg;
extern int  wrtchg;
extern int  netchg;
extern int  rrrchg;
extern int  attchg;
extern int  mkaudd;
extern int  mkaudu;
extern int  maxccs;
extern int  emllif;
extern int  msglen;
extern char *eattupl;
extern int  sigbmax;
extern int  siglmax;
extern int  sigckey;
extern int  sigchg;
extern int  afwkey;
extern int  dlkey;
extern int  maxdlm;
extern int  msskey;

/* club stuff */

extern int  clntrkey;
extern int  clsopkey;
extern int  tlckey;
extern int  bltkey;
extern int  clbwchg;
extern int  clbuchg;
extern int  clbdchg;
extern int  clblif;
extern int  cdnlaud;
extern int  cuplaud;
extern char *defclub;
extern int  modaxkey;
extern int  modchkey;
extern int  modhdkey;
extern int  tlckey;
extern int  bltkey;
extern char *tlcpag;
extern char *bltpag;
extern int  addnew;
extern int  drdaxkey;
extern int  ddlaxkey;
extern int  dwraxkey;
extern int  dulaxkey;


extern char defaultclub[32];



#define OPT_TOYOU     0
#define OPT_PTOYOU    1
#define OPT_FROMYOU   2
#define OPT_ALL       3



/* write.c */

char clubdir[256];

void emailwrite();

int getrecipient(int pr,char *rec);

int getclubrecipient(int pr, int err, int help, char *rec);

int getsubject(char *subject);

void uploadatt(char *attname, int num);

char *getattname(char *subject, int num);



/* read.c */

#define LASTMSG (1<<29)

int readmsg(struct message *msg);

void emailread();

int startreading(int mode, int startmsg);



/* receipt.c */

void sendreceipt(struct message *msg);



/* download.c */

void downloadatt(struct message *msg);


/* funcs.c */


int getrdmsgno(int *num,int msg,int help,int err,int def);

int askyesno(int *boolean,int msg,int err,int charge);

int confirmcancel();

void showheader(char *sig,struct message *msg);

int writeecuser(char *uid, struct emailuser *user);

int readecuser(char *uid, struct emailuser *user);

void appendsignature(char *into);

char *addhistory(char *h, char *s, int len);

void bbscrypt(char *buf,int size,int key);

int checklocks(struct message *msg);

int askmsgno();

void decompressmsg(struct message *msg);

void compressmsg(struct message *msg);



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


int getmsgheader(int msgno,struct message *msg);

int writemsgheader(struct message *msg);

void dbrm(struct message *msg);

int dbgetindex(struct ecidx *idx);

int dbchkemail(int msgno);

void setclub(char *club);


/* dbnum.c */

int findmsgnum(int *msgno, int targetnum, int direction);

int npmsgnum(int *msgno, int targetnum, int dir);



/* dbfrom.c */

int findmsgfrom(int *msgno, char *who, int targetnum, int direction);

int npmsgfrom(int *msgno, char *who, int targetnum, int dir);



/* dbto.c */

int findmsgto(int *msgno, char *whom, int targetnum, int direction);

int npmsgto(int *msgno, char *whom, int targetnum, int dir);



/* dbsubj.c */

int findmsgsubj(int *msgno, char *subject, int targetnum, int direction);

int npmsgsubj(int *msgno, char *subject, int targetnum, int dir);



/* preferences.c */

void preferences();



/* misc.c */

void stopautofw(struct message *msg);

void erasemsg(int forward, struct message *msg);

void copymsg(struct message *msg);

void forwardmsg(struct message *msg);

int backtrack(struct message *msg);

void deleteuser(struct message *msg);

void rmlocks();


/* reply.c */

void reply(struct message *msg, int forceemail);

int quotemessage(struct message *msg, char *fname);


/* modify.c */

void modifymail();

void modifyclubmsg(struct message *msg);

void clubopmodify(struct message *msg);


/* distlist.c */

void initlist();

void confdistlist();

int opendistribution(char *dist);

char *readdistribution();

void closedistribution();


/* clubhdr.c */


extern struct clubheader clubhdr;


int hdrselect(const struct dirent *d);

int ncsalphasort(const struct dirent **,
		 const struct dirent **);

int findclub(char *club);

int getclubid();

int loadclubhdr(char *club);

int saveclubhdr(struct clubheader *hdr);

int getdefaultax(useracc_t *uacc, char *club);

int getclubax(useracc_t *uacc, char *club);

void setclubax(useracc_t *uacc, char *club, int ax);


/* substvars.c */

void initecsubstvars();


/* mailcleanup.c */

int handler_cleanup(int argc, char **argv);
