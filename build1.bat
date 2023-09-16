@ECHO OFF
REM SET MINGW_PATH=c:\compilatori\mingw\mingw64-gcc4.5.4\bin
REM SET MINGW_PATH=..\mingw64\bin
call set_path_mingw.bat
%MINGW_PATH%\gcc p1.c -c -Os
%MINGW_PATH%\gcc ui.c -c -Os
%MINGW_PATH%\gcc app.c -c -Os
%MINGW_PATH%\windres resources.rc -o resources.o
%MINGW_PATH%\gcc app.o p1.o ui.o resources.o -s -mwindows -s
REM -mwindows -s
