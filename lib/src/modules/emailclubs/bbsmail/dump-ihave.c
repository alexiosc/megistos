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
main (int argc, char **argv)
{
	struct ihaverec ihave;
	int     i = 1;
	struct ihavelistc c;

	mkdir (mkfname (IHAVEDIR), 0777);	/* Paranoia mode and a silly thing to do */
	d_dbfpath (".");
	d_dbdpath (".");
	if (d_open ("ihavedb", "s") != S_OKAY) {
		fprintf (stderr, "Typhoon error %d\n", db_status);
		exit (2);
	}

	if (argc != 1 && argc != 3) {
		fprintf (stderr, "Syntax: %s [club time]\n", argv[0]);
		exit (0);
	}

	setbuf (stdout, NULL);
	bzero (&ihave, sizeof (ihave));
	if (argc == 1) {
		c.time = 0;
		strcpy (c.club, "");
	} else {
		c.time = atoi (argv[2]);
		strcpy (c.club, argv[1]);
	}

	d_keyfind (IHAVELISTC, &c);
	if (db_status != S_OKAY)
		d_keynext (IHAVELISTC);
	do {
		d_recread (&ihave);
		if (db_status != S_OKAY) {
			fprintf (stderr, "Typhoon error %d\n", db_status);
			exit (2);
		}
		if (argc == 3 && strcmp (ihave.club, argv[1]))
			break;
		printf ("%4d   %10ld %-15.15s   %s %s %s --> %s %d\n",
			i++,
			ihave.time, ihave.club,
			ihave.bbs, ihave.orgclub, ihave.msgid,
			ihave.club, ihave.num);
	} while (d_keynext (IHAVELISTC) == S_OKAY);
	fflush (stdout);
	printf ("0\n");
	fclose (stdout);
	return 0;
}


/* End of File */
