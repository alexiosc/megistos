#define WANT_STDIO_H 1
#define WANT_UNISTD_H 1
#define WANT_STDLIB_H 1
#include <bbsinclude.h>


void
main()
{
  int i, pid, status;
  for(i=0;i<5;i++){
    if((pid=fork())==0){
      system("echo Sleeping; sleep 1; echo Exiting");
      exit(0);
    } else printf("Spawned: %d\n",pid);
  }
  system("bash");
  printf("Waiting\n");
  for(i=0;i<5;i++){
    printf("Done: %d\n",wait(&status));
  }
  printf("Done\n");
}
