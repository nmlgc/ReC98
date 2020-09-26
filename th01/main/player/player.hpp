static const pixel_t PLAYER_W = 32;
static const pixel_t PLAYER_H = 32;

static const screen_x_t PLAYER_LEFT_MIN = (PLAYFIELD_LEFT);
static const screen_x_t PLAYER_LEFT_MAX = (PLAYFIELD_RIGHT - PLAYER_W);

static const screen_x_t PLAYER_LEFT_START = (PLAYFIELD_CENTER_X - (PLAYER_W / 2));

extern screen_x_t player_left;
static const screen_y_t player_top = (PLAYFIELD_BOTTOM - PLAYER_H);
static const screen_y_t player_center_y = (PLAYFIELD_BOTTOM - (PLAYER_H / 2));

void player_move_and_clamp(int delta);
void invincibility_sprites_update_and_render(bool16 invincible);

extern unsigned char player_deflecting;
extern unsigned char player_sliding;
extern bool16 player_invincible;

extern int lives;
extern int cardcombo_cur;
extern int cardcombo_max;
