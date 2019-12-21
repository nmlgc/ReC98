// Sets [velocity] to a vector with the given [angle] and a 12-pixel length.
//
// TH05 also insists on setting shot_t::angle via a ridiculous out-of-bounds
// access, and therefore *must* be called with [velocity] pointing inside a
// shot_t structure!
SPPoint pascal near shot_velocity_set(
	SPPoint near* velocity, unsigned char angle
);

struct shot_t {
	char flag;
	char age;
	motion_t pos;
	// The displayed sprite changes between this one and
	// [patnum_base + 1] every two frames.
#if GAME == 5
	char patnum_base;
	char type;
#else
	int patnum_base;
#endif
	char damage;
	char angle; // Unused in TH04

	void from_option_l(float offset = 0.0f) {
		this->pos.cur.x -= PLAYER_OPTION_DISTANCE + offset;
	}

	void from_option_r(float offset = 0.0f) {
		this->pos.cur.x += PLAYER_OPTION_DISTANCE + offset;
	}

	void set_option_sprite() {
		this->patnum_base = 22;
	}

	void set_option_sprite_and_damage(char damage) {
		set_option_sprite();
		this->damage = damage;
	}

	void set_random_angle_forwards(char random_range = 15, char offset = 184) {
		shot_velocity_set(
			(SPPoint near*)&this->pos.velocity,
			randring_angle(random_range, offset)
		);
	}
};

extern unsigned char shot_time;
extern shot_t near shots[];

// Points to the next free entry in [shots].
extern shot_t near *shot_ptr;
// Index of the last valid entry in [shots].
extern char shot_last_id;

// Searches and returns the next free shot slot, or NULL if there are no more
// free ones.
shot_t near* pascal near shots_add(void);
