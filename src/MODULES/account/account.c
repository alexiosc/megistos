/*****************************************************************************\
 **                                                                         **
 **  FILE:     account.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, November 94, Version 1.0                                  **
 **  PURPOSE:  Implement the User Account module                            **
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
 * Revision 1.1  2001/04/16 14:54:20  alexios
 * Initial revision
 *
 * Revision 1.9  1999/07/18 21:19:02  alexios
 * Changed a few fatal() calls to fatalsys().
 *
 * Revision 1.8  1998/12/27 15:27:18  alexios
 * Added autoconf support. Fixed stupid credit transfer bug.
 *
 * Revision 1.7  1998/07/24 10:13:49  alexios
 * Moved to stable status.
 *
 * Revision 1.6  1998/07/24 10:12:42  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 1.5  1997/11/06 20:10:39  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 1.4  1997/11/06 16:53:12  alexios
 * Changed things so the new auditing scheme is used.
 *
 * Revision 1.3  1997/11/03 00:39:13  alexios
 * Added code to handle ANSIASK flag. Removed code for hardwired
 * translation tables. Replaced it with code for the generalised
 * customisable tables. Added TRASK flag to force the system to
 * ask what translation table to use during login.
 *
 * Revision 1.2  1997/09/12 13:02:27  alexios
 * Added option STRPSS to control how strict the system is with
 * new passwords (if STRPSS is NO, passwords won't be required
 * to contain non-alphabetic characters). Added option MINPLN to
 * control the minimum length of a password. Password checking is
 * now case-insensitive. Fixed showstats() to take into account
 * bad formatting and a bug with new users using the facility.
 *
 * Revision 1.1  1997/09/01 10:27:45  alexios
 * Fixed a few minor bugs concerning the treatment of the Default
 * flags for ANSI and Translation preferences. Applied preference
 * changes to the system before the next prompt is given so it
 * too reflects the changes to the user's prefs.
 *
 * Revision 1.0  1997/08/28 10:06:46  alexios
 * Initial revision
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
#include "mbk_account.h"


/*                   123456789012345678901234567890 */
#define AUS_ACCEDT1 "USER CHANGED ACCOUNT DATA"
#define AUS_ACCEDT2 "USER CHANGED ACCOUNT DATA"
#define AUS_ACCEDT3 "USER CHANGED ACCOUNT DATA"
#define AUS_CRDXFER "CREDIT TRANSFER"
#define AUS_BLGPWCH "HACK TRY IN PASSWORD CHANGE"
#define AUS_PASSOTH "CHANGED OTHER'S PASSWORD"
 
/*                   1234567890123456789012345678901234567890123456789012... */
#define AUD_ACCEDT1 "User %s changed %s."
#define AUD_ACCEDT2 "User %s changed %s: %d->%d."
#define AUD_ACCEDT3 "User %s changed %s."
#define AUD_CRDXFER "%s transferred %d credits to %s"
#define AUD_BLGPWCH "User %-24s  Speed: %5d"
#define AUD_PASSOTH "%s changed %s's password"

#define AUT_ACCEDT1 (AUF_ACCOUNTING|AUF_INFO)
#define AUT_ACCEDT2 (AUF_ACCOUNTING|AUF_INFO)
#define AUT_ACCEDT3 (AUF_ACCOUNTING|AUF_CAUTION)
#define AUT_CRDXFER (AUF_ACCOUNTING|AUF_INFO)
#define AUT_BLGPWCH (AUF_SECURITY|AUF_ACCOUNTING|AUF_CAUTION)
#define AUT_PASSOTH (AUF_SECURITY|AUF_ACCOUNTING|AUF_CAUTION)


#define SETVALUE(x,f,s)  (x)=((s)?((x)|=(f)):((x)&=~(f)))


promptblk *msg;

int syskey;
int xfkey;
int remexp;
int strexp;
int safpsw;
int strpss;
int minpln;
int mkpswd;
int mkpwdf;
int lipsko;
int lognam;
int logcmp;
int logadr;
int logphn;
int logage;
int logsex;
int logsys;
int demcxf;
int mincxf;
int maxcxf;


useracc    *uacc,useraccount;


void
init()
{
  initmodule(INITALL);
  msg=opnmsg("account");
  setlanguage(thisuseracc.language);

  syskey=numopt(SYSKEY,0,129);
  xfkey=numopt(XFKEY,0,129);
  remexp=ynopt(REMEXP);
  strexp=ynopt(STREXP);
  safpsw=ynopt(SAFPSW);
  strpss=ynopt(STRPSS);
  minpln=numopt(MINPLN,3,15);
  mkpswd=ynopt(MKPSWD);
  mkpwdf=ynopt(MKPWDF);
  lipsko=numopt(LIPSKO,1,32767);
  lognam=ynopt(LOGNAM);
  logcmp=ynopt(LOGCMP);
  logadr=ynopt(LOGADR);
  logphn=ynopt(LOGPHN);
  logage=ynopt(LOGAGE);
  logsex=ynopt(LOGSEX);
  logsys=ynopt(LOGSYS);
  demcxf=ynopt(DEMCXF);
  mincxf=numopt(MINCXF,0,1000000);
  maxcxf=numopt(MAXCXF,0,1000000);

  uacc=&thisuseracc;
}


void
editaccount()
{
  useracc tempacc;
  FILE *fp;
  char fname[256], s[80], *cp;
  int i;

  memcpy(&tempacc,uacc,sizeof(tempacc));

  sprintf(fname,TMPDIR"/acc%05d",getpid());
  if((fp=fopen(fname,"w"))==NULL){
    logerrorsys("Unable to create data entry file %s",fname);
    return;
  }

  fprintf(fp,"%s\n",tempacc.username);
  fprintf(fp,"%s\n",tempacc.company);
  fprintf(fp,"%s\n",tempacc.address1);
  fprintf(fp,"%s\n",tempacc.address2);
  fprintf(fp,"%s\n",tempacc.phone);
  fprintf(fp,"%d\n",tempacc.age);
  fprintf(fp,"%s\n",getmsg(tempacc.sex=='M'?SEXM:SEXF));
  fprintf(fp,"%s\n",getmsg(tempacc.system-1+SYS1));
  fprintf(fp,"OK button\nCancel button\n");
  fclose(fp);

  dataentry("account",ACCVT,ACCLT,fname);

  if((fp=fopen(fname,"r"))==NULL){
    logerrorsys("Unable to read data entry file %s",fname);
    return;
  }

  for(i=0;i<11;i++){
    fgets(s,sizeof(s),fp);
    if((cp=strchr(s,'\n'))!=NULL)*cp=0;
    if(i==0)strcpy(tempacc.username,s);
    else if(i==1)strcpy(tempacc.company,s);
    else if(i==2)strcpy(tempacc.address1,s);
    else if(i==3)strcpy(tempacc.address2,s);
    else if(i==4)strcpy(tempacc.phone,s);
    else if(i==5)tempacc.age=atoi(s);
    else if(i==6)tempacc.sex=(strcmp(s,getmsg(SEXF))?'M':'F');
    else if(i==7){
      int j;

      for(j=0;j<8;j++)if(!strcmp(s,getmsg(SYS1+j))){
	tempacc.system=j+1;
	break;
      }
    }
  }

  fclose(fp);
  unlink(fname);
  if(sameas(s,"CANCEL")){
    prompt(EDITCAN);
    return;
  } else {
    prompt(EDITOK);
    
    if(lognam && strcmp(tempacc.username,uacc->username))
      audit(thisuseronl.channel,AUDIT(ACCEDT1),uacc->userid,"NAME");
    if(logcmp && strcmp(tempacc.company,uacc->company))
      audit(thisuseronl.channel,AUDIT(ACCEDT1),uacc->userid,"COMPANY");
    if(logadr && (strcmp(tempacc.address1,uacc->address1) ||
		  strcmp(tempacc.address2,uacc->address2)))
      audit(thisuseronl.channel,AUDIT(ACCEDT1),uacc->userid,"ADDRESS");
    if(logphn && strcmp(tempacc.phone,uacc->phone))
      audit(thisuseronl.channel,AUDIT(ACCEDT3),uacc->userid,"PHONE");
    if(logage && tempacc.age!=uacc->age)
      audit(thisuseronl.channel,AUDIT(ACCEDT2),uacc->userid,"AGE",
	    uacc->age,tempacc.age);
    if(logsex && tempacc.sex!=uacc->sex)
      audit(thisuseronl.channel,AUDIT(ACCEDT3),uacc->userid,"SEX");
    if(logsys && tempacc.system!=uacc->system)
      audit(thisuseronl.channel,AUDIT(ACCEDT2),uacc->userid,"SYSTEM",
	    uacc->system,tempacc.system);
  
    memcpy(uacc,&tempacc,sizeof(tempacc));
  }
}


char *
makeapass()
{
  FILE *words;
  static char pass[16]={0};
  char word[16]={0};
  int l,i,j;

  if ((words=fopen(FLETTRWORDS,"r"))!=NULL){
    randomize();
    fseek(words,0L,SEEK_END);
    l=(int)ftell(words);
    rewind(words);
    fseek(words,(long)rnd(l-15),SEEK_SET);
    fscanf(words,"%s",pass);
    fscanf(words,"%s",pass);
    fseek(words,(long)rnd(l-15),SEEK_SET);
    fscanf(words,"%s",word);
    fscanf(words,"%s",word);
    pass[4]=DELIM[rnd(strlen(DELIM))];
    memcpy(pass+5,word,5);
    fclose(words);

    j=rnd(4);
    if(j<2){
      int k=(j==0)?4:1;
      for(i=0;i<k;i++)pass[i]=toupper(pass[i]);
    }else{
      int k=(j==2)?9:6;
      for(i=5;i<k;i++)pass[i]=toupper(pass[i]);
    }
    
    return pass;
  } else {
    return NULL;
  }
}


int
stupidpass(char *pass)
{
  FILE *fp;
  char line[256];

  if(sameas(pass,uacc->userid))return 1;
  if((fp=fopen(BADPASSFILE,"r"))==NULL)return 0;
  while(!feof(fp)){
    if(fgets(line,256,fp)){
      int i;
      for(i=0;i<sizeof(line);i++){
	if(line[i]==10 || line[i]==13){
	  line[i]=0;
	  break;
	}
      }
      if(sameas(line,pass)){
	fclose(fp);
	return 1;
      }
    }
  }
  fclose(fp);
  return 0;
}


void
changepassword(char *userid, int login)
{
  char recommended [256], passwd[256], uid[80];
  int retries;

  strcpy(uid,uacc->userid);
  if(!uinsys(userid,0)){
    uacc=&useraccount;
    loaduseraccount(userid,uacc);
  }

  if(sameas(userid,uid)){
    for(retries=1;;retries++){
      do{
	prompt(PSCUR);
	setpasswordentry(1);
	getinput(15);
      }while(reprompt);
      if(!sameas(input,uacc->passwd)){
	prompt(CPSERR);
	if(!login)return;
	else if(retries>=lipsko){
	  prompt(PSWKO);
	  audit(thisuseronl.channel,AUDIT(BLGPWCH),
		thisuseracc.userid,baudstg(thisuseronl.baudrate));
	  disconnect(thisuseronl.emupty);
	}
      } else break;
    }
  }

  prompt(PREPSW,NULL);
  strcpy(passwd,makeapass());
  strcpy(recommended,passwd);
  endcnc();
  for(;;){
    if(mkpswd && mkpwdf){
      prompt(FRCPSW,recommended,NULL);
    } else {
      if(mkpswd)prompt(RECPSW,recommended,NULL);
      setpasswordentry(1);
      prompt(GPSWORD,NULL);
      getinput(15);
      if(!margc || isX(margv[0])){
	setpasswordentry(0);
	if(!login){
	  prompt(PNOTSET);
	  return;
	} else {
	  endcnc();
	  continue;
	}
      }
      rstrin();
      
      if(safpsw){
	int i,d=0;
	if(strlen(input)<minpln){
	  prompt(BADPSW1,NULL);
	  continue;
	}
	if(!strpss)d++;
	else {
	  for(i=0,d=0;input[i];i++)if(isupper(input[i])||!isalpha(input[i]))d++;
	}
	if(!d){
	  prompt(BADPSW1,NULL);
	  continue;
	}
	if(stupidpass(input)){
	  prompt(BADPSW2,NULL);
	  continue;
	}
	strcpy(passwd,input);
	if(sameas(uacc->passwd,passwd)){
	  prompt(BADPSW4);
	  continue;
	}
      }
    }
    prompt(GPSWAGN,NULL);
    setpasswordentry(1);
    getinput(15);
    rstrin();
    if(!sameas(input,passwd)){
      prompt(BADPSW3,NULL);
      setpasswordentry(0);
      if(!login){
	prompt(PNOTSET);
	return;
      } else {
	endcnc();
	continue;
      }
    }
    break;
  }
  setpasswordentry(0);
  strcpy(uacc->passwd,passwd);
  uacc->passexp=sysvar->pswexpiry;

  if(!userexists(userid))return;
  if(!uinsys(userid,0))saveuseraccount(uacc);
  prompt(PSWEPI);
  if(strcmp(userid,uid)){
    audit(thisuseronl.channel,AUDIT(PASSOTH),uid,userid);
  }
}


void
resetbbslib()
{
  char tmp[256];
  
  clsmsg(msg);
  msg=opnmsg("account");
  setlanguage(thisuseracc.language);
  if((thisuseracc.prefs&(UPF_ANSIDEF|UPF_ANSIASK))==0){
    SETVALUE(thisuseronl.flags,OLF_ANSION,thisuseracc.prefs&UPF_ANSION);
    setansiflag(thisuseronl.flags&OLF_ANSION);
  }
  setverticalformat((thisuseracc.prefs&UPF_NONSTOP)==0);
  setwaittoclear((thisuseracc.prefs&UPF_NONSTOP)==0);
  
  sprintf(tmp,"%s rows %d columns %d ixon ixoff",STTYBIN,
	  uacc->scnheight,uacc->scnwidth);
  system(tmp);
  sprintf(tmp,"%d",uacc->scnwidth);
  setenv("COLUMNS",tmp,1);
  sprintf(tmp,"%d",uacc->scnheight);
  setenv("ROWS",tmp,1);
  setlinelen(uacc->scnwidth);
  setscreenheight(uacc->scnheight);

  if((thisuseracc.prefs&(UPF_TRDEF|UPF_TRASK))==0)
    setxlationtable(getpxlation(thisuseracc));
}


void
editprefs()
{
  useracc tempacc;
  FILE *fp;
  char fname[256], s[80], *cp;
  int i;

  memcpy(&tempacc,uacc,sizeof(tempacc));

  sprintf(fname,TMPDIR"/acc%05d",getpid());
  if((fp=fopen(fname,"w"))==NULL){
    logerrorsys("Unable to create data entry file %s",fname);
    return;
  }

  if(tempacc.prefs&UPF_ANSIDEF)fprintf(fp,"%s\n",getmsg(ANSDEF));
  else if(tempacc.prefs&UPF_ANSIASK)fprintf(fp,"%s\n",getmsg(ANSASK));
  else if(tempacc.prefs&UPF_ANSION)fprintf(fp,"%s\n",getmsg(ANSON));
  else fprintf(fp,"%s\n",getmsg(ANSOFF));

  if(tempacc.prefs&UPF_TRDEF)fprintf(fp,"%s\n",getmsg(TRDEF));
  else if(tempacc.prefs&UPF_TRASK)fprintf(fp,"%s\n",getmsg(TRASK));
  else fprintf(fp,"%s\n",getmsg(TR0+getpxlation(tempacc)));

  fprintf(fp,"%s\n",(tempacc.prefs&UPF_NONSTOP?"on":"off"));
  fprintf(fp,"%s\n",(tempacc.prefs&UPF_VISUAL?"on":"off"));
  fprintf(fp,"%s\n",getmsg(LANG1+tempacc.language-1));
  fprintf(fp,"%d\n",tempacc.scnwidth);
  fprintf(fp,"%d\n",tempacc.scnheight);
  fprintf(fp,"%s\n",getmsg(PGSSTR+tempacc.pagestate));
  fprintf(fp,"%ld\n",tempacc.pagetime);
  fprintf(fp,"OK button\nCancel button\n");
  fclose(fp);

  dataentry("account",PRFVT,PRFLT,fname);

  if((fp=fopen(fname,"r"))==NULL){
    logerrorsys("Unable to read data entry file %s",fname);
    return;
  }

  for(i=0;i<12;i++){
    fgets(s,sizeof(s),fp);
    if((cp=strchr(s,'\n'))!=NULL)*cp=0;

    if(i==0){
      SETVALUE(tempacc.prefs,UPF_ANSIDEF,sameas(s,getmsg(ANSDEF)));
      SETVALUE(tempacc.prefs,UPF_ANSIASK,sameas(s,getmsg(ANSASK)));
      SETVALUE(tempacc.prefs,UPF_ANSION,sameas(s,getmsg(ANSON)));
    } else if(i==1){
      int n;
      SETVALUE(tempacc.prefs,UPF_TRDEF,sameas(s,getmsg(TRDEF)));
      SETVALUE(tempacc.prefs,UPF_TRASK,sameas(s,getmsg(TRASK)));
      for(n=0;n<NUMXLATIONS;n++){
	if(sameas(s,getmsg(TR0+n))){
	  setpxlation(tempacc,n);
	  break;
	}
      }
    } else if(i==2)SETVALUE(tempacc.prefs,UPF_NONSTOP,sameas(s,"on"));
    else if(i==3)SETVALUE(tempacc.prefs,UPF_VISUAL,sameas(s,"on"));
    else if(i==4){
      int j;
      for(j=0;j<10;j++)if(!strcmp(s,getmsg(LANG1+j))){
	tempacc.language=j+1;
	break;
      }
    } else if(i==5)tempacc.scnwidth=atoi(s);
    else if(i==6)tempacc.scnheight=atoi(s);
    else if(i==7){
      int j,k[4]={PGS_STORE,PGS_OK,PGS_ON,PGS_OFF};
      for(j=0;j<4;j++)if(!strcmp(s,getmsg(PGSSTR+j))){
	tempacc.pagestate=k[j];
	break;
      }
    } else if(i==8)tempacc.pagetime=atoi(s);
  }

  fclose(fp);
  unlink(fname);
  if(sameas(s,"CANCEL")){
    prompt(EDITCAN);
    return;
  } else {
    memcpy(uacc,&tempacc,sizeof(tempacc));
    if(sameas(uacc->userid,thisuseracc.userid))resetbbslib();
    prompt(EDITOK);
  }
}


void
transfercredits()
{
  int num, yes;
  char userid[80];
  useracc ruseracc, *ruacc=&ruseracc;
  classrec *class=findclass(uacc->curclss);

  if(uacc->credits<mincxf){
    prompt(XFERR1,mincxf);
    return;
  } else if((class->flags&CF_CRDXFER)==0){
    prompt(XFERR2);
    return;
  } else if(!haskey(uacc,xfkey)){
    prompt(XFERR2);
    return;
  } else if(!(demcxf||uacc->totpaid)){
    prompt(XFERR3);
    return;
  }

  if(!getnumber(&num,CREDTR,mincxf,min(uacc->credits-1,maxcxf),NUMERR,0,0)){
    prompt(CXFABO);
    return;
  }
  if(uacc->credits<mincxf){
    prompt(RANOUT);
    return;
  }

  for(;;){
    if(!getuserid(userid,CTWHO,UIDERR,0,NULL,0)){
      prompt(CXFABO);
      return;
    }
    if(sameas(userid,uacc->userid)){
      prompt(CTNSELF);
      continue;
    } else break;
  }

  if(!uinsys(userid,0))loaduseraccount(userid,ruacc);
  else ruacc=&othruseracc;

  class=findclass(ruacc->curclss);
  if(ruacc->credits<mincxf || (!haskey(ruacc,xfkey)) ||
     (!(demcxf||uacc->totpaid)) || ((class->flags&CF_CRDXFER)==0))
    prompt(CTWARN,userid);
  
  prompt(CTCONF,num,uacc->userid,userid);
  
  if(!getbool(&yes,CTCQUE,BOOLERR,0,0) || (!yes)){
    prompt(CXFABO);
    return;
  }

  if(!userexists(userid)){
    prompt(ACCDEL,userid);
    return;
  } else {
    ruacc=&ruseracc;
    if(!uinsys(userid,0))loaduseraccount(userid,ruacc);
    else ruacc=&othruseracc;

    if(num>=uacc->credits){
      prompt(NOENOT,uacc->credits);
      num=uacc->credits-1;
    }

    uacc->credits-=num;
    postcredits(userid,num,CRD_FREE);
    audit(thisuseronl.channel,AUDIT(CRDXFER),uacc->userid,num,userid);
    prompt(CXFOK,num,uacc->userid,userid);
    if(uinsys(userid,0)){
      char injbuf[16384];

      sprintf(injbuf,getmsglang(CXFINJ,othruseracc.language-1),uacc->userid,num);
      if(injoth(&othruseronl,injbuf,0))prompt(NOTICE,ruacc->userid);
    }
  }
}


void
showstats()
{
  char p1[80],p2[80],p3[80],p4[80];
  char buf[16384];
  int nod=cofdate(today())-cofdate(uacc->datecre);
  classrec *class=findclass(uacc->curclss);

  prompt(ACCST1);

  if(uacc->datecre!=today()){
    strcpy(p1,getmsg(DAYSNG+(nod!=1)));
    strcpy(p2,getmsg(TIMSNG+(uacc->connections!=1)));
    strcpy(p3,getmsg(DAYSNG+(uacc->passexp!=1)));
    sprompt(outbuf,ACCST2,nod,p1,p2,p3);
  } else sprompt(outbuf,ACCST2A,getpfix(DAYSNG,uacc->passexp));
  strcat(buf,outbuf);

  strcpy(p1,getpfix(CRDSNG,uacc->credits));
  strcpy(p2,getpfix(CRDSNG,uacc->totcreds));
  strcpy(p3,getpfix(CRDSNG,uacc->credsever));
  strcpy(p4,getpfix(MINSNG,uacc->timever));
  sprompt(outbuf,ACCST3,p1,p2,p3,p4);
  strcat(buf,outbuf);

  strcpy(p1,getpfix(FILSNG,uacc->filesdnl));
  strcpy(p2,getpfix(FILSNG,uacc->filesupl));
  sprompt(outbuf,ACCST4,p1,p2);
  strcat(buf,outbuf);
  
  strcat(buf,getmsg(ACCST5A));
  if(class->limpercall>=0){
    sprompt(outbuf,ACCST5B,class->limpercall,
	    getpfix(MINSNG,class->limpercall));
    strcat(buf,outbuf);
  }
  if(class->limperday>=0){
    sprompt(outbuf,ACCST5C,class->limperday,
	    getpfix(MINSNG,class->limperday));
    strcat(buf,outbuf);
  }
  if(class->crdperday){
    char hoften[80];
    strcpy(hoften,getmsg(DAILY));
    sprompt(outbuf,ACCST5D,class->crdperday,
	    getpfix(CRDSNG,class->crdperday),hoften);
    strcat(buf,outbuf);
  }

  if(class->crdperweek){
    char hoften[80];
    strcpy(hoften,getmsg(WEEKLY));
    sprompt(outbuf,ACCST5D,class->crdperweek,
	    getpfix(CRDSNG,class->crdperweek),hoften);
    strcat(buf,outbuf);
  }

  if(class->crdpermonth){
    char hoften[80];
    strcpy(hoften,getmsg(MNTHLY));
    sprompt(outbuf,ACCST5D,class->crdpermonth,
	    getpfix(CRDSNG,class->crdpermonth),
	    hoften);
    strcat(buf,outbuf);
  }

  if(class->flags&CF_NOCHRGE)strcat(buf,getmsg(ACCST5E));
  nod=class->ardays-uacc->classdays;
  if(class->ardays>0){
    sprompt(outbuf,ACCST5F,nod,getpfix(DAYSNG,nod),class->around);
    strcat(buf,outbuf);
  } else if(!class->ardays){
    sprompt(outbuf,ACCST5FT,class->around);
    strcat(buf,outbuf);
  }
  if(class->nadays!=-1){
    sprompt(outbuf,ACCST5G,class->nadays,
	    getpfix(DAYSNG,class->nadays),class->notaround);
    strcat(buf,outbuf);
  }
  if(strcmp(uacc->curclss,class->nocreds)){
    sprompt(outbuf,ACCST5H,class->nocreds);
    strcat(buf,outbuf);
  }
  if(strcmp(uacc->curclss,class->credpost)){
    sprompt(outbuf,ACCST5I,class->credpost);
    strcat(buf,outbuf);
  }
  strcat(buf,getmsg(ACCST5J));

  print(buf);
	 
  prompt(ACCST6);
}


void
passother()
{
  char userid[80];

  if(!getuserid(userid,OPSWHO,OUIDERR,0,NULL,0))return;
  else {
    prompt(PSWOTH,userid);
    changepassword(userid,0);
    uacc=&thisuseracc;
  }
}


int
run(int argc, char *argv[])
{
  int shownmenu=0;
  char c;

  uacc=&thisuseracc;

  for(;;){
    if(!(thisuseronl.flags&OLF_MMCALLING && thisuseronl.input[0])){
      if(!shownmenu){
	prompt(haskey(&thisuseracc,syskey)?ACCSMNU:ACCMNU,NULL);
	prompt(VSHMENU);
	shownmenu=2;
      }
    } else shownmenu=1;
    if(thisuseronl.flags&OLF_MMCALLING && thisuseronl.input[0]){
      thisuseronl.input[0]=0;
    } else {
      if(!nxtcmd){
	if(thisuseronl.flags&OLF_MMCONCAT){
	  thisuseronl.flags&=~OLF_MMCONCAT;
	  return 0;
	}
	if(shownmenu==1){
	  prompt(haskey(&thisuseracc,syskey)?SHSMENU:SHMENU,NULL);
	} else shownmenu=1;
	getinput(0);
	bgncnc();
      }
    }

    if((c=morcnc())!=0){
      cncchr();
      switch (c) {
      case 'A':
	prompt(ABOUT,NULL);
	if(remexp && sysvar->pswexpiry){
	  prompt(PASSXP);
	  if(thisuseracc.passexp>0){
	    prompt(PXPDAYS,thisuseracc.passexp,
		   getpfix(DAYSNG,thisuseracc.passexp));
	  } else {
	    prompt(PEXPIRED);
	  }
	}
	break;
      case 'C':
	editaccount();
	break;
      case 'P':
	changepassword(uacc->userid,0);
	setpasswordentry(0);
	break;
      case 'S':
	editprefs();
	break;
      case 'T':
	transfercredits();
	break;
      case 'V':
	showstats();
	break;
      case 'O':
	if(haskey(&thisuseracc,syskey))passother();
	else {
	  prompt(ERRSEL,c);
	  endcnc();
	  continue;
	}
	break;
      case 'X':
	prompt(LEAVE,NULL);
	return 0;
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
  return 0;
}


int
login(int argc, char *argv[])
{
  if(remexp && sysvar->pswexpiry){
    if(thisuseracc.passexp>0){
      prompt(EXPDAYS,thisuseracc.passexp,getpfix(DAYSNG,thisuseracc.passexp));
    } else {
      if(strexp){
	prompt(PASSEX);
	changepassword(uacc->userid,1);
      } else prompt(EXPIRED);
    }
  }
  return 0;
}


void
done()
{
  clsmsg(msg);
  exit(0);
}


void
main(int argc, char *argv[])
{
  setprogname(argv[0]);
  init();
  if(argc>1 && !strcmp(argv[1],"-login"))login(argc,argv);
  else run(argc,argv);
  done();
}
