/*****************************************************************************\
 **                                                                         **
 **  FILE:     bbsmail.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: B, May 1995, Version 0.5                                     **
 **            C, July 1995, Version 1.0                                    **
 **  PURPOSE:  Send a BBS E-mail message.                                   **
 **  NOTES:    See syntax() function for the syntax of this program.        **
 **            The following message header fields have to be completed by  **
 **            the calling process:                                         **
 **                                                                         **
 **            from:  A fully qualified and validated user ID.              **
 **            to:    A fully qualified and validated user ID. If the field **
 **                   contains a '@' or '%', the message is dispatched via  **
 **                   the mail(1) command. A copy is saved in the BBS mail  **
 **                   database. A header (prompt WNMSGH) is inserted in the **
 **                   message as well.                                      **
 **            flags: The message's flags.                                  **
 **                                                                         **
 **            All other fields are optional, but SHOULD be filled in by    **
 **            the calling process. The following fields are automatically  **
 **            filled in by bbsmail:                                        **
 **                                                                         **
 **            msgno: The number of the message.                            **
 **            crdate, crtime: Message time stamp.                          **
 **            timesread: Initialised as 0.                                 **
 **            numreplies: Initialised as 0.                                **
 **            fatt: Initialised to xxxxx.att, if not specified by caller.  **
 **                                                                         **
 **            This client will return an exit status of 1 if anything goes **
 **            wrong in the posting process.                                **
 **                                                                         **
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
 * Revision 1.1  2001/04/16 15:02:48  alexios
 * Initial revision
 *
 * Revision 1.6  1999/07/28 23:19:38  alexios
 * Moved run() to its own .c file in anticipation of a united
 * bbsmail/netclub binary.
 *
 * Revision 1.5  1999/07/18 22:07:59  alexios
 * Changed a few fatal() calls to fatalsys(). Support for the
 * new style IHAVE database.
 *
 * Revision 1.4  1998/12/27 16:31:55  alexios
 * Added autoconf support.
 *
 * Revision 1.3  1998/07/24 10:29:57  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 1.2  1997/11/06 20:17:18  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 1.1  1997/11/05 10:45:58  alexios
 * No changes.
 *
 * Revision 1.0  1997/08/28 11:23:40  alexios
 * Initial revision
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
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "bbsmail.h"

#define __SYSVAR_UNAMBIGUOUS__ 1
#include "mbk_sysvar.h"
#include "mbk_emailclubs.h"


/*#define DEBUG 1*/


promptblk *msg;
int       usercaller=0;
char      *bbscode;


void
init()
{
  int init=0;

  if(getenv("USERID")&&strcmp("",getenv("USERID"))){
    usercaller=1;
    init=INITALL;
  }else init=INITTTYNUM|INITOUTPUT|INITSYSVARS|INITERRMSGS|INITCLASSES;
  initmodule(init);

  msg=opnmsg("sysvar");
  bbscode=stgopt(SYSVAR_BBSCOD);
  clsmsg(msg);

  msg=opnmsg("emailclubs");
  if(init==INITALL)setlanguage(thisuseracc.language);
}


void
done()
{
  exit(0);
}


void
syntax()
{
  printf("syntax: bbsmail <header-file> <body-file> ");
  printf("[-{h|s|c} <attach-file>]\n\n");
  printf("The header-file must contain a valid mail header.\n");
  printf("The body-file must contain the body of the message.\n");
  printf("The optional argument declares an optional attached file.\n");
  printf("  -h = form hard link to the file.\n");
  printf("  -s = form symbolic link to the file.\n");
  printf("  -c = copy the file to the attachment directory.\n");
  printf("The following attach-file argument specifies the attachment\n");
  printf("file to be linked or copied.\n");
  exit(1);
}


int
main(int argc, char *argv[])
{
  setprogname(argv[0]);
  init();
  if(argc!=3&&argc!=5)syntax();
  if(argc==3)bbsmail_run(argv[1],argv[2],0,"");
  else if(strcmp(argv[3],"-h")&&strcmp(argv[3],"-s")&&strcmp(argv[3],"-c")){
    syntax();
  } else if(!strcmp(argv[3],"-h"))bbsmail_run(argv[1],argv[2],1,argv[4]);
  else if(!strcmp(argv[3],"-s"))bbsmail_run(argv[1],argv[2],2,argv[4]);
  else if(!strcmp(argv[3],"-c"))bbsmail_run(argv[1],argv[2],3,argv[4]);
  done();
  return 0;
}
