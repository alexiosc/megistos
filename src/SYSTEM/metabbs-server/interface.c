/*****************************************************************************\
 **                                                                         **
 **  FILE:     requests.c                                                   **
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
 * Revision 1.0  2000/01/22 19:28:08  alexios
 * Initial revision
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif


#define __METABBSD__ 1
#define WANT_SYS_STAT_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_SOCKET_H 1
#define WANT_ARPA_TELNET_H 1
#define WANT_SYS_UN_H 1
#define WANT_VARARGS_H 1
#define WANT_FCNTL_H 1
#define WANT_PWD_H 1
#include <bbsinclude.h>
#include <bbs.h>
#include "metabbsd.h"


static int         metabbsd_socket;
static char        input_line[256];
static const char  input_del[4]="\010 \010";


void
reply_printf(fd, code, fmt, va_alist)
int                 fd;
unsigned short int  code;
char               *fmt;
va_dcl
{
  va_list args;
  char    res[8];
  char    buf[2048];
  
  sprintf(res,"%03d ",(code&0x1ff)%999);
  
  va_start(args);
  vsprintf(buf,fmt,args);
  va_end(args);
  
  if(under_inetd){
    write(fd,res,strlen(res));
    write(fd,buf,strlen(buf));
    res[0]='\n';
    res[1]='\r';
    write(fd,res,2);
  } else {
    if(send(fd,res,strlen(res),0)<0){
      interrorsys("Unable to write result code %03d to socket.",code);
    }
    
    if(send(fd,buf,strlen(buf),0)<0){
      interrorsys("Unable to write result string to socket.");
    }
    res[0]='\n';
    res[1]='\r';
    if(send(fd,res,2,0)<0){
      interrorsys("Unable to write result string to socket.");
    }
  }
}


static int
get_char()
{
  unsigned char c;
  if(under_inetd) read(0,&c,1);
  else if(recv(metabbsd_socket,&c,1,0)<0){
    interrorsys("Unable to read from socket.");
    return EOF;
  }
  return c;
}



void
read_string()
{
  int cp=0;
  bzero(input_line,sizeof(input_line));
  input_line[cp]=0;

  for(;;){
    unsigned char c;
    c=get_char();

    c&=0xff;
    switch(c){

    case IAC:			/* Catch and ignore Telnet escape codes */
      {
	char reply[3];
	c=get_char();
	if(c!=(unsigned)EOF){
	  c&=0xff;
	  switch(c){
	  case WILL:
	  case WONT:
	    c=get_char();
	    reply[0]=IAC;
	    reply[1]=DONT;
	    reply[2]=c&0xff;

	    #if 0
	    if(under_inetd) write(0,reply,3);
	    else {
	      if(!send(metabbsd_socket,reply,3,0)<0){
		interrorsys("Unable to write to socket.");
	      }
	    }
	    #endif
	    break;
	  case DO:
	  case DONT:
	    c=get_char();
	    reply[0]=IAC;
	    reply[1]=WONT;
	    reply[2]=c&0xff;
	    
	    #if 0
	    if(under_inetd) write(0,reply,3);
	    else {
	      if(!send(metabbsd_socket,reply,3,0)<0){
		interrorsys("Unable to write to socket.");
	      }
	    }
	    #endif
	  }
	}
      }
      break;
      
    case 10:
    case 13:
      #ifdef DEBUG
      fprintf(stderr,"*** END OF LINE\n");
      #endif
      return;

    default:
      #ifdef DEBUG
      fprintf(stderr,"*** CHARACTED %d RECEIVED, INPUT_LINE=(%s)\n",c,input_line);
      #endif
      if(cp+1<sizeof(input_line)){
	input_line[cp++]=c;
	input_line[cp]=0;
      }
    }
  }
}


void
handleconnection (int fd)
{
  metabbsd_socket=fd;

#ifdef DEBUG
  fprintf(stderr,"*** Handling connection.\n");
#endif


  reply_printf(fd,RET_INF_HELLO,"%s metabbsd (%s)",host_name,rcs_ver);
  reply_printf(fd,RET_ASK_LOGIN,"Please identify yourself (BBS specification required).");

  read_string();
  reply_printf(fd,RET_INF_LOGGEDIN,"The string was (%s), len=%d.",input_line,strlen(input_line));

  reply_printf(fd,RET_ASK_PASSWORD,"Please authenticate yourself (enter password, will not echo).");
  read_string();

  reply_printf(fd,RET_ERR_LOGIN,"Login incorrect.");
  /*reply_printf(fd,RET_INF_LOGGEDIN,"Welcome, %s. What can we do for you?","hostname/BBS");*/
  reply_printf(fd,RET_INF_GOODBYE,"Goodbye.\n");


#ifdef DEBUG
  fprintf(stderr,"*** Leaving handleconnection().\n");
#endif
}
