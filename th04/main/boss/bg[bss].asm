public _tiles_bb_col, _boss_backdrop_colorfill, _tiles_bb_seg
_tiles_bb_col	db ?
	evendata
; Called with the GRCG set to the [color] parameter to boss_bg_render(), this
; function is supposed to fill the entire playfield area around the background
; image with the given color.
_boss_backdrop_colorfill	dw ?
_tiles_bb_seg	dw ?
