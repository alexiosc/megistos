/*****************************************************************************\
 **                                                                         **
 **  FILE:     cleanup.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, March 95                                                  **
 **  PURPOSE:  Cleanup part of the statistics module.                       **
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
 * Revision 1.2  2001/04/16 21:56:33  alexios
 * Completed 0.99.2 API, dragged all source code to that level (not as easy as
 * it sounds).
 *
 * Revision 0.4  1998/12/27 16:09:37  alexios
 * Added autoconf support.
 *
 * Revision 0.3  1997/11/06 20:05:23  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/11/05 11:12:54  alexios
 * Changed calls to audit() so they take advantage of the new
 * auditing scheme.
 *
 * Revision 0.1  1997/08/28 11:07:38  alexios
 * First registered revision. Adequate.
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
#define WANT_CTYPE_H 1
#define WANT_STRINGS_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "mbk_stats.h"
#include "stats.h"


void
init()
{
  char fname[256];
  FILE *fp;
  int cof=cofdate(today());

  printf("Statistics Cleanup\n\n");

  sprintf(fname,"%s/%s",STATDIR,DAYSSINCEFILE);
  if((fp=fopen(fname,"r"))!=NULL){
    int i;
    if(fscanf(fp,"%d\n",&i)==1){
      dayssince=cof-i;
      if(dayssince<0)dayssince=1;
    }
    fclose(fp);
  }
  if((fp=fopen(fname,"w"))!=NULL){
    fprintf(fp,"%d\n",cof);
    fclose(fp);
  }
  chmod(fname,0660);
  printf("Days since last cleanup: %d\n",dayssince);
  
  sprintf(oldstatsdir,"%s/%d",STATDIR,(int)tdyear(today()));
  mkdir(oldstatsdir,0750);
  sprintf(everdir,"%s/EVER",STATDIR);
  mkdir(everdir,0750);
}


void
mergedaystats(char *dir, char *name)
{
  char fname1[256], fname2[256];
  FILE *in1, *in2, *out;
  int numdays,i;

  sprintf(fname1,"%s/tmp%d~",dir,getpid());
  sprintf(fname2,"%s/%s",dir,name);
  if((out=fopen(fname1,"w"))==NULL)return;
  if((in1=fopen(DAYSTATFILE,"a+"))==NULL)return;
  if((in2=fopen(fname2,"a+"))==NULL)return;
  rewind(in1);
  rewind(in2);

  printf("  Generating %s...",fname2);
  
  if(fscanf(in2,"%d\n",&numdays)!=1)numdays=0;
  numdays+=dayssince;
  fprintf(out,"%d\n",numdays);
  
  for(i=0;i<24;i++){
    int crd1, crd2, min1, min2;
    
    crd1=crd2=min1=min2=0;
    fscanf(in1,"%d %d\n",&crd1,&min1);
    fscanf(in2,"%d %d\n",&crd2,&min2);
    fprintf(out,"%d %d\n",crd1+crd2,min1+min2);
  }
  fclose(in1);
  fclose(in2);
  fclose(out);
  rename(fname1,fname2);

  if((!getuid())||(!getgid())){
    sprintf(fname1,"chown bbs.bbs %s >&/dev/null",fname2);
    system(fname1);
  }

  printf(" Done.\n");
}


int
ttycmp(const void *p1, const void *p2)
{
  const struct ttystats *t1=p1, *t2=p2;
  return t1->channel - t2->channel;
}


void
mergettystats(char *dir, char *name)
{
  FILE            *in1, *in2, *out;
  char            fname1[256],fname2[256];
  struct ttystats ttystats[MAXTTYS];
  int             numttystats=0;
  int             numdays=0,i;

  sprintf(fname1,"%s/tmp%d~",dir,getpid());
  sprintf(fname2,"%s/%s",dir,name);
  if((out=fopen(fname1,"w"))==NULL)return;
  if((in1=fopen(TTYSTATFILE,"a+"))==NULL)return;
  if((in2=fopen(fname2,"a+"))==NULL)return;
  rewind(in1);
  rewind(in2);
  
  printf("  Generating %s...",fname2);

  if(fscanf(in2,"%d\n",&numdays)!=1)numdays=0;
  numdays+=dayssince;
  fprintf(out,"%d\n",numdays);
  
  while(!feof(in1)){
    struct ttystats tty;
    int i;

    memset(&tty,0,sizeof(tty));
    i=fscanf(in1,"%s %x %d %d %d\n",tty.name,&tty.channel,
		 &tty.credits,&tty.minutes,&tty.calls);
    if(numttystats>=MAXTTYS)break;
    if(i==5){
      memcpy(&ttystats[numttystats],&tty,sizeof(struct ttystats));
      numttystats++;
    } else break;
  }
  fclose(in1);

  while(!feof(in2)){
    struct ttystats tty;
    int i, j;

    memset(&tty,0,sizeof(tty));
    i=fscanf(in2,"%s %x %d %d %d\n",tty.name,&tty.channel,
	     &tty.credits,&tty.minutes,&tty.calls);
    if(i==5){
      int add=1;
      if(numttystats>0){
	for(j=0;j<numttystats;j++)if(!strcmp(ttystats[j].name,tty.name)){
	  ttystats[j].credits+=tty.credits;
	  ttystats[j].minutes+=tty.minutes;
	  ttystats[j].calls+=tty.calls;
	  add=0;
	  break;
	}
      }
      if(add){
	memcpy(&ttystats[numttystats],&tty,sizeof(struct ttystats));
	numttystats++;
      }
      if(numttystats>=MAXTTYS)break;
    } else break;
  }
  fclose(in2);

  qsort(ttystats,numttystats,sizeof(struct ttystats),ttycmp);
  for(i=0;i<numttystats;i++){
    fprintf(out,"%s %x %d %d %d\n",ttystats[i].name,ttystats[i].channel,
	    ttystats[i].credits,ttystats[i].minutes,ttystats[i].calls);
  }
  fclose(out);
  rename(fname1,fname2);
  if((!getuid())||(!getgid())){
    sprintf(fname1,"chown bbs.bbs %s >&/dev/null",fname2);
    system(fname1);
  }

  printf(" Done.\n");
}


int
baudcmp(const void *p1, const void *p2)
{
  const struct baudstats *t1=p1, *t2=p2;
  return t1->baud - t2->baud;
}


void
mergebaudstats(char *dir, char *name)
{
  FILE             *in1, *in2, *out;
  char             fname1[256],fname2[256];
  struct baudstats baudstats[MAXBAUDS];
  int              numbaudstats=0;
  int              numdays=0,i;

  sprintf(fname1,"%s/tmp%d~",dir,getpid());
  sprintf(fname2,"%s/%s",dir,name);
  if((out=fopen(fname1,"w"))==NULL)return;
  if((in1=fopen(BAUDSTATFILE,"a+"))==NULL)return;
  if((in2=fopen(fname2,"a+"))==NULL)return;
  rewind(in1);
  rewind(in2);
  
  printf("  Generating %s...",fname2);

  if(fscanf(in2,"%d\n",&numdays)!=1)numdays=0;
  numdays+=dayssince;
  fprintf(out,"%d\n",numdays);
  
  while(!feof(in1)){
    struct baudstats baud;
    int i;

    memset(&baud,0,sizeof(baud));
    i=fscanf(in1,"%d %d %d %d\n",&baud.baud,
	     &baud.credits,&baud.minutes,&baud.calls);
    if(numbaudstats>=MAXBAUDS)break;
    if(i==4){
      memcpy(&baudstats[numbaudstats],&baud,sizeof(struct baudstats));
      numbaudstats++;
    }
    else break;
  }
  fclose(in1);

  while(!feof(in2)){
    struct baudstats baud;
    int i,j;

    memset(&baud,0,sizeof(baud));
    i=fscanf(in2,"%d %d %d %d\n",&baud.baud,
		 &baud.credits,&baud.minutes,&baud.calls);
    
    if(i==4){
      int add=1;
      for(j=0;j<numbaudstats;j++)if(baudstats[j].baud==baud.baud){
	baudstats[j].credits+=baud.credits;
	baudstats[j].minutes+=baud.minutes;
	baudstats[j].calls+=baud.calls;
	add=0;
	break;
      }
      if(add){
	memcpy(&baudstats[numbaudstats],&baud,sizeof(struct baudstats));
	numbaudstats++;
      }
      if(numbaudstats>=MAXBAUDS)break;
    } else break;
  }
  fclose(in2);
  
  qsort(baudstats,numbaudstats,sizeof(struct baudstats),baudcmp);
  for(i=0;i<numbaudstats;i++){
    fprintf(out,"%d %d %d %d\n",baudstats[i].baud,
	    baudstats[i].credits,baudstats[i].minutes,baudstats[i].calls);
  }
  fclose(out);
  rename(fname1,fname2);
  if((!getuid())||(!getgid())){
    sprintf(fname1,"chown bbs.bbs %s >&/dev/null",fname2);
    system(fname1);
  }

  printf(" Done.\n");
}


int
clscmp(const void *p1, const void *p2)
{
  const struct clsstats *t1=p1, *t2=p2;
  return strcmp(t1->name,t2->name);
}


void
mergeclsstats(char *dir, char *name)
{
  FILE             *in1, *in2, *out;
  char             fname1[256],fname2[256];
  struct clsstats  clsstats[MAXCLSS];
  int              numclsstats=0;
  int              numdays=0,i;

  sprintf(fname1,"%s/tmp%d~",dir,getpid());
  sprintf(fname2,"%s/%s",dir,name);
  if((out=fopen(fname1,"w"))==NULL)return;
  if((in1=fopen(CLSSTATFILE,"a+"))==NULL)return;
  if((in2=fopen(fname2,"a+"))==NULL)return;
  rewind(in1);
  rewind(in2);
  
  printf("  Generating %s...",fname2);

  if(fscanf(in2,"%d\n",&numdays)!=1)numdays=0;
  numdays+=dayssince;
  fprintf(out,"%d\n",numdays);
  
  while(!feof(in1)){
    struct clsstats cls;
    int i;

    memset(&cls,0,sizeof(struct clsstats));
    i=fscanf(in1,"%s %d %d\n",cls.name,&cls.credits,&cls.minutes);
    if(numclsstats>=MAXCLSS)break;
    if(i==3){
      memcpy(&clsstats[numclsstats],&cls,sizeof(struct clsstats));
      numclsstats++;
    } else break;
  }
  fclose(in1);
  
  while(!feof(in2)){
    struct clsstats cls;
    int i,j;

    memset(&cls,0,sizeof(struct clsstats));
    i=fscanf(in2,"%s %d %d\n",cls.name,&cls.credits,&cls.minutes);

    if(i==3){
      int add=1;
      for(j=0;j<numclsstats;j++)if(!strcmp(clsstats[j].name,cls.name)){
	clsstats[j].credits+=cls.credits;
	clsstats[j].minutes+=cls.minutes;
	add=0;
	break;
      }
      if(add){
	memcpy(&clsstats[numclsstats],&cls,sizeof(struct clsstats));
	numclsstats++;
      }
      if(numclsstats>=MAXCLSS)break;
    } else break;
  }
  fclose(in2);

  qsort(clsstats,numclsstats,sizeof(struct clsstats),clscmp);
  for(i=0;i<numclsstats;i++){
    fprintf(out,"%s %d %d\n",clsstats[i].name,
	    clsstats[i].credits,clsstats[i].minutes);
  }
  fclose(out);
  rename(fname1,fname2);

  if((!getuid())||(!getgid())){
    sprintf(fname1,"chown bbs.bbs %s >&/dev/null",fname2);
    system(fname1);
  }
  printf(" Done.\n");
}


int
modcmp(const void *p1, const void *p2)
{
  const struct modstats *t1=p1, *t2=p2;
  return strcmp(t1->name,t2->name);
}


void
mergemodstats(char *dir, char *name)
{
  FILE             *in1, *in2, *out;
  char             fname1[256],fname2[256];
  struct modstats  modstats[MAXMODS];
  int              nummodstats=0;
  int              numdays=0,i;

  sprintf(fname1,"%s/tmp%d~",dir,getpid());
  sprintf(fname2,"%s/%s",dir,name);
  if((out=fopen(fname1,"w"))==NULL)return;
  if((in1=fopen(MODSTATFILE,"a+"))==NULL)return;
  if((in2=fopen(fname2,"a+"))==NULL)return;
  rewind(in1);
  rewind(in2);
  
  printf("  Generating %s...",fname2);

  if(fscanf(in2,"%d\n",&numdays)!=1)numdays=0;
  numdays+=dayssince;
  fprintf(out,"%d\n",numdays);
  
  while(!feof(in1)){
    struct modstats mod;
    char            line[1024],*cp;
    int             len,ptr,i;
    
    memset(&mod,0,sizeof(mod));

    if(nummodstats>=MAXMODS)break;
    if(!fgets(line,sizeof(line),in1))break;
    if(!sscanf(line,"%d %n",&len,&ptr))break;

    cp=&line[ptr];
    cp[len]=0;
    strncpy(mod.name,cp,sizeof(mod.name));
    cp+=len+1;

    i=sscanf(cp,"%d %d\n",&mod.credits,&mod.minutes);
    if(i==2){
      memcpy(&modstats[nummodstats],&mod,sizeof(struct modstats));
      nummodstats++;
    } else break;
  }
  fclose(in1);
  
  while(!feof(in2)){
    struct modstats mod;
    char            line[1024],*cp;
    int             len,ptr,i;
    
    memset(&mod,0,sizeof(mod));
    if(nummodstats>=MAXMODS)break;
    if(!fgets(line,sizeof(line),in2))break;
    if(!sscanf(line,"%d %n",&len,&ptr))break;
    
    cp=&line[ptr];
    cp[len]=0;
    strncpy(mod.name,cp,sizeof(mod.name));
    cp+=len+1;
    
    i=sscanf(cp,"%d %d\n",&mod.credits,&mod.minutes);
    if(i==2){
      int j,add=1;
      for(j=0;j<nummodstats;j++)if(!strcmp(modstats[j].name,mod.name)){
	modstats[j].credits+=mod.credits;
	modstats[j].minutes+=mod.minutes;
	add=0;
	break;
      }
      if(add){
	memcpy(&modstats[nummodstats],&mod,sizeof(struct modstats));
	nummodstats++;
      }
    } else break;
  }
  fclose(in2);
  
  qsort(modstats,nummodstats,sizeof(struct modstats),modcmp);
  for(i=0;i<nummodstats;i++){
    fprintf(out,"%d %s %d %d\n",strlen(modstats[i].name),
	    modstats[i].name,modstats[i].credits,modstats[i].minutes);
  }
  fclose(out);
  rename(fname1,fname2);

  if((!getuid())||(!getgid())){
    sprintf(fname1,"chown bbs.bbs %s >&/dev/null",fname2);
    system(fname1);
  }
  printf(" Done.\n");
}


void
clear(char *fname)
{
  FILE *fp=fopen(fname,"w");
  fclose(fp);
}


void
getstats()
{
  char fname[256];

  audit_setfile(CLNUPAUDITFILE);
  audit("CLEANUP",AUDIT(STATCUB),dayssince);

  printf("\nCalculating daily usage statistics.\n");
  sprintf(fname,"daystats.month-%02ld",tdmonth(today())+1);
  mergedaystats(oldstatsdir,fname);
  mergedaystats(oldstatsdir,"daystats");
  mergedaystats(everdir,"daystats");
  clear(DAYSTATFILE);

  printf("\nCalculating channel usage statistics.\n");
  sprintf(fname,"ttystats.month-%02ld",tdmonth(today())+1);
  mergettystats(oldstatsdir,fname);
  mergettystats(oldstatsdir,"ttystats");
  mergettystats(everdir,"ttystats");
  clear(TTYSTATFILE);

  printf("\nCalculating connection speed statistics.\n");
  sprintf(fname,"baudstats.month-%02ld",tdmonth(today())+1);
  mergebaudstats(oldstatsdir,fname);
  mergebaudstats(oldstatsdir,"baudstats");
  mergebaudstats(everdir,"baudstats");
  clear(BAUDSTATFILE);

  printf("\nCalculating user class usage statistics.\n");
  sprintf(fname,"clsstats.month-%02ld",tdmonth(today())+1);
  mergeclsstats(oldstatsdir,fname);
  mergeclsstats(oldstatsdir,"clsstats");
  mergeclsstats(everdir,"clsstats");
  clear(CLSSTATFILE);

  printf("\nCalculating module usage statistics.\n");
  sprintf(fname,"modstats.month-%02ld",tdmonth(today())+1);
  mergemodstats(oldstatsdir,fname);
  mergemodstats(oldstatsdir,"modstats");
  mergemodstats(everdir,"modstats");
  clear(MODSTATFILE);

  printf("\nDone generating statistics!\n\n");

  audit("CLEANUP",AUDIT(STATCUE));
  audit_resetfile();
}


void
done()
{
}
