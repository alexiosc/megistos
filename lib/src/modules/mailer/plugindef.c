/*****************************************************************************\
 **                                                                         **
 **  FILE:     plugindef.c                                                  **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1997, Version 0.1                                    **
 **  PURPOSE:  Handle the plugin definition file                            **
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
 * Revision 0.6  1999/07/18 21:42:47  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 0.5  1998/12/27 15:45:11  alexios
 * Added autoconf support.
 *
 * Revision 0.4  1998/08/14 11:31:09  alexios
 * No changes.
 *
 * Revision 0.3  1998/07/24 10:19:54  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:06:32  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 10:51:40  alexios
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
#include <bbsinclude.h>

#include "bbs.h"
#include "mailer.h"
#include "mbk_mailer.h"


struct plugin *plugins=NULL;
int            numplugins=0;


void
parseplugindef()
{
  FILE *fp;
  struct plugin p;
  int d=0, lines=0;

  if(plugins)free(plugins);
  numplugins=0;
  bzero(&p,sizeof(p));

  if((fp=fopen(PLUGINDEFFILE,"r"))==NULL){
    error_fatalsys("Unable to open %s for reading.",PLUGINDEFFILE);
  }

  while(!feof(fp)){
    char line[1024], *cp, keyword[256];
    int n;

    if(!fgets(line,sizeof(line),fp))break;
    lines++;

    if((cp=strrchr(line,'\n'))!=NULL)*cp=0;
    for(cp=line;*cp&&isspace(*cp);cp++);
    if(*cp=='#'||*cp==0)continue;

    if(!sscanf(cp,"%s %n",keyword,&n))continue;

    for(cp=&line[n];*cp&&isspace(*cp);cp++);

    if(sameas(keyword,"plugin")){
      strncpy(p.name,cp,NAMELEN);
      p.name[NAMELEN-1]=0;
    } else if(sameas(keyword,"descr")){
      if(d>=NUMLANGUAGES){
	error_fatal("Too many 'descr' keywords in %s line %d",
	      PLUGINDEFFILE,lines);
      }
      strncpy(p.descr[d],cp,DESCRLEN);
      p.descr[d++][DESCRLEN-1]=0;
    } else if(sameas(keyword,"flags")){
      for(;*cp;cp++){
	if(isspace(*cp))continue;
	switch(toupper(*cp)){
	case 'S':
	  p.flags|=PLF_SETUP;
	  break;
	case 'U':
	  p.flags|=PLF_UPLOAD;
	  break;
	case 'D':
	  p.flags|=PLF_DOWNLOAD;
	  break;
	case 'R':
	  p.flags|=PLF_REQMAN;
	  break;
	default:
	  error_fatal("Bad flag %c in %s line %d",
		*cp,PLUGINDEFFILE,lines);
	}
      }
    } else if(sameas(keyword,"end")){
      int i;
      struct plugin *pp=alcmem(sizeof(struct plugin)*++numplugins);

      if(numplugins>=MAXPLUGINS){
	error_fatal("Exceeded maximum of %d plugins.",MAXPLUGINS);
      }

      if(numplugins>1){
	memcpy(pp,plugins,sizeof(struct plugin)*(numplugins-1));
	free(plugins);
      }
      plugins=pp;
      for(i=1;i<NUMLANGUAGES;i++)if(!p.descr[i])strcpy(p.descr[i],p.descr[i-1]);
      memcpy(&plugins[numplugins-1],&p,sizeof(struct plugin));
      bzero(&p,sizeof(p));
      d=0;
    } else error_fatal("Unrecognised keyword %s in %s line %d.",
		 keyword,PLUGINDEFFILE,lines);
  }

  fclose(fp);
}
