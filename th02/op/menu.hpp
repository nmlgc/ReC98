// Shared menu code.

#include "pc98.h"

#if (GAME >= 4)
	typedef void (near pascal *near menu_unput_and_put_func_t)(
		int sel, vc2 col
	);
#else
	typedef void (near pascal *near menu_put_func_t)(int sel, tram_atrb2 atrb);
#endif

void pascal near menu_sel_update_and_render(int8_t max, int8_t direction);

#define menu_update_vertical(input, choice_count) { \
	if(input & INPUT_UP) { \
		menu_sel_update_and_render((choice_count - 1), -1); \
	} \
	if(input & INPUT_DOWN) { \
		menu_sel_update_and_render((choice_count - 1), +1); \
	} \
}
