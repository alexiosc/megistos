/*****************************************************************************\
 **                                                                         **
 **  FILE:     convert.c                                                    **
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
 * Revision 1.1  2001/04/16 14:55:04  alexios
 * Initial revision
 *
 * Revision 0.4  1999/07/18 21:21:38  alexios
 * Updated code to read the move BBSCOD(E) variable.
 *
 * Revision 0.3  1998/12/27 15:33:03  alexios
 * Added autoconf support.
 *
 * Revision 0.2  1998/08/11 10:03:22  alexios
 * A couple of bug fixes, plus ad hoc club renames for Acrobase.
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
#define WANT_PWD_H 1
#define WANT_GRP_H 1
#include <bbsinclude.h>

#include <endian.h>
#include <typhoon.h>
#include "bbs.h"
#include "email.h"
#include "clubs.h"
#include "../files/cnvutils.h"
#include "mbk_emailclubs.h"
#define __SYSVAR_UNAMBIGUOUS__ 1
#include "mbk_sysvar.h"

#ifdef USE_LIBZ
#define WANT_ZLIB_H 1
#endif


void indexmsg(int majornum, char *club, int msgno, int fpos, int flen);
char* findmsg(char *club, int majornum);
void traverse();
char *bbscode;


#define YN(x) (!(x)?'Y':'N')
#define fixto(x) ((x)>='0'?(x):((x)>'*'?(x)+44:((x)=='*'?(x):(x)+45)))
#define MAXSIGNO 65536


char dir[512];
char lastclub[24]="E-Mail";


struct clubidx {
  char  club[32];
  int   defax;
};


struct clubidx *ids;


/* Translate MAJOR's Mac-like CR characters to Unix NL */

static char *
nl2cr(char *s)
{
  char *cr;
  for(cr=strchr(s,'\r');cr;cr=strchr(cr+1,'\r'))*cr='\n';
  return s;
}



static void
makeheaderless(char *rec)
{
  struct clubheader new;
  char fname[256];

  /* Basics */

  memset(&new,0,sizeof(new));
  strcpy(new.club,&rec[25]);
  if(sameas(new.club,"Filosof"))strcpy(new.club,"Philosofia");
  if(sameas(new.club,"OS/2"))strcpy(new.club,"OS2");
  if(sameas(new.club,"User's"))strcpy(new.club,"Users");
  if(sameas(new.club,"travel"))strcpy(new.club,"Travel");
  if(sameas(new.club,"ANADROMH"))strcpy(new.club,"Anadromh");
  strcpy(lastclub,new.club);
  new.clubid=getclubid();
  strcpy(new.descr,"WARNING: headerless converted club!");
  strcpy(new.clubop,"Sysop");
  new.crdate=today();
  new.crtime=now();
  new.keyreadax=new.keydnlax=new.keywriteax=new.keyuplax=129;

  /* Parse message lifetime */

  new.msglife=clblif;

  /* accounting and charges */

  new.postchg=clbwchg;
  new.uploadchg=clbuchg;
  new.dnloadchg=clbdchg;
  new.credspermin=-1;

  /* Show progress */

  printf("%-10s %3d %-10s %s %s %c %c %c %c %3d\n",new.club,new.clubid,
	 new.clubop,strdate(new.crdate),strtime(new.crtime,1),
	 YN(new.keyreadax),YN(new.keydnlax),YN(new.keywriteax),YN(new.keyuplax),
	 new.msglife);
  fflush(stdout);

  /* Add the club */

  if(findclub(new.club)){
    fprintf(stderr,"OOPS: Area %s already exists. You must CLEAR the message\n"\
	    "base before running msgcnv! I'm assuming you don't have duplicate\n"\
	    "club names in your VESIGS.DAT. If you do, the VESIGS.DAT file is\n"\
	    "*very* damaged.\n\n",new.club);
    exit(1);
  }

  saveclubhdr(&new);

  sprintf(fname,"%s/%s",MSGSDIR,new.club);
  mkdir(fname,0770);

  sprintf(fname,"%s/%s/%s",MSGSDIR,new.club,MSGATTDIR);
  mkdir(fname,0770);

  sprintf(fname,"%s/%s/%s",MSGSDIR,new.club,MSGBLTDIR);
  mkdir(fname,0770);


  /* Add the club to all quickscan configurations */

  if(addnew)globalqsc(QSC_ADD,new.club);
}



static void
newclub(char *rec)
{
  struct clubheader new;
  char fname[256];

  /* Basics */
  
  memset(&new,0,sizeof(new));
  strcpy(new.club,&rec[5]);
  if(sameas(new.club,"Filosof"))strcpy(new.club,"Philosofia");
  if(sameas(new.club,"OS/2"))strcpy(new.club,"OS2");
  if(sameas(new.club,"User's"))strcpy(new.club,"Users");
  if(sameas(new.club,"travel"))strcpy(new.club,"Travel");
  if(sameas(new.club,"ANADROMH"))strcpy(new.club,"Anadromh");
  strcpy(lastclub,new.club);
  strcpy(ids[(unsigned char)rec[85]].club,new.club);
  ids[(unsigned char)rec[85]].defax=rec[114];

  new.clubid=rec[85];
  strcpy(new.descr,&rec[34]);
  strcpy(new.clubop,&rec[14]);
  new.crdate=convert_date(*((unsigned short int *)&rec[122]));
  new.crtime=convert_time(*((unsigned short int *)&rec[124]));
 
  /* Counters */

  new.nmsgs=new.msgno=((unsigned char)rec[86]|((unsigned char)rec[87]<<8));
  new.nfiles=((unsigned char)rec[88]|((unsigned char)rec[89]<<8));
  new.nfunapp=((unsigned char)rec[90]|((unsigned char)rec[91]<<8));

  /* Access control */

  switch(rec[114]){
  case 0:
    new.keyreadax=129;
  case 2:
    new.keydnlax=129;
  case 4:
    new.keywriteax=129;
  case 6:
    new.keyuplax=129;
  }

  /* Parse message lifetime */

  new.msglife=clblif;
  {
    char *lifetime="Message Lifetime: ", *cp;
    cp=strstr(&rec[155],lifetime);
    if(cp!=NULL){
      new.msglife=atoi(cp+strlen(lifetime));
    }
  }

  /* accounting and charges */

  new.postchg=clbwchg;
  new.uploadchg=clbuchg;
  new.dnloadchg=clbdchg;
  new.credspermin=-1;

  /* Show progress */

  printf("%-10s %3d %-10s %s %s %c %c %c %c %3d\n",new.club,new.clubid,
	 new.clubop,strdate(new.crdate),strtime(new.crtime,1),
	 YN(new.keyreadax),YN(new.keydnlax),YN(new.keywriteax),YN(new.keyuplax),
	 new.msglife);
  fflush(stdout);


  /* Add the club */

  if(findclub(new.club)){
    fprintf(stderr,"OOPS: Area %s already exists. You must CLEAR the message\n"\
	    "base before running msgcnv! I'm assuming you don't have duplicate\n"\
	    "club names in your VESIGS.DAT. If you do, the VESIGS.DAT file is\n"\
	    "*very* damaged.\n\n",new.club);
    exit(1);
  }

  saveclubhdr(&new);

  sprintf(fname,"%s/%s",MSGSDIR,new.club);
  mkdir(fname,0770);

  sprintf(fname,"%s/%s/%s",MSGSDIR,new.club,MSGATTDIR);
  mkdir(fname,0770);

  sprintf(fname,"%s/%s/%s",MSGSDIR,new.club,MSGBLTDIR);
  mkdir(fname,0770);


  /* Add the club's banner, if there is one */

  {
    char *thoughts="Thoughts of the Day:\r", *cp;
    cp=strstr(&rec[155],thoughts);
    if(cp!=NULL){
      FILE *fp;
      cp+=strlen(thoughts);
      nl2cr(cp);
      sprintf(fname,"%s/b%s",CLUBHDRDIR,new.club);
      if((fp=fopen(fname,"w"))==NULL){
	fprintf(stderr,"Oops, unable to write to banner file %s\n",fname);
	exit(1);
      }
      fputs(cp,fp);
      fputs("\n",fp);
      fclose(fp);
    }
  }

  /* Add the club to all quickscan configurations */

  if(addnew)globalqsc(QSC_ADD,new.club);
}


void
addihave(struct message *msg)
{
  FILE *fp;
  char fname[256];
  int i=today();

  sprintf(fname,"%s/ihave.%04d-%02d-%02d",
	  IHAVEDIR,tdyear(i),tdmonth(i)+1,tdday(i));
  
  if((fp=fopen(fname,"a"))==NULL)return;
  fprintf(fp,"%s/%s/%s %s/%ld\n",
	  msg->origbbs,msg->origclub,msg->msgid,
	  msg->club,msg->msgno);
  fclose(fp);
}


void
bbsencrypt(char *buf,int size,int key)
{
  char longkey[4]={0,0,0,0};
  register char smallkey;
  register int i;

  if(!key)return; /* club messages (key=0) aren't encrypted */
  memcpy(longkey,&key,sizeof(int));
  smallkey=(longkey[0]^longkey[1]^longkey[2]^longkey[3]);
  for(i=0;i<size;i++)buf[i]^=smallkey;
}


void
writemsg(struct message *msg, char *rec, int len)
{
  char msgname[256];
  FILE *fp;

    
  /* Generate the filename */

  if(!msg->club[0])sprintf(msgname,EMAILDIR"/"MESSAGEFILE,msg->msgno);
  else sprintf(msgname,"%s/%s/"MESSAGEFILE,MSGSDIR,msg->club,msg->msgno);
  
  
  /* Write the message header */

  if((fp=fopen(msgname,"w"))==NULL){
    fclose(fp);
    fprintf(stderr,"Unable to create %s\n",msgname);
    exit(1);
  }
  
  if(fwrite(msg,sizeof(struct message),1,fp)!=1){
    fprintf(stderr,"Unable to write header to %s\n",msgname);
    exit(1);
  }
  
  /* Now write the message body */
  
  nl2cr(&rec[155]);
  strcat(&rec[155],"\n");
  bbsencrypt(&rec[155],len+1,msg->cryptkey);
  if(fwrite(&rec[155],len+1,1,fp)!=1){
    fprintf(stderr,"Unable to write body to %s (errno=%d)\n",msgname,errno);
    exit(1);
  }
  fclose(fp);
}


void
addmsg(FILE *fp,char *club,int msgno,int fpos,int flen)
{
  struct message msg;
  char rec[65536];

  fseek(fp,fpos,SEEK_SET);
  fread(rec,flen,1,fp);

  bzero(&msg,sizeof(msg));
  
  rec[4]=fixto(rec[4]);
  
  /* BASICS */

  strcpy(msg.from,&rec[14]);
  strcpy(msg.to,&rec[4]);
  strcpy(msg.subject,&rec[34]);
  if(strcmp(club,"Email"))strcpy(msg.club,club);

  /* Message ID and origin */

  strcpy(msg.origbbs,bbscode);
  strcpy(msg.origclub,msg.club);
  sprintf(msg.msgid,"%ld.%02d%02d%02d%02d%02d%02d",
	  msg.msgno,
	  tdday(msg.crdate),tdmonth(msg.crdate)+1,tdyear(msg.crdate)%100,
	  tdhour(msg.crtime),tdmin(msg.crtime),tdsec(msg.crtime));

  /* CREATION DATE/TIME */

  msg.crdate=convert_date(*((unsigned short int *)&rec[122]));
  msg.crtime=convert_time(*((unsigned short int *)&rec[124]));

  /* MISC */

  msg.msgno=msgno;
  strcpy(msg.history,"Converted from MajorBBS");
  sprintf(msg.fatt,FILEATTACHMENT,(long)msgno);
  msg.replies=((unsigned char)rec[126]|((unsigned char)rec[127]<<8));
  if(!strcmp(club,"Email")){
    srand(time(NULL));
    while(!msg.cryptkey)msg.cryptkey=rand()%(1<<30);
  }

  /* FLAGS */

  msg.flags=0;
  if(rec[128]&0x2)msg.flags|=MSF_EXEMPT;
  if(rec[128]&0x10)msg.flags|=MSF_RECEIPT;
  if(rec[128]&0x40){
    char source[512], target[512];
    msg.flags|=MSF_FILEATT;

    sprintf(source,"%s/%s/%u.att",dir,club,*((unsigned int*)&rec[0]));

    if(!strcmp(club,"Email")){
      sprintf(target,EMAILATTDIR"/"FILEATTACHMENT,msg.msgno);
    } else {
      sprintf(target,"%s/%s/%s/"FILEATTACHMENT,MSGSDIR,msg.club,
	      MSGATTDIR,msg.msgno);
    }
    fcopy(source,target);
  }

  if(rec[128]&0x80)msg.flags|=MSF_APPROVD;
  if(rec[128]&0x80)msg.flags|=MSF_CANTMOD;



  /* Debugging info */

#if 0
  printf("%7d --> %10s/%-6d  FROM %-10s TO %-10s RE %s\n",
	 *((int*)rec),club,msgno,
	 msg.from,msg.to,msg.subject);
#endif


  /* Write message header and body */

  writemsg(&msg,rec,flen-154);

  /* Add to the Ihave/Sendme list */

  addihave(&msg);
}



void
convert(char *arg_majordir)
{
  FILE            *fp;
  char            rec[64<<10], c, *fname=rec;
  int             reclen;
  int             num=0, areas=0, headerless=0, msgno=0, fpos;
  promptblk *msg;

  ids=alcmem(sizeof(struct clubidx)*256);

  strcpy(dir,arg_majordir);
  
  msg=opnmsg("sysvar");
  bbscode=stgopt(SYSVAR_BBSCOD);
  clsmsg(msg);

  msg=opnmsg("emailclubs");
  clbwchg=numopt(CLBWCHG,-32767,32767);
  clbuchg=numopt(CLBUCHG,-32767,32767);
  clbdchg=numopt(CLBDCHG,-32767,32767);
  clblif=numopt(CLBLIF,0,32767);
  clsmsg(msg);

  /* Start conversion */

  sprintf(fname,"%s/vesigs.txt",arg_majordir?arg_majordir:".");
  fp=fopen(fname,"r");
  if(fp==NULL){
    sprintf(fname,"%s/VESIGS.TXT",arg_majordir?arg_majordir:".");
    if((fp=fopen(fname,"r"))==NULL){
      fprintf(stderr,
	      "msgcnv: convert(): unable to find vesigs.txt or VESIGS.TXT.\n");
      exit(1);
    }
  }

  printf("PASS 1. Adding clubs:\n");
  printf("                                             ACCESS:\n");
  printf("CLUB NAME   ID CLUB-OP    CREATION DATE/TIME R D W U MsgLife\n");
  printf("------------------------------------------------------------\n");

  while(!feof(fp)){
    if(fscanf(fp,"%d\n",&reclen)==0){
      if(feof(fp))break;
      fprintf(stderr,"msgcnv: convert(): unable to parse record length. Corrupted file?\n");
      exit(1);
    }
    if(feof(fp))break;
    fgetc(fp);			/* Get rid of the comma after the record length */

    if(fread(rec,reclen,1,fp)!=1){
      fprintf(stderr,"msgcnv: convert(): unable to read record around pos=%ld.\n",ftell(fp));
      exit(1);
    }

    if(rec[4]=='/'){
      newclub(rec);
      areas++;
    }

    do c=fgetc(fp); while(c=='\n' || c=='\r' || c==26);
    ungetc(c,fp);
  }

  rewind(fp);
  printf("\n\nPASS 2. Adding headerless clubs:\n");
  printf("                                             ACCESS:\n");
  printf("CLUB NAME   ID CLUB-OP    CREATION DATE/TIME R D W U MsgLife\n");
  printf("------------------------------------------------------------\n");
  while(!feof(fp)){
    if(fscanf(fp,"%d\n",&reclen)==0){
      if(feof(fp))break;
      fprintf(stderr,"msgcnv: convert(): unable to parse record length. Corrupted file?\n");
      exit(1);
    }
    if(feof(fp))break;
    fgetc(fp);			/* Get rid of the comma after the record length */

    if(fread(rec,reclen,1,fp)!=1){
      fprintf(stderr,"msgcnv: convert(): unable to read record around pos=%ld.\n",ftell(fp));
      exit(1);
    }

    {
      char tmp[64];
      strcpy(tmp,&rec[25]);
      if(sameas(tmp,"Filosof"))strcpy(tmp,"Philosofia");
      if(sameas(tmp,"OS/2"))strcpy(tmp,"OS2");
      if(sameas(tmp,"User's"))strcpy(tmp,"Users");
      if(sameas(tmp,"travel"))strcpy(tmp,"Travel");
      if(sameas(tmp,"ANADROMH"))strcpy(tmp,"Anadromh");

      if(rec[24]=='/' && strcmp(lastclub,tmp)){
	if(!findclub(tmp)){
	  makeheaderless(rec);
	  areas++;
	  headerless++;
	}
	strcpy(lastclub,tmp);
      }
    }

    do c=fgetc(fp); while(c=='\n' || c=='\r' || c==26);
    ungetc(c,fp);
  }


  rewind(fp);
  printf("\n\nPASS 3. Reading and ordering messages.\n");
  printf("------------------------------------------------------------\n");
  while(!feof(fp)){
    if(fscanf(fp,"%d\n",&reclen)==0){
      if(feof(fp))break;
      fprintf(stderr,"msgcnv: convert(): unable to parse record length. Corrupted file?\n");
      exit(1);
    }
    if(feof(fp))break;
    fgetc(fp);			/* Get rid of the comma after the record length */

    fpos=ftell(fp);
    if(fread(rec,reclen,1,fp)!=1){
      fprintf(stderr,"msgcnv: convert(): unable to read record around pos=%ld.\n",ftell(fp));
      exit(1);
    }

    if(rec[4]=='/')continue;
    if(rec[24]=='/' && strcmp(lastclub,&rec[25])){
      msgno=0;
      strcpy(lastclub,&rec[25]);
    }
    {
      char tmp[256];
      strcpy(tmp,&rec[25]);
      if(sameas(tmp,"Filosof"))strcpy(tmp,"Philosofia");
      if(sameas(tmp,"OS/2"))strcpy(tmp,"OS2");
      if(sameas(tmp,"User's"))strcpy(tmp,"Users");
      if(sameas(tmp,"travel"))strcpy(tmp,"Travel");
      if(sameas(tmp,"ANADROMH"))strcpy(tmp,"Anadromh");
      indexmsg(*((int*)rec),rec[24]=='/'?tmp:"Email",msgno,fpos,reclen);
    }

    num++;
    do c=fgetc(fp); while(c=='\n' || c=='\r' || c==26);
    ungetc(c,fp);
    if((num%100)==0)printf("%d ",num);fflush(stdout);
  }

  printf("\n\nPASS 4. Converting messages.\n");
  printf("------------------------------------------------------------\n");
  
  /* Now renumber and convert all the messages in order */

  traverse(fp);

  printf("\n\nCreated %d messages in %d areas (%d headerless clubs).\n",
	 num,areas+1,headerless);
}
