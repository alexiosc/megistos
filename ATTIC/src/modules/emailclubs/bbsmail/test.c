#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_UNISTD_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include <megistos/bbs.h>
#include <megistos/bbsmail.h>
#include <megistos/ihavedb.h>
#include <megistos/typhoon.h>
#include <megistos/mbk_emailclubs.h>


int
main ()
{
	struct ihaverec ihave;
	int     i = 1;
	struct netqueryc c;

	mkdir (mkfname (IHAVEDIR), 0777);	/* Paranoia mode and a silly thing to do */
	d_dbfpath (mkfname (IHAVEDIR));
	d_dbdpath (mkfname (IHAVEDIR));
	if (d_open ("ihavedb", "s") != S_OKAY) {
		fprintf (stderr, "error %d\n", db_status);
		exit (1);
	}

	bzero (&ihave, sizeof (ihave));


	i = time (0) - 24 * 3600;
	d_keyfind (TIME, &i);
	if (db_status != S_OKAY)
		d_keynext (TIME);
	do {
		d_recread (&ihave);
		fprintf (stderr, "%2d. %ld %s/%s/%s --> %s/%d\n",
			 i++, ihave.time, ihave.bbs, ihave.orgclub,
			 ihave.msgid, ihave.club, ihave.num);
	} while (d_keynext (TIME) == S_OKAY);

	return 0;
}


/* End of File */
