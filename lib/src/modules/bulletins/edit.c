/*****************************************************************************\
 **                                                                         **
 **  FILE:     edit.c                                                       **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1997, Version 0.5                                    **
 **  PURPOSE:  Edit bulletin entries                                        **
 **  NOTES:                                                                 **
 **                                                                         **
\*****************************************************************************/


/*
 * $Id$
 *
 * $Log$
 * Revision 1.1  2001/04/16 14:54:53  alexios
 * Initial revision
 *
 * Revision 0.5  1999/07/18 21:19:18  alexios
 * Changed a few fatal() calls to fatalsys().
 *
 * Revision 0.4  1998/12/27 15:27:54  alexios
 * Added autoconf support.
 *
 * Revision 0.3  1998/07/24 10:14:42  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/05 11:22:37  alexios
 * Changed calls to audit() so they take advantage of the new
 * auditing scheme.
 *
 * Revision 0.1  1997/08/28 10:07:31  alexios
 * First registered revision, adequate.
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
#define WANT_SYS_TYPES_H 1
#define WANT_DIRENT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "mbk_bulletins.h"
#include "bltidx.h"
#include "bulletins.h"


void
bltedt()
{
  struct bltidx blt;
  FILE *fp;
  char fname[256], s[80], *cp;
  int i;
  char lock[256];

  /* Get the bulletin */

  if(!getblt(EDTBLT,&blt))return;
  if(getaccess(blt.area)<flaxes){
    prompt(EDTNOAX,blt.area);
    return;
  }

  sprintf(lock,"%s-%s-%s-%s",BLTREADLOCK,thisuseracc.userid,blt.area,blt.fname);
  placelock(lock,"editing");

  sprintf(fname,TMPDIR"/blt%05d",getpid());
  if((fp=fopen(fname,"w"))==NULL){
    logerrorsys("Unable to create data entry file %s",fname);
    rmlock(lock);
    return;
  }

  fprintf(fp,"%s\n",blt.author);
  fprintf(fp,"%s\n",blt.descr);
  fprintf(fp,"OK button\nCancel button\n");
  fclose(fp);

  dataentry("bulletins",EBLTVT,EBLTLT,fname);

  if((fp=fopen(fname,"r"))==NULL){
    logerrorsys("Unable to read data entry file %s",fname);
    rmlock(lock);
    return;
  }

  for(i=0;i<5;i++){
    fgets(s,sizeof(s),fp);
    if((cp=strchr(s,'\n'))!=NULL)*cp=0;
    if(i==0)strcpy(blt.author,s);
    else if(i==1)strcpy(blt.descr,s);
  }

  fclose(fp);
  unlink(fname);
  if(sameas(s,"CANCEL")){
    prompt(ABORT);
    rmlock(lock);
    return;
  } else {
    if(!uidxref(blt.author,0)){
      if(margc&&isX(margv[0])){
	prompt(ABORT);
	rmlock(lock);
	return;
      }
      endcnc();
      prompt(EDTAUTHR,blt.author);
      if(!getuserid(blt.author,EDTAUTH,EDTAUTHR,0,NULL,0)){
	prompt(ABORT);
	rmlock(lock);
	return;
      }
    }

    if(!dbupdate(&blt)){
      prompt(EDITERR);
      rmlock(lock);
      return;
    }

    rmlock(lock);
    prompt(EDITOK);
    bltinfo(&blt);

    /* Audit it */

    if(audedt)audit(thisuseronl.channel,AUDIT(BLTEDT),
		    thisuseracc.userid,blt.fname,blt.area);
  }
}
