database libs {

data file [1024] "LIBRDATA"	contains libidx;
key  file [512]  "LIBRKEY0"	contains libidx.libnum;

key  file [512]  "LIBRKEY1"	contains libidx.keyname;
key  file [512]  "LIBRKEY2"	contains libidx.namep;
key  file [512]  "LIBRKEY3"	contains libidx.parent;
key  file [512]  "LIBRKEY4"	contains libidx.device;
key  file [512]  "LIBRKEY5"	contains libidx.numunapp;


record libidx {
  int   libnum;                 /* Serial number of the library */
  char  keyname  [20];		/* Lower case name of the library */
  char  fullname [256];		/* The full path of the library */
  char  dir      [256];		/* The directory of the library */
  char  club     [16];		/* This club owns the library */
  char  passwd   [16];		/* Library password (for entering) */
  char  descr    [40];		/* Library description */
  int   parent;  		/* The library's parent library's num */
  int   device;			/* Device where library is */

  int   crdate;			/* Creation date */
  int   crtime;			/* Creation time */

  int   readkey;		/* Key needed to see/enter the library */
  int   downloadkey;		/* Key needed to download from the library */
  int   uploadkey;		/* Key needed to upload to the library */
  int   overwritekey;		/* Key needed to overwrite files */

  char  libops[5][24];          /* Five library operators named */

  int   filelimit;		/* Maximum number of files in the lib */
  int   filesizelimit;		/* KBYTES: Maximum size per file */
  int   libsizelimit;		/* MBYTES: Maximum total size of the lib */

  int   dnlcharge;		/* Charge for downloading a file */
  int   uplcharge;		/* Charge for uploading a file */
  int   rebate;			/* Royalty percentage for uploaders */

  int   numfiles;		/* Number of approved files */
  int   numbytes;		/* Total size of approved files */
  int   numunapp;		/* Number of unapproved files */
  int   bytesunapp;		/* Total size of unapproved files */

  int   uploadsperday[7];	/* Number of uploads per day for seven days */
  int   bytesperday[7];		/* Size of uploads per day for seven days */

  int   flags;			/* Misc config flags for the lib */

  primary   key          libnum;
  alternate unique key   namep {parent, keyname};
  alternate key          keyname;
  alternate key          parent;
  alternate key          device;
  alternate key          numunapp;
}


} /* End of database */

