#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_UNISTD_H 1
#define WANT_FCNTL_H 1
#define WANT_TERMIOS_H 1
#include <bbsinclude.h>

#include "bbs.h"








/***************************************************************
 ***************************************************************
 ***************************************************************
 ***************************************************************
 ***************************************************************
 ***************************************************************
 ***************************************************************/










#define PROMPT "Your option? "

void
display()
{
  puts(PROMPT);
  puts(input);
  fflush(stdout);
}


void
editline()
{
  long oldflags;
  char c;
  int cp=0,count=0;

  oldflags=fcntl(0,F_GETFL);
  fcntl(0,F_SETFL,oldflags|O_NONBLOCK);

  input[0]=0;
  for(;;){
    display();

    while (read(0,&c,1)!=1){
      usleep(10000);
      count=(count+1)%10;
      if(count) continue;
      if(dontinjoth || injothfile[0]==0 || cp) continue;
      if(acceptinjoth()){
	reprompt=1;
	clrinp();
	fcntl(0,F_SETFL,oldflags);
	return;
      }
    }
    resetinactivity();
    
  }
  fcntl(0,F_SETFL,oldflags);
  return;
}












void
editline();

void
main()
{
  setlanguage(0);
  initmodule(INITALL);
  for(;;){
    editline();
    if(!reprompt)break;
  }
  printf("\n\n---> %s <---\n\n",input);
}
