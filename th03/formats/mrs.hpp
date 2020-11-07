/// Headerless, uncompressed 16-color + alpha, upside-down 288×184 image format
/// ---------------------------------------------------------------------------
/// .CDG was apparently not good enough? Used for gauge attack portraits and
/// bomb backgrounds.

static const int MRS_SLOT_COUNT = 8;
static const pixel_t MRS_W = 288;
static const pixel_t MRS_H = 184;

// Persistently flips the image in [slot] horizontally, using the [hflip_lut].
void pascal mrs_hflip(int slot);
/// ---------------------------------------------------------------------------
