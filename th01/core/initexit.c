#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th01/hardware/graph.h"
#include "th01/hardware/palette.h"
#include "th01/hardware/vplanset.h"
#include "th01/hardware/vsync.h"
#include "th01/hardware/ztext.h"

extern bool game_initialized;
extern void interrupt(* int06_old)();

void interrupt int06_game_exit();
void game_exit_inner(void);

void interrupt int06_nop()
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
	game_initialized = 0;
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
	game_initialized = 0;
}

void game_exit_inner(void)
{
	game_initialized = 0;
	setvect(6, int06_nop);
	vsync_exit();
	z_text_clear();
	z_palette_black_out();
	z_graph_exit();
	egc_start();
	setvect(6, int06_old);
}

void interrupt int06_game_exit()
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
