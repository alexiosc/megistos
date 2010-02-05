/*---------- headerfile for dbkey.ddl ----------*/
/* alignment is 4 */

/*---------- structures ----------*/
struct keywordidx {  /* size 56 */
    char    keyword[24];
    char    fname[24];
    char    approved;
    int     klibnum;
};

struct indexkey {  /* size 56 */
    char    keyword[24];
    char    approved;
    int     klibnum;
    char    fname[24];
};

struct maintkey {  /* size 53 */
    int     klibnum;
    char    approved;
    char    keyword[24];
    char    fname[24];
};

struct filekey {  /* size 53 */
    int     klibnum;
    char    approved;
    char    fname[24];
    char    keyword[24];
};

/*---------- record names ----------*/
#define KEYWORDIDX 1000L

/*---------- field names ----------*/

/*---------- key names ----------*/
#define INDEXKEY 0
#define MAINTKEY 1
#define FILEKEY 2

/*---------- sequence names ----------*/

/*---------- integer constants ----------*/
