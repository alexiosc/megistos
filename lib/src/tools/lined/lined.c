/*****************************************************************************\
 **                                                                         **
 **  FILE:     lined.c                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, March 95, Version 0.5 alpha                               **
 **            B, August 96, Version 0.6                                    **
 **  PURPOSE:  The Line Editor                                              **
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
 * Revision 1.1  2001/04/16 15:02:50  alexios
 * Initial revision
 *
 * Revision 0.8  2000/01/08 12:47:37  alexios
 * Slight bug fix that caused a segmentation fault when opening
 * new files.
 *
 * Revision 0.7  1999/07/18 22:09:18  alexios
 * Changed a few fatal() calls to fatalsys().
 *
 * Revision 0.6  1998/12/27 16:33:54  alexios
 * Added autoconf support. Added support for new file transfer
 * commands and fixed a slight bug.
 *
 * Revision 0.5  1998/07/24 10:31:13  alexios
 * Moved to stable status. Migrated to bbslib 0.6.
 *
 * Revision 0.4  1997/11/06 20:03:26  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.3  1997/11/05 10:50:13  alexios
 * Stopped using xlwrite() and reverted to write() since emud()
 * now performs all translations itself.
 *
 * Revision 0.2  1997/09/12 13:38:51  alexios
 * Fixed but with relative pathnames while uploading text. Made
 * sure the help message and ruler are output after a successful
 * upload so the user knows the upload is done. Added graceful
 * handling of save() errors. Save() now strips trailing blank
 * from the text it saves.
 *
 * Revision 0.1  1997/08/28 11:25:16  alexios
 * First registered revision. Adequate.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif



#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_TIME_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "mbk_lined.h"


#ifndef GREEK
#define IS_CANCEL(s) (sameas(s,"/C")||sameas(s,".C"))
#define IS_UPLOAD(s) (sameas(s,"/U")||sameas(s,".U"))
#define IS_SAVE(s)   (sameas(s,"/S")||sameas(s,".S"))
#define IS_OK(s)     (sameas(s,"OK"))
#else
#define IS_CANCEL(s) (sameas(latin(s),"/C")||sameas(latin(s),".C"))
#define IS_UPLOAD(s) (sameas(latin(s),"/U")||sameas(latin(s),".U"))
#define IS_SAVE(s)   (sameas(latin(s),"/S")||sameas(latin(s),".S"))
#define IS_OK(s)     (sameas(latin(s),"OK"))
#endif


struct line {
  char        *text;
  struct line *next;
} *first=NULL, *last=NULL, *inspoint=NULL;


promptblk    *msg;
int          numlines=0, numbytes=0, maxsize=1<<16;
extern char  input[MAXINPLEN];
char         wraparound[1024], filename[1024];


int          maxlen;
char         *txtupld;


static char *
latin(char *s)
{
  char buf[526];
  strcpy(buf,s);
  return latinize(buf);
}


void
init()
{
  initmodule(INITALL);
  msg=opnmsg("lined");
  setlanguage(thisuseracc.language);

  maxlen=numopt(MAXLEN,20,255);
  txtupld=stgopt(TXTUPLD);
}


void
insertline(struct line *afterline, char *s)
{
  struct line *new=(struct line *)alcmem(sizeof (struct line));

  if(!new)return;
  new->text=(char *)alcmem(strlen(s)+1);
  strcpy(new->text,s);
  if(!afterline)new->next=first;
  else {
    new->next=afterline->next;
    afterline->next=new;
  }
  if(!first || !afterline)first=new;
  if(!new->next)last=new;
  numlines++;
  numbytes+=strlen(s)+1;
  inspoint=new;
}


void
deletelines(int m, int n)
{
  struct line *l,*s,*e;
  int         i;

  numlines=numbytes=0;
  for(i=1,e=l=first,s=last=NULL;l;i++){
    if(i+1==m)s=l;
    if(i==n)e=l->next;
    if(i<m||i>n){
      numlines++;
      numbytes+=strlen(l->text)+1;
      last=l;
      l=l->next;
    } else {
      struct line *temp=l->next;
      free(l->text);
      free(l);
      l=temp;
    }
  }
  if(s)s->next=e;
  else first=e;
}


int
loadfile(char *fname)
{
  FILE        *fp;
  
  if((fp=fopen(fname,"r"))!=NULL){
    while(!feof(fp)){
      char line[1024];
      if(fgets(line,1024,fp)){
	char *cp=line;
	line[maxlen]=0;
	for(cp=line;*cp;cp++)if(*cp==10 || *cp==13){
	  *cp=0;
	  break;
	}
	if(numbytes+strlen(line)+1>maxsize){
	  prompt(SIZERR,maxsize);
	  fclose(fp);
	  return 1;
	}
	insertline(last,line);
      }
    }
    fclose(fp);
    return 1;
  }
  return 0;
}


void
edinputstring(int maxlen)
{
  int  cp=0, count=0;
  unsigned char c;

  nonblocking();
  reprompt=0;

  strcpy(input,wraparound);
  wraparound[0]=0;
  cp=strlen(input);
  if(cp)write(0,input,cp);

  if(!maxlen)maxlen=MAXINPLEN-1;
  for(;;){
    while (read(0,&c,1)!=1){
      usleep(10000);
      count=(count+1)%10;
      if(count) continue;
      if(dontinjoth || cp) continue;
      if(acceptinjoth()){
	reprompt=1;
	clrinp();
	blocking();
	return;
      }
    }
    resetinactivity();
    switch(c){
    case 13:
    case 10:
      c='\n';
      write(0,&c,1);
      fflush(stdout);
      input[cp]=0;
      monitorinput(getenv("CHANNEL"));
      if(handlegcs()){
	clrinp();
	reprompt=1;
      }
      blocking();
      return;
    case 127:
    case 8:
      if(cp){
	write(0,del,3);
	cp--;
      }
      break;
    default:
      if(cp+1+numbytes>=maxsize){
	char i=7;
	write(0,&i,1);
      } else if(cp<maxlen && (c>=0x20)){
	input[cp++]=c;
	write(0,&c,1);
      } else if(cp>maxlen){
	char i=7;
	write(0,&i,1);
      } else if(cp==maxlen){
	int i;
	char j=32;
	input[cp++]=c;
	input[cp]=0;
	for(i=0;cp && input[cp]!=32;cp--,i++)write(0,del,1);
	if(input[cp]==32)strcpy(wraparound,&input[cp+1]);
	else strcpy(wraparound,&input[cp]);
	for(;i;i--)write(0,&j,1);
	j='\n';
	write(0,&j,1);
	fflush(stdout);
	input[cp]=0;
	monitorinput(getenv("CHANNEL"));
	if(handlegcs()){
	  clrinp();
	  reprompt=1;
	}
	blocking();
	return;
      }
    }
  }
}


char *
edgetinput()
{
  afterinput=1;
  memset(input,0,sizeof(input));
  if(lastresult==PAUSE_QUIT) {
    reprompt=1;
  } else {
    resetvpos(0);
    edinputstring(maxlen);
  }
  resetvpos(0);
  nxtcmd=NULL;
  return margv[0];
}


void
cancel()
{
  if(!numlines){
    prompt(NCANCEL);
    return;
  } else if(numlines==1){
    numlines--;
    numbytes-=strlen(last->text)+1;
    free(last->text);
    free(last);
    inspoint=first=last=NULL;
  } else {
    struct line *l;
  
    for(l=first;l && l->next!=last;l=l->next);
    numlines--;
    numbytes-=strlen(last->text)+1;
    free(last->text);
    free(last);
    last=l;
    l->next=NULL;
    inspoint=l;
  }

  prompt(CANCEL,numlines+1,numlines,numbytes,maxsize);
}


void
showtext(int start, int end)
{
  struct line *l;
  int i;

  prompt(TXTHDR);
  for(i=1,l=first;l;l=l->next,i++){
    if(lastresult==PAUSE_QUIT)break;
    if(i>=start && i<=end)prompt(TXTLST,i,l->text);
    else if(i>end)break;
  }
}


void
listtext()
{
  prompt(TXTLSTH);
  showtext(1,numlines);
}


int
insert()
{
  struct line *l;
  int i,linenum;

  if(!getnumber(&linenum,INSERT,1,numlines,INVLIN,0,0))return 0;
  
  for(l=NULL,i=1;i<linenum;i++,l=(!l?first:l->next));
  inspoint=l;
  return 1;
}


void
sizewarn()
{
  if(maxsize-numbytes<maxlen)prompt(SIZEWARN,maxsize-numbytes);
}


void
retype()
{
  struct line *l;
  int i,linenum;

  if(!getnumber(&linenum,RETYPE,1,numlines,INVLIN,0,0))return;

  for(l=first,i=1;i<linenum;i++,l=l->next);
  prompt(TXTLST,i,l->text);
  
  prompt(EDITLN);
  prompt(RULER);
  numbytes-=strlen(l->text)+1;
  sizewarn();
  getinput(min(maxlen-1,maxsize-numbytes));
  free(l->text);
  l->text=(char *)alcmem(strlen(input)+1);
  strcpy(l->text,input);
  numbytes+=strlen(l->text)+1;
}


int
getrange(int *m, int *n, int min, int max, int pr, int err)
{
  int i;
  for(;;){
    if(morcnc()){
      if(isX(nxtcmd))return 0;
      rstrin();
    } else {
      prompt(pr,min,max);
      getinput(0);
      if(!margc)continue;
      if(margc==1 && isX(margv[0]))return 0;
      rstrin();
      nxtcmd=input;
    }
    *m=*n=0;
    if(!strchr(nxtcmd,'-') && sscanf(nxtcmd,"%d%n",n,&i))*m=*n;
    else if(sscanf(nxtcmd,"%d-%d%n",m,n,&i)==2);
    else if(sscanf(nxtcmd,"-%d%n",n,&i)==1)*m=min;
    else if(sscanf(nxtcmd,"%d-%n",m,&i)==1)*n=max;
    if(((*m)<min)||((*n)<min)||((*m)>max)||((*n)>max)||((*m)>(*n))){
      prompt(err,min,max);
      endcnc();
      input[0]=0;
      continue;
    }
    endcnc();
    return 1;
  }
  return 0;
}


void
change()
{
  int m,n,i,changes=0;
  char find[1024],replace[1024];
  struct line *l;

  if(!getrange(&m,&n,1,numlines,RWCHLN,RNGERR))return;
  if(n-m+5>=screenheight)prompt(RANGEOK,m,n);
  else showtext(m,n);
  endcnc();
  for(;;){
    prompt(FIND);
    getinput(0);
    bgncnc();
    if(!margc)continue;
    else if(isX(margv[0]))return;
    else {
      strncpy(find,input,sizeof(find));
      break;
    }
  }
  for(;;){
    prompt(REPLACE);
    getinput(0);
    bgncnc();
    if(!margc){
      replace[0]=0;
      break;
    }else if(isX(margv[0]))return;
    else {
      strncpy(replace,input,sizeof(find));
      break;
    }
  }

  changes=0;
  for(i=1,l=first;l&&(i<=n);i++,l=l->next){
    char line1[1024],line2[1024], *cp;
    if(i<m)continue;
    strcpy(line1,l->text);
    
    memset(line2,0,sizeof(line2));
    for(cp=line1;*cp;cp++){
      if(sameto(find,cp)){
	if(replace[0])strcat(line2,replace);
	cp+=strlen(find)-1;
      } else {
	int i=strlen(line2);
	line2[i]=*cp;
	line2[i+1]=0;
      }
    }
    line2[maxlen]=0;
    if(numbytes-strlen(l->text)+strlen(line2)>maxsize){
      prompt(REPLERR,i,maxsize);
      return;
    }
    if(strcmp(line1,line2)){
      changes++;
      numbytes-=strlen(l->text)+1;
      free(l->text);
      l->text=(char *)alcmem(strlen(line2)+1);
      strcpy(l->text,line2);
      numbytes+=strlen(l->text)+1;
    }
  }
  if(n-m+5>=screenheight)prompt(NCHNGD,changes);
  else {
    prompt(NLNRDS);
    showtext(m,n);
  }
}


void
delete()
{
  int m,n,yes=0;

  if(!getrange(&m,&n,1,numlines,DWDELN,RNGERR))return;
  if(n-m+5>=screenheight)prompt(RANGEOK,m,n);
  else showtext(m,n);
  if(!getbool(&yes,DELLIN+(n-m>0),YORN,0,0))return;
  if(!yes)return;

  deletelines(m,n);
}


void
newtext()
{
  int yes=0;
  if(!getbool(&yes,ASKNEW,YORN,0,0))return;
  if(!yes)return;
  deletelines(1,numlines);
}


void
upload()
{
  char fname[256],command[256],*cp,name[256],dir[256];
  FILE *fp;
  int  count = 0;

  name[0]=dir[0]=0;
  addxfer(FXM_UPLOAD,"UPLOAD-NAMELESS",txtupld,0,-1);
  dofiletransfer();
  
  sprintf(fname,XFERLIST,getpid());

  if((fp=fopen(fname,"r"))==NULL){
/*    prompt(XFERERR); */
    goto kill;
  }

  while (!feof(fp)){
    char line[1024];

    if(fgets(line,sizeof(line),fp)){
      strcpy(dir,line);
      break;
    }
  }
  if((cp=strchr(dir,'\n'))!=NULL)*cp=0;
  fclose(fp);

  sprintf(name,TMPDIR"/lined-%05d",getpid());

  sprintf(command,"cat %s/* >%s 2>/dev/null",dir,name);
  system(command);

  if(!loadfile(name))prompt(XFERERR);
  else {
    prompt(ENTHLP);
    prompt(RULER);
  }

 kill:
  if(count>=0){
    sprintf(command,"rm -rf %s %s",fname,dir);
    system(command);
  }
  if(name[0]){
    sprintf(command,"rm -f %s >&/dev/null",name);
    system(command);
  }
  killxferlist();
}


void
save()
{
  struct line *l;
  int mt=0;
  FILE *fp;

  if((fp=fopen(filename,"w"))==NULL){
    int i=errno;
    prompt(SAVEERR,i,sys_errlist[i]);
    errno=i;
    interrorsys("Unable to write to %s",filename);
    return;
  }

  for(l=first;l;l=l->next){
    int i=strspn(l->text," ");
    if(!strlen(&(l->text[i])))mt++;
    else {
      for(;mt;mt--)fprintf(fp,"\n");
      fprintf(fp,"%s\n",l->text);
    }
  }
  fclose(fp);
  exit(0);
}


void
abortedit()
{
  int yes=0;
  if(!getbool(&yes,ABORT,YORN,0,0))return;
  if(yes){
    unlink(filename);
    exit(1);
  }
}


void
menu()
{
  int shownmenu=0;
  char c;

  endcnc();

  for(;;){
    if(!nxtcmd){
      if(!shownmenu){
	prompt(EDTMNU);
	shownmenu=1;
      }
      prompt(EDTMNUS);
      getinput(0);
      bgncnc();
    }

    if((c=morcnc())!=0){
      cncchr();
      switch (c) {
	
      case 'A':
	if(numbytes<maxsize){
	  inspoint=last;
	  return;
	} else prompt(TOOBIG);
	break;
      case 'C':
	change();
	break;
      case 'D':
	delete();
	break;
      case 'H':
	prompt(HELP);
	break;
      case 'I':
	if(numbytes<maxsize){
	  if(insert())return;
	} else prompt(TOOBIG);
	break;
      case 'L':
	listtext();
	break;
      case 'N':
	newtext();
	break;
      case 'R':
	retype();
	break;
      case 'S':
	save();
	break;
      case 'U':
	upload();
	break;
      case 'X':
	abortedit();
	break;
      case '?':
	shownmenu=0;
	break;
      default:
	prompt(ERRSEL,c);
	endcnc();
	continue;
      }
    }
    if(lastresult==PAUSE_QUIT)resetvpos(0);
    endcnc();
  }
}


void
run()
{
  loadfile(filename);
  inspoint=last;
  prompt(ENTTXT,maxsize);
  if(numlines)prompt(REMINDER,numlines,numbytes);
  prompt(RULER);
  for(;;){
    if(numbytes>=maxsize){
      prompt(TOOBIG);
      menu();
      prompt(SIZINFO,numlines,numbytes,maxsize);
      prompt(ENTHLP);
      prompt(RULER);
    }
    sizewarn();
    edgetinput(80);
    rstrin();
    if(reprompt||sameas(input,"?")){
      reprompt=0;
      prompt(SIZINFO,numlines,numbytes,maxsize);
      prompt(ENTHLP);
      prompt(RULER);
    } else if(IS_CANCEL(input)){
      cancel();
    } else if(IS_UPLOAD(input)){
      upload();
    } else if(IS_SAVE(input)){
      save();
    } else if(isX(input)){
      abortedit();
      prompt(SIZINFO,numlines,numbytes,maxsize);
      prompt(ENTHLP);
      prompt(RULER);
    } else if(IS_OK(input) || numbytes>=maxsize){
      menu();
      prompt(SIZINFO,numlines,numbytes,maxsize);
      prompt(ENTHLP);
      prompt(RULER);
    } else {
      insertline(inspoint,input);
    }
  }
}


void
done()
{
  clsmsg(msg);
}


void
main(int argc, char *argv[])
{
  setprogname(argv[0]);
  if(argc==3 && (maxsize=atoi(argv[2]))){
    init();
    strcpy(filename,argv[1]);
    run();
    done();
  }
}

