# ReC98
# -----
# Makefile for the 16-bit part of the build process

CFLAGS = -ls -Ilibs\master.lib\ -I. -Lbin\ -O -a2

TH01 = \zunsoft.com \op.exe \reiiden.exe \fuuin.exe
TH02 = \zuninit.com \zun_res.com \op.exe \main.exe \maine.exe \zun.com
TH03 = \zunsp.com \res_yume.com \op.exe \main.exe \mainl.exe \zun.com
TH04 = \res_huma.com \op.exe \main.exe \maine.exe
TH05 = \res_kso.com \op.exe \main.exe \maine.exe

all: th01 th02 th03 th04 th05
	@echo Done. Find the executables in the bin\ subdirectory.

th01:: $(TH01:\=bin\th01\)
th02:: $(TH02:\=bin\th02\)
th03:: $(TH03:\=bin\th03\)
th04:: $(TH04:\=bin\th04\)
th05:: $(TH05:\=bin\th05\)

{th05}.asm{bin\th05}.obj:
	$(AS) /dGAME=5 $**, $@

# Shared TH04/TH05 assembly units
# -------------------------------
# Need to go into separate .obj directories since they will have different
# AFLAGS per game.
{th04}.asm{bin\th04}.obj:
	$(AS) /dGAME=4 $**, $@
{th04}.asm{bin\th05}.obj:
	$(AS) /dGAME=5 $**, $@
# -------------------------------

.obj.exe:
	$(CC) $(CFLAGS) -ml $**

.obj.com:
	tlink /t /3 $**

bin\th01\zunsoft.com: th01\zunsoft.c
	$(CC) $(CFLAGS) -mt -lt -nbin\th01\ $** masters.lib

bin\th01\op.exe: bin\th01\op.obj th01\op_02.c th01\op_03.c th01\op_04.c th01\op_06.cpp th01\op_10.c th01\op_11.c th01\op_12.cpp
	$(CC) $(CFLAGS) -ml -3 -nbin\th01\ -eOP.EXE @&&|
$**
|

bin\th01\reiiden.exe: bin\th01\reiiden.obj th01\main_02.c th01\main_03.c th01\main_04.c th01\main_06.cpp th01\main_12.c th01\main_13.c th01\main_14.c th01\main_16.c
	$(CC) $(CFLAGS) -ml -3 -nbin\th01\ -eREIIDEN.EXE @&&|
$**
|

bin\th01\fuuin.exe: bin\th01\fuuin.obj th01\fuuin_05.c th01\fuuin_06.c th01\fuuin_08.cpp th01\fuuin_11.c th01\fuuin_12.c th01\fuuin_13.c
	$(CC) $(CFLAGS) -ml -3 -nbin\th01\ -eFUUIN.EXE @&&|
$**
|

bin\th02\zun_res.com: th02\zun_res1.c th02\zun_res2.c
	$(CC) $(CFLAGS) -mt -lt -Z -nbin\th02\ -eZUN_RES.COM @&&|
$**
| masters.lib

bin\th02\op.exe: th02\op_01.c bin\th02\op.obj th02\op_02_1.c th02\op_02_2.c th02\op_03.c th02\op_04.c th02\op_05.c th02\op_06.c
	$(CC) $(CFLAGS) -ml -Z -DGAME=2 -nbin\th02\ -eOP.EXE @&&|
$**
|

bin\th02\main.exe: bin\th02\main.obj th02\main02_1.c th02\main02_2.c
	$(CC) $(CFLAGS) -ml -Z -DGAME=2 -nbin\th02\ -eMAIN.EXE @&&|
$**
|

bin\th02\maine.exe: bin\th02\maine.obj th02\maine021.c th02\maine022.c th02\maine_03.c th02\maine_04.c th02\maine_05.c
	$(CC) $(CFLAGS) -ml -3 -Z -DGAME=2 -nbin\th02\ -eMAINE.EXE @&&|
$**
|

bin\th03\op.exe: bin\th03\op.obj th03\op_02.c
	$(CC) $(CFLAGS) -ml -DGAME=3 -nbin\th03\ -eOP.EXE @&&|
$**
|

bin\th03\main.exe: bin\th03\main.obj th03\main_01.cpp th03\sprite16.cpp
	$(CC) $(CFLAGS) -ml -Z -DGAME=3 -nbin\th03\ -eMAIN.EXE @&&|
$**
|

bin\th04\op.exe: bin\th04\op.obj th04\op_01.cpp th04\op_02.c
	$(CC) $(CFLAGS) -ml -DGAME=4 -DBINARY='O' -nbin\th04\ -eOP.EXE @&&|
$**
|

bin\th04\scoreupd.obj: th04\scoreupd.asm
bin\th04\main.exe: bin\th04\main.obj bin\th04\scoreupd.obj
	$(CC) $(CFLAGS) -ml -DGAME=4 -DBINARY='M' -nbin\th04\ -eMAIN.EXE @&&|
$**
|

bin\th05\player.obj: th05\player.asm
bin\th05\hud_bar.obj: th05\hud_bar.asm
bin\th05\scoreupd.obj: th04\scoreupd.asm

bin\th05\op.exe: bin\th05\op.obj th05\op_01.cpp
	$(CC) $(CFLAGS) -ml -DGAME=5 -DBINARY='O' -nbin\th05\ -eOP.EXE @&&|
$**
|

bin\th05\main.exe: bin\th05\main.obj th05\p_common.cpp th05\p_reimu.cpp th05\p_marisa.cpp th05\p_mima.cpp th05\p_yuuka.cpp bin\th05\player.obj bin\th05\hud_bar.obj bin\th05\scoreupd.obj th05\main012.cpp
	$(CC) $(CFLAGS) -ml -3 -Z -DGAME=5 -DBINARY='M' -nbin\th05\ -eMAIN.EXE @&&|
$**
|

# ZUN.COM packing

bin\zuncom\zungen.com: zuncom\zungen.c
	mkdir bin\zuncom
	$(CC) $(CFLAGS) -mt -lt -nbin\zuncom\ -eZUNGEN.COM $**

bin\zuncom\zun_stub.bin: zuncom\zun_stub.asm
	mkdir bin\zuncom
	tasm zuncom\zun_stub.asm,bin\zuncom\zun_stub
	tlink -t bin\zuncom\zun_stub.obj,bin\zuncom\zun_stub.bin

bin\zuncom\comcstm.com: zuncom\comcstm.c
	mkdir bin\zuncom
	$(CC) $(CFLAGS) -mt -lt -nbin\zuncom\ -eCOMCSTM.com $**

bin\zuncom\cstmstub.bin: zuncom\cstmstub.asm
	mkdir bin\zuncom
	tasm zuncom\cstmstub.asm,bin\zuncom\cstmstub
	tlink -t bin\zuncom\cstmstub.obj,bin\zuncom\cstmstub.bin

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
