/*****************************************************************************\
 **                                                                         **
 **  FILE:     shm.c                                                        **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 1997                                               **
 **  PURPOSE:  Shared memory management for users and sysstructs            **
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
 * Revision 1.1  2001/04/16 15:00:36  alexios
 * Initial revision
 *
 * Revision 0.6  1999/07/18 22:00:00  alexios
 * Changed a few fatal() calls to fatalsys(). Numerous minor
 * fixes.
 *
 * Revision 0.5  1998/12/27 16:21:05  alexios
 * Added autoconf support. Added support for new getlinestatus().
 * New code to try to load backup copies of the SYSVAR file if
 * the normal one is corrupted.
 *
 * Revision 0.4  1998/07/26 21:11:32  alexios
 * No changes.
 *
 * Revision 0.3  1998/07/24 10:25:55  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.2  1997/11/06 20:04:14  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.1  1997/08/30 13:10:43  alexios
 * Initial revision. Adequate.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif


#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_UNISTD_H 1
#define WANT_STRING_H 1
#define WANT_SIGNAL_H 1
#define WANT_PWD_H 1
#define WANT_SYS_IPC_H 1
#define WANT_SYS_SHM_H 1
#define WANT_SYS_STAT_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_IOCTL_H 1
#define WANT_FCNTL_H 1
#define WANT_TERMIO_H 1
#define WANT_DIRENT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "mbk_sysvar.h"
#include "bbsd.h"



static unsigned char proj='M';


void
cleanuponline()
{
  /* Not particulary pretty, quick or secure */
  char command[256];
  sprintf(command,"\\rm -rf "ONLINEDIR);
  system(command);
  mkdir(ONLINEDIR,0770);
  chown(ONLINEDIR,bbsuid,bbsgid);
  chmod(ONLINEDIR,0770);	/* Make sure permissions are set correctly */
}


int
makeshm(char *userid)
{
  char fname[256];
  int shmid=0, fd;
  struct stat st;
  struct shmid_ds buf;
  struct passwd *pass;
    

  /* Produce a unique IPC key for the shared memory segment */

  proj=(proj+1)%0xff;
  sprintf(fname,"%s/%s",ONLINEDIR,userid);
  if(stat(fname,&st)){
    logerrorsys("Online user record %s not found.",fname);
    return -1;
  }


  /* Get the shared memory segment and set its owner to bbs.bbs */

  if((shmid=shmget(ftok(fname,proj),
		   4096,
		   IPC_CREAT|0660))==-1){
    logerrorsys("Unable to allocate 4k of shared memory");
  }

  lowerc(strcpy(fname,userid));
  pass=getpwnam(fname);

  if(shmctl(shmid,IPC_STAT,&buf)<0){
    logerrorsys("Unable to IPC_STAT shared memory");
  } else {
    if(pass!=NULL){
      buf.shm_perm.uid=pass->pw_uid;
      buf.shm_perm.gid=pass->pw_gid;
    } else {
      buf.shm_perm.uid=bbsuid;
      buf.shm_perm.gid=bbsgid;
    }

    if(shmctl(shmid,IPC_SET,&buf)<0){
      logerrorsys("Unable to IPC_SET shared memory");
    }
  }


  /* Write the shared memory ID to disk */

  sprintf(fname,"%s/.shmid-%s",ONLINEDIR,userid);
  chmod(fname,660);
  unlink(fname);
  if((fd=open(fname,O_WRONLY|O_CREAT|O_TRUNC))<0){
    logerrorsys("makeshm(): Unable to write shmid to %s",fname);
    killshm(userid,shmid);
    asapevents();
    return -1;
  }
  {
    char buf[256];
    sprintf(buf,"%012d",shmid);
    write(fd,buf,sizeof(buf));
  }
  close(fd);
  if(pass!=NULL)chown(fname,pass->pw_uid,pass->pw_gid);
  else chown(fname,bbsuid,bbsgid);
  chmod(fname,0444);

  numusers++;
  return shmid;
}



void
killshm(char *userid,int shmid)
{
  char fname[256];  
  struct shmid_ds buf;
  int i;

  if((thisshm=(struct shmuserrec *)shmat(shmid,NULL,0))==NULL)return;

  logoutuser();

  shmdt((char *)thisshm);
#ifdef DEBUG
  fprintf(stderr,"killing shmid %d\n",shmid);
#endif
  i=shmctl(shmid,IPC_RMID,&buf);

  if(i){
    logerror("Unable to destroy shared memory segment %d.",shmid);
  }

  /* Remove any remaining /usr/local/bbs/online files for this user */

  sprintf(fname,"%s/.shmid-%s",ONLINEDIR,userid);
  unlink(fname);
  sprintf(fname,"%s/_%s",ONLINEDIR,userid);
  unlink(fname);
  sprintf(fname,"%s/%s",ONLINEDIR,userid);
  unlink(fname);
  sprintf(fname,"%s/_[NO-USER]",ONLINEDIR);
  unlink(fname);
  numusers--;
}


void
monitorshm()
{
  struct shmid_ds buf;
  int    shmid;
  FILE   *fp;

  shmid=shmget(IPC_PRIVATE,sizeof(struct monitor),IPC_CREAT|0660);
  if(shmid<0){
    fatalsys("Unable to allocate shared memory for the monitor");
  }

  if(shmctl(shmid,IPC_STAT,&buf)<0){
    logerrorsys("Unable to IPC_STAT monitor memory");
  } else {

    buf.shm_perm.uid=bbsuid;
    buf.shm_perm.gid=bbsgid;

    if(shmctl(shmid,IPC_SET,&buf)<0){
      logerrorsys("Unable to IPC_SET monitor memory");
    }
  }

  if((fp=fopen(MONITORFILE,"w"))!=NULL){
    fprintf(fp,"%012d",shmid);
    fclose(fp);
  } else {
    int i=errno;
    shmctl(shmid,IPC_RMID,&buf);
    errno=i;
    fatalsys("Unable to create %s",MONITORFILE);
  }

  chown(MONITORFILE,bbsuid,bbsgid);
  chmod(MONITORFILE,0440);

  /* Attach the segment so it will be destroyed upon exiting from
     bbsd. */

  if(shmat(shmid,NULL,0)==(char*)-1){
    fatalsys("Unable to attach monitor memory segment %d, errno=%d\n",
	  shmid,errno);
  }
  shmctl(shmid,IPC_RMID,&buf);
}


void
sysvarshm()
{
  struct stat st;
  struct shmid_ds buf;
  int    shmid;
  FILE   *fp;
  int    tries;
  char   fname[256];

  /* Get a unique shared memory ID for the sysvar block */

  strcpy(fname,SYSVARFILE);
  for(tries=0;tries<6;tries++){
    if(!stat(fname,&st)){
      tries=0;
      break;
    }
    strcat(fname,tries?"O":".O");
  }
  if(tries){
    fatal("Yikes! No sysvar file (not even a backup)!");
  }

  for(tries=0;tries<256;tries++){
    proj=(proj+1)%0xff;
    errno=0;
    if((shmid=shmget(ftok(fname,proj),
		     8192,
		     IPC_CREAT|0660))==-1)continue;
    else {
      tries=0;
      break;
    }
  }


  /* Did it work? */

  if(tries){
    fatal("Failed to shmget() space for the sysvars (errno=%d).",errno);
  }

  
  /* bbsd is the mother of all bbs processes. When bbsd dies, nobody
     else is ever going to want the sysvar block, so we mark it for
     destruction immediately. It will be destroyed when bbsd exits. */

  if(shmctl(shmid,IPC_STAT,&buf)<0){
    logerrorsys("Unable to IPC_STAT sysvar memory");
  } else {

    buf.shm_perm.uid=bbsuid;
    buf.shm_perm.gid=bbsgid;

    if(shmctl(shmid,IPC_SET,&buf)<0){
      logerrorsys("Unable to IPC_SET sysvar memory");
    }
  }


  /* Now that we have the segment, attach it. */
  
  if((sysvar=(struct sysvar *)shmat(shmid,NULL,0))<0){
    fatalsys("Unable to attach sysvar block!");
  }

  /* Try to load the sysvar file. This is quite sensitive, especially
     if the zeroth backup is missing. */

  strcpy(fname,SYSVARFILE);
  for(tries=0;tries<6;tries++){
#ifdef DEBUG
    fprintf(stderr,"Attempting to load %s\n",fname);
#endif DEBUG
    if((fp=fopen(fname,"r"))!=NULL){
      char magic[5];

      /* Attempt to load it */
      if(fread(sysvar,sizeof(struct sysvar),1,fp)!=1){

	/* Whoops, failed to read it it. Try the backups next. */
	goto try_backup;
      }
      fclose(fp);


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
    strcat(fname,tries?"O":".O");
  }


  /* If we had to load a backup, make sure we copy it back to the
     original file. */

  if(strcmp(SYSVARFILE,fname)){
    char dummy[256];
    waitlock("LCK..sysvar",10);
    if(checklock("LCK..sysvar",dummy)<=0){
      placelock("LCK..sysvar","writing");
      fcopy(fname,SYSVARFILE);
      rmlock("LCK..sysvar");
    }
  }


  /* Uhm, this isn't ever going to happen, right? */

  waitlock("LCK..sysvarshm",60);
  placelock("LCK..sysvarshm","creating");


  /* Now write the SHM ID for the sysvar block */
  
  if((fp=fopen(SYSVARSHMFILE,"w"))==NULL){
    fatalsys("Unable to write sysvar shmid to %s",SYSVARSHMFILE);
    shmctl(shmid,IPC_RMID,&buf);
    return;
  }
  fprintf(fp,"%012d",shmid);
  fclose(fp);
  chown(SYSVARSHMFILE,bbsuid,bbsgid);
  chmod(SYSVARSHMFILE,0440);
  rmlock("LCK..sysvarshm");

  /*  initmodule(INITSYSVARS);*/
  shmctl(shmid,IPC_RMID,&buf);

  refreshsysvars();
}
