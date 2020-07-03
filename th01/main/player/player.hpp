static const int PLAYER_W = 32;
static const int PLAYER_H = 32;

static const int PLAYER_LEFT_MIN = (PLAYFIELD_LEFT);
static const int PLAYER_LEFT_MAX = (PLAYFIELD_RIGHT - PLAYER_W);

static const int PLAYER_LEFT_START = (PLAYFIELD_CENTER - (PLAYER_W / 2));

extern int player_left;
static const int player_top = (PLAYFIELD_BOTTOM - PLAYER_H);
static const int player_center_y = (PLAYFIELD_BOTTOM - (PLAYER_H / 2));

void player_move_and_clamp(int delta);

extern unsigned char player_deflecting;
