/*****************************************************************************\
 **                                                                         **
 **  FILE:     qwkout.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 1997, Version 0.1                                    **
 **  PURPOSE:  Output messages to a QWK packet                              **
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
 * Revision 1.1  2001/04/16 14:57:52  alexios
 * Initial revision
 *
 * Revision 0.8  1999/07/18 21:44:48  alexios
 * Changed a few fatal() calls to fatalsys().
 *
 * Revision 0.7  1998/12/27 15:48:12  alexios
 * Added autoconf support. Various fixes.
 *
 * Revision 0.6  1998/08/14 11:39:37  alexios
 * Fixed VERY serious one-character bug whereby the QWK mess-
 * age block count would be right- instead of left-aligned,
 * causing some (but not all) off-line readers to choke. Ahem,
 * the QWK specs say that the block count can be either way.
 * Oh well. Specs are specs and implementations are bollocks.
 *
 * Revision 0.5  1998/08/11 10:13:15  alexios
 * Added user encoding translation to the outgoing messages.
 *
 * Revision 0.4  1998/07/24 10:20:56  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.3  1997/11/06 20:06:43  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/11/03 00:41:28  alexios
 * QWK messages are now NOT translated to the user's current
 * translation preferences. The QWK reader should do this and
 * it's a bad idea anyway. Translation is for on-line BBSing
 * only.
 *
 * Revision 0.1  1997/08/28 10:55:29  alexios
 * First registered revision. Adequate.
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
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "mail.h"
#include "offline.mail.h"
#include "../../mailer.h"
#include "mbk_offline.mail.h"

#define __MAILER_UNAMBIGUOUS__
#include "mbk_mailer.h"

#define __EMAILCLUBS_UNAMBIGUOUS__
#include "mbk_emailclubs.h"

#ifdef USE_LIBZ
#define WANT_ZLIB_H 1
#endif


static int           msgno=0;
static int           lastconf=-1;
static FILE          *msgdat;
static FILE          *ndx=NULL;
static FILE          *ndxpers;
static struct qwkhdr qwkhdr;
static char          qwkbuf[128];
static int           numatt;


static void
clrbuf()
{
  memset(qwkbuf,0x20,128);
}


static void
strbuf(char *s)
{
  memcpy(qwkbuf,s,strlen(s));
}


static void
wrtbuf()
{
  if(!fwrite(qwkbuf,128,1,msgdat)){
    fatalsys("Unable to write to messages.dat");
  }
}


static char *
mkfield(char *f, char *s, int len)
{
  memset(f,0x20,len);
  memcpy(f,s,min(len,strlen(s)));
  return f;
}


static char *
mkfielduc(char *f, char *s, int len)
{
  int i,j=strlen(s);
  memset(f,0x20,min(j,len));
  memcpy(f,s,j);
  for(i=0;i<j;i++)f[i]=toupper(f[i]);
  return f;
}


static void
makeheader(int clubid, struct message *msg)
{
  char tmp[256], topic[128];

  memset(&qwkhdr,0x20,sizeof(struct qwkhdr));
  qwkhdr.status=clubid?STATUS_N:STATUS_P;
  sprintf(tmp,"%ld",msg->msgno);
  mkfield(qwkhdr.number,tmp,sizeof(qwkhdr.number));
  mkfield(qwkhdr.date,qwkdate(msg->crdate),sizeof(qwkhdr.date));
  mkfield(qwkhdr.time,strtime(msg->crtime,0),sizeof(qwkhdr.time));
  mkfielduc(qwkhdr.whoto,sameas(msg->to,ALL)?QWK_ALL:msg->to,
	    sizeof(qwkhdr.whoto));
  mkfielduc(qwkhdr.from,msg->from,sizeof(qwkhdr.from));
  strcpy(topic,msg->subject);
  xlate_out(topic);
  mkfield(qwkhdr.subject,topic,
	  sizeof(qwkhdr.subject)+(usepass?sizeof(qwkhdr.password):0));
  if(msg->flags&MSF_REPLY){
    sprintf(tmp,"%ld",msg->replyto);
    mkfield(qwkhdr.reference,tmp,sizeof(qwkhdr.reference));
  }
  qwkhdr.active=MSG_ACT;
  qwkhdr.conference[0]=clubid&0xff;
  qwkhdr.conference[1]=(clubid&0xff00)>>8;
  qwkhdr.msgno[0]=msgno&0xff;
  qwkhdr.msgno[1]=(msgno&0xff00)>>8;
}


static char *
mkpre(int clubid, struct message *msg)
{
  if(prefs.flags&OMF_HEADER){
    char s1[256]={0}, s2[256]={0}, s3[256]={0}, s4[256]={0};
    char s5[256]={0}, s6[256]={0}, s7[256]={0}, m4u[256]={0};
    
    setmbk(emailclubs_msg);
    strcpy(s1,xlatehist(msg->history));
    setmbk(mail_msg);
    sprintf(s2,"%s/%ld  ",clubid?clubhdr.club:EMAILCLUBNAME,msg->msgno);
    if(strlen(s1)+strlen(s2)>thisuseracc.scnwidth-1){
      s1[78-strlen(s2)]='*';
      s1[79-strlen(s2)]=0;
    }
    
    strcpy(s3,getmsg(MHDAY0+getdow(msg->crdate)));
    strcpy(s4,getmsg(MHJAN+tdmonth(msg->crdate)));
    sprintf(s2,"%s, %d %s %d, %s",
	    s3, tdday(msg->crdate), s4, tdyear(msg->crdate),
	    strtime(msg->crtime,1));
    
    if(clubid)strcpy(m4u,getmsg(MHFORU));
    
    if(msg->period){
      sprint(s3,getmsg(MHPERIOD),msg->period,getpfix(DAYSNG,msg->period));
    } else {
      strcpy(s3,msg->flags&MSF_EXEMPT?getmsg(MHXMPT):"");
    }
    strcpy(s4,msg->flags&MSF_RECEIPT?getmsg(MHRRR):"");
    
    if(msg->timesread){
      strcpy(s6,getmsg(MHTMRD));
      sprint(s5,s6,msg->timesread,getpfix(TIMSNG,msg->timesread));
    }else strcpy(s5,"");
    
    if(msg->replies){
      strcpy(s7,getmsg(MHNREP));
      sprint(s6,s7,msg->replies,getpfix(REPSNG,msg->replies));
    }else strcpy(s6,"");
    
    sprint(outbuf,getmsg(MSGHDR1),
	    clubid?clubhdr.club:EMAILCLUBNAME,msg->msgno,s1,
	    s2,s3,
	    msg->from,s4,
	    (msg->club[0]&&(sameas(thisuseracc.userid,msg->to)))?m4u:"",
	    sameas(msg->to,ALL)?getpfix(MHALL,1):msg->to,s5,
	    msg->subject,s6);
    
    if(msg->flags&MSF_FILEATT){
      if(msg->timesdnl){
	strcpy(s1,getmsg(MHNDNL));
	sprint(s2,s1,msg->timesdnl,getpfix(TIMSNG,msg->timesdnl));
      } else strcpy(s2,"");
      sprint(&outbuf[strlen(outbuf)],getmsg(MSGHDR2),msg->fatt,s2);
    }
    
    strcat(outbuf,getmsg(MSGHDR3));
    return strdup(outbuf);
  }

  return NULL;
}


#ifdef USE_LIBZ


static char *
mkbody(int clubid, struct message *msg)
{
  char fname[256], *body=NULL;
  gzFile *zfp;

  sprintf(fname,"%s/%s/"MESSAGEFILE,MSGSDIR,
	  msg->club[0]?msg->club:EMAILDIRNAME,
	  (long)msg->msgno);
  if((zfp=gzopen(fname,"rb"))==NULL){
    gzclose(zfp);
    fatalsys("Unable to open message %s/%d for reading",
	  msg->club[0]?msg->club:EMAILDIRNAME,msg->msgno);
  } else {
    struct message dummy;
    if(gzread(zfp,&dummy,sizeof(dummy))<=0){
      gzclose(zfp);
      fatalsys("Unable to fseek() message %s/%d",
	    msg->club[0]?msg->club:EMAILDIRNAME,msg->msgno);
    }
  }
  
  for(;;){
    char buffer[1025];
    int bytes=0;

    bytes=gzread(zfp,buffer,sizeof(buffer)-1);
    if(!bytes)break;
    else buffer[bytes]=0;

    if(msg->cryptkey)bbscrypt(buffer,bytes,msg->cryptkey);

    if(body==NULL)body=strdup(buffer);
    else {
      char *tmp=alcmem(strlen(body)+bytes+1);
      sprintf(tmp,"%s%s",body,buffer);
      free(body);
      body=tmp;
    }
  }
  gzclose(zfp);
  return body;
}


#else /* DON'T USE_LIBZ */


static char *
mkbody(int clubid, struct message *msg)
{
  char fname[256], *body=NULL;
  FILE *fp;

  sprintf(fname,"%s/%s/"MESSAGEFILE,MSGSDIR,
	  msg->club[0]?msg->club:EMAILDIRNAME,
	  (long)msg->msgno);
  if((fp=fopen(fname,"r"))==NULL){
    fclose(fp);
    fatalsys("Unable to open message %s/%d for reading",
	     msg->club[0]?msg->club:EMAILDIRNAME,msg->msgno);
  } else if(fseek(fp,sizeof(struct message),SEEK_SET)){
    int i=errno;
    fclose(fp);
    errno=i;
    fatalsys("Unable to fseek() message %s/%d",
	  msg->club[0]?msg->club:EMAILDIRNAME,msg->msgno);
  }
  while(!feof(fp)){
    char buffer[1025];
    int bytes=0;

    bytes=fread(buffer,1,sizeof(buffer)-1,fp);
    if(!bytes)break;
    else buffer[bytes]=0;

    if(msg->cryptkey)bbscrypt(buffer,bytes,msg->cryptkey);

    if(body==NULL)body=strdup(buffer);
    else {
      char *tmp=alcmem(strlen(body)+bytes+1);
      sprintf(tmp,"%s%s",body,buffer);
      free(body);
      body=tmp;
    }
  }
  fclose(fp);
  return body;
}


#endif /* USE_LIBZ */


static char *
mkfooter(int clubid, struct message *msg)
{
  if(msg->flags&MSF_FILEATT){
    char fname[256];
    int res;
    struct stat st;

    sprintf(fname,"%s/%s/"MSGATTDIR"/"FILEATTACHMENT,
	    MSGSDIR,msg->club[0]?msg->club:EMAILDIRNAME,msg->msgno);

    /* Check if the file is there */
    
    if(stat(fname,&st)){
      sprint(outbuf,getmsg(ATTNOT6));
      return strdup(outbuf);
    }


    /* Attempt to make the request for the file */

    if(prefs.flags&OMF_ATT){
      char dosfname[13], num[13];
      int i;

      sprintf(dosfname,"%-8.8s.att",clubid?msg->club:EMAILCLUBNAME);
      sprintf(num,"%ld",msg->msgno);
      strncpy(&dosfname[strlen(dosfname)-4-strlen(num)],num,strlen(num));
      for(i=0;dosfname[i];i++){
	dosfname[i]=dosfname[i]==' '?'-':
	qwkuc?toupper(dosfname[i]):tolower(dosfname[i]);
      }

      numatt++;
      res=mkrequest(clubid?msg->club:EMAILCLUBNAME,
		    dosfname,
		    fname,
		    msg->msgno,
		    RQP_ATT,
		    RQF_ATT);
    } else res=1;

    if(msg->club[0]&&(msg->flags&MSF_APPROVD)==0&&
       getclubax(&thisuseracc,msg->club)<CAX_COOP){
      sprint(outbuf,getmsg(ATTNOT5),msg->fatt,st.st_size);
    } else if(msg->club[0]&&getclubax(&thisuseracc,msg->club)<CAX_DNLOAD){
      sprint(outbuf,getmsg(ATTNOT4),msg->fatt,st.st_size);
    } else if(res&&prefs.flags&OMF_ATTYES){
      sprint(outbuf,getmsg(ATTNOT2),msg->fatt,st.st_size,
	     ctlname[0],msg->club[0]?msg->club:EMAILCLUBNAME,
	     msg->msgno);
    } else if(res&&prefs.flags&OMF_ATTASK){
      sprint(outbuf,getmsg(ATTNOT3),msg->fatt,st.st_size,
	     ctlname[0],msg->club[0]?msg->club:EMAILCLUBNAME,
	     msg->msgno);
    } else sprint(outbuf,getmsg(ATTNOT1),msg->fatt,st.st_size,
		  ctlname[0],msg->club[0]?msg->club:EMAILCLUBNAME,
		  msg->msgno);
    
    return strdup(outbuf);
  }

  return NULL;
}


void
dumpndx(int clubid, struct message *msg)
{
  struct qwkndx ndxrec;

  if(clubid!=lastconf){
    char fname[256];

    if(ndx){
      fclose(ndx);
      ndx=NULL;
    }
    
    sprint(fname,"%03d.ndx",lastconf=clubid);
    if((ndx=fopen(fname,"w"))==NULL){
      fatalsys("Unable to create index file %s",fname);
    }
  }

  /* Form the index record */

  ndxrec.blkofs=ltomks(1L+(long)ftell(msgdat)/128L);
  ndxrec.sig=clubid&0xff;

  /* Always write exactly five bytes. Ignore 32bit word alignment. */

  if(!fwrite(&ndxrec,5,1,ndx)){
    fatalsys("Unable to write to index file.");
  }

  /* Write to PERSONAL.NDX if we need to */

  if(!sameas(msg->to,thisuseracc.userid))return;

  if(!fwrite(&ndxrec,5,1,ndxpers)){
    fatalsys("Unable to write to personal.ndx.");
  }
}


void
dumpmsg(char *pre, char *body, char *post)
{
  int n=0;
  char tmp[7];

  n+=pre?strlen(pre):0;
  n+=body?strlen(body):0;
  n+=post?strlen(post):0;

  sprintf(tmp,"%-6d",1+(n+127)/128);
  strncpy(qwkhdr.blocks,tmp,6);

  memcpy(qwkbuf,&qwkhdr,sizeof(qwkbuf));
  wrtbuf();

  if(pre){
    xlate_out(pre);
    if(!fwrite(pre,strlen(pre),1,msgdat)){
      fatalsys("Unable to write to messages.dat");
    }
    free(pre);
  }
  if(body){
    xlate_out(body);
    if(fwrite(body,strlen(body),1,msgdat)!=1){
      fatalsys("Unable to write to messages.dat");
    }
    free(body);
  }
  if(post){
    xlate_out(post);
    if(!fwrite(post,strlen(post),1,msgdat)){
      fatalsys("Unable to write to messages.dat");
    }
    free(post);
  }

  clrbuf();
  if(n%128){
    if(!fwrite(qwkbuf,128-(n%128),1,msgdat)){
      fatalsys("Unable to write to messages.dat");
    }
  }
}


static void
updatemsg(int clubid, struct message *msg)
{
  struct message m;
  getmsgheader(msg->msgno,&m);
  m.timesread++;
  writemsgheader(&m);
}


void
receipt(int clubdid, struct message *msg)
{
  struct message rrr;
  char hdrname[256], fname[256], s1[256], s2[256];
  char command[256];
  FILE *fp;

  if(strcmp(msg->to,thisuseracc.userid))return;
  sprintf(fname,TMPDIR"/rrrB%d%lx",getpid(),time(0));
  if((fp=fopen(fname,"w"))==NULL)return;

  strcpy(s1,getmsg(EMAILCLUBS_MHDAY0+(cofdate(msg->crdate)-4)%7));
  strcpy(s2,getmsg(EMAILCLUBS_MHJAN+tdmonth(msg->crdate)));
  
  fprintf(fp,getmsg(EMAILCLUBS_RRRBODY),
	  getpfix(EMAILCLUBS_SEXMALE,thisuseracc.sex==USX_MALE),thisuseracc.userid,
	  EMAILCLUBNAME,msg->msgno,
	  s1, tdday(msg->crdate), s2, tdyear(msg->crdate),
	  strtime(msg->crtime,1));
  
  fclose(fp);

  memset(&rrr,0,sizeof(rrr));
  strcpy(rrr.from,thisuseracc.userid);
  strcpy(rrr.to,msg->from);
  sprintf(rrr.subject,getmsg(EMAILCLUBS_RRRSUBJ),EMAILCLUBNAME,msg->msgno);
  sprintf(rrr.history,HST_RECEIPT" %s/%ld",EMAILCLUBNAME,msg->msgno);
  rrr.flags=MSF_CANTMOD;

  sprintf(hdrname,TMPDIR"/rrrH%d%lx",getpid(),time(0));
  if((fp=fopen(hdrname,"w"))==NULL){
    unlink(fname);
    return;
  }
  fwrite(&rrr,sizeof(rrr),1,fp);
  fclose(fp);

  sprintf(command,"%s %s %s",BBSMAILBIN,hdrname,fname);
  system(command);
  unlink(hdrname);
  unlink(fname);

  if(uinsys(msg->from,1)){
    setmbk(mail_msg);
    sprintf(outbuf,getmsglang(RRRINJ,othruseracc.language-1),
	    thisuseracc.userid);
    injoth(&othruseronl,outbuf,0);
  }
  
  msg->flags&=~MSF_RECEIPT;
}


void
outmsg(int clubid, struct message *msg)
{
  char *preamble, *body, *footer;
  makeheader(clubid,msg);

  preamble=mkpre(clubid,msg);
  body=mkbody(clubid,msg);
  footer=mkfooter(clubid,msg);

  dumpndx(clubid,msg);
  dumpmsg(preamble,body,footer);
  
  if(msg->flags&MSF_RECEIPT){
    setmbk(emailclubs_msg);
    receipt(clubid,msg);
    setmbk(mail_msg);
  }
  updatemsg(clubid,msg);
}


void static
mkxlation()
{
  if(!loadprefs(USERQWK,&userqwk)){
    fatal("Unable to read user mailer preferences for %s",
	  thisuseracc.userid);
  }

  readxlation();
  xlationtable=(userqwk.flags&OMF_TR)>>OMF_SHIFT;

  if(userqwk.flags&USQ_GREEKQWK){

    /* Greek QWK, translate NL/CR to ASCII 0x0c */

    xlation[xlationtable]['\n']=EOL_GREEKQWK;
    xlation[xlationtable]['\r']=EOL_GREEKQWK;

  } else {

    /* Normal QWK, translate NL/CR to ASCII 224 */

    xlation[xlationtable]['\n']=EOL_QWK;
    xlation[xlationtable]['\r']=EOL_QWK;

#ifdef GREEK

    /* Translate accented lower case eta (ASCII 224) to "n" */
    /* It isn't an eta, but it looks extremely close and we */
    /* can't know the exact charset used, so only ASCII is  */
    /* a certainty. */

    if(fixeta)xlation[xlationtable][224]=etaxlt;

#endif /* GREEK */

  }
}


int
messagesdat()
{
  if((msgdat=fopen("messages.dat","w"))==NULL){
    logerrorsys("Unable to create messages.dat");
    return 1;
  }

  if((ndxpers=fopen("personal.ndx","w"))==NULL){
    logerrorsys("Unable to create personal.ndx");
    return 1;
  }

  mkxlation();

  msgno=numatt=0;
  lastconf=-1;

  /* Write the QWK copyright signature */

  clrbuf();
  strbuf(QWKSIG);
  wrtbuf();

  return 0;
}


int getnumatt()
{
  return numatt;
}
