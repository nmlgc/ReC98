#include "platform.h"

static const unsigned char BOMB_CIRCLE_FRAMES = 32;

extern bool bombing;

// Drops a bomb, if possible.
void pascal near player_bomb(void);

void near bomb_update_and_render(void);
