C:\swigwin-3.0.5\swig.exe -python -c++ -I"C:\Program Files (x86)\Microsoft SDKs\Windows\v7.0A\Include" -Wall -o _libhfst.cpp libhfst_win.i
cl.exe /EHsc /LD /IC:\Python33\include\ _libhfst.cpp /link libhfst.lib
move _libhfst.dll _libhfst.pyd
copy C:\python33\libs\python33.lib .
