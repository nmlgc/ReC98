#include "th04/sprites/cels.h"

/// Game-specific group and spawn types
/// -----------------------------------
#if GAME == 5
# include "th05/main/bullet/types.h"
#else
# include "th04/main/bullet/types.h"
#endif
/// -----------------------------------

/// States and modes
/// ----------------
/// Everything here needs to be kept in sync with the ASM versions in
/// bullet.hpp!
static const int BMS_DECAY_FRAMES_PER_CEL = 4;
#define BSS_CLOUD_FRAMES (BULLET_CLOUD_CELS * 4)
#define BMS_DECAY_FRAMES (BULLET_DECAY_CELS * BMS_DECAY_FRAMES_PER_CEL)

// Regular bullets with a given speed below BMS_SLOWDOWN_THRESHOLD are set to
// BMS_SLOWDOWN. This fires them at BMS_SLOWDOWN_BASE_SPEED instead, and then
// gradually slows them down to their given speed over the next
// BMS_SLOWDOWN_FRAMES.
// • In TH04, this is not done for stacks.
#define BMS_SLOWDOWN_BASE_SPEED 4.5f
#define BMS_SLOWDOWN_THRESHOLD (BMS_SLOWDOWN_BASE_SPEED - 0.5f)
#define BMS_SLOWDOWN_FRAMES 32

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
	// Slows down from BMS_SLOWDOWN_BASE_SPEED to [final_speed]
	BMS_SLOWDOWN = 0,
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
};
/// ----------------

// Needs to be kept in sync with the ASM version in bullet.inc!
struct bullet_t {
	unsigned char flag;
	char age;
	PlayfieldMotion pos;
	unsigned char from_group; // unused
	int8_t unused;
	SubpixelLength8 speed_cur;
	unsigned char angle;
	bullet_spawn_state_t spawn_state;
	bullet_move_state_t move_state;
	bullet_special_motion_t special_motion;
	SubpixelLength8 speed_final;
	union {
		unsigned char slowdown_time;	// with BMS_SLOWDOWN
		unsigned char turn_count;	// with BMS_SPECIAL
	} ax;
	union {
		// Difference between [speed_final] and the BMS_SLOWDOWN_BASE_SPEED.
		// Always positive for BMS_SLOWDOWN bullets.
		unsigned char slowdown_speed_delta;	// with BMS_SLOWDOWN
		unsigned char turn_angle;	// with BMS_SPECIAL
	} dx;
	int patnum;

#if GAME == 5
	// Coordinates for BSM_STRAIGHT
	SPPoint origin;
	int distance;
#endif
};

#define PELLET_W 8
#define PELLET_H 8
#define BULLET16_W 16
#define BULLET16_H 16

// Symmetrical around the center point of each bullet, and treated in relation
// to a 1×1 "hitbox" around the player's center point.
static const subpixel_t BULLET_KILLBOX_W = TO_SP(8);
static const subpixel_t BULLET_KILLBOX_H = TO_SP(8);

#if GAME == 5
# define PELLET_COUNT 180
# define BULLET16_COUNT 220

// Returns the patnum for the directional or vector bullet sprite starting at
// [patnum_base] that shows the given [angle].
int pascal near bullet_patnum_for_angle(int patnum_base, unsigned char angle);
// Updates [bullet]'s patnum based on its current angle.
void pascal near bullet_update_patnum(bullet_t near *bullet);

// Turns every 4th bullet into a point item when zapping bullets.
extern bool bullet_zap_drop_point_items;
#else
# define PELLET_COUNT 240
# define BULLET16_COUNT 200

// Returns the offset for a directional bullet sprite that shows the given
// [angle].
unsigned char pascal near bullet_patnum_for_angle(unsigned char angle);
#endif

#define BULLET_COUNT (PELLET_COUNT + BULLET16_COUNT)

extern bullet_t bullets[BULLET_COUNT];
#define pellets (&bullets[0])
#define bullets16 (&bullets[PELLET_COUNT])

// Number of times a bouncing bullet can change its direction before it
// automatically turns into a BMS_REGULAR bullet. Global state, not set
// per-bullet!
extern unsigned char bullet_turn_count_max;

// Set to `true` to clear all on-screen bullets, giving out a semi-exponential
// bonus for all bullets that were alive on the first frame of activity.
// Lasts for BULLET_ZAP_FRAMES and resets to `false` afterwards.
extern union {
	bool active;
	unsigned char frames; // doubles as the animation timer
} bullet_zap;
static const int BULLET_ZAP_FRAMES_PER_CEL = 4;
// ZUN bug: Effectively 1 in TH05, see bullets_update() for the cause.
static const int BULLET_ZAP_FRAMES = (
	BULLET_ZAP_CELS * BULLET_ZAP_FRAMES_PER_CEL
);

// # of frames left during which all on-screen bullets should decay.
// Gives a constant point bonus for every bullet decayed during that time.
extern unsigned char bullet_clear_time;

/// Rendering
/// ---------
union pellet_render_t {
	struct {
		screen_x_t left;
		vram_y_t top;
	} top;
	struct {
		vram_offset_t vram_offset;
		uint16_t sprite_offset;
	} bottom;
};

#if (GAME == 5)
	// Separate render list for pellets during their delay cloud stage.
	extern int pellet_clouds_render_count;
	extern bullet_t near *pellet_clouds_render[PELLET_COUNT];
#endif

extern int pellets_render_count;
extern pellet_render_t pellets_render[PELLET_COUNT];

// Renders the top and bottom part of all pellets, as per [pellets_render] and
// [pellets_render_count]. Assumptions:
// • ES is already be set to the beginning of a VRAM segment
// • The GRCG is active, and set to the intended color
// • pellets_render_top() is called before pellets_render_bottom()
void near pellets_render_top();
void near pellets_render_bottom();
/// ---------

/// Template
/// --------
// Needs to be kept in sync with the ASM version in bullet.inc!
struct bullet_template_t {
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
#else
	PlayfieldPoint velocity;
	bullet_group_t group;
	unsigned char angle;
	SubpixelLength8 speed;
	unsigned char count;
	bullet_template_delta_t delta;
	uint8_t unused_1;
	bullet_special_motion_t special_motion;
	uint8_t unused_2;
#endif
};

extern bullet_template_t bullet_template;
// Separate from the template, for some reason?
extern unsigned char bullet_template_turn_angle;

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
// bullets (which receive a move state of BMS_SLOWDOWN or BMS_REGULAR) or
// "special" ones (which are BMS_SPECIAL).
#if (GAME == 5)
	void near bullets_add_regular(void);
	void near bullets_add_special(void);
#else
	// TH04 additionally uses pointless per-difficulty wrappers around these
	// spawn functions that don't actually do anything difficulty-specific.
	void pascal near bullets_add_regular_easy(void);
	void pascal near bullets_add_regular_normal(void);
	void pascal near bullets_add_regular_hard_lunatic(void);
	void pascal near bullets_add_special_easy(void);
	void pascal near bullets_add_special_normal(void);
	void pascal near bullets_add_special_hard_lunatic(void);

	// Set to the version of the wrapper functions above that match the
	// current difficulty.
	extern nearfunc_t_near bullets_add_regular;
	extern nearfunc_t_near bullets_add_special;
#endif

// Further wrappers around the spawn functions that bypass base [speed] tuning
// of the resulting bullets based on [playperf], and fire them at a constant
// speed instead.
void near bullets_add_regular_fixedspeed(void);
void near bullets_add_special_fixedspeed(void);
/// --------
