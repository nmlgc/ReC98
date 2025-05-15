/// Everything here needs to be kept in sync with the ASM versions in
/// bullet.inc!

#include "th04/main/playfld.hpp"
#include "th04/main/rank.hpp"
#include "th04/sprites/cels.h"
#include "th02/main/entity.hpp"

extern "C" {

/// Game-specific group and spawn types
/// -----------------------------------

#if GAME == 5
#include "th05/main/bullet/types.h"
#else
#include "th04/main/bullet/types.h"
#endif
/// -----------------------------------

/// States and modes
/// ----------------

static const int BMS_DECAY_FRAMES_PER_CEL = 4;
#define BSS_CLOUD_FRAMES (BULLET_CLOUD_CELS * 4)
#define BMS_DECAY_FRAMES (BULLET_DECAY_CELS * BMS_DECAY_FRAMES_PER_CEL)

// Regular bullets with a given speed below BMS_DECELERATE_THRESHOLD are set to
// BMS_DECELERATE. This fires them at BMS_DECELERATE_BASE_SPEED instead, and
// then gradually slows them down to their given speed over the next
// BMS_DECELERATE_FRAMES.
// • In TH04, this is not done for stacks.
// • In TH05, this is not done for any group with BST_NO_DECELERATE set.
#define BMS_DECELERATE_BASE_SPEED 4.5f
#define BMS_DECELERATE_THRESHOLD (BMS_DECELERATE_BASE_SPEED - 0.5f)
#define BMS_DECELERATE_FRAMES 32

enum bullet_spawn_state_t {
	/// Hitbox is active
	/// ----------------

	BSS_GRAZEABLE = 0,
	BSS_GRAZED = 1,
	BSS_ACTIVE = 2,
	/// ----------------

	/// Delay "cloud", no hitbox
	/// ------------------------

	BSS_CLOUD_BACKWARDS = 3,
	BSS_CLOUD_FORWARDS = 4,
	BSS_CLOUD_END = (BSS_CLOUD_FORWARDS + BSS_CLOUD_FRAMES),
	/// ------------------------

	_bullet_spawn_state_t_FORCE_UINT8 = 0xFF
};

enum bullet_move_state_t {
	/// Hitbox is active
	/// ----------------

	// Slows down from BMS_DECELERATE_BASE_SPEED to [final_speed]
	BMS_DECELERATE = 0,
	// Special processing according to [special_motion]
	BMS_SPECIAL = 1,
	// No special processing
	BMS_REGULAR = 2,
	/// ----------------

	/// Decay, no hitbox
	/// ----------------

	BMS_DECAY = 4,
	BMS_DECAY_END = (BMS_DECAY + BMS_DECAY_FRAMES),
	/// ----------------

	_bullet_move_state_t_FORCE_UINT8 = 0xFF
};

enum bullet_special_motion_t {
	// This is so dumb.
	_bullet_special_motion_t_offset = static_cast<int8_t>((GAME - 5) * 0x81),

	// Slows down the bullet from its initial speed to 0, then aims to the
	// player and resets to its initial speed.
	// Affected by [bullet_special.turns_max].
	BSM_DECELERATE_THEN_TURN_AIMED,

	// Slows down the bullet from its initial speed to 0, then increases its
	// angle by [angle.turn_by] and resets to its initial speed.
	// Affected by [bullet_special.turns_max].
	BSM_DECELERATE_THEN_TURN,

	// Accelerates the speed of the bullet by [bullet_special.speed_delta]
	// every frame.
	BSM_SPEEDUP,

	// Slows down the bullet from its initial speed to 0 while turning it
	// towards [angle.target]. Upon reaching a speed of 0, the bullet
	// continues flying at that exact angle and resets to its initial speed.
	BSM_DECELERATE_TO_ANGLE,

	// Bounces the bullet into the opposite direction if it reaches the
	// respective edge of the playfield.
	// Affected by [bullet_special.turns_max].
	BSM_BOUNCE_LEFT_RIGHT,
	BSM_BOUNCE_TOP_BOTTOM,
	BSM_BOUNCE_LEFT_RIGHT_TOP_BOTTOM,
	BSM_BOUNCE_LEFT_RIGHT_TOP,

	// Accelerates the Y velocity of the bullet by [bullet_special.speed_delta]
	// every two frames.
	BSM_GRAVITY,

#if (GAME == 5)
	// Exact linear movement along a line; recalculates the bullet position
	// based on the origin, angle, and distance every frame. Useful if regular
	// incremental subpixel movement would introduce too much quantization
	// noise.
	BSM_EXACT_LINEAR,
#endif

	BSM_NONE = 0xFF,
};

union bullet_special_angle_t {
	unsigned char turn_by;
	char target;
	int8_t v;
};
/// ----------------

struct bullet_t {
	entity_flag_t flag;
	char age;
	PlayfieldMotion pos;
	unsigned char from_group; // ZUN bloat: Unused
	int8_t unused; // ZUN bloat
	SubpixelLength8 speed_cur;
	unsigned char angle;
	bullet_spawn_state_t spawn_state;
	bullet_move_state_t move_state;
	bullet_special_motion_t special_motion;
	SubpixelLength8 speed_final;
	union {
		unsigned char decelerate_time;	// with BMS_DECELERATE
		unsigned char turns_done;     	// with BMS_SPECIAL
	} u1;
	union {
		// Difference between [speed_final] and the BMS_DECELERATE_BASE_SPEED.
		// Always positive for BMS_DECELERATE bullets.
		SubpixelLength8 decelerate_speed_delta;	// with BMS_DECELERATE
		bullet_special_angle_t angle;          	// with BMS_SPECIAL
	} u2;
	int patnum;

#if GAME == 5
	// Coordinates for BSM_EXACT_LINEAR
	SPPoint origin;
	Subpixel distance;
#endif
};

// Symmetrical around the center point of each bullet, and treated in relation
// to a 1×1 "hitbox" around the player's center point.
static const subpixel_t BULLET_KILLBOX_W = TO_SP(8);
static const subpixel_t BULLET_KILLBOX_H = TO_SP(8);

// Must be at least `short` for optimization reasons.
static const unsigned short ANGLE_PER_SPRITE = (0x80 / BULLET_D_CELS);

#if GAME == 5
#define PELLET_COUNT 180
#define BULLET16_COUNT 220

// Returns the sprite ID of a directional or vector bullet sprite that
// represents the given [angle], relative to [patnum_base]. While the function
// is technically not restricted to `main_patnum_t` in TH05 and can also be
// used for a general (angle / BULLET_D_CELS) division, it still assumes
// [patnum_base] to be that type in order to distinguish vector bullets.
extern "C++" unsigned int pascal near bullet_patnum_for_angle(
	unsigned int patnum_base, unsigned char angle
);

// Turns every 4th bullet into a point item when zapping bullets.
extern bool bullet_zap_drop_point_items;
#else
#define PELLET_COUNT 240
#define BULLET16_COUNT 200

// Returns the offset for a directional bullet sprite that shows the given
// [angle].
unsigned char pascal near bullet_patnum_for_angle(unsigned char angle);
#endif

#define BULLET_COUNT (PELLET_COUNT + BULLET16_COUNT)

extern bullet_t bullets[BULLET_COUNT];
#define pellets (&bullets[0])
#define bullets16 (&bullets[PELLET_COUNT])

// Global parameters for special motion types.
extern union {
	// Number of times a bullet can change its direction during various special
	// motion types, before it changes back into a BMS_REGULAR bullet. A value
	// of 0 will still allow a single direction change.
	unsigned char turns_max;

	SubpixelLength8 speed_delta;
} bullet_special;

/// Template
/// --------

struct BulletTemplate {
	uint8_t spawn_type;
	unsigned char patnum;	// TH05: 0 = pellet
	PlayfieldPoint origin;
#if GAME == 5
	bullet_group_t group;
	bullet_special_motion_t special_motion;
	unsigned char spread;
	unsigned char spread_angle_delta;
	unsigned char stack;
	SubpixelLength8 stack_speed_delta;
	unsigned char angle;
	SubpixelLength8 speed;

private:
	// MODDERS: Just assign the values regularly, and don't rely on the
	// physical layout of the structure.
	void set16(unsigned char& val, uint8_t b0, uint8_t b1) {
		reinterpret_cast<uint16_t &>(val) = (b0 | (b1 << 8));
	}

	void set32(
		unsigned char& val, uint8_t b0, uint8_t b1, uint32_t b2, uint32_t b3
	) {
		reinterpret_cast<uint32_t &>(val) = (
			b0 | (b1 << 8) | (b2 << 16) | (b3 << 24)
		);
	}

	void set16_for_rank(
		unsigned char& val,
		uint8_t b0_e, uint8_t b1_e,
		uint8_t b0_n, uint8_t b1_n,
		uint8_t b0_h, uint8_t b1_h,
		uint8_t b0_l, uint8_t b1_l
	) {
		reinterpret_cast<uint16_t &>(val) = select_for_rank(
			(b0_e | (b1_e << 8)),
			(b0_n | (b1_n << 8)),
			(b0_h | (b1_h << 8)),
			(b0_l | (b1_l << 8))
		);
	}

public:
	void set_spread(unsigned char count, unsigned char angle_delta) {
		set16(spread, count, angle_delta);
	}

	void set_stack(unsigned char count, float speed_delta) {
		// MODDERS: Just assign the values regularly, and don't rely on the
		// physical layout of the structure.
		set16(stack, count, to_sp8(speed_delta));
	}

	void set_spread_stack(
		unsigned char spread, unsigned char spread_angle_delta,
		unsigned char stack, float stack_speed_delta
	) {
		set32(this->spread,
			spread, spread_angle_delta, stack, to_sp8(stack_speed_delta)
		);
	}

	void set_stack_for_rank(
		unsigned char count_easy, float speed_delta_easy,
		unsigned char count_normal, float speed_delta_normal,
		unsigned char count_hard, float speed_delta_hard,
		unsigned char count_lunatic, float speed_delta_lunatic
	) {
		set16_for_rank(stack,
			count_easy, to_sp8(speed_delta_easy),
			count_normal, to_sp8(speed_delta_normal),
			count_hard, to_sp8(speed_delta_hard),
			count_lunatic, to_sp8(speed_delta_lunatic)
		);
	}

	void set_spread_for_rank(
		unsigned char count_easy, unsigned char angle_delta_easy,
		unsigned char count_normal, unsigned char angle_delta_normal,
		unsigned char count_hard, unsigned char angle_delta_hard,
		unsigned char count_lunatic, unsigned char angle_delta_lunatic
	) {
		set16_for_rank(spread,
			count_easy, angle_delta_easy,
			count_normal, angle_delta_normal,
			count_hard, angle_delta_hard,
			count_lunatic, angle_delta_lunatic
		);
	}
#else
	PlayfieldPoint velocity;
	bullet_group_t group;
	unsigned char angle;
	SubpixelLength8 speed;
	unsigned char count;
	bullet_template_delta_t delta;
	uint8_t unused_1; // ZUN bloat
	bullet_special_motion_t special_motion;
	uint8_t unused_2; // ZUN bloat
#endif
};

extern BulletTemplate bullet_template;

// Separate from the template, for some reason?
extern bullet_special_angle_t bullet_template_special_angle;

// Modifies [bullet_template] based on [playperf] and the respective
// difficulty. These don't modify the base [speed]; that is done by the spawn
// functions themselves, unless overridden via the _fixedspeed() variants.
void pascal near bullet_template_tune_easy(void);
void pascal near bullet_template_tune_normal(void);
void pascal near bullet_template_tune_hard(void);
void pascal near bullet_template_tune_lunatic(void);

extern nearfunc_t_near bullet_template_tune;

// The actual functions for spawning bullets based on the [bullet_template].
// Both TH04 and TH05 pointlessly use separate functions for spawning "regular"
// bullets (which receive a move state of BMS_DECELERATE or BMS_REGULAR) or
// "special" ones (which are BMS_SPECIAL).
#if (GAME == 5)
void near bullets_add_regular(void);
void near bullets_add_special(void);

// Only used for the revenge bullets fired from Stage 3 Alice's barrier.
void far bullets_add_regular_far(void);
#else
// TH04 additionally uses pointless per-difficulty wrappers around these spawn
// functions that don't actually do anything difficulty-specific.
void pascal near bullets_add_regular_easy(void);
void pascal near bullets_add_regular_normal(void);
void pascal near bullets_add_regular_hard_lunatic(void);
void pascal near bullets_add_special_easy(void);
void pascal near bullets_add_special_normal(void);
void pascal near bullets_add_special_hard_lunatic(void);

// Set to the version of the wrapper functions above that match the current
// difficulty.
extern nearfunc_t_near bullets_add_regular;
extern nearfunc_t_near bullets_add_special;
#endif

// Further wrappers around the spawn functions that bypass base [speed] tuning
// of the resulting bullets based on [playperf], and fire them at a constant
// speed instead.
void near bullets_add_regular_fixedspeed(void);
void near bullets_add_special_fixedspeed(void);
/// --------

}

// ZUN bloat: Should be separate functions.
void near bullets_and_gather_invalidate(void);
