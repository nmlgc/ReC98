#include "platform.h"
#include "pc98.h"
#include "th01/math/subpixel.hpp"
#include "th02/main/entity.hpp"
#include "th02/main/item/item.hpp"

// Constants
// ---------

static const pixel_t ITEM_W = 16;
static const pixel_t ITEM_H = 16;
// ---------

struct item_pos_t {
	screen_x_t screen_left;
	Subpixel screen_top;
};

struct item_t {
	entity_flag_t flag;
	item_type_t type;
	item_pos_t pos[2];
	Subpixel velocity_y;
	pixel_t velocity_x_during_bounce;
	int age; // unused
};

// State
// -----

extern item_t items[ITEM_COUNT];

#define p_topleft	item_p_topleft

extern struct {
	screen_x_t x;
	union {
		screen_y_t screen;
		vram_y_t vram;
	} y;
} p_topleft;
extern int32_t item_score_this_frame;
// -----
