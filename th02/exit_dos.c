#pragma codeseg SHARED

#include "master.hpp"
#include "th02/core/initexit.h"

void game_exit_to_dos(void)
{
	game_exit();
	key_beep_on();
	text_systemline_show();
	text_cursor_show();
}
