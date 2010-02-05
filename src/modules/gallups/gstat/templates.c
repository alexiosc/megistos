/*
 * templates.c
 *
 */

/* template file format is a bit complicated, but its the 
 * only elegant way (for the time), to have arrays
 */


#include <stdio.h>
#include <string.h>

#include <megistos/gstat.h>
#include <megistos/mbk_gstat.h>

promptblock_t *msg;

void
args_init (void)
{
	char   *st, *ch;
	int     i, j, n, k, p;

	msg = msg_open ("gstat");
//      msg_setlanguage(userlang);

	WIDTH = msg_int (BARWIDTH, 50, 130);

	st = msg_string (AGES);

	ages = NULL;
	ch = st;
	n = -1;
	j = k = p = 0;

	n = sscanf (st, "%d %n", &i, &j);
	while (n > 0) {
		k++;
		ages = realloc (ages, k * sizeof (int));
		ages[k - 1] = i;

		p += j;
		n = sscanf (&st[p], "%d %n", &i, &j);
	}

	k += 2;
	ages = realloc (ages, k * sizeof (int));
	ages[k - 2] = 0;
	ages[k - 1] = 0;
}




#if 0

if (!strcmp (w, "ages")) {
	char   *ch;
	int     j, n;

	ages = NULL;
	ch = st;
	n = -1;
	j = 0;
	while (*ch) {
		if (*ch >= '0' && *ch <= '9') {
			if (n == -1)
				n = 0;
			n = n * 10 + (*ch) - '0';
		} else if (n > -1) {
			j++;
			ages = realloc (ages, j * sizeof (int));
			ages[j - 1] = n;
			n = -1;
		}
		ch++;
	}

	ages = realloc (ages, (j + 2) * sizeof (int));
	ages[j] = 0;
	ages[j + 1] = 0;
	continue;

	j = 0;
	while (ages[j] || ages[j + 1]) {
		printf ("%i -- %i\n", ages[j], ages[j + 1]);
		j += 2;
	}

	exit (1);
}

if (!strcmp (w, "barwidth")) {
	if (sscanf (st, "%i ", &WIDTH) == 1)
		continue;

	fprintf (stderr, "You must enter a number in barwidth {} directive\n");
	exit (1);
}

				/* strip the \n in [0], if it exists there */
if (st[0] == '\n')
	memmove (st, st + 1, strlen (st));


tem_data[i].template = strdup (st);
//                              printf("Text: %s\n", tem_data[i].template);

break;
}
}

fscanf (fp, "%s ", w);
}

fclose (fp);
}
#endif


/* End of File */
