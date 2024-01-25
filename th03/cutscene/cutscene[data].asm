if (GAME eq 5)
	public _colmap_count
	_colmap_count	db 0
		evendata
endif

if (GAME ge 4)
	public _BOX_MASKS
	_BOX_MASKS label word
		dw   8888h,     0h,  2222h,     0h
		dw   8888h,  4444h,  2222h,  1111h
		dw  0AAAAh,  4444h, 0AAAAh,  1111h
		dw  0AAAAh,  4444h, 0AAAAh,  5555h
		dw  0FFFFh, 0FFFFh, 0FFFFh, 0FFFFh
endif

public _CUTSCENE_KANJI
_CUTSCENE_KANJI	db  '  ', 0
	even
