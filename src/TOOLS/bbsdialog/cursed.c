/*****************************************************************************\
 **                                                                         **
 **  FILE:     cursed.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, November 94                                               **
 **            B, July 95                                                   **
 **  PURPOSE:  Implement visual (full-screen) part of dialog/form manager.  **
 **  NOTES:    WARNING: THIS CODE IS CURSED. :-)                            **
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
 * Revision 1.2  2001/04/16 21:56:34  alexios
 * Completed 0.99.2 API, dragged all source code to that level (not as easy as
 * it sounds).
 *
 * Revision 0.8  1999/08/13 17:09:11  alexios
 * Added call to resetinactivity() to handle slightly borken (sic)
 * telnet line timeouts. This is obsolete but harmless, now that emud
 * handles these.
 *
 * Revision 0.7  1999/07/18 22:07:30  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 0.6  1998/12/27 16:30:50  alexios
 * Added autoconf support. Added tentative support for
 * slcurses (doesn't work yet). Fixed bug that wouldn't
 * interpret the ^? (Delete) key.
 *
 * Revision 0.5  1998/07/24 10:29:41  alexios
 * Moved to stable status. Migrated to bbslib 0.6.
 *
 * Revision 0.4  1997/11/06 20:02:58  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.3  1997/11/05 10:49:19  alexios
 * Reverted to using msg_get() instead of xlgetmsg() since emud()
 * takes care of translations for everything passing through it
 * (even shell sessions).
 *
 * Revision 0.2  1997/09/12 13:35:04  alexios
 * Added a call to the fieldhelp() function. Fixed calls to
 * msg_get() that would return untranslated prompt blocks. Now
 * all prompts are properly translated for the right terminal
 * type.
 *
 * Revision 0.1  1997/08/28 11:21:38  alexios
 * First registered revision. Adequate.
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
#define WANT_NCURSES_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "bbsdialog.h"
#include "mbk_bbsdialog.h"

#ifndef KEY_DC
#  ifdef SLANG_VERSION
#    define KEY_DC SL_KEY_DELETE
#  endif
#endif

void
completeuserid(char *s)
{
  FILE *fp;
  char command[256],uid[256];

  if(!strlen(s))return;
  
  sprintf(command,"\\ls %s",USRDIR);
  if((fp=popen(command,"r"))==NULL){
    fclose(fp);
    strcpy(s,SYSOP);
    return;
  }
  while(!feof(fp)){
    uid[0]=0;
    if(!fscanf(fp,"%s",uid))continue;
    if(sameto(s,uid)){
      strcpy(s,uid);
      pclose(fp);
      return;
    }
  }
  pclose(fp);
  strcpy(s,SYSOP);
}


void
completeclass(char *s)
{
  int i;
  
  for(i=0;i<cls_count;i++)if(sameto(s,cls_classes[i].name)){
    strcpy(s,cls_classes[i].name);
    return;
  }
  strcpy(s,cls_classes[0].name);
}


static void
showstringfield(union object *obj)
{
  int i, space=0, startpos;

  addch((obj->s.cp>obj->s.shown)?'<':32);
  startpos=max(0,obj->s.cp-obj->s.shown);
  for(i=0;i<obj->s.shown;i++){
    if((!obj->s.data[i+startpos]) && !space)space=1;
    addch(space?32:((obj->s.flags&2)?'*':obj->s.data[i+startpos]&0xff));
  }
  if ((obj->s.cp < (i=strlen(obj->s.data))) && (i>obj->s.shown))
    addch('>'); else addch(32);
}


static void
shownumfield(union object *obj)
{
  unsigned char meta[32];

  sprintf(meta," %%%ds ",obj->n.flags&1?obj->n.shown:-obj->n.shown);
  printw(meta,obj->n.data);
}


static void
showlistfield(union object *obj)
{
  int i;

  for(i=0;obj->l.data[i];i++)addch(obj->l.data[i]&0xff);
  for(;i<obj->l.size;i++)addch(32);
}


static void
showtogglefield(union object *obj)
{
  addch(obj->t.data?obj->t.on:obj->t.off);
}


static void
showbuttonfield(union object *obj)
{
  int i,j=(obj->b.size-strlen(obj->b.label))/2;

  addch(obj->b.flags&1?'>':32);
  for(i=0;i<j;i++)addch(32);
  for(i=0;obj->b.label[i];i++)addch(obj->b.label[i]&0xff);
  for(i=0;i<(obj->b.size-strlen(obj->b.label)-j);i++)addch(32);
  addch(obj->b.flags&1?'<':32);
}


static void
drawfield(int n)
{
  move(object[n].s.y,object[n].s.x);
  attrset(0);
  if(object[n].s.color&(1<<10)){
    attron(COLOR_PAIR((object[n].s.color&0xff))|A_BOLD);
  } else {
    attron(COLOR_PAIR((object[n].s.color&0xff)));
  }
  switch(object[n].s.type){
  case OBJ_STRING:
    showstringfield(&object[n]);
    move(object[n].s.y,
	 min(object[n].s.x+object[n].s.cp+1,
	     object[n].s.x+object[n].s.shown+1));
    break;
  case OBJ_NUM:
    shownumfield(&object[n]);
    move(object[n].n.y,object[n].n.x+
	 (object[n].n.flags&1?
	  object[n].n.shown+1+object[n].n.cp-strlen(object[n].n.data):
	  object[n].n.cp+1));
    break;
  case OBJ_LIST:
    showlistfield(&object[n]);
    move(object[n].l.y,object[n].l.x);
    break;
  case OBJ_TOGGLE:
    showtogglefield(&object[n]);
    move(object[n].t.y,object[n].t.x);
    break;
  case OBJ_BUTTON:
    showbuttonfield(&object[n]);
    move(object[n].t.y,object[n].t.x);
    break;
  }
}


static void
handlestringfield(int n, chtype c)
{
  int i;
  union object *obj=&object[n];

  switch(c){
  case KEY_LEFT:
  case 2:
    if(obj->s.cp)obj->s.cp--;
    drawfield(n);
    refresh();
    break;
  case KEY_RIGHT:
  case 6:
    if(obj->s.cp<strlen(obj->s.data))obj->s.cp++;
    drawfield(n);
    refresh();
    break;
  case KEY_HOME:
  case 1:
    obj->s.cp=0;
    drawfield(n);
    refresh();
    break;
  case KEY_END:
  case 5:
    obj->s.cp=strlen(obj->s.data);
    drawfield(n);
    refresh();
    break;
  case 11:
    obj->s.data[obj->s.cp]=0;
    drawfield(n);
    refresh();
    break;
  case KEY_BACKSPACE:
  case 8:
  case 127:
    if((i=strlen(obj->s.data))>0 && obj->s.cp){
      int j;
      for(j=obj->s.cp-1;j<i;j++)obj->s.data[j]=obj->s.data[j+1];
      obj->s.data[i]=0;
      obj->s.cp--;
      drawfield(n);
      refresh();
    }
    break;
  case KEY_DC:
  case 4:
    if(obj->s.cp<(i=strlen(obj->s.data))){
      int j;
      for(j=obj->s.cp;j<i;j++)obj->s.data[j]=obj->s.data[j+1];
      obj->s.data[i]=0;
      drawfield(n);
      refresh();
    }
    break;
  default:
    if((i=strlen(obj->s.data))<obj->s.max && ISPRINT(c)){
      int j;

      if((obj->s.flags&4)&&(!isdigit(c)))c='/';
      if(obj->s.flags&1)c=toupper(c);
      for(j=i;j>=obj->s.cp;j--)obj->s.data[j+1]=obj->s.data[j];
      obj->s.data[obj->s.cp]=c&0xff;
      obj->s.cp++;
      drawfield(n);
      refresh();
    }
  } 
}


static void
handlenumfield(int n, chtype c)
{
  int i;
  union object *obj=&object[n];

  switch(c){
  case KEY_LEFT:
  case 2:
    if(obj->n.cp)obj->n.cp--;
    drawfield(n);
    refresh();
    break;
  case KEY_RIGHT:
  case 6:
    if(obj->n.cp<strlen(obj->n.data))obj->n.cp++;
    drawfield(n);
    refresh();
    break;
  case KEY_HOME:
  case 1:
    obj->n.cp=0;
    drawfield(n);
    refresh();
    break;
  case KEY_END:
  case 5:
    obj->n.cp=strlen(obj->n.data);
    drawfield(n);
    refresh();
    break;
  case KEY_BACKSPACE:
  case 127:
  case 8:
    if((i=strlen(obj->n.data))>0 && obj->n.cp){
      int j;
      for(j=obj->n.cp-1;j<i;j++)obj->n.data[j]=obj->n.data[j+1];
      obj->n.data[i]=0;
      obj->n.cp--;
      drawfield(n);
      refresh();
    }
    break;
  case KEY_DC:
  case 4:
    if(obj->n.cp<(i=strlen(obj->n.data))){
      int j;
      for(j=obj->n.cp;j<i;j++)obj->n.data[j]=obj->n.data[j+1];
      obj->n.data[i]=0;
      drawfield(n);
      refresh();
    }
    break;
  default:
    if((i=strlen(obj->n.data))<obj->n.shown && (isdigit(c)||c=='-')){
      int j;

      for(j=i;j>=obj->n.cp;j--)obj->n.data[j+1]=obj->n.data[j];
      obj->n.data[obj->n.cp]=c&0xff;
      obj->n.cp++;
      drawfield(n);
      refresh();
    }
  } 
}


static void
handlelistfield(int n, chtype c)
{
  union object *obj=&object[n];
  char *cp;

  switch(c){
  case KEY_RIGHT:
  case 6:
  case 32:
  case '+':
  case '=':
    obj->l.data+=strlen(obj->l.data)+1;
    if(!*obj->l.data)obj->l.data=obj->l.options;
    drawfield(n);
    refresh();
    break;
  case KEY_BACKSPACE:
  case KEY_LEFT:
  case 127:
  case 2:
  case 4:
  case 8:
  case '-':
  case '_':
    if(obj->l.data!=obj->l.options){
      for(cp=obj->l.data-2;*cp;cp--);
      cp++;
      obj->l.data=cp;
    } else {
      for(cp=obj->l.options;*cp!=0||*(cp+1)!=0;cp++);
      for(cp--;*cp;cp--);
      obj->l.data=cp+1;
    }
    drawfield(n);
    refresh();
    break;
  } 
}


static void
handletogglefield(int n, chtype c)
{
  union object *obj=&object[n];

  switch(c){
  case 32:
    obj->t.data=!obj->t.data;
    drawfield(n);
    refresh();
    break;
  } 
}


static void
handlebuttonfield(int n, chtype c)
{
  switch(c){
  case KEY_ENTER:
  case 10:
  case 13:
  case 32:
    endsession(object[n].b.label);
    break;
  } 
}


static void
handlechar(int n, chtype c)
{
  switch(object[n].s.type){
  case OBJ_STRING:
    handlestringfield(n,c);
    break;
  case OBJ_NUM:
    handlenumfield(n,c);
    break;
  case OBJ_LIST:
    handlelistfield(n,c);
    break;
  case OBJ_TOGGLE:
    handletogglefield(n,c);
    break;
  case OBJ_BUTTON:
    handlebuttonfield(n,c);
    break;
  }
}


static void
defocus (int n)
{
  int i;

  switch(object[n].s.type){
  case OBJ_STRING:
    if(object[n].s.flags&4){
      if(scandate(object[n].s.data)<0){
	strcpy(object[n].s.data,"1/1/1970");
	object[n].s.cp=strlen(object[n].s.data);
	drawfield(n);
      }
    } else if(object[n].s.flags&8){
      completeuserid(object[n].s.data);
      object[n].s.cp=strlen(object[n].s.data);
      drawfield(n);
    } else if(object[n].s.flags&16){
      completeclass(object[n].s.data);
      object[n].s.cp=strlen(object[n].s.data);
      drawfield(n);
    }
    break;
  case OBJ_NUM:
    i=atoi(object[n].n.data);
    i=max(i,object[n].n.min);
    i=min(i,object[n].n.max);
    sprintf(object[n].n.data,"%d",i);
    object[n].n.cp=strlen(object[n].n.data);
    drawfield(n);
    break;
  case OBJ_BUTTON:
    object[n].b.flags&=~1;
    drawfield(n);
    break;
  }
}


static void
focus (int n)
{
  switch(object[n].s.type){
  case OBJ_BUTTON:
    object[n].b.flags|=1;
    break;
  }
}


static void
initcolors()
{
  int i,j;

  for(i=0;i<8;i++)for(j=0;j<8;j++)init_pair(i+j*8,i,j);
}


static void
mainloop()
{
  int curfield=0;
  chtype c;

  for(;;){
    drawfield(curfield);
    inp_resetidle();
    switch(c=getch()){
    case 9:
    case 14:
    case KEY_DOWN:
      defocus(curfield);
      curfield=(curfield+1)%numobjects;
      focus(curfield);
      break;
    case 16:
#ifdef KEY_BTAB
    case KEY_BTAB:
#endif
    case KEY_UP:
      defocus(curfield);
      curfield=curfield--;
      if(curfield<0)curfield+=numobjects;
      focus(curfield);
      break;
    case 17:
    case 3:
      defocus(curfield);
      endsession("Cancel");
      break;
    case 18:
      visualhelp();
      break;
    case 15:
      fieldhelp(curfield);
      break;
    case 19:
      defocus(curfield);
      endsession("OK");
      break;
    case 12:
/*      attrset(A_NORMAL);
      printw(" "); */
      refresh();
#ifndef SLANG_VERSION
      wrefresh(curscr);
#else
      wrefresh(stdscr);
#endif
      break;
    case 24:
      return;
    default:
      if((c==KEY_LEFT || c==2) && (object[curfield].s.type==OBJ_BUTTON||
				   object[curfield].s.type==OBJ_TOGGLE)){
	defocus(curfield);
	curfield=curfield--;
	if(curfield<0)curfield+=numobjects;
	focus(curfield);
      } else if((c==KEY_RIGHT || c==6) && (object[curfield].s.type==OBJ_BUTTON||
					   object[curfield].s.type==OBJ_TOGGLE)){
	defocus(curfield);
	curfield=(curfield+1)%numobjects;
	focus(curfield);
      } else if((c==10||c==KEY_ENTER) && object[curfield].s.type!=OBJ_BUTTON){
	defocus(curfield);
	curfield=(curfield+1)%numobjects;
	focus(curfield);
      } else handlechar(curfield,c);
    }
  }
}

static void
parsetemplate()
{
  FILE *data=NULL;
  unsigned char c;
  char parms[1024], *cp, *ep, dataline[257];
  int state=0, len=0, n,y,x, sx=0,sy=0;
  int fg=7, bg=0, bold=0, quote=0, i;
  char *msg_buffer=msg_get(vtnum);

  if((data=fopen(dfname,"r"))==NULL){
    error_fatalsys("Unable to open data file %s",dfname);
  }

  while ((c=*msg_buffer++)!=0){
    if(c==13)continue;
    if (c==27 && !state) state=1;
    else if (c=='[' && state==1){
      state=2;
      len=0;
      parms[0]=0;
    } else if (c=='@' && state==1){
      state=3;
      len=0;
      parms[0]=0;
    } else if(state==2){
      if(isdigit(c) || c==';') {
	parms[len++]=c;
	parms[len]=0;
	parms[len+1]=0;
	len=len%77;
      } else {
	state=0;
	switch(c) {
	case 'A':
	  n=atoi(parms);
	  if(!n)n++;
	  getyx(stdscr,y,x);
	  move(y-n,x);
	  break;
	case 'B':
	  n=atoi(parms);
	  if(!n)n++;
	  getyx(stdscr,y,x);
	  move(y+n,x);
	  break;
	case 'C':
	  n=atoi(parms);
	  if(!n)n++;
	  getyx(stdscr,y,x);
	  move(y,x+n);
	  break;
	case 'D':
	  n=atoi(parms);
	  if(!n)n++;
	  getyx(stdscr,y,x);
	  move(y,x-n);
	  break;
	case 'H':
	  x=y=0;
	  sscanf(parms,"%d;%d",&x,&y);
	  if(x)x--;
	  if(y)y--;
	  move(y,x);
	  break;
	case 'J':
	  erase();
	  move(0,0);
	  break;
	case 'K':
	  clrtoeol();
	  break;
	case 'm':
	  cp=ep=parms;
	  while(*cp){
	    while(*ep && *ep!=';')ep++;
	    *(ep++)=0;
	    n=atoi(cp);
	    switch (n) {
	    case 0:
	      attrset(0);
	      fg=7;
	      bg=0;
	      bold=0;
	      break;
	    case 1:
	      attron(A_BOLD);
	      bold=1;
	      break;
	    case 2:
	      attroff(A_BOLD);
	      break;
	    case 4:
	      attron(A_UNDERLINE);
	      fg=4;
	      break;
	    case 5:
	      attron(A_BLINK);
	      break;
	    case 7:
	      attron(A_REVERSE);
	      n=fg;
	      fg=bg;
	      bg=n;
	      break;
	    case 21:
	    case 22:
	      attroff(A_BOLD);
	      bold=0;
	      break;
	    case 24:
	      attroff(A_UNDERLINE);
	      break;
	    case 25:
	      attroff(A_BLINK);
	      break;
	    case 27:
	      attroff(A_REVERSE);
	      n=fg;
	      fg=bg;
	      bg=n;
	      break;
	    default:
	      if (n>= 30 && n<=37) {
		fg=n-30;
		attron(COLOR_PAIR((bg*8+fg)));
	      } else if (n>=40 && n<=47) {
		bg=n-40;
		attron(COLOR_PAIR((bg*8+fg)));
	      }
	    }
	    cp=ep;
	  }
	  break;
	case 's':
	  getyx(stdscr,sy,sx);
	  break;
	case 'u':
	  move(sy,sx);
	  break;
	}
      }
    } else if(state==3) {
      union object obj;
      if(isdigit(c) || c=='-' || c==';' || c=='"' || quote) {
	if(c=='"')quote=!quote;
	parms[len++]=c;
	parms[len]=0;
	parms[len+1]=0;
	len=len%1021;
      } else {
	state=0;
	quote=0;
	memset(&obj,0,sizeof(obj));
	switch(c) {
	case 's':
	  obj.s.type=OBJ_STRING;
	  obj.s.color=(bg*8+fg)|(bold<<10);
	  getyx(stdscr,obj.s.y,obj.s.x);
	  if(sscanf(parms,"%d;%d;%ld",&obj.s.max,&obj.s.shown,&obj.s.flags)==3){
	    numobjects++;
	    if((obj.s.data=alcmem(obj.s.max+1))==NULL || 
	       (object=realloc(object,sizeof(union object)*numobjects))==NULL){
	      error_fatal("Unable to allocate dialog object buffers");
	    }
	    dataline[0]=0;
	    fgets(dataline,sizeof(dataline),data);
	    if((cp=strchr(dataline,'\n'))!=NULL)*cp=0;
	    memset(obj.s.data,0,obj.s.max+1);
	    strncpy(obj.s.data,dataline,obj.s.max);
	    obj.s.cp=strlen(obj.s.data);
	    if(obj.s.flags&1){
	      int i;
	      for(i=0;obj.s.data[i];i++)obj.s.data[i]=toupper(obj.s.data[i]);
	    }
	    memcpy(&object[numobjects-1],&obj,sizeof(union object));
	    showstringfield(&obj);
	  }
	  break;
	case 'n':
	  obj.n.type=OBJ_NUM;
	  obj.n.color=(bg*8+fg)|(bold<<10);
	  getyx(stdscr,obj.n.y,obj.n.x);
	  if(sscanf(parms,"%d;%d;%d;%ld",&obj.n.shown,&obj.n.min,&obj.n.max,
		    &obj.n.flags)==4){
	    numobjects++;
	    if((obj.n.data=alcmem(obj.n.shown+1))==NULL || 
	       (object=realloc(object,sizeof(union object)*numobjects))==NULL){
	      error_fatal("Unable to allocate dialog object buffers");
	    }
	    dataline[0]=0;
	    fgets(dataline,sizeof(dataline),data);
	    if((cp=strchr(dataline,'\n'))!=NULL)*cp=0;
	    sscanf(dataline," %s ",obj.n.data);
	    obj.n.cp=strlen(obj.n.data);
	    memcpy(&object[numobjects-1],&obj,sizeof(union object));
	    shownumfield(&obj);
	  }
	  break;
	case 'l':
	  obj.l.type=OBJ_LIST;
	  obj.l.color=(bg*8+fg)|(bold<<10);
	  getyx(stdscr,obj.l.y,obj.l.x);
	  if(sscanf(parms,"%d;\"%n",&obj.l.size,&i)==1){
	    numobjects++;
	    cp=&parms[i];
	    if((obj.l.options=alcmem(strlen(cp)+1))==NULL || 
	       (object=realloc(object,sizeof(union object)*numobjects))==NULL){
	      error_fatal("Unable to allocate dialog object buffers");
	    }
	    memset(obj.l.options,0,strlen(cp)+1);
	    strncpy(obj.l.options,cp,strlen(cp));

	    dataline[0]=0;
	    fgets(dataline,sizeof(dataline),data);
	    if((ep=strchr(dataline,'\n'))!=NULL)*ep=0;

	    obj.l.data=obj.l.options;
	    for(ep=cp,i=0;obj.l.options[i];i++){
	      if(obj.l.options[i]=='|' || obj.l.options[i]=='"'){
		obj.l.options[i]=0;
		if(!strcmp(ep,dataline))obj.l.data=ep;
		ep=&obj.l.options[i+1];
	      }
	    }
	    memcpy(&object[numobjects-1],&obj,sizeof(union object));
	    showlistfield(&obj);
	  }
	  break;
	case 't':
	  obj.t.type=OBJ_TOGGLE;
	  obj.t.color=(bg*8+fg)|(bold<<10);
	  getyx(stdscr,obj.t.y,obj.t.x);
	  numobjects++;
	  obj.t.on=parms[1];
	  obj.t.off=parms[2];
	  cp=&parms[i];
	  if((object=realloc(object,sizeof(union object)*numobjects))==NULL){
	    error_fatal("Unable to allocate dialog object buffers");
	  }
	  dataline[0]=0;
	  fgets(dataline,sizeof(dataline),data);
	  if((ep=strchr(dataline,'\n'))!=NULL)*ep=0;
	  obj.t.data=strcasecmp(dataline,"on")==0;
	  memcpy(&object[numobjects-1],&obj,sizeof(union object));
	  showtogglefield(&obj);
	  break;
	case 'b':
	  obj.b.type=OBJ_BUTTON;
	  obj.b.color=(bg*8+fg)|(bold<<10);
	  getyx(stdscr,obj.b.y,obj.b.x);
	  if(sscanf(parms,"%d;\"%n",&obj.b.size,&i)==1){
	    numobjects++;
	    cp=&parms[i];
	    if((obj.b.label=alcmem(strlen(cp)+1))==NULL ||
	       (object=realloc(object,sizeof(union object)*numobjects))==NULL){
	      error_fatal("Unable to allocate dialog object buffers");
	    }
	    if((ep=strchr(cp,'"'))!=NULL)*ep=0;
	    strncpy(obj.b.label,cp,strlen(cp)+1);

	    dataline[0]=0;
	    fgets(dataline,sizeof(dataline),data);
	    memcpy(&object[numobjects-1],&obj,sizeof(union object));
	    showbuttonfield(&obj);
	  }
	  break;
	}
      }
    } else if(!state)addch(c);
  }
  fclose(data);
}


void
runvisual()
{
  thisuseronl.flags|=(OLF_BUSY|OLF_NOTIMEOUT);
  initscr();

  printf("\033[0m");

  if(has_colors())start_color();
  noecho();
  initcolors();
  keypad(stdscr,TRUE);
#ifndef SLANG_VERSION
  meta(stdscr,1);
#endif

  parsetemplate();

  wrefresh(stdscr);
  refresh();

  mainloop();

  endsession("Linear");
}
