/*
 * utility to manually edit gallup headers, when
 * something went wrong during installation.
 * This was primarily created to provide a way to manually
 * upgrade gallups from previous versions.
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include <bbs.h>

#include "gallups.h"

const char helpmsg[]="
USAGE:
	gedit -{rw} gallupname

";

#define ACT_READ	1
#define ACT_WRITE	2

#define dumps(s)	printf("%s\n", s)
#define dumpi(i)	printf("%i\n", i)

#define inputs(s)	{ fgets(tempstr, sizeof(tempstr), stdin); tempstr[ strlen(tempstr)-1]='\0'; strcpy(s, tempstr); }
#define inputi(i)	{ fgets(tempstr, sizeof(tempstr), stdin); sscanf(tempstr, "%i", &i); }
#define inputli(i)	{ fgets(tempstr, sizeof(tempstr), stdin); sscanf(tempstr, "%li", &i); }

char gallupname[128]="";
int action=0;
struct gallup *ginfo;
struct question *questions;
struct answer *answers;

char tempstr[512];


int main(int argc, char *argv[])
{
  int i;
  struct gallup glp, *gin;

	fprintf(stderr, "Gallup editor\n");

	if(argc<3) {
		fprintf(stderr, "Please provide action and gallup name\n");
		exit(1);
	}
	
	for(i=1;i<argc;i++) {
		if(argv[i][0] == '-') {
			switch(argv[i][1]) {
				case 'r': action = ACT_READ; break;
				case 'w': action = ACT_WRITE; break;
				default:
					fprintf(stderr, "unknown argument %s\n", argv[i]);
			}
		} else strcpy(gallupname, argv[i]);
	}
	
	gin = &glp;

	if(action == ACT_READ) {
		loadgallup(gallupname, gin);
	
		dumpi(gflgs(gin));
		dumpi(gnumq(gin));
		dumps(gfnam(gin));
		dumps(gdesc(gin));
		dumpi(gcrd0(gin));
		dumpi(gcrd1(gin));
		dumpi(gcrd2(gin));
		dumps(gauth(gin));
		dumps(strtime(gtset(gin), 1));
		dumps(strdate(gdset(gin)));
		dumps(strtime(gtexp(gin), 1));
		dumps(strdate(gdexp(gin)));
	}

	if(action == ACT_WRITE) {
	  char temp[128];
		
		loadgallup(gallupname, gin);

		inputi(gflgs(gin));
		inputi(gnumq(gin));
		inputs(gfnam(gin));
		inputs(gdesc(gin));
		inputi(gcrd0(gin));
		inputi(gcrd1(gin));
		inputi(gcrd2(gin));
		inputs(gauth(gin));
		inputs(temp); gtset(gin) = scantime(temp); dumps(temp); dumps(strtime( gtset(gin), 1));
		inputs(temp); gdset(gin) = scandate(temp); dumps(temp); dumps(strdate( gdset(gin)));
		inputs(temp); gtexp(gin) = scantime(temp);
		inputs(temp); gdexp(gin) = scandate(temp);

		ginfo = gin;
		savegallup();
	}
	
  return 0;
}
