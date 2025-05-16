#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "platform/x86real/pc98/blit_low.hpp"
#include "platform/x86real/pc98/font.hpp"
#include "platform/x86real/pc98/graph.hpp"
#include "platform/x86real/pc98/grcg.hpp"
#include "platform/x86real/pc98/keyboard.hpp"
#include "platform/x86real/pc98/page.hpp"
#include "platform/x86real/pc98/palette.hpp"
#include "platform/x86real/pc98/vsync.hpp"
#include "th01/main/entity.hpp"
#include "th01/sprites/pellet.csp"
#include "Research/blitperf.csp"

static const pixel_t SPRITE_W = 8;
static const pixel_t SPRITE_H = 8;
static const vc_t SPRITE_COL = 2;
typedef dot_rect_t(16, SPRITE_H) sprite_rect_t;

#ifndef CPU
#error CPU macro not defined
#endif

#define _(x) __(x)
#define __(x) #x

const char BANNER[] = "PC-98 blitting benchmark (" _(CPU) " build, " __DATE__ " " __TIME__ ")";

#undef _
#undef __

void banner_put(void)
{
	puts(BANNER);
	for(int i = 0; i < (sizeof(BANNER) - 1); i++) {
		fputs("\x86\x44", stdout);
	}
	puts("");
}

// Low-level blitter variations
// ----------------------------

const uint8_t DONT_CHECK_LOW  = 0x1;
const uint8_t DONT_CHECK_HIGH = 0x2;

#define checked(dc, op) \
	_AX = *reinterpret_cast<dots16_t __ds *>(_SI); \
	if((dc & DONT_CHECK_LOW)  || _AL) { *((dots8_t __es *)(_DI + 0)) op _AL; } \
	if((dc & DONT_CHECK_HIGH) || _AH) { *((dots8_t __es *)(_DI + 1)) op _AH; } \

#define DEFINE_CHECKED(func, check) \
	void write_16_##func(seg_t plane_seg, const void far* sprite) \
	{ \
		stationary_impl(plane_seg, sprite, checked, check, =); \
	} \
	\
	void or_16_##func(seg_t plane_seg, const void far* sprite) \
	{ \
		stationary_impl(plane_seg, sprite, checked, check, |=); \
	}

DEFINE_CHECKED(check_first, DONT_CHECK_HIGH);
DEFINE_CHECKED(check_second, DONT_CHECK_LOW);
DEFINE_CHECKED(check_both, 0);

// That assignment to DX might have an impact, who knows!1!!
#define movs_body(ins, size, plane_seg, sprite) { \
	register int16_t loops_unrolled = blit_state.loops_unrolled; \
	_SI = FP_OFF(sprite); \
	_SI += blit_state.sprite_offset; \
	_DI = blit_state.vo; \
	_BX = blit_state.loops_remainder; \
	_asm { push ds; } \
	_DS = FP_SEG(sprite); \
	_ES = plane_seg; \
	static_assert(UNROLL_H == 8); \
	switch(_BX) { \
	case 0: do { asm { ins }; _SI += (2 - size);_DI += (ROW_SIZE - size); \
	case 7:      asm { ins }; _SI += (2 - size);_DI += (ROW_SIZE - size); \
	case 6:      asm { ins }; _SI += (2 - size);_DI += (ROW_SIZE - size); \
	case 5:      asm { ins }; _SI += (2 - size);_DI += (ROW_SIZE - size); \
	case 4:      asm { ins }; _SI += (2 - size);_DI += (ROW_SIZE - size); \
	case 3:      asm { ins }; _SI += (2 - size);_DI += (ROW_SIZE - size); \
	case 2:      asm { ins }; _SI += (2 - size);_DI += (ROW_SIZE - size); \
	case 1:      asm { ins }; _SI += (2 - size);_DI += (ROW_SIZE - size); \
	/*       */} while(--loops_unrolled > 0); \
	} \
	_asm { pop ds; } \
}

void movsb(seg_t plane_seg, const void far* sprite)
{
	movs_body(movsb, sizeof(uint8_t), plane_seg, sprite);
}

void movsw(seg_t plane_seg, const void far* sprite)
{
	movs_body(movsw, sizeof(uint16_t), plane_seg, sprite);
}

void naive_write(
	seg_t plane_seg, const void far* sprite, vram_byte_amount_t vram_w
)
{
	const dots8_t far* sprite_p = (
		reinterpret_cast<const dots8_t far *>(sprite) + blit_state.sprite_offset
	);
	const pixel_t h = (
		(blit_state.loops_unrolled * UNROLL_H) + blit_state.loops_remainder
	);
	vram_offset_t vo = blit_state.vo;
	vram_byte_amount_t stride = (ROW_SIZE - vram_w);

	GRCGStaticColor<SPRITE_COL> grcg(GC_RMW);
	for(pixel_t y = 0; y < h; y++) {
		for(vram_byte_amount_t x = 0; x < vram_w; x++) {
			pokeb(plane_seg, vo, sprite_p[x]);
			vo++;
		}
		sprite_p += blit_state.sprite_w;
		vo += stride;
	}
}

void naive_write_8(seg_t plane_seg, const void far* sprite)
{
	naive_write(plane_seg, sprite, sizeof(dots8_t));
}

void naive_write_16(seg_t plane_seg, const void far* sprite)
{
	naive_write(plane_seg, sprite, sizeof(dots16_t));
}
// ----------------------------

// Blitting methods tested
// -----------------------

inline void rotate(sprite_rect_t& shifted, screen_x_t& left) {
	_CX = left;
	_CX &= (BYTE_DOTS - 1);
	static_assert(SPRITE_H == 8);
	shifted[0] = __rotr__(sPELLET[0][0][0], _CX);
	shifted[1] = __rotr__(sPELLET[0][0][1], _CX);
	shifted[2] = __rotr__(sPELLET[0][0][2], _CX);
	shifted[3] = __rotr__(sPELLET[0][0][3], _CX);
	shifted[4] = __rotr__(sPELLET[0][0][4], _CX);
	shifted[5] = __rotr__(sPELLET[0][0][5], _CX);
	shifted[6] = __rotr__(sPELLET[0][0][6], _CX);
	shifted[7] = __rotr__(sPELLET[0][0][7], _CX);
}

void near grcg_blit_preshifted(const Blitter __ds* b, screen_x_t left)
{
	b->write(SEG_PLANE_B, &sPELLET[0][left & (BYTE_DOTS - 1)]);
}

void near grcg_rotate_and_blit(const Blitter __ds* b, screen_x_t left)
{
	sprite_rect_t shifted;
	rotate(shifted, left);
	b->write(SEG_PLANE_B, &shifted);
}

void near raw_blit_preshifted(const Blitter __ds* b, screen_x_t left)
{
	const sprite_rect_t& sprite = sPELLET[0][left & (BYTE_DOTS - 1)];
	b->or(SEG_PLANE_B, &sprite);
	b->or(SEG_PLANE_R, &sprite);
	b->or(SEG_PLANE_G, &sprite);
	b->or(SEG_PLANE_E, &sprite);
}

void near raw_rotate_and_blit(const Blitter __ds* b, screen_x_t left)
{
	sprite_rect_t shifted;
	rotate(shifted, left); b->or(SEG_PLANE_B, &shifted);
	rotate(shifted, left); b->or(SEG_PLANE_R, &shifted);
	rotate(shifted, left); b->or(SEG_PLANE_G, &shifted);
	rotate(shifted, left); b->or(SEG_PLANE_E, &shifted);
}
// -----------------------

// Test runs
// ---------

typedef void (* test_func_t)(const Blitter __ds*, screen_x_t);

struct Sprite : public entity_topleft_t {
	void init() {
		left = ((rand() % (RES_X + (SPRITE_W * 2))) - SPRITE_W);
		top = ((rand() % (RES_Y + (SPRITE_H * 2))) - SPRITE_H);
	}

	void move() {
		left += 1;
		top += 1;
		if(left >= RES_X) {
			left = -SPRITE_W;
		}
		if(top >= RES_Y) {
			top = -SPRITE_H;
		}
	}
};

Sprite sprites[14500];

enum option_type_t {
	OPT_SPRITE_COUNT,
	OPT_DURATION,
	OPT_SPRITE_COL,
	OPT_COUNT,
	OPT_INVALID = -1
};

struct Option {
	char cmd_c;
	const char* desc;
	uint16_t val;
	uint16_t min;
	uint16_t max;
};

struct Test {
	Option opt[OPT_COUNT];
	unsigned int slowdown;
	uint16_t frame;
	bool skip_locked;

	void frame_delay(unsigned int frames);
	void sprite_loop(test_func_t func);
	void run(bool grcg, const char* prompt, test_func_t func);
	void run(bool grcg_only);
};

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

void Test::sprite_loop(test_func_t func)
{
	Sprite near* sprite_p = sprites;
	for(uint16_t i = 0; i < opt[OPT_SPRITE_COUNT].val; i++) {
		const Blitter __ds* b = blitter_init_clip_lrtb(
			(sprite_p->left >> BYTE_BITS),
			sprite_p->top,
			((SPRITE_W + PRESHIFT) / BYTE_DOTS),
			SPRITE_H
		);
		if(b) {
			func(b, sprite_p->left);
		}
		sprite_p->move();
		sprite_p++;
	}
}

void Test::run(bool grcg, const char* prompt, test_func_t func)
{
	page_t page_back = 0;

	// Make sure we start at the very beginning of a frame
	while(vsync_count_32 < 1) {}
	vsync_count_16 = 0;
	vsync_count_32 = 0;
	slowdown = 0;

	printf("%s ", prompt);

	for(frame = 0; frame < opt[OPT_DURATION].val; frame++) {
		page_show(1 - page_back);
		page_access(page_back);

		graph_clear();

		if(grcg) {
			GRCG grcg(GC_RMW);
			grcg.setcolor(opt[OPT_SPRITE_COL].val);
			sprite_loop(func);
		} else {
			sprite_loop(func);
		}

		const uint8_t skip_pressed = (peekb(0, KEYGROUP_1) & K1_TAB);

		if(peekb(0, KEYGROUP_2) & K2_Q) {
			exit(0);
		}
		if(skip_pressed && !skip_locked) {
			// Run the remaining simulation steps to ensure a consistent
			// starting point for each test
			while(++frame < opt[OPT_DURATION].val) {
				Sprite near* sprite_p = sprites;
				for(uint16_t i = 0; i < opt[OPT_SPRITE_COUNT].val; i++) {
					sprite_p->move();
					sprite_p++;
				}
			}
		} else {
			frame_delay(1);
		}

		skip_locked = skip_pressed;
		page_back ^= 1;
	}
}

void Test::run(bool grcg_only)
{
	/*  */printf("\xEB\x9F" "   GRCG ");
	run(true, "preshifted", grcg_blit_preshifted);
	run(true, ", runtime-shifted", grcg_rotate_and_blit);
	if(!grcg_only) {
		printf("\n\xEB\x9F" "4-plane ");
		run(false, "preshifted", raw_blit_preshifted);
		run(false, ", runtime-shifted", raw_rotate_and_blit);
	}
	puts("");
}
// ---------

Test t = {{
	{ 's', "Sprite count", 2000, 1, (sizeof(sprites) / sizeof(sprites[0])) },
	{ 'd', "Frames per test", 100, 1, 999 },
	{ 'c', "GRCG sprite color", 2, 0x1, 0xF },
}};

const Palette4 PALETTE = {
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

	srand(0);
	{for(uint16_t i = 0; i < t.opt[OPT_SPRITE_COUNT].val; i++) {
		sprites[i].init();
	}}

	graph_show_16color_400line();
	palette_show(PALETTE);
	vsync_init();

	extern Blitter BLITTER_FUNCS[];
	blit_func_t orig_dots8_write = BLITTER_FUNCS[ 8 / BYTE_DOTS].write;

	puts("Unchecked, MOV:");
	t.run(false);

	puts("Unchecked, MOVS:");
	BLITTER_FUNCS[ 8 / BYTE_DOTS].write = movsb;
	BLITTER_FUNCS[16 / BYTE_DOTS].write = movsw;
	t.run(true);
	BLITTER_FUNCS[ 8 / BYTE_DOTS].write = orig_dots8_write;

	puts("Checking first byte:");
	BLITTER_FUNCS[16 / BYTE_DOTS].write = write_16_check_first;
	BLITTER_FUNCS[16 / BYTE_DOTS].or = or_16_check_first;
	t.run(false);

	puts("Checking second byte:");
	BLITTER_FUNCS[16 / BYTE_DOTS].write = write_16_check_second;
	BLITTER_FUNCS[16 / BYTE_DOTS].or = or_16_check_second;
	t.run(false);

	puts("Checking both bytes:");
	BLITTER_FUNCS[16 / BYTE_DOTS].write = write_16_check_both;
	BLITTER_FUNCS[16 / BYTE_DOTS].or = or_16_check_both;
	t.run(false);

	puts("Unchecked, unbatched, naive pure C implementation (no explicit register use):");
	BLITTER_FUNCS[ 8 / BYTE_DOTS].write = naive_write_8;
	BLITTER_FUNCS[16 / BYTE_DOTS].write = naive_write_16;
	t.run(true);

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
