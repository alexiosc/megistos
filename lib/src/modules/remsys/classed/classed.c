/*****************************************************************************\
 **                                                                         **
 **  FILE:     classed.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, June 94, version 1.00                                     **
 **  PURPOSE:  User accounting class editor                                 **
 **  NOTES:    Files:-                                                      **
 **            /bbs/usr/.class: Class database (binary sequential)          **
 **            /bbs/mbk/classed.mbk: Message block                          **
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
 * Revision 1.1  2001/04/16 14:48:32  alexios
 * Initial revision
 *
 * Revision 1.7  1999/07/18 21:11:35  alexios
 * Changed a few fatal() calls to fatalsys().
 *
 * Revision 1.6  1998/12/27 14:43:40  alexios
 * Added autoconf support.
 *
 * Revision 1.5  1998/08/11 09:59:28  alexios
 * No changes.
 *
 * Revision 1.4  1998/08/11 09:59:13  alexios
 * No changes.
 *
 * Revision 1.3  1998/07/24 10:06:29  alexios
 * Upgraded to version 0.6 of library.
 *
 * Revision 1.2  1997/11/06 20:08:20  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 1.1  1997/08/26 15:43:05  alexios
 * Fixed minor compiler warning.
 *
 * Revision 1.0  1997/08/26 15:34:06  alexios
 * Initial revision
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif



#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_UNISTD_H 1
#define WANT_STRING_H 1
#define WANT_CTYPE_H 1
#define WANT_LIMITS_H 1
#define WANT_DIRENT_H 1
#include <bbsinclude.h>

#include "bbs.h"

#include "mbk_classed.h"

#define NDEL      {'D','E','L','E','T','E','D',0,0,0}
#define CLASSDEL  {NDEL,NDEL,-1,NDEL,-1,NDEL,NDEL,0,0,0,0,0,CF_LOCKOUT}
#define AVONLY(s) (strcmp(classes[i].name,s)?s:"N/A")


promptblk *msg;
classrec  classes[MAXCLASS];
int       numclasses;


int classcompare (const void *r1, const void *r2)
{
  const classrec *a=r1, *b=r2;
  return strcmp(a->name,b->name);
}


static void
readclasses()
{
  FILE *fp;
  classrec classdel=CLASSDEL;

  if((fp=fopen(CLASSFILE,"r"))!=NULL){
    numclasses=fread(classes,sizeof(classrec),MAXCLASS,fp);
  } else numclasses=0;
  fclose(fp);
  if(!numclasses)memcpy(&classes[numclasses++],&classdel,sizeof(classrec));
}


void
saveclasses()
{
  FILE *fp;

  qsort(classes,numclasses,sizeof(classrec),classcompare);
  if((fp=fopen(CLASSFILE,"w"))==NULL){
    logerrorsys("Failed to create %s",CLASSFILE);
    prompt(IOERROR);
    return;
  }
  if(fwrite(classes,sizeof(classrec),numclasses,fp)!=numclasses){
    logerrorsys("Failed to write %s",CLASSFILE);
    prompt(IOERROR);
    return;
  }
  fclose(fp);
}


void
listclasschanges()
{
  int i;

  if(!numclasses){
    prompt(NOCLSES,NULL);
    return;
  }
  prompt(CCHLHDR,NULL);
  for(i=0;i<numclasses;i++){
    char s1[16]={0}, s2[16]={0};

    if(classes[i].nadays!=-1)sprintf(s1,"%d",classes[i].nadays);
    if(classes[i].ardays!=-1)sprintf(s2,"%d",classes[i].ardays);

    sprintf(outbuf,getmsg(CCHLTAB),classes[i].name,
	    AVONLY(classes[i].notaround),s1,
	    AVONLY(classes[i].around),s2,
	    AVONLY(classes[i].nocreds),
	    AVONLY(classes[i].credpost));
    print(outbuf,NULL);
  }
  prompt(CCHLFTR,NULL);
}


void
listclasses()
{
  int i;

  if(!numclasses){
    prompt(NOCLSES,NULL);
    return;
  }
  prompt(CLSLHDR,NULL);
  for(i=0;i<numclasses;i++){
    char s1[16]={0}, s2[16]={0};

    if(classes[i].limpercall!=-1)sprintf(s1,"%d",classes[i].limpercall);
    if(classes[i].limperday!=-1)sprintf(s2,"%d",classes[i].limperday);

    sprintf(outbuf,getmsg(CLSLTAB),classes[i].name,
	    s1,s2,
	    classes[i].crdperday,
	    classes[i].crdperweek,
	    classes[i].crdpermonth,
	    classes[i].flags&CF_NOCHRGE?'X':'-',
	    classes[i].flags&CF_LINUX?'X':'-',
	    classes[i].flags&CF_LOCKOUT?'X':'-',
	    classes[i].flags&CF_CRDXFER?'X':'-');
    print(outbuf,NULL);
  }
  prompt(CLSLFTR,NULL);
}


int
getclassname(class,msg,existing,err,def,defval)
char *class,*defval;
int  msg,existing,err,def;
{
  char newclass[10];
  int i, ok=0;
  while(!ok){
    memset(newclass,0,10);
    if(morcnc())strncpy(newclass,cncword(),10);
    else {
      prompt(msg,NULL);
      if(def){
	sprintf(outbuf,getmsg(DEFSTR),defval);
	print(outbuf,NULL);
      }
      getinput(0);
      if(margc)strncpy(newclass,margv[0],10);
      else if(def && !reprompt){
	strncpy(class,defval,10);
	return 1;
      } else endcnc();
    }
    if(sameas(newclass,"x"))return 0;
    if(newclass[0]=='?'){
      newclass[0]=0;
      listclasses();
      continue;
    }
    if(!newclass[0]){
      endcnc();
      continue;
    }
    ok=(existing==0);
    for(i=0;newclass[i];i++)newclass[i]=toupper(newclass[i]);
    if(existing==-1){
      strncpy(class,newclass,10);
      return 1;
    }
    for(i=0;i<numclasses;i++){
      if(sameas(newclass,classes[i].name)){
	if(existing) ok=1;
	else {
	  endcnc();
	  sprintf(outbuf,getmsg(err),newclass);
	  print(outbuf,NULL);
	  ok=0;
	  break;
	}
      }
    }
    if(existing && !ok){
      sprintf(outbuf,getmsg(err),newclass);
      print(outbuf,NULL);
      endcnc();
    }
  }
  strncpy(class,newclass,10);
  return 1;
}


int
keyed(long *k)
{
  long keys[KEYLENGTH];
  int shown=0;
  int key;
  char c;

  memcpy(keys,k,KEYLENGTH*sizeof(long));
  prompt(KEYPRO,NULL);
  for(;;){
    if(!shown){
      char s1[65]={0},s2[65]={0};
      int i;
      
      for(i=0;i<64;i++){
	s1[i]=(keys[i/32]&(1<<(i%32)))?'X':'-';
	s2[i]=(keys[(i+64)/32]&(1<<((i+64)%32)))?'X':'-';
      }
      prompt(KEYED,s1,s2,NULL);
      shown=1;
    }
    
    key=-1;
    for(;;){
      if((c=morcnc())!=0){
	if(toupper(c)=='X')return 0;
	key=cncint();
      } else {
	prompt(KEYASK,NULL);
	getinput(0);
	key=atoi(margv[0]);
	if(!margc || reprompt){
	  endcnc();
	  continue;
	} else if(isX(margv[0]))return 0;
	else if(sameas(margv[0],"OK")){
	  memcpy(k,keys,KEYLENGTH*sizeof(long));
	  return 1;
	}else if(sameas(margv[0],"ON")){
	  int i;
	  for(i=0;i<KEYLENGTH;i++)keys[i]=-1L;
	  shown=0;
	  key=-1;
	  break;
	}else if(sameas(margv[0],"OFF")){
	  int i;
	  for(i=0;i<KEYLENGTH;i++)keys[i]=0L;
	  shown=0;
	  key=-1;
	  break;
	}else if(sameas(margv[0],"?")){
	  key=-1;
	  shown=0;
	  break;
	}
      }
      if(key<1 || key>128){
	endcnc();
	prompt(NUMERR,1,128,NULL);
      }else break;
    }
    
    if(key>=1 && key<=128){
      key--;
      keys[key/32]^=(1<<(key%32));
      prompt(KEYON+((keys[key/32]&(1<<(key%32)))==0),key+1,NULL);
    }
  }
}


int
addclass()
{
  char name[10];
  classrec *newclass;
  int i;

  if(numclasses>=MAXCLASS){
    sprintf(outbuf,getmsg(TOOMANY),MAXCLASS);
    print(outbuf,NULL);
    return 0;
  }
  if(!getclassname(name,ADDCNAME,0,ALRDYEX,0,0))return 0;
  newclass=&classes[numclasses++];
  memset(newclass,0,sizeof(classrec));
  strncpy(newclass->name,name,10);
  if(!getnumber(&newclass->limpercall,ADDCQ1,-1,1500,NUMERR,0,0))return 1;
  if(!getnumber(&newclass->limperday,ADDCQ2,-1,1500,NUMERR,0,0))return 1;
  if(!getnumber(&newclass->crdperday,ADDCQ3,0,INT_MAX,NUMERR,0,0))return 1;
  if(!getnumber(&newclass->crdperweek,ADDCQ3A,INT_MIN,INT_MAX,NUMERR,0,0))return 1;
  if(!getnumber(&newclass->crdpermonth,ADDCQ3B,INT_MIN,INT_MAX,NUMERR,0,0))return 1;
  if(!getclassname(newclass->nocreds,ADDCQ4A,1,UNKCLSS,0,0))return 1;

  if (!getclassname(newclass->credpost,ADDCQ4B,1,UNKCLSS,0,0))return 1;

  if(!getnumber(&newclass->nadays,ADDCQ5,-1,0x7fffffff,NUMERR,0,0))return 1;
  if(newclass->nadays!=-1){
    if (!getclassname(newclass->notaround,ADDWHCL,1,UNKCLSS,0,0))return 1;
  } else {
    strcpy(newclass->notaround,newclass->name);
  }

  if(!getnumber(&newclass->ardays,ADDCQ6,-1,0x7fffffff,NUMERR,0,0))return 1;
  if(newclass->ardays!=-1){
    if (!getclassname(newclass->around,ADDWHCL,1,UNKCLSS,0,0))return 1;
  } else {
    strcpy(newclass->around,newclass->name);
  }

  if(!getbool(&i,ADDCQ7,BOOLERR,0,0))return 1;
  if(i)newclass->flags|=CF_NOCHRGE;
  if(!getbool(&i,ADDCQ8,BOOLERR,0,0))return 1;
  if(i)newclass->flags|=CF_LINUX;
  if(!getbool(&i,ADDCQ9,BOOLERR,0,0))return 1;
  if(i)newclass->flags|=CF_LOCKOUT;
  if(!getbool(&i,ADDCQ10,BOOLERR,0,0))return 1;
  if(!i)newclass->flags|=CF_CRDXFER;

  if(!keyed(newclass->keys))return 1;
  return 0;
}


void
delclass()
{
  char name[10];
  int i;

  if(!numclasses){
    prompt(NOCLSES,NULL);
    return;
  }
  if(!getclassname(name,DELCNAME,1,UNKCLSS,0,0))return;
  if(!getbool(&i,DELCCNF,BOOLERR,0,0))return;
  if(!i)return;
  
  for(i=0;i<numclasses;i++)if(sameas(name,classes[i].name))break;
  if(i+1<numclasses){
    memmove(&classes[i],&classes[i+1],sizeof(classrec)*(numclasses-(i+1)));
  }
  numclasses--;
  prompt(DELWARN,NULL);
}


void
listkeys(long *keys){
  long j;
  int i,first=-1,count=0;

  prompt(VIEWKY,NULL);
  for(i=0;i<(32*KEYLENGTH);i++){
    j=keys[i/32]&(1<<(i%32));
    count+=j;
    if(!j){
      if(first!=-1){
	if(first<(i-1))prompt(VIEWKY2,first+1,i,NULL);
	if(first==(i-1))prompt(VIEWKY1,first+1,NULL);
	first=-1;
      }
    }else{
      if(first==-1)first=i;
    }
  }
  if(first!=-1){
    if(first<(i-1))prompt(VIEWKY2,first+1,i,NULL);
    if(first==(i-1))prompt(VIEWKY1,first+1,NULL);
  }
  if(!count)prompt(VIEWKY0,NULL);
  else prompt(VIEWKYE,NULL);
}
       

void
viewclass()
{
  char name[10];
  int i;

  if(!numclasses){
    prompt(NOCLSES,NULL);
    return;
  }
  if(!getclassname(name,VEWCNAME,1,UNKCLSS,0,0))return;
  
  for(i=0;i<numclasses;i++)if(sameas(name,classes[i].name))break;

  sprintf(outbuf,getmsg(VIEWC1),classes[i].name);
  print(outbuf,NULL);
  if(classes[i].nadays>=0){
    sprintf(outbuf,getmsg(VIEWC2),classes[i].nadays,
	    getpfix(DAYSNG,classes[i].nadays),
	    classes[i].notaround);
    print(outbuf,NULL);
  }
  if(classes[i].ardays>=0){
    sprintf(outbuf,getmsg(VIEWC3),classes[i].ardays,
	    getpfix(DAYSNG,classes[i].ardays),
	    classes[i].around);
    print(outbuf,NULL);
  }
  prompt(VIEWC4A,classes[i].nocreds);
  prompt(VIEWC4C,classes[i].credpost);
  sprintf(outbuf,getmsg(VIEWC5),classes[i].limpercall,
	  getpfix(MINSNG,classes[i].limpercall));
  print(outbuf,NULL);

  sprintf(outbuf,getmsg(VIEWC6),classes[i].limperday,
	  getpfix(MINSNG,classes[i].limperday));
  print(outbuf,NULL);
  sprintf(outbuf,getmsg(VIEWC7),classes[i].crdperday,
	  getpfix(CRDSNG,classes[i].crdperday));
  print(outbuf,NULL);
  sprintf(outbuf,getmsg(VIEWC7A),classes[i].crdperweek,
	  getpfix(CRDSNG,classes[i].crdperweek));
  print(outbuf,NULL);
  sprintf(outbuf,getmsg(VIEWC7B),classes[i].crdpermonth,
	  getpfix(CRDSNG,classes[i].crdpermonth));
  print(outbuf,NULL);

  if(classes[i].flags&CF_NOCHRGE)prompt(VIEWC8,NULL);
  if(classes[i].flags&CF_LINUX)prompt(VIEWC9,NULL);
  if(classes[i].flags&CF_LOCKOUT)prompt(VIEWC10,NULL);
  if(classes[i].flags&CF_CRDXFER)prompt(VIEWC11,NULL);

  listkeys(classes[i].keys);

  prompt(VIEWCEND,NULL);
}
       

void
editclass()
{
  char name[10];
  classrec *n;
  int i;

  if(!numclasses){
    prompt(NOCLSES,NULL);
    return;
  }
  if(!getclassname(name,EDTCNAME,1,UNKCLSS,0,0))return;
  
  for(i=0;i<numclasses;i++)if(sameas(name,classes[i].name))break;
  n=&classes[i];

  if(!getnumber(&n->limpercall,ADDCQ1,-1,1500,NUMERR,DEFINT,n->limpercall))
    return;
  if(!getnumber(&n->limperday,ADDCQ2,-1,1500,NUMERR,DEFINT,n->limperday))
    return;
  if(!getnumber(&n->crdperday,ADDCQ3,0,0x7fffffff,NUMERR,DEFINT,n->crdperday))
    return;
  if(!getnumber(&n->crdperweek,ADDCQ3A,INT_MIN,INT_MAX,NUMERR,
		DEFINT,n->crdperweek))return;
  if(!getnumber(&n->crdpermonth,ADDCQ3B,INT_MIN,INT_MAX,NUMERR,
		DEFINT,n->crdpermonth))return;

  if (!getclassname(n->nocreds,ADDCQ4A,1,UNKCLSS,1,n->nocreds))return;
  if (!getclassname(n->credpost,ADDCQ4B,1,UNKCLSS,1,n->credpost))return;

  if(!getnumber(&n->nadays,ADDCQ5,-1,0x7fffffff,NUMERR,DEFINT,n->nadays))return;
  if(n->nadays!=-1){
    if (!getclassname(n->notaround,ADDWHCL,1,UNKCLSS,1,n->notaround))return;
  } else {
    strcpy(n->notaround,n->name);
  }

  if(!getnumber(&n->ardays,ADDCQ6,-1,0x7fffffff,NUMERR,DEFINT,n->ardays))return;
  if(n->ardays!=-1){
    if (!getclassname(n->around,ADDWHCL,1,UNKCLSS,1,n->around))return;
  } else {
    strcpy(n->around,n->name);
  }

  if(!getbool(&i,ADDCQ7,BOOLERR,DEFCHR,(n->flags&CF_NOCHRGE)!=0))return;
  (i)?(n->flags|=CF_NOCHRGE):(n->flags&=~CF_NOCHRGE);
  if(!getbool(&i,ADDCQ8,BOOLERR,DEFCHR,(n->flags&CF_LINUX)!=0))return;
  (i)?(n->flags|=CF_LINUX):(n->flags&=~CF_LINUX);
  if(!getbool(&i,ADDCQ9,BOOLERR,DEFCHR,(n->flags&CF_LOCKOUT)!=0))return;
  (i)?(n->flags|=CF_LOCKOUT):(n->flags&=~CF_LOCKOUT);
  if(!getbool(&i,ADDCQ10,BOOLERR,DEFCHR,(n->flags&CF_CRDXFER)==0))return;
  (!i)?(n->flags|=CF_CRDXFER):(n->flags&=~CF_CRDXFER);

  if(!keyed(n->keys))return;
}


void
moveclass()
{
  char source[10], target[10];

  if(!numclasses){
    prompt(NOCLSES,NULL);
    return;
  }
  if(!getclassname(source,MOVSRC,-1,UNKCLSS,0,0))return;
  if(!getclassname(target,MOVTRG,1,UNKCLSS,0,0))return;
  if(sameas(source,target)){
    prompt(NSAMCLS,NULL);
    return;
  } else {
    DIR           *dp;
    struct dirent *file;
    int           counter=0;
    
    if((dp=opendir(USRDIR))==NULL){
      fatalsys("Unable to diropen %s",ONLINEDIR);
    }

    prompt(MOVING,source,target);

    while((file=readdir(dp))!=NULL){
      if(file->d_name[0]!='.'){
	useracc user, *uacc=&user;
	char *userid=(char *)file->d_name, c='.';
	
	if(!uinsys(userid,0))loaduseraccount(userid,uacc);
	else uacc=&othruseracc;
	if(!uacc) return;
	
	if(sameas(uacc->curclss,source)){
	  counter++;
	  strcpy(uacc->tempclss,target);
	  strcpy(uacc->curclss,target);

	  if(!uinsys(userid,0))saveuseraccount(uacc);
	}
	write(0,&c,1);
      }
    }

    closedir(dp);
    prompt(MOVOK,counter);
  }
}


void
confirmquit()
{
  int i;

  if(!getbool(&i,QUITWRN,BOOLERR,DEFCHR,0)) return;
  if(i) exit(0);
}


void
mainmenu()
{
  char c;

  if(!(thisuseronl.flags&OLF_MMCALLING && thisuseronl.input[0])){
    prompt(MENU,NULL);
  }
  for(;;){
    if(thisuseronl.flags&OLF_MMCALLING && thisuseronl.input[0]){
      thisuseronl.input[0]=0;
    } else {
      if(!nxtcmd){
	if(thisuseronl.flags&OLF_MMCONCAT){
	  thisuseronl.flags&=~OLF_MMCONCAT;
	  saveclasses();
	  exit(0);
	}
	prompt(SHMENU,NULL);
	getinput(0);
	bgncnc();
      }
    }
    if(nxtcmd){
      while(*nxtcmd && isspace(*nxtcmd))nxtcmd++;
      if(*nxtcmd){
	c=cncchr();
	switch (c) {
	case 'A':
	  if(addclass())numclasses--;
	  break;
	case 'C':
	  listclasschanges();
	  break;
	case 'L':
	  listclasses();
	  break;
	case 'D':
	  delclass();
	  break;
	case 'V':
	  viewclass();
	  break;
	case 'E':
	  editclass();
	  break;
	case 'M':
	  moveclass();
	  break;
	case 'X':
	  saveclasses();
	  exit(0);
	case 'Q':
	  confirmquit();
	  break;
	case '?':
	  prompt(MENU,NULL);
	  endcnc();
	  break;
	default:
	  sprintf(outbuf,getmsg(ERRSEL),c);
	  print(outbuf,NULL);
	}
	endcnc();
      } else {
	endcnc();
      }
    } else {
      endcnc();
    }
  }
}
  

void
main(int argc,char *argv[])
{
  setprogname(argv[0]);
  initmodule(INITALL^INITCLASSES);
  msg=opnmsg("classed");
  readclasses();
  mainmenu();
  clsmsg(msg);
}
