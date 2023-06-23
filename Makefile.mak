# Makefile for the 16-bit part of the build process
# -------------------------------------------------








# ⚠️ CAUTION! ⚠️

# You are on the `master` branch, which builds PC-98 DOS binaries that are
# identical to ZUN's originally released binaries. If you want to port the game
# to other architectures or develop a mod that doesn't need to be byte-for-byte
# comparable to the original binary, start from the cleaned-up `debloated`
# branch instead. That branch is easier to read and modify, and builds smaller
# and faster PC-98 binaries while leaving all bugs and quirks from ZUN's
# original code in place.
# Seriously, you'd just be torturing yourself if you do anything nontrivial
# based on this branch.

# ⚠️ CAUTION! ⚠️







CFLAGS = -ls -I. -Lbin\ -O -b-
AFLAGS = /m /ml

# Currently, it only makes sense to enable extended dictionary processing for
# binaries that don't link the original binary release of MASTERS.LIB, which
# doesn't come with them.
LARGE_LFLAGS = -ml -lE

PIPELINE = \grzview.com
TH01 = \zunsoft.com \op.exe \reiiden.exe \fuuin.exe
TH02 = \zuninit.com \zun_res.com \op.exe \main.exe \maine.exe \zun.com
TH03 = \zunsp.com \res_yume.com \op.exe \main.exe \mainl.exe \zun.com
TH04 = \zuninit.com \memchk.com \res_huma.com \op.exe \main.exe \maine.exe  \zun.com
TH05 = \zuninit.com \memchk.com \gjinit.com \res_kso.com \op.exe \main.exe \maine.exe  \zun.com

all: pipeline th01 th02 th03 th04 th05 Research
	@echo Done. Find the executables in the bin\ subdirectory.

pipeline:: $(PIPELINE:\=bin\Pipeline\)
th01:: $(TH01:\=bin\th01\)
th02:: $(TH02:\=bin\th02\)
th03:: $(TH03:\=bin\th03\)
th04:: $(TH04:\=bin\th04\)
th05:: $(TH05:\=bin\th05\)

.obj.com:
	tlink /t /3 $**

bin\Pipeline\grzview.com: Pipeline\grzview.cpp th01\formats\grz.cpp bin\th01\f_imgd.obj platform\x86real\pc98\palette.cpp
	$(CC) $(CFLAGS) -Z -DGAME=1 -mt -lt -nbin\Pipeline\ @&&|
$**
| masters.lib

bin\th01\zunsoft.com: th01\zunsoft.cpp
	$(CC) $(CFLAGS) -mt -lt -DGAME=1 -nbin\th01\ $** masters.lib

{th01}.c{bin\th01}.obj:
	$(CC) $(CFLAGS) -ml -3 -Z -d -DGAME=1 -n$(@D) -c $**
{th01}.cpp{bin\th01}.obj:
	$(CC) $(CFLAGS) -ml -3 -Z -d -DGAME=1 -n$(@D) -c $**

bin\th01\op.exe: bin\piloadc.obj th01\op_01.cpp bin\th01\frmdelay.obj bin\th01\vsync.obj bin\th01\ztext.obj bin\th01\initexit.obj bin\th01\graph.obj bin\th01\ptn_0to1.obj bin\th01\vplanset.obj th01\op_07.cpp bin\th01\grp_text.obj bin\th01\ptn.obj th01\op_09.cpp bin\th01\f_imgd.obj bin\th01\grz.obj bin\th01\op.obj bin\th01\resstuff.obj bin\th01\mdrv2.obj bin\th01\pf.obj
	$(CC) $(CFLAGS) $(LARGE_LFLAGS) -3 -Z -d -DGAME=1 -DBINARY='O' -nbin\th01\ -eOP.EXE @&&|
$**
|

bin\th01\reiiden.exe: bin\piloadc.obj th01\main_01.cpp bin\th01\frmdelay.obj bin\th01\vsync.obj bin\th01\ztext.obj bin\th01\initexit.obj bin\th01\graph.obj bin\th01\ptn_0to1.obj bin\th01\vplanset.obj th01\main_07.cpp bin\th01\ptn.obj th01\main_08.cpp bin\th01\f_imgd.obj bin\th01\grz.obj bin\th01\reiiden.obj th01\main_09.cpp th01\bullet_l.cpp th01\grpinv32.cpp bin\th01\resstuff.obj th01\scrollup.cpp th01\egcrows.cpp th01\pgtrans.cpp th01\2x_main.cpp th01\egcwave.cpp th01\grph1to0.cpp th01\main_14.cpp th01\main_15.cpp bin\th01\mdrv2.obj th01\main_17.cpp th01\main_18.cpp th01\main_19.cpp th01\main_20.cpp th01\main_21.cpp bin\th01\pf.obj th01\main_23.cpp th01\main_24.cpp th01\main_25.cpp th01\main_26.cpp th01\main_27.cpp th01\main_28.cpp th01\main_29.cpp th01\main_30.cpp th01\main_31.cpp th01\main_32.cpp th01\main_33.cpp th01\main_34.cpp th01\main_35.cpp th01\main_36.cpp th01\main_37.cpp th01\main_38.cpp
	$(CC) $(CFLAGS) $(LARGE_LFLAGS) -3 -Z -d -DGAME=1 -DBINARY='M' -nbin\th01\ -eREIIDEN.EXE @&&|
$**
|

bin\th01\fuuin.exe: bin\piloadc.obj th01\fuuin_01.cpp bin\th01\input_mf.obj th01\fuuin_02.cpp th01\fuuin_03.cpp th01\fuuin_04.cpp bin\th01\vsync.obj bin\th01\ztext.obj bin\th01\initexit.obj bin\th01\graph.obj bin\th01\grp_text.obj th01\fuuin_10.cpp th01\f_imgd_f.cpp bin\th01\vplanset.obj th01\fuuin_11.cpp th01\2x_fuuin.cpp bin\th01\mdrv2.obj bin\th01\fuuin.obj
	$(CC) $(CFLAGS) $(LARGE_LFLAGS) -3 -Z -DGAME=1 -DBINARY='E' -nbin\th01\ -eFUUIN.EXE @&&|
$**
|

{th02}.c{bin\th02}.obj:
	$(CC) $(CFLAGS) -ml -3 -Z -DGAME=2 -n$(@D) -c $**
{th02}.cpp{bin\th02}.obj:
	$(CC) $(CFLAGS) -ml -3 -Z -DGAME=2 -n$(@D) -c $**

bin\th02\zun_res.com: th02\zun_res1.cpp th02\zun_res2.c th02\zun_res3.c
	$(CC) $(CFLAGS) -mt -lt -Z -DGAME=2 -nbin\th02\ -eZUN_RES.COM @&&|
$**
| masters.lib

bin\th02\op.exe: th02\op_01.cpp bin\th02\exit_dos.obj bin\th02\zunerror.obj bin\th02\grppsafx.obj bin\th02\op.obj bin\th01\vplanset.obj bin\th02\pi_load.obj bin\th02\grp_rect.obj bin\th02\frmdely2.obj bin\th02\input_s.obj bin\th02\initop.obj bin\th02\exit.obj bin\th02\snd_mmdr.obj bin\th02\snd_mode.obj bin\th02\snd_pmdr.obj bin\th02\snd_load.obj bin\th02\pi_put.obj bin\th02\snd_kaja.obj th02\op_02_3.cpp bin\th02\snd_se_r.obj bin\th02\snd_se.obj bin\th02\frmdely1.obj th02\op_03.cpp bin\th02\globals.obj th02\op_04.cpp th02\op_05.cpp th02\op_06.cpp
	$(CC) $(CFLAGS) $(LARGE_LFLAGS) -Z -DGAME=2 -nbin\th02\ -eOP.EXE @&&|
$**
|

bin\th02\main.exe: bin\th02\main.obj bin\th02\tile.obj th02\pointnum.cpp th02\item.cpp th02\hud.cpp th02\player_b.cpp bin\th02\zunerror.obj bin\th02\keydelay.obj th02\main02_1.cpp bin\th01\vplanset.obj bin\th02\pi_load.obj bin\th02\vector.obj bin\th02\frmdely1.obj bin\th02\input_s.obj bin\th02\exit.obj bin\th02\snd_mmdr.obj bin\th02\snd_mode.obj bin\th02\snd_pmdr.obj bin\th02\snd_dlyv.obj bin\th02\snd_load.obj th02\mpn_l_i.cpp bin\th02\initmain.obj bin\th02\pi_put.obj bin\th02\snd_kaja.obj bin\th02\snd_dlym.obj bin\th02\snd_se_r.obj bin\th02\snd_se.obj th02\main_03.cpp th02\hud_ovrl.cpp
	$(CC) $(CFLAGS) $(LARGE_LFLAGS) -3 -Z -DGAME=2 -nbin\th02\ -eMAIN.EXE @&&|
$**
|

bin\th02\maine.exe: bin\th02\ranks_c.obj bin\th02\maine.obj bin\th02\grppsafx.obj bin\th02\keydelay.obj bin\th01\vplanset.obj bin\th02\pi_load.obj bin\th02\frmdely1.obj th02\maine022.cpp bin\th02\input_s.obj bin\th02\exit.obj bin\th02\snd_mmdr.obj bin\th02\snd_mode.obj bin\th02\snd_pmdr.obj bin\th02\snd_load.obj bin\th02\initmain.obj bin\th02\pi_put.obj bin\th02\snd_kaja.obj bin\th02\snd_dlym.obj bin\th02\globals.obj th02\maine_03.cpp th02\maine_04.cpp th02\maine_05.cpp
	$(CC) $(CFLAGS) $(LARGE_LFLAGS) -3 -Z -DGAME=2 -nbin\th02\ -eMAINE.EXE @&&|
$**
|

{th03}.c{bin\th03}.obj:
	$(CC) $(CFLAGS) -ml -3 -Z -DGAME=3 -n$(@D) -c $**
{th03}.cpp{bin\th03}.obj:
	$(CC) $(CFLAGS) -ml -3 -Z -DGAME=3 -n$(@D) -c $**

bin\th03\res_yume.com: th03\res_yume.cpp
	$(CC) $(CFLAGS) -mt -lt -Z -DGAME=3 -nbin\th03\ -eRES_YUME.COM @&&|
$**
| masters.lib

bin\th03\op.exe: th03\op_01.cpp th03\op_02.cpp bin\th03\scoredat.obj th03\op_03.cpp bin\th03\op.obj bin\th02\exit_dos.obj bin\th01\vplanset.obj bin\th02\snd_mode.obj bin\th02\snd_pmdr.obj bin\th02\snd_load.obj bin\th03\exit.obj bin\th03\polar.obj bin\th03\cdg_put.obj bin\th02\frmdely1.obj bin\th03\input_s.obj bin\th03\pi_put.obj bin\th03\snd_kaja.obj bin\th03\initop.obj bin\th03\cdg_load.obj bin\th03\grppsafx.obj bin\th03\pi_load.obj bin\th03\inp_m_w.obj bin\th03\cdg_p_na.obj bin\th03\hfliplut.obj bin\th02\frmdely2.obj
	$(CC) $(CFLAGS) $(LARGE_LFLAGS) -3 -Z -DGAME=3 -DBINARY='O' -nbin\th03\ -eOP.EXE @&&|
$**
|

bin\th03\main.exe: bin\th03\main.obj th03\main_010.cpp th03\main_011.cpp bin\th03\cfg_lres.obj bin\th01\vplanset.obj bin\th02\snd_mode.obj bin\th02\snd_pmdr.obj bin\th03\vector.obj bin\th03\exit.obj bin\th03\polar.obj bin\th02\frmdely1.obj bin\th03\input_s.obj bin\th02\snd_se_r.obj bin\th03\snd_se.obj bin\th03\snd_kaja.obj bin\th03\initmain.obj bin\th03\pi_load.obj bin\th03\inp_m_w.obj bin\th03\collmap.obj bin\th03\hfliplut.obj th03\mrs.cpp th03\sprite16.cpp
	$(CC) $(CFLAGS) $(LARGE_LFLAGS) -3 -Z -DGAME=3 -nbin\th03\ -eMAIN.EXE @&&|
$**
|

bin\th03\mainl.exe: bin\th03\mainl.obj th03\cutscene.cpp bin\th03\cfg_lres.obj bin\th03\scoredat.obj th03\regist.cpp bin\th01\vplanset.obj bin\th02\snd_mode.obj bin\th02\snd_pmdr.obj bin\th02\snd_dlyv.obj bin\th02\snd_load.obj bin\th03\vector.obj bin\th03\exit.obj bin\th03\cdg_put.obj bin\th02\frmdely1.obj bin\th03\input_s.obj bin\th03\pi_put.obj bin\th03\pi_put_i.obj bin\th02\snd_se_r.obj bin\th03\snd_se.obj bin\th03\snd_kaja.obj bin\th03\initmain.obj bin\th03\cdg_load.obj th03\exitmain.cpp bin\th03\grppsafx.obj bin\th03\snd_dlym.obj bin\th03\inp_wait.obj bin\th03\pi_load.obj bin\th03\pi_put_q.obj bin\th03\inp_m_w.obj bin\th03\cdg_p_na.obj bin\th03\hfliplut.obj
	$(CC) $(CFLAGS) $(LARGE_LFLAGS) -3 -Z -DGAME=3 -DBINARY='L' -nbin\th03\ -eMAINL.EXE @&&|
$**
|

{th04}.c{bin\th04}.obj:
	$(CC) $(CFLAGS) -ml -3 -Z -DGAME=4 -n$(@D) -c $**
{th04}.cpp{bin\th04}.obj:
	$(CC) $(CFLAGS) -ml -3 -Z -DGAME=4 -n$(@D) -c $**

bin\th04\memchk.com: bin\th04\memchk.obj
	$(CC) $(CFLAGS) -mt -lt $**

bin\th04\res_huma.com: th04\res_huma.cpp
	$(CC) $(CFLAGS) -mt -lt -Z -DGAME=4 -nbin\th04\ -eRES_HUMA.COM @&&|
$**
| masters.lib

bin\th04\op.exe: bin\th04\op.obj th04\m_char.cpp bin\th01\vplanset.obj bin\th02\frmdely1.obj bin\th03\pi_put.obj bin\th03\pi_load.obj bin\th03\hfliplut.obj bin\th04\input_w.obj bin\th04\vector.obj bin\th04\snd_pmdr.obj bin\th04\snd_mmdr.obj bin\th04\snd_kaja.obj bin\th04\cdg_p_nc.obj bin\th04\snd_mode.obj bin\th04\snd_dlym.obj bin\th02\exit_dos.obj bin\th04\snd_load.obj bin\th04\cdg_put.obj bin\th04\exit.obj bin\th04\initop.obj bin\th04\cdg_p_na.obj bin\th04\input_s.obj bin\th04\snd_se_r.obj bin\th04\snd_se.obj bin\th04\egcrect.obj bin\th04\bgimage.obj bin\th04\bgimager.obj bin\th04\cdg_load.obj th04\frmdely2.c
	$(CC) $(CFLAGS) $(LARGE_LFLAGS) -DGAME=4 -DBINARY='O' -3 -Z -d -nbin\th04\ -eOP.EXE @&&|
$**
|

bin\th04\main.exe: bin\th04\main.obj bin\th04\slowdown.obj th04\demo.cpp th04\ems.cpp th04\tile_set.cpp th04\std.cpp th04\playfld.cpp th04\midboss4.cpp th04\f_dialog.cpp th04\dialog.cpp th04\boss_exp.cpp th04\stages.cpp th04\player_m.cpp bin\th04\player_p.obj bin\th04\scoreupd.obj th04\hud_ovrl.cpp bin\th04\cfg_lres.obj bin\th04\checkerb.obj bin\th04\mb_inv.obj bin\th04\boss_bd.obj bin\th01\vplanset.obj bin\th03\vector.obj bin\th02\frmdely1.obj bin\th03\hfliplut.obj th04\mpn_free.cpp bin\th04\input_w.obj th04\mpn_l_i.cpp bin\th04\vector.obj bin\th04\snd_pmdr.obj bin\th04\snd_mmdr.obj bin\th04\snd_kaja.obj bin\th04\snd_mode.obj bin\th04\snd_load.obj bin\th04\cdg_put.obj bin\th04\exit.obj bin\th04\initmain.obj bin\th04\cdg_p_na.obj bin\th04\cdg_p_pr.obj bin\th04\input_s.obj bin\th04\snd_se_r.obj bin\th04\snd_se.obj bin\th04\cdg_load.obj th04\gather.cpp bin\th04\scrolly3.obj bin\th04\motion_3.obj th04\midboss.cpp bin\th04\hud_hp.obj th04\mb_dft.cpp bin\th04\vector2n.obj bin\th04\spark_a.obj bin\th04\grcg_3.obj bin\th04\it_spl_u.obj th04\boss_4m.cpp th04\bullet_u.cpp th04\bullet_a.cpp th04\boss.cpp th04\boss_4r.cpp th04\boss_x2.cpp
	$(CC) $(CFLAGS) $(LARGE_LFLAGS) -DGAME=4 -DBINARY='M' -3 -Z -nbin\th04\ -eMAIN.EXE @&&|
$**
|

bin\th04\maine.exe: bin\th04\maine.obj bin\th04\cfg_lres.obj th04\cutscene.cpp th04\staff.cpp bin\th01\vplanset.obj bin\th02\frmdely1.obj bin\th03\pi_put.obj bin\th04\cdg_put.obj bin\th04\exit.obj bin\th04\initmain.obj bin\th04\input_s.obj bin\th04\snd_se_r.obj bin\th04\snd_se.obj bin\th04\bgimage.obj bin\th04\bgimager.obj bin\th03\pi_load.obj bin\th03\pi_put_q.obj bin\th04\cdg_load.obj bin\th03\hfliplut.obj bin\th04\input_w.obj bin\th04\vector.obj bin\th04\snd_pmdr.obj bin\th04\snd_mmdr.obj bin\th04\snd_kaja.obj bin\th04\snd_mode.obj bin\th04\snd_dlym.obj bin\th04\cdg_p_pl.obj bin\th04\snd_load.obj
	$(CC) $(CFLAGS) $(LARGE_LFLAGS) -DGAME=4 -DBINARY='E' -3 -Z -nbin\th04\ -eMAINE.EXE @&&|
$**
|

{th05}.cpp{bin\th05}.obj:
	$(CC) $(CFLAGS) -ml -3 -Z -DGAME=5 -n$(@D) -c $**

bin\th05\res_kso.com: th05\res_kso.cpp
	$(CC) $(CFLAGS) -mt -lt -Z -DGAME=5 -nbin\th05\ -eRES_KSO.COM @&&|
$**
| masters.lib

bin\th05\op.exe: th05\op010.cpp bin\th05\op.obj th05\op011.cpp th05\m_char.cpp bin\th04\cdg_p_na.obj bin\th04\snd_se_r.obj bin\th04\snd_se.obj bin\th04\bgimage.obj bin\th05\cdg_put.obj bin\th04\exit.obj bin\th05\vector.obj bin\th05\musicp_c.obj bin\th05\musicp_a.obj bin\th05\bgimager.obj bin\th05\snd_load.obj bin\th05\snd_kaja.obj bin\th05\pi_cpp_1.obj bin\th05\pi_asm_1.obj bin\th05\pi_cpp_2.obj bin\th05\pi_asm_2.obj bin\th05\initop.obj bin\th05\input_s.obj bin\th05\inp_h_w.obj bin\th05\snd_dlym.obj th05\cdg_p_nc.cpp bin\th05\frmdelay.obj bin\th04\cdg_load.obj bin\th05\egcrect.obj bin\th03\hfliplut.obj bin\th04\snd_pmdr.obj bin\th04\snd_mmdr.obj bin\th04\snd_mode.obj bin\th02\exit_dos.obj
	$(CC) $(CFLAGS) $(LARGE_LFLAGS) -DGAME=5 -DBINARY='O' -3 -Z -nbin\th05\ -eOP.EXE @&&|
$**
|

bin\th05\main.exe: bin\th05\main.obj bin\th04\slowdown.obj th05\demo.cpp th05\ems.cpp bin\th05\cfg_lres.obj th05\main010.cpp th05\f_dialog.cpp th05\dialog.cpp th05\boss_exp.cpp th05\playfld.cpp bin\th04\mb_inv.obj bin\th04\boss_bd.obj th05\boss_bg.cpp th05\laser_rh.cpp th05\p_common.cpp th05\p_reimu.cpp th05\p_marisa.cpp th05\p_mima.cpp th05\p_yuuka.cpp bin\th05\player.obj bin\th05\hud_bar.obj bin\th05\scoreupd.obj th05\midboss5.cpp th05\hud_ovrl.cpp bin\th04\player_p.obj bin\th04\vector2n.obj bin\th05\spark_a.obj th05\bullet_p.cpp bin\th04\grcg_3.obj th05\player_a.cpp bin\th05\bullet_1.obj th05\bullet_c.cpp bin\th03\vector.obj bin\th03\hfliplut.obj bin\th04\snd_pmdr.obj bin\th04\snd_mmdr.obj bin\th04\snd_mode.obj bin\th05\bullet.obj th05\bullet_t.cpp bin\th04\cdg_p_na.obj bin\th04\snd_se_r.obj bin\th04\snd_se.obj bin\th05\cdg_put.obj bin\th04\exit.obj bin\th05\vector.obj bin\th05\snd_load.obj bin\th05\snd_kaja.obj bin\th05\initmain.obj bin\th05\input_s.obj bin\th05\inp_h_w.obj bin\th05\frmdelay.obj bin\th04\cdg_load.obj bin\th04\scrolly3.obj bin\th04\motion_3.obj th05\gather.cpp th05\main032.cpp th05\midboss.cpp bin\th04\hud_hp.obj th05\mb_dft.cpp th05\laser.cpp th05\cheeto_u.cpp bin\th04\it_spl_u.obj th05\bullet_u.cpp th05\midboss1.cpp th05\boss_1.cpp th05\boss_4.cpp th05\boss_6.cpp th05\boss_x.cpp th05\boss.cpp th05\main014.cpp
	$(CC) $(CFLAGS) $(LARGE_LFLAGS) -3 -Z -DGAME=5 -DBINARY='M' -nbin\th05\ -eMAIN.EXE @&&|
$**
|

bin\th05\maine.exe: bin\th05\maine.obj th05\cutscene.cpp bin\th04\cfg_lres.obj th05\regist.cpp th05\staff.cpp bin\th04\cdg_p_na.obj bin\th04\snd_se_r.obj bin\th04\snd_se.obj bin\th04\bgimage.obj bin\th04\exit.obj bin\th05\vector.obj bin\th05\bgimager.obj bin\th05\snd_load.obj bin\th05\snd_kaja.obj bin\th05\pi_cpp_1.obj bin\th05\pi_asm_1.obj bin\th05\pi_cpp_2.obj bin\th05\pi_asm_2.obj bin\th05\initmain.obj bin\th05\input_s.obj bin\th05\inp_h_w.obj bin\th05\snd_dlym.obj bin\th05\frmdelay.obj bin\th04\cdg_load.obj bin\th05\egcrect.obj bin\th03\hfliplut.obj bin\th04\snd_pmdr.obj bin\th04\snd_mmdr.obj bin\th04\snd_mode.obj
	$(CC) $(CFLAGS) $(LARGE_LFLAGS) -DGAME=5 -DBINARY='E' -3 -Z -nbin\th05\ -eMAINE.EXE @&&|
$**
|

Research:
	cd Research
	-$(MAKE)
	cd ..\

# ZUN.COM packing

{bin\zuncom}.obj{bin\zuncom}.bin:
	tlink -t $**, $@

bin\zuncom\zungen.com: zuncom\zungen.c
	$(CC) $(CFLAGS) -mt -lt -nbin\zuncom\ -eZUNGEN.COM $**

bin\zuncom\comcstm.com: zuncom\comcstm.c
	$(CC) $(CFLAGS) -mt -lt -nbin\zuncom\ -eCOMCSTM.com $**

ZUNCOM_PREREQ = bin\zuncom\zungen.com bin\zuncom\zun_stub.bin

bin\th02\zun.com : $(ZUNCOM_PREREQ) libs\kaja\ongchk.com bin\th02\zuninit.com bin\th02\zun_res.com bin\th01\zunsoft.com
	bin\zuncom\zungen bin\zuncom\zun_stub.bin &&|
4
ONGCHK
ZUNINIT
ZUN_RES
ZUNSOFT
libs\kaja\ongchk.com
bin\th02\zuninit.com
bin\th02\zun_res.com
bin\th01\zunsoft.com
| bin\th02\zun.com

bin\th03\zun.com : $(ZUNCOM_PREREQ) libs\kaja\ongchk.com bin\th02\zuninit.com bin\th01\zunsoft.com bin\th03\zunsp.com bin\th03\res_yume.com
	bin\zuncom\zungen bin\zuncom\zun_stub.bin &&|
5
-1
-2
-3
-4
-5
libs\kaja\ongchk.com
bin\th02\zuninit.com
bin\th01\zunsoft.com
bin\th03\zunsp.com
bin\th03\res_yume.com
| bin\th03\zun.com

bin\th04\zuncom.bin : $(ZUNCOM_PREREQ) libs\kaja\ongchk.com bin\th04\zuninit.com bin\th04\res_huma.com bin\th04\memchk.com
	bin\zuncom\zungen bin\zuncom\zun_stub.bin &&|
4
-O
-I
-S
-M
libs\kaja\ongchk.com
bin\th04\zuninit.com
bin\th04\res_huma.com
bin\th04\memchk.com
| bin\th04\zuncom.bin

bin\th05\zuncom.bin : $(ZUNCOM_PREREQ) libs\kaja\ongchk.com bin\th05\zuninit.com bin\th05\res_kso.com bin\th05\gjinit.com bin\th05\memchk.com
	bin\zuncom\zungen bin\zuncom\zun_stub.bin &&|
5
-O
-I
-S
-G
-M
libs\kaja\ongchk.com
bin\th05\zuninit.com
bin\th05\res_kso.com
bin\th05\gjinit.com
bin\th05\memchk.com
| bin\th05\zuncom.bin

bin\th04\zun.com : bin\zuncom\comcstm.com zuncom\zun4.txt bin\th04\zuncom.bin bin\zuncom\cstmstub.bin
	bin\zuncom\comcstm zuncom\zun4.txt bin\th04\zuncom.bin bin\zuncom\cstmstub.bin 621381155 bin\th04\zun.com

bin\th05\zun.com : bin\zuncom\comcstm.com zuncom\zun5.txt bin\th05\zuncom.bin bin\zuncom\cstmstub.bin
	bin\zuncom\comcstm zuncom\zun5.txt bin\th05\zuncom.bin bin\zuncom\cstmstub.bin 628731748 bin\th05\zun.com
