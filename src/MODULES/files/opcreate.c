/*****************************************************************************\
 **                                                                         **
 **  FILE:     opcreate.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 1997, Version 0.1                               **
 **  PURPOSE:  The CREATE operation                                         **
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
 * Revision 1.1  2001/04/16 14:55:57  alexios
 * Initial revision
 *
 * Revision 0.5  2000/01/06 10:37:25  alexios
 * Modified calls to mklib to reflect new third argument.
 *
 * Revision 0.4  1999/07/18 21:29:45  alexios
 * Changed a few fatal() calls to fatalsys().
 *
 * Revision 0.3  1998/12/27 15:40:03  alexios
 * Added autoconf support.
 *
 * Revision 0.2  1998/07/24 10:18:32  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.1  1998/04/16 09:27:16  alexios
 * Initial version.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif


#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_STRING_H 1
#define WANT_CTYPE_H 1
#define WANT_UNISTD_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_STAT_H 1
#define WANT_FCNTL_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "files.h"
#include "mbk/mbk_files.h"


static int
getnewlibname(char *s)
{
  char *i,c;

  for(;;){
    lastresult=0;
    if((c=morcnc())!=0){
      if(sameas(nxtcmd,"X"))return 0;
      if(sameas(nxtcmd,"?")){
	listsublibs();
	endcnc();
	continue;
      }
      i=cncword();
    } else {
      prompt(OCREASK);
      getinput(0);
      bgncnc();
      i=cncword();
      if (!margc) {
	endcnc();
	continue;
      }
      if(isX(margv[0])){
	return 0;
      }
      if(sameas(margv[0],"?")){
	listsublibs();
	endcnc();
	continue;
      }
    }
    if(strlen(i)>sizeof(library.keyname)-1){
      prompt(OCRE2LN,sizeof(library.keyname)-1);
    } else if(strspn(i,FNAMECHARS)!=strlen(i)){
      prompt(OCRECHR);
    } else break;
  }
  strcpy(s,i);
  return 1;
}


static int
edit(struct libidx *lib)
{
  FILE *fp;
  char fname[256], s[80], *cp;
  int i;

  sprintf(fname,TMPDIR"/files%05d",getpid());
  if((fp=fopen(fname,"w"))==NULL){
    logerrorsys("Unable to create data entry file %s",fname);
    return 0;
  }

  fprintf(fp,"%s\n",lib->descr);
  fprintf(fp,"%s\n",lib->passwd);
  fprintf(fp,"%s\n",lib->club);
  fprintf(fp,"%s\n",lib->dir);
  fprintf(fp,"OK button\nCancel button\n");
  fclose(fp);

  dataentry("files",OCREVT,OCRELT,fname);

  if((fp=fopen(fname,"r"))==NULL){
    logerrorsys("Unable to read data entry file %s",fname);
    return 0;
  }

  for(i=0;i<7;i++){
    fgets(s,sizeof(s),fp);
    if((cp=strchr(s,'\n'))!=NULL)*cp=0;
    if(i==0)strcpy(lib->descr,s);
    else if(i==1)strcpy(lib->passwd,s);
    else if(i==2){
      if(s[0]){
	if(findclub(s))strcpy(lib->club,s);
	else prompt(OCRECNE,s);
      } else bzero(lib->club,sizeof(lib->club));
    } else if(i==3)strcpy(lib->dir,zonkdir(s));
  }

  fclose(fp);
  unlink(fname);
  if(sameas(s,"CANCEL")){
    prompt(OPCAN);
    return 0;
  }
  return 1;
}


void
op_create()
{
  char s[20], tmp[20];
  struct libidx lib;

  if(nesting(library.fullname)>maxnest){
    prompt(OCRENST,maxnest);
    return;
  }

  for(;;){
    if(!getnewlibname(s))return;

    if(libexists(s,library.libnum)){
      prompt(OCREEXS,s);
      endcnc();
      continue;
    } else break;
  }

  memcpy(&lib,&library,sizeof(lib));

  strcpy(lib.keyname,s);
  lowerc(lib.keyname);
  sprintf(lib.fullname,"%s/%s",library.fullname,s);
  sprintf(lib.dir,"%s/%s",library.dir,s);
  lib.descr[0]=0;
  lib.parent=library.libnum;
  lib.numfiles=lib.numbytes=lib.numunapp=lib.bytesunapp=0;
  bzero(lib.uploadsperday,sizeof(lib.uploadsperday));
  bzero(lib.bytesperday,sizeof(lib.bytesperday));
  strcpy(tmp,s);
  if(findclub(tmp))strcpy(lib.club,tmp);

  if(!edit(&lib))return;

  mklib(&lib,0,0);
  prompt(OCREOK,lib.fullname);
  enterlib(lib.libnum,0);
}
