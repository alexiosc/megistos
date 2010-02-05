/*
 * Utility to convert original gallup data file to the current script format
 * Output file is not guaranteed to compile correct with gsc, might need editing
 */

/* reverse engineer .dat file */

#include <stdio.h>

#include "bbs.h"

#include "cnvdat.h"

struct question *poll=NULL;

FILE *out;


void
nullupgallup(void) {

  unsigned int i;
  
  for (i=0;i<pollinfo.numquestions;i++)
    poll[i].chorep=poll[i].text=NULL;  

}

int
outputcharp(char *charp, FILE *filep) {

  unsigned int i = strlen(charp) + 1;
  if (fwrite(&i,sizeof(unsigned int),1,filep)!=1) {  return 0; }
  if (fwrite(charp,sizeof(char),i,filep)!=i) {  return 0; }
  return 1;

}

int
inputcharp (char **charp, FILE *filep) {

  unsigned int i;
  
  if (fread(&i,sizeof(unsigned int),1,filep)!=1) {  return 0; }
  *charp = (char *) alcmem (sizeof(char) * i);
  if (fread(*charp,sizeof(char),i,filep)!=i) {  return 0; }
  return 1;

}

int
numchoices (unsigned int q) {

  char *ct1, *ct2;
  int cn;

  ct1=poll[q].chorep;
  cn=0;
  while(cn<MAXCHOICES) {
    for (;*ct1==32;ct1++);
    for (ct2=ct1;*ct2!='\n' && *ct2!='\0';ct2++);
    if (ct2!=ct1) cn++;
    else break;
    if (*ct2=='\0') break;
    ct1=ct2+1;
  }
  return cn;
}



int
loadgallup(char *fn) {

  char filename[256];
  FILE *dat;
  unsigned int i;
  
  sprintf(filename,"%s.dat",fn);
  strcpy(pollinfo.filename,fn);
  dat=fopen(filename,"r");
  if(dat==NULL){ return 0;}
  
  
  fprintf(out, "# This file is reverse engineered by cnvdat using dat file %s\n#\n", fn);
    
  if(!inputcharp(&pollinfo.description,dat)) return 0;
  if(fread(&pollinfo.numquestions,sizeof(unsigned int),1,dat)!=1) {return 0; }
  if(fread(&pollinfo.flags,sizeof(char),1,dat)!=1) { return 0; }

  if(pollinfo.flags & GF_VIEWRESALL)fprintf(out, "# GF_VIEWRESALL enabled\n");
  if(pollinfo.flags & GF_MULTISUBMIT)fprintf(out, "# GF_MULTISUBMIT enables\n");
  
  fprintf(out, "#\n\n");
  fprintf(out, "title\t%s\n\n", pollinfo.description);
  fprintf(out, "type\tpoll\n\n");		// all version 1.0 gallups were polls
      
  poll = (struct question *) alcmem(sizeof(struct question) * pollinfo.numquestions);
  nullupgallup();
  
  for (i=0;i<pollinfo.numquestions;i++) {
    if(fread(&poll[i].qtype,sizeof(unsigned int),1,dat)!=1) {  return 0; }
    switch(poll[i].qtype&3) {
      case GQ_NUMBER:
		if(!inputcharp(&poll[i].text,dat))return 0;
		fprintf(out, "number %i %i\n", poll[i].qtype&GN_MASKMIN>>GN_MINSHIFT,
						poll[i].qtype&GN_MASKMAX>>GN_MAXSHIFT);
		fprintf(out, "{%s}\n", poll[i].text);
		break;
		
      case GQ_FREETEXT:
	        if(!inputcharp(&poll[i].text,dat)) return 0;
		fprintf(out, "text %i\n", poll[i].qtype>>2);
		fprintf(out, "{%s}\n", poll[i].text);
		break;

      case GQ_CHOICES_SINGLE:
      case GQ_CHOICES_MULTIPLE:
		if(!inputcharp(&poll[i].text,dat)) return 0;
		if(!inputcharp(&poll[i].chorep,dat)) return 0;
		
		if((poll[i].qtype&3) == GQ_CHOICES_SINGLE)fprintf(out, "select\n"); else fprintf(out, "combo\n");
		fprintf(out, "{%s}\n", poll[i].text);
		
		fprintf(out, "options	{");
		do {
		  char *st1, *st2;
		  
		  st1 = st2 = poll[i].chorep;
		  while(st1) {
		  	while(*st2 && *st2 != '\n')st2++;
		  	if(!(*st2))break;
		  	*st2 = '\0';
		  	fprintf(out, "%s|\n", st1);
		  	st1 = ++st2;
		  }
		} while(0);
		fprintf(out, "}\n");
		
		break;
	}

	fprintf(out, "\nend\n\n\n");
	
  }
  
  fclose(dat);
  return 1;
  
}

int main(int argc, char *argv[])
{
//	printf("Old gallups --> current conversion utility\n");
	
	if(argc<2) {
		printf("Enter answer file to convert\n");
		exit(0);
	}
	out = stdout;

	loadgallup(argv[1]);
	
	if(out!=stdout)fclose(out);
	
  return 0;
}

