# ReC98
# -----
# Makefile for the 16-bit part of the build process

CFLAGS = -ls -Ilibs\master.lib\ -Lbin\

TH01 = \zunsoft.com \op.exe \reiiden.exe \fuuin.exe
TH02 = \zuninit.com \zun_res.com \op.exe \main.exe \maine.exe
TH03 = \zunsp.com \res_yume.com \op.exe \main.exe \mainl.exe
TH04 = \zuninit.com \memchk.com \res_huma.com \op.exe \main.exe \maine.exe
TH05 = \zuninit.com \memchk.com \gjinit.com \res_kso.com \op.exe \main.exe \maine.exe

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

bin\th04\memchk.com: bin\th04\memchk.obj
	$(CC) $(CFLAGS) -mt -lt $**
