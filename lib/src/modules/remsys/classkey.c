/*****************************************************************************\
 **                                                                         **
 **  FILE:     classkey.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 94                                                   **
 **  PURPOSE:  Class and key oriented functions for the remote sysop menu   **
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
 * Revision 1.1  2001/04/16 14:58:05  alexios
 * Initial revision
 *
 * Revision 0.5  1998/12/27 16:07:28  alexios
 * Added autoconf support.
 *
 * Revision 0.4  1998/07/24 10:23:31  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.3  1997/11/06 20:05:18  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/11/05 11:10:55  alexios
 * Changed calls to audit() to take into account the new
 * auditing scheme.
 *
 * Revision 0.1  1997/08/28 11:04:28  alexios
 * First registered revision. Adequate.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif



#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_UNISTD_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "remsys.h"

#include "mbk_remsys.h"


void
listclasses()
{
  int i;

  prompt(CLSLSTHDR,NULL);
  for(i=0;i<numuserclasses;i++)prompt(CLSLSTTAB,userclasses[i].name);
  prompt(CLSLSTEND,NULL);
}



int
getclassname(class,msg,existing,err,def,defval)
char *class,*defval;
int  msg,existing,err,def;
{
  char newclass[10];
  int i, ok=0;
  while(!ok){
    memset(newclass,0,10);
    if(morcnc())strncpy(newclass,cncword(),10);
    else {
      prompt(msg,NULL);
      if(def){
	sprintf(outbuf,getmsg(def),defval);
	print(outbuf,NULL);
      }
      getinput(0);
      if(margc)strncpy(newclass,margv[0],10);
      else if(def && !reprompt){
	strncpy(class,defval,10);
	return 1;
      } else endcnc();
    }
    if(sameas(newclass,"x"))return 0;
    if(newclass[0]=='?'){
      newclass[0]=0;
      listclasses();
      continue;
    }
    if(!newclass[0]){
      endcnc();
      continue;
    }
    ok=(existing==0);
    for(i=0;newclass[i];i++)newclass[i]=toupper(newclass[i]);
    for(i=0;i<numuserclasses;i++){
      if(sameas(newclass,userclasses[i].name)){
	if(existing) ok=1;
	else {
	  endcnc();
	  sprintf(outbuf,getmsg(err),newclass);
	  print(outbuf,NULL);
	  ok=0;
	  break;
	}
      }
    }
    if(existing && !ok){
      sprintf(outbuf,getmsg(err),newclass);
      print(outbuf,NULL);
      endcnc();
    }
  }
  strncpy(class,newclass,10);
  return 1;
}


int
keyed(long *k)
{
  long keys[KEYLENGTH];
  int shown=0;
  int key;
  char c;

  memcpy(keys,k,KEYLENGTH*sizeof(long));
  for(;;){
    if(!shown){
      char s1[65]={0},s2[65]={0};
      int i;
      
      for(i=0;i<64;i++){
	s1[i]=(keys[i/32]&(1<<(i%32)))?'X':'-';
	s2[i]=(keys[(i+64)/32]&(1<<((i+64)%32)))?'X':'-';
      }
      prompt(RSKEYSTAB,s1,s2,NULL);
      shown=1;
    }
    
    key=-1;
    for(;;){
      if((c=morcnc())!=0){
	if(toupper(c)=='X')return 0;
	key=cncint();
      } else {
	prompt(RSKEYSASK,NULL);
	getinput(0);
	key=atoi(margv[0]);
	if(!margc || reprompt){
	  endcnc();
	  continue;
	} else if(isX(margv[0]))return 0;
	else if(sameas(margv[0],"OK")){
	  memcpy(k,keys,KEYLENGTH*sizeof(long));
	  return 1;
	}else if(sameas(margv[0],"ON")){
	  int i;
	  for(i=0;i<KEYLENGTH;i++)keys[i]=-1L;
	  shown=0;
	  key=-1;
	  break;
	}else if(sameas(margv[0],"OFF")){
	  int i;
	  for(i=0;i<KEYLENGTH;i++)keys[i]=0L;
	  shown=0;
	  key=-1;
	  break;
	}else if(sameas(margv[0],"?")){
	  key=-1;
	  shown=0;
	  break;
	}
      }
      if(key<1 || key>128){
	endcnc();
	prompt(NUMERR,1,128,NULL);
      }else break;
    }
    
    if(key>=1 && key<=128){
      key--;
      keys[key/32]^=(1<<(key%32));
      prompt(RSKEYSON+((keys[key/32]&(1<<(key%32)))==0),key+1,NULL);
    }
  }
}


void
rsys_classed()
{
  char command[256];

  sprintf(command,"%s/%s",BINDIR,"classed");
  runmodule(command);
}


void
rsys_class()
{
  int     getclassname();
  char    userid[24], class[10];
  useracc usracc, *uacc=&usracc;

  if(!getuserid(userid,RSCLASSWHO,UNKUID,0,NULL,0))return;

  if(!uinsys(userid,0))loaduseraccount(userid,uacc);
  else uacc=&othruseracc;
  
  if(!morcnc())prompt(RSCLASSREP,uacc->userid,uacc->curclss);

  if(!getclassname(class,RSCLASSCLS,1,RSCLASSERR,0,""))return;

  if(!userexists(userid)){
    prompt(RSCLASSDEL,NULL);
    return;
  } else if (!uinsys(userid,0)) {
    useracc temp;
    char oldclass[32];

    loaduseraccount(userid,&temp);

    strcpy(oldclass,temp.curclss);
    strncpy(temp.curclss,class,sizeof(temp.curclss));
    strncpy(temp.tempclss,temp.curclss,sizeof(temp.tempclss));
    temp.classdays=0;
    audit(getenv("CHANNEL"),AUDIT(NEWCLSS),temp.userid,oldclass,
	  temp.curclss);

    saveuseraccount(&temp);
  } else {
    char oldclass[32];

    strcpy(oldclass,uacc->curclss);
    strncpy(uacc->curclss,class,sizeof(uacc->tempclss));
    strncpy(uacc->tempclss,uacc->curclss,sizeof(uacc->tempclss));
    uacc->classdays=0;

    audit(getenv("CHANNEL"),AUDIT(NEWCLSS),uacc->userid,oldclass,
	  uacc->curclss);

    sprintf(outbuf,getmsglang(RSCLASSNOT,othruseracc.language-1),uacc->curclss);
    if(injoth(&othruseronl,outbuf,0))prompt(NOTIFIED,uacc->userid);
  }
  prompt(RSCLASSOK,NULL);
}


void
rsys_keys()
{
  int     keyed();
  char    userid[24];
  useracc usracc, *uacc=&usracc;
  long    keys[KEYLENGTH];

  if(!getuserid(userid,RSKEYSWHO,UNKUID,0,NULL,0))return;
  if(sameas(userid,SYSOP)){
    prompt(RSKEYSSYS,NULL);
    return;
  }

  if(!uinsys(userid,0))loaduseraccount(userid,uacc);
  else uacc=&othruseracc;

  memcpy(keys,uacc->keys,sizeof(keys));
  if(!keyed(keys))return;

  if(!userexists(userid)){
    prompt(RSKEYSDEL,NULL);
    return;
  } else if (!uinsys(userid,0)) {
    useracc temp;

    loaduseraccount(userid,&temp);
    memcpy(temp.keys,keys,sizeof(temp.keys));
    saveuseraccount(&temp);
  } else {
    memcpy(uacc->keys,keys,sizeof(uacc->keys));
  }
  prompt(RSKEYSOK,NULL);
}



