@echo off
echo Running the first, 32-bit part of the ReC98 build process.

: Windows 9x doesn't support stderr redirection, and always sets ERRORLEVEL to
: 2 if you attempt to do that, regardless of `tasm32`'s existence. NT properly
: returns 9009 if not found, or 0 otherwise.
set STDERR_IGNORE=
tasm32 >NUL 2>NUL
if errorlevel 9009 goto no_tasm32
if errorlevel    2 goto check_tasm32_win9x

: NT + TASM32 existing confirmed at this point
setlocal
set STDERR_IGNORE=2^>NUL
goto build

: Re-run the actual TASM check for Windows 9x. Calling a nonexistent command
: leaves ERRORLEVEL untouched, so we have to override it ourselves first.
:check_tasm32_win9x
call set_errorlevel_to_1.bat
tasm32 >NUL %STDERR_IGNORE%
if errorlevel 1 goto no_tasm32

:build

: Neither BCC32 nor TASM32 automatically create nonexisting output
: directories. Tup would, but not everybody can use it.
for /L %%i in (1,1,5) do mkdir bin\th0%%i %STDERR_IGNORE%

tup

goto eof

:no_tasm32
echo Could not find TASM32.
echo Please make sure that the BIN directory of Turbo Assembler 5.0 is in your PATH.
goto eof

:eof
echo -------------------------------------------------------------------------------
