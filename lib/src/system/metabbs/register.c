/*****************************************************************************\
 **                                                                         **
 **  FILE:     register.c                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  PURPOSE:  Meta-daemon for networking/distributing BBSs over networks.  **
 **  NOTES:    Purposes:                                                    **
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
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.2  2000/01/08 12:17:03  alexios
 * Added an alarm() call to set a timeout, just in case.
 *
 * Revision 1.1  1999/07/28 23:16:48  alexios
 * One very slight addition.
 *
 * Revision 1.0  1999/07/18 22:05:10  alexios
 * Initial revision
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
const char *__RCS=RCS_VER;
#endif


#include <stdio.h>
#include <ctype.h>
#include <sys/stat.h>
#include <rpc/rpc.h>
#include <sys/utsname.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <metaservices.h>


/* We don't expect *that* many BBSs on the same system, so we'll be
   doing dynamic allocation but naive sequential searches. */

struct registration_package_t * registered_systems = NULL;
struct registration_package_t * this_system = NULL;

int num_systems=0;


/* This is a sequential search. It's disgrace against Knuth, but with
   two or three systems on the same machine, it's more convenient,
   less memory-hungry *and* faster than a bsearch() */

int find_system(char *codename)
{
  int i;
  for(i=0;codename[i];i++)codename[i]=tolower(codename[i]);
  for(i=0;i<num_systems;i++){
    if(!strcmp(codename,registered_systems[i].codename))return i;
  }
  return -1;			/* Not found */
}



/* Get our own hostname to store as the hostname of all local BBSs. We
   obviously don't trust anything they throw at us in the hostname
   field of the registration package. */

char *
my_hostname()
{
  static char     *hostname=NULL;
  struct hostent  *me;
  struct utsname   uts;
  int              res=uname(&uts);


  /* Hey, we were called before. Return the cached hostname. */
  if(hostname!=NULL)return hostname;


  /* First time round. Do stuff. */

  if(res){
    perror("uname");
    exit(1);
  }

#ifdef DEBUG
  fprintf(stderr,"our hostname: \"%s\"\n",uts.nodename);
#endif
  
  if((me=gethostbyname(uts.nodename))==NULL){
    perror("gethostbyname");
    exit(1);
  }

#ifdef DEBUG
  fprintf(stderr,"Our own hostent:\n\n");
  fprintf(stderr,"hostname: %s\n",me->h_name);
  fprintf(stderr,"aliases:  ");
  {
    int i;
    for(i=0;me->h_aliases[i];i++)fprintf(stderr,"%s ",me->h_aliases[i]);
  }
  fprintf(stderr,"\n");
  fprintf(stderr,"length:   %d\n",me->h_length);
  fprintf(stderr,"addrs:    ");
  {
    int i;
    for(i=0;me->h_addr_list[i];i++)
      fprintf(stderr,"%s ",inet_ntoa(*((struct in_addr*)me->h_addr_list[i])));
  }
  fprintf(stderr,"\n\n");
#endif

  /* Be paranoid -- there are strange host tables and DNS out there
     and lusers have taken to syadmining. */

  if(!strchr(me->h_name,'.')){

#ifdef DEBUG
    fprintf(stderr,"Hostname is not fully qualified. Using first IP address...\n");
#endif

    /* Eeeeeyarghl! */

    hostname=strdup(inet_ntoa(*((struct in_addr*)me->h_addr_list[0])));
    return hostname;
  }

  return hostname=strdup(me->h_name);
}





/* Add timestamps etc and copy reg to the array of systems */ 

static void
add_system(int n, registration_package_t *reg)
{
  int i;
  struct registration_package_t *rs=&registered_systems[n];
  memcpy(rs,reg,sizeof(registration_package_t));

  /* convert BBS codename to lower case: this is our primary key */

  for(i=0;rs->codename[i];i++)rs->codename[i]=tolower(rs->codename[i]);

  /* These look silly, but we need to copy the temporary strings */

  if(rs->url!=NULL)rs->url=strdup(rs->url);
  if(rs->email!=NULL)rs->email=strdup(rs->email);
  if(rs->access_allow!=NULL)rs->access_allow=strdup(rs->access_allow);
  if(rs->access_deny!=NULL)rs->access_deny=strdup(rs->access_deny);
  if(rs->bbs_ad!=NULL)rs->bbs_ad=strdup(rs->bbs_ad);
  if(rs->prefix!=NULL)rs->prefix=strdup(rs->prefix);
  rs->hostname=strdup(my_hostname());

  /* Stamp the registration time to allow expiry checks */

  rs->regtime=time(NULL);
  rs->flags=0;
}



static int
validate(registration_package_t *reg)
{
  char tmp[1024];
  FILE *fp;
  int  invalid=0;
  struct stat st;

#ifdef DEBUG
  fprintf(stderr,"Registration request for BBS %s (%s)\n",
	  reg->codename,reg->bbstitle);
#endif

  /* First some simple validations, not related to security */

  if(!strlen(reg->codename))return 0;
  if(!strlen(reg->bbstitle))return 0;
  if(reg->users_online<0)return 0;
  if(reg->lines_free<0)return 0;
  if(reg->lines_max<0)return 0;
  if(reg->port<0||reg->port>65535)return 0;
  if(!strlen(reg->prefix))return 0;
  if(reg->bbsd_pid<2)return 0;

  /* First security check: existence of bbsd at specified PID */

  sprintf(tmp,"/proc/%d/status",reg->bbsd_pid);
  if((fp=fopen(tmp,"r"))==NULL)return 0;

  while(!feof(fp)){
    char line[256],key[256],val[256];
    if(!fgets(line,sizeof(line),fp))break;
    if(!sscanf(line,"%s %s",key,val)!=2)continue;

    if(!strcmp(key,"Name:"))invalid|=strcmp(val,"bbsd");
    else if(!strcmp(key,"Uid:"))invalid|=strcmp(val,"0");
    else if(!strcmp(key,"Gid:"))invalid|=strcmp(val,"0");
  }
  fclose(fp);
  if(invalid)return 0;


  /* Second security check: existence of prefix directory and key
     components */

  sprintf(tmp,"%s/etc/sysvar",reg->prefix);
  if(stat(tmp,&st))return 0;


  /* Third security check: We obviously don't want to be tricked into
     using root to do our dirty networking stuff. The BBS UID/GID
     should belong to a user, not root. */

  if((reg->bbs_uid==0) || (reg->bbs_gid==0))return 0;
  

  /* Ok, the registration is valid and the BBS is local. */

  return 1;
}



/* Make some space in the dynamic array of registrations. The caller is
   expected to have established that the registration package isn't already in
   the array. make_space() returns the index (0-based, of course) of the new
   package. */

int make_space()
{
  int i;

  if(!num_systems){
    
    /* New registration */
    
#ifdef DEBUG
    fprintf(stderr,"This is our first registration for this session.\n");
#endif
    
    num_systems=1;
    registered_systems=(struct registration_package_t*)
      malloc(sizeof(struct registration_package_t));
    i=0;
  } else {
    struct registration_package_t* tmp;
    
#ifdef DEBUG
    fprintf(stderr,"New (but not first) registration, making space.\n");
#endif
    
    /* Make some space */
    
    num_systems++;
    
    tmp=(struct registration_package_t*)
      malloc(num_systems*sizeof(struct registration_package_t));
    
    memcpy(tmp,
	   registered_systems,
	   sizeof(struct registration_package_t)*(num_systems-1));
    
    free(registered_systems);
    registered_systems=tmp;
    
    i=num_systems-1;
  }

  return i;
}



int * metabbs_register_1_svc(registration_package_t *reg,
			     struct svc_req *client)
{
  static int retval=0;
  int i;


  /* Set a reasonable timeout */

  alarm(60);



  /* First of all, validate this package. */

  if(!validate(reg)){
    retval=-1;
    return &retval;
  }


  /* Now check if this is a new registration, or a BBS heartbeat */

  if((i=find_system(reg->codename))<0) i=make_space();

#ifdef DEBUG
  fprintf(stderr,"Right, adding system.\n");
#endif

  add_system(i,reg);
  
  return &retval;
}
