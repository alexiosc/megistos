/*****************************************************************************\
 **                                                                         **
 **  FILE:     gettydefs.c                                                  **
 **  AUTHORS:  Alexios (based on uugetty 2.1)                               **
 **  PURPOSE:  handle /etc/gettydefs-like LINETYPE declarations             ** 
 **  NOTES:                                                                 **
 **  LEGALESE:                                                              **
 **                                                                         **
 **  This program is free software; you  can redistribute it and/or modify  **
 **  it under the terms of the GNU  General Public License as published by  **
 **  the Free Software Foundation; either version 2 of the License, or (at  **
 **  your option) any later version.                                        **
 **                                                                         **
 **  This program is distributed  in the hope  that it will be useful, but  **
 **  WITHOUT    ANY WARRANTY;   without  even  the    implied warranty  of  **
 **  MERCHANTABILITY or  FITNESS FOR  A PARTICULAR  PURPOSE.   See the GNU  **
 **  General Public License for more details.                               **
 **                                                                         **
 **  You  should have received a copy   of the GNU  General Public License  **
 **  along with    this program;  if   not, write  to  the   Free Software  **
 **  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.              **
\*****************************************************************************/


/*
 * $Id$
 *
 * $Log$
 * Revision 1.1  2001/04/16 15:00:27  alexios
 * Initial revision
 *
 * Revision 1.2  1998/12/27 16:15:40  alexios
 * Removed debugging information.
 *
 * Revision 1.1  1998/12/15 22:11:57  alexios
 * General beautification. Fixed bug that would incorrectly set
 * more than one of the mutually exclusive CBAUD flags in the termios.
 *
 * Revision 1.0  1998/12/13 23:18:28  alexios
 * Initial revision
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
#endif

#define OPENTTY_C 1
#define WANT_CTYPE_H 1
#include <bbsinclude.h>
#include <bbs.h>
#include <bbsgetty.h>
#include <gettydefs.h>



struct termios itermios=DEFAULT_ITERMIOS; /* Pre-connection termios flags */
struct termios ftermios=DEFAULT_FTERMIOS; /* Post-connection termiso flags */


#define FAIL    -1
#define SUCCESS 0



/* findsym() - look for field in symtab list */

static int
findsym(char *field, struct symtab *symtab)
{
  for(;symtab->name!=NULL;symtab++) {
    if(strcmp(symtab->name, field)==0) {
      return symtab->value;
    }
  }
  return FAIL;
}



#define	toggle(f,b) if(inverted)(f)&=~(b);else(f)|=(b)

static void
addfield(struct termios *termio, char *field)
{
  unsigned long  val;
  int            inverted;
  

  /* There are flags, who, through no fault of their own, are SANE */

  if(strcmp(field,"SANE")==0) {
    termio->c_iflag|=ISANE;
    termio->c_oflag|=OSANE;
    termio->c_cflag|=CSANE;
    termio->c_lflag|=LSANE;
  } else {

    /* Does this mean these flags are INSANE? :-) */


    /* -FLAG reverses the meaning */
    if (*field=='-'){
      inverted=1;
      field++;
    } else {
      inverted=0;
    }

    /* Look for different flags */

    if((val=findsym(field,imodes))!=FAIL){
      toggle(termio->c_iflag,val);
    } else if((val=findsym(field,omodes))!=FAIL) {
      toggle(termio->c_oflag,val);
    } else if((val=findsym(field,cmodes))!=FAIL) {
      if(val&CBAUD)termio->c_cflag&=~CBAUD;
      toggle(termio->c_cflag,val);
    } else if((val=findsym(field,lmodes)) != FAIL) {
      toggle(termio->c_lflag,val);
    } else {
      logerror("Undefined LINETYPE symbol: \"%s\"",field);
      debug(D_GTAB,"Undefined LINETYPE symbol: \"%s\"",field);
    }
  }
}



static void
parseinitial()
{
  char *cp;
  

  /* No INITIAL specified; return */ 

  if(!initial){
    debug(D_GTAB,"No INITIAL specified; returning.");
    return;
  }


  /* parse the INITIAL string */

  debug(D_GTAB,"Parsing INITIAL: \"%s\"",initial);

  cp=strtok(initial," \t\r\n");
  do{
    debug(D_GTAB,"INITIAL: parsing token \"%s\"",cp);
    addfield(&itermios,cp);
  } while((cp=strtok(NULL," \t\n\r"))!=NULL);


  /* Debug the lot */
  debug(D_GTAB,"Initial termios: iflag=%x, oflag=%x, cflag=%x, lflag=%x",
	itermios.c_iflag, itermios.c_oflag,
	itermios.c_cflag, itermios.c_lflag);
  debug(D_GTAB,"Initial line discipline: %x",itermios.c_line);
}



static void
parsefinal()
{
  char *cp;
  

  /* No FINAL specified; return */ 

  if(!final){
    debug(D_GTAB,"No FINAL specified; returning.");
    return;
  }


  /* parse the FINAL string */

  debug(D_GTAB,"Parsing FINAL: \"%s\"",final);

  cp=strtok(final," \t\r\n");
  do{
    debug(D_GTAB,"FINAL: parsing token \"%s\"",cp);
    addfield(&ftermios,cp);
  } while((cp=strtok(NULL," \t\n\r"))!=NULL);


  /* Debug the lot */
  debug(D_GTAB,"Final termios: iflag=%x, oflag=%x, cflag=%x, lflag=%x",
	ftermios.c_iflag, ftermios.c_oflag,
	ftermios.c_cflag, ftermios.c_lflag);
  debug(D_GTAB,"Final line discipline: %x",ftermios.c_line);
}



void
parselinetype()
{
  debug(D_GTAB,"Parselinetype() called.");
  parseinitial();
  parsefinal();
}




void
settermios(struct termios *termios, int state)
{
  register int i;
  int cbaud;
  static struct termios setterm;
  char Cintr=CINTR;
  char Cerase=CERASE;
  char Ckill=CKILL;
  
  tcgetattr(0,&setterm);

  if(!state){			/* Initial settings */
    setterm.c_iflag=termios->c_iflag;
    setterm.c_oflag=termios->c_oflag;
    setterm.c_cflag=termios->c_cflag;
    setterm.c_lflag=termios->c_lflag;
    setterm.c_line=termios->c_line;
    
    /* single character processing */
    setterm.c_lflag&=~(ICANON);
    setterm.c_cc[VMIN]=1;
    setterm.c_cc[VTIME]=0;
    
    /* sanity check */
    if((setterm.c_cflag&CBAUD)==0)setterm.c_cflag|=SSPEED;
    if((setterm.c_cflag&CSIZE)==0)setterm.c_cflag|=DEF_CFL;
    setterm.c_cflag|=(CREAD|HUPCL);

    /* What speed are we talking at? */
    cbaud=setterm.c_cflag&CBAUD;
    for(i=0;speedtab[i].cbaud && speedtab[i].cbaud!=cbaud;i++);
    unsetenv("BAUD");
    setenv("BAUD",speedtab[i].speed,1);
    
    tcsetattr(0,TCSANOW,&setterm);
    tcsetattr(1,TCSANOW,&setterm); /* Paranoid */
    tcsetattr(2,TCSANOW,&setterm); /* What else? */

  } else {

    setterm.c_iflag = termios->c_iflag;
    setterm.c_oflag = termios->c_oflag;
    setterm.c_cflag = termios->c_cflag;
    setterm.c_lflag = termios->c_lflag;
    setterm.c_line  = termios->c_line;
    
    /* sanity check */
    if((setterm.c_cflag&CBAUD)==0)setterm.c_cflag|=SSPEED;
    if((setterm.c_cflag&CSIZE)==0)setterm.c_cflag|=DEF_CFL;
    setterm.c_cflag|=CREAD;
    
    /* set c_cc[] chars to reasonable values */
    /*    bzero(&setterm.c_cc,sizeof(setterm.c_cc));*/
    setterm.c_cc[VINTR]=Cintr;
    setterm.c_cc[VQUIT]=CQUIT;
    setterm.c_cc[VERASE]=Cerase;
    setterm.c_cc[VKILL]=Ckill;
    setterm.c_cc[VEOF]=CEOF;
#ifdef CDISCARD
    setterm.c_cc[VDISCARD]=CDISCARD;
#endif
#ifdef CEOL
    setterm.c_cc[CEOL] = CEOL;
#endif

    /*
     *  SMR - Linux does funny things if VMIN is zero (like more doesn't work),
     *        so I put it to one here.
     */

    setterm.c_cc[VMIN] = 1;
    tcsetattr(0,TCSANOW,&setterm);
    tcsetattr(1,TCSANOW,&setterm);
    tcsetattr(2,TCSANOW,&setterm);
  }
}

