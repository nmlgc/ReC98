#include "platform.h"
#include "pc98.h"
#include "th03/common.h"
#include "th03/math/randring.hpp"
#include "th03/main/playfld.hpp"
#include "th03/main/hitbox.hpp"
#include "th03/main/hitcirc.hpp"

static const pixel_t HITCIRCLE_W = 48;
static const pixel_t HITCIRCLE_H = 48;

static const int HITCIRCLE_FRAMES = 16;

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
