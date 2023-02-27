#include "x86real.h"
#include "platform/x86real/pc98/blitter.hpp"
#include "platform/x86real/pc98/egc.hpp"
#include "platform/x86real/pc98/grcg.hpp"
#include "th01/main/bullet/pellet.hpp"

/// Constants
/// ---------

// Can't declare these as `static const` variables, because that would break
// compile-time Subpixel arithmetic
#define PELLET_LEFT_MIN (PLAYFIELD_LEFT)
#define PELLET_LEFT_MAX (PLAYFIELD_RIGHT - PELLET_W)
#define PELLET_TOP_MIN (PLAYFIELD_TOP)
#define PELLET_TOP_MAX (PLAYFIELD_BOTTOM)

#define PELLET_BOUNCE_TOP_MIN (PLAYFIELD_TOP + ((PELLET_H / 4) * 3))

#define PELLET_VELOCITY_MAX to_sp(8.0f)

static const unsigned int PELLET_DESTROY_SCORE = 10;
static const int PELLET_DECAY_FRAMES = 20;
static const int PELLET_DECAY_CELS = 2;
static const int PELLET_DECAY_FRAMES_PER_CEL = (
	PELLET_DECAY_FRAMES / PELLET_DECAY_CELS
);
/// ---------

/// Globals
/// -------

CPellets Pellets;
Pellet near *p;
bool pellet_interlace = false;
unsigned int pellet_destroy_score_delta = 0;
#include "th01/sprites/pellet.csp"
/// -------

CPellets::CPellets(void)
{
	int i;

	p = iteration_start();
	for(i = 0; i < PELLET_COUNT; i++, p++) {
		p->moving = false;
	}

	alive_count = 0;
}

void vector2_to_player_from(
	screen_x_t x,
	screen_y_t y,
	subpixel_t &ret_x,
	subpixel_t &ret_y,
	subpixel_t length,
	unsigned char plus_angle
)
{
	plus_angle = iatan2(
		(player_center_y() - y), ((player_center_x() - (PELLET_W / 2)) - x)
	) + plus_angle;
	ret_x = polar_x(0, length, plus_angle);
	ret_y = polar_y(0, length, plus_angle);
}

// Sets the velocity for pellet #[i] in the given [group]. Returns true if
// this was the last pellet for this group.
bool group_velocity_set(
	Subpixel &ret_x,
	Subpixel &ret_y,
	pellet_group_t group,
	subpixel_t speed,
	int &i,
	screen_x_t pellet_left,
	screen_y_t pellet_top
)
{
	// Due to this default, invalid group values will lead to add_group()
	// repeatedly calling this function, until it completely filled the pellet
	// array with identical bullets, moving at the same velocity – which is not
	// initialized anywhere.
	// (Not really a ZUN bug until we can discover a game state where this can
	// actually happen.)
	bool done = false;
	unsigned char angle = 0x00;
	unsigned char spread_delta = 0x00;

	#define to_aim_or_not_to_aim() \
		if(group >= PG_AIMED_SPREADS) { \
			goto aim; \
		} \
		/* Static group; add a 90° angle, so that 0° points downwards */ \
		angle += 0x40; \
		goto no_aim;

	switch(group) {
	case PG_1:
		ret_y.v = speed;
		ret_x.set(0.0f);
		done = true;
		break;
	case PG_1_AIMED:
		vector2_between(
			pellet_left,
			pellet_top,
			(player_center_x() - PELLET_W),
			player_center_y(),
			ret_x.v,
			ret_y.v,
			speed
		);
		done = true;
		break;

	case PG_2_SPREAD_WIDE:
	case PG_2_SPREAD_WIDE_AIMED:	spread_delta = 0x08;	// fallthrough
	case PG_2_SPREAD_NARROW:
	case PG_2_SPREAD_NARROW_AIMED:
		/**/ if(i == 0) { angle = (+0x04 + spread_delta); }
		else if(i == 1) { angle = (-0x04 - spread_delta); done = true; }
		to_aim_or_not_to_aim();

	case PG_3_SPREAD_WIDE:
	case PG_3_SPREAD_WIDE_AIMED:	spread_delta = 0x05;	// fallthrough
	case PG_3_SPREAD_NARROW:
	case PG_3_SPREAD_NARROW_AIMED:
		/**/ if(i == 0) { angle =   0x00; }
		else if(i == 1) { angle = (+0x04 + spread_delta); }
		else if(i == 2) { angle = (-0x04 - spread_delta); done = true; }
		to_aim_or_not_to_aim();

	case PG_4_SPREAD_WIDE:
	case PG_4_SPREAD_WIDE_AIMED:	spread_delta = 0x04;	// fallthrough
	case PG_4_SPREAD_NARROW:
	case PG_4_SPREAD_NARROW_AIMED:
		/**/ if(i == 0) { angle = (+0x04 +  spread_delta); }
		else if(i == 1) { angle = (-0x04 -  spread_delta); }
		else if(i == 2) { angle = (+0x0C + (spread_delta * 3)); }
		else if(i == 3) { angle = (-0x0C - (spread_delta * 3)); done = true; }
		to_aim_or_not_to_aim();

	case PG_5_SPREAD_WIDE:
	case PG_5_SPREAD_WIDE_AIMED:	spread_delta = 0x04;	// fallthrough
	case PG_5_SPREAD_NARROW:
	case PG_5_SPREAD_NARROW_AIMED:
		/**/ if(i == 0) { angle =   0x00; }
		else if(i == 1) { angle = (+0x04 +  spread_delta); }
		else if(i == 2) { angle = (-0x04 -  spread_delta); }
		else if(i == 3) { angle = (+0x08 + (spread_delta * 2)); }
		else if(i == 4) { angle = (-0x08 - (spread_delta * 2)); done = true; }
		to_aim_or_not_to_aim();

	case PG_1_RANDOM_NARROW_AIMED:
		angle = ((rand() & 0x0F) - 0x07);
		done = true;
		goto aim;

	case PG_1_RANDOM_WIDE:
		angle = ((rand() & 0x3F) + 0x20);
		done = true;
		goto no_aim;

	aim:
		vector2_to_player_from(
			pellet_left, pellet_top, ret_x.v, ret_y.v, speed, angle
		);
		break;

	no_aim:
		vector2(ret_x.v, ret_y.v, speed, angle);
		break;
	}
	i++;
	return done;
}

inline subpixel_t base_speed_for_rank(void) {
	return
		(rank == RANK_EASY) ? to_sp(0.0f) :
		(rank == RANK_NORMAL) ? to_sp(0.375f) :
		(rank == RANK_HARD) ? to_sp(0.75f) :
		to_sp(1.125f);
}

#define speed_set(speed) \
	speed += base_speed_for_rank(); \
	/* Note that ((subpixel * pellet_speed_t) / pellet_speed_t) still gives a
	/* correct subpixel result. */ \
	speed += ((resident->pellet_speed * speed) / PELLET_SPEED_MULTIPLIER); \
	if(speed < to_sp(1.0f)) { \
		speed = to_sp(1.0f); \
	}

#define pellet_init(pellet, left, top, group, spawn_with_cloud) \
	pellet->decay_frame = 0; \
	pellet->cur_left.v = TO_SP(left); \
	pellet->cur_top.v = TO_SP(top); \
	pellet->cloud_left = left; \
	pellet->cloud_top = top; \
	if(spawn_with_cloud) { \
		pellet->cloud_frame = 1; \
	} else { \
		pellet->moving = true; \
	} \
	pellet->from_group = group;

void CPellets::add_group(
	screen_x_t left, screen_y_t top, pellet_group_t group, subpixel_t speed
)
{
	int i;
	int group_i = 0;
	int group_done;
	Subpixel vel_x;
	Subpixel vel_y;

	// Should be >=, but yeah, it's just an inconsequential oversight.
	if(alive_count > PELLET_COUNT) {
		return;
	}
	if(
		(left >= PLAYFIELD_RIGHT) ||
		(top < (PLAYFIELD_TOP - PELLET_H)) ||
		(left < (PLAYFIELD_LEFT - PELLET_W)) ||
		(top > PLAYFIELD_BOTTOM)
	) {
		return;
	}
	speed_set(speed);

	p = iteration_start();
	for(i = 0; i < PELLET_COUNT; i++, p++) {
		if(p->moving || p->cloud_frame) {
			continue;
		}
		pellet_init(p, left, top, group, spawn_with_cloud);
		p->prev_left.v = -1;
		alive_count++;
		group_done = group_velocity_set(
			vel_x, vel_y, group, speed, group_i, left, top
		);
		p->velocity.x.v = vel_x.v;
		p->velocity.y.v = vel_y.v;
		if(group_done) {
			return;
		}
	}
}

void CPellets::add_single(
	screen_x_t left,
	screen_y_t top,
	unsigned char angle,
	subpixel_t speed_base,
	pellet_motion_t motion_type,
	subpixel_t speed_for_motion_fixed,
	screen_x_t spin_center_x,
	screen_y_t spin_center_y
)
{
	int i;
	Subpixel vel_x;
	Subpixel vel_y;

	// Should be >=, but yeah, it's just an inconsequential oversight.
	if(alive_count > PELLET_COUNT) {
		return;
	}
	speed_set(speed_base);

	p = iteration_start();
	for(i = 0; i < PELLET_COUNT; i++, p++) {
		if(p->moving || p->cloud_frame) {
			continue;
		}
		pellet_init(p, left, top, PG_NONE, spawn_with_cloud);
		p->motion_type = motion_type;
		p->prev_left.v = -1;
		alive_count++;
		p->spin_center.x.v = TO_SP(spin_center_x);
		p->spin_center.y.v = TO_SP(spin_center_y);
		if(motion_type == PM_SPIN) {
			vector2(vel_x.v, vel_y.v, speed_for_motion_fixed, angle);
			p->spin_velocity.x.v = vel_x.v;
			p->spin_velocity.y.v = vel_y.v;
			p->angle = iatan2(
				(p->cur_top - p->spin_center.y),
				(p->cur_left - p->spin_center.x)
			);
		}
		vector2(vel_x.v, vel_y.v, speed_base, angle);
		p->speed.v = speed_for_motion_fixed;
		p->velocity.x.v = vel_x.v;
		p->velocity.y.v = vel_y.v;
		return;
	}
}

void CPellets::motion_type_apply_for_cur(void)
{
	Subpixel velocity_to_player_x;
	Subpixel velocity_to_player_y;

	switch(p->motion_type) {
	case PM_GRAVITY:
		p->velocity.y.v += p->speed.v;
		break;
	case PM_SLING_AIMED:
		if(p->sling_direction == PSD_NONE) {
			p->sling_direction = static_cast<pellet_sling_direction_t>(
				(rand() & 1) + PSD_CLOCKWISE
			);
		}
		if(p->sling_direction == PSD_CLOCKWISE) {
			vector2(p->velocity.x.v, p->velocity.y.v, p->speed.v, p->angle);
		} else /* PSD_COUNTERCLOCKWISE */ {
			vector2(p->velocity.y.v, p->velocity.x.v, p->speed.v, p->angle);
		}
		p->angle += PELLET_SLING_DELTA_ANGLE;
		if(p->angle > 0x100) {
			vector2_between(
				p->cur_left.to_pixel(),
				p->cur_top.to_pixel(),
				(player_center_x() - PELLET_W),
				player_center_y(),
				p->velocity.x.v,
				p->velocity.y.v,
				p->speed.v
			);
			p->from_group = PG_1_AIMED;
			p->angle = 0x00;
		}
		break;
	case PM_BOUNCE_FROM_TOP_THEN_GRAVITY:
		// ZUN landmine: Wow... Three of them in one single if() expression.
		// 1)
		// 2) Pellets are clipped at both the left (1) and the right (2)
		//    edge of the playfield at those exact same coordinates,
		//    *before* this code gets to run. Thus, they won't ever
		//    bounce from those two sides here.
		// 3) Comparing screen-space coordinates to subpixels. What's a
		//    type system? :zunpet:
		if(
			(p->cur_left.v <= PELLET_LEFT_MIN)
			|| (p->cur_left.to_pixel() >= to_sp(PELLET_LEFT_MAX))
			|| (p->cur_top.v <= to_sp(PELLET_BOUNCE_TOP_MIN))
		) {
			p->velocity.x.v = -p->velocity.x.v;
			p->velocity.y.set(0.0f);
			p->motion_type = PM_GRAVITY;
			// Nope, this doesn't help.
			if(p->cur_left.v <= to_sp(PELLET_LEFT_MIN)) {
				p->cur_left.set(PELLET_LEFT_MIN + 1.0f);
			}
			if(p->cur_left.v >= to_sp(PELLET_LEFT_MAX)) {
				p->cur_left.set(PELLET_LEFT_MAX - 1.0f);
			}
			if(p->cur_top.v <= to_sp(PELLET_TOP_MIN)) {
				p->cur_top.set(PELLET_TOP_MIN + 1.0f);
			}
		}
		break;
	case PM_FALL_STRAIGHT_FROM_TOP_THEN_REGULAR:
		if(p->cur_top.to_pixel() <= PELLET_BOUNCE_TOP_MIN) {
			p->velocity.x.set(0.0f);
			p->velocity.y.v = p->speed.v;
			p->motion_type = PM_REGULAR;
			if(p->cur_top.to_pixel() <= PLAYFIELD_TOP) {
				p->cur_top.set(PLAYFIELD_TOP + 1.0f);
			}
		}
		break;
	case PM_SPIN:
		p->cur_left.v = polar_x(
			p->spin_center.x.v, PELLET_SPIN_CIRCLE_RADIUS, p->angle
		);
		p->cur_top.v = polar_y(
			p->spin_center.y.v, PELLET_SPIN_CIRCLE_RADIUS, p->angle
		);
		p->spin_center.x.v += p->spin_velocity.x.v;
		p->spin_center.y.v += p->spin_velocity.y.v;
		p->velocity.set(0.0f, 0.0f);
		p->angle += PELLET_SPIN_DELTA_ANGLE;
		break;
	case PM_CHASE:
		vector2_between(
			p->cur_left.to_pixel(),
			p->cur_top.to_pixel(),
			(player_center_x() - PELLET_W),
			player_center_y(),
			velocity_to_player_x.v,
			velocity_to_player_y.v,
			p->speed.v
		);
		if(p->cur_top.v < PELLET_CHASE_TOP_MAX) {
			#define chase(cur, target) \
				(cur > target) ? to_sp(-0.0625f) : \
				(cur < target) ? to_sp( 0.0625f) : \
				to_sp(0.0f);
			p->velocity.x.v += chase(p->velocity.x.v, velocity_to_player_x.v);
			p->velocity.y.v += chase(p->velocity.y.v, velocity_to_player_y.v);
			#undef chase
		}
		break;
	}
}

inline bool overlaps_shot(
	screen_x_t pellet_left, screen_y_t pellet_top, int i
) {
	return overlap_xywh_xywh_lt_gt(
		pellet_left, pellet_top, PELLET_W, PELLET_H,
		Shots.left[i], Shots.top[i], SHOT_W, SHOT_H
	);
}

// Processes any collision between the currently iterated pellet, the Orb, or
// a deflecting player. (Regular, life-losing hit testing between pellets and
// the player is done elsewhere!)
void pellet_hittest_orb_and_deflect(Pellet near* p)
{
	if(p->decay_frame) {
		return;
	}

	const screen_x_t pellet_left = p->cur_left.to_pixel();
	const screen_y_t pellet_top = p->cur_top.to_pixel();

	if(overlap_xywh_xywh_lt_gt(
		pellet_left, pellet_top, (PELLET_W + 8), PELLET_H,
		orb_cur_left, orb_cur_top, ORB_W, ORB_H
	)) {
		p->velocity.y.v >>= 1;
		p->velocity.x.v >>= 1;
		p->decay_frame = 1;
		pellet_destroy_score_delta += PELLET_DESTROY_SCORE;
	} else if(player_deflecting && overlap_xywh_xywh_lt_gt(
		pellet_left,
		pellet_top,
		PELLET_W,
		PELLET_H,
		(player_left - PELLET_W),
		(player_top - (PELLET_H * 2)),
		(PLAYER_W + (PELLET_W * 2)),
		(PLAYER_H + (PELLET_H * 2))
	)) {
		char deflect_angle;
		if(p->cur_left.to_pixel() <= (player_left + 12)) {
			deflect_angle = 0x80;
		} else {
			deflect_angle = 0x00;
		}
		vector2(p->velocity.x.v, p->velocity.y.v, to_sp(8.0f), deflect_angle);
		if(!p->from_group) {
			p->motion_type = PM_REGULAR;
		}
	}
}

void CPellets::decay_tick_for_cur(void)
{
	p->decay_frame++;
	if(p->decay_frame > (PELLET_DECAY_FRAMES + 1)) {
		p->decay_frame = 0;
		p->moving = false;
		alive_count--;
	}
}

// Why, I don't even?!?
inline void p_sloppy_wide_unput() {
	egc_copy_rect_1_to_0_16_word_w(
		p->prev_left.to_pixel(), p->prev_top.to_pixel(), PELLET_W, PELLET_H
	);
}

inline void p_sloppy_wide_unput_at_cur_pos() {
	egc_copy_rect_1_to_0_16_word_w(
		p->cur_left.to_pixel(), p->cur_top.to_pixel(), PELLET_W, PELLET_H
	);
}

void CPellets::unput(void)
{
	if(alive_count == 0) {
		return;
	}
	EGCCopy egc;
	p = iteration_start();
	for(int i = 0; i < PELLET_COUNT; i++, p++) {
		if(!p->moving || (p->prev_left.v == -1)) {
			continue;
		}
		egc.rect_interpage(
			p->prev_left.to_pixel(), p->prev_top.to_pixel(), PELLET_W, PELLET_H,
			1
		);
	}
}

void CPellets::unput_update_render(void)
{
	int i;

	interlace_field ^= 1;

	clouds_unput_update_render();
	unput();

	p = iteration_start();
	for(i = 0; i < PELLET_COUNT; i++, p++) {
		if(!p->moving) {
			continue;
		}
		if(p->from_group == PG_NONE && p->motion_type) {
			motion_type_apply_for_cur();
		}
		if(p->velocity.y.v > PELLET_VELOCITY_MAX) {
			p->velocity.y.v = PELLET_VELOCITY_MAX;
		}
		if(p->velocity.x.v > PELLET_VELOCITY_MAX) {
			p->velocity.x.v = PELLET_VELOCITY_MAX;
		}
		p->cur_top.v += p->velocity.y.v;
		p->cur_left.v += p->velocity.x.v;

		// Shot<->Pellet hit testing
		if((p->decay_frame == 0) && Shots.hittest_pellet(
			p->cur_left.to_pixel(), p->cur_top.to_pixel()
		)) {
			p->decay_frame = 0;
			p->moving = false;
			alive_count--;
			p_sloppy_wide_unput();
		}

		// Clipping
		if(
			p->cur_top.v >= to_sp(PELLET_TOP_MAX) ||
			p->cur_top.v < to_sp(PELLET_TOP_MIN) ||
			p->cur_left.v >= to_sp(PELLET_LEFT_MAX) ||
			p->cur_left.v <= to_sp(PELLET_LEFT_MIN)
		) {
			p->moving = false;
			alive_count--;
			p->decay_frame = 0;
			p_sloppy_wide_unput();
		}
	}

	Shots.unput_update_render();

	GRCGStaticColor<V_WHITE> grcg(GC_RMW);

	p = iteration_start();
	for(i = 0; i < PELLET_COUNT; i++, p++) {
		if(!p->moving) {
			continue;
		}
		if(!pellet_interlace || (interlace_field == (i & 1))) {
			pellet_hittest_orb_and_deflect(p);
		}
		const screen_x_t screen_left = p->cur_left.to_pixel();
		const screen_y_t screen_top = p->cur_top.to_pixel();
		const Blitter __ds* b = blitter_init_clip_b(
			(screen_left >> BYTE_BITS),
			screen_top,
			sizeof(sPELLET[0][0][0]),
			PELLET_H
		);
		if(b && (p->decay_frame < PELLET_DECAY_FRAMES)) {
			const int cel = (
				(p->decay_frame + (PELLET_DECAY_FRAMES_PER_CEL - 1)) /
				PELLET_DECAY_FRAMES_PER_CEL
			);
			b->write(SEG_PLANE_B, &sPELLET[cel][screen_left & BYTE_MASK]);
		}
		p->prev_left.v = p->cur_left.v;
		p->prev_top.v = p->cur_top.v;
		if(p->decay_frame) {
			decay_tick_for_cur();
		} else if(hittest_player_for_cur()) {
			p_sloppy_wide_unput(); // Turns off the GRCG...
			grcg_setcolor_rmw(V_WHITE);

			p->moving = false;
			alive_count--;
			p->decay_frame = 0;
		}
	}
}

void CPellets::unput_and_reset(void)
{
	p = iteration_start();
	for(int i = 0; i < PELLET_COUNT; i++, p++) {
		if(!p->moving) {
			continue;
		}
		p_sloppy_wide_unput_at_cur_pos();
		p->decay_frame = 0;
		p->moving = false;
		p->cloud_frame = 0;
	}
	alive_count = 0;
}

void CPellets::decay(void)
{
	p = iteration_start();
	for(int i = 0; i < PELLET_COUNT; i++, p++) {
		if(!p->moving || p->decay_frame) {
			continue;
		}
		p->velocity.y.v /= 1.5f;
		p->velocity.x.v /= 1.5f;
		p->decay_frame = 1;
		pellet_destroy_score_delta += PELLET_DESTROY_SCORE;
	}
}

void CPellets::reset(void)
{
	p = iteration_start();
	for(int i = 0; i < PELLET_COUNT; i++, p++) {
		if(!p->moving) {
			continue;
		}
		p->moving = false;
		p->decay_frame = 0;
		p->cloud_frame = 0;
	}
	alive_count = 0;
}

bool CPellets::hittest_player_for_cur(void)
{
	if(player_invincible || p->decay_frame) {
		return false;
	}
	if(
		(p->cur_left.to_pixel() >= (player_left + 4)) &&
		(p->cur_left.to_pixel() <= (player_left + 20)) &&
		(p->cur_top.to_pixel() >= (player_top + (player_sliding * 8))) &&
		// Yup, <, not <= as in the overlap_point_le_ge() macro.
		(p->cur_top.to_pixel() < (player_top + PLAYER_H - PELLET_H))
	) {
		player_is_hit = true;
		return true;
	}
	return false;
}

void CPellets::clouds_unput_update_render(void)
{
	p = iteration_start();
	for(int i = 0; i < PELLET_COUNT; i++, p++) {
		if(p->cloud_frame == 0) {
			continue;
		}
		p->cloud_frame++;
		if(p->cloud_frame == 2) {
			pellet_cloud_put_8(p->cloud_left, p->cloud_top, V_WHITE, 0);
		} else if(p->cloud_frame == 5) {
			pellet_cloud_unput_8(p->cloud_left, p->cloud_top, 0);
		} else if(p->cloud_frame == 6) {
			pellet_cloud_put_8(p->cloud_left, p->cloud_top, V_WHITE, 1);
		} else if(p->cloud_frame == 9) {
			pellet_cloud_unput_8(p->cloud_left, p->cloud_top, 1);
			p->cloud_frame = 0;
			p->moving = true;
		}
	}
}
