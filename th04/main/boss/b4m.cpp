/// Stage 4 Boss - Marisa
/// ---------------------

#pragma option -zCB4M_UPDATE_TEXT -zPmain_03

#include "th04/sprites/main_pat.h"
#include "th04/main/custom.hpp"
#include "th04/main/boss/boss.hpp"

// Constants
// ---------

static const pixel_t BIT_W = 32;
static const pixel_t BIT_H = 32;
static const int BIT_KILL_FRAMES_PER_CEL = 4;
// ---------

// Structures
// ----------

#define BIT_COUNT 4

enum bit_flag_t {
	BF_FREE = 0,
	BF_MOVEOUT_SPIN = 1,
	BF_SPIN = 2,
	BF_KILL_ANIM = 0x80,
	BF_KILL_ANIM_last = (
		BF_KILL_ANIM + (ENEMY_KILL_CELS * BIT_KILL_FRAMES_PER_CEL) - 1
	),

	_bit_flag_t_FORCE_UINT8 = 0xFF
};

struct bit_t {
	bit_flag_t flag;
	unsigned char angle;	// input for [center]
	PlayfieldPoint center;
	main_patnum_t patnum;
	/* ------------------------- */ int8_t unused_1[8];
	Subpixel distance;	// input for [center]
	Subpixel moveout_speed;
	int hp;
	int damage_this_frame;
	/* ------------------------- */ int8_t unused_2;
	char angle_speed;	// ACTUAL TYPE: unsigned char
};

#define bits (reinterpret_cast<bit_t *>(custom_entities))
// ----------

// State
// -----

#define flystep_pointreflected_frame boss_statebyte[13]

extern uint8_t bits_alive;

extern void (near pascal *near bit_fire)(bit_t near& bit);
extern screen_x_t bit_center_x[BIT_COUNT];
extern screen_x_t bit_center_y[BIT_COUNT];
// -----

// Game logic
// ----------

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
// ----------
