/*****************************************************************************\
 **                                                                         **
 **  FILE:     timedate.h                                                   **
 **  AUTHORS:  Alexios                                                      **
 **  REVISION: A, July 94                                                   **
 **  PURPOSE:  Various time & date handling functions                       **
 **  NOTES:    We always return long values instead of int. Word alignment  **
 **            blows that 'space reservation' argument to pieces, better    **
 **            to use 32-bit ints, anyway.                                  **
 **                                                                         **
 **            function | returns |  bitmap      24      16      8       0  **
 **          -----------|---------|--------------|-------|-------|-------|  **
 **            today    | date    |       00000000YYYYYYYY0000MMMM000DDDDD  **
 **            mktime   | time    |       00000000000HHHHH00MMMMMM00SSSSSS  **
 **            now      | time    |       00000000000HHHHH00MMMMMM00SSSSSS  **
 **            strtime  | char*   | HH:MM[:SS] (if secstoo nonzero)         **
 **            strdate  | char*   | DD-MON-YY                               **
 **                                                                         **
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
 **                                                                         **
\*****************************************************************************/


/*
 * $Id$
 *
 * $Log$
 * Revision 1.3  2001/04/22 14:49:05  alexios
 * Merged in leftover 0.99.2 changes and additional bug fixes.
 *
 * Revision 0.4  1998/12/27 14:31:16  alexios
 * Added autoconf support. Added function to get the day of the
 * week of a supplied date.
 *
 * Revision 0.3  1997/11/06 20:03:54  alexios
 * Added GPL legalese to the top of this file.
 *
 * Revision 0.2  1997/09/12 12:52:28  alexios
 * Fixed strdate() so it doesn't use the libc strftime() call,
 * which is obviously changing.
 *
 * Revision 0.1  1997/08/26 16:35:17  alexios
 * First registered revision. Adequate.
 *
 *
 */


#ifndef RCS_VER 
#define RCS_VER "$Id$"
const char *__RCS=RCS_VER;
#endif




#define WANT_STDIO_H 1
#define WANT_STDLIB_H 1
#define WANT_TIME_H 1
#define WANT_CTYPE_H 1
#define WANT_STRING_H 1
#define WANT_TIME_H 1
#include <bbsinclude.h>
#include "timedate.h"


static int daymon[]={0,31,59,90,120,151,181,212,243,273,304,334};


long
maketime(h,m,s)
int h,m,s;
{
  return s | (m<<8) | (h<<16);
}


long
makedate(d,m,y)
int d,m,y;
{
  return (d&0x1f) | ((m-1)<<8) | (((y-1970)&0xff)<<16);
}


long
today()
{
  struct tm *dt;
  time_t t;

  t=time(0);
  dt=localtime(&t);
  return((dt->tm_mday)&0x1f)|((dt->tm_mon)<<8)|(((dt->tm_year-70)&0xff)<<16);
}


long
now()
{
  struct tm *dt;
  time_t t;

  t=time(0);
  dt=localtime(&t);
  return maketime(dt->tm_hour,dt->tm_min,dt->tm_sec);
}


char *
strtime(long time,int secstoo)
{
  static char buf[64];
  int h=(time>>16)&0xff;
  int m=(time>>8)&0xff;
  int s=time&0xff;

  if(secstoo)sprintf(buf,"%02d:%02d:%02d",h,m,s);
  else sprintf(buf,"%02d:%02d",h,m);
  return buf;
}


static char *months[12]={
  "JAN","FEB","MAR",
  "APR","MAY","JUN",
  "JUL","AUG","SEP",
  "OCT","NOV","DEC"};


char *
strdate(long date)
{
  static char buff[32]={0};
  sprintf(buff,"%02d-%3.3s-%02d",
	  (int)tdday(date),months[tdmonth(date)],(int)tdyear(date)%100);
  return buff;
}


long
scandate(char *datstr)
{
  int monthlen[12]={31,28,31,30,31,30,31,31,30,31,30,31};
  int mon,day,year;
  char c1,c2;

  if(sscanf(datstr,"%d%c%d%c%d",&day,&c1,&mon,&c2,&year)==5){
    if((c1!=c2)||((c1!='/')&&(c1!='-'))) return -1L;
  } else if(sscanf(datstr,"%d%c%d",&day,&c1,&mon)==3){
    year=tdyear(now());
    if((c1!='/')&&(c1!='-')) return -1L;
  } else return -1L;

  if(year<70)year+=2000;
  else if(year<100)year+=1900;
  if(year<1970 || year>2225 || mon<1 || mon>12) return -1L;
  if(__isleap(year))monthlen[1]++;
  if(day<1 || day>monthlen[mon-1]) return -1L;

  return makedate(day,mon,year);
}


int
scantime(timstr)
char *timstr;
{
  int h,m,s;
  
  if (sscanf(timstr,"%d:%d:%d",&h,&m,&s)==3);
  else if (sscanf(timstr,"%d:%d",&h,&m)==2)s=0;
  else return -1L;
  
  if(h<1 || h>23 || m<0 || m>59 || s<0 || s>59) return -1L;
  
  return maketime(h,m,s);
}


long
cofdate(date)
long date;
{
     int year,month,days;

     year=tdyear(date)-1970;
     month=tdmonth(date);
     days=365*year+(year+3)/4;
     days+=daymon[month]+(month > 2 && (year&3) == 0);
     return(days+tdday(date)-1);
}


long
dateofc(count)
long count;
{
  int year,month,ydays,mdays,thisyr,ytm;

  for (year=1970,ydays=0,thisyr=366 ; ydays+thisyr <= count ; ) {
    ydays+=thisyr;
    thisyr=365+__isleap((++year));
  }
  for (month=1,mdays=0 ; month < 12 ; month++) {
    ytm=daymon[month]+(__isleap(year) && month >= 2);
    if (ytm > count-ydays) {
      break;
    }
    mdays=ytm;
  }
  return(makedate(count-ydays-mdays+1,month,year));
}


int getdow(int date)
{
  struct tm tm;
  time_t t;
  bzero(&tm,sizeof(tm));
  tm.tm_mday=tdday(date);
  tm.tm_mon=tdmonth(date);
  tm.tm_year=tdyear(date)-1900;
  t=mktime(&tm);
  memcpy(&tm,localtime(&t),sizeof(tm));
  return tm.tm_wday;
}
