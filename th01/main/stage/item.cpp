extern "C" {
#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "th01/common.h"
#include "th01/math/clamp.hpp"
#include "th01/hardware/egc.h"
#include "th01/main/playfld.hpp"
#include "th01/formats/ptn.hpp"
#include "th01/formats/stagedat.hpp"
#include "th01/snd/mdrv2.h"
#include "th01/main/vars.hpp"
#include "th01/main/stage/stageobj.hpp"
#include "th01/main/player/player.hpp"
#include "th01/sprites/main_ptn.h"
}
#include "th01/main/hud/hud.hpp"
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

#define item_is_visible(item) ( \
	(item.flag > IF_SPLASH) && (item.flag < IF_COLLECTED) \
)

// Note that this hitbox is actually perfectly symmetrical around the
// player's center point, even though it might not look like it.
#define item_player_hittest(item) ( \
	(item.left > (player_left - (PLAYER_W - (ITEM_W / 4)))) && \
	(item.left < (player_left + (PLAYER_W - (ITEM_W / 4)))) && \
	(item.top  > (player_top  - (PLAYER_H - (ITEM_H / 4)))) && \
	item_is_visible(item) \
)

#define item_collect_init(item) { \
	item.velocity_y = -2; \
	item.flag_state.collect_time = 16; \
	item.top = clamp_max_2_ge(item.top, (PLAYFIELD_BOTTOM - ITEM_H)); \
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

void bomb_hittest(int slot)
{
	if(!item_player_hittest(items_bomb[slot])) {
		return;
	}
	ptn_sloppy_unput_16(items_bomb[slot].left, items_bomb[slot].top);

	item_collect_init(items_bomb[slot]);

	if(bombs < BOMBS_MAX) {
		bombs++;
		hud_bombs_put(bombs - 1);
		items_bomb[slot].flag = IF_COLLECTED;
	} else {
		score += 10000;
		hud_score_and_cardcombo_render();
		items_bomb[slot].flag = IF_COLLECTED_OVER_CAP;
	}
	mdrv2_se_play(15);
}

void items_bomb_render(void)
{
	for(int i = 0; i < ITEM_BOMB_COUNT; i++) {
		if(item_is_visible(items_bomb[i])) {
			ptn_put_8(items_bomb[i].left, items_bomb[i].top, PTN_ITEM_BOMB);
		}
	}
}

// Unused.
void items_bomb_unput(void)
{
	for(int i = 0; i < ITEM_BOMB_COUNT; i++) {
		if(item_is_visible(items_bomb[i])) {
			ptn_sloppy_unput_16(items_bomb[i].left, items_bomb[i].top);
		}
	}
}
