static const int PLAYER_ANIM_IMAGES_PER_SLOT = 32;

struct player_anim_images_t {
	dots8_t *img[PLAYER_ANIM_IMAGES_PER_SLOT];

	dots8_t*& operator [](int image) {
		return img[image];
	}
};

// Collection of up to [PLAYER_ANIM_IMAGES_PER_SLOT] player animation sprites
// from a .BOS file, with a consistent byte-aligned / 8w×h size. Used for
// sprites with a width ≠ [PTN_W] or a height ≠ [PTN_H].
class CPlayerAnim {
	dots8_t *alpha[PLAYER_ANIM_IMAGES_PER_SLOT];
	Planar<player_anim_images_t> planes;
	vram_byte_amount_t vram_w;
	pixel_t h;
	int bos_image_count;

	// Loads all images from the .BOS file with the given [fn] inside the
	// currently active packfile. Always returns 0.
	int load(const char fn[PF_FN_LEN]);

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
	/// --------
};

extern CPlayerAnim player_anim_forward;
extern CPlayerAnim player_anim_slide;
