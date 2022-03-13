/// TH05 in-game dialog script format
/// ---------------------------------

struct tx2_header_t {
	// The dialog script for player character N is stored between
	// `offset_for[N]` and `offset_for[N + 1]`.
	uint16_t offset_for[PLAYCHAR_COUNT + 1];
};

const uint8_t FACE_NONE = 0xFF;

// Script buffer pointer
extern unsigned char far *dialog_p;

// Loading and freeing
// -------------------

// Loads the dialog script for the current player character from the .TX2 file
// with the given name. `far` in this game, as it's also called from outside
// its segment.
void pascal dialog_load(const char *fn);

// Loads the dialog script for the current player character and stage.
void near dialog_load(void);
// -------------------
/// ---------------------------------
