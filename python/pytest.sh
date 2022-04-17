#!/bin/bash

BASEDIR=$(realpath $PWD)
export PYTHONPATH=$BASEDIR:$BASEDIR/lib

OPTS="--doctest-modules --ff --strict-markers -vvv --rootdir=$PWD"

if [[ "$*" =~ \.py ]]; then
    pytest $OPTS "$@"
else
    pytest $OPTS "$@" megistos/*py pytest/*py
fi

# End of file.
