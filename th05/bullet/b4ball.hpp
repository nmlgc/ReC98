#define B4BALL_COUNT 63
#define B4BALL_W 32
#define B4BALL_H 32

typedef struct {
	unsigned char flag;
	unsigned char angle;
	motion_t pos;
	unsigned int age;
	int revenge;
	int patnum_tiny_base;
	int hp;
	int damaged_this_frame;
	SubpixelLength8 speed;
	int8_t padding;
} b4ball_t;

#define b4ball_template (reinterpret_cast<b4ball_t &>(custom_entities[0]))
#define b4balls (reinterpret_cast<b4ball_t *>(&custom_entities[1]))

void pascal near b4balls_reset(void);
void pascal near b4balls_add(void);
void pascal near b4balls_update(void);
void pascal near b4balls_render(void);
