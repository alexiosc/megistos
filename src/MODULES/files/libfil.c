/*****************************************************************************\
 **                                                                         **
 **  FILE:     libfil.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  PURPOSE:  Convert MBBS 5.31 file DATabases to Megistos format.         **
 **  NOTES:    This is NOT guarranteed to work on anything but MajorBBS     **
 **            version 5.31, for which it was written.                      **
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
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.2  1998/12/27 15:40:03  alexios
 * Added autoconf support.
 *
 * Revision 0.1  1998/04/16 09:27:16  alexios
 * Initial version.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
const char *__RCS=RCS_VER;
#endif



#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_FCNTL_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include <endian.h>
#include <typhoon.h>
#include "bbs.h"
#include "config.h"
#include "cnvutils.h"
#include "files.h"


void
libfil(char *arg_majordir)
{
  FILE            *fp;
  char            rec[16384], c, *fname=rec;
  int             reclen;
  int             num=0;
  char            tmp[10];
  struct libidx   lib;
  struct fileidx  *file;

  bzero(&lib,sizeof(lib));

  sprintf(fname,"%s/libfil.txt",arg_majordir?arg_majordir:".");
  fp=fopen(fname,"r");
  if(fp==NULL){
    sprintf(fname,"%s/LIBFIL.TXT",arg_majordir?arg_majordir:".");
    if((fp=fopen(fname,"r"))==NULL){
      fprintf(stderr,"libcnv: libfil(): unable to find libfil.txt or LIBFIL.TXT.\n");
      exit(1);
    }
  }

  printf("\nInstalling Files... "); fflush(stdout);

  file=alcmem(sizeof(struct fileidx));

  while(!feof(fp)){
    if(fscanf(fp,"%d\n",&reclen)==0){
      if(feof(fp))break;
      fprintf(stderr,"libcnv: libfil(): unable to parse record length. Corrupted file?\n");
      exit(1);
    }
    if(feof(fp))break;
    fgetc(fp);			/* Get rid of the comma after the record length */

    if(fread(rec,reclen,1,fp)!=1){
      fprintf(stderr,"libcnv: libfil(): unable to read record around pos=%ld.\n",ftell(fp));
      exit(1);
    }

    bzero(file,sizeof(struct fileidx));
    
    /* Filename */
    strcpy(file->fname,lcase(&rec[10]));

    /* Skip Major-generated files: index., files., topfiles. */
    if(!strcmp(file->fname,"index.")||
       !strcmp(file->fname,"files.")||
       !strcmp(file->fname,"topfiles."))continue;
    
    /* Library number (Major keeps string references to libraries) */
    if(!sameas(&rec[1],lib.keyname)){
      strcpy(tmp,&rec[1]);
      if(libread(tmp, library.libnum, &lib)!=1){
	printf("\nWarning: Library %s doesn't exist. Skipping file %s.\n",
	       lib.fullname, file->fname);
      }
    }

    file->flibnum=lib.libnum;

    file->timestamp=convert_timedate(stg2short(&rec[400]),stg2short(&rec[402]));
    file->flags=0;
    file->approved=toupper(rec[0])=='A';
    file->downloaded=stg2int(&rec[408]);
    file->descrlen=strlen(&rec[74])+1;
    strcpy(file->uploader,&rec[23]);
    if(file->approved)strcpy(file->approved_by,"Sysop"); /* Major lacks this */
    strcpy(file->summary,&rec[33]);
    strcpy(file->description,&rec[74]);

    if(fileexists(lib.libnum,file->fname,0)||
       fileexists(lib.libnum,file->fname,1)){
      printf("\nWarning: file %s already exists in library %s. Skipping.\n",
	     file->fname,lib.fullname);
    } else {
      filecreate(file);
    }

    /* DONE! */
    if((++num%100)==0){
      printf("%d ",num); 
      fflush(stdout);
    }
    do c=fgetc(fp); while(c=='\n' || c=='\r' || c==26);
    ungetc(c,fp);
  }
  printf("\n\nInstalled %d files.\n",num);

}
