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

static const int SPARK_COUNT = 64;

extern spark_t sparks[SPARK_COUNT];

// Index of the next spark_t instance within [sparks] to be set when adding a
// new spark, regardless of its [flag].
extern unsigned int spark_ring_i;

// Number of spark_t instances within [sparks] between two successive
// SRA_SPRITE instances. All others get initialized to SRA_DOT.
extern uint8_t spark_sprite_interval;

// Sparks are transitioned to F_REMOVE after their [age] reaches this value.
extern uint8_t spark_age_max;
