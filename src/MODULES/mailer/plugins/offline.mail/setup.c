/*****************************************************************************\
 **                                                                         **
 **  FILE:     setup.c                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1997, Version 0.1                                    **
 **  PURPOSE:  Mail plugin setup part                                       **
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
 * Revision 1.1  2001/04/16 14:57:52  alexios
 * Initial revision
 *
 * Revision 0.5  1999/07/18 21:44:48  alexios
 * Changed a few fatal() calls to fatalsys().
 *
 * Revision 0.4  1998/12/27 15:48:12  alexios
 * Added autoconf support.
 *
 * Revision 0.3  1998/07/24 10:20:56  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:06:43  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 10:55:29  alexios
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
#include "offline.mail.h"
#include "../../mailer.h"
#include "mbk_offline.mail.h"

#define __MAILER_UNAMBIGUOUS__
#include "mbk_mailer.h"


struct prefs prefs;


void readprefs(struct prefs *prefs)
{
  if(loadprefs(progname,prefs)!=1){
    bzero(prefs,sizeof(struct prefs));
    prefs->flags=0;
    if(defhdr)prefs->flags|=OMF_HEADER;
    if(defatt)prefs->flags|=(defatt==1)?OMF_ATTYES:OMF_ATTASK;
    if(defreq)prefs->flags|=(defreq==1)?OMF_REQYES:OMF_REQASK;
    writeprefs(prefs);
  }
}


void writeprefs(struct prefs *prefs)
{
  saveprefs(progname,sizeof(struct prefs),prefs);
}


void
setprefs()
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

  fprintf(fp,"%s\n",getmsg(OMVTN+(prefs.flags&OMF_ATT)));
  fprintf(fp,"%s\n",getmsg(OMVTN+((prefs.flags&OMF_REQ)>>2)));
  fprintf(fp,"%s\n",prefs.flags&OMF_HEADER?"on":"off");
  fprintf(fp,"OK button\nCancel button\n");
  fclose(fp);

  dataentry("offline.mail",OMVT,OMLT,fname);

  if((fp=fopen(fname,"r"))==NULL){
    logerrorsys("Unable to read data entry file %s",fname);
    return;
  }

  for(i=0;i<6;i++){
    fgets(s,sizeof(s),fp);
    if((cp=strchr(s,'\n'))!=NULL)*cp=0;
    if(i==0){
      int i,j=-1;
      for(i=0;i<3;i++)if(sameas(getmsg(OMVTN+i),s)){
	j=i;
	break;
      }
      if(j<0){
	fatal("Bad value \"%s\" for attachment inclusion.",s);
      }
      prefs.flags&=~OMF_ATT;
      if(j)prefs.flags|=j==1?OMF_ATTYES:OMF_ATTASK;
    } else if(i==1){
      int i,j=-1;
      for(i=0;i<3;i++)if(sameas(getmsg(OMVTN+i),s)){
	j=i;
	break;
      }
      if(j<0){
	fatal("Bad value \"%s\" for request inclusion.",s);
      }
      prefs.flags&=~OMF_REQ;
      if(j)prefs.flags|=j==1?OMF_REQYES:OMF_REQASK;
    } else if(i==2){
      if(sameas("on",s))prefs.flags|=OMF_HEADER;
      else prefs.flags&=~OMF_HEADER;
    }
  }

  fclose(fp);
  unlink(fname);
  if(sameas(s,"CANCEL")){
    prompt(OMSCAN);
    return;
  } else {
    saveprefs(progname,sizeof(prefs),&prefs);
    prompt(OMSOK);
  }
}


void
setup()
{
  int shownmenu=0;
  char c;

  for(;;){
    thisuseronl.flags&=~OLF_BUSY;
    if(!(thisuseronl.flags&OLF_MMCALLING && thisuseronl.input[0])){
      if(!shownmenu){
	prompt(OMMENU);
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
	  prompt(OMSHORT);
	} else shownmenu=1;
	getinput(0);
	bgncnc();
      }
    }

    if((c=morcnc())!=0){
      cncchr();
      switch (c) {
      case 'S':
	setprefs();
	break;
      case 'C':
	setqsc();
	break;
      case 'X':
	return;
      case '?':
	shownmenu=0;
	break;
      default:
	prompt(OMERR,c);
	endcnc();
	continue;
      }
    }
    if(lastresult==PAUSE_QUIT)resetvpos(0);
    endcnc();
  }
}
