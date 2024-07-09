; Blank line to remove HP bar
public _gHUD_HP_BLANK
_gHUD_HP_BLANK label byte
	rept HUD_KANJI_W
		db g_EMPTY
	endm
		db 0 ; '\0'

; Colors for the HP bars.
public _HUD_HP_COLORS
_HUD_HP_COLORS label byte
	db TX_RED
	db TX_MAGENTA
	db TX_CYAN
	db TX_YELLOW
	db TX_WHITE
HUD_HP_COLOR_COUNT = ($ - _HUD_HP_COLORS)
