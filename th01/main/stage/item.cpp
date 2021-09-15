extern "C" {
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "th01/main/playfld.hpp"
#include "th01/formats/ptn.hpp"
#include "th01/formats/stagedat.hpp"
#include "th01/main/stage/stageobj.hpp"
}
#include "th01/main/stage/item.hpp"

/// Constants
/// ---------

static const pixel_t ITEM_W = PTN_W;
static const pixel_t ITEM_H = PTN_H;
/// ---------

/// Structures
/// ----------

enum item_flag_t {
	IF_FREE = 0,
	IF_SPLASH = 1,
	IF_FALL = 2,
	IF_BOUNCE = 3,
	IF_COLLECTED = 99,
	IF_COLLECTED_OVER_CAP = 100,

	_item_flag_t_FORCE_INT16 = 0x7FFF
};

union item_flag_state_t {
	unsigned char splash_radius;	// During IF_SPLASH. In pixels.
	unsigned char collect_time; 	// During ≥IF_COLLECTED.
};

struct item_t {
	// Also overloaded for the text popup shown when the item is collected.
	screen_x_t left;
	screen_y_t top;
	int16_t unknown_zero;
	pixel_t velocity_y;

	char flag; // item_flag_t
	item_flag_state_t flag_state;
};

static const int ITEM_BOMB_COUNT = 4;
static const int ITEM_POINT_COUNT = 10;

extern item_t items_bomb[ITEM_BOMB_COUNT];
extern item_t items_point[ITEM_POINT_COUNT];
/// ----------

/// Helper functions
/// ----------------

#define item_add(item, from_card_slot) { \
	item.flag = IF_SPLASH; \
	item.left = cards.left[from_card_slot]; \
	item.top = cards.top[from_card_slot]; \
	item.unknown_zero = 0; \
	item.velocity_y = 2; \
	item.flag_state.splash_radius = 4; \
}
/// ----------------

void items_bomb_add(int from_card_slot)
{
	for(int i = 0; i < ITEM_BOMB_COUNT; i++) {
		if(items_bomb[i].flag == IF_FREE) {
			item_add(items_bomb[i], from_card_slot);
			return;
		}
	}
}
