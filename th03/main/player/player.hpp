#define HALFHEARTS_MAX 10

#define ROUND_START_INVINCIBILITY_FRAMES 50

#define MISS_INVINCIBILITY_FRAMES 110
#define MISS_DAMAGE_MAX 6
#define KNOCKBACK_FRAMES 64

#define SPELL_AUTOFIRE_FRAMES 128
#define CHARGE_AT_AVAIL_RING_SIZE 64

// Gauge
// -----
#define GAUGE_MAX (0xFF << 4)

typedef uint16_t gauge_t;
typedef uint8_t gauge_perbyte_t;

void pascal near gauge_avail_add(unsigned char pid, unsigned char charge);
// -----

// Charge Shots
// ------------
typedef void (far pascal *near chargeshot_add_func_t)(
	Subpixel center_x, Subpixel center_y
);

extern farfunc_t_near chargeshot_update[PLAYER_COUNT];
extern farfunc_t_near chargeshot_render[PLAYER_COUNT];
// ------------

typedef struct {
	PlayfieldPoint center;
	bool is_hit;
	uint8_t unused_1;
	unsigned char invincibility_time;
	char halfhearts;
	playchar_paletted_t playchar_paletted;
	speed_t speed;
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
} player_t;

extern unsigned char pid_current;
extern unsigned char pid_other;
