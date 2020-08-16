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

/// Midbosses
/// ---------
typedef struct {
	motion_t pos;
	unsigned int frames_until;
	int hp;
	unsigned char sprite;
	unsigned char phase;
	int phase_frame;
	// Treated as a bool in TH04
	unsigned char damage_this_frame;
	unsigned char angle;
} midboss_stuff_t;

extern midboss_stuff_t midboss;

// Callbacks
extern  farfunc_t_near midboss_update_func;
extern nearfunc_t_near midboss_render_func;

#define MIDBOSS_DEC(stage) \
	void pascal  far midboss##stage##_update(void); \
	void pascal near midboss##stage##_render(void);
/// ---------

/// Score
/// -----
extern unsigned long score_delta;

void pascal near score_update_and_render(void);

// Adds the entire score delta at once to the current score.
void pascal score_delta_commit(void);
/// -----
