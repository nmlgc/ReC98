#define B6BALL_COUNT 63
#define B6BALL_W 32
#define B6BALL_H 32

typedef struct {
	unsigned char flag;
	unsigned char angle;
	motion_t pos;
	unsigned int age;
	Subpixel cloud_radius;
	int patnum_tiny;
	int decay_frames;
	int16_t unused;
	SubpixelLength8 speed;
	int8_t padding;
} b6ball_t;

#define b6ball_template (reinterpret_cast<b6ball_t &>(custom_entities[0]))
#define b6balls (reinterpret_cast<b6ball_t *>(&custom_entities[1]))

void pascal near b6balls_add();
void pascal near b6balls_update();
void pascal near b6balls_render();
