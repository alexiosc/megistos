/*---------- headerfile for ihavedb.ddl ----------*/
/* alignment is 4 */

/*---------- structures ----------*/
struct ihaverec {		/* size 153 */
	long    time;
	char    bbs[80];
	char    msgid[32];
	char    orgclub[16];
	char    club[16];
	int     num;
	char    type;
};

struct clubqueryc {		/* size 24 */
	char    type;
	int     num;
	char    club[16];
};

struct netqueryc {		/* size 128 */
	char    msgid[32];
	char    orgclub[16];
	char    bbs[80];
};

struct ihavelistc {		/* size 20 */
	char    club[16];
	long    time;
};

/*---------- record names ----------*/
#define IHAVEREC 1000L

/*---------- field names ----------*/

/*---------- key names ----------*/
#define CLUBQUERYC 0
#define NETQUERYC 1
#define IHAVELISTC 2

/*---------- sequence names ----------*/

/*---------- integer constants ----------*/


/* End of File */
