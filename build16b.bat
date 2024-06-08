@echo off
echo Running the second, 16-bit part of the ReC98 build process.
echo If this fails or shows other weird behavior, run BUILD16B separately in DOSBox.
REM (Yes, we don't use %0%, as it actually has to be %0 on DOS. Just spelling
REM out the name saves us that trouble.)

maker -B
if errorlevel 9009 goto no_make
if errorlevel 216 goto 64_bit
goto eof

:64_bit
echo You're running a 64-bit OS. Run BUILD16B.BAT separately in DOSBox instead.
goto eof

:no_make
echo Could not find MAKER.
echo Please make sure that the BIN directory of Turbo C++ 4.0J is in your PATH.

:eof
