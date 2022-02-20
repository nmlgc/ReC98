#define CURVEBULLET_W 32
#define CURVEBULLET_H 32
#define CURVEBULLET_TRAIL_NODE_COUNT 16
#define CURVEBULLET_COUNT 7

enum curvebullet_flag_t {
	CBF_FREE = 0,
	CBF_SLOWDOWN = 1,
	CBF_SPEEDUP = 2,

	_curvebullet_flag_t_FORCE_UINT8 = 0xFF
};

// Defines the [col] instead of the (automatically calculated) [sprite].
typedef struct {
	curvebullet_flag_t flag;
	unsigned char angle;
	PlayfieldMotion pos;
	unsigned int age;
	int16_t unused_2;
	int col;
	int32_t unused_3;
	SubpixelLength8 speed;
	int8_t padding;
} curvebullet_template_t;

typedef struct {
	curvebullet_flag_t flag;
	unsigned char angle;
	PlayfieldMotion pos;
	unsigned int age;
	int16_t unused_1;
	int sprite;
	int32_t unused_2;
	SubpixelLength8 speed;
	int8_t padding;
} curvebullet_head_t;

typedef struct {
	curvebullet_flag_t flag;
	char col;
	PlayfieldPoint node_pos[CURVEBULLET_TRAIL_NODE_COUNT];
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
// Beware, [top] is actually interpreted as an unsigned screen-space
// coordinate! [top] must therefore be between 0 and (RES_Y - 1).
void __fastcall near curvebullet_put(
	uscreen_x_t left, uscreen_y_t top, int sprite
);

void pascal near curvebullets_add();
void near curvebullets_update();
void pascal near curvebullets_render();
