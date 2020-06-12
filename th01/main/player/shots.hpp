static const int SHOT_COUNT = 8;

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

	// Processes any collision between *the given* shot and the Orb, placed at
	// the given position, and returns true if they did collide.
	bool16 hittest_orb(int i, int orb_left, int orb_top);
};

extern CShots Shots;
