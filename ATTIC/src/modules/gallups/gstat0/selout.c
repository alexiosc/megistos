/*
 * This is the output module
 *
 * Contains specialized functions to output select questions.
 * It also contains functions for graphic tables.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "gallups.h"
#include "gstat.h"
#include "mbk_gstat.h"

#define BARCHAR	"Ü"

treekey_t INTmask;
char tempstr[16384];
char colstr[20];

void dump_select_options(void)
{
  int i;
  treekey_t key;

	alloc_ca(qseldatacnt(curquest), 1);
	key_set(INTmask, 1, 0, 0);

	dump(TEMH_SO);
	for(i=0;i<qseldatacnt(curquest);i++) {
		key_set(key, i);
		CA.fields[i] = class_sum(key, INTmask);
	}

	gather_ca(qseldatacnt(curquest), 1);
	for(i=0;i<qseldatacnt(curquest);i++) {
		load_ca(i, i, i, 0);
		dump(TEMT_SO);
	}

	load_ca(0, 0, 0, 0);
	dump(TEMF_SO);
	free_ca();
}

void dump_select_options_sex(void)
{
  int i, j, jl;
  treekey_t key;

	class_handlers[1](CMD_SIZE, &jl);
	alloc_ca(qseldatacnt(curquest), jl);
	key_set(INTmask, 1, 1, 0);
	  
	dump(TEMH_SOS);
	for(i=0;i<qseldatacnt(curquest);i++) {
		key[1] = i;
		for(j=0;j<jl;j++) {
			key[2] = j;
			CA.fields[i*jl+j] = class_sum(key, INTmask);
		}
	}

	gather_ca(qseldatacnt(curquest), jl);
	for(i=0;i<qseldatacnt(curquest);i++) {
		load_ca(i, i*jl, i, 0);
		dump(TEMT_SOS);
	}
	
	load_ca(0, 0, 0, 0);
	dump(TEMF_SOS);
	free_ca();
}

void dump_select_options_age(void) {
  int i, j, jl;
  treekey_t key;

	class_handlers[2](CMD_SIZE, &jl);
	alloc_ca(qseldatacnt(curquest), jl);
	
	key_set(INTmask, 1, 0, 1);
	key[0] = handler_count;
	for(i=0;i<qseldatacnt(curquest);i++) {
		key[1] = i;
		for(j=0;j<jl;j++) {
			key[3] = j;
			CA.fields[i*jl+j] = class_sum(key, INTmask);
		}
	}

	gather_ca(qseldatacnt(curquest), jl);
	dump(TEMH_SOA);
	for(i=0;i<qseldatacnt(curquest);i++) {
		load_ca(i, i*jl, i, 0);
		dump(TEMT_SOA);
	}

	load_ca(0, 0, 0, 0);
	dump(TEMF_SOA);
	free_ca();
}

void dump_select_options_sex_age(void)
{
  int i, j, n, jl, jll;
  treekey_t key;
	
	class_handlers[1](CMD_SIZE, &jl);		// sex handler
	class_handlers[2](CMD_SIZE, &jll);		// age handler
	alloc_ca(qseldatacnt(curquest) * jl, jll);

	key_set(INTmask, 1, 1, 1);
	key[0] = handler_count;
	for(i=0;i<qseldatacnt(curquest);i++) {
		key[1] = i;
		for(j=0;j<jl;j++) {
			key[2] = j;
			for(n=0;n<jll;n++) {
				key[3] = n;
				CA.fields[(i*jl+j)*jll+n] = class_sum(key, INTmask);
			}
		}
	}

	gather_ca(qseldatacnt(curquest) * jl, jll);
	dump(TEMH_SOSA);
	for(i=0;i<qseldatacnt(curquest);i++) {
		load_ca(i, i*jl*jll, i*jl, 0);
		dump(TEMT_SOSA);
	}

	load_ca(0, 0, 0, 0);
	dump(TEMF_SOSA);
	free_ca();
}







/* charts */

	
void chart_select_options(void)
{
  int i, j, n;
  treekey_t key;

	alloc_ca(qseldatacnt(curquest), 1);

	key_set(INTmask, 1, 0, 0);
  
	/* key[1,x,y] is the options, sum up for x and y and print results */
	for(i=0;i<qseldatacnt(curquest);i++) {
		key_set(key, i);
		CA.fields[i] = class_sum(key, INTmask);
	}

	gather_ca(qseldatacnt(curquest), 1);

	dump(TEMGH_SO);

	for(i=0;i<qseldatacnt(curquest);i++) {
		load_ca(i, i, i, 0);
		
		j = floor((WIDTH * CA.fields[i] / CA.row_t_sum) + 0.5);

		tempstr[0]='\0';
		strcat(tempstr, "[0;1;31m");
		n=WIDTH;
		for(;j>0;j--,n--)strcat(tempstr, BARCHAR);
		for(;n>0;n--)strcat(tempstr, " ");
		strcat(tempstr, "[0m");

		dump(TEMGT_SO, tempstr);
	}

	load_ca(0, 0, 0, 0);
	dump(TEMGF_SO);
	
	free_ca();
}

void chart_select_options_sex(void)
{
  int i, j, jl, jj, n;
  treekey_t key;

	class_handlers[1](CMD_SIZE, &jl);

	alloc_ca(qseldatacnt(curquest), jl);

	key_set(INTmask, 1, 1, 0);
  
	for(i=0;i<qseldatacnt(curquest);i++) {
		key[1] = i;
		for(j=0;j<jl;j++) {
			key[2] = j;
			CA.fields[i*jl+j] = class_sum(key, INTmask);
		}
	}

	gather_ca(qseldatacnt(curquest), jl);

	dump(TEMGH_SOS);

	for(i=0;i<qseldatacnt(curquest);i++) {
		load_ca(i, i*jl, i, 0);
		
		tempstr[0]='\0';
		n = WIDTH;
		strcat(tempstr, "[0;1m");
		for(jj=0;jj<jl;jj++) {
			sprintf(colstr, "[3%im", 1+jj);
			strcat(tempstr, colstr);

			j = floor((WIDTH * CA.fields[jl*i+jj] / CA.row_t_sum) + 0.5);
			for(;j>0;j--,n--)strcat(tempstr, BARCHAR);
		}


/* there might be a differnce to the actual size of the bar beacuse of the
   roundings for the same row sum. The difference (if it exists), is always
   equal to 1. So add one more bar character of the last color. Of course this
   is not right. I'd prefer a white bar between the two colors or at the beginning.
   ANW */
   
		if(WIDTH - n < (WIDTH * CA.row_p_sum[i] / CA.row_t_sum)) {
#if 1
			strcat(tempstr, BARCHAR);
			n--;
#else
			sprintf(colstr, "[0;1;37m%s", BARCHAR);
			memmove(tempstr+strlen(colstr), tempstr, strlen(tempstr)+1);
			memcpy(tempstr, colstr, strlen(colstr));
			n--;
#endif
		}

		for(;n>0;n--)strcat(tempstr, " ");
		strcat(tempstr, "[0m");
			
		dump( TEMGT_SOS , tempstr);
	}

	load_ca(0, 0, 0, 0);
	dump(TEMGF_SOS);
	
	free_ca();
}

void chart_select_options_age(void)
{
  int i, j, jl, jj, n;
  treekey_t key;

	class_handlers[2](CMD_SIZE, &jl);

	alloc_ca(qseldatacnt(curquest), jl);

	key_set(INTmask, 1, 0, 1);
	key[0] = handler_count;
		  
	/* key[1,x,y] is the options, sum up for x and y and print results */
	for(i=0;i<qseldatacnt(curquest);i++) {
		key[1] = i;

		for(j=0;j<jl;j++) {
			key[3] = j;
			CA.fields[i*jl+j] = class_sum(key, INTmask);
		}
	}

	gather_ca(qseldatacnt(curquest), jl);
	
	dump(TEMGH_SOA);

	for(i=0;i<qseldatacnt(curquest);i++) {
		load_ca(i, i*jl, i, 0);
		
		tempstr[0]='\0';
		n = WIDTH;
		strcat(tempstr, "[0;1m");
		for(j=0;j<jl;j++) {
			sprintf(colstr, "[3%im", j+1);
			strcat(tempstr, colstr);
			jj = floor((WIDTH * CA.fields[i*jl+j] / CA.row_t_sum) + 0.5);
			for(;jj>0;jj--,n--)strcat(tempstr, BARCHAR);
		}

		for(;n>0;n--)strcat(tempstr, " ");
		strcat(tempstr, "[0m");


		dump( TEMGT_SOA , tempstr);
	}

	load_ca(0, 0, 0, 0);
	dump(TEMGF_SOA);
	
	free_ca();
}

void chart_select_options_sex_age(void)
{
  int i, j, k, jl, jll, jj, n;
  treekey_t key;
  char *s[2];

	class_handlers[1](CMD_SIZE, &jl);
	class_handlers[2](CMD_SIZE, &jll);
	alloc_ca(qseldatacnt(curquest) * jl, jll);
	key_set(INTmask, 1, 1, 1);
	key[0] = handler_count;
	for(i=0;i<qseldatacnt(curquest);i++) {
		key[1] = i;
		
		for(j=0;j<jl;j++) {
			key[2] = j;
			
			for(n=0;n<jll;n++) {
				key[3] = n;
				
				CA.fields[(i*jl+j)*jll+n] = class_sum(key, INTmask);
			}
		}
	}
	
	gather_ca(qseldatacnt(curquest) * jl, jll);


	dump(TEMGH_SOSA);

	s[0] = tempstr;
	s[1] = &tempstr[8192];
		
	for(i=0;i<qseldatacnt(curquest);i++) {
		load_ca(i, i*jl*jll, i*jl, 0);
		
		for(k=0;k<jl;k++) {

			s[k][0]='\0';
			n = WIDTH;
			strcat(s[k], "[0;1m");
	
			for(j=0;j<jll;j++) {
				sprintf(colstr, "[3%im", j+1);
				strcat(s[k], colstr);
				jj = floor((WIDTH * CA.fields[(i*jl+k)*jll+j] / CA.row_t_sum) + 0.5);
				for(;jj>0;jj--,n--)strcat(s[k], BARCHAR);
			}

			for(;n>0;n--)strcat(s[k], " ");
			strcat(s[k], "[0m");
		}

		dump( TEMGT_SOSA , s[0], s[1]);
	}

	load_ca(0, 0, 0, 0);
	dump(TEMGF_SOSA);
	
	free_ca();
}
