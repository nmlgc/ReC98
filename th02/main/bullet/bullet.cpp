#include "th02/main/bullet/bullet.hpp"
#include "libs/master.lib/master.hpp"
#include "th01/rank.h"
#include "th02/resident.hpp"
#include "th02/core/globals.hpp"
#include "th02/main/entity.hpp"
#include "th02/main/spark.hpp"

// Conceptually identical to the same constants in TH04, but not worth their
// own header to avoid the duplication. (And indeed named "size type" so that
// the variants would abbreviate the same as they would for "spawn types"!)
enum bullet_size_type_t {
	BST_PELLET = 1,
	BST_BULLET16 = 2,
};

struct bullet_t {
	int8_t flag; // ACTUAL TYPE: entity_flag_t
	int8_t size_type; // ACTUAL TYPE: bullet_size_type_t

	// Stores the current and previous position, indexed with the currently
	// rendered VRAM page.
	SPPoint screen_topleft[2];

	SPPoint velocity;
	main_patnum_t patnum; // Only used with `BST_BULLET16`.

	// Only used with `BST_BULLET16`.
	bullet_group_or_special_motion_t group_or_special_motion;

	unsigned char angle;
	SubpixelLength8 speed;

	// ZUN bloat: There's a padding byte to store a second value...
	union {
		uint8_t special_frames;
		uint8_t turns_done;
		uint8_t v;
	} u1;
	int8_t padding;
};

// State
// -----

#define cur_left   	bullet_cur_left
#define cur_top    	bullet_cur_top
#define screen_left	bullet_screen_left
#define screen_top 	bullet_screen_top
#define stack      	bullet_stack

extern bullet_t bullets[BULLET_COUNT];

extern screen_x_t screen_left;
extern screen_y_t screen_top;
extern Subpixel8 rank_base_speed;
extern Subpixel near* cur_left;
extern Subpixel near* cur_top;

extern uint8_t rank_base_stack;
extern uint8_t stack;
// -----

void bullets_and_sparks_init(void)
{
	int i;

	if(!reduce_effects) {
		spark_sprite_interval = 1;
		spark_age_max = 48;
	} else {
		spark_sprite_interval = 7;
		spark_age_max = 24;
	}

	{
		bullet_t near *p = bullets;
		for(i = 0; i < BULLET_COUNT; i++, p++) {
			p->flag = F_FREE;
		}
	}
	{
		spark_t near *p = sparks;
		for(i = 0; i < SPARK_COUNT; i++, p++) {
			p->flag = F_FREE;
			p->angle = irand();
			p->speed_base.v = (irand() & (to_sp8(4.0f) - 1));
			if((spark_sprite_interval & i) == 0) {
				p->default_render_as = SRA_SPRITE;
			} else {
				p->default_render_as = SRA_DOT;
			}
		}
	}

	// Well, it corresponds to the earliest usage of the respective unions...
	// (The Stage 2 midboss uses BSM_CHASE, Meira uses BSM_BOUNCE_*, and
	// BSM_DRIFT_* remains unused until Marisa.)
	bullet_special.u1.chase_speed.set(0.0625f);
	bullet_special.u2.drift_speed.set(4.0f);
	bullet_special.u3.turns_max = 1;

	rank_base_speed.v = (
		(rank == RANK_EASY)    ? to_sp8(-0.625f) :
		(rank == RANK_NORMAL)  ? to_sp8( 0.0f) :
		(rank == RANK_HARD)    ? to_sp8( 0.0f) :
		(rank == RANK_LUNATIC) ? to_sp8(+0.75f) :
		to_sp8(0.0f)
	);
	rank_base_stack = 0;
	if((rank == RANK_HARD) || (rank == RANK_LUNATIC)) {
		rank_base_stack = 1;
	}
	stack = rank_base_stack;
}
