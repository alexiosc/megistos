/*****************************************************************************\
 **                                                                         **
 **  FILE:     register_non_megistos.c                                      **
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
 * Revision 1.1  2001/04/16 15:00:50  alexios
 * Initial revision
 *
 * Revision 1.1  2000/01/08 12:17:03  alexios
 * Added an alarm() call to set a timeout, just in case.
 *
 * Revision 1.0  1999/07/18 22:05:10  alexios
 * Initial revision
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
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

#include "metaservices.h"
#include "metabbs.h"


char *
get_canonical_name(char *hostname)
{
  struct hostent  *host;


  if((host=gethostbyname(hostname))==NULL){
    perror("gethostbyname");
    exit(1);
  }

#ifdef DEBUG
  fprintf(stderr,"This guy's hostent:\n\n");
  fprintf(stderr,"hostname: %s\n",host->h_name);
  fprintf(stderr,"aliases:  ");
  {
    int i;
    for(i=0;host->h_aliases[i];i++)fprintf(stderr,"%s ",host->h_aliases[i]);
  }
  fprintf(stderr,"\n");
  fprintf(stderr,"length:   %d\n",host->h_length);
  fprintf(stderr,"addrs:    ");
  {
    int i;
    for(i=0;host->h_addr_list[i];i++)
      fprintf(stderr,"%s ",inet_ntoa(*((struct in_addr*)host->h_addr_list[i])));
  }
  fprintf(stderr,"\n\n");
#endif

  /* Be paranoid -- there are strange host tables and DNS out there
     and lusers have taken to sysadminning. */

  if(!strchr(host->h_name,'.')){

#ifdef DEBUG
    fprintf(stderr,"Hostname is not fully qualified. Using first IP address...\n");
#endif

    return inet_ntoa(*((struct in_addr*)host->h_addr_list[0]));
  }

  return host->h_name;
}



static int
validate_non_megistos(registration_package_t *reg)
{
  char tmp[1024];
  FILE *fp;
  int  invalid=0;
  struct stat st;

#ifdef DEBUG
  fprintf(stderr,"Registration request for non-BBS system %s (%s)\n",
	  reg->codename,reg->bbstitle);
#endif

  /* First some simple validations, not related to security */

  if(!strlen(reg->codename))return 0;
  if(!strlen(reg->hostname))return 0;
  if(!strlen(reg->prefix))return 0;
  if(reg->port<0||reg->port>65535)return 0;
  if(reg->bbsd_pid<2)return 0;


  /* Security check: existence of bbsd at specified PID. This makes sense even
     for non-BBS systems, because they can only be nominated by other, running
     BBS systems. The BBS daemon making the registration is expceted to
     identify itself. */

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
     components. For reason of existence, see above security check. */

  sprintf(tmp,"%s/etc/sysvar",reg->prefix);
  if(stat(tmp,&st))return 0;
  

  /* Ok, the registration is valid and the nominating BBS is local. */

  return 1;
}



/* Add timestamps etc and copy reg to the array of systems. Do non-BBS specific
   stuff, too. */

static void
add_system_non_megistos(int n, registration_package_t *reg)
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
  rs->hostname=strdup(get_canonical_name(rs->hostname));

  rs->users_online=-1;
  rs->lines_free=-1;
  rs->lines_max=-1;

  /* Stamp the registration time to allow expiry checks */

  rs->regtime=time(NULL);
  if(rs->flags)rs->flags=SFL_DONT_DISCONNECT;
  rs->flags|=SFL_NON_MEGISTOS;
}



int * metabbs_register_non_megistos_1_svc(registration_package_t *reg,
					  struct svc_req *client)
{
  static int retval=0;
  int i;


  /* Set a reasonable timeout */

  alarm(60);


  /* First of all, validate this package. */

  if(!validate_non_megistos(reg)){
    retval=-1;
    return &retval;
  }


  /* Now check if this is a new registration, or a heartbeat/update */

  if((i=find_system(reg->codename))<0) i=make_space();

#ifdef DEBUG
  fprintf(stderr,"Right, adding system.\n");
#endif

  add_system_non_megistos(i,reg);
  
  return &retval;
}
