/*****************************************************************************\
 **                                                                         **
 **  FILE:     chat.c                                                       **
 **  AUTHORS:  Alexios (based on uugetty 2.1)                               **
 **  PURPOSE:  Execute chat-like scripts to initialise modems etc           **
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
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.1  1999/07/18 21:54:26  alexios
 * One slight cosmetic change.
 *
 * Revision 1.0  1998/12/13 23:18:28  alexios
 * Initial revision
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
const char *__RCS=RCS_VER;
#endif



#define WANT_SETJMP_H 1
#define WANT_IOCTL_H 1
#define WANT_STRING_H 1
#define WANT_SIGNAL_H 1
#define WANT_UNISTD_H 1
#include <bbsinclude.h>
#include <bbs.h>
#include "bbsgetty.h"


#define EXPECT 0
#define SEND   1
#define AUTOBD 0xff


/* unquote() - decode char(s) after a '\' is found. Returns the pointer s;
   decoded char in *c. */

static char valid_oct[]="01234567";
static char valid_dec[]="0123456789";
static char valid_hex[]="0123456789aAbBcCdDeEfF";

static char *
unquote(char *s, char *c)
{
  int value, base;
  char n, *valid;
  
  n=*s++;
  switch(n){
  case 'b':			/* Backspace \b */
    *c='\b';
    break;
  case 'c':
    if((n=*s++)=='\n')*c='\0';	/* Literal \c */
    else *c=n;
    break;
  case 'f':
    *c='\f';			/* Form Feed \f */
    break;
  case 'n':
    *c='\n';			/* New Line \n */
    break;
  case 'r':
    *c='\r';			/* Carriage Return \r */
    break;
  case 's':
    *c=' ';			/* Non-delimiting Space \s */
    break;
  case 't':
    *c='\t';			/* Tab \t */
    break;
  case '\n':
    *c='\0';			/* ignore NL which follows a '\' */
    break;
  case '\\':
    *c='\\';			/* Backslash \\ */
    break;

  default:			/* Handle \xxx numbered ASCII */
    if(isdigit(n)){
      value=0;
      if(n=='0'){
	if(*s=='x'){
	  valid=valid_hex;
	  base=16;
	  s++;
	}else{
	  valid=valid_oct;
	  base=8;
	}
      }else{
	valid=valid_dec;
	base=10;
	s--;
      }
      while(strpbrk(s,valid)==s){
	value=(value*base)+(int)(*s-'0');
	s++;
      }
      *c=(value&0xff);
    } else *c=n;
    break;
  }
  return s;
}



static char hex[]="0123456789abcdef";

static char *
quote(char *s)
{
  static char res[8192];
  register char *cp=res;

  bzero(res,sizeof(res));
  for(;*s;s++){
    if(*((unsigned char *)s)==(unsigned char)AUTOBD){
      *(cp++)='[';
      *(cp++)='B';
      *(cp++)='A';
      *(cp++)='U';
      *(cp++)='D';
      *(cp++)=']';
      break;
    } else if(!isprint(*s)){
      if(*s<0||*s>32){
	*(cp++)='\\';
	*(cp++)='0';
	*(cp++)='x';
	*(cp++)=hex[*s/16];
	*(cp++)=hex[*s%16];
      } else {
	*(cp++)='^';
	*(cp++)=(*s+'@');
      }
    } else if(*s=='\\'){
      *(cp++)='\\';
    } else *(cp++)=*s;
  }

  return res;
}



/* send() - send a string to stdout */

static int
send(char *s)
{
  register int retval=0;
  char ch;

  if(strcmp(s,"\"\"")==0){	/* ("") used as a place holder (do-nothing) */
    debug(D_CHAT,"SENDING: [nothing]");
    return retval;
  }

  debug(D_CHAT,"SENDING: %s",quote(s));
  while((ch=*s++)){
    if(ch=='\\'){
      switch(*s){
      case 'p':			/* '\p' == pause */
	debug(D_CHAT,"\\p specified, pausing for 1s.");
	sleep(1);
	s++;
	continue;
      case 'd':			/* '\d' == delay */
	debug(D_CHAT,"\\d specified, pausing for 2s.");
	sleep(2);
	s++;
	continue;
      case 'K':			/* '\K' == BREAK */
	debug(D_CHAT,"\\K specified, sending BREAK.");
	ioctl(1,TCSBRK,0);	/* Send the BREAK signal */
	s++;
	continue;
      default:
	s=unquote(s,&ch);	/* Process and print */
	break;
      }
    }
    if(putc(ch,stdout)==EOF){
      retval=-1;
      break;
    }
  }
  debug(D_CHAT, "SEND: %s.",(retval==0)?"OK":"failed");
  return retval;
}



/* expalarm() - called when expect()'s SIGALRM goes off */

jmp_buf env;

void
expalarm()
{
  longjmp(env,1);
}



/* expmatch() - compares expected string with the one gotten */

static char valid[]="0123456789";

static int
expmatch(char *got, char *exp)
{
  register int ptr=0;

  while(*exp){
    /* If we see the AUTOBD token, then we store any digits into autorate */

    if(*((unsigned char*)exp)==AUTOBD) {
      while(*got&&strpbrk(got,valid)==got){
	autobaud=1;
	if(ptr<(sizeof(autorate)-2))autorate[ptr++]=*got;
	got++;
      }
      if(*got=='\0')return 0;	/* didn't get it all yet */
      autorate[ptr]='\0';
      exp++;
      continue;
    }

    /* Otherwise, just compare characters */
    if (*got++!=*exp++)return 0;
  }

  return 1;
}



/* expect() - look for a specific string on stdin */

int
expect(char *s)
{
  register int i;
  static int expfail=EXPFAIL;
  static int retval=-1;
  char ch, *p, word[8192], buf[8192];
  static void (*oldalarm)()=NULL;

  if(!strcmp(s,"\"\"")){		/* ("") used as a place holder (do-nothing) */
    debug(D_CHAT,"EXPECT: [nothing]");
    return 0;
  }

  /* look for escape chars in expected word */
  
  retval=-1;
  expfail=EXPFAIL;
  for(p=word;(ch=(*s++));){
    if(ch=='\\'){
      if(*s=='A') {		/* spot for AutoBaud digits */
	*p++=AUTOBD;
	s++;
	continue;
      } else if(*s=='T'){	/* change expfail timeout */
	if(isdigit(*++s)){
	  s=unquote(s,&ch);
	  /* allow 1 - 255 second timeout */
	  if((expfail=((unsigned char)ch))<1) expfail=1;
	}
	continue;
      } else s=unquote(s,&ch);
    }
    *p++=(ch)?ch:'\177';
  }
  *p='\0';


  /* Set the long jump for the timeout */
  if(setjmp(env)){		/* expalarm returns non-zero here */
    debug(D_CHAT,"Timed out after %d second(s).",expfail);
    signal(SIGALRM,oldalarm);
    return -1;
  }

  /* Set the timeout alarm */

  oldalarm=signal(SIGALRM,expalarm);
  alarm((unsigned) expfail);
  

  debug(D_CHAT,"EXPECT: (timeout=%d) %s",expfail,quote(word));
  p=buf;
  bzero(buf,sizeof(buf));

  /* Now read what the device has to say for itself */
  while ((ch=getc(stdin))!=EOF) {
    *p++=ch;
    if(strlen(buf)>=strlen(word)) {
      for(i=0;buf[i];i++){
	if(expmatch(&buf[i],word)) {
	  retval=0;
	  break;
	}
      }
    }

    if(!retval)break;

    /* To make sure that buf never overflows, we'll zap it whenever an
       NL or CR is seen as the last character. */
    ch=buf[strlen(buf)-1];
    if(ch=='\n'||ch=='\r'){
      bzero(buf,sizeof(buf));
      p=buf;
    }
  }
  alarm(0);
  signal(SIGALRM,oldalarm);
  debug(D_CHAT, "GOT: %s",quote(buf));
  debug(D_CHAT, "EXPECT: %s.",(retval==0) ? "OK" : "failed");
  return(retval);
}


/* Handle expect/send strings */

int
chat(char *s)
{
  register int  state=EXPECT;
  int           finished=0, if_fail=0;
  char          c, *p;
  char          word[8192];
  
  debug(D_CHAT,"Chatting with script \"%s\"",s);

  while(!finished){
    p=word;

    for(p=word;(c=(*s))!=0 && c!=' ' && c!='\t' && c!='-';s++)*p++=*s;
    for(;(c=(*s))!=0 &&(c==' ' || c=='\t' || c=='-');s++);

    finished=(c=='\0');
    if_fail=(c=='-');
    *p='\0';

    switch(state){

      /* The EXPECT state first */
      
    case EXPECT:
      if(expect(word)<0){
	if(if_fail==0)return -1; /* No if_fail sequence */
      } else {
	
	/* Eat up rest of current sequence */

	if(if_fail==1){
	  while ((c=(*s++))!='\0'&&c!=' ');
	  if(c=='\0')finished=1;
	  if_fail=0;
	}
      }

      /* Move the state machine to the SEND state */
      state=SEND;

      break;

    case SEND:
      if(send(word)<0)return -1;

      /* Back to the EXPECT state */
      state=EXPECT;
      break;

    }
    continue;
  }

  debug(D_CHAT,"chat() exiting successfully.");
  return 0;
}


