#include "th02/main/midboss/midboss.hpp"
#include "th04/main/playfld.hpp"

static const pixel_t MIDBOSS_W_MAX = 64;
static const pixel_t MIDBOSS_H_MAX = 64;
static const unsigned int MIDBOSS_BONUS_UNIT_VALUE = 1280;

struct midboss_stuff_t {
	PlayfieldMotion pos;
	unsigned int frames_until;
	int hp;
	unsigned char sprite;
	unsigned char phase;
	int phase_frame;
	// Treated as a bool in TH04
	unsigned char damage_this_frame;
	unsigned char angle;
};

extern midboss_stuff_t midboss;

// Grants a score bonus of [units * MIDBOSS_BONUS_UNIT_VALUE], rendered as one
// new point number popup per unit around the midboss sprite.
void pascal near midboss_score_bonus(unsigned int units);

// Callbacks. *_func() functions are "activated" by setting the regular
// function once the midboss battle starts.
extern nearfunc_t_near midboss_invalidate;
extern     func_t_near midboss_update;
extern nearfunc_t_near midboss_render;
extern     func_t_near midboss_update_func;
extern nearfunc_t_near midboss_render_func;

void midboss_reset(void);
void pascal near midboss_invalidate_func(void);

// Activates the midboss battle if [stage_frame] == [midboss.frames_until].
void midboss_activate_if_stage_frame_is_midboss_start_frame(void);

// Processes any collision of player shots within a box with the given radius
// around the current position of the midboss. Returns the total amount of
// damage dealt to it this frame, and plays the given sound effect if that
// amount is nonzero.
int pascal near midboss_hittest_shots_damage(
	subpixel_t radius_x, subpixel_t radius_y, int se_on_hit
);

// Directly subtracts the dealt damage from [midboss.hp], like
// boss_hittest_shots().
inline void midboss_hittest_shots(subpixel_t radius_x, subpixel_t radius_y) {
	midboss.damage_this_frame = midboss_hittest_shots_damage(
		radius_x, radius_y, 4
	);
	midboss.hp -= midboss.damage_this_frame;
}

// Readability wrapper, consistent with boss_hittest_shots_invincible().
inline int midboss_hittest_shots_invincible(
	subpixel_t radius_x, subpixel_t radius_y
) {
	return midboss_hittest_shots_damage(radius_x, radius_y, 10);
}

// ZUN quirk: This is the place where [damage_this_frame] is reset, but this
// function is typically not called during PHASE_EXPLODE_BIG. As a result, the
// nonzero [damage_this_frame] value that caused the midboss to be defeated in
// the first place is carried over to the next midboss, causing it to flash
// white during the first frame that calls this function.
#define midboss_put_generic(left, top, patnum) { \
	if(midboss.damage_this_frame == 0) { \
		super_roll_put(left, top, patnum); \
	} else { \
		super_roll_put_1plane(left, top, patnum, 0, super_plane(V_WHITE)); \
		midboss.damage_this_frame = 0; \
	} \
}

// Updates the defeat animation during PHASE_EXPLODE_BIG, and resets the boss
// during any other phase. TH04's version also takes ownership of
// [midboss.phase_frame], incrementing it on every call.
void near midboss_defeat_update(void);

// Renders the default PHASE_EXPLODE_BIG animation.
void near midboss_defeat_render(void);

#undef MIDBOSS_DEC
#define MIDBOSS_DEC(stage) \
	void pascal  far midboss##stage##_update(void); \
	void pascal near midboss##stage##_render(void);

// "midbosses" unfortunately has 9 characters and therefore won't work as a
// 8.3 filename. However, since these have no names anyway, we can just
// declare all of them here.
MIDBOSS_DEC(1);
MIDBOSS_DEC(2);
MIDBOSS_DEC(3);
MIDBOSS_DEC(4);
MIDBOSS_DEC(5);
MIDBOSS_DEC(x);
