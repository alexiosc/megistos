#!/bin/sh
#
# FILE: mkversion.sh 
# AUTHOR: Alexios
#

if [ ! -e version.mk ]; then
    echo 0 >version.mk
fi

ver=$[ `cat version.mk` + 1 ]
echo $ver >version.mk

(
    echo '/* Automatically generated by mkversion.sh , do NOT edit. */'
    echo 
    echo '#define BJ_MAJORVERSION "'$1'"'
    echo '#define BJ_MINORVERSION "'$2'"'
    echo '#define BJ_COMPILED_BY  "'`whoami`'@'`hostname`'"'
    echo '#define BJ_MAKE_NUMBER  "'$ver'"'
    echo '#define BJ_DATE         "'`date '+%y-%m-%d %H:%M'`'"'
) >bjver.h
