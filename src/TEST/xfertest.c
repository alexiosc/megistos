#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#include <bbsinclude.h>

#include "bbs.h"

void
main()
{
  printf("xfertest\n\n");

  setprogname(argv[0]);
  initmodule(INITALL);

  print("@VERSION@ (bbslib initialised if program version shown)\n\n");

  setaudit("FILE TRANSFER TEST OK","%s -> %s","FILE TRANSFER TEST FAILED","%s -) %s");
  printf("addxfer()=%d, errno=%d\n",addxfer('U', "*", "An upload test", 10),errno);
  fflush(stdout);
  printf("Spawning updown...\n");fflush(stdout);
  printf("dofiletransfer()=%d\n",dofiletransfer());fflush(stdout);
/*    killxferlist(); */

}
