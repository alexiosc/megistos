/*****************************************************************************\
 **                                                                         **
 **  FILE:     download.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1997, Version 0.1                                    **
 **  PURPOSE:  Download QWK packets                                         **
 **  NOTES:    Invokes all plugins and compresses the resulting files.      **
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
 * Revision 0.10  1999/07/18 21:42:47  alexios
 * Changed a few error_fatal() calls to error_fatalsys(). Made QWK packets
 * transient wrt file transfers.
 *
 * Revision 0.9  1998/12/27 15:45:11  alexios
 * Added autoconf support. Added GREEKQWK keyword to DOOR.ID,
 * to notify the client of the message format in the file.
 *
 * Revision 0.8  1998/08/14 11:31:09  alexios
 * DOSsified output to files so that braindead DOS-based OLRs
 * can still read text without falling over.
 *
 * Revision 0.7  1998/08/11 10:11:15  alexios
 * Migrated file transfer calls to new format.
 *
 * Revision 0.6  1998/07/24 10:19:54  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.5  1997/12/02 20:45:35  alexios
 * Switched to using the archiver file instead of locally
 * defined compression/decompression programs.
 *
 * Revision 0.4  1997/11/06 20:06:32  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.3  1997/11/06 16:55:18  alexios
 * Changed calls to setaudit() to use the new auditing scheme.
 *
 * Revision 0.2  1997/11/03 00:42:29  alexios
 * Fixed possible bug with use of ctlname as a string instead
 * of an array of strings.
 *
 * Revision 0.1  1997/08/28 10:42:54  alexios
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
#define WANT_DIRENT_H 1
#define WANT_TIME_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "systemversion.h"
#include "mailer.h"
#include "mbk_mailer.h"
#define __ARCHIVERS_UNAMBIGUOUS__
#include "mbk_archivers.h"


static int
plugindnl(int n)
{
  char command[256];
  int res;
  sprintf(command,"%s --download",plugins[n].name);
  res=runcommand(command);
  cnc_end();
  if(res)return res==512?2:1;
  return 0;
}


static int
mkfiles(char *dir)
{
  FILE *fp;
  char fname[256];

  sprintf(fname,"%s/door.id",dir);
  if((fp=fopen(fname,"w"))==NULL){
    prompt(ERRQWK);
    fclose(fp);
    return 0;
  }
  fprintf(fp,"DOOR = MegistosMail\r\n");
  fprintf(fp,"VERSION = %s\r\n",VERSION);
  fprintf(fp,"SYSTEM = %s\r\n",bbs_systemversion);
  fprintf(fp,"CONTROLNAME = %s\r\n",ctlname[0]);
  fprintf(fp,"MIXEDCASE = YES\r\n");
  if(userqwk.flags&USQ_GREEKQWK)fprintf(fp,"GREEKQWK\r\n");
  fclose(fp);

  return 1;
}


static int filesel(const struct dirent *d)
{
  return d->d_name[0]!='.';
}


static void
copyfiles(char *dir)
{
  struct dirent **d=NULL;
  int i,j=scandir(MAILERFILESDIR,&d,filesel,alphasort);
  for(i=0;i<j;i++){
    char fname1[256], fname2[256];
    sprintf(fname1,"%s/%s",MAILERFILESDIR,d[i]->d_name);
    sprintf(fname2,"%s/%s",dir,d[i]->d_name);
    unix2dos(fname1,fname2);
    free(d[i]);
  }
  if(d!=NULL)free(d);
}


static int
compress(char *packetname,char *dir)
{
  char command[256];
  char fname[256];
  char tmp[256];

  /* Now compress the packet */

  msg_set(archivers);
  sprintf(tmp,"%s >&/dev/null",msg_get(ARCHIVERS_COMPRESS1+userqwk.compressor*7));
  sprintf(command,tmp,packetname,"*");
  strcpy(tmp,msg_get(ARCHIVERS_NAME1+userqwk.compressor*7));
  msg_reset();
  prompt(PACKING,tmp);
  if(system(command)){
    prompt(PACKERR);
    return 0;
  }
  prompt(PACKOK);
  

  /* Erase all the other files */

  sprintf(fname,"%s/.tmp",dir);
  rename(packetname,fname);
  sprintf(command,"\\rm -rf %s/*",dir);
  system(command);
  rename(fname,packetname);
  
  return 1;
}


static int offer(char *fname,char *dir)
{
  struct stat st;
  char descr[256];
  char audit[2][80];

  if(stat(fname,&st)){
    prompt(ERRQWK);
    return 0;
  }


  /* Set the description */

  sprintf(descr,msg_get(QWKDESC));


  /* Set the audit messages */

  strcpy(audit[0],AUS_QWKDNL);
  sprintf(audit[1],AUD_QWKDNL,thisuseracc.userid,(int)st.st_size);
  xfer_setaudit(AUT_QWKDNL,audit[0],audit[1],0,NULL,NULL);


  /* Register the file for downloading */

  xfer_add(FXM_TRANSIENT,fname,descr,chgdnl,-1);


  /* Perform the transfer */

  xfer_run();
  xfer_kill_list();
  cnc_end();
  return 1;
}


void
download()
{
  int i, fail;
  char dir[256], command[256];

  if(!usr_canpay(chgdnl)){
    prompt(DNLNCRD);
    return;
  }

  if(loadprefs(USERQWK,&userqwk)!=1){
    prompt(stpncnf?NOTCFG2:NOTCFG);
    if(stpncnf)return;
    else defaultvals();
  }

  readxlation();
  xlationtable=(userqwk.flags&OMF_TR)>>OMF_SHIFT;

  prompt(BEGINQWK,userqwk.packetname);


  /* Make the directory and cd to it */

  sprintf(dir,TMPDIR"/mailer.%lx%x",time(0),getpid());
  sprintf(command,"\\rm -rf %s",dir);
  system(command);
  if(mkdir(dir,0770)){
    error_fatalsys("Unable to make directory %s",dir);
  }
  chdir(dir);
  
  
  /* Create any general purpose files, like DOOR.ID */

  if(!mkfiles(dir))goto kill;

  /* Run all plugins */

  for(fail=i=0;i<numplugins;i++){
    if(plugins[i].flags&PLF_DOWNLOAD)if((fail=plugindnl(i))!=0)break;
  }

  if(fail){
    prompt(fail==1?ERRQWK:ABOQWK);
    goto kill;
  } else {

    /* Produce the packet's filename */

    char fname[64], *s=userqwk.packetname;
    for(i=0;s[i];i++)s[i]=qwkuc?toupper(s[i]):tolower(s[i]);
    sprintf(fname,"%s/%s.%s",dir,s,qwkuc?"QWK":"qwk");

    /* Copy any mandatory files to the temporary directory */

    copyfiles(dir);

    /* Compress the packet */

    if(!compress(fname,dir))goto kill;

    /* Charge the user */

    usr_chargecredits(chgdnl);

    /* Offer it for download */

    if(!offer(fname,dir))goto kill;
  }

  chdir("/");
  return;

  /* Delete the directory */

kill:
  chdir("/");
  if(system(command)){
    error_fatal("Unable to rm -rf directory %s",dir);
  }
}
