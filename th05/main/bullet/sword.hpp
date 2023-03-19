#define SWORD_COUNT 63
#define SWORD_W 32
#define SWORD_H 32

typedef struct {
	entity_flag_t flag;
	unsigned char angle;
	PlayfieldMotion pos;
	unsigned int twirl_time;
	uint16_t unused_1;
	int patnum_tiny;
	int decay_frames;
	int16_t unused_2;
	SubpixelLength8 speed;
	int8_t padding;
} sword_t;

struct sword_template_t {
	/* -------------------- */ int8_t unused_1;
	unsigned char angle;
	PlayfieldPoint origin;
	/* -------------------- */ int16_t unused_2[4];
	unsigned int twirl_time;
	/* -------------------- */ int16_t unused_3;
	int patnum_tiny;
	/* -------------------- */ int16_t unused_4[2];
	SubpixelLength8 speed;
};

#define sword_template (\
	reinterpret_cast<sword_template_t &>(custom_entities[0]) \
)
#define swords (reinterpret_cast<sword_t *>(&custom_entities[1]))

// Spawns a new sword according to the [sword_template]. Reads all non-unused
// fields of the sword_template_t structure.
void pascal near swords_add(void);

void pascal near swords_update(void);
void pascal near swords_render(void);
