/*****************************************************************************\
 **                                                                         **
 **  FILE:     channels.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  PURPOSE:  Code dealing with BBS channels (the current one, mostly)     **
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
\*****************************************************************************/


/*
 * $Id$
 *
 * $Log$
 * Revision 1.1  2001/04/16 14:49:33  alexios
 * Initial revision
 *
 * Revision 1.1  1999/07/18 21:01:53  alexios
 * Minor paranoia modifications to setlinestatus() (unlink line
 * status file before re-creating it).
 *
 * Revision 1.0  1998/12/27 14:31:03  alexios
 * Initial revision
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif


#define WANT_TERMIO_H 1
#define WANT_IOCTL_H 1
#define WANT_DIRENT_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_STAT_H 1
#define WANT_UNISTD_H 1
#define WANT_FCNTL_H 1
#include <bbsinclude.h>

#define CHANNELS_C
#include "config.h"
#include "channels.h"
#include "miscfx.h"
#include "errors.h"
#include "bbsmod.h"


/* The default linestatus */

static struct linestatus default_linestatus = {
  LST_NORMAL,			/* Reset the line to the NORMAL state */
  LSR_OK,			/* Pretend there's no error */
  0,				/* Set the bps rate to zero */
  "[NO-USER]",			/* There's no user in the channel */
};


int
getlinestatus(char *tty, struct linestatus *status)
{
  char fname[256], line[256], majst[64], minst[64], user[64];
  int i, n, baud;
  
  /* Open the status file. If it doesn't exist, return sane defaults */

  sprintf(fname,"%s/.status-%s",CHANDEFDIR,tty);
  if((i=open(fname,O_RDONLY))<0){
    memcpy(status,&default_linestatus,sizeof(struct linestatus));
    return -1;
  }

  /* Read the status line from the file */

  bzero(line,sizeof(line));
  read(i,line,sizeof(line)-1);
  close(i);

  /* Set the defaults */

  majst[0]=0;
  minst[0]=0;
  baud=0;
  user[0]=0;
  memcpy(status,&default_linestatus,sizeof(struct linestatus));

  /* Now parse the line */

  i=sscanf(line,"%s %s %d %s",majst,minst,&baud,user);

  /* Parse the state */

  switch(i){
  case 4:
    strcpy(status->user,user);
  case 3:
    status->baud=baud;
  case 2:
    for(n=0;n<LSR_NUMRESULTS;n++){
      if(sameas(line_results[n],minst)){
	status->result=n;
	break;
      }
    }
  case 1:
    for(n=0;n<LST_NUMSTATES;n++){
      if(sameas(line_states[n],majst)){
	status->state=n;
	break;
      }
    }
  }

  return 1;
}


int
setlinestatus(char *tty, struct linestatus *status)
{
  char fname[256], line[256];
  int i;
  
  /* Create the status file. */

  sprintf(fname,"%s/.status-%s",CHANDEFDIR,tty);
  unlink(fname);		/* Just in case */
  if((i=creat(fname,0666))<0){
    fatalsys("Unable to creat(\"%s\",0666).",fname);
  }

  /* Construct and write the status line */

  if(status->state>=LST_NUMSTATES || status->state<0) status->state=LST_NORMAL;
  if(status->result>=LSR_NUMRESULTS || status->result<0) status->result=LSR_OK;
  sprintf(line,"%s %s %d %s\n",
	  line_states[status->state],
	  line_results[status->result],
	  status->baud,
	  status->user[0]?status->user:"[NO-USER]");
  write(i,line,strlen(line));
  close(i);
  chown(fname,bbs_uid,bbs_gid);
  chmod(fname,0660);
  return 1;
}


void
setlinestate(char *tty, int state)
{
  struct linestatus status;

  getlinestatus(tty,&status);
  if(state>=LST_NUMSTATES || state<0) state=LST_NORMAL;
  status.state=state;
  setlinestatus(tty,&status);
}


void
setlineresult(char *tty, int result)
{
  struct linestatus status;

  getlinestatus(tty,&status);
  if(result>=LSR_NUMRESULTS || result<0) result=LSR_OK;
  status.result=result;
  setlinestatus(tty,&status);
}


void
hangup()
{
  struct termios termio;

  (void) ioctl(0, TCGETS, &termio);
  termio.c_cflag &= ~CBAUD;
  termio.c_cflag |= B0;
  (void) ioctl(0, TCSETSF, &termio);
}


int
disconnect(char *ttyname)
{
  DIR *dp;
  struct dirent *buf;
  struct stat st;
  char fname[600];

  sprintf(fname,DEVDIR"/%s",ttyname);
  if(stat(fname,&st)) return -1;

  if((dp=opendir(PROCDIR))==NULL)exit(1);
  while((buf=readdir(dp))!=NULL){
    struct stat s;
    char fname[64];

    sprintf(fname,"%s/%s",PROCDIR,buf->d_name);
    if(stat(fname,&s)) continue;

    {
      char *cp=(char *)&buf->d_name;
      int j=strlen(cp);
      int myid=getpid();

      while(*cp && isdigit(*cp++))j--;
      if(!j && atoi(buf->d_name)!=myid){
	FILE *fp;
	int  d,tty;
	char s[1024], c;

	sprintf(fname,"%s/%s/stat",PROCDIR,buf->d_name);
	if((fp=fopen(fname,"r"))==NULL)continue;
	if(fscanf(fp,"%d %s %c %d %d %d %d",&d,s,&c,&d,&d,&d,&tty)!=7)
	  continue;
	if((tty&0xff)==(st.st_rdev&0xff)){
/*	  printf("Killing job %5s %s TTY= 0x04,0x%02x.\n",buf->d_name,s,tty&0xff); */
	  kill(atoi(buf->d_name),SIGHUP);
	}
      }
    }
  }
  closedir(dp);
  return 0;
}


char *
baudstg(int baud)
{
  static char string[10];

  switch(baud){
  case 0:
    strcpy(string,"[NET]");
    break;
  default:
    sprintf(string,"%d",baud);
  }
  return string;
}
