/*****************************************************************************\
 **                                                                         **
 **  FILE:     insert.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 1996, Version 0.5                               **
 **  PURPOSE:  Insert bulletins into the database.                          **
 **  NOTES:                                                                 **
 **                                                                         **
\*****************************************************************************/


/*
 * $Id$
 *
 * $Log$
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.6  1998/12/27 15:27:54  alexios
 * Added autoconf support. Minor fixes.
 *
 * Revision 0.5  1998/08/11 10:02:34  alexios
 * Fixed file transfer request to use FXM constants instead of
 * the previous, hackish way of doing it.
 *
 * Revision 0.4  1998/07/24 10:14:42  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.3  1997/11/06 16:54:01  alexios
 * Changed calls to setaudit() to use the new auditing scheme.
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
const char *__RCS=RCS_VER;
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
#include "mbk_bulletins.h"
#include "bltidx.h"
#include "bulletins.h"

#ifdef USE_LIBZ
#define WANT_ZLIB_H 1
#endif


static char *
askclub()
{
  static char insclub[16];

  strcpy(insclub,club);

  if(!club[0]){
    if(!getclub(insclub,NBCLUB,NBRCLB,
		thisuseracc.lastclub[0]?DEFLTS:0,thisuseracc.lastclub)){
      return NULL;
    }
  } else prompt(NBCLUB1);

  return insclub;
}


static int
askfile(char *club)
{
  int i;
  char c;
  static char fname[256];
  struct stat st;

  for(;;){
    fmt_lastresult=0;
    if((c=cnc_more())!=0){
      if(sameas(cnc_nxtcmd,"X"))return 0;
      if(sameas(cnc_nxtcmd,"."))return -1;
      i=cnc_int();
    } else {
      prompt(NBMSGN);
      inp_get(0);
      i=atoi(margv[0]);
      if((!margc||(margc==1&&sameas(margv[0],"."))) && !inp_reprompt()) {
	return -1;
      } else if (!margc) {
	cnc_end();
	continue;
      }
      if(inp_isX(margv[0]))return 0;
    }

    strcpy(fname,mkfname(MSGSDIR"/%s/"MESSAGEFILE,club,(uint32)i));
    if(stat(fname,&st)){
      prompt(NBMSGNR,club,i);
      cnc_end();
    } else return i;
  }
  return 0;
}


#ifdef USE_LIBZ


int
getmsgheader(char *club, int msgno,struct message *msg)
{
  char lock[256], fname[256], tmp[256];
  gzFile *zfp;

  sprintf(tmp,"%d",msgno);
  sprintf(lock,MESSAGELOCK,club,tmp);
  if((lock_wait(lock,20))==LKR_TIMEOUT)return 0;
  lock_place(lock,"reading");

  strcpy(fname,mkfname(MSGSDIR"/%s/"MESSAGEFILE,club,(long)msgno));
  if((zfp=gzopen(fname,"rb"))==NULL){
    gzclose(zfp);
    lock_rm(lock);
    return 0;
  } else if(gzread(zfp,msg,sizeof(struct message))<=0){
    gzclose(zfp);
    lock_rm(lock);
    return 0;
  }
  gzclose(zfp);
  lock_rm(lock);
  return 1;
}


static int
fcopymsg(char *source, char *target)
{
  gzFile *zs;
  FILE *t;
  int br, bw, tr, tw;
  char buf[8192];

  if((zs=gzopen(source,"rb"))==NULL){
    return -1;
  }
  if((t=fopen(target,"w"))==NULL){
    gzclose(zs);
    return -1;
  }

  if(gzread(zs,buf,sizeof(struct message))<=0){
    gzclose(zs);
    fclose(t);
    unlink(target);
    return -1;
  }

  for(br=bw=tr=tw=0;br==bw;){
    br=gzread(zs,buf,sizeof(buf));
    if(br<0){
      gzclose(zs);
      fclose(t);
      unlink(target);
      return -1;
    }
    if(!br)break;
    bw=fwrite(buf,1,br,t);
    if(bw<0){
      gzclose(zs);
      fclose(t);
      unlink(target);
      return -1;
    }
    tr+=br;
    tw+=bw;
  }
  gzclose(zs);
  fclose(t);
  if(tr!=tw){
    unlink(target);
    return -1;
  }
  return 0;
}


#else /* DON'T USE_LIBZ */


int
getmsgheader(char *club, int msgno,struct message *msg)
{
  char lock[256], fname[256], tmp[256];
  FILE *fp;

  sprintf(tmp,"%d",msgno);
  sprintf(lock,MESSAGELOCK,club,tmp);
  if((lock_wait(lock,20))==LKR_TIMEOUT)return 0;
  lock_place(lock,"reading");

  strcpy(fname,mkfname(MSGSDIR"/%s/"MESSAGEFILE,club,(uint32)msgno));
  if((fp=fopen(fname,"r"))==NULL){
    fclose(fp);
    lock_rm(lock);
    return 0;
  } else if(fread(msg,sizeof(struct message),1,fp)!=1){
    fclose(fp);
    lock_rm(lock);
    return 0;
  }
  fclose(fp);
  lock_rm(lock);
  return 1;
}


static int
fcopymsg(char *source, char *target)
{
  FILE *s, *t;
  int br, bw, tr, tw;
  char buf[8192];

  if((s=fopen(source,"r"))==NULL){
    return -1;
  }
  if((t=fopen(target,"w"))==NULL){
    fclose(s);
    return -1;
  }

  if(fseek(s,sizeof(struct message),SEEK_SET)){
    fclose(s);
    fclose(t);
    unlink(target);
    return -1;
  }

  for(br=bw=tr=tw=0;br==bw;){
    br=fread(buf,1,sizeof(buf),s);
    if(br<0){
      fclose(s);
      fclose(t);
      unlink(target);
      return -1;
    }
    if(!br)break;
    bw=fwrite(buf,1,br,t);
    if(bw<0){
      fclose(s);
      fclose(t);
      unlink(target);
      return -1;
    }
    tr+=br;
    tw+=bw;
  }
  fclose(s);
  fclose(t);
  if(tr!=tw){
    unlink(target);
    return -1;
  }
  return 0;
}


#endif /* USE_ZLIB */


static void
insmsg(char *club, uint32 msgno)
{
  struct message msg;
  struct bltidx blt;
  char source[256], target[256], opt='B';
  struct stat st;


  /* Get the message header -- we'll copy most of the record from here */

  if(!getmsgheader(club,msgno,&msg)){
    prompt(NBIO,club,msgno);
    return;
  }


  /* Prepare the new bulletin record */

  bzero(&blt,sizeof(struct bltidx));

  blt.num=dbgetlast()+1;
  blt.date=today();
  sprintf(blt.fname,"%d.blt",msgno);
  strcpy(blt.area,club);
  strncpy(blt.author,msg.from,sizeof(blt.author));
  strcpy(blt.descr,msg.subject);


  /* Set the source and target files for linking/copying the bulletin */

  strcpy(source,mkfname(MSGSDIR"/%s/"MESSAGEFILE,club,msgno));
  strcpy(target,mkfname(MSGSDIR"/%s/%s/%s",club,MSGBLTDIR,blt.fname));


  /* Check if the article already exists in the database */

  if(dbexists(blt.area,blt.fname)){
    struct bltidx tmp;
    dbget(&tmp);
    prompt(NBFNXS,tmp.fname,tmp.area,tmp.num);
    return;
  }


  /* Prompt the user if the message has a file attachment */

  if(msg.flags&MSF_FILEATT){
    int i;
    char fatt[256];
    struct stat st1, st2;

    strcpy(source,mkfname(MSGSDIR"/%s/"MESSAGEFILE,club,msgno));
    strcpy(fatt,mkfname(MSGSDIR"/%s/%s/%d.att",club,MSGATTDIR,msgno));

    if(stat(fatt,&st1)){
      prompt(NBATTR,club,msgno);
      return;
    }
    if(stat(source,&st2)){
      prompt(NBBODR,club,msgno);
      return;
    }

    prompt(NBATT,club,msgno,st1.st_size);

    for(;;){
      inp_setflags(INF_HELP);
      i=get_menu(&opt,0,0,NBBODATT,NBBAR,"AB",NBBAD,
		st1.st_size>=st2.st_size?'A':'B');
      inp_clearflags(INF_HELP);
      if(!i){
	prompt(BLTCAN);
	return;
      }
      if(i==-1){
	prompt(NBATT,club,msgno,st1.st_size);
	cnc_end();
	continue;
      } else break;
    }

    if(opt=='A')strcpy(source,fatt);
  }


  /* Check if the target file already exists */

  if(!stat(target,&st)){
    prompt(NBFNEX,blt.fname,blt.area);
    return;
  }


  /* Link or copy the bulletin file */

  if(opt=='A'){
    if(link(source,target)<0){
      if(fcopy(source,target)<0){
	prompt(NBCPR);
	return;
      }
    }
  } else {
    if(fcopymsg(source,target)<0){
      prompt(NBCPR);
      return;
    }
  }


  /* Insert the database entry */

  blt.num=dbgetlast()+1; /* Just in case */
  if(!dbins(&blt)){
    prompt(NBERR);
    return;
  }


  /* Notify the user */

  prompt(NBINFO,
	 blt.num,
	 blt.fname,
	 blt.descr,
	 blt.area,
	 blt.author);


  /* Update the club header */

  loadclubhdr(club);
  clubhdr.nblts++;
  saveclubhdr(&clubhdr);


  /* Audit it */

  if(audins)audit(thisuseronl.channel,AUDIT(BLTINS),
		  thisuseracc.userid,blt.fname,blt.area);

}


static void
insupl(char *club)
{
  char fname[256],command[256],*cp,name[256],dir[256];
  char source[256],target[256];
  FILE *fp;
  int  count=-1;
  struct bltidx blt;


  /* Upload the file */
  
  xfer_setaudit(0,NULL,NULL,0,NULL,NULL);
  sprintf(source,thisuseracc.userid);
  xfer_add(FXM_UPLOAD,source,"",0,0);
  xfer_run();


  /* Scan the uploaded file(s) */
  
  sprintf(fname,XFERLIST,getpid());
  
  if((fp=fopen(fname,"r"))==NULL){
    prompt(BLTCAN);
    goto kill;
  }
  
  while (!feof(fp)){
    char line[1024];
    
    if(fgets(line,sizeof(line),fp)){
      count++;
      if(!count)strcpy(dir,line);
      else if(count==1)strcpy(name,line);
    }
  }
  
  if((cp=strchr(dir,'\n'))!=NULL)*cp=0;
  if((cp=strchr(name,'\n'))!=NULL)*cp=0;
  fclose(fp);
  
  if(count<1){
    prompt(BLTCAN);
    goto kill;
  } else if(count>1){
    prompt(BLTUPL2M);
  }


  /* Prepare the new bulletin record */

  bzero(&blt,sizeof(struct bltidx));

  blt.num=dbgetlast()+1;
  blt.date=today();
  strcpy(blt.area,club);


  /* Get the author of the bulletin */

  if(!get_userid(blt.author,NBUSER,NBRRUID,NBUSERD,thisuseracc.userid,0)){
    prompt(BLTCAN);
    goto kill;
  }


  /* Get the description/title of the bulletin */

  if(!getdescr(blt.descr,NBDSCR)){
    prompt(BLTCAN);
    goto kill;
  }


  /* Generate the filename */

  {
    int i;
    struct stat st;
    char *sp;
    
    if((cp=strrchr(name,'/'))!=NULL)*cp++=0;
    if(strlen(cp)>8)cp[8]=0;
    if((sp=strchr(cp,'.'))!=NULL){
      *sp++=0;
      if(strlen(sp)>3)sp[3]=0;
    }
    sprintf(blt.fname,"%s.%s",cp,(sp&&*sp)?sp:"blt");
    for(i=1;;i++){
      strcpy(target,mkfname(MSGSDIR"/%s/%s/%s",club,MSGBLTDIR,blt.fname));
      if(stat(target,&st))break;
      sprintf(blt.fname,"%s.%d",cp,i);
    }
  }


  /* Now copy the uploaded file over */

  sprintf(source,"%s/%s",dir,cp);
  if(fcopy(source,target)){
    prompt(NBCPER2,blt.fname);
    unlink(target);
    goto kill;
  }


  /* Insert the database entry */

  if(!dbins(&blt)){
    prompt(NBERR);
    goto kill;
  }

  
  /* Notify the user */

  prompt(NBINFO,
	 blt.num,
	 blt.fname,
	 blt.descr,
	 blt.area,
	 blt.author);


  /* Update the club header */

  loadclubhdr(club);
  clubhdr.nblts++;
  saveclubhdr(&clubhdr);


  /* Audit it */

  if(audins)audit(thisuseronl.channel,AUDIT(BLTINS),
		  thisuseracc.userid,blt.fname,blt.area);

 
  /* Kill remaining transfer files */

 kill:
  sprintf(command,"rm -rf %s %s",fname,dir);
  system(command);
  if(name[0]){
    sprintf(command,"rm -f %s >&/dev/null",name);
    system(command);
  }
  xfer_kill_list();
}


void
insertblt()
{
  char *insclub;
  int msgnum;

  if(getaccess(club)<flaxes)return;
  
  if((insclub=askclub())==NULL){
    prompt(BLTCAN);
    return;
  }

  if((msgnum=askfile(insclub))==0){
    prompt(BLTCAN);
    return;
  } else if(msgnum==-1) {
    cnc_end();
    insupl(insclub);
  }
  else insmsg(insclub,msgnum);
}


int
extins(char *msgspec)
{
  char *cp;
  if((cp=strchr(msgspec,'/'))==NULL){
    error_fatal("Syntax error running bulletins -insert %s",msgspec);
  }
  *cp++=0;
  insmsg(msgspec,atoi(cp));
  return 0;
}
