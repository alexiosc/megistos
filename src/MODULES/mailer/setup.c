/*****************************************************************************\
 **                                                                         **
 **  FILE:     setup.c                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1997, Version 0.1                                    **
 **  PURPOSE:  Setup preferences etc                                        **
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
 * Revision 1.1  2001/04/16 14:57:39  alexios
 * Initial revision
 *
 * Revision 0.8  1999/07/18 21:42:47  alexios
 * Changed a few fatal() calls to fatalsys().
 *
 * Revision 0.7  1998/12/27 15:45:11  alexios
 * Added autoconf support.
 *
 * Revision 0.6  1998/08/14 11:31:09  alexios
 * No changes.
 *
 * Revision 0.5  1998/08/11 10:11:15  alexios
 * Added code to setup translation for users.
 *
 * Revision 0.4  1998/07/24 10:19:54  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.3  1997/12/02 20:45:35  alexios
 * Switched to using the archiver file instead of locally
 * defined compression/decompression programs.
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
#define __ARCHIVERS_UNAMBIGUOUS__
#include "mbk_archivers.h"


#define NUMSEL MAXPLUGINS

const static char sel[NUMSEL]="1234567890ABCDEFGHIJKLMNOPQRTUVWYZ";


static void
showsetupmenu()
{
  char pad[256];
  int i;

  prompt(SETUPH);

  for(i=0;i<254;i+=2)pad[i]='.',pad[i+1]=' ';
  pad[255]=0;

  for(i=0;i<numplugins;i++){
    char line[256];
    if(!(plugins[i].flags&PLF_SETUP))continue;
    strcpy(line,&pad[i%2]);
    strcpy(&line[67-strlen(plugins[i].descr[thisuseracc.language-1])],
	   plugins[i].descr[thisuseracc.language-1]);
    line[66-strlen(plugins[i].descr[thisuseracc.language-1])]=32;
    prompt(SETUPPL,sel[i],line);
  }

  prompt(SETUPF);
}


static int
setupmenu()
{
  int shownmenu=0;
  char c;
  char options[NUMSEL];

  strcpy(options,sel);
  options[numplugins]=0;

  for(;;){
    lastresult=0;
    if((c=morcnc())!=0){
      if(sameas(nxtcmd,"X"))return 0;
      c=cncchr();
      shownmenu=1;
    } else {
      if(!shownmenu)showsetupmenu();
      else prompt(SETUPSH);
      shownmenu=1;
      getinput(0);
      bgncnc();
      if(nxtcmd)c=cncchr();
    }
    if (!margc) {
      endcnc();
      continue;
    }
    if(isX(margv[0])){
      return 0;
    } else if(margc && (c=='?'||sameas(margv[0],"?"))){
      shownmenu=0;
      continue;
    } else if(strchr(options,c)||c=='S')return c;
    else {
      prompt(ERRSEL,c);
      endcnc();
      continue;
    }
  }
  return 0;
}


void
defaultvals()
{
  userqwk.compressor=0;
  userqwk.decompressor=0;
  if(defgrk)userqwk.flags|=USQ_GREEKQWK;
  strcpy(userqwk.packetname,bbsid);
  saveprefs(USERQWK,sizeof(userqwk),&userqwk);
}


void
setupqwk()
{
  FILE *fp;
  char fname[256], s[80], *cp;
  int i;

  if(loadprefs(USERQWK,&userqwk)!=1){
    defaultvals();
  }

  sprintf(fname,TMPDIR"/mailer%05d",getpid());
  if((fp=fopen(fname,"w"))==NULL){
    logerrorsys("Unable to create data entry file %s",fname);
    return;
  }

  setmbk(archivers);
  fprintf(fp,"%s\n",getmsg(ARCHIVERS_NAME1+userqwk.compressor*7));
  fprintf(fp,"%s\n",getmsg(ARCHIVERS_NAME1+userqwk.decompressor*2));
  rstmbk();
  fprintf(fp,"%s\n",userqwk.flags&USQ_GREEKQWK?"on":"off");
  fprintf(fp,"%s\n",userqwk.packetname);
  fprintf(fp,"%s\n",getmsg(TR0+((userqwk.flags&OMF_TR)>>OMF_SHIFT)));
  fprintf(fp,"OK button\nCancel button\n");
  fclose(fp);

  dataentry("mailer",QWKVT,QWKLT,fname);

  if((fp=fopen(fname,"r"))==NULL){
    logerrorsys("Unable to read data entry file %s",fname);
    return;
  }

  setmbk(archivers);
  for(i=0;i<8;i++){
    fgets(s,sizeof(s),fp);
    if((cp=strchr(s,'\n'))!=NULL)*cp=0;
    if(i==0){
      int i;
      userqwk.compressor=-1;
      for(i=0;i<MAXARCHIVERS;i++)if(sameas(getmsg(ARCHIVERS_NAME1+i*7),s)){
	userqwk.compressor=i;
	break;
      }
      if(userqwk.compressor<0){
	fatal("Bad value \"%s\" for compressor.",s);
      }
    } else if(i==1){
      int i;
      userqwk.decompressor=-1;
      for(i=0;i<MAXARCHIVERS;i++)if(sameas(getmsg(ARCHIVERS_NAME1+i*7),s)){
	userqwk.decompressor=i;
	break;
      }
      if(userqwk.decompressor<0){
	fatal("Bad value \"%s\" for decompressor.",s);
      }
    } else if(i==2){
      if(sameas("on",s))userqwk.flags|=USQ_GREEKQWK;
      else userqwk.flags&=~USQ_GREEKQWK;
    } else if(i==3){
      strcpy(userqwk.packetname,stripspace(s));
    } else if(i==4){
      int n;
      setmbk(mailer_msg);
      for(n=0;n<NUMXLATIONS;n++){
	if(sameas(s,getmsg(TR0+n))){
	  userqwk.flags&=~OMF_TR;
	  userqwk.flags|=n<<OMF_SHIFT;
	  break;
	}
      }
    }
  }
  setmbk(mailer_msg);

  fclose(fp);
  unlink(fname);
  if(sameas(s,"CANCEL")){
    prompt(SETUPAB);
    return;
  } else {
    saveprefs(USERQWK,sizeof(userqwk),&userqwk);
    prompt(SETUPOK);
  }
}


static void
pluginsetup(int n)
{
  char command[256];
  sprintf(command,"%s -setup",plugins[n].name);
  runmodule(command);
  endcnc();
}


void
setup()
{
  char c, *cp;
  for(;;)
    switch(c=setupmenu()){
    case 0:
      return;
    case 'S':
      setupqwk();
      break;
    default:
      if((cp=strchr(sel,c))==NULL)continue;
      pluginsetup((int)(cp-sel));
    }
}
