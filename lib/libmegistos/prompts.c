/*****************************************************************************\
 **                                                                         **
 **  FILE:     prompts.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, June 94                                                   **
 **  PURPOSE:  Access and use customizable system prompts in compiled .mbk  **
 **            files.                                                       **
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
 * Revision 1.1  2001/04/16 14:51:07  alexios
 * Initial revision
 *
 * Revision 0.6  1999/07/18 21:01:53  alexios
 * Changed a few fatal() calls to fatalsys().
 *
 * Revision 0.5  1998/12/27 14:31:16  alexios
 * Added autoconf support. Added code to recognise prompt files
 * by magic number and commit sepuku if they seem corrupted.
 *
 * Revision 0.4  1998/07/24 10:08:57  alexios
 * Made use of new error reporting.
 *
 * Revision 0.3  1997/11/06 20:03:54  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/11/05 10:58:35  alexios
 * Added a setlanguage() to opnmsg() -- possible bug there.
 *
 * Revision 0.1  1997/08/26 16:35:17  alexios
 * First registered revision. Adequate.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif




#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_STRINGS_H 1
#define WANT_CTYPE_H 1
#define WANT_UNISTD_H 1
#include <bbsinclude.h>
#include "config.h"
#include "errors.h"
#include "useracc.h"
#include "miscfx.h"
#include "prompts.h"


char       *msgbuf;
promptblk  *curblk=NULL;
promptblk  *lastblk=NULL;
promptblk  *sysblk=NULL;
long       lastprompt;
char       postfix[80];
int        numlangs;
char       languages[NUMLANGUAGES][64];


promptblk *
opnmsg(char *name)
{
  char fname[256], magic[4];
  long result;

  lastblk=curblk;
  curblk=(promptblk *)alcmem(sizeof(promptblk));

  sprintf(fname,"%s/%s.mbk", MBKDIR, name);
  if((curblk->handle=fopen(fname,"r"))==NULL){
    fatalsys("Unable to open prompt file %s",fname);
  }
  if (fread(magic,sizeof(magic),1,curblk->handle)!=1){
    fatalsys("Unable to read magic number from prompt file %s",fname);
  }
  if(strncmp(magic,MBK_MAGIC,4)){
    fatal("Corrupted file %s. Remove it and use msgidx to recreate.",fname);
  }
  if (fread(&(curblk->indexsize),sizeof(long),1,curblk->handle)!=1){
    fatalsys("Corrupted prompt file %s (indexcount)",fname);
  }
  if (fread(&(curblk->langoffs),sizeof(curblk->langoffs),1,curblk->handle)!=1){
    fatalsys("Corrupted prompt file %s (langoffs)",fname);
  }

  curblk->indexsize++;
  curblk->index=(long *)alcmem(curblk->indexsize*sizeof(long));
  result=fread(curblk->index,sizeof(long),curblk->indexsize,curblk->handle);
  if(result!=curblk->indexsize){
    fatal("Corrupted prompt file %s (index)",fname);
  }
  curblk->indexsize--;
  curblk->language=0;
  sprintf(curblk->fname,"%s.mbk",name);
  lastprompt=-1;

  if(thisshm)setlanguage(thisuseracc.language);

  return curblk;
}


void
setmbk(promptblk *blk)
{
  lastblk=curblk;
  curblk=blk;
  lastprompt=-1;
}


void
rstmbk()
{
  if(!lastblk)return;
  curblk=lastblk;
  lastprompt=-1;
}


char *
getmsglang(int num,int language)
{
  long offset,size;
  int oldnum;

  language=language%(NUMLANGUAGES);

  if(!curblk)return NULL;
  oldnum=num;
  num+=curblk->langoffs[language];

  if(num==lastprompt)return msgbuf;
  if(!msgbuf)msgbuf=alcmem(MSGBUFSIZE);

  if(num<0||num>curblk->indexsize){
    fatal("Prompt %d (lang %d) out of range (1-%d) in %s",
	  (void *)num,(void *)language,
	  (void *)curblk->indexsize,curblk->fname);
  }

  offset=curblk->index[num-1];
  if(fseek(curblk->handle,offset,SEEK_SET)){
    fatalsys("Failed to fseek() prompt #%d location %ld in %s",
	  (void *)oldnum,(void *)offset,curblk->fname);
  }
  size=curblk->index[num]-offset;
  if(size>=MSGBUFSIZE)size=MSGBUFSIZE-1;
  size=MSGBUFSIZE-1;
  if(fread(msgbuf,size,1,curblk->handle)!=1){
/*    fatal("Error reading prompt %d (lang %d) in %s (s=%ld i=%ld o=%ld)",
	  (void *)oldnum,(void *)language,
	  curblk->fname,(void *)size,
	  (void *)curblk->index[num],(void *)offset); */
  }
  lastprompt=num;
  return msgbuf;
}


char *
getpfixlang(int num,int value,int language)
{
  long offset,size;

  postfix[0]=0;
  num+=(value!=1)+curblk->langoffs[language];
  if(num<1||num>curblk->indexsize){
    fatal("Prompt number %d out of range (1-%d) in file %s",
	  (void *)num,(void *)curblk->indexsize,curblk->fname,0,0,0);
  }
  offset=curblk->index[num-1];
  if((size=curblk->index[num]-offset)>79)return postfix;
  if(fseek(curblk->handle,offset,SEEK_SET)){
    fatalsys("Failed to fseek() prompt location %ld in file %s",
	  (void *)offset,curblk->fname);
  }
  if(fread(postfix,size,1,curblk->handle)!=1){
    fatalsys("Error reading prompt %d in file %s %ld %ld %ld",
	  (void *)num,curblk->fname,(void *)size,(void *)curblk->index[num],(void *)offset,0);
  }
  return postfix;
}


void
clsmsg(promptblk *blk)
{
  if(!curblk)return;
  if(blk && blk->fname[0]){
    fclose(blk->handle);
    free(blk->index);
    blk->fname[0]=0;
    free(blk);
    blk=NULL;
    if (msgbuf) {
      free(msgbuf);
      msgbuf=NULL;
    }
  }
}


char *
lastwd(char *s)                               
{
  char *cp;
  
  if(!s || !(*s))return(s);
  for(cp=s+strlen(s)-1;cp>=s && isspace(*cp);cp--){
    if(cp==s)return(cp);
  }
  for (;cp>=s && !isspace(*cp);cp--){
    if(cp==s)return(cp);
  }
  return(cp+1);
}


long
lngopt(int num,long floor,long ceiling)
{
  long temp;
  
  if(sscanf(lastwd(getmsg(num)),"%ld",&temp)){
    if(temp>=floor && temp<=ceiling)return(temp);
    fatal("Long numeric option %d in file %s is out of range",
	   (void *)num,curblk->fname,0,0,0,0);
  }
  fatal("Long numeric option %d in file %s has bad value",
	(void *)num,curblk->fname,0,0,0,0);
  return -1;
}


unsigned
hexopt(int num,unsigned floor,unsigned ceiling)
{
  long temp;
  
  if(sscanf(lastwd(getmsg(num)),"%lx",&temp)){
    if(temp>=floor && temp<=ceiling)return((unsigned)temp);
    fatal("Hex numeric option %d in file %s is out of range",
	  (void *)num,curblk->fname,0,0,0,0);
  }
  fatal("Hex numeric option %d in file %s has bad value",
	(void *)num,curblk->fname,0,0,0,0);
  return -1;
}


int
numopt(int num, int floor, int ceiling)            
{
  return((int)lngopt(num,floor+0L,ceiling+0L));
}


int
ynopt(int num)                           
{
  int rc=0;

  switch(toupper(*lastwd(getmsg(num)))){
  case 'Y':
    rc=1;
  case 'N':
    return(rc);
  }
  fatal("Yes/No option %d in file %s has bad value",
	(void *)num,curblk->fname,0,0,0,0);
  return -1;
}


char
chropt(int num)
{
  return(*lastwd(getmsg(num)));
}


char *
stgopt(int msgnum)                     
{
  char *cp,*mp;
  
  cp=alcmem(strlen(mp=getmsg(msgnum))+1);
  strcpy(cp,mp);
  return(cp);
}


int
tokopt(int msgnum,char *toklst, ...)
{
  char **ppt,*token;
  int i;
  
  token=lastwd(getmsg(msgnum));
  for(ppt=&toklst,i=1;*ppt!=NULL;ppt++,i++){
    if(strcmp(token,*ppt)==0)return i;
  }
  return(0);
}


void
setlanguage(int l)
{
  if(!curblk)return;
  curblk->language=(l-1)%(NUMLANGUAGES);
  sysblk->language=(l-1)%(NUMLANGUAGES);
  lastprompt=-1;
}
