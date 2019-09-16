/* ReC98
 * -----
 * Types shared between TH04 and TH05
 */

/// Math
/// ----
class Subpixel {
private:
	int v;

public:
	Subpixel() {}
	Subpixel(float screen_v) { *this = screen_v; }

	Subpixel& operator =(float screen_v) {
		v = static_cast<int>(screen_v * 16.0f);
		return *this;
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
extern  farfunc_t_near boss_update_func;
extern nearfunc_t_near boss_backdrop_colorfill;
extern nearfunc_t_near boss_bg_render_func;
extern nearfunc_t_near boss_fg_render_func;

#define BOSS_DEC(name) \
	void pascal  far name##_update(void); \
	void pascal near name##_bg_render(void); \
	void pascal near name##_fg_render(void);
// ------

/// Score
/// -----
extern unsigned long score_delta;

void pascal near score_update_and_render(void);

// Adds the entire score delta at once to the current score.
void pascal score_delta_commit(void);
/// -----
