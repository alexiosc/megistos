/*---------- headerfile for ecdb.ddl ----------*/
/* alignment is 4 */

/*---------- structures ----------*/
struct ecidx {			/* size 232 */
	long    num;
	char    from[80];
	char    to[80];
	char    subject[64];
	long    flags;
};

struct fromc {			/* size 84 */
	char    from[80];
	long    num;
};

struct toc {			/* size 84 */
	char    to[80];
	long    num;
};

struct subjectc {		/* size 68 */
	char    subject[64];
	long    num;
};

/*---------- record names ----------*/
#define ECIDX 1000L

/*---------- field names ----------*/
#define NUM 1001L
#define FROM 1002L
#define TO 1003L
#define SUBJECT 1004L

/*---------- key names ----------*/
#define FROMC 1
#define TOC 2
#define SUBJECTC 3

/*---------- sequence names ----------*/

/*---------- integer constants ----------*/
#define UID_LEN 80
#define SUBJ_LEN 64


/* End of File */
