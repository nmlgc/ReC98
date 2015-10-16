public _atexittbl
if LDATA
_atexittbl	dd MAX_ATEXIT dup(?)
else
_atexittbl	dw MAX_ATEXIT dup(?)
endif
