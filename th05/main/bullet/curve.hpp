#define CURVEBULLET_W 32
#define CURVEBULLET_H 32
#define CURVEBULLET_TRAIL_NODE_COUNT 16
#define CURVEBULLET_COUNT 7

// Defines the [col] instead of the (automatically calculated) [sprite].
typedef struct {
	unsigned char flag;
	unsigned char angle;
	motion_t pos;
	unsigned int age;
	int16_t unused_2;
	int col;
	int32_t unused_3;
	SubpixelLength8 speed;
	int8_t padding;
} curvebullet_template_t;

typedef struct {
	unsigned char flag;
	unsigned char angle;
	motion_t pos;
	unsigned int age;
	int16_t unused_1;
	int sprite;
	int32_t unused_2;
	SubpixelLength8 speed;
	int8_t padding;
} curvebullet_head_t;

typedef struct {
	char flag;
	char col;
	SPPoint node_pos[CURVEBULLET_TRAIL_NODE_COUNT];
	unsigned char node_sprite[CURVEBULLET_TRAIL_NODE_COUNT];
} curvebullet_trail_t;

#define curvebullet_template \
	(reinterpret_cast<curvebullet_template_t &>(custom_entities[0]))

#define curvebullet_heads \
	(reinterpret_cast<curvebullet_head_t *>(&custom_entities[1]))
extern curvebullet_trail_t curvebullet_trails[CURVEBULLET_COUNT + 1];

// Puts the given curve bullet [sprite] (between 0 and BULLET_D_CELS) at the
// given position. Assumptions:
// • ES is already be set to the beginning of a VRAM segment
// • The GRCG is active, and set to the intended color
// Beware, [top] is actually interpreted as unsigned! [top] must therefore be
// between 0 and (RES_Y - 1).
void __fastcall near curvebullet_put(
	unsigned int left, unsigned int top, int sprite
);

void pascal near curvebullets_add();
void pascal near curvebullets_update();
void pascal near curvebullets_render();
