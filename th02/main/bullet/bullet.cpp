#pragma option -zPmain_03 -G

#include "th02/main/bullet/bullet.hpp"
#include "libs/master.lib/master.hpp"
#include "th01/rank.h"
#include "th02/resident.hpp"
#include "th02/core/globals.hpp"
#include "th02/math/vector.hpp"
#include "th02/math/randring.hpp"
#include "th02/hardware/pages.hpp"
#include "th02/main/entity.hpp"
#include "th02/main/playperf.hpp"
#include "th02/main/spark.hpp"
#include "th02/main/player/player.hpp"
#include "th01/sprites/pellet.h"

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

// Constants
// ---------

static const subpixel_t SPEED_MIN = TO_SP(1);
// ---------

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
extern int8_t easy_slow_skip_cycle;
// -----

#pragma option -a2

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

// Sets the velocity for bullet #[i] in the given [group]. Returns true if this
// was the last bullet for this group.
// Structurally very similar to the TH01 version.
bool16 pascal near group_velocity_set(
	int& i, int16_t group, bullet_t near& bullet, subpixel_t speed
)
{
	int16_t i_angle = 0;
	bool16 done = false;

	// ZUN bloat: Should take the pixel values as parameters instead of
	// repurposing the subpixel fields in the structure.
	// ZUN quirk: Then, it could have also taken the correct center position
	// for both 8×8 pellets and 16×16 bullets without assuming pellets here,
	// resulting in actually accurate vectors. (Not that it would help much,
	// given the fundamental inaccuracy of the underlying polar_*() functions.)
	// ZUN bloat: Also, these are only needed when aiming.
	const screen_y_t bullet_top = bullet.screen_topleft[page_back].y;
	const screen_y_t aim_y = (player_center_y() - (PELLET_H / 2));
	const screen_x_t aim_x = (player_center_x() - (PELLET_W / 2));
	const screen_x_t bullet_left = bullet.screen_topleft[page_back].x;

	// TH01 solved this more elegantly by moving all aimed groups past a
	// certain value...
	#define to_aim_or_not_to_aim(first_aimed) { \
		if(group <= (first_aimed - 1)) { /* ZUN bloat: `< first_aimed` */ \
			goto no_aim; \
		} \
		goto aim; \
	}

	#define ring(n) { \
		i_angle = (i * (0x100 / n)); \
		if(i >= (n - 1)) { \
			done = true; \
		} \
		goto no_aim; \
	}

	switch(group) {
	case BG_1_AIMED:
		done = true;
		goto aim;

	case BG_2_SPREAD_ULTRAWIDE_AIMED:	i_angle += 0x05; // fallthrough
	case BG_2_SPREAD_WIDE:
	case BG_2_SPREAD_WIDE_AIMED:	i_angle += 0x03; // fallthrough
	case BG_2_SPREAD_MEDIUM:
	case BG_2_SPREAD_MEDIUM_AIMED:	i_angle += 0x03; // fallthrough
	case BG_2_SPREAD_NARROW:
	case BG_2_SPREAD_NARROW_AIMED:
		/**/ if(i == 0) { i_angle = (+0x03 + i_angle); }
		else if(i == 1) { i_angle = (-0x03 - i_angle); done = true; }
		to_aim_or_not_to_aim(BG_2_SPREAD_NARROW_AIMED);

	case BG_3_SPREAD_WIDE:
	case BG_3_SPREAD_WIDE_AIMED:	i_angle += 0x08; // fallthrough
	case BG_3_SPREAD_MEDIUM:
	case BG_3_SPREAD_MEDIUM_AIMED:	i_angle += 0x08; // fallthrough
	case BG_3_SPREAD_NARROW:
	case BG_3_SPREAD_NARROW_AIMED:
		/**/ if(i == 0) { i_angle  =  0x00; }
		else if(i == 1) { i_angle = (+0x08 + i_angle); }
		else if(i == 2) { i_angle = (-0x08 - i_angle); done = true; }
		to_aim_or_not_to_aim(BG_3_SPREAD_NARROW_AIMED);

	case BG_4_SPREAD_WIDE:
	case BG_4_SPREAD_WIDE_AIMED:	i_angle += 0x06; // fallthrough
	case BG_4_SPREAD_MEDIUM:
	case BG_4_SPREAD_MEDIUM_AIMED:	i_angle += 0x06; // fallthrough
	case BG_4_SPREAD_NARROW:
	case BG_4_SPREAD_NARROW_AIMED:
		/**/ if(i == 0) { i_angle = (+0x03 +  i_angle); }
		else if(i == 1) { i_angle = (-0x03 -  i_angle); }
		else if(i == 2) { i_angle = (+0x09 + (i_angle * 3)); }
		else if(i == 3) { i_angle = (-0x09 - (i_angle * 3)); done = true; }
		to_aim_or_not_to_aim(BG_4_SPREAD_NARROW_AIMED);

	case BG_5_SPREAD_WIDE:
	case BG_5_SPREAD_WIDE_AIMED:	i_angle += 0x06; // fallthrough
	case BG_5_SPREAD_MEDIUM:
	case BG_5_SPREAD_MEDIUM_AIMED:	i_angle += 0x06; // fallthrough
	case BG_5_SPREAD_NARROW:
	case BG_5_SPREAD_NARROW_AIMED:
		/**/ if(i == 0) { i_angle  =  0x00; }
		else if(i == 1) { i_angle = (+0x06 +  i_angle); }
		else if(i == 2) { i_angle = (-0x06 -  i_angle); }
		else if(i == 3) { i_angle = (+0x0C + (i_angle * 2)); }
		else if(i == 4) { i_angle = (-0x0C - (i_angle * 2)); done = true; }
		to_aim_or_not_to_aim(BG_5_SPREAD_NARROW_AIMED);

	case BG_2_RING:
		// ZUN bloat: Could reuse the same ring code.
		if(i == 0) {
			i_angle = 0x00;
		} else {
			i_angle = 0x80;
			done = true;
		}
		goto no_aim;

	case BG_4_RING: 	ring(4);
	case BG_8_RING: 	ring(8);
	case BG_16_RING:	ring(16);
	case BG_32_RING:	ring(32);

	case BG_2_SPREAD_HORIZONTALLY_SYMMETRIC:
		if(i == 0) {
			i_angle = 0x00;
		} else {
			// ZUN bloat: `bullet.angle = 0x80 - bullet.angle;` would have been
			// clearer than using a multiplication to counteract the addition
			// below.
			i_angle = (0x80 - (bullet.angle * 2));
			done = true;
		}
		goto no_aim;

	case BG_1:
		done = true;
		goto no_aim;

	case BG_1_RANDOM_ANGLE:
		i_angle = randring2_next8();
		done = true;
		goto no_aim;

	case BG_RANDOM_ANGLE:
		i_angle = randring2_next8();
		if(i >= bullet.angle) {
			done = true;
		}
		goto no_aim;

	case BG_RANDOM_ANGLE_AND_SPEED:
		i_angle = randring2_next8();
		speed += randring2_next8_ge_lt_sp(0.0f, 2.0f);
		if(i >= bullet.angle) {
			done = true;
		}
		goto no_aim;

	default:
	aim:
		vector2_between_plus(
			bullet_left,
			bullet_top,
			aim_x,
			aim_y,
			(bullet.angle + i_angle),
			bullet.velocity.x.v,
			bullet.velocity.y.v,
			speed
		);
		break;

	no_aim:
		vector2(
			bullet.velocity.x.v,
			bullet.velocity.y.v,
			(bullet.angle + i_angle),
			speed
		);
	}

	i++;
	TO_SP_INPLACE(bullet.screen_topleft[page_back].x.v);
	TO_SP_INPLACE(bullet.screen_topleft[page_back].y.v);
	return done;
}

// Returns whether this bullet should be skipped.
bool16 pascal near bullet_speed_tune(subpixel_t& speed)
{
	// Makes more sense to express it as a scalar in relation to [playperf]
	// because "3.0f" too easily suggests that a [playperf] of -3 would zero
	// the speed (which it doesn't).
	speed += ((speed * playperf) / 48);

	speed += rank_base_speed;
	if(speed >= SPEED_MIN) {
		return false;
	}
	easy_slow_skip_cycle++;
	if((rank == RANK_EASY) && (easy_slow_skip_cycle & 1)) {
		return true;
	}
	speed = SPEED_MIN;
	return false;
}
