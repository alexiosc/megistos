#!/bin/sh

major=$1
minor=$2
patch=$3
file=$4
date=`date +'%d%b%y'|tr '[:lower:]' '[:upper:]'`

gawk <lsm/$file.lsm -vmajor=$major -vminor=$minor -vpatch=$patch -vdate=$date -- '{
    gsub(/@major/,major);
    gsub(/@minor/,minor);
    gsub(/@patch/,patch);
    gsub(/@date/,date);
    print;
}'
