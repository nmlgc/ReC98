/// Player stuff
/// ------------
/// A random and incomplete collection of per-player state. The game contains
/// a lot more subsystems that store per-player data, so this file should only
/// declare functions that are defined within the one translation unit that
/// focuses on operating on this structure.

#include "th03/main/player/ch_shot.hpp"
#include "th03/main/player/gauge.hpp"
#include "th03/main/player/shot.hpp"
#include "th03/main/chars/speed.hpp"
#include "th03/main/collmap.hpp"
#include "th03/main/playfld.hpp"
#include "th03/hardware/input.h"

#define HALFHEARTS_MAX 10

#define ROUND_START_INVINCIBILITY_FRAMES 50

#define MISS_INVINCIBILITY_FRAMES 110
#define MISS_DAMAGE_MAX 6
#define KNOCKBACK_FRAMES 64

#define SPELL_AUTOFIRE_FRAMES 128
#define CHARGE_AT_AVAIL_RING_SIZE 64

struct player_stuff_t {
	PlayfieldPoint center;
	bool is_hit;
	uint8_t unused_1; // ZUN bloat
	unsigned char invincibility_time;
	char halfhearts;
	PlaycharPalettedOptional playchar_paletted;
	speed_t speed_base;
	shot_mode_t shot_mode;
	unsigned char patnum_movement;
	unsigned char patnum_glow;
	unsigned char knockback_time;
	unsigned char move_lock_time;
	unsigned char knockback_angle;
	unsigned char knockback_length;
	bool knockback_active;
	bool is_cpu;
	unsigned char cpu_dodge_strategy; // unused
	unsigned char gauge_charge_speed;
	gauge_t gauge_charged;
	gauge_t gauge_avail;
	unsigned char cpu_charge_at_avail_ring_p;
	unsigned char bombs;

	// Set to [playchar_paletted] when active, for some reason...
	unsigned char hyper_active;

	unsigned char lose_anim_time;

	input_t human_movement_last;
	shot_active_t shot_active;
	unsigned char spell_ready_frames;

	// A CPU player will charge up a gauge attack once ([gauge_avail] >> 4)
	// has reached the (random) value at [cpu_charge_at_avail_ring_p] of this
	// array.
	gauge_perbyte_t cpu_charge_at_avail_ring[CHARGE_AT_AVAIL_RING_SIZE];

	nearfunc_t_near hyper;	// Either hyper_standby() or [hyper_func].
	nearfunc_t_near hyper_func;
	chargeshot_add_func_t chargeshot_add;
	unsigned char rounds_won;
	uint8_t unused_2;

	// A CPU player will focus on dodging bullets while [cpu_frame] remains
	// smaller than this value.
	unsigned int cpu_safety_frames;

	unsigned int combo_bonus_max;
	unsigned char combo_hits_max;
	unsigned char miss_damage_next;
	unsigned int cpu_frame;

	unsigned char gauge_attacks_fired;
	unsigned char boss_attacks_fired;
	unsigned char boss_attacks_reversed;
	unsigned char boss_panics_fired;

	uint8_t padding[6];
};

extern player_stuff_t players[PLAYER_COUNT];

// Currently updated stuff instance.
extern player_stuff_t near *player_cur;

// Point of the last detected collision, on the top edge of the player's
// hitbox. Pretends to be at subpixel resolution, but is only ever set to
// coordinates on a 16×2-pixel grid. (Yes, 8 times worse than the tile
// resolution of the collision bitmap!)
extern PlayfieldPoint player_hittest_collision_top;

// Detects any collision of [player_cur] in a ([hitbox_size]×[hitbox_size])
// square of collision map tiles around the player's center position. Sets
// [player_cur->is_hit] and [player_hittest_collision_top] if such a collision
// was found. Uses [pid.curent].
void near pascal player_hittest(collmap_tile_amount_t hitbox_size);
