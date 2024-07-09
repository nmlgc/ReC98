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

// Always updated by any of the .GRP loading or blitting functions.
extern Palette4 grp_palette;

// Overwrites [grp_palette] with [pal].
void grp_palette_set_all(const Palette4& pal);

// Just loads [grp_palette] from the .GRP file with the given [fn], and updates
// the hardware palette with it. Returns garbage.
int grp_palette_load_show(const char *fn);

// Sane version of grp_palette_load_show(). Returns 0 on success, 1 on file
// opening failure.
int grp_palette_load_show_sane(const char *fn);

// Displays the .GRP image loaded from [fn] on the currently accessed VRAM
// page, using the current hardware palette. Returns the return value from
// PiLoad.
int grp_put(const char *fn);

// Like grp_put(), but sets the hardware palette to the one in [fn]'s header.
int grp_put_palette_show(const char *fn);

// Like grp_put(), but treats color #15 as transparent.
int grp_put_colorkey(const char *fn);

#if (BINARY == 'E')
	extern int grp_palette_tone;

	// Sets colors 1 - 15 (excluding color 0!) of z_Palettes and the hardware
	// palette to [grp_palette] at the given [tone].
	// The toning algorithm is equivalent to master.lib's palette_settone().
	void pascal grp_palette_settone(int tone);

	// Equivalent to the master.lib functions, but based on the [grp_palette].
	// Implemented using grp_palette_settone(), and thus ignoring color 0.
	void pascal grp_palette_black_out(unsigned int frame_delay_per_step);
	void pascal grp_palette_black_in(unsigned int frame_delay_per_step);
	void pascal grp_palette_white_out(unsigned int frame_delay_per_step);
	void pascal grp_palette_white_in(unsigned int frame_delay_per_step);
#endif
/// -----------
