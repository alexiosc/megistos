/*
 * This is the output module
 *
 * Contains specialized functions to output combo questions.
 * It also contains functions for graphic tables.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <megistos/gallups.h>
#include <megistos/gstat.h>
#include <megistos/mbk_gstat.h>

#define BARCHAR	"Ü"

treekey_t INTmask;
char    tempstr[16384];
char    colstr[20];

void
dump_combo_options (void)
{
	int     i, z, zm;
	treekey_t key;
	int     siz0;

	class_handlers[0] (CMD_SIZE, &siz0);

	zm = strlen (qcomch (curquest));
	alloc_ca (siz0 * zm, 1);
	key_set (INTmask, 1, 0, 0, 1);
	key_set (key, 0, 0, 0, 0);


	dump (TEMH_CO);
	for (i = 0; i < siz0; i++) {
		key[1] = i;
		for (z = 0; z < zm; z++) {
			key[4] = z;
			CA.fields[i * zm + z] = class_sum (key, INTmask);
		}
	}

	gather_cax (siz0 * zm, 1, siz0, zm);
	for (i = 0; i < siz0; i++) {
		CA.comboidx = 0;
		for (z = 0; z < zm; z++) {
			load_ca (i, i * zm + z, i * zm + z, 0);
			dump (TEMT_CO);
		}
		if (i < siz0 - 1)
			dump (TEMS_CO);
	}

	load_ca (0, 0, 0, 0);
	dump (TEMF_CO);
	free_ca ();
}

void
dump_combo_options_sex (void)
{
	int     i, z, zm, j;
	treekey_t key;
	int     siz0, siz1;

	class_handlers[0] (CMD_SIZE, &siz0);
	class_handlers[1] (CMD_SIZE, &siz1);

	zm = strlen (qcomch (curquest));
	alloc_ca (siz0 * zm, siz1);
	key_set (INTmask, 1, 1, 0, 1);
	key_set (key, 0, 0, 0, 0);


	for (i = 0; i < siz0; i++) {
		key[1] = i;
		for (j = 0; j < siz1; j++) {
			key[2] = j;
			for (z = 0; z < zm; z++) {
				key[4] = z;
				CA.fields[(i * zm + z) * siz1 + j] =
				    class_sum (key, INTmask);
			}
		}
	}

	gather_cax (siz0 * zm, siz1, siz0, zm);

	dump (TEMH_COS);
	for (i = 0; i < siz0; i++) {
		CA.comboidx = 0;
		for (z = 0; z < zm; z++) {
			load_ca (i, (i * zm + z) * siz1, i * zm + z, 0);
			dump (TEMT_COS);
		}
		if (i < siz0 - 1)
			dump (TEMS_COS);
	}

	load_ca (0, 0, 0, 0);
	dump (TEMF_COS);
	free_ca ();
}

void
dump_combo_options_age (void)
{
	int     i, z, zm, j;
	treekey_t key;
	int     siz0, siz1;

	class_handlers[0] (CMD_SIZE, &siz0);
	class_handlers[2] (CMD_SIZE, &siz1);

	zm = strlen (qcomch (curquest));
	alloc_ca (siz0 * zm, siz1);
	key_set (INTmask, 1, 0, 1, 1);
	key_set (key, 0, 0, 0, 0);


	for (i = 0; i < siz0; i++) {
		key[1] = i;
		for (j = 0; j < siz1; j++) {
			key[3] = j;
			for (z = 0; z < zm; z++) {
				key[4] = z;
				CA.fields[(i * zm + z) * siz1 + j] =
				    class_sum (key, INTmask);
			}
		}
	}

	gather_cax (siz0 * zm, siz1, siz0, zm);

	dump (TEMH_COA);
	for (i = 0; i < siz0; i++) {
		CA.comboidx = 0;
		for (z = 0; z < zm; z++) {
			load_ca (i, (i * zm + z) * siz1, i * zm + z, 0);
			dump (TEMT_COA);
		}
		if (i < siz0 - 1)
			dump (TEMS_COA);
	}

	load_ca (0, 0, 0, 0);
	dump (TEMF_COA);
	free_ca ();
}


void
dump_combo_options_sex_age (void)
{
	int     i, z, zm, j, n;
	treekey_t key;
	int     siz0, siz1, siz2;

	class_handlers[0] (CMD_SIZE, &siz0);
	class_handlers[1] (CMD_SIZE, &siz1);
	class_handlers[2] (CMD_SIZE, &siz2);

	zm = strlen (qcomch (curquest));

	alloc_ca (siz0 * zm * siz1, siz2);
	key_set (INTmask, 1, 1, 1, 1);
	key_set (key, 0, 0, 0, 0);


	for (i = 0; i < siz0; i++) {
		key[1] = i;
		for (n = 0; n < siz1; n++) {
			key[2] = n;
			for (j = 0; j < siz2; j++) {
				key[3] = j;
				for (z = 0; z < zm; z++) {
					key[4] = z;
					CA.fields[((i * zm + z) * siz1 +
						   n) * siz2 + j] =
					    class_sum (key, INTmask);
				}
			}
		}
	}

	gather_cax (siz0 * zm * siz1, siz2, siz0, zm * siz1);

	dump (TEMH_COSA);
	for (i = 0; i < siz0; i++) {
		CA.comboidx = 0;
		for (z = 0; z < zm; z++) {
			load_ca (i, (i * zm + z) * siz1 * siz2,
				 (i * zm + z) * siz1, 0);
			dump (TEMT_COSA);
		}
		if (i < siz0 - 1)
			dump (TEMS_COSA);
	}

	load_ca (0, 0, 0, 0);
	dump (TEMF_COSA);
	free_ca ();
}









/* charts */


void
chart_combo_options (void)
{
	int     i, j, n;
	int     siz0, z, zm;
	treekey_t key;

	class_handlers[0] (CMD_SIZE, &siz0);

	zm = strlen (qcomch (curquest));
	alloc_ca (siz0 * zm, 1);
	key_set (INTmask, 1, 0, 0, 1);
	key_set (key, 0, 0, 0, 0);


	for (i = 0; i < siz0; i++) {
		key[1] = i;
		for (z = 0; z < zm; z++) {
			key[4] = z;
			CA.fields[i * zm + z] = class_sum (key, INTmask);
		}
	}

	gather_cax (siz0 * zm, 1, siz0, zm);

	dump (TEMGH_CO);

	for (i = 0; i < siz0; i++) {
		CA.comboidx = 0;
		for (z = 0; z < zm; z++) {
			load_ca (i, i * zm + z, i * zm + z, 0);

			j = floor ((WIDTH * CA.fields[i * zm + z] /
				    CA.fld_p_sum[i]) + 0.5);

			tempstr[0] = '\0';
			strcat (tempstr, "[0;1;31m");
			n = WIDTH;
			for (; j > 0; j--, n--)
				strcat (tempstr, BARCHAR);
			for (; n > 0; n--)
				strcat (tempstr, " ");
			strcat (tempstr, "[0m");

			dump (TEMGT_CO, tempstr);
		}
		if (i < siz0 - 1)
			dump (TEMGS_CO);
	}

	load_ca (0, 0, 0, 0);
	dump (TEMGF_CO);

	free_ca ();
}


void
chart_combo_options_sex (void)
{
	int     i, j, jj, n;
	int     siz0, siz1, z, zm;
	treekey_t key;

	class_handlers[0] (CMD_SIZE, &siz0);
	class_handlers[1] (CMD_SIZE, &siz1);

	zm = strlen (qcomch (curquest));
	alloc_ca (siz0 * zm, siz1);
	key_set (INTmask, 1, 1, 0, 1);
	key_set (key, 0, 0, 0, 0);


	for (i = 0; i < siz0; i++) {
		key[1] = i;
		for (j = 0; j < siz1; j++) {
			key[2] = j;
			for (z = 0; z < zm; z++) {
				key[4] = z;
				CA.fields[(i * zm + z) * siz1 + j] =
				    class_sum (key, INTmask);
			}
		}
	}

	gather_cax (siz0 * zm, siz1, siz0, zm);

	dump (TEMGH_COS);
	for (i = 0; i < qseldatacnt (curquest); i++) {
		CA.comboidx = 0;
		for (z = 0; z < zm; z++) {

			load_ca (i, (i * zm + z) * siz1, i * zm + z, 0);

			tempstr[0] = '\0';
			n = WIDTH;
			strcat (tempstr, "[0;1m");
			for (jj = 0; jj < siz1; jj++) {
				sprintf (colstr, "[3%im", 1 + jj);
				strcat (tempstr, colstr);

				j = floor ((WIDTH *
					    CA.fields[(i * zm + z) * siz1 +
						      jj] / CA.fld_p_sum[i]) +
					   0.5);
				for (; j > 0; j--, n--)
					strcat (tempstr, BARCHAR);
			}

			if (WIDTH - n <
			    (WIDTH * CA.row_p_sum[i * zm + z] /
			     CA.fld_p_sum[i])) {
				strcat (tempstr, BARCHAR);
				n--;
			}

			for (; n > 0; n--)
				strcat (tempstr, " ");
			strcat (tempstr, "[0m");

			dump (TEMGT_COS, tempstr);

		}
		if (i < siz0 - 1)
			dump (TEMGS_COS);
	}

	load_ca (0, 0, 0, 0);
	dump (TEMGF_COS);

	free_ca ();
}


void
chart_combo_options_age (void)
{
	int     i, j, jj, n;
	int     siz0, siz1, z, zm;
	treekey_t key;

	class_handlers[0] (CMD_SIZE, &siz0);
	class_handlers[2] (CMD_SIZE, &siz1);

	zm = strlen (qcomch (curquest));
	alloc_ca (siz0 * zm, siz1);
	key_set (INTmask, 1, 0, 1, 1);
	key_set (key, 0, 0, 0, 0);


	for (i = 0; i < siz0; i++) {
		key[1] = i;
		for (j = 0; j < siz1; j++) {
			key[3] = j;
			for (z = 0; z < zm; z++) {
				key[4] = z;
				CA.fields[(i * zm + z) * siz1 + j] =
				    class_sum (key, INTmask);
			}
		}
	}

	gather_cax (siz0 * zm, siz1, siz0, zm);

	dump (TEMGH_COA);
	for (i = 0; i < siz0; i++) {
		CA.comboidx = 0;
		for (z = 0; z < zm; z++) {
			load_ca (i, (i * zm + z) * siz1, i * zm + z, 0);

			tempstr[0] = '\0';
			n = WIDTH;
			strcat (tempstr, "[0;1m");
			for (jj = 0; jj < siz1; jj++) {
				j = floor ((WIDTH *
					    CA.fields[(i * zm + z) * siz1 +
						      jj] / CA.fld_p_sum[i]) +
					   0.5);
				if (j) {
					sprintf (colstr, "[3%im", 1 + jj);
					strcat (tempstr, colstr);
					for (; j > 0; j--, n--)
						strcat (tempstr, BARCHAR);
				}
			}

			if (WIDTH - n <
			    (WIDTH * CA.row_p_sum[i * zm + z] /
			     CA.fld_p_sum[i])) {
				strcat (tempstr, BARCHAR);
				n--;
			}

			for (; n > 0; n--)
				strcat (tempstr, " ");
			strcat (tempstr, "[0m");

			dump (TEMGT_COA, tempstr);

		}
		if (i < siz0 - 1)
			dump (TEMGS_COA);
	}

	load_ca (0, 0, 0, 0);
	dump (TEMGF_COA);

	free_ca ();
}



void
chart_combo_options_sex_age (void)
{
	int     i, j, k, jj, n;
	int     siz0, siz1, siz2, z, zm;
	treekey_t key;
	char   *s[2];

	class_handlers[0] (CMD_SIZE, &siz0);
	class_handlers[1] (CMD_SIZE, &siz1);
	class_handlers[2] (CMD_SIZE, &siz2);

	zm = strlen (qcomch (curquest));

	alloc_ca (siz0 * zm * siz1, siz2);
	key_set (INTmask, 1, 1, 1, 1);
	key_set (key, 0, 0, 0, 0);


	for (i = 0; i < siz0; i++) {
		key[1] = i;
		for (n = 0; n < siz1; n++) {
			key[2] = n;
			for (j = 0; j < siz2; j++) {
				key[3] = j;
				for (z = 0; z < zm; z++) {
					key[4] = z;
					CA.fields[((i * zm + z) * siz1 +
						   n) * siz2 + j] =
					    class_sum (key, INTmask);
				}
			}
		}
	}

	gather_cax (siz0 * zm * siz1, siz2, siz0, zm * siz1);

	dump (TEMGH_COSA);

	s[0] = tempstr;
	s[1] = &tempstr[8192];

	for (i = 0; i < siz0; i++) {
		CA.comboidx = 0;
		for (z = 0; z < zm; z++) {
			load_ca (i, (i * zm + z) * siz1 * siz2,
				 (i * zm + z) * siz1, 0);

			for (k = 0; k < siz1; k++) {

				s[k][0] = '\0';
				n = WIDTH;
				strcat (s[k], "[0;1m");

				for (j = 0; j < siz2; j++) {
					jj = floor ((WIDTH *
						     CA.
						     fields[((i * zm +
							      z) * siz1 +
							     k) * siz2 +
							    j] /
						     CA.fld_p_sum[i]) + 0.5);

					if (jj) {
						sprintf (colstr, "[3%im",
							 j + 1);
						strcat (s[k], colstr);
						for (; jj > 0; jj--, n--)
							strcat (s[k], BARCHAR);
					}
				}

				for (; n > 0; n--)
					strcat (s[k], " ");
				strcat (s[k], "[0m");
			}

			dump (TEMGT_COSA, s[0], s[1]);
		}
		if (i < siz0 - 1)
			dump (TEMGS_COSA);
	}

	load_ca (0, 0, 0, 0);
	dump (TEMGF_COSA);

	free_ca ();
}


/* End of File */
