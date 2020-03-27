/// Game-specific pattern and spawn types
/// -------------------------------------
#if GAME == 5
# include "th05/bullet/pattypes.h"
#else
# include "th04/bullet/pattypes.h"
#endif
/// -------------------------------------

/// States and modes
/// ----------------
#pragma option -b-

#define BSS_CLOUD_FRAMES (BULLET_CLOUD_CELS * 4)
#define BMS_DECAY_FRAMES (BULLET_DECAY_CELS * 4)
#define BMS_SLOWDOWN_BASE_SPEED 4.5f
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
};

enum bullet_move_state_t {
	/// Hitbox is active
	/// ----------------
	// Slows down from BMS_SLOWDOWN_BASE_SPEED to [final_speed]
	BMS_SLOWDOWN = 0,
	// Special processing according to [special_motion]
	BMS_SPECIAL = 1,
	// No special processing
	BMS_NORMAL = 2,
	/// ----------------

	/// Decay, no hitbox
	/// ----------------
	BMS_DECAY = 4,
	BMS_DECAY_END = (BMS_DECAY + BMS_DECAY_FRAMES),
	/// ----------------
};

enum bullet_special_motion_t {
};

#pragma option -b
/// ----------------

struct bullet_t {
	char flag;
	char age;
	motion_t pos;
	unsigned char from_pattern; // unused
	int8_t unused;
	SubpixelLength8 speed_cur;
	unsigned char angle;
	bullet_spawn_state_t spawn_state;
	bullet_move_state_t move_state;
	bullet_special_motion_t special_motion;
	unsigned char speed_final;
	union {
		unsigned char slowdown_time;	// with BMS_SLOWDOWN
		unsigned char turn_count;	// with BMS_SPECIAL
	} ax;
	union {
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

#if GAME == 5
# define PELLET_COUNT 180
# define BULLET16_COUNT 220

// Returns the patnum for the directional or vector bullet sprite starting at
// [patnum_base] that shows the given [angle].
int pascal near bullet_patnum_for_angle(int patnum_base, unsigned char angle);
// Updates [bullet]'s patnum based on its current angle.
void pascal near bullet_update_patnum(bullet_t near *bullet);

#else
# define PELLET_COUNT 240
# define BULLET16_COUNT 200

// Returns the offset for a directional bullet sprite that shows the given
// [angle].
int pascal near bullet_patnum_for_angle(unsigned char angle);
#endif

#define BULLET_COUNT (PELLET_COUNT + BULLET16_COUNT)

extern bullet_t bullets[BULLET_COUNT];
#define pellets (&bullets[0])
#define bullets16 (&bullets[PELLET_COUNT])

/// Rendering
/// ---------
union pellet_render_t {
	struct {
		int left;
		int top;
	} top;
	struct {
		uint16_t vram_offset;
		uint16_t sprite_offset;
	} bottom;
};

extern int pellets_alive;
extern pellet_render_t pellets_render[PELLET_COUNT];

// Renders the top and bottom part of all pellets, as per [pellets_render] and
// [pellets_alive]. Assumptions:
// • ES is already be set to the beginning of a VRAM segment
// • The GRCG is active, and set to the intended color
// • pellets_render_top() is called before pellets_render_bottom()
void near pellets_render_top();
void near pellets_render_bottom();
/// ---------

struct bullet_template_t {
	uint8_t spawn_type;
	unsigned char patnum;	// TH05: 0 = pellet
	SPPoint origin;
#if GAME == 5
	bullet_pattern_t pattern;
	bullet_special_motion_t special_motion;
	unsigned char spread;
	unsigned char spread_angle_delta;
	unsigned char stack;
	SubpixelLength8 stack_speed_delta;
	unsigned char angle;
	SubpixelLength8 speed;
#else
	SPPoint velocity;
	bullet_pattern_t pattern;
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
