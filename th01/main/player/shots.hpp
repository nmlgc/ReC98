static const int SHOT_COUNT = 8;

struct CShots {
	int left[SHOT_COUNT];
	int top[SHOT_COUNT];
	int unknown[SHOT_COUNT];

	// A shot slot can be considered "alive" if either of these are nonzero.
	unsigned char moving[SHOT_COUNT];
	unsigned char decay_frame[SHOT_COUNT];
};

extern CShots Shots;
