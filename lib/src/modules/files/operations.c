/*****************************************************************************\
 **                                                                         **
 **  FILE:     operations.c                                                 **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 1997, Version 0.1                               **
 **  PURPOSE:  File Libraries, libop operations                             **
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
 * Revision 1.1  2001/04/16 14:56:00  alexios
 * Initial revision
 *
 * Revision 0.4  2000/01/06 10:37:25  alexios
 * Added command entries for ADDTREE and DELTREE.
 *
 * Revision 0.3  1999/07/18 21:29:45  alexios
 * Added lots of new commands. Fixed security bug in main
 * loop.
 *
 * Revision 0.2  1998/12/27 15:40:03  alexios
 * Added autoconf support.
 *
 * Revision 0.1  1998/04/16 09:27:16  alexios
 * Initial version.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif



#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "files.h"
#include "mbk_files.h"


struct ops {
  char command[16];
  int  restricted;
  void (*action)(void);
};


static struct ops ops[]={
  {"CREATE",      1, op_create},
  {"LIBDEL",      1, op_delete},
  {"ADDTREE",     1, op_addtree},
  {"DELTREE",     1, op_deltree},

  {"EDIT",        1, op_edit},
  {"ACCESS",      1, op_access},
  {"CHARGES",     1, op_charges},
  {"LIMITS",      0, op_limits},
  {"OPTIONS",     1, op_options},
  {"LIBDESCRIBE", 0, op_describe},

  {"CD",         0, selectlib},
  {"DIR",        0, listapproved},
  {"FILES",      0, op_files},
  {"INFO",       0, fullinfo},
  {"LS",         0, op_ls},
  {"TREE",       0, libtree},
  {"DEL",        0, op_del},
  {"MOVE",       0, op_move},
  {"COPY",       0, op_copy},

  {"DESCR",      0, op_descr},
  {"LONG",       0, op_long},

  {"UNAPP",      0, op_listunapp},
  {"APPROVE",    0, op_approve},
  {"DISAPP",     0, op_disapprove},

  {"CACHE",      1, op_cache},
  {"",           0, NULL}
}; 

static int numops=0;


void
operations()
{
  int shownmenu=0;

  if(!numops){
    for(numops=0;ops[numops].command[0];numops++);
  }

  for(;;){
    if(!islibop(&library))return;
    if(!shownmenu){
      prompt(masterlibop?OPRSMENU:OPRMENU);
      shownmenu=1;
    }
    prompt(OPRSHORT);
    getinput(0);

    bgncnc();

    if(!margc || reprompt)continue;
    else if(margc==1 && sameas(margv[0],"?"))shownmenu=0;
    else if(margc==1 && isX(margv[0]))return;
    else {
      char *command;
      int i, found=0,execute=-1;
      
      command=cncword();
      for(i=0;i<numops;i++){
	if(sameto(command,ops[i].command)){
	  if((ops[i].restricted==0)||masterlibop){
	    found++;
	    execute=i;
	  }
	}
      }
      if(!found){
	prompt(OPRERR);
	endcnc();
      } else if(found==1)(ops[execute].action)();
      else {
	prompt(OPRRED,command);
	endcnc();
      }
    }
    if(lastresult==PAUSE_QUIT)resetvpos(0);
  }
}
