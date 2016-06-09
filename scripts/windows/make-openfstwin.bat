SET debug_compile=

if "%1%"=="/DEBUG" SET debug_compile=/Zi /O2 /MDd

SET extra_cpp_files=
SET extra_obj_files=

if exist symbol-table-ops.cpp SET extra_cpp_files=symbol-table-ops.cpp
if exist symbol-table-ops.cpp SET extra_obj_files=symbol-table-ops.obj

cl %debug_compile% /EHsc /LD /DOPENFSTEXPORT /D_MSC_VER /DWINDOWS /DWIN32 /Feopenfst.dll /I ..\include\ compat.cpp flags.cpp fst.cpp properties.cpp symbol-table.cpp %extra_cpp_files% util.cpp
!! lib.exe /OUT:openfst.lib compat.obj flags.obj fst.obj properties.obj symbol-table.obj %extra_obj_files% util.obj
