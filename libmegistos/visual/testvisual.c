#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_NCURSES_H 1
#define WANT_SYS_IOCTL_H 1
#define WANT_SYS_KD_H 1
#define WANT_SYS_TYPES_H 1
#define WANT_LINUX_ERRNO_H 1
#define WANT_LINUX_TTY_H 1
#define WANT_LINUX_VT_H 1
#include <bbsinclude.h>

#include "bbs.h"

void
main()
{
  int c,i;
  
  initvisual();
  initmodule(INITOUTPUT|INITSIGNALS);
/*  setxlationtable(TRT_7BIT); */
  directvideo=1;

  randomize();
  setrefresh(0);
  clearscreen(0x07,32);
  cursorxy(0,0);
  attr=BG_GREEN|FG_WHITE;
/*  for(c=0;c<31;c++){
    setblock(rnd(numcolumns/2),rnd(numrows/2),
	     numcolumns/2+rnd(numcolumns/2),
	     numrows/2+rnd(numrows/2),rnd(6)*16|0x0f,33+rnd(15));
  }
  for(c=0;c<31;c++){
    attr=c;
    vprintat(c,c,"This is a test...");
    attr=c+31;
    vprintat(c+20,c,"This is a test...");
    attr=c+62;
    vprintat(c+40,c,"This is a test...");
    attr=c+62+31;
    vprintat(c+60,c,"This is a test...");
    attr=c+2*62;
    vprintat(c+80,c,"This is a test...");
  } */
  {
    int x,y;
    
    for(y=0;y<16;y++)for(x=0;x<16;x++){
      attr=y*16+x;
      vprintat(x*4,y," \376\376 ");
    }
  }

  {
    char c=screen[2];
    attr=0x0f;
    vprintat(100,10,"->%d<-",c);
    c=screen[3];
    vprintat(100,11,"->%d<-",c);
  }

/*  setblock(10,10,79,24,0x0f,'.');
  vfputblock("/dosc/tp/ss10.bin",52,5,80,24); */
  setrefresh(0);
  dumpscreen();

/*  setwindow(80,10,120,24); */

  vprint("This is a test... Type on! >");

/*  while ((c = getch()) != 'q') {
    vprint("%c", c);
  } */

  getch();

  {
    promptblk *msg=opnmsg("login");
    setrefresh(1);
    clearscreen(0x07,32);
    cursorxy(0,0);
    printansi(getmsg(12));
    clsmsg(msg);
    getch();
    printansi("\033[0;1;32;5mOogah!\n");
  }

  dumpscreen();
  getch();

  initthingies();
  rootthingy->data[0]='.';
  rootthingy->data[1]=0x20;
  rootthingy->draw();

  setrefresh(0);
  i=0;
  for(c=0;c<30;c++){
    int a;
    struct thingy *t=newthingy(rootthingy,&TPR_WINDOW,rnd(numcolumns/2),
			       rnd(numrows/2),
			       20+rnd(numcolumns/2),
			       5+rnd(numrows/2),TFL_WINDOW_FRAMEDD|TFL_WINDOW_FRAMESP);
    CT=t;
    a=((rnd(7)<<4)+1)|FG_WHITE;
    window_setattrs(a,a,a);
    window_settitle("Random Window");
    t->draw();
    i++;
    dumpscreen();
  }
  setrefresh(0);
  dumpscreen();
  
  attr=0x2f;

  runthingies();
  
  donevisual();
}
