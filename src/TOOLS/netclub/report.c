/*****************************************************************************\
 **                                                                         **
 **  FILE:     report.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1999.                                                **
 **  PURPOSE:  Print import point reports.                                  **
 **  NOTES:    See syntax() function for the syntax of this program.        **
 **                                                                         **
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
 * Revision 1.3  2001/04/22 14:49:08  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
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
#define WANT_SYS_STAT_H 1
#define WANT_DIRENT_H 1
#define WANT_TIME_H 1
#include <bbsinclude.h>
#include <bbs.h>
#include "netclub.h"



void
print_report(char *fname, char *sysname)
{
  FILE *fp;
  int   delta=0;
  int   numexp=0;
  int   numclubs=0;
  int   lastsync=0;
  int   ihavedate=0;
  int   timenow=time(NULL);
  char  tmp[256];

  if((fp=fopen(fname,"r"))==NULL){
    perror("netclub: print_report: fopen():");
    exit(1);
  }

  while(!feof(fp)){
    char line[512], key[512];
    int x;
    if(!fgets(line,sizeof(line),fp))break;
    if(sscanf(line,"%s %d",key,&x)==2){
      if(sameas(key,"delta:")) delta=x;
      else if(sameas(key,"last-update:")) lastsync=x;
      else if(sameas(key,"last-ihave-time:")) ihavedate=x;
    } else if(sscanf(line,"%s %*s %*s",key)==1){
      if(sameas(key,"import:"))numexp++;
      else if(sameas(key,"club:"))numclubs++;
    }
  }
  fclose(fp);

  printf("System name:     %s\n",sysname);
  printf("Filename:        %s\n",fname);

  {
    int m,h,d;
    d=delta/86400;
    h=(delta%86400)/3600;
    m=(delta%3600)/60;
    sprintf(fname,"%d",delta);	/* Reusing the fname variable to save space */
    printf("Synced every:    %d days, %d hours, %d mins.\n",d,h,m);
  }

  strftime(tmp,sizeof(tmp),"%a, %d/%b/%Y %H:%M:%S",localtime((time_t*)&lastsync));
  printf("Last sync:       %s\n",tmp);

  lastsync+=delta;
  strftime(tmp,sizeof(tmp),"%a, %d/%b/%Y %H:%M:%S",localtime((time_t*)&lastsync));
  printf("Next sync:       %s (or later)\n",tmp);

  strftime(tmp,sizeof(tmp),"%a, %d/%b/%Y %H:%M:%S",localtime((time_t*)&timenow));
  printf("Time now:        %s\n",tmp);

  printf("Clubs imported:  %d\n",numexp);
  printf("Clubs on system: %d %s\n",numclubs,
	 numclubs?"":"(or temporarily unknown number of clubs)");
  printf("\n");
}
