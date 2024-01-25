#define PUPPET_COUNT 2
#define PUPPET_W 32
#define PUPPET_H 32
#define PUPPET_HP 500

typedef struct {
	entity_flag_t flag;
	unsigned char angle;
	PlayfieldMotion pos;
	unsigned int phase_frame;
	union {
		subpixel_t motion;
		unsigned int gather;
	} radius;
	int patnum;
	int hp;
	int damage_this_frame;
	int16_t padding;
} puppet_t;

#define puppets (reinterpret_cast<puppet_t *>(custom_entities))

void pascal near puppets_update();
void pascal near puppets_render();
