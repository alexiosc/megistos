/*****************************************************************************\
 **                                                                         **
 **  FILE:     prompts.h                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, June 94                                                   **
 **  PURPOSE:  Interface to prompts.c                                       **
 **            files.                                                       **
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
 * Revision 1.1  2001/04/16 14:48:56  alexios
 * Initial revision
 *
 * Revision 0.5  1998/12/27 15:19:19  alexios
 * Added the message block magic number.
 *
 * Revision 0.4  1997/11/06 20:03:39  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.3  1997/11/05 10:52:05  alexios
 * Removed definitions of xlgetmsg() and xlgetmsglang(), since
 * emud now performs all translations on the fly.
 *
 * Revision 0.2  1997/09/01 10:25:46  alexios
 * Added macros to call getmsglang() and getmsg() and translate
 * the returned string according to the currently set
 * xlation_table.
 *
 * Revision 0.1  1997/08/26 15:48:53  alexios
 * First registered revision. Adequate.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif




#ifndef PROMPTS_H
#define PROMPTS_H


/* MBK magic */

#define MBK_MAGIC "MMBK"

typedef struct {
     char fname[64];
     FILE *handle;
     long indexsize;     
     long *index;
     int  language;
     int  langoffs[NUMLANGUAGES];
} promptblk;


extern char       *msgbuf;
extern promptblk  *curblk, *lastblk, *sysblk;
extern long       lastprompt;
extern char       postfix[80];
extern int        language;
extern int        numlangs;
extern char       languages[NUMLANGUAGES][64];


promptblk *opnmsg(char *name);

void setmbk(promptblk *blk);

void rstmbk();

char *getmsglang(int num, int language);

#define getmsg(num) getmsglang(num,curblk->language)

char *getpfixlang(int num,int value,int language);

#define getpfix(num,value) getpfixlang(num,value,curblk->language)

void clsmsg(promptblk *blk);

int sameas(char *s1, char *s2);

char *lastwd(char *s);

long lngopt(int num,long floor,long ceiling);

unsigned hexopt(int num,unsigned floor,unsigned ceiling);

int numopt(int num, int floor, int ceiling);

int ynopt(int num);

char chropt(int num);

char *stgopt(int msgnum);

int tokopt(int msgnum,char *toklst, ...);

void setlanguage (int l);


#endif /* PROMPTS_H */
