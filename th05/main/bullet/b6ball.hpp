/// Shinki's 32×32 ball bullets
/// ---------------------------

#define B6BALL_COUNT 63
#define B6BALL_W 32
#define B6BALL_H 32

enum b6ball_flag_t {
	B6BF_FREE = 0,
	B6BF_CLOUD = 1,
	B6BF_ALIVE = 2,
	B6BF_DECAY = 3,

	_b6ball_flag_t_FORCE_UINT8 = 0xFF
};

struct b6ball_t {
	b6ball_flag_t flag;
	int8_t unused_1;
	PlayfieldMotion pos;
	unsigned int age; // unused and broken, because it's never reset
	Subpixel cloud_radius;
	int patnum_tiny;
	int decay_frames;
	int8_t unused_2[4];
};

struct b6ball_template_t {
	/* -------------------- */ int8_t _unused_1;
	unsigned char angle;
	PlayfieldPoint origin;
	/* -------------------- */ int16_t _unused_2[6];
	int patnum_tiny;
	/* -------------------- */ int16_t _unused_3[2];
	SubpixelLength8 speed;
};

// Supplements the actual load call from _DM05.TX2. It's understandable why
// you'd want to load these sprites as part of the dialog script (that's the
// best place to hide load times, after all), but tiny-format conversion should
// have really been part of the script commands as well, then.
#define b6balls_load() { \
	for(int i = TINY_B6BALL_START; i < TINY_B6BALL_END; i++) { \
		super_convert_tiny(i); \
	} \
}

#define b6ball_template ( \
	reinterpret_cast<b6ball_template_t &>(custom_entities[0]) \
)
#define b6balls (reinterpret_cast<b6ball_t *>(&custom_entities[1]))

// Spawns a new ball bullet according to the [b6ball_template]. Reads all
// non-unused fields of the b6ball_template_t structure.
void near b6balls_add();

void near b6balls_update();
