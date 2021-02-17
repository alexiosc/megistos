/*****************************************************************************\
 **                                                                         **
 **  FILE:     files.h                                                      **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, September 1997, Version 0.1                               **
 **  PURPOSE:  File Libraries, function headers                             **
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
 * $Id: files.h,v 2.0 2004/09/13 19:44:51 alexios Exp $
 *
 * $Log: files.h,v $
 * Revision 2.0  2004/09/13 19:44:51  alexios
 * Stepped version to recover CVS repository after near-catastrophic disk
 * crash.
 *
 * Revision 1.5  2003/12/27 08:59:39  alexios
 * Adjusted #includes.
 *
 * Revision 1.4  2003/12/24 20:12:12  alexios
 * Ran through megistos-config --oh.
 *
 * Revision 1.3  2001/04/22 14:49:06  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.5  2000/01/06 10:37:25  alexios
 * Added string to hold the dummy file description of a file in
 * a OS-only library. Various other declarations and cosmetic
 * changes.
 *
 * Revision 0.4  1999/07/18 21:29:45  alexios
 * Fixed the libop() macro. Declared support for the rebate
 * file. Minor changes to the audit trail entries. Lots of
 * new functions declared to cover the near completion of the
 * module.
 *
 * Revision 0.3  1998/12/27 15:40:03  alexios
 * Added autoconf support.
 *
 * Revision 0.2  1998/04/21 10:13:39  alexios
 * Loads of changes to accommodate all the new stuff.
 *
 * Revision 0.1  1998/04/16 09:27:16  alexios
 * Initial version.
 *
 *
 */


#include "dblib.h"
#include "dbfile.h"
#include "dbkey.h"


#define libop (key_owns(&thisuseracc,libopkey)||islibop(&library))
#define masterlibop (key_owns(&thisuseracc,libopkey))
#define setflag(flags,f,on) (flags=((on)?(flags|(f)):(flags&(~(f)))))



#define SLOWDEVLOCK    "LCK..slowdev.%d"
#define SLOWDEVFILE    FILELIBDIR"/.slow.devs"
#define REBATELOG      TMPDIR"/rebate-%d"	/* %d is our PID */

#define LIBCACHEDIR    FILELIBDIR"/.CACHE"

#define LIBUPDLOCK     "LCK..libupd.%d"


#define LBF_READONLY 0x0000001	/* The library is RO or on a RO medium */
#define LBF_SLOW     0x0000002	/* The library is on a slow medium */
#define LBF_OSDIR    0x0000004	/* Like Major's "DOS-only" libs */
#define LBF_FILELIST 0x0000008	/* Print "file list" even for OS libs */
#define LBF_AUTOAPP  0x0000010	/* Automatic approval of all files */
#define LBF_NOINDEX  0x0000020	/* Never create Indices/File lists */
#define LBF_DNLAUD   0x0000040	/* Audit downloads */
#define LBF_UPLAUD   0x0000080	/* Audit uploads */
#define LBF_LOCKUPL  0x0000100	/* Password protect uploads */
#define LBF_LOCKDNL  0x0000200	/* Password protect downloads */
#define LBF_LOCKENTR 0x0000400	/* Password protect entry */
#define LBF_DOS83    0x0000800	/* Impose RT-11, CP/M, DOS, TOS 8+3 filenames */



/*                   123456789012345678901234567890 */
#define AUS_FUPLOK  "FILE UPLOADED"
#define AUS_FUPLERR "FILE UPLOAD FAILED"
#define AUS_FDNLOK  "FILE DOWNLOADED"
#define AUS_FDNLERR "FILE DOWNLOAD FAILED"


/*                   1234567890123456789012345678901234567890123456789012... */
#define AUD_FUPLOK  "%%s -> %s/%%s"
#define AUD_FUPLERR "%%s -) %s/%%s"
#define AUD_FDNLOK  "%%s <- %s/%%s"
#define AUD_FDNLERR "%%s (- %s/%%s"


#define AUT_FUPLOK  (AUF_TRANSFER|AUF_INFO)
#define AUT_FUPLERR AUT_FUPLOK
#define AUT_FDNLOK  AUT_FUPLOK
#define AUT_FDNLERR AUT_FUPLOK




/* files.c */

promptblock_t *msg;

extern int entrykey;
extern int libopkey;
extern int defrkey;
extern int defdkey;
extern int defukey;
extern int defokey;
extern int defflim;
extern int defslim;
extern int defllim;
extern int defuchg;
extern int defdchg;
extern int defreb;
extern int defuaud;
extern int defdaud;
extern char *libmain;
extern int maxnest;
extern char *rdmefil;
extern int rdmesiz;
extern char *othrdme;
extern int numtries;
extern char *filedes;
extern char *fnchars;
extern int deslen;
extern int maxkeyw;
extern int accmtsd;
extern int sldevto;
extern int sldcmax;
extern int sldctim;
extern int sldcsmn;
extern char *filelst;
extern char *othrfls;
extern char *fileind;
extern char *fileindd;
extern char *mfilind;
extern char *mfilindd;
extern char *filetop;
extern int numtops;
extern int showhid;
extern char *filelstd;
extern char *topfild;
extern char *mfiletp;
extern int nummtps;
extern char *mtpfild;
extern char *mfillst;
extern char *mfillstd;
extern int srlstln;
extern char *osfdesc;

extern int peffic;

extern int sopkey;

void    readsettings ();


/* dblib.c */

extern struct libidx library;

void    dblibopen ();

int     libexists (char *s, int parent);

int     libdelete (int libnum);

int     libexistsnum (int num);

int     libread (char *s, int parent, struct libidx *library);

int     libreadnum (int num, struct libidx *library);

void    libcreate (struct libidx *lib);

int     libmaxnum ();

int     libgetfirst (struct libidx *l);

int     libgetnext (struct libidx *l);

int     libgetchild (int parent, char *namegt, struct libidx *l);

int     libupdate (struct libidx *lib);

#define LIF_ADD 1
#define LIF_DEL 0

void    libinstfile (struct libidx *lib, struct fileidx *f, int bytes,
		     int add);



/* dbfile.c */

void    dbfileopen ();

void    filecreate (struct fileidx *file);

void    fileupdate (struct fileidx *file);

void    filedelete (struct fileidx *file);

int     fileexists (int libnum, char *fname, int approved);

int     fileread (int libnum, char *fname, int approved, struct fileidx *f);

int     filegetfirst (int libnum, struct fileidx *file, int approved);

int     filegetnext (int libnum, struct fileidx *file);

int     filegetoldest (int libnum, time_t newer_than, int approved,
		       struct fileidx *file);

int     filegetnextoldest (int libnum, struct fileidx *file);



/* dbkey.c */

void    dbkeyopen ();

void    addkeywords (char *s, int approved, struct fileidx *f);

void    addkeyword (struct keywordidx *kw);

void    deletekeyword (int libnum, char *fname, int approved, char *keyword);

int     keywordfind (int libnum, char *keyword, struct maintkey *k);

int     keygetfirst (int libnum, struct maintkey *k);

int     keygetnext (int libnum, struct maintkey *k);

int     keyindexfirst (struct indexkey *k);

int     keyindexnext (struct indexkey *k);

int     keyfilefirst (int libnum, char *fname, int approved,
		      struct filekey *k);

int     keyfilenext (int libnum, char *fname, int approved, struct filekey *k);

void    delfilekeywords (struct libidx *l, struct fileidx *f);



/* mklib.c */

void    makemainlib ();

void    mklib (struct libidx *lib, int readytowrite, int flags);


/* substvars.c */

void    initlibsubstvars ();


/* select.c */

inline void enterlastlib ();

int     enterlib (int libnum, int quiet);

void    entermainlib ();

int     getsellibname (struct libidx *l);

void    selectlib ();


/* operations.c */

void    operations ();


/* clubhdr.c */

int     findclub (char *club);


/* access.c */

#define ACC_VISIBLE  0
#define ACC_ENTER    1
#define ACC_DOWNLOAD 2
#define ACC_UPLOAD   3

void    forcepasswordfail ();

int     islibop (struct libidx *l);

int     getlibaccess (struct libidx *l, int access_type);

void    locklib ();

void    unlocklib ();

int     checklocks (int libnum);

int     adminlock (int libnum);

void    adminunlock ();

int     autoapp (struct libidx *l);


/* list.c */

void    libtree ();

int     listsublibs ();

int     osdirlisting ();

void    listapproved ();

int     filelisting (int approved);


/* misc.c */

#define SYMLINKTO  "symbolic link to "

char   *leafname (char *s);

char   *zonkdir (char *s);

int     nesting (char *s);

void    libinfo ();

void    fullinfo ();

#define getfiletype(s) _getfiletype(s,10)

char   *_getfiletype (char *fname, int recurse);

int     calcxfertime (int size, int inseconds);

int     calccharge (int size, struct libidx *l);

int     fileinfo (struct libidx *l, struct fileidx *f);

char   *lcase (char *s);


/* opedit.c */

void    op_edit ();


/* opaccess.c */

void    op_access ();


/* opcreate.c */

void    op_create ();


/* opdelete.c */

void    op_delete ();


/* opaddtree.c */

void    op_addtree ();


/* opdeltree.c */

void    op_deltree ();


/* opcharges.c */

void    op_charges ();


/* oplimits.c */

void    op_limits ();


/* opoptions.c */

void    op_options ();


/* opmisc.c */

void    op_describe ();


/* opls.c */

void    op_ls ();


/* opfiles.c */

void    op_files ();


/* opunapp.c */

void    op_listunapp ();


/* opapprove.c */

void    op_approve ();


/* opdisapp.c */

void    op_disapprove ();


/* opdisapp.c */

void    op_disapp ();


/* oplibren.c */

void    op_libren ();


/* opdescr.c */

void    op_descr ();
void    op_long ();


/* opdel.c */

void    op_del ();


/* opmove.c */

void    op_move ();


/* opmove.c */

void    op_copy ();


/* upload.c */

#define MAXFILENAMELEN 23	/* DO NOT CHANGE THIS */

#define KEYWORDCHARS "abcdefghijklmnopqrstuvwxyz0123456789,'-"

void    upload ();


/* fileops.c */

void    initslowdevs ();

int     getlibgroup (struct libidx *lib);

int     checkliblock (struct libidx *lib);

int     obtainliblock (struct libidx *lib, int timeout, char *reason);

void    rmliblock (struct libidx *lib);

int     installfile (char *source, char *finalname, struct libidx *lib);


/* cache.c */

char   *cachefile (struct libidx *lib, struct fileidx *file);


/* opcache.c */

void    op_cache ();


/* libcnv.c */

int     cnvmain (int argc, char **argv);


/* cleanup.c */

int     cleanup ();


/* download.c */

void    download (char *fnames);	/* Optional filespecs to download */


/* sublib.c */

void    get_children ();

int     firstchild ();

int     nextchild ();


/* search.c */

extern struct re_pattern_buffer *regexp;

int     mkregexp (char *re);

int     mkwildcard (char *s);

void    filesearch ();


/* filearray.c */

struct filerec {
	char    fname[24];
	char    summary[44];
	int     size;
};

int     gettotalcharge ();

int     expandspec (char *s, int quiet);

void    reset_filearray ();

struct filerec *firstfile ();

struct filerec *nextfile ();



/* End of File */
