#include "platform.h"
#include "pc98.h"
#include "th01/math/subpixel.hpp"
#include "th02/main/entity.hpp"
#include "th02/main/item/item.hpp"

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

extern item_t items[ITEM_COUNT];
