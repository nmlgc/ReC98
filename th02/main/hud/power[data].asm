; Colors for the power bars. Indexed with [shot_level].
public _HUD_POWER_COLORS
_HUD_POWER_COLORS label byte
	db TX_RED
	db TX_RED
	db TX_RED
	db TX_MAGENTA
	db TX_MAGENTA
	db TX_BLUE
	db TX_GREEN
	db TX_CYAN
	db TX_YELLOW
if (GAME ge 4)
	db TX_WHITE
endif
