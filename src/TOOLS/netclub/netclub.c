/*****************************************************************************\
 **                                                                         **
 **  FILE:     netclub.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1999.                                                **
 **  PURPOSE:  Synchronise distributed BBS clubs by talking to MetaBBS.     **
 **  NOTES:    See syntax() function for the syntax of this program.        **
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
 * Revision 1.1  2001/04/16 15:02:55  alexios
 * Initial revision
 *
 * Revision 0.1  2000/12/08 15:14:10  alexios
 * Initial checkin.
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
#include <typhoon.h>

#include "bbs.h"
#include "netclub.h"

#define __SYSVAR_UNAMBIGUOUS__ 1
#include "mbk_sysvar.h"
#include "mbk_emailclubs.h"


promptblock_t  *msg;
int         usercaller=0;
char       *bbscode;

int         mode=MODE_NOP;	/* Operation mode */
int         debug=0;		/* Debugging mode */
int         force=0;		/* Force sync */
int         dryrun=0;		/* Dry run */
char       *sys=NULL;		/* Name of single system to use */
char       *clubname=NULL;	/* Club name to list */




void
syntax()
{
  printf("syntax: netclub [options]\n\nOptions:\n\b");
  printf("   -c              List remote clubs.\n");
  printf("   -d              Verbose debugging on.\n");
  printf("   -f              Force sync now, regardless of desired times.\n");
  printf("   -g              (Go) Synchronise remote clubs.\n");
  printf("   -I clubname     Get info on remote club (best used with -s).\n");
  printf("   -l              List import points/sync times, exit immediately.\n");
  printf("   -n              Dry run, don't write anything to disk.\n");
  printf("   -s host/BBS     Only operate on specified system.\n");
  exit(1);
}


void
init(int argc, char **argv)
{
  int init=0;
  char c;

  while((c=getopt(argc,argv,"cdfgI:lns:h?"))!=EOF){
    switch(c){
    case 'c':
      mode=MODE_LISTCLUBS;
      break;
    case 'I':
      mode=MODE_CLUBINFO;
      clubname=strdup(optarg);
      break;
    case 'l':
      mode=MODE_REPORT;
      break;
    case 'g':
      mode=MODE_SYNC;
      break;
    case 'd':
      debug=1;
      break;
    case 'f':
      force=1;
      break;
    case 'n':
      dryrun=1;
      break;
    case 's':
      sys=strdup(optarg);
      break;
    case 'h':
    case '?':
    default:
      syntax();
    }
  }
  
  mkdir(IHAVEDIR,0777);		/* Paranoia mode and a silly thing to do */
  d_dbfpath(IHAVEDIR);
  d_dbdpath(IHAVEDIR);
  if(d_open("ihavedb","s")!=S_OKAY){
    error_log("Cannot open ihave database (db_status %d)\n",db_status);
    return;
  }


  if(getenv("USERID")&&strcmp("",getenv("USERID"))){
    usercaller=1;
    init=INI_ALL;
  }else init=INI_TTYNUM|INI_OUTPUT|INI_SYSVARS|INI_ERRMSGS|INI_CLASSES;
  mod_init(init);

  msg=msg_open("sysvar");
  bbscode=msg_string(SYSVAR_BBSCOD);
  msg_close(msg);

  msg=msg_open("emailclubs");
  if(init==INI_ALL)msg_setlanguage(thisuseracc.language);
}


void
run()
{
  if(mode==MODE_NOP){
    fprintf(stderr,"No operation mode specified, no action will be taken.\n");
    fprintf(stderr,"Try -h for help.\n\n");
    exit(1);
  }
  iterate();
}


void
done()
{
  exit(0);
}


int
main(int argc, char *argv[])
{
  mod_setprogname(argv[0]);
  init(argc,argv);
  run();
  done();
  return 0;
}
