#include <stdio.h>

// Moves the DOS text cursor to the text RAM cell at
// ((max((x - 1), 0), (max((y - 1), 0)).
#define text_cursor_move_1_based(x, y) { \
	printf("\x1B[" #y ";" #x "H"); \
}

// Fills the text layer with spaces.
// ZUN bloat: The slowest imaginable version of this operation.
#define text_fill_space(tmp_x, tmp_y) { \
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
	text_cursor_move_1_based(0, 0); \
	text_fill_space(tmp_x, tmp_y); \
}

inline void text_color_reset(void) {
	printf("\x1B[0m");
}

// Fills the text layer with transparent spaces. Yes, this overwrites the
// perfectly suitable master.lib function with the same name.
#define text_clear_sloppy(tmp_x, tmp_y) { \
	text_color_reset(); \
	text_cursor_move_1_based(1, 1); \
	text_fill_space(tmp_x, tmp_y); \
}
