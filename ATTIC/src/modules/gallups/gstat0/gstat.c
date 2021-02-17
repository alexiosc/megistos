/*
 * This the status module of the gallups module
 *
 */

// its purpose is to create graphic tables with statistical
// data of the results of the gallups (polls&quizzes)

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "bbs.h"
#include "gallups.h"
#include "gstat.h"

int gsflags=0;

int WIDTH=60;
struct curargs CA;

struct question *curquest;
struct answer *curans;
struct userdata user, *curuser=&user;

struct treenode tree;

struct gallup gallupinfo, *ginfo=&gallupinfo;
struct question *questions;
struct answer *answers;
char curprompt[128];

handler_t class_handlers[GMAXCLASS];
int handler_count=0;

char tempstr[16384];
int userlang=1;

const char help[]="
Syntax:
	%s -t# -g# -lN gallupname
	
	Options:
	-t#	: set table printing flag to #
	-g#	: set graphics printing flag to #
	
		Printig flag (#) can be one of:
			0: disable
			1: show options
			2: show options vs. sex
			3: show options vs. age
			4: show options vs. sex vs. age

	-lN	: set user language to N (default is 1)

";




char gallupname[128]="";
int tablemode=0;
int graphmode=0;

void parse_commandline(int vargc, char *vargv[])
{
  int i, j;

	if(vargc<2) {
		fprintf(stderr, "enter gallup name\n");

		fprintf(stderr, help, strrchr(vargv[0], '/')?(strrchr(vargv[0], '/')+1):vargv[0]);
		exit(1);
	}
	
	for(i=1;i<vargc;i++) {
		if(vargv[i][0] == '-') {
			switch(vargv[i][1]) {
				case 't':
					for(j=2;j<strlen(vargv[i]);j++)
						switch(vargv[i][j]) {
							case '0': tablemode=0; break;
							case '1': tablemode |= FL_OPT; break;
							case '2': tablemode |= FL_OPTSEX; break;
							case '3': tablemode |= FL_OPTAGE; break;
							case '4': tablemode |= FL_OPTSEXAGE; break;
						}
					break;
				case 'g':
					for(j=2;j<strlen(vargv[i]);j++)
						switch(vargv[i][j]) {
							case '0': graphmode=0; break;
							case '1': graphmode |= FL_OPT; break;
							case '2': graphmode |= FL_OPTSEX; break;
							case '3': graphmode |= FL_OPTAGE; break;
							case '4': graphmode |= FL_OPTSEXAGE; break;
						}
					break;
				case 'l': userlang = vargv[i][2] - '0';
					if(userlang==0)userlang=1;
					break;
			}
		} else {
			strcpy(gallupname, vargv[i]);
		}
	}
}


void analyze_question(int qi)
{
  FILE *fp, *idx;
  char filename[128];
  useracc_t uac;
  treekey_t key;
  struct answer a;
  struct treenode *n;
  
  int i, j, k;

	if(!gallup_loaded)
		return;
		
	if(qtyp(curquest) != GQ_SELECT && qtyp(curquest) != GQ_COMBO)return;
	
	sprintf(filename, "%s/%s/%s%i", GALLUPSDIR, gfnam(ginfo), GRESFILE, qi);
	fp = fopen(filename, "r");
	
	sprintf(filename, "%s/%s/%s", GALLUPSDIR, gfnam(ginfo), GINDEXFILE);
	idx = fopen(filename, "r");

	curans = &a;
	
	fgets(tempstr, sizeof(tempstr), idx);
	while(!feof(idx)) {
		if(gflgs(ginfo) & GF_LOGUSERID) {
			sscanf(tempstr, "%s", user.userid);
			if(!usr_exists(user.userid)) {
				printf("user %s doesnot exist\n", user.userid);
				exit(1);
			}
			
			usr_loadaccount(user.userid, &uac);
			
			user.age = uac.age;
			user.sex = uac.sex;
		} else {
			printf("No user logging facility enabled. Cannot proceed\n");
			exit(2);
		}
		
		switch(qtyp(curquest)) {
			case GQ_SELECT:
				fread(&aseldt(curans), sizeof(int), 1, fp);
				break;
			case GQ_COMBO:
				inputcharp(&acomdt(curans), fp);
				break;
		}
		
		switch(qtyp(curquest)) {
			case GQ_SELECT:
				key[0] = handler_count;
				for(i=0;i<handler_count;i++)
					class_handlers[i](CMD_IDX, &key[i+1]);

				n = tree_search(key);
				n->leafcount++;
				break;
				
			case GQ_COMBO:
				key[0] = handler_count;
				splitstring(acomdt(curans), &user.anscomidx, &j);
			
				for(k=0;k<qcomdatacnt(curquest);k++) {
					user.anscomfld = k;
					user.anscompos = k;
					for(i=0;i<handler_count;i++) {
						class_handlers[i](CMD_IDX, &key[i+1]);
					}
					
					n = tree_search(key);
					n->leafcount++;
//					printf("n->leafcount = %d\n", n->leafcount);
				}
				free(user.anscomidx);
				break;
		}
		


		fgets(tempstr, sizeof(tempstr), idx);
	}
	
	fclose(fp);
	
	fclose(idx);
}

void dump_select_question(void)
{
	if(tablemode & FL_OPT)
		dump_select_options();
		
	if(tablemode & FL_OPTSEX)
		dump_select_options_sex();
	
	if(tablemode & FL_OPTAGE)
		dump_select_options_age();
	
	if(tablemode & FL_OPTSEXAGE)
		dump_select_options_sex_age();


	if(graphmode & FL_OPT)
		chart_select_options();
	
	if(graphmode & FL_OPTSEX)
		chart_select_options_sex();
	
	if(graphmode & FL_OPTAGE)
		chart_select_options_age();
	
	if(graphmode & FL_OPTSEXAGE)
		chart_select_options_sex_age();
}

void dump_combo_question(void)
{
	if(tablemode & FL_OPT)
		dump_combo_options();
		
	if(tablemode & FL_OPTSEX)
		dump_combo_options_sex();
	
	if(tablemode & FL_OPTAGE)
		dump_combo_options_age();
	
	if(tablemode & FL_OPTSEXAGE)
		dump_combo_options_sex_age();

	if(graphmode & FL_OPT)
		chart_combo_options();
	
	if(graphmode & FL_OPTSEX)
		chart_combo_options_sex();
	
	if(graphmode & FL_OPTAGE)
		chart_combo_options_age();
	
	if(graphmode & FL_OPTSEXAGE)
		chart_combo_options_sex_age();
}


void analyze(void)
{
  int i, j;
  treekey_t key;


	handler_count=0;

	handler_register(class_options_handler);
        handler_register(class_sex_handler);
	handler_register(class_age_handler);

	for(i=0;i<gnumq(ginfo);i++) {
		curquest = &questions[i];
		if(qtyp(curquest) != GQ_SELECT && qtyp(curquest) != GQ_COMBO)continue;

		if(qtyp(curquest) == GQ_COMBO) {
			handler_register(class_choices_handler);
		}

		handler_init();

		tree_setup();

		key[0] = handler_count;
		for(j=0;j<handler_count;j++)
			class_handlers[j](CMD_SIZE, &key[j+1]);
	
		tree_init(key);

		printf("Analyzing question %i\n", i);

		printf("%s\n", qprm(curquest));
		printf("[0m");

		if(!(qflg(curquest) & QF_SELECTNOMENU)) {
			for(j=0;j<qseldatacnt(curquest);j++)
				printf("„§ ¢¦šã %i: %s\n", j+1, qseldataidx(curquest)[j]);
			printf("\n");
		}

		if(qtyp(curquest) == GQ_COMBO) {
			for(j=0;j<qcompromcnt(curquest);j++)
				printf("€¤« ©«¦ ®å˜ §œ›å¦¬ %c --> %s\n", qcomch(curquest)[j], qcompromidx(curquest)[j]);
		}


		analyze_question(i);

		if(qtyp(curquest) == GQ_SELECT)dump_select_question();
		if(qtyp(curquest) == GQ_COMBO)dump_combo_question();

		printf("Analyzing question ends\n");

		tree_free();
	}
}


int main(int argc, char *argv[])
{
	mod_setprogname(argv[0]);
	
	parse_commandline(argc, argv);
	
	show("Gallup Statistical Analyzer utility\n");


	loadgallup(gallupname, ginfo);

	args_init();
	init_printf();

	analyze();

  return 0;
}
	