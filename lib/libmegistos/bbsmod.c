/*****************************************************************************\
 **                                                                         **
 **  FILE:     bbsmod.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, June 94                                                   **
 **  PURPOSE:  Implement various module functions.                          **
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
 * Revision 1.1  2001/04/16 14:49:30  alexios
 * Initial revision
 *
 * Revision 0.9  2000/01/06 10:56:23  alexios
 * Changed calls to write(2) to send_out().
 *
 * Revision 0.8  1999/07/28 23:06:34  alexios
 * Fixed slight bulletins bug (yes, a bulletins but in bbsmod).
 *
 * Revision 0.7  1999/07/18 21:01:53  alexios
 * Slight changes in calls to fatal() and fatalsys(). Beautifications.
 * Minor corrections to syschat() and loaduser().
 *
 * Revision 0.6  1998/12/27 14:31:16  alexios
 * Added autoconf support. Made allowances for new getlinestatus().
 * Added magic number checking for SYSVAR and backing up of the
 * file. Added code to look in passwd for the uid and gid of the
 * BBS user. Added flag to show that user is in Sysop chat mode so
 * that Sysops can be warned when abandoning their users in the
 * 'dungeon'. Other slight changes.
 *
 * Revision 0.5  1998/08/14 11:27:44  alexios
 * Set monitor ID the moment we know we're riding a user and
 * not a daemon or userless process.
 *
 * Revision 0.4  1998/07/24 10:08:57  alexios
 * Added module information structure and a function to set it.
 * Added function to set only the progname field in the module
 * structure, for quick migration. All programs using the lib
 * are expected to register their names if they need to use the
 * error reporting facility.
 *
 * Revision 0.3  1997/11/06 20:03:54  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/11/03 00:34:41  alexios
 * Removed code for hardwired translation tables. Added code to
 * handle generalised tables. Changed all calls to xlwrite() to
 * write() since emud now handles all translations.
 *
 * Revision 0.1  1997/08/26 16:35:17  alexios
 * First registered revision. Adequate.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif



#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_UNISTD_H 1
#define WANT_STRINGS_H 1
#define WANT_CTYPE_H 1
#define WANT_SIGNAL_H 1
#define WANT_FCNTL_H 1
#define WANT_TERMIOS_H 1
#define WANT_SYS_IOCTL_H 1
#define WANT_SYS_STAT_H 1
#define WANT_SYS_IPC_H 1
#define WANT_SYS_SHM_H 1
#define WANT_PWD_H 1
#define WANT_SEND_OUT 1
#include <bbsinclude.h>

#include "bbs.h"
#include "mbk_sysvar.h"


struct sysvar *sysvar=NULL;
static promptblk *chatmsg;
static long initialised=0;
struct bbsmodule module;
int    bbs_uid, bbs_gid;


void donemodule();
void catchsig();
void syschat();


void
setmoduleinfo(struct bbsmodule *mod)
{
  memcpy(&module,mod,sizeof(module));
}


void
setprogname(char *s)
{
  char *cp=strrchr(s,'/');
  if(cp!=NULL)module.progname=strdup(cp+1);
  else module.progname=strdup(s);
}



void
initsignals()
{
  signal(SIGINT,SIG_IGN);
  signal(SIGQUIT,SIG_IGN);
  signal(SIGSTOP,SIG_IGN);
  signal(SIGTSTP,SIG_IGN);
  signal(SIGTERM,catchsig);
  signal(SIGKILL,catchsig);
  signal(SIGSEGV,catchsig);
  signal(SIGFPE,catchsig);
  signal(SIGHUP,catchsig);
  signal(SIGILL,catchsig);
}  


void
donesignals()
{
  signal(SIGINT,SIG_DFL);
  signal(SIGQUIT,SIG_DFL);
  signal(SIGSTOP,SIG_DFL);
  signal(SIGTSTP,SIG_DFL);
  signal(SIGTERM,SIG_DFL);
  signal(SIGKILL,SIG_DFL);
  signal(SIGSEGV,SIG_DFL);
  signal(SIGFPE,SIG_DFL);
  signal(SIGHUP,SIG_DFL);
  signal(SIGILL,SIG_DFL);
}  


void
loadsysvars()
{
  FILE *sysvarf;
  int shmid,load=0,i;
  char fname[256];

  /* Wait for any pending locks on the file */

  waitlock("LCK..sysvarshm",60);
  waitlock("LCK..sysvar",60);

  /* Is the sysvar file somewhere in shared memory? */

  if((sysvarf=fopen(SYSVARSHMFILE,"r"))!=NULL){
    char magic[5];
    fscanf(sysvarf,"%d",&shmid);

    /* Yup, attach it */

    sysvar=(struct sysvar *)shmat(shmid,NULL,0);
    if((int)sysvar<0)load=1;
    else {

      /* Check the magic number, just to be sure */

      memcpy(magic,sysvar->magic,sizeof(sysvar->magic));
      magic[4]=0;

      if(strcmp(magic,SVR_MAGIC)){
	/* Don't know what we just attached, but it shore ain't sysvar! */
	fatal("Incorrent magic number in sysvar, will not attach!");
      }
    }
  } else {

    /* The sysvar isn't in shared memory, so we'll have to read it on
       our own. This is really really bad, but we'll steel ourselves
       and get on with it anyway. */

    load=1;
  }
  fclose(sysvarf);

  /* You lucky, lucky bastard! */
  if(!load)return;

  /* Allocate memory */  
  sysvar=(struct sysvar *)alcmem(sizeof(struct sysvar));

  strcpy(fname,SYSVARFILE);
  for(i=0;i<6;i++){
    if((sysvarf=fopen(fname,"r"))!=NULL){
      char magic[5];

      /* Attempt to load it */
      if(fread(sysvar,sizeof(struct sysvar),1,sysvarf)!=1){
	/* Whoops, failed to read it it. Try the backups next. */
	goto try_backup;
      }
      fclose(sysvarf);

      /* Check magic number */
      memcpy(magic,sysvar->magic,sizeof(sysvar->magic));
      magic[4]=0;
      if(strcmp(magic,SVR_MAGIC)){
	/* Not enough magic. Try the backups. */
	goto try_backup;
      }

      /* Wheee, it works! */
      break;

    }
  try_backup:
    strcat(fname,i?"O":".O");
  }
}


void
savesysvars()
{
  FILE *sysvarf;
  char fname[256], magic[5];
  struct stat st;

  /* Don't save if sysvar is corrupted or non-existent */
  if(!sysvar)return;
  magic[4]=0;
  memcpy(magic,sysvar->magic,sizeof(sysvar->magic));
  if(strcmp(magic,SVR_MAGIC))return;

  /* Make a backup copy of the sysvar file and age it -- it tends to
     die at bad crashes and we need the backups */

  if(!stat(SYSVARFILE".OOOO",&st))rename(SYSVARFILE".OOOO",SYSVARFILE".OOOOO");
  if(!stat(SYSVARFILE".OOO",&st))rename(SYSVARFILE".OOO",SYSVARFILE".OOOO");
  if(!stat(SYSVARFILE".OO",&st))rename(SYSVARFILE".OO",SYSVARFILE".OOO");
  if(!stat(SYSVARFILE".O",&st))rename(SYSVARFILE".O",SYSVARFILE".OO");
  if(!stat(SYSVARFILE,&st))fcopy(SYSVARFILE,SYSVARFILE".O");
  
  /* Make sure the files have the right owners/permissions if we're root */
  if(!getuid()){
    chown(SYSVARFILE,bbs_uid,bbs_gid);
    chown(SYSVARFILE".O",bbs_uid,bbs_gid);
    chown(SYSVARFILE".OO",bbs_uid,bbs_gid);
    chown(SYSVARFILE".OOO",bbs_uid,bbs_gid);
    chown(SYSVARFILE".OOOO",bbs_uid,bbs_gid);
    chown(SYSVARFILE".OOOOO",bbs_uid,bbs_gid);
    chmod(SYSVARFILE,0660);
    chmod(SYSVARFILE".O",0660);
    chmod(SYSVARFILE".OO",0660);
    chmod(SYSVARFILE".OOO",0660);
    chmod(SYSVARFILE".OOOO",0660);
    chmod(SYSVARFILE".OOOOO",0660);
  }

  sprintf(fname,SYSVARFILE".%d",(int)getpid());
  if((sysvarf=fopen(fname,"w"))!=NULL){
    fwrite(sysvar,sizeof(struct sysvar),1,sysvarf);
  } else {
    /* Too late to gripe. Fail quietly and exit, hoping it's all right. */
    unlink(fname);
    return;
  }

  /* Phew, it worked. Close the file. */
  fclose(sysvarf);

  /* Make sure the file was written properly -- paranoia check */
  if((sysvarf=fopen(fname,"r"))!=NULL){
    char dummy[256];
    magic[4]=0;

    if(fread(sysvar,sizeof(struct sysvar),1,sysvarf)==1){
      memcpy(magic,sysvar->magic,sizeof(sysvar->magic));

      /* Magic or More Magic? */
      if(!strcmp(magic,SVR_MAGIC)){
	/* More Magic */
	
	/* Lock the file and put it in its rightful place. */
	waitlock("LCK..sysvar",10);
	if(checklock("LCK..sysvar",dummy)<=0){
	  placelock("LCK..sysvar","writing");
	  fcopy(fname,SYSVARFILE);
	  unlink(fname);
	  rmlock("LCK..sysvar");
	}
      }
    }
  }
  unlink(fname);
  
  /* Hey, I may be paranoid, but They *are* out to get me! */
  shmdt((char*)sysvar);
}


void
loadclasses()
{
  FILE *fp;
  struct stat s;

  if((fp=fopen(CLASSFILE,"r"))==NULL){
    fatalsys("Failed to open user class file %s.",CLASSFILE);
  }
  
  stat(CLASSFILE,&s);
  if(!s.st_size){
    fatal("User class file %s is emtpy.",CLASSFILE);
  }
  if(s.st_size%sizeof(classrec)){
    fatal("User class file %s has bad format.",CLASSFILE);
  }
 
  userclasses=realloc(userclasses,s.st_size);
  numuserclasses=s.st_size/sizeof(classrec);
  if(numuserclasses!=fread(userclasses,sizeof(classrec),MAXCLASS,fp)){
    fatalsys("Can't read user classes from %s.",CLASSFILE);
  }

  fclose(fp);
}


void
loadlanguages()
{
  FILE *langfp;

  numlangs=0;
  if((langfp=fopen(LANGUAGEFILE,"r"))!=NULL){
    while(!feof(langfp)){
      char line[1024];
      
      if(fgets(line,1024,langfp)){
	char *cp=line;
	char *nlp=strrchr(line,10);
	
	if(nlp)*nlp=0;
	while(*cp && isspace(*cp))cp++;
	if(*cp && *cp!='#')strcpy(languages[numlangs++],cp);
      }
    }
    fclose(langfp);
  }
}


void
loaduser()
{
  char userid[64]={0}, fname[256];
  FILE *fp;
  int shmid;
  strncpy(userid,getenv("USERID"),63);
  if(strlen(userid)<3){
    fatal("Variable $USERID incorrectly set.");
  }

  sprintf(fname,"%s/.shmid-%s",ONLINEDIR,userid);
  if((fp=fopen(fname,"r"))==NULL){
    fatalsys("Unable to open file %s",fname);
  }
  if(!fscanf(fp,"%d",&shmid)){
    fatalsys("Unable to read file %s",fname);
  }
  fclose(fp);

  if((thisshm=(struct shmuserrec *)shmat(shmid,NULL,0))==NULL){
    fatalsys("Unable to shmat() to %s.",fname);
  }

  thisuseronl.flags&=~(OLF_BUSY|OLF_NOTIMEOUT|OLF_INHIBITGO|OLF_INSYSCHAT);
  setlanguage(thisuseracc.language);
  setlinelen(thisuseracc.scnwidth);
  setscreenheight(thisuseracc.scnheight);
  setverticalformat((thisuseracc.prefs&UPF_NONSTOP)?0:1);
  setansiflag(thisuseronl.flags&OLF_ANSION);
  setwaittoclear((thisuseracc.prefs&UPF_NONSTOP)==0);
  /*  setxlationtable(getpxlation(thisuseracc));*/
}


void
saveuser()
{
  char userid[64]={0};
  
  strncpy(userid,getenv("USERID"),63);
  
  initialised&=~INITUSER;
  if(!strcmp(userid,thisuseracc.userid)){
    if(!saveuseraccount(&thisuseracc)){
      logerror("Unable to save account for %s",userid);
    }
  }else{
    logerror("User ID name mismatch \"%s\"!=\"%s\", "\
	     "won't save account.",userid,thisuseracc.userid);
  }
  
  if(!strcmp(userid,thisuseronl.userid)){
    if(!saveuseronlrec(&thisuseronl)){
      logerror("Unable to save online info for %s",userid);
    }
  }else{
    logerror("UserID mismatch \"%s\"!=\"%s\", "\
	     "won't save online info.",userid,thisuseronl.userid);
  }
}


void
getprevinput()
{
  if(thisuseronl.flags&OLF_MMCALLING && thisuseronl.input[0]){
    strcpy(input,thisuseronl.input);
    parsin();
    nxtcmd=NULL;
    bgncnc();
  }
}


void
initmodule(long f)
{
  struct passwd *pass;

  umask(0007);
  regpid(getenv("CHANNEL"));
  initialised|=f;
  if(f&INITSYSVARS)loadsysvars();
  if(f&INITOUTPUT)initoutput();
  if(f&INITUSER)loaduser();
  if(f&INITERRMSGS)yeserrormessages();
  else noerrormessages();
  if(f&INITINPUT){
    initinput();
    if(initialised&INITUSER && initialised&INITSYSVARS){
      setmonitorid(thisuseracc.userid);
      settimeout(sysvar->idlezap);
    }
  }

  if(f&INITSIGNALS)initsignals();
  if(f&INITCLASSES)loadclasses();
  if(f&INITLANGS)loadlanguages();
  if(f&INITGLOBCMD)initgcs();
  if(f&INITTTYNUM)initchannels();
  if(f&INITATEXIT)atexit(donemodule);
  if((f&INITUSER) && (f&INITINPUT))getprevinput();
  if(f&INITCHAT)signal(SIGCHAT,syschat);
  else signal(SIGCHAT,SIG_IGN);

  pass=getpwnam(BBSUSERNAME);
  if(pass==NULL){
    fatal("User "BBSUSERNAME" is not in /etc/passwd!");
  }
  bbs_uid=pass->pw_uid;
  bbs_gid=pass->pw_gid;
}


void
donemodule()
{
  if(initialised&INITINPUT)doneinput();
  if(initialised&INITOUTPUT)doneoutput();
  if(initialised&INITUSER)saveuser();
  if(initialised&INITSYSVARS)savesysvars();
  initialised=0;
}


void
catchsig()
{
  hangup();
  exit(1);
}


void
endchat()
{
  void sigchat();

  thisuseronl.flags&=~(OLF_BUSY|OLF_NOTIMEOUT|OLF_INSYSCHAT);
  setmbk(sysblk);
  prompt(CHATEND);
  setmbk(chatmsg);
  reprompt=1;
  signal(SIGCHAT,syschat);
}


void
syschat()
{
  thisuseronl.flags|=OLF_BUSY|OLF_NOTIMEOUT|OLF_INSYSCHAT;
  chatmsg=curblk;
  setmbk(sysblk);
  reprompt=0;
  prompt(CHATBEG);
  signal(SIGCHAT,endchat);

  while(!reprompt){
    char c;
    
    usleep(20000);
    if(read(fileno(stdin),&c,1)==1){
      if(c==8 || c==127){
	char del[3]="\010 \010";
	send_out(fileno(stdout),del,3);
      } else send_out(fileno(stdout),&c,1);
    }
  }

  {
    char fname[256],command[256];
    FILE *fp;
    
    sprintf(fname,"%s/.emu-%s",EMULOGDIR,getenv("CHANNEL"));
    if((fp=fopen(fname,"w"))==NULL)return;
    fcntl(fileno(fp),F_SETFL,fcntl(fileno(fp),F_GETFL)|O_NONBLOCK);
    fprintf(fp,"\n");
    fclose(fp);
    if(!getuid() || !getgid()){
      sprintf(command,"chown bbs.bbs %s >&/dev/null",fname);
      system(command);
    }
  }
}


void
regpid(char *tty)
{
  FILE *fp;
  char fname[256];
  char command[256];

  if(tty==NULL || !tty[0] || !strcmp(tty,"(null)"))return;
  sprintf(fname,"%s/register-%s",BBSETCDIR,tty);
  if((fp=fopen(fname,"w"))==NULL){
    fatalsys("Can't open %s for writing.",fname);
  }
  fprintf(fp,"%d",(int)getpid());
  fclose(fp);
  if(!getuid() || !getgid()){
    sprintf(command,"chown bbs.bbs %s >&/dev/null",fname);
    system(command);
  }
}
