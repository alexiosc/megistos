/*****************************************************************************\
 **                                                                         **
 **  FILE:     setup.c                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 1997, Version 0.1                                  **
 **  PURPOSE:  Bulletins plugin setup part (not much of it)                 **
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
 * Revision 1.1  2001/04/16 14:57:42  alexios
 * Initial revision
 *
 * Revision 0.5  1999/07/18 21:43:59  alexios
 * Changed a few fatal() calls to fatalsys().
 *
 * Revision 0.4  1998/12/27 15:46:41  alexios
 * Added autoconf support.
 *
 * Revision 0.3  1998/07/24 10:20:15  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:06:59  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 10:53:22  alexios
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
#include <bbsinclude.h>

#include "bbs.h"
#include "offline.bulletins.h"
#include "../../mailer.h"
#include "mbk_offline.bulletins.h"

#define __MAILER_UNAMBIGUOUS__
#include "mbk_mailer.h"

#define __BULLETINS_UNAMBIGUOUS__
#include "mbk_bulletins.h"


struct prefs prefs;


void readprefs(struct prefs *prefs)
{
  if(loadprefs(progname,prefs)!=1){
    bzero(prefs,sizeof(struct prefs));
    prefs->flags=defblt?OBF_INDEX:0;
    if(defansi)prefs->flags|=OBF_ANSI;
    writeprefs(prefs);
  }
}


void writeprefs(struct prefs *prefs)
{
  saveprefs(progname,sizeof(struct prefs),prefs);
}


void
setup()
{
  FILE *fp;
  char fname[256], s[80], *cp;
  int i;

  readprefs(&prefs);

  sprintf(fname,TMPDIR"/mailer%05d",getpid());
  if((fp=fopen(fname,"w"))==NULL){
    logerrorsys("Unable to create data entry file %s",fname);
    return;
  }

  fprintf(fp,"%s\n",prefs.flags&OBF_INDEX?"on":"off");
  fprintf(fp,"%s\n",prefs.flags&OBF_ANSI?"on":"off");
  fprintf(fp,"OK button\nCancel button\n");
  fclose(fp);

  dataentry("offline.bulletins",OBVT,OBLT,fname);

  if((fp=fopen(fname,"r"))==NULL){
    logerrorsys("Unable to read data entry file %s",fname);
    return;
  }

  for(i=0;i<5;i++){
    fgets(s,sizeof(s),fp);
    if((cp=strchr(s,'\n'))!=NULL)*cp=0;
    if(i==0){
      if(sameas("on",s))prefs.flags|=OBF_INDEX;
      else prefs.flags&=~OBF_INDEX;
    }else if(i==1){
      if(sameas("on",s))prefs.flags|=OBF_ANSI;
      else prefs.flags&=~OBF_ANSI;
    }
  }

  fclose(fp);
  unlink(fname);
  if(!sameas(s,"CANCEL"))saveprefs(progname,sizeof(prefs),&prefs);
}
