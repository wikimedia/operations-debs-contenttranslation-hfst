#!/bin/sh

# A script to download dlfcn

if ! (mkdir tmp); then
    echo "Error when making temporary directory tmp!";
    exit 1;
fi

cd tmp;

if ! (wget http://dlfcn-win32.googlecode.com/files/dlfcn-win32-r19.tar.bz2); then
    echo "Error when retrieving dlfcn!";
    exit 1;
fi

if ! (tar -xjf dlfcn-win32-r19.tar.bz2); then
    echo "Error when extracting files!";
    exit 1;
fi

if [ ! -d "dlfcn-win32-r19" ]; then
    echo "Error: no directory dlfcn-win32-r19!";
    exit 1;
fi

cd dlfcn-win32-r19;

if ! (cp dlfcn.c ../../dlfcn.c); then
    echo "Error when copying file dlfcn.c!";
    exit 1;
fi

if ! (cp dlfcn.h ../../dlfcn.h); then
    echo "Error when copying file dlfcn.h!";
    exit 1;
fi

if ! (rm -f *); then
    echo "Error when removing temporary files!";
    exit 1;
fi

cd ..;

if ! (rmdir dlfcn-win32-r19); then
    echo "Error when removing directory dlfcn-win32-r19!";
    exit 1;
fi

if ! (rm -f *); then
    echo "Error when removing temporary files!";
    exit 1;
fi

cd ..;

if ! (rmdir tmp); then
    echo "Error when removing temporary directory tmp!";
    exit 1;
fi


# Modify the file dlfcn.h

if ! (sed -i 's/#define DLFCN_H/#define DLFCN_H \
#ifdef __cplusplus \
extern "C" { \
#endif/' dlfcn.h); then
    echo "Modifying the file dlfcn.h failed!";
    exit 1;
fi

if ! (sed -i 's/#endif \/\* DLFCN_H \*\// \
#ifdef __cplusplus \
} \
#endif \
#endif \/\* DLFCN_H \*\//' dlfcn.h); then
    echo "Modifying the file dlfcn.h failed!";
    exit 1;
fi
