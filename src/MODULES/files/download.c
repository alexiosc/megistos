/*****************************************************************************\
 **                                                                         **
 **  FILE:    download.c                                                    **
 **  AUTHORS: Alexios                                                       **
 **  PURPOSE: Download files.                                               **
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
\*****************************************************************************/


/*
 * $Id$
 *
 * $Log$
 * Revision 1.1  2001/04/16 14:55:42  alexios
 * Initial revision
 *
 * Revision 0.3  1999/07/18 21:29:45  alexios
 * Major changes to allow for download rebates, etc.
 *
 * Revision 0.2  1998/12/27 15:40:03  alexios
 * Moved code to filearray.c for brevity. Added autoconf
 * support.
 *
 * Revision 0.1  1998/04/21 10:12:53  alexios
 * Initial revision.
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
#define WANT_FCNTL_H 1
#define WANT_SYS_STAT_H 1
#define WANT_REGEX_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "files.h"
#include "mbk_files.h"


static char *
getfilenames()
{
  static char fn[256];

  for(;;){
    if(morcnc()){
      strcpy(fn,cncword());
      if(!getlibaccess(&library,ACC_DOWNLOAD)){
	prompt(DNLNAX);
	return NULL;
      }
    } else {
      if(!getlibaccess(&library,ACC_DOWNLOAD)){
	prompt(DNLNAX);
	return NULL;
      }
      prompt(DNLASK);
      getinput(sizeof(fn)-1);
      strcpy(fn,input);
    }

    if(isX(fn))return NULL;
    else if(!strlen(fn)){
      endcnc();
      continue;
    } else if(!strcmp(fn,"?")){
      prompt(DNLHLP);
      endcnc();
      continue;
    } else break;
  }

  return fn;
}


void
dodownload()
{
  struct stat st;
  char audit[2][80];
  struct filerec *f;
  char fname[512];
  int  rebate;


  /* Set auditing */

  if(library.flags&LBF_DNLAUD){
    sprintf(audit[0],AUD_FDNLOK,library.fullname);
    sprintf(audit[1],AUD_FDNLERR,library.fullname);
    setaudit(AUT_FDNLOK,AUS_FDNLOK,audit[0],
	     AUT_FDNLERR,AUS_FDNLERR,audit[1]);
  } else setaudit(0,NULL,NULL,0,NULL,NULL);


  /* Remove the rebate file */

  sprintf(fname,REBATELOG,(int)getpid());
  unlink(fname);


  /* Go through the files */

  f=firstfile();
  while(f){

    /* Check existence of file */
    sprintf(fname,"%s/%s",library.dir,f->fname);
    if(stat(fname,&st)){
      prompt(DNLFMS,f->fname);
      f=nextfile();
      continue;
    }

    /* Rebate */
    rebate=(library.rebate * calccharge(st.st_size,&library)) / 100;
    {
      char command[1024];
      struct fileidx file;
      if(fileread(library.libnum,f->fname,1,&file)){
	sprintf(command,"echo %d %s %d %s >>"REBATELOG,
		rebate,file.uploader,library.libnum,f->fname,(int)getpid());
	setcmd(command,NULL);
      }
    }
		     
    /* Register the file for downloading */
    addxfer(FXM_DOWNLOAD,fname,f->summary,library.dnlcharge,-1);

    f=nextfile();
  }

  /* Perform the transfer */

  dofiletransfer();
  killxferlist();
  endcnc();
}


void
postdownload()
{
  FILE *fp;
  char fname[256];

  sprintf(fname,REBATELOG,(int)getpid());
  if((fp=fopen(fname,"r"))==NULL)return; /* No rebates logged */
  
  while(!feof(fp)){
    int rebate, libnum, res;
    char fname[256], user[256];
    struct libidx lib;
    struct fileidx file;

    if(fscanf(fp,"%d %s %d %s %d %*s\n",&rebate,user,&libnum,fname,&res)!=5){
      logerror("Rebate file %s had incorrect format.",fname);
      fclose(fp);
      unlink(fname);
      return;
    }

    /* Post the rebate to the user */
    if(rebate)postcredits(user,rebate,0);

    /* Increase the downloads counter of the file */
    if(libreadnum(libnum,&lib)){
      bzero(&file,sizeof(file));
      if(!fileread(libnum,fname,1,&file)){
	if(!fileread(libnum,fname,0,&file))continue;
      }
      if(!strcmp(file.fname,fname)){
	file.downloaded++;
	fileupdate(&file);
      }
    }
  }

  fclose(fp);
  unlink(fname);
}


void
download(char *fnames)
{
  char *spec;
  int  numfiles=0, charge;

  if(fnames==NULL) for(;;){
    if((spec=getfilenames())==NULL)return;
    
    numfiles=expandspec(spec,0);
    
    if(!numfiles)endcnc();
    else break;
  } else {
    expandspec(fnames,0);
  }

  charge=gettotalcharge();
  if(!canpay(charge)){
    prompt(DNLNCR);
    return;
  } else chargecredits(charge);

  dodownload();

  postdownload();
}
