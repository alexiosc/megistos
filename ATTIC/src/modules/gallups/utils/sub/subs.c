
/*
 * this readin a .sub file and emmits the userids found there
 */

#include <stdio.h>

int main(int argc, char *argv[])
{
  FILE *fp;
  char userid[24];

	if(argc<2) {
		fprintf(stderr, "Please supply the submit file\n");
		exit(0);
	}
	
	fp = fopen(argv[1], "r");
		fread(&userid, 24, 1, fp);
	while(!feof(fp)) {
		print("%s\n", userid);
		fread(&userid, 24, 1, fp);
	}
	
	fclose(fp);
}
