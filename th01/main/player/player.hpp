static const pixel_t PLAYER_W = 32;
static const pixel_t PLAYER_H = 32;

static const screen_x_t PLAYER_LEFT_MIN = (PLAYFIELD_LEFT);
static const screen_x_t PLAYER_LEFT_MAX = (PLAYFIELD_RIGHT - PLAYER_W);

static const screen_x_t PLAYER_LEFT_START = (PLAYFIELD_CENTER_X - (PLAYER_W / 2));

extern screen_x_t player_left;
static const screen_y_t player_top = (PLAYFIELD_BOTTOM - PLAYER_H);

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

// Unblits, updates, and renders the player based on the current input,
// handling all possible special moves together with any orb repulsion, but
// *not* performing regular player/Orb collision detection. Setting that
// hilarious double negative of a parameter to `false` resets the player state
// instead.
void player_unput_update_render(bool16 do_not_reset_player_state);

extern bool player_deflecting;
extern bool player_sliding;
extern bool16 player_invincible;

extern int lives;
extern int cardcombo_cur;
extern int cardcombo_max;
