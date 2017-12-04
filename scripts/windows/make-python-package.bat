echo off

mkdir %1
mkdir %1\hfst
mkdir %1\hfst\exceptions
mkdir %1\hfst\sfst_rules
mkdir %1\hfst\xerox_rules

copy README_python_win.txt %1\README.txt
copy _libhfst.pyd %1\
copy libhfst.py %1\
copy hfst\__init__.py %1\hfst\__init__.py
copy hfst\exceptions\__init__.py %1\hfst\exceptions\__init__.py
copy hfst\sfst_rules\__init__.py %1\hfst\sfst_rules\__init__.py
copy hfst\xerox_rules\__init__.py %1\hfst\xerox_rules\__init__.py

"C:\Program Files\7-Zip\7z.exe" a -t7z %1".7z" %1
"C:\Program Files\7-Zip\7z.exe" a -tzip %1".zip" %1
