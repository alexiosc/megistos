/*****************************************************************************\
 **                                                                         **
 **  FILE:     miscfx.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, June 94                                                   **
 **  PURPOSE:  Implement various useful functions                           **
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
 * Revision 1.1  2001/04/16 14:50:42  alexios
 * Initial revision
 *
 * Revision 0.11  1999/07/28 23:06:34  alexios
 * No changes, effectively.
 *
 * Revision 0.10  1998/12/27 14:31:16  alexios
 * Added autoconf support. Added emulation of usleep() call for
 * systems that don't support it. Removed various functions to
 * other files to reduce the load on miscfx.c.
 *
 * Revision 0.9  1998/08/11 10:01:10  alexios
 * Added stripspace() to strip white space surrounding a token.
 *
 * Revision 0.8  1998/07/24 10:08:57  alexios
 * Made use of new error reporting.
 *
 * Revision 0.7  1997/11/06 20:03:54  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.6  1997/11/03 00:34:41  alexios
 * Optimised stgxlate for speed. Added a new function,
 * faststgxlate() that is suitable for very fast applications
 * where a complete translation table is available. This is
 * used by emud to translate text on the fly.
 *
 * Revision 0.5  1997/09/12 12:52:28  alexios
 * Added lowerc() and upperc() to convert strings to lower and
 * upper case respectively. Changed injoth() so it uses the
 * injoth IPC message queue instead of its previous method of
 * creating temporary disk files.
 *
 * Revision 0.4  1997/09/01 10:26:52  alexios
 * Fixed erroneous check to ANSI enable flag.
 *
 * Revision 0.3  1997/08/30 12:57:20  alexios
 * Removed bladcommand(). Replaced it with bbsdcommand(). The
 * daemon commands have not changed, though the daemon itself
 * has. The function syntax is different, though.
 *
 * Revision 0.2  1997/08/28 12:48:47  alexios
 * Fixed bug in uidxref cache that would refuse to retrieve
 * user Abc if user Abcd had been retrieved earlier.
 *
 * Revision 0.1  1997/08/26 16:35:17  alexios
 * First registered revision. Adequate.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif


#define WANT_SYS_SHM_H 1
#define WANT_SYS_MSG_H 1
#define WANT_TERMIOS_H 1
#define WANT_SYS_IOCTL_H 1
#define WANT_DIRENT_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include "config.h"
#include "bbs.h"
#include "menuman.h"
#include "mbk_sysvar.h"



/* Whoops, MSGMAX (max length of IPC message) not defined. Guess wildly */
#ifndef MSGMAX
#define MSGMAX 4096
#endif



void *
alcmem(size_t size)
{
  void *ptr=malloc(size);
  if(ptr)return ptr;
  fatal("Failed to allocate %08d bytes",size);
  return NULL; /* Get rid of warning -- we're not returning anyway */
}


char *
lowerc(char *s)
{
  char *cp;
  for(cp=s;*cp;cp++)*cp=tolower(*cp);
  return s;
}


char *
upperc(char *s)
{
  char *cp;
  for(cp=s;*cp;cp++)*cp=toupper(*cp);
  return s;
}


char *
stripspace(char *s)
{
  char *cp, *ep;
  int i=strspn(s," \n\t\r");
  cp=&s[i];
  for(ep=&cp[strlen(cp)-1];ep>cp
	&&(isspace(*ep)||(*ep=='\n')||(*ep=='\t')||(*ep=='\r'));ep--)*ep=0;
  return cp;
}


int
sameto(char *shorts, char *longs)
{
  while (*shorts != '\0') {
    if (tolower(*shorts) != tolower(*longs)) {
      return(0);
    }
    shorts++;
    longs++;
  }
  return(1);
}


int
sameas(char *stg1, char *stg2)
{
  while (*stg1 != '\0') {
    if (tolower(*stg1) != tolower(*stg2)) {
      return(0);
    }
    stg1++;
    stg2++;
  }
  return(*stg2 == '\0');
}


char *zeropad(char *s, int count)
{
  int i;
  for(i=1;i<count;i++)if(!s[i-1])s[i]=0;
  return s;
}


int
bbsdcommand(char *command, char *tty, char *arg)
{
  FILE *fp;
  char fname[256];
  
  sprintf(fname,BBSDPIPEFILE);
  if((fp=fopen(fname,"w"))==NULL){
    return 0;
  }
  fprintf(fp,"%s %s %s\n",command,tty,strlen(arg)?arg:".");
  fclose(fp);
  return 1;
}


int
dataentry(char *msg, int visual, int linear, char *data)
{
  char command[256];

  sprintf(command,"%s %s %d %d %s",BBSDIALOGBIN,msg,visual,linear,data);
  return runmodule(command);
}


inline char *
stgxlate(char *s,char *t)
{
  register char *table=t;
  register unsigned char *cp;
  for(cp=s;*cp;cp++)if(table[(int)*cp])*cp=table[(int)*cp];
  return s;
}


inline char *
faststgxlate(char *s,char *t)
{
  register char *table=t;
  register unsigned char *cp;
  for(cp=s;*cp;cp++)*cp=table[(int)*cp];
  return s;
}


int
search(char *string, char *keywords)
{
  char *cp, *sp;
  
  for(cp=keywords;*cp;cp=sp+1){
    if((sp=strchr(cp,32))!=NULL)*sp=0;
    else sp=cp+strlen(cp)-1;
    if(*cp && strstr(string,cp))return 1;
  }
  return 0;
}


int
runmodule(char *s)
{
  int res;

  doneinput();
  donesignals();
  if(nxtcmd && *nxtcmd){
    strcpy(thisuseronl.input,nxtcmd);
    thisuseronl.flags|=OLF_MMCONCAT;
  }else thisuseronl.flags&=~OLF_MMCONCAT;
  res=system(s);
  regpid(thisuseronl.channel);
  thisuseronl.flags&=~OLF_MMCONCAT;
  initinput();
  initsignals();
  thisuseronl.flags&=~(OLF_BUSY|OLF_NOTIMEOUT);
  resetinactivity();
  if(thisuseronl.flags&OLF_MMGCDGO)exit(0);
  return res;
}


int
editor(char *fname,int limit)
{
  char command[256];

  if(thisuseracc.prefs&UPF_VISUAL && thisuseronl.flags&OLF_ANSION){
    sprintf(command,"%s %s %d",VISEDBIN,fname,limit);
    return runmodule(command);
  } else {
    sprintf(command,"%s %s %d",LINEDBIN,fname,limit);
    return runmodule(command);
  }
}


void
gopage(char *s)
{
  union menumanpage p;
  FILE *fp;
  int found=0;

  if(thisuseronl.flags&OLF_INHIBITGO){
    setmbk(sysblk);
    prompt(CANTGO);
    rstmbk(sysblk);
    return;
  }

  if((fp=fopen(MENUMANPAGES,"r"))==NULL)return;
  while(!feof(fp)){
    if(fread(&p,sizeof(union menumanpage),1,fp)!=1){
      fclose(fp);
      setmbk(sysblk);
      prompt(GONAX,s);
      rstmbk(sysblk);
      return;
    } else if (sameas(s,p.m.name)) {
      found=1;
      break;
    }
  }
  fclose(fp);
  if(!found){
    setmbk(sysblk);
    prompt(GONAX,s);
    rstmbk(sysblk);
    return;
  }
  
  found=0;
  if(hassysaxs(&thisuseracc,USY_MASTERKEY)) found=1;
  if(p.m.class[0]&&!sameas(p.m.class,thisuseracc.curclss)) found=0;
  if(!haskey(&thisuseracc,p.m.key)) found=0;
  else found=1;
  
  if(!found){
    setmbk(sysblk);
    prompt(GONAX,s);
    rstmbk(sysblk);
    return;
  }
  
  strncpy(thisuseronl.prevpage,p.m.prev,15);
  strncpy(thisuseronl.curpage,p.m.name,15);
  thisuseronl.curpage[15]=0;
  thisuseronl.flags|=OLF_MMGCDGO;
  thisuseronl.flags&=~OLF_MMCALLING;
  fflush(stdout);
  exit(0);
}
  

int
fcopy(char *source, char *target)
{
  FILE *s, *t;
  int br, bw, tr, tw;
  char buf[8192];

  if((s=fopen(source,"r"))==NULL)return -1;
  if((t=fopen(target,"w"))==NULL){
    fclose(s);
    return -1;
  }

  for(br=bw=tr=tw=0;br==bw;){
    br=read(fileno(s),buf,sizeof(buf));
    if(br<0){
      fclose(s);
      fclose(t);
      unlink(target);
      return -1;
    }
    if(!br)break;
    bw=write(fileno(t),buf,br);
    if(bw<0){
      fclose(s);
      fclose(t);
      unlink(target);
      return -1;
    }
    tr+=br;
    tw+=bw;
  }
  fclose(s);
  fclose(t);
  if(tr!=tw){
    unlink(target);
    return -1;
  }
  return 0;
}



#ifndef HAVE_USLEEP
#  ifndef HAVE_SELECT
#    error "This system lacks both usleep() and select() -- unable to proceed."
#  endif

int usleep(int microseconds)
{
  struct timeval t;
  t.ts_sec=microseconds / 1000000;
  t.ts_usec=microseconds % 1000000;
  select(1,0,0,&t);
  return 1;
}

#endif
