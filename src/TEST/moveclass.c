#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#include <bbsinclude.h>

#include <bbs.h>

void
main(int argc, char **argv)
{
  int i;
  FILE *fp;
  useracc u;
  for(i=1;i<argc;i++){
    if((fp=fopen(argv[i],"r"))==NULL)continue;
    if(fread(&u,sizeof(u),1,fp)!=1)continue;
    u.pagestate=0;
    if(strcmp(u.curclss,"SYSOP")&&strcmp(u.curclss,"SYSAX")){
	    strcpy(u.curclss,"OPERATOR");
	    strcpy(u.tempclss,"OPERATOR");
	    }
/*    if(u.totpaid>0&&u.totpaid<10){
      strcpy(u.curclss,"ACTIVE");
      strcpy(u.tempclss,"ACTIVE");
    } else if(u.totpaid>=10){
      strcpy(u.curclss,"FRIENDS");
      strcpy(u.tempclss,"FRIENDS");
    }*/
    printf("%-10s %5ld %-10s %-10s\n",u.userid,u.totpaid,
	   u.curclss,u.tempclss);
    fclose(fp);
    if((fp=fopen(argv[i],"w"))==NULL){
      printf("ERROR\n");
      continue;
    }
    if(fwrite(&u,sizeof(u),1,fp)!=1){
      printf("ERROR\n");
      continue;
    }
    fclose(fp);
  }
}
