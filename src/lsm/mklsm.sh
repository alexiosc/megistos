#!/bin/sh

major=$1
minor=$2
date=`date +'%d%b%y'|tr '[:lower:]' '[:upper:]'`

gawk <lsm/$3.lsm -vmajor=$major -vminor=$minor -vdate=$date -- '{
    gsub(/@major/,major);
    gsub(/@minor/,minor);
    gsub(/@date/,date);
    print;
}'
