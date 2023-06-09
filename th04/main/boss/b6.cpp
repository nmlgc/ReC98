#include "platform.h"
#include "pc98.h"
#include "th01/math/subpixel.hpp"
#include "th04/sprites/main_pat.h"
#include "th04/main/playfld.hpp"
#include "th04/main/custom.hpp"

#define phase2_fly_path  	yuuka6_phase2_fly_path
#define PHASE2_FLY_ANGLES	YUUKA6_PHASE2_FLY_ANGLES

// Constants
// ---------

static const pixel_t BG_SHAPE_W = 16;
static const pixel_t BG_SHAPE_H = 16;

static const pixel_t CHASECROSS_W = 32;
static const pixel_t CHASECROSS_H = 32;
static const int CHASECROSS_KILL_FRAMES_PER_CEL = 4;

// The number of different paths Yuuka can take.
static const int PHASE2_FLY_PATHS = 2;

// The number of individual points on each fly path.
static const int PHASE2_FLY_NODES = 5;

extern const unsigned char PHASE2_FLY_ANGLES[PHASE2_FLY_PATHS][
	PHASE2_FLY_NODES
];
// ---------

// Structures
// ----------

#define BG_SHAPE_COUNT 56

struct bg_shape_t {
	SPPoint pos;
	unsigned char angle;
	SubpixelLength8 speed;
};

// 1 additional unused one, for some reason?
extern bg_shape_t bg_shapes[BG_SHAPE_COUNT + 1];

extern main_patnum_t bg_shape_patnum;
extern Subpixel bg_shape_flyout_speed;

// Called on every frame for each shape after [pos] was updated. Can implement
// custom clipping and respawning behavior.
extern void (near pascal *near bg_shape_clip)(bg_shape_t near& shape);

#define CHASECROSS_COUNT (CUSTOM_COUNT - 1)

enum chasecross_flag_t {
	CCF_FREE = 0,
	CCF_ALIVE = 1,
	CCF_KILL_ANIM = (PAT_ENEMY_KILL * CHASECROSS_KILL_FRAMES_PER_CEL),
	CCF_KILL_ANIM_END = (
		CCF_KILL_ANIM + (ENEMY_KILL_CELS * CHASECROSS_KILL_FRAMES_PER_CEL)
	),

	_chasecross_flag_t_FORCE_UINT8 = 0xFF
};

// Chasing cross bullets
struct chasecross_t {
	chasecross_flag_t flag;
	unsigned char angle;
	PlayfieldPoint center;
	/* ------------------------- */ int8_t unused_1[4];
	PlayfieldPoint velocity;
	unsigned int age;
	/* ------------------------- */ int8_t unused_2[4];
	int hp;
	int damage_this_frame;
	SubpixelLength8 speed;
	/* ------------------------- */ int8_t padding;
};

#define chasecrosses (reinterpret_cast<chasecross_t *>(custom_entities))

enum safetycircle_flag_t {
	SCF_FREE = 0,
	SCF_GROW = 1,
	SCF_SHRINK = 2,

	_safetycircle_flag_t_FORCE_UINT8 = 0xFF
};

struct safetycircle_t {
	safetycircle_flag_t flag;
	/* ------------------------- */ int8_t unused_1;
	screen_point_t center;
	/* ------------------------- */ int8_t unused_2[8];
	unsigned int shrink_frames;
	pixel_t radius_filled;
	pixel_t radius_ring_distance;
	/* ------------------------- */ int8_t unused_3[8];
	uint4_t col_ring;
	/* ------------------------- */ int8_t padding;
};

#define safetycircle ( \
	reinterpret_cast<safetycircle_t &>(custom_entities[CUSTOM_COUNT - 1]) \
)
// ----------

// These indicate the state of the last completed animation, and are only used
// to decide whether to trigger a transition to a different state via one of
// the _anim_* functions.
enum yuuka6_sprite_state_t {
	VANISHED = 0,
	PARASOL_BACK_OPEN = 1,
	PARASOL_BACK_CLOSED = 2,
	PARASOL_FORWARD = 3,
	PARASOL_LEFT = 4,
	PARASOL_SHIELD = 8,
};

extern int yuuka6_anim_frame;
extern yuuka6_sprite_state_t yuuka6_sprite_state;
extern uint8_t phase2_fly_path;

void pascal near chasecrosses_add(
	unsigned char angle, subpixel_length_8_t speed
)
;

// Call these once per frame to run the indicated sprite animation. All of
// these return true once the animation is finished.
bool near yuuka6_anim_parasol_back_close(void)
;
bool near yuuka6_anim_parasol_back_open(void)
;
bool near yuuka6_anim_parasol_back_pull_forward(void)
;
bool near yuuka6_anim_parasol_back_pull_left(void)
;
bool near yuuka6_anim_parasol_left_spin_back(void)
;
bool near yuuka6_anim_vanish(void)
;
bool near yuuka6_anim_appear(void)
;
bool near yuuka6_anim_parasol_shield(void)
;

void pascal near yuuka6_phase_next(
	explosion_type_t explosion_type, int next_end_hp
);
