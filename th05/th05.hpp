/* ReC98
 * -----
 * Include file for TH05
 */

#include "ReC98.h"
#include "th01/math/area.hpp"
#include "th04/shared.hpp"
#include "th05/resident.hpp"

/// Formats
/// -------
dots8_t __seg* pascal near bb_load(const char far *fn);
/// -------

/// Stages
/// ------
void pascal near stage2_update(void);
void pascal near stage2_invalidate(void);
/// ------

/// Bosses
/// ------
#include "th05/main/boss/boss.hpp"

BOSS_DEC(sara);
BOSS_DEC(louise);
BOSS_DEC(alice);

BOSS_DEC(mai_yuki);
// Pointing to the same address as [boss2]! Might not be possible anymore once
// that variable has to be moved to a C++ translation unit...
extern boss_stuff_t yuki;

BOSS_DEC(yumeko);
extern unsigned char yumeko_interval_phase4;
extern unsigned char yumeko_interval_phase7;

BOSS_DEC(shinki);
BOSS_DEC(exalice);
/// ------
