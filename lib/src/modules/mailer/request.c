/*****************************************************************************\
 **                                                                         **
 **  FILE:     request.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1997, Version 0.1                                    **
 **  PURPOSE:  Record file requests                                         **
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
 * Revision 1.1  2001/04/16 14:57:52  alexios
 * Initial revision
 *
 * Revision 0.4  1998/12/27 15:48:12  alexios
 * Added autoconf support. One bug fix.
 *
 * Revision 0.3  1998/07/24 10:20:56  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:06:43  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/28 10:55:29  alexios
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
#include <bbsinclude.h>

#include "bbs.h"
#include "typhoon.h"
#include "offline.mail.h"
#include "../../mailer.h"


static int reqdbid;


void
openreqdb()
{
  d_dbfpath(MAILERREQDIR);
  d_dbdpath(MAILERREQDIR);
  if(d_open("request","s")!=S_OKAY){
    fatal("Unable to open QWK REQUEST database (db_status %d)",
	  db_status);
  }
  d_dbget(&reqdbid);
}


int
mkrequest(char *area, char *dosfname, char *fname,
	  int msgno, int priority, int flags)
{
  int olddb=-1, retval;
  struct reqidx idx;

  bzero(&idx,sizeof(idx));
  if(d_dbget(&olddb)!=S_OKAY)olddb=-1;
  if(olddb!=reqdbid)d_dbset(reqdbid);

  if(d_keylast(REQNUM)!=S_OKAY)idx.reqnum=1;
  else {
    if(d_keyread(&idx.reqnum)!=S_OKAY){
      fatal("Unable to read last key (db_status %d)",db_status);
    }
    idx.reqnum++;
  }

  strncpy(idx.userid,thisuseracc.userid,sizeof(idx.userid)-1);
  strncpy(idx.reqarea,area,sizeof(idx.reqarea)-1);
  strncpy(idx.dosfname,dosfname,sizeof(idx.dosfname)-1);
  strncpy(idx.reqfname,fname,sizeof(idx.reqfname)-1);
  idx.priority=priority;
  idx.reqflags=flags;
  idx.reqdate=today();
  idx.msgno=msgno;

  retval=d_fillnew(REQIDX,&idx)==S_OKAY;
  if(olddb!=-1&&olddb!=reqdbid)d_dbset(olddb);
  return retval;
}


int
getfirstreq(struct reqidx *idx)
{
  struct orderc o;
  d_dbset(reqdbid);
  strncpy(o.userid,thisuseracc.userid,sizeof(idx->userid)-1);
  o.reqnum=0;
  o.priority=0;
  strcpy(o.reqarea,"\1");

  if(d_keyfind(ORDERC,&o)!=S_OKAY){
    if(d_keyprev(ORDERC))return 0;
  }
  if(d_recread(idx)!=S_OKAY){
    if(db_status!=S_DELETED&&db_status!=S_NOTFOUND)
      fatal("Unable to read request record, db_status=%d.",
	    db_status);
    return 0;
  }
  return sameas(idx->userid,thisuseracc.userid);
}


int
getnextreq(struct reqidx *idx)
{
  int n=idx->reqnum;
  d_dbset(reqdbid);
  d_keyfind(REQNUM,&(idx->reqnum));
  if(d_keynext(REQIDX)!=S_OKAY)return 0;
  if(d_recread(idx)!=S_OKAY){
    fatal("Unable to read request record, db_status=%d.",
	  db_status);
  }
  if(n==idx->reqnum){
    if(d_keynext(REQIDX)!=S_OKAY)return 0;
    if(d_recread(idx)!=S_OKAY){
      fatal("Unable to read request record, db_status=%d.",
	    db_status);
    }
    if(n==idx->reqnum)fatal("Whoops, looping at request %d.",n);
  }
  return sameas(idx->userid,thisuseracc.userid);
}


int
rmrequest(struct reqidx *idx)
{
  d_dbset(reqdbid);
  if(d_keyfind(REQNUM,&(idx->reqnum))!=S_OKAY)return 0;
  return d_delete()==S_OKAY;
}


int
updrequest(struct reqidx *idx)
{
  d_dbset(reqdbid);
  return d_recwrite(idx)==S_OKAY;
}
