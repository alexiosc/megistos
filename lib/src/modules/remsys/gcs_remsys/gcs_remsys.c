/*****************************************************************************\
 **                                                                         **
 **  FILE:     gcs_remsys.c                                                 **
 **  AUTHORS:  Alexios                                                      **
 **  PURPOSE:  The Remote Sysop global commands                             **
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
 * Revision 1.1  2001/04/16 14:58:07  alexios
 * Initial revision
 *
 * Revision 0.1  2000/12/08 15:12:38  alexios
 * Initial checkin.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
const char *__RCS=RCS_VER;
#endif


#include <bbsinclude.h>
#include <bbs.h>
#include <mbk_sysvar.h>


int
gcs_invis()
{
  if(margc==1 && sameas(margv[0],"/invis")){
    if(hassysaxs(&thisuseracc,USY_INVIS)){
      thisuseronl.flags^=OLF_INVISIBLE;
      msg_set(msg_sys);
      prompt((thisuseronl.flags&OLF_INVISIBLE)?INVON:INVOFF);
      msg_reset();
      return 1;
    }
  }
  return 0;
}


int
gcs_gdet()
{
  int  kgdnam, kgdcom, kgdadr, kgdpho, kgdage, kgdsex;
  int  kgdpss, kgdpass;
  static char userid[32];
  useracc_t usracc, *uacc=&usracc;
  char wh[80],age[80],sex[80];
  char s1[80],s2[80],s3[80],s4[80];
  char d1[80],d2[80];
  char sys[80],ns[80],lang[80];

  if(margc==2 && sameas(margv[0],"/l") && hassysaxs(&thisuseracc,USY_GDET)){
    memset(userid,0,sizeof(userid));
    strcpy(userid,margv[1]);
    usr_uidxref(userid,0);
    if(!usr_exists(userid)){
      msg_set(msg_sys);
      prompt(GDETUR,userid);
      msg_reset();
      return 1;
    }
    if(!usr_insys(userid,0))usr_loadaccount(userid,uacc);
    else uacc=&othruseracc;

    msg_set(msg_sys);

    kgdnam=msg_int(KGDNAM,0,129);
    kgdcom=msg_int(KGDCOM,0,129);
    kgdadr=msg_int(KGDADR,0,129);
    kgdpho=msg_int(KGDPHO,0,129);
    kgdage=msg_int(KGDAGE,0,129);
    kgdsex=msg_int(KGDSEX,0,129);
    kgdpss=msg_int(KGDPSS,0,129);
    kgdpass=msg_bool(KGDPASS);

    strcpy(wh,msg_get(GDETNAX));
    strcpy(sex,uacc->sex==USX_MALE?msg_get(GDETM):msg_get(GDETF));
    memset(s1,0,sizeof(s1));
    if(uacc->flags&UFL_SUSPENDED)strcpy(s1,msg_get(GDETSUSP));
    memset(s2,0,sizeof(s2));
    if(uacc->flags&UFL_EXEMPT)strcpy(s2,msg_get(GDETXMPT));
    memset(s3,0,sizeof(s3));
    if(uacc->flags&UFL_DELETED)strcpy(s3,msg_get(GDETDEL));
    memset(s4,0,sizeof(s3));
    if(uacc->sysaxs[0]||uacc->sysaxs[1]||uacc->sysaxs[2])
      strcpy(s4,msg_get(GDETOP));
    strcpy(sys,msg_get(GDETS1+uacc->system-1));
    ns[0]=0;
    if(uacc->prefs&UPF_NONSTOP)strcpy(ns,msg_get(GDETNST));
    strcpy(lang,msg_get(GDETL1+uacc->language-1));
    sprintf(age,"%d",uacc->age);

    strcpy(d1,strdate(uacc->datecre));
    strcpy(d2,(uacc->datelast>=0)?strdate(uacc->datelast):"");
    prompt(GDET,userid,
	   d1,s1,s2,
	   d2,s3,s4,
	   (key_owns(&thisuseracc,kgdnam)?uacc->username:wh),
	   (key_owns(&thisuseracc,kgdcom)?uacc->company:wh),
	   (key_owns(&thisuseracc,kgdadr)?uacc->address1:wh),
	   (key_owns(&thisuseracc,kgdadr)?uacc->address2:wh),
	   (key_owns(&thisuseracc,kgdpho)?uacc->phone:wh),
	   (key_owns(&thisuseracc,kgdage)?age:wh),
	   (key_owns(&thisuseracc,kgdsex)?sex:wh),
	   sys,uacc->scnwidth,uacc->scnheight,ns,
	   lang,uacc->curclss,
	   ((!kgdpass)&&key_owns(&thisuseracc,kgdpss)?uacc->passwd:wh),
	   uacc->credits,uacc->totpaid);
    
    msg_reset();
    return 1;
  }
  return 0;
}


int
gcs_remsys()
{
  if(margc==1 &&
     (sameas(margv[0],"/olympos")||sameas(margv[0],"/hypermenu")||
      sameas(margv[0],"/@"))){
    int i,j;
    
    for(i=j=0;i<sizeof(thisuseracc.sysaxs)/sizeof(long);i++)
      j|=thisuseracc.sysaxs[i];

    if(j){
      char dummy[16];
      char lock[256];
      int i;

      sprintf(lock,"LCK-remsys-%s",thisuseronl.channel);
      i=lock_check(lock,dummy);
      if(i>0 || i==LKR_OWN){
	msg_set(msg_sys);
	prompt(REMSERR);
	msg_reset();
	return 1;
      }
      runmodule(REMSYSBIN);
      lock_rm(lock);
      return 1;
    }
  }
  return 0;
}


int
gcs_audit()
{
  if(!hassysaxs(&thisuseracc,USY_PAGEAUDIT))return 0;
  if(margc&&sameas(margv[0],"/audit")){
    if(margc==1){
      msg_set(msg_sys);
      prompt(AUDITHLP);
      msg_reset();
      return 1;
    } else if(margc==2){
      msg_set(msg_sys);
      if(sameas("o",margv[1])){
	thisuseracc.auditfiltering&=~AUF_SEVERITY;
	prompt(AUDITOFF);
      } else if(sameto("e",margv[1])){
	thisuseracc.auditfiltering&=~AUF_SEVERITY;
	thisuseracc.auditfiltering|=AUF_EMERGENCY;
	prompt(AUDITE);
      } else if(sameto("c",margv[1])){
	thisuseracc.auditfiltering&=~AUF_SEVERITY;
	thisuseracc.auditfiltering|=AUF_EMERGENCY|AUF_CAUTION;
	prompt(AUDITC);
      } else if(sameto("i",margv[1])){
	thisuseracc.auditfiltering|=AUF_SEVERITY;
	prompt(AUDITI);
      } else prompt(AUDITHLP);
    } else prompt(AUDITHLP);
    msg_reset();
    return 1;
  }
  return 0;
}


/** The entry point to this global command handler */

int
__INIT_GCS__()
{
  if(gcs_invis())return 1;
  if(gcs_gdet())return 1;
  if(gcs_remsys())return 1;
  if(gcs_audit())return 1;
  
  return 0;
}
