/*
 * Touch sysvar utility to manually correct corruptions in sysvar file
 *
 */

/*
USAGE:
	touchsysvar [--{parameter-name} ] sysvarfile
	
	-u : do update (otherwise just print value of parameter)
	--{parameter-name} : parameter affected
*/


#include <stdio.h>
#include <strings.h>
#include <unistd.h>

#include <bbs.h>
#include <bbsmod.h>

char    paramlist[][20] = { "emessages", "" };
int     pint;
long    plong;
int     value = 0;
int     update = 0;

struct sysvar sv;


void
error (char *erstr)
{
	fprintf (stderr, "touchsysvar: %s\n", erstr);
	exit (EXIT_FAILURE);
}

void
loadsysv (char *fname)
{
	FILE   *fp;

	if ((fp = fopen (fname, "r")) == NULL)
		error ("cannot open sysvar file for reading");
	if (fread (&sv, sizeof (struct sysvar), 1, fp) != 1)
		error ("error reading sysvar file");
	if (strncmp (sv.magic, SYSVAR_MAGIC, 4)) {
		printf ("\nMAGIC = %s\n", sv.magic);
		error ("sysvar file seems corrupted");
	}
	fclose (fp);

	printf ("System variable file for %s\n", sv.bbstitle);
}

void
writesysv (char *fname)
{
	FILE   *fp;
	char    temp[256];

	sprintf (temp, "%s.temp", fname);
	if ((fp = fopen (temp, "w")) == NULL)
		error ("cannot open temporary file for writing");
	strncpy (sv.magic, SYSVAR_MAGIC, 4);
	if (fwrite (&sv, sizeof (struct sysvar), 1, fp) != 1)
		error ("error writing temporary sysvar file");
	fclose (fp);

/* do a check more! */
	if ((fp = fopen (temp, "r")) == NULL)
		error ("cannot open temporary file for check");
	if (fread (&sv, sizeof (struct sysvar), 1, fp) != 1)
		error ("cannot read temporary sysvar file");
	fclose (fp);

	if (strncmp (sv.magic, SYSVAR_MAGIC, 4)) {
		unlink (temp);
		error ("temporary sysvar file seems corrupted");
	}

	unlink (fname);
	rename (temp, fname);
}



void
do_emessages (void)
{
	printf ("sysvar.emessages = %i\n", sv.emessages);
	if (value) {
		sv.emessages = pint;
		update = 1;
		printf ("new value = %i\n", sv.emessages);
	}

}

void
processp (char *paramname)
{
	int     i;

	for (i = 0;; i++) {
		if (!strcmp (paramlist[i], ""))
			error ("parameter currently not implemented");
		if (!strcmp (paramlist[i], paramname))
			break;
	}

	printf ("\n");
	if (!strcmp (paramname, "emessages"))
		do_emessages ();
	printf ("\n");

}

int
main (int argc, char *argv[])
{
	int     i;

	printf ("touchsysvar utility for Megistos BBS\n\n");


	if (argc < 3) {
		printf
		    ("USAGE: touchsysvar sysvarfile parameter-name\n\nCurrently implemented parameters:\n");
		for (i = 0;; i++)
			if (!strcmp (paramlist[i], ""))
				break;
			else
				printf ("\t%s\n", paramlist[i]);
		printf ("\n");
		exit (0);
	}

	if (argc == 4) {
		printf ("NEW value specified\n");
		value = 1;
		pint = atoi (argv[3]);
		plong = atol (argv[3]);
	}


	printf ("Processing file %s for parameter %s\n", argv[1], argv[2]);
	loadsysv (argv[1]);
	processp (argv[2]);
	if (update)
		writesysv (argv[1]);

	return 0;
}


/* End of File */
