/*****************************************************************************\
 **                                                                         **
 **  FILE:     windows.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 94, Version 0.01 alpha                             **
 **  PURPOSE:  Handle curses windows and screen in general                  **
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
 * Revision 1.2  2001/04/16 21:56:28  alexios
 * Completed 0.99.2 API, dragged all source code to that level (not as easy as
 * it sounds).
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
#define WANT_STRING_H 1
#define WANT_NCURSES_H 1
#include <bbsinclude.h>

#include "msged.h"


WINDOW *listwin;
WINDOW *infowin;
int    optlistsize;


static void
initcolors()
{
  init_pair(CP_TITLE,COLOR_CYAN,COLOR_BLACK);
  init_pair(CP_FRAMES,COLOR_GREEN,COLOR_BLACK);
  init_pair(CP_FILETAB1,COLOR_BLACK,COLOR_MAGENTA);
  init_pair(CP_FILETAB2,COLOR_WHITE,COLOR_MAGENTA);
  init_pair(CP_OPTION,COLOR_GREEN,COLOR_BLACK);
  init_pair(CP_OPTCHNG,COLOR_YELLOW,COLOR_BLACK);
  init_pair(CP_OPTNAV,COLOR_BLUE,COLOR_BLACK);
  init_pair(CP_INFOFLD,COLOR_WHITE,COLOR_BLACK);
  init_pair(CP_INFONUM,COLOR_GREEN,COLOR_BLACK);
  init_pair(CP_INFOBAR,COLOR_BLACK,COLOR_WHITE);
}


void
initwindows()
{
  fprintf(stderr,"\033[0m");
  initscr();
  if(LINES<15 || COLS<80){
    fprintf(stderr,"msged: Need at least an 80x15 screen to run on.\n");
    exit(1);
  }
  if(has_colors())start_color();
  cbreak();
  noecho();
  
  initcolors();

  wattron(stdscr,COLOR_PAIR(CP_TITLE)|A_REVERSE);
  move(0,0);
  clrtoeol();
  move(0,(COLS-strlen(TITLE)-1)/2);
  wprintw(stdscr,TITLE);
  wrefresh(stdscr);

  listwin=newwin((optlistsize=LINES-6),COLS-1,1,0);
  wattrset(listwin,COLOR_PAIR(CP_FRAMES)|A_BOLD);
  wborder(listwin,0xba,0xba,0xcd,0x20,0xc9,0xbb,0xba,0xba);
  wsetscrreg(listwin,1,optlistsize-1);
  keypad(listwin,TRUE);
  meta(listwin,1);
  
  infowin=newwin(5,COLS-1,LINES-5,0);
  wattrset(infowin,COLOR_PAIR(CP_FRAMES)|A_BOLD);
  wborder(infowin,0xba,0xba,0xcd,0xcd,0xcc,0xb9,0xc8,0xbc);
  meta(infowin,1);
  wrefresh(infowin);
}


void
listopts()
{
  int i;

  for(i=0;i<optlistsize-1;i++){
    wmove(listwin,optlistsize-i-1,2);
    if(curoptnum-i>=0){
      printopt(displist[curoptnum-i]);
    } else {
      int j;
      wattrset(listwin,A_NORMAL);
      for(j=0;j<COLS-5;j++)waddch(listwin,' ');
    }
  }
  wrefresh(listwin);
  refresh();
}


void
scrollup()
{
  int i;

  scrollok(listwin,TRUE);
  wattrset(listwin,A_NORMAL);
  wscrl(listwin,-1);
  
  for(i=0;i<optlistsize-1;i++){
    if(i==optlistsize-2){
      wattrset(listwin,COLOR_PAIR(CP_FRAMES)|A_BOLD);
      mvwaddch(listwin,optlistsize-i-1,0,0xba);
      mvwaddch(listwin,optlistsize-i-1,COLS-2,0xba);
      wattrset(listwin,A_NORMAL);
      wmove(listwin,optlistsize-i-1,2);
    }
    if(curoptnum-i>=0){
      if(i==optlistsize-2)printopt(displist[curoptnum-i]);
    } else {
      int j;
      if(i==optlistsize-2){
	wattrset(listwin,A_NORMAL);
	for(j=0;j<COLS-5;j++)waddch(listwin,' ');
      }
    }
  }
  wrefresh(listwin);
  refresh();
}


void
scrolldown()
{
  int i;
  
  wattrset(listwin,A_NORMAL);
  scrollok(listwin,TRUE);
  wscrl(listwin,1);
  scrollok(listwin,FALSE);
  
  for(i=0;i<optlistsize-1;i++){
    if(!i){
      wattrset(listwin,COLOR_PAIR(CP_FRAMES)|A_BOLD);
      mvwaddch(listwin,optlistsize-1,0,0xba);
      mvwaddch(listwin,optlistsize-1,COLS-2,0xba);
      wattrset(listwin,A_NORMAL);
      wmove(listwin,optlistsize-1,2);
    }
    if(curoptnum-i>=0){
      if(!i)printopt(displist[curoptnum-i]);
    } else {
      int j;
      if(!i){
	wattrset(listwin,A_NORMAL);
	for(j=0;j<COLS-5;j++)waddch(listwin,' ');
      }
    }
  }
  wrefresh(listwin);
  refresh();
}


void
updateinfo()
{
  int i;
  int j;
  unsigned char s[256];
  char c[256];

  wattrset(infowin,COLOR_PAIR(CP_INFOFLD)|A_BOLD);
  mvwprintw(infowin,1,2,"File: ");
  wattrset(infowin,COLOR_PAIR(CP_INFONUM)|A_BOLD);
  wprintw(infowin,"%-16s",displist[curoptnum]->opt_file);

  wattrset(infowin,COLOR_PAIR(CP_INFOFLD)|A_BOLD);
  wprintw(infowin,"Option: ");
  wattrset(infowin,COLOR_PAIR(CP_INFONUM)|A_BOLD);
  wprintw(infowin,"%4d/%-4d %-16s ",curoptnum+1,dispoptions,
	  (displist[curoptnum]->opt_type?displist[curoptnum]->opt_name:
	  "[FILENAME TAG]"));

  wattrset(infowin,COLOR_PAIR(CP_INFOBAR)|A_BOLD);
  j=(int)(2*(((float)COLS-62.0)*(float)curoptnum/((float)dispoptions-1.0)));
  memset(s,219,sizeof(s));
  s[COLS-62]=0;
  for(i=0;i<j/2;i++)s[i]=32;
  if(j%2)s[i]=222;
  wprintw(infowin,"%s",s);

  wattrset(infowin,COLOR_PAIR(CP_INFOFLD)|A_BOLD);
  mvwprintw(infowin,2,2,"Format: ");
  wattrset(infowin,COLOR_PAIR(CP_INFONUM)|A_BOLD);
  switch(displist[curoptnum]->opt_type){
  case 0:
    wprintw(infowin,"[NONE]        ");
    for(i=0;i<COLS-27;i++)waddch(infowin,32);
    break;
  case 'C':
    wprintw(infowin,"CHARACTER     ");
    for(i=0;i<COLS-27;i++)waddch(infowin,32);
    break;
  case 'S':
    wprintw(infowin,"STRING        ");
    for(i=0;i<COLS-27;i++)waddch(infowin,32);
    wattrset(infowin,COLOR_PAIR(CP_INFOFLD)|A_BOLD);
    mvwprintw(infowin,2,24,"Maximum length: ");
    wattrset(infowin,COLOR_PAIR(CP_INFONUM)|A_BOLD);
    wprintw(infowin,"%d",displist[curoptnum]->opt_max);
    break;
  case 'T':
    wprintw(infowin,"TEXT BLOCK    ");
    for(i=0;i<COLS-27;i++)waddch(infowin,32);
    wattrset(infowin,COLOR_PAIR(CP_INFONUM)|A_BOLD);
    mvwprintw(infowin,2,24,"Press ");
    wattrset(infowin,COLOR_PAIR(CP_INFOFLD)|A_BOLD);
    wprintw(infowin,"F2");
    wattrset(infowin,COLOR_PAIR(CP_INFONUM)|A_BOLD);
    wprintw(infowin," to edit the text block.");
    break;
  case 'N':
  case 'L':
    wprintw(infowin,"NUMERIC       ");
    for(i=0;i<COLS-27;i++)waddch(infowin,32);
    wattrset(infowin,COLOR_PAIR(CP_INFOFLD)|A_BOLD);
    mvwprintw(infowin,2,24,"Range: ");
    wattrset(infowin,COLOR_PAIR(CP_INFONUM)|A_BOLD);
    wprintw(infowin,"%ld to %ld",
	    displist[curoptnum]->opt_min,displist[curoptnum]->opt_max);
    break;
  case 'H':
  case 'X':
    wprintw(infowin,"HEX           ");
    for(i=0;i<COLS-27;i++)waddch(infowin,32);
    wattrset(infowin,COLOR_PAIR(CP_INFOFLD)|A_BOLD);
    mvwprintw(infowin,2,24,"Range: ");
    wattrset(infowin,COLOR_PAIR(CP_INFONUM)|A_BOLD);
    wprintw(infowin,"%lx to %lx",
	    displist[curoptnum]->opt_min,displist[curoptnum]->opt_max);
    break;
  case 'B':
    wprintw(infowin,"YES/NO        ");
    for(i=0;i<COLS-27;i++)waddch(infowin,32);
    break;
  case 'E':
    wprintw(infowin,"MULTI-CHOICE  ");
    for(i=0;i<COLS-27;i++)waddch(infowin,32);
    memset(c,0,sizeof(c));
    strncpy(c,displist[curoptnum]->opt_choices,COLS-39);
    if(strlen(c)!=strlen(displist[curoptnum]->opt_choices))strcat(c,"...");
    wattrset(infowin,COLOR_PAIR(CP_INFOFLD)|A_BOLD);
    mvwprintw(infowin,2,24,"Choices: ");
    wattrset(infowin,COLOR_PAIR(CP_INFONUM)|A_BOLD);
    wprintw(infowin,"%s",c);
    break;
  }

  wrefresh(infowin);
}

