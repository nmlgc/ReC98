#include "th04/sprites/cels.h"

#define PARTICLE_W 16
#define PARTICLE_H 16

#define PARTICLE_CELS 4
#define B4BALL_CELS 4
#define B4_CELS 16

/// Pattern numbers for the super_*() functions.
/// Since super_entry_bfnt() doesn't take a "start patnum" parameter, the
/// order in which the files are loaded has to match the order here.
typedef enum {
	/// Stage-independent
	/// =================
	// miko32.bft
	// ----------
	PAT_ENEMY_KILL = 4,
	PAT_ENEMY_KILL_last = (PAT_ENEMY_KILL + ENEMY_KILL_CELS - 1),
	PAT_CLOUD_BULLET16_BLUE,
	PAT_CLOUD_BULLET16_BLUE_last = (PAT_CLOUD_BULLET16_BLUE + BULLET_CLOUD_CELS - 1),
	PAT_CLOUD_BULLET16_RED,
	// ----------
	// reimu16.bft / mari16.bft / mima16.bft / yuka16.bft
	// --------------------------------------------------
	PAT_SHOT_SUB = 22,
	PAT_OPTION = 26,
	// --------------------------------------------------
	// miko16.bft / st06_16.bft
	// ------------------------
	PAT_ITEM = 36,

	// Non-directional bullets
	PAT_BULLET16_N_BLUE = 44,
	PAT_BULLET16_N_BALL_BLUE = PAT_BULLET16_N_BLUE,
	PAT_BULLET16_N_OUTLINED_BALL_BLUE,
	PAT_BULLET16_N_SMALL_BALL_BLUE,
	PAT_BULLET16_N_CROSS_BLUE,	// Green during the EX-Alice battle
	PAT_BULLET16_N_RED,
	PAT_BULLET16_N_BALL_RED = PAT_BULLET16_N_RED,
	PAT_BULLET16_N_OUTLINED_BALL_RED,
	PAT_BULLET16_N_SMALL_BALL_RED,
	PAT_BULLET16_N_STAR,

	// Directional bullets
	PAT_BULLET16_D,
	PAT_BULLET16_D_BLUE = PAT_BULLET16_D,
	PAT_BULLET16_D_BLUE_last = (PAT_BULLET16_D_BLUE + BULLET_D_CELS - 1),
	PAT_BULLET16_D_GREEN,	// Purple during the EX-Alice battle
	PAT_BULLET16_D_GREEN_last = (PAT_BULLET16_D_GREEN + BULLET_D_CELS - 1),
	// Vector bullets
	PAT_BULLET16_V,
	PAT_BULLET16_V_RED = PAT_BULLET16_V,
	PAT_BULLET16_V_RED_last = (PAT_BULLET16_V_RED + BULLET_V_CELS - 1),
	PAT_BULLET16_V_BLUE,	// Yellow during the EX-Alice battle
	PAT_BULLET16_V_BLUE_last = (PAT_BULLET16_V_BLUE + BULLET_V_CELS - 1),

	PAT_CLOUD_PELLET,
	PAT_CLOUD_PELLET_last = (PAT_CLOUD_PELLET + BULLET_CLOUD_CELS - 1),

	PAT_BULLET_KILL,
	PAT_BULLET_KILL_last = (PAT_BULLET_KILL + BULLET_DECAY_CELS - 1),
	PAT_DECAY_PELLET,
	PAT_DECAY_PELLET_last = (PAT_DECAY_PELLET + BULLET_DECAY_CELS - 1),
	PAT_DECAY_BULLET16,
	PAT_DECAY_BULLET16_last = (PAT_DECAY_BULLET16 + BULLET_DECAY_CELS - 1),

	PAT_FIREWAVE_LEFT = 168,	// st06_16.bft only
	PAT_FIREWAVE_RIGHT,     	// st06_16.bft only

	PAT_EXPLOSION_SMALL,

	PAT_PARTICLE = 172,
	PAT_PARTICLE_last = (PAT_PARTICLE + PARTICLE_CELS),
	// ------------------------
	/// =================

	/// Stage 4
	/// =======
	// st03.bb1 / st03.bb2
	// -------------------
	// Internally, both Mai and Yuki use Mai's patnums, starting at PAT_MAI.
	// They are only differentiated inside the rendering function, by adding
	// B4_CELS onto the patnum for Yuki. Thus, both files are assumed to have
	// the same number of sprites.
	PAT_MAI = 180,
	PAT_B4_STILL = PAT_MAI,
	PAT_B4_RIGHT,
	PAT_B4_LEFT,

	PAT_YUKI = (PAT_MAI + B4_CELS),
	// -------------------

	// st03.bb3
	// --------
	PAT_B4BALL_SNOW = 212,
	PAT_B4BALL_SNOW_last = (PAT_B4BALL_SNOW + B4BALL_CELS - 1),
	PAT_B4BALL_FIRE,
	PAT_B4BALL_FIRE_last = (PAT_B4BALL_FIRE + B4BALL_CELS - 1),
	PAT_B4BALL_SNOW_HIT,
	PAT_B4BALL_SNOW_HIT_last = (PAT_B4BALL_SNOW_HIT + B4BALL_CELS - 1),
	PAT_DECAY_B4BALL,
	PAT_DECAY_B4BALL_last = (PAT_DECAY_B4BALL + BULLET_DECAY_CELS - 1),
	// --------
	/// =======

	/// Stage 5
	/// =======
	// st04.bb2
	// --------
	PAT_KNIFE = 193,
	PAT_KNIFE_last = (PAT_KNIFE + BULLET_V_CELS),
	PAT_DECAY_KNIFE,
	PAT_DECAY_KNIFE_last = (PAT_DECAY_KNIFE + BULLET_DECAY_CELS - 1),
	/// -------
	/// =======

	/// Stage 6
	/// =======
	// st05.bb4
	// --------
	PAT_B6BALL_BLUE_1 = 200,
	PAT_B6BALL_PURPLE,
	PAT_B6BALL_BLUE_2,
	PAT_B6BALL_BLUE_3,
	PAT_DECAY_B6BALL,
	PAT_DECAY_B6BALL_last = (PAT_DECAY_B6BALL + BULLET_DECAY_CELS - 1),
	/// -------
	/// =======
} main_patnum_t;
