#include "th04/sprites/cels.h"

/// Stage-independent pattern numbers for the super_*() functions
/// -------------------------------------------------------------
/// Since super_entry_bfnt() doesn't take a "start patnum" parameter, the
/// order in which the files are loaded has to match the order here.
typedef enum {
	// miko32.bft
	// ----------
	PAT_CLOUD_BULLET16_BLUE = 20,
	PAT_CLOUD_BULLET16_BLUE_last = (PAT_CLOUD_BULLET16_BLUE + BULLET_CLOUD_CELS - 1),
	PAT_CLOUD_BULLET16_RED,
	// ----------
	// miko16.bft
	// ----------
	PAT_OPTION_REIMU = 38,
	PAT_OPTION_MARISA,
	PAT_ITEM = 44,

	PAT_BULLET16_N_OUTLINED_BALL_WHITE = 52,
	PAT_BULLET16_N_OUTLINED_BALL_RED,
	PAT_BULLET16_N_OUTLINED_BALL_GREEN,
	PAT_BULLET16_N_OUTLINED_BALL_BLUE,
	PAT_BULLET16_N_STAR,
	PAT_BULLET16_N_BALL_BLUE,
	PAT_BULLET16_N_SMALL_BALL_YELLOW,
	PAT_BULLET16_N_CROSS_YELLOW,
	PAT_BULLET16_N_SMALL_BALL_RED,
	PAT_BULLET16_N_BALL_RED,
	PAT_BULLET16_N_HEART_BALL_RED,

	PAT_EXPLOSION_SMALL = 68,

	PAT_BULLET_KILL = 72,
	PAT_BULLET_KILL_last = (PAT_BULLET_KILL + BULLET_DECAY_CELS - 1),
	PAT_BULLET16_D,
	PAT_BULLET16_D_BLUE = PAT_BULLET16_D,
	PAT_BULLET16_D_BLUE_last = (PAT_BULLET16_D_BLUE + BULLET_D_CELS - 1),
	PAT_BULLET16_D_YELLOW,	// Purple during the EX-Alice battle
	PAT_BULLET16_D_YELLOW_last = (PAT_BULLET16_D_YELLOW + BULLET_D_CELS - 1),

	PAT_DECAY_PELLET,
	PAT_DECAY_PELLET_last = (PAT_DECAY_PELLET + BULLET_DECAY_CELS - 1),
	PAT_DECAY_BULLET16,
	PAT_DECAY_BULLET16_last = (PAT_DECAY_BULLET16 + BULLET_DECAY_CELS - 1),
	// ----------
} main_patnum_t;
/// -------------------------------------------------------------
