/*****************************************************************************\
 **                                                                         **
 **  FILE:     news.c                                                       **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 95, Version 1.0                                      **
 **            B, August 96, Version 1.0                                    **
 **  PURPOSE:  Display latest news at login and/or inside BBS               **
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
 * Revision 1.8  2000/01/06 11:41:35  alexios
 * Made main() return a value.
 *
 * Revision 1.7  1999/07/18 21:47:26  alexios
 * Changed a few fatal() calls to fatalsys().
 *
 * Revision 1.6  1998/12/27 16:06:39  alexios
 * Added autoconf support.
 *
 * Revision 1.5  1998/08/11 10:18:49  alexios
 * Fixed [E]dit command bugs. Migrated file transfers to the
 * new format.
 *
 * Revision 1.4  1998/07/24 10:22:52  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 1.3  1997/11/06 20:13:48  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 1.2  1997/11/06 16:58:09  alexios
 * Changed calls to setaudit() so they use the new auditing
 * scheme.
 *
 * Revision 1.1  1997/09/12 13:19:14  alexios
 * Fixed news bulletin listing (it used to be out of alignment
 * and looked ugly). Added default answer of 'N' to the ASKUPL
 * question. Also implemented the ability to EDIT the bulletin
 * rather than re-uploading it.
 *
 * Revision 1.0  1997/08/28 11:02:32  alexios
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
#define WANT_TIME_H 1
#define WANT_SYS_STAT_H 1
#define WANT_DIRENT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "news.h"
#include "mbk_news.h"


promptblk *msg;

int  linkey;
int  entrykey;
int  sopkey;
int  defdur;
int  defshw;
int  defhdr;
char *defcls;
int  defkey;
int  maxlen;
char *upldesc;


void
init()
{
  classrec *cls;

  initmodule(INITALL);
  msg=opnmsg("news");
  setlanguage(thisuseracc.language);

  linkey=numopt(LINKEY,0,129);
  entrykey=numopt(ENTRYKEY,0,129);
  sopkey=numopt(SOPKEY,0,129);
  defdur=numopt(DEFDUR,0,3650);
  maxlen=numopt(MAXLEN,256,262144);

  if((defshw=tokopt(DEFSHW,"ALWAYS","ONCE"))==0){
    fatal("Option DEFSHW in news.msg has bad value");
  }else defshw--;

  if((defhdr=tokopt(DEFHDR,"NONE","DATE","TIME","BOTH"))==0){
    fatal("Option DEFHDR in news.msg has bad value");
  }else defhdr--;

  defcls=stgopt(DEFCLS);

  if((*defcls!='\0')&&(cls=findclass(defcls=stgopt(DEFCLS)))==NULL){
    fatal("User class \"%s\" does not exist!",defcls);
  }

  upldesc=stgopt(UPLDESC);
}


int
bltcmp(const void *a, const void *b)
{
  const struct newsbulletin *ba=a;
  const struct newsbulletin *bb=b;
  int i;

  if((i=bb->priority-ba->priority)!=0)return i;
  if((i=bb->date-ba->date)!=0)return i;
  if((i=bb->time-ba->time)!=0)return i;
  if((i=bb->num-ba->num)!=0)return i;
  return 0;
}


void
shownews(int lin, int sop)
{
  DIR *dp;
  FILE *fp;
  char fname[256];
  struct dirent *dirent;
  struct newsbulletin blt, *showlist=NULL, *tmp;
  int numblt=0,i,shownheader=0;

  if((dp=opendir(NEWSDIR))==NULL){
    fatalsys("Unable to opendir %s",NEWSDIR);
  }

  while((dirent=readdir(dp))!=NULL){
    if(!sameto("hdr-",dirent->d_name))continue;
    sprintf(fname,"%s/%s",NEWSDIR,dirent->d_name);

    if((fp=fopen(fname,"r"))==NULL)continue;
    if(fread(&blt,sizeof(blt),1,fp)!=1){
      fclose(fp);
      continue;
    }
    fclose(fp);

    if(!blt.enabled)continue;
    if(!haskey(&thisuseracc,sopkey)){
      if(!haskey(&thisuseracc,blt.key))continue;
      if(blt.class[0] && !sameas(thisuseracc.curclss,blt.class))continue;
    }
    
    numblt++;
    tmp=alcmem(numblt*sizeof(blt));
    if(numblt)memcpy(tmp,showlist,(numblt-1)*sizeof(blt));
    memcpy(&tmp[numblt-1],&blt,sizeof(blt));
    if(showlist)free(showlist);
    showlist=tmp;
 }
  closedir(dp);

  qsort(showlist,numblt,sizeof(blt),bltcmp);

  if(!numblt){
    if(!lin)prompt(NONEWS);
    free(showlist);
    return;
  }

  for(i=0;i<numblt;i++){
    if(sop){
      if(!shownheader){
	shownheader=1;
	prompt(RDNEWS);
      }
      prompt(SHEADER,showlist[i].num,
	     strdate(showlist[i].date),strtime(showlist[i].time,1),
	     showlist[i].priority,
	     showlist[i].numdays,
	     getpfix(VEDIT1A+showlist[i].info,1),
	     showlist[i].class,
	     showlist[i].key);
    } else if(showlist[i].info){
      char hdr[256]={0};
      switch(showlist[i].info){
      case 1:
	sprintf(hdr,"%s",strdate(showlist[i].date));
	break;
      case 2:
	sprintf(hdr,"%s",strtime(showlist[i].time,1));
	break;
      case 3:
	sprintf(hdr,"%s %s",strdate(showlist[i].date),
		strtime(showlist[i].time,1));
	break;
      }
      if(thisuseracc.datelast<=showlist[i].date){
	if(!shownheader){
	  shownheader=1;
	  prompt(RDNEWS);
	}
	prompt(HEADER,hdr,getpfix(NEWBLT,1));
      } else {
	if(!shownheader){
	  shownheader=1;
	  prompt(RDNEWS);
	}
	prompt(HEADER,hdr,"");
      }
    } else if(thisuseracc.datelast<=showlist[i].date)prompt(NEWBLT);
    
    sprintf(fname,NEWSFNAME,showlist[i].num);
    print("\n");
    if(lastresult==PAUSE_QUIT)break;
    printfile(fname);
    prompt(BLTDIV);
    if(lastresult==PAUSE_QUIT)break;
  }
  free(showlist);
}


void
listblts()
{
  DIR *dp;
  FILE *fp;
  char fname[256];
  struct dirent *dirent;
  struct newsbulletin blt;
  

  if((dp=opendir(NEWSDIR))==NULL){
    fatalsys("Unable to opendir %s",NEWSDIR);
  }

  prompt(LSTHDR);

  while((dirent=readdir(dp))!=NULL){
    if(!sameto("hdr-",dirent->d_name))continue;
    sprintf(fname,"%s/%s",NEWSDIR,dirent->d_name);

    if((fp=fopen(fname,"r"))==NULL)continue;
    if(fread(&blt,sizeof(blt),1,fp)!=1){
      fclose(fp);
      continue;
    }
    fclose(fp);
    if(lastresult==PAUSE_QUIT)break;
    prompt(LSTTAB,blt.num,strdate(blt.date),strtime(blt.time,1),
	   blt.priority,blt.numdays,blt.enabled?' ':'*',
	   blt.class,blt.key);
  }
  prompt(LSTFTR);
  closedir(dp);
}


int
askbltnum(int pr)
{
  int i,r;
  struct stat st;
  char fname[256];

  for(;;){
    i=0;
    setinputflags(INF_HELP);
    r=getnumber(&i,pr,1,32767,NUMERR,0,0);
    setinputflags(INF_NORMAL);
    if(!r)return 0;
    if(r==-1){
      listblts();
      continue;
    } else {
      sprintf(fname,NEWSHDR,i);
      if(stat(fname,&st)){
	prompt(NUMERR,i);
	continue;
      }
      sprintf(fname,NEWSFNAME,i);
      if(stat(fname,&st)){
	prompt(NUMERR,i);
	continue;
      }
      return i;
    }
  }
}


int
getbltnum()
{
  int i;
  struct stat st;

  char fname[256];
  for(i=1;;i++){
    sprintf(fname,NEWSFNAME,i);
    if(!stat(fname,&st))continue;
    sprintf(fname,NEWSHDR,i);
    if(!stat(fname,&st))continue;
    return i;
  }
}


void
upload(char *uploadname)
{
  char fname[256],command[256],*cp,name[256],dir[256];
  FILE *fp;
  int  count=-1;
  
  name[0]=dir[0]=0;
  setaudit(0,NULL,NULL,0,NULL,NULL);
  addxfer(FXM_UPLOAD,uploadname,upldesc,0,0);
  dofiletransfer();
  
  sprintf(fname,XFERLIST,getpid());
  
  if((fp=fopen(fname,"r"))==NULL)goto kill;

  while (!feof(fp)){
    char line[1024];
    
    if(fgets(line,sizeof(line),fp)){
      count++;
      if(!count)strcpy(dir,line);
      else if(count==1)strcpy(name,line);
    }
  }
  
  if((cp=strchr(dir,'\n'))!=NULL)*cp=0;
  if((cp=strchr(name,'\n'))!=NULL)*cp=0;
  fclose(fp);
  
  if(count<1)goto kill;
  else if(count>1)prompt(FTOOMANY);
  
  {
    char command[256];
    sprintf(command,"cp %s %s",name,uploadname);
    system(command);
  }

 kill:
  sprintf(command,"rm -rf %s %s",fname,dir);
  system(command);
  if(name[0]){
    sprintf(command,"rm -f %s >&/dev/null",name);
    system(command);
  }
  killxferlist();
}


void
insert(int num)
{
  char fname[256], fname2[256];
  FILE *fp;
  int  duration=defdur, enabled=1, info=defhdr, key=defkey, priority=0;
  int  i, j, check;
  char class[16], s[256], *cp, res[256], action;
  struct stat st;
  struct newsbulletin blt;

  if(num){
    sprintf(fname,NEWSHDR,num);
    if((fp=fopen(fname,"r"))==NULL){
      prompt(NUMERR,num);
      return;
    }
    fread(&blt,sizeof(blt),1,fp);
    fclose(fp);

    duration=blt.numdays;
    enabled=blt.enabled;
    info=blt.info;
    key=blt.key;
    priority=blt.priority;
    strcpy(class,blt.class);
  } else {
    memset(&blt,0,sizeof(blt));
  }

  sprintf(fname,TMPDIR"/news%05d",getpid());
  if((fp=fopen(fname,"w"))==NULL){
    logerrorsys("Unable to create data entry file %s",fname);
    return;
  }

  fprintf(fp,"%d\n",duration);
  fprintf(fp,"%s\n",enabled?"on":"");
  fprintf(fp,"%s\n",getmsg(VEDIT1A+info));
  fprintf(fp,"%s\n",class);
  fprintf(fp,"%d\n",key);
  fprintf(fp,"%d\n",priority);
  
  fprintf(fp,"OK button\nCancel button\n");
  fclose(fp);

  dataentry("news",VEDIT,LEDIT,fname);

  if((fp=fopen(fname,"r"))==NULL){
    logerrorsys("Unable to read data entry file %s",fname);
    return;
  }

  for(i=0;i<12;i++){
    fgets(s,sizeof(s),fp);
    if((cp=strchr(s,'\n'))!=NULL)*cp=0;
    if(i==0)sscanf(s,"%d",&duration);
    else if(i==1)enabled=sameas(s,"ON");
    else if(i==2){
      for(j=0;j<3;j++)if(!strcmp(getmsg(VEDIT1A+j),s)){
	info=j;
	break;
      }
    } else if(i==3)strcpy(class,stripspace(s));
    else if(i==4)sscanf(s,"%d",&key);
    else if(i==5)sscanf(s,"%d",&priority);
    else if(i==8)strcpy(res,s);
  }
  if(sameas(res,"CANCEL")){
    prompt(CANCEL);
    fclose(fp);
    unlink(fname);
    return;
  }
  
  fclose(fp);
  unlink(fname);

  if(class[0] && findclass(class)==0)prompt(WARNCLS,class);

  if(!num){
    blt.date=today();
    blt.time=now();
  }
  blt.numdays=duration;
  blt.priority=priority;
  blt.enabled=enabled;
  strcpy(blt.class,class);
  blt.key=key;
  blt.info=info;

  if(num){
    if(!getmenu(&action,0,0,ASKUPL,ASKERR,"YNE",ASKUPLD,'N'))action='N';
    check=action!='N';
  } else {
    check=0;
    action='Y';
  }

  if(!num)blt.num=num=getbltnum();

  sprintf(fname2,NEWSFNAME,num);
  
  sprintf(fname,NEWSHDR,num);
  if((fp=fopen(fname,"w"))==NULL){
    prompt(IOERR);
    unlink(fname2);
    unlink(fname);
    return;
  }
  fwrite(&blt,sizeof(blt),1,fp);
  fclose(fp);

  switch(action){
  case 'N':
    break;
  case 'Y':
    sprintf(fname,NEWSFNAME,num);
    upload(fname);

    sprintf(fname,NEWSFNAME,num);
    if(!stat(fname,&st)){
      prompt(BLTOK,num);
      return;
    } else {
      sprintf(fname,NEWSHDR,num);
      if(check)prompt(IOERR);
      unlink(fname);
    }
    break;
  case 'E':
    sprintf(fname,NEWSFNAME,num);
    sprintf(fname2,TMPDIR"/filedes%08lx",time(0));
    unlink(fname2);
    fcopy(fname,fname2);
    editor(fname2,maxlen);
    if(stat(fname2,&st)){
      prompt(TXTCAN);
      endcnc();
    } else {
      fcopy(fname2,fname);
      unlink(fname2);
      prompt(BLTOK,num);
    }
  }
}


void
edit()
{
  int num=askbltnum(ASKEDT);
  if(num)insert(num);
}



void
delete()
{
  int num=askbltnum(DELBLT);
  if(num){
    char fname[256];
    sprintf(fname,NEWSFNAME,num);
    unlink(fname);
    sprintf(fname,NEWSHDR,num);
    unlink(fname);
    prompt(DELOK);
  }
}



void
cleanup()
{
  DIR *dp;
  FILE *fp;
  char fname[256];
  struct dirent *dirent;
  struct newsbulletin blt;
  int dayssince=1, cof=cofdate(today());

  printf("News cleanup\n\n");

  sprintf(fname,"%s/.LAST.CLEANUP",NEWSDIR);
  if((fp=fopen(fname,"r"))!=NULL){
    int i;
    if(fscanf(fp,"%d\n",&i)==1){
      dayssince=cof-i;
      if(dayssince<0)dayssince=1;
    }
    fclose(fp);
  }
  if((fp=fopen(fname,"w"))!=NULL){
    fprintf(fp,"%d\n",cof);
    fclose(fp);
  }
  chmod(fname,0660);
  printf("Days since last cleanup: %d\n\n",dayssince);


  if((dp=opendir(NEWSDIR))==NULL){
    fatalsys("Unable to opendir %s",NEWSDIR);
  }

  while((dirent=readdir(dp))!=NULL){
    if(!sameto("hdr-",dirent->d_name))continue;
    sprintf(fname,"%s/%s",NEWSDIR,dirent->d_name);

    if((fp=fopen(fname,"r"))==NULL)continue;
    if(fread(&blt,sizeof(blt),1,fp)!=1){
      fclose(fp);
      continue;
    }
    fclose(fp);

    if(!blt.numdays)continue;
    blt.numdays-=dayssince;
    if(blt.numdays<=0){
      blt.numdays=0;
      blt.enabled=0;
    }

    if((fp=fopen(fname,"w"))==NULL)continue;
    if(fwrite(&blt,sizeof(blt),1,fp)!=1){
      fclose(fp);
      continue;
    }
    fclose(fp);
  }
  closedir(dp);
  printf("News cleanup done.\n\n");
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

  if(!haskey(&thisuseracc,sopkey)){
    shownews(0,0);
    return;
  }

  for(;;){
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
	if(shownmenu==1)prompt(SHMENU);
	else shownmenu=1;
	getinput(0);
	bgncnc();
      }
    }

    if((c=morcnc())!=0){
      cncchr();
      switch (c) {
      case 'R':
	shownews(0,haskey(&thisuseracc,sopkey));
	break;
      case 'I':
	insert(0);
	break;
      case 'L':
	listblts();
	break;
      case 'E':
	edit();
	break;
      case 'D':
	delete();
	break;
      case 'X':
	prompt(LEAVE,NULL);
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
login()
{
  print("\n");
  shownews(1,0);
}


void
done()
{
  clsmsg(msg);
  exit(0);
}


int
main(int argc, char *argv[])
{
  setprogname(argv[0]);
  if(argc>1 && !strcmp(argv[1],"-cleanup")){
    cleanup();
    exit(0);
  }
  init();
  if(argc>1 && !strcmp(argv[1],"-login"))login();
  else run();
  done();
  return 1;
}

