/*****************************************************************************\
 **                                                                         **
 **  FILE:     misc.c                                                       **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 1996, Version 0.5                               **
 **  PURPOSE:  Miscellaneous functions                                      **
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
#include <bbsinclude.h>

#include "bbs.h"
#include "mbk_bulletins.h"
#include "bltidx.h"
#include "bulletins.h"


int
getclub(char *club, int pr, int err, int def, char *defval)
{
  char *i;
  char c;

  for(;;){
    lastresult=0;
    if((c=morcnc())!=0){
      if(sameas(nxtcmd,"X"))return 0;
      if(sameas(nxtcmd,"?")){
	listclubs();
	endcnc();
	continue;
      }
      i=cncword();
    } else {
      if(pr)prompt(pr);
      if(def)prompt(def,defval);
      getinput(0);
      bgncnc();
      i=cncword();
      if(!margc || (margc==1 && sameas(margv[0],"."))){
	if(defval&&defval[0])strcpy(i,defval);
	else {
	  endcnc();
	  continue;
	}
	break;
      } else if(isX(margv[0]))return 0;
      if(sameas(margv[0],"?")){
	listclubs();
	endcnc();
	continue;
      }
    }

    if(*i=='/')i++;

    if(!i[0] || sameas(i,".")){
      if(defval&&defval[0])strcpy(i,defval);
      else {
	endcnc();
	continue;
      }
      break;
    } else if(!findclub(i)){
      if(err)prompt(err,i);
      endcnc();
      continue;
    } else break;
  }

  strcpy(club,i);
  return 1;
}


int
getaccess(char *club)
{
  int ax;
  if(haskey(&thisuseracc,sopkey))return FLA_PRIVILEGED;
  if(!club[0])return FLA_NONE;

  ax=getclubax(&thisuseracc,club);
  if(ax<CAX_COOP)return FLA_NONE;
  else if(ax==CAX_COOP)return FLA_COOP;
  else if(ax>CAX_COOP)return FLA_CLUBOP;
  return FLA_NONE;
}


int
getdescr(char *s, int pr)
{
  char *i;

  endcnc();
  for(;;){
    if(morcnc()){
      i=nxtcmd;
      rstrin();
    } else {
      if(pr)prompt(pr,s);
      getinput(DESCR_LEN-1);
      bgncnc();
      if(!margc)continue;
      i=input;
      rstrin();
    }

    if(!i[0])continue;
    else if(isX(i))return 0;
    else {
      strcpy(s,i);
      while(s[strlen(s)-1]==32)s[strlen(s)-1]=0;
      return 1;
    }
  }
}


void
bltinfo(struct bltidx *blt)
{
  prompt(BLTINFO,
	 blt->num,
	 blt->fname,
	 blt->descr,
	 blt->area,
	 blt->author,
	 blt->timesread,getpfix(TIMESSNG,blt->timesread));
}
