database keywords {

data file [512] "KEYDATA"	contains keywordidx;
key  file [512] "KEYKEY0"	contains keywordidx.indexkey;
key  file [512] "KEYKEY1"	contains keywordidx.maintkey;
key  file [512] "KEYKEY2"	contains keywordidx.filekey;

record keywordidx {
  char           keyword     [24];         /* Keyword */
  char           fname       [24];         /* Name of the file */
  char           approved;                 /* 1 if approved, else 0 */
  int            klibnum;                  /* Library number */

  primary   key  indexkey   {keyword, approved, klibnum, fname};
  alternate key  maintkey   {klibnum, approved, keyword, fname};
  alternate key  filekey    {klibnum, approved, fname,   keyword};
}


} /* End of database */
