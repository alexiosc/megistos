/*
 * Utility to fix email last message pointer
 *
 */

#include <stdio.h>
#include <strings.h>

#include <bbs.h>
#include <mail.h>

int quiet=0;
int debug=0;
int update=0;
int force=0;
char userid[24]="";
int newindex=-1;

void error(char *erstr)
{
	fprintf(stderr, "fixemail: %s\n", erstr);
	exit(EXIT_FAILURE);
}


void parse_params(int argc, char *argv[])
{
  int i;

	for(i=1;i<argc;i++) {
		if(!strcmp(argv[i], "-q")) {quiet=1; continue; }
		if(!strcmp(argv[i], "-d")) {debug=1; continue; }
		if(!strcmp(argv[i], "-f")) {force=1; continue; }
		if(!strcmp(argv[i], "-m")) {
			i++;
			newindex = atoi( argv[i] );
			continue;
		}
		
		strcpy(userid, argv[i]);
		break;
	}

	if(!strcmp(userid, "")) {
		printf("\nUSAGE : fixemail [-q] [-d] [-m value] userid\n
\t-q : quiet\n\t-d : debug info\n\t-f : force update\n\t-m : new message value\n\n");
		exit(0);
	}
	
	if(newindex==-1) update=0; else update=1;

	if(!quiet && debug) printf("userid %s  new index=%i\n", userid, newindex);
}

	
void dump_info(struct emailuser eu)
{
	if(quiet) return;

}

	
int main(int argc, char *argv[])
{
  struct emailuser eu;
  char fname[256];
  FILE *fp;
  
	parse_params(argc, argv);
	
	if(!quiet) printf("fixemail utility for Megistos BBS\n");

	sprintf(fname, "%s/%s", MSGUSRDIR, userid);
	if((fp=fopen(fname, "r"))==NULL) error("cannot open user file for reading");
	if(fread(&eu, sizeof(struct emailuser), 1, fp)!=1) error("cannot read user file");
	fclose(fp);
	
	if(!update && !quiet) {
		printf("User %s  last message pointer %i  flags=0x%0lx prefs=0x%0lx\n", userid, 
						eu.lastemailread, eu.flags, eu.prefs);
		exit(0);
	}

	if((eu.lastemailread<newindex) && !force) exit(0);

	if(!quiet) printf("updating...");
	
	eu.lastemailread = newindex;
		
	if((fp=fopen(fname, "w"))==NULL) error("cannot open user file for writing");
	if(fwrite(&eu, sizeof(struct emailuser), 1, fp)!=1) error("cannot write to user file");
	fclose(fp);

	if(!quiet) printf("done\n");
	
  return 0;
}
