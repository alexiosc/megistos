/*****************************************************************************\
 **                                                                         **
 **  FILE:     metabbs-server.c                                             **
 **  AUTHORS:  Alexios                                                      **
 **  PURPOSE:                                                               **
 **  NOTES:                                                                 **
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
 * Revision 1.1  2001/04/16 15:01:01  alexios
 * Initial revision
 *
 * Revision 1.0  2000/01/23 20:46:33  alexios
 * Initial revision
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif


#define WANT_SYS_STAT_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_WAIT_H 1
#define WANT_SYS_SOCKET_H 1
#define WANT_NETINET_IN_H 1
#define WANT_UNISTD_H 1
#define WANT_PWD_H 1
#define WANT_SYS_FCNTL_H 1
#define WANT_SYS_IOCTL_H 1
#include <bbsinclude.h>
#include "bbs.h"
#include "metabbs-server.h"


char               *rcs_ver=RCS_VER;
char               *secrets_file=NULL;
int                 port=METABBS_PORT;
char                host_name[256];
char               *progname;
int                 under_inetd=0;
int                 sock;
struct sockaddr_in  name;
struct sockaddr_in  peer;
int                 bbsuid,bbsgid;



void
syntax()
{
  printf("syntax: metabbs-server -s file [options]\n\n");
  printf("   -s secrets      Secrets file to read.\n\nOptions:\n\n");
  printf("   -p port         Port to listen to (not applicable if running under inetd).\n");
  exit(1);
}


void
get_args(int argc, char **argv)
{
  char c;

  while((c=getopt(argc,argv,"p:s:h?"))!=EOF){
    switch(c){
    case 'p':
      if(atoi(optarg)<=0 || atoi(optarg)>65535)syntax();
      port=atoi(optarg);
      break;
    case 's':
      secrets_file=strdup(optarg);
      break;
    case 'h':
    case '?':
    default:
      syntax();
    }
  }

  if(secrets_file==NULL)syntax();
}


static void
getpwbbs()
{
  struct passwd *pass=getpwnam(BBSUSERNAME);
  if(pass==NULL)fatal("User %s not found.",BBSUSERNAME);
  bbsuid=pass->pw_uid;
  bbsgid=pass->pw_gid;
}


static void
mksocket()
{
  int len,n;

  /* Create the socket */
  if((sock=socket(AF_INET,SOCK_STREAM,0))<0){
    fatalsys("Unable to create metabbs-server socket");
  }

  /* Create server address */
  bzero(&name,sizeof(struct sockaddr_in));
  name.sin_family=AF_INET;
  name.sin_port=htons(METABBS_PORT);
  len=sizeof(struct sockaddr_in);
  n=INADDR_ANY;
  memcpy(&name.sin_addr,&n,sizeof(long));

  /* Bind the socket */
  if(bind(sock,(struct sockaddr*)&name,len)<0){
    fatalsys("Failed to bind metabbs-server socket (%d/tcp)",METABBS_PORT);
  }
}


static void
storepid()
{
  FILE *fp=fopen(BBSETCDIR"/metabbs-server.pid","w");
  if(fp==NULL){
    fatalsys("Unable to open "BBSETCDIR"/metabbs-server.pid for writing.");
  }
  fprintf(fp,"%d",getpid());
  fclose(fp);
  chmod(BBSETCDIR"/metabbs-server.pid",0600);
  chown(BBSETCDIR"/metabbs-server.pid",0,0);
}


static void
handle_child_exit(int sig)
{
  int status;
  int pid;
  while((pid=waitpid(-1,&status,WNOHANG))>0){
    #ifdef DEBUG
    fprintf(stderr,"*** Caught child exit, child pid=%d, signaled=%d, signal=%d\n",pid,WIFSIGNALED(status),WTERMSIG(status));
    #endif
  }
  signal(SIGCHLD,handle_child_exit);
}


static void
mainloop()
{
  int ns=0, len, pid;

#ifdef DEBUG
  fprintf(stderr,"*** In main loop.\n");
#endif DEBUG
  

  /* If running under inetd, then the file descriptor is 0. Although it might
     look like stdin (fd 0) isn't really open for input AND output, this is
     misleading. Stdin and stdout are both open for input and output, since
     they're the same descriptor duplicated with dup2(). */

  if(under_inetd)handleconnection(0);
  else {
    signal(SIGCHLD,handle_child_exit);
    for(;;){
      if(listen(sock,5)<0){
	fatalsys("Unable to listen to socket (%d/tcp)",METABBS_PORT);
      }
      
      if((ns=accept(sock,(struct sockaddr*)&name,&len))<0){
	fatalsys("accept() failed for socket (%d/tcp)",METABBS_PORT);
      }


      /* If running under inetd, then it does all the forking. If we're our own
         daemon, we're responsible for spawning a new thread of execution to
         handle the incoming request and there's no need to handle more
         connections than one. */

      pid=fork();

      #ifdef DEBUG
      fprintf(stderr,"*** Forking new subprocess, pid=%d\n",pid);
      #endif
      
      /* Whoops */
      
      if(pid<0){
	interrorsys("Unable to fork() subprocess to deal with request.");
	close(ns);
	continue;
	
      } else if(pid==0) {	/* Child process here */
	handleconnection(ns);
	exit(0);
      }
      
      /* Parent process returns to the loop. */

      close(ns);		/* Don't need this any more. */
    }
  }
}


static void
checkuid()
{
  if (getuid()){
    fprintf(stderr, "%s: getuid: not super-user\n", progname);
    exit(1);
  }
}


static void
checkinetd()
{
  int len=sizeof(name), res;

  /* Try to get information on the other end. If we fail, then we'll
     run independently. */

  res=getpeername(0, &peer, &len);

  under_inetd=(res==0);
}


static void
forkdaemon()
{
  switch(fork()){
  case -1:
    fprintf(stderr,"%s: fork: unable to fork daemon\n",progname);
    exit(1);
  case 0:
    ioctl(0,TIOCNOTTY,NULL);
    close(0);
#ifndef DEBUG
    close(1);
    close(2);
#endif
    break;
  default:
    exit(0);
  }
}


static void
init()
{
  if(!under_inetd)forkdaemon();	/* Fork() the daemon */
  getpwbbs();			/* Get the /etc/passwd entry user 'bbs' */
  if(!under_inetd)mksocket();	/* Make BBSD's FIFO and set its permissions */
  storepid();			/* Store the daemon's PID */

  if(gethostname(host_name,sizeof(host_name))<0){
    fatalsys("Unable to get hostname.");
  }
}


int
main(int argc, char *argv[])
{
  progname=argv[0];
  setprogname(argv[0]);

  get_args(argc,argv);

  setenv("CHANNEL","[metabbs-server]",1);
  signal(SIGPIPE,SIG_IGN);

  checkuid();			/* Make sure the superuser is running us */
  checkinetd();			/* Are we running under inetd? */

  init();			/* Miscellaneous initialisations */
  mainloop();			/* Finally, run the daemon's main loop */
  
  return 0;
}
