#include "th01/main/boss/boss.hpp"
#include "th01/main/player/orb.hpp"
#include "th01/formats/bos.hpp"
#include "game/coords.hpp"

/// Entities
/// --------

// Slot count for unique .BOS files associated with CBossEntity instances.
// *Not* CBossEntity instances themselves!
#define BOS_ENTITY_SLOT_COUNT 4

// An individual entity rendered with sprites from a .BOS file. May or may not
// be animated, and may or may not have a hitbox for collision with the Orb.
class CBossEntity : public BOS {
public:
	screen_x_t cur_left;
	screen_y_t cur_top;
	screen_x_t prev_left;
	screen_y_t prev_top;
	LRTB<screen_x_t, screen_y_t> move_clamp; // Relative to VRAM
	LRTB<pixel_t, pixel_t> hitbox_orb; // Relative to [cur_left] and [cur_top]

protected:
	int bos_image;

public:
	uint8_t bos_slot;
	bool hitbox_orb_inactive;

	// Locks both movement and rendering via the locked_*() methods if nonzero.
	int lock_frame;

	// Loads all images from the .BOS file with the given [fn] inside the
	// currently active packfile into the given CBossEntity .BOS [slot], and
	// keeps the .BOS metadata in this CBossEntity instance. Always returns 0.
	int load(const char fn[PF_FN_LEN], int slot);

	// Copies the .BOS header data of [src] to this instance.
	void metadata_assign(const CBossEntity near &src) {
		bos_image_count = src.bos_image_count;
		bos_slot = src.bos_slot;
		h = src.h;
		vram_w = src.vram_w;
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
	// for each row, based at the entity's current position. Used for Elis'
	// entrance animation.
	// Calls put_1line() for each row, and clips the sprite accordingly.
	void wave_put(int image, int len, pixel_t amp, int phase) const;

	// Like wave_put(), but calls egc_copy_rect_1_to_0_16() for each line
	// instead.
	void wave_sloppy_unput(int len, pixel_t amp, int phase) const;
	/// --------

	/// Movement
	/// --------
protected:
	void move(const pixel_t &delta_x, const pixel_t &delta_y) {
		prev_left = cur_left;
		prev_top = cur_top;

		cur_left += delta_x;
		if(move_clamp.left > cur_left) {
			cur_left = move_clamp.left;
		}
		if(move_clamp.right < cur_left) {
			cur_left = move_clamp.right;
		}

		cur_top += delta_y;
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

	// Sets [cur_left], [cur_top], and the [move_clamp] area.
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
		screen_x_t move_clamp_left = PLAYFIELD_LEFT,
		screen_x_t move_clamp_right = (PLAYFIELD_RIGHT + SINGYOKU_W),
		screen_y_t move_clamp_top = PLAYFIELD_TOP,
		screen_y_t move_clamp_bottom = (PLAYFIELD_BOTTOM - SINGYOKU_H)
	);

	// (Just read the actual function code, it's impossible to summarize these
	// without spelling out every single line here. Most notably though, it
	// only actually moves or renders the entity if [lock_frame] is 0.)
	void locked_move_and_put_8(
		pixel_t delta_x, pixel_t delta_y, int lock_frames
	);
	void locked_move_unput_and_put_8(
		pixel_t delta_x, pixel_t delta_y, int lock_frames
	);

	// ZUN bug: The lock concept should really not apply to blitting. Only
	// unblitting and reblitting an entity every 3 frames allows other
	// overlapping sprites (i.e., bullets, player shots, or the Orb) to rip
	// holes into it as part of their respective unblitting calls during these
	// 3 frames. That's what causes the flickering during most of YuugenMagan's
	// attack phases. This method can only be interpreted as a desperate
	// attempt at improving performance, pointing out how much this game would
	// have benefitted from a proper sprite system.
	void locked_unput_and_put_8(void) {
		locked_move_unput_and_put_8(0, 0, 3);
	}

	void unlock_put_lock_8(void) {
		lock_frame = 0;
		locked_move_and_put_8(0, 0, 3);
	}

	void unlock_put_image_lock_8(int image) {
		lock_frame = 0;
		bos_image = image;
		locked_move_and_put_8(0, 0, 3);
	}

	void unlock_unput_put_image_lock_8(int image) {
		lock_frame = 0;
		bos_image = image;
		locked_unput_and_put_8();
	}
	/// --------

	/// Collision detection
	/// -------------------

	// Sets [hitbox_orb] to the given coordinates, relative to the top-left
	// corner of the image. The area corresponds to the one that the Orb's
	// centered hitbox has to fully overlap. Relative to the entity's sprite:
	//
	// 	                                [this->cur_top]
	// 	                 ┌──────────────────────────────────────────┐
	// 	                 │            Orb top                       │
	// 	                 │          ┌─────────┐                     │
	// 	                 │          │       [top]                   │
	// 	                 │ Orb left │ ╔═══════════════╗             │
	// 	                 │          │ ║               ║             │
	// 	                 │          └─║               ║ [right]     │
	// 	[this->cur_left] │            ║               ║             │
	// 	                 │     [left] ║               ║─┐           │
	// 	                 │            ║               ║ │           │
	// 	                 │            ╚═══════════════╝ │ Orb right │
	// 	                 │                 [bottom]     │           │
	// 	                 │                    └─────────┘           │
	// 	                 │                     Orb bottom           │
	// 	                 └──────────────────────────────────────────┘
	void hitbox_orb_set(
		pixel_t left, pixel_t top, pixel_t right, pixel_t bottom
	) {
		hitbox_orb.left = (left + ORB_HITBOX_W);
		hitbox_orb.right = (right - ORB_HITBOX_W);
		hitbox_orb.top = (top + ORB_HITBOX_H);
		hitbox_orb.bottom = (bottom - ORB_HITBOX_H);
	}

	void hitbox_orb_activate() {
		hitbox_orb_inactive = false;
	}

	void hitbox_orb_deactivate() {
		hitbox_orb_inactive = true;
	}

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
// we can't ever directly declare instances of this template without emitting
// another constructor for this class.)
template <pixel_t W, pixel_t H> struct CBossEntitySized : public CBossEntity {
	pixel_t w_static() const {
		return W;
	}

	pixel_t h_static() const {
		return H;
	}

	screen_x_t cur_center_x(void) const {
		return (cur_left + (W / 2));
	}

	screen_x_t cur_center_y(void) const {
		return (cur_top + (H / 2));
	}

	screen_x_t cur_right(void) const {
		return (cur_left + W);
	}
};

// Frees all images in the given [slot].
void bos_entity_free(int slot);

// ZUN bloat: The static initialization code in the original game proves that
// ZUN declared these as 5 individual variables rather than a single 5-element
// array. This fact explains why especially YuugenMagan and Elis ended up with
// highly redundant code. There are definitely better and cleaner ways of
// handling these entities.
extern CBossEntity boss_entity_0;
extern CBossEntity boss_entity_1;
extern CBossEntity boss_entity_2;
extern CBossEntity boss_entity_3;
extern CBossEntity boss_entity_4;
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
class CBossAnim : public BOS {
public:
	screen_x_t left;
	screen_y_t top;
	unsigned char bos_image;
	unsigned char bos_slot;

	// Loads all images from the .BOS file with the given [fn] inside the
	// currently active packfile into the given CBossAnim .BOS [slot], and
	// keeps the .BOS metadata in this CBossAnim instance. Always returns 0.
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
