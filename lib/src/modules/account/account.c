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
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 1.9  1999/07/18 21:19:02  alexios
 * Changed a few error_fatal() calls to error_fatalsys().
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
const char *__RCS=RCS_VER;
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


promptblock_t *msg;

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


useracc_t *uacc,useraccount;


static void
init()
{
  mod_init(INI_ALL);
  msg=msg_open("account");
  msg_setlanguage(thisuseracc.language);

  syskey=msg_int(SYSKEY,0,129);
  xfkey=msg_int(XFKEY,0,129);
  remexp=msg_bool(REMEXP);
  strexp=msg_bool(STREXP);
  safpsw=msg_bool(SAFPSW);
  strpss=msg_bool(STRPSS);
  minpln=msg_int(MINPLN,3,15);
  mkpswd=msg_bool(MKPSWD);
  mkpwdf=msg_bool(MKPWDF);
  lipsko=msg_int(LIPSKO,1,32767);
  lognam=msg_bool(LOGNAM);
  logcmp=msg_bool(LOGCMP);
  logadr=msg_bool(LOGADR);
  logphn=msg_bool(LOGPHN);
  logage=msg_bool(LOGAGE);
  logsex=msg_bool(LOGSEX);
  logsys=msg_bool(LOGSYS);
  demcxf=msg_bool(DEMCXF);
  mincxf=msg_int(MINCXF,0,1000000);
  maxcxf=msg_int(MAXCXF,0,1000000);

  uacc=&thisuseracc;
}


void
editaccount()
{
  useracc_t tempacc;

  memcpy(&tempacc,uacc,sizeof(tempacc));

  sprintf(inp_buffer,"%s\n%s\n%s\n%s\n%s\n%d\n%s\n%s\nOK\nCancel\n",
	  tempacc.username,
	  tempacc.company,
	  tempacc.address1,
	  tempacc.address2,
	  tempacc.phone,
	  tempacc.age,
	  msg_get(tempacc.sex=='M'?SEXM:SEXF),
	  msg_get(tempacc.system-1+SYS1));

  if(dialog_run("account",ACCVT,ACCLT,inp_buffer,MAXINPLEN)!=0){
    error_log("Unable to run data entry subsystem");
    return;
  }

  dialog_parse(inp_buffer);

  if (sameas(margv[10],"OK") || sameas (margv[10],margv[8])) { 
    int j;
    strcpy(tempacc.username,margv[0]);
    strcpy(tempacc.company,margv[1]);
    strcpy(tempacc.address1,margv[2]);
    strcpy(tempacc.address2,margv[3]);
    strcpy(tempacc.phone,margv[4]);
    tempacc.age=atoi(margv[5]);
    tempacc.sex=(strcmp(margv[6],msg_get(SEXF))?'M':'F');
    
    for(j=0;j<8;j++)if(!strcmp(margv[7],msg_get(SYS1+j))){
      tempacc.system=j+1;
      break;
    }

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
  } else {
    prompt(EDITCAN);
    return;
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
  if((fp=fopen(mkfname(BADPASSFILE),"r"))==NULL)return 0;
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
  if(!usr_insys(userid,0)){
    uacc=&useraccount;
    usr_loadaccount(userid,uacc);
  }

  if(sameas(userid,uid)){
    for(retries=1;;retries++){
      do{
	prompt(PSCUR);
	inp_setflags(INF_PASSWD);
	inp_get(15);
	inp_clearflags(INF_PASSWD);
      }while(inp_reprompt());
      if(!sameas(inp_buffer,uacc->passwd)){
	prompt(CPSERR);
	if(!login)return;
	else if(retries>=lipsko){
	  prompt(PSWKO);
	  audit(thisuseronl.channel,AUDIT(BLGPWCH),
		thisuseracc.userid,channel_baudstg(thisuseronl.baudrate));
	  channel_disconnect(thisuseronl.emupty);
	}
      } else break;
    }
  }

  prompt(PREPSW,NULL);
  strcpy(passwd,makeapass());
  strcpy(recommended,passwd);
  cnc_end();
  for(;;){
    if(mkpswd && mkpwdf){
      prompt(FRCPSW,recommended,NULL);
    } else {
      if(mkpswd)prompt(RECPSW,recommended,NULL);
      inp_setflags(INF_PASSWD);
      prompt(GPSWORD,NULL);
      inp_get(15);
      inp_clearflags(INF_PASSWD);
      if(!margc || inp_isX(margv[0])){
	inp_clearflags(INF_PASSWD);
	if(!login){
	  prompt(PNOTSET);
	  return;
	} else {
	  cnc_end();
	  continue;
	}
      }
      inp_raw();
      
      if(safpsw){
	int i,d=0;
	if(strlen(inp_buffer)<minpln){
	  prompt(BADPSW1,NULL);
	  continue;
	}
	if(!strpss)d++;
	else {
	  for(i=0,d=0;inp_buffer[i];i++)
	    if(isupper(inp_buffer[i])||!isalpha(inp_buffer[i]))d++;
	}
	if(!d){
	  prompt(BADPSW1,NULL);
	  continue;
	}
	if(stupidpass(inp_buffer)){
	  prompt(BADPSW2,NULL);
	  continue;
	}
	strcpy(passwd,inp_buffer);
	if(sameas(uacc->passwd,passwd)){
	  prompt(BADPSW4);
	  continue;
	}
      }
    }
    prompt(GPSWAGN,NULL);
    inp_setflags(INF_PASSWD);
    inp_get(15);
    inp_clearflags(INF_PASSWD);
    inp_raw();
    if(!sameas(inp_buffer,passwd)){
      prompt(BADPSW3,NULL);
      inp_setflags(INF_PASSWD);
      if(!login){
	prompt(PNOTSET);
	return;
      } else {
	cnc_end();
	continue;
      }
    }
    break;
  }
  inp_clearflags(INF_PASSWD);
  strcpy(uacc->passwd,passwd);
  uacc->passexp=sysvar->pswexpiry;

  if(!usr_exists(userid))return;
  if(!usr_insys(userid,0))usr_saveaccount(uacc);
  prompt(PSWEPI);
  if(strcmp(userid,uid)){
    audit(thisuseronl.channel,AUDIT(PASSOTH),uid,userid);
  }
}


void
resetbbslib()
{
  char tmp[256];
  
  msg_close(msg);
  msg=msg_open("account");
  msg_setlanguage(thisuseracc.language);
  if((thisuseracc.prefs&(UPF_ANSIDEF|UPF_ANSIASK))==0){
    SETVALUE(thisuseronl.flags,OLF_ANSION,thisuseracc.prefs&UPF_ANSION);
    if(thisuseronl.flags&OLF_ANSION)out_setflags(1);
    else out_clearflags(0);
  }
  fmt_setverticalformat((thisuseracc.prefs&UPF_NONSTOP)==0);
  if((thisuseracc.prefs&UPF_NONSTOP)==0)out_setflags(OFL_WAITTOCLEAR);
  else out_clearflags(OFL_WAITTOCLEAR);
  
  sprintf(tmp,"%s rows %d columns %d ixon ixoff",STTYBIN,
	  uacc->scnheight,uacc->scnwidth);
  system(tmp);
  sprintf(tmp,"%d",uacc->scnwidth);
  setenv("COLUMNS",tmp,1);
  sprintf(tmp,"%d",uacc->scnheight);
  setenv("ROWS",tmp,1);
  fmt_setlinelen(uacc->scnwidth);
  fmt_setscreenheight(uacc->scnheight);

  if((thisuseracc.prefs&(UPF_TRDEF|UPF_TRASK))==0)
    out_setxlation(usr_getpxlation(thisuseracc));
}


void
editprefs()
{
  useracc_t tempacc;
  char tmp[2048];
  int i;

  memcpy(&tempacc,uacc,sizeof(tempacc));

  inp_buffer[0]='\0';
  if(tempacc.prefs&UPF_ANSIDEF)sprintf(tmp,"%s\n",msg_get(ANSDEF));
  else if(tempacc.prefs&UPF_ANSIASK)sprintf(tmp,"%s\n",msg_get(ANSASK));
  else if(tempacc.prefs&UPF_ANSION)sprintf(tmp,"%s\n",msg_get(ANSON));
  else sprintf(tmp,"%s\n",msg_get(ANSOFF));
  strcat(inp_buffer,tmp);

  if(tempacc.prefs&UPF_TRDEF)sprintf(tmp,"%s\n",msg_get(TRDEF));
  else if(tempacc.prefs&UPF_TRASK)sprintf(tmp,"%s\n",msg_get(TRASK));
  else sprintf(tmp,"%s\n",msg_get(TR0+usr_getpxlation(tempacc)));
  strcat(inp_buffer,tmp);

  sprintf(tmp,"%s\n%s\n%s\n%d\n%d\n",
	  (tempacc.prefs&UPF_NONSTOP?"on":"off"),
	  (tempacc.prefs&UPF_VISUAL?"on":"off"),
	  msg_get(LANG1+tempacc.language-1),
	  tempacc.scnwidth,
	  tempacc.scnheight);
  strcat(inp_buffer,tmp);
  
  sprintf(tmp,"%s\n%d\nOK\nCancel\n",
	  msg_get(PGSSTR+tempacc.pagestate),
	  tempacc.pagetime);
  strcat(inp_buffer,tmp);

  if(dialog_run("account",PRFVT,PRFLT,inp_buffer,MAXINPLEN)<0){
    error_log("Unable to run data entry subsystem");
    return;
  }

  dialog_parse(inp_buffer);

  if (sameas(margv[11],"OK") || sameas (margv[11],margv[9])) { 
    for(i=0;i<12;i++){
      char *s=margv[i];

      if(i==0){
	SETVALUE(tempacc.prefs,UPF_ANSIDEF,sameas(s,msg_get(ANSDEF)));
	SETVALUE(tempacc.prefs,UPF_ANSIASK,sameas(s,msg_get(ANSASK)));
	SETVALUE(tempacc.prefs,UPF_ANSION,sameas(s,msg_get(ANSON)));
      } else if(i==1){
	int n;
	SETVALUE(tempacc.prefs,UPF_TRDEF,sameas(s,msg_get(TRDEF)));
	SETVALUE(tempacc.prefs,UPF_TRASK,sameas(s,msg_get(TRASK)));
	for(n=0;n<NUMXLATIONS;n++){
	  if(sameas(s,msg_get(TR0+n))){
	    usr_setpxlation(tempacc,n);
	    break;
	  }
	}
      } else if(i==2)SETVALUE(tempacc.prefs,UPF_NONSTOP,sameas(s,"on"));
      else if(i==3)SETVALUE(tempacc.prefs,UPF_VISUAL,sameas(s,"on"));
      else if(i==4){
	int j;
	for(j=0;j<10;j++)if(!strcmp(s,msg_get(LANG1+j))){
	  tempacc.language=j+1;
	  break;
	}
      } else if(i==5)tempacc.scnwidth=atoi(s);
      else if(i==6)tempacc.scnheight=atoi(s);
      else if(i==7){
	int j,k[4]={PGS_STORE,PGS_OK,PGS_ON,PGS_OFF};
	for(j=0;j<4;j++)if(!strcmp(s,msg_get(PGSSTR+j))){
	  tempacc.pagestate=k[j];
	  break;
	}
      } else if(i==8)tempacc.pagetime=atoi(s);
    }

    memcpy(uacc,&tempacc,sizeof(tempacc));
    if(sameas(uacc->userid,thisuseracc.userid))resetbbslib();
    prompt(EDITOK);
  } else {
    prompt(EDITCAN);
  }
}


void
transfercredits()
{
  int num, yes;
  char userid[80];
  useracc_t ruseracc, *ruacc=&ruseracc;
  classrec_t *class=cls_find(uacc->curclss);

  if(uacc->credits<mincxf){
    prompt(XFERR1,mincxf);
    return;
  } else if((class->flags&CLF_CRDXFER)==0){
    prompt(XFERR2);
    return;
  } else if(!key_owns(uacc,xfkey)){
    prompt(XFERR2);
    return;
  } else if(!(demcxf||uacc->totpaid)){
    prompt(XFERR3);
    return;
  }

  if(!get_number(&num,CREDTR,mincxf,min(uacc->credits-1,maxcxf),NUMERR,0,0)){
    prompt(CXFABO);
    return;
  }
  if(uacc->credits<mincxf){
    prompt(RANOUT);
    return;
  }

  for(;;){
    if(!get_userid(userid,CTWHO,UIDERR,0,NULL,0)){
      prompt(CXFABO);
      return;
    }
    if(sameas(userid,uacc->userid)){
      prompt(CTNSELF);
      continue;
    } else break;
  }

  if(!usr_insys(userid,0))usr_loadaccount(userid,ruacc);
  else ruacc=&othruseracc;

  class=cls_find(ruacc->curclss);
  if(ruacc->credits<mincxf || (!key_owns(ruacc,xfkey)) ||
     (!(demcxf||uacc->totpaid)) || ((class->flags&CLF_CRDXFER)==0))
    prompt(CTWARN,userid);
  
  prompt(CTCONF,num,uacc->userid,userid);
  
  if(!get_bool(&yes,CTCQUE,BOOLERR,0,0) || (!yes)){
    prompt(CXFABO);
    return;
  }

  if(!usr_exists(userid)){
    prompt(ACCDEL,userid);
    return;
  } else {
    ruacc=&ruseracc;
    if(!usr_insys(userid,0))usr_loadaccount(userid,ruacc);
    else ruacc=&othruseracc;

    if(num>=uacc->credits){
      prompt(NOENOT,uacc->credits);
      num=uacc->credits-1;
    }

    uacc->credits-=num;
    usr_postcredits(userid,num,CRD_FREE);
    audit(thisuseronl.channel,AUDIT(CRDXFER),uacc->userid,num,userid);
    prompt(CXFOK,num,uacc->userid,userid);
    if(usr_insys(userid,0)){
      char injbuf[16384];

      sprompt_other(othrshm,injbuf,CXFINJ,uacc->userid,num);
      if(usr_injoth(&othruseronl,injbuf,0))prompt(NOTICE,ruacc->userid);
    }
  }
}


void
showstats()
{
  char p1[80],p2[80],p3[80],p4[80];
  char buf[16384];
  int nod=cofdate(today())-cofdate(uacc->datecre);
  classrec_t *class=cls_find(uacc->curclss);

  prompt(ACCST1);

  if(uacc->datecre!=today()){
    sprompt(p1,DAYSNG+(nod!=1));
    sprompt(p2,TIMSNG+(uacc->connections!=1));
    sprompt(p3,DAYSNG+(uacc->passexp!=1));
    sprompt(out_buffer,ACCST2,nod,p1,p2,p3);
  } else sprompt(out_buffer,ACCST2A,msg_getunit(DAYSNG,uacc->passexp));
  strcat(buf,out_buffer);

  strcpy(p1,msg_getunit(CRDSNG,uacc->credits));
  strcpy(p2,msg_getunit(CRDSNG,uacc->totcreds));
  strcpy(p3,msg_getunit(CRDSNG,uacc->credsever));
  strcpy(p4,msg_getunit(MINSNG,uacc->timever));
  sprompt(out_buffer,ACCST3,p1,p2,p3,p4);
  strcat(buf,out_buffer);

  strcpy(p1,msg_getunit(FILSNG,uacc->filesdnl));
  strcpy(p2,msg_getunit(FILSNG,uacc->filesupl));
  sprompt(out_buffer,ACCST4,p1,p2);
  strcat(buf,out_buffer);
  
  strcat(buf,msg_get(ACCST5A));
  if(class->limpercall>=0){
    sprompt(out_buffer,ACCST5B,class->limpercall,
	    msg_getunit(MINSNG,class->limpercall));
    strcat(buf,out_buffer);
  }
  if(class->limperday>=0){
    sprompt(out_buffer,ACCST5C,class->limperday,
	    msg_getunit(MINSNG,class->limperday));
    strcat(buf,out_buffer);
  }
  if(class->crdperday){
    char hoften[80];
    strcpy(hoften,msg_get(DAILY));
    sprompt(out_buffer,ACCST5D,class->crdperday,
	    msg_getunit(CRDSNG,class->crdperday),hoften);
    strcat(buf,out_buffer);
  }

  if(class->crdperweek){
    char hoften[80];
    sprompt(hoften,WEEKLY);
    sprompt(out_buffer,ACCST5D,class->crdperweek,
	    msg_getunit(CRDSNG,class->crdperweek),hoften);
    strcat(buf,out_buffer);
  }

  if(class->crdpermonth){
    char hoften[80];
    sprompt(hoften,MNTHLY);
    sprompt(out_buffer,ACCST5D,class->crdpermonth,
	    msg_getunit(CRDSNG,class->crdpermonth),
	    hoften);
    strcat(buf,out_buffer);
  }

  if(class->flags&CLF_NOCHRGE)strcat(buf,msg_get(ACCST5E));
  nod=class->ardays-uacc->classdays;
  if(class->ardays>0){
    sprompt(out_buffer,ACCST5F,nod,msg_getunit(DAYSNG,nod),class->around);
    strcat(buf,out_buffer);
  } else if(!class->ardays){
    sprompt(out_buffer,ACCST5FT,class->around);
    strcat(buf,out_buffer);
  }
  if(class->nadays!=-1){
    sprompt(out_buffer,ACCST5G,class->nadays,
	    msg_getunit(DAYSNG,class->nadays),class->notaround);
    strcat(buf,out_buffer);
  }
  if(strcmp(uacc->curclss,class->nocreds)){
    sprompt(out_buffer,ACCST5H,class->nocreds);
    strcat(buf,out_buffer);
  }
  if(strcmp(uacc->curclss,class->credpost)){
    sprompt(out_buffer,ACCST5I,class->credpost);
    strcat(buf,out_buffer);
  }
  strcat(buf,msg_get(ACCST5J));

  print(buf);
	 
  prompt(ACCST6);
}


void
passother()
{
  char userid[80];

  if(!get_userid(userid,OPSWHO,OUIDERR,0,NULL,0))return;
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
  char c=0;

  init();
  uacc=&thisuseracc;

  for(;;){
    if(!(thisuseronl.flags&OLF_MMCALLING && thisuseronl.input[0])){
      if(!shownmenu){
	prompt(key_owns(&thisuseracc,syskey)?ACCSMNU:ACCMNU,NULL);
	prompt(VSHMENU);
	shownmenu=2;
      }
    } else shownmenu=1;
    if(thisuseronl.flags&OLF_MMCALLING && thisuseronl.input[0]){
      thisuseronl.input[0]=0;
    } else {
      if(!cnc_nxtcmd){
	if(thisuseronl.flags&OLF_MMCONCAT){
	  thisuseronl.flags&=~OLF_MMCONCAT;
	  return 0;
	}
	if(shownmenu==1){
	  prompt(key_owns(&thisuseracc,syskey)?SHSMENU:SHMENU,NULL);
	} else shownmenu=1;
	inp_get(0);
	cnc_begin();
      }
    }

    if((c=cnc_more())!=0){
      cnc_chr();
      switch (c) {
      case 'A':
	prompt(ABOUT,NULL);
	if(remexp && sysvar->pswexpiry){
	  prompt(PASSXP);
	  if(thisuseracc.passexp>0){
	    prompt(PXPDAYS,thisuseracc.passexp,
		   msg_getunit(DAYSNG,thisuseracc.passexp));
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
	inp_clearflags(INF_PASSWD);
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
	if(key_owns(&thisuseracc,syskey))passother();
	else {
	  prompt(ERRSEL,c);
	  cnc_end();
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
	cnc_end();
	continue;
      }
    }
    if(fmt_lastresult==PAUSE_QUIT)fmt_resetvpos(0);
    cnc_end();
  }
  return 0;
}


int
login(int argc, char *argv[])
{
  init();
  if(remexp && sysvar->pswexpiry){
    if(thisuseracc.passexp>0){
      prompt(EXPDAYS,
	     thisuseracc.passexp,
	     msg_getunit(DAYSNG,thisuseracc.passexp));
    } else {
      if(strexp){
	prompt(PASSEX);
	changepassword(uacc->userid,1);
      } else prompt(EXPIRED);
    }
  }
  return 0;
}


extern int handler_cleanup(int,char**);


int handler_userdel(int argc, char **argv)
{
  char *victim=argv[2], fname[1024];

  if(strcmp(argv[1],"--userdel")||argc!=3){
    fprintf(stderr,"User deletion handler: syntax error\n");
    return 1;
  }

  if(!usr_exists(victim)){
    fprintf(stderr,"User deletion handler: user %s does not exist\n",victim);
    return 1;
  }

  sprintf(fname,"%s/%s",mkfname(USRDIR),victim);
  unlink(fname);
  sprintf(fname,"%s/%s",mkfname(RECENTDIR),victim);
  unlink(fname);

  return 0;
}


mod_info_t mod_info_account = {
  "account",
  "User Account Manager",
  "Alexios Chouchoulas <alexios@vennea.demon.co.uk>",
  "Shows and edits user's account and global preferences.",
  RCS_VER,
  "1.0",
  {90,login},			/* Login handler */
  {0,run},			/* Interactive handler */
  {0,NULL},			/* Install logout handler */
  {0,NULL},			/* Hangup handler */
  {0,handler_cleanup},		/* Cleanup handler */
  {99,handler_userdel}		/* Delete user handler */
};


int
main(int argc, char *argv[])
{
  mod_setinfo(&mod_info_account);
  return mod_main(argc,argv);
}
