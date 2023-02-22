# ReC98 Research
# --------------
# Makefile

.autodepend

LFLAGS = -L..\bin\

all: HOLDKEY.EXE

HOLDKEY.EXE: HOLDKEY.OBJ
	$(CC) $(LFLAGS) masters.lib $**
