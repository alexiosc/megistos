database files {

data file [512] "FILEDATA"	contains fileidx;
key  file [512] "FILEKEY0"	contains fileidx.statlibfn;
key  file [512] "FILEKEY1"	contains fileidx.timelib;

record fileidx {
  char           fname       [24];         /* Name of the file */
  int            flibnum;                  /* Library number */
  long           timestamp;                /* Time/date of upload */
  int            flags;                    /* File flags */
  int            downloaded;               /* Times downloaded */
  unsigned short descrlen;                 /* Length of the long description */
  char           uploader    [24];         /* User who uploaded this */
  char           approved_by [24];         /* Libop who approved it */
  char           summary     [44];         /* Short description */
  char           approved;                 /* 1=approved, 0=unapproved */
  char           description [3958]        /* Long description (variable) */
                 variable by descrlen;

  primary   key          statlibfn {flibnum, approved, fname};
  alternate key          timelib   {flibnum, approved, timestamp, fname};
}


} /* End of database */
