/*****************************************************************************\
 **                                                                         **
 **  FILE:     protocols.c                                                  **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 94, Version 0.5 alpha                           **
 **  PURPOSE:  Extra 'protocols' for the file transfer module               **
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
 * Revision 1.2  2001/04/16 21:56:34  alexios
 * Completed 0.99.2 API, dragged all source code to that level (not as easy as
 * it sounds).
 *
 * Revision 0.5  1999/07/18 22:09:33  alexios
 * Changed a few error_fatal() calls to error_fatalsys(). Minor bug fixes.
 *
 * Revision 0.4  1998/12/27 16:34:28  alexios
 * Added autoconf support.
 *
 * Revision 0.3  1998/07/24 10:31:31  alexios
 * Moved to stable status. Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:18:32  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 11:25:42  alexios
 * First registered revision. Adequate.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
const char *__RCS=RCS_VER;
#endif




#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_CTYPE_H 1
#define WANT_UNISTD_H 1
#define WANT_TIME_H 1
#define WANT_STRING_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include <math.h>
#include "bbs.h"
#include "updown.h"
#include "mbk_updown.h"


char filetype[256];
long filesize;
long xfertime;


void
getfiletype(char *fname,int recurse)
{
  FILE *fp;
  char command[256], line[1024], *cp=line;

  strcpy(filetype,msg_get(FTUNK));
  if(!recurse)return;

  sprintf(command,"file %s",fname);
  if((fp=popen(command,"r"))==NULL) return;
  line[0]=0;
  fgets(line,sizeof(line),fp);
  fclose(fp);

  if((cp=strchr(line,10))!=NULL)*cp=0;
  if((cp=strchr(line,13))!=NULL)*cp=0;
  if(!line[0]) return;

  if((cp=strchr(line,32))==NULL)return;
  else cp++;
  if(sameto(SYMLINKTO,cp)){
    cp+=strlen(SYMLINKTO);
    getfiletype(cp,recurse-1);
  } else strcpy(filetype,cp);
  filetype[60]=0;
}


void
getfilesize()
{
  int i;
  struct stat st;

  filesize=0L;
  for(i=0;i<totalitems;i++){
    if((xferlist[i].flags&(XFF_TAGGED+XFF_KILLED))==0 ||
       ((xfertagged||logout)&&(xferlist[i].flags&XFF_KILLED)==0)){
      if(!xferlist[i].size){
	if(!stat(xferlist[i].fullname,&st)){
	  filesize+=(xferlist[i].size=st.st_size);
	}
      } else filesize+=xferlist[i].size;
    } else if((xferlist[i].flags&XFF_KILLED)==0){
      if(!xferlist[i].size)if(!stat(xferlist[i].fullname,&st)){
	xferlist[i].size=st.st_size;
      }
    }
  }


  /* Time in minutes = Size / ((bps/10) * protocol efficiency * 60) */

  xfertime=(int)
    (rint(((double)filesize) /
	   ((((double)(thisuseronl.baudrate?thisuseronl.baudrate:38400)/10.0)*
	    (((double)peffic/100.0))) * 60.0)));
}


void
extraprotocols()
{
  getfilesize();
  if(xferlist[firstentry].dir==FXM_DOWNLOAD ||
     xferlist[firstentry].dir==FXM_TRANSIENT){
    if(NUMFILES==1){
      getfiletype(xferlist[firstentry].fullname,MAXRECURSE);
      if(filesize<0){
	prompt(FNOTFND,xferlist[firstentry].filename);
	exit(1);
      } else {
	int i;
	
	for(i=0;i<numviewers;i++){
	  if(strstr(filetype,viewers[i].string)==filetype){
	    struct protocol prot;
	    
	    sprintf(prot.name,msg_get(VIEWNAME),viewers[i].type);
	    strcpy(prot.select,vprsel);
	    strcpy(prot.command,viewers[i].command);
	    prot.flags=PRF_NEEDN|PRF_VIEWER;
	    
	    numprotocols++;
	    protocols=realloc(protocols,sizeof(struct protocol)*numprotocols);
	    if(!protocols){
	      error_fatal("Unable to allocate memory for the protocol"\
		    "table",NULL);
	    } else {
	      memcpy(&protocols[numprotocols-1],&prot,sizeof(struct protocol));
	      memset(&prot,0,sizeof(prot));
	      strcpy(prot.stopkey,"Ctrl-C");
	      prot.flags=PRF_NEEDN;
	    }
	  }
	}
      }
    }
  } else {
    if(key_owns(&thisuseracc,lnkkey)){
      struct protocol prot;

      sprintf(prot.name,msg_get(LNKNAM));
      strcpy(prot.select,lnksel);
      strcpy(prot.command,"");
      prot.flags=PRF_UPLOAD|PRF_LINK;
      
      numprotocols++;
      protocols=realloc(protocols,sizeof(struct protocol)*numprotocols);
      if(!protocols){
	error_fatal("Unable to allocate memory for the protocol"\
	      "table",NULL);
      } else {
	memcpy(&protocols[numprotocols-1],&prot,sizeof(struct protocol));
	memset(&prot,0,sizeof(prot));
      }
    }
  }
}
