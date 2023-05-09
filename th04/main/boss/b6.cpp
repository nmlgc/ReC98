#include "platform.h"
#include "pc98.h"
#include "th01/math/subpixel.hpp"
#include "th04/sprites/main_pat.h"
#include "th04/main/playfld.hpp"
#include "th04/main/custom.hpp"

// Constants
// ---------

static const pixel_t CHASECROSS_W = 32;
static const pixel_t CHASECROSS_H = 32;
static const int CHASECROSS_KILL_FRAMES_PER_CEL = 4;
// ---------

// Structures
// ----------

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
