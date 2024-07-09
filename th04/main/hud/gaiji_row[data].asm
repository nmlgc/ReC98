; Shared buffer for one full row of gaiji characters. Used for temporarily
; storing the two scores, and the enemy health, dream, and power bars.
public _hud_gaiji_row
_hud_gaiji_row	db (HUD_KANJI_W + 1) dup (0)
	db 0	; (word alignment)
