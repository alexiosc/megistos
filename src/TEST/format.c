#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#include <bbsinclude.h>

#define LINELEN 72

#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((b)>(a)?(a):(b))

int RMARGIN=1;
int LMARGIN=0;

#define FFL_FORMAT     0x0000000f
#define FFL_FLUSHLEFT  0x00000000
#define FFL_FLUSHRIGHT 0x00000001
#define FFL_CENTRE     0x00000002
#define FFL_WRAP       0x00000004
#define FFL_JUSTIFY    0x00000008
#define FFL_BEGIN      0x00000010
#define FFL_END        0x00000020

long flags=FFL_FLUSHLEFT;
int  xpos=0;
char prevline[1024];
int  plidx=0;
char command[64];
int  comidx=0;
int  comstate=0;
char lastc=32;
int  lastpos=0;
char *lastp=NULL;
int  savepos=0;

char *
strins(char *s, int index, char *what)
{
  char before[1024]={0}, *cp=s+index;
  char retbuf[8192];

  if(index)memcpy(before,s,index);
  sprintf(retbuf,"%s%s%s",before,what,cp);
  return retbuf;
}


void
justify(char *s)
{
  int numspaces=LINELEN-RMARGIN-LMARGIN-lastpos;
  float spacing;
  int i;
  char *cp,*p;
  
  if(numspaces<=0)return;
  spacing=strlen(s)/numspaces;
  for(i=0;i<numspaces;i++){
    cp=s+(int)(((float)(i+1))*spacing);
    for(p=cp;*p&&!(*p==32);p++);
    if(*p){
      strcpy(s,strins(s,p-s," "));
    } else {
      for(p=cp;p>=s&&!(*p==32);p--);
      if(p>=s){
	strcpy(s,strins(s,p-s," "));
      } else break;
    }
  }
}


void
format(char *s)
{
  char *cp=s;
  char c;

  lastp=NULL;
  while((c=*cp)!=0){
    if(flags&FFL_BEGIN && flags&(FFL_WRAP|FFL_JUSTIFY)){
      if(c==10||c==13)c=32;
      if(lastc!=32 && c==32){
	lastpos=xpos;
      }
      lastc=c;
    }
    
    switch(comstate){
    case 0:
      if(c==27){
	command[0]=0;
	comidx=0;
	comstate=1;
	comidx=0;
      } else {
	prevline[plidx++]=c;
	prevline[plidx]=0;
	xpos++;
      }
      break;
    case 1:
      if(c=='['){
	comstate=2;
      } else if (c=='!'){
	comstate=3;
      } else {
	comstate=0;
	prevline[plidx++]=c;
	prevline[plidx]=0;
      }
      break;
    case 2:
      if(!comidx){
	prevline[plidx++]=27;
	prevline[plidx++]='[';
	prevline[plidx]=0;
      }
    case 3:
      if(comstate!=3){
	prevline[plidx++]=c;
	prevline[plidx]=0;
      }
      if(isdigit(c)||c==';'){
	command[comidx++]=c;
      } else {
	command[comidx]=0;
	if(comstate==2){
	  switch(c){
	  case 'C':
	    if(command[0])xpos=min(LINELEN-1,xpos+atoi(command));
	    else xpos=min(LINELEN-1,xpos+1);
	    break;
	  case 'D':
	    if(command[0])xpos=max(0,xpos-atoi(command));
	    else xpos=max(0,xpos-1);
	    break;
	  case 'J':
	    xpos=0;
	    break;
	  case 'H':
	    {
	      int i,j;
	      if(sscanf(command,"%d;%d",&i,&j)==2)xpos=j-1;
	      else xpos=0;
	      if(xpos<0)j=0;
	      else if(xpos>=LINELEN)xpos=LINELEN-1;
	      break;
	    }
	  case 's':
	    savepos=xpos;
	    break;
	  case 'u':
	    xpos=savepos;
	    break;
	  }
	} else if(comstate==3){
	  switch(c){
	  case 'L':
	    flags=(flags&~FFL_FORMAT)|FFL_FLUSHLEFT|FFL_BEGIN;
	    break;
	  case 'R':
	    flags=(flags&~FFL_FORMAT)|FFL_FLUSHRIGHT|FFL_BEGIN;
	    break;
	  case 'C':
	    flags=(flags&~FFL_FORMAT)|FFL_CENTRE|FFL_BEGIN;
	    break;
	  case 'W':
	    flags=(flags&~FFL_FORMAT)|FFL_WRAP|FFL_BEGIN;
	    break;
	  case 'J':
	    flags=(flags&~FFL_FORMAT)|FFL_JUSTIFY|FFL_BEGIN;
	    break;
	  case '(':
	    flags|=FFL_BEGIN;
	    break;
	  case ')':
	    flags|=FFL_END;
	    break;
	  case 'r':
	    if(strlen(command))RMARGIN=min(LINELEN-10,atoi(command));
	    else RMARGIN=min(LINELEN-10,LINELEN-xpos);
	    break;
	  case 'l':
	    if(strlen(command))LMARGIN=min(LINELEN-10,atoi(command));
	    else LMARGIN=min(LINELEN-10,xpos);
	    break;
	  case 'F':
	    if(*(cp+1)){
	      char multiple[256]={0};
	      char temp[1024];
	      memset(multiple,*(cp+1),LINELEN-LMARGIN-RMARGIN-xpos);

	      sprintf(temp,"%s%s",multiple,cp+2);
	      strcpy(cp+1,temp);
	    }
	    break;
	  }
	}
	comstate=0;
      }
      break;
    }
    
    if(flags&(FFL_WRAP|FFL_JUSTIFY) && flags&FFL_BEGIN){
      char *sp=strrchr(prevline,32);
      if(xpos>=LINELEN-RMARGIN-LMARGIN){
	char lpadding[256]={0};
	if(sp){
	  *sp=0;
	  if(flags&FFL_JUSTIFY)justify(prevline);
	  if(LMARGIN)memset(lpadding,32,LMARGIN);
	  printf("%s%s\n",lpadding,prevline);
	  for(sp=cp;sp>=s && *sp!=32;sp--);
	  if(sp!=lastp){
	    cp=sp;
	    for(cp=sp;*cp && *cp==32;cp++);
	    if(cp>s)cp--;
	    lastp=cp;
	  }
	} else {
	  if(LMARGIN)memset(lpadding,32,LMARGIN);
	  printf("%s%s\n",lpadding,prevline);
	}	  
	xpos=0;
	plidx=0;
      }
      if(flags&FFL_END)flags&=~(FFL_BEGIN);
    }

    if(flags&FFL_BEGIN && flags&~FFL_BEGIN && (c==10||c==13)){
      char padding[256]={0}, lpadding[256]={0};
      int  numspaces=LINELEN-RMARGIN-LMARGIN-xpos+1;
      
      if(flags&FFL_CENTRE)numspaces/=2;
      if(numspaces<0 || numspaces>255){
	padding[0]=0;
      } else memset(padding,32,numspaces);
      prevline[plidx]=0;
      
      if(LMARGIN)memset(lpadding,32,LMARGIN);
      printf("%s%s%s",lpadding,padding,prevline);
      if(flags&FFL_END)flags&=~(FFL_BEGIN);
      xpos=0;
      plidx=0;
    } else if (flags&FFL_BEGIN && ((flags&FFL_FORMAT)==FFL_FLUSHLEFT)
	       && (c==10||c==13)){
      char lpadding[256]={0};
      if(LMARGIN)memset(lpadding,32,LMARGIN);
      printf("%s%s",lpadding,prevline);
      if(flags&FFL_END)flags&=~(FFL_BEGIN);
      lastpos=0;
      lastc=-1;
      xpos=0;
      plidx=0;
    } else if (!(flags&FFL_BEGIN) && (c==10||c==13)) {
      char lpadding[256]={0};
      if(flags&FFL_END)if(LMARGIN)memset(lpadding,32,LMARGIN);
      printf("%s%s",lpadding,prevline);
      if(flags&FFL_END)flags&=~(FFL_BEGIN|FFL_END);
      lastpos=0;
      lastc=-1;
      xpos=0;
      plidx=0;
    }
    cp++;
  }
}





void
main()
{
  while(!feof(stdin)){
    char line[1024];
    if(!fgets(line,1024,stdin))continue;
    format(line);
  }
  {
    char lpadding[256]={0};
    memset(lpadding,32,LMARGIN);
    prevline[plidx]=0;
    if(flags&(FFL_WRAP|FFL_JUSTIFY))printf("%s%s\n\n\n",lpadding,prevline);
  }
}

