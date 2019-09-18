; Shared buffer for one full row of gaiji characters. Used for temporarily
; storing the two scores, and the enemy health, dream, and power bars.
HUD_TRAM_W = 8
public _HUD_GAIJI_ROW
_hud_gaiji_row	db (HUD_TRAM_W + 1) dup (0)
	db 0	; (word alignment)
