@echo off
REM Batch script to compile main.c and source files from subfolders into ks.exe and run it

REM Set the output executable name
set OUTPUT=ks.exe

REM Collect main.c and files from subfolders
setlocal enabledelayedexpansion
set SOURCES=main.c
set SOURCES=!SOURCES! main_all.c

REM Add all .c files from the subdirectories
for /D %%d in (ga_ks greedy_ks dynamic_ks bruteforce_ks) do (
    for %%f in (%%d\*.c) do (
        set SOURCES=!SOURCES! %%f
    )
)

REM Include paths for header files (root and subdirectories)
set INCLUDES=-I. -Iga_ks -Igreedy_ks -Idynamic_ks -Ibruteforce_ks

REM Compile using GCC with include paths
echo Compiling your program...
gcc !SOURCES! %INCLUDES% -o %OUTPUT%

REM Check for compilation errors
if %ERRORLEVEL% neq 0 (
    echo Compilation failed!
    pause
    exit /b %ERRORLEVEL%
)

REM Run the compiled executable
echo Compilation successful. Running the program...
@REM echo ------------------------------------------------
%OUTPUT%
@REM echo ------------------------------------------------
pause
