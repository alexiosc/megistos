/*****************************************************************************\
 **                                                                         **
 **  FILE:     find.c                                                       **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, April 95, Version 0.5 alpha                               **
 **  PURPOSE:  The Visual Editor find/replace functions                     **
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
 * Revision 1.1  2001/04/16 15:03:03  alexios
 * Initial revision
 *
 * Revision 0.8  1999/08/13 17:10:05  alexios
 * Fixed things so that user inactivity timers are reset to handle
 * slightly borken (sic) telnet line timeouts. This is useless but
 * harmless, since emud handles these timeouts.
 *
 * Revision 0.7  1998/12/27 16:35:48  alexios
 * Added autoconf support.
 *
 * Revision 0.6  1998/08/14 12:01:28  alexios
 * No changes.
 *
 * Revision 0.5  1997/11/06 20:03:31  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.4  1997/11/05 10:50:43  alexios
 * Stopped using xlgetmsg() and reverted to getmst() since emud
 * now performs all translations itself.
 *
 * Revision 0.3  1997/09/12 13:41:18  alexios
 * Used translated message blocks instead of raw ones.
 *
 * Revision 0.2  1997/08/31 09:23:15  alexios
 * Removed calls to the visual library, replaced them with ncurses
 * calls.
 *
 * Revision 0.1  1997/08/28 11:26:56  alexios
 * First registered revision. Adequate.
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
#define WANT_TIME_H 1
#define WANT_NCURSES_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "vised.h"
#include "mbk_vised.h"


static char findtext[1024]={0};
static char ftxt[1024]={0};
static int opt=0;

int fy=0,fx=0,fl=0;


void
find()
{
  int c;

  move(LINES-2,0);
  printansi(getmsg(FIND1));
  refresh();
  strcpy(ftxt,getstg(findtext,rmargin));
  if(isX(ftxt)||ftxt[0]==0){
    showstatus();
    return;
  } else strcpy(findtext,ftxt);
  move(LINES-2,0);
  printansi(getmsg(FIND2));
  refresh();

  for(opt=0;!opt;){
    char s[2],t[2];

    while((c=mygetch())==ERR)usleep(20000);

    if(c==3||c==27){
      showstatus();
      return;
    }
    s[0]=c;
    s[1]=0;
    strcpy(t,latinize(s));
    c=toupper(t[0]);
    switch(c){
    case 10:
    case 13:
      opt=1;
      break;
    case 'I':
      opt=2;
      break;
    case 'P':
      opt=3;
      break;
    }
  }

  dosearch();
}


void
dosearch()
{
  char *cp;
  int c,n;
  struct line *l;

  if(!findtext[0])find();
  fx=fy=fl=0;

  strcpy(ftxt,findtext);
  if(opt==2)for(c=0;ftxt[c];c++)ftxt[c]=toupper(ftxt[c]);
  else if(opt==3)strcpy(ftxt,phonetic(findtext));

  for(n=cy,l=current;l;l=l->next,n++){
    char line[1024];
    
    if(opt==2){
      strcpy(line,l->text);
      for(c=0;l->text[c];c++)line[c]=toupper(line[c]);
    } else if(opt==3){
      strcpy(line,l->text);
      phonetic(line);
    } else strcpy(line,l->text);

    if((cp=strstr((n==cy&&cx)?&line[cx]:line,ftxt))!=NULL){
      cy=fy=n;
      fl=strlen(ftxt);
      cx=fx=(cp-line);
      cx+=fl;
      current=l;
      if((cy-toprow+1)<1||(cy-toprow+1)>=LINES-2)centerline();
      showtext(0);
      showstatus();
      refresh();
      return;
    }
  }
  movepage(numlines);
  showstatus();
}


void
replace()
{
  int c,n;
  static char findtext[1024]={0},ftxt[1024]={0},reptxt[1024]={0};
  char *cp;
  struct line *l;
  int opt,action=0,all=0;

  move(LINES-2,0);
  printansi(getmsg(FREP1));
  refresh();
  strcpy(ftxt,getstg(findtext,rmargin));
  if(isX(ftxt)||ftxt[0]==0){
    showstatus();
    return;
  } else strcpy(findtext,ftxt);

  move(LINES-2,0);
  printansi(getmsg(FREP2));
  refresh();
  strcpy(reptxt,getstg(reptxt,rmargin));
  if(isX(reptxt)){
    showstatus();
    return;
  }

  move(LINES-2,0);
  printansi(getmsg(FREP3));
  refresh();

  for(opt=0;!opt;){
    char s[2],t[2];

    while((c=mygetch())==ERR)usleep(20000);

    if(c==3||c==27){
      showstatus();
      return;
    }
    s[0]=c;
    s[1]=0;
    strcpy(t,latinize(s));
    c=toupper(t[0]);
    switch(c){
    case 10:
    case 13:
      opt=1;
      break;
    case 'I':
      opt=2;
      break;
    case 'P':
      opt=3;
      break;
    }
  }

  fy=fx=fl=0;

  strcpy(ftxt,findtext);
  if(opt==2)for(c=0;ftxt[c];c++)ftxt[c]=toupper(ftxt[c]);
  else if(opt==3)strcpy(ftxt,phonetic(findtext));
  
  do{
    for(n=cy,l=current;l;l=l->next,n++){
      char line[1024];
      
      if(opt==2){
	strcpy(line,l->text);
	for(c=0;l->text[c];c++)line[c]=toupper(line[c]);
      } else if(opt==3){
	strcpy(line,l->text);
	phonetic(line);
      } else strcpy(line,l->text);

      if((cp=strstr((n==cy&&cx)?&line[cx]:line,ftxt))!=NULL){
	cy=fy=n;
	fl=strlen(ftxt);
	cx=fx=(cp-line);
	cx+=fl;
	current=l;
	if(!all){
	  if((cy-toprow+1)<1||(cy-toprow+1)>=LINES-2)centerline();
	  showtext(0);
	}
	break;
      }
    }
    if(l){
      if(!all){
	move(LINES-2,0);
	printansi(getmsg(FREP4));
	putcursor();
	refresh();
      }

      for(action=0;!action;){
	char s[2],t[2];

	if(!all){
	  while((c=mygetch())==ERR)usleep(20000);
	
	  if(c==3||c==27){
	    showstatus();
	    return;
	  }
	  s[0]=c;
	  s[1]=0;
	  strcpy(t,latinize(s));
	  c=toupper(t[0]);
	} else c='Y';
	switch(c){
	case 'Y':
	  {
	    char temp[1024];
	    int  b;

	    strcpy(temp,l->text);
	    b=numbytes-strlen(temp);
	    temp[fx]=0;
	    strcat(temp,reptxt);
	    strcat(temp,&l->text[fx+fl]);
	    b+=strlen(temp);
	    if(b>maxsize){
	      bel(ERRSIZ);
	      l=NULL;
	      action=-1;
	    } else {
	      cx-=strlen(ftxt);
	      cx+=strlen(reptxt);
	      current=getline(cy=n);
	      putcursor();
	      action=1;
	      numbytes=b;
	      strcpy(l->text,temp);
	      fl=0;
	    }
	  }
	  break;
	case 'N':
	  action=1;
	  break;
	case 'A':
	  all=1;
	  action=1;
	  break;
	case 'Q':
	  action=-1;
	  l=NULL;
	  break;
	}
      }
    }
  } while (l);

  if((cy-toprow+1)<1||(cy-toprow+1)>=LINES-2)centerline();
  showtext(0);
}
