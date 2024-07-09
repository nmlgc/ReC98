#include "platform.h"

// Shows the pause menu, and returns `true` if the player selected to quit.
bool16 pause_menu(void);

// Shows the continue menu. Relaunches the main executable if the player
// decides to use a continue (and does not return in this case), or returns
// `false`.
bool16 continue_menu(void);
