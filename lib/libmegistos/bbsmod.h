/*****************************************************************************\
 **                                                                         **
 **  FILE:     bbsmod.h                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, June 94                                                   **
 **  PURPOSE:  Interface to module functions bbsmod.c                       **
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
 * Revision 1.1  2001/04/16 14:48:48  alexios
 * Initial revision
 *
 * Revision 0.4  1998/12/27 15:19:19  alexios
 * Declare the BBS user's UID and GID.
 *
 * Revision 0.3  1998/07/26 21:17:06  alexios
 * Added structure to declare modules and their individual
 * functions, plus functions to initialise said structure.
 * The setprogname() function is necessary for proper error
 * reporting.
 *
 * Revision 0.2  1997/11/06 20:03:39  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/26 15:48:53  alexios
 * First registered revision. Adequate.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif




#ifndef BBSMOD_H
#define BBSMOD_H


struct bbsmodule {
  char *progname;		/* The program name */
  char *version;		/* Full RCS compatible version */
  int  *(*login)(int,char**);	/* main() function for login processing */
  int  *(*run)(int,char**);	/* main module runtime */
  int  *(*logout)(int,char**);	/* logout handler */
  int  *(*cleanup)(int,char**);	/* cleanup handler */
};


extern struct bbsmodule module;
extern int bbs_uid, bbs_gid;


extern struct sysvar *sysvar;


#define INITALL     0xffffffff
#define INITSIGNALS 0x00000001
#define INITINPUT   0x00000002
#define INITSYSVARS 0x00000004
#define INITCLASSES 0x00000008
#define INITERRMSGS 0x00000010
#define INITATEXIT  0x00000020
#define INITLANGS   0x00000040
#define INITOUTPUT  0x00000080
#define INITUSER    0x00000100
#define INITGLOBCMD 0x00000200
#define INITTTYNUM  0x00000400
#define INITCHAT    0x00000800



void setmoduleinfo(struct bbsmodule *mod);

void setprogname(char *s);

void initmodule(long f);

void donemodule();

void initncurses();

void initsignals();

void donesignals();

void loadclasses();

void loadsysvars();

void loadlanguages();

void regpid (char *tty);


#endif /* BBSMOD_H */
