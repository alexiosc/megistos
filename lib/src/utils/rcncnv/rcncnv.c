/*****************************************************************************\
 **                                                                         **
 **  FILE:     regcnv.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  PURPOSE:  Convert MBBS 5.31 "recent" Megistos format.                  **
 **  NOTES:    This is NOT guarranteed to work on anything but MajorBBS     **
 **            version 5.31, for which it was written.                      **
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
\*****************************************************************************/


/*
 * $Id$
 *
 * $Log$
 * Revision 1.3  2001/04/22 14:49:08  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.1  1998/12/27 16:40:35  alexios
 * Added autoconf support.
 *
 * Revision 1.0  1998/08/14 12:03:41  alexios
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
#define WANT_FCNTL_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_STAT_H 1
#define WANT_GETOPT_H 1
#include <bbsinclude.h>

#include <endian.h>
#include <typhoon.h>
#include "bbs.h"



void convert(char *, char *);



static int bigendian=0;


static void
print_endian_warning()
{
  short int eat=0xbeef; /* moo */
  unsigned char  *tmp2=(char*)&eat;
  if(*tmp2==0xbe){
    printf("Argh, this is a big endian machine! This won't work properly.\n");
    bigendian=1;
    exit(1);
  }
}


static void
syntax()
{
  fprintf(stderr,"rcncnv: convert MajorBBS 5.xx recent database to Megistos format.\n\n"\
	  "Syntax: rcncnv options.\n\nOptions:\n"\
	  "  -u dir   or  --usrdir dir:   modify user accounts in given directory\n"\
	  "        By default, the BBS user directory is used.\n\n"\
	  "  -m dir   or  --majordir dir: read Major databases from specified directory.\n"\
	  "        Defaults to the current directory.\n\n");
  exit(1);
}


static struct option long_options[] = {
  {"usrdir",   1, 0, 'u'},
  {"majordir", 1, 0, 'm'},
  {0, 0, 0, 0}
};


static char *arg_usrdir;
static char *arg_majordir=".";


static void
parseopts(int argc, char **argv)
{
  int c;

  while (1) {
    int option_index = 0;

    c=getopt_long(argc, argv, "u:m:", long_options, &option_index);
    if(c==-1) break;

    switch (c) {
    case 'u':
      arg_usrdir=strdup(optarg);
      break;
    case 'm':
      arg_majordir=strdup(optarg);
      break;
    default:
      syntax();
    }
  }
}


int
main(int argc, char **argv)
{
  arg_usrdir=strdup(mkfname(USRDIR));

  mod_setprogname(argv[0]);
  parseopts(argc, argv);
  print_endian_warning();

  convert(arg_usrdir, arg_majordir);
  
  printf("Syncing disks...\n");
  fflush(stdout);
  system("sync");

  return 0;
}
