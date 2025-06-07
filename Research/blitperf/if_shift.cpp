#include <stdlib.h>
#include <stdio.h>
#include "Research/blitperf/blitperf.hpp"
#include "platform/x86real/pc98/blit_low.hpp"
#include "platform/x86real/pc98/grcg.hpp"
#include "platform/x86real/pc98/palette.hpp"
#include "platform/grp_clip.hpp"
#include "th01/main/entity.hpp"
#include "th01/sprites/pellet.csp"

static const pixel_t SPRITE_W = 8;
static const pixel_t SPRITE_H = 8;
static const vram_byte_amount_t SPRITE_STRIDE = (
	(SPRITE_W + PRESHIFT) / BYTE_DOTS
);
typedef dot_rect_t(16, SPRITE_H) sprite_rect_t;

const char BANNER[] = "PC-98 blitting check/shift benchmark (" _(CPU) " build, " __DATE__ " " __TIME__ ")";

entity_topleft_t sprites[14500];

void (* test_func)(const Blitter __ds*, screen_x_t);

// Low-level blitter variations
// ----------------------------

void __fastcall or_8(seg_t /* _AX */)
{
	stationary_impl(_AX, 8, d_8, 0x00, 0);
}

void __fastcall or_16(seg_t /* _AX */)
{
	stationary_impl(_AX, 16, d_16, 0x00, 0);
}

const uint8_t DONT_CHECK_LOW  = 0x1;
const uint8_t DONT_CHECK_HIGH = 0x2;

#define checked(dc, op) \
	_AX = *reinterpret_cast<dots16_t __ds *>(_SI); \
	if((dc & DONT_CHECK_LOW)  || _AL) { *((dots8_t __es *)(_DI + 0)) op _AL; } \
	if((dc & DONT_CHECK_HIGH) || _AH) { *((dots8_t __es *)(_DI + 1)) op _AH; } \

#define DEFINE_CHECKED(func, check) \
	void __fastcall write_16_##func(seg_t /* _AX */) \
	{ \
		stationary_impl(_AX, 16, checked, check, =);\
	} \
	\
	void __fastcall or_16_##func(seg_t /* _AX */) \
	{ \
		stationary_impl(_AX, 16, checked, check, |=); \
	}

DEFINE_CHECKED(check_first, DONT_CHECK_HIGH);
DEFINE_CHECKED(check_second, DONT_CHECK_LOW);
DEFINE_CHECKED(check_both, 0);

void __fastcall movs_8(seg_t /* _AX */)
{
	march_impl(_AX, 8, u_8, X86::R_AX);
}

void __fastcall movs_16(seg_t /* _AX */)
{
	march_impl(_AX, 16, u_16, X86::R_AX);
}

void __fastcall naive_write(seg_t plane_seg, vram_byte_amount_t vram_w)
{
	const dots8_t far* sprite_p = (
		reinterpret_cast<const dots8_t far *>(blit_source.dots_start.fp) +
		blit_state.sprite_offset
	);
	vram_offset_t vo = blit_state.vo;
	vram_byte_amount_t stride = (ROW_SIZE - vram_w);

	GRCG grcg(GC_RMW);
	grcg.setcolor(t.opt[OPT_SPRITE_COL].val);
	for(pixel_t y = 0; y < blit_state.h_clipped; y++) {
		for(vram_byte_amount_t x = 0; x < vram_w; x++) {
			pokeb(plane_seg, vo, sprite_p[x]);
			vo++;
		}
		sprite_p += blit_source.stride;
		vo += stride;
	}
}

void __fastcall naive_write_8(seg_t plane_seg)
{
	naive_write(plane_seg, sizeof(dots8_t));
}

void __fastcall naive_write_16(seg_t plane_seg)
{
	naive_write(plane_seg, sizeof(dots16_t));
}
// ----------------------------

// Blitting methods tested
// -----------------------

sprite_rect_t shifted;

inline void rotate(screen_x_t& left) {
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
	blit_source.dots_start.fp = &sPELLET[0][left & (BYTE_DOTS - 1)];
	b->write(SEG_PLANE_B);
}

void near grcg_rotate_and_blit(const Blitter __ds* b, screen_x_t left)
{
	blit_source.dots_start.fp = &shifted;
	rotate(left);
	b->write(SEG_PLANE_B);
}

void near raw_blit_preshifted(const Blitter __ds* b, screen_x_t left)
{
	blit_source.dots_start.fp = &sPELLET[0][left & (BYTE_DOTS - 1)];
	b->write(SEG_PLANE_B);
	b->write(SEG_PLANE_R);
	b->write(SEG_PLANE_G);
	b->write(SEG_PLANE_E);
}

void near raw_rotate_and_blit(const Blitter __ds* b, screen_x_t left)
{
	blit_source.dots_start.fp = &shifted;
	rotate(left); b->write(SEG_PLANE_B);
	rotate(left); b->write(SEG_PLANE_R);
	rotate(left); b->write(SEG_PLANE_G);
	rotate(left); b->write(SEG_PLANE_E);
}
// -----------------------

// Test runs
// ---------

void test_update(void)
{
	entity_topleft_t *sprite_p = sprites;
	for(uint16_t i = 0; i < t.opt[OPT_SPRITE_COUNT].val; i++) {
		sprite_p->left += 1;
		sprite_p->top += 1;
		if(sprite_p->left >= RES_X) {
			sprite_p->left = -SPRITE_W;
		}
		if(sprite_p->top >= RES_Y) {
			sprite_p->top = -SPRITE_H;
		}
		sprite_p++;
	}
}

void test_render(void)
{
	entity_topleft_t *sprite_p = sprites;
	for(uint16_t i = 0; i < t.opt[OPT_SPRITE_COUNT].val; i++) {
		const Blitter __ds* b = blitter_init_clip(
			(sprite_p->left >> BYTE_BITS), sprite_p->top
		);
		if(b) {
			test_func(b, sprite_p->left);
		}
		sprite_p++;
	}
}

void run(
	void (__fastcall *or_8)(seg_t) = nullptr,
	void (__fastcall *or_16)(seg_t) = nullptr
)
{
	/*  */printf("\xEB\x9F" "   GRCG preshifted ");
	test_func = grcg_blit_preshifted;
	t.run(true);

	printf(", runtime-shifted ");
	test_func = grcg_rotate_and_blit;
	t.run(true);
	if(or_8) {
		BLITTER_FUNCS[ 8 / BYTE_DOTS].write = or_8;
		BLITTER_FUNCS[16 / BYTE_DOTS].write = or_16;
		printf("\n\xEB\x9F" "4-plane preshifted ");
		test_func = raw_blit_preshifted;
		t.run(false);

		printf(", runtime-shifted ");
		test_func = raw_rotate_and_blit;
		t.run(false);
	}
	puts("");
}

void test_main(void)
{
	srand(0);
	entity_topleft_t *sprite_p = sprites;
	for(uint16_t i = 0; i < t.opt[OPT_SPRITE_COUNT].val; i++) {
		sprite_p->left = ((rand() % (RES_X + (SPRITE_W * 2))) - SPRITE_W);
		sprite_p->top = ((rand() % (RES_Y + (SPRITE_H * 2))) - SPRITE_H);
		sprite_p++;
	}
	blitter_set_source_region(0, 0, SPRITE_STRIDE, SPRITE_H, SPRITE_STRIDE);

	extern Blitter BLITTER_FUNCS[];
	void (__fastcall *orig_dots8_write)(seg_t) = (
		BLITTER_FUNCS[ 8 / BYTE_DOTS].write
	);

	palette_show(PALETTE_DEFAULT);

	puts("Unchecked, MOV:");
	run(or_8, or_16);

	puts("Unchecked, MOVS:");
	BLITTER_FUNCS[ 8 / BYTE_DOTS].write = movs_8;
	BLITTER_FUNCS[16 / BYTE_DOTS].write = movs_16;
	run();
	BLITTER_FUNCS[ 8 / BYTE_DOTS].write = orig_dots8_write;

	puts("Checking first byte:");
	BLITTER_FUNCS[16 / BYTE_DOTS].write = write_16_check_first;
	run(or_8, or_16_check_first);

	puts("Checking second byte:");
	BLITTER_FUNCS[16 / BYTE_DOTS].write = write_16_check_second;
	run(or_8, or_16_check_second);

	puts("Checking both bytes:");
	BLITTER_FUNCS[16 / BYTE_DOTS].write = write_16_check_both;
	run(or_8, or_16_check_both);

	puts("Unchecked, unbatched, naive pure C implementation (no explicit register use):");
	BLITTER_FUNCS[ 8 / BYTE_DOTS].write = naive_write_8;
	BLITTER_FUNCS[16 / BYTE_DOTS].write = naive_write_16;
	run();
}
// ---------

void if_shift_startup(void)
{
	t.opt[OPT_SPRITE_COUNT].max = (sizeof(sprites) / sizeof(sprites[0]));
}

#pragma startup if_shift_startup
