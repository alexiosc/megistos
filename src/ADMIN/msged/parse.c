/*****************************************************************************\
 **                                                                         **
 **  FILE:     parse.c                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, August 94, Version 0.01 alpha                             **
 **  PURPOSE:  Parse a config file into a linked list of option structs.    **
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
 * Revision 1.2  2001/04/16 21:56:28  alexios
 * Completed 0.99.2 API, dragged all source code to that level (not as easy as
 * it sounds).
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
const char *__RCS=RCS_VER;
#endif



#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_UNISTD_H 1
#define WANT_STRING_H 1
#define WANT_CTYPE_H 1
#define WANT_NCURSES_H 1
#include <bbsinclude.h>

#include "config.h"
#include "useracc.h"
#include "miscfx.h"
#include "msged.h"


int
special(char *s)
{
  int value=(strlen(s)==6)&&(strstr(s,"LEVEL")==s)&&isdigit(s[5]);
  value|=(strlen(s)==7)&&(strstr(s,"LEVEL")==s)&&isdigit(s[5])&&isdigit(s[6]);
  value|=(!strcmp(s,"LANG"));
  return value;
}


void insopt(struct option *newopt)
{
  if(curopt)curopt->opt_next=newopt;
  newopt->opt_prev=curopt;
  curopt=newopt;
  if(!options)options=newopt;
  if(newopt->opt_type)numoptions++;
}


void
parsefile(char *filename)
{
  FILE *input;
  char rawname[64], *cp, ch=0;
  char *mods=NULL, *s=NULL;
  char keyword[64];
  char opttext[16384]={0}, hlptext[16384]={0};
  int mode, i, curlang, curlevel;
  
  while(curopt && curopt->opt_next)curopt=curopt->opt_next;

  /* Open files, calculate names */
  
  if((input=fopen(filename,"r"))==NULL){
    errp("Unable to open %s\n",filename);
    exit(-1);
  }
  
  if((cp=strrchr(filename,'/'))==0)cp=filename;
  else cp++;
  strcpy(rawname,cp);
  if((cp=strstr(rawname,".msg"))!=0)*cp=0;

  /* Insert filename tab */
  
  {
    struct option *newopt=alcmem(sizeof(struct option));
    
    memset(newopt,0,sizeof(struct option));
    newopt->opt_type=0;
    sprintf(newopt->opt_file,"%s.msg",rawname);
    insopt(newopt);
  }
  
  /* Initialise variables */
  
  mode=0;
  curlang=0;
  curlevel=0;
  strcpy(keyword,"");
  
  while(!feof(input)){
    char line[1024], xlated[1024], text[16384];
    char *cp;
    int  escape;
    
    if(!fgets(line,1024,input)) continue;
    
    switch(mode){
    case 0:
      
      /* Find keyword and start of text block */
      
      cp=(char *)strchr(line,'{');
      if(cp){
	char *kp=line;
	
	mode=1;
	while(isspace(*kp)&&(*kp))kp++;
	strncpy(keyword,kp,64);
	
	opttext[0]=0;
	
	for(kp=keyword;*kp;kp++)if(isspace(*kp)){
	  *kp=0;
	  break;
	}
	debug("\nKEYWORD: %s\n",keyword);
	
	/* Handle special keywords */
	
	if(special(keyword)){
	  if (!strcmp("LANG",keyword)){
	    curlang++;
	    
	    debug("CURLANG=%d\n",curlang);
	  } else {
	    char *cp=keyword+strlen("LEVEL");
	    curlevel=atoi(cp);
	    debug("CURLEVEL=%d\n",curlevel);
	  }
	}
	
	/* Begin reading text block */
	
	strcpy(xlated,++cp);
	strcpy(line,xlated);
      } else {
	char temp[1024],*cp,*ep=NULL;
	
	strcpy(temp,line);
	cp=temp;
	while(*cp==32)cp++;
	for(;*cp;){
	  ep=&cp[strlen(cp)-1];
	  if(*ep==32||*ep=='\n'||*ep=='\r')*ep=0;
	  else break;
	}
	
	if(hlptext[0]==0&&(*cp==0))break;
	sprintf(line,"%s\n",cp);
	if(strlen(hlptext)+strlen(line)>sizeof(hlptext)){
	  errp("Help text after option %s is too big.\n",keyword);
	  exit(-1);
	} else strcat(hlptext,line);
	debug("HELP TEXT: (%s)\n",cp);
	break;
      }
      
    case 1:
      
      /* Translate escape sequences */
      
      strcpy(xlated,line);
      for(cp=xlated,escape=0,i=0;*cp;cp++){
	if((*cp==0x7e)&&(!escape))escape=1;
	else if((*cp==0x7d)&&(!escape))line[i++]='\377';
	else {
	  escape=0;
	  line[i++]=*cp;
	}
      }
      line[i]=0;
      cp=(char *)strrchr(line,0xff);
      
      if(cp){
	ch=*cp;
	*cp=0;
      }
      if(strlen(opttext)+strlen(line)>sizeof(opttext)){
	errp("Option text for option %s is too big.\n",keyword);
	exit(-1);
      } else strcat(opttext,line);
      debug("OPTION TEXT: (%s)\n",line);
      
      /* Check for end of text block */
      
      if(cp){
	char *kp;
	
	*cp=ch;
	strcpy(text,line);
	kp=(char *)strrchr(line,0xff);
	*kp=0;
	mods=kp+1;
	while(mods && *mods==32)mods++;
	if(*mods=='('){
	  while(mods&&*mods!=')')mods++;
	  mods++;
	}
	
	mode=0;
#ifdef DEBUG
	fprintf(stderr,"MODE=0\n");
#endif
      }
      /* Parse text block */
      
      if(cp && !special(keyword) && strcmp(keyword,"LANGEND")){
	if(!mode){
	  struct option *newopt=alcmem(sizeof(struct option));
	  
	  memset(newopt,0,sizeof(struct option));
	  sprintf(newopt->opt_file,"%s.msg",rawname);
	  strncpy(newopt->opt_name,keyword,32);
	  newopt->opt_language=curlang;
	  newopt->opt_level=curlevel;
	  newopt->opt_help=alcmem(strlen(hlptext)+1);
	  strcpy(newopt->opt_help,hlptext);
	  
	  while(mods && *mods==32)mods++;
	  
	  switch(newopt->opt_type=toupper(*mods)){
	  case 'C':
	    newopt->opt_min=opttext[strlen(opttext)-1];
	    if(!opttext[0]){
	      errp("Bad format for character option %s.\n",keyword);
	      exit(-1);
	    }
	    strncpy(newopt->opt_descr,opttext,80);
	    newopt->opt_descr[strlen(newopt->opt_descr)-1]=0;
	    while(newopt->opt_descr[0]&&
		  newopt->opt_descr[strlen(newopt->opt_descr)-1]==32){
	      newopt->opt_descr[strlen(newopt->opt_descr)-1]=0;
	    }
#ifdef DEBUG
	    fprintf(stderr,"CHAROPT: CHAR %c DESCR %s\n",newopt->opt_min,newopt->opt_descr);
#endif
	    newopt->opt_max=0;
	    newopt->opt_choices=NULL;
	    break;
	    
	  case 'S':
	    mods++;
	    if(sscanf(mods,"%ld",&newopt->opt_max)!=1){
	      errp("Bad format for string option %s.\n",keyword);
	      exit(-1);
	    }
	    while(mods && !isdigit(*mods))mods++;
	    while(mods && isdigit(*mods))mods++;
	    while(mods && *mods==32)mods++;
	    strncpy(newopt->opt_descr,mods,sizeof(newopt->opt_descr)-1);
#ifdef DEBUG
	    fprintf(stderr,"STRINGOPT: MAX %ld DESCR %s\n",newopt->opt_max,newopt->opt_descr);
#endif
	    newopt->opt_contents=alcmem(strlen(opttext)+1);
	    strcpy(newopt->opt_contents,opttext);
	    newopt->opt_min=0;
	    break;
	    
	  case 'T':
	    mods++;
	    while(mods && *mods==32)mods++;
	    strncpy(newopt->opt_descr,mods,sizeof(newopt->opt_descr)-1);
	    
	    if(MSGBUFSIZE<strlen(opttext)){
	      errp("Text option %s is too long.\n",keyword);
	      exit(-1);
	    }
	    newopt->opt_contents=alcmem(strlen(opttext)+1);
	    strcpy(newopt->opt_contents,opttext);
#ifdef DEBUG
	    fprintf(stderr,"TEXTOPT: LENGTH=%d DESCR %s\n",strlen(opttext),newopt->opt_descr);
#endif
	    newopt->opt_min=0;
	    break;
	    
	  case 'N':
	  case 'L':
	    s=&opttext[strlen(opttext)-1];
	    if(!isdigit(*s)){
	      errp("Bad format for numeric option %s.\n",keyword);
	      exit(-1);
	    }
	    while(s>opttext && isdigit(*s))s--;
	    *s=0;
	    s++;
	    while(opttext[0]&&opttext[strlen(opttext)-1]==32){
	      opttext[strlen(opttext)-1]=0;
	    }
	    strncpy(newopt->opt_descr,opttext,sizeof(newopt->opt_descr)-1);
	    newopt->opt_contents=(char *)atoi(s);
	    
	    if(sscanf(++mods,"%ld %ld",&newopt->opt_min,&newopt->opt_max)!=2){
	      errp("Bad format for numeric option %s.\n",keyword);
	      exit(-1);
	    }
	    newopt->opt_choices=NULL;
#ifdef DEBUG
	    fprintf(stderr,"NUMOPT: MIN %ld MAX %ld DESCR %s\n",newopt->opt_min,newopt->opt_max,newopt->opt_descr);
#endif
	    break;
	    
	  case 'H':
	  case 'X':
	    s=&opttext[strlen(opttext)-1];
	    if(!isxdigit(*s)){
	      errp("Bad format for hex option %s.\n",keyword);
	      exit(-1);
	    }
	    while(s>opttext && isxdigit(*s))s--;
	    *s=0;
	    s++;
	    while(opttext[0]&&opttext[strlen(opttext)-1]==32){
	      opttext[strlen(opttext)-1]=0;
	    }
	    strncpy(newopt->opt_descr,opttext,sizeof(newopt->opt_descr)-1);
	    {
	      unsigned int i;
	      sscanf(s,"%x",&i);
	      newopt->opt_contents=(char *)i;
	    }
	    
	    if(sscanf(++mods,"%lx %lx",&newopt->opt_min,&newopt->opt_max)!=2){
	      errp("Bad format for numeric option %s.\n",keyword);
	      exit(-1);
	    }
	    newopt->opt_choices=NULL;
#ifdef DEBUG
	    fprintf(stderr,"HEXOPT: MIN %ld MAX %ld DESCR %s\n",newopt->opt_min,newopt->opt_max,newopt->opt_descr);
#endif
	    break;
	    
	  case 'B':
	    s=&opttext[strlen(opttext)-1];
	    while(s>opttext && *s!=32)s--;
	    *s=0;
	    s++;
	    while(opttext[0]&&opttext[strlen(opttext)-1]==32){
	      opttext[strlen(opttext)-1]=0;
	    }
	    strncpy(newopt->opt_descr,opttext,sizeof(newopt->opt_descr)-1);
	    if(strcmp(s,"YES")&&strcmp(s,"NO")){
	      errp("Bad format for boolean option %s.\n",keyword);
	      exit(-1);
	    } else newopt->opt_min=strcmp(s,"YES")==0;
	    newopt->opt_max=0;
	    newopt->opt_choices=NULL;
#ifdef DEBUG
	    fprintf(stderr,"BOOLOPT: VALUE=%ld DESCR %s\n",newopt->opt_min,newopt->opt_descr);
#endif
	    break;
	    
	  case 'E':
	    s=&opttext[strlen(opttext)-1];
	    while(s>opttext && *s!=32)s--;
	    *s=0;
	    s++;
	    while(opttext[0]&&opttext[strlen(opttext)-1]==32){
	      opttext[strlen(opttext)-1]=0;
	    }
	    strncpy(newopt->opt_descr,opttext,sizeof(newopt->opt_descr)-1);
	    mods++;
	    while(mods && *mods==32)mods++;
	    if(!strstr(mods,s)){
	      errp("Bad value for multiple choice option %s.\n",keyword);
	      exit(-1);
	    }
	    newopt->opt_choices=alcmem(strlen(mods)+1);
	    strcpy(newopt->opt_choices,mods);
	    newopt->opt_contents=strstr(newopt->opt_choices,s);
	    newopt->opt_min=0;
	    newopt->opt_max=0;
#ifdef DEBUG
	    fprintf(stderr,"MCOPT: CHOICES=(%s) DESCR %s\n",
		    newopt->opt_choices,newopt->opt_descr);
#endif
	    break;
	    
	  default:
	    errp("Unknown option type for option %s.\n",keyword);
	    exit(-1);
	  }
	  
	  {
	    char *cp=newopt->opt_descr;
	    while(*cp&&*cp!=10&&*cp!=13)cp++;
	    *cp=0;
	  }

	  insopt(newopt);
	  
	  /* 	    debug("MODS: (%s)\n",mods); */
	  debug("----------------------- DONE OPTION %s\n",keyword);
	  hlptext[0]=0;  /* HIC SOUPIERAE */
	}
      }
    break;
    }
  }
  
  fclose(input);
}

