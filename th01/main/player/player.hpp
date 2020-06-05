static const int PLAYER_W = 32;

static const int PLAYER_LEFT_MIN = (PLAYFIELD_LEFT);
static const int PLAYER_LEFT_MAX = (PLAYFIELD_RIGHT - PLAYER_W);

static const int PLAYER_LEFT_START = (PLAYFIELD_CENTER - (PLAYER_W / 2));

extern int player_left;

void player_move_and_clamp(int delta);
