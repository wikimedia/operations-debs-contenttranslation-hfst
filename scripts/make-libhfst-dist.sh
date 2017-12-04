#!/bin/sh

# A script for creating a minimal LGPL package for HFST which contains
# only openfst back-ends, HFST library and python bindings.
# First argument is the the normal HFST
# distribution tarball and second one the directory where alternative files
# for LGPL distribution can be found (folder lgpl-release in hfst repository).

if [ "$1" = "--help" -o "$1" = "-h" ]; then
    echo ""
    echo "A script for creating a minimal LGPL package for HFST which contains"
    echo "only openfst back-ends, HFSTlibrary and python bindings."
    echo ""
    echo "Usage: make-libhfst-dist.sh DIST LGPL_DIR"
    echo ""
    echo "DIST:     the normal HFST distribution tarball"
    echo "LGPL_DIR: the folder where alternative files for LGPL distribution can be found"
    echo ""
    exit 0
fi

if [ ! -e "$1" ]; then
    echo "File "$1" does not exist"
    exit 1
fi

if [ ! -d "$2" ]; then
    echo "Directory "$2" does not exist"
    exit 1
fi

OUTPUT=`tar -xzvf $1`
DIR=`echo $OUTPUT | perl -pe 's/ /\n/g;' | head -1 | perl -pe 's/\///;'`
cd $DIR
cp -R $2/* .
autoreconf -i && ./configure && make dist
tar -xzf $1
NEWDIRNAME="lib"$DIR
mv $DIR $NEWDIRNAME
TARBALL="lib"$DIR".tar.gz"
tar -czvf $TARBALL "lib"$DIR
cp $TARBALL ../
echo "Created lgpl package "$TARBALL
