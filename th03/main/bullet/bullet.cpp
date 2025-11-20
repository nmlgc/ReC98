#include "th03/main/bullet/bullet.hpp"
#include "th03/sprites/pellet.h"
#include "decomp.hpp"
#include <stddef.h>

enum bullet_flag_t {
	BF_FREE = 0,
	BF_PELLET = 1,
	BF_BULLET16 = 2,
	BF_PELLET_TRANSFER = 3,
	BF_PELLET_CLOUD = 4,
	BF_INVALID = 5,

	_bullet_flag_t_FORCE_UINT8 = 0xFF
};

struct bullet_trail_coords_t {
	PlayfieldSubpixel v[TRAIL_POINT_COUNT];
};

struct bullet_trail_t {
	bullet_trail_coords_t center_x;
	bullet_trail_coords_t center_y;
};

struct bullet_t {
	bullet_flag_t flag;
	uint8_t age;
	PlayfieldPoint center;

	// Target X position within the target playfield.
	PlayfieldSubpixel target_center_x_for_target_pid;

	// Target X position relative to the originating playfield. Once [center.x]
	// reaches this position, the bullet is replaced with a new [group_next] of
	// [BF_PELLET_CLOUD] bullets at ([target_center_x_for_target_pid], 2.0f) on
	// the other playfield. [speed_next] and [angle_next] is also factored into
	// the velocity of this new group.
	// Technically redundant with the above value, but ZUN didn't write
	// subpixel-supporting functions for conversions from screen to playfield
	// space, so...
	PlayfieldSubpixel target_center_x_for_origin_pid;

	SPPoint velocity;
	SubpixelLength8 speed_next;
	unsigned char angle_next;
	pid_t pid;
	bullet_group_t group_next;

	sprite16_offset_t sprite_offset;
	bullet_accel_type_t accel_type;

	// ZUN bloat: The game never sets this to `false`. A per-instance `bool`
	// seems quite wasteful for what's supposedly a debugging feature, since
	// [flag] already decides whether a bullet can or can not be collided with.
	bool is_collidable;

	// Cycles through all 16×16 cels if [flag] == [BF_BULLET16], ignored
	// otherwise.
	bool is_animated;

	// ZUN bloat: 3 bytes per instance is at least one too many. At the very
	// leas, the per-instance `bool` could have been replaced by assigning
	// a `nullptr` to [trail], but this could have also been an 8-bit index
	// into [bullet_trail_ring] with a zero value.
	bool has_trail;
	bullet_trail_t near *trail;
};

// State
// -----

extern bullet_t bullets[BULLET_COUNT];

extern bullet_trail_t bullet_trail_ring[TRAIL_RING_SIZE];

// Index of the next `bullet_trail_t` instance within [bullet_trail_ring] to be
// assigned to a bullet with trail sprites.
extern uint8_t bullet_trail_ring_i;
// -----

#pragma codeseg PELLET_PUT main_04
#pragma option -k-
#pragma warn -rch

void __fastcall near grcg_pellet_put(
	screen_x_t /* _AX */, size_t cel_offset, vram_y_t top
)
{
	#define left _AX
	#define _AX static_cast<int16_t>(_AX)

	_SI = left;

	// ZUN bloat: _DI = vram_offset_shift_fast((left & ~1), top)
	_AX = left;
	_AX >>= 4;
	asm { shl ax, 1 };
	top <<= 6;
	_AX += top;
	static_cast<uvram_y_t>(top) >>= 2;
	_AX += top;
	_DI = _AX;

	// ZUN bloat: `_SI = (FP_OFF(&sPELLET[cel][_SI % (PRESHIFT * 2)])`.
	static_assert(sizeof(sPELLET[0][0]) == 16);
	_SI &= ((PRESHIFT * 2) - 1);
	_SI <<= 4;
	_SI += FP_OFF(&sPELLET);
	_SI += cel_offset;

	// ZUN bloat: Since this is a signed comparison that will be `true` for all
	// negative numbers, this is *probably* supposed to defend against the
	// General Protection Fault that would arise when overflowing an unaligned
	// destination pointer of a 32-bit write? But even if ZUN wrote a much
	// clearer `< 0` comparison, the playfield border would still cover every
	// possible (partially) negative position. The smallest still visible
	/// pellet coordinate would be
	//
	// 	[left] = (((PLAYFIELD_BORDER - PELLET_W) + 1) = 9, and
	// 	[top] = (((PLAYFIELD_BORDER / 2) - PELLET_H) + 1) = 5,
	//
	// which translates to a VRAM offset of 404, far away from any danger of
	// overflowing. It would have made more sense to just clip any pellets
	// below that offset.
	if(_AX < 8) {
		goto narrow;
	}

	static_assert(sizeof(sPELLET[0][0][0]) == 4);
	static_assert(PELLET_VRAM_H == 4);
wide:
	MOVSD
	_DI += (ROW_SIZE - sizeof(dots32_t));
	MOVSD
	_DI += (ROW_SIZE - sizeof(dots32_t));
	MOVSD
	_DI += (ROW_SIZE - sizeof(dots32_t));
	MOVSD
	return;
	_asm { nop };

narrow:
	asm { movsw }
	_SI += (sizeof(pellet_dots_t) - 2);
	_DI += (ROW_SIZE - sizeof(dots16_t));
	asm { movsw }
	_SI += (sizeof(pellet_dots_t) - 2);
	_DI += (ROW_SIZE - sizeof(dots16_t));
	asm { movsw }
	_SI += (sizeof(pellet_dots_t) - 2);
	_DI += (ROW_SIZE - sizeof(dots16_t));
	asm { movsw }

	#undef _AX
	#undef left
}

#pragma option -k.
#pragma warn +rch
