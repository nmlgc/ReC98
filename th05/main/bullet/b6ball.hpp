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

typedef struct {
	b6ball_flag_t flag;
	unsigned char angle; // unused
	PlayfieldMotion pos;
	unsigned int age; // unused and broken, because it's never reset
	Subpixel cloud_radius;
	int patnum_tiny;
	int decay_frames;
	int16_t unused;
	SubpixelLength8 speed; // unused
	int8_t padding;
} b6ball_t;

#define b6ball_template (reinterpret_cast<b6ball_t &>(custom_entities[0]))
#define b6balls (reinterpret_cast<b6ball_t *>(&custom_entities[1]))

// Spawns a new ball bullet according to the [b6ball_template].
void near b6balls_add();

void near b6balls_update();
