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

// Keep the jump target identical by moving this function below.
void pascal near divide_velocity_by_raw();

#define divide_velocity_by(divisor) { \
	_BX = divisor; \
	divide_velocity_by_raw(); \
}

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
		// Mod: Prevent the original function's division by zero by warping
		// Marisa directly to the target point on the first frame, and to the
		// reflected point on the second frame.

		// Size optimization; directly using the correct register for IDIV,
		// and performing all arithmetic directly on the register instead of
		// through AX.
		#define frames_to_point _BX

		frames_to_point = duration;
		frames_to_point >>= 1;
		frames_to_point -= (BRAKE_DURATION / 2);
		boss.pos.velocity.x.v = (POINT_X - boss.pos.cur.x);
		boss.pos.velocity.y.v = (POINT_Y - boss.pos.cur.y);
		if(frames_to_point != 0) {
			divide_velocity_by(frames_to_point);
		} else {
			// 2 frames of movement, followed by one frame of returning `true`
			// and no movement.
			flystep_pointreflected_frame = (BRAKE_DURATION - 3);
		}

		#undef frames_to_point
	}
	flystep_pointreflected_frame++;

	// No braking if we're in workaround mode.
	const int duration_without_braking = (duration - BRAKE_DURATION);
	if(
		(flystep_pointreflected_frame >= duration_without_braking) &&
		(duration_without_braking != 0)
	) {
		divide_velocity_by(2);
	}

	// Size optimization; `flystep_pointreflected_frame` is `unsigned char`
	// anyway.
	if(flystep_pointreflected_frame >= static_cast<unsigned char>(duration)) {
		return true;
	}
	boss.pos.update_seg3();
	return false;
}

#pragma option -k-

void pascal near divide_velocity_by_raw()
{
	boss.pos.velocity.x.v /= static_cast<int16_t>(_BX);
	boss.pos.velocity.y.v /= static_cast<int16_t>(_BX);
}

#pragma option -k.
