/*****************************************************************************\
 **                                                                         **
 **  FILE:     login.c                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1997, Version 0.5                                    **
 **  PURPOSE:  Notify user of new bulletins since their last login          **
 **  NOTES:                                                                 **
 **                                                                         **
\*****************************************************************************/


/*
 * $Id$
 *
 * $Log$
 * Revision 2.0  2004/09/13 19:44:50  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2003/12/27 12:29:40  alexios
 * Adjusted #includes.
 *
 * Revision 1.4  2003/12/24 20:12:15  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.3  1998/12/27 15:27:54  alexios
 * Added autoconf support.
 *
 * Revision 0.2  1998/07/24 10:14:42  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.1  1997/08/28 10:07:31  alexios
 * First registered revision, adequate.
 *
 *
 */


static const char rcsinfo[] =
    "$Id$";


#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_DIRENT_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include "mbk_bulletins.h"
#include "bltidx.h"
#include "bulletins.h"
#include <libtyphoon/typhoon.h>


int
login (int argc, char **argv)
{
	return 0;
	/*
	   char **areas=NULL;
	   struct bltidx blt;
	   int cofd=cofdate(thisuseracc.datelast);
	   int newblts=0;
	   int numareas=0;

	   d_keyfind(DATE,&thisuseracc.datelast);
	   if(db_status!=S_OKAY)d_keynext(DATE);

	   while(db_status==S_OKAY){
	   d_recread(&blt);

	   if(cofdate(blt.date)>=cofd){
	   newblts++;
	   if(numareas){
	   char **newareas=alcmem(numareas*sizeof(char*))
	   }
	   }


	   strcpy(a,strdate(blt.date));
	   strcpy(b,strdate(thisuseracc.datelast));
	   print("%3d. %-10s, %-40s, %s %s\n",blt.num,blt.area,blt.descr,a,b);
	   d_keynext(DATE);
	   } */
}



/* End of File */
