@echo off
echo Running the second, 16-bit part of the ReC98 build process.
echo If this fails or shows other weird behavior, run BUILD16B separately in DOSBox.
REM (Yes, we don't use %0%, as it actually has to be %0 on DOS. Just spelling
REM out the name saves us that trouble.)

tlink >NUL
if errorlevel 9009 goto no_tlink
if errorlevel 216 goto 64_bit

tcc >NUL
if errorlevel 9009 goto no_tcc
if errorlevel 216 goto 64_bit

maker
if errorlevel 9009 goto no_make
if errorlevel 216 goto 64_bit
goto eof

:64_bit
echo You're running a 64-bit OS. Run BUILD16B.BAT separately in DOSBox instead.
goto eof

:no_tlink
echo Could not find TLINK.
goto tc4j_bin
:no_make
echo Could not find MAKER.
goto tc4j_bin
:tc4j_bin
echo Please make sure that the BIN directory of Turbo C++ 4.0J is in your PATH.
goto eof

:eof
