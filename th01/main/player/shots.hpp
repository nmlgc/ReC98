#include "th01/sprites/pellet.h"
#include "th01/math/overlap.hpp"

static const int SHOT_COUNT = 8;
static const int SHOT_W = 16;
static const int SHOT_H = 16;

struct CShots {
	int left[SHOT_COUNT];
	int top[SHOT_COUNT];
	int unknown[SHOT_COUNT];

	// A shot slot can be considered "alive" if either of these are nonzero.
	unsigned char moving[SHOT_COUNT];
	unsigned char decay_frame[SHOT_COUNT];

	void add(int new_left, int new_top);
	void unput_and_reset_all(void);
	void unput_update_render(void);

	bool16 is_moving(int i) {
		return moving[i];
	}

	// Processes any collision between *the given* shot and the Orb, placed at
	// the given position, and returns true if they did collide.
	bool16 hittest_orb(int i, int orb_left, int orb_top);

	// Processes any collision between *any* shot and a pellet, placed at the
	// given position, and returns true if they did collide.
	bool16 hittest_pellet(int pellet_left, int pellet_top);

	// Processes any collision between *any* shot and a boss with the given
	// hitbox, and returns true if they did collide.
	bool16 hittest_boss(
		int hitbox_left, int hitbox_top, int hitbox_w, int hitbox_h
	);
};

extern CShots Shots;
