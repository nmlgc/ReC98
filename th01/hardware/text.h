// Fills the text layer with spaces.
// PORTERS: Implement better, and more consistently.
#define text_fill_space(esc_move_topleft, space, tmp_x, tmp_y) { \
	printf(esc_move_topleft); \
	for(tmp_y = 0; tmp_y < (RES_Y / GLYPH_H); tmp_y++) { \
		for(tmp_x = 0; tmp_x < (RES_X / GLYPH_HALF_W); tmp_x++) { \
			printf(space); \
		} \
	} \
}

// Fills the text layer with opaque black.
// MODDERS: This should maybe reset the current text mode color.
#define text_fill_black( \
	esc_color_bg_black_fg_black, esc_move_topleft, space, tmp_x, tmp_y \
) { \
	printf(esc_color_bg_black_fg_black); \
	text_fill_space(esc_move_topleft, space, tmp_x, tmp_y); \
}

// Fills the text layer with transparent spaces. Yes, this overwrites the
// perfectly suitable master.lib function with the same name.
#define text_clear_sloppy(tmp_x, tmp_y) { \
	printf("\x1B[0m"); /* Reset text mode color */ \
	/* (yes, this escape sequence is actually 1-based) */ \
	text_fill_space("\x1B[1;1H", " ", tmp_x, tmp_y); \
}
