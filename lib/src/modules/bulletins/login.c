/*****************************************************************************\
 **                                                                         **
 **  FILE:     login.c                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1997, Version 0.5                                    **
 **  PURPOSE:  Notify user of new bulletins since their last login          **
 **  NOTES:                                                                 **
 **                                                                         **
\*****************************************************************************/


/*
 * $Id$
 *
 * $Log$
 * Revision 1.1  2001/04/16 14:54:55  alexios
 * Initial revision
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
#endif


#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_DIRENT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "mbk_bulletins.h"
#include "bltidx.h"
#include "bulletins.h"
#include "typhoon.h"


void
login()
{
  return;
  /*
  char **areas=NULL;
  struct bltidx blt;
  int cofd=cofdate(thisuseracc.datelast);
  int newblts=0;
  int numareas=0;

  d_keyfind(DATE,&thisuseracc.datelast);
  if(db_status!=S_OKAY)d_keynext(DATE);

  while(db_status==S_OKAY){
    d_recread(&blt);

    if(cofdate(blt.date)>=cofd){
      newblts++;
      if(numareas){
	char **newareas=alcmem(numareas*sizeof(char*))
      }
    }


    strcpy(a,strdate(blt.date));
    strcpy(b,strdate(thisuseracc.datelast));
    print("%3d. %-10s, %-40s, %s %s\n",blt.num,blt.area,blt.descr,a,b);
    d_keynext(DATE);
  }*/
}

