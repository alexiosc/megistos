/*****************************************************************************\
 **                                                                         **
 **  FILE:     mkchan.c                                                     **
 **  AUTHORS:  alexios                                                      **
 **  REVISION: B, 1995                                                      **
 **  PURPOSE:  Compile the channel definition file.                         **
 **  NOTES:                                                                 **
 **  LEGALESE:                                                              **
 **                                                                         **
 **  This program is free software; you  can redistribute it and/or modify  **
 **  it under the terms of the GNU  General Public License as published by  **
 **  the Free Software Foundation; either version 2 of the License, or (at  **
 **  your option) any later version.                                        **
 **                                                                         **
 **  This program is distributed  in the hope  that it will be useful, but  **
 **  WITHOUT    ANY WARRANTY;   without  even  the    implied warranty  of  **
 **  MERCHANTABILITY or  FITNESS FOR  A PARTICULAR  PURPOSE.   See the GNU  **
 **  General Public License for more details.                               **
 **                                                                         **
 **  You  should have received a copy   of the GNU  General Public License  **
 **  along with    this program;  if   not, write  to  the   Free Software  **
 **  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.              **
 **                                                                         **
\*****************************************************************************/


/*
 * $Id$
 *
 * $Log$
 * Revision 1.1  2001/04/16 15:03:23  alexios
 * Initial revision
 *
 * Revision 1.5  1999/07/18 22:11:13  alexios
 * Added code to grok the new M flag that enables the MetaBBS
 * client on a specific channel.
 *
 * Revision 1.4  1998/12/27 16:38:24  alexios
 * Added autoconf support. Added magic number support and removed
 * warnings.
 *
 * Revision 1.3  1998/07/24 10:32:30  alexios
 * Migrated to bbslib 0.6.
 *
 * Revision 1.2  1997/11/06 20:19:18  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 1.1  1997/11/03 00:44:02  alexios
 * Generalised the channel translation flags. Now flags 0-9
 * specify a translation table, rather than flags 7,8 and G
 * that specified one of the hardwired xlation tables.
 *
 * Revision 1.0  1997/08/28 11:33:40  alexios
 * Initial revision
 *
 *
 */


#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_STRING_H 1
#define WANT_CTYPE_H 1
#define WANT_SYS_STAT_H 1
#include <bbsinclude.h>

#include <bbs.h>


int
chancmp(const void *a, const void *b)
{
  return ((struct channeldef *)a)->channel-((struct channeldef *)b)->channel;
}


int
stringcmp(const void *a, const void *b)
{
  return strcmp((char*)a,(char*)b);
}


int
ttycmp(const void *a, const void *b)
{
  return ((struct channeldef *)a)->ttyname-((struct channeldef *)b)->ttyname;
}


int main(int argc, char **argv)
{
  FILE *fpin, *fpout;
  int linenum=0,errors=0;

  setprogname(argv[0]);
  if((fpin=fopen(CHANDEFSRCFILE,"r"))==NULL){
    fprintf(stderr,"mkchan: Unable to open %s\n",CHANDEFSRCFILE);
    exit(1);
  }

  while(!feof(fpin)){
    char line[1024], *cp;
    char tty[16], type, sups, lang[8], flags[32], config[32];
    int key, j;
    unsigned int num;

    if(!fgets(line,1024,fpin))break;
    linenum++;
    cp=line;
    while(isspace(*cp))cp++;
    if(*cp=='#')continue;
    if(sscanf(cp,"%s %x %s %c %c %d %s %s",
	      tty,&num,config,&type,&sups,&key,lang,flags)==8){
      struct channeldef *tmp=NULL;

      numchannels++;
      tmp=alcmem(sizeof(struct channeldef)*numchannels);
      if(!tmp){
	fprintf(stderr,"mkchan: Unable to allocate channel table.\n");
	exit(1);
      }
      memcpy(tmp,channels,sizeof(struct channeldef)*(numchannels-1));
      free(channels);
      channels=tmp;
      if(!channels){
	fprintf(stderr,"mkchan: Unable to allocate channel table.\n");
	exit(1);
      }

      strcpy(channels[numchannels-1].ttyname,tty);
      channels[numchannels-1].channel=num;
      channels[numchannels-1].key=key;
      strcpy(channels[numchannels-1].config,config);
      switch(toupper(type)){
      case 'M':
	channels[numchannels-1].flags|=TTF_MODEM;
	break;
      case 'S':
	channels[numchannels-1].flags|=TTF_SERIAL;
	break;
      case 'C':
	channels[numchannels-1].flags|=TTF_CONSOLE;
	break;
      case 'T':
	channels[numchannels-1].flags|=TTF_TELNET;
	break;
      default:
	fprintf(stderr,"mkchan: line %d: bad channel type '%c'.\n",linenum,type);
	errors++;
      }
      if(toupper(sups)=='Y')channels[numchannels-1].flags|=TTF_SIGNUPS;
      else if(toupper(sups)!='N'){
	fprintf(stderr,
		"mkchan: line %d: allow_signup expects 'Y' or 'N'.\n",linenum);
	errors++;
      }

      channels[numchannels-1].lang=1;
      if(toupper(lang[strlen(lang)-1])=='A'){
	lang[strlen(lang)-1]=0;
	channels[numchannels-1].lang=-1;
      }
      {
	int i=atoi(lang);
	if(i>=1 && i<=10)channels[numchannels-1].lang*=i;
	else {
	  fprintf(stderr,"mkchan: Warning: line %d: "\
		  "language not specified, #1 assumed.\n",linenum);
	  channels[numchannels-1].lang=1;
	}
      }

      /*      channels[numchannels-1].flags|=TTF_ANSI; */
      channels[numchannels-1].xlation=0;

      for(j=0;flags[j];j++)switch(toupper(flags[j])){
      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9':
	channels[numchannels-1].xlation=toupper(flags[j])-'0';
	break;
      case 'A':
	channels[numchannels-1].flags|=TTF_ASKXLT;
	break;
      case 'V':
	channels[numchannels-1].flags|=TTF_ANSI;
	break;
      case 'D':
	channels[numchannels-1].flags&=~TTF_ANSI;
	break;
      case 'S':
	channels[numchannels-1].flags|=TTF_ASKANSI;
	break;
      case 'M':
#ifdef HAVE_METABBS
	channels[numchannels-1].flags|=TTF_METABBS;
#else
	fprintf(stderr,"mkchan: line %d: Warning: ignoring flag 'M' which "
		"enables MetaBBS (not installed).\n",linenum);
#endif
	break;
      default:
	fprintf(stderr,"mkchan: line %d: bad flag '%c'.\n",linenum,flags[j]);
	errors++;
      }
    }
  }
  fclose(fpin);
  
  {
    int i;
    char ttyname[16]={0};
    int channel=-1;

    qsort(channels,numchannels,sizeof(struct channeldef),stringcmp);
    for(i=0;i<numchannels;i++){
      if(strcmp(ttyname,channels[i].ttyname)){
	strcpy(ttyname,channels[i].ttyname);
      } else {
	fprintf(stderr,"mkchan: duplicate tty name '%s'.\n",ttyname);
	errors++;
      }
    }
       
    qsort(channels,numchannels,sizeof(struct channeldef),chancmp);
    for(i=0;i<numchannels;i++){
      if(channel!=channels[i].channel){
	channel=channels[i].channel;
      } else {
	fprintf(stderr,"mkchan: duplicate channel number '%x'.\n",channel);
	errors++;
      }
    }
  }

  if((fpout=fopen(CHANDEFFILE,"w"))==NULL){
    fprintf(stderr,"mkchan: Unable to open %s for writing.\n",CHANDEFFILE);
    exit(1);
  }

  fputs(CHANNEL_MAGIC,fpout);	/* Stamp the magic "number". */

  if(fwrite(&numchannels,sizeof(numchannels),1,fpout)!=1){
    fprintf(stderr,"mkchan: Unable to write to %s.\n",CHANDEFFILE);
    exit(1);
  }
  if(fwrite(channels,sizeof(struct channeldef),numchannels,fpout)!=numchannels){
    fprintf(stderr,"mkchan: Unable to write to %s.\n",CHANDEFFILE);
    exit(1);
  }

  fclose(fpout);
  chmod(CHANDEFFILE,0660);
  exit(0);
}
