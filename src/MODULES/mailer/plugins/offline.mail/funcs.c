/*****************************************************************************\
 **                                                                         **
 **  FILE:     funcs.c                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1997, Version 0.1                                    **
 **  PURPOSE:  Various functions                                            **
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
 * Revision 1.1  2001/04/16 14:57:44  alexios
 * Initial revision
 *
 * Revision 0.4  1998/12/27 15:48:12  alexios
 * Added autoconf support.
 *
 * Revision 0.3  1998/08/11 10:13:15  alexios
 * Moved hdrselect() to this file.
 *
 * Revision 0.2  1997/11/06 20:06:43  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 10:55:29  alexios
 * First registered revision. Adequate.
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
#define WANT_DIRENT_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "offline.mail.h"
#include "../../mailer.h"
#include "mbk_offline.mail.h"

#define __MAILER_UNAMBIGUOUS__
#include "mbk_mailer.h"

#define __EMAILCLUBS_UNAMBIGUOUS__
#include "mbk_emailclubs.h"


static int oldverticalformat;
static int ind=0;

struct clubheader clubhdr;


int
getclub(char *club, int pr, int err, int all, int email)
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
      prompt(pr);
      getinput(0);
      bgncnc();
      i=cncword();
      if(!margc){
	endcnc();
	continue;
      } else if(isX(margv[0]))return 0;
      if(sameas(margv[0],"?")){
	listclubs();
	endcnc();
	continue;
      }
    }

    if(*i=='/')i++;

    if(sameas(i,"ALL")&all){
      strcpy(club,"ALL");
      return 1;
    } else if(sameas(i,omceml)&&email){
      strcpy(club,omceml);
      return 1;
    }
    if(!findclub(i)){
      prompt(err);
      endcnc();
      continue;
    } else break;
    return 1;
  }

  strcpy(club,i);
  return 1;
}


void
listclubs()
{
  struct dirent **clubs;
  int n,i;

  setmbk(emailclubs_msg);
  n=scandir(CLUBHDRDIR,&clubs,hdrselect,alphasort);
  prompt(EMAILCLUBS_LCHDR);
  for(i=0;i<n;free(clubs[i]),i++){
    char *cp=&clubs[i]->d_name[1];
    if(!loadclubhdr(cp))continue;
    if(lastresult==PAUSE_QUIT)break;
    if(getclubax(&thisuseracc,cp)==CAX_ZERO)continue;
    prompt(EMAILCLUBS_LCTAB,clubhdr.club,clubhdr.clubop,clubhdr.descr);
  }
  free(clubs);
  if(lastresult==PAUSE_QUIT){
    setmbk(mail_msg);
    return;
  }
  prompt(EMAILCLUBS_LCFTR);
  setmbk(mail_msg);
}


unsigned long
mkstol(unsigned long x)
{
  return(((x&~0xff000000)|0x00800000)>>(24-((x>>24)&0x7f)));
}


unsigned long
ltomks(unsigned long x)
{
  int exp;

  exp=0;
  if (!x) exp=0x80+24;
  else if (x>=0x01000000) {
    while (x&0xff000000) {
      x>>=1;
      exp--;
    }
  }
  else {
    while (!(x&0x00800000)) {
      x<<=1;
      exp++;
    }
  }
  return((x&~0x00800000)|((24L-exp+0x80)<<24));
}


char *qwkdate(int date)
{
  static char buff[32]={0};
  struct tm dt={0};

  dt.tm_mday=tdday(date);
  dt.tm_mon=tdmonth(date);
  dt.tm_year=tdyear(date);
  strftime(buff,32,"%m-%d-%y",&dt);
  return buff;
}


void
startind()
{
  if(!prgind)return;
  oldverticalformat=verticalformat;
  setverticalformat(0);
  prompt(OMDLIND0);
  ind=0;
}


void
progressind(int i)
{
  if(!prgind)return;
  prompt(OMDLIND1+ind,i);
  ind=(ind+1)%8;
}


void
endind()
{
  if(!prgind)return;
  setverticalformat(oldverticalformat);
  prompt(OMDLINDE);
}


static char inclublock[256];


void
goclub(char *club)
{
  rmlock(inclublock);
  if(club){
    sprintf(inclublock,INCLUBLOCK,thisuseronl.channel,club);
    placelock(inclublock,"reading");
  }
  setclub(club);
}


void
abort()
{
  blocking();
  thisuseronl.flags&=~(OLF_BUSY|OLF_NOTIMEOUT);
  setmbk(mailer_msg);
  prompt(MAILER_ABORT);
  exit(2);
}
