/*****************************************************************************\
 **                                                                         **
 **  FILE:     bltcnv.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  PURPOSE:  Convert MBBS 5.31 bulletin database to Megistos format.      **
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
 * Revision 1.1  1998/12/27 15:27:54  alexios
 * Added autoconf support.
 *
 * Revision 1.0  1998/07/24 10:14:19  alexios
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
#define WANT_GETOPT_H 1
#include <bbsinclude.h>

#include <typhoon.h>
#include "bbs.h"
#include "bltidx.h"
#include "bulletins.h"


#define BLTLEN 110



static void
syntax()
{
  fprintf(stderr,"bltcnv: convert MajorBBS 5.xx bulletins to Megistos format.\n\n"\
	  "Syntax: bltcnv options.\n\nOptions:\n"\
	  "  -m dir   or  --majordir dir: read Major databases from specified directory.\n"\
	  "        Defaults to the current directory.\n\n");
  exit(1);
}


static struct option long_options[] = {
  {"majordir", 1, 0, 'm'},
  {0, 0, 0, 0}
};


static char *arg_majordir=".";


static void
parseopts(int argc, char **argv)
{
  int c;

  while (1) {
    int option_index = 0;

    c=getopt_long(argc, argv, "m:", long_options, &option_index);
    if(c==-1) break;

    switch (c) {
    case 'm':
      arg_majordir=strdup(optarg);
      break;
    default:
      syntax();
    }
  }
}



void
convert()
{
  FILE            *fp;
  char            rec[64<<10], c, *fname=rec;
  char            source[256], target[256], lastclub[32]={0};
  int             reclen;
  int             num=0;
  struct bltidx   blt;

  sprintf(fname,"%s/bulletin.txt",arg_majordir?arg_majordir:".");
  fp=fopen(fname,"r");
  if(fp==NULL){
    sprintf(fname,"%s/BULLETIN.TXT",arg_majordir?arg_majordir:".");
    if((fp=fopen(fname,"r"))==NULL){
      fprintf(stderr,
	      "bltcnv: convert(): unable to find bulletin.txt or BULLETIN.TXT.\n");
      exit(1);
    }
  }

  while(!feof(fp)){
    if(fscanf(fp,"%d\n",&reclen)==0){
      if(feof(fp))break;
      fprintf(stderr,"bltcnv: convert(): unable to parse record length. Corrupted file?\n");
      exit(1);
    }
    if(feof(fp))break;
    fgetc(fp);			/* Get rid of the comma after the record length */

    if(reclen!=BLTLEN){
      fprintf(stderr,"bltcnv: convert() incorrect record length.\n");
      exit(1);
    }

    if(fread(rec,reclen,1,fp)!=1){
      fprintf(stderr,"bltcnv: convert(): unable to read record around pos=%ld.\n",ftell(fp));
      exit(1);
    }

    bzero(&blt,sizeof(blt));
    blt.num=(((unsigned char)rec[0])|(((unsigned char)rec[1])<<8));
    blt.date=today();
    sprintf(blt.fname,"conv-%d.blt",blt.num);

    if(!sameas(lastclub,&rec[15])){
      strcpy(lastclub,&rec[15]);
      if(!findclub(lastclub)){
	fprintf(stderr,"convert(): area (%s) does not exist!\n",lastclub);
	exit(1);
      }
    }
    strcpy(blt.area,lastclub);
    strcpy(blt.author,&rec[26]);
    strcpy(blt.descr,&rec[36]);
    blt.timesread=(((unsigned char)rec[77])|(((unsigned char)rec[78])<<8));

    sprintf(source,"%s/%s/%s",arg_majordir,&rec[15],&rec[2]);
    strcpy(target,mkfname(MSGSDIR"/%s/%s/%s",blt.area,MSGBLTDIR,blt.fname));
    fcopy(source,target);
    dbins(&blt);
    printf("%3d %-13s %-10s %s\n",blt.num,blt.fname,blt.area,blt.descr);

    num++;
    do c=fgetc(fp); while(c=='\n' || c=='\r' || c==26);
    ungetc(c,fp);
  }
  fclose(fp);
  printf("\nConverted %d bulletin(s)\n",num);
}


int
bltcnv_main(int argc, char **argv)
{
  mod_setprogname(argv[0]);
  parseopts(argc, argv);

  dbopen();
  convert();
  
  printf("Syncing disks...\n");
  fflush(stdout);
  system("sync");

  return 0;
}
