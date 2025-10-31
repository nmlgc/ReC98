#include "th03/main/enemy/efe.hpp"
#include "th03/snd/snd.h"
#include "th03/sprites/main_s16.hpp"

// Position flags
// --------------

typedef uint8_t enemy_pos_type_t;

// Clips the enemy at the left and right edges of the playfield.
static const enemy_pos_type_t EPT_CLIP_X = 0x01;

// Clips the enemy at the bottom edge of the playfield.
static const enemy_pos_type_t EPT_CLIP_BOTTOM = 0x02;

// If set, horizontal spawn positions and movement velocities are applied as
// given in the script. If not set, they are horizontally mirrored. (Yes, this
// would have been easier to describe if it were the other way round.)
static const enemy_pos_type_t EPT_DO_NOT_MIRROR_X = 0x80;
// --------------

// Entity flags
// ------------

// Script is running and has spawned its enemy
static const efe_flag_t EF_RUNNING_SPAWNED = 1;

// Script is running and hasn't spawned its enemy
static const efe_flag_t EF_RUNNING_UNSPAWNED = 3;
// ------------

struct enemy_t {
	efe_flag_t flag;
	uint8_t frame;
	PlayfieldPoint center;
	uint8_t explosion_max_enemy_hits_half;
	uint8_t hp;
	pid_t pid;
	pixel_length_8_t size_pixels;
	uint16_t script_ip; // Offset from [script_base]
	uint16_t script_op_frame;
	uint8_t near *script_base; // Pointer to first script instruction
	SPPoint velocity;
	int8_t unused_1[4];

	// 16-bit angles!
	// ZUN landmine: Should be a single 16-bit variable instead of a `union`
	// to not break on big-endian systems.
	union {
		uint16_t wide;
		struct {
			unsigned char fine;
			unsigned char coarse;
		} split;
	} angle;

	int8_t angle_speed;
	int8_t unused_2;
	uint8_t chain_slot;
	uint8_t formation_type;
	uint8_t formation_i; // ID of this enemy within its formation
	subpixel_length_8_t speed;
	uint8_t loop_i;
	enemy_pos_type_t pos_type;
	int8_t padding[14];

	// Sprite size in 16-pixel units. 0 = invalid.
	uvram_word_amount_8_t& size_words(void) {
		return static_cast<uvram_word_amount_8_t>(
			explosion_max_enemy_hits_half
		);
	}
};

inline void enemy_t_verify(void) {
	efe_subclass_verify(reinterpret_cast<enemy_t *>(nullptr));
}

// Constants
// ---------

static const int ENEMY_COUNT = 40;

// TH03 generates a sequence of 256 random formations and formation directions
// for each round.
static const int FORMATION_RING_SIZE = 256;

// Arbitrary limitations to avoid more precise buffer size calculations.
static const int FORMATION_ENEMIES_MAX = 16;
static const int FORMATIONS_MAX = 24;

extern const sprite16_offset_t SO_ENEMIES[];
// ---------

// State
// -----

#define enemies reinterpret_cast<enemy_t *>(&efes[0])

// ZUN bloat: Declaring a structure with an
//
// 	uint8_t near *for_enemy[FORMATION_ENEMIES_MAX];
//
// array would have been more readable and generated one fewer instruction.
typedef uint8_t near *enemy_script_p;

extern uint8_t enemy_formation_type;
extern uint8_t enemy_formation_i;

// ZUN bloat: One pointer is enough.
extern uint8_t __seg *enedat_2;
extern uint8_t __seg *enedat;

// ZUN bloat: Twice as much as the arbitrary limitation...
extern uint8_t formation_enemy_count[FORMATIONS_MAX * 2];

extern enemy_script_p __seg *formation_scripts;
extern uint8_t __seg *formation_type_ring;
extern enemy_pos_type_t __seg *formation_pos_type_ring;
extern uint8_t formation_p[PLAYER_COUNT];
extern uint8_t formation_count;
// -----

void pascal enemies_add(
	uint8_t near *script_base, pid_t pid, enemy_pos_type_t pos_type
)
{
	enemy_t near *p = enemies;
	for(int i = 0; i < ENEMY_COUNT; (i++, p++)) {
		if(p->flag != EFF_FREE) {
			continue;
		}
		p->flag = EF_RUNNING_UNSPAWNED;
		p->script_ip = 0;
		p->script_op_frame = 0;
		p->loop_i = 0;
		p->script_base = script_base;
		p->pid = pid;
		p->formation_type = enemy_formation_type;
		p->formation_i = enemy_formation_i;
		p->pos_type = pos_type;
		break;
	}
}

#define p (efe_p.enemy)

void near enemy_put(void)
{
	sprite16_offset_t so = SO_ENEMIES[p->size_words() - 1];

	// Should use `p->size_words()` rather than the ugly underlying field, but
	// can't due to code generation issues. Doesn't really count as bloat
	// though, since `size_words()` was definitely our abstraction.
	so -= (p->hp * p->explosion_max_enemy_hits_half * (16 / BYTE_DOTS));

	screen_x_t left;
	screen_y_t top;
	pixel_length_8_t size_half = (p->size_pixels / 2);
	left = (playfield_fg_x_to_screen(p->center.x, p->pid) - size_half);
	top  = (playfield_fg_y_to_screen(p->center.y, p->pid) - size_half);
	sprite16_put(left, top, so);
}

enum enemy_explosion_flag_keyframe_t {
	KEYFRAME_HIT_ENEMIES = 10,
	KEYFRAME_DECAY = 32,
	KEYFRAME_DONE = 36,
};

void near enemy_explosion_flag_update(void)
{
	if(p->frame == KEYFRAME_HIT_ENEMIES) {
		p->flag = EFF_EXPLOSION_HITTING_ENEMIES;
		snd_se_play(3);
	} else if(p->frame == KEYFRAME_DECAY) {
		p->flag = EFF_EXPLOSION_IGNORING_ENEMIES;
	} else if(p->frame >= KEYFRAME_DONE) {
		p->flag = EFF_FREE;
	}
}

#undef p
