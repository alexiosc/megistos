#!/bin/bash

if [ ! -e version.mk ]; then
    echo 0 >version.mk
fi

ver=$[ `cat version.mk` + 1 ]
echo $ver >version.mk

cat <<EOF >../INCLUDE/ver.h
/* Automatically generated, do NOT edit. */
#define __MAJORVERSION "$1"
#define __MINORVERSION "$2"
#define __PATCHLEVEL   "$3"
#define __COMPILED_BY  "`whoami`@`hostname`"
#define __MAKE_NUMBER  "$ver"
#define __DATE         "`date '+%y-%m-%d %H:%m'`"

extern char bbs_shortversion[];
extern char bbs_systemversion[];
extern char bbs_compiledby[];
extern char bbs_compiledon[];
extern char bbs_majorversion[];
extern char bbs_minorversion[];
extern char bbs_patchlevel[];
extern char bbs_makenumber[];
EOF
