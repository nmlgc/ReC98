/// Entities
/// --------

// Slot count for unique .BOS files associated with CBossEntity instances.
// *Not* CBossEntity instances themselves!
#define BOS_ENTITY_SLOT_COUNT 4

// An individual entity rendered with sprites from a .BOS file. May or may not
// be animated, and may or may not have a hitbox for collision with the Orb.
class CBossEntity {
public:
	screen_x_t cur_left;
	screen_y_t cur_top;
	screen_x_t prev_left;
	screen_y_t prev_top;
	vram_byte_amount_t vram_w;
	pixel_t h;
	area_t<screen_x_t, screen_y_t> move_clamp; // Relative to VRAM
	area_t<pixel_t, pixel_t> hitbox_orb; // Relative to [cur_left] and [cur_top]

	// Never actually read outside of the functions that set them...
	pixel_t prev_delta_y;
	pixel_t prev_delta_x;

	int bos_image_count;

protected:
	int zero_1;
	int bos_image;
	int unknown;

public:
	bool16 hitbox_orb_inactive;
	bool16 loading;
	int move_lock_frame;
	int zero_2;
	char zero_3;
	unsigned char bos_slot;

	CBossEntity();

	// Even Turbo C++ 4.0J implements copy constructors for trivially
	// constructible types via an equivalent of memcpy() by default. This
	// constructor downgrades that to dumb single-member assignment, and is
	// undeniably worse. MODDERS: Delete.
	CBossEntity(const CBossEntity near &other) {
		cur_left = other.cur_left;
		cur_top = other.cur_top;
		prev_left = other.prev_left;
		prev_top = other.prev_top;
		vram_w = other.vram_w;
		h = other.h;
		move_clamp.left = other.move_clamp.left;
		move_clamp.right = other.move_clamp.right;
		move_clamp.top = other.move_clamp.top;
		move_clamp.bottom = other.move_clamp.bottom;
		hitbox_orb.left = other.hitbox_orb.left;
		hitbox_orb.right = other.hitbox_orb.right;
		hitbox_orb.top = other.hitbox_orb.top;
		hitbox_orb.bottom = other.hitbox_orb.bottom;
		prev_delta_y = other.prev_delta_y;
		prev_delta_x = other.prev_delta_x;
		bos_image_count = other.bos_image_count;
		zero_1 = other.zero_1;
		bos_image = other.bos_image;
		unknown = other.unknown;
		hitbox_orb_inactive = other.hitbox_orb_inactive;
		loading = other.loading;
		move_lock_frame = other.move_lock_frame;
		zero_2 = other.zero_2;
		zero_3 = other.zero_3;
		bos_slot = other.bos_slot;
	}

	// Loads all images from the .BOS file with the given [fn] inside the
	// currently active packfile into the given CBossEntity .BOS [slot], and
	// keeps the .BOS metadata in this CBossEntity instance. Always returns 0.
	void load(const char fn[PF_FN_LEN], int slot) {
		loading = true;
		load_inner(fn, slot);
		loading = false;
	}

	int load_inner(const char fn[PF_FN_LEN], int slot);

	// Copies the .BOS header data of this instance to the given variables. In
	// practice, only used to copy these values from one CBossEntity to
	// another, via metadata_assign().
	void metadata_get(
		int &image_count,
		unsigned char &slot,
		vram_byte_amount_t &vram_w,
		pixel_t &h
	) const;

	// Copies the .BOS header data of [src] to this instance.
	void metadata_assign(const CBossEntity near &src) {
		// MODDERS: Delete this unnecessary and wasteful temporary copy.
		CBossEntity tmp(src);

		tmp.metadata_get(bos_image_count, bos_slot, vram_w, h);
	}

	int image(void) const {
		return bos_image;
	}

	void set_image(int image) {
		bos_image = image;
	}

	pixel_t w_aligned(void) const {
		return ((vram_w * BYTE_DOTS) + 16);
	}

	/// Blitting
	/// --------
	// All functions with an [image] parameter use that image from [bos_slot],
	// *not* the [bos_image] of this instance.
	// Well, OK, except for the next one, with...

	// Sets [bos_image] and blits the image to the entity's current position.
	// Additionally clips at the bottom edge of VRAM.
	void set_image_unput_and_put_8(int image) {
		bos_image = image;
		unput_and_put_8(cur_left, cur_top, bos_image);
	}

	// Like CPlayerAnim, all of these also make an attempt at clipping the
	// sprite at the left and right edges of VRAM. This only really works if
	// [left] is a multiple of 16 and inside the [-RES_X, RES_X[ range,
	// though, and is pretty much broken otherwise.

	// Blits [image] to the entity's current position. Additionally clips at
	// the bottom edge of VRAM.
	// (This function really shouldn't exist, as it can introduce a disparity
	// between [bos_image] and the one on screen.)
	void put_8(int image) const {
		put_8(cur_left, cur_top, image);
	}

	// Blits [bos_image] to the entity's current position.
	// Additionally clips at the bottom edge of VRAM.
	void put_8(void) const {
		put_8(cur_left, cur_top, bos_image);
	}

	// Blits [image] to (⌊left/8⌋*8, top).
	// Additionally clips at the bottom edge of VRAM.
	void put_8(screen_x_t left, vram_y_t top, int image) const;

	// Precisely restores pixels according to the alpha mask of [image] from
	// VRAM page 1, starting at (⌊left/8⌋*8, top).
	// Additionally clips at the top and bottom edges of VRAM.
	void unput_8(screen_x_t left, vram_y_t top, int image) const;

	// Like put_8(), but restores all pixels in the blitted sprite
	// rectangle from VRAM page 1 prior to blitting.
	// Additionally clips at the top and bottom edges of VRAM.
	void unput_and_put_8(screen_x_t left, vram_y_t top, int image) const;

	// Blits line #[row] of [image] to (left, top).
	// Additionally clips at the bottom edge of VRAM.
	void put_1line(screen_x_t left, vram_y_t y, int image, pixel_t row) const;

	// Like put_1line(), but restores all pixels along the line from VRAM page
	// 1 prior to blitting the line.
	void unput_and_put_1line(
		screen_x_t left, vram_y_t y, int image, pixel_t row
	) const;

	// Blits [image] with a wave function applied to the starting X coordinate
	// for each row, based at the given (left, top) point. Used for Elis'
	// entrance animation.
	// Calls put_1line() for each row, and clips the sprite accordingly.
	void wave_put(
		screen_x_t left,
		vram_y_t top,
		int image,
		int len,
		pixel_t amp,
		int phase
	) const;

	// Like wave_put(), but calls unput_and_put_1line() for each line instead.
	// For a sloppy, EGC-accelerated unblitter function, see egc_wave_unput().
	void wave_unput_and_put(
		screen_x_t left,
		vram_y_t top,
		int image,
		int len,
		pixel_t amp,
		int phase
	) const;

	// Tries to unblit the two sprites at (left_1, top) and (left_2, top) that
	// were previously blitted with the given wave function using the EGC, but
	// fails.
	void egc_sloppy_wave_unput_double_broken(
		screen_x_t left_1, vram_y_t top, int unused,
		int len_1, pixel_t amp_1, int phase_1,
		screen_x_t left_2,
		int len_2, pixel_t amp_2, int phase_2
	) const;

	// Blits the 16×8 pixels of [bos_image] in [bos_slot] starting at
	// (bos_left, bos_top), relative to the top-left corner of the sprite, to
	//	((⌊cur_left/8⌋ + bos_left/8⌋) * 8, (cur_top + bos_top))
	// after precisely restoring pixels according to the alpha mask of the
	// pixels to be blitted from VRAM page 1.
	// Additionally clips at the top and bottom edges of VRAM.
	void unput_and_put_16x8_8(pixel_t bos_left, pixel_t bos_top) const;

	// Restores the pixels inside the entire ([vram_w]*8)×[h] rectangle
	// starting at (cur_left, cur_top) from VRAM page 1.
	void sloppy_unput(void) const;
	/// --------

	/// Movement
	/// --------
protected:
	void move(const pixel_t &delta_x, const pixel_t &delta_y) {
		prev_delta_x = delta_x;
		prev_delta_y = delta_y;
		prev_left = cur_left;
		prev_top = cur_top;

		cur_left += prev_delta_x;
		if(move_clamp.left > cur_left) {
			cur_left = move_clamp.left;
		}
		if(move_clamp.right < cur_left) {
			cur_left = move_clamp.right;
		}

		cur_top += prev_delta_y;
		if(cur_top < move_clamp.top) {
			cur_top = move_clamp.top;
		}
		if(cur_top > move_clamp.bottom) {
			cur_top = move_clamp.bottom;
		}
	}

public:
	void pos_cur_set(screen_x_t left, screen_x_t top) {
		cur_left = left;
		cur_top = top;
	}

	// Sets [cur_left], [cur_top], [unknown], and the [move_clamp] area.
	//
	// Kikuri is the only boss who relies on move clamping. All others ignore
	// the feature by just directly partying on [cur_left] and [cur_top], and
	// can ignore the last 4 parameters. ZUN is very likely to just have
	// copy-pasted their [move_clamp_right] and [move_clamp_bottom] values from
	// SinGyoku, as they don't make a lot of sense in context of the entity
	// widths of other bosses.
	void pos_set(
		screen_x_t left,
		screen_y_t top,
		int unknown = 48,
		screen_x_t move_clamp_left = PLAYFIELD_LEFT,
		screen_x_t move_clamp_right = (PLAYFIELD_RIGHT + SINGYOKU_W),
		screen_y_t move_clamp_top = PLAYFIELD_TOP,
		screen_y_t move_clamp_bottom = (PLAYFIELD_BOTTOM - SINGYOKU_H)
	);

	// Sets [hitbox_orb] to the given coordinates, relative to the top-left
	// corner of the image.
	void hitbox_set(pixel_t left, pixel_t top, pixel_t right, pixel_t bottom) {
		hitbox_orb.left = left;
		hitbox_orb.right = right;
		hitbox_orb.top = top;
		hitbox_orb.bottom = bottom;
	}

	// (Just read the actual function code, it's impossible to summarize these
	// without spelling out every single line here.)
	void move_lock_and_put_8(
		int unused, pixel_t delta_x, pixel_t delta_y, int lock_frames
	);
	void move_lock_unput_and_put_8(
		int unused, pixel_t delta_x, pixel_t delta_y, int lock_frames
	);

	void move_lock_and_put_8(void) {
		move_lock_frame = 0;
		move_lock_and_put_8(0, 0, 0, 3);
	}

	void move_lock_and_put_image_8(int image) {
		move_lock_frame = 0;
		bos_image = image;
		move_lock_and_put_8(0, 0, 0, 3);
	}

	void move_lock_unput_and_put_image_8(int image) {
		move_lock_frame = 0;
		bos_image = image;
		move_lock_unput_and_put_8(0, 0, 0, 3);
	}
	/// --------

	/// Collision detection
	/// -------------------
public:
	// Simply returns whether the orb collided with this entity on the last
	// frame. (TODO: Last frame???)
	bool16 hittest_orb(void) const;
	/// -------------------
};

// Despite CBossEntity's own width and height fields, ZUN still likes to
// statically hardcode the intended sprite sizes when calculating offsets
// within a .BOS sprite. Since bosses #define more readable names for each
// instance of [boss_entities], we might as well use the opportunity to lift up
// these static sizes into the type system, and avoid the need for per-boss
// boilerplate coordinate functions.
//
// (Due to CBossEntity unfortunately having a non-inlined default constructor,
// we can't ever directly declare instance of this template without emitting
// another constructor for this class.)
template <pixel_t W, pixel_t H> struct CBossEntitySized : public CBossEntity {
	screen_x_t cur_center_x(void) const {
		return (cur_left + (W / 2));
	}

	screen_x_t cur_center_y(void) const {
		return (cur_top + (H / 2));
	}

	screen_x_t cur_right(void) const {
		return (cur_left + W);
	}
}

// Frees all images in the given [slot].
void bos_entity_free(int slot);

extern CBossEntity boss_entities[5];
/// --------

/// Non-entity animations
/// ---------------------

// Slot count for unique .BOS files associated with CBossAnim instances.
// *Not* CBossAnim instances themselves!
#define BOS_ANIM_SLOT_COUNT 2

// Stripped-down version of CBossEntity, with just animation support. These
// only have functions for direct byte-aligned blitting onto page 0, in
// exchange for the alpha plane being pre-negated at load time? No idea why.
// That 1-instruction negation is certainly not what makes the original code
// slow.
class CBossAnim {
public:
	screen_x_t left;
	screen_y_t top;
	vram_byte_amount_t vram_w;
	pixel_t h;
	unsigned char bos_image_count;
	unsigned char bos_image;
	unsigned char bos_slot;

	// Loads all images from the .BOS file with the given [fn] inside the
	// currently active packfile into the given CBossAnim .BOS [slot], and
	// keeps the .BOS metadata in this CBossEntity instance. Always returns 0.
	// Identical to CBossEntity::load() with an added alpha negation loop.
	int load(const char fn[PF_FN_LEN], int slot);

	// Blits [bos_image] to (⌊left/8⌋*8, top).
	// Additionally clips at the bottom edge of VRAM.
	void put_8(void) const;
};

// Frees all images in the given [slot].
void bos_anim_free(int slot);

extern CBossAnim boss_anims[2];
/// ---------------------
