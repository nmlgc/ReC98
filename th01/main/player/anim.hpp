#include "th01/formats/bos.hpp"

static const int PLAYER_ANIM_IMAGES_PER_SLOT = 32;

// Collection of up to [PLAYER_ANIM_IMAGES_PER_SLOT] player animation sprites
// from a .BOS file, with a consistent byte-aligned / 8w×h size. Used for
// sprites with a width ≠ [PTN_W] or a height ≠ [PTN_H].
class CPlayerAnim {
	bos_image_t images[PLAYER_ANIM_IMAGES_PER_SLOT];
	vram_byte_amount_t vram_w;
	pixel_t h;
	int bos_image_count;

public:
	// Loads all images from the .BOS file with the given [fn] inside the
	// currently active packfile. Always returns 0.
	int load(const char fn[PF_FN_LEN]);

	// Frees all [bos_image_count] loaded images.
	void free(void);

	/// Blitting
	/// --------
	// All of these clip the sprite at the top and bottom edges of VRAM. Like
	// CBossEntity and CBossAnim, they also make an attempt at clipping on the
	// left and right edges, but that only really works if [left] is a
	// multiple of 16 and inside the [-RES_X, RES_X[ range, and is pretty much
	// broken otherwise.

	// Precisely restores pixels according to the alpha mask of [image] from
	// VRAM page 1, starting at (⌊left/8⌋*8, top).
	void unput_8(screen_x_t left, vram_y_t top, int image) const;

	// Blits [image] to (⌊left/8⌋*8, top) on VRAM page 0.
	void put_0_8(screen_x_t left, vram_y_t top, int image) const;

	// Blits [put_image] to
	// 	(⌊  put_left/8⌋*8,   put_top)
	// on VRAM page 0, after attempting to restore the pixels of [unput_image]
	// starting at
	// 	(⌊unput_left/8⌋*8, unput_top),
	// that wouldn't be overlapped by the subsequent [put_image] blit, from
	// VRAM page 1.
	//
	// Only unblits correctly if |⌊put_left/8⌋*8 - ⌊unput_left/8⌋*8| ≤ 1,
	// though, and spends a lot of CPU time in optimizing the dot patterns for
	// unblitting. Calling unput_8() and put_0_8() separately might therefore
	// be just as fast.
	void unput_and_put_overlapped_8(
		screen_x_t put_left,
		vram_y_t put_top,
		screen_x_t unput_left,
		vram_y_t unput_top,
		int put_image,
		int unput_image
	) const;
	/// --------
};

// Really though, everything about this is bad, these do not deserve more
// semantic names
extern CPlayerAnim player_48x48;
extern CPlayerAnim player_48x32;
