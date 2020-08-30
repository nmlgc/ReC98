@echo off
echo Running the first, 32-bit part of the ReC98 build process.

set ReC98_ASM=tasm32 /m /mx /kh32768 /t /ilibs\master.lib\
set CXX32=bcc32

%ReC98_ASM% 1>NUL 2>NUL
if errorlevel 9009 goto no_tasm32

%CXX32% 1>NUL 2>NUL
if errorlevel 9009 goto no_bcc32

REM Silence incorrect warnings for Borland C++ 5.5
REM ----------------------------------------------
REM 'identifier' is assigned a value that is never used
set CXX32FLAGS=%CXX32FLAGS% -w-8004
REM Comparing signed and unsigned values
set CXX32FLAGS=%CXX32FLAGS% -w-8012
REM ----------------------------------------------

set CXX32FLAGS=%CXX32FLAGS% -O2 -v- -x-

: Neither BCC32 nor TASM32 automatically create nonexisting output
: directories...
mkdir bin\Pipeline 2>NUL
for /L %%i in (1,1,5) do mkdir bin\th0%%i 2>NUL

del /S *.obj

set BMP2ARR=bin\Pipeline\bmp2arr.exe

%CXX32% %CXX32FLAGS% -nbin/Pipeline/ Pipeline\bmp2arr.c Pipeline\bmp2arrl.c

%BMP2ARR% -i th01/sprites/pellet.bmp -o th01/sprites/pellet.csp -sym sPELLET -of c -sw 8 -sh 8 -pshf inner
%BMP2ARR% -i th01/sprites/pellet_c.bmp -o th01/sprites/pellet_c.asp -sym _sPELLET_CLOUD -of asm -sw 16 -sh 16
%BMP2ARR% -i th01/sprites/shape8x8.bmp -o th01/sprites/shape8x8.asp -sym _sSHAPE8X8 -of asm -sw 8 -sh 8
%BMP2ARR% -i th02/sprites/pellet.bmp -o th02/sprites/pellet.asp -sym _sPELLET -of asm -sw 8 -sh 8 -pshf outer
%BMP2ARR% -i th02/sprites/sparks.bmp -o th02/sprites/sparks.asp -sym _sSPARKS -of asm -sw 8 -sh 8 -pshf outer
%BMP2ARR% -i th02/sprites/pointnum.bmp -o th02/sprites/pointnum.asp -sym _sPOINTNUMS -of asm -sw 8 -sh 8
%BMP2ARR% -i th03/sprites/score.bmp -o th03/sprites/score.asp -sym _sSCORE_FONT -of asm -sw 8 -sh 8 -u
%BMP2ARR% -i th04/sprites/pelletbt.bmp -o th04/sprites/pelletbt.asp -sym _sPELLET_BOTTOM -of asm -sw 8 -sh 4 -pshf outer
%BMP2ARR% -i th04/sprites/pointnum.bmp -o th04/sprites/pointnum.asp -sym _sPOINTNUMS -of asm -sw 8 -sh 8 -pshf inner
%BMP2ARR% -i th05/sprites/gaiji.bmp -o th05/sprites/gaiji.asp -sym _sGAIJI -of asm -sw 16 -sh 16
%BMP2ARR% -i th05/sprites/piano_l.bmp -o th05/sprites/piano_l.asp -sym _sPIANO_LABEL_FONT -of asm -sw 8 -sh 8

%ReC98_ASM% th01_op.asm bin\th01\op.obj
%ReC98_ASM% th01_reiiden.asm bin\th01\reiiden.obj
%ReC98_ASM% th01_fuuin.asm bin\th01\fuuin.obj

%ReC98_ASM% th02_zuninit.asm bin\th02\zuninit.obj
%ReC98_ASM% th02_op.asm bin\th02\op.obj
%ReC98_ASM% th02_main.asm bin\th02\main.obj
%ReC98_ASM% th02_maine.asm bin\th02\maine.obj

%ReC98_ASM% /DTHIEF libs\sprite16\sprite16.asm bin\th03\zunsp.obj
%ReC98_ASM% th03_op.asm bin\th03\op.obj
%ReC98_ASM% th03_main.asm bin\th03\main.obj
%ReC98_ASM% th03_mainl.asm bin\th03\mainl.obj

%ReC98_ASM% th04_op.asm bin\th04\op.obj
%ReC98_ASM% th04_main.asm bin\th04\main.obj
%ReC98_ASM% th04_maine.asm bin\th04\maine.obj

%ReC98_ASM% th05_op.asm bin\th05\op.obj
%ReC98_ASM% th05_main.asm bin\th05\main.obj
%ReC98_ASM% th05_maine.asm bin\th05\maine.obj
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
