#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_UNISTD_H 1
#define WANT_STRINGS_H 1
#define WANT_CTYPE_H 1
#include <bbsinclude.h>

#include "bbs.h"

#include "majormsg.h"

promptblk *msg;

void
main()
{
  msg=opnmsg("majormsg.mbk");
  printf("%s",getmsg(HELLO));
  clsmsg(msg);
}
