#define WANT_STDIO_H 1
#define WANT_UNISTD_H 1
#define WANT_STDLIB_H 1
#define WANT_FILE_H 1
#include <bbsinclude.h>

void
main()
{
  int fd=open("/tmp/oogah",O_WRONLY);
  printf("fd=%d, errno=%d\n",fd,errno);
  printf("lock=%d, errno=%d\n",flock(fd,LOCK_EX),errno);

  {
    int fd2=open("/tmp/oogah",O_WRONLY);
    printf("fd=%d, errno=%d\n",fd2,errno);
  }

  close(fd);

  {
    int fd2=open("/tmp/oogah",O_WRONLY);
    printf("fd=%d, errno=%d\n",fd2,errno);
  }

}
