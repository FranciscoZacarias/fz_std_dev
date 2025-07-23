@echo off

set compiler_and_entry=cl ..\src\main.c

REM Enable warnings with: /W4 /wd4201
REM /wd4201 Ignores the compiler warning C4201 about nameless structs/unions
set cl_default_flags=/Isrc /nologo /FC /Zi 

set external_include= /I"..\src\fz_std"

REM set linker_flags= user32.lib ^
REM                   gdi32.lib ^
REM                   Shell32.lib ^
REM                   winmm.lib

if not exist build mkdir build
pushd build
%compiler_and_entry% %cl_default_flags% %external_include% %linker_flags% /Fe"fz_std.exe"
popd