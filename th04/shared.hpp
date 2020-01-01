/* ReC98
 * -----
 * Types shared between TH04 and TH05
 */

/// Math
/// ----
#include "th03/math/subpixel.hpp"
#include "th04/math/motion.hpp"
#include "th03/math/randring.h"
/// ----

/// Rank
/// ----
int pascal far select_for_rank(
	int for_easy, int for_normal,
	int for_hard, int for_lunatic
);
/// ----

/// Formats
/// -------
#include "th03/formats/cdg.h"
#include "th04/formats/bb.h"
/// -------

/// Sound
/// -----
#include "th02/snd/snd.h"
/// -----

/// Player
/// ------
#include "th04/player/player.h"
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

// Bosses
// ------
typedef struct {
	motion_t pos;
	int hp;
	unsigned char sprite;
	unsigned char phase;
	int phase_frame;
	unsigned char damage_this_frame;
	unsigned char mode;
	// Used for both movement and bullet angles.
	unsigned char angle;
	unsigned char mode_change;
	int phase_end_hp;
} boss_stuff_t;

extern boss_stuff_t boss;
extern SPPoint boss_hitbox_radius;

// Callbacks
extern  farfunc_t_near boss_update;
extern nearfunc_t_near boss_fg_render;
extern  farfunc_t_near boss_update_func;
extern nearfunc_t_near boss_backdrop_colorfill;
extern nearfunc_t_near boss_bg_render_func;
extern nearfunc_t_near boss_fg_render_func;

#define BOSS_DEC(name) \
	void pascal  far name##_update(void); \
	void pascal near name##_bg_render(void); \
	void pascal near name##_fg_render(void);

// Explosions
void pascal far explosions_small_reset(void);
// ------

/// Score
/// -----
#define score_delta SCORE_DELTA
extern unsigned long score_delta;

void pascal near score_update_and_render(void);

// Adds the entire score delta at once to the current score.
void pascal score_delta_commit(void);
/// -----
