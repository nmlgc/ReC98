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

// Lines
// -----

static const pixel_t DIALOG_MARGIN = 16;

static const pixel_t DIALOG_LINE_W = (PLAYFIELD_W - DIALOG_MARGIN - FACE_W);
static const screen_x_t DIALOG_CURSOR_PLAYCHAR_LEFT = (
	PLAYFIELD_RIGHT - DIALOG_MARGIN - DIALOG_LINE_W
);
static const screen_y_t DIALOG_CURSOR_PLAYCHAR_TOP = (
	PLAYFIELD_BOTTOM - DIALOG_MARGIN - DIALOG_BOX_H
);

static const screen_x_t DIALOG_CURSOR_BOSS_LEFT = (
	PLAYFIELD_LEFT + DIALOG_MARGIN
);
static const screen_y_t DIALOG_CURSOR_BOSS_TOP = (
	DIALOG_CURSOR_PLAYCHAR_TOP - FACE_H
);
// -----

extern struct {
	#if (GAME == 5)
		tram_x_t x;
		tram_y_t y;
	#else
		screen_x_t x;
		screen_y_t y;
	#endif
} dialog_cursor;

enum dialog_side_t {
	DIALOG_SIDE_PLAYCHAR = 0,
	DIALOG_SIDE_BOSS = 1,

	_dialog_side_t_FORCE_INT16 = 0x7FFF
};

extern dialog_side_t dialog_side;

// Restores the [FACE_W]×[FACE_H] pixels starting at (⌊left/8⌋*8, top) on the
// currently active VRAM page with the same pixels from the other VRAM page.
void pascal near dialog_face_unput_8(uscreen_x_t left, uvram_y_t top);

// Runs the next dialog scene in a blocking way.
// During the TH05 Extra Stage Clear replay, this function
// • skips the dialog for the call before the fight, while replicating the
//   sprite loading and BGM change side effects from the original script,
// • and directly switches back to OP.EXE for the call after the fight.
void dialog_animate(void);

#if (GAME == 4)
	// Dialog-related image functions with optional EMS support
	// --------------------------------------------------------

	// Loads the remaining .CDG images for in-game dialog that haven't been in
	// memory since the start of the stage (i.e., the player character
	// faceset), freeing any images that aren't used during a dialog (i.e.,
	// the bomb background) in exchange for the necessary conventional memory.
	void near dialog_init(void);

	// Restores the bomb background image, after freeing any dialog-only images
	// (i.e., the player character faceset) in exchange for the necessary
	// conventional memory.
	// Apparently, this was also the most convenient place to load the boss
	// faceset used for both the Mugetsu defeat / Gengetsu entrance dialog and
	// the Gengetsu defeat dialogue? To differentiate between those two, the
	// function tracks how often it has been called during the Extra Stage.
	void near dialog_exit(void);
	// --------------------------------------------------------
#endif
