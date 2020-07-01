#include "th01/sprites/pellet.h"
#include "th01/math/subpixel.hpp"
#include "th01/math/vector.hpp"
#include "th01/main/bullet/pellet.hpp"
#include "th01/main/playfld.hpp"
#include "th01/main/player/player.hpp"

/// Constants
/// ---------
// Can't declare these as `static const` variables, because that would break
// compile-time Subpixel arithmetic
#define PELLET_LEFT_MIN (PLAYFIELD_LEFT)
#define PELLET_LEFT_MAX (PLAYFIELD_RIGHT - PELLET_W)
#define PELLET_TOP_MIN (PLAYFIELD_TOP)

#define PELLET_BOUNCE_TOP_MIN (PLAYFIELD_TOP + ((PELLET_H / 4) * 3))
/// ---------

/// Globals
/// -------
pellet_t near *pellet_cur;
/// -------

void CPellets::motion_type_apply_for_cur(void)
{
	#define p pellet_cur
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
				p->cur_left.to_screen(),
				p->cur_top.to_screen(),
				player_left + 8,
				player_center_y,
				p->velocity.x.v,
				p->velocity.y.v,
				p->speed.v
			);
			p->from_pattern = 12;
			p->angle = 0x00;
		}
		break;
	case PM_BOUNCE_FROM_TOP_THEN_GRAVITY:
		// Wow... Three ZUN bugs in one single if() expression.
		// 1)
		// 2) Pellets are clipped at both the left (1) and the right (2)
		//    edge of the playfield at those exact same coordinates,
		//    *before* this code gets to run. Thus, they won't ever
		//    bounce from those two sides here.
		// 3) Comparing screen-space coordinates to subpixels. What's a
		//    type system? :zunpet:
		if(
			(p->cur_left.v <= PELLET_LEFT_MIN)
			|| (p->cur_left.to_screen() >= to_sp(PELLET_LEFT_MAX))
			|| (p->cur_top.v <= to_sp(PELLET_BOUNCE_TOP_MIN))
		) {
			p->velocity.x.v = -p->velocity.x.v;
			p->velocity.y = 0.0f;
			p->motion_type = PM_GRAVITY;
			// Nope, this doesn't help.
			if(p->cur_left.v <= to_sp(PELLET_LEFT_MIN)) {
				p->cur_left = (PELLET_LEFT_MIN + 1.0f);
			}
			if(p->cur_left.v >= to_sp(PELLET_LEFT_MAX)) {
				p->cur_left = (PELLET_LEFT_MAX - 1.0f);
			}
			if(p->cur_top.v <= to_sp(PELLET_TOP_MIN)) {
				p->cur_top = (PELLET_TOP_MIN + 1.0f);
			}
		}
		break;
	case PM_FALL_STRAIGHT_FROM_TOP_THEN_NORMAL:
		if(p->cur_top.to_screen() <= PELLET_BOUNCE_TOP_MIN) {
			p->velocity.x = 0.0f;
			p->velocity.y.v = p->speed.v;
			p->motion_type = PM_NORMAL;
			if(p->cur_top.to_screen() <= PLAYFIELD_TOP) {
				p->cur_top = (PLAYFIELD_TOP + 1.0f);
			}
		}
		break;
	case PM_SPIN:
		#define to_spin_circle(coord) \
			((static_cast<long>(coord) * PELLET_SPIN_CIRCLE_RADIUS) >> 8)
		p->cur_left.v = (to_spin_circle(Cos8(p->angle)) + p->spin_center.x.v);
		p->cur_top.v = (to_spin_circle(Sin8(p->angle)) + p->spin_center.y.v);
		p->spin_center.x.v += p->spin_velocity.x.v;
		p->spin_center.y.v += p->spin_velocity.y.v;
		p->velocity.x = 0.0f;
		p->velocity.y = 0.0f;
		p->angle += PELLET_SPIN_DELTA_ANGLE;
		#undef to_spin_circle
		break;
	case PM_CHASE:
		vector2_between(
			p->cur_left.to_screen(),
			p->cur_top.to_screen(),
			player_left + 8,
			player_center_y,
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
	#undef p
}

void pellet_put(int left, int top, int cel)
{
	// Some `__asm` statements here look like they could be expressed using
	// register pseudovariables. However, TCC would then use a different
	// instruction than the one in ZUN's original binary.
	_ES = SEG_PLANE_B;

	_AX = (left >> 3);
	_DX = top;
	_DX <<= 6;
	__asm add	ax, dx;
	_DX >>= 2;
	__asm add	ax, dx;
	__asm mov	di, ax;

	_AX = (left & 7) << 4;
	_BX = cel;
	_BX <<= 7;
	__asm add	ax, bx;
	_AX += reinterpret_cast<uint16_t>(sPELLET);

	__asm mov	si, ax;
	_CX = PELLET_H;
	put_loop: {
		__asm movsw
		_DI += (ROW_SIZE - sizeof(dots16_t));
		if(static_cast<int16_t>(_DI) >= PLANE_SIZE) {
			return;
		}
	}
	__asm loop	put_loop;
}

void pellet_render(int left, int top, int cel)
{
	grcg_setcolor_rmw(7);
	pellet_put(left, top, cel);
	grcg_off();
}
