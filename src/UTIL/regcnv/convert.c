/*****************************************************************************\
 **                                                                         **
 **  FILE:     convert.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  PURPOSE:  Convert MBBS 5.31 user registry to Megistos format.          **
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
 * Revision 1.2  2001/04/16 21:56:34  alexios
 * Completed 0.99.2 API, dragged all source code to that level (not as easy as
 * it sounds).
 *
 * Revision 1.1  1998/12/27 16:40:53  alexios
 * Added autoconf support.
 *
 * Revision 1.0  1998/07/16 23:14:59  alexios
 * Initial revision
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
#define WANT_PWD_H 1
#define WANT_GRP_H 1
#include <bbsinclude.h>

#include <endian.h>
#include <typhoon.h>
#include "bbs.h"
#include <registry.h>



#define REGISTRY_RECLEN 1002



void
convert(char *arg_dir, char *arg_majordir, int arg_templ)
{
  FILE       *fp;
  char        rec[16384], c, *fname=rec;
  int         reclen;
  int         num=0;
  struct registry reg;

  /* Start conversion */

  sprintf(fname,"%s/registry.txt",arg_majordir?arg_majordir:".");
  fp=fopen(fname,"r");
  if(fp==NULL){
    sprintf(fname,"%s/REGISTRY.TXT",arg_majordir?arg_majordir:".");
    if((fp=fopen(fname,"r"))==NULL){
      fprintf(stderr,
	      "regcnv: convert(): unable to find registry.txt or REGISTRY.TXT.\n");
      exit(1);
    }
  }

  while(!feof(fp)){
    if(fscanf(fp,"%d\n",&reclen)==0){
      if(feof(fp))break;
      fprintf(stderr,"regcnv: convert(): unable to parse record length. Corrupted file?\n");
      exit(1);
    }
    if(feof(fp))break;
    fgetc(fp);			/* Get rid of the comma after the record length */

    if(reclen!=REGISTRY_RECLEN){
      fprintf(stderr,"regcnv: convert(): record length isn't %d. "\
	      "Is this a v5.31 file?\n",REGISTRY_RECLEN);
      exit(1);
    }

    if(fread(rec,reclen,1,fp)!=1){
      fprintf(stderr,"regcnv: convert(): unable to read record around pos=%ld.\n",ftell(fp));
      exit(1);
    }

    bzero(&reg,sizeof(reg));

    reg.template=arg_templ;
    strcpy(reg.summary,&rec[10]);
    memcpy(reg.registry,&rec[50],sizeof(reg.registry));


    /* Now add the registry */
    {
      FILE *fp;
      char fname[256];
      sprintf(fname,"%s/%s",arg_dir,rec);
      if((fp=fopen(fname,"w"))==NULL){
	fprintf(stderr,"Oops, unable to create %s\n",rec);
	exit(1);
      }
      fwrite(&reg,sizeof(reg),1,fp);
      fclose(fp);
    }
    
    putchar('.');fflush(stdout);


    /* DONE! */
    num++;
    do c=fgetc(fp); while(c=='\n' || c=='\r' || c==26);
    ungetc(c,fp);
  }

  printf("\n\nCreated %d user registries.\n",num);
}
