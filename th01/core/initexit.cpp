#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "shiftjis.hpp"
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
	vram_planes_set();
}

void game_exit(void)
{
	if(game_initialized != true) {
		return;
	}
	game_initialized = false;
	game_exit_inner();
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
