/*****************************************************************************\
 **                                                                         **
 **  FILE:     ttynum.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 94                                                   **
 **  PURPOSE:  Number ttys so they look like MajorBBS channels.             **
 **  NOTES:    Tty numbering is defined in /bbs/channel.defs/CHANNELS.      **
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
 * Revision 0.5  1999/07/18 21:01:53  alexios
 * Changed a few fatal() calls to fatalsys(). Fixed a slight
 * oversight in telnetlinecount().
 *
 * Revision 0.4  1998/12/27 14:31:16  alexios
 * Added autoconf support. Added code to recognise the channel
 * file by magic number and choke if it isn't there. Altered
 * code to use the new getlinestatus().
 *
 * Revision 0.3  1998/07/24 10:08:57  alexios
 * Made use of new error reporting.
 *
 * Revision 0.2  1997/11/06 20:03:54  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/26 16:35:17  alexios
 * First registered revision. Adequate.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif



#define TTYNUM_C 1
#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#include <bbsinclude.h>

#include "bbs.h"


struct channeldef *channels=NULL;
struct channeldef *lastchandef=NULL;
int                numchannels=0;


int
chancmp(const void *a, const void *b)
{
  return ((struct channeldef *)a)->channel-((struct channeldef *)b)->channel;
}


void
initchannels()
{
  FILE *fp;
  char magic[256];

  if((fp=fopen(CHANDEFFILE,"r"))==NULL){
    fatalsys("Unable to open %s",CHANDEFFILE);
  }

  /* Check the magic number */
  bzero(magic,sizeof(magic));
  if(fread(magic,strlen(CHANNEL_MAGIC),1,fp)!=1){
    fatalsys("Unable to read magic number from %s",CHANDEFFILE);
  }
  if(strcmp(magic,CHANNEL_MAGIC)){
    fatal("Corrupted channel table file (%s), use mkchan to recreate it.",
	  CHANDEFFILE);
  }

  if(channels){
    free(channels);
    numchannels=0;
  }
  if(fread(&numchannels,sizeof(numchannels),1,fp)!=1){
    fatalsys("Unable to read %s",CHANDEFFILE);
  }

  if((channels=alcmem(sizeof(struct channeldef)*numchannels))==NULL){
    fatalsys("Unable to allocate memory for channel table.",
	  CHANDEFFILE);
  }

  if(fread(channels,sizeof(struct channeldef),numchannels,fp)!=numchannels){
    fatalsys("Unable to read %s",CHANDEFFILE);
  }

  fclose(fp);
  lastchandef=channels;
}


int
getchannelnum(char *tty)
{
  int i;

  if(lastchandef && !strcmp(lastchandef->ttyname,tty))
    return lastchandef->channel;
  for(i=0;i<numchannels;i++){
    if(!strcmp(channels[i].ttyname,tty)){
      lastchandef=&channels[i];
      return channels[i].channel;
    }
  }
  return -1;
}


int
getchannelindex(char *tty)
{
  int i;

  for(i=0;i<numchannels;i++){
    if(!strcmp(channels[i].ttyname,tty)){
      lastchandef=&channels[i];
      return i;
    }
  }
  return -1;
}


char *
getchannelname(int num)
{
  struct channeldef *temp, key;

  key.channel=num;
  if(lastchandef && lastchandef->channel==num) return lastchandef->ttyname;
  temp=bsearch(&key,channels,numchannels,sizeof(struct channeldef),chancmp);
  if(!temp)return NULL;
  lastchandef=temp;
  return temp->ttyname;
}


int
telnetlinecount()
{
  int i, retval;

  for(i=0,retval=0;i<numchannels;i++){
    if(channels[i].flags&TTF_TELNET){
      struct linestatus status;
      getlinestatus(channels[i].ttyname,&status);
      if(strcmp(status.user,"[NO-USER]") ||
	 (status.result!=LSR_INIT && status.result!=LSR_OK
	  && status.result!=LSR_FAIL && status.result!=LSR_LOGOUT
	  && status.result!=LSR_FAIL))retval++;
    }
  }
  return retval;
}
