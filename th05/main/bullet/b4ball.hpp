#define B4BALL_COUNT 63
#define B4BALL_W 32
#define B4BALL_H 32

struct b4ball_t {
	unsigned char flag;
	unsigned char angle;
	PlayfieldMotion pos;
	unsigned int age;
	bool16 revenge;
	int patnum_tiny_base;
	int hp;
	int damaged_this_frame;
	SubpixelLength8 speed;
	int8_t padding;
};

struct b4ball_template_t {
	/* -------------------- */ int8_t _unused_1;
	unsigned char angle;
	PlayfieldPoint origin;
	/* -------------------- */ int16_t _unused_2[5];
	bool16 revenge;
	int patnum_tiny_base;
	int hp;
	/* -------------------- */ int16_t _unused_3;
	SubpixelLength8 speed;
};

#define b4ball_template ( \
	reinterpret_cast<b4ball_template_t &>(custom_entities[0]) \
)
#define b4balls (reinterpret_cast<b4ball_t *>(&custom_entities[1]))

void pascal near b4balls_reset(void);

// Spawns a new ball bullet according to the [b4ball_template]. Reads all
// non-unused fields of the b4ball_template_t structure.
void pascal near b4balls_add(void);

void pascal near b4balls_update(void);
void pascal near b4balls_render(void);
