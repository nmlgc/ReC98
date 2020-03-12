PTN_COUNT = 8

public _flag_palette_show, _flag_grp_put, _ptn_image_count, _flag_grp_colorkey
_flag_palette_show	dw 1
_flag_grp_put	dw 1
	db 3 dup(0)
_ptn_image_count	db PTN_COUNT dup(0)

if BINARY eq 'E'
	public _grp_palette_tone
	_grp_palette_tone	dw 100
endif

_flag_grp_colorkey	db 0
