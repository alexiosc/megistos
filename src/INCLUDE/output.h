/*****************************************************************************\
 **                                                                         **
 **  FILE:     output.h                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, June 94                                                   **
 **  PURPOSE:  Provide an interface to output.c, autoconfig the kernel,     **
 **            solve differential equations, speed up Windows, and other    **
 **            legends.                                                     **
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
 * Revision 0.6  2000/01/06 11:37:41  alexios
 * Added declaration for send_out(), a wrapper for write(2) that
 * deals with overruns due to non-blocking I/O.
 *
 * Revision 0.5  1998/12/27 15:19:19  alexios
 * Added declarations that allow us to enable/disable auto-
 * matic translation.
 *
 * Revision 0.4  1998/07/26 21:17:06  alexios
 * Added function printlongfile() that outputs a very long file
 * checking if the user has interrupted the listing.
 *
 * Revision 0.3  1997/11/06 20:03:39  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/11/03 00:29:40  alexios
 * Removed hardwired translation tables.
 *
 * Revision 0.1  1997/08/26 15:48:53  alexios
 * First registered revision. Adequate.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif




#ifndef OUTPUT_H
#define OUTPUT_H


#define _ASCIIVARCHAR '@'
#define _VARCHAR      0x7f


extern char outbuf[8192];
extern int  ansienable;
extern int  waittoclear;
extern int  afterinput;
extern int  inhibitvars;
extern int  protectvars;


struct substvar {
  char *varname;
  char *(*varcalc)(void);
  void *next;
};


void initoutput();

void doneoutput();

void initemu ();

void setxlationtable(int i);

#define XLATION_OFF -1		/* Disable automatic translation */
#define XLATION_ON  -2		/* Re-enable automatic translation */



#ifndef OUTPUT_O

void prompt (int num,...);

void sprompt (char *stg, int num,...);

void print (char *buf,...);

void sprint (char *stg,char *buf,...);

#endif

#ifdef WANT_SEND_OUT

int send_out (int fd, char *s, int count);

#endif

int printfile (char *fname);

int printlongfile (char *fname);

int catfile (char *fname);

void setansiflag (int f);

void setwaittoclear (int f);

void initsubstvars ();

void addsubstvar ();


#endif /* OUTPUT_H */
