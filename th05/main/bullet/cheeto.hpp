#include "th04/main/playfld.hpp"

#define CHEETO_W 32
#define CHEETO_H 32
#define CHEETO_TRAIL_NODE_COUNT 16
#define CHEETO_COUNT 7

enum cheeto_flag_t {
	CF_FREE = 0,
	CF_SLOWDOWN = 1,
	CF_SPEEDUP = 2,

	_cheeto_flag_t_FORCE_UINT8 = 0xFF
};

// Defines the [col] instead of the (automatically calculated) [sprite].
struct cheeto_template_t {
	/* -------------------- */ int8_t _unused_1;
	unsigned char angle;
	PlayfieldPoint origin;
	/* -------------------- */ int16_t _unused_2[6];
	vc2 col;
	/* -------------------- */ int32_t _unused_3;
	SubpixelLength8 speed;
};

struct cheeto_head_t {
	cheeto_flag_t flag; // unused here
	unsigned char angle;
	PlayfieldMotion pos;
	unsigned int age;
	int16_t unused_1;
	int sprite;
	int32_t unused_2;
	SubpixelLength8 speed;
	int8_t padding;
};

struct cheeto_trail_t {
	cheeto_flag_t flag;
	char col;
	PlayfieldPoint node_pos[CHEETO_TRAIL_NODE_COUNT];
	unsigned char node_sprite[CHEETO_TRAIL_NODE_COUNT];
};

#define cheeto_template \
	(reinterpret_cast<cheeto_template_t &>(custom_entities[0]))

#define cheeto_heads \
	(reinterpret_cast<cheeto_head_t *>(&custom_entities[1]))
extern cheeto_trail_t cheeto_trails[CHEETO_COUNT + 1];

// Puts the given cheeto bullet [sprite] (between 0 and BULLET_D_CELS) at the
// given position. Assumptions:
// • ES is already set to the beginning of a VRAM segment
// • The GRCG is active, and set to the intended color
// Beware, [top] is actually interpreted as an unsigned screen-space
// coordinate! [top] must therefore be between 0 and (RES_Y - 1).
void __fastcall near cheeto_put(uscreen_x_t left, uscreen_y_t top, int sprite);

// Spawns a new cheeto bullet according to the [cheeto_template]. Reads all
// non-unused fields of the cheeto_template_t structure.
void near cheetos_add(void);

void near cheetos_update();
void pascal near cheetos_render();
