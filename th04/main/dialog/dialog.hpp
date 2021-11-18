// Box
// ---
#define DIALOG_BOX_W 320
#define DIALOG_BOX_H 48
#define DIALOG_BOX_TILE_W 16
#define DIALOG_BOX_TILE_H 4
#define DIALOG_BOX_TILE_COUNT 3

#define DIALOG_BOX_TILE_VRAM_W (DIALOG_BOX_TILE_W / BYTE_DOTS)
#define DIALOG_BOX_VRAM_W (DIALOG_BOX_W / BYTE_DOTS)

extern const dot_rect_t(DIALOG_BOX_TILE_W, DIALOG_BOX_TILE_H) DIALOG_BOX_TILES[
	DIALOG_BOX_TILE_COUNT
];

void pascal near dialog_box_put(uscreen_x_t left, uvram_y_t top, int tile);
void pascal near dialog_box_fade_in();
// ---

enum dialog_side_t {
	DIALOG_SIDE_PLAYCHAR = 0,
	DIALOG_SIDE_BOSS = 1,

	_dialog_side_t_FORCE_INT16 = 0x7FFF
};

extern dialog_side_t dialog_side;

// Restores the [FACE_W]×[FACE_H] pixels starting at (⌊left/8⌋*8, top) on the
// currently active VRAM page with the same pixels from the other VRAM page.
void pascal near dialog_face_unput_8(uscreen_x_t left, uvram_y_t top);

#if (GAME == 4)
	// Dialog-related image functions with optional EMS support
	// --------------------------------------------------------

	// Loads the remaining .CDG images for in-game dialog that haven't been in
	// memory since the start of the stage (i.e., the player character
	// faceset), freeing any images that aren't used during a dialog (i.e.,
	// the bomb background) in exchange for the necessary conventional memory.
	void near dialog_init(void);
	// --------------------------------------------------------
#endif
