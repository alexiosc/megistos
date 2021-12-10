#!/bin/bash

BASEDIR=$(readlink -e $(dirname "$0")/..)
ENVDIR=python
PYTHONDIR="$BASEDIR/$ENVDIR"

fail () {
    echo 1>&2 "$@"
    exit 1
}

set -e
set -x

# We must be in the base directory.
cd $BASEDIR || fail "Failed to cd to $BASEDIR"

# Sanity checks.
[[ -d .git && -d node_modules && -d www ]] ||
    fail "Could not find base directory, tried $BASEDIR"

[[ -d $ENVDIR ]] &&
    fail "Directory ${ENVDIR} exists, please delete it or move it ouf ot the way."

[[ -r requirements.txt ]] ||
    fail "Hmm, requirements.txt is missing! Is your git repository checked out properly?"

# Add it to .gitignore just in case
grep -q "^${ENVDIR}$" .gitignore || echo "$ENVDIR" >>.gitignore

# And do the work.
#virtualenv -p $(which python3) --no-site-packages $PYTHONDIR
virtualenv -p $(which python3) $PYTHONDIR
. $PYTHONDIR/bin/activate

# We'll also need some Debian packages to help building.
#sudo apt-get -y install python3-dev python3-lxml libjpeg-dev || true

# Go!
pip install -r requirements.txt

# And instal overrides
cd $BASEDIR/overrides; make

# End of file.
