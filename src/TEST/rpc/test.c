#include <stdio.h>
#include <rpc/rpc.h>
#include "test.h"

extern int errno;

int main(int argc, char **argv)
{
  CLIENT *cl;
  char *server;

  foo_res *result;

  if(argc!=2){
    printf("boink!\n");
    exit(1);
  }

  server=argv[1];
  
  cl=clnt_create(server,TESTPROG,TESTVERS,"tcp");

  if(cl==NULL){
    printf("---2\n");
    clnt_pcreateerror(server);
    exit(1);
  }

  result=foo_1(NULL,cl);
  if(result==NULL){
    clnt_perror(cl,server);
    exit(1);
  }
  
  if(result->errno!=0){
    errno=result->errno;
    perror("foo()");
    exit(1);
  } else {
    printf("server reports: foo()=\"%s\"\n",result->foo_res_u.ret_string);
  }

  return 0;
}
