
This directory contains 64-bit python bindings for HFST for Mac OS X. The C++
part is binary code and the python part is source code. The bindings work with
all versions of python3. The structure of the directory is the following:

  .
  ├── hfst
  │   ├── exceptions
  │   │   └── __init__.py
  │   ├── __init__.py
  │   ├── sfst_rules
  │   │   └── __init__.py
  │   └── xerox_rules
  │       └── __init__.py
  ├── libhfst.py
  ├── _libhfst.so
  └── README


The files 'libhfst.py' and '_libhfst.so' as well as folder 'hfst' should be
installed under folder 'site-packages' of the version of python you are using,
e.g. /usr/local/lib/python3.4/site-packages/. Alternatively, you can use python
in the directory where you have these files or add the path to sys.path.

For more information about the python API, see:

  https://hfst.github.io/python/index.html
