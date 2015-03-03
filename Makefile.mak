# ReC98
# -----
# Makefile for the 16-bit part of the build process

CFLAGS = -ls -Ilibs\master.lib\ -I. -Lbin\ -O -a2

TH01 = \zunsoft.com \op.exe \reiiden.exe \fuuin.exe
TH02 = \zuninit.com \zun_res.com \op.exe \main.exe \maine.exe
TH03 = \zunsp.com \res_yume.com \op.exe \main.exe \mainl.exe
TH04 = \res_huma.com \op.exe \main.exe \maine.exe
TH05 = \res_kso.com \op.exe \main.exe \maine.exe

all: th01 th02 th03 th04 th05
	@echo Done. Find the executables in the bin\ subdirectory.

th01:: $(TH01:\=bin\th01\)
th02:: $(TH02:\=bin\th02\)
th03:: $(TH03:\=bin\th03\)
th04:: $(TH04:\=bin\th04\)
th05:: $(TH05:\=bin\th05\)

.obj.exe:
	$(CC) $(CFLAGS) -ml $**

.obj.com:
	tlink /t /3 $**

bin\th01\zunsoft.com: th01\zunsoft.c
	$(CC) $(CFLAGS) -mt -lt -nbin\th01\ $** masters.lib

bin\th01\op.exe: bin\th01\op.obj th01\op_11.c
	$(CC) $(CFLAGS) -ml -3 -nbin\th01\ -eOP.EXE $**

bin\th01\reiiden.exe: bin\th01\reiiden.obj th01\main_16.c
	$(CC) $(CFLAGS) -ml -3 -nbin\th01\ -eREIIDEN.EXE $**

bin\th01\fuuin.exe: bin\th01\fuuin.obj th01\fuuin_11.c th01\fuuin_13.c
	$(CC) $(CFLAGS) -ml -3 -nbin\th01\ -eFUUIN.EXE @&&|
$**
|

bin\th02\op.exe: bin\th02\op.obj th02\op_02.c th02\op_03.c th02\op_04.c th02\op_05.c th02\op_06.c
	$(CC) $(CFLAGS) -ml -Z -DGAME=2 -nbin\th02\ -eOP.EXE @&&|
$**
|

bin\th02\maine.exe: bin\th02\maine.obj th02\maine_03.c th02\maine_04.c th02\maine_05.c
	$(CC) $(CFLAGS) -ml -3 -Z -DGAME=2 -nbin\th02\ -eMAINE.EXE @&&|
$**
|

bin\th03\op.exe: bin\th03\op.obj th03\op_02.c
	$(CC) $(CFLAGS) -ml -DGAME=3 -nbin\th03\ -eOP.EXE @&&|
$**
|

bin\th04\op.exe: bin\th04\op.obj th04\op_02.c
	$(CC) $(CFLAGS) -ml -DGAME=4 -nbin\th04\ -eOP.EXE @&&|
$**
|
