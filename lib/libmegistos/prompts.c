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
 * Revision 1.2  2001/04/16 21:56:29  alexios
 * Completed 0.99.2 API, dragged all source code to that level (not as easy as
 * it sounds).
 *
 * Revision 0.6  1999/07/18 21:01:53  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
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
const char *__RCS=RCS_VER;
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
#include "bbsmod.h"


#define msg_get_nobot(x) msg_getl_bot((x),(msg_cur->language),0)


char           *msg_buffer;
promptblock_t  *msg_cur=NULL;
promptblock_t  *msg_last=NULL;
promptblock_t  *msg_sys=NULL;

static long       lastprompt;

static char       postfix[80];
int               msg_numlangs;
char              msg_langnames[NUMLANGUAGES][64];


void
msg_init()
{
  FILE *langfp;

  msg_numlangs=0;
  if((langfp=fopen(LANGUAGEFILE,"r"))!=NULL){
    while(!feof(langfp)){
      char line[1024];
      
      if(fgets(line,1024,langfp)){
	char *cp=line;
	char *nlp=strrchr(line,10);
	
	if(nlp)*nlp=0;
	while(*cp && isspace(*cp))cp++;
	if(*cp && *cp!='#')strcpy(msg_langnames[msg_numlangs++],cp);
      }
    }
    fclose(langfp);
  }
}


promptblock_t *
msg_open(char *name)
{
  char fname[256], magic[4];
  long result;

  msg_last=msg_cur;
  msg_cur=(promptblock_t *)alcmem(sizeof(promptblock_t));

  sprintf(fname,"%s/%s.mbk", MBKDIR, name);
  if((msg_cur->handle=fopen(fname,"r"))==NULL){
    error_fatalsys("Unable to open prompt file %s",fname);
  }
  if (fread(magic,sizeof(magic),1,msg_cur->handle)!=1){
    error_fatalsys("Unable to read magic number from prompt file %s",fname);
  }
  if(strncmp(magic,MBK_MAGIC,4)){
    error_fatal("Corrupted file %s. Remove it and use msgidx to recreate.",fname);
  }
  if (fread(&(msg_cur->indexsize),sizeof(long),1,msg_cur->handle)!=1){
    error_fatalsys("Corrupted prompt file %s (indexcount)",fname);
  }
  if (fread(&(msg_cur->langoffs),sizeof(msg_cur->langoffs),1,msg_cur->handle)!=1){
    error_fatalsys("Corrupted prompt file %s (langoffs)",fname);
  }

  msg_cur->indexsize++;
  msg_cur->index=(long *)alcmem(msg_cur->indexsize*sizeof(long));
  result=fread(msg_cur->index,sizeof(long),msg_cur->indexsize,msg_cur->handle);
  if(result!=msg_cur->indexsize){
    error_fatal("Corrupted prompt file %s (index)",fname);
  }
  msg_cur->indexsize--;
  msg_cur->language=0;
  sprintf(msg_cur->fname,"%s.mbk",name);
  lastprompt=-1;

  if(thisshm)msg_setlanguage(thisuseracc.language);

  return msg_cur;
}


void
msg_set(promptblock_t *blk)
{
  msg_last=msg_cur;
  msg_cur=blk;
  lastprompt=-1;
}


void
msg_reset()
{
  if(msg_last==NULL)return;
  msg_cur=msg_last;
  lastprompt=-1;
}


static char *
msg_botprocess(int num, int lang, char *s)
{
  static char *botbuf=NULL;
  char tmp[32];
  char *cp=s;
  int count=0;

  if(botbuf==NULL){
    botbuf=alcmem(256<<10); /* 256k, allocated on demand only */
  }
  
  bzero(botbuf,sizeof(botbuf));
  
  /* xxx will be updated later */
  sprintf(botbuf,"601 xxx %s %d %d\n",msg_cur->fname,num,lang);

  for(cp=s;*cp;cp++){
    if(*cp=='%'){
      char *sp=cp;
    
      if(*(cp+1)=='%'){
	cp++;
	continue;
      }

      for(cp++;(*cp) && strcspn(cp,"diouxXeEfgcspn");cp++);
      
      if(*cp){
	count++;
	strcat(botbuf,"602 ");
	strncat(botbuf,sp,cp-sp+1);
	strcat(botbuf,"\n");
      }

      *sp=1;			/* 'mark' the original format specifier */
    }
  }

  sprintf(tmp,"601 %3d",count);
  memcpy(botbuf,tmp,7);		/* Copy just the "601 xxx" part */
  strcat(botbuf,"603 ");
  strcat(botbuf,s);
  strcat(botbuf,"\n699\n");

  return botbuf;
}


char *
msg_getl_bot(int num, int language, int checkbot)
{
  long offset=0,size;
  int oldnum;

  language=language%(NUMLANGUAGES);

  if(!msg_cur)return NULL;
  oldnum=num;
  num+=msg_cur->langoffs[language];

  if(num==lastprompt)return msg_buffer;
  if(!msg_buffer)msg_buffer=alcmem(MSGBUFSIZE);

  if(num<0||num>msg_cur->indexsize){
    error_fatal("Prompt %d (lang %d) out of range (1-%d) in %s",
		(void *)num,(void *)language,
		(void *)msg_cur->indexsize,msg_cur->fname);
  }

  offset=msg_cur->index[num-1];
  if(fseek(msg_cur->handle,offset,SEEK_SET)){
    error_fatalsys("Failed to fseek() prompt #%d location %ld in %s",
		   (void *)oldnum,(void *)offset,msg_cur->fname);
  }
  size=msg_cur->index[num]-offset;
  if(size>=MSGBUFSIZE)size=MSGBUFSIZE-1;
  size=MSGBUFSIZE-1;
  if(fread(msg_buffer,size,1,msg_cur->handle)!=1){
/*    error_fatal("Error reading prompt %d (lang %d) in %s (s=%ld i=%ld o=%ld)",
	  (void *)oldnum,(void *)language,
	  msg_cur->fname,(void *)size,
	  (void *)msg_cur->index[num],(void *)offset); */
  }
  lastprompt=num;

  /* If this is a bot, format the prompt for it. */

  if(mod_isbot() || 
     (thisshm!=NULL && checkbot!=0 && (thisuseronl.flags&OLF_ISBOT))){
    lastprompt=-1;
    return msg_botprocess(num,language,msg_buffer);
  }

  return msg_buffer;
}


char *
msg_getunitl(int num,int value,int language)
{
  long offset,size;

  postfix[0]=0;
  num+=(value!=1)+msg_cur->langoffs[language];
  if(num<1||num>msg_cur->indexsize){
    error_fatal("Prompt number %d out of range (1-%d) in file %s",
	  (void *)num,(void *)msg_cur->indexsize,msg_cur->fname,0,0,0);
  }
  offset=msg_cur->index[num-1];
  if((size=msg_cur->index[num]-offset)>79)return postfix;
  if(fseek(msg_cur->handle,offset,SEEK_SET)){
    error_fatalsys("Failed to fseek() prompt location %ld in file %s",
	  (void *)offset,msg_cur->fname);
  }
  if(fread(postfix,size,1,msg_cur->handle)!=1){
    error_fatalsys("Error reading prompt %d in file %s %ld %ld %ld",
	  (void *)num,msg_cur->fname,(void *)size,(void *)msg_cur->index[num],(void *)offset,0);
  }
  return postfix;
}


void
msg_close(promptblock_t *blk)
{
  if(!msg_cur)return;
  if(blk && blk->fname[0]){
    fclose(blk->handle);
    free(blk->index);
    blk->fname[0]=0;
    free(blk);
    blk=NULL;
    if (msg_buffer) {
      free(msg_buffer);
      msg_buffer=NULL;
    }
  }
}


static char *
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
msg_long(int num,long floor,long ceiling)
{
  long temp;
  
  if(sscanf(lastwd(msg_get_nobot(num)),"%ld",&temp)){
    if(temp>=floor && temp<=ceiling)return(temp);
    error_fatal("Long numeric option %d in file %s is out of range",
	   (void *)num,msg_cur->fname,0,0,0,0);
  }
  error_fatal("Long numeric option %d in file %s has bad value",
	(void *)num,msg_cur->fname,0,0,0,0);
  return -1;
}


unsigned
msg_hex(int num,unsigned floor,unsigned ceiling)
{
  long temp;
  
  if(sscanf(lastwd(msg_get_nobot(num)),"%lx",&temp)){
    if(temp>=floor && temp<=ceiling)return((unsigned)temp);
    error_fatal("Hex numeric option %d in file %s is out of range",
	  (void *)num,msg_cur->fname,0,0,0,0);
  }
  error_fatal("Hex numeric option %d in file %s has bad value",
	(void *)num,msg_cur->fname,0,0,0,0);
  return -1;
}


int
msg_int(int num, int floor, int ceiling)            
{
  return((int)msg_long(num,floor+0L,ceiling+0L));
}


int
msg_bool(int num)                           
{
  int rc=0;

  switch(toupper(*lastwd(msg_get_nobot(num)))){
  case 'Y':
    rc=1;
  case 'N':
    return(rc);
  }
  error_fatal("Yes/No option %d in file %s has bad value",
	(void *)num,msg_cur->fname,0,0,0,0);
  return -1;
}


char
msg_char(int num)
{
  return(*lastwd(msg_get_nobot(num)));
}


char *
msg_string(int msgnum)                     
{
  char *cp,*mp;
  
  cp=alcmem(strlen(mp=msg_get_nobot(msgnum))+1);
  strcpy(cp,mp);
  return(cp);
}


int
msg_token(int msgnum,char *toklst, ...)
{
  char **ppt,*token;
  int i;
  
  token=lastwd(msg_get_nobot(msgnum));
  for(ppt=&toklst,i=1;*ppt!=NULL;ppt++,i++){
    if(strcmp(token,*ppt)==0)return i;
  }
  return(0);
}


void
msg_setlanguage(int l)
{
  if(!msg_cur)return;
  msg_cur->language=(l-1)%(NUMLANGUAGES);
  msg_sys->language=(l-1)%(NUMLANGUAGES);
  lastprompt=-1;
}
