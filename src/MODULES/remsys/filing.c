/*****************************************************************************\
 **                                                                         **
 **  FILE:     filing.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 94                                                   **
 **  PURPOSE:  file oriented functions for the remote sysop menu            **
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
 * Revision 0.2  1997/08/30 13:01:01  alexios
 * Increased EDITOR command file size limit from 512k to 4M. Let's
 * hope it's (a) enough and (b) not too much. Only trusted people
 * should have access to EDITOR anyway -- it's too dangerous.
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
#define WANT_TIME_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "remsys.h"

#include "mbk_remsys.h"


void
rsys_type()
{
  char fname[256]={0}, *cp;

  for(;;){
    if(morcnc()){
      rstrin();
      strcpy(fname,nxtcmd);
      break;
    }else{
      prompt(RSTYPEASK,NULL);
      getinput(0);
      bgncnc();
      if(!margc || reprompt) {
	endcnc();
	continue;
      } else if(isX(margv[0]))return;
      else {
	rstrin();
	strcpy(fname,nxtcmd);
	break;
      }
    }
  }

  fname[255]=0;
  cp=fname;
  while(*cp && !isspace(*cp))cp++;
  *cp=0;
  
  if(!catfile(fname))prompt(RSTYPEERR,fname);
}


void
cpmv(int asksrc,int asktrg,int ok, int err, char *cmd)
{
  char source[256]={0},target[256]={0}, command [515]={0};
  char *cp;

  for(;;){
    if(morcnc()){
      rstrin();
      strcpy(source,nxtcmd);
      break;
    }else{
      prompt(asksrc,NULL);
      getinput(0);
      bgncnc();
      if(!margc || reprompt) {
	endcnc();
	continue;
      } else if(isX(margv[0]))return;
      else {
	rstrin();
	strcpy(source,nxtcmd);
	break;
      }
    }
  }

  cncword();
  cp=source;
  while(*cp && !isspace(*cp))cp++;
  *cp=0;

  for(;;){
    if(morcnc()){
      rstrin();
      strcpy(target,nxtcmd);
      break;
    }else{
      prompt(asktrg,NULL);
      getinput(0);
      bgncnc();
      if(!margc || reprompt) {
	endcnc();
	continue;
      } else if(isX(margv[0]))return;
      else {
	rstrin();
	strcpy(target,nxtcmd);
	break;
      }
    }
  }

  cp=target;
  while(*cp && !isspace(*cp))cp++;
  *cp=0;
  endcnc();

  sprintf(command,"%s %s %s",cmd,source,target);
  prompt(runcommand(command)?err:ok);
}


void
rsys_copy()
{
  cpmv(RSCOPYSRC,RSCOPYTRG,RSCOPYOK,RSCOPYERR,"\\cp");
}


void
rsys_ren()
{
  cpmv(RSRENSRC,RSRENTRG,RSRENOK,RSRENERR,"\\mv");
}


void
rsys_dir()
{
  char fname[256]={0};
  char command[512]={0};
  char *cp=fname;

  for(;;){
    if(morcnc()){
      rstrin();
      strcpy(fname,nxtcmd);
      break;
    }else{
      prompt(RSDIRASK,NULL);
      getinput(0);
      bgncnc();
      if(!margc || reprompt) {
	endcnc();
	continue;
      } else if(isX(margv[0]))return;
      else {
	rstrin();
	strcpy(fname,nxtcmd);
	break;
      }
    }
  }

  fname[255]=0;
  cp=fname;
  while(*cp && !isspace(*cp))cp++;
  *cp=0;
  
  sprintf(command,"\\ls -la %s",fname);
  if(runcommand(command))prompt(RSDIRERR,fname);
}


void
rsys_del()
{
  char fname[256]={0};
  char command[512]={0};
  char *cp=fname;

  for(;;){
    if(morcnc()){
      rstrin();
      strcpy(fname,nxtcmd);
      break;
    }else{
      prompt(RSDELASK,NULL);
      getinput(0);
      bgncnc();
      if(!margc || reprompt) {
	endcnc();
	continue;
      } else if(isX(margv[0]))return;
      else {
	rstrin();
	strcpy(fname,nxtcmd);
	break;
      }
    }
  }

  fname[255]=0;
  cp=fname;
  while(*cp && !isspace(*cp))cp++;
  *cp=0;
  
  sprintf(command,"\\rm -f %s",fname);
  if(runcommand(command))prompt(RSDELERR,fname);
}


void
rsys_sys()
{
  if(morcnc()){
    rstrin();
  }else{
    prompt(RSSYSASK,NULL);
    getinput(0);
    bgncnc();
  }
  if(!nxtcmd || !*nxtcmd)return;
  if(isX(nxtcmd))return;
  {
    char command[512]={0};
    strcpy(command,nxtcmd);
    runcommand(command);
  }
}


void
rsys_shell()
{
  runcommand(unixsh);
}


void
rsys_editor()
{
  char fname[256],c;
  FILE *fp;

  for(;;){
    if((c=morcnc())!=0){
      if(sameas(nxtcmd,"X"))return;
    } else {
      prompt(RSEDITWHF);
      getinput(0);
      nxtcmd=input;
      if (!margc) {
	endcnc();
	continue;
      }
      if(isX(margv[0])){
	return;
      }
    }

    strcpy(fname,cncword());
    if((fp=fopen(fname,"r"))==NULL){
      fclose(fp);
      prompt(RSXFERERR,fname);
      endcnc();
      continue;
    } else {
      char tempname[256];

      sprintf(tempname,TMPDIR"/rsys%08lx",time(0));
      unlink(tempname);
      symlink(fname,tempname);
      fclose(fp);
      editor(tempname,4<<20);
      unlink(tempname);
      return;
    }
  }
}


