#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "libs/sprite16/sprite16.h"
#include "th03/common.h"
#include "th03/math/randring.hpp"
#include "th03/main/frames.h"
#include "th03/main/playfld.hpp"
#include "th03/main/hitbox.hpp"
#include "th03/main/hitcirc.hpp"
#include "th03/main/v_colors.hpp"
#include "th03/sprites/main_s16.hpp"

static const pixel_t HITCIRCLE_W = 48;
static const pixel_t HITCIRCLE_H = 48;
static const uvram_byte_amount_t HITCIRCLE_VRAM_W = (HITCIRCLE_W / BYTE_DOTS);

static const int HITCIRCLE_CELS = 4;
static const unsigned int HITCIRCLE_FRAMES_PER_CEL = 4;
static const int HITCIRCLE_FRAMES = (HITCIRCLE_FRAMES_PER_CEL * HITCIRCLE_CELS);

static const int HITCIRCLE_ENEMY_COUNT = 12;

// ZUN quirk: Should *maybe* be [PLAYER_COUNT]? If both players get hit within
// [HITCIRCLE_FRAMES], the earlier animation is cut off. It's too obvious of an
// oversight to classify it as a bug, though. The sudden stop of the animation
// could also be supposed to telegraph that the other player got hit, without
// having to peek over to the other playfield.
static const int HITCIRCLE_PLAYER_COUNT = 1;

static const int HITCIRCLE_COUNT = (
	HITCIRCLE_ENEMY_COUNT + HITCIRCLE_PLAYER_COUNT
);

struct HitCircle {
	uint8_t age; // Alive if ≥1.
	pid_t pid;
	screen_point_t topleft;

	void spawn(const pid2& pid_) {
		age = 1;
		pid = pid_;
	}

	sprite16_offset_t cel(void) const {
		// ZUN bloat: (SO_HITCIRCLE + (
		// 	((age - 1) / HITCIRCLE_FRAMES_PER_CEL) * HITCIRCLE_VRAM_W)
		// ). 1 SHR, 1 IMUL. This compiles to both those *and* a bunch of MOVs
		// and ADDs in between...
		static_assert(HITCIRCLE_VRAM_W == 6);
		_BX = (age - 1);
		_BX /= HITCIRCLE_FRAMES_PER_CEL;
		_BX *= 2;
		return (SO_HITCIRCLE + _BX + _BX + _BX);
	}
};

// ZUN bloat: Merge into HitCircle::spawn().
#define hitcircle_set_topleft(p, center_x, center_y, pid) { \
	p.topleft.x = ( \
		playfield_fg_x_to_screen(center_x, pid) - (HITCIRCLE_W / 2) \
	); \
	p.topleft.y = (TO_PIXEL(center_y) + PLAYFIELD_TOP - (HITCIRCLE_H / 2)); \
}

extern HitCircle hitcircles[HITCIRCLE_COUNT];

void pascal hitcircles_enemy_add(
	subpixel_t center_x, subpixel_t center_y, pid2 pid
)
{
	#define last_id hitcircles_enemy_last_id
	extern uint8_t last_id;
	last_id++;
	if(last_id >= HITCIRCLE_ENEMY_COUNT) {
		last_id = 0;
	}

	HitCircle near& p = hitcircles[last_id];
	p.spawn(pid);

	if(!hitcircles_enemy_add_do_not_randomly_center_within_hitbox) {
		center_x = (
			hitbox.origin.topleft.x.v +
			randring_far_next16_mod(hitbox.radius.x * 2)
		);
		center_y = (
			hitbox.origin.topleft.y.v +
			randring_far_next16_mod(hitbox.radius.y * 2)
		);
	}
	hitcircle_set_topleft(p, center_x, center_y, pid);

	#undef last_id
}

void pascal hitcircles_player_add(
	subpixel_t center_x, subpixel_t center_y, pid2 pid
)
{
	HitCircle near& p = hitcircles[HITCIRCLE_ENEMY_COUNT];
	p.spawn(pid);
	hitcircle_set_topleft(p, center_x, center_y, pid);
}

void near hitcircles_update(void)
{
	HitCircle near* p = hitcircles;
	int i = 0;
	while(i < HITCIRCLE_COUNT) {
		if(p->age) {
			p->age++;

			// Not off-by-one, since [age] starts at 1.
			if(p->age > HITCIRCLE_FRAMES) {
				p->age = 0;
			}
		}
		i++;
		p++;
	}
}

void near hitcircles_render(void)
{
	const HitCircle near* p = hitcircles;

	sprite16_mono_(true);

	// ZUN bloat
	_DX = round_or_result_frame;
	asm { and dx, 1 };
	_DX += V_YELLOW_DARK;
	sprite16_mono_color(_DX);

	sprite16_put_size.set(HITCIRCLE_W, HITCIRCLE_H);

	int i = 0;
	while(i < HITCIRCLE_ENEMY_COUNT) {
		if(p->age) {
			sprite16_clip_set_for_pid(p->pid);
			sprite16_offset_t so = p->cel();
			sprite16_put(p->topleft.x, p->topleft.y, so);
		}
		i++;
		p++;
	}

	// Player circle
	static_assert(HITCIRCLE_PLAYER_COUNT == 1);
	_DX = V_WHITE;
	sprite16_mono_color(_DX);
	if(p->age) {
		sprite16_clip_set_for_pid(p->pid);
		sprite16_offset_t so = p->cel();
		sprite16_put(p->topleft.x, p->topleft.y, so);
	}

	sprite16_mono_(false);
}
