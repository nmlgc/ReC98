@echo off
echo Running the second, 16-bit part of the ReC98 build process.
echo If this fails or shows other weird behavior, run BUILD16B separately in DOSBox.
REM (Yes, we don't use %0%, as it actually has to be %0 on DOS. Just spelling
REM out the name saves us that trouble.)

set ReC98_LINK=tlink

%ReC98_LINK% 1>NUL 2>NUL
if errorlevel 9009 goto no_tlink
if errorlevel 216 goto 64_bit

%ReC98_LINK% /t bin\th01\zunsoft.obj
%ReC98_LINK% bin\th01\op.obj
%ReC98_LINK% bin\th01\reiiden.obj
%ReC98_LINK% bin\th01\fuuin.obj
%ReC98_LINK% /t bin\th02\zuninit.obj
%ReC98_LINK% /t bin\th02\zun_res.obj
%ReC98_LINK% bin\th02\op.obj
%ReC98_LINK% bin\th02\main.obj
%ReC98_LINK% bin\th02\maine.obj
%ReC98_LINK% /t /3 bin\th03\zunsp.obj
%ReC98_LINK% /t bin\th03\res_yume.obj
%ReC98_LINK% bin\th03\op.obj
%ReC98_LINK% bin\th03\main.obj
%ReC98_LINK% bin\th03\mainl.obj
%ReC98_LINK% /t bin\th04\res_huma.obj
%ReC98_LINK% bin\th04\op.obj
%ReC98_LINK% bin\th04\main.obj
%ReC98_LINK% bin\th04\maine.obj
%ReC98_LINK% /t bin\th05\res_kso.obj
%ReC98_LINK% bin\th05\op.obj
%ReC98_LINK% bin\th05\main.obj
%ReC98_LINK% bin\th05\maine.obj
echo Done. Find the executables in the bin\ subdirectory.
goto eof

:64_bit
echo You're running a 64-bit OS. Run BUILD16B.BAT separately in DOSBox instead.
goto eof

:no_tlink
echo Could not find TLINK.
echo Please make sure that the BIN directory of Turbo C++ 4.0J is in your PATH.
goto eof

:eof
