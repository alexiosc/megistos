/*****************************************************************************\
 **                                                                         **
 **  FILE:     bbslogout.c                                                  **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 94, Version 1.0 alpha                              **
 **  PURPOSE:  Perform user logout sequence                                 **
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
 * Revision 1.1  2001/04/16 15:00:31  alexios
 * Initial revision
 *
 * Revision 0.6  1998/12/27 16:20:53  alexios
 * Added autoconf support. Added support for new getlinestatus().
 *
 * Revision 0.5  1998/07/24 10:25:42  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.4  1997/11/06 20:15:33  alexios
 * This program is now stable.
 *
 * Revision 0.3  1997/11/06 20:04:43  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/08/30 13:09:35  alexios
 * Cleaned up the code (not too much work there). Set the flag
 * OLF_LOGGEDOUT so that bbsd knows this was a normal discon-
 * nection.
 *
 * Revision 0.1  1997/08/28 11:14:36  alexios
 * First registered revision. Adequate.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif



#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_STRING_H 1
#define WANT_CTYPE_H 1
#define WANT_UNISTD_H 1
#define WANT_TERMIOS_H 1
#define WANT_SYS_IOCTL_H 1
#define WANT_SYS_TYPES_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "mbk_login.h"


promptblk *msg;



void resetlinestatus()
{
  struct linestatus status;
  getlinestatus(thisuseronl.channel,&status);
  status.result=LSR_LOGOUT;
  status.baud=atoi(getenv("BAUD"));
  status.user[0]=0;
  setlinestatus(thisuseronl.channel,&status);
}


void
main(int argc, char *argv[])
{
  char fname[256];
  int hup=!strcmp(argv[0],"bbshangup");

  setprogname(argv[0]);

  initmodule(INITALL);
  msg=opnmsg("login");
  setlanguage(thisuseracc.language);

  if(!hup){
    setverticalformat(0);
    prompt(SEEYA);
    thisuseronl.flags|=OLF_LOGGEDOUT;
  }

  thisuseracc.datelast=today();

  donemodule();
  disconnect(thisuseronl.emupty);

  sprintf(fname,"%s/%s",ONLINEDIR,thisuseracc.userid);
  unlink(fname);

  resetlinestatus();
}
