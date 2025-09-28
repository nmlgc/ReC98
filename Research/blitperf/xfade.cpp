#include <stdlib.h>
#include <stdio.h>
#include "Research/blitperf/blitperf.hpp"
#include "libs/master.lib/pc98_gfx.hpp"
#include "platform/x86real/pc98/blitter.hpp"
#include "platform/x86real/pc98/egc.hpp"
#include "platform/x86real/pc98/page.hpp"
#include "platform/x86real/pc98/vsync.hpp"
#include "platform/x86real/flags.hpp"
#include "platform/palette.hpp"
#include "platform/grp_surf.hpp"
#include "x86real.h"

// Constants
// ---------

static const unsigned int IMAGE_COUNT = 2;

static const pixel_t MASK_H = 4;
static const uint8_t MASK_COUNT = 6;
static const dots16_t MASKS[MASK_COUNT][MASK_H] = {
	0x0000, 0x1111, 0x0000, 0x4444,
	0x8888, 0x1111, 0x2222, 0x4444,
	0xAAAA, 0x5555, 0xAAAA, 0x5555,
	0xEEEE, 0x7777, 0xBBBB, 0xDDDD,
	0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
	0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
};

const char *PI_FN[IMAGE_COUNT] = { "MS4.PI", "MS5.PI" };
const char BANNER[] = "PC-98 crossfading benchmark (" _(CPU) " build, " __DATE__ " " __TIME__ ")";
// ---------

// State
// -----

GrpSurface_M4 image[IMAGE_COUNT];
GrpSurface_M4 near *image_cur = &image[0];
uvram_byte_amount_t W;
upixel_t EGCRegionH;
static uint8_t ImageI = 0;
static uint8_t MaskI = 0;
void (* test_func)(const dots16_t near *mask_p);
// -----

// Test runs
// ---------

extern void (*MASKED_OR[])(seg_t, const dots16_t __ds *, uint16_t);
extern void (*ERASE_MASKED_OR[])(seg_t, const dots16_t __ds *, uint16_t);

void test_update(void)
{
	MaskI++;
	MaskI %= MASK_COUNT;
	if(MaskI == 0) {
		ImageI++;
		ImageI %= IMAGE_COUNT;
		image_cur = &image[ImageI];
	}
}

void blit_cpu(
	void (*func)(seg_t, const dots16_t __ds *, uint16_t),
	const dots16_t near *mask_p
)
{
	const seg_t plane_paras = image_cur->plane_paras;
	blit_source.dots_start.fp = MK_FP(image_cur->plane_B, 0);
	blitter_init_noclip(0, 0);
	func(SEG_PLANE_B, mask_p, MASK_H);
	blit_source.dots_start.part.seg += plane_paras;
	func(SEG_PLANE_R, mask_p, MASK_H);
	blit_source.dots_start.part.seg += plane_paras;
	func(SEG_PLANE_G, mask_p, MASK_H);
	blit_source.dots_start.part.seg += plane_paras;
	func(SEG_PLANE_E, mask_p, MASK_H);
}

void test_cpu(const dots16_t near *mask_p)
{
	void (*func)(seg_t, const dots16_t __ds *, uint16_t) = ERASE_MASKED_OR[
		W / 4u
	];
	for(uint16_t i = 0; i < t.opt[OPT_SPRITE_COUNT].val; i++) {
		blit_cpu(func, mask_p);
	}
}

void test_grcg(const dots16_t near *mask_p)
{
#if (CPU == 386)
	uvram_dword_amount_t grcg_rep = (W / sizeof(dots32_t));
#else
	uvram_word_amount_t grcg_rep = (W / sizeof(dots16_t));
#endif
	const vram_byte_amount_t skip_bytes = (ROW_SIZE - W);

	void (*func)(seg_t, const dots16_t __ds *, uint16_t) = MASKED_OR[W / 4u];
	for(uint16_t i = 0; i < t.opt[OPT_SPRITE_COUNT].val; i++) {
		{
			GRCG grcg(GC_RMW);
			grcg.set_color_static(0);
			_ES = SEG_PLANE_B;
			_DI = vram_offset_shift(0, 0);
			for(uint16_t row = 0; row < image_cur->h; row++) {
				_AX = mask_p[row % MASK_H];
#if (CPU == 386)
				_DX = _AX;
				_EAX <<= 16;
				_AX = _DX;
				_CX = grcg_rep;
				asm { cld; db 0x66, 0xF3, 0xAB; } // REP STOSD
#else
				_CX = grcg_rep;
				asm { cld; rep stosw; }
#endif
				_DI += skip_bytes;
			}
		}
		blit_cpu(func, mask_p);
	}
}

void test_egc(const dots16_t near *mask_p)
{
	const uvram_word_amount_t egc_words = (
		((W * BYTE_DOTS) + (EGC_REGISTER_DOTS - 1)) / EGC_REGISTER_DOTS
	);
	const uvram_byte_amount_t skip_bytes = (ROW_SIZE - W);
	const seg_t plane_paras = image_cur->plane_paras;

	{
		EGC egc;
		outport(EGC_ACTIVEPLANEREG, 0xFFF0);
		outport(EGC_READPLANEREG, 0x00FF);
		outport(EGC_ADDRRESSREG, 0);
		outport(EGC_BITLENGTHREG, ((W * BYTE_DOTS) - 1));
		outport(EGC_MODE_ROP_REG, 0x29F0);
	}

	for(uint16_t i = 0; i < t.opt[OPT_SPRITE_COUNT].val; i++) {
		vram_offset_t vo_dst = vram_offset_shift(0, 0);
		upixel_t top = 0;
		blitter_set_source_region(0, 0, W, EGCRegionH, image_cur->w);
		while(top < image_cur->h) {
			const pixel_t clipped_region_h = (image_cur->h - top);
			if(clipped_region_h < blit_source.h) {
				blit_source.h = clipped_region_h;
			}
			blit_source.dots_start.fp = MK_FP(image_cur->plane_B, 0);
			void (__fastcall *func)(seg_t) = (
				blitter_init_noclip(0, RES_Y).write_offscreen
			);
			func(SEG_PLANE_B); blit_source.dots_start.part.seg += plane_paras;
			func(SEG_PLANE_R); blit_source.dots_start.part.seg += plane_paras;
			func(SEG_PLANE_G); blit_source.dots_start.part.seg += plane_paras;
			func(SEG_PLANE_E);

			_DI = vo_dst;
			pixel_t egc_rows_remaining = blit_source.h;
			blit_source.offset += (egc_rows_remaining * blit_source.stride);
			vo_dst += (egc_rows_remaining * ROW_SIZE);
			_SI = vram_offset_shift(0, RES_Y);
			_asm { cld; }
			_ES = SEG_PLANE_B;
			{
				EGC egc;

				// x86 only supports 8-bit port numbers as immediates… :(
				_DX = EGC_MASKREG;

				do {
					outport(_DX, mask_p[top % MASK_H]);
					_CX = egc_words;
					__emit__(0xF3, 0x26, 0xA5); // REP MOVSW ES:[DI], ES:[SI]
					_DI += skip_bytes;
					top++;
					egc_rows_remaining--;
				} while(!FLAGS_ZERO);
			}
		}
	}
}

void test_render(void)
{
	uint8_t mask_i = MaskI;
	if(MaskI >= MASK_COUNT) {
		mask_i = (((MASK_COUNT * 2) - 2) - MaskI);
	}
	test_func(MASKS[mask_i]);
}

void test_main(void)
{
	Palette8 palette;

	{for(unsigned int i = 0; i < IMAGE_COUNT; i++) {
		const char near* fn = PI_FN[i];
		int ret = GrpSurface_LoadPI(image[i], &palette, fn);
		if(ret) {
			printf("\xEB\xA2 Could not load %s: %d\n", fn, ret);
			return;
		}
		if(image[i].w != ROW_SIZE) {
			printf("\xEB\xA2 %s must be 640 pixels wide.\n", fn);
			return;
		}
	}}

	vsync_count_16 = 0;
	while(vsync_count_16 < 1) {
	}
	for(int i = 0; i < COLOR_COUNT; i++) {
		const RGB8 c8 = palette[i];
		RGB4 c4;

		// Slightly darken the palette to make the text more readable
		c4.c.r = (((c8.c.r * 3u) / 4u) >> 4);
		c4.c.g = (((c8.c.g * 3u) / 4u) >> 4);
		c4.c.b = (((c8.c.b * 3u) / 4u) >> 4);
		palette_show_single(i, c4);
	}

	page_access(0); graph_clear();
	page_access(1); graph_clear();

	printf("Sprite count: %u\n", t.opt[OPT_SPRITE_COUNT].val);
	puts("W   | EGC (optimized)  | EGC (ZUN)        | GRCG + CPU       | CPU only");
	for(W = 4; W <= ROW_SIZE; W += 4) {
		printf("%3d | ", (W * BYTE_DOTS));
		EGCRegionH = ((0x8000 - PLANE_SIZE) / W);
		test_func = test_egc;
		t.run(false);

		printf(" | ");
		EGCRegionH = 1;
		test_func = test_egc;
		t.run(false);

		blitter_set_source_region(0, 0, W, image_cur->h, image_cur->w);

		printf(" | ");
		test_func = test_grcg;
		t.run(false);

		printf(" | ");
		test_func = test_cpu;
		t.run(false);

		puts("");
	}

	{for(unsigned int i = 0; i < IMAGE_COUNT; i++) {
		image[i].free();
	}}
}
// ---------

void masked_startup(void)
{
	COL_CLEAR = -1;
	t.opt[OPT_SPRITE_COL].remove();
	t.opt[OPT_SPRITE_COUNT].val = 8;
	t.opt[OPT_SPRITE_COUNT].max = 0xFFFF;
	t.opt[OPT_DURATION].val = ((MASK_COUNT * 2) * 4);
	t.opt[OPT_DURATION].max = ((99 / (MASK_COUNT * 2)) * (MASK_COUNT * 2));
}

#pragma startup masked_startup
