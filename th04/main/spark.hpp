/// Spark sprites, as seen when killing enemies or grazing
/// ------------------------------------------------------
/// Everything here needs to be kept in sync with the ASM versions in
/// spark.inc!

#include "th04/main/playfld.hpp"
#include "th02/main/entity.hpp"

struct spark_t {
	entity_flag_t flag;
	unsigned char age;
	PlayfieldMotion center;
	// Set during sparks_init() and never again, and only involved in
	// determining the initial velocity in sparks_add_*(). Also has no reason
	// to be 16-bit.
	unsigned int angle;
};

static const int SPARK_COUNT = ((GAME == 5) ? 64 : 96);

// sparks_invalidate() and sparks_init() accidentally still this value in TH05.
#define SPARK_COUNT_BUG 96

extern spark_t sparks[SPARK_COUNT];

// Byte offset of the next spark_t instance to be looked at when adding a new
// spark. Relative to the beginning of [sparks].
extern uint16_t spark_ring_offset;

// Adds spark sprites at random distances between [radius_min] and
// ([radius_min] + 2.0f) away from ([center_x], [center_y]), using the random
// angles set in sparks_init(). Looks at the next [count] instances of [sparks]
// beginning at [spark_ring_offset], and only adds new sparks in slots that
// are currently free.
void pascal sparks_add_random(
	Subpixel center_x, Subpixel center_y, subpixel_t radius_min, int count
);

// Adds spark sprites along a [count]-point circle at the given [radius] away
// from ([center_x], [center_y]). Obviously ignores the random angle set in
// sparks_init(). Looks at the next [count] instances of [sparks] beginning at
// [spark_ring_offset], and only adds new sparks in slots that are currently
// free.
void pascal near sparks_add_circle(
	Subpixel center_x, Subpixel center_y, subpixel_t distance, int count
);

// Initializes all sparks with a random angle.
void near sparks_init(void);

void near sparks_update(void);
void near sparks_render(void);
void near sparks_invalidate(void);
