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
 * Revision 1.4  2001/10/03 18:05:40  alexios
 * Rectified ancient, far too naive API invocations.
 *
 * Revision 1.3  2001/04/22 14:49:04  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.7  1999/07/18 21:11:35  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
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
const char *__RCS=RCS_VER;
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
#define CLASSDEL  {NDEL,NDEL,-1,NDEL,-1,NDEL,NDEL,0,0,0,0,0,CLF_LOCKOUT}
#define AVONLY(s) (strcmp(classes[i].name,s)?s:"N/A")


promptblock_t *msg;
classrec_t  classes[MAXCLASS];
int       numclasses;


int classcompare (const void *r1, const void *r2)
{
  const classrec_t *a=r1, *b=r2;
  return strcmp(a->name,b->name);
}


static void
readclasses()
{
  FILE *fp;
  classrec_t classdel=CLASSDEL;

  if((fp=fopen(mkfname(CLASSFILE),"r"))!=NULL){
    numclasses=fread(classes,sizeof(classrec_t),MAXCLASS,fp);
  } else numclasses=0;
  fclose(fp);
  if(!numclasses)memcpy(&classes[numclasses++],&classdel,sizeof(classrec_t));
}


void
saveclasses()
{
  FILE *fp;

  qsort(classes,numclasses,sizeof(classrec_t),classcompare);
  if((fp=fopen(mkfname(CLASSFILE),"w"))==NULL){
    error_logsys("Failed to create %s",mkfname(CLASSFILE));
    prompt(IOERROR);
    return;
  }
  if(fwrite(classes,sizeof(classrec_t),numclasses,fp)!=numclasses){
    error_logsys("Failed to write %s",mkfname(CLASSFILE));
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
    prompt(NOCLSES);
    return;
  }
  prompt(CCHLHDR);
  for(i=0;i<numclasses;i++){
    char s1[16]={0}, s2[16]={0};
    
    if(classes[i].nadays!=-1)snprintf(s1,sizeof(s1),"%d",classes[i].nadays);
    if(classes[i].ardays!=-1)snprintf(s2,sizeof(s1),"%d",classes[i].ardays);
    
    prompt(CCHLTAB,classes[i].name,
	   AVONLY(classes[i].notaround),s1,
	   AVONLY(classes[i].around),s2,
	   AVONLY(classes[i].nocreds),
	   AVONLY(classes[i].credpost));
  }
  prompt(CCHLFTR);
}


void
listclasses()
{
  int i;

  if(!numclasses){
    prompt(NOCLSES);
    return;
  }
  prompt(CLSLHDR);
  for(i=0;i<numclasses;i++){
    char s1[16]={0}, s2[16]={0};

    if(classes[i].limpercall!=-1)snprintf(s1,sizeof(s1),"%d",classes[i].limpercall);
    if(classes[i].limperday!=-1)snprintf(s2,sizeof(s2),"%d",classes[i].limperday);

    prompt(CLSLTAB,classes[i].name,
	   s1,s2,
	   classes[i].crdperday,
	   classes[i].crdperweek,
	   classes[i].crdpermonth,
	   classes[i].flags&CLF_NOCHRGE?'X':'-',
	   classes[i].flags&CLF_LINUX?'X':'-',
	   classes[i].flags&CLF_LOCKOUT?'X':'-',
	   classes[i].flags&CLF_CRDXFER?'X':'-');
  }
  prompt(CLSLFTR);
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
    if(cnc_more())strncpy(newclass,cnc_word(),10);
    else {
      prompt(msg);
      if(def) prompt(DEFSTR,defval);
      inp_get(0);
      if(margc)strncpy(newclass,margv[0],10);
      else if(def && !inp_reprompt()){
	strncpy(class,defval,10);
	return 1;
      } else cnc_end();
    }
    if(sameas(newclass,"x"))return 0;
    if(newclass[0]=='?'){
      newclass[0]=0;
      listclasses();
      continue;
    }
    if(!newclass[0]){
      cnc_end();
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
	  cnc_end();
	  prompt(err,newclass);
	  ok=0;
	  break;
	}
      }
    }
    if(existing && !ok){
      prompt(err,newclass);
      cnc_end();
    }
  }
  strncpy(class,newclass,10);
  return 1;
}


int
keyed(bbskey_t *k)
{
  bbskey_t keys[KEYLENGTH];
  int shown=0;
  int key;
  char c;

  memcpy(keys,k,KEYLENGTH*sizeof(bbskey_t));
  prompt(KEYPRO);
  for(;;){
    if(!shown){
      char s1[65]={0},s2[65]={0};
      int i;
      
      for(i=0;i<64;i++){
	s1[i]=(keys[i/32]&(1<<(i%32)))?'X':'-';
	s2[i]=(keys[(i+64)/32]&(1<<((i+64)%32)))?'X':'-';
      }
      prompt(KEYED,s1,s2);
      shown=1;
    }
    
    key=-1;
    for(;;){
      if((c=cnc_more())!=0){
	if(toupper(c)=='X')return 0;
	key=cnc_int();
      } else {
	prompt(KEYASK);
	inp_get(0);
	key=atoi(margv[0]);
	if(!margc || inp_reprompt()){
	  cnc_end();
	  continue;
	} else if(inp_isX(margv[0]))return 0;
	else if(sameas(margv[0],"OK")){
	  memcpy(k,keys,KEYLENGTH*sizeof(bbskey_t));
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
	cnc_end();
	prompt(NUMERR,1,128);
      }else break;
    }
    
    if(key>=1 && key<=128){
      key--;
      keys[key/32]^=(1<<(key%32));
      prompt(KEYON+((keys[key/32]&(1<<(key%32)))==0),key+1);
    }
  }
}


int
addclass()
{
  char name[10];
  classrec_t *newclass;
  int i;

  if(numclasses>=MAXCLASS){
    prompt(TOOMANY,MAXCLASS);
    return 0;
  }
  if(!getclassname(name,ADDCNAME,0,ALRDYEX,0,0))return 0;
  newclass=&classes[numclasses++];
  memset(newclass,0,sizeof(classrec_t));
  strncpy(newclass->name,name,10);
  if(!get_number(&newclass->limpercall,ADDCQ1,-1,1500,NUMERR,0,0))return 1;
  if(!get_number(&newclass->limperday,ADDCQ2,-1,1500,NUMERR,0,0))return 1;
  if(!get_number(&newclass->crdperday,ADDCQ3,0,INT_MAX,NUMERR,0,0))return 1;
  if(!get_number(&newclass->crdperweek,ADDCQ3A,INT_MIN,INT_MAX,NUMERR,0,0))return 1;
  if(!get_number(&newclass->crdpermonth,ADDCQ3B,INT_MIN,INT_MAX,NUMERR,0,0))return 1;
  if(!getclassname(newclass->nocreds,ADDCQ4A,1,UNKCLSS,0,0))return 1;

  if (!getclassname(newclass->credpost,ADDCQ4B,1,UNKCLSS,0,0))return 1;

  if(!get_number(&newclass->nadays,ADDCQ5,-1,0x7fffffff,NUMERR,0,0))return 1;
  if(newclass->nadays!=-1){
    if (!getclassname(newclass->notaround,ADDWHCL,1,UNKCLSS,0,0))return 1;
  } else {
    strcpy(newclass->notaround,newclass->name);
  }

  if(!get_number(&newclass->ardays,ADDCQ6,-1,0x7fffffff,NUMERR,0,0))return 1;
  if(newclass->ardays!=-1){
    if (!getclassname(newclass->around,ADDWHCL,1,UNKCLSS,0,0))return 1;
  } else {
    strcpy(newclass->around,newclass->name);
  }

  if(!get_bool(&i,ADDCQ7,BOOLERR,0,0))return 1;
  if(i)newclass->flags|=CLF_NOCHRGE;
  if(!get_bool(&i,ADDCQ8,BOOLERR,0,0))return 1;
  if(i)newclass->flags|=CLF_LINUX;
  if(!get_bool(&i,ADDCQ9,BOOLERR,0,0))return 1;
  if(i)newclass->flags|=CLF_LOCKOUT;
  if(!get_bool(&i,ADDCQ10,BOOLERR,0,0))return 1;
  if(!i)newclass->flags|=CLF_CRDXFER;

  if(!keyed(newclass->keys))return 1;
  return 0;
}


void
delclass()
{
  char name[10];
  int i;

  if(!numclasses){
    prompt(NOCLSES);
    return;
  }
  if(!getclassname(name,DELCNAME,1,UNKCLSS,0,0))return;
  if(!get_bool(&i,DELCCNF,BOOLERR,0,0))return;
  if(!i)return;
  
  for(i=0;i<numclasses;i++)if(sameas(name,classes[i].name))break;
  if(i+1<numclasses){
    memmove(&classes[i],&classes[i+1],sizeof(classrec_t)*(numclasses-(i+1)));
  }
  numclasses--;
  prompt(DELWARN);
}


void
listkeys(bbskey_t *keys){
  bbskey_t j;
  int i,first=-1,count=0;

  prompt(VIEWKY);
  for(i=0;i<(32*KEYLENGTH);i++){
    j=keys[i/32]&(1<<(i%32));
    count+=j;
    if(!j){
      if(first!=-1){
	if(first<(i-1))prompt(VIEWKY2,first+1,i);
	if(first==(i-1))prompt(VIEWKY1,first+1);
	first=-1;
      }
    }else{
      if(first==-1)first=i;
    }
  }
  if(first!=-1){
    if(first<(i-1))prompt(VIEWKY2,first+1,i);
    if(first==(i-1))prompt(VIEWKY1,first+1);
  }
  if(!count)prompt(VIEWKY0);
  else prompt(VIEWKYE);
}
       

void
viewclass()
{
  char name[10];
  int i;

  if(!numclasses){
    prompt(NOCLSES);
    return;
  }
  if(!getclassname(name,VEWCNAME,1,UNKCLSS,0,0))return;
  
  for(i=0;i<numclasses;i++)if(sameas(name,classes[i].name))break;

  propmt(VIEWC1,classes[i].name);
  if(classes[i].nadays>=0){
    prompt(VIEWC2,classes[i].nadays,
	   msg_getunit(DAYSNG,classes[i].nadays),
	   classes[i].notaround);
  }
  if(classes[i].ardays>=0){
    prompt(VIEWC3,classes[i].ardays,
	   msg_getunit(DAYSNG,classes[i].ardays),
	   classes[i].around);
  }
  prompt(VIEWC4A,classes[i].nocreds);
  prompt(VIEWC4C,classes[i].credpost);
  prompt(VIEWC5,
	 classes[i].limpercall,msg_getunit(MINSNG,classes[i].limpercall));
  prompt(VIEWC6,
	 classes[i].limperday,msg_getunit(MINSNG,classes[i].limperday));
  prompt(VIEWC7,
	 classes[i].crdperday,msg_getunit(CRDSNG,classes[i].crdperday));
  prompt(VIEWC7A,
	 classes[i].crdperweek,msg_getunit(CRDSNG,classes[i].crdperweek));
  propmt(VIEWC7B,classes[i].crdpermonth,
	 msg_getunit(CRDSNG,classes[i].crdpermonth));

  if(classes[i].flags&CLF_NOCHRGE)prompt(VIEWC8);
  if(classes[i].flags&CLF_LINUX)prompt(VIEWC9);
  if(classes[i].flags&CLF_LOCKOUT)prompt(VIEWC10);
  if(classes[i].flags&CLF_CRDXFER)prompt(VIEWC11);

  listkeys(classes[i].keys);

  prompt(VIEWCEND);
}
       

void
editclass()
{
  char name[10];
  classrec_t *n;
  int i;

  if(!numclasses){
    prompt(NOCLSES);
    return;
  }
  if(!getclassname(name,EDTCNAME,1,UNKCLSS,0,0))return;
  
  for(i=0;i<numclasses;i++)if(sameas(name,classes[i].name))break;
  n=&classes[i];

  if(!get_number(&n->limpercall,ADDCQ1,-1,1500,NUMERR,DEFINT,n->limpercall))
    return;
  if(!get_number(&n->limperday,ADDCQ2,-1,1500,NUMERR,DEFINT,n->limperday))
    return;
  if(!get_number(&n->crdperday,ADDCQ3,0,0x7fffffff,NUMERR,DEFINT,n->crdperday))
    return;
  if(!get_number(&n->crdperweek,ADDCQ3A,INT_MIN,INT_MAX,NUMERR,
		DEFINT,n->crdperweek))return;
  if(!get_number(&n->crdpermonth,ADDCQ3B,INT_MIN,INT_MAX,NUMERR,
		DEFINT,n->crdpermonth))return;

  if (!getclassname(n->nocreds,ADDCQ4A,1,UNKCLSS,1,n->nocreds))return;
  if (!getclassname(n->credpost,ADDCQ4B,1,UNKCLSS,1,n->credpost))return;

  if(!get_number(&n->nadays,ADDCQ5,-1,0x7fffffff,NUMERR,DEFINT,n->nadays))return;
  if(n->nadays!=-1){
    if (!getclassname(n->notaround,ADDWHCL,1,UNKCLSS,1,n->notaround))return;
  } else {
    strcpy(n->notaround,n->name);
  }

  if(!get_number(&n->ardays,ADDCQ6,-1,0x7fffffff,NUMERR,DEFINT,n->ardays))return;
  if(n->ardays!=-1){
    if (!getclassname(n->around,ADDWHCL,1,UNKCLSS,1,n->around))return;
  } else {
    strcpy(n->around,n->name);
  }

  if(!get_bool(&i,ADDCQ7,BOOLERR,DEFCHR,(n->flags&CLF_NOCHRGE)!=0))return;
  (i)?(n->flags|=CLF_NOCHRGE):(n->flags&=~CLF_NOCHRGE);
  if(!get_bool(&i,ADDCQ8,BOOLERR,DEFCHR,(n->flags&CLF_LINUX)!=0))return;
  (i)?(n->flags|=CLF_LINUX):(n->flags&=~CLF_LINUX);
  if(!get_bool(&i,ADDCQ9,BOOLERR,DEFCHR,(n->flags&CLF_LOCKOUT)!=0))return;
  (i)?(n->flags|=CLF_LOCKOUT):(n->flags&=~CLF_LOCKOUT);
  if(!get_bool(&i,ADDCQ10,BOOLERR,DEFCHR,(n->flags&CLF_CRDXFER)==0))return;
  (!i)?(n->flags|=CLF_CRDXFER):(n->flags&=~CLF_CRDXFER);

  if(!keyed(n->keys))return;
}


void
moveclass()
{
  char source[10], target[10];

  if(!numclasses){
    prompt(NOCLSES);
    return;
  }
  if(!getclassname(source,MOVSRC,-1,UNKCLSS,0,0))return;
  if(!getclassname(target,MOVTRG,1,UNKCLSS,0,0))return;
  if(sameas(source,target)){
    prompt(NSAMCLS);
    return;
  } else {
    DIR           *dp;
    struct dirent *file;
    int           counter=0;
    
    if((dp=opendir(mkfname(USRDIR)))==NULL){
      error_fatalsys("Unable to diropen %s",mkfname(ONLINEDIR));
    }

    prompt(MOVING,source,target);

    while((file=readdir(dp))!=NULL){
      if(file->d_name[0]!='.'){
	useracc_t user, *uacc=&user;
	char *userid=(char *)file->d_name, c='.';
	
	if(!usr_insys(userid,0))usr_loadaccount(userid,uacc);
	else uacc=&othruseracc;
	if(!uacc) return;
	
	if(sameas(uacc->curclss,source)){
	  counter++;
	  strcpy(uacc->tempclss,target);
	  strcpy(uacc->curclss,target);

	  if(!usr_insys(userid,0))usr_saveaccount(uacc);
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

  if(!get_bool(&i,QUITWRN,BOOLERR,DEFCHR,0)) return;
  if(i) exit(0);
}


void
mainmenu()
{
  char c;

  if(!(thisuseronl.flags&OLF_MMCALLING && thisuseronl.input[0])){
    prompt(MENU);
  }
  for(;;){
    if(thisuseronl.flags&OLF_MMCALLING && thisuseronl.input[0]){
      thisuseronl.input[0]=0;
    } else {
      if(!cnc_nxtcmd){
	if(thisuseronl.flags&OLF_MMCONCAT){
	  thisuseronl.flags&=~OLF_MMCONCAT;
	  saveclasses();
	  exit(0);
	}
	prompt(SHMENU);
	inp_get(0);
	cnc_begin();
      }
    }
    if(cnc_nxtcmd){
      while(*cnc_nxtcmd && isspace(*cnc_nxtcmd))cnc_nxtcmd++;
      if(*cnc_nxtcmd){
	c=cnc_chr();
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
	  prompt(MENU);
	  cnc_end();
	  break;
	default:
	  prompt(ERRSEL,c);
	}
	cnc_end();
      } else {
	cnc_end();
      }
    } else {
      cnc_end();
    }
  }
}
  

int
main(int argc,char *argv[])
{
  mod_setprogname(argv[0]);
  mod_init(INI_ALL^INI_CLASSES);
  msg=msg_open("classed");
  readclasses();
  mainmenu();
  msg_close(msg);

  return 0;
}
