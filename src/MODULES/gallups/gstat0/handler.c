/*
 * handler module for gstat module
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "gstat.h"

/* cmd, is the action to be taken,
 * u, is the user record that gave the answer,
 * a, is the answer the user entered
 */
 

int tempint;
char tempstr[16384];

int handler_register(handler_t handler)
{
	if(handler_count>=GMAXCLASS)return 0;

	class_handlers[ handler_count ] = handler;

//	printf("adding handler <%p> for size %i\n", handler, i);
	handler_count++;

  return 1;
}

void handler_init(void)
{
  int i, size;

	for(i=0;i<handler_count;i++) {
		class_handlers[i](CMD_SIZE, &size);
	}
}
	

void class_options_handler(int cmd, void *d)
{
	switch(cmd) {
		case CMD_SIZE:
			if(qtyp(curquest)==GQ_SELECT)
				*(int *)d = qseldatacnt(curquest);		// number of options here
			if(qtyp(curquest)==GQ_COMBO)
				*(int *)d = qcomdatacnt(curquest);
			break;
		case CMD_IDX:
			if(qtyp(curquest) == GQ_SELECT)
				*(int *)d = anumdt(curans);
			if(qtyp(curquest) == GQ_COMBO)
				*(int *)d = user.anscomfld;					// nice yeah?!
			break;
		case CMD_PRM:
			if(qtyp(curquest) == GQ_SELECT)
				strcpy(curprompt, qseldataidx(curquest)[ *(int *)d ]);
			if(qtyp(curquest) == GQ_COMBO)
				strcpy(curprompt, qcomdataidx(curquest)[ *(int *)d ]);
			break;
	}
}

void class_choices_handler(int cmd, void *d)
{
	switch(cmd) {
		case CMD_SIZE:
			*(int *)d = strlen(qcomch(curquest));		// number of options here
			break;
		case CMD_IDX:
			*(int *)d = user.anscomidx[ user.anscompos ][0]-'0';
//			printf("Q: %d Indexing for %i --> %c %d\n", user.anscomfld, user.anscompos, user.anscomidx[ user.anscompos ][0], *(int *)d);
			break;
		case CMD_PRM:
			strcpy(curprompt, qcomdataidx(curquest)[ *(int *)d ]);
			break;
	}
}


int *ages;

void class_age_handler(int cmd, void *d)
{
  int i;

	switch(cmd) {
		case CMD_SIZE:
			for(i=0;;i++)
				if(!ages[i*2+0] && !ages[i*2+1]) {
					*(int *)d = i;
					return;
				}
			fprintf(stderr, "Error in ages variable (handler.c)\n");
			exit(1);
			break;
		case CMD_IDX:
			for(i=0;;i++)
				if(user.age >= ages[i*2+0] && user.age <= ages[i*2+1]) {
					*(int *)d = i;
					return;
				}
			
			fprintf(stderr, "User age %i could not be positioned in any valid division\n", user.age);
			exit(1);
			break;
		case CMD_PRM:
		{
		  int mn,mx;
		  	mn = ages[ *(int *)d * 2 + 0];
		  	mx = ages[ *(int *)d * 2 + 1];
	
			if(!mn && !mx) {
				fprintf(stderr, "Error in prompt for division %i\n", *(int *)d);
				exit(1);
			}
			
			if(!mn && mx) {
				sprintf(curprompt, "  --%2i", mx);
			} else
			if(mn && mx==999) {
				sprintf(curprompt, "%2i--  ", mn);
			} else {
				sprintf(curprompt, "%2i--%2i", mn, mx);
			}
		}; break;
	}
}

void class_sex_handler(int cmd, void *d)
{
	switch(cmd) {
		case CMD_SIZE:
			*(int *)d = 2;
			break;
		case CMD_IDX:
			if(user.sex == 'M')*(int *)d = 0;
			else if(user.sex == 'F')*(int *)d = 1;
			else {
				printf("fatal: could not dereference answer in %s\n", __FUNCTION__);
				exit(1);
			}
			break;
		case CMD_PRM:
			if(*(int *)d == 0)strcpy(curprompt, "M");
			else if(*(int *)d == 1)strcpy(curprompt, "F");
			break;
	}
}

int handlers_init(void)
{
	
//	register_handler(class_age_handler);
//	register_handler(class_sex_handler);

  return 0;	
}

int class_sum(treekey_t key, treekey_t mask)
{
  int i, sum=0;
  struct treenode *n;
  treekey_t kk;
  
	key[0] = handler_count;
	for(i=1;i<=handler_count;i++)if(mask[i] == 0)key[i]=0;

	key_copy(kk, key);

	if(!key_next(kk, mask)) {
		n = tree_search(key);
	  return n->leafcount;
	}
	
	do {
		n = tree_search(key);
		sum += n->leafcount;
	} while(key_next(key, mask));

  return sum;
}
