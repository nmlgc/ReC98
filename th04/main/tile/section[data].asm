public _TILE_SECTION_OFFSETS
_TILE_SECTION_OFFSETS label word
	@@i = 0
	rept TILE_SECTION_COUNT_MAX
		dw (@@i * TILES_MEMORY_X * TILE_ROWS_PER_SECTION * word)
		@@i = (@@i + 1)
	endm
