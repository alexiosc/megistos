/*---------- headerfile for request.ddl ----------*/
/* alignment is 4 */

/*---------- structures ----------*/
struct reqidx {  /* size 340 */
    int     reqnum;
    char    userid[24];
    char    reqarea[24];
    char    reqfname[256];
    char    dosfname[13];
    int     priority;
    long    reqflags;
    int     reqdate;
    int     msgno;
};

struct orderc {  /* size 56 */
    char    userid[24];
    char    reqarea[24];
    int     reqnum;
    int     priority;
};

/*---------- record names ----------*/
#define REQIDX 1000L

/*---------- field names ----------*/
#define REQNUM 1001L
#define USERID 1002L

/*---------- key names ----------*/
#define ORDERC 0

/*---------- sequence names ----------*/

/*---------- integer constants ----------*/
#define UIDLEN 24
#define AREALEN 24
#define FNAMELEN 256
#define DOSFNAMELEN 13
