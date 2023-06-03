#pragma option -zPmain_01 -G

#include "platform.h"
#include "pc98.h"
#include "master.hpp"
#include "th01/rank.h"
#include "th01/math/subpixel.hpp"
#include "th02/common.h"
#include "th02/resident.hpp"
#include "th02/core/globals.hpp"
#include "th02/hardware/pages.hpp"
extern "C" {
#include "th02/snd/snd.h"
}
#include "th02/main/entity.hpp"
#include "th02/main/playfld.hpp"
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

extern const main_patnum_t ITEM_PATNUM[IT_COUNT];
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

#define p_left_ptr   	item_p_left_ptr
#define p_top_ptr    	item_p_top_ptr
#define p_left       	item_p_left
#define p_top        	item_p_top
#define drop_cycle   	item_drop_cycle
#define collect_skill	item_collect_skill
#define frames_unused	item_frames_unused

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
extern int32_t item_score_this_frame;
// -----

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
