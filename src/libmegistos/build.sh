#!/bin/bash

BASEDIR=$(dirname $(readlink -f "$0"))

[[ -d $BASEDIR/m4 ]] || mkdir $BASEDIR/m4
[[ -e $BASEDIR/megistos ]] || ( cd $BASEDIR; ln -s . megistos )

set -e

autoreconf --install
autoconf
aclocal
#automake

./configure "$@"
make

# End of file.