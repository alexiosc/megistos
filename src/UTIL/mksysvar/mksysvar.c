/*****************************************************************************\
 **                                                                         **
 **  FILE:     mksysvar.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 94                                                   **
 **  PURPOSE:  Creates global system variables/configuration file           **
 **  NOTES:    Reads system configuration from sysvar.mbk and stores them   **
 **            in /bbs/sysvar. That file also stores system statistics,     **
 **            and other accounting stuff. If the file exists, all that is  **
 **            not affected in any way. If the file is inexistent, it is    **
 **            created by this utility.                                     **
 **                                                                         **
 **            It is highly recommended (ie *DO*IT*!) to run mksysvar once  **
 **            in a while (eg every morning). Of course you have to run it  **
 **            to update sysvar if you change config options like the name  **
 **            of the BBS (found in sysvar.msg)                             ** 
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
 * Revision 1.1  2001/04/16 15:03:23  alexios
 * Initial revision
 *
 * Revision 1.6  1999/08/13 17:11:01  alexios
 * Cosmetic changes, mostly, plus a clean return from main().
 *
 * Revision 1.5  1999/07/18 22:11:40  alexios
 * Changed a few fatal() calls to fatalsys().
 *
 * Revision 1.4  1998/12/27 16:38:56  alexios
 * Added autoconf support. Added code to handle new variables.
 *
 * Revision 1.3  1998/07/24 10:32:39  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 1.2  1997/11/06 20:19:27  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 1.1  1997/11/06 17:09:17  alexios
 * Fixed a leftover silly bug.
 *
 * Revision 1.0  1997/08/28 11:34:24  alexios
 * Initial revision
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif



#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_UNISTD_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#include <bbsinclude.h>

#include "bbs.h"

#include "mbk_sysvar.h"

promptblk *sysvars;


int
main()
{
  FILE *sysvarf;
  struct sysvar sysvar;
  int exists=0;
  sysvars=opnmsg("sysvar");

  if((sysvarf=fopen(SYSVARFILE,"r+"))!=NULL)exists=1;
  else if((sysvarf=fopen(SYSVARFILE,"w+"))!=NULL)exists=0;
  else fatalsys("Unable to open/create %s.",SYSVARFILE,0);

  if(!exists){
    fprintf(stderr,"%s does not exist, creating it.\n",SYSVARFILE);
    memset(&sysvar,0x00,sizeof(struct sysvar));
  } else {
    if(fread(&sysvar,sizeof(struct sysvar),1,sysvarf)!=1){
      fatalsys("Error reading %s.",SYSVARFILE,0);
    }
  }

  strcpy(sysvar.bbstitle,stgopt(BBSTTL));
  strcpy(sysvar.company,stgopt(COMPANY));
  strcpy(sysvar.address1,stgopt(ADDRES1));
  strcpy(sysvar.address2,stgopt(ADDRES2));
  strcpy(sysvar.city,stgopt(CITY));
  strcpy(sysvar.dataphone,stgopt(DATAPH));
  strcpy(sysvar.voicephone,stgopt(VOICEPH));
  strcpy(sysvar.livephone,stgopt(LIVEPH));
  sysvar.idlezap=numopt(IDLZAP,0,32767);
  sysvar.idlovr=numopt(IDLOVR,0,129);
  sysvar.saverate=numopt(SVRATE,0,32767);
  strcpy(sysvar.chargehour,stgopt(CHGHOUR));
  strcpy(sysvar.mincredits,stgopt(CHGTIME));
  strcpy(sysvar.minmoney,stgopt(CHGMIN));
  sysvar.bbsrst=numopt(BBSRST,0,9999);

  sysvar.pswexpiry=numopt(PSWEXP,0,360);
  sysvar.pagekey=numopt(PAGEKEY,0,129);
  sysvar.pgovkey=numopt(PGOVKEY,0,129);
  sysvar.pallkey=numopt(PALLKEY,0,129);
  sysvar.glockie=ynopt(GLOCKIE);
  sysvar.lonaud=ynopt(LONAUD);
  sysvar.lofaud=ynopt(LOFAUD);
  sysvar.tnlmax=numopt(TNLMAX,1,32767);

  /* Stamp it with the magic number */

  memcpy(sysvar.magic,SVR_MAGIC,sizeof(sysvar.magic));

  if(fseek(sysvarf,0,SEEK_SET)){
    fatalsys("Error seeking %s.",SYSVARFILE,0);
  }
  if(fwrite(&sysvar,sizeof(struct sysvar),1,sysvarf)!=1){
    fatalsys("Error writing %s.",SYSVARFILE,0);
  }
  fclose(sysvarf);

  return 0;
}
