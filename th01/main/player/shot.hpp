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

	CShots() {
		unknown[0] = 0x50;
		unknown[1] = 0x60;
		unknown[2] = 0x70;

		// ZUN bloat: Why no loop?
		static_assert(SHOT_COUNT == 8);
		moving[0] = false;
		moving[1] = false;
		moving[2] = false;
		moving[3] = false;
		moving[4] = false;
		moving[5] = false;
		moving[6] = false;
		moving[7] = false;
	}

	void add(screen_x_t new_left, screen_y_t new_top);
	void unput_and_reset(void);
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
	// hitbox, and returns true if they did collide. At the right and bottom
	// edges, the coordinates of the given hitbox correspond to the top-left
	// edge of the shot sprite, so this constellation would still register as
	// a collision:
	//
	// 	                         [hitbox_w_minus_shot_w]
	// 	                        ┌───────────────────────┐
	// 	                        │                       │
	// 	[hitbox_h_minus_shot_h] │                       │
	// 	                        │                       │
	// 	                        └───────────────────────┤┐
	// 	                                                └┘ ← shot sprite
	//
	// Use the shot_hitbox_t() macro to convert a more visual on-screen hitbox
	// to this format.
	bool16 hittest_boss(
		screen_x_t hitbox_left,
		screen_y_t hitbox_top,
		pixel_t hitbox_w_minus_shot_w,
		pixel_t hitbox_h_minus_shot_h
	);
};

// Might even be related to pellets, and not to shots.
extern bool16 unused_boss_stage_flag;

extern CShots Shots;

// Converts a visual on-screen hitbox to the shot sprite-excluding format
// expected by CShots::hittest_boss(). This allows hitboxes to be specified
// like this instead:
//
// 	               [w]
// 	    ┌───────────────────────┐
// 	    │                       │
// 	[h] │                       │
// 	    │        shot sprite → ┌┤
// 	    └──────────────────────┴┘
//
#define shot_hitbox_w(w) ((w) - SHOT_W)
#define shot_hitbox_h(h) ((h) - SHOT_H)
#define shot_hitbox_t(left, top, w, h) \
	left, top, shot_hitbox_w(w), shot_hitbox_h(h)
