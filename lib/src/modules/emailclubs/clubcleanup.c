/*****************************************************************************\
 **                                                                         **
 **  FILE:     clubcleanup.c                                                **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 95                                              **
 **            B, August 96                                                 **
 **            C, August 96                                                 **
 **  PURPOSE:  Perform club cleanup                                         **
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
 * Revision 1.1  2001/04/16 14:54:58  alexios
 * Initial revision
 *
 * Revision 0.1  2000/12/08 15:12:45  alexios
 * Initial checkin.
 *
 * Revision 1.5  1999/07/18 21:12:42  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
 *
 * Revision 1.4  1998/12/27 15:17:13  alexios
 * Added autoconf support. Minor fixes.
 *
 * Revision 1.3  1998/08/11 09:59:43  alexios
 * Made sure msgno points beyond the last message in a club to
 * account for Major->Megistos conversion problems and possible
 * corruptions in the databases.
 *
 * Revision 1.2  1998/07/24 10:08:19  alexios
 * Upgraded to version 0.6 of library.
 *
 * Revision 1.1  1997/11/06 20:09:02  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 1.0  1997/08/30 12:52:57  alexios
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
#define WANT_CTYPE_H 1
#define WANT_STRINGS_H 1
#define WANT_DIRENT_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "email.h"
#include "mailcleanup.h"
#include "mbk_emailclubs.h"


struct top *toppop, *topmsgs, *topfiles, *topblts;
struct top *topdnl;


void
inittop(struct top **t)
{
  (*t)=(struct top *)alcmem(sizeof(struct top)*TOP_N_ENTRIES);
  memset((*t),0,sizeof(struct top)*TOP_N_ENTRIES);
}


void
entertop(struct top *t, char *label, char *scorestg, int score)
{
  int i,j;
  for(i=0;i<TOP_N_ENTRIES-1;i++){
    if(score>t[i].score){
      for(j=TOP_N_ENTRIES-1;j>i;j--)memcpy(&t[j],&t[j-1],sizeof(struct top));
      strcpy(t[i].label,label);
      strcpy(t[i].scorestg,scorestg);
      t[i].score=score;
      break;
    }
  }
}


void
savetop(struct top *t, char *dir, char *name)
{
  FILE *fp;
  int i;
  char fname[256],command[256];

  sprintf(fname,"%s/%s",dir,name);
  if((fp=fopen(fname,"w"))==NULL)return;
  for(i=0;i<TOP_N_ENTRIES;i++){
    if(t[i].label[0])fprintf(fp,"%9s  %s\n",t[i].scorestg,t[i].label);
  }
  fclose(fp);
  if(!getuid() || !getgid()){
    sprintf(command,"chown bbs.bbs %s >&/dev/null",fname);
    system(command);
  }
}


char *
ltoa(long l)
{
  static char res[20];
  sprintf(res,"%ld",l);
  return res;
}


int
cleanup_checklocks(struct message *msg)
{
  int i;
  channel_status_t status;
  char lock[256],dummy[64];

  for(i=0;i<chan_count;i++){
    if(channel_getstatus(channels[i].ttyname,&status)){
      if(status.result==LSR_USER){
	sprintf(dummy,"%d",msg->msgno);
	sprintf(lock,MSGREADLOCK,channels[i].ttyname,
		msg->club[0]?msg->club:EMAILCLUBNAME,
		dummy);
	if(lock_check(lock,dummy)>0)return 0;
      }
    }
  }
  return 1;
}


int
cleanup_erasemsg(struct message *msg)
{
  char fname[512], clubdir[256];
  int timeout=0, ok=0;
  int retval=0;
  struct stat st;

  /* Wait until message becomes free, or 20 seconds have passed */

  for(timeout=0;timeout<20;timeout++){
    if(cleanup_checklocks(msg)){
      ok=1;
      break;
    } else sleep(1);
  }


  /* Not ok, message still being acted upon. Ignoring it. */

  if(!ok)return -1;

  
  /* Not necessary here, but here goes... */

  if(msg->club[0])sprintf(clubdir,"%s/%s",MSGSDIR,msg->club);
  else strcpy(clubdir,EMAILDIR);


  /* Delete files and count space freed */

  sprintf(fname,"%s/"MESSAGEFILE,clubdir,msg->msgno);
  if(!stat(fname,&st))retval+=st.st_size;
  unlink(fname);
  sprintf(fname,"%s/.ATT/%d.att",clubdir,msg->msgno);
  if(!stat(fname,&st))if(st.st_nlink==1)retval+=st.st_size;
  unlink(fname);


  /* Update message replied to */

  if(msg->replyto && msg->flags&MSF_REPLY){
    FILE *fp;
    struct message replied;
    char lock[256],s[64],*cp,club[256],t[256],*clp;
    int ok;

    if((cp=strstr(msg->history,HST_REPLY))!=NULL){
      ok=(sscanf(cp,"%*s %s",t)==1);
      if(ok){
	ok=(clp=strchr(t,'/'))!=NULL;
	if(ok){
	  *clp=0;
	  strcpy(club,t);
	}
      }
      if(sameas(club,EMAILCLUBNAME))strcpy(club,".email");
    }

    sprintf(s,"%d",msg->replyto);
    sprintf(lock,MESSAGELOCK,club,s);
    if(lock_wait(lock,10)==LKR_TIMEOUT)return retval;
    lock_place(lock,"updating");

    sprintf(fname,"%s/%s/"MESSAGEFILE,MSGSDIR,club,msg->replyto);
    if((fp=fopen(fname,"r+"))!=NULL){
      if(fread(&replied,sizeof(replied),1,fp)){
	int i=replied.replies;
	if((--replied.replies)<0)replied.replies=0;
	if(replied.replies!=i){
	  rewind(fp);
	  fwrite(&replied,sizeof(replied),1,fp);
	}
      }
      fclose(fp);
    }
    lock_rm(lock);
  }
  return retval;
}


void
fwperiodic(struct message *msg)
{
  FILE *fp1, *fp2, *fp3;
  struct message checkmsg, orig;
  char temp[256], source[256], fatt[256], lock[256], clubdir[256];
  char clubname[256];
  char header[256], body[256], command[256], original[256], origclub[256];
  char origdir[256];
  int bytes, clubmsg=0;

  memcpy(&orig,msg,sizeof(orig));

  if(msg->club[0])strcpy(origclub,msg->club);
  else strcpy(origclub,EMAILCLUBNAME);
  strcpy(origdir,msg->club);


  clubmsg=1;
  strcpy(clubdir,msg->club);
  strcpy(clubname,clubdir);
  loadclubhdr(msg->club);


  /* Check if we can copy the file attachment */

  if(clubmsg && (msg->flags&MSF_FILEATT)){
    msg->flags|=MSF_APPROVD;
  }


  /* Mail the message */
  
  sprintf(original,"%s/%d",clubdir,msg->msgno);

  if(!origdir[0]){
    sprintf(source,EMAILDIR"/"MESSAGEFILE,msg->msgno);
  } else {
    sprintf(source,"%s/%s/"MESSAGEFILE,MSGSDIR,clubdir,msg->msgno);
  }

  if((fp1=fopen(source,"r"))==NULL){
    error_fatalsys("Unable to open %s.",source);
  }

  sprintf(body,TMPDIR"/cc%05dB",getpid());
  if((fp2=fopen(body,"w"))==NULL){
    error_fatalsys("Unable to create %s.",body);
  }

  sprintf(header,TMPDIR"/cc%05dH",getpid());
  if((fp3=fopen(header,"w"))==NULL){
    error_fatalsys("Unable to create %s.",header);
  }

  fwrite(msg,sizeof(struct message),1,fp3);
  fclose(fp3);

  fseek(fp1,sizeof(struct message),SEEK_SET);
  do{
    if((bytes=fread(temp,1,sizeof(temp),fp1))!=0){
      if(msg->cryptkey)bbscrypt(temp,bytes,msg->cryptkey);
      fwrite(temp,bytes,1,fp2);
    }
  }while(bytes);
  
  fclose(fp1);
  fclose(fp2);

  lock_rm(lock);

  if(!origdir[0]){
    sprintf(fatt,EMAILDIR"/"MSGATTDIR"/"FILEATTACHMENT,msg->msgno);
  } else {
    sprintf(fatt,"%s/%s/%s/"FILEATTACHMENT,
	    MSGSDIR,origdir,MSGATTDIR,msg->msgno);
  }

  if(!(msg->flags&MSF_FILEATT)){
    sprintf(command,"%s %s %s",BBSMAILBIN,header,body);
  }else {
    sprintf(command,"%s %s %s -h %s",BBSMAILBIN,header,body,fatt);
  }
  system(command);


  /* Notify the user(s) */
    
  if((fp1=fopen(header,"r"))==NULL){
    printf("\n\nclubcleanup(): ERROR, Unable to open message header %s",header);
  } else if(fread(&checkmsg,sizeof(checkmsg),1,fp1)!=1){
    fclose(fp1);
    printf("\n\nclubcleanup(): ERROR, Unable to read message header %s\n",header);
  }
  fclose(fp1);


  /* Clean up */

  unlink(header);
  unlink(body);
  cleanup_erasemsg(&orig);
}


static int
msgselect(const struct dirent *d)
{
  return d->d_name[0]!='.';
}


void
clubcleanup()
{
  char fname[256];
  DIR *dp;
  struct dirent *dir, **msgs;
  struct clubheader club;
  struct message msg;
  FILE *fp;
  int ctoday=cofdate(today());
  int msgdel=0, msgdelb=0, msglive=0, msgper=0, msgfile=0, msgunapp=0;
  int msgfper=0, msgpop=0, msgdnl=0;
  uint32 pass, n, i, maxmsgno=0;

  if(dayssince<1){
    printf("clubcleanup(): no need to cleanup clubs yet.\n");
    return;
  } else printf("Clubs cleanup...\n\n");

  inittop(&toppop);
  inittop(&topmsgs);
  inittop(&topfiles);
  inittop(&topblts);
  inittop(&topdnl);

  strcpy(fname,CLUBHDRDIR);
  if((dp=opendir(fname))==NULL){
    printf("clubcleanup(): can't open directory %s, cleanup not done\n",fname);
    return;
  }

  sysvar->clubmsgslive=0;
  printf("Club name        MSGDEL KBDEL NMSGS NFILE UNAPP  NPER FWPER\n");

  while((dir=readdir(dp))!=NULL){
    maxmsgno=0;

    /* Get the name of a club */

    if(dir->d_name[0]!='h')continue;
    printf("%-16s: ",&(dir->d_name[1]));


    /* Open the header of the club */

    sprintf(fname,"%s/%s",CLUBHDRDIR,dir->d_name);
    if((fp=fopen(fname,"r"))==NULL){
      printf("Error while opening header (errno=%d)\n",errno);
      continue;
    }


    /* Read the header */

    memset(&club,0,sizeof(club));
    if(fread(&club,sizeof(club),1,fp)!=1){
      int i=errno;
      printf("Error while reading header (errno=%d, %s)\n",i,strerror(i));
      fclose(fp);
      continue;
    }
    fclose(fp);


    /* Open the club's directory */

    sprintf(fname,"%s/%s",MSGSDIR,club.club);
    if((n=scandir(fname,&msgs,msgselect,alphasort))<0){
      printf("Error while reading directory %s\n",fname);
      continue;
    }

    /* Read and process club's message files */

    msgdel=msgdelb=msglive=msgper=msgfile=msgunapp=msgfper=0;
    msgpop=msgdnl=0;

    for(i=0;i<n;i++){
      dir=msgs[i];
      sprintf(fname,"%s/%s/%s",MSGSDIR,club.club,dir->d_name);
      
      if((fp=fopen(fname,"r"))==NULL)continue;
      
      memset(&msg,0,sizeof(msg));
      if(fread(&msg,sizeof(msg),1,fp)!=1){
	fclose(fp);
	continue;
      }

      if(strncmp(msg.club,club.club,strlen(club.club)+1)){
	fprintf(stderr,"Fixing corrupted message: (%s)\n",fname);
	strcpy(msg.club,club.club);
	rewind(fp);
	if(ftell(fp)==0) fwrite(&msg,sizeof(msg),1,fp);
      }
      fclose(fp);

      /* Record the maximum message number */

      if(msg.msgno>maxmsgno)maxmsgno=msg.msgno;

      
      /* expire club messages */

      if((club.msglife>0)&&((msg.flags&MSF_EXEMPT)==0)&&(msg.period==0)){
	if((ctoday-cofdate(msg.crdate))>club.msglife){
	  int dbytes=cleanup_erasemsg(&msg);
	  if(dbytes!=-1){
	    msgdel++;
	    msgdelb+=dbytes;
	  }
	} else {
	  sysvar->clubmsgslive++;
	  msglive++;
	}
      } else {
	sysvar->clubmsgslive++;
	msglive++;
      }

      if(msg.flags&MSF_FILEATT){
	msgfile++;
	if((msg.flags&MSF_APPROVD)==0)msgunapp++;
      }

      if(msg.period){
	msgper++;
	if(ctoday-cofdate(msg.crdate)>=msg.period){
	  fwperiodic(&msg);
	  msgfper++;
	}
      }

      msgpop+=msg.timesread;
      if(msg.flags&MSF_FILEATT){
	msgdnl+=msg.timesdnl;
      }

      free(msgs[i]);
    }
    free(msgs);
    
    /* Paranoia check: make sure club's msgno pointer points beyond
       last message in area */

    if(((int32)club.msgno==-1) || (club.msgno<maxmsgno))club.msgno=maxmsgno;
    /*fprintf(stderr,"club=%s (%s) msgno=%u, max=%u\n",
      club.club,club.descr,club.msgno,maxmsgno);*/


    /* Update club header */

    club.nmsgs=msglive;
    club.nper=msgper;
    club.nfiles=msgfile;
    club.nfunapp=msgunapp;

    /* Record top entries */

    entertop(toppop,club.club,ltoa(msgpop),msgpop);
    entertop(topmsgs,club.club,ltoa(msglive),msglive);
    entertop(topfiles,club.club,ltoa(msgfile),msgfile);
    entertop(topblts,club.club,ltoa(club.nblts),club.nblts);
    entertop(topdnl,club.club,ltoa(msgdnl),msgdnl);


    /* Save club header */

    sprintf(fname,"%s/h%s",CLUBHDRDIR,club.club);
    if((fp=fopen(fname,"w"))==NULL){
      printf("Error while opening header (errno=%d)\n",errno);
      continue;
    }


    /* Write the header */
    
    if(fwrite(&club,sizeof(club),1,fp)!=1){
      printf("Error while writing header (errno=%d)\n",errno);
      fclose(fp);
      continue;
    }
    fclose(fp);


    /* Tabulate cleanup results */

    printf("%5d %5d %5d %5d %5d %5d %5d\n",
	   msgdel,msgdelb>>10,msglive,msgfile,msgunapp,msgper,msgfper);
    
  }


  /* End of Club cleanup, save top charts */

  for(pass=0;pass<2;pass++){
    char dir[256];
    
    if(!pass)strcpy(dir,STATDIR);
    else sprintf(dir,"%s/%ld",STATDIR,tdyear(today()));
    
    savetop(toppop,dir,"top-club-readings");
    savetop(topmsgs,dir,"top-club-messages");
    savetop(topfiles,dir,"top-club-files");
    savetop(topblts,dir,"top-club-bulletins");
    savetop(topdnl,dir,"top-club-downloads");
  }
}
