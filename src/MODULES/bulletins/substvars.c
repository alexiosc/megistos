/*****************************************************************************\
 **                                                                         **
 **  FILE:     insert.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 1996, Version 0.5                               **
 **  PURPOSE:  Insert bulletins into the database.                          **
 **  NOTES:                                                                 **
 **                                                                         **
\*****************************************************************************/


/*
 * $Id$
 *
 * $Log$
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.4  1999/07/18 21:19:18  alexios
 * Fixed sneaky little substitution variable bug.
 *
 * Revision 0.3  1998/12/27 15:27:54  alexios
 * Added autoconf support.
 *
 * Revision 0.2  1998/07/24 10:14:42  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.1  1997/08/28 10:07:31  alexios
 * First registered revision, adequate.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
const char *__RCS=RCS_VER;
#endif



#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "mbk_bulletins.h"
#include "bltidx.h"
#include "bulletins.h"


static char *
sv_club()
{
  return club;
}


void
initbltsubstvars()
{
  struct substvar table []={
    {"@CLUB@",sv_club,NULL},
    {"",NULL,NULL}
  };
  
  int i=0;
  
  while(table[i].varname[0]){
    out_addsubstvar(table[i].varname,table[i].varcalc);
    i++;
  }
}
