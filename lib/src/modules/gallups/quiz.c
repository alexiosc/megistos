/*
	IMPLEMENTATION OF THIS MODULE HAS STOPPED IN ORDER TO
	INSTALL THE MODULE ON THE BBS SOON

	Quizzes are safe from ordinary users, but they cannot
	vulnerable to systemic attack.
*/


/*
 * This file contains quiz-specific code
 *
 */

#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>


#define GLCKIDXFILE	"LOCK_IDX"
#define GLCKDATFILE	"LOCK_DAT"

long answer_pos;		// position in GLOCKFILE to store answer index

struct storerec {
	char userid[24];
	int anscount;
	time_t seconds;
	long index;
};

struct storerec *stored_answers=NULL;
struct answer *stored_data=NULL;
int answer_count=0;

struct storerec *current;

char lockfile[128]="";


void store_init(char *userid)
{
  FILE *fp;
  int i;
  
	if(stored_answers) {
		free(stored_answers);
		stored_answers = NULL;
		answer_count=0;
	}
	
	sprintf(lockfile, "%s/%s/%s", GALLUPSDIR, gfnam(ginfo), GLCKIDXFILE);

	if((fp=fopen(lockfile, "r"))!=NULL) {
		/* file does exist, check for userid inside */
		fread(&answer_count, sizeof(answer_count), 1, fp);
		stored_answers = malloc(answer_count * sizeof(struct storerec));
		
		fread(&stored_answers[0], sizeof(struct storerec), answer_count, fp);

		fclose(fp);
		for(i=0;i<answer_count;i++)
			if(!strcasecmp(stored_answers[i].userid, userid)) {
				current = &stored_answers[i];
				return;
			}
	}
	
	answer_count++;
	stored_answers = realloc(stored_answers, answer_count * sizeof(struct storerec));
	current = &stored_answers[ answer_count-1 ];
	strcpy(current->userid, userid);
	current->anscount=0;
	current->seconds = 0;
	current->index = 0;
}

void store_done(void)
{
  FILE *fp;
  int i;

	if((fp=fopen(lockfile, "w"))==NULL) {
		print("Could not create lockfile\n");
		return;
	}
	
	fwrite(&stored_answers[0], sizeof(struct storerec), answer_count, fp);
	fclose(fp);
}

void answers_init(void)
{
  int i;
  FILE *fp;
  char filename[128];
  struct question *q;

	stored_data = malloc(answer_count * sizeof(answer));
	
	sprintf(filename, "%s/%s/%s", GALLUPSDIR, gfnam(ginfo), GLCKDATFILE);
	fp=fopen(filename, "r");
	
	for(i=0;i<answer_count;i++) {
		q = &questions[i];
		fseek(fp, stored_answers[i].index, SEEK_SET);
		switch(qtyp(q)) {
			case GQ_NUMBER:
				




	

/* store answer INDEX in the temporary file */
int store_answer(int index)
{
