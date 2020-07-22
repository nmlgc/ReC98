; Colors for the HP bars.
public _HUD_HP_COLORS
_HUD_HP_COLORS label byte
	db TX_RED
	db TX_MAGENTA
	db TX_CYAN
	db TX_YELLOW
	db TX_WHITE
HUD_HP_COLOR_COUNT = ($ - _HUD_HP_COLORS)
