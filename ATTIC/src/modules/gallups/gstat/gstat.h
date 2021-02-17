/*
 * gstat header file
 *
 */


#include <megistos/gallups.h>

#define VERBOSE		1
#define QUIET		2


#define prompt(f...)
#define show(f...)	if(gsflags&VERBOSE)printf(##f)

extern int gsflags;
extern char hand[4];
extern char galname[128];

extern int WIDTH;
extern struct curargs CA;

#if 0
#define _T(t)	TEMH_##t,TEMT_##t,TEMF_##t,TEMS_##t,TEMGH_##t,TEMGT_##t,TEMGF_##t,TEMGS_##t

#define _TT(t,v)	{TEMH_##t, #v"_header", NULL},		\
			{TEMT_##t, #v"_template", NULL},	\
			{TEMF_##t, #v"_footer", NULL},		\
			{TEMS_##t, #v"_separator", NULL},	\
			{TEMGH_##t, #v"_gheader", NULL},	\
			{TEMGT_##t, #v"_gtemplate", NULL},	\
			{TEMGF_##t, #v"_gfooter", NULL},	\
			{TEMGS_##t, #v"_gseparator", NULL}

/* alsways TEM_LAST should exist at the end */
enum tem_macros { _T (SO), _T (SOS), _T (SOA), _T (SOSA),
	_T (CO), _T (COS), _T (COA), _T (COSA),
	TEM_AGES, TEM_BARWIDTH,
	TEM_LAST
};

struct _tem_data {
	int     tem_type;
	char    tem_name[30];
	char   *template;
};

extern struct _tem_data tem_data[];
#endif


extern int *ages;

struct curargs {
	int    *fields;
	int     curoption;
	int     curfield;
	int     currow;
	int     curcol;

	int    *row_p_sum;
	int    *col_p_sum;
	int     row_t_sum;
	int     col_t_sum;

	int    *fld_p_sum;

	int     comboidx;
};

extern struct curargs CA;




/*
 * The implementation of the algorithm is as follows:
 *	make the classes were each question can be put
 *	Classes can be created for every possible key
 *		i.e. answer, age, sex
 *
 *	Each class is handled by its specific handler
 */

#define FL_OPT		0x01
#define FL_OPTSEX	0x02
#define FL_OPTAGE	0x04
#define FL_OPTSEXAGE	0x08


#define GMAXCLASS	5

#define CMD_SIZE	1
#define CMD_IDX		2
#define CMD_PRM		3

/* this structure contains every possible class key */
/* add more key fields here */
struct userdata {
	char    userid[24];
	int     age;
	char    sex;
	char  **anscomidx;
	int     anscomfld;
	int     anscompos;
};


extern struct question *curquest;
extern struct answer *curans;
extern struct userdata user, *curuser;
extern char curprompt[128];

/* tree.c */

#define key_set(k,f...)	_key_set(k, ##f, -1)


/* tree node, leafcount can be used to hold the data wanted */
struct treenode {
	struct treenode *leafs;
	int     leafcount;
};

extern struct treenode tree;

/* [0] holds the size of the key */
typedef int treekey_t[GMAXCLASS + 1];

void    tree_setup (void);
void    tree_addleaf (struct treenode *n, int size);
void    tree_addlevel (struct treenode *n, int size);
void    tree_init (treekey_t key);
void    tree_freelevel (struct treenode *n);
void    tree_free (void);
struct treenode *tree_getleaf (struct treenode *n, treekey_t key, int idx);
struct treenode *tree_search (treekey_t key);
void    _key_set (treekey_t key, ...);
int     key_next (treekey_t key, const treekey_t mask);
void    key_copy (treekey_t dst, treekey_t src);
void    test_tree (void);


/* handler.c */
typedef void (*handler_t) (int, void *);

extern handler_t class_handlers[GMAXCLASS];
extern int handler_count;

int     handler_register (handler_t handler);
void    handler_init (void);

void    class_options_handler (int cmd, void *d);
void    class_sex_handler (int cmd, void *d);
void    class_age_handler (int cmd, void *d);
void    class_choices_handler (int cmd, void *d);

int     handlers_init (void);

int     class_sum (treekey_t key, treekey_t mask);



/* selout.c */
void    dump_select (int flag);
void    dump_select_options (void);
void    dump_select_options_sex (void);
void    dump_select_options_age (void);
void    dump_select_options_sex_age (void);

void    chart_select_options (void);
void    chart_select_options_sex (void);
void    chart_select_options_age (void);
void    chart_select_options_sex_age (void);

/* comout.c */
void    dump_combo (int flag);
void    dump_combo_options (void);
void    dump_combo_options_sex (void);
void    dump_combo_options_age (void);
void    dump_combo_options_sex_age (void);

void    chart_combo_options (void);
void    chart_combo_options_sex (void);
void    chart_combo_options_age (void);
void    chart_combo_options_sex_age (void);



extern int WIDTH;
typedef void (*dump_func) (void);

/* templates.c */

extern int userlang;
void    args_init (void);


/* gprintf.c */
void    init_printf (void);
void    load_ca (int copt, int cfld, int crow, int ccol);
char   *strndup (char *s, int c, size_t size);
void    alloc_ca (int size, int elem);
void    free_ca (void);
void    gather_ca (int rows, int cols);
void    gather_cax (int rows, int cols, int fields, int fcount);
int     dump (int prm, ...);



/* End of File */
