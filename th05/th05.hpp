/* ReC98
 * -----
 * Include file for TH05
 */

#include "ReC98.h"
#include "th04/shared.hpp"

/// Formats
/// -------
bb_seg_t pascal near bb_load(const char far *fn);
/// -------

/// Player
/// ------
// Shots
// -----
// Shot cycle bitflags
#define SC_1X 0x8 // Triggered 1× per cycle
#define SC_2X 0x2 // Triggered 2× per cycle
#define SC_3X 0x1 // Triggered 3× per cycle
#define SC_6X 0x4 // Triggered 6× per cycle

// Returns the current shot cycle, and prepares everything for more shots
// being added.
char pascal near shot_cycle_init(void);

// Common per-iteration data for shot type control functions.
// (Yeah, code generation mandated additions to [i] to be wrapped into
// functions, so why not bundle all of the rather intricate shot handling
// stuff as well.)
struct ShotAddIterator {
	unsigned char angle;
	unsigned char i;

	ShotAddIterator(unsigned char count)
		: i(count) {
	}

	void add_secondary(unsigned char n) {
		i += n;
	}

	unsigned char next(void) {
		return i -= 1;
	}
};

// Requires [cycle] to be defined in some way. (It's _AL in the original game,
// and I didn't want to pollute the namespace)
#define SHOT_FUNC_INIT(count, primary_cycle, secondary_cycle, secondary_offset_expr) \
	shot_t near *shot; \
	ShotAddIterator sai(count); \
	\
	cycle = shot_cycle_init(); \
	if((cycle & (primary_cycle | secondary_cycle)) == 0) { \
		return; \
	} \
	if(cycle & secondary_cycle) { \
		sai.secondary_offset_expr; \
	}
// -----
/// ------

/// Stages
/// ------
void pascal near stage2_update(void);
void pascal near stage2_invalidate(void);
/// ------

/// Midbosses
/// ---------
MIDBOSS_DEC(1);
MIDBOSS_DEC(2);
MIDBOSS_DEC(3);
MIDBOSS_DEC(4);
MIDBOSS_DEC(5);
MIDBOSS_DEC(x);
/// ---------

/// Bosses
/// ------
// Callbacks
extern nearfunc_t_near boss_custombullets_render;

extern unsigned int boss_sprite_left;
extern unsigned int boss_sprite_right;
extern unsigned int boss_sprite_stay;

extern boss_stuff_t boss2;

BOSS_DEC(sara);
BOSS_DEC(louise);
BOSS_DEC(alice);

BOSS_DEC(mai_yuki);
// Pointing to the same address as `boss2`! Might not be possible anymore once
// that variable has to be moved to a C++ translation unit...
extern boss_stuff_t yuki;

BOSS_DEC(yumeko);
extern unsigned char yumeko_interval_phase4;
extern unsigned char yumeko_interval_phase7;

BOSS_DEC(shinki);
BOSS_DEC(exalice);
/// ------
