/*****************************************************************************\
 **                                                                         **
 **  FILE:     usercleanup.c                                                **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, March 95                                                  **
 **  PURPOSE:  Perform cleanup on users' accounts                           **
 **  NOTES:    Actions performed:                                           **
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
 * Revision 1.1  2001/04/16 14:54:27  alexios
 * Initial revision
 *
 * Revision 1.6  1998/12/27 15:18:42  alexios
 * One minor fix.
 *
 * Revision 1.5  1998/07/24 10:08:41  alexios
 * Upgraded to version 0.6 of library.
 *
 * Revision 1.4  1997/11/06 20:09:18  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 1.3  1997/11/06 16:48:39  alexios
 * Switched audit() calls to the new auditing scheme.
 *
 * Revision 1.2  1997/09/14 13:46:51  alexios
 * Fixed bug that would SIGSEGV when deleting a user because
 * thisuseronl was NULL.
 *
 * Revision 1.1  1997/08/30 12:53:50  alexios
 * Changed bladcommand() calls to bbsdcommand().
 *
 * Revision 1.0  1997/08/26 15:47:25  alexios
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
#define WANT_CTYPE_H 1
#define WANT_STRINGS_H 1
#define WANT_DIRENT_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include "bbs.h"


#define DAYSSINCEFILE ".LAST.CLEANUP"


/*                   123456789012345678901234567890 */
#define AUS_USERCUB "USER ACCOUNT CLEANUP"
#define AUS_USERCUE "END OF USER ACCOUNT CLEANUP"

/*                   1234567890123456789012345678901234567890123456789012... */
#define AUD_USERCUB "%d day(s) since last user cleanup"
#define AUD_USERCUE "%d out of %d users modified"

#define AUT_USERCUB (AUF_INFO|AUF_EVENT|AUF_ACCOUNTING)
#define AUT_USERCUE (AUF_INFO|AUF_EVENT|AUF_ACCOUNTING)


struct top *topcreds, *toppaid, *toptimever, *topcredsever, *topfilesdnl;
struct top *topfilesupl, *topbytesdnl, *topbytesupl, *topmsgs, *topconn;
struct top *topold;


int  dayssince=1;
int  numusers=0;
int  nummodified=0;


void
inittop(struct top **t)
{
  (*t)=(struct top *)alcmem(sizeof(struct top)*TOP_N_ENTRIES);
  memset((*t),0,sizeof(struct top)*TOP_N_ENTRIES);
}


void
entertop(struct top *t, char *label, char *scorestg, int score)
{
  int i,j;
  for(i=0;i<TOP_N_ENTRIES-1;i++){
    if(score>t[i].score){
      for(j=TOP_N_ENTRIES-1;j>i;j--)memcpy(&t[j],&t[j-1],sizeof(struct top));
      strcpy(t[i].label,label);
      strcpy(t[i].scorestg,scorestg);
      t[i].score=score;
      break;
    }
  }
}


void
savetop(struct top *t, char *dir, char *name)
{
  FILE *fp;
  int i;
  char fname[256],command[256];

  sprintf(fname,"%s/%s",dir,name);
  if((fp=fopen(fname,"w"))==NULL)return;
  for(i=0;i<TOP_N_ENTRIES;i++){
    if(t[i].label[0])fprintf(fp,"%9s  %s\n",t[i].scorestg,t[i].label);
  }
  fclose(fp);
  if((!getuid())||(!getgid())){
    sprintf(command,"chown bbs.bbs %s >&/dev/null",fname);
    system(command);
  }
}


char *
ltoa(long l)
{
  static char res[20];
  sprintf(res,"%ld",l);
  return res;
}


void
init()
{
  char fname[256];
  FILE *fp;
  int cof=cofdate(today());

  initmodule(INITTTYNUM|INITOUTPUT|INITSYSVARS|INITERRMSGS|INITCLASSES);

  printf("User account cleanup\n\n");

  sprintf(fname,"%s/%s",USRDIR,DAYSSINCEFILE);
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
  printf("Days since last cleanup: %d\n\n",dayssince);
}


void
usercleanup()
{
  FILE     *fp, *ufp;
  char     command[256], name[256], fname[256];
  useracc  usracc, *uacc=&usracc;
  int      numdays, pass;
  classrec *ourclass;
  int      langstats[NUMLANGUAGES]={0};
  int      ANSIstats=0;
  int      visualstats=0;
  int      malestats=0;
  int      corpstats=0;
  int      sysaxstats=0;
  int      suspstats=0;
  int      exemptstats=0;
  int      agestats[5][8];

  bzero(agestats,sizeof(agestats));
  setauditfile(CLNUPAUDITFILE);
  audit("CLEANUP",AUDIT(USERCUB),dayssince);

  inittop(&topcreds);
  inittop(&toppaid);
  inittop(&toptimever);
  inittop(&topcredsever);
  inittop(&topfilesdnl);
  inittop(&topfilesupl);
  inittop(&topbytesdnl);
  inittop(&topbytesupl);
  inittop(&topmsgs);
  inittop(&topconn);
  inittop(&topold);

  sprintf(command,"\\ls %s",USRDIR);
  if((fp=popen(command,"r"))==NULL)return;

  while(!feof(fp)){
    if(fscanf(fp,"%s",name)==1){
      int save=0;

      printf("USERID:   %s\n",name);
      numusers++;

      uacc=&usracc;
      if(!uinsys(name,0)){
	sprintf(fname,"%s/%s",USRDIR,name);
	if((ufp=fopen(fname,"r"))==NULL){
	  fclose(ufp);
	  continue;
	}
	if((fread(uacc,sizeof(useracc),1,ufp))!=1){
	  fclose(ufp);
	  continue;
	}
	fclose(ufp);
      }else uacc=&othruseracc;
      
      printf("NAME:     %s: %s\n",uacc->userid,uacc->username);
      if(dayssince){
	save=1;
	nummodified++;

	uacc->passexp=max(uacc->passexp-dayssince,0);
	printf("PASSEXP:  %s: %ld day(s)\n",name,uacc->passexp);

	if(uacc->timetdy){
	  printf("TIMETDAY: %s: %ld min(s)\n",name, uacc->timetdy);
	  uacc->timetdy=0;
	}
	
	uacc->classdays+=dayssince;
	printf("INCLASS:  %s: %ld day(s)\n",name,uacc->classdays);

	if(strcmp(uacc->tempclss,uacc->curclss)){
	  printf("TMPCLASS: %s: %s reverts-to %s\n",name,uacc->curclss,
		 uacc->tempclss);
	  strcpy(uacc->curclss,uacc->tempclss);
	}

	if((ourclass=findclass(uacc->curclss))!=NULL){
	  if(uacc->classdays>=ourclass->ardays){
	    printf("AROUND:   %s: %ld day(s)\n",name, uacc->classdays);
	    if(strcmp(uacc->curclss,ourclass->around)){
	      printf("ARCLASS:  %s: %s moves-to %s\n",name,
		     uacc->curclss,ourclass->around);
	      audit("CLEANUP",AUDIT(NEWCLSS),uacc->userid,uacc->curclss,
		    ourclass->around);
	      strcpy(uacc->curclss,ourclass->around);
	      strcpy(uacc->tempclss,ourclass->around);
	      uacc->classdays=0;
	    }
	  } else if(uacc->datelast>0 && ourclass->nadays>=0){
	    numdays=max(0,cofdate(today())-cofdate(uacc->datelast));
	    printf("NAROUND:  %s: %d day(s)\n",name,numdays);
	    if(strcmp(uacc->curclss,ourclass->around)){
	      if(numdays>ourclass->nadays){
		printf("NACLASS:  %s: %s moves-to %s\n",name,
		       uacc->curclss,ourclass->notaround);
		audit("CLEANUP",AUDIT(NEWCLSS),uacc->userid,uacc->curclss,
		      ourclass->notaround);
		strcpy(uacc->curclss,ourclass->notaround);
		strcpy(uacc->tempclss,ourclass->notaround);
		uacc->classdays=0;
	      }
	    }
	  }

	  if(uacc->credits<ourclass->crdperday){
	    int amount=ourclass->crdperday-uacc->credits;
	    uacc->credits+=amount;
	    uacc->totcreds+=amount;
	    sysvar->tcreds+=amount;
	    printf("DAYPOST:  %s: %d credits-posted\n",name,amount);
	    audit("CLEANUP",AUDIT(CRDPOST),amount,
		  "FREE",uacc->userid);
	  }

	  if(ourclass->crdperweek&&((cofdate(today())-3)%7==0)){
	    uacc->credits+=ourclass->crdperweek;
	    uacc->totcreds+=ourclass->crdperweek;
	    printf("WEEKPOST: %s: %d credits-posted\n",name,
		   ourclass->crdperweek);
	    audit("CLEANUP",AUDIT(CRDPOST),ourclass->crdperweek,
		  "FREE",uacc->userid);
	  }

	  if(ourclass->crdperweek&&(tdday(today())==1)){
	    uacc->credits+=ourclass->crdpermonth;
	    uacc->totcreds+=ourclass->crdpermonth;
	    printf("MNTHPOST: %s: %d credits-posted\n",name,ourclass->
		   crdpermonth);
	    audit("CLEANUP",AUDIT(CRDPOST),ourclass->crdpermonth,
		  "FREE",uacc->userid);
	  }
	}
      }

      if((!(uacc->flags&UFL_EXEMPT)) &&
	 (uacc->flags&UFL_DELETED||(!strcmp(uacc->curclss,DELETEDCLASS)))){
	int i;
	
	if(uinsys(name,0)){
	  bbsdcommand("hangup",othruseronl.channel,"");
	}
	for(i=0;i<20 && uinsys(name,0);i++)usleep(100000);
	if(!uinsys(name,0)){
	  char lowercase[256];
	  char *cp;

	  strcpy(lowercase,uacc->userid);
	  for(cp=lowercase;*cp;cp++)*cp=tolower(*cp);

	  /* thisuseronl.channel is ignored by bbsd -- this is not a
	     bug, the daemon always demands a tty so we give it "-" */

	  bbsdcommand("delete","-",uacc->userid);

	  printf("DELETED:  %s\n",uacc->userid);
	  audit("CLEANUP",AUDIT(USERDEL),
		uacc->userid,uacc->curclss,uacc->credits);
	}
      } else {
	langstats[uacc->language-1]++;
	if(uacc->prefs&UPF_ANSION)ANSIstats++;
	if(uacc->prefs&UPF_VISUAL)visualstats++;
	if(uacc->sex==USX_MALE)malestats++;
	if(uacc->company[0])corpstats++;
	if(uacc->sysaxs[0]||uacc->sysaxs[1]||uacc->sysaxs[2])sysaxstats++;
	if(uacc->flags&UFL_SUSPENDED)suspstats++;
	if(uacc->flags&UFL_EXEMPT)exemptstats++;
	agestats[min(max(0,((uacc->age/10)-1)),4)][(uacc->system-1)]++;
	printf("CLASSN:   %s: %s\n",uacc->userid,uacc->curclss);
      }

      if(save){
	sprintf(fname,"%s/%s",USRDIR,name);
	if((ufp=fopen(fname,"w"))==NULL){
	  fclose(ufp);
	  continue;
	}
	if((fwrite(uacc,sizeof(useracc),1,ufp))!=1){
	  fclose(ufp);
	  continue;
	}
	fclose(ufp);
      }

      entertop(topcreds,uacc->userid,ltoa(uacc->totcreds),uacc->totcreds);
      entertop(toppaid,uacc->userid,ltoa(uacc->totpaid),uacc->totpaid);
      entertop(toptimever,uacc->userid,ltoa(uacc->timever),uacc->timever);
      entertop(topcredsever,uacc->userid,ltoa(uacc->credsever),uacc->credsever);
      entertop(topfilesdnl,uacc->userid,ltoa(uacc->filesdnl),uacc->filesdnl);
      entertop(topfilesupl,uacc->userid,ltoa(uacc->filesupl),uacc->filesupl);
      entertop(topbytesdnl,uacc->userid,ltoa(uacc->bytesdnl),uacc->bytesdnl);
      entertop(topbytesupl,uacc->userid,ltoa(uacc->bytesupl),uacc->bytesupl);
      entertop(topmsgs,uacc->userid,ltoa(uacc->msgswritten),uacc->msgswritten);
      entertop(topconn,uacc->userid,ltoa(uacc->connections),uacc->connections);
      entertop(topold,uacc->userid,strdate(uacc->datecre),
	       0x7fffffff-cofdate(uacc->datecre));

      printf("--------------------------------------");
      printf("----------------------------------\n");
    }
  }
  fclose(fp);

  for(pass=0;pass<2;pass++){
    char dir[256];
    
    if(!pass)strcpy(dir,STATDIR);
    else sprintf(dir,"%s/%ld",STATDIR,tdyear(today()));
    
    savetop(topcreds,dir,"top-credits");
    savetop(toppaid,dir,"top-paidcreds");
    savetop(toptimever,dir,"top-timespent");
    savetop(topcredsever,dir,"top-credsspend");
    savetop(topfilesdnl,dir,"top-filesdnl");
    savetop(topfilesupl,dir,"top-filesupl");
    savetop(topbytesdnl,dir,"top-bytesdnl");
    savetop(topbytesupl,dir,"top-bytesupl");
    savetop(topmsgs,dir,"top-msgswritten");
    savetop(topconn,dir,"top-numconnections");
    savetop(topold,dir,"top-oldestsignups");
  }

  if((fp=fopen(DEMOSTATFILE,"w"))!=NULL){
    int i,j;
    
    for(i=0;i<NUMLANGUAGES;i++)fprintf(fp,"%d\n",langstats[i]);
    fprintf(fp,"%d\n",ANSIstats);
    fprintf(fp,"%d\n",visualstats);
    fprintf(fp,"%d\n",malestats);
    fprintf(fp,"%d\n",corpstats);
    fprintf(fp,"%d\n",sysaxstats);
    fprintf(fp,"%d\n",suspstats);
    fprintf(fp,"%d\n",exemptstats);
    for(j=0;j<8;j++){
      for(i=0;i<5;i++)fprintf(fp,"%5d ",agestats[i][j]);
      fprintf(fp,"\n");
    }
  }
  fclose(fp);

  audit("CLEANUP",AUDIT(USERCUE),nummodified,numusers);
}


void
done()
{
}


void
main(int argc, char *argv[])
{
  setprogname(argv[0]);
  if(argc==2 && !strcmp(argv[1],"-cleanup")){
    init();
    usercleanup();
    done();
  } else {
    fprintf(stderr,"usercleanup: This is a cleanup-only module\n");
  }
}






