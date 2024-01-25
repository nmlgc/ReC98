#include "th04/main/player/shot.hpp"

// Shot types
#define ST_NORMAL 0
#define ST_HOMING 1
#define ST_MISSILE_LEFT 2
#define ST_MISSILE_RIGHT 3
#define ST_MISSILE_STRAIGHT 4

// Shot cycle bitflags
#define SC_1X 0x8 // Triggered 1× per cycle
#define SC_2X 0x2 // Triggered 2× per cycle
#define SC_3X 0x1 // Triggered 3× per cycle
#define SC_6X 0x4 // Triggered 6× per cycle

// Returns the current shot cycle, and prepares everything for more shots
// being added.
char near shot_cycle_init(void);

// Common per-iteration data for shot type control functions.
// (Yeah, code generation mandated additions to [i] to be wrapped into
// functions, so why not bundle all of the rather intricate shot handling
// stuff as well.)
struct ShotAddIterator {
	unsigned char angle;
	unsigned char i;

	ShotAddIterator(unsigned char count)
		: i(count) {
	}

	void add_secondary(unsigned char n) {
		i += n;
	}

	void set_random_angle(
		unsigned char min = -0x48, unsigned char max = -0x38
	) {
		angle = randring1_next8_and_ge_lt(min, max);
	}

	unsigned char next(void) {
		return i -= 1;
	}
};

#define shot_func_init( \
	shot, \
	sai, \
	cycle, \
	count, \
	primary_cycle, \
	secondary_cycle, \
	secondary_offset_expr \
) \
	Shot near *shot; \
	ShotAddIterator sai(count); \
	\
	cycle = shot_cycle_init(); \
	if((cycle & (primary_cycle | secondary_cycle)) == 0) { \
		return; \
	} \
	if(cycle & secondary_cycle) { \
		sai.secondary_offset_expr; \
	}

// We *really* want to fit those on a line...
#define OPT_L shot->from_option_l()
#define OPT_R shot->from_option_r()
#define MISSILE_L shot->type = ST_MISSILE_LEFT
#define MISSILE_R shot->type = ST_MISSILE_RIGHT
#define MISSILE_S shot->type = ST_MISSILE_STRAIGHT

#define VELOCITY_X(screen_x) shot->pos.velocity.x.set(screen_x);
#define VELOCITY_Y(screen_y) shot->pos.velocity.y.set(screen_y);

#define VELOCITY_XY(screen_x, screen_y) \
	VELOCITY_X(screen_x); \
	VELOCITY_Y(screen_y);

#define VELOCITY_YX(screen_y, screen_x) \
	VELOCITY_Y(screen_y); \
	VELOCITY_X(screen_x);
