/*****************************************************************************\
 **                                                                         **
 **  FILE:     upload.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 1997, Version 0.1                                  **
 **  PURPOSE:  Off line mailer, uploading packets                           **
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
 * Revision 0.9  1999/07/18 21:42:47  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 0.8  1998/12/27 15:45:11  alexios
 * Added autoconf support.
 *
 * Revision 0.7  1998/08/14 11:31:09  alexios
 * No changes.
 *
 * Revision 0.6  1998/08/11 10:11:15  alexios
 * Migrated file transfer calls to new format.
 *
 * Revision 0.5  1998/07/24 10:19:54  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.4  1997/12/02 20:45:35  alexios
 * Switched to using the archiver file instead of locally
 * defined compression/decompression programs.
 *
 * Revision 0.3  1997/11/06 20:06:32  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/11/06 16:55:18  alexios
 * Changed calls to setaudit() to use the new auditing scheme.
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
#define WANT_DIRENT_H 1
#define WANT_SYS_STAT_H 1
#define WANT_FCNTL_H 1
#define WANT_TIME_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "mailer.h"
#include "mbk_mailer.h"
#define __ARCHIVERS_UNAMBIGUOUS__
#include "mbk_archivers.h"


static char dir[256];


static void
killdir()
{
  char command[256];
  sprintf(command,"rm -rf %s",dir);
  system(command);
  xfer_kill_list();
}


static int
receivefile()
{
  char fname[256], *cp, name[256], source[256];
  FILE *fp;
  int  count=-1;


  /* Upload the file */
  
  xfer_setaudit(AUT_QWKUPL,AUS_QWKUPL,AUD_QWKUPL,0,NULL,NULL);
  sprintf(source,"%s.rep",thisuseracc.userid);
  xfer_add(FXM_UPLOAD,source,"",0,0);
  xfer_run();
  cnc_end();


  /* Scan the uploaded file(s) */
  
  sprintf(fname,XFERLIST,getpid());
  
  if((fp=fopen(fname,"r"))==NULL){
    prompt(ABORT);
    unlink(fname);
    killdir();
    return 0;
  }
  
  while (!feof(fp)){
    char line[1024];
    
    if(fgets(line,sizeof(line),fp)){
      count++;
      if(!count)strcpy(dir,line);
      else if(count==1)strcpy(name,line);
    }
  }
  
  if((cp=strchr(dir,'\n'))!=NULL)*cp=0;
  if((cp=strchr(name,'\n'))!=NULL)*cp=0;
  fclose(fp);
  unlink(fname);
  
  if(count<1){
    prompt(ABORT);
    killdir();
    return 0;
  } else if(count>1){
    prompt(UPL2MF);
    return 2;
  } else prompt(UPL1F);
  return 1;
}


static void
makedir()
{
  char command[256];

  /* Make a unique directory and chdir() to it */

  sprintf(dir,TMPDIR"/rep.%lx%x",time(0),getpid());
  sprintf(command,"\\rm -rf %s",dir);
  system(command);
  if(mkdir(dir,0770)){
    error_fatalsys("Unable to make directory %s",dir);
  }
  chdir(dir);
}


static int
uplsel(const struct dirent *d)
{
  return d->d_name[0]!='.';
}


static int
askdupl()
{
  int shown=0, yes=0, res;
  for(;;){
    if(!shown)prompt(WRNDUPL);
    inp_setflags(INF_HELP);
    res=get_bool(&yes,ASKDUPL,ASKDUPR,ASKDUPD,0);
    inp_clearflags(INF_HELP);
    if(res<0)shown=0;
    else if(!res)prompt(ASKDUPR);
    else return yes;
  }
}


static int
chkcrc(char *fname)
{
  unsigned long crc;
  int len, i, add=1;

  /* Obtain CRC32 of the file to see if it's already been uploaded */

  if(cksum(fname,&crc,&len)){
    prompt(REPRPRE);
    return 0;
  }

  for(i=0;i<NUMOLDREP;i++){
    if(userqwk.oldcrc[i]==crc && userqwk.oldlen[i]==len){
      if(!askdupl()) return 0;
      else add=0;
    }
  }

  /* If necessary, store the new CRC for later */

  if(add){
    memcpy(&(userqwk.oldcrc[1]),&(userqwk.oldcrc[0]),
	   sizeof(userqwk.oldcrc[0]*(NUMOLDREP-1)));
    userqwk.oldcrc[NUMOLDREP-1]=crc;
    
    memcpy(&(userqwk.oldlen[1]),&(userqwk.oldlen[0]),
	   sizeof(userqwk.oldlen[0]*(NUMOLDREP-1)));
    userqwk.oldlen[NUMOLDREP-1]=len;
  }
  return 1;
}


static int
decompress(char *fname)
{
  char command[256], tmp[256];

  /* Decompress the packet */

  msg_set(archivers);
  sprintf(tmp,"%s >&/dev/null",msg_get(ARCHIVERS_UNCOMPRESS1+userqwk.decompressor*7));
  sprintf(command,tmp,fname,"");
  strcpy(tmp,msg_get(ARCHIVERS_NAME1+userqwk.decompressor*7));
  msg_reset();
  prompt(UNPACK,tmp);
  if(system(command)){
    prompt(UPACKR);
    return 0;
  }
  prompt(UPACKOK);
  

  /* Erase the packet itself */

  unlink(fname);

  return 1;
}


static int
pluginupl(int n, int reqman)
{
  char command[256];
  int res;
  sprintf(command,"%s --%s",plugins[n].name,reqman?"reqman":"upload");
  res=runcommand(command);
  cnc_end();
  if(res)return res==512?2:1;
  return 0;
}


static int
process(char *name)
{
  char fname[256];
  int ok;

  sprintf(fname,"%s/%s",dir,name);

  /* Prepare the packet */

  makedir();
  ok=chkcrc(fname);
  if(ok)ok=decompress(fname);

  /* Run all plugins to process the packet */

  if(ok){
    int fail=0, i;
    for(fail=i=0;i<numplugins;i++){
      if(plugins[i].flags&PLF_UPLOAD)if((fail=pluginupl(i,0))!=0)break;
    }

    if(fail){
      prompt(fail==1?ERRREP:ABOREP);
      ok=0;
    } else for(fail=i=0;i<numplugins;i++){
      if(plugins[i].flags&PLF_REQMAN)if((fail=pluginupl(i,1))!=0)break;
    }
  }

  if(ok)return 1;

  unlink(fname);
  return 0;
}


void
upload()
{
  struct dirent **d=NULL;
  int i,j,res=1;

  /* Are we allowed to upload? */

  if(!key_owns(&thisuseracc,uplkey)){
    prompt(UPLNAX);
    cnc_end();
    return;
  }

  /* Load the user preferences, complain if we have to */

  if(loadprefs(USERQWK,&userqwk)!=1){
    prompt(stpncnf?NOTCFG2:NOTCFG);
    if(stpncnf)return;
    else defaultvals();
  }

  /* Allow the user to upload file(s) */

  if(!receivefile())return;

  /* Scan through all the files, processing them */

  j=scandir(dir,&d,uplsel,alphasort);
  if(!j){
    if(d)free(d);
    return;
  }

  for(i=0;i<j;i++){
    if(res){
      if(j>1)prompt(REPF,i+1,j);
      res=process(d[i]->d_name);
    }
    free(d[i]);
  }
  
  free(d);
  chdir("/");
  killdir();
  saveprefs(USERQWK,sizeof(userqwk),&userqwk);
}
