#include "th01/main/playfld.hpp"
#include "th01/formats/ptn.hpp"

static const pixel_t PLAYER_W = 32;
static const pixel_t PLAYER_H = 32;

static const screen_x_t PLAYER_LEFT_MIN = (PLAYFIELD_LEFT);
static const screen_x_t PLAYER_LEFT_MAX = (PLAYFIELD_RIGHT - PLAYER_W);

static const screen_x_t PLAYER_LEFT_START = (PLAYFIELD_CENTER_X - (PLAYER_W / 2));

static const int PLAYER_MISS_INVINCIBILITY_FRAMES = 150;

extern screen_x_t player_left;
static const screen_y_t player_top = (PLAYFIELD_BOTTOM - PLAYER_H);
extern bool player_deflecting;
extern bool player_sliding;
extern bool player_is_hit;
extern bool16 player_invincible;
extern int player_invincibility_time;

inline screen_x_t player_center_x(void) {
	return (player_left + (PLAYER_W / 2));
}

inline screen_y_t player_center_y(void) {
	return (player_top + (PLAYER_H / 2));
}

inline screen_x_t player_right(void) {
	return (player_left + PLAYER_W);
}

inline screen_y_t player_bottom(void) {
	return (player_top + PLAYER_H);
}

void player_move_and_clamp(pixel_t delta);
void invincibility_sprites_update_and_render(bool16 invincible);

#define player_put(cel) { \
	ptn_put_8(player_left, player_top, cel); \
}

// Blits the default player sprite to its current position. Used whenever it
// was or might have been just unblitted.
inline void player_put_default(void) {
	player_put(PTN_MIKO_L);
}

#define player_miss_put() { \
	orb_put_default(); \
	player_put(PTN_MIKO_MISS + ( \
		(irand() % 8) == 0 ? (PTN_MIKO_MISS_ALTERNATE - PTN_MIKO_MISS) : 0 \
	)); \
}

// Unblits, updates, and renders the player based on the current input,
// handling all possible special moves together with any orb repulsion, but
// *not* performing regular player/Orb collision detection. Setting that
// hilarious double negative of a parameter to `false` resets the player state
// instead.
void player_unput_update_render(bool16 do_not_reset_player_state);

inline void player_unput_update_render(void) {
	player_unput_update_render(true);
}

inline void player_reset(void) {
	player_unput_update_render(false);
}

// Shows the player hit/respawn animation in a blocking way, and updates the
// HUD to reflect the lost life, together with all related game state. Except
// for, ironically, [rem_lives], which is assumed to have been decremented
// prior to calling this function.
void player_miss_animate_and_update(void);

extern int cardcombo_cur;
extern int cardcombo_max;
