/*****************************************************************************\
 **                                                                         **
 **  FILE:     graffiti.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 94, Version 1.0                                    **
 **  PURPOSE:  Graffiti Wall                                                **
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
 * Revision 1.1  2001/04/16 14:57:32  alexios
 * Initial revision
 *
 * Revision 1.6  1999/07/18 21:42:37  alexios
 * Changed a few fatal() calls to fatalsys().
 *
 * Revision 1.5  1998/12/27 15:44:51  alexios
 * Added autoconf support. Migrated to new locking functions.
 *
 * Revision 1.4  1998/08/14 11:30:53  alexios
 * Minor bug fixes.
 *
 * Revision 1.3  1998/08/11 10:10:18  alexios
 * Removed umask() call.
 *
 * Revision 1.2  1998/07/24 10:19:31  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 1.1  1997/11/06 20:11:34  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 1.0  1997/08/28 10:42:25  alexios
 * Initial revision
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif



#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_CTYPE_H 1
#define WANT_UNISTD_H 1
#define WANT_TIME_H 1
#define WANT_STRING_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "mbk_graffiti.h"
#include "graffiti.h"

promptblk *msg;


int entrykey;
int maxlen;
int maxsize;
int maxmsgs;
int ovrkey;
int syskey;
int wrtkey;


static char *zonk(char *s)
{
  int i;
  for(i=strlen(s)-1;i>0;i--)if(s[i]==32)s[i]=0; else break;
  return s;
}


void
init()
{
  initmodule(INITALL);
  msg=opnmsg("graffiti");
  setlanguage(thisuseracc.language);

  entrykey=numopt(ENTRYKEY,0,129);
  maxlen=numopt(MAXLEN,1,255);
  maxsize=numopt(MAXSIZE,1,32767);
  maxmsgs=numopt(MAXMSGS,1,100);
  ovrkey=numopt(OVRKEY,0,129);
  syskey=numopt(SYSKEY,0,129);
  wrtkey=numopt(WRTKEY,0,129);

  randomize();
}


int
checkfile()
{
  struct stat    buf;
  FILE           *fp;
  struct wallmsg header;

  if(stat(WALLFILE,&buf)){
    if((waitlock(WALLLOCK,5))==LKR_TIMEOUT){
      logerror("Timed out waiting for lock %s",WALLLOCK);
      return 0;
    }
    placelock(WALLLOCK,"creating");
    
    if((fp=fopen(WALLFILE,"w"))==NULL){
      fatalsys("Unable to create file %s",WALLFILE);
    }
    memset(&header,0,sizeof(header));
    strcpy(header.userid,SYSOP);
    sprintf(header.message,"%d",0);
    fwrite(&header,sizeof(header),1,fp);

    fclose(fp);
    chmod(WALLFILE,0666);
    rmlock(WALLLOCK);
  }
  return 1;
}


void
drawmessage()
{
  FILE           *fp, *out;
  char           fname[256];
  char           message[256]={0};
  char           userid[24];
  int            numlines=0, i;
  struct wallmsg wallmsg;

  if(!haskey(&thisuseracc,wrtkey)){
    prompt(WRTNAX);
    endcnc();
    return;
  } else if(!checkfile()){
    prompt(OOPS);
    return;
  } else {
    if((waitlock(WALLLOCK,5))==LKR_TIMEOUT){
      logerror("Timed out waiting for lock %s",WALLLOCK);
      return;
    }
    placelock(WALLLOCK,"checking");
    
    if((fp=fopen(WALLFILE,"r"))==NULL){
      rmlock(WALLLOCK);
      fatalsys("Unable to open file %s",WALLFILE);
    }
    
    if(!fread(&wallmsg,sizeof(wallmsg),1,fp)){
      rmlock(WALLLOCK);
      fatalsys("Unable to read file %s",WALLFILE);
    }

    numlines=atoi(wallmsg.message);
    strcpy(userid,wallmsg.userid);
    if(!haskey(&thisuseracc,ovrkey)
       && sameas(wallmsg.userid,thisuseracc.userid) && numlines>=maxmsgs){
      prompt(MSGDENY,NULL);
      rmlock(WALLLOCK);
      return;
    }
  }
  fclose(fp);
  rmlock(WALLLOCK);
  
  for(;;){
    if(!morcnc()){
      prompt(NEWMSG);
      bzero(input,MAXINPLEN+1);
      getinput(maxlen);
      bgncnc();
    }
    rstrin();
    strcpy(message,cncall());
    
    if(reprompt){
      endcnc();
      continue;
    } else if(!message[0] || isX(message)) return;
    else break;
  }

  prompt(WALLSAV,NULL);

  placelock(WALLLOCK,"writing");
  if((fp=fopen(WALLFILE,"r"))==NULL){
    int i=errno;
    rmlock(WALLLOCK);
    errno=i;
    fatalsys("Unable to open file %s",WALLFILE);
  }
  
  fread(&wallmsg,sizeof(wallmsg),1,fp);

  sprintf(fname,TMPDIR"/graffiti%05d",getpid());
  if((out=fopen(fname,"w"))==NULL){
    int i=errno;
    rmlock(WALLLOCK);
    errno=i;
    fatalsys("Unable to create temporary file %s",fname);
  }
  if(sameas(thisuseracc.userid,userid))numlines++;
  else numlines=1;
  
  memset(&wallmsg,0,sizeof(wallmsg));
  strcpy(wallmsg.userid,thisuseracc.userid);
  sprintf(wallmsg.message,"%d",numlines);
  fwrite(&wallmsg,sizeof(wallmsg),1,out);

  strcpy(wallmsg.message,message);
  fwrite(&wallmsg,sizeof(wallmsg),1,out);

  for(i=0;(i<(maxsize-1))&&(!feof(fp));){
    if(fread(&wallmsg,sizeof(wallmsg),1,fp) && wallmsg.userid[0]){
      i++;
      fwrite(&wallmsg,sizeof(wallmsg),1,out);
    }
  }
  fclose(out);
  fclose(fp);

  if(fcopy(fname,WALLFILE)){
    prompt(OOPS,NULL);
    rmlock(WALLLOCK);
    return;
  }
  unlink(fname);
  rmlock(WALLLOCK);
  prompt(WALLDON,NULL);
}


void
readwall()
{
  FILE *fp;
  struct wallmsg wallmsg;
  struct stat    buf;
  
  if(stat(WALLFILE,&buf)){
    prompt(EMPTY,NULL);
    return;
  }

  prompt(WALLHEAD,NULL);
  
  if((fp=fopen(WALLFILE,"r"))==NULL){
    fatalsys("Unable to open %s for reading.",WALLFILE);
  }

  fread(&wallmsg,sizeof(wallmsg),1,fp);
  while(!feof(fp)){
    if(!fread(&wallmsg,sizeof(wallmsg),1,fp))continue;
    if(wallmsg.userid[0]){
      sprintf(outbuf,"%s%s\n",colors[rnd(MAXCOLOR)],zonk(wallmsg.message));
      print(outbuf);
      if(lastresult==PAUSE_QUIT){
	fclose(fp);
	prompt(ABORT,NULL);
	return;
      }
    }
  }
  fclose(fp);
  prompt(WALLEND,NULL);
}


void
listwall()
{
  FILE           *fp;
  int            i=0;
  struct wallmsg wallmsg;
  struct stat    buf;
  
  if(stat(WALLFILE,&buf)){
    prompt(EMPTY,NULL);
    return;
  }

  prompt(WALLHEAD,NULL);
  
  if((fp=fopen(WALLFILE,"r"))==NULL){
    fatalsys("Unable to open %s for reading.",WALLFILE);
  }

  fread(&wallmsg,sizeof(wallmsg),1,fp);
  while(!feof(fp)){
    if(!fread(&wallmsg,sizeof(wallmsg),1,fp))continue;
    i++;
    if(wallmsg.userid[0]){
      sprintf(outbuf,"%3d %-10s %s\n",i,wallmsg.userid,zonk(wallmsg.message));
      print(outbuf,NULL);
      if(lastresult==PAUSE_QUIT){
	fclose(fp);
	prompt(ABORT,NULL);
	return;
      }
    }
  }
  fclose(fp);
  prompt(WALLEND,NULL);
}


void
cleanwall()
{
  FILE           *fp;
  struct wallmsg wallmsg;
  struct stat    buf;
  int            linenum;
  
  if(stat(WALLFILE,&buf) || (buf.st_size/sizeof(wallmsg))<2){
    prompt(WALLEMPTY,NULL);
    return;
  }

  if((fp=fopen(WALLFILE,"r+"))==NULL){
    fatalsys("Unable to open %s for reading.",WALLFILE);
  }

  for(;;){
    if(!getnumber(&linenum,DELMSG,1,buf.st_size/sizeof(wallmsg),BADNUM,0,0)){
      rmlock(WALLLOCK);
      fclose(fp);
      return;
    }
    if(waitlock(WALLLOCK,5)==LKR_TIMEOUT){
      prompt(TIMEOUT,NULL);
      fclose(fp);
      return;
    }
    placelock(WALLLOCK,"cleaning");
    fstat(fileno(fp),&buf);
    if(linenum>=buf.st_size/sizeof(wallmsg)){
      prompt(BADNUM,NULL);
      rmlock(WALLLOCK);
    } else {
      if(fseek(fp,sizeof(wallmsg)*linenum,SEEK_SET)){
	int i=errno;
	rmlock(WALLLOCK);
	errno=i;
	fatalsys("Unable to seek %s",WALLFILE);
      }
      if(!fread(&wallmsg,sizeof(wallmsg),1,fp)){
	int i=errno;
	rmlock(WALLLOCK);
	errno=i;
	fatalsys("Unable to read %s",WALLFILE);
      }
      if(!wallmsg.userid[0]){
	rmlock(WALLLOCK);
	prompt(BADNUM);
      } else {
	wallmsg.userid[0]=0;
	if(fseek(fp,sizeof(wallmsg)*linenum,SEEK_SET)){
	  int i=errno;
	  rmlock(WALLLOCK);
	  errno=i;
	  fatalsys("Unable to seek %s",WALLFILE);
	}
	if(!fwrite(&wallmsg,sizeof(wallmsg),1,fp)){
	  int i=errno;
	  rmlock(WALLLOCK);
	  errno=i;
	  fatalsys("Unable to write %s",WALLFILE);
	}
	fclose(fp);
	rmlock(WALLLOCK);
	prompt(WALLDEL,NULL);
	return;
      }
    }
  }
}


void
run()
{
  int shownintro=0;
  int shownmenu=0;
  char c;

  if(!haskey(&thisuseracc,entrykey)){
    prompt(NOENTRY,NULL);
    return;
  }

  for(;;){
    if(!(thisuseronl.flags&OLF_MMCALLING && thisuseronl.input[0])){
      if(!shownintro){
	prompt(HITHERE,NULL);
	shownintro=1;
      }
      if(!shownmenu){
	prompt(haskey(&thisuseracc,syskey)?SYSMENU:MENU,NULL);
	prompt(VSHMENU);
	shownmenu=2;
      }
    } else shownintro=shownmenu=1;
    if(thisuseronl.flags&OLF_MMCALLING && thisuseronl.input[0]){
      thisuseronl.input[0]=0;
    } else {
      if(!nxtcmd){
	if(thisuseronl.flags&OLF_MMCONCAT){
	  thisuseronl.flags&=~OLF_MMCONCAT;
	  return;
	}
	if(shownmenu==1){
	  prompt(haskey(&thisuseracc,syskey)?SYSSHMENU:SHMENU,NULL);
	} else shownmenu=1;
	getinput(0);
	bgncnc();
      }
    }

    if((c=morcnc())!=0){
      cncchr();
      switch (c) {
      case 'A':
	prompt(ABOUT,NULL);
	break;
      case 'D':
	drawmessage();
	break;
      case 'R':
	readwall();
	break;
      case 'L':
	if(haskey(&thisuseracc,syskey))listwall();
	else prompt(ERRSEL,c);
	break;
      case 'C':
	if(haskey(&thisuseracc,syskey))cleanwall();
	else prompt(ERRSEL,c);
	break;
      case 'X':
	prompt(LEAVE,NULL);
	return;
      case '?':
	shownmenu=0;
	break;
      default:
	prompt(ERRSEL,c);
      }
    }
    if(lastresult==PAUSE_QUIT)resetvpos(0);
    endcnc();
  }
}


void
done()
{
  clsmsg(msg);
  exit(0);
}


int
main(int argc, char **argv)
{
  setprogname(argv[0]);
  init();
  run();
  done();
  return 0;
}
