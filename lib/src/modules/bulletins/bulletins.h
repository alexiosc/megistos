/*****************************************************************************\
 **                                                                         **
 **  FILE:     bulletins.h                                                  **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 1996, Version 0.5                               **
 **  PURPOSE:  Bulletin reader header file.                                 **
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
 * Revision 1.2  2001/04/16 21:56:31  alexios
 * Completed 0.99.2 API, dragged all source code to that level (not as easy as
 * it sounds).
 *
 * Revision 0.4  1999/07/28 23:10:22  alexios
 * Added a command to download a bulletin.
 *
 * Revision 0.3  1998/07/24 10:14:42  alexios
 * Migrated to bbslib 0.6. Added support for conversion of
 * Major BBS-based bulletin database.
 *
 * Revision 0.2  1997/11/06 20:06:29  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 10:07:31  alexios
 * First registered revision, adequate.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif


/* bulletins.c */

extern promptblock_t *msg, *clubmsg;

extern int   entrykey;
extern int   sopkey;
extern int   flaxes;
extern int   indsel;
extern int   indspd;
extern int   audins;
extern int   auddel;
extern int   audedt;
extern int   audrd;
extern int   askdef;
extern int   ainsdef;
extern char *dnldesc;



#define FLA_NONE      -1
#define FLA_COOP       0
#define FLA_CLUBOP     1
#define FLA_PRIVILEGED 2


/* db.c */

void dbopen();

void dbclose();

int dbgetfirst();

int dbgetlast();

int dbins(struct bltidx *blt);

int dbexists(char *area, char *fname);

void dbget(struct bltidx *blt);

int dblistfind(char *club, int num);

int dbfound();

int dblistfirst();

int dblistnext();

int dblistlast();

int dblistprev();

int dbnumexists(int num);

int dbchkambiguity(char *fname);

int dbupdate(struct bltidx *blt);

int dbdelete();


/* clubs.c */

extern char club[16];

void selectclub();

void listclubs();


/* insert.c */

int getmsgheader(char *club, int msgno,struct message *msg);

void insertblt();

int extins(char *msgspec);


/* list.c */

void list(int full);

void listambiguous(char *fname);


/* read.c */

int getblt(int pr, struct bltidx *blt);

void bltread();

void bltdnl();

void showblt(struct bltidx *blt);


/* misc.c */

int getclub(char *club, int pr, int err, int def, char *defval);

int getaccess(char *club);

int getdescr(char *s, int pr);

void bltinfo(struct bltidx *blt);



/* substvars.c */

void initbltsubstvars();



/* clubhdr.c */

extern struct clubheader clubhdr;


int findclub(char *club);

int getclubid();

int loadclubhdr(char *club);

int saveclubhdr(struct clubheader *hdr);

int getdefaultax(useracc_t *uacc, char *club);

int getclubax(useracc_t *uacc, char *club);

void setclubax(useracc_t *uacc, char *club, int ax);


/* delete.c */

int checklocks(struct bltidx *blt);
void bltdel();


/* search.c */

void keysearch();


/* edit.c */

void bltedt();


/* autoins.c */

void autoins();


/* login.c */

int login(int argc, char **argv);


/* cleanup.c */

int cleanup(int argc, char **argv);
