/*---------- headerfile for dbfile.ddl ----------*/
/* alignment is 4 */

/*---------- structures ----------*/
struct fileidx {  /* size 4093 */
    char    fname[24];
    int     flibnum;
    long    timestamp;
    int     flags;
    int     downloaded;
    unsigned short   descrlen;
    char    uploader[24];
    char    approved_by[24];
    char    summary[44];
    char    approved;
    char    description[3958];
};

struct statlibfn {  /* size 29 */
    int     flibnum;
    char    approved;
    char    fname[24];
};

struct timelib {  /* size 36 */
    int     flibnum;
    char    approved;
    long    timestamp;
    char    fname[24];
};

/*---------- record names ----------*/
#define FILEIDX 1000L

/*---------- field names ----------*/

/*---------- key names ----------*/
#define STATLIBFN 0
#define TIMELIB 1

/*---------- sequence names ----------*/

/*---------- integer constants ----------*/
