/*****************************************************************************\
 **                                                                         **
 **  FILE:    search.c                                                      **
 **  AUTHORS: Alexios                                                       **
 **  PURPOSE: Search for files.                                             **
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
 * Revision 1.1  2001/04/16 14:56:05  alexios
 * Initial revision
 *
 * Revision 0.5  2000/01/06 10:37:25  alexios
 * Completed support for searching in OS-only libraries.
 *
 * Revision 0.4  1999/07/18 21:29:45  alexios
 * Changed a few fatal() calls to fatalsys(). Numerous other
 * changes.
 *
 * Revision 0.3  1998/12/27 15:40:03  alexios
 * Added autoconf support.
 *
 * Revision 0.2  1998/07/24 10:18:32  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.1  1998/04/21 10:12:53  alexios
 * Initial revision.
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
#define WANT_FCNTL_H 1
#define WANT_TIME_H 1
#define WANT_SYS_STAT_H 1
#define WANT_DIRENT_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_REGEX_H 1
#include <bbsinclude.h>

#include <sys/wait.h>
#include "bbs.h"
#include "files.h"
#include "mbk_files.h"


/* The query result data type. Total size: 96 bytes */

struct result {
  char keyword[24];		/* The matching keyword, if available */
  char fname  [24];		/* The filename of the matching file */
  char summary[44];		/* Short description of the file */
  int  libnum;			/* Library number this file belongs to */
};


struct  result *resultcache=NULL;  /* Enough results for one page */
int     numresultsincache;         /* Number of results in cache */
int     lastpage=-1;		   /* The last page displayed */


struct _daemoninfo {
  int  daemondead;		/* The daemon has finished its task */
  int  filecreated;		/* The daemon has created the file */
  int  nummatches;		/* Number of matches found so far */
  int  nomore;                  /* No more matches found */
};


#define daemoninfo (*((struct _daemoninfo*)&_thisuseraux))
#define NUMPAGES ((daemoninfo.nummatches+srlstln-1)/srlstln)


/* Search types */

#define SHF_FNAME     0x01	/* Search by filename */
#define SHF_KEYWORD   0x02	/* Search by keyword */
#define SHF_ANYWHERE  0x04	/* Search by keyword */
#define SHF_DATE      0x08	/* Search by date */
#define SHF_DAYCOUNT  0x10	/* Search by day count */
#define SHF_TYPE      0x1f	/* All types ORed together */

/* Search subtypes */

#define SHF_LITERAL   0x40	/* Search by literal string */
#define SHF_REGEXP    0x80	/* Search by regular expression or wildcard */


static char    searchfor[1024];
static int     searchtype;
static time_t  searchtime;
static char    resultfname[256];
static FILE   *resultfp;
static int     daemonpid;

struct re_pattern_buffer *regexp=NULL;


static char *
getsearchterm()
{
  char *fn=input;
  
  for(;;){
    if(morcnc())fn=cncword();
    else {
      prompt(SRASK);
      getinput(0);
      fn=input;
    }

    if(isX(fn))return NULL;
    else if(!strlen(fn)){
      endcnc();
      continue;
    } else if(!strcmp(fn,"?")){
      prompt(SRHELP);
      endcnc();
      continue;
    } else break;
  }

  return fn;
}


int mkregexp(char *re)
{
  int len=strlen(re);
  char *errmsg;

  lcase(re);

  if(regexp==NULL){
    regexp=alcmem(sizeof(struct re_pattern_buffer));
    bzero(regexp,sizeof(struct re_pattern_buffer));
  }

  regexp->allocated=len*2;
  if(regexp->buffer)free(regexp->buffer);
  regexp->buffer=alcmem(regexp->allocated);
  regexp->translate=NULL;
  if(regexp->fastmap)free(regexp->fastmap);
  regexp->fastmap=alcmem(256);
  regexp->fastmap_accurate=0;
  errmsg=(char*)re_compile_pattern(re,len,regexp);
  if(errmsg!=NULL){
    prompt(SRRXERR,re,errmsg);
    return 0;
  }

  return 1;
}


int mkwildcard (char *s)
{
  char tmp[2048], add[4];
  register int i, quotenext=0;

  lcase(s);
  strcpy(tmp,"^");
  for(i=0;s[i];s++){
    if(quotenext==1){
      sprintf(add,"%c",s[i]);
      strcat(tmp,add);
    } else switch(s[i]){
    case '?':
      strcat(tmp,".");
      break;
    case '*':
      strcat(tmp,".*");
      break;
    case '{': case '}': case ')': case '(':
    case '+': case '|': case '^': case '$':
    case '.':
    case '\\':
      sprintf(add,"\\%c",s[i]);
      strcat(tmp,add);
      quotenext=1;
      break;
    default:
      tmp[strlen(tmp)+1]=0;
      tmp[strlen(tmp)]=s[i];
    }
  }
  strcat(tmp,"$");
  return mkregexp(tmp);
}


static int
grokanywhere(char *s)
{
  searchtype=SHF_ANYWHERE;
  strcpy(searchfor,s);
  return 1;
}


static int
_grokterm(char *s, int type)
{
  searchtype=type;

  /* It's a regexp */

  if(*s=='/'){
    char *end=&s[strlen(s)-1];
    if(*end=='/')*end=0;	/* Kill trailing slash */
    s++;			/* Kill leading slash */
    searchtype|=SHF_REGEXP;	/* Searching by regexp */
    if(!mkregexp(s))return 0;	/* Compile the regexp and check it */
  }
  
  /* A string with wildcards. Translate DOS/Unix wildcards into a
     regexp and treat this whole thing as a regexp search. */

  else if(strcspn(s,"*?[]")!=strlen(s)){
    searchtype|=SHF_REGEXP;
    if(!mkwildcard(s))return 0;	/* Convert wildcards into regexp and check */
  }

  /* Aha, a literal string */
  
  else searchtype|=SHF_LITERAL;

  strcpy(searchfor,s);
  return 1;
}


static int
grokdate(char *s)
{
  int t;
  struct tm tm;

  if(*s=='-'){
    searchtime=time(0)-(60*60*24*(1+atoi(++s)));
    searchtype=SHF_DAYCOUNT;
    return 1;
  }
  
  t=scandate(s);
  if(t<0){
    prompt(SRDTERR);
    return 0;
  }
  
  bzero(&tm,sizeof(tm));
  tm.tm_mday=tdday(t);
  tm.tm_mon=tdmonth(t);
  tm.tm_year=tdyear(t)-1900;
  searchtime=mktime(&tm);
  searchtype=SHF_DATE;
  return 1;
}


static int
grokterm(char *s)
{
  if(*s=='+')return _grokterm(++s,SHF_KEYWORD);
  else if(*s=='-' || strchr(s,'/')>s)return grokdate(s);
  else if(*s=='?')return grokanywhere(++s);
  else return _grokterm(s,SHF_FNAME);
}


static void
found(struct libidx *l, struct fileidx *f, char *keyword)
{
  struct result r;
  bzero(&r,sizeof(r));
  if(searchtype&(SHF_DAYCOUNT|SHF_DATE)){
    struct tm *tm=localtime(&(f->timestamp));
    strcpy(r.keyword,strdate(makedate(tm->tm_mday,
				      tm->tm_mon+1,
				      tm->tm_year+1900)));
  } else if(keyword)strcpy(r.keyword,keyword);
  strcpy(r.fname,f->fname);
  strcpy(r.summary,f->summary);
  r.libnum=f->flibnum;
  if(!fwrite(&r,sizeof(r),1,resultfp)){
    fatalsys("Search daemon unable to write to %s",resultfname);
  }
  fflush(resultfp);		/* Keep it in sync */
  daemoninfo.nummatches++;
}


static void
os_found(struct libidx *l, char *fname, struct stat *st)
{
  struct result r;
  bzero(&r,sizeof(r));
  if(searchtype&(SHF_DAYCOUNT|SHF_DATE)){
    struct tm *tm=localtime(&(st->st_mtime));
    strcpy(r.keyword,strdate(makedate(tm->tm_mday,
				      tm->tm_mon+1,
				      tm->tm_year+1900)));
  }
  strcpy(r.fname,fname);
  strcpy(r.summary,osfdesc);
  r.libnum=l->libnum;
  if(!fwrite(&r,sizeof(r),1,resultfp)){
    fatalsys("Search daemon unable to write to %s",resultfname);
  }
  fflush(resultfp);		/* Keep it in sync */
  daemoninfo.nummatches++;
}


static void
search_fnames(struct libidx *l)
{
  int morefiles;
  struct fileidx f;

  if(searchtype&SHF_LITERAL){
    /* Quick Typhoon-based search for literal filename */

    if(fileread(l->libnum,searchfor,1,&f))found(l,&f,NULL);
  } else {
    /* Slower search for regexp */

    morefiles=filegetfirst(l->libnum,&f,1);
    while(morefiles){
      char tmp[24];
      int len=strlen(f.fname);
      strcpy(tmp,f.fname);
      lcase(tmp);
      if(!f.approved || f.flibnum!=l->libnum)break;
      if((len=re_search(regexp,tmp,len,0,len,NULL))>=0)found(l,&f,NULL);
      morefiles=filegetnext(l->libnum,&f);
    }
  }
}


static char *match_to;


static int insensitive_match(const struct dirent *d)
{
  return sameas(match_to,(char*)d->d_name);
}


static void
os_search_fnames(struct libidx *l)
{
  struct stat st;
  char        fname[1024];

  if(searchtype&SHF_LITERAL){
    int              i,j;
    struct dirent  **d=NULL;
    

    /* Looking for one file only, the search is literal */
    
    match_to=searchfor;
    if((j=scandir(l->dir,&d,insensitive_match,alphasort))==0){
      if(d)free(d);
      return;
    }
    
    for(i=0;i<j;i++){
      sprintf(fname,"%s/%s",library.dir,d[i]->d_name);
      if(stat(fname,&st)==0) os_found(l,d[i]->d_name,&st);
      free(d[i]);
    }
    free(d);
  
  } else {
    DIR            *dp;
    struct dirent  *d;
    
    /* Slower search for regexp */


    /* Open the library directory */
    
    if((dp=opendir(l->dir))==NULL){
      fatalsys("Unable to open library %s (directory: %s)",
	       l->fullname,l->dir);
    }

    while((d=readdir(dp))!=NULL){
      char tmp[24];
      int len=strlen(d->d_name);

      strcpy(tmp,d->d_name);
      lcase(tmp);

      if((len=re_search(regexp,tmp,len,0,len,NULL))>=0) {
	sprintf(fname,"%s/%s",l->dir,d->d_name);
	if(stat(fname,&st)==0) os_found(l,d->d_name,&st);
      }
    }

    closedir(dp);
  }
}


static void
search_keywords(struct libidx *l)
{
  int morekeys;
  struct maintkey    k;
  struct fileidx     f;

  if(searchtype&SHF_LITERAL){
    /* Quick Typhoon-based search for literal keyword */

    morekeys=keywordfind(l->libnum,searchfor,&k);
    while(morekeys){
      if(!sameas(searchfor,k.keyword))break;
      if(fileread(l->libnum,k.fname,1,&f))found(l,&f,k.keyword);
      morekeys=keygetnext(l->libnum,&k);
    }
  } else {
    /* Slower search for regexp */
    
    morekeys=keygetfirst(l->libnum,&k);
    while(morekeys){
      char tmp[24];
      int len=strlen(k.keyword);
      strcpy(tmp,k.keyword);
      lcase(k.keyword);
      if(!k.approved||(k.klibnum!=l->libnum))break;
      if((len=re_search(regexp,tmp,len,0,len,NULL))>=0){
	if(fileread(l->libnum,k.fname,1,&f))found(l,&f,k.keyword);
      }
      morekeys=keygetnext(l->libnum,&k);
    }
  }
}


static void
search_anywhere(struct libidx *l,char *phterm)
{
  int morefiles;
  struct fileidx f;

  /* Ssslllooowww phonetic search */

  morefiles=filegetfirst(l->libnum,&f,1);
  while(morefiles){
    int matched=0;
    struct fileidx tmp;
    if(!f.approved || f.flibnum!=l->libnum)break;
    
    memcpy(&tmp,&f,sizeof(struct fileidx));
    
    /* First search the file record itself */
    
    if(strstr(phonetic(tmp.fname),phterm))matched=1;
    else if(strstr(phonetic(tmp.uploader),phterm))matched=1;
    else if(strstr(phonetic(tmp.summary),phterm))matched=1;
    else if(strstr(phonetic(tmp.description),phterm))matched=1;
    
    /* Have we found it? */
    
    if(matched){
      found(l,&f,NULL);
    } else {
      
      /* Nope, so do the keywords as well. */
      
      struct filekey k,tmp;
      int    morekeys;
      
      morekeys=keyfilefirst(l->libnum,f.fname,1,&k);
      while(morekeys){
	memcpy(&tmp,&k,sizeof(struct filekey));
	if(strstr(phonetic(tmp.keyword),phterm)){
	  matched=1;
	  break;
	}
	morekeys=keyfilenext(l->libnum,f.fname,1,&k);
      }
      if(matched)found(l,&f,k.keyword);
    }
    
    morefiles=filegetnext(l->libnum,&f);
  }
}


static void
os_search_anywhere(struct libidx *l,char *phterm)
{
  struct stat     st;
  char            fname[1024];
  DIR            *dp;
  struct dirent  *d;

  /* In OS-only libs, the only 'anywhere' we can look at is the filename */
    

  /* Open the library directory */
    
  if((dp=opendir(l->dir))==NULL){
    fatalsys("Unable to open library %s (directory: %s)",
	     l->fullname,l->dir);
  }

  while((d=readdir(dp))!=NULL){
    if(strstr(phonetic(d->d_name),phterm)){
      sprintf(fname,"%s/%s",l->dir,d->d_name);
      if(stat(fname,&st)==0) os_found(l,d->d_name,&st);
    }
  }
  
  closedir(dp);
}


static void
search_date(struct libidx *l)
{
  int morefiles;
  struct fileidx f;

  /* Quick Typhoon-based search for timestamps */

  morefiles=filegetoldest(l->libnum,searchtime,1,&f);
  while(morefiles){
    if(!f.approved || f.flibnum!=l->libnum || f.timestamp<searchtime)break;
    found(l,&f,NULL);
    morefiles=filegetnextoldest(l->libnum,&f);
  }
}


static void
os_search_date(struct libidx *l)
{
  struct stat     st;
  char            fname[1024];
  DIR            *dp;
  struct dirent  *d;

  /* Open the library directory */
    
  if((dp=opendir(l->dir))==NULL){
    fatalsys("Unable to open library %s (directory: %s)",
	     l->fullname,l->dir);
  }

  while((d=readdir(dp))!=NULL){
    sprintf(fname,"%s/%s",l->dir,d->d_name);
    if(stat(fname,&st))continue;
    if(st.st_mtime>=searchtime)os_found(l,d->d_name,&st);
  }
  
  closedir(dp);
}


static void
daemon_search()
{
  int   morelibs;

  if((resultfp=fopen(resultfname,"w"))==NULL){
    fatalsys("Search daemon couldn't create %s",resultfname);
  }

  daemoninfo.filecreated=1;
 
  morelibs=firstchild();
  while(morelibs>=0){
    struct libidx  l;

    if(!libreadnum(morelibs,&l)){
      fatal("Oops, library %d disappeared while searching!",
	    morelibs);
    }

    /* Check security */
    forcepasswordfail();
    if(getlibaccess(&l,ACC_ENTER)){
      switch(searchtype&SHF_TYPE){
      case SHF_FNAME:
	if(l.flags&LBF_OSDIR)os_search_fnames(&l);
	else search_fnames(&l);
	break;

      case SHF_KEYWORD:
	if((l.flags&LBF_OSDIR)==0)search_keywords(&l);
	break;

      case SHF_ANYWHERE:
	{
	  /* Turn the search key into a phonetic string */
	  char phterm[1024];
	  strcpy(phterm,searchfor);
	  phonetic(phterm);
	  if(l.flags&LBF_OSDIR)os_search_anywhere(&l,phterm);
	  else search_anywhere(&l,phterm);
	}
	break;
      case SHF_DAYCOUNT:
      case SHF_DATE:
	if(l.flags&LBF_OSDIR)os_search_date(&l);
	else search_date(&l);
	break;
      }
    }
    morelibs=nextchild();
  }

  fclose(resultfp);
  daemoninfo.daemondead=1;
  exit(0);			/* End of daemon's life */
}


static void
show_entry(int row, struct libidx *l, struct result *r)
{
  char tmp1[256], tmp2[256];

  tmp1[0]=tmp2[0]=0;
  sprintf(tmp2,"%s/%s",&(l->fullname[strlen(library.fullname)+1]),r->fname);
  if(tmp2[0]=='/')strcpy(tmp2,r->fname);
  if(strlen(tmp2)+strlen(r->keyword)>47){
    char *s=&tmp2[strlen(tmp2)+strlen(r->keyword)-44];
    sprintf(tmp1,"...%s",s);
  } else strcpy(tmp1,tmp2);
  
  prompt(SRTABL,row,r->keyword,strlen(r->keyword)?" ":"",
	 46-strlen(r->keyword)-(strlen(r->keyword)>0),
	 tmp1,r->summary);
}


static int
display_canned_page(int page)
{
  int i, oldlibnum=-1;
  struct libidx l;

  prompt(SRTABH);
  for(i=0;resultcache[i].fname[0];i++){
    if(oldlibnum!=resultcache[i].libnum){
      oldlibnum=resultcache[i].libnum;
      if(!libreadnum(resultcache[i].libnum,&l)){
	fatal("Unable to read library %d.",resultcache[i].libnum);
      }
    }
    show_entry(i+1,&l,&resultcache[i]);
  }
  prompt(SRTABF,page+1,NUMPAGES,daemoninfo.daemondead?"":getpfix(SRTABU,1));
  return i;
}


static void
wait_results(int page)
{
  int start=srlstln*page;
  int end=start+srlstln;
  int status;

  prompt(SRTABW);
  while(!daemoninfo.daemondead && daemoninfo.nummatches<end){
    usleep(100000);		/* Wait a bit */
    
    if(waitpid(daemonpid,&status,WNOHANG)==daemonpid){
      clsmsg(sysblk);
      initoutput();
      setmbk(msg);
      initinput();
      /*print("daemon died, %d matches, returning %d\n",
	daemoninfo.nummatches,daemoninfo.nummatches-start);*/
      break;
    }
  }
}


int
display_page(int page)
{
  int            start=srlstln*page;
  int            end=start+srlstln;
  int            i;
  int            oldlibnum=-1;
  int            numentries;
  struct libidx  l;

  /* Should we redisplay the same old page? */

  if(lastpage==page)return display_canned_page(page);


  /* Don't have a full page yet, wait for it */

  numentries=0;
  daemoninfo.nomore=1;
  if(daemoninfo.daemondead==0 && daemoninfo.nummatches<end)
    wait_results(page);
  numentries=min(srlstln,daemoninfo.nummatches-start);


  /* Check if daemon returned anything at all */

  if(page==0 && !daemoninfo.nummatches){
    prompt(SRDMNONE);
    return -1;
  }


  /* Oops, not found any entries for this page */

  if(!numentries){
    prompt(SRDMNM);
    daemoninfo.nomore=1;
    return numentries;
  }

  /* Seek to the right place in the results file */

  if(fseek(resultfp,start*sizeof(struct result),SEEK_SET)<0){
    fatal("Oops, unable to fseek() results file %s",
	  resultfname);
  }

  /* Prepare the results cache */
  
  bzero(resultcache,sizeof(srlstln*sizeof(struct result)));
  numresultsincache=0;


  /* Now print the table */

  prompt(SRTABH);
  for(i=0;i<numentries;i++){
    struct result r;
    

    /* Read the result entry */

    if(!fread(&r,sizeof(r),1,resultfp)){
      fatalsys("Unable to read from file %s.",resultfname);
    }


    /* Can the entry for later */

    memcpy(&resultcache[i],&r,sizeof(r));
    numresultsincache++;
    

    /* Read the new library, if necessary */

    if(oldlibnum!=r.libnum){
      oldlibnum=r.libnum;
      if(!libreadnum(r.libnum,&l)){
	fatal("Unable to read library %d.",r.libnum);
      }
    }


    /* Print the entry */

    show_entry(i+1,&l,&r);
  }

  prompt(SRTABF,page+1,NUMPAGES,daemoninfo.daemondead?"":getpfix(SRTABU,1));

  return numentries;
}


static int
get_navigator_command(char *opt, int current_page, int shortmenu)
{
  int shownmenu=shortmenu;
  char c;

  for(;;){
    lastresult=0;
    if((c=morcnc())!=0){
      if(sameas(nxtcmd,"X"))return 0;
      c=cncchr();
      shownmenu=1;
    } else {
      if(!shownmenu){
	int res=display_page(current_page);
	if(res<0) return 0;
	if(res==0 && daemoninfo.nomore){
	  *opt='E';		/* [E]nd */
	  return 1;
	}
	prompt(SRMNU,numresultsincache);
	shownmenu=1;
      } else prompt(SRSMNU,numresultsincache);
      getinput(0);
      bgncnc();
      c=cncchr();
    }
    if (!margc) {
      endcnc();
      continue;
    }
    if(isX(margv[0])){
      return 0;
    } else if(margc && (c=='?'||sameas(margv[0],"?"))){
      prompt(SRMNHLP);
      shownmenu=0;
      continue;
    } else if(strchr("FBNPI",c)){
      *opt=c;
      return 1;
    } else if(isdigit(c)){
      int num;
      nxtcmd--;
      num=cncint();
      if(num<1||num>numresultsincache){
	prompt(SRMNRN,numresultsincache);
	endcnc();
	continue;
      }
      *opt='D';
      return -num;
    } else {
      prompt(SRMNER);
      endcnc();
      continue;
    }
  }
  return 0;
}


static void
seeinfo()
{
  struct libidx  l;
  struct fileidx f;
  int fileno;

  if(!getnumber(&fileno,SRMNINA,1,
		min(srlstln,numresultsincache),
		SRMNINR,0,0))return;
  else fileno--;


  /* Read the library */

  if(!libreadnum(resultcache[fileno].libnum,&l)){
    fatal("Floor Yanked Under From Feet error, library %d.",
	  resultcache[fileno].libnum);
  }


  /* Read the file */

  if(!fileread(resultcache[fileno].libnum,
	       resultcache[fileno].fname,1,&f)){
    fatal("Floor Yanked Under From Feet error, file %s/%s",
	  l.fullname,resultcache[fileno].fname);
  }

  fileinfo(&l,&f);
}


static void
download_numbered_file(int n)
{
  struct result *file=&resultcache[n-1];
  struct libidx l;

  if(!libreadnum(file->libnum,&l)){
    endcnc();
    return;
  }
  prompt(SRLIBJMP,file->fname,l.fullname);

  if(!getlibaccess(&library,ACC_DOWNLOAD)){
    prompt(DNLNAX);
    return;
  }

  memcpy(&l,&library,sizeof(l));
  enterlib(file->libnum,1);
  download(file->fname);
  memcpy(&l,&library,sizeof(l));
}


static int
browse_results()
{
  int current_page=0;
  int shortmenu=0;
  int num;

  for(;;){
    char opt;

    if((num=get_navigator_command(&opt,current_page,shortmenu))==0)return 0;
    switch(opt){
    case 'E':			/* [E]nd */
      current_page--;
      shortmenu=1;
      break;
    case 'F':
      if(daemoninfo.daemondead&&
	 current_page+1>=NUMPAGES){
	prompt(SRMNEN);
	shortmenu=0;
	continue;
      } else {
	current_page++;
	shortmenu=0;
	continue;
      }
    case 'B':
      if(current_page>0){
	current_page--;
	shortmenu=0;
	continue;
      } else {
	prompt(SRMNBG);
	endcnc();
	continue;
      }
    case 'N':
      return 1;
    case 'D':
      download_numbered_file(-num);
      break;
    case 'I':
      seeinfo(current_page);
      shortmenu=1;
      break;
    case 'P':
      {
	int pageno;
	if(getnumber(&pageno,SRMNJMA,1,NUMPAGES,SRMNJMR,0,0)){
	  shortmenu=0;
	  current_page=pageno-1;
	} else shortmenu=0;
	break;
      }
    }
  }

  return 0;
}


static int
search_client()
{ 
  int status, res;


  /* Wait for the results file to appear. Stop if daemon died before
     creating the file */

  while(!daemoninfo.daemondead&&!daemoninfo.filecreated){
    usleep(100000);
    if(waitpid(daemonpid,&status,WNOHANG)==daemonpid){
      daemoninfo.daemondead=1;
      break;
    }
  }

  if(daemoninfo.daemondead){
    clsmsg(sysblk);
    initoutput();
    initinput();
    setmbk(msg);
  }
  

  /* Early results */

  if(daemoninfo.daemondead&&!daemoninfo.filecreated){
    prompt(SRDMER1);
    endcnc();
    return 0;
  } else if(daemoninfo.daemondead&&!daemoninfo.nummatches){
    prompt(SRDMNONE);
    endcnc();
    return 0;
  }

  /* Open the file */

  if((resultfp=fopen(resultfname,"r"))==NULL){
    fatalsys("Unable to open %s",resultfname);
  }


  /* Browse through the results */

  res=browse_results();


  /* Clean-up */

  unlink(resultfname);
  waitpid(0,&status,WNOHANG);

  return res;
}


static int
start_search()
{
  sprintf(resultfname,TMPDIR"/filesrch.%d",getpid());

  /* Prepare the results cache */
  if(resultcache==NULL)resultcache=alcmem(srlstln*sizeof(struct result));
  lastpage=-1;

  bzero(&daemoninfo,sizeof(struct _daemoninfo));

  daemonpid=fork();

  if(daemonpid==0){		/* We're the daemon */
    close(0);
    close(1);
    close(2);
    doneoutput();		/* Stop being a BBS module */
    doneinput();
    donesignals();
    noerrormessages();		/* Don't print messages */
    settimeout(24*60);		/* Don't timeout */
    daemon_search();
  } else if(daemonpid<0){
    fatal("Unable to spawn search daemon.");
  }

  regpid(thisuseronl.channel);
  yeserrormessages();
  resetinactivity();
  return search_client();	/* We're the spawner */
}


void
filesearch()
{
  for(;;){
    char *tmp;
    if((tmp=getsearchterm())==NULL)return;
    if(!grokterm(tmp)){
      endcnc();
      continue;
    }
    get_children();
    if(!start_search())break;
  }
}
