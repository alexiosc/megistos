/*****************************************************************************\
 **                                                                         **
 **  FILE:     funcs.c                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 94, Version 0.01 alpha                             **
 **  PURPOSE:  Miscellaneous functions                                      **
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
 * Revision 1.3  2001/04/22 14:49:04  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
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
#define WANT_UNISTD_H 1
#define WANT_STRINGS_H 1
#define WANT_NCURSES_H 1
#include <bbsinclude.h>

#include "msged.h"


void
printopt(struct option *opt)
{
  if(!opt)return;
  if(!opt->opt_type){
    char tab[256]={0},temp[256]={0};

    wattrset(listwin,COLOR_PAIR(CP_FILETAB1));
    wprintw(listwin,"%c",0xdf);
    wattrset(listwin,COLOR_PAIR(CP_FILETAB2)|A_BOLD);
    sprintf(temp,"  %s options  ",opt->opt_file);
    wprintw(listwin,temp);
    wattrset(listwin,COLOR_PAIR(CP_FILETAB1));
    memset(tab,0xdf,COLS-6-strlen(temp));
    wprintw(listwin,tab);
  } else {
    char line[256]={0}, dots[256]={0}, setting[256]={0};
    int i,j;

    wattrset(listwin,COLOR_PAIR(CP_OPTION)|A_BOLD);
    switch(opt->opt_type){
    case 'C':
      sprintf(setting,"%c",(char)opt->opt_min);
      break;
    case 'S':
      strcpy(setting,opt->opt_contents);
      break;
    case 'T':
      strcpy(setting,"[TEXT]");
      break;
    case 'N':
    case 'L':
      sprintf(setting,"%d",(int)opt->opt_contents);
      break;
    case 'H':
    case 'X':
      sprintf(setting,"%x",(int)opt->opt_contents);
      break;
    case 'B':
      sprintf(setting,"%s",opt->opt_min?"YES":"NO");
      break;
    case 'E':
      {
	char *cp=setting, *ep;
	strcpy(setting,opt->opt_contents);
	while(*cp && *cp==32)cp++;
	ep=cp;
	while(*ep && *ep!=32 && isprint(*ep))ep++;
	*ep=0;
      }
      break;
    }
    
    j=strlen(opt->opt_descr)%2;
    for(i=0;i<COLS-7-strlen(opt->opt_descr)-strlen(setting);i++){
      dots[i]=j?'.':32;
      j=(j+1)%2;
    }
      
    sprintf(line,"%s %s %s",opt->opt_descr,dots,setting);
    wprintw(listwin,line);
  }
}


