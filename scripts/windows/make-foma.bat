SET debug_compile=

if "%1%"=="/DEBUG" SET debug_compile=/Zi /O2 /MDd

cl /EHsc /LD /D_MSC_VER /I . /Felibfoma.dll *.c
