/*****************************************************************************\
 **                                                                         **
 **  FILE:     distlist.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, June 1995, Version 0.5                                    **
 **  PURPOSE:  Configure and use distribution lists                         **
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
 * Revision 1.1  2001/04/16 14:55:07  alexios
 * Initial revision
 *
 * Revision 0.7  1999/07/18 21:21:38  alexios
 * Changed a few fatal() calls to fatalsys().
 *
 * Revision 0.6  1998/12/27 15:33:03  alexios
 * Added autoconf support.
 *
 * Revision 0.5  1998/08/11 10:03:22  alexios
 * Made club listings non case-sensitive.
 *
 * Revision 0.4  1998/07/24 10:17:37  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.3  1997/11/06 20:05:26  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/09/14 13:49:59  alexios
 * Redesigned internal distribution list mechanism to get rid
 * of numerous little problems and bugs (and to speed it up by
 * not using popen() any more).
 *
 * Revision 0.1  1997/08/28 10:21:30  alexios
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
#define WANT_TIME_H 1
#define WANT_DIRENT_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "mbk_emailclubs.h"
#include "email.h"


static char   current[256];
static char   **lst;
static int    inspoint=0;
static int    protection=0;
static int    readpoint=0;
static struct dirent **d;


int
addrcmp(const void *a, const void *b)
{
  return strcmp(*(char **)a,*(char **)b);
}


static void
sortlist()
{
  qsort(lst,inspoint,sizeof(char *),addrcmp);
}


void
initlist()
{
  if(lst!=NULL){
    int i;
    for(i=0;i<inspoint;i++)if(lst[i]!=NULL)free(lst[i]);
  }
  free(lst);
  lst=NULL;
  inspoint=0;
}


static int
dlgetmenu(option,show,lmenu,smenu,err,opts,def,defval)
char *option, defval, *opts;
int  show,lmenu,smenu,err,def;
{
  int shownmenu=!show;
  char c;

  for(;;){
    lastresult=0;
    if((c=morcnc())!=0){
      if(sameas(nxtcmd,"X"))return 0;
      c=cncchr();
      shownmenu=1;
    } else {
      if(!shownmenu && lmenu)prompt(lmenu);
      shownmenu=1;
      if(smenu)prompt(smenu,current);
      if(def){
	sprintf(outbuf,getmsg(def),defval);
	print(outbuf,NULL);
      }
      getinput(0);
      bgncnc();
      c=cncchr();
    }
    if((!margc||(margc==1&&sameas(margv[0],".")))&&def && !reprompt) {
      *option=defval;
      return 1;
    } else if (!margc) {
      endcnc();
      continue;
    }
    if(isX(margv[0])){
      return 0;
    } else if(margc && sameas(margv[0],"?")){
      shownmenu=0;
      continue;
    } else if(strchr(opts,c)){
      *option=c;
      return 1;
    } else {
      if(err)prompt(err,c);
      endcnc();
      continue;
    }
  }
  return 0;
}


static int
checkselectname(char *name)
{
  char *cp;
  DIR *dp;
  struct dirent *dir;
  FILE *fp;
  char fname[256];
  int p;

  if(name[0]!='!'){
    prompt(DLSERR1);
    return 0;
  }

  if(name[0]==name[1]){
    prompt(DLSERR3,name);
    return 0;
  }

  for(cp=&name[1];*cp;cp++)if(!strchr(FNAMECHARS,*cp)){
    prompt(DLSERR2);
    return 0;
  }

  if(sameas(name,"!mass")||sameas(name,"!all")){
    prompt(DLSERR3,name);
    return 0;
  }
  
  if(!strcmp(name,"!"))sprintf(name,"!.%s",thisuseracc.userid);
  
  if((dp=opendir(MSGSDISTDIR))==NULL)return 0;
  while((dir=readdir(dp))!=NULL){
    if(sameas(dir->d_name,".")||sameas(dir->d_name,".."))continue;
    if(sameas(&name[1],dir->d_name)){
      sprintf(name,"!%s",dir->d_name);
      break;
    }
  }
  closedir(dp);
  
  strcpy(name,&name[1]);
  sprintf(fname,"%s/%s",MSGSDISTDIR,name);
  if((fp=fopen(fname,"r"))==NULL)return 1;
  if(fscanf(fp,"%d",&p)==1){
    if(!haskey(&thisuseracc,p)){
      prompt(DLSERR3,name);
      return 0;
    }
  }

  fclose(fp);
  return 1;
}


void
listlists()
{
  DIR *dp;
  struct dirent *dir;
  int i;
  
  prompt(LSTLSTH);
  prompt(LSTLST,"MASS");
  prompt(LSTLST,"ALL");

  for(i=0;i<numuserclasses;i++){
    char s[80];
    if(lastresult==PAUSE_QUIT)return;
    sprintf(s,"!%s",userclasses[i].name);
    prompt(LSTLST,s);
  }

  if((dp=opendir(MSGSDISTDIR))==NULL)return;
  while((dir=readdir(dp))!=NULL){
    if(sameas(dir->d_name,".")||sameas(dir->d_name,".."))continue;
    if(lastresult==PAUSE_QUIT){
      closedir(dp);
      return;
    }
    prompt(LSTLST,dir->d_name);
  }
  closedir(dp);
  prompt(LSTLSTF);
}


int
getname(char *name, int pr)
{
  char *i, c;

  for(;;){
    lastresult=0;
    if((c=morcnc())!=0){
      if(sameas(nxtcmd,"X"))return 0;
      i=cncword();
    } else {
      prompt(pr);
      getinput(0);
      bgncnc();
      i=cncword();
      if (!margc) {
	endcnc();
	continue;
      }
      if(isX(margv[0])){
	return 0;
      }
    }
    if(sameas(i,"?")){
      listlists();
      endcnc();
      continue;
    } else if(!checkselectname(i))continue;
    else {
      strcpy(name,i);
      return 1;
    }
  }
  return 0;
}


static int
getdistlistname()
{
  if(!haskey(&thisuseracc,sopkey)){
    sprintf(current,".%s",thisuseracc.userid);
    return 1;
  }
  return getname(current,DLSASK);
}


static void
loadlist()
{
  char fname[256];
  int i;
  FILE *fp;

  sprintf(fname,"%s/%s",MSGSDISTDIR,current);

  initlist();

  lst=alcmem(sizeof(char *)*256);
  bzero(lst,sizeof(char *)*256);

  if((fp=fopen(fname,"r"))==NULL)return;
  if(fscanf(fp,"%d",&protection)!=1){
    fclose(fp);
    return;
  }
  for(i=0;i<256;i++){
    char line[1024];
    if(fscanf(fp,"%s",line)!=1){
      fclose(fp);
      return;
    }
    lst[inspoint++]=strdup(line);
  }
  fclose(fp);
  sortlist();
  readpoint=0;
}


static void
savelist()
{
  char fname[256];
  int i;
  FILE *fp;

  sprintf(fname,"%s/%s",MSGSDISTDIR,current);

  if(!inspoint)unlink(fname);
  sortlist();
  if((fp=fopen(fname,"w"))==NULL)return;
  fprintf(fp,"%d\n",protection);
  for(i=0;i<inspoint;i++)if(lst[i])fprintf(fp,"%s\n",lst[i]);
  fclose(fp);
}


void
listlist()
{
  int i;
  int cost=0;

  sortlist();
  prompt(DLLISTH,current,protection);
  for(i=0;i<inspoint && lst[i];i++){
    prompt(DLLISTL,i+1,lst[i]);
    if(lastresult==PAUSE_QUIT)return;
    if(strchr(lst[i],'@')||strchr(lst[i],'%'))cost+=netchg;
    cost+=wrtchg;
  }
  prompt(DLLISTF,cost,getpfix(CRDSING,cost));
}


int
getaddress(char *uid)
{
  char *s=NULL;

  for(;;){
    if(morcnc())s=cncword();
    else {
      prompt(DLAWHO);
      getinput(0);
      bgncnc();
      if(!margc){
	endcnc();
	continue;
      }
      s=cncword();
    }
    if(sameas(s,"?")){
      endcnc();
      listlist();
      continue;
    } else if(isX(s)){
      endcnc();
      return 0;
    } else {
      if(strchr(s,'@')||strchr(s,'%')){
	if(haskey(&thisuseracc,netkey)){
	  strcpy(uid,s);
	  return 1;
	} else {
	  prompt(DLANNET);
	  endcnc();
	  continue;
	}
      } else if(!uidxref(s,0)){
	endcnc();
	prompt(DLAUNKID,s);
	continue;
      }else {
	strcpy(uid,s);
	return 1;
      }
    }
  }
  return 0;
}


void
add2list()
{
  char uid[256];

  if(inspoint>255){
    prompt(DLAR1,maxdlm);
    return;
  }

  for(;;){
    if(!getaddress(uid))return;
    else {
      int i;
      for(i=0;i<inspoint;i++)if(sameas(lst[i],uid)){
	endcnc();
	prompt(DLADUPL);
	return;
      }
    }
    break;
  }
  lst[inspoint++]=strdup(uid);
}


void
listdel()
{
  int i,n;
  
  if(!inspoint){
    prompt(DLDR1);
    return;
  }

  for(;;){
    setinputflags(INF_HELP);
    i=getnumber(&n,DLDASK,1,inspoint,DLDERR,0,0);
    setinputflags(INF_NORMAL);
    if(!i)return;
    if(i<1)listlist();
    else break;
  }
  
  if(n<inspoint)lst[n-1]=lst[inspoint-1];
  free(lst[inspoint-1]);
  lst[--inspoint]=NULL;
  sortlist();
}


void
getprotection()
{
  if(!getnumber(&protection,DLPASK,0,
		sameas(thisuseracc.userid,SYSOP)?129:128,
		DLPERR,0,0))return;
}


void
confdistlist()
{
  char opt;
  int firsttime=1;

  int sop=haskey(&thisuseracc,sopkey);

  if(!haskey(&thisuseracc,dlkey)){
    prompt(DLNOAX);
    return;
  }

  if(!getdistlistname())return;
  loadlist();

  for(;;){
    if(!dlgetmenu(&opt,firsttime,sop?DLSMNU:DLMNU,sop?DLSMNUS:DLMNUS,DLERRS,
		  sop?"HLADPSK":"HLAD",0,0))break;
    firsttime=0;
    switch(opt){
    case 'H':
      prompt(sop?DLHELPS:DLHELP,maxdlm);
      break;
    case 'L':
      listlist();
      break;
    case 'A':
      add2list();
      break;
    case 'D':
      listdel();
      break;
    case 'P':
      getprotection();
      break;
    case 'S':
      savelist();
      getdistlistname();
      break;
    case 'K':
      {
	int yes;
	if(getbool(&yes,DLKASK,DLKERR,0,0)){
	  if(yes){
	    char fname[256];
	    sprintf(fname,"%s/%s",MSGSDISTDIR,current);
	    unlink(fname);
	    return;
	  }
	}
      }
      break;
    }
  }
  savelist();
}


static int
usrselect(const struct dirent *d)
{
  return d->d_name[0]!='.';
}


int
opendistribution(char *dist)
{
  strcpy(current,&dist[1]);
  if((dist[0]=='!' && dist[1]=='!')||sameas(dist,"!all")){
    int i;

    initlist();
    inspoint=scandir(USRDIR,&d,usrselect,ncsalphasort);

    if(inspoint<0){
      fatalsys("I/O error occured!");
    }

    lst=alcmem(sizeof(char*)*inspoint);

    for(i=0;i<inspoint;i++){
      lst[i]=strdup(d[i]->d_name);
      free(d[i]);
    }

    free(d);
    sortlist();
    readpoint=0;
  } else {
    loadlist();
    readpoint=0;
  }
  return 1;
}


char *readdistribution()
{
  if(current[0]=='!'){
    useracc uacc;
    for(;readpoint<inspoint;){
      char *uid=lst[readpoint++];
      loaduseraccount(uid,&uacc);
      if(sameas(uacc.curclss,&current[1]))return uid;
    }
    return NULL;
  }

  return readpoint<inspoint?lst[readpoint++]:NULL;
}


void closedistribution()
{
  initlist();
}
