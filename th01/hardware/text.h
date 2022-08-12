// Fills the text layer with spaces.
// ZUN bloat: The slowest imaginable version of this operation.
#define text_fill_space(esc_move_topleft, tmp_x, tmp_y) { \
	printf(esc_move_topleft); \
	for(tmp_y = 0; tmp_y < (RES_Y / GLYPH_H); tmp_y++) { \
		for(tmp_x = 0; tmp_x < (RES_X / GLYPH_HALF_W); tmp_x++) { \
			printf(" "); \
		} \
	} \
}

// Fills the text layer with opaque black.
// MODDERS: This should maybe reset the current text mode color.
#define text_fill_black(tmp_x, tmp_y) { \
	printf("\x1B[16;40m"); \
	text_fill_space("\x1B[0;0H", tmp_x, tmp_y); \
}

inline void text_color_reset(void) {
	printf("\x1B[0m");
}

// Fills the text layer with transparent spaces. Yes, this overwrites the
// perfectly suitable master.lib function with the same name.
#define text_clear_sloppy(tmp_x, tmp_y) { \
	text_color_reset(); \
	/* (yes, this escape sequence is actually 1-based) */ \
	text_fill_space("\x1B[1;1H", tmp_x, tmp_y); \
}
