/*****************************************************************************\
 **                                                                         **
 **  FILE:     clubs.h                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1995, Version 0.5                                    **
 **  PURPOSE:  Header file for the clubs module                             **
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
 * Revision 0.5  1999/07/18 21:21:38  alexios
 * Added support for the network manager menu.
 *
 * Revision 0.4  1998/07/24 10:17:37  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.3  1997/11/06 20:05:26  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/09/12 13:04:17  alexios
 * Added functionality to look for messages in ALL clubs, not
 * just the ones configured for Quickscan (of course, 'all'
 * being defined as 'all clubs the user has access to'). This is
 * useful while looking for new messages to the user, where we
 * don't care whether a club is in the user's Quickscan or not.
 *
 * Revision 0.1  1997/08/28 10:21:30  alexios
 * First registered revision. Adequate.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif




#define KEYSCAN  "\000\055\055\055\055\055\055\055"  /* 0-7              */ \
                 "\055\055\055\055\055\055\055\055"  /* 8-15             */ \
                 "\055\055\055\055\055\055\055\055"  /* 16-23            */ \
                 "\055\055\055\055\055\055\055\055"  /* 24-31            */ \
                 "\055\055\055\055\055\055\055\055"  /* 32-39    !"#$%&' */ \
                 "\055\055\055\055\055\055\055\055"  /* 40-47   ()*+,-./ */ \
                 "\060\061\062\063\064\065\066\067"  /* 48-55   01234567 */ \
                 "\070\071\055\055\055\055\055\055"  /* 56-63   89:;<=>? */ \
                 "\055\101\102\103\104\105\106\107"  /* 64-71   @ABCDEFG */ \
                 "\110\111\112\113\114\115\116\117"  /* 72-79   HIJKLMNO */ \
                 "\120\121\122\123\124\125\126\127"  /* 80-87   PQRSTUVW */ \
                 "\130\131\132\055\055\055\055\055"  /* 88-95   XYZ[\]^_ */ \
                 "\055ABCDEFG"                       /* 96-103  `abcdefg */ \
                 "HIJKLMNO"                          /* 104-111 hijklmno */ \
                 "PQRSTUVW"                          /* 112-119 pqrstuvw */ \
                 "XYZ\055\055\055\055\055"           /* 120-127 xyz{|}~  */ \
                 "ABGDEZIT"                          /* 128-135 ABGDEZHU */ \
                 "IKLMNXOP"                          /* 136-143 IKLMNJOP */ \
                 "RSTYFXCO"                          /* 144-151 RSTYFXCV */ \
                 "ABGDEZIT"                          /* 152-159 abgdezhu */ \
                 "IKLMNXOP"                          /* 160-167 iklmnjop */ \
                 "RSSTYFXC"                          /* 168-175 rsstyfxc */ \
                 "\055\055\055\055\055\055\055\055"  /* 176-183 graphics */ \
                 "\055\055\055\055\055\055\055\055"  /* 184-191 graphics */ \
                 "\055\055\055\055\055\055\055\055"  /* 192-199 graphics */ \
                 "\055\055\055\055\055\055\055\055"  /* 200-207 graphics */ \
                 "\055\055\055\055\055\055\055\055"  /* 208-215 graphics */ \
                 "\055\055\055\055\055\055\055\055"  /* 216-223 graphics */ \
                 "OAEIIIOY"                          /* 224-231 waehiioy */ \
                 "YO\055\055\055\055\055"            /* 232-239 yv       */ \
                 "\055\055\055\055\055\055\055\055"  /* 240-247 graphics */ \
                 "\055\055\055\055\055\055\055\055"  /* 248-255 graphics */



/* clubs.c */

int defaultrate;


/* clubwrite.c */

void clubwrite();


/* clubread.c */

extern int numkeys;
extern char *keywords[128];
extern char *phonetic[128];
extern int quickscan;
extern int filescan;
extern int keyscan;
extern int inemail;
extern int allclubs;
extern int savecounter;
extern int lastkey;


void showkeywords();

void clubread();

void scanmessages();

void keywordscan();

void fileapp();



/* clubscan.c */

void scanupdatemsg(struct message *msg,int read);

int scan4msg(int *msgno, int *sequencebroken, int targetnum, int dir, int mode);

/*int scan4files(int *msgno, int *sequencebroken, int targetnum, int dir, int mode);*/

char clubreadmenu(struct message *msg, char defopt);

char clubheadermenu(struct message *msg, char defopt);

int startscanning(int startmsg, int bdir);

void scanupdatemsg(struct message *msg,int read);



/* clublist.c */

void listmessages();


/* qsc.c */

struct lastread *uqsc;

struct lastread *ustartqsc(char *uid);

struct lastread *startqsc();

struct lastread *getqsc();

struct lastread *nextqsc();

struct lastread *prevqsc();

struct lastread *findqsc(char *club);

struct lastread *goqsc(char *club);

struct lastread *resetqsc();

void initialise();

int isfirstqsc();

int islastqsc();

void all(int add);

void addqsc(char *club, int lastmsg, int flags);

int delqsc(char *club);

int killqsc(char *club);

int getlastread(char *club);

void setlastread(char *club, int msg);

void doneqsc();

void usaveqsc(char *uid);

void saveqsc();

int quickscanmenu(struct message *msg);

void configurequickscan(int create);

void doquickscan();

int qgoclub();



/* operations.c */

#define QSC_ADD 1
#define QSC_DEL 0

void globalqsc(int add, char *club);

void listclubs();

void longlistclubs();

void operations();


/* networking.c */

#ifdef HAVE_METABBS
#ifdef __CLUBS_C
void networking();
#endif
#endif


/* clubfx.c */

extern char inclublock[256];

extern int threadmessage;

extern char threadclub[16];

void enterdefaultclub();

void enterclub(char *club);

void showbanner();

int checkinclub(char *club);

int getclub(char *club, int pr, int err, int all);

int thread(struct message *msg, char defopt);


/* clubop.c */

char clubopmenu(struct message *msg);


/* msgcnv.c */

int msgcnv_main(int argc, char **argv);

