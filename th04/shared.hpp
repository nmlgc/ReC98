/* ReC98
 * -----
 * Types shared between TH04 and TH05
 */

#define DEFCONV pascal

/// Math
/// ----
typedef int subpixel_t;

inline subpixel_t to_sp(float screen_v) {
	return static_cast<subpixel_t>(screen_v * 16.0f);
}

class Subpixel {
public:
	// Code generation will require direct access to v, if performing
	// arithmetic with a local variable...
	subpixel_t v;

	void operator +=(float screen_v) {
		this->v += to_sp(screen_v);
	}

	void operator -=(float screen_v) {
		this->v -= to_sp(screen_v);
	}

	void operator =(float screen_v) {
		v = to_sp(screen_v);
	}
};

struct SPPoint {
	Subpixel x, y;

	void set(float screen_x, float screen_y) {
		x = screen_x;
		y = screen_y;
	}
};

typedef struct {
	SPPoint cur;
	SPPoint prev;
	SPPoint velocity;

	void init(float screen_x, float screen_y) {
		cur.x = screen_x;
		prev.x = screen_x;
		cur.y = screen_y;
		prev.y = screen_y;
	}
} motion_t;

#include "th03/math/randring.h"

inline char randring_angle(char random_range, char offset)
{
	return randring1_next16_and(random_range) + offset;
}
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

// Shots
// -----
// Sets [velocity] to a vector with the given [angle] and a 12-pixel length.
//
// TH05 also insists on setting shot_t::angle via a ridiculous out-of-bounds
// access, and therefore *must* be called with [velocity] pointing inside a
// shot_t structure!
SPPoint pascal near shot_velocity_set(
	SPPoint near* velocity, unsigned char angle
);

struct shot_t {
	char flag;
	char age;
	motion_t pos;
	// The displayed sprite changes between this one and
	// [patnum_base + 1] every two frames.
#if GAME == 5
	char patnum_base;
	char type;
#else
	int patnum_base;
#endif
	char damage;
	char angle; // Unused in TH04

	void from_option_l(float offset = 0.0f) {
		this->pos.cur.x -= PLAYER_OPTION_DISTANCE + offset;
	}

	void from_option_r(float offset = 0.0f) {
		this->pos.cur.x += PLAYER_OPTION_DISTANCE + offset;
	}

	void set_option_sprite() {
		this->patnum_base = 22;
	}

	void set_option_sprite_and_damage(char damage) {
		set_option_sprite();
		this->damage = damage;
	}

	void set_random_angle_forwards(char random_range = 15, char offset = 184) {
		shot_velocity_set(
			(SPPoint near*)&this->pos.velocity,
			randring_angle(random_range, offset)
		);
	}
};

// Searches and returns the next free shot slot, or NULL if there are no more
// free ones.
shot_t near* pascal near shots_add(void);
// -----
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
