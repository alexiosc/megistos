/*****************************************************************************\
 **                                                                         **
 **  FILE:     clubop.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 1995                                               **
 **  PURPOSE:  Club Operator functions                                      **
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
 * Revision 1.1  2001/04/16 14:54:59  alexios
 * Initial revision
 *
 * Revision 0.5  1998/12/27 15:33:03  alexios
 * Added autoconf support.
 *
 * Revision 0.4  1998/07/24 10:17:37  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.3  1997/11/06 20:05:26  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/08/30 12:58:35  alexios
 * One minor fix to get rid of a compiler warning.
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
#define WANT_DIRENT_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "mbk_emailclubs.h"
#include "clubs.h"
#include "email.h"


void
tagmsg(struct message *msg)
{
  getmsgheader(msg->msgno,msg);
  msg->flags^=MSF_EXEMPT;
  writemsgheader(msg);
  prompt(msg->flags&MSF_EXEMPT?COPTTG:COPTUN);
}


void
periodic(struct message *msg)
{
  int i;
  
  if(!getnumber(&i,COPPASK,0,999999,COPPERR,COPPDEF,msg->period))return;
  
  getmsgheader(msg->msgno,msg);
  msg->period=i;
  writemsgheader(msg);

  if(!msg->period){
    loadclubhdr(msg->club);
    clubhdr.nper--;
    saveclubhdr(&clubhdr);
    prompt(COPPOK1);
  } else {
    loadclubhdr(msg->club);
    clubhdr.nper++;
    saveclubhdr(&clubhdr);
    prompt(COPPOK2,msg->period,getpfix(DAYSNG,msg->period));
  }
}


void
approve(struct message *msg)
{
  getmsgheader(msg->msgno,msg);
  msg->flags^=MSF_APPROVD;
  writemsgheader(msg);

  loadclubhdr(msg->club);
  if(msg->flags&MSF_APPROVD)clubhdr.nfunapp--;
  else clubhdr.nfunapp++;
  saveclubhdr(&clubhdr);

  prompt(msg->flags&MSF_APPROVD?COPAAPP:COPAUNA);
}


void
insatt(struct message *msg)
{
  char opt;
  int res, truncpos;
  FILE *fpi, *fpo;
  char fnamei[256], fnameo[256];
  struct message m;
  char buf[1024];
  int read, written;

  for(;;){
    setinputflags(INF_HELP);
    res=getmenu(&opt,1,COPIAMNU,COPIASMNU,COPIARS,"OA",0,0);
    setinputflags(INF_NORMAL);
    if(res<0){
      prompt(COPIAH);
      endcnc();
      continue;
    }
    break;
  }

  sprintf(fnamei,"%s/%s/%s/"FILEATTACHMENT,
	  MSGSDIR,msg->club,MSGATTDIR,msg->msgno);
  sprintf(fnameo,"%s/%s/"MESSAGEFILE,
	  MSGSDIR,msg->club,msg->msgno);

  if((fpi=fopen(fnamei,"r"))==NULL){
    fclose(fpi);
    prompt(COPIAR);
    return;
  }

  if(opt=='A'){
    if((fpo=fopen(fnameo,"a"))==NULL){
      fclose(fpi);
      fclose(fpo);
      prompt(COPIAR);
      return;
    }
    fprintf(fpo,"\n\n");
  } else {
    if((fpo=fopen(fnameo,"r+"))==NULL){
      fclose(fpi);
      fclose(fpo);
      prompt(COPIAR);
      return;
    }
    fseek(fpo,sizeof(struct message),SEEK_SET);
  }

  do{
    read=fread(&buf,1,sizeof(buf),fpi);
    written=fwrite(&buf,1,read,fpo);
    if(lastresult==PAUSE_QUIT)break;
  }while(read && read==written);

  truncpos=ftell(fpo);
  fclose(fpi);
  fclose(fpo);
  truncate(fnameo,truncpos);
  unlink(fnamei);

  getmsgheader(msg->msgno,&m);
  res=(m.flags&MSF_APPROVD)==0;
  m.flags&=~(MSF_FILEATT|MSF_APPROVD);
  writemsgheader(&m);

  loadclubhdr(msg->club);
  clubhdr.nfiles--;
  if(res)clubhdr.nfunapp--;
  saveclubhdr(&clubhdr);

  prompt(opt=='A'?COPIAA:COPIAO);
}


void
insblt(struct message *msg)
{
  char command[256];
  if(!msg->club[0]){
    fatal("Sanity check failed: club message with no set club.");
  }
  sprintf(command,"%s -insert %s/%ld",BULLETINBIN,msg->club,msg->msgno);
  runmodule(command);
}


char
clubopmenu(struct message *msg)
{
  int menu=msg->flags&MSF_FILEATT?COPMNUF:COPMNU;
  int help=msg->flags&MSF_FILEATT?COPMNUFH:COPMNUH;
  char opts[32];
  char opt;
  int i;

  strcpy(opts,(msg->flags&MSF_FILEATT?"MECFTPBAI":"MECFTPB"));

  for(;;){
    setinputflags(INF_HELP);
    i=getmenu(&opt,1,0,menu,COPERR,opts,0,0);
    setinputflags(INF_NORMAL);

    if(!i)return 0;
    else if(i<0){
      endcnc();
      prompt(help);
      continue;
    } else break;
  }
  switch (opt){
  case 'C':
    copymsg(msg);
    return 1;
  case 'F':
    forwardmsg(msg);
    return 1;
  case 'M':
    clubopmodify(msg);
    return 0;
  case 'E':
    erasemsg(0,msg);
    return 1;
  case 'T':
    tagmsg(msg);
    return 0;
  case 'P':
    periodic(msg);
    return 0;
  case 'A':
    approve(msg);
    return 0;
  case 'I':
    insatt(msg);
    return 1;
  case 'B':
    insblt(msg);
    return 0;
  }
  return 'N';
}
