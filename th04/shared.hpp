/* ReC98
 * -----
 * Types shared between TH04 and TH05
 */

#include "th04/common.h"

/// Math
/// ----
#include "th01/math/subpixel.hpp"
#include "th04/math/motion.hpp"
#include "th03/math/randring.h"
/// ----

/// Formats
/// -------
#include "th03/formats/cdg.h"
#include "th04/formats/bb.h"
/// -------

/// Player
/// ------
#include "th04/main/player/player.h"
#include "th04/score.h"
/// ------

/// Stages
/// ------
extern nearfunc_t_near stage_invalidate;
extern nearfunc_t_near stage_render;
/// ------

/// Score
/// -----
extern unsigned long score_delta;

void pascal near score_update_and_render(void);

// Adds the entire score delta at once to the current score.
void pascal score_delta_commit(void);
/// -----
