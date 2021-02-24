; ReC98
; -----
; PC-98 hardware constants not covered by master.lib

; Text
; ====
GAIJI_W = 16
GAIJI_TRAM_W = (GAIJI_W / 8)
GLYPH_HALF_W = 8
GLYPH_FULL_W = 16
GLYPH_H = 16
; ====

; Graphics
; ========
RES_X = 640
RES_Y = 400
ROW_SIZE = (RES_X / 8)
PLANE_SIZE = (ROW_SIZE * RES_Y)
COLOR_COUNT = 16

PLANE_COUNT = 4

; RGB color triple, used for the Palettes structure
rgb_t struc
	r db ?
	g db ?
	b db ?
rgb_t ends

palette_t struc
	colors	rgb_t COLOR_COUNT dup(<?>)
palette_t ends
; ========

SEG_PLANE_B = 0A800h
SEG_PLANE_R = 0B000h
SEG_PLANE_G = 0B800h
SEG_PLANE_E = 0E000h
SEG_PLANE_DIST_BRG = 800h
SEG_PLANE_DIST_E = 2800h
