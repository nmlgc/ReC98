#define S2PARTICLE_COUNT 64

typedef struct {
	unsigned char flag;
	unsigned char angle;
	motion_t pos;
	unsigned int zoom;
	int16_t unused[5];
} s2particle_t;

#define s2particles (reinterpret_cast<s2particle_t *>(custom_entities))
