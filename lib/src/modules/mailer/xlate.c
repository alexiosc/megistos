/*****************************************************************************\
 **                                                                         **
 **  FILE:     xlate.c                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 1998, Version 0.1                                  **
 **  PURPOSE:  Off line mailer                                              **
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
 * Revision 0.4  1999/07/18 21:42:47  alexios
 * Changed a few fatal() calls to fatalsys().
 *
 * Revision 0.3  1998/12/27 15:45:11  alexios
 * Added autoconf support.
 *
 * Revision 0.2  1998/08/14 11:31:09  alexios
 * Removed newlines from fatal() calls. Added function
 * unix2dos() to translate files to the DOS newline format.
 *
 * Revision 0.1  1998/08/11 10:10:48  alexios
 * Initial revision.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif


#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_STRING_H 1
#include <bbsinclude.h>

#include <bbs.h>
#include "mailer.h"



char kbdxlation[NUMXLATIONS][256];
char xlation[NUMXLATIONS][256];
int  xlationtable;


void
readxlation()
{
  FILE *fp;
  if((fp=fopen(XLATIONFILE,"r"))==NULL){
    fatalsys("unable to open %s",XLATIONFILE);
  }
  if(fread(xlation,sizeof(xlation),1,fp)!=1){
    fatalsys("unable to read %s",XLATIONFILE);
  }
  if(fread(kbdxlation,sizeof(kbdxlation),1,fp)!=1){
    fatalsys("unable to read %s",XLATIONFILE);
  }
  fclose(fp);
}


void
unix2dos(char *fname, char *target)
{
  char buf [16384];
  FILE *fpi, *fpo;
  char fname2[256];

  if(!strcmp(fname,target))sprintf(fname2,"%s~",fname);
  else strcpy(fname2,target);

  if((fpi=fopen(fname,"r"))==NULL){
    fatalsys("Unable to open %s for DOS conversion",fname);
  }
  if((fpo=fopen(fname2,"w"))==NULL){
    fatalsys("Unable to create %s",fname2);
  }

  do{
    int i;
    if(!fgets(buf,sizeof(buf),fpi))break;
    i=strcspn(buf,"\r\n");
    buf[i]=0;
    xlate_out(buf);
    fputs(buf,fpo);
    fputs("\r\n",fpo);
  }while(!feof(fpi));

  fclose(fpo);
  fclose(fpi);

  if(!strcmp(fname,target))rename(fname2,fname);
}
