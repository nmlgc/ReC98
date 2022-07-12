; Colors for the power bars. Indexed with the SHOT_LEVELS values.
public _HUD_POWER_COLORS
_HUD_POWER_COLORS	label byte
	db TX_RED
	db TX_RED
	db TX_RED
	db TX_MAGENTA
	db TX_MAGENTA
	db TX_BLUE
	db TX_GREEN
	db TX_CYAN
	db TX_YELLOW
HUD_POWER_COLOR_COUNT = ($ - _HUD_POWER_COLORS)
