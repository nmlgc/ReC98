#pragma option -zPmain_04

#include "th03/main/enemy/enemy.hpp"
#include "th03/main/enemy/efe.hpp"
#include "th03/main/hud/start.hpp"
#include "th03/main/player/stuff.hpp"
#include "th03/main/difficul.hpp"
#include "th03/formats/enedat.hpp"
#include "th03/math/vector.hpp"
#include "th03/snd/snd.h"
#include "th03/sprites/main_s16.hpp"
#include "th03/sprites/player.hpp"
#include "th01/math/polar.hpp"
#include "libs/master.lib/master.hpp"
#include "x86real.h"

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

	// Current loop counter for the (broken) [EO_LOOP_*] instructions.
	uint8_t loop_i;

	enemy_pos_type_t pos_type;
	int8_t padding[14];

	// Sprite size in 16-pixel units. 0 = invalid.
	// ZUN bloat: Fully redundant with [size_pixels]. The code should
	// explicitly assign [explosion_max_enemy_hits_half] in the [EO_SPAWN]
	// handler and then use [size_pixels] everywhere else.
	uvram_word_amount_8_t& size_words(void) {
		return static_cast<uvram_word_amount_8_t>(
			explosion_max_enemy_hits_half
		);
	}
};

inline void enemy_t_verify(void) {
	efe_subclass_verify(reinterpret_cast<enemy_t *>(nullptr));
}

#pragma option -a2

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

void near enemy_explosion_put(void)
{
	sprite16_offset_t so;
	pixel_t size;
	uint8_t cel;

	if(p->frame < KEYFRAME_HIT_ENEMIES) {
		so = SO_EXPLOSIONS[p->size_words() - 1][0];
	} else if(p->frame < KEYFRAME_DECAY) {
		cel = (p->frame / 4);
		so = SO_EXPLOSIONS[p->size_words() - 1][1 + (cel & 1)];
	} else if(p->frame < KEYFRAME_DONE) {
		// ZUN bloat: ^ The condition doesn't need to duplicate the keyframe.
		so = SO_EXPLOSIONS[p->size_words() - 1][3];
	}

	size = (p->size_pixels + 16);
	sprite16_put_size.w.v = to_vram_word(size);
	sprite16_put_size.h = (size / 2);

	// ZUN bloat: A separate variable doesn't hurt.
	#define size_half size
	size_half >>= 1;

	screen_x_t left;
	screen_y_t top;
	left = (playfield_fg_x_to_screen(p->center.x, p->pid) - size_half);
	top  = (playfield_fg_y_to_screen(p->center.y, p->pid) - size_half);
	sprite16_put(left, top, so);

	#undef size_half
}

#undef p
#pragma codeseg ENEMY_2_TEXT main_04 // ZUN bloat

void pascal near enemy_formation_spawn(
	int formation_type, pid_t pid, enemy_pos_type_t pos_type
)
{
	int script_i = (formation_type * FORMATION_ENEMIES_MAX);
	enemy_formation_type = formation_type;
	enemy_formation_i = 0;
	while(enemy_formation_i < formation_enemy_count[formation_type]) {
		enemies_add(formation_scripts[script_i], pid, pos_type);
		enemy_formation_i++;
		script_i++;
	}
}

void pascal near enemy_formations_update_for(pid_t pid)
{
	if(enemies_alive[pid]) {
		return;
	}
	uint8_t p = formation_p[pid];

	// Could be done at the call site, but eh… Not worth a bloat designation.
	enemy_speed = (round_speed / ((ROUND_SPEED_MAX + 1) / ENEMY_SPEED_COUNT));

	enemy_formation_spawn(
		formation_type_ring[p], pid, formation_pos_type_ring[p]
	);
	formation_p[pid]++;
}

void enemy_formations_update(void)
{
	if(hud_start_flag != HSF_DONE) {
		return;
	}
	static_assert(PLAYER_COUNT == 2);
	enemy_formations_update_for(0);
	enemy_formations_update_for(1);
}

void enemy_formations_load(void)
{
	enedat_header_t header;

	extern const char ENEDAT_DAT[];
	file_ropen(ENEDAT_DAT);
	file_read(&header, sizeof(header));
	enedat_2 = static_cast<uint8_t __seg *>(hmem_allocbyte(header.size));
	formation_scripts = HMem<enemy_script_p>::alloc(
		FORMATIONS_MAX * FORMATION_ENEMIES_MAX
	);
	formation_type_ring = HMem<uint8_t>::alloc(FORMATION_RING_SIZE);
	formation_pos_type_ring = HMem<enemy_pos_type_t>::alloc(
		FORMATION_RING_SIZE
	);
	enedat = enedat_2;
	file_read(enedat, header.size);
	file_close();

	unsigned int enedat_p = 0;
	int enemy_i;
	int enemy_count;
	unsigned int script_size;
	int formation_i = 0;
	while(1) {
		// ZUN landmine: Not validated against [FORMATION_ENEMIES_MAX].
		enemy_count = *reinterpret_cast<uint16_t *>(&enedat[enedat_p]);
		if(enemy_count == 0) {
			break;
		}

		formation_enemy_count[formation_i] = enemy_count;
		enedat_p += sizeof(uint16_t);
		for(enemy_i = 0; enemy_i < enemy_count; enemy_i++) {
			script_size = enedat[enedat_p];
			enedat_p++;
			*(
				formation_scripts + (formation_i * FORMATION_ENEMIES_MAX) +
				enemy_i
			) = reinterpret_cast<uint8_t near *>(enedat_p);

			enedat_p += script_size;
		}
		formation_i++;
	};
	formation_count = formation_i;
}

void enemy_formations_randomize(void)
{
	uint8_t next;

	// ZUN landmine: Uninitialized. In ZUN's original binary, this variable is
	// allocated to a stack address that always holds a value of 0x5E. That
	// value comes from the lower 8 bits of the [InitStart] constant that the
	// C0 entry point assigns to `SI`, which is then callee-saved onto the
	// stack by every function that uses `SI` from the start of the program to
	// the first call of this function.
	// Should be initialized to `formation_count` to ensure deterministic RNG
	// behavior.
	uint8_t prev;

	for(int i = 0; i < FORMATION_RING_SIZE; i++) {
		do {
			next = (irand() % formation_count);
		} while(next == prev);
		formation_type_ring[i] = next;
		prev = next;

		formation_pos_type_ring[i] = ((irand() & 1) * EPT_DO_NOT_MIRROR_X);
	}
	static_assert(PLAYER_COUNT == 2);
	formation_p[0] = 0;
	formation_p[1] = 0;
	enemies_alive[0] = 0;
	enemies_alive[1] = 0;
}

void enemy_formations_free(void)
{
	hmem_free(enedat);
	hmem_free(formation_scripts);
	hmem_free(formation_type_ring);
	hmem_free(formation_pos_type_ring);
}

// ZUN quirk: The addition of these two expressions is a convoluted, slow, and
// bizarrely inaccurate way of expressing
//
// 	(([v] * ([enemy_speed] + 6)) / 9)
//
// with the added inaccuracy of two integer divisions causing the result to be
// off by 1 at regular intervals.
// (The result for [v] == 1.0f and [enemy_speed] == 3 is 0.9375f, not the 1.0f
// you'd get from the simplified formula.)
inline subpixel_t enemy_speedtune_1(subpixel_t v) {
	return ((enemy_speed * v) / 9);
}
inline subpixel_t enemy_speedtune_2(subpixel_t v) {
	return ((2 * v) / 3);
}

bool near enemy_move_and_clip(void)
{
	enemy_t near& p = *efe_p.enemy;
	subpixel_t velocity;

	velocity = p.velocity.x.v;
	velocity = (enemy_speedtune_1(velocity) + enemy_speedtune_2(velocity));
	if(p.pos_type & EPT_DO_NOT_MIRROR_X) {
		p.center.x.v += velocity;
	} else {
		p.center.x.v -= velocity;
	}
	if(p.pos_type & EPT_CLIP_X) {
		if(
			(p.center.x.v <= to_sp(-32.0f)) ||
			(p.center.x.v >= to_sp(PLAYFIELD_W + 32.0f))
		) {
			goto clip;
		}
	}

	velocity = p.velocity.y.v;
	velocity = (enemy_speedtune_1(velocity) + enemy_speedtune_2(velocity));
	p.center.y.v += velocity;
	if(p.pos_type & EPT_CLIP_BOTTOM) {
		if((p.center.y.v >= to_sp(PLAYFIELD_H + 32.0f))) {
			goto clip;
		}
	}
	return false;

clip:
	p.flag = EFF_FREE;
	return true;
}

void near enemy_velocity_set_from_angle_and_speed(void)
{
	#define p (*efe_p.enemy)

	asm { push es; } // ZUN bloat: Yes, no point to this at all...
	vector2(p.velocity.x.v, p.velocity.y.v, p.angle.split.coarse, p.speed);
	asm { pop es; } // …or to this.

	#undef p
}

void near enemy_angle_update(void)
{
	#define p (*efe_p.enemy)

	// Looks like the tuning done for speeds, except that this instance of
	// enemy_speedtune_1() receives the result of an inlined version of
	// enemy_speedtune_2() instead of [p.angle_speed], resulting in smaller
	// angles as [enemy_speed] increases.
	//
	// Also note how a signed 16-bit integer is technically not enough to cover
	// the entire scaled range of possible [angle_speed] values here. The extra
	// factor of 2 means that the 8-bit [angle_speed] gets left-shifted by 9
	// bits, causing [speed_wide] to already overflow into negative numbers for
	// angle speeds ≥0x40 rather than ≥0x80. Hence, [speed_wide] would have
	// needed to hold at least 17 bits to store the correct un-truncated result
	// here.
	// Then again, who would seriously use angle speeds of 90° *per frame*. -8
	// and +8 are the highest speeds used in the original scripts. So this is
	// neither a quirk nor a landmine.
	int16_t speed_wide = ((p.angle_speed * (0x100 * 2)) / 3);
	speed_wide += enemy_speedtune_1(speed_wide);
	p.angle.wide += speed_wide;

	#undef p
}

subpixel_length_8_t pascal near chain_pellet_speed(subpixel_length_8_t base)
{
	int v = base;
	v *= round_speed;
	v >>= (SUBPIXEL_BITS + 3);
	v += base;
	if(v >= (ROUND_SPEED_MAX + 1)) {
		v = ROUND_SPEED_MAX;
	}
	return v;
}

bool near enemy_run(void)
{
	enemy_t near& enemy = *efe_p.enemy;

	// ZUN bloat: Can be replaced with either direct assignment, or a separate,
	// more explicitly named variable.
	int16_t var;

	player_stuff_t near *player;

	// ZUN bloat: There are better ways of moving through the instruction
	// stream than duplicating ([enemy.script_base] + [enemy.script_ip]).
	uint8_t __es *script;

	uint8_t op_size;
	uint8_t op_duration;
	subpixel_length_8_t speed_on_sine_axis;
	Subpixel8 velocity_tmp;
	pid_t pid = enemy.pid;

	player = &players[pid];
	_ES = FP_SEG(enedat_2);
	script = static_cast<uint8_t __es *>(enemy.script_base);
	script += enemy.script_ip;

	// ZUN bloat: Every clipped branch that returns `true` redundantly sets the
	// [enemy.flag] to [EFF_FREE].
	while(1) {
		switch(reinterpret_cast<enedat_op_t __es *>(script)->code) {
		case EO_MOVE_LINEAR:
		case EO_MOVE_LINEAR_STOP_AT_PLAYER_Y:
		case EO_MOVE_LINEAR_STOP_AT_PLAYER_X:
			#define p reinterpret_cast<enedat_op_linear_t __es *>(script)
			if(enemy.script_op_frame == 0) {
				enemy.speed = p->speed;
				enemy.angle.split.coarse = p->angle;
				enemy.angle.split.fine = 0;
				enemy_velocity_set_from_angle_and_speed();
			}
			if(!enemy_move_and_clip()) {
				op_duration = p->duration;
				op_size = sizeof(*p);

				enum {
					HALF_W = TO_SP(PLAYER_W / 2),
					HALF_H = TO_SP(PLAYER_H / 2),
				};
				if(p->code == EO_MOVE_LINEAR_STOP_AT_PLAYER_Y) {
					if(
						(enemy.center.y.v >= (player->center.y.v - HALF_H)) &&
						(enemy.center.y.v <= (player->center.y.v + HALF_H))
					) {
						enemy.script_op_frame = 0;
						break;
					}
				} else if(p->code == EO_MOVE_LINEAR_STOP_AT_PLAYER_X) {
					if(
						(enemy.center.x.v >= (player->center.x.v - HALF_W)) &&
						(enemy.center.x.v <= (player->center.x.v + HALF_W))
					) {
						enemy.script_op_frame = 0;
						break;
					}
				}
			} else {
				enemy.flag = EFF_FREE;
				return true;
			}
			#undef p
			goto wait_and_return;

		case EO_MOVE:
			#define p reinterpret_cast<enedat_op_duration_t __es *>(script)
			if(!enemy_move_and_clip()) {
				op_duration = p->duration;
				op_size = sizeof(*p);
			} else {
				enemy.flag = EFF_FREE;
				return true;
			}
			#undef p
			goto wait_and_return;

		case EO_MOVE_WITH_SPEED:
			#define p reinterpret_cast<enedat_op_speed_t __es *>(script)
			if(enemy.script_op_frame == 0) {
				enemy.speed = p->speed;
				enemy_velocity_set_from_angle_and_speed();
			}
			if(!enemy_move_and_clip()) {
				op_duration = p->duration;
				op_size = sizeof(*p);
			} else {
				enemy.flag = EFF_FREE;
				return true;
			}
			#undef p
			goto wait_and_return;

		case EO_MOVE_CIRCULAR:
		case EO_MOVE_CIRCULAR_PLUS:
			#define p reinterpret_cast<enedat_op_circular_base_t __es *>(script)
			if(enemy.script_op_frame == 0) {
				enemy.angle.split.coarse = p->angle_start;
				enemy.angle.split.fine = 0;
				enemy.angle_speed = p->angle_speed;
			}
			enemy.speed = p->speed;
			enemy_velocity_set_from_angle_and_speed();

			if(p->code == EO_MOVE_CIRCULAR_PLUS) {
				#undef p
				#define p ( \
					reinterpret_cast<enedat_op_circular_plus_t __es *>(script) \
				)
				enemy.velocity.x.v += p->velocity_x_plus.v;
				enemy.velocity.y.v += p->velocity_y_plus.v;
				op_duration = p->duration;
				op_size = sizeof(*p);
			} else {
				#undef p
				#define p reinterpret_cast<enedat_op_circular_t __es *>(script)
				op_duration = p->duration;
				op_size = sizeof(*p);
			}

			if(!enemy_move_and_clip()) {
				enemy_angle_update();
			} else {
				enemy.flag = EFF_FREE;
				return true;
			}
			#undef p
			goto wait_and_return;

		case EO_WAIT:
			#define p reinterpret_cast<enedat_op_duration_t __es *>(script)
			op_duration = p->duration;
			op_size = sizeof(*p);
			#undef p
			goto wait_and_return;

		case EO_MOVE_SINE_X:
		case EO_MOVE_SINE_Y:
			#define p reinterpret_cast<enedat_op_sine_t __es *>(script)
			if(enemy.script_op_frame == 0) {
				enemy.angle.wide = 0x00;
				enemy.angle_speed = p->angle_speed;
			}
			speed_on_sine_axis = p->speed_on_sine_axis; // ZUN bloat
			enemy.velocity.x.v = polar_x_fast(
				0, speed_on_sine_axis, enemy.angle.split.coarse
			);
			enemy.velocity.y.v = p->velocity_on_linear_axis.v;
			if(p->code == EO_MOVE_SINE_Y) {
				velocity_tmp.v = enemy.velocity.x.v;
				enemy.velocity.x.v = enemy.velocity.y.v;
				enemy.velocity.y.v = velocity_tmp.v;
			}

			if(!enemy_move_and_clip()) {
				enemy_angle_update();
			} else {
				enemy.flag = EFF_FREE;
				return true;
			}

			op_duration = p->duration;
			op_size = sizeof(*p);
			#undef p
			goto wait_and_return;

		case EO_STOP:
			enemy.flag = EFF_FREE;
			return true;

		case EO_SPAWN:
			#define p reinterpret_cast<enedat_op_spawn_t __es *>(script)
			enemy.flag = EF_RUNNING_SPAWNED;

			var = p->center_x_divided_by_8;
			if(enemy.pos_type & EPT_DO_NOT_MIRROR_X) {
				enemy.center.x.v = (var << (3 + SUBPIXEL_BITS));
			} else {
				enemy.center.x.v = (
					to_sp(PLAYFIELD_W) - (var << (3 + SUBPIXEL_BITS))
				);
			}

			var = p->center_y_divided_by_8;
			enemy.center.y.v = (var << (3 + SUBPIXEL_BITS));

			enemy.size_words() = p->size_words[enemy_speed];
			enemy.size_pixels = (enemy.size_words() * 16);
			enemy.hp = p->hp[enemy_speed];
			enemy.pos_type |= ((p->clip_x != false) * EPT_CLIP_X);
			enemy.pos_type |= ((p->clip_bottom != false) * EPT_CLIP_BOTTOM);

			op_size = sizeof(*p);
			#undef p
			break;

		case EO_CLIP_X:
			enemy.pos_type |= EPT_CLIP_X;
			op_size = sizeof(enedat_op_t);
			break;

		// ZUN bloat: The next three operations are unused in the original
		// `ENEDAT.DAT`.
		case EO_CLIP_BOTTOM:
			enemy.pos_type |= EPT_CLIP_BOTTOM;
			op_size = sizeof(enedat_op_t);
			break;

		// ZUN landmine: These loop instructions don't really work for two
		// reasons:
		// • If the branch is taken, the IP displacement is only applied to
		//   [enemy.script_ip] – not to [script], which the `switch` after the
		//   `continue` immediately reads from. Yet another symptom of the
		//   bloat behind [script] as a whole.
		// • And since [op_size] is not set in that case either, execution will
		//   effectively jump to some place further down the instruction stream
		//   that depends on the previously processed instruction.
		//
		// ZUN bloat: Also, both of these implementations only differ in a
		// single line:
		case EO_LOOP_ABS:
			#define p reinterpret_cast<enedat_op_loop_t __es *>(script)
			if(enemy.loop_i >= p->count) {
				enemy.loop_i = 0;
				op_size = sizeof(*p);
			} else {
				enemy.loop_i++;
				enemy.script_ip = p->ip_disp; // ← This one...
				script += op_size;
				continue;
			}
			#undef p
			break;

		case EO_LOOP_REL:
			#define p reinterpret_cast<enedat_op_loop_t __es *>(script)
			if(enemy.loop_i >= p->count) {
				enemy.loop_i = 0;
				op_size = sizeof(*p);
			} else {
				enemy.loop_i++;
				enemy.script_ip += p->ip_disp; // ← …vs. this one.
				script += op_size;
				continue;
			}
			#undef p
			break;

		default:
		wait_and_return:
			var = op_duration;
			var = (((var / 2) * 3) - ((enemy_speed * var) / 6));
			if(var <= enemy.script_op_frame) {
				enemy.script_op_frame = 0;
				enemy.script_ip += op_size;
			} else {
				enemy.script_op_frame++;
			}
			return false;
		}
		enemy.script_ip += op_size;
		script += op_size;
	}
}
