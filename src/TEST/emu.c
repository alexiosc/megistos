#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_UNISTD_H 1
#define WANT_TERMIOS_H 1
#define WANT_SYS_STAT_H 1
#define WANT_SYS_TYPES_H 1
#include <bbsinclude.h>

#include "bbs.h"


void
emulate(char *dev)
{
  FILE            *fp;
  int             tty, c;
  char            devname[256], fname[256], emudname[256];
  struct termios  oldkbdtermios;
  struct termios  newkbdtermios;
  long            len=0;
  char            buf[EMULOGSIZE];
  int             count=0;


  /* Begin input emulation */

  sprintf(devname,"/dev/%s",dev);
  tty=open(devname, O_RDWR|O_NOCTTY);

  /* Switch stdin to non blocking mode */

  nonblocking();
  tcgetattr(0, &oldkbdtermios);
  newkbdtermios = oldkbdtermios;
  newkbdtermios.c_lflag = newkbdtermios.c_lflag & ~ (ICANON | ECHO);
  tcsetattr(0, TCSAFLUSH, &newkbdtermios);

  /* Begin output emulation */

  sprintf(fname,"%s/.log-%s",mkfname(EMULOGDIR),dev);
  if((fp=fopen(fname,"r"))==NULL){
    fprintf(stderr,"Error opening %s\n",fname);
  } else {
    fseek(fp,0,SEEK_END);
    for(;;){
      usleep(10000);
      count=(count+1)%10;
      if(!count){
	do{
	  len=read(fileno(fp),buf,EMULOGSIZE);
	  if(len>0)write(0,buf,len);
	} while (len>0);
      }
      
      if((read(0,&c,1))==1){
	if(c==27)break;
	ioctl(tty,EMUPUTCHAR,(long)c);
	count=-1;
      }
    }
  }

  /* Switch bach to blocking mode, close files, etc */

 endemu:
  close(tty);
  blocking();
  tcsetattr(0, TCSAFLUSH, &oldkbdtermios);
  fclose(fp);
}


void
main()
{
  emulate("tty8");
}
