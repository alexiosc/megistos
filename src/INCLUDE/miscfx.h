/*****************************************************************************\
 **                                                                         **
 **  FILE:     miscfx.h                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, June 94                                                   **
 **  PURPOSE:  Interface to miscfx.h, implementing various useful functs.   **
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
 * Revision 1.1  2001/04/16 14:48:54  alexios
 * Initial revision
 *
 * Revision 0.8  1999/07/18 21:13:24  alexios
 * Supplied own version of usleep for borken (sic) bastard
 * operating systems that don't define it.
 *
 * Revision 0.7  1998/12/27 15:19:19  alexios
 * Moved functions that didn't really belong here to other
 * header files.
 *
 * Revision 0.6  1998/08/14 11:23:21  alexios
 * Added long-awaited function stripspace() to remove leading
 * and trailing white space from a string.
 *
 * Revision 0.5  1997/11/06 20:03:39  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.4  1997/11/03 00:29:40  alexios
 * Optimised stgxlate for speed; created a new translation
 * function, faststgxlate that is suitable for very fast
 * applications with complete translation tables.
 *
 * Revision 0.3  1997/09/12 12:45:25  alexios
 * Added lowerc() and upperc() functions.
 *
 * Revision 0.2  1997/08/30 12:54:20  alexios
 * Removed bladcommand(), replaced it by bbsdcommand() (different
 * syntax).
 *
 * Revision 0.1  1997/08/26 15:48:53  alexios
 * First registered revision. Adequate.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif




#ifndef MISCFX_H
#define MISCFX_H

#define WANT_TIME_H 1
#define WANT_UNISTD_H 1
#include <bbsinclude.h>



#define PHONETIC "\000\000\000\000\000\000\000\000"  /* 0-7              */ \
                 "\000\000\000\000\000\000\000\000"  /* 8-15             */ \
                 "\000\000\000\000\000\000\000\000"  /* 16-23            */ \
                 "\000\000\000\000\000\000\000\000"  /* 24-31            */ \
                 "\000\000\000\000\000\000\000\000"  /* 32-39    !"#$%&' */ \
                 "\000\000\000\000\000\000\000\000"  /* 40-47   ()*+,-./ */ \
                 "\060\061\062\063\064\065\066\067"  /* 48-55   01234567 */ \
                 "\070\071\000\000\000\000\000\000"  /* 56-63   89:;<=>? */ \
                 "\000\101\102\103\104\105\106\107"  /* 64-71   @ABCDEFG */ \
                 "\110\111\112\113\114\115\116\117"  /* 72-79   HIJKLMNO */ \
                 "\120\121\122\123\124\125\126\127"  /* 80-87   PQRSTUVW */ \
                 "\130\131\132\000\000\000\000\000"  /* 88-95   XYZ[\]^_ */ \
                 "\000ABCDEFG"                       /* 96-103  `abcdefg */ \
                 "HIJKLMNO"                          /* 104-111 hijklmno */ \
                 "PQRSTUVW"                          /* 112-119 pqrstuvw */ \
                 "XYZ\000\000\000\000\000"           /* 120-127 xyz{|}~  */ \
                 "ABGDEZIT"                          /* 128-135 ABGDEZHU */ \
                 "IKLMNXOP"                          /* 136-143 IKLMNJOP */ \
                 "RSTYFXCO"                          /* 144-151 RSTYFXCV */ \
                 "ABGDEZIT"                          /* 152-159 abgdezhu */ \
                 "IKLMNXOP"                          /* 160-167 iklmnjop */ \
                 "RSSTYFXC"                          /* 168-175 rsstyfxc */ \
                 "\000\000\000\000\000\000\000\000"  /* 176-183 graphics */ \
                 "\000\000\000\000\000\000\000\000"  /* 184-191 graphics */ \
                 "\000\000\000\000\000\000\000\000"  /* 192-199 graphics */ \
                 "\000\000\000\000\000\000\000\000"  /* 200-207 graphics */ \
                 "\000\000\000\000\000\000\000\000"  /* 208-215 graphics */ \
                 "\000\000\000\000\000\000\000\000"  /* 216-223 graphics */ \
                 "OAEIIIOY"                          /* 224-231 waehiioy */ \
                 "YO\000\000\000\000\000"            /* 232-239 yv       */ \
                 "\000\000\000\000\000\000\000\000"  /* 240-247 graphics */ \
                 "\000\000\000\000\000\000\000\000"  /* 248-255 graphics */


#define LATINIZE "\000\000\000\000\000\000\000\000"  /* 0-7              */ \
                 "\000\000\000\000\000\000\000\000"  /* 8-15             */ \
                 "\000\000\000\000\000\000\000\000"  /* 16-23            */ \
                 "\000\000\000\000\000\000\000\000"  /* 24-31            */ \
                 "\000\000\000\000\000\000\000\000"  /* 32-39    !"#$%&' */ \
                 "\000\000\000\000\000\000\000\000"  /* 40-47   ()*+,-./ */ \
                 "\000\000\000\000\000\000\000\000"  /* 48-55   01234567 */ \
                 "\000\000\000\000\000\000\000\000"  /* 56-63   89:;<=>? */ \
                 "\000\000\000\000\000\000\000\000"  /* 64-71   @ABCDEFG */ \
                 "\000\000\000\000\000\000\000\000"  /* 72-79   HIJKLMNO */ \
                 "\000\000\000\000\000\000\000\000"  /* 80-87   PQRSTUVW */ \
                 "\000\000\000\000\000\000\000\000"  /* 88-95   XYZ[\]^_ */ \
                 "\000\000\000\000\000\000\000\000"  /* 96-103  `abcdefg */ \
                 "\000\000\000\000\000\000\000\000"  /* 104-111 hijklmno */ \
                 "\000\000\000\000\000\000\000\000"  /* 112-119 pqrstuvw */ \
                 "\000\000\000\000\000\000\000\000"  /* 120-127 xyz{|}~  */ \
                 "ABGDEZHU"                          /* 128-135 ABGDEZHU */ \
                 "IKLMNJOP"                          /* 136-143 IKLMNJOP */ \
                 "RSTYFXCV"                          /* 144-151 RSTYFXCV */ \
                 "abgdezhu"                          /* 152-159 abgdezhu */ \
                 "iklmnjop"                          /* 160-167 iklmnjop */ \
                 "rsstyfxc"                          /* 168-175 rsstyfxc */ \
                 "\000\000\000\000\000\000\000\000"  /* 176-183 graphics */ \
                 "\000\000\000\000\000\000\000\000"  /* 184-191 graphics */ \
                 "\000\000\000\000\000\000\000\000"  /* 192-199 graphics */ \
                 "\000\000\000\000\000\000\000\000"  /* 200-207 graphics */ \
                 "\000\000\000\000\000\000\000\000"  /* 208-215 graphics */ \
                 "\000\000\000\000\000\000\000\000"  /* 216-223 graphics */ \
                 "vaehiioy"                          /* 224-231 waehiioy */ \
                 "yv\000\000\000\000\000\000"        /* 232-239 yv       */ \
                 "\000\000\000\000\000\000\000\000"  /* 240-247 graphics */ \
                 "\000\000\000\000\000\000\000\000"  /* 248-255 graphics */


#define rnd(num)      (int)((long)rand()%(num))
#define randomize()   srand((unsigned)time(NULL)+(unsigned)getpid())
#define min(a,b)      (((a)<(b))?(a):(b))
#define max(a,b)      (((a)>(b))?(a):(b))
#define phonetic(s)   stgxlate(s,PHONETIC)
#ifdef GREEK
#define latinize(s)   stgxlate(s,LATINIZE)
#define tolatin(c)    (LATINIZE[c]?LATINIZE[c]:(c))
#else
#define latinize(s)   (s)
#define tolatin(c)    (c)
#endif


void *alcmem (size_t size);

char *lowerc (char *s);

char *upperc (char *s);

char *stripspace(char *s);

int sameto(char *shorts, char *longs);

int sameas(char *stg1, char *stg2);

char *zeropad(char *s, int count);

inline char *stgxlate(char *s, char *table);

inline char *faststgxlate(char *s, char *table);

int bbsdcommand(char *command, char *tty, char *arg);

int dataentry(char *msg, int visual, int linear, char *data);

int search(char *string, char *keywords);

int runmodule(char *s);

int editor(char *fname,int limit);

void gopage(char *page);

int fcopy(char *source, char *target);


/* Redeclare usleep() for some systems */
#ifndef HAVE_USLEEP
#ifndef __P
#define __P
#endif
extern void usleep __P((unsigned long __usec));
#endif /* HAVE_USLEEP */



#endif /* MISCFX_H */
