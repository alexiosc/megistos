/*****************************************************************************\
 **                                                                         **
 **  FILE:     offline.mail.c                                               **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1997, Version 0.1                                    **
 **  PURPOSE:  Off line mailer, mail plugin                                 **
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
 * Revision 1.1  2001/04/16 14:57:44  alexios
 * Initial revision
 *
 * Revision 0.4  1998/12/27 15:48:12  alexios
 * Added autoconf support.
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
#include "offline.mail.h"
#include "../../mailer.h"
#include "mbk_offline.mail.h"

#define __MAILER_UNAMBIGUOUS__
#include "mbk_mailer.h"

#define __EMAILCLUBS_UNAMBIGUOUS__
#include "mbk_emailclubs.h"


promptblk *mail_msg;
promptblk *emailclubs_msg;
promptblk *mailer_msg;

char *progname;
char *defclub;

int   sopkey;
int   wrtkey;
int   netkey;
int   rrrkey;
int   wrtchg;
int   netchg;
int   rrrchg;
int   msglen;

char* bbsid;
int   ansihi;
int   ansibye;
char* hifile;
char* byefile;
char* ctlname[6];
int   qwkuc;

int  updqsc;
int  defatt;
int  defreq;
int  defhdr;
char *omceml;
char *allnam;
int  usepass;
int  fixeta;
char etaxlt;
int  prgind;


void
init()
{
  int i;
  initmodule(INITALL);

  emailclubs_msg=opnmsg("emailclubs");
  setlanguage(thisuseracc.language);

  sopkey=numopt(EMAILCLUBS_SOPKEY,0,129);
  wrtkey=numopt(EMAILCLUBS_WRTKEY,0,129);
  netkey=numopt(EMAILCLUBS_NETKEY,0,129);
  rrrkey=numopt(EMAILCLUBS_RRRKEY,0,129);
  wrtchg=numopt(EMAILCLUBS_WRTCHG,-32767,32767);
  netchg=numopt(EMAILCLUBS_NETCHG,-32767,32767);
  rrrchg=numopt(EMAILCLUBS_RRRCHG,-32767,32767);
  defclub=stgopt(EMAILCLUBS_DEFCLUB);
  msglen=numopt(EMAILCLUBS_MSGLEN,1,256)<<10;

  mailer_msg=opnmsg("mailer");
  bbsid=stgopt(MAILER_BBSID);
  ansihi=ynopt(MAILER_ANSIHI);
  ansibye=ynopt(MAILER_ANSIBYE);
  hifile=stgopt(MAILER_HIFILE);
  byefile=stgopt(MAILER_BYEFILE);
  for(i=0;i<6;i++)ctlname[i]=stgopt(MAILER_CTLNAME1+i);
  if((qwkuc=tokopt(MAILER_QWKUC,"LOWERCASE","UPPERCASE"))==0){
    fatal("Option QWKUC in mailer.msg has bad value.");
  }else qwkuc--;

  mail_msg=opnmsg("offline.mail");
  setlanguage(thisuseracc.language);

  if((defatt=tokopt(DEFATT,"NO","YES","ASK"))==0){
    fatal("Option DEFATT in offline.mail.msg has bad value.");
  }else defatt--;

  if((defreq=tokopt(DEFREQ,"NO","YES","ASK"))==0){
    fatal("Option DEFREQ in offline.mail.msg has bad value.");
  }else defreq--;

  updqsc=ynopt(UPDQSC);
  defhdr=ynopt(DEFHDR);
  omceml=stgopt(OMCEML);
  allnam=stgopt(ALLNAM);
  usepass=ynopt(USEPASS);
  fixeta=ynopt(FIXETA);
  etaxlt=chropt(ETAXLT);
  prgind=ynopt(PRGIND);
}


void
done()
{
  clsmsg(emailclubs_msg);
  clsmsg(mailer_msg);
  clsmsg(mail_msg);
}


void
warn()
{
  fprintf(stderr,"This is a Mailer plugin. ");
  fprintf(stderr,"It should not be run by the user.\n");
  exit(1);
}


int
main(int argc, char *argv[])
{
  setprogname(argv[0]);
  if(argc<2)warn();
  atexit(done);
  progname=argv[0];
  init();
  if(!strcmp(argv[1],"-setup"))setup();
  else if(!strcmp(argv[1],"-download"))return omdownload();
  else if(!strcmp(argv[1],"-upload"))return omupload();
  else if(!strcmp(argv[1],"-reqman"))return reqman();
  else warn();
  done();
  return 0;
}
