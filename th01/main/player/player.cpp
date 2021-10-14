/// Durations
/// ---------

#define SWING_FRAMES_PER_CEL 3
#define SWING_FRAMES 23
#define SHOTCOMBO_FRAMES_PER_CEL 6
/// ---------

/// .BOS sprite IDs
/// ---------------

#define SWING_CELS 8
#define FLIPKICK_CELS 6
#define SHOTCOMBO_CELS 4
static const int SLIDE_CELS = 2;

// miko_ac.bos
enum player_48x48_cel_t {
	C_SWING = 0,
	C_SWING_last = (C_SWING + SWING_CELS - 1),

	C_L_FLIPKICK,
	C_L_FLIPKICK_last = (C_L_FLIPKICK + FLIPKICK_CELS - 1),
	C_R_FLIPKICK,
	C_R_FLIPKICK_last = (C_R_FLIPKICK + FLIPKICK_CELS - 1),

	C_L_SHOTCOMBO,
	C_L_SHOTCOMBO_last = (C_L_SHOTCOMBO + SHOTCOMBO_CELS - 1),
	C_R_SHOTCOMBO,
	C_R_SHOTCOMBO_last = (C_R_SHOTCOMBO + SHOTCOMBO_CELS - 1),

	_player_48x48_cel_t_FORCE_INT16 = 0x7FFF
};

// miko_ac2.bos
enum player_48x32_cel_t {
	C_L_SLIDE,
	C_L_SLIDE_last = (C_L_SLIDE + SLIDE_CELS - 1),
	C_R_SLIDE,
	C_R_SLIDE_last = (C_R_SLIDE + SLIDE_CELS - 1),
	C_L_SLIDEKICK,
	C_R_SLIDEKICK,

	_player_48x32_cel_t_FORCE_INT16 = 0x7FFF
};
/// ---------------

/// Types
/// -----

enum mode_t {
	// Standing still or dashing left or right. Can switch into M_SHOOT
	// or M_SWING_OR_SLIDE.
	M_REGULAR = 0,

	// Regular shot while standing still or dashing. Quickly switches back
	// into M_REGULAR.
	M_SHOOT = 1,

	// Stationary swing, or sliding left or right. Not interruptible, but can
	// launch into a special attack combo in the end.
	M_SWING_OR_SLIDE = 2,

	// First, second, and third special attacks in a potential combo.
	M_SPECIAL_FIRST = 3,
	M_SPECIAL_SECOND = 4,
	M_SPECIAL_THIRD = 5,
};

enum submode_direction_t {
	SD_STATIONARY = INPUT_NONE,
	SD_LEFT = INPUT_LEFT,
	SD_RIGHT = INPUT_RIGHT,
	SD_NO_ORB_REPEL_THEN_STATIONARY_BUG = INPUT_LEFT_RIGHT,
};

enum submode_special_t {
	SS_FLIPKICK_MOVING = 0,
	SS_FLIPKICK_STATIONARY = 2,
	SS_SLIDEKICK = 4,
	SS_SHOTCOMBO = 6,

	_submode_special_t_FORCE_INT16 = 0x7FFF
};

enum x_direction_t {
	X_RIGHT = 0,
	X_LEFT = 1,
};

union submode_t {
	int8_t initial; // useless

	// During M_REGULAR, M_SHOOT, and M_SWING_OR_SLIDE. submode_direction_t.
	int8_t direction;

	// During M_SPECIAL_*. (submode_special_t | x_direction_t).
	int8_t special;
};
/// -----

/// Shared state
/// ------------

extern bool player_invincible_against_orb;
/// ------------

{
	extern int8_t mode; // mode_t
	extern int8_t dash_direction; // x_direction_t
	extern submode_t submode;
}
