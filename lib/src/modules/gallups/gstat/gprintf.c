/*
 * In this module we define some new features in printf(3) function
 *
 * %width.<code>F
	width  = width of field (normal use)
	<code> =
	
	Globals:
		1	: option #
		2	: current field value
		3	: current field percent (on total)
		4	: current field percent (on row)
		5	: current field percent (on column)

		10	: row partial sum
		11	: row partial sum percent (on total)
		12	: column partial sum
		13	: column partial sum percent
		14	: row total sum
		15	: row total sum percent (on total col)
		16	: column total sum
		17	: column total sum prcent (on total row)
		
		22	: current field value and increase current field
		23	: current field percent (on total) and increase current field
		24	: current field percent (on row) and increase current field
		25	: current field percent (on column) and increase current field
		
		30	: row partial sum and increase current column variable
		32	: row partial sum percent and increase current column variable
		32	: column partial sum and increase current column variable
		33	: column partial sum percent and increase current column variable

		50	: option # only if current field is 0

		60	: field partial sum
		61	: current field percent on field partial sum

		90	: zero current column variable
		91	: increase column variable
		92	: increase row variable

		80	: zero current age pointer division and do command 81
		81	: print age in age pointer and increase current age pointer

		85	: print current combo prompt character and increase current combo pointer

		100	: disable color insertion (default)
		101	: enable color insertion (default)
*/


#define __USE_GNU 1
#define __USE_UNIX98 1
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <printf.h>


extern int asprintf __P ((char **__restrict __ptr,
			  __const char *__restrict __fmt, ...))
     __attribute__ ((__format__ (__printf__, 2, 3)));


#include "bbs.h"
#include "gstat.h"

#define INT	"%i"
#define FLT	"%3.0f"

int insert_color_dir=0;


char dumpstr[16384];

int dump(int prm, ...)
{
  va_list ap;
  char *s=msg_get(prm);
  
	va_start(ap, prm);
	vprintf(s, ap);
	va_end(ap);

  return 0;
}





int gallup_print(FILE *stream, const struct printf_info *info, const void *const *args)
{
  char *buffer=NULL;
  int len=0;

	if(info->prec>-1) {
		switch(info->prec) {
			case 1: asprintf(&buffer, INT, CA.curoption+1); break;
			case 2: asprintf(&buffer, INT, CA.fields[ CA.curfield ]); break;
			case 3: asprintf(&buffer, FLT, CA.fields[ CA.curfield ] * 100.0 / CA.row_t_sum); break;
			case 4: asprintf(&buffer, FLT, CA.fields[ CA.curfield ] * 100.0 / CA.row_p_sum[ CA.currow ]); break;
			case 5: asprintf(&buffer, FLT, CA.fields[ CA.curfield ] * 100.0 / CA.col_p_sum[ CA.curcol ]); break;

			case 10: asprintf(&buffer, INT, CA.row_p_sum[ CA.currow ]); break;
			case 11: asprintf(&buffer, FLT, CA.row_p_sum[ CA.currow ] * 100.0 / CA.row_t_sum); break;
			case 12: asprintf(&buffer, INT, CA.col_p_sum[ CA.curcol ]); break;
			case 13: asprintf(&buffer, FLT, CA.col_p_sum[ CA.curcol ] * 100.0 / CA.col_t_sum); break;
			case 14: asprintf(&buffer, INT, CA.row_t_sum); break;
			case 15: asprintf(&buffer, FLT, CA.row_t_sum * 100.0 / CA.col_t_sum); break;
			case 16: asprintf(&buffer, INT, CA.col_t_sum); break;
			case 17: asprintf(&buffer, FLT, CA.col_t_sum * 100.0 / CA.row_t_sum); break;

			case 22: asprintf(&buffer, INT, CA.fields[ CA.curfield++ ]); break;
			case 23: asprintf(&buffer, FLT, CA.fields[ CA.curfield++ ] * 100.0 / CA.row_t_sum); break;
			case 24: asprintf(&buffer, FLT, CA.fields[ CA.curfield++ ] * 100.0 / CA.row_p_sum[ CA.currow ]); break;
			case 25: asprintf(&buffer, FLT, CA.fields[ CA.curfield++ ] * 100.0 / CA.col_p_sum[ CA.curcol ]); break;

			case 30: asprintf(&buffer, INT, CA.row_p_sum[ CA.currow++ ]); break;
			case 31: asprintf(&buffer, FLT, CA.row_p_sum[ CA.currow++ ] * 100.0 / CA.row_t_sum); break;
			case 32: asprintf(&buffer, INT, CA.col_p_sum[ CA.curcol++ ]); break;
			case 33: asprintf(&buffer, FLT, CA.col_p_sum[ CA.curcol++ ] * 100.0 / CA.col_t_sum); break;

			case 50: if(!CA.comboidx)asprintf(&buffer, INT, CA.curoption+1);
				else asprintf(&buffer, "%s", " ");
				break;

			case 60: asprintf(&buffer, INT, CA.fld_p_sum[ CA.curoption ]); break;
			case 61: asprintf(&buffer, FLT, CA.fields[ CA.curfield ] * 100.0 / CA.fld_p_sum[ CA.curoption ]); break;
			case 62: if(!insert_color_dir)asprintf(&buffer, FLT, CA.fields[ CA.curfield++ ] * 100.0 / CA.fld_p_sum[ CA.curoption ]);
				else asprintf(&buffer, "[3%im"FLT, CA.comboidx % 7 + 1, CA.fields[ CA.curfield++ ] * 100.0 / CA.fld_p_sum[ CA.curoption ]);
				break;
			case 63: if(!insert_color_dir)asprintf(&buffer, FLT, CA.row_p_sum[ CA.currow ] * 100.0 / CA.fld_p_sum[ CA.curoption ]);
				else asprintf(&buffer, "[3%im"FLT, CA.comboidx % 7 + 1, CA.row_p_sum[ CA.currow ] * 100.0 / CA.fld_p_sum[ CA.curoption ]);
				break;
			
			case 90: CA.curcol = 0; break;
			case 91: CA.curcol++; break;
			case 92: CA.currow++; break;

			case 80: CA.curfield=0;
			case 81: if(ages[ CA.curfield ] == 0 || ages[ CA.curfield ] == 999)
					asprintf(&buffer, "%s", "  ");
				else asprintf(&buffer, "%i", ages[ CA.curfield ]); CA.curfield++;
				break;

			case 85: if(!insert_color_dir)asprintf(&buffer, "%c", qcomch(curquest)[ CA.comboidx ]);
				else asprintf(&buffer, "[3%im%c", CA.comboidx % 7 + 1, qcomch(curquest)[ CA.comboidx ]);
				break;
			case 86: CA.comboidx++; break;
				
			case 100: insert_color_dir=0; break;
			case 101: insert_color_dir=1; break;
			
			default:
				return 0;
		}
	}
	
	if(!buffer)return 0;
	len = strlen(buffer);

	if(len == 0)return 0;
	
	
	len = fprintf(stream, "%*s", info->left? -info->width:info->width, buffer);

/* Clean up and return. */
	free(buffer);
  return len;
}


int gallup_print_arginfo(const struct printf_info *info, size_t n, int *argtypes)
{
  return 0;
}


void load_ca(int copt, int cfld, int crow, int ccol)
{
	CA.curoption = copt;
	CA.curfield = cfld;
	CA.currow = crow;
	CA.curcol = ccol;
}


char *strndup(char *s, int c, size_t size)
{
	memset(s, c, size);
	s[size]='\0';

  return s;
}

void alloc_ca(int size, int elem)
{
  int i;

	CA.fields = malloc(size * elem * sizeof(int));
	for(i=0;i<size*elem;i++)CA.fields[i] = 0;
	
	CA.row_p_sum = malloc(size * sizeof(int));
	for(i=0;i<size;i++)CA.row_p_sum[i] = 0;
	
	CA.col_p_sum = malloc(elem * sizeof(int));
	for(i=0;i<elem;i++)CA.col_p_sum[i] = 0;

	CA.col_t_sum = CA.row_t_sum = 0;
	CA.curfield = CA.curoption = CA.currow = CA.curcol = 0;

	CA.comboidx = 0;
	CA.fld_p_sum = NULL;
}

void free_ca(void)
{
	free(CA.fields);
	free(CA.col_p_sum);
	free(CA.row_p_sum);
	if(CA.fld_p_sum)free(CA.fld_p_sum);
}


void gather_ca(int rows, int cols)
{
  int i, j;

	for(i=0;i<rows;i++)
		for(j=0;j<cols;j++) {
			CA.row_p_sum[i] += CA.fields[cols * i + j];
			CA.col_p_sum[j] += CA.fields[cols * i + j];
		}
	for(i=0;i<rows;i++)
		CA.col_t_sum += CA.row_p_sum[i];
	
	for(j=0;j<cols;j++)
		CA.row_t_sum += CA.col_p_sum[j];
}

void gather_cax(int rows, int cols, int fields, int fcount)
{
  int i, j;

	gather_ca(rows, cols);
	
	CA.fld_p_sum = malloc(sizeof(int) * fields);

	for(i=0;i<fields;i++) {
		CA.fld_p_sum[i] = 0;
		for(j=0;j<fcount;j++)
			CA.fld_p_sum[i] += CA.row_p_sum[i*fcount + j];
	}
}


void init_printf(void)
{
	/* a warning will be produced when compiling with libc5 for arg 2
	   glibc2 will compile without warning. This has no consequences,
	   cause gallup_print_arginfo() will never be called libc5 */
	   
	register_printf_function ('F', (printf_function)gallup_print, gallup_print_arginfo);
}
