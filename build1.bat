@ECHO OFF
SET MINGW_PATH=c:\compilatori\mingw\mingw64-gcc4.5.4\bin
REM SET MINGW_PATH=..\mingw64\bin
%MINGW_PATH%\gcc p1.c -c
%MINGW_PATH%\gcc ui.c -c
%MINGW_PATH%\windres resources.rc -o resources.o
%MINGW_PATH%\gcc p1.o ui.o resources.o -s -mwindows
REM -mwindows -s
