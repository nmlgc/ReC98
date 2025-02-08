/// Spark sprites
/// -------------

#include "th02/main/entity.hpp"
#include "th01/math/subpixel.hpp"

enum spark_render_as_t {
	SRA_DOT = 0, // 1×1-pixel dot
	SRA_SPRITE = 14, // Hardcoded 8×8-pixel spark sprite
};

struct spark_t {
	entity_flag_t flag;
	uint8_t age;

	// Stores the current and previous position, indexed with the currently
	// rendered VRAM page.
	SPPoint screen_topleft[2];

	SPPoint velocity;
	spark_render_as_t render_as;
	int8_t unused_1;

	// Defaults, initialized at the beginning of each stage
	// ----------------------------------------------------

	unsigned char angle;
	SubpixelLength8 speed_base;
	int8_t unused_2;
	spark_render_as_t default_render_as;
	// ----------------------------------------------------
};

static const unsigned int SPARK_COUNT = 64;

extern spark_t sparks[SPARK_COUNT];

// Index of the next spark_t instance within [sparks] to be set when adding a
// new spark, regardless of its [flag].
extern unsigned int spark_ring_i;

// Number of spark_t instances within [sparks] between two successive
// SRA_SPRITE instances. All others get initialized to SRA_DOT.
extern uint8_t spark_sprite_interval;

// Sparks are transitioned to F_REMOVE after their [age] reaches this value.
extern uint8_t spark_age_max;

// Added to the velocity of each active spark after its position was updated.
extern Subpixel spark_accel_x;

// Spawns [count] sparks at the given point, overwriting old sprites in case
// there aren't enough free slots. When spawning [as_sprite], the sparks form
// expand in a [count]-ring at [speed_base] from the given point; otherwise,
// they move at their initially seeded angle and speed with [speed_base] added.
// [top] can be within [0; (RES_Y * 2)[, and is wrapped into the regular VRAM
// range if necessary.
void pascal sparks_add(
	screen_x_t left,
	uscreen_y_t top,
	subpixel_t speed_base,
	int count,
	bool16 as_sprite
);

void sparks_update_and_render(void);
void sparks_invalidate(void);
