/*****************************************************************************\
 **                                                                         **
 **  FILE:     offline.bulletins.c                                          **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 1997, Version 0.1                                  **
 **  PURPOSE:  Graffiti wall plugin, download                               **
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
 * Revision 1.2  2001/04/16 21:56:32  alexios
 * Completed 0.99.2 API, dragged all source code to that level (not as easy as
 * it sounds).
 *
 * Revision 0.6  1999/07/18 21:44:25  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 0.5  1998/12/27 15:47:33  alexios
 * Added autoconf support.
 *
 * Revision 0.4  1998/08/14 11:36:01  alexios
 * Added auto-translation to user's character set and to the
 * DOS newline scheme (NLCR).
 *
 * Revision 0.3  1998/07/24 10:20:42  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:06:55  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 10:54:33  alexios
 * First registered revision. Adequate.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
const char *__RCS=RCS_VER;
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
#include "offline.graffiti.h"
#include "../../mailer.h"
#include "mbk_offline.graffiti.h"
#include "../../../graffiti/graffiti.h"

#define __MAILER_UNAMBIGUOUS__
#include "mbk_mailer.h"

#define __GRAFFITI_UNAMBIGUOUS__
#include "mbk_graffiti.h"


static int
addtodoorid()
{
  FILE *fp;

  if((fp=fopen("door.id","a"))==NULL){
    fclose(fp);
    return 1;
  }
  fprintf(fp,"CONTROLTYPE = WALL\rFILE\n_WALL = %s\r\n",wallfil);
  fclose(fp);
  return 0;
}


static char *zonk(char *s)
{
  int i;
  for(i=strlen(s)-1;i>0;i--)if(s[i]==32)s[i]=0; else break;
  return s;
}


int
ogdownload()
{
  FILE           *fp, *out;
  struct wallmsg wallmsg;
  struct stat    st;
  char           buf[8192];
  int            shown=0;
  int            oldansi;
  int            numlines=0;

  if(!loadprefs(USERQWK,&userqwk)){
    error_fatal("Unable to read user mailer preferences for %s",
	  thisuseracc.userid);
  }

  readxlation();
  xlationtable=(userqwk.flags&OMF_TR)>>OMF_SHIFT;

  readprefs(&prefs);

  if(!(prefs.flags&OGF_YES))return 0;

  prompt(DLHDR);
  if(!key_owns(&thisuseracc,entrykey)){
    prompt(DLNAX);
    return 0;
  }
  
  if(stat(WALLFILE,&st)){
    prompt(DLDMT);
    return 0;
  }

  msg_set(graffiti_msg);
  oldansi=out_flags&OFL_ANSIENABLE;
  out_setansiflag((prefs.flags&OGF_ANSI)==1);

  if((fp=fopen(WALLFILE,"r"))==NULL){
    error_fatalsys("Unable to open %s for reading.",WALLFILE);
  }

  if((out=fopen(wallfil,"w"))==NULL){
    error_fatalsys("Unable to create wall file %s",wallfil);
  }

  fread(&wallmsg,sizeof(wallmsg),1,fp);
  while(!feof(fp)){
    if(!fread(&wallmsg,sizeof(wallmsg),1,fp))continue;
    if(wallmsg.userid[0]){
      if(!shown){
	shown=1;
	sprompt(buf,GRAFFITI_WALLHEAD);
	fputs(buf,out);
      }
      zonk(wallmsg.message);
      fprintf(out,"%s%s\r\n",
	      prefs.flags&OGF_ANSI?colors[rnd(MAXCOLOR)]:"",
	      wallmsg.message);
      numlines++;
      if((prefs.numlines>0) && numlines>=prefs.numlines)break;
    }
  }
  sprompt(buf,GRAFFITI_WALLEND);
  fputs(buf,out);

  out_setansiflag(oldansi);
  fclose(fp);
  fclose(out);
  unix2dos(wallfil,wallfil);
  msg_reset();
  prompt(DLOK);

  return addtodoorid();
}
