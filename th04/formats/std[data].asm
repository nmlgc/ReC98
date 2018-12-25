public _std_seg, _std_fn
_std_seg	dw 0
if GAME eq 5
	_std_fn 	db 'ST00.STD', 0
else
	_std_fn 	dd aSt00_std
	aSt00_std	db 'ST00.STD', 0
endif
		db 0
