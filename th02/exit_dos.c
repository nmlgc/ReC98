#pragma option -zCSHARED

#include "master.hpp"
#include "th02/core/initexit.h"

// TODO: Remove this macro once those functions are part of the actual SHARED
// segment (not SHARED_) in TH04 and TH05, after graph_putsa_fx() has been
// turned into its own translation unit.
#define game_exit() __asm { nop; push cs; call near ptr game_exit; }

void game_exit_to_dos(void)
{
	game_exit();
	key_beep_on();
	text_systemline_show();
	text_cursor_show();
}
