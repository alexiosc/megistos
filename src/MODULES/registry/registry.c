/*****************************************************************************\
 **                                                                         **
 **  FILE:     registry.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: B, November 94, Version 2.0                                  **
 **  PURPOSE:  Implement the Users' Registry a second time                  **
 **  NOTES:    (The first revision was lost in an accident involving a      **
 **            make-clean and 35 points of IQ).                             **
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
 * Revision 1.1  2001/04/16 14:57:59  alexios
 * Initial revision
 *
 * Revision 2.5  1999/07/18 21:47:54  alexios
 * Changed a few fatal() calls to fatalsys().
 *
 * Revision 2.4  1998/12/27 16:07:17  alexios
 * Added autoconf support.
 *
 * Revision 2.3  1998/07/24 10:23:17  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 2.2  1997/11/06 20:14:10  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 2.1  1997/09/12 13:21:02  alexios
 * Phonetic search was broken beyond belief. Fixed it.
 *
 * Revision 2.0  1997/08/28 11:03:31  alexios
 * Initial revision.
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
#include "mbk_registry.h"
#include "registry.h"


promptblk *msg;

int entrykey;
int syskey;
int crkey;
int template [3][30];

struct registry registry;


int
loadregistry(char *userid)
{
  FILE *fp;
  char fname[256];

  memset(&registry,0,sizeof(registry));
  sprintf(fname,"%s/%s",REGISTRYDIR,userid);
  if((fp=fopen(fname,"r"))==NULL)return -1;
  if(fread(&registry,sizeof(struct registry),1,fp)!=1){
    fatalsys("Unable to read registry %s",fname);
  }
  registry.template=registry.template%3;
  fclose(fp);
  return 0;
}


int
saveregistry(char *userid)
{
  FILE *fp;
  char fname[256];

  sprintf(fname,"%s/%s",REGISTRYDIR,userid);
  if((fp=fopen(fname,"w"))==NULL)return -1;
  if(fwrite(&registry,sizeof(struct registry),1,fp)!=1){
    fatalsys("Unable to write registry %s",fname);
  }
  fclose(fp);
  return 0;
}


void
init()
{
  int i,j;

  initmodule(INITALL);
  msg=opnmsg("registry");
  setlanguage(thisuseracc.language);

  entrykey=numopt(ENTRYKEY,0,129);
  syskey=numopt(SYSKEY,0,129);
  crkey=numopt(CRKEY,0,129);
  for(i=0;i<3;i++)for(j=0;j<30;j++)template[i][j]=numopt(T1F1+i*30+j,0,255);
}


void
login()
{
  if(haskey(&thisuseracc,entrykey) && loadregistry(thisuseracc.userid)){
    prompt(REGPLS);
  }
}


void
directory()
{
  int  shownhelp=0;
  char c, command[256];
  FILE *pipe;
  
  for(;;){
    lastresult=0;
    if((c=morcnc())!=0){
      c=cncchr();
      shownhelp=1;
    } else {
      if(!shownhelp)prompt(DINTRO,NULL);
      prompt(DLETTER,NULL);
      shownhelp=1;
      getinput(0);
      bgncnc();
      c=cncchr();
    }
    if(!margc && !reprompt)return;
    else if (!margc && reprompt) {
      endcnc();
      continue;
    }
    if(margc && sameas(margv[0],"?")){
      shownhelp=0;
      continue;
    } else if(isalpha(c)){
      break;
    } else {
      prompt(DIRERR,c);
      endcnc();
      continue;
    }
  }

  nonblocking();
  thisuseronl.flags|=OLF_BUSY;

  prompt(DIRHDR);

  sprintf(command,"\134ls %s |grep -i \"^[%c-Z]\"",REGISTRYDIR,c);
  if((pipe=popen(command,"r"))==NULL){
    fatalsys("Unable to spawn ls|grep pipe for %s",REGISTRYDIR);
  }
  
  for(;;){
    char line[256], c;

    if(fscanf(pipe,"%s",line)!=1)break;
    if(lastresult==PAUSE_QUIT){
      prompt(DIRCAN);
      break;
    }
    if(read(0,&c,1)==1)if(c==3 || c==10 || c==13){
      prompt(DIRCAN);
      break;
    }
    loadregistry(line);
    prompt(DIRLIN,line,registry.summary);
  }
  prompt(DIRFTR);
  pclose(pipe);
  blocking();
}


void
scan()
{
  int  shownhelp=0;
  char c, command[256];
  FILE *pipe;
  
  for(;;){
    lastresult=0;
    if((c=morcnc())!=0){
      c=cncchr();
      shownhelp=1;
    } else {
      if(!shownhelp)prompt(SINTRO,NULL);
      prompt(SLETTER,NULL);
      shownhelp=1;
      getinput(0);
      bgncnc();
      c=cncchr();
    }
    if(!margc && !reprompt)return;
    else if (!margc && reprompt) {
      endcnc();
      continue;
    }
    if(margc && sameas(margv[0],"?")){
      shownhelp=0;
      continue;
    } else if(isalpha(c)){
      break;
    } else {
      prompt(DIRERR,c);
      endcnc();
      continue;
    }
  }
  
  shownhelp=0;
  for(;;){
    lastresult=0;
    if(!morcnc()){
      if(!shownhelp)prompt(SCANKW,NULL);
      prompt(GETKEYW,NULL);
      shownhelp=1;
      getinput(0);
      bgncnc();
    }
    if (!margc) {
      endcnc();
      continue;
    } else if(isX(nxtcmd)){
      return;
    } else if(sameas(margv[0],"?")){
      shownhelp=0;
      endcnc();
      continue;
    } else break;
  }

  phonetic(nxtcmd);

  nonblocking();
  thisuseronl.flags|=OLF_BUSY;
  prompt(DIRHDR);

  sprintf(command,"\134ls %s |grep -i \"^[%c-Z]\"",REGISTRYDIR,c);
  if((pipe=popen(command,"r"))==NULL){
    fatalsys("Unable to spawn ls|grep pipe for %s",REGISTRYDIR);
  }
  
  for(;;){
    char line[256], c, summary[80];
    int i,pos,found;

    if(fscanf(pipe,"%s",line)!=1)break;
    if(lastresult==PAUSE_QUIT){
      prompt(DIRCAN);
      break;
    }
    if(read(0,&c,1)==1)if(c==3 || c==10 || c==13){
      prompt(DIRCAN);
      break;
    }
    loadregistry(line);

    for(found=i=pos=0;i<30;pos+=template[registry.template][i++]+1){
      char tmp[1024];
      bzero(tmp,sizeof(tmp));
      strncpy(tmp,&registry.registry[pos],sizeof(tmp)-1);
      phonetic(tmp);
      if(search(tmp,nxtcmd)){
	found=1;
	break;
      }
    }
    if(!found){
      char tmp[1024];
      bzero(tmp,sizeof(tmp));
      strncpy(tmp,registry.summary,sizeof(tmp)-1);
      phonetic(tmp);
      strcpy(summary,registry.summary);
      found=search(tmp,nxtcmd);
      strcpy(registry.summary,summary);
    }
    if(found)prompt(DIRLIN,line,registry.summary);
  }

  prompt(DIRFTR);
  pclose(pipe);
  blocking();
}


void
lookup()
{
  char userid[128], *format[33], buf[8192];
  int  i,j,pos;

  for(;;){
    if(!getuserid(userid,LKUPWHO,UIDERR,0,0,0))return;
    if(loadregistry(userid)){
      endcnc();
      prompt(UIDERR);
    } else break;
  }
  
  format[0]=userid;
  for(i=pos=0,j=1;i<30;pos+=template[registry.template][i++]+1){
    if(template[registry.template][i])format[j++]=&registry.registry[pos];
  }
  format[j++]=registry.summary;
  format[j]=NULL;
  vsprintf(buf,getmsg(T1LOOKUP+registry.template),format);
  print("%s",buf);
}


void
edit(char *userid)
{
  int i, pos;
  FILE *fp;
  char fname[256], s[256], *cp;

  loadregistry(userid);

  sprintf(fname,TMPDIR"/reg%05d",getpid());
  if((fp=fopen(fname,"w"))==NULL){
    logerrorsys("Unable to create data entry file %s",fname);
    return;
  }
  for(i=pos=0;i<30;pos+=template[registry.template][i++]+1){
    if(!template[registry.template][i])break;
    fprintf(fp,"%s\n",&registry.registry[pos]);
  }
  fprintf(fp,"%s\nOK button\nCancel button\n",registry.summary);
  fclose(fp);

  dataentry("registry",T1VISUAL+registry.template,
	    T1LINEAR+31*registry.template,fname);

  if((fp=fopen(fname,"r"))==NULL){
    logerrorsys("Unable to read data entry file %s",fname);
    return;
  }
  for(i=pos=0;i<30;pos+=template[registry.template][i++]+1){
    if(!template[registry.template][i])break;
    fgets(s,sizeof(s),fp);
    if((cp=strchr(s,'\n'))!=NULL)*cp=0;
    strcpy(&registry.registry[pos],s);
  }
  fgets(s,sizeof(s),fp);
  if((cp=strchr(s,'\n'))!=NULL)*cp=0;
  strcpy(registry.summary,s);
  fgets(s,sizeof(s),fp);
  fgets(s,sizeof(s),fp);
  fgets(s,sizeof(s),fp);
  if((cp=strchr(s,'\n'))!=NULL)*cp=0;
  fclose(fp);
  unlink(fname);
  if(sameas(s,"CANCEL")){
    prompt(EDITCAN);
    return;
  } else prompt(EDITOK);

  saveregistry(userid);
}


void
editother()
{
  char userid[128];

  if(!getuserid(userid,EDITWHO,EDITERR,0,0,0))return;
  edit(userid);
}


void
change()
{
  char opt;

  if(!getmenu(&opt,1,CHINFO,CHANGE,CHERR,"123",0,0)){
    prompt(NOCHANGE);
    return;
  } else opt-='1';
  
  if(loadregistry(thisuseracc.userid)){
    prompt(REGCR);
    registry.template=opt;
  }else{
    if(registry.template==opt){
      prompt(NONCHANGE);
      return;
    } else {
      registry.template=opt;
      memset(registry.registry,0,sizeof(registry.registry));
      prompt(TMPLCH);
    }
  }
  saveregistry(thisuseracc.userid);
}


void
run()
{
  int shownmenu=0;
  char c;

  if(!haskey(&thisuseracc,entrykey)){
    prompt(NOENTRY,NULL);
    return;
  }

  for(;;){
    thisuseronl.flags&=~OLF_BUSY;
    if(!(thisuseronl.flags&OLF_MMCALLING && thisuseronl.input[0])){
      if(!shownmenu){
	prompt(haskey(&thisuseracc,syskey)?REGSMNU:REGMNU,NULL);
	prompt(VSHMENU);
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
	  prompt(haskey(&thisuseracc,syskey)?SHSMENU:SHMENU,NULL);
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
	directory();
	break;
      case 'E':
	if(haskey(&thisuseracc,syskey))editother();
	else {
	  prompt(ERRSEL,c);
	  endcnc();
	  continue;
	}
	break;
      case 'L':
	lookup();
	break;
      case 'S':
	scan();
	break;
      case 'Y':
	if(haskey(&thisuseracc,crkey))edit(thisuseracc.userid);
	else {
	  prompt(EDITNAX);
	  endcnc();
	  continue;
	}
	break;
      case 'C':
	change();
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
done()
{
  clsmsg(msg);
  exit(0);
}


int
main(int argc, char *argv[])
{
  setprogname(argv[0]);
  init();
  if(argc>1 && !strcmp(argv[1],"-login"))login();
  else run();
  done();
  return 0;
}
