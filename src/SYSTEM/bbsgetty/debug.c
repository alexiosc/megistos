/*****************************************************************************\
 **                                                                         **
 **  FILE:     debug.c                                                      **
 **  AUTHORS:  Alexios (based on uugetty 2.1)                               **
 **  PURPOSE:  bbsgetty debugging facility                                  **
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
\*****************************************************************************/


/*
 * $Id$
 *
 * $Log$
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.2  1999/07/18 21:54:26  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 1.1  1998/12/15 22:11:57  alexios
 * Make sure that the debug file has file descriptor greater
 * than 2.
 *
 * Revision 1.0  1998/12/13 23:18:28  alexios
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
#define WANT_UNISTD_H 1
#define WANT_STRINGS_H 1
#define WANT_CTYPE_H 1
#define WANT_TIME_H 1
#define WANT_VARARGS_H 1
#include <bbsinclude.h>
#include <bbs.h>


static FILE  *df=NULL;
static int    debuglevel;



/* Set the debugging level */

void
setdebuglevel(int i)
{
  debuglevel=i;
}



/* Debug something. This follows the printf format, but with a level
   argument before anything else. Only debug entries above the debug
   threshold actually get logged. The filename and line number fields
   are filled in by the debug() macro. */

void
_debug(level,file,line,format,va_alist)
int level, line;
char *format, *file;
va_dcl
{
  va_list args;
  va_start(args);
  if(level&debuglevel){
    void initdebug();

    if(df==NULL)initdebug();
    fprintf(df,"%2x (%s:%d) ",level,file,line);
    vfprintf(df,format,args);
    fputc('\n',df);
    fflush(df);
  }
  va_end(args);
}



/* Start debugging */

void
initdebug()
{
  char fname[256];

  /* Open the debugging file, making sure it has a file descriptor > 2 */

  sprintf(fname,TMPDIR"/bbsgetty_debug.%ld",(long)getpid());
  if((df=fopen(fname,"w"))==NULL){
    error_fatalsys("Unable to open debug file \"%s\"",fname);
  }

  if(fileno(df)<3){
    int fd1, fd2, fd3;		/* Make sure fd>2 */
    fd1=dup(fileno(df));
    fd2=dup(fileno(df));
    fd3=dup(fileno(df));
    close(fd1);
    close(fd2);
    fclose(df);
    if((df=fdopen(fd3,"w"))==NULL){
      error_fatalsys("Unable to open debug file \"%s\"",fname);
    }
  }
  
  _debug(0xff,__FILE__,__LINE__,"Debug file opened");
}
