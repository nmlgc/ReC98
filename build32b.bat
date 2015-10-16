@echo off
echo Running the first, 32-bit part of the ReC98 build process.

set ReC98_ASM=tasm32 /m /mx /kh32768 /t /ilibs\master_l\

del /S *.obj
for /L %%i in (1,1,5) do mkdir bin\th0%%i 2>NUL

%ReC98_ASM% 1>NUL 2>NUL
if errorlevel 9009 goto no_tasm32

%ReC98_ASM% t1op.asm bin\th01\op.obj
%ReC98_ASM% t1reiide.asm bin\th01\reiiden.obj
%ReC98_ASM% t1fuuin.asm bin\th01\fuuin.obj

%ReC98_ASM% t2zunini.asm bin\th02\zuninit.obj
%ReC98_ASM% t2op.asm bin\th02\op.obj
%ReC98_ASM% t2main.asm bin\th02\main.obj
%ReC98_ASM% t2maine.asm bin\th02\maine.obj

%ReC98_ASM% t3zunsp.asm bin\th03\zunsp.obj
%ReC98_ASM% t3r_yume.asm bin\th03\res_yume.obj
%ReC98_ASM% t3op.asm bin\th03\op.obj
%ReC98_ASM% t3main.asm bin\th03\main.obj
%ReC98_ASM% t3mainl.asm bin\th03\mainl.obj

%ReC98_ASM% t4r_huma.asm bin\th04\res_huma.obj
%ReC98_ASM% t4op.asm bin\th04\op.obj
%ReC98_ASM% t4main.asm bin\th04\main.obj
%ReC98_ASM% t4maine.asm bin\th04\maine.obj

%ReC98_ASM% t5r_kso.asm bin\th05\res_kso.obj
%ReC98_ASM% t5op.asm bin\th05\op.obj
%ReC98_ASM% t5main.asm bin\th05\main.obj
%ReC98_ASM% t5maine.asm bin\th05\maine.obj
goto eof

:no_tasm32
echo Could not find TASM32.
echo Please make sure that the BIN directory of Turbo Assembler 5.0 is in your PATH.
goto eof

:eof
echo -------------------------------------------------------------------------------
