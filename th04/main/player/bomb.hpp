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

// Drops a bomb, if possible. Also cancels a death if called during the
// deathbomb window.
void pascal near player_bomb(void);
