; ReC98
; -----
; PC-98 hardware constants not covered by master.lib

; Text
; ====
GAIJI_W = 16
GAIJI_TRAM_W = (GAIJI_W / 8)
GLYPH_HEIGHT = 16
; ====

; Graphics
; ========
RES_X = 640
RES_Y = 400
ROW_SIZE = (RES_X / 8)
; Collides with master.lib's bfnt_entry_pat.asm
; PLANE_SIZE = (ROW_SIZE * RES_Y)
COLOR_COUNT = 16
; ========
