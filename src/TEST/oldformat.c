#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#include <bbsinclude.h>


#define MAXLEN 72

char prevline[8192]={0};
int xpos=0;


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
  int numspaces=MAXLEN-strlen(s);
  float spacing=strlen(s)/numspaces;
  int i;
  char *cp,*p;

  for(i=0;i<numspaces;i++){
    cp=s+(int)(((float)(i+1))*spacing);
    for(p=cp;*p&&!(*p==32);p++);
    if(*p){
      strcpy(s,strins(s,p-s," "));
    } else {
      for(p=cp;p>=s&&!(*p==32);p--);
      if(p>=s){
	strcpy(s,strins(s,p-s," "));
      } else return;
    }
  }
}


void
wrap(char **s, int just)
{
  if(xpos+strlen(*s)<MAXLEN){
    strcat(prevline,*s);
    xpos+=strlen(*s);
    **s=0;
    return;
  } else {
    char *cp=*s, *sp, word[1024];

    for(;*cp&&!(*cp==32);cp++);
    if(cp-*s){
      memset(word,0,sizeof(word));
      memcpy(word,*s,(cp-*s));
      if(xpos+strlen(word)<MAXLEN){
	strcat(prevline,word);
	xpos+=strlen(word);
      } else {
	char *ep=&prevline[strlen(prevline)-1];
	for(;ep!=(prevline-1) && (*ep==32);ep--);
	*(ep+1)=0;

	if(just)justify(prevline);
	
	printf("%s\n",prevline);
	strcpy(prevline,word);
	xpos=strlen(word);
      }
    }

    sp=cp;
    for(;*cp&&(*cp==32);cp++);
    if(cp-sp){
      memset(word,0,sizeof(word));
      memcpy(word,sp,(cp-sp));
      if(xpos+strlen(word)<MAXLEN){
	strcat(prevline,word);
	xpos+=strlen(word);
      } else {
	char *ep=&prevline[strlen(prevline)-1];
	for(;ep!=(prevline-1) && (*ep==32);ep--);
	*(ep+1)=0;

	if(just)justify(prevline);
	
	printf("%s\n",prevline);
	prevline[0]=0;
	xpos=0;
      }
    }
    *s=cp;
  }
}


void
main()
{
  int state;
  char param[64], command, *cp;
  char line[1024];

  while(!feof(stdin)){
    if(!fgets(line,sizeof(line),stdin))continue;
    for(cp=line;*cp;cp++)if(*cp==10 || *cp==13){
      *cp=32;
      break;
    }
    cp=line;
    while(*cp)wrap(&cp,1);
  }
  printf("%s\n",prevline);
}

