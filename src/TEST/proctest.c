#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_UNISTD_H 1
#define WANT_CTYPE_H 1
#define WANT_SYS_STAT_H 1
#define WANT_DIRENT_H 1
#define WANT_SIGNAL_H 1
#include <bbsinclude.h>


main()
{
  DIR *dp;
  struct dirent *buf;

/*  struct stat s;
  char fname[600]="/proc/624/fd/0";
  if(stat(fname,&s))exit(0);
  printf("%04x\n",s.st_rdev); */

  if((dp=opendir("/proc"))==NULL)exit(1);
  while((buf=readdir(dp))!=NULL){
    struct stat s;
    char fname[64];

    sprintf(fname,"/proc/%s",buf->d_name);
    if(stat(fname,&s)) continue;

    if(s.st_uid==2000){
      char *s=(char *)&buf->d_name;
      int j=strlen(s);
      while(*s && isdigit(*s++))j--;
      if(!j){
	FILE *fp;
	int  d,tty;
	char s[1024], c;

	sprintf(fname,"/proc/%s/stat",buf->d_name);
	if((fp=fopen(fname,"r"))==NULL)continue;
	if(fscanf(fp,"%d %s %c %d %d %d %d",&d,s,&c,&d,&d,&d,&tty)!=7)
	  continue;
	kill(atoi(buf->d_name),SIGKILL);
      }
    }
  }
  closedir(dp);
}
