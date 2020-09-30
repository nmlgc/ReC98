#define SWORD_COUNT 63
#define SWORD_W 32
#define SWORD_H 32

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
} sword_t;

#define sword_template (reinterpret_cast<sword_t &>(custom_entities[0]))
#define swords (reinterpret_cast<sword_t *>(&custom_entities[1]))

void pascal near swords_add(void);
void pascal near swords_update(void);
void pascal near swords_render(void);
