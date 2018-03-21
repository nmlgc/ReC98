; Copy of the palette used during the logo, to allow non-blocking fades in
; contrast to master.lib's blocking palette_black_in() and palette_black_out()
; functions. (Then again, master.lib has the PaletteTone global for that...)
_zunsoft_palette	db 48 dup(?)

; ZUN Soft logo explosion structure.
; These are only animated by increasing the distance; origin, angle, and speed
; stay constant.
; For increased precision, all coordinates (origin, distance, and speed) are
; stored in units of 1/16th of a pixel.
zunsoft_pyro_t struc
	alive	db ?
	frame	db ? ; since creation
	origin	Point ?
	distance_prev	dw ? ; unused
	distance	dw ?
	speed	dw ?
	angle	db ?
	patnum_base	db ? ; displayed sprite is incremented every 4 frames
zunsoft_pyro_t ends

ZUNSOFT_PYRO_COUNT = 256
_zunsoft_pyros	zunsoft_pyro_t ZUNSOFT_PYRO_COUNT dup(<?>)
