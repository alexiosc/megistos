#include <rpc/rpc.h>
#include <sys/dir.h>
#include "test.h"

extern int errno;
extern char *malloc();
extern char *strdup();

foo_res *
foo_1_svc(void *a, struct svc_req *b)
{
  static foo_res res;
  res.foo_res_u.ret_string=strdup("bar!");
  return &res;
}
