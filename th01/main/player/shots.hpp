#include "th01/sprites/pellet.h"
#include "th01/math/overlap.hpp"

static const int SHOT_COUNT = 8;
static const pixel_t SHOT_W = 16;
static const pixel_t SHOT_H = 16;

struct CShots {
	screen_x_t left[SHOT_COUNT];
	screen_y_t top[SHOT_COUNT];
	int unknown[SHOT_COUNT];

	// A shot slot can be considered "alive" if either of these are nonzero.
	bool moving[SHOT_COUNT];
	unsigned char decay_frame[SHOT_COUNT];

	void add(screen_x_t new_left, screen_y_t new_top);
	void unput_and_reset_all(void);
	void unput_update_render(void);

	bool16 is_moving(int i) {
		return moving[i];
	}

	// Processes any collision between *the given* shot and the Orb, placed at
	// the given position, and returns true if they did collide.
	bool16 hittest_orb(int i, screen_x_t orb_left, screen_y_t orb_top);

	// Processes any collision between *any* shot and a pellet, placed at the
	// given position, and returns true if they did collide.
	bool16 hittest_pellet(screen_x_t pellet_left, screen_y_t pellet_top);

	// Processes any collision between *any* shot and a boss with the given
	// hitbox, and returns true if they did collide.
	bool16 hittest_boss(
		screen_x_t hitbox_left,
		screen_y_t hitbox_top,
		pixel_t hitbox_w,
		pixel_t hitbox_h
	);
};

extern CShots Shots;
