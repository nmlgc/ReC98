# ReC98 Research
# --------------
# Makefile

.autodepend

LFLAGS = -L..\bin -ls
CFLAGS = -I..\ -O -b- -Z -d -G -k- -p -x-

all: HOLDKEY.EXE BLITPERF

{.;..\platform\x86real;..\platform\x86real\pc98}.cpp{obj\8086}.obj:
	-@mkdir obj >NUL
	-@mkdir obj\8086 >NUL
	$(CC) $(CFLAGS) -DCPU=8086 -ms -1- -o$@ -c $**

{.;..\platform\x86real;..\platform\x86real\pc98}.cpp{obj\286}.obj:
	-@mkdir obj >NUL
	-@mkdir obj\286 >NUL
	$(CC) $(CFLAGS) -DCPU=286 -ms -2 -o$@ -c $**

{.;..\platform\x86real;..\platform\x86real\pc98}.cpp{obj\386}.obj:
	-@mkdir obj >NUL
	-@mkdir obj\386 >NUL
	$(CC) $(CFLAGS) -DCPU=386 -ms -3 -o$@ -c $**

HOLDKEY.EXE: HOLDKEY.OBJ
	$(CC) $(LFLAGS) masters.lib $**

BLITPERF_OBJ = -BLITPERF.obj -noexcept.obj -blitter.obj -font.obj -graph.obj -grcg.obj -palette.obj -vsync.obj

BLITPERF: BLIT8086.EXE BLIT286.EXE BLIT386.EXE

BLIT8086.EXE:: $(BLITPERF_OBJ:-=obj\8086\)
	$(CC) $(LFLAGS) -e$& @&&|
$**
|

BLIT286.EXE:: $(BLITPERF_OBJ:-=obj\286\)
	$(CC) $(LFLAGS) -e$& @&&|
$**
|

BLIT386.EXE:: $(BLITPERF_OBJ:-=obj\386\)
	$(CC) $(LFLAGS) -e$& @&&|
$**
|
