// Needed outside to allow callers to set these to "custom" colors… i.e., the
// intended ones after they partied on the palette themselves. Would be cleaner
// if regist() just set the correct hardware palette itself… oh well, it also
// helps to document which colors you'd better not use in the background image.
#define COL_REGIST_SELECTED	3 // V_GREEN
#define COL_REGIST_REGULAR 	V_WHITE

#define regist_colors_set() { \
	z_Palettes[COL_REGIST_SELECTED].set(0x7, 0xF, 0x7); \
	z_Palettes[COL_REGIST_REGULAR ].set(0xF, 0xF, 0xF); \
	z_palette_set_all_show(z_Palettes); \
}

// Shows the high score list for the current difficulty. If the given game
// result is good enough to be on there, the player is asked to enter a name,
// before the result is inserted and written to the high score file.
void regist(
	int32_t score, int16_t stage, const char route[SCOREDAT_ROUTE_LEN + 1]
);
