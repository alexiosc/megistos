/*****************************************************************************\
 **                                                                         **
 **  FILE:     read.c                                                       **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 1996, Version 0.5                               **
 **  PURPOSE:  Read bulletins                                               **
 **  NOTES:                                                                 **
 **                                                                         **
\*****************************************************************************/


/*
 * $Id$
 *
 * $Log$
 * Revision 1.1  2001/04/16 14:54:55  alexios
 * Initial revision
 *
 * Revision 0.5  1999/07/28 23:10:22  alexios
 * Added support for downloading bulletins.
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
#include <bbsinclude.h>

#include "bbs.h"
#include "mbk_bulletins.h"
#include "bltidx.h"
#include "bulletins.h"


int
fnamexref(char *fname)   /* Not much of an xref function yet */
{
  int res;
  if(club[0])return dbexists(club,fname);
  if((res=dbchkambiguity(fname))==2){
    prompt(BLTAMB,fname);
    listambiguous(fname);
  }
  return res;
}


int
getblt(int pr, struct bltidx *blt)
{
  char *i;
  char c;

again:
  for(;;){
    lastresult=0;
    if((c=morcnc())!=0){
      if(sameas(nxtcmd,"X"))return 0;
      if(sameas(nxtcmd,"?")){
	list(0);
	endcnc();
	continue;
      }
      i=cncword();
    } else {
      prompt(pr);
      getinput(0);
      bgncnc();
      i=cncword();
      if(!margc || (margc==1 && sameas(margv[0],"."))){
	endcnc();
	continue;
      } else if(isX(margv[0]))return 0;
      if(sameas(margv[0],"?")){
	list(0);
	endcnc();
	continue;
      }
    }

    if(!i[0] || sameas(i,".")){
      endcnc();
      continue;
    } else if(dbnumexists(atoi(i))){
      break;
    } else {
      int res=fnamexref(i);
      if(res==1)break;
      else if(!res){
	if(club[0])prompt(UNKBLTC,club);
	else prompt(UNKBLT);
      }
      endcnc();
      continue;
    }
  }
  dbget(blt);
  if((club[0]&&strcmp(club,blt->area))||
     getclubax(&thisuseracc,blt->area)<CAX_READ){
    prompt(UNKBLTC,club);
    endcnc();
    goto again;
  }
  return 1;
}



void
bltread()
{
  struct bltidx blt;

  if(!(club[0]?dblistfind(club,1):dblistfirst())){
    if(!club[0])prompt(BLTNOBT);
    else prompt(CLBNOBT,club);
    return;
  }

  if(!getblt(READBLT,&blt))return;

  bltinfo(&blt);

  showblt(&blt);
}



static void
offerblt(struct bltidx *blt)
{
  char fname[256], lock[256];
  char a[256];

  prompt(BLTHDR);

  sprintf(fname,MSGSDIR"/%s/%s/%s",blt->area,MSGBLTDIR,blt->fname);
  sprintf(lock,"%s-%s-%s-%s",BLTREADLOCK,thisuseracc.userid,blt->area,blt->fname);

  placelock(lock,"downloading");
  lastresult=PAUSE_CONTINUE;

  sprintf(a,AUD_BLTDNL,thisuseracc.userid,blt->fname,blt->area);
  setaudit(AUT_BLTDNL,AUS_BLTDNL,a,0,NULL,NULL);

  if(addxfer(FXM_DOWNLOAD,fname,dnldesc,0,-1)){
    dofiletransfer();
    killxferlist();
  }

  blt->timesread++;
  dbupdate(blt);
  rmlock(lock);
}



void
bltdnl()
{
  struct bltidx blt;

  if(!(club[0]?dblistfind(club,1):dblistfirst())){
    if(!club[0])prompt(BLTNOBT);
    else prompt(CLBNOBT,club);
    return;
  }

  if(!getblt(DNLBLT,&blt))return;

  bltinfo(&blt);

  offerblt(&blt);
}



void
showblt(struct bltidx *blt)
{
  char fname[256], lock[256];
  prompt(BLTHDR);

  sprintf(fname,MSGSDIR"/%s/%s/%s",blt->area,MSGBLTDIR,blt->fname);
  sprintf(lock,"%s-%s-%s-%s",BLTREADLOCK,thisuseracc.userid,blt->area,blt->fname);

  thisuseronl.flags|=OLF_BUSY;
  placelock(lock,"reading");
  lastresult=PAUSE_CONTINUE;
  if(!catfile(fname)){
    prompt(PANIC1,blt->fname);
    rmlock(lock);
    thisuseronl.flags&=~OLF_BUSY;
    return;
  }
  if(lastresult==PAUSE_QUIT){
    prompt(ABORT);
    rmlock(lock);
    thisuseronl.flags&=~OLF_BUSY;
    return;
  }
  prompt(ENDBLT);
  thisuseronl.flags&=~OLF_BUSY;

  blt->timesread++;
  dbupdate(blt);
  rmlock(lock);


  /* Audit it */

  if(audrd)audit(thisuseronl.channel,AUDIT(BLTRD),
		  thisuseracc.userid,blt->fname,blt->area);
}
