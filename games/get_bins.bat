::===============================================================
:: Program for extraction binaries for boffin magnetic games
::
::===============================================================

@echo off

:: Set dir variables
set dst_dir=".\BINS\"
set ext=.bin

:: Remove and make bins directory
:: rmdir %dst_dir% /S /Q 1> nul 2> nul
mkdir %dst_dir% 1> nul 2> nul

:: Copy all bins
setlocal enabledelayedexpansion
for /r . %%f in (*%ext%) do (
    set str=%%f
    set str=!str:*Games\=!
    set str=!str:~0,3!
    set foo=%%f
    set foo=!foo:*_=!
    for /f "tokens=1 delims=\" %%a in ("!foo!") do (
        set foo=%%a
    )
    if NOT !str! == BIN (
        echo %%f | find /v "BINS" 1> nul 2> nul && copy /-Y %%f %dst_dir%"!str!"%ext%  2> nul && echo !str!%ext% copy from !foo! || echo Failed to copy !foo!
    )
)
endlocal

echo      _.-'''''-._
echo    .'  _     _  '.
echo   /   (_)   (_)   \
echo  ^|  ,           ,  ^|
echo  ^|  \`.       .`/  ^|
echo   \  '.`'""""`.'  /
echo    '.  `'---'`  .'
echo      '-._____.-'

PAUSE