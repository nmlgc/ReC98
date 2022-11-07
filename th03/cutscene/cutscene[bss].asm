NAME_LEN = 6
NAME_KANJI_LEN = (NAME_LEN / 2)
NAME_W = ((NAME_LEN * GLYPH_HALF_W) + GLYPH_FULL_W)

BOX_LEFT = 80
BOX_TOP = 320
BOX_W = 480
BOX_H = (GLYPH_H * 4)

BOX_VRAM_W = (BOX_W / BYTE_DOTS)
BOX_RIGHT = (BOX_LEFT + BOX_W)
BOX_BOTTOM = (BOX_TOP + BOX_H)

public _script, _fast_forward, _box_bg
if (GAME ge 4)
	public _script_p
	_script  	db 8192 dup(?)
	_script_p	dw ?
else
	_script	dd ?
endif
_box_bg	dd ?
_fast_forward	db ?

if (GAME ge 4)
	db 60 dup(?)
endif
if (GAME eq 5)
	COLMAP_COUNT = 8

	colmap_t struc
		CM_values	db COLMAP_COUNT dup (?)
		CM_keys	dw (NAME_KANJI_LEN * COLMAP_COUNT) dup (?)
	colmap_t ends

	public _colmap
	_colmap	colmap_t <?>
endif
	evendata

public _cursor, _text_interval, _text_col, _text_fx
public _script_number_param_default
_cursor                     	Point <?>
_text_interval              	dw ?
_text_col                   	db ?
_text_fx                    	db ?
_script_number_param_default	dw ?
