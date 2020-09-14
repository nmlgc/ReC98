: Dumb, full batch build script, provided as a fallback for systems that can't
: run Tup. Auto-generated via `tup generate`; make sure to re-run that command
: if the Tupfile changes.
@echo on
tasm32 /m /mx /kh32768 /t th01_zunsoft.asm bin\th01\zunsoft.obj
tasm32 /m /mx /kh32768 /t th01_op.asm bin\th01\op.obj
tasm32 /m /mx /kh32768 /t th01_reiiden.asm bin\th01\reiiden.obj
tasm32 /m /mx /kh32768 /t th01_fuuin.asm bin\th01\fuuin.obj
tasm32 /m /mx /kh32768 /t th02_zuninit.asm bin\th02\zuninit.obj
tasm32 /m /mx /kh32768 /t th02_zun_res.asm bin\th02\zun_res.obj
tasm32 /m /mx /kh32768 /t th02_op.asm bin\th02\op.obj
tasm32 /m /mx /kh32768 /t th02_main.asm bin\th02\main.obj
tasm32 /m /mx /kh32768 /t th02_maine.asm bin\th02\maine.obj
tasm32 /m /mx /kh32768 /t th03_zunsp.asm bin\th03\zunsp.obj
tasm32 /m /mx /kh32768 /t th03_res_yume.asm bin\th03\res_yume.obj
tasm32 /m /mx /kh32768 /t th03_op.asm bin\th03\op.obj
tasm32 /m /mx /kh32768 /t th03_main.asm bin\th03\main.obj
tasm32 /m /mx /kh32768 /t th03_mainl.asm bin\th03\mainl.obj
tasm32 /m /mx /kh32768 /t th04_zuninit.asm bin\th04\zuninit.obj
tasm32 /m /mx /kh32768 /t th04_res_huma.asm bin\th04\res_huma.obj
tasm32 /m /mx /kh32768 /t th04_op.asm bin\th04\op.obj
tasm32 /m /mx /kh32768 /t th04_main.asm bin\th04\main.obj
tasm32 /m /mx /kh32768 /t th04_maine.asm bin\th04\maine.obj
tasm32 /m /mx /kh32768 /t th05_res_kso.asm bin\th05\res_kso.obj
tasm32 /m /mx /kh32768 /t th05_op.asm bin\th05\op.obj
tasm32 /m /mx /kh32768 /t th05_main.asm bin\th05\main.obj
tasm32 /m /mx /kh32768 /t th05_maine.asm bin\th05\maine.obj
@echo off
