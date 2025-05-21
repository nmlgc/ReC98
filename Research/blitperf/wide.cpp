#include <stdlib.h>
#include <stdio.h>
#include "Research/blitperf/blitperf.hpp"
#include "platform/x86real/pc98/blitter.hpp"
#include "platform/x86real/pc98/palette.hpp"
#include "Research/blitperf/wide.csp"

static const vram_byte_amount_t SPRITE_W = (640 / BYTE_DOTS);
static const pixel_t SPRITE_H = 40;

const char BANNER[] = "PC-98 wide blitting benchmark (" _(CPU) " build, " __DATE__ " " __TIME__ ")";

uvram_byte_amount_t W;

// Test runs
// ---------

extern Blitter BLITTER_FUNCS[];
extern void (__fastcall *DISPLACED[])(seg_t);
extern void (__fastcall *MARCHING[])(seg_t);
extern void (__fastcall *MOVS[])(seg_t);
extern void (__fastcall *REP_MOVS[])(seg_t);

void test_update(void)
{
}

void test_render(void)
{
	static uint8_t cycle = 0;

	screen_y_t top = (RES_Y - SPRITE_H + cycle);
	for(uint16_t i = 0; i < t.opt[OPT_SPRITE_COUNT].val; i++) {
		const Blitter __ds* b = blitter_init_clip(0, top);
		if(b) {
			b->write(SEG_PLANE_B);
		}
		top += SPRITE_H;
		if(top >= RES_Y) {
			top -= (RES_Y + SPRITE_H);
		}
	}

	cycle++;
	if(cycle >= SPRITE_H) {
		cycle = 0;
	}
}

void test_main(void)
{
	palette_show(PALETTE_DEFAULT);
	printf("Sprite count: %u\n", t.opt[OPT_SPRITE_COUNT].val);
	puts("W   | Displaced        | Marching         | MOVS             | REP MOVS");

	blit_source.dots_start.fp = &sWIDE[0][0];
	for(W = 4; W <= ROW_SIZE; W += 4) {
		printf("%3d | ", (W * BYTE_DOTS));
		blitter_set_source_region(0, 0, W, SPRITE_H, SPRITE_W);

		BLITTER_FUNCS[W].write = DISPLACED[W / 4u];
		t.run(true);

		printf(" | ");
		BLITTER_FUNCS[W].write = MARCHING[W / 4u];
		t.run(true);

		printf(" | ");
		BLITTER_FUNCS[W].write = MOVS[W / 4u];
		t.run(true);

		printf(" | ");
		BLITTER_FUNCS[W].write = REP_MOVS[W / 4u];
		t.run(true);

		puts("");
	}
}
// ---------

void wide_startup(void)
{
	t.opt[OPT_SPRITE_COUNT].val = 512;
	t.opt[OPT_SPRITE_COUNT].max = 0xFFFF;
	t.opt[OPT_DURATION].val = 40;
	t.opt[OPT_DURATION].max = 99;
}

#pragma startup wide_startup
