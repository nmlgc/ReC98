#pragma option -zPmain_04 -G

#include "th03/main/bullet/bullet.hpp"
#include "th03/main/player/bomb.hpp"
#include "th03/main/player/cur.hpp"
#include "th03/main/player/gba.hpp"
#include "th03/main/player/stuff.hpp"
#include "th03/main/enemy/expl.hpp"
#include "th03/main/difficul.hpp"
#include "th03/main/hitbox.hpp"
#include "th03/math/randring.hpp"
#include "th03/math/vector.hpp"
#include "th03/sprites/pellet.h"
#include "th02/main/bullet/impl.hpp"
#include "th02/sprites/bullet16.h"
#include "th02/v_colors.hpp"
#include "th01/hardware/grcg.hpp"
#include "libs/master.lib/pc98_gfx.hpp"
#include "libs/sprite16/sprite16.h"
#include "platform/x86real/flags.hpp"
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
		// We really should either fail or just not handle invalid bullet
		// types, and provide proper `case`s for these three. Instead, this
		// code explicitly creates the possibility of spawning bullets with
		// invalid flags, forcing bullets_update() to defend against them.
		// More on this whole issue in that function.
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
	// ZUN bloat: For example, which sprite do we get if [p->flag] happens to
	// be [BF_BULLET16]? We could *technically* use [BT_BULLET16_CUSTOM] to use
	// the template's [sprite_offset], but that would violate soundness: That
	// type is not a valid `bullet_flag_t` value, and bullets_update() treats
	// is as invalid. [BF_BULLET16], however, would always result in PID 1's
	// sprite since this function is always called with ([pid.so_attack] ==
	// [SO_ATTACK_P2]). The cast obscures that this function was really only
	// ever meant to be used for pellets.
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

void bullets_update(void)
{
	#define coord_next static_cast<playfield_subpixel_t>(_AX)

	// ZUN bloat: Unused, and could overflow because [BULLETS_COUNT] is larger
	// than 255.
	uint8_t alive = 0;

	// ZUN bloat: Yes, directly assigning [p->pid] to BX would have generated
	// better code, but then you *keep* BX instead of always adding the base
	// pointer to it…
	#define pid_subscript(ptr) ( \
		_BH = 0, _BL = p->pid, _BX += FP_OFF(ptr), *((uint8_t near *)(_BX)) \
	)

	collmap_tile_h = 1;
	explosion_hittest_mode = EHM_PELLET;

	// ZUN bloat: A `for` loop would have been more readable.
	int i = (BULLET_COUNT + 1);
	p = (bullets - 1);
	while(1) {
		p++;

		// ZUN bloat: `if(--i == 0)` compiles into DEC+JZ. This… doesn't.
		_AX = --i;
		if(static_cast<int16_t>(_AX) == 0) {
			break;
		}

		// Yes, bullets with invalid flags are treated as nonexistent here, but
		// not in bullets_add(), and will therefore take up space in [bullets]
		// until the next call to bullets_reset(). bullets_add()'s `default`
		// case might very well accidentally spawn such invalid bullets under
		// certain circumstance; players have reported several bugs in TH03
		// that seem to be caused by out-of-bounds structure accesses, so we
		// can't rule out as of November 2025.
		// TODO: Revisit this once we've completely RE'd the game and then
		// classify the existence of [BF_INVALID] as bloat or a quirk.
		if((p->flag == BF_FREE) || (p->flag >= BF_INVALID)) {
			continue;
		}
		alive++;
		p->age++;

		if(p->flag == BF_PELLET_CLOUD) {
			// ZUN bloat: `if((p->age & 3) == 0)`
			_AL = (p->age & 3);
			if(FLAGS_ZERO) {
				#define so_next static_cast<vram_byte_amount_t>(_AX)
				so_next = (p->sprite_offset + XY(PELLET_CLOUD_W, 0));
				if(so_next >= (
					SO_PELLET_CLOUD +
					XY((PELLET_CLOUD_W * PELLET_CLOUD_CELS), 0)
				)) {
					p->flag = BF_PELLET;
				} else {
					p->sprite_offset = so_next;
				}
				#undef so_next
			}
			continue;
		}

		// X coordinate
		// ------------
		// ZUN bug: If two or more bullets share the same trail point slot as
		// a result of the [TRAIL_RING_SIZE] quirk, separately processing X and
		// Y can cause trail point coordinates to get mixed up if the first
		// bullet gets clipped due to its Y coordinate. In that case, X will
		// come from the first bullet, and Y will come from the second one.
		// bullets_render() will then blit trail sprites to this mixed-up
		// position for a single frame, until the second bullet is removed as
		// well. Hence, this is a bug we can fix without affecting gameplay, as
		// the clipping condition from the first bullet still applies due to
		// the quirk, regardless of the mixed-up positions.

		coord_next = p->center.x;
		coord_prev = coord_next;
		coord_next += p->velocity.x.v;

		if(p->flag != BF_PELLET_TRANSFER) {
			// ZUN bloat: `if(
			// 	(bomb_flag[p->pid] != BF_INACTIVE) || damage_all_on[p->pid]
			// )`
			if(
				(pid_subscript(bomb_flag) != BF_INACTIVE) ||
				pid_subscript(damage_all_on)
			) {
				goto remove_x;
			} else if(p->has_trail) {
				// Bullets with a trail are only removed after their last trail
				// point has reached the clipping coordinate. However, bullets
				// are also rendered without any playfield boundary clipping in
				// general – doing so would break the deliberate out-of-bounds
				// movement of [BF_PELLET_TRANSFER] bullets, and unclipped
				// rendering is also slightly faster.
				// The combination of these details now creates two rendering
				// issues for the main sprite if a bullet's speed is fast
				// enough:
				//
				// 1) If a bullet travels all the way through the border
				//    between the left and right playfields in the center of
				//    VRAM before it is removed, it will pop in at the
				//    respective opposite edge of the other playfield.
				// 2) If a bullet's X coordinate ever exceeds VRAM boundaries,
				//    SPRITE16's unclipped VRAM offset calculation will place
				//    its sprite at a wildly unrelated point in VRAM.
				//
				// To work around both of these, ZUN clamps the X coordinate of
				// the main entity to the clipping coordinate, letting it
				// invisibly wait [TRAIL_POINT_COUNT] frames under the border
				// until the last trail point has caught up. The Y coordinate
				// does not have this issue because SPRITE16 does clip that one
				// against the top and bottom edges of the visible 200 lines.
				//
				// Of course, this workaround assumes that the playfield border
				// fully covers a 16×16 bullet at [CENTER_MIN] and
				// [CENTER_X_MAX].
				static_assert(
					(CENTER_MIN - TO_SP(BULLET16_W / 2)) >=
					TO_SP(-(PLAYFIELD_BORDER * 2))
				);
				static_assert(
					(CENTER_X_MAX + TO_SP(BULLET16_W / 2)) <=
					TO_SP(PLAYFIELD_W + (PLAYFIELD_BORDER * 2))
				);

				if(coord_next > CENTER_MIN) {
					if(coord_next < CENTER_X_MAX) {
						goto clamp_done;
					} else {
						goto clamp_max;
					}
				} else {
					goto clamp_min;
				}
				clamp_min:	coord_next = CENTER_MIN;  	goto clamp_done;
				clamp_max:	coord_next = CENTER_X_MAX;
				clamp_done:

				coord_max.v = CENTER_X_MAX;
				_BX = offsetof(bullet_trail_t, center_x);
				bullet_trail_update_and_clip(
					_AX,
					_DX,
					reinterpret_cast<bullet_trail_coords_t near *>(_BX)
				);
				if(FLAGS_CARRY) {
					goto remove_x;
				}
				optimization_barrier();
				goto passed_x_checks;
			} else {
				if((coord_next <= CENTER_MIN) || (coord_next >= CENTER_X_MAX)) {
					goto remove_x;
				}
			}
			optimization_barrier();
			goto passed_x_checks;

		remove_x:
			_SI = _SI;
			p->flag = BF_FREE;
			continue;
		} else {
			// ZUN bloat: There are better ways of checking the coordinate than
			// hardcoding the assumption of the physical layout together with
			// the expected horizontal movement direction.
			static_assert(PLAYER_COUNT == 2);
			_BL = p->pid;
			if(_BL == 0) {
				if(coord_next >= p->target_center_x_for_origin_pid.v) {
					goto transfer;
				} else {
					goto passed_x_checks;
				}
			} else {
				if(coord_next <= p->target_center_x_for_origin_pid.v) {
					goto transfer;
				} else {
					optimization_barrier();
					goto passed_x_checks;
				}
			}

		transfer:
			p->flag = BF_PELLET_CLOUD;
			p->pid ^= 1;

			// ZUN bloat
			_DX = p->target_center_x_for_target_pid.v;
			p->center.x.v = _DX;

			// ZUN quirk: Yup, overriding the random Y position the bullet
			// aimed for when it spawned.
			p->center.y.set(2.0f);

			p->speed_next += 0.5f;
			bullet_template.count = 0;
			bullets_add_next_from_p();
			p->flag = BF_FREE;
			goto next;
		}
	passed_x_checks:
		p->center.x.v = coord_next;
		// ------------

		// Y coordinate
		// ------------

		coord_next = p->center.y;
		coord_prev = coord_next;
		coord_next += p->velocity.y.v;

		if(p->has_trail) {
			coord_max.v = CENTER_Y_MAX;
			_BX = offsetof(bullet_trail_t, center_y);
			bullet_trail_update_and_clip(
				_AX, _DX, reinterpret_cast<bullet_trail_coords_t near *>(_BX)
			);
			if(FLAGS_CARRY) {
				goto remove_y;
			}
			optimization_barrier();
			goto passed_y_checks;
		} else if((coord_next > CENTER_MIN) && (coord_next < CENTER_Y_MAX)) {
			goto passed_y_checks;
		}
	remove_y:
		p->flag = BF_FREE;
		continue;

	passed_y_checks:
		p->center.y.v = coord_next;
		if(p->accel_type != BAT_NONE) {
			bullet_update_velocity_y();
		}
		// ------------

		// Pellet collision with explosions
		if(p->flag == BF_PELLET) {
			enum {
				HITBOX_SIZE = TO_SP(12),
			};

			#define coord_y coord_next
			#define coord_x static_cast<playfield_subpixel_t>(_DX)

			coord_x = p->center.x;
			coord_x -= (HITBOX_SIZE / 2);
			coord_y = coord_next;
			coord_y -= (HITBOX_SIZE / 2);
			hitbox.origin.topleft.x.v = coord_x;
			hitbox.origin.topleft.y.v = coord_y;

			coord_x += HITBOX_SIZE;
			coord_y += HITBOX_SIZE;
			hitbox.right.v = coord_x;
			hitbox.bottom.v = coord_y;

			#undef coord_x
			#undef coord_y

			// ZUN bloat: One byte more than through AL, as Turbo C++ 4.0J
			// would usually generate...
			_BL = p->pid;
			hitbox.pid = _BL;

			/* TODO: Replace with the decompiled call
			 * 	explosions_hittest();
			 * once the segmentation allows us to, if ever */
			asm { push cs; call near ptr explosions_hittest; }
			if(_AL != 0) {
				static_assert(PLAYER_COUNT == 2);
				// ZUN bloat: `if(gba_flag_active[p->pid ^ 1] == GBAF_NONE)`
				_BH = 0;
				_BL = p->pid;
				_BL ^= 1;
				_BX += FP_OFF(gba_flag_active);
				if(*reinterpret_cast<uint8_t near *>(_BX) == GBAF_NONE) {
					p->flag = BF_PELLET_TRANSFER;
					p->group_next = BG_RANDOM_CONSTRAINED_ANGLE_AIMED;
					p->angle_next = 0x00;
					bullets_add_next_from_p();
				}
				p->flag = BF_FREE;
				continue;
			}
		}

		// Non-transfer bullet collision with players
		if((p->flag != BF_PELLET_TRANSFER) && p->is_collidable) {
			collmap_topleft.x = p->center.x;
			collmap_topleft.y = p->center.y;
			collmap_pid = p->pid;

			/* TODO: Replace with the decompiled call
			 * 	collmap_set_vline();
			 * once the segmentation allows us to, if ever */
			_asm { push cs; call near ptr collmap_set_vline; }
		}
	next:
		_AX = _AX;
	};

	#undef pid_subscript
	#undef coord_next
}

#undef coord_prev
#undef p

void bullets_render(void)
{
	// ZUN bloat: Could have shared variables (and registers!) with regular
	// bullets.
	register bullet_t near *pellet_p;
	register unsigned int pellet_i;

	int bullet_i;
	struct {
		screen_y_t y;
		screen_x_t x;
	} topleft;
	sprite16_offset_t so;
	int trail_i;

	#define topleft_set(topleft, bullet, center_x, center_y, w, h) { \
		topleft.x = ( \
			playfield_fg_x_to_screen(center_x, bullet->pid) - (w / 2) \
		); \
		topleft.y = ( \
			playfield_fg_y_to_screen(center_y, bullet->pid) - (h / 2) \
		); \
	}

	egc_on();
	sprite16_clip.reset();

	// 16×16 bullets (full-color)
	// --------------------------

	sprite16_put_size.set(BULLET16_W, BULLET16_H);
	bullet_t near *bullet_p = bullets;
	bool need_cloud_pass = false;
	for(bullet_i = 0; bullet_i < BULLET_COUNT; (bullet_i++, bullet_p++)) {
		if(bullet_p->flag == BF_BULLET16) {
			so = bullet_p->sprite_offset;
			if(bullet_p->has_trail) {
				so += (BULLET16_TRAIL_CELS * (BULLET16_W / BYTE_DOTS));

				trail_i = (TRAIL_POINT_COUNT - 1);
				while(trail_i > 0) {
					topleft_set(
						topleft,
						bullet_p,
						bullet_p->trail->center_x.v[trail_i],
						bullet_p->trail->center_y.v[trail_i],
						BULLET16_W,
						BULLET16_H
					);
					sprite16_put_noclip(topleft.x, topleft.y, so);
					trail_i -= TRAIL_POINTS_PER_SPRITE;
					so -= (BULLET16_W / BYTE_DOTS);
				}
			}

			topleft_set(
				topleft,
				bullet_p,
				bullet_p->center.x,
				bullet_p->center.y,
				BULLET16_W,
				BULLET16_H
			);
			if(bullet_p->is_animated) {
				so += (
					(bullet_p->age % BULLET16_CELS) * (BULLET16_W / BYTE_DOTS)
				);
			}
			sprite16_put_noclip(inhibit_Z3(topleft.x), topleft.y, so);
		} else if(bullet_p->flag == BF_PELLET_CLOUD) {
			need_cloud_pass = true;
		}
	}
	// --------------------------

	// 32×32 delay clouds (white)
	// --------------------------

	if(need_cloud_pass) {
		sprite16_mono_(true);
		sprite16_mono_color_(V_WHITE);
		sprite16_put_size.set(PELLET_CLOUD_W, PELLET_CLOUD_H);
		bullet_p = bullets;
		for(bullet_i = 0; bullet_i < BULLET_COUNT; (bullet_i++, bullet_p++)) {
			if(bullet_p->flag == BF_PELLET_CLOUD) {
				topleft_set(
					topleft,
					bullet_p,
					bullet_p->center.x,
					bullet_p->center.y,
					PELLET_CLOUD_W,
					PELLET_CLOUD_H
				);
				sprite16_put(topleft.x, topleft.y, bullet_p->sprite_offset);
			}
		}
		sprite16_mono_(keep_0(false));
	}
	// --------------------------

	egc_off();

	// 8×8 pellets
	// -----------

	grcg_setcolor(GC_RMW, V_WHITE);
	_ES = SEG_PLANE_B;
	pellet_p = bullets;
	pellet_i = keep_0(0);
	do {
		static_assert(BF_PELLET == 1);
		static_assert(BF_PELLET_TRANSFER == 3);
		if(pellet_p->flag & 1) {
			#define left static_cast<screen_x_t>(_AX)
			#define top static_cast<int>(_BX)

			left = (playfield_fg_x_to_screen(
				pellet_p->center.x, (_AL = pellet_p->pid, _AH ^= _AH, _AX)
			) - (PELLET_W / 2));
			top = pellet_p->center.y;
			top >>= (SUBPIXEL_BITS + 1); // Subpixel screen space → VRAM
			top += ((PLAYFIELD_BORDER / 2) - (PELLET_VRAM_H / 2));

			// Already counted as bloat inside that function.
			_DX = C_PELLET;
			if(pellet_p->flag != BF_PELLET) {
				_DH = C_PELLET_TRANSFER;
			}
			grcg_pellet_put(left, _DX, top);

			#undef top
			#undef left
		}
		pellet_p++;
		pellet_i++;
	} while(pellet_i < BULLET_COUNT);

	// ZUN bloat: Just a grcg_off();
	_asm {
		xor	ax, ax;
		out	0x7C, ax;
	}
	// -----------
}
