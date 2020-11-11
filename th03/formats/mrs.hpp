/// Headerless, uncompressed 16-color + alpha, upside-down 288×184 image format
/// ---------------------------------------------------------------------------
/// .CDG was apparently not good enough? Used for gauge attack portraits and
/// bomb backgrounds.

static const int MRS_SLOT_COUNT = 8;
static const pixel_t MRS_W = 288;
static const pixel_t MRS_H = 184;

// Loads the .MRS image from [fn] into the given [slot], which is assumed to
// be empty.
void pascal mrs_load(int slot, const char *fn);

// Frees the .MRS image in the given [slot].
void pascal mrs_free(int slot);

// Displays the .MRS image in the given [slot] at (⌊left/8⌋*8, top).
void pascal mrs_put_8(screen_x_t left, uscreen_y_t top, int slot);

// Displays the .MRS image in the given [slot] at (⌊left/8⌋*8, top),
// disregarding its alpha plane, and optionally altering its colors slightly.
void pascal mrs_put_noalpha_8(
	screen_x_t left, uscreen_y_t top, int slot, bool altered_colors
);

// Persistently flips the image in [slot] horizontally, using the [hflip_lut].
void pascal mrs_hflip(int slot);
/// ---------------------------------------------------------------------------
