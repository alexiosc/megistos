/*****************************************************************************\
 **                                                                         **
 **  FILE:     visual.h                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, April 95                                                  **
 **  PURPOSE:  Header file for the advanced visual library.                 **
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
 * Revision 1.2  2001/04/16 21:56:28  alexios
 * Completed 0.99.2 API, dragged all source code to that level (not as easy as
 * it sounds).
 *
 * Revision 0.3  1997/11/06 20:03:39  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/08/30 12:54:20  alexios
 * Visual is now obsolete and dangerous. It should NOT be included
 * anywhere. If you still need to, define the symbol VISUAL before
 * #including visual.h
 *
 * Revision 0.1  1997/08/26 15:48:53  alexios
 * First registered revision. Adequate.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif


#ifdef VISUAL


#define FG_BLACK          0x00
#define FG_BLUE           0x01
#define FG_GREEN          0x02
#define FG_CYAN           0x03
#define FG_RED            0x04
#define FG_MAGENTA        0x05
#define FG_BROWN          0x06
#define FG_LIGHT_GREY     0x07
#define FG_DARK_GREY      0x08
#define FG_LIGHT_BLUE     0x09
#define FG_LIGHT_GREEN    0x0a
#define FG_LIGHT_CYAN     0x0b
#define FG_LIGHT_RED      0x0c
#define FG_LIGHT_MAGENTA  0x0d
#define FG_YELLOW         0x0e
#define FG_WHITE          0x0f

#define BG_BLACK          0x00
#define BG_BLUE           0x10
#define BG_GREEN          0x20
#define BG_CYAN           0x30
#define BG_RED            0x40
#define BG_MAGENTA        0x50
#define BG_BROWN          0x60
#define BG_LIGHT_GREY     0x70

#define BOLD              0x08
#define BLINK             0x80

#define NUMCOLUMNS        (wx2-wx1+1)
#define NUMROWS           (wy2-wy1+1)



struct thingy {
  int           x,y;
  int           w,h;
  int           cursorx,cursory,attr;
  long          flags;
  char          *data;
  int           thingyID;
  struct thingy *parent;
  struct thingy *next;
  struct thingy *prev;
  struct thingy *children;
  int           numchildren;
  struct thingy *focused;
  struct thingy *ontop;
  void          (*init)(void);
  void          (*draw)(void);
  void          (*done)(void);
  int           (*handleinput)(int key);
  void          (*focus)(void);
  void          (*defocus)(void);
};


struct prototype {
  int  datasize;
  void (*init)(void);
  void (*draw)(void);
  void (*done)(void);
  int  (*handleinput)(int key);
  void (*focus)(void);
  void (*defocus)(void);
};


extern int           autorefresh;
extern unsigned int  numrows,numcolumns;
extern unsigned int  cursorx;
extern unsigned int  cursory;
extern unsigned int  wx1;
extern unsigned int  wy1;
extern unsigned int  wx2;
extern unsigned int  wy2;
extern int           lastcolumn;
extern int           attr;
extern unsigned char *screen;


/* visual.c */

void initvisual();
void donevisual();


/* screen.c */

#define dumpline(n) dumpblock(wx1,wy1+n,wx2,wy1+n)

void initscreen();
void donescreen();
void dumpscreen();
void dumpblock(int x1, int y1, int x2, int y2);
void dumpchar(int ofs,int x, int y);
void cursorxy(int x,int y);
void setcolor(int a);
void clearscreen(unsigned char attr,unsigned char chr);
void cleartoeol(unsigned char a,unsigned char chr);
void setblock(int x1,int y1,int x2,int y2,unsigned char attr,unsigned char chr);
void maskblock(int x1,int y1,int x2,int y2,unsigned char attrand,unsigned char attror);


/* keyboard.c */

void initkeyboard();
void donekeyboard();


/* print.c */

void setrefresh(int onoff);
void setwindow(int x1,int y1,int x2,int y2);
void vscroll(int delta);
void vnewline();
void vputat(int x, int y, unsigned char attr, unsigned char chr);
void vputch(unsigned char chr);
void vprint();
void vprintat();


/* put.c */

void vputscreen(unsigned char *source);
void vputblock(unsigned char *source, int x, int y, int w, int h);
void vgetblock(unsigned char *target, int x, int y, int w, int h);
int vfputblock(const char *fname, int x, int y, int w, int h);


/* ansi.c */

void printansi(char *s);


/* thingy.c */

extern struct thingy          *rootthingy;
extern struct thingy          *curthingy;
extern int                    quit;

#define CT (curthingy)

void initthingies();
struct thingy *newthingy(struct thingy *under,struct prototype *prototype,
			 int x,int y,int w,int h,int flags);
void delthingy(struct thingy *thingy);
void runthingies();
void thingy_done();
int thingy_handleinput(int key);
void thingy_draw();
void thingy_setflag(int flag,int onoff);


/* thingy_root.c */

extern struct prototype TPR_ROOT;


/* thingy_window.c */

#define TFL_WINDOW_FRAME   0x0007
#define TFL_WINDOW_FRAMESS 0x0001
#define TFL_WINDOW_FRAMEDD 0x0002
#define TFL_WINDOW_FRAMEDS 0x0003
#define TFL_WINDOW_FRAMESD 0x0004
#define TFL_WINDOW_FRAMEB1 0x0005
#define TFL_WINDOW_FRAMEB2 0x0006
#define TFL_WINDOW_FRAMEB3 0x000f
#define TFL_WINDOW_FRAMESP 0x0008
#define TFL_WINDOW_SHADOW  0x0010

#define TFL_WINDOW (TFL_WINDOW_FRAMESS|TFL_WINDOW_SHADOW)

struct window_data {
  char *title;
  char *overlap;
  char frames[8];
  char frameattr[8];
  char titleattr;
  char insideattr;
  char shadowand,shadowor;
};

extern struct prototype TPR_WINDOW;

void window_init();
void window_done();
void window_settitle(char *s);
void window_setframes(char *s);
void window_setattrs(int frame, int title, int inside);
void window_setshadow(int shadowand, int shadowor);
void window_draw();

#endif /* VISUAL */
