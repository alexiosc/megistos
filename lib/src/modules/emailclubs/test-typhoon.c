#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#include <bbsinclude.h>

#include <libtyphoon/typhoon.h>
#include "ecdbase.h"


#define BSE_FOUND   1
#define BSE_NFOUND  0
#define BSE_OPEN   -1
#define BSE_LOCK   -2
#define BSE_STAT   -3
#define BSE_READ   -4
#define BSE_WRITE  -5
#define BSE_CAN    -6
#define BSE_END    -7
#define BSE_BEGIN  -8


extern int findmsgto (int *msgno, char *who, int targetnum, int direction);


void
error_fatal (char *a, char *b)
{
	fprintf (stderr, "%s: %s\n", a, b);
	exit (1);
}


#define LOOKFOR "Sysop"

void
main ()
{
	struct ecidx buf;
	int     i, j, msgno, bk;
	struct toc toc;

	d_dbfpath ("/bbs/msgs/Acro/.DB");
	d_dbdpath ("/bbs/msgs");
	if (d_open (".ecdb", "s") != S_OKAY) {
		fprintf (stderr, "Cannot open database (status=%d).\n",
			 db_status);
	}

	system ("clear");

	printf ("Enter message number (<0 = backwards, >0=forwards)\n");
	if (!scanf ("%d", &msgno))
		exit (1);

	if (msgno < 0) {
		msgno = -msgno;
		bk = 1;
	} else
		bk = 0;

	i = 1;
	j = findmsgto (&msgno, LOOKFOR, msgno, bk ? 2 : 4);

	if (j == BSE_END)
		j = findmsgto (&msgno, LOOKFOR, msgno, 2);
	else if (j == BSE_BEGIN)
		j = findmsgto (&msgno, LOOKFOR, msgno, 4);

	for (; db_status == S_OKAY;) {
		d_recread (&buf);
		if (strcmp (buf.to, LOOKFOR))
			break;
		printf ("#%2d. %5d. FROM %-10s  TO %-10s  SUBJ %s\n", i++,
			buf.num, buf.from, buf.to, buf.subject);
		if (bk)
			d_keyprev (TOC);
		else
			d_keynext (TOC);
	}

	d_close ();
}


/* End of File */
