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
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.5  1999/07/18 21:44:48  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
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
const char *__RCS=RCS_VER;
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
  int i;

  readprefs(&prefs);

  strcpy(inp_buffer,msg_get(OMVTN+(prefs.flags&OMF_ATT)));
  strcat(inp_buffer,"\n");
  strcat(inp_buffer,msg_get(OMVTN+((prefs.flags&OMF_REQ)>>2)));
  strcat(inp_buffer,"\n");
  strcat(inp_buffer,prefs.flags&OMF_HEADER?"on":"off");
  strcat(inp_buffer,"\nOK\nCANCEL\n");
  
  if(dialog_run("offline.mail",OMVT,OMLT,inp_buffer,MAXINPLEN)!=0){
    error_log("Unable to run data entry subsystem");
    return;
  }

  dialog_parse(inp_buffer);

  if(sameas(margv[5],"OK")||sameas(margv[5],margv[3])){
    for(i=0;i<6;i++){
      char *s=margv[i];

      if(i==0){
	int i,j=-1;
	for(i=0;i<3;i++)if(sameas(msg_get(OMVTN+i),s)){
	  j=i;
	  break;
	}
	if(j<0){
	  error_fatal("Bad value \"%s\" for attachment inclusion.",s);
	}
	prefs.flags&=~OMF_ATT;
	if(j)prefs.flags|=j==1?OMF_ATTYES:OMF_ATTASK;
      } else if(i==1){
	int i,j=-1;
	for(i=0;i<3;i++)if(sameas(msg_get(OMVTN+i),s)){
	  j=i;
	  break;
	}
	if(j<0){
	  error_fatal("Bad value \"%s\" for request inclusion.",s);
	}
	prefs.flags&=~OMF_REQ;
	if(j)prefs.flags|=j==1?OMF_REQYES:OMF_REQASK;
      } else if(i==2){
	if(sameas("on",s))prefs.flags|=OMF_HEADER;
	else prefs.flags&=~OMF_HEADER;
      }
    }

    saveprefs(progname,sizeof(prefs),&prefs);
    prompt(OMSOK);
  } else {
    prompt(OMSCAN);
    return;
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
      if(!cnc_nxtcmd){
	if(thisuseronl.flags&OLF_MMCONCAT){
	  thisuseronl.flags&=~OLF_MMCONCAT;
	  return;
	}
	if(shownmenu==1){
	  prompt(OMSHORT);
	} else shownmenu=1;
	inp_get(0);
	cnc_begin();
      }
    }

    if((c=cnc_more())!=0){
      cnc_chr();
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
	cnc_end();
	continue;
      }
    }
    if(fmt_lastresult==PAUSE_QUIT)fmt_resetvpos(0);
    cnc_end();
  }
}
