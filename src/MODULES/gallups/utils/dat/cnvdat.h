#ifndef __GALLUPS_H
#define __GALLUPS_H

#define GALLUPSDIR BBSDATADIR"/gallups/.old"

#define GQ_NUMBER           0
#define GQ_FREETEXT         1
#define GQ_CHOICES_SINGLE   2
#define GQ_CHOICES_MULTIPLE 3

#define GI_MAXFNLEN        11

#define GF_VIEWRESALL       1
#define GF_MULTISUBMIT      2

#define GN_MASKMIN       0x1fffc
#define GN_MASKMAX    0xfffe0000
#define GN_MINSHIFT            2
#define GN_MAXSHIFT           17

struct question {
  char *text;
  char *chorep;
  unsigned int  qtype;
};

struct {
  unsigned int numquestions;
  char filename[GI_MAXFNLEN];
  char *description;
  char flags;
} pollinfo;

const unsigned int MAXCHOICES = (2 << sizeof(int)) - 2;

#endif
