/* ReC98
 * -----
 * Include file for TH05
 */

#include "ReC98.h"
#include "th04/shared.hpp"
#include "th05/resident.hpp"

/// Formats
/// -------
bb_seg_t pascal near bb_load(const char far *fn);
/// -------

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
