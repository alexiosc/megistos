/*****************************************************************************\
 **                                                                         **
 **  FILE:     vised.h                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, April 95, Version 0.5 alpha                               **
 **            B, September 95, Version 0.6 alpha                           **
 **  PURPOSE:  The Visual Editor header file                                **
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
 * Revision 1.3  2001/04/22 14:49:08  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.6  1999/08/13 17:10:05  alexios
 * Fixed things so that user inactivity timers are reset to handle
 * slightly borken (sic) telnet line timeouts. This is useless but
 * harmless, since emud handles these timeouts.
 *
 * Revision 0.5  1998/08/14 12:01:28  alexios
 * No changes.
 *
 * Revision 0.4  1997/11/06 20:03:31  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.3  1997/09/12 13:41:18  alexios
 * Removed function moveblock().
 *
 * Revision 0.2  1997/08/31 09:23:15  alexios
 * Removed calls to the visual library, replaced them with ncurses
 * calls.
 *
 * Revision 0.1  1997/08/28 11:26:56  alexios
 * First registered revision. Adequate.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif



#define mygetch() (inp_resetidle(),getch())



/* #define MAXLEN      (numcolumns-1) */
#define MAXLEN      999
#ifdef CTRL
#undef CTRL
#endif
#define CTRL(c)     ((c)-'@')
#define NOWRAP      (formatmode!=LEFT&&formatmode!=JUSTIFY)
#define BLOCK       (kbx<kkx||kby<kky)

#define NOFORMAT   0
#define LEFT       1
#define RIGHT      2
#define CENTRE     3
#define JUSTIFY    4


struct line {
  char        *text;
  struct line *next;
};


extern struct line  *first;
extern struct line  *last;
extern struct       line *top;
extern struct       line *current;
extern promptblock_t    *msg;
extern int          numlines, numbytes, maxsize;
extern char         filename[1024];
extern int          cx,cy,toprow,leftcol;
extern int          kbx,kby,kkx,kky;
extern int          fx,fy,fl;
extern int          metamode;
extern int          insertmode;
extern int          formatmode;
extern int          rmargin;

extern int          maxlen;
extern int          vscrinc;
extern int          hscrinc;
extern int          pageinc;
extern int          insert;
extern int          format;
extern char         *qtechrs;
extern int          qtemaxc;
extern int          cfgtxt;
extern int          cbgtxt;
extern int          cfgfnd;
extern int          cbgfnd;
extern int          cfgblk;
extern int          cbgblk;
extern int          cfgqte;
extern int          cbgqte;
extern char         *txtupld;
extern char         *stins[2];
extern char         *stformat[5];
extern char         *statust;
extern char         *statusb;
extern char         *statusm;
extern char         *statuso;
extern char         *statusk;


/* vised.c */

int getfg(int p);
int getbg(int p);
void init();
int loadfile(char *fname);
void savefile();
void run();
void done();


/* display.c */

void putcursor();
void bel(int error);
void showstatus();
void showtext(int num);
void noblock();


/* edit.c */

void inschar (int c, int update);
void splitline();
void newline();
void joinlines(int target);
void backspace();
void delline();
void deletechar();


/* utils.c */

struct line *getline(int line);
void insertline(struct line *afterline, char *s);
void deleteline(int num);
void centerline();
void gotoline(int line, int column);
void movecursor(int dy,int dx);
void movepage(int incr);
int  getlinenum(struct line *l);
void counttext();
char *getstg(char *def, int maxlen);
void printansi(char *s);
void attr(int cga_attr);
void cleartoeol();
void maskblock(int x1, int y1, int x2, int y2, unsigned char a);


/* format.c */

void formatline();
void formatpara();
void rightmargin();


/* blocks.c */

void delblock();
void copyblock(int move);


/* find.c */

void find();
void replace();
void dosearch();


/* exit.c */

int doquit();
void golined();
