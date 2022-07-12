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
goto check_bcc32

: Re-run the actual TASM check for Windows 9x. Calling a nonexistent command
: leaves ERRORLEVEL untouched, so we have to override it ourselves first.
:check_tasm32_win9x
call set_errorlevel_to_1.bat
tasm32 >NUL %STDERR_IGNORE%
if errorlevel 1 goto no_tasm32

:check_bcc32
call set_errorlevel_to_1.bat
bcc32 >NUL %STDERR_IGNORE%
if errorlevel 1 goto no_bcc32

: Neither BCC32 nor TASM32 automatically create nonexisting output
: directories. Tup would, but not everybody can use it.
mkdir bin\zuncom %STDERR_IGNORE%
mkdir bin\Pipeline %STDERR_IGNORE%
for %%i in (1 2 3 4 5) do mkdir bin\th0%%i %STDERR_IGNORE%

call set_errorlevel_to_1.bat
tup version >NUL
if     errorlevel 1 goto fallback
: NT returns negative values for things like DLL import failures
if not errorlevel 0 goto fallback

tup
goto eof

:fallback
echo [:(] Failed to run Tup (gittup.org/tup), falling back on a dumb full rebuild...
if not errorlevel 0 echo (Delete `tup.exe` to avoid the error message boxes in the future)
call Tupfile.bat

goto eof

:no_tasm32
echo Could not find TASM32.
echo Please make sure that the BIN directory of Turbo Assembler 5.0 is in your PATH.
goto eof

:no_bcc32
echo Could not find BCC32.
echo Please make sure that the BIN directory of Borland C++ 5.5 is in your PATH.
goto eof

:eof
echo -------------------------------------------------------------------------------
