#!/bin/bash

BASEDIR=$(realpath $PWD)
BASEDIR=.
export PYTHONPATH=$BASEDIR:$BASEDIR/lib

OPTS="--doctest-modules --ff --strict-markers -vvv "
#OPTS+="--rootdir=$PWD "
OPTS+="--cov-report=html --cov=megistos "

if [[ "$*" =~ \.py ]]; then
    pytest $OPTS "$@"
else
    pytest $OPTS "$@" megistos/*py pytest/*py
fi

# End of file.
