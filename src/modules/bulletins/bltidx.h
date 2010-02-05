/*---------- headerfile for bltidx.ddl ----------*/
/* alignment is 4 */

/*---------- structures ----------*/
struct bltidx {			/* size 133 */
	int     num;
	int     date;
	int     flags;
	int     timesread;
	char    fname[13];
	char    area[16];
	char    author[24];
	char    descr[64];
};

struct numc {			/* size 20 */
	char    area[16];
	int     num;
};

struct fnamec {			/* size 29 */
	char    fname[13];
	char    area[16];
};

/*---------- record names ----------*/
#define BLTIDX 1000L

/*---------- field names ----------*/
#define NUM 1001L
#define DATE 1002L
#define FNAME 1005L

/*---------- key names ----------*/
#define NUMC 3
#define FNAMEC 4

/*---------- sequence names ----------*/

/*---------- integer constants ----------*/
#define FNAME_LEN 13
#define AREA_LEN 16
#define UID_LEN 24
#define DESCR_LEN 64


/* End of File */


/* End of File */
