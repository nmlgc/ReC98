#include "th02/main/player/bomb.hpp"

extern bool bombing_disabled;
extern unsigned char bomb_frame;
#if (GAME == 4)
// Pointless indirection to player_bomb().
extern nearfunc_t_near player_bomb_func;
#endif

// Character-specific bomb update and render functions
// ---------------------------------------------------

extern nearfunc_t_near playchar_bomb_func;

void pascal near bomb_reimu(void);
void pascal near bomb_marisa(void);
// ---------------------------------------------------

#if (GAME == 4)
// Handles the BB?.BB animation, scroll deactivation, common palette
// manipulation, and calls [playchar_bomb_func].
void near bomb_update_and_render(void);
#endif

// Drops a bomb, if possible. Also cancels a death if called during the
// deathbomb window.
void pascal near player_bomb(void);
