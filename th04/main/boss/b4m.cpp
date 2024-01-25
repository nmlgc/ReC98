/// Stage 4 Boss - Marisa
/// ---------------------

#include "platform.h"
#include "pc98.h"
#include "th01/math/subpixel.hpp"
#include "th04/math/motion.hpp"
extern "C" {
#include "th04/main/playfld.hpp"
}
#include "th04/main/phase.hpp"
#include "th04/main/boss/boss.hpp"

/// State
/// -----

#define flystep_pointreflected_frame boss_statebyte[13]
/// -----

// On [flystep_pointreflected_frame] 0, this function sets up [boss] movement
// towards the point reflection of Marisa's position across a fixed position
// near the top of the sealed moon in the background. The velocity is
// calculated to reach this exact point at [duration - 12], with Marisa braking
// on the last 12 frames by halving that velocity each frame. Every call to
// this function, including the one on frame 0, then applies this velocity to
// [boss].
// [duration] values <12 will move Marisa into the opposite direction instead.
// Returns `true` if the function was called for [duration] frames.
bool pascal near marisa_flystep_pointreflected(int duration)
{
	enum {
		POINT_X = TO_SP(PLAYFIELD_W / 2),
		POINT_Y = TO_SP((PLAYFIELD_H * 7) / 23),
		BRAKE_DURATION = 12,
	};
	if(flystep_pointreflected_frame == 0) {
		// Mod: Prevent the original function's division by zero by not moving
		// Marisa at all in that case.
		int frames_to_point = ((duration / 2) - (BRAKE_DURATION / 2));
		if(frames_to_point == 0) {
			return true;
		}
		boss.pos.velocity.x.v = ((POINT_X - boss.pos.cur.x) / frames_to_point);
		boss.pos.velocity.y.v = ((POINT_Y - boss.pos.cur.y) / frames_to_point);
		// The bytes we saved above, compared to the original binary
		_asm { nop; nop; nop; nop; nop; nop; nop; nop; }
	}
	flystep_pointreflected_frame++;
	if(flystep_pointreflected_frame >= (duration - BRAKE_DURATION)) {
		boss.pos.velocity.x.v /= 2;
		boss.pos.velocity.y.v /= 2;
	}
	if(flystep_pointreflected_frame >= duration) {
		return true;
	}
	boss.pos.update_seg3();
	return false;
}
