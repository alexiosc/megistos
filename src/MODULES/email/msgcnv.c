/*****************************************************************************\
 **                                                                         **
 **  FILE:     msgcnv.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  PURPOSE:  Convert MBBS 5.31 VESIGS database to Megistos format.        **
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
 * Revision 1.1  2001/04/16 14:55:28  alexios
 * Initial revision
 *
 * Revision 0.2  1998/12/27 15:33:03  alexios
 * Added autoconf support.
 *
 * Revision 0.1  1998/07/24 10:16:36  alexios
 * Initial revision.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
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
#include "clubs.h"
#include "email.h"



void convert(char *);



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
  fprintf(stderr,"msgcnv: convert MajorBBS 5.xx VESIGS database to Megistos format.\n\n"\
	  "Syntax: msgcnv options.\n\nOptions:\n"\
	  "  -m dir   or  --majordir dir: read Major databases from specified directory.\n"\
	  "        Defaults to the current directory.\n\n");
  exit(1);
}


static struct option long_options[] = {
  {"majordir", 1, 0, 'm'},
  {0, 0, 0, 0}
};


static char *arg_majordir=".";


static void
parseopts(int argc, char **argv)
{
  int c;

  while (1) {
    int option_index = 0;

    c=getopt_long(argc, argv, "m:", long_options, &option_index);
    if(c==-1) break;

    switch (c) {
    case 'm':
      arg_majordir=strdup(optarg);
      break;
    default:
      syntax();
    }
  }
}


int
msgcnv_main(int argc, char **argv)
{
  setprogname(argv[0]);
  parseopts(argc, argv);
  print_endian_warning();

  fprintf(stderr,"WARNING WARNING WARNING!!!\n");
  fprintf(stderr,"I'm expecting you to have a COMPLETE EMPTY "\
	  "Megistos message base.\n");
  fprintf(stderr,"Last chance to quit and clean it up: press ctrl-c.\n\n");
  {
    char line[1024];
    fgets(line,sizeof(line),stdin);
  }

  convert(arg_majordir);
  
  printf("Syncing disks...\n");
  fflush(stdout);
  system("sync");

  return 0;
}
