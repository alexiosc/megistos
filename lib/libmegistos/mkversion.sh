#!/bin/bash

if [ ! -e version.mk ]; then
    echo 0 >version.mk
fi

ver=$[ `cat version.mk` + 1 ]
echo $ver >version.mk

cat <<EOF >version.h
/* Automatically generated, do NOT edit. */
#define __MAJORVERSION "$1"
#define __MINORVERSION "$2"
#define __PATCHLEVEL   "$3"
#define __COMPILED_BY  "`whoami`@`hostname`"
#define __MAKE_NUMBER  "$ver"
#define __DATE         "`date '+%y-%m-%d %H:%m'`"
EOF
