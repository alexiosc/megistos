/*****************************************************************************\
 **                                                                         **
 **  FILE:     menuman.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 94, Version 0.1 alpha                                **
 **            B, September 95, Version 0.2                                 **
 **            C, August 97, Version 1.0                                    **
 **  PURPOSE:  Provide menuing interface for the BBS.                       **
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
 * Revision 1.2  2001/04/16 21:56:33  alexios
 * Completed 0.99.2 API, dragged all source code to that level (not as easy as
 * it sounds).
 *
 * Revision 1.9  1999/08/04 01:00:13  alexios
 * Fixed silly bug that caused exits from menuman-handled submenus
 * to not update the current page description.
 *
 * Revision 1.8  1999/07/18 21:46:19  alexios
 * Changed a few error_fatal() calls to error_fatalsys(). Cosmetic changes.
 *
 * Revision 1.7  1998/12/27 16:00:47  alexios
 * Added autoconf support. Various minor fixes.
 *
 * Revision 1.6  1998/08/14 11:43:40  alexios
 * Flagged relogons so that bbsd can audit them.
 *
 * Revision 1.5  1998/07/26 21:01:49  alexios
 * Fixed slight relogon problems.
 *
 * Revision 1.4  1998/07/24 10:21:37  alexios
 * Fixed problem with exit codes that caused user to be kicked
 * out after a fatal error in some module by making menuman
 * returning 126 when the user chooses to leave the system.
 * Migrated to bbslib 0.6.
 *
 * Revision 1.3  1997/11/06 20:12:43  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 1.2  1997/11/06 16:56:15  alexios
 * Added code to detect and issue the relogon command.
 *
 * Revision 1.1  1997/09/01 10:30:04  alexios
 * Fixed erroneous check for the ANSI enable flag in the user
 * preference field instead of thisuseronl.flags&OLF_ANSION.
 *
 * Revision 1.0  1997/08/28 11:00:36  alexios
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
#define WANT_SYS_STAT_H 1
#define WANT_FCNTL_H 1
#include <bbsinclude.h>

#define I_AM_MENUMAN
#include "bbs.h"
#include "menuman.h"
#include "mbk_menuman.h"


promptblock_t *msg;

struct pageidx {
  char page[16];
  long offset;
  int flags;
};


FILE               *pagefile=NULL;
struct pageidx     *pageindex=NULL;
int                numpages=0;
union menumanpage  curpage;
struct pageidx     *curidx=NULL;
int                pagetype=0;

int  defccr;
int  useshm;
int  retmenu;
int  extmenu;
char *toppag;
char *extpag;
char *menpro;
char *menepi;
char *shmbeg;
char *shmopt;
char *shmlop;
char *shmend;
char *shmprm;
char *relogstg;
int  keyrel;


void
describe()
{
  int i;
  if(!curpage.m.descr[0][0])for(i=0;i<NUMLANGUAGES;i++){
    strcpy(thisuseronl.descr[i],msg_getl(DEFDESCR,i));
  } else memcpy(thisuseronl.descr,curpage.e.descr,sizeof(thisuseronl.descr));
}


void
loadindex()
{
  FILE *fp;
  
  if((fp=fopen(MENUMANINDEX,"r"))==NULL){
    error_fatalsys("Unable to open %s",MENUMANINDEX);
  }
  if(pageindex)free(pageindex);
  numpages=0;
  while(!feof(fp)){
    char line[256];
    char page[256];
    long offset;
    int flags=0;
    
    if(!fgets(line,256,fp))continue;
    if(sscanf(line,"%s %ld %x",page,&offset,&flags)!=3){
      fclose(fp);
      error_fatal("Menuman index %s bad format",MENUMANINDEX);
    }
    numpages++;
    pageindex=realloc(pageindex,sizeof(struct pageidx)*numpages);
    memset(&pageindex[numpages-1],0,sizeof(struct pageidx));
    strncpy(pageindex[numpages-1].page,page,15);
    pageindex[numpages-1].offset=offset;
    pageindex[numpages-1].flags=flags;
  }
  fclose(fp);
}


void
init()
{
  int mmangopage();
  void goback();

  mod_init(INI_ALL);
  msg=msg_open("menuman");
  msg_setlanguage(thisuseracc.language);

  defccr=msg_int(DEFCCR,0,32767);

  if((useshm=msg_token(USESHM,"PROMPT","SHORT")-1)<0){
    error_fatal("LEVEL2 option USESHM (menuman.msg) has bad value.");
  }
  if((retmenu=msg_token(RETMENU,"SHORT","LONG")-1)<0){
    error_fatal("LEVEL2 option RETMENU (menuman.msg) has bad value.");
  }
  if((extmenu=msg_token(EXTMENU,"SHORT","LONG")-1)<0){
    error_fatal("LEVEL2 option EXTMENU (menuman.msg) has bad value.");
  }

  toppag=msg_string(TOPPAG);
  extpag=msg_string(EXTPAG);
  menpro=strdup(msg_get(MENPRO));
  menepi=strdup(msg_get(MENEPI));
  shmbeg=strdup(msg_get(SHMBEG));
  shmopt=strdup(msg_get(SHMOPT));
  shmlop=strdup(msg_get(SHMLOP));
  shmend=strdup(msg_get(SHMEND));
  shmprm=strdup(msg_get(SHMPRM));

  relogstg=msg_string(RELOGSTG);
  keyrel=msg_int(KEYREL,0,129);
  
  if((pagefile=fopen(MENUMANPAGES,"r"))==NULL){
    error_fatalsys("Unable to open %s",MENUMANPAGES);
  }

  loadindex();
  if(!strlen(thisuseronl.curpage)){
    strcpy(thisuseronl.curpage,toppag);
    out_setflags(OFL_AFTERINPUT);
  }
  if(thisuseronl.flags&OLF_MMCALLING)goback();
  else {
    mmangopage(thisuseronl.curpage);
  }
}


void
done()
{
  msg_close(msg);
  fclose(pagefile);
}


int
pagecmp(const void *a, const void *b)
{
  const struct pageidx *index1=a;
  const struct pageidx *index2=b;
  return(strcmp(index1->page,index2->page));
}


int
retrievepage(char *page)
{
  struct pageidx *p;

  p=bsearch(page,pageindex,numpages,sizeof(struct pageidx),pagecmp);
  if(!p) return 0;
  curidx=p;

  if(fseek(pagefile,curidx->offset,SEEK_SET)) {
    error_fatalsys("Unable to read page %s",curidx->page);
  }
  if(fread(&curpage,sizeof(curpage),1,pagefile)!=1){
    error_fatalsys("Unable to read page %s",curidx->page);
  }

  return 1;
}


int
checkpperm(char *page)
{
  struct pageidx *p;
  union  menumanpage mmp;

  if(!page || !page[0]) return 0;

  p=bsearch(page,pageindex,numpages,sizeof(struct pageidx),pagecmp);
  if(!p) return 0;
  
  if(fseek(pagefile,p->offset,SEEK_SET)){
    error_fatalsys("Unable to read page %s",p->page);
  }
  if(fread(&mmp,sizeof(mmp),1,pagefile)!=1){
    error_fatalsys("Unable to read page %s",p->page);
  }

  if(hassysaxs(&thisuseracc,USY_MASTERKEY)) return 1;
  if(mmp.m.class[0]&&!sameas(mmp.m.class,thisuseracc.curclss)) return 0;
  if(!key_owns(&thisuseracc,mmp.m.key)) return 0;
  return 1;
}


int
mmangopage(char *pagename)
{
  if(!checkpperm(pagename)) {
    prompt(NOAXES1,pagename);
    return 0;
  }
  if((thisuseronl.flags&OLF_MMGCDGO)==0)
    strncpy(thisuseronl.prevpage,thisuseronl.curpage,15);
  strncpy(thisuseronl.curpage,pagename,15);
  thisuseronl.curpage[15]=0;
  if(retrievepage(pagename)){
    if(thisuseronl.flags&OLF_MMGCDGO){
      thisuseronl.flags&=~OLF_MMGCDGO;
      strncpy(thisuseronl.prevpage,curpage.m.prev,15);
    }
    if(curpage.m.type==PAGETYPE_MENU){
      int i;
      for(i=0;curpage.m.opts[i].opt && i<MENUOPTNUM;i++){
	if(!checkpperm(curpage.m.opts[i].name)){
	  curpage.m.opts[i].opt*=-1;
	}
      }
    }
    thisuseronl.credspermin=
      (curpage.m.creds==DEFAULTCCR)?defccr:curpage.m.creds;
    describe();
    return 1;
  }
  return 0;
}


void
showfile (union menumanpage *p)
{
  char rawname[256], *cp;
  char fname[256];
  int ansi=thisuseronl.flags&OLF_ANSION,i;

  if(p->m.type!=PAGETYPE_MENU && p->f.type!=PAGETYPE_FILE)return;
  if((cp=strrchr(p->m.fname,'/'))==NULL)cp=p->m.fname;
  strcpy(rawname,cp);
  if((cp=strstr(rawname,".ans"))!=NULL)*cp=0;
  else if((cp=strstr(rawname,".asc"))!=NULL)*cp=0;
  
  for(i=thisuseracc.language-1;i>=0;i--){
    sprintf(fname,"%s/%s-%d.%s",MENUMANDIR,rawname,i,ansi?"ans":"asc");
    if(out_printfile(fname))return;
    sprintf(fname,"%s/%s-%d.%s",MENUMANDIR,rawname,i,(!ansi)?"ans":"asc");
    if(out_printfile(fname))return;
  }
  sprintf(fname,"%s/%s.%s",MENUMANDIR,rawname,ansi?"ans":"asc");
  if(out_printfile(fname))return;
  sprintf(fname,"%s/%s.%s",MENUMANDIR,rawname,(!ansi)?"ans":"asc");
  if(out_printfile(fname))return;
  out_printfile(rawname);
  error_log("Unable to locate page file similar to %s/%s",MENUMANDIR,rawname);
}


void
shortmenu(int which)
{
  if(which){
    int i;

    print(shmbeg);
    for(i=0;curpage.m.opts[i].opt && i<MENUOPTNUM;i++){
      if(curpage.m.opts[i].opt>0){
	struct pageidx *p=NULL;
	p=bsearch(curpage.m.opts[i].name,pageindex,numpages,
		  sizeof(struct pageidx),pagecmp);
	if(p->flags&MPF_HIDDEN)continue;
	print(shmopt,toupper(curpage.m.opts[i].opt));
      }
    }
    print(shmlop,'X');
    print(shmend);
  } else {
    print(shmprm);
  }
}


void
byebye(int relog)
{
  char fname[256];

  if(relog){
    sprintf(fname,"%s/.relog-%s",ONLINEDIR,thisuseronl.channel);
    close(creat(fname,0660));
  }
  sprintf(fname,"%s/.logout-%s",ONLINEDIR,thisuseronl.channel);
  close(creat(fname,0660));
}


static int
checkexit()
{
  for(;;){
    int i;
    for(i=0;i<NUMLANGUAGES;i++){
      strcpy(thisuseronl.descr[i],msg_getl(XITDESCR,i));
    }
    
    prompt(RUSXITL);
    cnc_end();
    inp_get(0);
    cnc_begin();
    if(!margc || inp_reprompt())continue;
    else if(margc && sameas(relogstg,margv[0])){
      if(key_owns(&thisuseracc,keyrel)){
	thisuseronl.flags|=OLF_RELOGGED;
	byebye(1);
	return 2;
      } else {
	describe();
	return 0;
      }
    } else switch(cnc_yesno()){
    case 'Y':
      byebye(0);
      return 1;
    default:
      describe();
      return 0;
    }
  }

  return 0;
}


int
handleexit()
{
  if(sameas(curpage.m.name,toppag) || curpage.m.prev[0]==0
     || sameas(curpage.m.prev,extpag)){
    return checkexit();
  } else mmangopage(curpage.m.prev);
  return 0;
}


void
goback()
{
  char temp[16]={0};
  strncpy(temp,thisuseronl.prevpage,15);
  thisuseronl.flags|=OLF_MMEXITING;
  mmangopage(temp);
}


int
handlemenupage()
{
  int givenmenu=0;

  if((thisuseronl.flags&OLF_MMEXITING)&&(!extmenu))givenmenu=1;
  thisuseronl.flags&=~OLF_MMEXITING;
  describe();

  out_setflags(OFL_AFTERINPUT);
  for(;;){

  what_a_disgrace:   /* Will it make you feel better if I say Microsoft uses */
                     /* these? Naah... Well, I'm ashamed of myself! :-)      */

    if(!givenmenu){
      givenmenu=1;
      print(menpro);
      showfile(&curpage);
      print(menepi);
      shortmenu(useshm);
    } else shortmenu(1);

    inp_get(0);
    cnc_begin();
    if(margc && inp_isX(cnc_nxtcmd)){
      switch(handleexit()){
      case 2:
	/* for(;;)sleep(666666); */
      case 1:
	return 0;
      }
    } else if(margc && sameas(cnc_nxtcmd,"?")) {
      cnc_end();
      givenmenu=0;
    } else if(!margc && !inp_reprompt()) {
      cnc_end();
      if(retmenu)givenmenu=0;
      continue;
    } else if(inp_reprompt()) {
      continue;
    }else {
      int i;
      char c=toupper(cnc_chr());
      for(i=0;curpage.m.opts[i].opt && i<MENUOPTNUM;i++){
	if(toupper(curpage.m.opts[i].opt)==c){
	  mmangopage(curpage.m.opts[i].name);
	  return 1;
	} else if (toupper(-curpage.m.opts[i].opt)==c){
	  prompt(NOAXES2,c);
	  goto what_a_disgrace;
	}
      }
      prompt(ERRSEL,c);
    }
  }
}


void
handlefilepage()
{
  showfile(&curpage);
  goback();
}


void
handleexecpage()
{
  char *s, inpstr[2048+256];
  char fname[2048];

  s=cnc_all();
  sprintf(inpstr,"%s%s",curpage.e.input,((s==NULL || !*s)?"\0":s));
  memset(thisuseronl.input,0,sizeof(thisuseronl.input));
  strncpy(thisuseronl.input,inpstr,
	  max(strlen(inpstr),sizeof(thisuseronl.input)));
  describe();

  thisuseronl.flags|=OLF_MMCALLING|OLF_MMEXITING;
  if(thisuseronl.input[0])thisuseronl.flags|=OLF_MMCONCAT;

  mod_done(INI_ALL);
  sprintf(fname,BINDIR"/%s",curpage.e.fname);
  execlp(fname,fname,"--run",NULL);
  prompt(CANTXEC,curpage.e.name);
  exit(0);
}


void
handlerunpage()
{
  thisuseronl.flags|=OLF_BUSY|OLF_NOTIMEOUT;
  describe();
  mod_done(INI_SIGNALS|INI_INPUT);
  system(STTYBIN" sane intr 0x03");
  system(curpage.r.command);
  system(STTYBIN" -echo start undef stop undef intr undef susp undef");
  mod_regpid(thisuseronl.channel);
  mod_init(INI_SIGNALS|INI_INPUT);
  thisuseronl.flags&=~(OLF_BUSY|OLF_NOTIMEOUT);
  inp_resetidle();
  mmgopage(thisuseronl.prevpage);
}


void
run()
{
  for(;;){
    if(sameas(thisuseronl.curpage,extpag)){
      int retval=checkexit();
      if(retval)return;
      goback();
    }
    switch(curpage.m.type){
    case PAGETYPE_MENU:
      if(!handlemenupage()) return;
      break;
    case PAGETYPE_FILE:
      handlefilepage();
      break;
    case PAGETYPE_EXEC:
      handleexecpage();
      break;
    case PAGETYPE_RUN:
      handlerunpage();
      break;
    }
  }
}


int
main(int argc, char **argv)
{
  mod_setprogname(argv[0]);
  init();    /* Why is this so TurboVision-like? Heh heh */
  run();
  done();    /* Sorry, couldn't help it -- I had to. [A] */
  return 126;
}
