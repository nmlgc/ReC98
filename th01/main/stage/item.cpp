extern "C" {
#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "th01/common.h"
#include "th01/resident.hpp"
#include "th01/v_colors.hpp"
#include "th01/math/clamp.hpp"
#include "th01/hardware/egc.h"
#include "th01/hardware/graph.h"
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
#include "th01/main/shape.hpp"
#include "th01/main/stage/item.hpp"
#include "th01/shiftjis/item.hpp"

/// Constants
/// ---------

static const pixel_t ITEM_W = PTN_W;
static const pixel_t ITEM_H = PTN_H;

// Assumes that [BOMB_COLLECT_1] and [BOMB_COLLECT_CAP] have the same length
// in bytes!
static const pixel_t BOMB_COLLECT_1_W = shiftjis_w(BOMB_COLLECT_1);

static const pixel_t BOMB_COLLECT_2_W = shiftjis_w(BOMB_COLLECT_2);

// TODO: Remove, once data can be emitted here
#undef BOMB_COLLECT_1
#undef BOMB_COLLECT_2
#undef BOMB_COLLECT_CAP
extern const unsigned char BOMB_COLLECT_1[];
extern const unsigned char BOMB_COLLECT_2[];
extern const unsigned char BOMB_COLLECT_CAP[];
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

/// Function types
/// --------------

// Called every frame to check collision between the player and an item in the
// given [slot]. Should set its [flag] to IF_COLLECTED or IF_COLLECTED_OVER_CAP
// if they did collide.
typedef void hittest_func_t(int slot);

// Called while an item slot's [flag] is ≥ IF_COLLECTED. Therefore, also
// responsible to eventually set a different flag.
typedef void collect_update_and_render_func_t(int slot);

// Called a single time if an uncollected item fell below the playfield, after
// its slot is reset to IF_FREE.
typedef void drop_func_t(void);
/// --------------

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

inline screen_x_t bomb_collect_2_left(item_t* slots, const int i) {
	// Line 2 is centered relative to line 1.
	enum {
		X_OFFSET = ((BOMB_COLLECT_2_W - BOMB_COLLECT_1_W) / 2)
	};
	return clamp_max_2(
		clamp_min_2((slots[i].left - X_OFFSET), PLAYFIELD_LEFT),
		(PLAYFIELD_RIGHT - BOMB_COLLECT_2_W)
	);
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

void items_bomb_reset(void)
{
	items_bomb[0].flag = IF_FREE;
	items_bomb[1].flag = IF_FREE;
	items_bomb[2].flag = IF_FREE;
	items_bomb[3].flag = IF_FREE;
}

void item_unput_update_render(
	int slot,
	char &flag,
	hittest_func_t &hittest,
	screen_x_t &left,
	screen_y_t &top,
	pixel_t &velocity_y,
	unsigned char &splash_radius,
	main_ptn_id_t ptn_id,
	collect_update_and_render_func_t &collect_update_and_render,
	drop_func_t &on_drop
)
{
	hittest(slot);

	if(flag == IF_SPLASH) {
		#define circle_x (left + (ITEM_W / 2))
		#define circle_y (top + (ITEM_H / 2))

		shape_circle_sloppy_unput(circle_x, circle_y, splash_radius, 0x08);
		splash_radius += 4;
		if(splash_radius >= 48) {
			flag = IF_FALL;
			return;
		}
		shape_circle_put(circle_x, circle_y, splash_radius, V_WHITE, 0x08);

		#undef circle_y
		#undef circle_x
	} else if(flag == IF_FALL) {
		ptn_unput_8(left, top, ptn_id);
		top += velocity_y;
		if(top >= (PLAYFIELD_BOTTOM - ITEM_H)) {
			velocity_y = -8;
			flag = IF_BOUNCE;
			goto bounce_update;
		}
		ptn_put_8(left, top, ptn_id);
	} else if(flag == IF_BOUNCE) {
		ptn_unput_8(left, top, ptn_id);

bounce_update:
		top += velocity_y;
		velocity_y++;
		if(top >= PLAYFIELD_BOTTOM) {
			flag = IF_FREE;
			on_drop();
			return;
		}
		ptn_put_8(left, top, ptn_id);
	} else if(flag >= IF_COLLECTED) {
		collect_update_and_render(slot);
	}
}

void bomb_collect_update_and_render(int slot)
{
	#define item items_bomb[slot]

	egc_copy_rect_1_to_0_16(item.left, item.top, BOMB_COLLECT_1_W, GLYPH_H);
	if(item.flag == IF_COLLECTED) {
		egc_copy_rect_1_to_0_16(
			bomb_collect_2_left(items_bomb, slot),
			(item.top + GLYPH_H),
			BOMB_COLLECT_2_W,
			GLYPH_H
		);
	}

	item.top += item.velocity_y;
	item.flag_state.collect_time--;
	if(item.flag_state.collect_time == 0) {
		item.flag = IF_FREE;
		return;
	}
	if(item.flag == IF_COLLECTED) {
		graph_putsa_fx(item.left, item.top, V_WHITE, BOMB_COLLECT_1);
		graph_putsa_fx(
			bomb_collect_2_left(items_bomb, slot),
			(item.top + GLYPH_H),
			V_WHITE,
			BOMB_COLLECT_2
		);
	} else /* item.flag == IF_COLLECTED_OVER_CAP */ {
		graph_putsa_fx(item.left, item.top, V_WHITE, BOMB_COLLECT_CAP);
	}

	#undef item
}

void bomb_drop(void)
{
}
