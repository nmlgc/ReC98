#pragma option -zPmain_01 -G

#include "platform.h"
#include "libs/master.lib/pc98_gfx.hpp"
#include "th01/rank.h"
#include "th01/math/subpixel.hpp"
#include "th02/common.h"
#include "th02/resident.hpp"
#include "th02/math/randring.hpp"
#include "th02/core/globals.hpp"
#include "th02/hardware/pages.hpp"
#include "th02/snd/snd.h"
#include "th02/main/entity.hpp"
#include "th02/main/playfld.hpp"
#include "th02/main/playperf.hpp"
#include "th02/main/score.hpp"
#include "th02/main/scroll.hpp"
#include "th02/main/hud/hud.hpp"
#include "th02/main/item/item.hpp"
#include "th02/main/item/shared.hpp"
#include "th02/main/player/player.hpp"
#include "th02/main/pointnum/pointnum.hpp"
#include "th02/main/tile/tile.hpp"
#include "th02/sprites/main_pat.h"

// Constants
// ---------

static const pixel_t ITEM_W = 16;
static const pixel_t ITEM_H = 16;

#define SEMIRANDOM_RING	ITEM_SEMIRANDOM_RING

extern const item_type_t SEMIRANDOM_RING[10];
extern const main_patnum_t ITEM_PATNUM[IT_COUNT];

static const uint8_t SEMIRANDOM_RING_SIZE = (
	sizeof(SEMIRANDOM_RING) / sizeof(SEMIRANDOM_RING[0])
);
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

#define p_left_ptr       	item_p_left_ptr
#define p_top_ptr        	item_p_top_ptr
#define p_left           	item_p_left
#define p_top            	item_p_top
#define semirandom_ring_p	item_semirandom_ring_p
#define semirandom_cycle 	item_semirandom_cycle
#define drop_cycle       	item_drop_cycle
#define collect_skill    	item_collect_skill
#define frames_unused    	item_frames_unused

// ZUN bloat: Should have been local to items_update_and_render(), and been a
// single reference instead of two pointers.
extern screen_x_t near* p_left_ptr;
extern Subpixel near* p_top_ptr;

// ZUN bloat: Could have been local to items_update_and_render().
extern screen_x_t p_left;
extern union {
	screen_y_t screen;
	vram_y_t vram;
} p_top;
extern uint8_t semirandom_ring_p;
extern score_t item_score_this_frame;
// -----

void near items_init_and_reset(void)
{
	semirandom_ring_p = randring1_next8_ge_lt(0, (SEMIRANDOM_RING_SIZE - 2));
	for(int i = 0; i < ITEM_COUNT; i++) {
		items[i].flag = F_FREE;
	}
	point_items_collected = 0;
	pointnums_init_for_rank_and_reset();
	items_miss_add_gameover = false;
}

void pascal items_add_semirandom(screen_x_t left, screen_y_t top)
{
	if(item_bigpower_override) {
		item_bigpower_override--;
		items_add(left, top, IT_BIGPOWER);
		return;
	}

	extern uint8_t semirandom_cycle;
	if((semirandom_cycle++ % 3) != 0) {
		return;
	}

	if(randring1_next16_ge_lt(0, 512) == 18) {
		items_add(left, top, IT_BOMB);
	} else {
		items_add(left, top, SEMIRANDOM_RING[semirandom_ring_p]);
	}
	semirandom_ring_p++;
	if(semirandom_ring_p >= SEMIRANDOM_RING_SIZE) {
		semirandom_ring_p = 0;
	}
}

void pascal items_add(screen_x_t left, screen_y_t top, int type)
{
	if(item_bigpower_override && (type < IT_BOMB)) {
		item_bigpower_override--;
		type = IT_BIGPOWER;
	}

	item_t near* p = items;

	// ZUN bloat: Should be a separate variable.
	top <<= SUBPIXEL_BITS;
	#define top static_cast<subpixel_t>(top)

	if((lives == LIVES_MAX) && (type == IT_1UP)) {
		type = IT_BOMB;
	}
	for(int i = 0; i < ITEM_COUNT; (i++, p++)) {
		if(p->flag == F_FREE) {
			p->flag = F_ALIVE;
			p->type = static_cast<item_type_t>(type); // ZUN bloat
			p->pos[0].screen_left = left;
			p->pos[0].screen_top.v = top;
			p->pos[1].screen_left = left;
			p->pos[1].screen_top.v = top;
			p->velocity_y.set(-3.0f);
			p->velocity_x_during_bounce = 0;
			p->age = 0;
			break;
		}
	}

	#undef top
}

template <class T> struct hack {
	T x[ITEM_MISS_COUNT];
};

void pascal near items_miss_add(screen_x_t left, screen_y_t top)
{
	int items_added = 0;
	int i;
	bool16 bigpower_not_spawned_yet = true;

	// ZUN bloat: Just use a item_type_t.
	union {
		item_type_t type;
		int v;
	} type;

	extern const hack<Subpixel8> ITEM_MISS_VELOCITY_Y_SIDES;
	extern const hack<pixel_delta_8_t> ITEM_MISS_VELOCITY_X_CENTER;
	extern const hack<Subpixel8> ITEM_MISS_VELOCITY_Y_CENTER;

	const hack<Subpixel8> VELOCITY_Y_SIDES = ITEM_MISS_VELOCITY_Y_SIDES;
	const hack<pixel_delta_8_t> VELOCITY_X_CENTER = ITEM_MISS_VELOCITY_X_CENTER;
	const hack<Subpixel8> VELOCITY_Y_CENTER = ITEM_MISS_VELOCITY_Y_CENTER;

	// ZUN quirk: Probably meant to be ((PLAYFIELD_W / 3) * 1) and
	// ((PLAYFIELD_W / 3) * 2), but [player_topleft] is relative to the
	// top-left corner of the *screen*, not the playfield.
	int8_t field_distance_from_center = (
		(player_topleft.x <= (PLAYFIELD_LEFT + ((PLAYFIELD_W /  4) * 1))) ? -1 :
		(player_topleft.x <= (PLAYFIELD_LEFT + ((PLAYFIELD_W / 12) * 7))) ?  0 :
		/*                                                               */  1
	);

	item_t near* p = items;

	// ZUN bloat: Should be a separate variable.
	top <<= SUBPIXEL_BITS;
	#define top static_cast<subpixel_t>(top)

	for(i = 0; i < ITEM_COUNT; (i++, p++)) {
		if(p->flag != F_FREE) {
			continue;
		}
		p->flag = F_ALIVE;
		p->pos[0].screen_left = left;
		p->pos[0].screen_top.v = top;
		p->pos[1].screen_left = left;
		p->pos[1].screen_top.v = top;
		p->age = 0;

		if(!items_miss_add_gameover) {
			if(bigpower_not_spawned_yet) {
				type.v = (
					((randring1_next8() % (ITEM_MISS_COUNT - items_added)) == 0)
						? IT_BIGPOWER
						: (randring1_next8() % IT_BOMB) // Power or point
				);
			} else {
				type.v = (randring1_next8() % IT_BOMB); // Power or point
			}
			if(type.v == IT_BIGPOWER) {
				bigpower_not_spawned_yet = false;
			}
		} else {
			type.v = IT_BIGPOWER;
		}

		p->type = type.type;
		if(field_distance_from_center != 0) {
			p->velocity_y.v = VELOCITY_Y_SIDES.x[items_added];
			p->velocity_x_during_bounce = (field_distance_from_center * -2);
		} else {
			p->velocity_y.v = VELOCITY_Y_CENTER.x[items_added];
			p->velocity_x_during_bounce = VELOCITY_X_CENTER.x[items_added];
		}
		items_added++;
		if(items_added >= ITEM_MISS_COUNT) {
			break;
		}
	}

	#undef top
}

void near items_invalidate(void)
{
	for(int i = 0; i < ITEM_COUNT; i++) {
		if(items[i].flag == F_FREE) {
			continue;
		}

		item_pos_t near* pos = &items[i].pos[page_back];

		screen_y_t top = pos->screen_top.to_pixel();
		tiles_invalidate_rect(pos->screen_left, top, ITEM_W, ITEM_H);

		pos->screen_left = items[i].pos[page_front].screen_left;
		pos->screen_top  = items[i].pos[page_front].screen_top;

		if(items[i].flag == F_REMOVE) {
			items[i].flag = F_FREE;
		}
	}
	pointnums_invalidate();
}

// Returns `true` if the player collided with and collected the item.
bool16 pascal near item_hittest_y(item_t near& item)
{
	extern uint8_t collect_skill;
	screen_y_t top = p_top.screen;

	// Translation: The 16×16 bounding box of an item must fully lie within the
	// top 40 pixels of the player.
	if(
		(top >= player_topleft.y) && (top <= player_topleft.y + (PLAYER_H / 2))
	) {
		// ZUN bug: Not aligned to anything meaningful. Which would require the
		// on-screen width of the point number, and could never be expressed as
		// a constant.
		screen_x_t pointnum_left = (p_left - 12);

		switch(item.type) {
		case IT_POWER:
			if(power < POWER_MAX) {
				power++;
				player_shot_level_update_and_hud_power_put();
				power_overflow = 0;
				item_score_this_frame += 1;
			} else {
				if(power_overflow < POWER_OVERFLOW_MAX) {
					power_overflow++;
				}
				item_score_this_frame += POWER_OVERFLOW_BONUS[power_overflow];
				collect_skill++;
			}
			collect_skill++;
			pointnums_add(
				pointnum_left,
				p_top.screen,
				POWER_OVERFLOW_BONUS[power_overflow]
			);
			break;

		case IT_POINT: {
			uint16_t value;

			point_items_collected++;
			if(top <= (PLAYFIELD_TOP + 48)) {
				collect_skill += 8;
				value = 5120;
			} else {
				value = (2800 - (top * 7));
				if(value >= 2000) {
					collect_skill += 4;
				} else if(value >= 1000) {
					collect_skill += 2;
				} else {
					collect_skill++;
				}
			}
			pointnums_add(pointnum_left, p_top.screen, value);
			item_score_this_frame += value;
			break;
		}

		case IT_BOMB:
			if(bombs < BOMBS_MAX) {
				bombs++;
				item_score_this_frame += 1000;
				pointnums_add(pointnum_left, p_top.screen, 1000);
				hud_bombs_put();
			} else {
				item_score_this_frame += 6553;
				pointnums_add(pointnum_left, p_top.screen, 6553);
				collect_skill += 16;
			}
			break;

		case IT_BIGPOWER:
			if(power < (POWER_MAX - 10)) {
				power += 10;
				item_score_this_frame++;
				power_overflow = 0;
			} else {
				if(power_overflow < (POWER_OVERFLOW_MAX - 4)) {
					power_overflow += 5;
				} else {
					power_overflow = POWER_OVERFLOW_MAX;
				}
				power = POWER_MAX;
				item_score_this_frame += POWER_OVERFLOW_BONUS[power_overflow];
			}
			pointnums_add(
				pointnum_left,
				p_top.screen,
				POWER_OVERFLOW_BONUS[power_overflow]
			);
			player_shot_level_update_and_hud_power_put();
			break;

		case IT_1UP:
			// If this is `false`, items_add() has likely already turned this
			// into a bomb item. Makes sense to not do anything in that case.
			if(lives < LIVES_MAX) {
				lives++;
				hud_lives_put();
				snd_se_play(8);
			}
			break;
		}

		item.flag = F_REMOVE;
		snd_se_play(13);
		if(collect_skill >= 32) {
			item_skill++;
			collect_skill -= 32;
		}
		return true;
	}
	return false;
}

void near items_update_and_render(void)
{
	extern int frames_unused; // ZUN bloat
	extern uint8_t drop_cycle;

	item_t near* p = items;
	frames_unused++;
	item_score_this_frame = 0;

	for(int i = 0; i < ITEM_COUNT; (i++, p++)) {
		if(p->flag != F_ALIVE) {
			continue;
		}

		// Update
		// ------

		item_pos_t near& pos = p->pos[page_back];
		p_left_ptr = &pos.screen_left;
		p_top_ptr = &pos.screen_top;

		if(p->velocity_y <= 0) {
			*p_left_ptr += p->velocity_x_during_bounce;
		}
		p_top_ptr->v += p->velocity_y.v;

		p_left = *p_left_ptr;
		p_top.screen = p_top_ptr->to_pixel();

		if(p_top.screen < (PLAYFIELD_TOP - ITEM_H)) {
			// ZUN bloat: Could have been done prior to the assignment above.
			p_top.screen = (PLAYFIELD_TOP - ITEM_H);
			p_top_ptr->v = to_sp(PLAYFIELD_TOP - ITEM_H);
		} else if(p_top.screen >= PLAYFIELD_BOTTOM) {
			p->flag = F_REMOVE;
			drop_cycle++;
			if((drop_cycle & 0xF) == 0) {
				item_skill--;
			}
			continue;
		}

		if(
			(p_left <= (PLAYFIELD_LEFT - ITEM_W)) || (p_left >= PLAYFIELD_RIGHT)
		) {
			p->flag = F_REMOVE;
			continue;
		}

		p->age++;
		p->velocity_y.v += to_sp(0.0625f);

		// Translation: Player width plus 8 additional pixels to the left and
		// right.
		if(
			!player_is_hit &&
			(p_left >= (player_topleft.x - (PLAYER_W / 2) + (ITEM_W / 2))) &&
			(p_left <= (player_topleft.x + (PLAYER_W / 2) + (ITEM_W / 2)))
		) {
			if(item_hittest_y(*p)) {
				continue;
			}
		}
		// ------

		// Render
		// ------

		// ZUN bloat: Should have *definitely* been a distinct local variable.
		// The [vram] field is valid below.
		p_top.screen += scroll_line;

		if(p_top.vram >= RES_Y) {
			p_top.vram -= RES_Y;
		}
		super_roll_put_tiny(p_left, p_top.vram, ITEM_PATNUM[p->type]);
		// ------
	}

	if(item_score_this_frame) {
		if(rank >= RANK_HARD) {
			// Matches the operand set in pointnums_init_for_rank_and_reset().
			item_score_this_frame <<= (rank - RANK_NORMAL);
		}
		score_delta += item_score_this_frame;
	}
	pointnums_update_and_render();
}
