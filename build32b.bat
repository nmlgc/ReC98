@echo off
echo Running the first, 32-bit part of the ReC98 build process.

set ReC98_ASM=tasm32 /m /mx /kh32768 /t /ilibs\master.lib\
set CXX32=bcc32

del /S *.obj
for /L %%i in (1,1,5) do mkdir bin\th0%%i 2>NUL

%ReC98_ASM% 1>NUL 2>NUL
if errorlevel 9009 goto no_tasm32

%CXX32% 1>NUL 2>NUL
if errorlevel 9009 goto no_bcc32

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
