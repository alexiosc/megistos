/*****************************************************************************\
 **                                                                         **
 **  FILE:     accesses.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 96, Version 0.5                                      **
 **  PURPOSE:  Teleconferences, user/channel accesses                       **
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
 * Revision 0.6  1998/12/27 16:10:27  alexios
 * Added autoconf support. Added support for new channel_getstatus().
 * Other slight fixes.
 *
 * Revision 0.5  1998/08/14 11:45:25  alexios
 * Rewrote channel engine to use directories for channels and
 * files for the header and user records. This makes sure no
 * strange filing bugs show up like before.
 *
 * Revision 0.4  1998/08/11 10:21:33  alexios
 * Serious one-character bug fixed.
 *
 * Revision 0.3  1998/07/24 10:24:49  alexios
 * Generic debugging. Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:06:11  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 11:08:28  alexios
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
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "telecon.h"
#include "mbk_telecon.h"


int
getdefusrax(char *channel, char *userid)
{
  static struct tlcuser usr;
  int sop;

  if(!strcmp(channel,userid))return CUF_ACCESS|CUF_MODERATOR;
  if(!strcmp(channel,MAINCHAN))return CUF_ACCESS;

  usr_insys(userid,0);
  sop=key_owns(&thisuseracc,sopkey);

  if(usr_exists(channel)){
    if(!usr_insys(channel,0))return CUF_NONE;
    
    if(!loadtlcuser(channel,&usr)){
      error_fatal("Can't load user record for %s",channel);
    }
    
    if(sop)return CUF_ACCESS|CUF_MODERATOR;
    else if(usr.flags&TLF_BEGUNINV)return CUF_NONE;
    else if(usr.flags&TLF_BEGPANEL)return CUF_ACCESS|CUF_READONLY;
    else return CUF_ACCESS;
  } else if(channel[0]=='/'){
    int i;
    
    usr_insys(userid,0);
    i=getclubax(&othruseracc,channel);

    if(i<CAX_READ)return -NAXCLUB;
    else if(i<CAX_WRITE)return CUF_ACCESS|CUF_READONLY;
    else if(i<CAX_COOP)return CUF_ACCESS;
    else return CUF_ACCESS|CUF_MODERATOR;
  }

  return -UNKCHAN;
}


int
getusrax(char *channel, char *userid)
{
  int sop;

  usr_insys(userid,0);
  sop=key_owns(&thisuseracc,sopkey);
  
  if(sameas(channel,MAINCHAN)){                  /* Main */
    strcpy(channel,MAINCHAN);
    return CUF_ACCESS|(sop?CUF_MODERATOR:0);

  } else if(sameas(userid,channel)){             /* Own personal channel */
    strcpy(channel,userid);
    return CUF_ACCESS|CUF_MODERATOR;

  } else {			/* Other channels, non-default ax */
    struct chanhdr *hdr=readchanhdr(channel);
    struct chanusr *usr=readchanusr(channel,userid);

    if(hdr!=NULL && usr!=NULL){
      if(usr->flags&CUF_EXPLICIT)return usr->flags;
      if(hdr->flags&CHF_OPEN)return usr->flags|CUF_ACCESS;
      else if(hdr->flags&CHF_READONLY)
	return usr->flags|CUF_ACCESS|CUF_READONLY;
      else if(hdr->flags&CHF_PRIVATE)return usr->flags&=~CUF_ACCESS;
      else return usr->flags;
    }
  }

  if(channel[0]=='/'){                          /* Club channel */
    if(!findclub(channel))return -UNKCLUB;
    else {
      int i;

      usr_insys(userid,0);
      i=getclubax(&othruseracc,channel);

      if(i<CAX_READ)return -NAXCLUB;
      else if(i<CAX_WRITE)return CUF_ACCESS|CUF_READONLY;
      else if(i<CAX_COOP)return CUF_ACCESS;
      else return CUF_MODERATOR|CUF_ACCESS;
    }
  } else if(usr_exists(channel)){
    struct chanhdr *hdr=readchanhdr(channel);
    int ax=CUF_NONE;
    if(!usr_insys(channel,0))return ax;
    if(hdr->flags&CHF_PRIVATE)ax=CUF_NONE;
    else if(hdr->flags&CHF_READONLY)ax=CUF_ACCESS|CUF_READONLY;
    else if(hdr->flags&CHF_OPEN)ax=CUF_ACCESS;
    if(sop)ax|=CUF_MODERATOR;
    return ax;
  }

  return -UNKCHAN;
}


void
setusrax(char *channel, char *userid, char sex, int flagson, int flagsoff)
{
  struct chanusr *usr=readchanusr(channel,userid);
  
  if(!usr){
    usr=makechanusr(userid,flagson);
    makechannel(channel,userid);
  }

  usr->flags&=~flagsoff;
  usr->flags|=flagson;

  if(sex)usr->sex=sex;

  if(!writechanusr(channel,usr)){
    error_fatal("Unable to write user %s to channel %s",userid,channel);
  }

  usr_insys(userid,0);
  if(!strcmp(othruseronl.telechan,channel))othruseraux.access=usr->flags;
}


void
moderate(char *channel, char *userid, char *moderator)
{
  if(sameas(channel,userid)){
    strcpy(moderator,userid);
    return;
  } else if(channel[0]=='/'){
    if(getclubax(&thisuseracc,channel)>=CAX_COOP && moderator[0]=='\0'){
      strcpy(moderator,userid);
    }
  }
}
