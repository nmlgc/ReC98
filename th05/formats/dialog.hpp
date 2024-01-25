/// TH05 in-game dialog script format
/// ---------------------------------

struct tx2_header_t {
	// The dialog script for player character N is stored between
	// `offset_for[N]` and `offset_for[N + 1]`.
	uint16_t offset_for[PLAYCHAR_COUNT + 1];
};

// Parameters for the 0x06 sprite blitting command.
struct tx2_op_06_params {
	screen_x_t left;
	screen_y_t top;
	uint8_t patnum;
};

const uint8_t FACE_NONE = 0xFF;

// Script buffer pointer. The segment part also doubles as the base pointer to
// the allocated dialog buffer for later dialog_free() calls, and therefore
// must not be changed while running the script – hence the explicit `far`.
extern unsigned char far *dialog_p;

// Loading and freeing
// -------------------

// Loads the dialog script for the current player character from the .TX2 file
// with the given name. `far` in this game, as it's also called from outside
// its segment.
void pascal dialog_load(const char *fn);

// Loads the dialog script for the current player character and stage.
void near dialog_load(void);

// Frees any previously loaded dialog script.
void near dialog_free(void);
// -------------------
/// ---------------------------------
