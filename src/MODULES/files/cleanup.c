/*****************************************************************************\
 **                                                                         **
 **  FILE:     cleanup.c                                                    **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, April 1998                                                **
 **  PURPOSE:  Cleanup code for the file libraries                          **
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
 * Revision 1.2  2001/04/16 21:56:32  alexios
 * Completed 0.99.2 API, dragged all source code to that level (not as easy as
 * it sounds).
 *
 * Revision 0.4  2000/01/06 10:37:25  alexios
 * Lots of bug fixes that caused segmentation faults during
 * cleanup.
 *
 * Revision 0.3  1998/12/27 15:40:03  alexios
 * Added autoconf support.
 *
 * Revision 0.2  1998/04/21 10:13:39  alexios
 * Daily maintenance of the file library.
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
#define WANT_DIRENT_H 1
#define WANT_TIME_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include "bbs.h"
#include "files.h"


#define frac(bytes) ((int)((float)((bytes)%(1<<20))/10485.76))


struct topfiles {
  char text[80];
  int  downloads;
};


int               dayssince;
unsigned int      tot_files=0, tot_bytes=0;
unsigned int      tot_unappfiles=0, tot_unappbytes=0;
unsigned int      tot_dnlfiles=0, tot_dnlbytes=0;
unsigned int      files=0, bytes=0;
unsigned int      unappfiles=0, unappbytes=0;
unsigned int      dnlfiles=0, dnlbytes=0;
struct topfiles  *topfiles;
struct topfiles  *mastertopfiles;
struct libidx     mainlibrary;
FILE             *mastertopfp;
FILE             *masterfilefp;



static void
delfilelst(struct libidx *l)
{
  struct fileidx f;
  bzero(&f,sizeof(f));
  strcpy(f.fname,filelst);
  f.flibnum=l->libnum;
  f.approved=1;
  filedelete(&f);
}


static void
filelst_header(FILE *fp, struct libidx *l)
{
  if(fp==NULL)return;
  fprintf(fp,"MEGISTOS FILE LIBRARY\nFILE DIRECTORY\n\n");
  fprintf(fp,"Directory for library %s:\n%s\n\n",
	  l->fullname,l->descr);
}


static void
listchildren(FILE *fp, struct libidx *l)
{
  struct libidx child;
  int           first=1;
  int           res;
  char          tmp[20];

  if(fp==NULL)return;

  /* Mention the children libraries, if any */
  
  res=libgetchild(l->libnum,"",&child);
  while(res && child.parent==l->libnum){
    if(first){
      first=0;
      fprintf(fp,"SUB-LIBRARIES:\nLibrary name          Description\n"\
	      "---------------------------------------------------"\
	      "----------------------------\n");
    }
    fprintf(fp,"%-20s  %s\n",leafname(child.fullname),child.descr);
    strcpy(tmp,child.keyname);
    res=libgetchild(l->libnum,tmp,&child);
  }
  if(!first)fprintf(fp,"---------------------------------"\
		    "----------------------------------------------\n\n");
}


static FILE *
filelst_open(struct libidx *l)
{
  FILE *fp=NULL;
  char fname[512];

  delfilelst(l);
  sprintf(fname,"%s/%s",l->dir,filelst);
  if((l->flags&LBF_NOINDEX)==0)fp=fopen(fname,"w");
  else fp=NULL;
  if(fp!=NULL) {
    filelst_header(fp,l);
    listchildren(fp,l);
    filelst_header(masterfilefp,l);
    listchildren(masterfilefp,l);
  }

  return fp;
}


static void
filelst_add(FILE *fp, struct libidx *l, struct fileidx *f, int size)
{
  /* Record the file in the file list */
  if(fp==NULL)return;
  if(!files){
    fprintf(fp,"Filename                   "\
	    "Size Uploader   Description\n"\
	    "---------------------------------------------------"\
	    "----------------------------\n");
  }
  fprintf(fp,"%-22.22s %8d %-10.10s %.36s\n",
	  f->fname, size, f->uploader, f->summary);
}


static void
filelst_add_os(FILE *fp, struct libidx *l, int size,
	       char *date, char *time, char *fname)
{
  if(fp==NULL)return;
  if(!files){
    fprintf(fp,"     Size     Date     Time     Filename\n"\
	    "---------------------------------------------------"\
	    "----------------------------\n");
  }
  fprintf(fp,"%9d  %-9.9s %-8.8s   %s\n",size,date,time,fname);
}


static void
filelst_footer(FILE *fp, struct libidx *l)
{
  if(fp==NULL)return;

  if(files)
    fprintf(fp,"---------------------------------------------------"\
	    "----------------------------\n\n\nTotals:\n"\
	    "-----------------------------------\n");

  fprintf(fp,"  Files . . . . . . . .  %7d\n",files);
  fprintf(fp,"  Kbytes . . . . . . . . %7d\n",bytes>>10);

  if((l->flags&LBF_OSDIR)==0){
    fprintf(fp,"  Downloads . . . . . .  %7d\n",dnlfiles);
    fprintf(fp,"  Downloaded Kbytes  . . %7d\n\n",dnlbytes>>10);
  }
}


static void
filelst_readd(FILE *fp, struct libidx *l)
{
  struct fileidx f;
  bzero(&f,sizeof(f));
  strcpy(f.fname,filelst);
  f.flibnum=l->libnum;
  f.timestamp=time(NULL);
  f.descrlen=1;
  f.approved=1;
  strcpy(f.uploader,"Sysop");
  strcpy(f.approved_by,"Sysop");
  strcpy(f.summary,filelstd);
  filecreate(&f);
}


static void
filelst_close(FILE *fp, struct libidx *l)
{
  if(fp==NULL)return;
  filelst_footer(fp,l);
  filelst_footer(masterfilefp,l);
  filelst_readd(fp,l);
  fclose(fp);
}








static void
deltopfiles(struct libidx *l)
{
  struct fileidx f;
  bzero(&f,sizeof(f));
  strcpy(f.fname,filetop);
  f.flibnum=l->libnum;
  f.approved=1;
  filedelete(&f);
}


static void
topfiles_header(FILE *fp, struct libidx *l)
{
  if(fp==NULL)return;
  fprintf(fp,"MEGISTOS FILE LIBRARY\nTOP DOWNLOADS\n\n");
  fprintf(fp,"Top %d for library %s (%s).\n\n",numtops,l->fullname,l->descr);
}


static FILE *
topfiles_open(struct libidx *l)
{
  FILE *fp=NULL;
  char fname[512];

  bzero(topfiles,sizeof(struct topfiles)*numtops);
  deltopfiles(l);
  sprintf(fname,"%s/%s",l->dir,filetop);
  if((l->flags&LBF_NOINDEX)==0)fp=fopen(fname,"w");
  else fp=NULL;
  if(fp!=NULL)topfiles_header(fp,l);

  return fp;
}


static void
topfiles_add(FILE *fp, struct libidx *l, struct fileidx *f)
{
  int i,j;

  for(i=0;i<numtops-1;i++){
    if(f->downloaded>topfiles[i].downloads){
      for(j=numtops-1;j>i;j--){
	memcpy(&topfiles[j],&topfiles[j-1],sizeof(struct topfiles));
      }
      sprintf(topfiles[i].text,"%9d %-22.22s %-10.10s %.35s",
	      f->downloaded,f->fname,f->uploader,f->summary);
      topfiles[i].downloads=f->downloaded;
      break;
    }
  }
}


static void
topfiles_footer(FILE *fp, struct libidx *l)
{
  int i;

  if(fp==NULL)return;
  fprintf(fp,"Downloads Filename               Uploader   Description\n"\
	  "---------------------------------------------------"\
	  "----------------------------\n");
  for(i=0;i<numtops && topfiles[i].text[0];i++)
    fprintf(fp,"%s\n",topfiles[i].text);
  fprintf(fp,"---------------------------------------------------"\
	  "----------------------------\n");
}


static void
topfiles_readd(FILE *fp, struct libidx *l)
{
  struct fileidx f;
  bzero(&f,sizeof(f));
  strcpy(f.fname,filetop);
  f.flibnum=l->libnum;
  f.timestamp=time(NULL);
  f.descrlen=1;
  f.approved=1;
  strcpy(f.uploader,"Sysop");
  strcpy(f.approved_by,"Sysop");
  strcpy(f.summary,topfild);
  filecreate(&f);
}


static void
topfiles_close(FILE *fp, struct libidx *l)
{
  if(fp==NULL)return;
  topfiles_footer(fp,l);
  topfiles_readd(fp,l);
  fclose(fp);
}








static void
delmastertopfiles(struct libidx *l)
{
  struct fileidx f;
  bzero(&f,sizeof(f));
  strcpy(f.fname,mfiletp);
  f.flibnum=l->libnum;
  f.approved=1;
  filedelete(&f);
}


static void
mastertopfiles_header(FILE *fp, struct libidx *l)
{
  if(fp==NULL)return;
  fprintf(fp,"MEGISTOS FILE LIBRARY\nTOP DOWNLOADS OF ALL LIBRARIES\n\n");
  fprintf(fp,"Top %d for all libraries.\n\n",numtops);
}


static FILE *
mastertopfiles_open(struct libidx *l)
{
  FILE *fp=NULL;
  char fname[512];

  bzero(mastertopfiles,sizeof(struct topfiles)*nummtps);
  delmastertopfiles(l);
  sprintf(fname,"%s/%s",l->dir,mfiletp);
  if((l->flags&LBF_NOINDEX)==0)fp=fopen(fname,"w");
  else fp=NULL;
  if(fp!=NULL)mastertopfiles_header(fp,l);

  return fp;
}


static void
mastertopfiles_add(FILE *fp, struct libidx *l, struct fileidx *f)
{
  int i,j;
  char tmp[512], fullname[80];

  for(i=0;i<nummtps-1;i++){
    if(f->downloaded>mastertopfiles[i].downloads){
      for(j=nummtps-1;j>i;j--){
	memcpy(&mastertopfiles[j],&mastertopfiles[j-1],sizeof(struct topfiles));
      }

      sprintf(tmp,"%s/%s",l->fullname,f->fname);
      if(strlen(tmp)>30)sprintf(fullname,"...%s",&(tmp[strlen(tmp)-27]));
      else strcpy(fullname,tmp);
      sprintf(mastertopfiles[i].text,"%5d %-30.30s %-10.10s %.30s",
	      f->downloaded,fullname,f->uploader,f->summary);
      mastertopfiles[i].downloads=f->downloaded;
      break;
    }
  }
}


static void
mastertopfiles_footer(FILE *fp, struct libidx *l)
{
  int i;

  if(fp==NULL)return;

  fprintf(fp,"Dnlds Library/Filename               Uploader   Description\n"\
	  "---------------------------------------------------"\
	  "----------------------------\n");
  for(i=0;i<nummtps && mastertopfiles[i].text[0];i++)
    fprintf(fp,"%s\n",mastertopfiles[i].text);
  fprintf(fp,"---------------------------------------------------"\
	  "----------------------------\n");
}


static void
mastertopfiles_readd(FILE *fp, struct libidx *l)
{
  struct fileidx f;
  bzero(&f,sizeof(f));
  strcpy(f.fname,mfiletp);
  f.flibnum=l->libnum;
  f.timestamp=time(NULL);
  f.descrlen=1;
  f.approved=1;
  strcpy(f.uploader,"Sysop");
  strcpy(f.approved_by,"Sysop");
  strcpy(f.summary,mtpfild);
  filecreate(&f);
}


static void
mastertopfiles_close(FILE *fp, struct libidx *l)
{
  if(fp==NULL)return;
  mastertopfiles_footer(fp,l);
  mastertopfiles_readd(fp,l);
  fclose(fp);
}








static void
delmasterfilelst(struct libidx *l)
{
  struct fileidx f;
  bzero(&f,sizeof(f));
  strcpy(f.fname,mfillst);
  f.flibnum=l->libnum;
  f.approved=1;
  filedelete(&f);
}


static void
masterfilelst_header(FILE *fp, struct libidx *l)
{
  if(fp==NULL)return;
  fprintf(fp,"MEGISTOS FILE LIBRARY\nMASTER FILE DIRECTORY\n\n");
}


static FILE *
masterfilelst_open(struct libidx *l)
{
  FILE *fp=NULL;
  char fname[512];

  delmasterfilelst(l);
  sprintf(fname,"%s/%s",l->dir,mfillst);
  if((l->flags&LBF_NOINDEX)==0)fp=fopen(fname,"w");
  else fp=NULL;
  if(fp!=NULL)masterfilelst_header(fp,l);
  return fp;
}


static void
masterfilelst_readd(FILE *fp, struct libidx *l)
{
  struct fileidx f;
  bzero(&f,sizeof(f));
  strcpy(f.fname,mfillst);
  f.flibnum=l->libnum;
  f.timestamp=time(NULL);
  f.descrlen=1;
  f.approved=1;
  strcpy(f.uploader,"Sysop");
  strcpy(f.approved_by,"Sysop");
  strcpy(f.summary,mfillstd);
  filecreate(&f);
}


static void
masterfilelst_close(FILE *fp, struct libidx *l)
{
  if(fp==NULL)return;
  masterfilelst_readd(fp,l);
  fclose(fp);
}










static void keywordindex(struct libidx *l)
{
  struct maintkey   k;
  FILE             *fp;
  char              fname[512];
  struct fileidx    f;
  int               more;


  /* Delete the old index */
  bzero(&f,sizeof(f));
  strcpy(f.fname,fileind);
  f.flibnum=l->libnum;
  f.approved=1;
  filedelete(&f);

  
  /* Open the index file */
  sprintf(fname,"%s/%s",l->dir,fileind);
  if((fp=fopen(fname,"w"))==NULL)return;

  
  /* Write the header */
  fprintf(fp,"MEGISTOS FILE LIBRARY\nKEYWORD INDEX\n\n");
  fprintf(fp,"Index for library %s:\n%s\n\n",
	  l->fullname,l->descr);
  fprintf(fp,"Keyword                 File                    "\
	  "Uploader   Description\n"\
	  "----------------------------------------"\
	  "---------------------------------------\n");


  /* Print the index itself */
  more=keygetfirst(l->libnum,&k);

  while(more){
    if(k.klibnum!=l->libnum)break;
    if(k.keyword[0]==32)continue;
    if(!fileread(l->libnum,k.fname,1,&f))continue;

    fprintf(fp,"%-23s %-23s %-10.10s %.19s\n",
	    k.keyword, k.fname, f.uploader, f.summary);

    more=keygetnext(l->libnum,&k);
  }

  fprintf(fp,"----------------------------------------"\
	  "---------------------------------------\n");
  fclose(fp);


  /* Re-add the index record to the database */
  bzero(&f,sizeof(f));
  strcpy(f.fname,fileind);
  f.flibnum=l->libnum;
  f.timestamp=time(NULL);
  f.descrlen=1;
  f.approved=1;
  strcpy(f.uploader,"Sysop");
  strcpy(f.approved_by,"Sysop");
  strcpy(f.summary,fileindd);
  filecreate(&f);
}










static void masterkeywordindex()
{
  struct libidx     l;
  struct indexkey   k;
  struct fileidx    f;
  FILE             *fp;
  char              fname[512];
  int               more, oldlibnum=-1;


  /* Delete the old index */
  bzero(&f,sizeof(f));
  strcpy(f.fname,mfilind);
  f.flibnum=mainlibrary.libnum;
  f.approved=1;
  filedelete(&f);

  
  /* Open the index file */
  sprintf(fname,"%s/%s",mainlibrary.dir,mfilind);
  if((fp=fopen(fname,"w"))==NULL)return;

  
  /* Write the header */
  fprintf(fp,"MEGISTOS FILE LIBRARY\nMASTER KEYWORD INDEX\n\n"\
	  "Keyword Index for all libraries.\n\n"\
	  "Keyword                 Library/File\n"\
	  "----------------------------------------"\
	  "---------------------------------------\n");


  /* Print the index itself */
  more=keyindexfirst(&k);

  while(more){
    char fullname[512];
    if(k.keyword[0]==32)continue;

    if(oldlibnum!=k.klibnum){
      oldlibnum=k.klibnum;
      if(!libreadnum(k.klibnum,&l))continue;
    }
    
    sprintf(fname,"%s/%s",l.fullname,k.fname);
    if(strlen(fullname)>54)
      sprintf(fullname,"...%s",&(fname[strlen(fname)-51]));
    else strcpy(fullname,fname);

    fprintf(fp,"%-23s %s\n",k.keyword,fullname);

    more=keyindexnext(&k);
  }

  fprintf(fp,"----------------------------------------"\
	  "---------------------------------------\n");
  fclose(fp);


  /* Re-add the index record to the database */
  bzero(&f,sizeof(f));
  strcpy(f.fname,mfilind);
  f.flibnum=mainlibrary.libnum;
  f.timestamp=time(NULL);
  f.descrlen=1;
  f.approved=1;
  strcpy(f.uploader,"Sysop");
  strcpy(f.approved_by,"Sysop");
  strcpy(f.summary,mfilindd);
  filecreate(&f);
}










static int listsel(const struct dirent *d)
{
  return (showhid||d->d_name[0]!='.') &&
    strcmp(d->d_name,".") && strcmp(d->d_name,"..");
}


/* Things to do during OS library cleanup:
    * Recalculate statistics. (ok)
    * Regenerate file listings. (ok)
*/


void
oslib(struct libidx *l)
{
  FILE            *fp;
  struct dirent  **d=NULL;
  int              i, j;
  struct stat      st;
  struct tm       *tm;
  char             fname[512];


  /* Reset the counters */
  files=bytes=unappfiles=unappbytes=dnlfiles=dnlbytes=0;


  /* Open the file listing */
  fp=filelst_open(l);


  /* Scan the directory */
  if((j=scandir(l->dir,&d,listsel,alphasort))==0){
    if(d)free(d);
    goto printstat;
  }


  /* Loop through the files */
  for(i=0;i<j;free(d[i]),i++){


    /* Get the size and dates of the file */
    bzero(&st,sizeof(st));
    sprintf(fname,"%s/%s",l->dir,d[i]->d_name);
    if(stat(fname,&st))continue;

    /* Record file in file listing */
    tm=localtime(&st.st_mtime);
    filelst_add_os(fp,l,st.st_size,
		   strdate(makedate(tm->tm_mday,tm->tm_mon+1,1900+tm->tm_year)),
		   strtime(maketime(tm->tm_hour,tm->tm_min,tm->tm_sec),1),
		   d[i]->d_name);
    filelst_add_os(masterfilefp,l,st.st_size,
		   strdate(makedate(tm->tm_mday,tm->tm_mon+1,1900+tm->tm_year)),
		   strtime(maketime(tm->tm_hour,tm->tm_min,tm->tm_sec),1),
		   d[i]->d_name);


    /* Count total files and bytes */
    files++;
    bytes+=st.st_size;
  }

  /* Close the filelist */

  filelst_close(fp,l);
  if(d!=NULL)free(d);

  /* Sum up */
  
  tot_files+=files;
  tot_bytes+=bytes;

printstat:
  printf("%-37.37s %5d %3d.%02d (Stats N/A, OS-only library)\n",
	 l->fullname,
	 files,bytes>>20,frac(bytes));
}


static void
dolib(struct libidx *l)
{
  FILE          *fp1, *fp2;
  struct         fileidx f;
  int            more;
  char           fname[512];

  /* Reset the counters */
  files=bytes=unappfiles=unappbytes=dnlfiles=dnlbytes=0;


  /* Open the filelst */
  fp1=filelst_open(l);

  /* Open the topfiles */
  fp2=topfiles_open(l);


  /* Loop through all files */
  more=filegetfirst(l->libnum,&f,1);
  while(more){
    struct stat st;


    /* Get the size of the file */
    sprintf(fname,"%s/%s",l->dir,f.fname);
    st.st_size=0;
    stat(fname,&st);


    /* Count unapproved files and bytes */
    if(!f.approved){
      unappfiles++;
      unappbytes+=st.st_size;
    } else {
      
      /* Record the file in the index, listings etc */
      filelst_add(fp1,l,&f,st.st_size);
      topfiles_add(fp2,l,&f);

      /* Record the file in the master listings */
      mastertopfiles_add(mastertopfp,l,&f);
      filelst_add(masterfilefp,l,&f,st.st_size);
    }


    /* Count total files and bytes */
    files++;
    bytes+=st.st_size;


    /* Count downloads and downloaded bytes */
    dnlfiles+=f.downloaded;
    dnlbytes+=st.st_size*f.downloaded;


    /* Next file */
    more=filegetnext(l->libnum,&f);
  }


  /* Sum up */
  tot_files+=files;
  tot_bytes+=bytes;
  tot_unappfiles+=unappfiles;
  tot_unappbytes+=unappbytes;
  tot_dnlfiles+=dnlfiles;
  tot_dnlbytes+=dnlbytes;


  /* File list footers and stuff */
  filelst_close(fp1,l);
  topfiles_close(fp2,l);


  /* Make keyword index */
  keywordindex(l);


  printf("%-37.37s %5d %3d.%02d %5d %3d.%02d %6d %4d.%02d\n",
	 l->fullname,
	 files,bytes>>20,frac(bytes),
	 unappfiles,unappbytes>>20,frac(unappbytes),
	 dnlfiles,dnlbytes>>20,frac(dnlbytes));
}


static void
shiftweekstats(struct libidx *l)
{
  if(dayssince>6){
    bzero(&l->uploadsperday,sizeof(l->uploadsperday));
    bzero(&l->bytesperday,sizeof(l->bytesperday));
  } else {
    int i, j;
    /* Do it the REALLY naive way */
    for(i=0;i<dayssince;i++){
      for(j=6;j;j--){
	l->uploadsperday[j]=l->uploadsperday[j-1];
	l->bytesperday[j]=l->bytesperday[j-1];
      }
      l->uploadsperday[0]=0;
      l->bytesperday[0]=0;
    }
  }
}


/* Things to do during library cleanup:
    * Recalculate statistics. (ok)
    * Regenerate file listing. 
    * Regenerate indices.
    * Regenerate topfiles.
    * Shift uploadsperday/bytesperday. (ok)
    * Mail libops about new files once a week.
*/

static void
libcleanup()
{
  struct libidx l;
  int    more;

  /* Get the main library for the master files */

  if(libread(libmain,0,&mainlibrary)!=1){
    printf("Unable to find Main (\"%s\") library! Can't continue.\n",libmain);
    return;
  }

  /* Open the master files */

  mastertopfp=mastertopfiles_open(&mainlibrary);
  masterfilefp=masterfilelst_open(&mainlibrary);


  /* Loop through libraries */

  more=libgetfirst(&l);
  printf("                                         "\
	 "Total      Unapproved     Downloads\n"\
	 "Library                               "\
	 "Files MBytes Files MBytes  Files  MBytes\n"\
	 "----------------------------------------"\
	 "---------------------------------------\n");

  while(more){
    char fullname[256];
    strcpy(fullname,l.fullname);
    if(strlen(fullname)>37)
      sprintf(fullname,"...%s",&(l.fullname[strlen(l.fullname)-34]));


    /* Cleanup the library and its files and keywords */

    fprintf(masterfilefp,"\n\n\n\n");
    if(l.flags&LBF_OSDIR)oslib(&l);
    else dolib(&l);

    /* Shift uploadsperday/bytesperday */

    shiftweekstats(&l);
    
    /* Update the library's Typhoon record */
    libupdate(&l);



    more=libgetnext(&l);
  }


  /* Close the master files */
  mastertopfiles_close(mastertopfp,&mainlibrary);
  masterfilelst_close(mastertopfp,&mainlibrary);


  /* Make the master index */
  masterkeywordindex();


  /* Print library statistics */
  printf("----------------------------------------"\
	 "---------------------------------------\n"\
	 "%-37s %5d %3d.%02d %5d %3d.%02d %6d %4d.%02d\n",
	 "Totals",
	 tot_files,tot_bytes>>20,frac(tot_bytes),
	 tot_unappfiles,tot_unappbytes>>20,frac(tot_unappbytes),
	 tot_dnlfiles,tot_dnlbytes>>20,frac(tot_dnlbytes));
}


static int get_dayssince()
{
  FILE  *fp;
  char   fname[256];
  int    dayssince=0;
  int    cof=cofdate(today());

  strcpy(fname,FILELIBDIR"/.LASTCLEANUP");
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
  printf("filecleanup: Days since last cleanup: %d\n\n",dayssince);
  return dayssince;
}


int
cleanup()
{
  if((dayssince=get_dayssince())<1){
    printf("filecleanup: No need to cleanup file libraries yet.\n");
    return 0;
  }

  msg=msg_open("files");
  readsettings();
  topfiles=alcmem(sizeof(struct topfiles)*numtops);
  mastertopfiles=alcmem(sizeof(struct topfiles)*nummtps);

  dblibopen();
  dbfileopen();
  dbkeyopen();

  libcleanup();

  return 0;
}
