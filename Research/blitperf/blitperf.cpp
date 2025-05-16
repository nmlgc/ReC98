/// Basic code shared among all blitting benchmark tests
/// ----------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Research/blitperf/blitperf.hpp"
#include "platform/x86real/pc98/font.hpp"
#include "platform/x86real/pc98/graph.hpp"
#include "platform/x86real/pc98/grcg.hpp"
#include "platform/x86real/pc98/keyboard.hpp"
#include "platform/x86real/pc98/page.hpp"
#include "platform/x86real/pc98/vsync.hpp"
#include "Research/blitperf/blitperf.csp"

void graph_clear(void)
{
	GRCGStaticColor<static_cast<vc_t>(0)> grcg(GC_TDW);
	_ES = SEG_PLANE_B;
	_DI = 0;
#if (CPU == 386)
	_CX = (PLANE_SIZE / sizeof(uint32_t));
	asm { cld; db 0x66, 0xF3, 0xAB; } // REP STOSD
#else
	_CX = (PLANE_SIZE / sizeof(uint16_t));
	asm { cld; rep stosw; }
#endif
}

void Test::frame_delay(unsigned int frames)
{
	if(vsync_count_16 != 0) {
		++slowdown;
	} else {
		while(vsync_count_16 < frames) {}
	}
	if(frame != 0) {
		printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
	}
	printf(
		"\xEB\xA0 %3d/%3d \xEB\xA1 %6lu", slowdown, (frame + 1), vsync_count_32
	);
	vsync_count_16 = 0;
}

void Test::run(bool grcg)
{
	page_t page_back = 0;

	// Make sure we start at the very beginning of a frame
	while(vsync_count_32 < 1) {}
	vsync_count_16 = 0;
	vsync_count_32 = 0;
	slowdown = 0;

	for(frame = 0; frame < opt[OPT_DURATION].val; frame++) {
		page_show(1 - page_back);
		page_access(page_back);

		graph_clear();

		if(grcg) {
			GRCG grcg(GC_RMW);
			grcg.setcolor(opt[OPT_SPRITE_COL].val);
			test_render();
		} else {
			test_render();
		}

		const uint8_t skip_pressed = (peekb(0, KEYGROUP_1) & K1_TAB);

		if(peekb(0, KEYGROUP_2) & K2_Q) {
			exit(0);
		}
		if(skip_pressed && !skip_locked) {
			// Run the remaining simulation steps to ensure a consistent
			// starting point for each test
			while(frame++ < opt[OPT_DURATION].val) {
				test_update();
			}
		} else {
			test_update();
			frame_delay(1);
		}

		skip_locked = skip_pressed;
		page_back ^= 1;
	}
}

Test t = {{
	// The sprite cap must be defined in the test itself.
	{ 's', "Sprite count", 2000, 1, 0 },

	{ 'd', "Frames per test", 100, 1, 999 },
	{ 'c', "GRCG sprite color", 2, 0x1, 0xF },
}};

extern const Palette4 PALETTE_DEFAULT = {
	0x0, 0x0, 0x0,
	0x0, 0x0, 0x7,
	0x7, 0x0, 0x0,
	0x7, 0x0, 0x7,
	0x0, 0x7, 0x0,
	0x0, 0x7, 0x7,
	0x7, 0x7, 0x0,
	0x7, 0x7, 0x7,
	0x3, 0x3, 0x3,
	0x0, 0x0, 0x4,
	0x4, 0x0, 0x0,
	0x4, 0x0, 0x4,
	0x0, 0x4, 0x0,
	0x0, 0x4, 0x4,
	0x4, 0x4, 0x0,
	0x4, 0x4, 0x4,
};

void banner_put(void)
{
	const char *p = BANNER;
	while(*p) {
		fputc(*(p++), stdout);
	}
	puts("");
	int len = (p - BANNER);
	for(int i = 0; i < len; i++) {
		fputs("\x86\x44", stdout);
	}
	puts("");
}

int option_invalid(const char* argv0, const char* arg)
{
	printf("%s: invalid option: %s\n", argv0, arg);
	return 1;
}

int __cdecl main(int argc, const char *argv[])
{
	// Command line parsing
	// --------------------

	Option* cur_opt = nullptr;
	for(int arg_i = 1; arg_i < argc; arg_i++) {
		const char* cur_arg = argv[arg_i];

		if(cur_opt != nullptr) {
			uint32_t val_long;

			if(cur_arg[0] == '\0') {
				printf("%s: missing option for /%c\n", argv[0], cur_opt->cmd_c);
				return 2;
			} else if(sscanf(cur_arg, "%lu", &val_long) != 1) {
				printf(
					"%s: invalid value for /%c: %s\n",
					argv[0], cur_opt->cmd_c, cur_arg
				);
				return 3;
			} else if((val_long < cur_opt->min) || (val_long > cur_opt->max)) {
				printf(
					"%s: value for /%c (%s) out of range (must be between %u and %u, got %s)\n",
					argv[0],
					cur_opt->cmd_c,
					cur_opt->desc,
					cur_opt->min,
					cur_opt->max,
					cur_arg
				);
				return 4;
			}
			cur_opt->val = val_long;
			cur_opt = nullptr;
		} else if((cur_arg[0] == '-') || (cur_arg[0] == '/')) {
			if(cur_arg[2] != '\0') {
				return option_invalid(argv[0], cur_arg);
			}
			if(cur_arg[1] == '?') {
				banner_put();
				printf("Usage: %s", argv[0]);
				{for(int i = 0; i < OPT_COUNT; i++) {
					printf(" [/%c %d]", t.opt[i].cmd_c, t.opt[i].val);
				}}
				puts("\n");
				{for(int i = 0; i < OPT_COUNT; i++) {
					printf(
						"\t/%c\t%s (%u-%u)\n",
						t.opt[i].cmd_c,
						t.opt[i].desc,
						t.opt[i].min,
						t.opt[i].max
					);
				}}
				return 0;
			}

			cur_opt = nullptr;
			{for(int i = 0; i < OPT_COUNT; i++) {
				if(tolower(cur_arg[1]) == tolower(t.opt[i].cmd_c)) {
					cur_opt = &t.opt[i];
				}
			}}
			if(cur_opt == nullptr) {
				return option_invalid(argv[0], cur_arg);
			}
		}
	}
	// --------------------

	printf("%s", "\x1B*");
	banner_put();
	{for(int i = 0; i < OPT_COUNT; i++) {
		printf("%s%s: %u", ((i >= 1) ? ", " : ""), t.opt[i].desc, t.opt[i].val);
	}}
	puts("\nCall with /? for options, hold Q to quit, or TAB to skip to the next test.\n");

	graph_show_16color_400line();
	vsync_init();

	test_main();
	return 0;
}

void blitperf_startup(void)
{
	font_gaiji_write(
		sBLITPERF, (sizeof(sBLITPERF) / sizeof(sBLITPERF[0])), 0x21
	);

	// Hide cursor
	fprintf(stdout, "\x1B[>5h");
}

void blitperf_exit(void)
{
	// Flush input
	_AX = 0x0C00;
	geninterrupt(0x21);

	// Show cursor
	fprintf(stdout, "\x1B[>5l");
}

#pragma startup blitperf_startup
#pragma exit blitperf_exit
