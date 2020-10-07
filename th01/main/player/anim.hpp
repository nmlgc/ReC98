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
};

extern CPlayerAnim player_anim_forward;
extern CPlayerAnim player_anim_slide;
