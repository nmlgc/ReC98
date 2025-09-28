: Dumb, full batch build script for 32-bit systems that can't run Tup, but can
: natively run DOS-based tools. Automatically generated whenever `Tupfile.lua`
: is modified.
@echo off
mkdir Research\blitperf %STDERR_IGNORE%
mkdir bin\Pipeline %STDERR_IGNORE%
mkdir bin\Research %STDERR_IGNORE%
mkdir bin\th01 %STDERR_IGNORE%
mkdir bin\th02 %STDERR_IGNORE%
mkdir bin\th03 %STDERR_IGNORE%
mkdir bin\th04 %STDERR_IGNORE%
mkdir bin\th05 %STDERR_IGNORE%
mkdir obj %STDERR_IGNORE%
mkdir obj\Pipeline %STDERR_IGNORE%
mkdir obj\Research %STDERR_IGNORE%
mkdir obj\Research\086 %STDERR_IGNORE%
mkdir obj\Research\286 %STDERR_IGNORE%
mkdir obj\Research\386 %STDERR_IGNORE%
mkdir obj\th01 %STDERR_IGNORE%
mkdir obj\th02 %STDERR_IGNORE%
mkdir obj\th03 %STDERR_IGNORE%
mkdir obj\th04 %STDERR_IGNORE%
mkdir obj\th05 %STDERR_IGNORE%
mkdir th01\sprites %STDERR_IGNORE%
mkdir th02\sprites %STDERR_IGNORE%
mkdir th03\sprites %STDERR_IGNORE%
mkdir th04\sprites %STDERR_IGNORE%
mkdir th05\sprites %STDERR_IGNORE%
echo -c  -I.  -O  -b-  -3  -Z  -d  -G  -k-  -p  -x-  -IPipeline/  -mt  -nobj/Pipeline/  Pipeline/grzview.cpp  th01/formats/grz.cpp  platform/x86real/pc98/palette.cpp  Pipeline/bmp2arrl.c  Pipeline/bmp2arr.c  Pipeline/zungen.c  Pipeline/comcstm.c>obj\batch000.@c
tcc @obj/batch000.@c
echo -c -s -t c0t.obj obj\Pipeline\grzview.obj obj\Pipeline\grz.obj obj\Pipeline\palette.obj, bin\Pipeline\grzview.com, obj\Pipeline\grzview.map, bin\masters.lib emu.lib maths.lib ct.lib>obj\Pipeline\grzview.@l
tlink @obj\Pipeline\grzview.@l
echo -c -s -t c0t.obj obj\Pipeline\bmp2arrl.obj obj\Pipeline\bmp2arr.obj, bin\Pipeline\bmp2arr.com, obj\Pipeline\bmp2arr.map, emu.lib maths.lib ct.lib>obj\Pipeline\bmp2arr.@l
tlink @obj\Pipeline\bmp2arr.@l
echo -c -s -t c0t.obj obj\Pipeline\zungen.obj, bin\Pipeline\zungen.com, obj\Pipeline\zungen.map, emu.lib maths.lib ct.lib>obj\Pipeline\zungen.@l
tlink @obj\Pipeline\zungen.@l
echo -c -s -t c0t.obj obj\Pipeline\comcstm.obj, bin\Pipeline\comcstm.com, obj\Pipeline\comcstm.map, emu.lib maths.lib ct.lib>obj\Pipeline\comcstm.@l
tlink @obj\Pipeline\comcstm.@l
tasm32 /m /mx /kh32768 /t Pipeline\zun_stub.asm obj\Pipeline\zun_stub.obj
tlink -x -t obj\Pipeline\zun_stub.obj, obj\Pipeline\zun_stub.bin
tasm32 /m /mx /kh32768 /t Pipeline\cstmstub.asm obj\Pipeline\cstmstub.obj
tlink -x -t obj\Pipeline\cstmstub.obj, obj\Pipeline\cstmstub.bin
tasm32 /m /mx /kh32768 /t /ml libs\piloadc\piloadc.asm obj\piloadc.obj
tasm32 /m /mx /kh32768 /t /ml libs\piloadc\piloadm.asm obj\piloadm.obj
tasm32 /m /mx /kh32768 /t /dTHIEF libs\sprite16\sprite16.asm obj\th03\zunsp.obj
echo -c  -I.  -O  -b-  -3  -Z  -d  -G  -k-  -p  -x-  -ml  -zCPLATFORM_TEXT  -nobj/  platform/x86real/doserror.cpp  platform/x86real/noexcept.cpp  platform/x86real/spawn.cpp  platform/x86real/pc98/blitter.cpp  platform/x86real/pc98/egc.cpp  platform/x86real/pc98/font.cpp  platform/x86real/pc98/grcg.cpp  platform/x86real/pc98/grp_clip.cpp>obj\batch001.@c
tcc @obj/batch001.@c
bin\Pipeline\bmp2arr.com -q -i th01/sprites/leaf_s.bmp -o th01/sprites/leaf_s.csp -sym sSPARK -of cpp -sw 8 -sh 8
bin\Pipeline\bmp2arr.com -q -i th01/sprites/leaf_l.bmp -o th01/sprites/leaf_l.csp -sym sLEAF_LEFT -of cpp -sw 8 -sh 8
bin\Pipeline\bmp2arr.com -q -i th01/sprites/leaf_r.bmp -o th01/sprites/leaf_r.csp -sym sLEAF_RIGHT -of cpp -sw 8 -sh 8
bin\Pipeline\bmp2arr.com -q -i th01/sprites/ileave_m.bmp -o th01/sprites/ileave_m.csp -sym sINTERLEAVE_MASKS -of cpp -sw 8 -sh 8
bin\Pipeline\bmp2arr.com -q -i th01/sprites/laser_s.bmp -o th01/sprites/laser_s.csp -sym sSHOOTOUT_LASER -of cpp -sw 16 -sh 8
bin\Pipeline\bmp2arr.com -q -i th01/sprites/mousecur.bmp -o th01/sprites/mousecur.csp -sym sMOUSE_CURSOR -of cpp -sw 16 -sh 16
bin\Pipeline\bmp2arr.com -q -i th01/sprites/pellet.bmp -o th01/sprites/pellet.csp -sym sPELLET -of cpp -sw 8 -sh 8 -pshf inner
bin\Pipeline\bmp2arr.com -q -i th01/sprites/pellet_c.bmp -o th01/sprites/pellet_c.csp -sym sPELLET_CLOUD -of cpp -sw 16 -sh 16
bin\Pipeline\bmp2arr.com -q -i th01/sprites/pillar.bmp -o th01/sprites/pillar.csp -sym sPILLAR -of cpp -sw 32 -sh 8
bin\Pipeline\bmp2arr.com -q -i th01/sprites/shape8x8.bmp -o th01/sprites/shape8x8.csp -sym sSHAPE8X8 -of cpp -sw 8 -sh 8
bin\Pipeline\bmp2arr.com -q -i th01/sprites/bonusbox.bmp -o th01/sprites/bonusbox.csp -sym sSTAGEBONUS_BOX -of cpp -sw 8 -sh 4
echo -c  -I.  -O  -b-  -3  -Z  -d  -DGAME=1  -mt  -nobj/th01/  th01/zunsoft.cpp>obj\batch002.@c
tcc @obj/batch002.@c
echo -c -s -t c0t.obj obj\th01\zunsoft.obj, bin\th01\zunsoft.com, obj\th01\zunsoft.map, bin\masters.lib emu.lib maths.lib ct.lib>obj\th01\zunsoft.@l
tlink @obj\th01\zunsoft.@l
tasm32 /m /mx /kh32768 /t th01.asm obj\th01\th01.obj
echo -c  -I.  -O  -b-  -3  -Z  -d  -G  -k-  -p  -x-  -ml  -DGAME=1  -nobj/th01/  th01/entry.cpp  th01/egc.cpp  th01/frmdelay.cpp  th01/game.cpp  th01/graph.cpp  th01/grp2xscs.cpp  th01/grp_text.cpp  th01/grp.cpp  th01/initexit.cpp  th01/mdrv2.cpp  th01/pf.cpp  th01/planar.cpp  th01/scoredat.cpp  th01/regist.cpp  th01/resstuff.cpp  th01/tram_x16.cpp  th01/vsync.cpp  th01/ztext.cpp  th01/op_01.cpp  th01/input.cpp  th01/main_01.cpp  th01/ptn.cpp  th01/grz.cpp>obj\batch003.@c
echo th01/main_09.cpp  th01/bullet_l.cpp  th01/grpinv32.cpp  th01/scrollup.cpp  th01/pgtrans.cpp  th01/grph1to0.cpp  th01/main_14.cpp  th01/main_15.cpp  th01/main_17.cpp  th01/main_18.cpp  th01/main_20.cpp  th01/main_21.cpp  th01/main_23.cpp  th01/main_24.cpp  th01/main_25.cpp  th01/main_26.cpp  th01/player.cpp  th01/stages.cpp  th01/main_28.cpp  th01/main_29.cpp  th01/main_30.cpp  th01/main_31.cpp  th01/main_32.cpp  th01/particle.cpp  th01/main_33.cpp  th01/main_34.cpp  th01/main_35.cpp  th01/main_36.cpp  th01/main_37.cpp  th01/main_38.cpp  th01/fuuin_01.cpp>>obj\batch003.@c
echo th01/fuuin_03.cpp>>obj\batch003.@c
tcc @obj/batch003.@c
echo -c -s -E c0l.obj obj\doserror.obj obj\noexcept.obj obj\spawn.obj obj\blitter.obj obj\egc.obj obj\font.obj obj\grcg.obj obj\grp_clip.obj obj\piloadc.obj obj\th01\th01.obj obj\th01\entry.obj obj\th01\egc.obj obj\th01\frmdelay.obj obj\th01\game.obj obj\th01\graph.obj obj\th01\grp2xscs.obj obj\th01\grp_text.obj obj\th01\grp.obj obj\th01\initexit.obj obj\th01\mdrv2.obj obj\th01\pf.obj obj\th01\planar.obj obj\th01\scoredat.obj obj\th01\regist.obj obj\th01\resstuff.obj obj\th01\tram_x16.obj obj\th01\vsync.obj obj\th01\ztext.obj obj\th01\op_01.obj obj\th01\input.obj obj\th01\main_01.obj obj\th01\ptn.obj obj\th01\grz.obj obj\th01\main_09.obj obj\th01\bullet_l.obj obj\th01\grpinv32.obj obj\th01\scrollup.obj obj\th01\pgtrans.obj obj\th01\grph1to0.obj obj\th01\main_14.obj obj\th01\main_15.obj obj\th01\main_17.obj obj\th01\main_18.obj obj\th01\main_20.obj obj\th01\main_21.obj obj\th01\main_23.obj obj\th01\main_24.obj obj\th01\main_25.obj obj\th01\main_26.obj obj\th01\player.obj+>obj\th01\debloat.@l
echo obj\th01\stages.obj obj\th01\main_28.obj obj\th01\main_29.obj obj\th01\main_30.obj obj\th01\main_31.obj obj\th01\main_32.obj obj\th01\particle.obj obj\th01\main_33.obj obj\th01\main_34.obj obj\th01\main_35.obj obj\th01\main_36.obj obj\th01\main_37.obj obj\th01\main_38.obj obj\th01\fuuin_01.obj obj\th01\fuuin_03.obj, bin\th01\debloat.exe, obj\th01\debloat.map, emu.lib mathl.lib cl.lib>>obj\th01\debloat.@l
tlink @obj\th01\debloat.@l
bin\Pipeline\bmp2arr.com -q -i th02/sprites/bombpart.bmp -o th02/sprites/bombpart.asp -sym _sBOMB_PARTICLES -of asm -sw 8 -sh 8
bin\Pipeline\bmp2arr.com -q -i th02/sprites/pellet.bmp -o th02/sprites/pellet.asp -sym _sPELLET -of asm -sw 8 -sh 8 -pshf outer
bin\Pipeline\bmp2arr.com -q -i th02/sprites/sparks.bmp -o th02/sprites/sparks.asp -sym _sSPARKS -of asm -sw 8 -sh 8 -pshf outer
bin\Pipeline\bmp2arr.com -q -i th02/sprites/pointnum.bmp -o th02/sprites/pointnum.asp -sym _sPOINTNUMS -of asm -sw 8 -sh 8
bin\Pipeline\bmp2arr.com -q -i th02/sprites/verdict.bmp -o th02/sprites/verdict.csp -sym sVERDICT_MASKS -of cpp -sw 16 -sh 16
tasm32 /m /mx /kh32768 /t /dGAME=2 th02_zuninit.asm obj\th02\zuninit.obj
echo -c -s -t -3  obj\th02\zuninit.obj, bin\th02\zuninit.com, obj\th02\zuninit.map, >obj\th02\zuninit.@l
tlink @obj\th02\zuninit.@l
echo -c  -I.  -O  -b-  -3  -Z  -d  -DGAME=2  -mt  -nobj/th02/  th02/zun_res1.cpp  th02/zun_res2.cpp>obj\batch004.@c
tcc @obj/batch004.@c
echo -c -s -t c0t.obj obj\th02\zun_res1.obj obj\th02\zun_res2.obj, bin\th02\zun_res.com, obj\th02\zun_res.map, bin\masters.lib emu.lib maths.lib ct.lib>obj\th02\zun_res.@l
tlink @obj\th02\zun_res.@l
echo 4 ONGCHK ZUNINIT ZUN_RES ZUNSOFT libs/kaja/ongchk.com bin/th02/zuninit.com bin/th02/zun_res.com bin/th01/zunsoft.com>obj\th02\zun.@z
bin\Pipeline\zungen.com obj/Pipeline/zun_stub.bin obj\th02\zun.@z bin/th02/zun.com
echo -c  -I.  -O  -b-  -3  -Z  -d  -DGAME=2  -ml  -DBINARY='O'  -nobj/th02/  th02/op_01.cpp  th02/exit_dos.cpp  th02/zunerror.cpp  th02/grppsafx.cpp  th02/vplanset.cpp  th02/pi_load.cpp  th02/grp_rect.cpp  th02/frmdely2.cpp  th02/input_rs.cpp  th02/initop.cpp  th02/exit.cpp  th02/snd_mmdr.c  th02/snd_mode.c  th02/snd_pmdr.c  th02/snd_load.cpp  th02/pi_put.cpp  th02/snd_kaja.cpp  th02/op_02_3.cpp  th02/snd_se_r.cpp  th02/snd_se.cpp  th02/frmdely1.cpp  th02/op_03.cpp  th02/globals.cpp  th02/op_04.cpp>obj\batch005.@c
echo th02/op_05.cpp  th02/op_music.cpp>>obj\batch005.@c
tcc @obj/batch005.@c
tasm32 /m /mx /kh32768 /t /dGAME=2 th02_op.asm obj\th02\op.obj
echo -c -s -E c0l.obj obj\th02\op_01.obj obj\th02\exit_dos.obj obj\th02\zunerror.obj obj\th02\grppsafx.obj obj\th02\op.obj obj\th02\vplanset.obj obj\th02\pi_load.obj obj\th02\grp_rect.obj obj\th02\frmdely2.obj obj\th02\input_rs.obj obj\th02\initop.obj obj\th02\exit.obj obj\th02\snd_mmdr.obj obj\th02\snd_mode.obj obj\th02\snd_pmdr.obj obj\th02\snd_load.obj obj\th02\pi_put.obj obj\th02\snd_kaja.obj obj\th02\op_02_3.obj obj\th02\snd_se_r.obj obj\th02\snd_se.obj obj\th02\frmdely1.obj obj\th02\op_03.obj obj\th02\globals.obj obj\th02\op_04.obj obj\th02\op_05.obj obj\th02\op_music.obj, bin\th02\op.exe, obj\th02\op.map, emu.lib mathl.lib cl.lib>obj\th02\op.@l
tlink @obj\th02\op.@l
tasm32 /m /mx /kh32768 /t /dGAME=2 th02_main.asm obj\th02\main.obj
echo -c  -I.  -O  -b-  -3  -Z  -d  -DGAME=2  -ml  -DBINARY='M'  -nobj/th02/  th02/spark.cpp  th02/tile.cpp  th02/pointnum.cpp  th02/item.cpp  th02/hud.cpp  th02/player_b.cpp  th02/player.cpp  th02/keydelay.cpp  th02/main02_1.cpp  th02/vector.cpp  th02/snd_dlyv.c  th02/mpn_l_i.cpp  th02/initmain.cpp  th02/snd_dlym.cpp  th02/main_03.cpp  th02/hud_ovrl.cpp  th02/bullet.cpp  th02/dialog.cpp  th02/boss_5.cpp  th02/regist_m.cpp>obj\batch006.@c
tcc @obj/batch006.@c
tasm32 /m /mx /kh32768 /t /dGAME=2 th02\spark_i.asm obj\th02\spark_i.obj
echo -c -s -E c0l.obj obj\th02\main.obj obj\th02\spark.obj obj\th02\spark_i.obj obj\th02\tile.obj obj\th02\pointnum.obj obj\th02\item.obj obj\th02\hud.obj obj\th02\player_b.obj obj\th02\player.obj obj\th02\zunerror.obj obj\th02\keydelay.obj obj\th02\main02_1.obj obj\th02\vplanset.obj obj\th02\pi_load.obj obj\th02\vector.obj obj\th02\frmdely1.obj obj\th02\input_rs.obj obj\th02\exit.obj obj\th02\snd_mmdr.obj obj\th02\snd_mode.obj obj\th02\snd_pmdr.obj obj\th02\snd_dlyv.obj obj\th02\snd_load.obj obj\th02\mpn_l_i.obj obj\th02\initmain.obj obj\th02\pi_put.obj obj\th02\snd_kaja.obj obj\th02\snd_dlym.obj obj\th02\snd_se_r.obj obj\th02\snd_se.obj obj\th02\main_03.obj obj\th02\hud_ovrl.obj obj\th02\bullet.obj obj\th02\dialog.obj obj\th02\boss_5.obj obj\th02\regist_m.obj, bin\th02\main.exe, obj\th02\main.map, emu.lib mathl.lib cl.lib>obj\th02\main.@l
tlink @obj\th02\main.@l
echo -c  -I.  -O  -b-  -3  -Z  -d  -DGAME=2  -ml  -DBINARY='E'  -nobj/th02/  th02/end.cpp  th02/maine022.cpp  th02/maine_03.cpp  th02/maine_04.cpp  th02/staff.cpp>obj\batch007.@c
tcc @obj/batch007.@c
tasm32 /m /mx /kh32768 /t /dGAME=2 th02_maine.asm obj\th02\maine.obj
echo -c -s -E c0l.obj obj\th02\end.obj obj\th02\maine.obj obj\th02\grppsafx.obj obj\th02\keydelay.obj obj\th02\vplanset.obj obj\th02\pi_load.obj obj\th02\frmdely1.obj obj\th02\maine022.obj obj\th02\input_rs.obj obj\th02\exit.obj obj\th02\snd_mmdr.obj obj\th02\snd_mode.obj obj\th02\snd_pmdr.obj obj\th02\snd_load.obj obj\th02\initmain.obj obj\th02\pi_put.obj obj\th02\snd_kaja.obj obj\th02\snd_dlym.obj obj\th02\globals.obj obj\th02\maine_03.obj obj\th02\maine_04.obj obj\th02\staff.obj, bin\th02\maine.exe, obj\th02\maine.map, emu.lib mathl.lib cl.lib>obj\th02\maine.@l
tlink @obj\th02\maine.@l
bin\Pipeline\bmp2arr.com -q -i th03/sprites/score.bmp -o th03/sprites/score.asp -sym _sSCORE_FONT -of asm -sw 8 -sh 8 -u
bin\Pipeline\bmp2arr.com -q -i th03/sprites/flake.bmp -o th03/sprites/flake.asp -sym _sFLAKE -of asm -sw 16 -sh 8
echo -c -s -t -3  obj\th03\zunsp.obj, bin\th03\zunsp.com, obj\th03\zunsp.map, >obj\th03\zunsp.@l
tlink @obj\th03\zunsp.@l
echo -c  -I.  -O  -b-  -3  -Z  -d  -DGAME=3  -mt  -nobj/th03/  th03/res_yume.cpp>obj\batch008.@c
tcc @obj/batch008.@c
echo -c -s -t c0t.obj obj\th03\res_yume.obj, bin\th03\res_yume.com, obj\th03\res_yume.map, bin\masters.lib emu.lib maths.lib ct.lib>obj\th03\res_yume.@l
tlink @obj\th03\res_yume.@l
echo 5 -1 -2 -3 -4 -5 libs/kaja/ongchk.com bin/th02/zuninit.com bin/th01/zunsoft.com bin/th03/zunsp.com bin/th03/res_yume.com>obj\th03\zun.@z
bin\Pipeline\zungen.com obj/Pipeline/zun_stub.bin obj\th03\zun.@z bin/th03/zun.com
echo -c  -I.  -O  -b-  -3  -Z  -d  -DGAME=3  -ml  -DBINARY='O'  -nobj/th03/  th03/op_01.cpp  th03/op_music.cpp  th03/op_main.cpp  th03/op_02.cpp  th03/scoredat.cpp  th03/op_sel.cpp  th03/exit.cpp  th03/polar.cpp  th03/input_s.cpp  th03/pi_put.cpp  th03/snd_kaja.cpp  th03/initop.cpp  th03/cdg_load.cpp  th03/grppsafx.cpp  th03/pi_load.cpp  th03/inp_m_w.cpp>obj\batch009.@c
tcc @obj/batch009.@c
tasm32 /m /mx /kh32768 /t /dGAME=3 th03_op.asm obj\th03\op.obj
tasm32 /m /mx /kh32768 /t /dGAME=3 th03\cdg_put.asm obj\th03\cdg_put.obj
tasm32 /m /mx /kh32768 /t /dGAME=3 th03\cdg_p_na.asm obj\th03\cdg_p_na.obj
tasm32 /m /mx /kh32768 /t /dGAME=3 th03\hfliplut.asm obj\th03\hfliplut.obj
echo -c -s -E c0l.obj obj\th03\op_01.obj obj\th03\op.obj obj\th03\op_music.obj obj\th03\op_main.obj obj\th03\op_02.obj obj\th03\scoredat.obj obj\th03\op_sel.obj obj\th02\exit_dos.obj obj\th02\vplanset.obj obj\th02\snd_mode.obj obj\th02\snd_pmdr.obj obj\th02\snd_load.obj obj\th03\exit.obj obj\th03\polar.obj obj\th03\cdg_put.obj obj\th02\frmdely1.obj obj\th03\input_s.obj obj\th03\pi_put.obj obj\th03\snd_kaja.obj obj\th03\initop.obj obj\th03\cdg_load.obj obj\th03\grppsafx.obj obj\th03\pi_load.obj obj\th03\inp_m_w.obj obj\th03\cdg_p_na.obj obj\th03\hfliplut.obj obj\th02\frmdely2.obj, bin\th03\op.exe, obj\th03\op.map, emu.lib mathl.lib cl.lib>obj\th03\op.@l
tlink @obj\th03\op.@l
tasm32 /m /mx /kh32768 /t /dGAME=3 th03_main.asm obj\th03\main.obj
echo -c  -I.  -O  -b-  -3  -Z  -d  -DGAME=3  -ml  -DBINARY='M'  -nobj/th03/  th03/playfld.cpp  th03/cfg_lres.cpp  th03/hitcirc.cpp  th03/hud_stat.cpp  th03/player_m.cpp  th03/main_010.cpp  th03/main_011.cpp  th03/vector.cpp  th03/snd_se.cpp  th03/initmain.cpp  th03/mrs.cpp  th03/sprite16.cpp>obj\batch010.@c
tcc @obj/batch010.@c
tasm32 /m /mx /kh32768 /t /dGAME=3 th03\collmap.asm obj\th03\collmap.obj
echo -c -s -E c0l.obj obj\th03\main.obj obj\th03\playfld.obj obj\th03\cfg_lres.obj obj\th03\hitcirc.obj obj\th03\hud_stat.obj obj\th03\player_m.obj obj\th03\main_010.obj obj\th03\main_011.obj obj\th02\vplanset.obj obj\th02\snd_mode.obj obj\th02\snd_pmdr.obj obj\th03\vector.obj obj\th03\exit.obj obj\th03\polar.obj obj\th02\frmdely1.obj obj\th03\input_s.obj obj\th02\snd_se_r.obj obj\th03\snd_se.obj obj\th03\snd_kaja.obj obj\th03\initmain.obj obj\th03\pi_load.obj obj\th03\inp_m_w.obj obj\th03\collmap.obj obj\th03\hfliplut.obj obj\th03\mrs.obj obj\th03\sprite16.obj, bin\th03\main.exe, obj\th03\main.map, emu.lib mathl.lib cl.lib>obj\th03\main.@l
tlink @obj\th03\main.@l
echo -c  -I.  -O  -b-  -3  -Z  -d  -DGAME=3  -ml  -DBINARY='L'  -nobj/th03/  th03/mainl_sc.cpp  th03/cutscene.cpp  th03/regist.cpp  th03/staff.cpp  th03/pi_put_i.cpp  th03/exitmain.cpp  th03/snd_dlym.cpp  th03/inp_wait.cpp  th03/pi_put_q.cpp>obj\batch011.@c
tcc @obj/batch011.@c
tasm32 /m /mx /kh32768 /t /dGAME=3 th03_mainl.asm obj\th03\mainl.obj
echo -c -s -E c0l.obj obj\th03\cfg_lres.obj obj\th03\mainl_sc.obj obj\th03\mainl.obj obj\th03\cutscene.obj obj\th03\scoredat.obj obj\th03\regist.obj obj\th03\staff.obj obj\th02\vplanset.obj obj\th02\snd_mode.obj obj\th02\snd_pmdr.obj obj\th02\snd_dlyv.obj obj\th02\snd_load.obj obj\th03\vector.obj obj\th03\exit.obj obj\th03\cdg_put.obj obj\th02\frmdely1.obj obj\th03\input_s.obj obj\th03\pi_put.obj obj\th03\pi_put_i.obj obj\th02\snd_se_r.obj obj\th03\snd_se.obj obj\th03\snd_kaja.obj obj\th03\initmain.obj obj\th03\cdg_load.obj obj\th03\exitmain.obj obj\th03\grppsafx.obj obj\th03\snd_dlym.obj obj\th03\inp_wait.obj obj\th03\pi_load.obj obj\th03\pi_put_q.obj obj\th03\inp_m_w.obj obj\th03\cdg_p_na.obj obj\th03\hfliplut.obj, bin\th03\mainl.exe, obj\th03\mainl.map, emu.lib mathl.lib cl.lib>obj\th03\mainl.@l
tlink @obj\th03\mainl.@l
bin\Pipeline\bmp2arr.com -q -i th04/sprites/pelletbt.bmp -o th04/sprites/pelletbt.asp -sym _sPELLET_BOTTOM -of asm -sw 8 -sh 4 -pshf outer
bin\Pipeline\bmp2arr.com -q -i th04/sprites/pointnum.bmp -o th04/sprites/pointnum.asp -sym _sPOINTNUMS -of asm -sw 8 -sh 8 -pshf inner
tasm32 /m /mx /kh32768 /t /dGAME=4 th04_zuninit.asm obj\th04\zuninit.obj
echo -c -s -t -3  obj\th04\zuninit.obj, bin\th04\zuninit.com, obj\th04\zuninit.map, >obj\th04\zuninit.@l
tlink @obj\th04\zuninit.@l
echo -c  -I.  -O  -b-  -3  -Z  -d  -DGAME=4  -mt  -nobj/th04/  th04/res_huma.cpp>obj\batch012.@c
tcc @obj/batch012.@c
echo -c -s -t c0t.obj obj\th04\res_huma.obj, bin\th04\res_huma.com, obj\th04\res_huma.map, bin\masters.lib emu.lib maths.lib ct.lib>obj\th04\res_huma.@l
tlink @obj\th04\res_huma.@l
tasm32 /m /mx /kh32768 /t /dGAME=4 th04_memchk.asm obj\th04\memchk.obj
echo -c -s -t c0t.obj obj\th04\memchk.obj, bin\th04\memchk.com, obj\th04\memchk.map, emu.lib maths.lib ct.lib>obj\th04\memchk.@l
tlink @obj\th04\memchk.@l
echo 4 -O -I -S -M libs/kaja/ongchk.com bin/th04/zuninit.com bin/th04/res_huma.com bin/th04/memchk.com>obj\th04\zuncom.@z
bin\Pipeline\zungen.com obj/Pipeline/zun_stub.bin obj\th04\zuncom.@z obj/th04/zuncom.bin
bin\Pipeline\comcstm.com th04/zun.txt obj/th04/zuncom.bin obj/Pipeline/cstmstub.bin 621381155 bin/th04/zun.com
echo -c  -I.  -O  -b-  -3  -Z  -d  -DGAME=4  -ml  -DBINARY='O'  -nobj/th04/  th04/op_main.cpp  th04/input_w.cpp  th04/vector.cpp  th04/snd_pmdr.c  th04/snd_mmdr.c  th04/snd_kaja.cpp  th04/snd_mode.cpp  th04/snd_dlym.cpp  th04/snd_load.cpp  th04/exit.cpp  th04/initop.cpp  th04/cdg_p_na.cpp  th04/snd_se.cpp  th04/egcrect.cpp  th04/bgimage.cpp  th04/op_setup.cpp  th04/zunsoft.cpp  th04/op_music.cpp  th04/score_db.cpp  th04/score_e.cpp  th04/hi_view.cpp  th04/op_title.cpp  th04/m_char.cpp>obj\batch013.@c
tcc @obj/batch013.@c
tasm32 /m /mx /kh32768 /t /dGAME=4 th04_op.asm obj\th04\op.obj
tasm32 /m /mx /kh32768 /t /dGAME=4 th04\cdg_p_nc.asm obj\th04\cdg_p_nc.obj
tasm32 /m /mx /kh32768 /t /dGAME=4 th04\grppsafx.asm obj\th04\grppsafx.obj
tasm32 /m /mx /kh32768 /t /dGAME=4 th04_op2.asm obj\th04\op2.obj
tasm32 /m /mx /kh32768 /t /dGAME=4 th04\cdg_put.asm obj\th04\cdg_put.obj
tasm32 /m /mx /kh32768 /t /dGAME=4 th04\input_s.asm obj\th04\input_s.obj
tasm32 /m /mx /kh32768 /t /dGAME=4 th04\bgimager.asm obj\th04\bgimager.obj
tasm32 /m /mx /kh32768 /t /dGAME=4 th04\cdg_load.asm obj\th04\cdg_load.obj
echo -c -s -E c0l.obj obj\th04\op_main.obj obj\th04\op.obj obj\th02\vplanset.obj obj\th02\frmdely1.obj obj\th03\pi_put.obj obj\th03\pi_load.obj obj\th03\hfliplut.obj obj\th04\input_w.obj obj\th04\vector.obj obj\th04\snd_pmdr.obj obj\th04\snd_mmdr.obj obj\th04\snd_kaja.obj obj\th04\cdg_p_nc.obj obj\th04\snd_mode.obj obj\th04\snd_dlym.obj obj\th02\exit_dos.obj obj\th04\snd_load.obj obj\th04\grppsafx.obj obj\th04\op2.obj obj\th04\cdg_put.obj obj\th04\exit.obj obj\th04\initop.obj obj\th04\cdg_p_na.obj obj\th04\input_s.obj obj\th02\snd_se_r.obj obj\th04\snd_se.obj obj\th04\egcrect.obj obj\th04\bgimage.obj obj\th04\bgimager.obj obj\th04\cdg_load.obj obj\th02\frmdely2.obj obj\th04\op_setup.obj obj\th04\zunsoft.obj obj\th04\op_music.obj obj\th04\score_db.obj obj\th04\score_e.obj obj\th04\hi_view.obj obj\th04\op_title.obj obj\th04\m_char.obj, bin\th04\op.exe, obj\th04\op.map, emu.lib mathl.lib cl.lib>obj\th04\op.@l
tlink @obj\th04\op.@l
tasm32 /m /mx /kh32768 /t /dGAME=4 th04_main.asm obj\th04\main.obj
echo -c  -I.  -O  -b-  -3  -Z  -d  -DGAME=4  -ml  -DBINARY='M'  -nobj/th04/  th04/slowdown.cpp  th04/demo.cpp  th04/ems.cpp  th04/tile_set.cpp  th04/std.cpp  th04/circle.cpp  th04/tile.cpp  th04/playfld.cpp  th04/midboss4.cpp  th04/f_dialog.cpp  th04/dialog.cpp  th04/boss_exp.cpp  th04/stages.cpp  th04/player_m.cpp  th04/player_p.cpp  th04/hud_ovrl.cpp  th04/cfg_lres.cpp  th04/checkerb.cpp  th04/mb_inv.cpp  th04/boss_bd.cpp  th04/score_rm.cpp  th04/mpn_free.cpp  th04/mpn_l_i.cpp  th04/initmain.cpp>obj\batch014.@c
echo th04/gather.cpp  th04/scrolly3.cpp  th04/midboss.cpp  th04/hud_hp.cpp  th04/mb_dft.cpp  th04/grcg_3.cpp  th04/it_spl_u.cpp  th04/boss_4m.cpp  th04/bullet_u.cpp  th04/bullet_a.cpp  th04/boss.cpp  th04/boss_4r.cpp  th04/boss_x2.cpp>>obj\batch014.@c
tcc @obj/batch014.@c
tasm32 /m /mx /kh32768 /t /dGAME=4 th04\scoreupd.asm obj\th04\scoreupd.obj
tasm32 /m /mx /kh32768 /t /dGAME=4 th04\cdg_p_pr.asm obj\th04\cdg_p_pr.obj
tasm32 /m /mx /kh32768 /t /dGAME=4 th04\motion_3.asm obj\th04\motion_3.obj
tasm32 /m /mx /kh32768 /t /dGAME=4 th04\vector2n.asm obj\th04\vector2n.obj
tasm32 /m /mx /kh32768 /t /dGAME=4 th04\spark_a.asm obj\th04\spark_a.obj
echo -c -s -E c0l.obj obj\th04\main.obj obj\th04\slowdown.obj obj\th04\demo.obj obj\th04\ems.obj obj\th04\tile_set.obj obj\th04\std.obj obj\th04\circle.obj obj\th04\tile.obj obj\th04\playfld.obj obj\th04\midboss4.obj obj\th04\f_dialog.obj obj\th04\dialog.obj obj\th04\boss_exp.obj obj\th04\stages.obj obj\th04\player_m.obj obj\th04\player_p.obj obj\th04\scoreupd.obj obj\th04\hud_ovrl.obj obj\th04\cfg_lres.obj obj\th04\checkerb.obj obj\th04\mb_inv.obj obj\th04\boss_bd.obj obj\th04\score_rm.obj obj\th02\vplanset.obj obj\th03\vector.obj obj\th02\frmdely1.obj obj\th03\hfliplut.obj obj\th04\mpn_free.obj obj\th04\input_w.obj obj\th04\mpn_l_i.obj obj\th04\vector.obj obj\th04\snd_pmdr.obj obj\th04\snd_mmdr.obj obj\th04\snd_kaja.obj obj\th04\snd_mode.obj obj\th04\snd_load.obj obj\th04\cdg_put.obj obj\th04\exit.obj obj\th04\initmain.obj obj\th04\cdg_p_na.obj obj\th04\cdg_p_pr.obj obj\th04\input_s.obj obj\th02\snd_se_r.obj obj\th04\snd_se.obj obj\th04\cdg_load.obj obj\th04\gather.obj+>obj\th04\main.@l
echo obj\th04\scrolly3.obj obj\th04\motion_3.obj obj\th04\midboss.obj obj\th04\hud_hp.obj obj\th04\mb_dft.obj obj\th04\vector2n.obj obj\th04\spark_a.obj obj\th04\grcg_3.obj obj\th04\it_spl_u.obj obj\th04\boss_4m.obj obj\th04\bullet_u.obj obj\th04\bullet_a.obj obj\th04\boss.obj obj\th04\boss_4r.obj obj\th04\boss_x2.obj, bin\th04\main.exe, obj\th04\main.map, emu.lib mathl.lib cl.lib>>obj\th04\main.@l
tlink @obj\th04\main.@l
echo -c  -I.  -O  -b-  -3  -Z  -d  -DGAME=4  -ml  -DBINARY='E'  -nobj/th04/  th04/maine_e.cpp  th04/score_d.cpp  th04/hi_end.cpp  th04/cutscene.cpp  th04/staff.cpp>obj\batch015.@c
tcc @obj/batch015.@c
tasm32 /m /mx /kh32768 /t /dGAME=4 th04_maine_master.asm obj\th04\mainem.obj
tasm32 /m /mx /kh32768 /t /dGAME=4 th04\cdg_p_pl.asm obj\th04\cdg_p_pl.obj
tasm32 /m /mx /kh32768 /t /dGAME=4 th04_maine.asm obj\th04\maine.obj
echo -c -s -E c0l.obj obj\th04\maine_e.obj obj\th04\mainem.obj obj\th04\score_d.obj obj\th04\score_e.obj obj\th04\hi_end.obj obj\th02\vplanset.obj obj\th02\frmdely1.obj obj\th03\pi_put.obj obj\th03\pi_load.obj obj\th03\pi_put_q.obj obj\th03\hfliplut.obj obj\th04\input_w.obj obj\th04\vector.obj obj\th04\snd_pmdr.obj obj\th04\snd_mmdr.obj obj\th04\snd_kaja.obj obj\th04\snd_mode.obj obj\th04\snd_dlym.obj obj\th04\cdg_p_pl.obj obj\th04\snd_load.obj obj\th04\grppsafx.obj obj\th04\maine.obj obj\th04\cdg_put.obj obj\th04\exit.obj obj\th04\initmain.obj obj\th04\input_s.obj obj\th02\snd_se_r.obj obj\th04\snd_se.obj obj\th04\bgimage.obj obj\th04\bgimager.obj obj\th04\cdg_load.obj obj\th04\cutscene.obj obj\th04\staff.obj, bin\th04\maine.exe, obj\th04\maine.map, emu.lib mathl.lib cl.lib>obj\th04\maine.@l
tlink @obj\th04\maine.@l
bin\Pipeline\bmp2arr.com -q -i th05/sprites/gaiji.bmp -o th05/sprites/gaiji.asp -sym _sGAIJI -of asm -sw 16 -sh 16
bin\Pipeline\bmp2arr.com -q -i th05/sprites/piano_l.bmp -o th05/sprites/piano_l.asp -sym _sPIANO_LABEL_FONT -of asm -sw 8 -sh 8
tasm32 /m /mx /kh32768 /t /dGAME=5 th05_zuninit.asm obj\th05\zuninit.obj
echo -c -s -t -3  obj\th05\zuninit.obj, bin\th05\zuninit.com, obj\th05\zuninit.map, >obj\th05\zuninit.@l
tlink @obj\th05\zuninit.@l
echo -c  -I.  -O  -b-  -3  -Z  -d  -DGAME=5  -mt  -nobj/th05/  th05/res_kso.cpp>obj\batch016.@c
tcc @obj/batch016.@c
echo -c -s -t c0t.obj obj\th05\res_kso.obj, bin\th05\res_kso.com, obj\th05\res_kso.map, bin\masters.lib emu.lib maths.lib ct.lib>obj\th05\res_kso.@l
tlink @obj\th05\res_kso.@l
tasm32 /m /mx /kh32768 /t /dGAME=5 th05_gjinit.asm obj\th05\gjinit.obj
echo -c -s -t -3  obj\th05\gjinit.obj, bin\th05\gjinit.com, obj\th05\gjinit.map, >obj\th05\gjinit.@l
tlink @obj\th05\gjinit.@l
tasm32 /m /mx /kh32768 /t /dGAME=5 th05_memchk.asm obj\th05\memchk.obj
echo -c -s -t -3  obj\th05\memchk.obj, bin\th05\memchk.com, obj\th05\memchk.map, >obj\th05\memchk.@l
tlink @obj\th05\memchk.@l
echo 5 -O -I -S -G -M libs/kaja/ongchk.com bin/th05/zuninit.com bin/th05/res_kso.com bin/th05/gjinit.com bin/th05/memchk.com>obj\th05\zuncom.@z
bin\Pipeline\zungen.com obj/Pipeline/zun_stub.bin obj\th05\zuncom.@z obj/th05/zuncom.bin
bin\Pipeline\comcstm.com th05/zun.txt obj/th05/zuncom.bin obj/Pipeline/cstmstub.bin 628731748 bin/th05/zun.com
echo -c  -I.  -O  -b-  -3  -Z  -d  -DGAME=5  -ml  -DBINARY='O'  -nobj/th05/  th05/op_main.cpp  th05/vector.cpp  th05/musicp_c.cpp  th05/snd_load.cpp  th05/snd_kaja.cpp  th05/pi_cpp_1.cpp  th05/pi_cpp_2.cpp  th05/initop.cpp  th05/inp_h_w.cpp  th05/snd_dlym.cpp  th05/cdg_p_nc.cpp  th05/frmdelay.cpp  th05/egcrect.cpp  th05/op_setup.cpp  th05/cfg.cpp  th05/op_title.cpp  th05/op_music.cpp  th05/score_db.cpp  th05/score_e.cpp  th05/hi_view.cpp  th05/m_char.cpp>obj\batch017.@c
tcc @obj/batch017.@c
tasm32 /m /mx /kh32768 /t /dGAME=5 th05_op.asm obj\th05\op.obj
tasm32 /m /mx /kh32768 /t /dGAME=5 th05_op2.asm obj\th05\op2.obj
tasm32 /m /mx /kh32768 /t /dGAME=5 th05\cdg_put.asm obj\th05\cdg_put.obj
tasm32 /m /mx /kh32768 /t /dGAME=5 th05\musicp_a.asm obj\th05\musicp_a.obj
tasm32 /m /mx /kh32768 /t /dGAME=5 th05\bgimager.asm obj\th05\bgimager.obj
tasm32 /m /mx /kh32768 /t /dGAME=5 th05\pi_asm_1.asm obj\th05\pi_asm_1.obj
tasm32 /m /mx /kh32768 /t /dGAME=5 th05\pi_asm_2.asm obj\th05\pi_asm_2.obj
tasm32 /m /mx /kh32768 /t /dGAME=5 th05\input_s.asm obj\th05\input_s.obj
echo -c -s -E c0l.obj obj\th05\op_main.obj obj\th05\op.obj obj\th03\hfliplut.obj obj\th04\snd_pmdr.obj obj\th04\snd_mmdr.obj obj\th04\snd_mode.obj obj\th02\exit_dos.obj obj\th04\grppsafx.obj obj\th05\op2.obj obj\th04\cdg_p_na.obj obj\th02\snd_se_r.obj obj\th04\snd_se.obj obj\th04\bgimage.obj obj\th05\cdg_put.obj obj\th04\exit.obj obj\th05\vector.obj obj\th05\musicp_c.obj obj\th05\musicp_a.obj obj\th05\bgimager.obj obj\th05\snd_load.obj obj\th05\snd_kaja.obj obj\th05\pi_cpp_1.obj obj\th05\pi_asm_1.obj obj\th05\pi_cpp_2.obj obj\th05\pi_asm_2.obj obj\th05\initop.obj obj\th05\input_s.obj obj\th05\inp_h_w.obj obj\th05\snd_dlym.obj obj\th05\cdg_p_nc.obj obj\th05\frmdelay.obj obj\th04\cdg_load.obj obj\th05\egcrect.obj obj\th05\op_setup.obj obj\th04\zunsoft.obj obj\th05\cfg.obj obj\th05\op_title.obj obj\th05\op_music.obj obj\th05\score_db.obj obj\th05\score_e.obj obj\th05\hi_view.obj obj\th05\m_char.obj, bin\th05\op.exe, obj\th05\op.map, emu.lib mathl.lib cl.lib>obj\th05\op.@l
tlink @obj\th05\op.@l
tasm32 /m /mx /kh32768 /t /dGAME=5 th05_main.asm obj\th05\main.obj
echo -c  -I.  -O  -b-  -3  -Z  -d  -DGAME=5  -ml  -DBINARY='M'  -nobj/th05/  th05/demo.cpp  th05/ems.cpp  th05/cfg_lres.cpp  th05/std.cpp  th05/main010.cpp  th05/circle.cpp  th05/f_dialog.cpp  th05/dialog.cpp  th05/boss_exp.cpp  th05/playfld.cpp  th05/boss_bg.cpp  th05/score_rm.cpp  th05/laser_rh.cpp  th05/p_common.cpp  th05/p_reimu.cpp  th05/p_marisa.cpp  th05/p_mima.cpp  th05/p_yuuka.cpp  th05/midboss5.cpp  th05/hud_ovrl.cpp  th05/bullet_p.cpp  th05/player_a.cpp  th05/bullet_c.cpp  th05/bullet_t.cpp>obj\batch018.@c
echo th05/initmain.cpp  th05/gather.cpp  th05/main032.cpp  th05/midboss.cpp  th05/mb_dft.cpp  th05/laser.cpp  th05/cheeto_u.cpp  th05/bullet_u.cpp  th05/midboss1.cpp  th05/boss_1.cpp  th05/boss_4.cpp  th05/boss_6.cpp  th05/boss_x.cpp  th05/boss.cpp  th05/main014.cpp>>obj\batch018.@c
tcc @obj/batch018.@c
tasm32 /m /mx /kh32768 /t /dGAME=5 th05\player.asm obj\th05\player.obj
tasm32 /m /mx /kh32768 /t /dGAME=5 th05\hud_bar.asm obj\th05\hud_bar.obj
tasm32 /m /mx /kh32768 /t /dGAME=5 th05\scoreupd.asm obj\th05\scoreupd.obj
tasm32 /m /mx /kh32768 /t /dGAME=5 th05\spark_a.asm obj\th05\spark_a.obj
tasm32 /m /mx /kh32768 /t /dGAME=5 th05\bullet_1.asm obj\th05\bullet_1.obj
tasm32 /m /mx /kh32768 /t /dGAME=5 th05\bullet.asm obj\th05\bullet.obj
tasm32 /m /mx /kh32768 /t /dGAME=5 th05\hud_num.asm obj\th05\hud_num.obj
echo -c -s -E c0l.obj obj\th05\main.obj obj\th04\slowdown.obj obj\th05\demo.obj obj\th05\ems.obj obj\th05\cfg_lres.obj obj\th05\std.obj obj\th04\tile.obj obj\th05\main010.obj obj\th05\circle.obj obj\th05\f_dialog.obj obj\th05\dialog.obj obj\th05\boss_exp.obj obj\th05\playfld.obj obj\th04\mb_inv.obj obj\th04\boss_bd.obj obj\th05\boss_bg.obj obj\th05\score_rm.obj obj\th05\laser_rh.obj obj\th05\p_common.obj obj\th05\p_reimu.obj obj\th05\p_marisa.obj obj\th05\p_mima.obj obj\th05\p_yuuka.obj obj\th05\player.obj obj\th05\hud_bar.obj obj\th05\scoreupd.obj obj\th05\midboss5.obj obj\th05\hud_ovrl.obj obj\th04\player_p.obj obj\th04\vector2n.obj obj\th05\spark_a.obj obj\th05\bullet_p.obj obj\th04\grcg_3.obj obj\th05\player_a.obj obj\th05\bullet_1.obj obj\th05\bullet_c.obj obj\th05\bullet.obj obj\th05\bullet_t.obj obj\th03\vector.obj obj\th03\hfliplut.obj obj\th04\snd_pmdr.obj obj\th04\snd_mmdr.obj obj\th04\snd_mode.obj obj\th04\cdg_p_na.obj obj\th02\snd_se_r.obj obj\th04\snd_se.obj+>obj\th05\main.@l
echo obj\th05\cdg_put.obj obj\th04\exit.obj obj\th05\vector.obj obj\th05\snd_load.obj obj\th05\snd_kaja.obj obj\th05\initmain.obj obj\th05\input_s.obj obj\th05\inp_h_w.obj obj\th05\frmdelay.obj obj\th04\cdg_load.obj obj\th04\scrolly3.obj obj\th04\motion_3.obj obj\th05\gather.obj obj\th05\main032.obj obj\th05\midboss.obj obj\th04\hud_hp.obj obj\th05\mb_dft.obj obj\th05\laser.obj obj\th05\cheeto_u.obj obj\th04\it_spl_u.obj obj\th05\bullet_u.obj obj\th05\midboss1.obj obj\th05\boss_1.obj obj\th05\boss_4.obj obj\th05\boss_6.obj obj\th05\boss_x.obj obj\th05\hud_num.obj obj\th05\boss.obj obj\th05\main014.obj, bin\th05\main.exe, obj\th05\main.map, emu.lib mathl.lib cl.lib>>obj\th05\main.@l
tlink @obj\th05\main.@l
echo -c  -I.  -O  -b-  -3  -Z  -d  -DGAME=5  -ml  -DBINARY='E'  -nobj/th05/  th05/maine_e.cpp  th05/score_d.cpp  th05/hi_end.cpp  th05/cutscene.cpp  th05/allcast.cpp  th05/regist.cpp  th05/staff.cpp>obj\batch019.@c
tcc @obj/batch019.@c
tasm32 /m /mx /kh32768 /t /dGAME=5 th05_maine_master.asm obj\th05\mainem.obj
tasm32 /m /mx /kh32768 /t /dGAME=5 th05_maine.asm obj\th05\maine.obj
echo -c -s -E c0l.obj obj\th05\maine_e.obj obj\th05\mainem.obj obj\th05\score_d.obj obj\th05\score_e.obj obj\th05\hi_end.obj obj\th03\hfliplut.obj obj\th04\snd_pmdr.obj obj\th04\snd_mmdr.obj obj\th04\snd_mode.obj obj\th04\grppsafx.obj obj\th04\cdg_p_na.obj obj\th02\snd_se_r.obj obj\th04\snd_se.obj obj\th04\bgimage.obj obj\th04\exit.obj obj\th05\vector.obj obj\th05\bgimager.obj obj\th05\snd_load.obj obj\th05\snd_kaja.obj obj\th05\pi_cpp_1.obj obj\th05\pi_asm_1.obj obj\th05\pi_cpp_2.obj obj\th05\pi_asm_2.obj obj\th05\initmain.obj obj\th05\input_s.obj obj\th05\inp_h_w.obj obj\th05\snd_dlym.obj obj\th05\frmdelay.obj obj\th04\cdg_load.obj obj\th05\egcrect.obj obj\th05\cutscene.obj obj\th05\allcast.obj obj\th05\regist.obj obj\th05\maine.obj obj\th05\staff.obj, bin\th05\maine.exe, obj\th05\maine.map, emu.lib mathl.lib cl.lib>obj\th05\maine.@l
tlink @obj\th05\maine.@l
echo -c  -I.  -O  -b-  -3  -Z  -d  -G  -k-  -p  -x-  -ms  -nobj/Research/  Research/holdkey.c  platform/x86real/noexcept.cpp  platform/x86real/pc98/blitter.cpp  platform/x86real/pc98/grp_clip.cpp>obj\batch020.@c
tcc @obj/batch020.@c
echo -c -s c0s.obj obj\Research\holdkey.obj, bin\Research\holdkey.exe, obj\Research\holdkey.map, bin\masters.lib emu.lib maths.lib cs.lib>obj\Research\holdkey.@l
tlink @obj\Research\holdkey.@l
echo -c  -I.  -O  -b-  -3  -Z  -d  -G  -k-  -p  -x-  -ms  -DCPU=386  -nobj/Research/  Research/pi_bench.cpp  platform/x86real/pc98/graph.cpp>obj\batch021.@c
tcc @obj/batch021.@c
echo -c -s c0s.obj obj\Research\pi_bench.obj obj\Research\noexcept.obj obj\Research\blitter.obj obj\Research\grp_clip.obj obj\Research\graph.obj obj\piloadm.obj, bin\Research\pi_bench.exe, obj\Research\pi_bench.map, bin\masters.lib emu.lib maths.lib cs.lib>obj\Research\pi_bench.@l
tlink @obj\Research\pi_bench.@l
bin\Pipeline\bmp2arr.com -q -i Research/blitperf/blitperf.bmp -o Research/blitperf/blitperf.csp -sym sBLITPERF -of cpp -sw 16 -sh 16
bin\Pipeline\bmp2arr.com -q -i Research/blitperf/wide.bmp -o Research/blitperf/wide.csp -sym sWIDE -of c -sw 640 -sh 40
echo -c  -I.  -O  -b-  -3  -Z  -d  -G  -k-  -p  -x-  -ms  -DCPU=86  -1-  -nobj/Research/086/  Research/blitperf/blitperf.cpp  platform/x86real/noexcept.cpp  platform/x86real/pc98/blitter.cpp  platform/x86real/pc98/font.cpp  platform/x86real/pc98/graph.cpp  platform/x86real/pc98/grcg.cpp  platform/x86real/pc98/grp_clip.cpp  platform/x86real/pc98/palette.cpp  platform/x86real/pc98/vsync.cpp  Research/blitperf/if_shift.cpp  Research/blitperf/wide.cpp  Research/blitperf/wide_b.cpp>obj\batch022.@c
echo Research/blitperf/xfade.cpp  Research/blitperf/xfade_b.cpp  platform/x86real/pc98/egc.cpp  platform/x86real/pc98/grp_surf.cpp>>obj\batch022.@c
tcc @obj/batch022.@c
echo -c -s c0s.obj obj\Research\086\if_shift.obj obj\Research\086\blitperf.obj obj\Research\086\noexcept.obj obj\Research\086\blitter.obj obj\Research\086\font.obj obj\Research\086\graph.obj obj\Research\086\grcg.obj obj\Research\086\grp_clip.obj obj\Research\086\palette.obj obj\Research\086\vsync.obj, bin\Research\ifshf086.exe, obj\Research\086\ifshf086.map, emu.lib maths.lib cs.lib>obj\Research\086\ifshf086.@l
tlink @obj\Research\086\ifshf086.@l
echo -c -s c0s.obj obj\Research\086\wide.obj obj\Research\086\wide_b.obj obj\Research\086\blitperf.obj obj\Research\086\noexcept.obj obj\Research\086\blitter.obj obj\Research\086\font.obj obj\Research\086\graph.obj obj\Research\086\grcg.obj obj\Research\086\grp_clip.obj obj\Research\086\palette.obj obj\Research\086\vsync.obj, bin\Research\wide086.exe, obj\Research\086\wide086.map, emu.lib maths.lib cs.lib>obj\Research\086\wide086.@l
tlink @obj\Research\086\wide086.@l
echo -c -s c0s.obj obj\piloadm.obj obj\Research\086\xfade.obj obj\Research\086\xfade_b.obj obj\Research\086\egc.obj obj\Research\086\grp_surf.obj obj\Research\086\blitperf.obj obj\Research\086\noexcept.obj obj\Research\086\blitter.obj obj\Research\086\font.obj obj\Research\086\graph.obj obj\Research\086\grcg.obj obj\Research\086\grp_clip.obj obj\Research\086\palette.obj obj\Research\086\vsync.obj, bin\Research\xfade086.exe, obj\Research\086\xfade086.map, bin\masters.lib emu.lib maths.lib cs.lib>obj\Research\086\xfade086.@l
tlink @obj\Research\086\xfade086.@l
echo -c  -I.  -O  -b-  -3  -Z  -d  -G  -k-  -p  -x-  -ms  -DCPU=286  -2  -nobj/Research/286/  Research/blitperf/blitperf.cpp  platform/x86real/noexcept.cpp  platform/x86real/pc98/blitter.cpp  platform/x86real/pc98/font.cpp  platform/x86real/pc98/graph.cpp  platform/x86real/pc98/grcg.cpp  platform/x86real/pc98/grp_clip.cpp  platform/x86real/pc98/palette.cpp  platform/x86real/pc98/vsync.cpp  Research/blitperf/if_shift.cpp  Research/blitperf/wide.cpp  Research/blitperf/wide_b.cpp>obj\batch023.@c
echo Research/blitperf/xfade.cpp  Research/blitperf/xfade_b.cpp  platform/x86real/pc98/egc.cpp  platform/x86real/pc98/grp_surf.cpp>>obj\batch023.@c
tcc @obj/batch023.@c
echo -c -s c0s.obj obj\Research\286\if_shift.obj obj\Research\286\blitperf.obj obj\Research\286\noexcept.obj obj\Research\286\blitter.obj obj\Research\286\font.obj obj\Research\286\graph.obj obj\Research\286\grcg.obj obj\Research\286\grp_clip.obj obj\Research\286\palette.obj obj\Research\286\vsync.obj, bin\Research\ifshf286.exe, obj\Research\286\ifshf286.map, emu.lib maths.lib cs.lib>obj\Research\286\ifshf286.@l
tlink @obj\Research\286\ifshf286.@l
echo -c -s c0s.obj obj\Research\286\wide.obj obj\Research\286\wide_b.obj obj\Research\286\blitperf.obj obj\Research\286\noexcept.obj obj\Research\286\blitter.obj obj\Research\286\font.obj obj\Research\286\graph.obj obj\Research\286\grcg.obj obj\Research\286\grp_clip.obj obj\Research\286\palette.obj obj\Research\286\vsync.obj, bin\Research\wide286.exe, obj\Research\286\wide286.map, emu.lib maths.lib cs.lib>obj\Research\286\wide286.@l
tlink @obj\Research\286\wide286.@l
echo -c -s c0s.obj obj\piloadm.obj obj\Research\286\xfade.obj obj\Research\286\xfade_b.obj obj\Research\286\egc.obj obj\Research\286\grp_surf.obj obj\Research\286\blitperf.obj obj\Research\286\noexcept.obj obj\Research\286\blitter.obj obj\Research\286\font.obj obj\Research\286\graph.obj obj\Research\286\grcg.obj obj\Research\286\grp_clip.obj obj\Research\286\palette.obj obj\Research\286\vsync.obj, bin\Research\xfade286.exe, obj\Research\286\xfade286.map, bin\masters.lib emu.lib maths.lib cs.lib>obj\Research\286\xfade286.@l
tlink @obj\Research\286\xfade286.@l
echo -c  -I.  -O  -b-  -3  -Z  -d  -G  -k-  -p  -x-  -ms  -DCPU=386  -nobj/Research/386/  Research/blitperf/blitperf.cpp  platform/x86real/noexcept.cpp  platform/x86real/pc98/blitter.cpp  platform/x86real/pc98/font.cpp  platform/x86real/pc98/graph.cpp  platform/x86real/pc98/grcg.cpp  platform/x86real/pc98/grp_clip.cpp  platform/x86real/pc98/palette.cpp  platform/x86real/pc98/vsync.cpp  Research/blitperf/if_shift.cpp  Research/blitperf/wide.cpp  Research/blitperf/wide_b.cpp>obj\batch024.@c
echo Research/blitperf/xfade.cpp  Research/blitperf/xfade_b.cpp  platform/x86real/pc98/egc.cpp  platform/x86real/pc98/grp_surf.cpp>>obj\batch024.@c
tcc @obj/batch024.@c
echo -c -s c0s.obj obj\Research\386\if_shift.obj obj\Research\386\blitperf.obj obj\Research\386\noexcept.obj obj\Research\386\blitter.obj obj\Research\386\font.obj obj\Research\386\graph.obj obj\Research\386\grcg.obj obj\Research\386\grp_clip.obj obj\Research\386\palette.obj obj\Research\386\vsync.obj, bin\Research\ifshf386.exe, obj\Research\386\ifshf386.map, emu.lib maths.lib cs.lib>obj\Research\386\ifshf386.@l
tlink @obj\Research\386\ifshf386.@l
echo -c -s c0s.obj obj\Research\386\wide.obj obj\Research\386\wide_b.obj obj\Research\386\blitperf.obj obj\Research\386\noexcept.obj obj\Research\386\blitter.obj obj\Research\386\font.obj obj\Research\386\graph.obj obj\Research\386\grcg.obj obj\Research\386\grp_clip.obj obj\Research\386\palette.obj obj\Research\386\vsync.obj, bin\Research\wide386.exe, obj\Research\386\wide386.map, emu.lib maths.lib cs.lib>obj\Research\386\wide386.@l
tlink @obj\Research\386\wide386.@l
echo -c -s c0s.obj obj\piloadm.obj obj\Research\386\xfade.obj obj\Research\386\xfade_b.obj obj\Research\386\egc.obj obj\Research\386\grp_surf.obj obj\Research\386\blitperf.obj obj\Research\386\noexcept.obj obj\Research\386\blitter.obj obj\Research\386\font.obj obj\Research\386\graph.obj obj\Research\386\grcg.obj obj\Research\386\grp_clip.obj obj\Research\386\palette.obj obj\Research\386\vsync.obj, bin\Research\xfade386.exe, obj\Research\386\xfade386.map, bin\masters.lib emu.lib maths.lib cs.lib>obj\Research\386\xfade386.@l
tlink @obj\Research\386\xfade386.@l
