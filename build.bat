@echo off

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
goto check_32bit

: Re-run the actual TASM check for Windows 9x. Calling a nonexistent command
: leaves ERRORLEVEL untouched, so we have to override it ourselves first.
:check_tasm32_win9x
call set_errorlevel_to_1.bat
tasm32 >NUL %STDERR_IGNORE%
if errorlevel 1 goto no_tasm32

: Trying to run either a 64-bit or 16-bit program might look like a better way
: of checking OS bitness, but
: • Windows XP insists on showing an ugly message box when trying to run a
:   64-bit program, and
: • Wine insists on starting DOSBox to run a 16-bit .COM program, which may or
:   may not be installed.
: So, environment variables it is. Thankfully, these are available on every
: 64-bit version of Windows, so we can assume 32-bit if they don't exist.
:check_32bit
set ReC98_DOS=
if "%PROCESSOR_ARCHITEW6432%" == "AMD64" set ReC98_DOS=bin\msdos -e -x
if "%PROCESSOR_ARCHITECTURE%" == "AMD64" set ReC98_DOS=bin\msdos -e -x

call set_errorlevel_to_1.bat
%ReC98_DOS% tlink >NUL %STDERR_IGNORE%
if errorlevel 1 goto no_tlink

call set_errorlevel_to_1.bat
%ReC98_DOS% tcc >NUL %STDERR_IGNORE%
if errorlevel 1 goto no_tcc

if "%ReC98_DOS%" == "" goto fallback

: If we can run Tup, we're also on a decently modern Windows. Update the dumb
: full batch build script by parsing out commands from `tup parse`'s stdout.

: Using three files is the easiest way to preserve the error level of `tup
: parse`, unfortunately.
set unparsed=.tup\unparsed.bat
set parsed=.tup\parsed.bat
set final=build_dumb.bat

: The separate `tup parse` call might take some time.
xcopy /-I /L /D /Y        Tupfile.lua %final% | findstr /B /C:"1 " >NUL || ^
xcopy /-I /L /D /Y Pipeline\rules.lua %final% | findstr /B /C:"1 " >NUL
if errorlevel 1 goto tup

: Tup insists on reparsing the Tupfile if we add or remove any file between
: `tup parse` and `tup`… unless we place it in `.tup/`, which might not exist
: yet.
if not exist .tup\ bin\tup init

bin\tup parse >%unparsed%
if errorlevel 1 del %unparsed% && goto eof

: Wine doesn't support sub-shell output redirection.
call :build_dumb_parse %unparsed% >%parsed%
del %unparsed%

for /f "usebackq" %%f in ('%parsed%') do (
	if 0 neq %%~zf ( move /y %parsed% %final% >NUL ) else ( del %parsed% )
)
goto tup

:build_dumb_parse
setlocal EnableDelayedExpansion
for /f "delims=" %%l in (%~1) do (
	set line=%%l
	if "!line:~0,2!" == "$ " echo !line:~2!
)
endlocal
exit /b

:tup
bin\tup
goto return_from_tup

:fallback
echo [..] Running on a 32-bit OS, falling back on a dumb full rebuild...

: Windows 9x wouldn't support %final% in this position.
call build_dumb.bat

:return_from_tup
if errorlevel 1 goto eof
goto success

:no_tasm32
echo Could not find TASM32.
echo Please make sure that the BIN directory of Turbo Assembler 5.0 is in your PATH.
goto path

:no_tcc
echo Could not find TCC.
goto tc4j_bin
:no_tlink
echo Could not find TLINK.
goto tc4j_bin
:tc4j_bin
echo Please make sure that the BIN directory of Turbo C++ 4.0J is in your PATH.
echo All components of its path must contain characters within your system's
echo *Current language for non-Unicode programs*, but can exceed the 8.3 DOS
echo limitation.
goto path

:path
echo (Current PATH: `%PATH%`)
goto eof

:success
echo Done. Find the executables in the bin\ subdirectory.
echo -------------------------------------------------------------------------------

:eof
