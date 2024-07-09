#include <stdarg.h>
#include <stdlib.h>
#include "libs/master.lib/master.hpp"
#include "libs/master.lib/pc98_gfx.hpp"
#include "th01/hardware/graph.h"
#include "th01/hardware/palette.h"
#include "th01/hardware/vplanset.h"
#include "th01/hardware/vsync.hpp"
#include "th01/hardware/ztext.hpp"
#include "th01/core/initexit.hpp"

static bool game_initialized = false;
static void interrupt (* int06_old)(...);

void interrupt int06_game_exit(...);
void game_exit_inner(void);

void interrupt int06_nop(...)
{
}

void game_init(void)
{
	if(game_initialized) {
		return;
	}
	game_initialized = true;
	int06_old = getvect(6);
	setvect(6, int06_game_exit);
	vsync_init();
	z_text_init();
	egc_start();
	graph_start();
	respal_create();
	z_respal_set();
	vram_planes_set();
}

void game_exit(void)
{
	if(game_initialized != true) {
		return;
	}
	game_initialized = false;
	game_exit_inner();
	respal_free();
}

void game_switch_binary(void)
{
	if(game_initialized != true) {
		return;
	}
	game_exit_inner();
	z_text_25line();
	z_text_setcursor(CURSOR_HIDE);
	z_text_clear();
	z_text_show();
	game_initialized = false;
}

void game_exit_inner(void)
{
	game_initialized = false;
	setvect(6, int06_nop);
	vsync_exit();
	z_text_clear();
	z_palette_black_out();
	z_graph_exit();
	egc_start();
	setvect(6, int06_old);
}

void interrupt int06_game_exit(...)
{
	game_exit();
	exit(0);
}

void game_exit_print_error(const char *fmt, ...)
{
	char buf[256];
	va_list ap;

	va_start(ap, fmt);
	vsprintf(buf, fmt, ap);
	game_exit();
	z_text_print(buf);
	exit(1);
	va_end(ap);
}
