public _exitbuf, _exitfopen, _exitopen
if LDATA
_exitbuf	dd dummy
_exitfopen	dd dummy
_exitopen	dd dummy
else
_exitbuf	dw dummy
_exitfopen	dw dummy
_exitopen	dw dummy
endif
