/*****************************************************************************\
 **                                                                         **
 **  FILE:     usrcnv.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  PURPOSE:  Convert MBBS 5.31 user account database to Megistos format.  **
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
 * Revision 1.2  2001/04/16 21:56:34  alexios
 * Completed 0.99.2 API, dragged all source code to that level (not as easy as
 * it sounds).
 *
 * Revision 1.3  1998/12/27 16:41:03  alexios
 * Added autoconf support.
 *
 * Revision 1.2  1998/07/24 10:40:08  alexios
 * Fixed slight bug in parseopts().
 *
 * Revision 1.1  1998/07/24 10:33:29  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 1.0  1998/07/10 21:09:25  alexios
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



void convert(char *, char *, char *, int, int);



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
  fprintf(stderr,"usrcnv: convert MajorBBS 5.xx user account database to Megistos format.\n\n"\
	  "Syntax: usrcnv options.\n\nOptions:\n"\
	  "  -u dir   or  --userdir dir:  put user account files under the supplied\n"\
	  "        directory. By default, accounts are made in the current directory.\n\n"\
	  "  -m dir   or  --majordir dir: read Major databases from specified directory.\n"\
	  "        Defaults to the current directory.\n\n"\
	  "  -c class or  --class class:  set initial user class (default: MAJOR)\n\n"\
	  "  -f       or  --fast:         fast user conversion: does not make home\n"\
	  "         directories, does not call bbsuseracc. Superuser must append\n"\
	  "         local files .passwd and .shadow to the respective files in /etc.\n"\
	  "         This method is a lot faster than the normal way of operation, but\n"\
	  "         it needs more operator intervention and is shadow-password specific.\n\n"\
	  "  -U uid   or  --uid uid:      set the first numeric uid to be used for UNIX\n"\
	  "         user records. The default behaviour is that of (bbs)adduser.\n\n");
  exit(1);
}


static struct option long_options[] = {
  {"userdir",  1, 0, 'u'},
  {"majordir", 1, 0, 'm'},
  {"class",    1, 0, 'c'},
  {"fast",     0, 0, 'f'},
  {"uid",      1, 0, 'U'},
  {0, 0, 0, 0}
};


static char *arg_usrdir=".";
static char *arg_majordir=".";
static char *arg_class="MAJOR";
static int   arg_fast=0;
static int   arg_uid=-1;


static void
parseopts(int argc, char **argv)
{
  int c;

  while (1) {
    int option_index = 0;

    c=getopt_long(argc, argv, "u:m:c:fU:", long_options, &option_index);
    if(c==-1) break;

    switch (c) {
    case 'u':
      arg_usrdir=strdup(optarg);
      break;
    case 'm':
      arg_majordir=strdup(optarg);
      break;
    case 'c':
      arg_class=strdup(optarg);
      break;
    case 'U':
      arg_uid=atoi(optarg);
      break;
    case 'f':
      arg_fast=1;
      break;
    default:
      syntax();
    }
  }
}


int
main(int argc, char **argv)
{
  mod_setprogname(argv[0]);
  parseopts(argc, argv);
  print_endian_warning();

  if(getuid()){
    fprintf(stderr,"Error: this program will create UNIX users as well as\n"\
	    "Megistos ones (actually it'll do whatever bbsuseradd does, but\n"\
	    "we're trying to be on the safe side). You must run usrcnv as\n"\
	    "the superuser.\n\n");
    fflush(stderr);
    exit(1);
  }

  if(isatty(fileno(stdout))||isatty(fileno(stderr))){
    fprintf(stderr,"\nWARNING: "\
	    "Please keep BOTH standard output and standard error of this\n"\
	    "program by logging to a file. For example, run:\n\n"\
	    "usrcnv 2>&1 |tee usrcnv.log\n\n"\
	    "A lot of warnings and information that you WILL need to\n"\
	    "complete the conversion will be in there.\n"\
	    "If you're sure you're doing the right thing, press Enter.\n");
    {
      char s[256];
      fgets(s,sizeof(s),stdin);
    }
  }
  
  convert(arg_usrdir, arg_majordir, arg_class, arg_fast, arg_uid);
  
  printf("Syncing disks...\n");
  fflush(stdout);
  system("sync");

  printf("\nREMEMBER:\n\n"\
	 "  * It's entirely your responsibility to physically copy\n"\
	 "    the user account files to %s.\n\n",USRDIR);

  printf("  * Please MAKE SURE that the user class %s exists, or you\n"\
	 "    will get fatal errors every time someone tries to log in!\n\n",arg_class);

  return 0;
}
