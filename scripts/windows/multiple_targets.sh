#!/bin/sh
# This is a script that might be useful when compiling
# HFST with mingw in cygwin environment.
# It changes 'c:' in pathnames to '/cygdrive/c/'.

files=`find . -name '*.Plo'`
for file in $files;
do
    sed -i 's/c\:\\/\/cygdrive\/c\//' $file;
done
