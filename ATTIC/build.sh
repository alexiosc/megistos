#!/bin/bash

PROGNAME=${0#*/}

fail () {
    echo "${PROGNAME}: $@" 1>&2
    exit 1
}

# The base directory
BASEDIR=$(readlink -f "$0")
BASEDIR=${BASEDIR%/*}
[[ -d "$BASEDIR" ]] || fail "BASEDIR ($BASEDIR) is not a directory"
echo "Base directory:          $BASEDIR"

# The build directory
BUILDDIR=$(readlink -f ${BUILDDIR:-$BASEDIR/build})
[[ -d "$BASEDIR" ]] || fail "BUILDDIR ($BUILDDIR) is not a directory"
echo "Build directory:         $BUILDDIR"

# Build directories
PYBUILDDIR=${BUILDDIR}/python
[[ -d ${PYBUILDDIR} ]] || mkdir -p "$PYBUILDDIR"
echo "Python build directory:  $PYBUILDDIR"

PYSOURCEDIR=${BASEDIR}/pymegistos
[[ -d ${PYBUILDDIR} ]] || fail "Python source directory $PYSOURCEDIR not found"
echo "Python source directory: $PYBUILDDIR"

# Get a list of binaries, set variables like PYTHON3=/usr/bin/python3
BINARIES=(
    python3
    virtualenv
)

for a in "${BINARIES[@]}"; do
    varname=$(sed <<<"$a" 's/[^A-Za-z0-9]+/_/g')
    varname=${varname^^}
    bin=$(which "$a")
    if [[ -x "$bin" ]]; then
	declare "$varname"="$bin"
	#echo "$varname is ${!varname}"
    fi
done

# Create and activate the virtual environment
cd ${PYBUILDDIR}
$VIRTUALENV --python $PYTHON3 ${PYBUILDDIR}
ACTIVATE=${PYBUILDDIR}/bin/activate
[[ -r "$ACTIVATE" ]] || fail "virtualenv activation script $ACTIVATE not found"
source "$ACTIVATE"

pip3 install -r $PYSOURCEDIR/requirements.txt

# C stuff
libtoolize --copy --ltdl --force


# End of file.
