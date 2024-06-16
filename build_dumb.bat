: Dumb, full batch build script for 32-bit systems that can't run Tup, but can
: natively run DOS-based tools. Automatically generated whenever `Tupfile.lua`
: is modified.
@echo off
bcc32 -w-8004 -w-8012 -O2 -v- -x- -nbin/Pipeline/ Pipeline/bmp2arr.c Pipeline/bmp2arrl.c
tasm32 /m /mx /kh32768 /t Pipeline\zun_stub.asm obj\Pipeline\zun_stub.obj
tasm32 /m /mx /kh32768 /t Pipeline\cstmstub.asm obj\Pipeline\cstmstub.obj
tasm32 /m /mx /kh32768 /t /ml libs\piloadc\piloadc.asm obj\piloadc.obj
tasm32 /m /mx /kh32768 /t /dTHIEF libs\sprite16\sprite16.asm obj\th03\zunsp.obj
bin\Pipeline\bmp2arr.exe -q -i th01/sprites/leaf_s.bmp -o th01/sprites/leaf_s.csp -sym sSPARK -of cpp -sw 8 -sh 8
bin\Pipeline\bmp2arr.exe -q -i th01/sprites/leaf_l.bmp -o th01/sprites/leaf_l.csp -sym sLEAF_LEFT -of cpp -sw 8 -sh 8
bin\Pipeline\bmp2arr.exe -q -i th01/sprites/leaf_r.bmp -o th01/sprites/leaf_r.csp -sym sLEAF_RIGHT -of cpp -sw 8 -sh 8
bin\Pipeline\bmp2arr.exe -q -i th01/sprites/ileave_m.bmp -o th01/sprites/ileave_m.csp -sym sINTERLEAVE_MASKS -of cpp -sw 8 -sh 8
bin\Pipeline\bmp2arr.exe -q -i th01/sprites/laser_s.bmp -o th01/sprites/laser_s.csp -sym sSHOOTOUT_LASER -of cpp -sw 16 -sh 8
bin\Pipeline\bmp2arr.exe -q -i th01/sprites/mousecur.bmp -o th01/sprites/mousecur.csp -sym sMOUSE_CURSOR -of cpp -sw 16 -sh 16
bin\Pipeline\bmp2arr.exe -q -i th01/sprites/pellet.bmp -o th01/sprites/pellet.csp -sym sPELLET -of cpp -sw 8 -sh 8 -pshf inner
bin\Pipeline\bmp2arr.exe -q -i th01/sprites/pellet_c.bmp -o th01/sprites/pellet_c.csp -sym sPELLET_CLOUD -of cpp -sw 16 -sh 16
bin\Pipeline\bmp2arr.exe -q -i th01/sprites/pillar.bmp -o th01/sprites/pillar.csp -sym sPILLAR -of cpp -sw 32 -sh 8
bin\Pipeline\bmp2arr.exe -q -i th01/sprites/shape8x8.bmp -o th01/sprites/shape8x8.csp -sym sSHAPE8X8 -of cpp -sw 8 -sh 8
bin\Pipeline\bmp2arr.exe -q -i th01/sprites/bonusbox.bmp -o th01/sprites/bonusbox.csp -sym sSTAGEBONUS_BOX -of cpp -sw 8 -sh 4
tasm32 /m /mx /kh32768 /t /dGAME=1 th01_op.asm obj\th01\op.obj
tasm32 /m /mx /kh32768 /t /dGAME=1 th01_reiiden.asm obj\th01\reiiden.obj
tasm32 /m /mx /kh32768 /t /dGAME=1 th01_fuuin.asm obj\th01\fuuin.obj
bin\Pipeline\bmp2arr.exe -q -i th02/sprites/bombpart.bmp -o th02/sprites/bombpart.asp -sym _sBOMB_PARTICLES -of asm -sw 8 -sh 8
bin\Pipeline\bmp2arr.exe -q -i th02/sprites/pellet.bmp -o th02/sprites/pellet.asp -sym _sPELLET -of asm -sw 8 -sh 8 -pshf outer
bin\Pipeline\bmp2arr.exe -q -i th02/sprites/sparks.bmp -o th02/sprites/sparks.asp -sym _sSPARKS -of asm -sw 8 -sh 8 -pshf outer
bin\Pipeline\bmp2arr.exe -q -i th02/sprites/pointnum.bmp -o th02/sprites/pointnum.asp -sym _sPOINTNUMS -of asm -sw 8 -sh 8
bin\Pipeline\bmp2arr.exe -q -i th02/sprites/verdict.bmp -o th02/sprites/verdict.csp -sym sVERDICT_MASKS -of cpp -sw 16 -sh 16
tasm32 /m /mx /kh32768 /t /dGAME=2 th02_zuninit.asm obj\th02\zuninit.obj
tasm32 /m /mx /kh32768 /t /dGAME=2 th02_op.asm obj\th02\op.obj
tasm32 /m /mx /kh32768 /t /dGAME=2 th02_main.asm obj\th02\main.obj
tasm32 /m /mx /kh32768 /t /dGAME=2 th02_maine.asm obj\th02\maine.obj
bin\Pipeline\bmp2arr.exe -q -i th03/sprites/score.bmp -o th03/sprites/score.asp -sym _sSCORE_FONT -of asm -sw 8 -sh 8 -u
tasm32 /m /mx /kh32768 /t /dGAME=3 th03_op2.asm obj\th03\op2.obj
tasm32 /m /mx /kh32768 /t /dGAME=3 th03_op.asm obj\th03\op.obj
tasm32 /m /mx /kh32768 /t /dGAME=3 th03\cdg_put.asm obj\th03\cdg_put.obj
tasm32 /m /mx /kh32768 /t /dGAME=3 th03\cdg_p_na.asm obj\th03\cdg_p_na.obj
tasm32 /m /mx /kh32768 /t /dGAME=3 th03\hfliplut.asm obj\th03\hfliplut.obj
tasm32 /m /mx /kh32768 /t /dGAME=3 th03_main.asm obj\th03\main.obj
tasm32 /m /mx /kh32768 /t /dGAME=3 th03\collmap.asm obj\th03\collmap.obj
tasm32 /m /mx /kh32768 /t /dGAME=3 th03_mainl.asm obj\th03\mainl.obj
bin\Pipeline\bmp2arr.exe -q -i th04/sprites/pelletbt.bmp -o th04/sprites/pelletbt.asp -sym _sPELLET_BOTTOM -of asm -sw 8 -sh 4 -pshf outer
bin\Pipeline\bmp2arr.exe -q -i th04/sprites/pointnum.bmp -o th04/sprites/pointnum.asp -sym _sPOINTNUMS -of asm -sw 8 -sh 8 -pshf inner
tasm32 /m /mx /kh32768 /t /dGAME=4 th04_zuninit.asm obj\th04\zuninit.obj
tasm32 /m /mx /kh32768 /t /dGAME=4 th04_memchk.asm obj\th04\memchk.obj
tasm32 /m /mx /kh32768 /t /dGAME=4 th04_op_master.asm obj\th04\opm.obj
tasm32 /m /mx /kh32768 /t /dGAME=4 th04\cdg_p_nc.asm obj\th04\cdg_p_nc.obj
tasm32 /m /mx /kh32768 /t /dGAME=4 th04\grppsafx.asm obj\th04\grppsafx.obj
tasm32 /m /mx /kh32768 /t /dGAME=4 th04_op2.asm obj\th04\op2.obj
tasm32 /m /mx /kh32768 /t /dGAME=4 th04\cdg_put.asm obj\th04\cdg_put.obj
tasm32 /m /mx /kh32768 /t /dGAME=4 th04\input_s.asm obj\th04\input_s.obj
tasm32 /m /mx /kh32768 /t /dGAME=4 th04\bgimager.asm obj\th04\bgimager.obj
tasm32 /m /mx /kh32768 /t /dGAME=4 th04\cdg_load.asm obj\th04\cdg_load.obj
tasm32 /m /mx /kh32768 /t /dGAME=4 th04_op.asm obj\th04\op.obj
tasm32 /m /mx /kh32768 /t /dGAME=4 th04_main.asm obj\th04\main.obj
tasm32 /m /mx /kh32768 /t /dGAME=4 th04\scoreupd.asm obj\th04\scoreupd.obj
tasm32 /m /mx /kh32768 /t /dGAME=4 th04\cdg_p_pr.asm obj\th04\cdg_p_pr.obj
tasm32 /m /mx /kh32768 /t /dGAME=4 th04\motion_3.asm obj\th04\motion_3.obj
tasm32 /m /mx /kh32768 /t /dGAME=4 th04\vector2n.asm obj\th04\vector2n.obj
tasm32 /m /mx /kh32768 /t /dGAME=4 th04\spark_a.asm obj\th04\spark_a.obj
tasm32 /m /mx /kh32768 /t /dGAME=4 th04_maine_master.asm obj\th04\mainem.obj
tasm32 /m /mx /kh32768 /t /dGAME=4 th04\cdg_p_pl.asm obj\th04\cdg_p_pl.obj
tasm32 /m /mx /kh32768 /t /dGAME=4 th04_maine.asm obj\th04\maine.obj
bin\Pipeline\bmp2arr.exe -q -i th05/sprites/gaiji.bmp -o th05/sprites/gaiji.asp -sym _sGAIJI -of asm -sw 16 -sh 16
bin\Pipeline\bmp2arr.exe -q -i th05/sprites/piano_l.bmp -o th05/sprites/piano_l.asp -sym _sPIANO_LABEL_FONT -of asm -sw 8 -sh 8
tasm32 /m /mx /kh32768 /t /dGAME=5 th05_zuninit.asm obj\th05\zuninit.obj
tasm32 /m /mx /kh32768 /t /dGAME=5 th05_gjinit.asm obj\th05\gjinit.obj
tasm32 /m /mx /kh32768 /t /dGAME=5 th05_memchk.asm obj\th05\memchk.obj
tasm32 /m /mx /kh32768 /t /dGAME=5 th05_op_master.asm obj\th05\opm.obj
tasm32 /m /mx /kh32768 /t /dGAME=5 th05_op2.asm obj\th05\op2.obj
tasm32 /m /mx /kh32768 /t /dGAME=5 th05\cdg_put.asm obj\th05\cdg_put.obj
tasm32 /m /mx /kh32768 /t /dGAME=5 th05\musicp_a.asm obj\th05\musicp_a.obj
tasm32 /m /mx /kh32768 /t /dGAME=5 th05\bgimager.asm obj\th05\bgimager.obj
tasm32 /m /mx /kh32768 /t /dGAME=5 th05\pi_asm_1.asm obj\th05\pi_asm_1.obj
tasm32 /m /mx /kh32768 /t /dGAME=5 th05\pi_asm_2.asm obj\th05\pi_asm_2.obj
tasm32 /m /mx /kh32768 /t /dGAME=5 th05\input_s.asm obj\th05\input_s.obj
tasm32 /m /mx /kh32768 /t /dGAME=5 th05_op.asm obj\th05\op.obj
tasm32 /m /mx /kh32768 /t /dGAME=5 th05_main.asm obj\th05\main.obj
tasm32 /m /mx /kh32768 /t /dGAME=5 th05\player.asm obj\th05\player.obj
tasm32 /m /mx /kh32768 /t /dGAME=5 th05\hud_bar.asm obj\th05\hud_bar.obj
tasm32 /m /mx /kh32768 /t /dGAME=5 th05\scoreupd.asm obj\th05\scoreupd.obj
tasm32 /m /mx /kh32768 /t /dGAME=5 th05\spark_a.asm obj\th05\spark_a.obj
tasm32 /m /mx /kh32768 /t /dGAME=5 th05\bullet_1.asm obj\th05\bullet_1.obj
tasm32 /m /mx /kh32768 /t /dGAME=5 th05\bullet.asm obj\th05\bullet.obj
tasm32 /m /mx /kh32768 /t /dGAME=5 th05_maine_master.asm obj\th05\mainem.obj
tasm32 /m /mx /kh32768 /t /dGAME=5 th05_maine.asm obj\th05\maine.obj
bin\Pipeline\bmp2arr.exe -q -i Research/blitperf.bmp -o Research/blitperf.csp -sym sBLITPERF -of cpp -sw 16 -sh 16
