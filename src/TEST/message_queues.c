#define WANT_STDLIB_H 1
#define WANT_STDIO_H 1
#define WANT_UNISTD_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_SYS_IPC_H 1
#define WANT_SYS_MSG_H 1
#include <bbsinclude.h>


struct mymsgbuf {
  long mtype;
  int  n;
} a;


void
main()
{
  struct msqid_ds buf;
  int child;
  int id;

  id=msgget(IPC_PRIVATE,IPC_CREAT|IPC_EXCL|0777);
  printf("msgget()=%d, errno=%d\n",id,errno);

  system("ipcs -q");

  child=fork();

  if(child){
    int k;
    printf("CHILD.\n");
    sleep(5);
    for(;;){
      k=msgrcv(id,&a,sizeof(a.n),0,IPC_NOWAIT);
      if(k!=sizeof(a.n)){
	printf("Failed to receive.\n");
      } else {
	printf("Received %d\n",a.n);
      }
      usleep(250000);
    }
  } else {
    int m=1;
    printf("PARENT.\n");
    for(;m<20;m++){
      a.mtype=1;
      a.n=m;
      if(!msgsnd(id,&a,sizeof(a.n),0)){
	printf("Sent %d\n",m);
      } else printf("Failed to send %d\n",m);
      sleep(2);
    }
  }
  
  

  if(!child){
    id=msgctl(id,IPC_RMID,&buf);
    printf("msgctl()=%d, errno=%d\n",id,errno);
  }
}
