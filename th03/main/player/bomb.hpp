#include "th03/main/playfld.hpp"
struct player_t;

static const unsigned char BOMB_FRAMES = 180;

enum bomb_state_t {
	BOMB_INACTIVE = 0,
	BOMB_PREPARING = 1,
	BOMB_ACTIVE = 2,
};

extern bomb_state_t bomb_state[PLAYER_COUNT];
extern unsigned char bomb_frame[PLAYER_COUNT];

extern bool damage_all_enemies_on[PLAYFIELD_COUNT];

// Drops a bomb or uses a hyper, if possible.
void pascal near player_bomb(player_t near *player);
