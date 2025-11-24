#pragma option -zPmain_04 -G

#include "th03/main/bullet/bullet.hpp"
#include "th03/main/player/cur.hpp"
#include "th03/main/player/stuff.hpp"
#include "th03/main/difficul.hpp"
#include "th03/main/hitbox.hpp"
#include "th03/math/randring.hpp"
#include "th03/math/vector.hpp"
#include "th03/sprites/pellet.h"
#include "th02/main/bullet/impl.hpp"
#include "th02/sprites/bullet16.h"
#include "decomp.hpp"
#include <stddef.h>

#pragma option -a2

// Constants
// ---------

// ZUN quirk: 16×16 bullets are clipped as soon as they are no longer visible.
// Reusing the same clipping coordinates for 8×8 pellets, however, means that
// these stay alive for slightly longer than you might expect.
inline void verify_bullet16_size(void) {
	static_assert(BULLET16_W == BULLET16_H);
}
static const playfield_subpixel_t CENTER_MIN = TO_SP(-(BULLET16_W / 2));
static const playfield_subpixel_t CENTER_X_MAX = TO_SP(
	PLAYFIELD_W + (BULLET16_W / 2)
);
static const playfield_subpixel_t CENTER_Y_MAX = TO_SP(
	PLAYFIELD_H + (BULLET16_H / 2)
);
// ---------

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

	// The `_next` fields are only read when spawning derived bullet groups via
	// bullets_add_next_from_p().
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

// ZUN bloat: group_velocity_set() should have just received a mutable
// reference to the bullet, like in TH02.
extern unsigned char bullet_group_i_angle;

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
#pragma codeseg

void bullets_reset(void)
{
	for(int i = 0; i < BULLET_COUNT; i++) {
		bullets[i].flag = BF_FREE;
	}
	bullet_trail_ring_i = 0;
}

bool16 pascal near group_velocity_set(int i)
{
	bool16 done;

	int16_t i_angle = 0;

	// ZUN bloat: A `PlayfieldPoint` has less duplication and better codegen.
	PlayfieldSubpixel aim_x;
	PlayfieldSubpixel aim_y;

	// Due to this default, invalid group values will cause the spawn functions
	// to repeatedly call this function, until it completely filled the pellet
	// array with identical aimed bullets, moving at the same velocity.
	// (Not really a ZUN bug until we can discover a game state where this can
	// actually happen.)
	done = false;

	uint8_t ring_remaining = 0;
	uint8_t ring_i_shift = 8;
	aim_x = players[bullet_template.pid].center.x;
	aim_y = players[bullet_template.pid].center.y;

	subpixel_length_8_t speed = bullet_template.speed;

	switch(bullet_template.group) {
	bullet_group_2_3_4_5_spreads_impl(i_angle, done, bullet_template.group, i);

	// ZUN bloat: Removing code duplication from the ring count, while adding
	// code duplication for the aimed case below...
	case BG_32_RING: ring_remaining = 16; ring_i_shift--;	// fallthrough
	case BG_16_RING: ring_remaining += 8; ring_i_shift--;	// fallthrough
	case BG_8_RING:  ring_remaining += 4; ring_i_shift--;	// fallthrough
	case BG_4_RING:  ring_remaining += 2; ring_i_shift--;	// fallthrough
	case BG_2_RING:
		ring_remaining += 1;
		ring_i_shift--;
		i_angle = (i << ring_i_shift);
		if(ring_remaining <= i) {
			done = true;
		}
		goto no_aim;

	case BG_RING:
		bullet_group_ring_impl(i_angle, done, i, bullet_template.count, no_aim);

	case BG_32_RING_AIMED: ring_remaining = 16; ring_i_shift--;	// fallthrough
	case BG_16_RING_AIMED: ring_remaining += 8; ring_i_shift--;	// fallthrough
	case BG_8_RING_AIMED:  ring_remaining += 4; ring_i_shift--;	// fallthrough
	case BG_4_RING_AIMED:  ring_remaining += 2; ring_i_shift--;	// fallthrough
	case BG_2_RING_AIMED:
		ring_remaining += 1;
		ring_i_shift--;
		i_angle = (i << ring_i_shift);
		if(ring_remaining <= i) {
			done = true;
		}
		goto aim;

	case BG_RING_AIMED:
		bullet_group_ring_impl(i_angle, done, i, bullet_template.count, aim);

	bullet_groups_shared_between_th02_and_th03_impl(
		i_angle,
		done,
		bullet_template.angle,
		i,
		bullet_template.count,
		randring2_next16
	);

	case BG_RANDOM_CONSTRAINED_ANGLE_AIMED:
		i_angle = randring2_next16_ge_lt(0x00, 0x20);
		i_angle -= 0x10;
		if(i >= bullet_template.count) {
			done = true;
		}
		goto aim;

	case BG_1_AIMED:
		done = true;
		goto aim;

	default:
	aim:
		vector2_between_plus(
			bullet_template.center.x,
			bullet_template.center.y,
			aim_x,
			aim_y,
			(i_angle + bullet_template.angle),
			bullet_template.velocity_tmp.x.v,
			bullet_template.velocity_tmp.y.v,
			speed
		);
		break;

	no_aim:
		vector2(
			bullet_template.velocity_tmp.x.v,
			bullet_template.velocity_tmp.y.v,
			(i_angle + bullet_template.angle),
			speed
		);
	}

	bullet_group_i_angle = (i_angle + bullet_template.angle);
	return done;
}

void bullets_add(void)
{
	bullet_t near *p;
	int trail_i;
	int bullet_i;
	int group_i = 0;
	union {
		PlayfieldSubpixel playfield;
		screen_x_t screen;
	} target_center_x;
	screen_x_t origin_center_x_screen;
	Subpixel speed;
	bool done;
	bool accel = false;
	uint8_t flag; // ACTUAL TYPE: bullet_flag_t

	if(
		(bullet_template.center.y.v <= CENTER_MIN) ||
		(bullet_template.center.y.v >= CENTER_Y_MAX) ||
		(bullet_template.center.x.v <= CENTER_MIN) ||
		(bullet_template.center.x.v >= CENTER_X_MAX)
	) {
		return;
	}

	p = bullets;
	switch(bullet_template.type) {
	case BT_PELLET_WITH_ACCEL:
		accel = true;
		flag = BF_PELLET;
		break;

	case BT_BULLET16_DEFAULT_WITH_ACCEL:
		accel = true;
		// fallthrough
	case BT_BULLET16_DEFAULT:
		bullet_template.sprite_offset = (pid.so_attack + SO_BULLET16);
		flag = BF_BULLET16;
		break;

	case BT_BULLET16_CUSTOM:
		flag = BF_BULLET16;
		break;

	case BT_BULLET16_CUSTOM_WITH_ACCEL:
		accel = true;
		flag = BF_BULLET16;
		break;

	default:
		static_assert(BT_PELLET == BF_PELLET);
		static_assert(BT_PELLET_TRANSFER == BF_PELLET_TRANSFER);
		static_assert(BT_PELLET_CLOUD == BF_PELLET_CLOUD);
		flag = bullet_template.type;
		break;
	}

	SubpixelLength8 speed_orig = bullet_template.speed;
	bullet_template.speed.v += bullet_base_speed.v;
	if(bullet_template.speed.v > to_sp8(8.0f)) {
		bullet_template.speed.v = to_sp8(8.0f);
	} else if(bullet_template.speed.v < to_sp8(1.0f)) {
		bullet_template.speed.v = to_sp8(1.0f);
	}

	for(bullet_i = 0; bullet_i < BULLET_COUNT; (bullet_i++, p++)) {
		if(p->flag != BF_FREE) {
			continue;
		}
		p->flag = static_cast<bullet_flag_t>(flag);
		p->age = 0;

		// ZUN bloat: A template structure would have been nice!
		p->center.x = bullet_template.center.x;
		p->center.y = bullet_template.center.y;
		p->group_next = bullet_template.group;
		p->pid = bullet_template.pid;
		p->sprite_offset = bullet_template.sprite_offset;
		p->is_animated = bullet_template.is_animated;
		p->is_collidable = bullet_template.is_collidable;
		p->has_trail = bullet_template.has_trail;

		if(bullet_template.has_trail) {
			p->trail = &bullet_trail_ring[bullet_trail_ring_i++];
			if(bullet_trail_ring_i >= TRAIL_RING_SIZE) {
				bullet_trail_ring_i = 0;
			}
			for(trail_i = 0; trail_i < TRAIL_POINT_COUNT; trail_i++) {
				p->trail->center_x.v[trail_i] = bullet_template.center.x;
				p->trail->center_y.v[trail_i] = bullet_template.center.y;
			}
		}

		if(accel) {
			p->accel_type = bullet_template.accel_type;
		} else {
			p->accel_type = BAT_NONE;
		}

		if(flag == BF_PELLET_TRANSFER) {
			origin_center_x_screen = playfield_fg_x_to_screen(
				bullet_template.center.x, bullet_template.pid
			);

			// ZUN bloat: Directly assigning [p->target_center_x_for_target_pid]
			// would have reduced [target_center_x] from a `union` to the
			// single screen-space value calculated below.
			target_center_x.playfield.v = randring2_next16_mod_ge_lt_sp(
				0, PLAYFIELD_W
			);
			p->target_center_x_for_target_pid.v = target_center_x.playfield.v;

			// ZUN quirk: Using a pixel-space function loses subpixel precision
			// for the following angle calculation, as well as for the target
			// check in the update function.
			static_assert(PLAYER_COUNT == 2);
			target_center_x.screen = playfield_fg_x_to_screen(
				target_center_x.playfield.v, (1 - bullet_template.pid)
			);

			speed.v = (to_sp(4.375f) + (round_speed / 3));

			// Assumes that Y coordinates don't change between playfields.
			vector2_between_plus(
				TO_SP(origin_center_x_screen),
				p->center.y,
				TO_SP(target_center_x.screen),
				randring2_next16_ge_lt_sp(0.0f, 16.0f),
				0,
				p->velocity.x.v,
				p->velocity.y.v,
				speed
			);
			p->target_center_x_for_origin_pid.v = screen_x_to_playfield(
				target_center_x.screen, bullet_template.pid
			);
			p->angle_next = bullet_template.angle;
			p->speed_next = bullet_template.speed;
			break;
		} else {
			done = group_velocity_set(group_i);
			p->velocity.x = bullet_template.velocity_tmp.x;
			p->velocity.y = bullet_template.velocity_tmp.y;
			p->angle_next = bullet_group_i_angle;
			p->speed_next = bullet_template.speed;
			if(flag == BF_PELLET_CLOUD) {
				p->sprite_offset = SO_PELLET_CLOUD;
			}
			if(done) {
				break;
			}
			group_i++;
		}
	}

	bullet_template.speed = speed_orig;
}

void bullets_add_transfer_pellet(void)
{
	bullet_template.type = BT_PELLET_TRANSFER;
	bullets_add();
}

void bullet_template_reset_stuff(void)
{
	bullet_template.angle = 0x00;
	bullet_template.count = 0;
	bullet_template.is_animated = true;
	bullet_template.is_collidable = true;
	bullet_template.has_trail = false;
}

// ZUN bloat: Why not just pass an actual `bullet_trail_coords_t *` instance?!
#define p reinterpret_cast<bullet_t near *>(_SI)

// ZUN bloat: Both of these could have been passed as `__fastcall` parameters.
#define coord_prev static_cast<playfield_subpixel_t>(_CX)
extern PlayfieldSubpixel coord_max;

// ZUN bloat: Also, did this *really* have to assign its return value to the
// carry flag?
void __fastcall near bullet_trail_update_and_clip(
	int16_t, int16_t, bullet_trail_coords_t near *coords
)
{
	#define tmp static_cast<playfield_subpixel_t>(_DX)

	reinterpret_cast<uint8_t near *>(coords) += FP_OFF(p->trail);
	coords->v[5].v = tmp = coords->v[4];
	if((tmp > CENTER_MIN) && (tmp < coord_max.v)) {
		coords->v[4].v = coords->v[3].v;
		coords->v[3].v = coords->v[2].v;
		coords->v[2].v = coords->v[1].v;
		coords->v[1].v = coords->v[0].v;
		coords->v[0].v = coord_prev;
		asm { clc }
		return;
	}
	asm { stc }

	#undef tmp
}

// ZUN bloat: Ironically, both call sites mutate [p] before calling this
// function, and then remove [p]. Why not just mutate the template directly
// then? Instead, we get this function that only sets half of the template and
// is hard to name as a result.
void near bullets_add_next_from_p(void)
{
	static_assert(BF_PELLET_TRANSFER == BT_PELLET_TRANSFER);
	static_assert(BF_PELLET_CLOUD == BT_PELLET_CLOUD);
	bullet_template.type = static_cast<bullet_type_t>(p->flag);

	// ZUN bloat: Assigning the entire `PlayfieldPoint` generates better code.
	bullet_template.center.x = p->center.x;
	bullet_template.center.y = p->center.y;

	// ZUN landmine: These copies of [speed], [angle], [pid], and [group] will
	// break once the structure layout changes. I won't define stuttery "speed
	// and angle" and "PID and group" structures and mess up the rest of the
	// code just to have well-defined assignments here.
	// For searchability:
	// 	bullet_template.speed = p->speed_next;
	// 	bullet_template.angle = p->angle_next;
	// 	bullet_template.group = p->group_next;
	// 	bullet_template.pid = p->pid;
	#define template_offset(field) offsetof(bullet_template_t, field)
	#define instance_offset(field) offsetof(bullet_t, field)
	static_assert(
		(template_offset(angle) - template_offset(speed)) ==
		(instance_offset(angle_next) - instance_offset(speed_next))
	);
	*reinterpret_cast<uint16_t *>(&bullet_template.speed) = (
		*reinterpret_cast<uint16_t *>(&p->speed_next)
	);
	static_assert(
		(template_offset(group) - template_offset(pid)) ==
		(instance_offset(group_next) - instance_offset(pid))
	);
	*reinterpret_cast<uint16_t *>(&bullet_template.pid) = (
		*reinterpret_cast<uint16_t *>(&p->pid)
	);
	#undef instance_offset
	#undef template_offset

	bullets_add();
}

void near bullet_update_velocity_y(void)
{
	// ZUN bloat: Reserving a register across functions, and then assigning
	// another one...
	#define p_ reinterpret_cast<bullet_t near *>(_DI)
	p_ = p;

	switch(p_->accel_type) {
	case BAT_Y:
		if(p_->velocity.y.v < BULLET_ACCEL_Y_VELOCITY_MAX) {
			p_->velocity.y += 0.0625f;
		}
		break;
	}

	#undef p_
}

#undef coord_prev
#undef p
