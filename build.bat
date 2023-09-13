SET MINGW_PATH=c:\compilatori\mingw\mingw64-gcc4.5.4\bin
REM SET MINGW_PATH=..\mingw64\bin
%MINGW_PATH%\gcc p.c -c -mwindows
%MINGW_PATH%\windres resources.rc -o resources.o
%MINGW_PATH%\gcc p.o resources.o -s -mwindows
REM -mwindows -s
