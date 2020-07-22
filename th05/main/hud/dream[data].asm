; Colors for the dream bars.
public _HUD_DREAM_COLORS
_HUD_DREAM_COLORS label byte
	db TX_RED
	db TX_RED
	db TX_MAGENTA
	db TX_MAGENTA
	db TX_BLUE
	db TX_GREEN
	db TX_CYAN
	db TX_YELLOW
	db TX_WHITE
HUD_DREAM_COLOR_COUNT = ($ - _HUD_DREAM_COLORS)
