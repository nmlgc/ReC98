#define KNIFE_COUNT 63
#define KNIFE_W 32
#define KNIFE_H 32

typedef struct {
	unsigned char flag;
	unsigned char angle;
	motion_t pos;
	unsigned int twirl_time;
	uint16_t unused_1;
	int patnum_tiny;
	int decay_frames;
	int16_t unused_2;
	SubpixelLength8 speed;
	int8_t padding;
} knife_t;

#define knife_template (reinterpret_cast<knife_t &>(custom_entities[0]))
#define knives (reinterpret_cast<knife_t *>(&custom_entities[1]))

void pascal near knives_add(void);
void pascal near knives_update(void);
void pascal near knives_render(void);
