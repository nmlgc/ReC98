# ReC98 Research
# --------------
# Makefile

.autodepend

LFLAGS = -L..\bin -ls
CFLAGS = -I..\ -O -b- -Z -d -G -k- -p -x-

all: HOLDKEY.EXE

HOLDKEY.EXE: HOLDKEY.OBJ
	$(CC) $(LFLAGS) masters.lib $**
