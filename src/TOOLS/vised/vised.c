/*****************************************************************************\
 **                                                                         **
 **  FILE:     vised.c                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, April 95, Version 0.5 alpha                               **
 **            B, September 95, Version 0.6 alpha                           **
 **            C, August 96, Version 0.7                                    **
 **  PURPOSE:  The Visual Editor                                            **
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
 * Revision 1.3  2001/04/22 14:49:08  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.11  2000/01/08 12:48:03  alexios
 * Fixed slight bug that caused a segmentation fault.
 *
 * Revision 0.10  1999/08/13 17:10:05  alexios
 * Fixed things so that user inactivity timers are reset to handle
 * slightly borken (sic) telnet line timeouts. This is useless but
 * harmless, since emud handles these timeouts.
 *
 * Revision 0.9  1999/07/18 22:10:59  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 0.8  1998/12/27 16:35:48  alexios
 * Added autoconf support. One slight fix.
 *
 * Revision 0.7  1998/08/14 12:01:28  alexios
 * No changes.
 *
 * Revision 0.6  1998/07/24 10:31:45  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.5  1997/11/06 20:03:31  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.4  1997/11/05 10:50:43  alexios
 * Reverted back to untranslated messages since emud now
 * performs all translations.
 *
 * Revision 0.3  1997/09/12 13:41:18  alexios
 * Used translated prompts instead of raw ones. Added the ability
 * to understand basic lined commands (/s, /u, x) as long as they
 * start on the first column. Fixed MM_CONCAT problems that would
 * cause the updown() tool to freak out if the user chose to upload
 * text. Saving now strips any trailing blank lines from the text.
 * Made the user BUSY and NOTIMEOUT so that they can't be paged and
 * the system won't kick them out while they're in the editor. If
 * uploading text, we revert to normal operation so that pages may
 * be received. Various bug fixes to accommodate the use of ncurses
 * instead of the visual library. Added a check for KEY_SUSPEND in
 * addition to CTRL('Z'). It seems to work everywhere now. Slight
 * cosmetic and behaviour changes and fixes.
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
const char *__RCS=RCS_VER;
#endif



#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_TIME_H 1
#define WANT_SYS_IOCTL_H 1
#define WANT_SYS_KD_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_LINUX_ERRNO_H 1
#define WANT_LINUX_TTY_H 1
#define WANT_LINUX_VT_H 1
#define WANT_NCURSES_H 1
#include <bbsinclude.h>

#include <sys/kd.h>
#include "bbs.h"
#include "vised.h"
#include "mbk_vised.h"


#ifndef GREEK
#define IS_UPLOAD(s) (sameas(s,"/U")||sameas(s,".U"))
#define IS_SAVE(s)   (sameas(s,"/S")||sameas(s,".S"))
#else
#define IS_UPLOAD(s) (sameas(latin(s),"/U")||sameas(latin(s),".U"))
#define IS_SAVE(s)   (sameas(latin(s),"/S")||sameas(latin(s),".S"))
#endif


struct       line *first=NULL;
struct       line *last=NULL;
struct       line *top=NULL;
struct       line *current=NULL;
promptblock_t    *msg;
int          numlines=0, numbytes=0, maxsize=262144;
char         filename[1024];
int          cx=0,cy=0,toprow=0,leftcol=0;
int          kbx=0,kby=1,kkx=0,kky=1;
int          metamode=0;
int          insertmode=0;
int          formatmode=0;
int          rmargin=75;
int          ok=0;
int          oldmetaflag;


int          maxlen;
int          vscrinc;
int          hscrinc;
int          pageinc;
int          insert;
int          format;
char         *qtechrs;
int          qtemaxc;
int          cfgtxt;
int          cbgtxt;
int          cfgfnd;
int          cbgfnd;
int          cfgblk;
int          cbgblk;
int          cfgqte;
int          cbgqte;
char         *txtupld;
char         *stins[2];
char         *stformat[5];
char         *statust;
char         *statusb;
char         *statusm;
char         *statuso;
char         *statusk;


static char *
latin(char *s)
{
  char buf[526];
  strcpy(buf,s);
  return latinize(buf);
}


int
getfg(int p)
{
  return msg_token(p,"BLACK","DARKBLUE","DARKGREEN","DARKCYAN","DARKRED",
		"DARKMAGENTA","BROWN","GREY","DARKGREY","BLUE","GREEN",
		"CYAN","RED","MAGENTA","YELLOW","WHITE")-1;
}


int
getbg(int p)
{
  return msg_token(p,"BLACK","BLUE","GREEN","CYAN","RED","MAGENTA","BROWN",
		"GREY")-1;
}


void
init()
{
  int i;

  mod_init(INI_ALL);
  msg=msg_open("vised");
  msg_setlanguage(thisuseracc.language);

  system(STTYBIN" -echo start undef stop undef intr undef susp undef");

  maxlen=msg_int(RMARGIN,20,999);
  vscrinc=msg_int(VSCRINC,1,25);
  hscrinc=msg_int(HSCRINC,1,25);
  pageinc=msg_int(PAGEINC,0,100);
  insert=msg_bool(INSERT);
  if((format=msg_token(FORMAT,"NONE","LEFT","RIGHT","CENTRE","JUSTIFY")-1)<0){
    error_fatal("LEVEL2 option INSERT (vised.msg) has bad value.");
  }
  txtupld=msg_string(TXTUPLD);
  stins[0]=msg_string(STOVR);
  stins[1]=msg_string(STINS);
  for(i=0;i<5;i++)stformat[i]=msg_string(STNONE+i);
  qtechrs=msg_string(QTECHRS);
  qtemaxc=msg_int(QTEMAXC,1,10);
  statust=msg_string(STATUST);
  statusb=msg_string(STATUSB);
  statusm=msg_string(STATUSM);
  statuso=msg_string(STATUSO);
  statusk=msg_string(STATUSK);

  if((cfgtxt=getfg(CFGTXT))<0)
    error_fatal("LEVEL2 option CFGTXT (vised.msg) has bad value.");
  if((cbgtxt=getbg(CBGTXT))<0)
    error_fatal("LEVEL2 option CBGTXT (vised.msg) has bad value.");

  if((cfgblk=getfg(CFGBLK))<0)
    error_fatal("LEVEL2 option CFGBLK (vised.msg) has bad value.");
  if((cbgblk=getbg(CBGBLK))<0)
    error_fatal("LEVEL2 option CBGBLK (vised.msg) has bad value.");

  if((cfgfnd=getfg(CFGFND))<0)
    error_fatal("LEVEL2 option CFGFND (vised.msg) has bad value.");
  if((cbgfnd=getbg(CBGFND))<0)
    error_fatal("LEVEL2 option CBGFND (vised.msg) has bad value.");

  if((cfgqte=getfg(CFGQTE))<0)
    error_fatal("LEVEL2 option CFGQTE (vised.msg) has bad value.");
  if((cbgqte=getbg(CBGQTE))<0)
    error_fatal("LEVEL2 option CBGQTE (vised.msg) has bad value.");

  thisuseronl.input[0]=0;
  /*  thisuseronl.flags&=~(OLF_MMCONCAT); */
}


int
loadfile(char *fname)
{
  FILE        *fp;
  
  if((fp=fopen(fname,"r"))!=NULL){
    while(!feof(fp)){
      char line[MAXLEN+1]={0};
      if(fgets(line,sizeof(line),fp)){
	char *cp=line;
	char tabs[MAXLEN+1], *tp=tabs;
	int i;

	memset(tabs,1,sizeof(tabs));
	line[MAXLEN]=tabs[MAXLEN]=0;
	for(cp=line;*cp;cp++)if(*cp==10 || *cp==13){
	  *cp=0;
	  break;
	}

	for(i=0;line[i]&&(*tp);i++)if(line[i]=='\t'){
	  int j;
	  for(j=0;(j<8)&&(*tp);j++)*(tp++)=32;
	} else *(tp++)=line[i];
	*tp=0;

	if(numbytes+strlen(tabs)+1>maxsize){
	  prompt(LOADERR,maxsize);
	  fclose(fp);
	  return 1;
	}
	insertline(last,tabs);
      }
    }
    fclose(fp);
    return 1;
  }
  return 0;
}


void
savefile()
{
  struct line *l;
  int mt=0;
  FILE *fp;

  if((fp=fopen(filename,"w"))==NULL){
    int i=errno;
    prompt(SAVEERR,i,sys_errlist[i]);
    error_setnotify(0);
    errno=i;
    error_fatalsys("Unable to write to %s",filename);
  }

  for(l=first;l;l=l->next){
    int i=strspn(l->text," ");
    if(!strlen(&(l->text[i])))mt++;
    else {
      for(;mt;mt--)fprintf(fp,"\n");
      fprintf(fp,"%s\n",l->text);
    }
  }
  if(numbytes>maxsize)ftruncate(fileno(fp),maxsize);

  fclose(fp);
}


void
help()
{
  int p=HELP1,c;
  switch(metamode){
  case 0:
    p=HELP1;
    break;
  case -3:
  case 3:
    p=HELP2;
    break;
  case -2:
  case 2:
    p=HELP3;
    break;
  }
  for(;p<=HELP4;p++){
    move(1,0);
    printansi(msg_get(p));
    refresh();
    while((c=mygetch())==ERR)usleep(20000);
    if(c!=10&&c!=13&&c!=KEY_ENTER)break;
  }
  showstatus();
  showtext(0);
  refresh();
}


void
upload()
{
  char fname[256],command[256],*cp,name[256],dir[256];
  FILE *fp;

  cnc_end();
  name[0]=dir[0]=0;
  xfer_add(FXM_UPLOAD,"UPLOAD-NAMELESS",txtupld,0,-1);
  thisuseronl.flags&=~(OLF_BUSY|OLF_NOTIMEOUT);
  xfer_run();
  thisuseronl.flags|=(OLF_BUSY|OLF_NOTIMEOUT);
  
  sprintf(fname,XFERLIST,getpid());

  if((fp=fopen(fname,"r"))==NULL){
/*    prompt(XFERERR); */
    goto kill;
  }

  while (!feof(fp)){
    char line[1024];

    if(fgets(line,sizeof(line),fp)){
      strcpy(dir,line);
      break;
    }
  }
  if((cp=strchr(dir,'\n'))!=NULL)*cp=0;
  fclose(fp);

  sprintf(name,TMPDIR"/vised-%05d",getpid());

  sprintf(command,"cat %s/* >%s 2>/dev/null",dir,name);
  system(command);

  if(!loadfile(name))prompt(XFERERR);

 kill:
  sprintf(command,"rm -rf %s %s",fname,dir);
  system(command);
  if(name[0]){
    sprintf(command,"rm -f %s >&/dev/null",name);
    system(command);
  }
  xfer_kill_list();
}


void
initvisual()
{
  initscr();
  scrollok(stdscr,FALSE);
  leaveok(stdscr,FALSE);

  if(has_colors()){
    int i,j;
    int cols[8]={COLOR_BLACK,COLOR_BLUE,COLOR_GREEN,COLOR_CYAN,
		 COLOR_RED,COLOR_MAGENTA,COLOR_YELLOW,COLOR_WHITE};
  
    start_color();
    for(i=0;i<8;i++)for(j=0;j<8;j++)init_pair(i+j*8,cols[i],cols[j]);
  }

  ioctl(0,KDGKBMETA,&oldmetaflag);
  ioctl(0,KDSKBMETA,K_ESCPREFIX);
  cbreak();
  noecho();
  keypad(stdscr,TRUE);
  meta(stdscr,1);
}


static void
moveinposition()
{
  int j,num=0;
  struct line *l;
  
  for(l=first;l;l=l->next){
    for(j=0;l->text[j]&&j<qtemaxc;j++)if(strchr(qtechrs,l->text[j])){
      num++;
      break;
    }
  }
  num++;
  
  if(num+1<numlines)gotoline(num,1);
  else gotoline(0,1);
}


void
run()
{
  thisuseronl.flags|=(OLF_BUSY|OLF_NOTIMEOUT);

  initvisual();
  mod_init(INI_SIGNALS);
  idlok(stdscr,TRUE);

  loadfile(filename);
  if(!numlines)insertline(NULL,"");

  if(!pageinc)pageinc=LINES-4;
  insertmode=insert;
  formatmode=format;
  rmargin=maxlen;

  erase();
  showstatus();
  
  moveinposition();

  showtext(0);
  refresh();

  nodelay(stdscr,TRUE);

  for(ok=0;!ok;){
    int c=0, pause=0;
    
    while((c=mygetch())==ERR){
      usleep(1000);
      if(++pause==25)showstatus();
      if(pause==25 && metamode<0){
	metamode=-metamode;
	showstatus();
      }
    }
    if(fl){
      fl=0;
      if(fy>=toprow && fy<=toprow+numlines-3)showtext(fy-toprow+1);
    }
      
    switch(metamode){
    case 0:
      switch(c){
      case 27:
	metamode=1;
	break;
      case CTRL('O'):
	metamode=-2;
	break;
      case CTRL('K'):
	metamode=-3;
	break;
      case KEY_UP:
      case CTRL('P'):
	movecursor(-1,0);
	break;
      case KEY_DOWN:
      case CTRL('N'):
	movecursor(1,0);
	break;
      case KEY_LEFT:
      case CTRL('B'):
	movecursor(0,-1);
	break;
      case KEY_RIGHT:
      case CTRL('F'):
	movecursor(0,1);
	break;
      case KEY_HOME:
      case CTRL('A'):
	movecursor(0,-2);
	break;
      case KEY_END:
      case CTRL('E'):
	movecursor(0,2);
	break;
      case CTRL('T'):
      case KEY_PPAGE:
	movepage(-pageinc);
	break;
      case CTRL('V'):
      case KEY_NPAGE:
	movepage(pageinc);
	break;
      case CTRL('Q'):
	movepage(-numlines);
	break;
      case CTRL('W'):
	movepage(numlines);
	break;
      case CTRL('R'):
	help();
	break;
      case CTRL('L'):
	while(mygetch()!=ERR);
	centerline();
	showstatus();
	showtext(0);
	clearok(stdscr,TRUE);
	refresh();
	break;
      case CTRL('U'):
	dosearch();
	break;
      case CTRL('Y'):
	noblock();
	delline();
	break;
      case CTRL('D'):
	noblock();
	deletechar();
	break;
      case 8:
      case 127:
      case KEY_BACKSPACE:
	noblock();
	backspace();
	break;
      case 10:
      case 13:
	if(current->text&&IS_SAVE(current->text)){
	  backspace();
	  backspace();
	  savefile();
	  ok=1;
	} else if(current->text&&IS_UPLOAD(current->text)){
	  backspace();
	  backspace();
	  out_setflags(OFL_AFTERINPUT);
	  prompt(CLRSCR);
	  upload();
	  clearok(stdscr,1);
	  movepage(numlines);
	  centerline();
	  showtext(0);
	  showstatus();
	} else if(current->text&&inp_isX(current->text)){
	  backspace();
	  if(doquit()){
	    unlink(filename);
	    ok=-1;
	  } else {
	    showtext(0);
	    showstatus();
	  }
	} else {
	  if(NOWRAP)formatline();
	  else newline();
	}
	break;
      case 9:
	{
	  int i;
	  for(i=0;i<4;i++)inschar(32,0);
	  showtext(0);
	}
	break;
	break;
      case CTRL('C'):
	if(doquit()){
	  unlink(filename);
	  ok=-1;
	} else showstatus();
	break;
      case KEY_SUSPEND:
      case CTRL('Z'):
	out_setflags(OFL_AFTERINPUT);
	prompt(CLRSCR);
	upload();
	clearok(stdscr,1);
	movepage(numlines);
	centerline();
	showtext(0);
	showstatus();
	break;
      case CTRL('X'):
	golined();
	break;
      case CTRL('S'):
	savefile();
	ok=1;
	break;
      default:
	noblock();
	if(c>=32 && c<=255)inschar(c,1);
      }
      break;
    case 1:      /* META-<chr> COMBINATIONS */
      {
	char s[2],t[2];
	s[0]=c;
	s[1]=0;
	strcpy(t,latinize(s));
	c=toupper(t[0]);
	switch(c){
	case 'v':
	case 'V':
	  movepage(-pageinc);
	  break;
	case '<':
	case ',':
	  movepage(-numlines);
	  break;
	case '>':
	case '.':
	  movepage(numlines);
	  break;
	case 'I':
	  insertmode^=1;
	  break;
	case 'L':
	  formatmode=LEFT;
	  break;
	case 'C':
	  formatmode=CENTRE;
	  break;
	case 'R':
	  formatmode=RIGHT;
	  break;
	case 'J':
	  formatmode=JUSTIFY;
	  break;
	case 'N':
	  formatmode=NOFORMAT;
	  break;
	case 'F':
	  noblock();
	  formatpara();
	  showtext(0);
	  break;
	case 'X':
	  savefile();
	  ok=1;
	  break;
	case 'Q':
	  if(doquit()){
	    unlink(filename);
	    ok=-1;
	  } else showstatus();
	  break;
	case '%':
	  replace();
	  break;
	case CTRL('R'):
	  help();
	  break;
	}
      }
      metamode=0;
      showstatus();
      break;
    case -2:
    case 2:
      {
	char s[2],t[2];
	s[0]=c;
	s[1]=0;
	strcpy(t,latinize(s));
	c=toupper(t[0]);
	switch(c){
	case 'I':
	  insertmode^=1;
	  break;
	case 'L':
	  formatmode=LEFT;
	  break;
	case 'C':
	  formatmode=CENTRE;
	  break;
	case 'R':
	  formatmode=RIGHT;
	  break;
	case 'J':
	  formatmode=JUSTIFY;
	  break;
	case 'N':
	  formatmode=NOFORMAT;
	  break;
	case CTRL('R'):
	  help();
	  break;
	}
	if(metamode>0)showstatus();
	metamode=0;
	break;
      }
    case -3:
    case 3:
      {
	char s[2],t[2];
	s[0]=c;
	s[1]=0;
	strcpy(t,latinize(s));
	c=toupper(t[0]);
	switch(c){
	case 'B':
	  kbx=cx;
	  kby=cy;
	  showtext(0);
	  break;
	case 'K':
	  kkx=cx;
	  kky=cy;
	  showtext(0);
	  break;
	case 'Y':
	  delblock();
	  /*centerline();*/
	  showtext(0);
	  break;
	case 'V':
	case 'M':
	  copyblock(1);
	  break;
	case 'C':
	  copyblock(0);
	  break;
	case 'F':
	  find();
	  break;
	case 'A':
	  replace();
	  break;
	case 'R':
	  rightmargin();
	  break;
	case CTRL('R'):
	  help();
	  break;
	}
	if(metamode>0)showstatus();
	metamode=0;
	break;
      }
    }
  }
}


void
done()
{
  ioctl(0,KDSKBMETA,oldmetaflag);
  endwin();
  out_setflags(OFL_AFTERINPUT);
  prompt(CLRSCR);
  system(STTYBIN" -echo start undef stop undef intr undef susp undef");
  thisuseronl.flags&=~(OLF_BUSY|OLF_NOTIMEOUT);
}


int
main(int argc, char *argv[])
{
  mod_setprogname(argv[0]);
  if(argc==3 && (maxsize=atoi(argv[2]))){
    init();
    strcpy(filename,argv[1]);
    run();
    done();
    exit(ok==-1);
  }
  return 1;
}

