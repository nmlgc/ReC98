	extern _zunsoft_palette:byte:48

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

PYRO_COUNT = 256
	extern _pyros:zunsoft_pyro_t:PYRO_COUNT
