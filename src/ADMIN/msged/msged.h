/*****************************************************************************\
 **                                                                         **
 **  FILE:     msged.h                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 94, Version 0.01 alpha                             **
 **  PURPOSE:  Defines and stuff                                            **
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
 * Revision 1.1  2001/04/16 14:48:40  alexios
 * Initial revision
 *
 * Revision 0.1  2000/12/08 15:12:19  alexios
 * Initial checkin.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif



/* #define DEBUG */

#ifdef DEBUG
#define debug errp
#else
#define debug(a,b)
#endif


#define max(a,b) (((a)>(b))?(a):(b))
#define min(a,b) (((a)<(b))?(a):(b))


#define CP_TITLE     1
#define CP_FRAMES    2
#define CP_FILETAB1  3
#define CP_FILETAB2  4
#define CP_OPTION    5
#define CP_OPTCHNG   6
#define CP_OPTNAV    7
#define CP_INFOFLD   8
#define CP_INFONUM   9
#define CP_INFOBAR  10

#define TITLE     "MSGED - Megistos BBS configuration tool 0.01"

#define errp(f,s) fprintf(stderr,f,s)


struct option {
  char          opt_file[64];
  char          opt_name[32];
  int           opt_level;
  int           opt_type;
  int           opt_language;
  long          opt_min;
  long          opt_max;
  char          opt_descr[80];
  char          *opt_help;
  char          *opt_contents;
  char          *opt_choices;
  struct option *opt_prev;
  struct option *opt_next;
};


extern int           configlevel;
extern int           curlanguage;
extern struct option **displist;
extern struct option *options;
extern struct option *curopt;
extern struct option *topopt;
extern int           numoptions;
extern int           dispoptions;
extern int           dispoptnum;
extern int           curoptnum;

extern WINDOW        *listwin;
extern WINDOW        *infowin;
extern int           optlistsize;


void initwindows();
void listopts();
void scrollup();
void scrolldown();
void updateinfo();

void insopt(struct option *opt);
void parsefile(char *filename);

void printopt(struct option *opt);
