/*****************************************************************************\
 **                                                                         **
 **  FILE:     mkmtree                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 94, Version 1.0                                      **
 **  PURPOSE:  Produce a compiled menu tree file out of a menu tree spec-   **
 **            ification script.                                            **
 **  NOTES:    Input file format:                                           **
 **                                                                         **
 **            Lines beginning with '#' are comments.                       **
 **                                                                         **
 **            page <name>                                                  **
 **            descr <description>            OPTIONAL                      **
 **            type <type>                                                  **
 **            credits <credits>              OPTIONAL                      **
 **            key <keynumber>                OPTIONAL                      **
 **            class <class>                  OPTIONAL                      **
 **            hidden                         OPTIONAL                      **
 **            file <filename>                OPTIONAL                      **
 **            exec <program> <input>         OPTIONAL                      **
 **            run <shell-command>            OPTIONAL                      **
 **            opt <char> <name>              OPTIONAL                      **
 **            : : :                                                        **
 **            : : :                                                        **
 **            opt <char> <name>                                            **
 **            endpage                                                      **
 **                                                                         **
 **            (and all over again for each page).                          **
 **                                                                         **
 **            name: the name of a page, case insensitive, up to 15 chars   **
 **            description: the description of the page, up to 40 chars.    **
 **                 if not specified, menuman description (option MMDESC    **
 **                 in menuman.msg) is given. Up to 10 such directives may  **
 **                 be entered for a single page, reflecting different      **
 **                 descriptions for each of the 10 different languages.    **
 **            type: type of the page, among:                               **
 **                 MENU: page is a menu. Menuman prints a given file and   **
 **                     parses menu selections (see 'file' and 'opt-goto')  **
 **                 FILE: menuman prints a given file and returns to prev   **
 **                     page.                                               **
 **                 EXEC: execute another BBS module, giving specified in-  **
 **                     put to it.                                          **
 **                 RUN: execute a given shell command                      **
 **            credits: specifying a value for the 'credits' directive      **
 **                 sets the credit consumption rate for that page. If      **
 **                 omitted, the credit consumption rate is that defined    **
 **                 in option DEFCCR, level 2, menuman.msg. The unit is     **
 **                 ***NOT*** credits/min, but credits/100 mins, so that    **
 **                 for a charge of 1 credit per minute, this field should  **
 **                 contain '100'.                                          **
 **            keynumber: specifying a key number (1-128) allows access to  **
 **                 the page to users possessing the key only. Omitting     **
 **                 the 'key' directive gives access to all.                **
 **            class: specifying a class name restricts access to users of  **
 **                 the given class only. All classes are given access by   **
 **                 default.                                                **
 **            hidden: hides the option. This page will not appear any-     **
 **                 where, although it will be active. Useful for 'secret'  **
 **                 areas, like the remote sysop menu.                      **
 **            filename: specify the file to display. Available ONLY when   **
 **                 'type' is either MENU or FILE. The number of the lang-  **
 **                 uage [0-9] is appended to the filename. If the user     **
 **                 does not allow ANSI graphics, an extension .asc is      **
 **                 appended; otherwise, .ans is appended. If a .asc file   **
 **                 cannot be found, a .ans file is sought for, and vice    **
 **                 versa. If no files can be found for given language,     **
 **                 a file of the previous language is sought for. If no    **
 **                 file for language 0 is found, a file without a lang #   **
 **                 is sought for. If everything fails, we try to open the  **
 **                 filename as-is. If that fails, we log an error.         **
 **                                                                         **
 **                 Here's what happens: suppose filename=mainmenu, lang=2, **
 **                 ANSI=on.                                                **
 **                                                                         **
 **                 Try    mainmenu-2.ans     If not found,                 **
 **                 Try    mainmenu-2.asc     If not found,                 **
 **                 Try    mainmenu-1.ans     If not found,                 **
 **                 Try    mainmenu-1.asc     If not found,                 **
 **                 Try    mainmenu-0.ans     If not found,                 **
 **                 Try    mainmenu-0.asc     If not found,                 **
 **                 Try    mainmenu.ans       If not found,                 **
 **                 Try    mainmenu.asc       If not found,                 **
 **                 Try    mainmenu           If not found,                 **
 **                 Log an error and display nothing.                       **
 **                                                                         **
 **                 Specifying an .ans or .asc extension in <filename>      **
 **                 forces the program to drop the extension so the above   **
 **                 is possible.                                            **
 **                                                                         **
 **            program: specify the filename of the module to run. Only     **
 **                 available when 'type' is EXEC.                          **
 **            input: input to pass to the module to be executed. White     **
 **                 space is allowed. Only available when 'type' is EXEC.   **
 **            shell-command: a complete shell command to run. White space  **
 **                 is allowed. Only available when 'type' is RUN.          **
 **            char: a character option for a menu selection. Use only      **
 **                 when 'type' is MENU. If option is selected, we go to    **
 **                 page <name> as given in the opt-goto pair. If the page  **
 **                 does not exist, an error is logged. Each menu may have  **
 **                 up to 64 options (should be enought, right?)            **
 **            Use the 'endpage' directive to end the page definition.      **
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
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.5  1998/12/27 16:06:28  alexios
 * Added autoconf support.
 *
 * Revision 1.4  1998/08/11 10:18:18  alexios
 * Fixed initialisation bug.
 *
 * Revision 1.3  1998/07/24 10:22:39  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 1.2  1997/11/06 20:13:23  alexios
 * This program is now stable.
 *
 * Revision 1.1  1997/11/06 20:05:15  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 1.0  1997/08/28 11:01:50  alexios
 * Initial revision
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
const char *__RCS=RCS_VER;
#endif




/*
 * $Id$
 *
 * $Log$
 * Revision 1.3  2001/04/22 14:49:07  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.5  1998/12/27 16:06:28  alexios
 * Added autoconf support.
 *
 * Revision 1.4  1998/08/11 10:18:18  alexios
 * Fixed initialisation bug.
 *
 * Revision 1.3  1998/07/24 10:22:39  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 1.2  1997/11/06 20:13:23  alexios
 * This program is now stable.
 *
 * Revision 1.1  1997/11/06 20:05:15  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 1.0  1997/08/28 11:01:50  alexios
 * Initial revision
 *
 * Revision 0.2  1996/09/17 13:24:18  alexios
 * Corrected MAXLANGUAGES bug. mkmtree is now considered Stable.
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif
 

#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_UNISTD_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#include <bbsinclude.h>

#include "menuman.h"
#include "bbs.h"
#include "mbk_menuman.h"

#define ISSPACE(c) ((c)>0 && isspace(c))

#define DIR_PAGE   1
#define DIR_DESC   2
#define DIR_TYPE   3
#define DIR_CRED   4
#define DIR_KEY    5
#define DIR_CLSS   6
#define DIR_HIDDEN 7
#define DIR_FILE   8
#define DIR_EXEC   9
#define DIR_RUN   10
#define DIR_OPT   11
#define DIR_END   12

#define error(f,d,s) fprintf(stderr,"mkmtree: line %d: "f,d,s)


FILE *in, *out, *idx;
char fname[256];
int symtabentries=0;
char *symtab=NULL;


struct directive {
  char name[10];
  int  code;
};


struct pageidx {
  char page[16];
  long offset;
};


struct pageidx     *pageindex=NULL;
int                numpages=0;
union menumanpage  curpage;
struct pageidx     *curidx=NULL;


struct directive directives[]={
  {"page",DIR_PAGE},
  {"descr",DIR_DESC},
  {"type",DIR_TYPE},
  {"credits",DIR_CRED},
  {"key",DIR_KEY},
  {"class",DIR_CLSS},
  {"hidden",DIR_HIDDEN},
  {"file",DIR_FILE},
  {"exec",DIR_EXEC},
  {"run",DIR_RUN},
  {"opt",DIR_OPT},
  {"endpage",DIR_END},
  {"\0",0}
};


void
help()
{
  fprintf(stderr,"mkmtree usage:\n"); 
  fprintf(stderr,"                mkmtree -       Read stdin\n");
  fprintf(stderr,"                mkmtree name    Read name\n\n");
  exit(0);
}


int
pagenameok(char *s)
{
  int i;
  for(i=0;s[i];i++){
    char c;
    c=s[i]=toupper(s[i]);
    if(ISSPACE(c))return 0;
    if(!isalpha(c) && !isdigit(c))return 0;
  }
  return 1;
}


int
checksymbol(char *s)
{
  int i;
  for(i=0;i<symtabentries;i++){
    if(sameas(s,&symtab[i*(PAGENAMELEN+1)]))return 1;
  }
  return 0;
}


void
addsymbol(char *s)
{
  if(!checksymbol(s)){
    symtab=realloc(symtab,(++symtabentries)*(PAGENAMELEN+1));
    strncpy(&symtab[(symtabentries-1)*(PAGENAMELEN+1)],s,16);
  }
}


int
marksymbol(char *s)
{ 
  int i;
  for(i=0;i<symtabentries;i++){
    if(sameas(s,&symtab[i*(PAGENAMELEN+1)])){
      char *c=&symtab[i*(PAGENAMELEN+1)+PAGENAMELEN];
      if(*c)return 1;
      (*c)++;
      return 0;
    }
  }
  return 0;
}


int
optcmp(const void *a, const void *b)
{
  const struct menuoption *c1=a,*c2=b;
  return (c1->opt)-(c2->opt);
}
  

void
parse()
{
  int mode=0,linenum=0,pagetype=0,key=0,creds=DEFAULTCCR;
  char name[PAGENAMELEN], descr[NUMLANGUAGES][PAGEDESCRLEN];
  char class[10], file[FNAMELEN], exec[FNAMELEN];
  char run[RUNSTRLEN], input[INPUTSTRLEN];
  struct menuoption opts[MENUOPTNUM];
  int numopts=0, numdescs=0, flags=0;
  union menumanpage pagerec;
  char command[256];
  float frac;
  promptblock_t *msg;

  msg=msg_open("menuman");

  addsymbol(msg_get(TOPPAG));
  addsymbol(msg_get(EXTPAG));

  bzero(file,sizeof(file));
  bzero(exec,sizeof(exec));
  bzero(run,sizeof(run));

  if(!strcmp("-",fname)) in=stdin;
  else if ((in=fopen(fname,"r"))==NULL) {
    fprintf(stderr,"mkmtree: Unable to open %s\n",fname);
    exit(-1);
  }
  
  if((out=fopen(MENUMANPAGES,"w"))==NULL) {
    fprintf(stderr,"mkmtree: Unable to write %s\n",MENUMANPAGES);
    exit(-1);
  }

  sprintf(fname,"%s",tmpnam(0));
  if((idx=fopen(fname,"w"))==NULL) {
    fprintf(stderr,"mkmtree: Unable to write %s\n",MENUMANPAGES);
    exit(-1);
  }

  mode=0;
  linenum=0;
  
  while(!feof(in)){
    char line[1024], *cp, *sp, keyword[32], *value=NULL;
    int i,directive;

    if(!fgets(line,1024,in))continue;
    linenum++;

    for(cp=line;*cp;cp++)if(*cp==10 || *cp==13){
      *cp=0;
      break;
    }
    for(cp=line;*cp && ISSPACE(*cp);cp++);
    if(!strlen(cp)) continue;
    if(*cp=='#') continue;
    strncpy(keyword,cp,31);
    keyword[31]=0;
    for(sp=keyword;*sp && !ISSPACE(*sp);sp++);
    *sp=0;
    for(;*cp && !ISSPACE(*cp);cp++);
    for(value=cp;*value && ISSPACE(*value);value++);
    
    for(directive=0,i=0;!directive && directives[i].name[0];i++){
      if(sameas(directives[i].name,keyword))directive=directives[i].code;
    }
    if(!directive){
      error("Unknown directive (%s).\n",linenum,keyword);
      exit(-1);
    }

    switch(mode){
    case 0:
      switch(directive){
      case DIR_PAGE:
	if(strlen(value)>PAGENAMELEN-1) {
	  error("Page name '%s' too long.\n",linenum,value);
	  exit(-1);
	}
	if (!pagenameok(value)){
	  error("Invalid page name (%s).\n",linenum,value);
	  exit(-1);
	}
	if(marksymbol(value)){
	  error("Duplicate page name (%s).\n",linenum,value);
	  exit(-1);
	}
	strcpy(name,value);
	mode=1;
	pagetype=0;
	creds=DEFAULTCCR;
	key=0;
	class[0]=0;
	flags=0;
	file[0]=0;
	run[0]=0;
	input[0]=0;
	numopts=0;
	numdescs=0;
	memset(descr,0,sizeof(descr));
	memset(&opts,0,sizeof(opts));
	break;
      default:
	error("Expecting PAGE directive, found \"%s\".\n",linenum,keyword);
	exit(-1);
      }
      break;
    case 1:
      switch(directive){
      case DIR_DESC:
	if(strlen(value)>PAGEDESCRLEN-1){
	  error("Page description '%s' too long.\n",linenum,value);
	  exit(-1);
	} else if(numdescs>NUMLANGUAGES){
	  error("More than %d description strings.\n",linenum,NUMLANGUAGES);
	  exit(-1);
	} else {
	  int i;
	  for(i=numdescs;i<NUMLANGUAGES;i++){
	    strncpy(descr[i],value,PAGEDESCRLEN-1);
	    descr[i][PAGEDESCRLEN-1]=0;
	  }
	  numdescs++;
	}
	break;
      case DIR_TYPE:
	if(!sameas(value,"MENU") && !sameas(value,"FILE") &&
	   !sameas(value,"EXEC") && !sameas(value,"RUN")){
	  error("Invalid page type (%s).\n",linenum,value);
	  exit(-1);
	}
	pagetype=toupper(value[0]);
	break;
      case DIR_CRED:
	frac=(float)atof(value);
	creds=(int)(frac*100.0);
	break;
      case DIR_KEY:
	if((key=atoi(value))<1 || key>(32*KEYLENGTH)){
	  error("Expected value 1-128, found \"%s\".\n",linenum,value);
	  exit(-1);
	}
	break;
      case DIR_CLSS:
	if(strlen(value)>9){
	  error("Class name '%s' too long.\n",linenum,value);
	  exit(-1);
	} else {
	  int i;
	  strncpy(class,value,9);
	  class[9]=0;
	  for(i=0;i<9 && class[i];i++)class[i]=toupper(class[i]);
	}
	break;
      case DIR_HIDDEN:
	flags|=MPF_HIDDEN;
	break;
      case DIR_FILE:
	if(strlen(value)>FNAMELEN-1){
	  error("Class name '%s' too long.\n",linenum,value);
	  exit(-1);
	}
	strncpy(file,value,FNAMELEN-1);
	file[FNAMELEN-1]=0;
	break;
      case DIR_RUN:
	if(strlen(value)>RUNSTRLEN-1){
	  error("Shell command too long (%s).\n",linenum,value);
	  exit(-1);
	}
	strncpy(run,value,RUNSTRLEN-1);
	run[FNAMELEN-1]=0;
	break;
      case DIR_EXEC:
	{
	  char *value2=strchr(value,' ');
	  if(value2==NULL){
	    input[0]=0;
	  } else {
	    *(value2++)=0;
	    for(;*value2 && ISSPACE(*value2);value2++);
	    if(strlen(input)>INPUTSTRLEN-1){
	      error("Input string '%s' too long.\n",linenum,value2);
	      exit(-1);
	    }
	    strncpy(input,value2,INPUTSTRLEN-1);
	    input[INPUTSTRLEN-1]=0;
	  }
	  if(strlen(value)>FNAMELEN-1){
	    error("Module name '%s' too long.\n",linenum,value);
	    exit(-1);
	  }
	  strncpy(exec,value,FNAMELEN-1);
	  exec[FNAMELEN-1]=0;
	}
	break;
      case DIR_OPT:
	{
	  char *value2=strchr(value,' ');
	  if(value2==NULL){
	    error("Expecting two parameters for OPT, found '%s'.\n",linenum,value);
	    exit(-1);
	  } else {
	    *(value2++)=0;

	    if(strlen(value)!=1){
	      error("Expecting character as first parameter, found '%s'.\n",linenum,value);
	      exit(-1);
	    } else if(!isprint(value[0])) {
	      error("Expecting printable character for OPT, found '%s'\n",linenum,value);
	      exit(-1);
	    }
	    opts[numopts].opt=value[0];
	    
	    for(;*value2 && ISSPACE(*value2);value2++);
	    if(strlen(value)>PAGENAMELEN-1) {
	      error("Page name '%s' too long.\n",linenum,value2);
	      exit(-1);
	    }
	    if (!pagenameok(value2)){
	      error("Invalid page name (%s).\n",linenum,value2);
	      exit(-1);
	    }
	    addsymbol(value2);
	    strcpy(opts[numopts].name,value2);
	    numopts++;
	  }
	}
	break;
      case DIR_END:
	mode=0;

	if(!numopts && pagetype=='M'){
	  error("Menu page %s without any options!\n",linenum,name);
	  exit(-1);
	} else if(numopts && pagetype!='M'){
	  error("Menu options defined for non-menu page %s!\n",linenum,name);
	  exit(-1);
	} else if(file[0] && pagetype!='M' && pagetype!='F'){
	  error("Can't use the file directive in page %s!\n",linenum,name);
	  exit(-1);
	} else if(exec[0] && pagetype!='E'){
	  error("Can't use the exec directive in page %s!\n",linenum,name);
	  exit(-1);
	} else if(run[0] && pagetype!='R'){
	  error("Can't use the run directive in page %s!\n",linenum,name);
	  exit(-1);
	} else if(!file[0] && (pagetype=='M' || pagetype=='F')){
	  error("Need a file directive for page %s!\n",linenum,name);
	  exit(-1);
	}
	
	switch(pagetype){
	case 'M':
	  memset(&pagerec,0,sizeof(pagerec));
	  strcpy(pagerec.m.name,name);
	  memcpy(&pagerec.m.descr,descr,sizeof(descr));
	  pagerec.m.type=pagetype;
	  pagerec.m.creds=creds;
	  pagerec.m.key=key;
	  strcpy(pagerec.m.class,class);
	  pagerec.m.flags=flags;
	  strcpy(pagerec.m.fname,file);
	  qsort(opts,numopts,sizeof(struct menuoption),optcmp);
	  memcpy(pagerec.m.opts,opts,sizeof(pagerec.m.opts));
	  break;
	case 'F':
	  memset(&pagerec,0,sizeof(pagerec));
	  strcpy(pagerec.f.name,name);
	  memcpy(&pagerec.f.descr,descr,sizeof(descr));
	  pagerec.f.type=pagetype;
	  pagerec.f.creds=creds;
	  pagerec.f.key=key;
	  strcpy(pagerec.f.class,class);
	  pagerec.f.flags=flags;
	  strcpy(pagerec.f.fname,file);
	  break;
	case 'E':
	  memset(&pagerec,0,sizeof(pagerec));
	  strcpy(pagerec.e.name,name);
	  memcpy(&pagerec.e.descr,descr,sizeof(descr));
	  pagerec.e.type=pagetype;
	  pagerec.e.creds=creds;
	  pagerec.e.key=key;
	  strcpy(pagerec.e.class,class);
	  pagerec.e.flags=flags;
	  strcpy(pagerec.e.fname,exec);
	  strcpy(pagerec.e.input,input);
	  break;
	case 'R':
	  memset(&pagerec,0,sizeof(pagerec));
	  strcpy(pagerec.r.name,name);
	  memcpy(&pagerec.r.descr,descr,sizeof(descr));
	  pagerec.r.type=pagetype;
	  pagerec.r.creds=creds;
	  pagerec.r.key=key;
	  strcpy(pagerec.r.class,class);
	  pagerec.r.flags=flags;
	  strcpy(pagerec.r.command,run);
	  break;
	}
	strcpy(pagerec.m.prev,"TOP");
	fprintf(idx,"%-16s %6ld %08x\n",name,ftell(out),flags);

	if(fwrite(&pagerec,sizeof(pagerec),1,out)!=1){
	  fprintf(stderr,"mkmtree: Unable to write %s\n",MENUMANPAGES);
	  exit(-1);
	}
	file[0]=0;
	exec[0]=0;
	run[0]=0;
	break;
      default:
	error("Found '%s' before 'ENDPAGE'.\n",linenum,keyword);
	exit(-1);
      }
    }
  }

  {
    int i;
    for(i=0;i<symtabentries;i++){
      char *c=&symtab[i*(PAGENAMELEN+1)+PAGENAMELEN];
      char *s=&symtab[i*(PAGENAMELEN+1)];
      if(!*c) {
	fprintf(stderr,"mkmtree: line %d: Undefined page reference '%s'.\n",
		linenum,s);
	exit(-1);
      }
    }
  }
  
  fclose(in);
  fclose(out);
  fclose(idx);
  
  sprintf(command,"sort %s -k 1,16 >%s",fname,MENUMANINDEX);
  if(system(command)){
    fprintf(stderr,"mkmtree: Unable to sort index.\n");
    exit(-1);
  }
  unlink(fname);
}



void
loadindex()
{
  FILE *fp;
  
  if((fp=fopen(MENUMANINDEX,"r"))==NULL){
    fprintf(stderr,"mkmtree: Unable to open %s\n",MENUMANINDEX);
    exit(-1);
  }
  if(pageindex)free(pageindex);
  numpages=0;
  while(!feof(fp)){
    char line[256];
    char page[256];
    long offset;
    
    if(!fgets(line,256,fp))continue;
    if(sscanf(line,"%s %ld",page,&offset)!=2){
      fclose(fp);
      fprintf(stderr,"mkmtree: Menuman index %s bad format\n",MENUMANINDEX);
      exit(-1);
    }
    numpages++;
    pageindex=realloc(pageindex,sizeof(struct pageidx)*numpages);
    memset(&pageindex[numpages-1],0,sizeof(struct pageidx));
    strncpy(pageindex[numpages-1].page,page,15);
    pageindex[numpages-1].offset=offset;
  }
  fclose(fp);
}


int
pagecmp(const void *a, const void *b)
{
  const struct pageidx *index1=a;
  const struct pageidx *index2=b;
  return(strcmp(index1->page,index2->page));
}


void
thread(char *page, char *to)
{
  struct pageidx *p;
  union menumanpage curpage;

  p=bsearch(page,pageindex,numpages,sizeof(struct pageidx),pagecmp);
  if(!p) return;
  curidx=p;

  if(fseek(out,curidx->offset,SEEK_SET)) {
    fprintf(stderr,"mkmtree: Unable to seek page %s\n",curidx->page);
    exit(-1);
  }
  if(fread(&curpage,sizeof(curpage),1,out)!=1){
    fprintf(stderr,"mkmtree: Unable to read page %s\n",curidx->page);
    exit(-1);
  }

  if(strlen(curpage.m.prev)) return;
  
  strcpy(curpage.m.prev,to);

  if(fseek(out,curidx->offset,SEEK_SET)) {
    fprintf(stderr,"mkmtree: Unable to seek page %s\n",curidx->page);
    exit(-1);
  }
  if(fwrite(&curpage,sizeof(curpage),1,out)!=1){
    fprintf(stderr,"mkmtree: Unable to write page %s\n",curidx->page);
    exit(-1);
  }
}


void
graft()
{
  int i;
  union menumanpage p;

  loadindex();

  if((out=fopen(MENUMANPAGES,"r+"))==NULL) {
    fprintf(stderr,"mkmtree: Unable to write %s\n",MENUMANPAGES);
    exit(-1);
  }

  for(i=0;i<=numpages-1;i++){
    if(fseek(out,sizeof(union menumanpage) * i,SEEK_SET)){
      fprintf(stderr,"mkmtree: Unable to seek %s\n",MENUMANPAGES);
      exit(-1);
    }
    if(fread(&p,sizeof(union menumanpage),1,out)!=1){
      fprintf(stderr,"mkmtree: Unable to read %s\n",MENUMANPAGES);
      exit(-1);
    }

    if(p.m.type==PAGETYPE_MENU){
      int j;
      for(j=0;p.m.opts[j].opt && j<MENUOPTNUM;j++){
	thread(p.m.opts[j].name,p.m.name);
      }
    }
  }
  fclose(out);
}
  
  
int
main(int argc, char *argv[])
{
  mod_setprogname(argv[0]);
  if(argc!=2)help();
  strcpy(fname,argv[1]);
  parse();
  graft();
  return 0;
}
