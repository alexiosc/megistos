/*****************************************************************************\
 **                                                                         **
 **  FILE:     checksup.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1995, Version 1.0                                    **
 **  PURPOSE:  Checks a new account for validity.                           **
 **  NOTES:    Part of the supauth script.                                  **
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
 * Revision 1.1  2001/04/16 15:02:50  alexios
 * Initial revision
 *
 * Revision 1.4  1998/12/27 16:33:17  alexios
 * Added autoconf support.
 *
 * Revision 1.3  1998/07/24 10:30:06  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 1.2  1997/11/06 20:17:43  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 1.1  1997/09/12 13:38:30  alexios
 * Added a check for the phone number's length.
 *
 * Revision 1.0  1997/08/28 11:24:50  alexios
 * Initial revision
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
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "mbk_signup.h"


promptblk *msg;
useracc uacc;


int
checkchars(char *s, char *also, int num)
{
  char *cp;
  int i;
  for(cp=s;*cp;cp++){
    if(isalpha(*cp))continue;
    if(*cp==32)continue;
    if(strchr(also,*cp))continue;
    if(num && isdigit(*cp))continue;
#ifdef GREEK
    i=-*cp;
    if((i>=81 && i<=128)||(i>=23 && i<=32))continue;
#endif
    return 0;
  }
  return 1;
}


int
checknum(char *s, char *also)
{
  char *cp;
  for(cp=s;*cp;cp++){
    if(strchr(also,*cp))continue;
    if(isdigit(*cp))continue;
    return 0;
  }
  return 1;
}


int countwords(char *s)
{
  char *cp;
  int word=1, count=0;
  for(cp=s;*cp;cp++){
    if(word && *cp!=32){
      count++;
      word=0;
    }
    if(*cp==32)word=1;
  }
  return count;
}


void
checkname()
{
  int show=0;

  if(!checkchars(uacc.username,".-",0)){
    prompt(CKSNAME);
    prompt(CKSNAME1);
    show=1;
  }
  if(countwords(uacc.username)>2){
    if(!show)prompt(CKSNAME);
    prompt(CKSNAME2);
    show=1;
  }
  if(show)prompt(CKSDIV);
}



void
checkaddress()
{
  int show=0;
  int i,j,k;

  if(!checkchars(uacc.address1,".-,",1)||(!checkchars(uacc.address2,".-,",1))){
    prompt(CKSADDR);
    prompt(CKSADDR1);
    show=1;
  }
  for(i='0',j=k=0;i<='9';i++){
    j+=(strchr(uacc.address1,i)!=NULL);
    k+=(strchr(uacc.address2,i)!=NULL);
  }
  if(j==0||k==0){
    if(!show)prompt(CKSADDR);
    prompt(CKSADDR2);
    show=1;
  }
  if(show)prompt(CKSDIV);
}



void
checkphone()
{
  int show=0;

  if(!checknum(uacc.phone,".-, ")){
    prompt(CKSPHONE);
    prompt(CKSPHONE1);
    show=1;
  }
  if(strlen(uacc.phone)!=7){
    if(!show)prompt(CKSPHONE);
    prompt(CKSPHONE2);
    show=1;
  }
  if(show)prompt(CKSDIV);
}



void
check(char *userid)
{
  loaduseraccount(userid,&uacc);
  prompt(CKSHEADER);
  
  checkname();
  checkaddress();
  checkphone();

  prompt(CKSFOOTER);
}


void
main(int argc, char **argv)
{
  int init;

  setprogname(argv[0]);
  if(argc!=2){
    printf("syntax: checksup userid\n\n");
    exit(1);
  }

  if(!userexists(argv[1]))exit(1);

  if(getenv("USERID")&&strcmp("",getenv("USERID")))init=INITALL;
  else init=INITTTYNUM|INITOUTPUT|INITSYSVARS|INITERRMSGS|INITCLASSES;
  initmodule(init);

  msg=opnmsg("signup");

  check(argv[1]);
  donemodule();
}
