/*****************************************************************************\
 **                                                                         **
 **  FILE:     upload.c                                                     **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, November 1997, Version 0.1                                **
 **  PURPOSE:  Upload files                                                 **
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
 * Revision 0.5  1999/07/18 21:29:45  alexios
 * Changed a few error_fatal() calls to error_fatalsys(). Completed the
 * upload() code.
 *
 * Revision 0.4  1998/12/27 15:40:03  alexios
 * Added autoconf support. Slight fixes.
 *
 * Revision 0.3  1998/07/24 10:18:32  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 0.2  1998/04/21 10:13:39  alexios
 * Some minor changes to accommodate the for the new state of
 * things in the module.
 *
 * Revision 0.1  1998/04/16 09:27:16  alexios
 * Initial version.
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
#define WANT_FCNTL_H 1
#define WANT_TIME_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "files.h"
#include "mbk_files.h"
#define __ARCHIVERS_UNAMBIGUOUS__
#include "mbk_archivers.h"


#define LIM_CANCEL_ALL     -1
#define LIM_CANCEL_CURRENT -2
#define LIM_OK             0


static int
filewithinlimits(int bytes)
{
  long int nb=(library.libsizelimit<<20)-library.numbytes-library.bytesunapp;
  long int bpf=min(nb,library.filesizelimit<<10);

  if(library.numfiles+library.numunapp>=library.filelimit){
    prompt(UPLXLNF);
    return LIM_CANCEL_ALL;
  }

  if(bytes>bpf){
    prompt(UPLXLBF);
    return LIM_CANCEL_CURRENT;
  }

  if(library.numbytes+library.bytesunapp>=(library.libsizelimit<<20)){
    prompt(UPLXLNB);
    return LIM_CANCEL_ALL;
  }

  return LIM_OK;
}


static int
checkfname(char *s)
{
  lowerc(s);
  if(strspn(s,fnchars)!=strlen(s)){
    prompt(FNERR,fnchars);
    return 0;
  }

  if(fileexists(library.libnum,s,0)||fileexists(library.libnum,s,1)){
    prompt(UPLDUP);
    return 0;
  }

  if(library.flags&LBF_DOS83) {
    char *cp=strchr(s,'.');
    if(cp==NULL){
      if((strlen(s)>8) || (*s==0)){
	prompt(FDNDOS);
	return 0;
      }
    } else if((cp-s<1) || (cp-s>8) || (strlen(cp)>4) || (strchr(cp+1,'.')!=NULL)){
      prompt(FDNDOS);
      return 0;
    }
  }
  return 1;
}


 /* Bit of a hack, but some of the functions below are really starting
    to need too many arguments. */

static struct stat st;
static char        *ftype;



static char*
filetype(char *fname)
{
  if(stat(fname,&st)){
    error_fatalsys("Sanity check failed, unable to stat %s",fname);
  }
  return ftype=getfiletype(fname);
}


static void
filehdr(char *fname, struct fileidx *f, char *keywords)
{
  char *filetype=getfiletype(fname);
  struct stat st;
  struct tm *dt;

  dt=localtime((const time_t *)&(f->timestamp));

  bzero(&st,sizeof(st));
  stat(fname,&st);

  prompt(FILEHDR1,f->fname,
	 strdate(makedate(dt->tm_mday,dt->tm_mon+1,1900+dt->tm_year)),
	 strtime(maketime(dt->tm_hour,dt->tm_min,dt->tm_sec),1),
	 f->uploader,
	 f->downloaded,msg_getunit(TIMESNG,f->downloaded),
	 st.st_size);

  if(f->approved)prompt(FILEHDR2,f->approved_by);

  prompt(FILEHDR3,filetype,&keywords[1],f->summary,f->description);
}


static void
fileheader(char *name, int multiple, char *source, int filenum, int numfiles)
{
  /* Print the file information */

  if(multiple){
    char tmp[256], *np;
    int rem=numfiles-filenum;
    if(!rem)strcpy(tmp,msg_get(REMZER));
    else sprintf(tmp,msg_get(rem==1?REMSNG:REMPLR),rem);
    np=strrchr(name,'/');
    if(np)np++;
    else np=name;
    prompt(UPLINFM,filenum,tmp,np,st.st_size,
	   msg_getunit(BYTESNG,st.st_size==1),ftype);
  } else {
    prompt(UPLINF1,
	   source,
	   st.st_size,msg_getunit(BYTESNG,st.st_size==1),
	   ftype);
  }
}


static int
confirmcan()
{
  int yes;
  if(!get_bool(&yes,UPLACN,UPLACR,0,0))return 0;
  if(yes)return 1;
  return 0;
}


static int
getdescr(char *descr)
{
  cnc_end();
  for(;;){
    prompt(UPLSHDS);
    inp_get(43);
    if(!strlen(inp_buffer)&&!accmtsd){
      cnc_end();
      prompt(UPLSDMT);
      continue;
    } else if(inp_isX(inp_buffer)){
      if(confirmcan())return 0;
    } else break;
  }
  inp_raw();
  strcpy(descr,inp_buffer);
  return 1;
}


static char*
editdescr(char *descr)
{
  int fd;
  char fname[256];
  struct stat st;

  sprintf(fname,TMPDIR"/des-%05d",getpid());
  for(;;){
    if((fd=open(fname,O_WRONLY|O_CREAT,0600))<0){
      error_fatalsys("Unable to open() %s for writing.",fname);
    }
    write(fd,descr,strlen(descr));
    close(fd);

    if(editor(fname,deslen)||stat(fname,&st)){
      if(confirmcan()){
	free(descr);
	return NULL;
      }
    } else break;
  }

  free(descr);

  stat(fname,&st);
  descr=alcmem(st.st_size+1);
  bzero(descr,st.st_size+1);
  if((fd=open(fname,O_RDONLY))<0){
    error_fatalsys("Unable to open() %s for reading.",fname);
  }
  read(fd,descr,st.st_size);
  close(fd);
  unlink(fname);
  return descr;
}


static promptblock_t *archivers=NULL;


static char*
getlongdescr(char *fname,char *filetype)
{
  int n, found=0;
  static char *longdescr=NULL;

  /* See if the uploaded archive contains a long description file */

  prompt(UPLDIZW);

  if(!archivers)archivers=msg_open("archivers");

  for(n=0;n<MAXARCHIVERS;n++){
    msg_set(archivers);
    if(strlen(msg_get(ARCHIVERS_UNCOMPRESS1+n*7))&&
       strstr(filetype,msg_get(ARCHIVERS_STRING1+n*7))){
      char dir[256], fmt[256], command[512], *cp;

      sprintf(dir,TMPDIR"/diz-%05d",getpid());
      mkdir(dir,0700);

      sprintf(fmt,"cd %s;%s >&/dev/null;cd -",
	      dir,
	      msg_get(ARCHIVERS_UNCOMPRESS1+n*7));
      sprintf(command,fmt,fname,filedes);
      msg_set(msg);

      system(command);

      strcpy(fmt,filedes);
      cp=strtok(fmt," \n\r\t");
      while(cp){
	struct stat st;
	sprintf(command,"%s/%s",dir,cp);
	if(!stat(command,&st)){
	  FILE *fp;
	  char *des=alcmem(st.st_size);
	  int yes=1;

	  bzero(des,st.st_size);
	  found=1;
	  
	  if((fp=fopen(command,"r"))==NULL){
	    error_fatalsys("Sanity check failed: unable to open %s",command);
	  }

	  while(!feof(fp)){
	    char line[1024], *cp;
	    if(!fgets(line,sizeof(line),fp))break;
	    if((cp=strrchr(line,'\r'))!=NULL)*cp=0;
	    if((cp=strrchr(line,'\n'))!=NULL)*cp=0;
	    cp=&line[strlen(line)];
	    *cp++='\n';
	    *cp=0;
	    strcat(des,line);
	  }
	  fclose(fp);
	  if(strlen(des)>deslen)des[deslen]=0;
	  longdescr=strdup(des);
	  free(des);
	  prompt(UPLDIZF,cp,longdescr);

	  if(!get_bool(&yes,UPLDIZA,UPLDIZR,0,0)){
	    if(confirmcan())return NULL;
	  }
	  if(!yes)longdescr=editdescr(longdescr);
	  
	  break;
	}
	cp=strtok(NULL," \n\r\t");
      }

      sprintf(command,"\\rm -rf %s",dir);
      system(command);
      msg_set(msg);
      if(found)return longdescr;
    }
  }

  msg_set(msg);
  if(!found){
    prompt(UPLLDES,deslen);
    longdescr=strdup("");
    return editdescr(longdescr);
  }
  return NULL;
}


static char *
getkeywords()
{
  static char keywords [2424];	/* Enough for 100 keywords plus */
  int numkeywords=0;

  keywords[0]=0;
  prompt(UPLKEYS);

  for(;numkeywords<=maxkeyw;){
    prompt(UPLKEY,numkeywords+1);
    inp_get(23);
    lowerc(inp_buffer);
    if(!strlen(inp_buffer)){
      cnc_end();
      prompt(UPLKEYC);
      continue;
    } else if(inp_isX(inp_buffer)){
      if(confirmcan())return NULL;
      cnc_end();
      prompt(UPLKEYC);
      continue;
    } else if(sameas(inp_buffer,"?")){
      cnc_end();
      prompt(UPLKEYH,keywords);
      continue;
    } else if(sameas(inp_buffer,".")){
      break;
    } else if(strspn(inp_buffer,KEYWORDCHARS)!=strlen(inp_buffer)||strlen(inp_buffer)>23){
      cnc_end();
      prompt(UPLKEYR);
      continue;
    } else {
      char tmp[2424], *cp;
      int dupl=0;

      strcpy(tmp,keywords);
      for(cp=strtok(tmp," ");cp;cp=strtok(NULL," ")){
	if(!strcmp(cp,inp_buffer)){
	  cnc_end();
	  prompt(UPLKEYD);
	  dupl=1;
	  break;
	}
      }
      if(!dupl){
	sprintf(tmp," %s ",inp_buffer);
	strcat(keywords,numkeywords?&tmp[1]:tmp);
	numkeywords++;
      }
    }
  }
  return keywords;
}



static int
acceptfile (char *name, int multiple, char *origsrc, int filenum, int numfiles)
{
  char source[MAXFILENAMELEN+1];
  char descr[44];
  char *longdescr;
  char *keywords;
  int  approved=0;
  char opt;
  struct fileidx *f;
  

  /* Get file type. This doesn't change, so it's out of the edit 'loop'. */

  filetype(name);
  
edit:

  
  /* Produce information about the file */

  fileheader(name,multiple,origsrc,filenum,numfiles);


  /* Check file size against library limits */

  switch(filewithinlimits(st.st_size)){
  case LIM_CANCEL_ALL:
    return 0;
  case LIM_CANCEL_CURRENT:
    return 1;
  case LIM_OK:
    break;    
  default:
    error_fatal("Sanity check for filewithinlimits() failed!");
  }


  /* Check if the user can pay the charges for the file */

  if(usr_canpay(library.uplcharge)){
    usr_chargecredits(library.uplcharge);
  } else {
    prompt(UPLNCR);
    return 0;			/* Cancel all files if user can't afford uploads */
  }


  /* Check name of file */
  
  strcpy(source,origsrc);

  for(;;){
    char *np=source;
    if(multiple){
      if((np=strrchr(name,'/'))!=NULL)np++;
      else np=name;
    }
    if(!checkfname(np)){
      cnc_end();
      prompt(UPLASK);
      inp_get(MAXFILENAMELEN);
      strcpy(source,inp_buffer);
    } else break;
    if(multiple){		/* Yuk */
      if((np=strrchr(name,'/'))!=NULL)np++;
      else np=name;
    }
    fileheader(name,multiple,origsrc,filenum,numfiles);
  }
  
  
  /* Get the file's short description */
  
  if(!getdescr(descr))return 0;


  /* Get or unpack the long description */

  if((longdescr=getlongdescr(name,ftype))==NULL)return 0;


  /* Get the keywords */

  if((keywords=getkeywords())==NULL)return 0;


  /* Make the file record */

  approved=autoapp(&library);
  f=alcmem(sizeof(struct fileidx));
  bzero(f,sizeof(struct fileidx));
  if(!multiple){
    strcpy(f->fname,source);
  } else {
    char *np=name;
    if((np=strrchr(name,'/'))!=NULL)np++;
    strcpy(f->fname,np);
  }
  f->flibnum=library.libnum;
  f->timestamp=time(NULL);
  f->approved=approved!=0;
  f->descrlen=strlen(longdescr)+1;
  strcpy(f->uploader,thisuseracc.userid);
  if(approved)strcpy(f->approved_by,thisuseracc.userid);
  strcpy(f->summary,descr);
  strcpy(f->description,longdescr);

  /* View the file header and ask for final confirmation */

  filehdr(name,f,keywords);
  for(;;){
    if(!get_menu(&opt,1,0,LASTCON,0,"YNE",LASTCND,'Y')){
      if(confirmcan())return 0;
    } else break;
  }

  if(opt=='E'){
    free(f);
    free(longdescr);
    goto edit;			/* Oh yeah (dirty but saves code size) */
  } else if(opt=='Y'){
    

    /* Insert the file record into the database */

    filecreate(f);


    /* Update the library statistics */

    libinstfile(&library,f,st.st_size,LIF_ADD);


    /* Copy the file to its library directory */

    installfile(name,f->fname,&library);


    /* Add the keywords */

    addkeywords(keywords,autoapp(&library)!=0,f);


    /* Audit it */

    if(library.flags&LBF_UPLAUD){
      char tmp[256];
      sprintf(tmp,AUD_FUPLOK,library.fullname);
      audit(thisuseronl.channel,AUT_FUPLOK,AUS_FUPLOK,tmp,
	    thisuseracc.userid,f->fname);
    }

    /* Notify the user if the file needs approval */

    if(!autoapp(&library))prompt(NEEDSAPP);
  }
  
  return 1;
}


static int
uploadfile(int multiple, char *source)
{
  int res=0;
  int count=0;
  int numfiles=0;
  char fname[256]={0};
  char name[256]={0};
  char dir[256]={0};
  char line[1024];
  char *command=line;
  char *cp;
  FILE *fp;

  /* Set the audit trail entries */

  if(library.flags&LBF_UPLAUD){
    char tmp[256];
    sprintf(tmp,AUD_FUPLERR,library.fullname);
    xfer_setaudit(0,NULL,NULL,AUT_FUPLERR,AUS_FUPLERR,tmp);
  } else xfer_setaudit(0,NULL,NULL,0,NULL,NULL);


  /* Prepare for the upload */

  if(multiple)strcpy(source,"*");
  xfer_add(FXM_UPLOAD,source,"",0,0);


  /* Force use of multi-file protocols */

  if(multiple)xfer_add(FXM_UPLOAD,source,"",0,0);


  /* Do the file transfer */

  xfer_run();


  /* Scan the uploaded file(s) */
  
  sprintf(fname,XFERLIST,getpid());
  
  if((fp=fopen(fname,"r"))==NULL){
    prompt(UPLCAN);
    goto kill;
  }


  /* Count the number of uploaded files */

  numfiles=-1;
  while(!feof(fp))if(fgets(line,sizeof(line),fp))numfiles++;


  /* Process the uploaded files */

  rewind(fp);
  while (!feof(fp)){
    if(fgets(line,sizeof(line),fp)){
      if((cp=strchr(line,'\n'))!=NULL)*cp=0;
      if(!count)strcpy(dir,line);
      else {
	if(!acceptfile(line,multiple,source,count,numfiles)){
	  prompt(count>1?UPLCAN1:UPLCAN);
	  fclose(fp);
	  goto kill;
	}
      }
      count++;
    }
  }
  
  fclose(fp);
  

  /* Kill remaining transfer files */

 kill:
  sprintf(command,"\\rm -rf %s %s",fname,dir);
  system(command);
  if(name[0]){
    sprintf(command,"rm -f %s >&/dev/null",name);
    system(command);
  }
  xfer_kill_list();
  return res;
}


static char *
getuploadfname(int *multiple)
{
  char *fn=inp_buffer;
  
  *multiple=0;
  for(;;){
    if(cnc_more())fn=cnc_word();
    else {
      prompt(UPLASK);
      inp_get(MAXFILENAMELEN);
      fn=inp_buffer;
    }

    if(inp_isX(fn))return NULL;

    if(!strlen(fn)){
      cnc_end();
      continue;
    }

    if(strchr(fn,'*')){
      *multiple=1;
      break;
    } else if(!checkfname(fn))cnc_end();
    else break;
  }

  return fn;
}


static void
sizewarn()
{
  char files[256], bytes1[256];
  
  /* These WILL print negative values if worse comes to worse. */

  int nf=library.filelimit-library.numfiles-library.numunapp;
  long int nb=(library.libsizelimit<<20)-library.numbytes-library.bytesunapp;
  long int bpf=min(nb,library.filesizelimit<<10);
  
  strcpy(files,msg_getunit(FILESNG,nf));
  strcpy(bytes1,msg_getunit(BYTESNG,nb));

  prompt(SIZEWARN,nf,files,nb,bytes1,bpf,msg_getunit(BYTESNG,bpf));
}


void
upload()
{
  int multiple=0;
  char *fn, *tmp;

  /* Check if library is read-only */

  if(library.flags&LBF_READONLY){
    prompt(LIBRO);
    cnc_end();
    return;
  }

  /* Check if user has upload access to the library */

  if(!getlibaccess(&library,ACC_UPLOAD)){
    prompt(UPLNAX);
    cnc_end();
    return;
  }

  /* Check if the library can take any more files */

  if(library.numfiles>=library.filelimit){
    prompt(LIBFULF);
    return;
  }
  if(library.numbytes>=(library.libsizelimit<<20)){
    prompt(LIBFULB);
    return;
  }

  /* Make sure the user can afford at least one file BEFORE upload */

  if(!usr_canpay(library.uplcharge)){
    prompt(UPLWNCR);
    cnc_end();
    return;
  }

  /* Warn about library limits */
  sizewarn();

  /* Finally, get the uploaded filename */

  if((fn=getuploadfname(&multiple))==NULL)return;
  tmp=strdup(fn);

  uploadfile(multiple,tmp);
  free(tmp);
}
