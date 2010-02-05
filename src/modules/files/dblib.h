/*---------- headerfile for dblib.ddl ----------*/
/* alignment is 4 */

/*---------- structures ----------*/
struct libidx {  /* size 860 */
    int     libnum;
    char    keyname[20];
    char    fullname[256];
    char    dir[256];
    char    club[16];
    char    passwd[16];
    char    descr[40];
    int     parent;
    int     device;
    int     crdate;
    int     crtime;
    int     readkey;
    int     downloadkey;
    int     uploadkey;
    int     overwritekey;
    char    libops[5][24];
    int     filelimit;
    int     filesizelimit;
    int     libsizelimit;
    int     dnlcharge;
    int     uplcharge;
    int     rebate;
    int     numfiles;
    int     numbytes;
    int     numunapp;
    int     bytesunapp;
    int     uploadsperday[7];
    int     bytesperday[7];
    int     flags;
};

struct namep {  /* size 24 */
    int     parent;
    char    keyname[20];
};

/*---------- record names ----------*/
#define LIBIDX 1000L

/*---------- field names ----------*/
#define LIBNUM 1001L
#define KEYNAME 1002L
#define PARENT 1008L
#define DEVICE 1009L
#define NUMUNAPP 1025L

/*---------- key names ----------*/
#define NAMEP 1

/*---------- sequence names ----------*/

/*---------- integer constants ----------*/
