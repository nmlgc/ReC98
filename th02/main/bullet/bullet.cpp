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
#include "th02/main/frames.hpp"
#include "th02/main/playperf.hpp"
#include "th02/main/spark.hpp"
#include "th02/main/player/bomb.hpp"
#include "th02/main/player/player.hpp"
#include "th01/sprites/pellet.h"
#include "th02/sprites/bullet16.h"

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

	// Due to this default, invalid group values will cause the spawn functions
	// to repeatedly call this function, until it completely filled the pellet
	// array with identical aimed bullets, moving at the same velocity.
	// (Not really a ZUN bug until we can discover a game state where this can
	// actually happen.)
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

bool16 pascal near bullet_clip(screen_x_t left, screen_y_t top)
{
	// ZUN quirk: Inconsistent for both 8×8 pellets and 16×16 bullets.
	if(
		(left < (PLAYFIELD_LEFT - PELLET_W)) ||
		(left > PLAYFIELD_RIGHT) ||
		(top < (PLAYFIELD_TOP - BULLET16_H)) ||
		(top > (PLAYFIELD_BOTTOM - 1))
	) {
		return true;
	}
	return false;
}

#pragma warn -rch
#pragma warn -ccc
#define stack_next(stack_i, group_i, speed) \
	/* Sneaky! That's how we can pretend this is an actual function that */ \
	/* returns a value. */ \
	stack_i >= bullet_stack) { \
		break; \
	} \
	speed >>= 1; \
	if(rank == RANK_LUNATIC) { \
		speed += to_sp(0.5f); \
	} \
	if(speed < SPEED_MIN) { \
		break; \
	} \
	stack_i++; \
	group_i = 0; \
	if(false

void pascal near bullets_add_pellet(
	screen_x_t left,
	screen_y_t top,
	unsigned char angle,
	uint8_t group,
	subpixel_t speed
)
{
	int group_i = 0;
	int stack_i = 0;
	if(bullet_clip(left, top) || bombing || bullet_speed_tune(speed)) {
		return;
	}

	// ZUN bloat: Could have been a single `for` loop.
	int slot_i = 0;
	do {
		while(slot_i < BULLET_COUNT) {
			if(bullets[slot_i].flag != F_FREE) {
				slot_i++;
				continue;
			}
			bullet_t near& p = bullets[slot_i];

			// Already scored as ZUN bloat in group_velocity_set().
			p.screen_topleft[page_back].x.v = left;
			p.screen_topleft[page_back].y.v = top;

			p.group_or_special_motion = BG_NONE;
			p.flag = F_ALIVE;
			p.size_type = BST_PELLET;
			p.u1.v = 0;
			p.angle = angle;

			slot_i++;
			if(group_velocity_set(group_i, group, p, speed)) {
				break;
			}
		}
		if(stack_next(stack_i, group_i, speed)) {
			break;
		}
	} while(1);
}

void pascal near bullets_add_16x16(
	screen_x_t left,
	screen_y_t top,
	unsigned char angle,
	bullet_group_or_special_motion_t group_or_special_motion,
	main_patnum_t patnum,
	subpixel_t speed
)
{
	int group_i = 0;
	int stack_i = 0;
	if(
		bullet_clip(left, top) ||
		bombing ||
		((group_or_special_motion != BSM_GRAVITY) && bullet_speed_tune(speed))
	) {
		return;
	}

	// ZUN bloat: Could have been a single `for` loop.
	int slot_i = 0;
	do {
		while(slot_i < BULLET_COUNT) {
			if(bullets[slot_i].flag != F_FREE) {
				slot_i++;
				continue;
			}
			bullet_t near& p = bullets[slot_i];
			p.group_or_special_motion = group_or_special_motion;
			p.size_type = BST_BULLET16;
			p.flag = F_ALIVE;
			p.patnum = patnum;
			p.u1.v = 0;
			p.speed.v = speed;
			p.angle = angle;
			slot_i++;
			if(group_or_special_motion < BG_SPECIAL_MOTIONS) {
				// Already scored as ZUN bloat in group_velocity_set().
				p.screen_topleft[page_back].x.v = left;
				p.screen_topleft[page_back].y.v = top;
				if(!group_velocity_set(
					group_i, group_or_special_motion, p, speed
				)) {
					continue;
				}
			} else {
				p.screen_topleft[page_back].x.v = TO_SP(left);
				p.screen_topleft[page_back].y.v = TO_SP(top);
				vector2(p.velocity.x.v, p.velocity.y.v, angle, speed);
			}
			break;
		}
		if(stack_next(stack_i, group_i, speed)) {
			break;
		}
	} while(1);
}

#pragma warn .rch
#pragma warn .ccc

// Calculates [bullet.velocity] for the special motion types.
void pascal near bullet_update_special(bullet_t near &bullet)
{
	const pixel_t bullet_top = cur_top->to_pixel();
	const pixel_t aim_y = (player_center_y() - 16);
	const pixel_t bullet_left = cur_left->to_pixel();
	const pixel_t aim_x = (player_center_x() - (BULLET16_W / 2));

	#define chase_player(bullet, bullet_left, bullet_top, x2, y2, speed) { \
		/**/ if(bullet_left < aim_x) { bullet.velocity.x.v += speed.v; } \
		else if(bullet_left > aim_x) { bullet.velocity.x.v -= speed.v; } \
		/**/ if(bullet_top  < aim_y) { bullet.velocity.y.v += speed.v; } \
		else if(bullet_top  > aim_y) { bullet.velocity.y.v -= speed.v; } \
	}

	switch(bullet.group_or_special_motion) {
	case BSM_CHASE:
		chase_player(
			bullet,
			bullet_left,
			bullet_top,
			aim_x,
			aim_y,
			bullet_special.u1.chase_speed
		);
		break;

	case BSM_HOMING:
		bullet.u1.special_frames++;
		if(bullet.u1.special_frames < bullet_special.u2.homing_duration) {
			vector2_between_plus(
				bullet_left,
				bullet_top,
				aim_x,
				aim_y,
				0x00,
				bullet.velocity.x.v,
				bullet.velocity.y.v,
				bullet.speed
			);
		} else {
			bullet.group_or_special_motion = BG_NONE;
		}
		break;

	case BSM_DECELERATE_THEN_TURN_AIMED:
		if((stage_frame & 7) != 0) {
			break;
		}
		bullet.velocity.x.v /= 2;
		bullet.velocity.y.v /= 2;
		if((bullet.velocity.x.v == 0) && (bullet.velocity.y.v == 0)) {
			vector2_between_plus(
				bullet_left,
				bullet_top,
				aim_x,
				aim_y,
				0x00,
				bullet.velocity.x.v,
				bullet.velocity.y.v,
				bullet.speed
			);
			bullet.u1.turns_done++;
			if(bullet.u1.turns_done >= bullet_special.u3.turns_max) {
				bullet.group_or_special_motion = BG_NONE;
			}
		}
		break;

	case BSM_GRAVITY:
		bullet.velocity.y.v += bullet_special.u1.gravity_speed.v;
		break;

	case BSM_DRIFT_ANGLE_AND_SPEED:
		bullet.angle += bullet_special.u1.drift_angle;
		bullet.speed.v += bullet_special.u2.drift_speed.v;
		vector2(
			bullet.velocity.x.v, bullet.velocity.y.v, bullet.angle, bullet.speed
		);
		bullet.u1.special_frames++;
		if(bullet.u1.special_frames > bullet_special.u3.drift_duration) {
			bullet.group_or_special_motion = BG_NONE;
		}
		break;

	case BSM_DRIFT_ANGLE_CHASE:
		bullet.angle += bullet_special.u1.drift_angle;
		vector2(
			bullet.velocity.x.v, bullet.velocity.y.v, bullet.angle, bullet.speed
		);
		chase_player(
			bullet,
			bullet_left,
			bullet_top,
			aim_x,
			aim_y,
			bullet_special.u2.drift_speed
		);
		bullet.u1.special_frames++;
		if(bullet.u1.special_frames > bullet_special.u3.drift_duration) {
			bullet.group_or_special_motion = BG_NONE;
		}
		break;

	case BSM_BOUNCE_LEFT_RIGHT_TOP_BOTTOM:
		if(
			(bullet_left < (PLAYFIELD_LEFT + BOUNCE_MARGIN)) ||
			(bullet_left > (PLAYFIELD_RIGHT - BULLET16_W - BOUNCE_MARGIN))
		) {
			bullet.velocity.x.v *= -1;
			bullet.u1.turns_done++;
		}
		// fallthrough

	case BSM_BOUNCE_TOP_BOTTOM:
		if(
			(bullet_top < (PLAYFIELD_TOP + BOUNCE_MARGIN)) ||
			(bullet_top > (PLAYFIELD_BOTTOM - BULLET16_H - BOUNCE_MARGIN))
		) {
			bullet.velocity.y.v *= -1;
			bullet.u1.turns_done++;
		}
		if(bullet.u1.turns_done > bullet_special.u3.turns_max) {
			bullet.group_or_special_motion = BG_NONE;
		}
		break;
	}
}
