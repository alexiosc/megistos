/*****************************************************************************\
 **                                                                         **
 **  FILE:     notify.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, November 1997, Version 0.1                                **
 **  PURPOSE:  Notify users about other users logging in.                   **
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
 * Revision 1.1  2001/04/16 14:57:57  alexios
 * Initial revision
 *
 * Revision 1.4  1999/07/18 21:47:34  alexios
 * Changed a few fatal() calls to fatalsys().
 *
 * Revision 1.3  1998/12/27 16:06:58  alexios
 * Added autoconf support. Added support for new getlinestatus().
 *
 * Revision 1.2  1998/07/24 10:23:07  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 1.1  1997/11/06 20:14:02  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 1.0  1997/11/03 23:53:22  alexios
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
#include "mbk_notify.h"

promptblk *msg;

int entrykey;
int invkey;
int sopkey;
int numusr;

struct listitem {
  char userid[24];
};

struct listitem *list=NULL;

int  numusers;
int  own;


int
listcmp(const void *a, const void *b)
{
  return strcmp(((struct listitem*)a)->userid,
		((struct listitem*)b)->userid);
}


void
init()
{
  initmodule(INITALL);
  msg=opnmsg("notify");
  setlanguage(thisuseracc.language);
  entrykey=numopt(ENTRYKEY,0,129);
  invkey=numopt(SOPKEY,0,129);
  sopkey=numopt(INVKEY,0,129);
  numusr=numopt(NUMUSR,1,1000);
}


inline void
donelist()
{
  if(list!=NULL){
    free(list);
    list=NULL;
    numusers=0;
  }
}


inline void
newlist()
{
  if(list!=NULL)donelist();
  list=alcmem(numusr*sizeof(thisuseracc.userid));
  numusers=0;
}


void
loadlist(char *userid)
{
  char fname[256];
  FILE *fp;

  newlist();
  sprintf(fname,"%s/%s",NOTIFYDIR,userid);
  if((fp=fopen(fname,"r"))==NULL){
    if(errno!=ENOENT){
      fatalsys("Unable to open %s (errno=%d)",fname);
    } else return;
  }
  while(!feof(fp)){
    char line[256], *cp;
    if(!fgets(line,sizeof(line),fp))break;
    cp=strtok(line,"\n\r");
    if(!userexists(cp))continue;
    strcpy(list[numusers++].userid,cp);
  }
  fclose(fp);
  qsort(list,numusers,sizeof(struct listitem),listcmp);
  own=strcmp(userid,thisuseracc.userid);
}


void
savelist()
{
  char fname[256];
  FILE *fp;
  int i;

  sprintf(fname,"%s/%s",NOTIFYDIR,thisuseracc.userid);
  if((fp=fopen(fname,"w"))==NULL){
    fatalsys("Unable to create %s",fname);
  }
  for(i=0;i<numusers;i++)fprintf(fp,"%s\n",list[i].userid);
  fclose(fp);
}


void
notifyothers()
{
  int  i;
  char fname[256];
  struct stat st;
  struct listitem key;
  struct linestatus status;

  strcpy(key.userid,thisuseracc.userid);

  for(i=0;i<numchannels;i++){
    if(getlinestatus(channels[i].ttyname,&status)){
      if(status.result==LSR_USER){
	sprintf(fname,NOTIFYDIR"/%s",status.user);
	if(stat(fname,&st))continue;

	/* Check for Notify invisibility */

	uinsys(status.user,0);
	if(haskey(&thisuseracc,invkey)&&!haskey(&othruseracc,invkey))continue;

	/* Now load the other user's notify list and check it */

	loadlist(status.user);
	if(bsearch(&key,list,numusers,sizeof(struct listitem),listcmp)!=NULL){
	  sprompt(outbuf,INJMSG,
		  getpfix(SEXM,thisuseracc.sex==USX_MALE),
		  thisuseracc.userid);
	  injoth(&othruseronl,outbuf,0);
	}
      }
    }
  }
}


void
notifyme()
{
  int i,j,k;
  int *online;
  char tmp[8192];

  loadlist(thisuseracc.userid);
  online=alcmem(numusers*sizeof(int));
  bzero(online,numusers*sizeof(int));
  for(i=j=0;i<numusers;i++){
    if(!uinsys(list[i].userid,1))continue;
    if(haskey(&othruseracc,invkey)&&!haskey(&thisuseracc,invkey))continue;
    online[i]=1+(othruseracc.sex==USX_FEMALE);
    j++;
  }

  if(!j)return;
  for(i=k=0;i<numusers;i++){
    if(!online[i])continue;
    k++;
    if(k==1){
      if(j==1)sprompt(outbuf,LOGIN1,getpfix(CONM,online[i]));
      else sprompt(outbuf,LOGIN1,getpfix(CONP,online[i]));
    }
    if(k>1 && k<j){
      sprompt(tmp,LOGIN3);
      strcat(outbuf,tmp);
    } else if(k>1 && k==j){
      sprompt(tmp,LOGIN4);
      strcat(outbuf,tmp);
    }
    sprompt(tmp,LOGIN2,getpfix(SEXM,online[i]),list[i].userid);
    strcat(outbuf,tmp);
  }
  sprompt(tmp,LOGIN5);
  strcat(outbuf,tmp);
  print(outbuf);
}


void
login()
{
  notifyothers();
  notifyme();
}


void
add()
{
  if(numusers==numusr)prompt(ADDLIM,numusr);
  else if(numusers>numusr)prompt(ADDLM2,numusers,numusr);
  else {
    struct listitem key;
    useracc acc;
    for(;;){
      if(!getuserid(key.userid,ADDASK,ADDERR,0,0,0))return;
      if(sameas(key.userid,thisuseracc.userid)){
	prompt(ADDHUH);
	endcnc();
	continue;
      }
      if(bsearch(&key,list,numusers,sizeof(struct listitem),listcmp)!=NULL){
	prompt(ADDEXS,key.userid);
	endcnc();
	continue;
      } else break;
    }
    strcpy(list[numusers].userid,key.userid);
    numusers++;
    loaduseraccount(key.userid,&acc);
    prompt(ADDOK,getpfix(SEXM,acc.sex==USX_MALE),acc.userid);
    qsort(list,numusers,sizeof(struct listitem),listcmp);
  }
}


void
delete()
{
  struct listitem key, *p;

  if(!numusers){
    prompt(NOUSERS);
    return;
  }

  for(;;){
    if(!getuserid(key.userid,DELASK,DELERR,0,0,0))return;
    if((p=bsearch(&key,list,numusers,sizeof(struct listitem),listcmp))==NULL){
      prompt(DELERR,key.userid);
      endcnc();
      continue;
    } else break;
  }

  if(numusers>1){
    strcpy(p->userid,"\377\377\377");
    qsort(list,numusers,sizeof(struct listitem),listcmp);
  }
  numusers--;
  prompt(DELOK,key.userid);
}


void
listusers()
{
  int i;
  if(!numusers){
    prompt(NOUSERS);
    return;
  }
  prompt(LISTHD);
  for(i=0;i<numusers;i++)prompt(LISTU,list[i].userid);
  prompt(LISTFT,numusers);
}


void
run()
{
  int shownmenu=0;
  char c;

  if(!haskey(&thisuseracc,entrykey)){
    prompt(NOENTRY);
    return;
  }

  loadlist(thisuseracc.userid);

  for(;;){
    thisuseronl.flags&=~OLF_BUSY;
    if(!(thisuseronl.flags&OLF_MMCALLING && thisuseronl.input[0])){
      if(!shownmenu){
	prompt(MENU);
	shownmenu=2;
      }
    } else shownmenu=1;
    if(thisuseronl.flags&OLF_MMCALLING && thisuseronl.input[0]){
      thisuseronl.input[0]=0;
    } else {
      if(!nxtcmd){
	if(thisuseronl.flags&OLF_MMCONCAT){
	  thisuseronl.flags&=~OLF_MMCONCAT;
	  return;
	}
	if(shownmenu==1){
	  prompt(SHMENU);
	} else shownmenu=1;
	getinput(0);
	bgncnc();
      }
    }

    if((c=morcnc())!=0){
      cncchr();
      switch (c) {
      case 'H':
	prompt(HELP,numusr);
	break;
      case 'L':
	listusers();
	break;
      case 'A':
	add();
	break;
      case 'D':
	delete();
	break;
      case 'X':
	prompt(LEAVE);
	savelist();
	return;
      case '?':
	shownmenu=0;
	break;
      default:
	prompt(ERRSEL,c);
	endcnc();
	continue;
      }
    }
    if(lastresult==PAUSE_QUIT)resetvpos(0);
    endcnc();
  }
}


void
done()
{
  if(own)savelist();
  clsmsg(msg);
}


int
main(int argc, char *argv[])
{
  setprogname("notify");
  atexit(done);
  init();
  if(argc>1 && !strcmp(argv[1],"-login"))login();
  else run();
  done();
  return 0;
}
