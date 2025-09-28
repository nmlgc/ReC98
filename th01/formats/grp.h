/// .PI variant
/// -----------
/// .PI is a common lossless PC-98 image format that features efficient
/// compression for the often dithered 16-color pixel art typically associated
/// with the platform. This .GRP format only differs from regular .PI files in
/// two minor aspects:
///
/// • The two magic header bytes are "ZN" instead of "Pi". (Lol)
/// • The palette uses PC-98-native 4-bit color component values from 0x0 to
///   0xF, leaving the top 4 bits empty. .PI loaders that expect 8-bit color
///   components will therefore interpret .GRP images as being very dark.
///
/// These functions are just wrappers around the PiLoad library, which
/// implements the actual format by directly decoding an image to VRAM.
/// All .GRP images are assumed to be 640×400.
///
/// More info on the original format: https://mooncore.eu/bunny/txt/pi-pic.htm

#include "pc98.h"

// Flags
// -----

typedef uint8_t grp_put_flag_t;

// Keeps the current hardware palette. Still updates [grp_palette] though!
static const grp_put_flag_t GPF_PALETTE_KEEP = (0 << 0);

// Sets the hardware palette to the one from the header of the displayed .GRP.
static const grp_put_flag_t GPF_PALETTE_SHOW = (1 << 0);

// Treats color #15 as transparent.
static const grp_put_flag_t GPF_COLORKEY     = (1 << 1);
// -----

// Palette
// -------

// Always updated by any of the .GRP loading or blitting functions.
extern Palette4 grp_palette;

// Sets colors 1 - 15 (excluding color 0!) of z_Palettes and the hardware
// palette to [grp_palette] at the given [tone].
// The toning algorithm is equivalent to master.lib's palette_settone().
void grp_palette_settone(int tone);

// Equivalent to the master.lib functions, but based on the [grp_palette].
// Implemented using grp_palette_settone(), and thus ignoring color 0.
void grp_palette_black_out(unsigned int frame_delay_per_step);
void grp_palette_black_in(unsigned int frame_delay_per_step);
void grp_palette_white_out(unsigned int frame_delay_per_step);
void grp_palette_white_in(unsigned int frame_delay_per_step);
// -------

// Displays the .GRP image loaded from [fn] on the currently accessed VRAM
// page, applying the given flags. Returns the return value from PiLoad.
int grp_put(const char *fn, grp_put_flag_t flag);
/// -----------
