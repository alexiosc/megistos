/*****************************************************************************\
 **                                                                         **
 **  FILE:     msged.c                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 94, Version 0.01 alpha                             **
 **  PURPOSE:  Message editor and configuration tool                        **
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
 * Revision 1.1  2001/04/16 14:48:40  alexios
 * Initial revision
 *
 * Revision 0.1  2000/12/08 15:12:19  alexios
 * Initial checkin.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
const char *__RCS=RCS_VER;
#endif



#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_UNISTD_H 1
#define WANT_NCURSES_H 1
#include <bbsinclude.h>

#include "msged.h"


int           configlevel=0;
int           curlanguage=0;
struct option **displist=NULL;
struct option *options=NULL;
struct option *curopt=NULL;
int           numoptions=0;   /* Total number of options read from files */
int           dispoptions=0;  /* Total number of option lines displayed (+tabs) */
int           dispoptnum=0;   /* Total number of options displayed (- tabs) */
int           curoptnum=0;    /* Current index in displist */


void
syntax()
{
  fprintf(stderr,"syntax:\n");
  fprintf(stderr,"         msged level_num msg_file ...\n\n");
  fprintf(stderr,"         level_num = 1, 2, 3, etc (usually 1,2, or 3)\n");
  fprintf(stderr,"         file      = a configuration .msg file\n\n");
  exit(1);
}


void
readfiles(int argc,char *argv[])
{
  int i;

  if(argc<=2)syntax();
  if((configlevel=atoi(argv[1]))<=0)syntax();
  for(i=2;i<argc;i++){
    fprintf(stderr,"Reading in %s...",argv[i]);
    parsefile(argv[i]);
    fprintf(stderr,"  ok\n");
  }
}


void
initlist()
{
  struct option *i=options;

  dispoptions=0;
  dispoptnum=0;
  curoptnum=0;
  curopt=displist[0];
  
  while(i){
    if(i->opt_type==0 || 
       (i->opt_level==configlevel && 
	(i->opt_language==curlanguage || i->opt_level!=3))){
      displist=realloc(displist,sizeof(struct option *)*(++dispoptions));
      if(!displist){
	errp("Unable to allocate display list%s.\n","");
	exit(-1);
      }
      displist[dispoptions-1]=i;
      if(i->opt_type)dispoptnum++;
    }
    i=i->opt_next;
  }
}


void
done()
{
  endwin();
}


void
main(int argc, char *argv[])
{
  readfiles(argc,argv);
  initwindows();
  atexit(done);
  initlist();
  listopts();
  
/*  printf("\n\n\n");
  {
    int i;
    struct option *opt=options;
    for(i=0;i<numoptions;i++){
      printf("%s (%c): %s\n",opt->opt_name,opt->opt_type,opt->opt_descr);
      opt=opt->opt_next;
    }
  } */

  for(;;){
    chtype ch;
    
    updateinfo();

    ch=mvwgetch(listwin,optlistsize-1,COLS-4);
    if((ch==KEY_UP || ch==16) && curoptnum>0) {
      curoptnum--;
      scrollup();
    } else if((ch==KEY_DOWN || ch==14) && curoptnum<dispoptions-1) {
      curoptnum++;
      scrolldown();
    } else if(ch==KEY_PPAGE || ch==21){
      curoptnum=max(curoptnum-(optlistsize/2),0);
      listopts();
    } else if(ch==KEY_NPAGE || ch==22){
      curoptnum=min(curoptnum+(optlistsize/2),dispoptions-1);
      listopts();
    } else if(ch==KEY_HOME || ch==1){
      curoptnum=0;
      listopts();
    } else if(ch==KEY_END || ch==5){
      curoptnum=dispoptions-1;
      listopts();
    } else if(ch=='<'){
      int i=curoptnum-1;
      while(i>=0 && displist[i]->opt_type)i--;
      curoptnum=max(0,i);
      listopts();
    } else if(ch=='>'){
      int i=curoptnum+1;
      while((i<dispoptions-1) && displist[i]->opt_type)i++;
      curoptnum=min(i,dispoptions-1);
      listopts();
    } else if(ch==27 || ch==KEY_F(9))break;
/*    else printf("\n  %o  \n",ch); */
  }
  attrset(0);
  werase(stdscr);
  refresh();
}

