// PC-98 sprite and image management
// ---------------------------------

#include "platform/x86real/pc98/grp_surf.hpp"
#include "platform/x86real/pc98/blitter.hpp"
#include "platform/x86real/pc98/egc.hpp"
#include "platform/x86real/flags.hpp"
#include "libs/master.lib/master.hpp"
#include "libs/piloadc/piloadm.hpp"
#include "x86real.h"

static const uint16_t PILOAD_BUFFER_SIZE = 0x4000;

// The research tools don't have the [VRAM_PLANE] array from `planar.h`.
static const seg_t VRAM_PLANES[PLANE_COUNT] = {
	SEG_PLANE_B, SEG_PLANE_R, SEG_PLANE_G, SEG_PLANE_E,
};

// Interfacing with the blitters
// -----------------------------

void near blitter_set_source_region_for(
	seg_t plane_B,
	uvram_byte_amount_t stride,
	pixel_t h,
	const LTWH<upixel_t> near *region
)
{
	blit_source.dots_start.fp = MK_FP(plane_B, 0);
	blit_source.stride = stride;
	if(region) {
		vram_x_t vram_left = (region->left / BYTE_DOTS);
		blit_source.offset = ((region->top * stride) + vram_left);
		blit_source.w = (
			((region->left + region->w + BYTE_MASK) / BYTE_DOTS) - vram_left
		);
		blit_source.h = region->h;
	} else {
		blit_source.offset = 0;
		blit_source.w = blit_source.stride;
		blit_source.h = h;
	}
}

#define blitter_func_4plane(func, plane_paras) { \
	_DI = plane_paras; \
	func(SEG_PLANE_B); blit_source.dots_start.part.seg += _DI; \
	func(SEG_PLANE_R); blit_source.dots_start.part.seg += _DI; \
	func(SEG_PLANE_G); blit_source.dots_start.part.seg += _DI; \
	func(SEG_PLANE_E); \
}

void near blitter_write_offscreen_4plane_fast(uint16_t plane_paras)
{
	_asm {
		cld;
		push ds;
#if (CPU >= 286)
		push SEG_PLANE_E;
		push SEG_PLANE_G;
		push SEG_PLANE_R;
		push SEG_PLANE_B;
#else
		mov ax, SEG_PLANE_E; push ax;
		mov ax, SEG_PLANE_G; push ax;
		mov ax, SEG_PLANE_R; push ax;
		mov ax, SEG_PLANE_B; push ax;
#endif
	}
	register seg_t sprite_seg = blit_source.dots_start.part.seg;
	const uint16_t rep_movs_units = (
#if (CPU == 386)
		((blit_state.h_clipped * blit_state.w_clipped) + 3) / 4u
#else
		((blit_state.h_clipped * blit_state.w_clipped) + 1) / 2u
#endif
	);

	// We assume [blit_state.sprite_offset] to be 0 here.
	_AX = blit_source.dots_start.part.off;
	register uint8_t planes_remaining = PLANE_COUNT;
	do {
		_asm pop es;
		_DS = sprite_seg;
		_DI = vram_offset_shift(0, RES_Y);
		_SI = _AX;
		_CX = rep_movs_units;
#if (CPU == 386)
		__emit__(0xF3, 0x66, 0xA5); // REP MOVSD
#else
		__emit__(0xF3, 0xA5); // REP MOVSW
#endif
		sprite_seg += plane_paras;
		planes_remaining--;
	} while(!FLAGS_ZERO);
	_asm pop ds;
}
// -----------------------------

inline uint16_t plane_paras_for(uvram_byte_amount_t vram_w, upixel_t h) {
	return (((vram_w * h) + 15) / 16);
}

bool near surface_alloc(
	GrpSurface_M& surf, upixel_t w, upixel_t h, unsigned int plane_count
)
{
	surf.free();
	const uvram_byte_amount_t vram_w = ((w + BYTE_MASK) / BYTE_DOTS);
	const uint16_t plane_paras = plane_paras_for(vram_w, h);
	const seg_t plane_B = reinterpret_cast<seg_t>(
		hmem_alloc(plane_paras * plane_count)
	);
	if(!plane_B) {
		return true;
	}
	surf.plane_B = plane_B;
	surf.plane_paras = plane_paras;
	surf.w = vram_w;
	surf.h = h;
	return false;
}

// Surface classes
// ---------------

void GrpSurface_M::free(void)
{
	if(!plane_B) {
		return;
	}
	hmem_free(reinterpret_cast<void __seg *>(plane_B));
	plane_B = 0;
	plane_paras = 0;
	w = 0;
	h = 0;
}

bool GrpSurface_M1::alloc(upixel_t w, upixel_t h)
{
	return surface_alloc(*this, w, h, 1);
}

void GrpSurface_M1::snap(
	uscreen_x_t dst_left,
	uscreen_y_t dst_top,
	vram_plane_t plane,
	const LTWH<upixel_t> near *region
)
{
	blitter_set_source_region_for(VRAM_PLANES[plane], ROW_SIZE, h, region);
	blit_source.stride = w;

	// `blitter_init_noclip((dst_left / BYTE_DOTS), dst_top).snap(plane_B);`
	// would miscompile; see `Borland C++ decompilation.md` for details.
	const Blitter __ds& b = blitter_init_noclip(
		(dst_left / BYTE_DOTS), dst_top
	);
	b.snap(plane_B);
}

void GrpSurface_M1::write(
	vram_plane_t plane,
	screen_x_t left,
	screen_y_t top,
	const LTWH<upixel_t> near *region
)
{
	blitter_set_source_region_for(plane_B, ROW_SIZE, h, region);
	const Blitter __ds* b = blitter_init_clip((left >> BYTE_BITS), top);
	if(!b) {
		return;
	}
	b->write(VRAM_PLANES[plane]);
}

bool GrpSurface_M4::alloc(upixel_t w, upixel_t h)
{
	return surface_alloc(*this, w, h, 4);
}

void GrpSurface_M4::snap(
	uscreen_x_t dst_left,
	uscreen_y_t dst_top,
	const LTWH<upixel_t> near *region
)
{
	blitter_set_source_region_for(SEG_PLANE_B, ROW_SIZE, h, region);
	blit_source.stride = w;
	const Blitter __ds& b = blitter_init_noclip(
		(dst_left / BYTE_DOTS), dst_top
	);
	_SI = plane_B;
	_DI = plane_paras;
	b.snap(_SI); _SI += _DI; blit_source.dots_start.part.seg = SEG_PLANE_R;
	b.snap(_SI); _SI += _DI; blit_source.dots_start.part.seg = SEG_PLANE_G;
	b.snap(_SI); _SI += _DI; blit_source.dots_start.part.seg = SEG_PLANE_E;
	b.snap(_SI);
}

void GrpSurface_M4::write(
	screen_x_t left, screen_y_t top, const LTWH<upixel_t> near *region
)
{
	blitter_set_source_region_for(plane_B, w, h, region);
	const Blitter __ds* b = blitter_init_clip((left >> BYTE_BITS), top);
	if(!b) {
		return;
	}
	blitter_func_4plane(b->write, this->plane_paras);
}

void GrpSurface_M4::write_bg_region(
	upixel_t left, upixel_t top, upixel_t w, upixel_t h
)
{
	static LTWH<upixel_t> region;
	region.left = left;
	region.top = top;
	region.w = w;
	region.h = h;
	write(left, top, &region);
}

void GrpSurface_M4::or_masked(
	screen_x_t left,
	screen_y_t top,
	const dots16_t __ds *masks,
	unsigned int mask_count,
	const LTWH<upixel_t> near *region
)
{
	const seg_t plane_paras = this->plane_paras;
	blitter_set_source_region_for(plane_B, w, h, region);
	const Blitter __ds* b = blitter_init_clip((left >> BYTE_BITS), top);
	if(!b) {
		return;
	}
	void (__fastcall *write_offscreen)(seg_t) = b->write_offscreen;
	const upixel_t pixel_w_clipped = (blit_state.w_clipped * BYTE_DOTS);
	unsigned int mask_offset = 0;
	unsigned int mask_offset_mask = ((mask_count * sizeof(masks[0])) - 1);
	const upixel_t egc_words = (
		(pixel_w_clipped + (EGC_REGISTER_DOTS - 1)) / EGC_REGISTER_DOTS
	);
	const uvram_byte_amount_t skip_bytes = (ROW_SIZE - blit_state.w_clipped);

	// Since the EGC preserves its registers across activations, we only have
	// to do the general setup once.
	{
		EGC egc;
		outport(EGC_ACTIVEPLANEREG, 0xFFF0);
		outport(EGC_READPLANEREG, 0x00FF);
		outport(EGC_ADDRRESSREG, (left & EGC_REGISTER_MASK));
		outport(EGC_BITLENGTHREG, (pixel_w_clipped - 1));
		outport(EGC_MODE_ROP_REG, 0x29F0);
	}

	pixel_t rows_remaining = blit_state.h_clipped;
	const bool fast_blit_path = (blit_state.w_clipped == blit_source.stride);
	blit_state.h_clipped = ((0x8000 - PLANE_SIZE) / blit_state.w_clipped);
	while(rows_remaining > 0) {
		if(rows_remaining < blit_state.h_clipped) {
			blit_state.h_clipped = rows_remaining;
		}
		if(fast_blit_path) {
			blitter_write_offscreen_4plane_fast(plane_paras);
		} else {
			_SI = blit_source.dots_start.part.seg;
			blitter_func_4plane(write_offscreen, plane_paras);
			blit_source.dots_start.part.seg = _SI;
		}

		pixel_t egc_rows_remaining = blit_state.h_clipped;
		blit_source.dots_start.part.off += (
			egc_rows_remaining * blit_source.stride
		);

		// x86 only supports 8-bit port numbers as immediates… :(
		_DX = EGC_MASKREG;

		_ES = SEG_PLANE_B;
		_SI = vram_offset_shift(0, RES_Y);
		_DI = blit_state.vo;
		blit_state.vo += (egc_rows_remaining * ROW_SIZE);
		rows_remaining -= egc_rows_remaining;
		_asm { cld; }
		{
			EGC egc;
			do {
				outport(_DX, *reinterpret_cast<uint16_t __ds *>( \
					FP_OFF(masks) + mask_offset \
				));
				_CX = egc_words;
				__emit__(0xF3, 0x26, 0xA5); // REP MOVSW ES:[DI], ES:[SI]
				_DI += skip_bytes;
				mask_offset += sizeof(masks[0]);
				mask_offset &= mask_offset_mask;
				egc_rows_remaining--;
			} while(!FLAGS_ZERO);
		}
	}
}
// ---------------

// Pulling the palette out of the buffer this way might look like reliance on
// implementation details, but it is, in fact, officially sanctioned by
// PILOADC.DOC.
void near piload_maybe_extract_palette(Palette8 *palette, int8_t __seg *buf)
{
	if(palette) {
		*palette = *reinterpret_cast<const Palette8 far *>(MK_FP(buf, 0x100));
	}
}

#ifndef __LARGE__
int far file_read_far(void far *buf, unsigned wsize)
{
	return file_read(buf, wsize);
}
#define file_read file_read_far
#endif

int GrpSurface_LoadPI(
	GrpSurface_M4& surf, Palette8 *palette, const char *fn, pi_flag_t flags
)
{
	int ret;
	uint8_t option = 0;
	uint16_t plane_paras_new;

	if(!file_ropen(fn)) {
		return FileNotFound;
	}

	int8_t __seg *buf = HMem<int8_t>::alloc(PILOAD_BUFFER_SIZE);
	if(!buf) {
		ret = InsufficientMemory;
		goto err_with_file;
	}
	if(flags & PIF_LINESKIP) {
		option |= PILOAD_OPT_LINESKIP;
	}
	ret = PiLoadHeaderL(buf, PILOAD_BUFFER_SIZE, file_read, option);
	if(ret < 0) {
		goto err_with_file_and_buf;
	}

	// Reuse the existing allocation if the new image is exactly as large as
	// the old one. ZUN designated rather small heaps for the game processes,
	// and certain master.lib functions (*cough* pf*() *cough*) can leave the
	// heap in an unusually fragmented state. Thus, we might not be able to
	// place the newly allocated image anywhere else than at the same general
	// position where we already loaded an image.
	plane_paras_new = (static_cast<uint16_t>(ret) / PLANE_COUNT);
	if(plane_paras_new != surf.plane_paras) {
		surf.free();
		surf.plane_B = FP_SEG(hmem_alloc(ret));
		if(!surf.plane_B) {
			ret = InsufficientMemory;
			goto err_with_file_and_buf;
		}
		surf.plane_paras = plane_paras_new;
	}

	ret = PiLoadPlanesL(surf.plane_B, buf, PILOAD_BUFFER_SIZE);

	surf.w = (
		*reinterpret_cast<const uint16_t far *>(MK_FP(buf, 0x134)) / BYTE_DOTS
	);
	surf.h = *reinterpret_cast<const uint16_t far *>(MK_FP(buf, 0x136));
	surf.plane_B = *reinterpret_cast<const seg_t far *>(MK_FP(buf, 0x14C));
	piload_maybe_extract_palette(palette, buf);
err_with_file_and_buf:
	HMem<int8_t>::free(buf);
err_with_file:
	file_close();
	return ret;
}

int GrpSurface_BlitBackgroundPI(Palette8 *palette, const char *fn)
{
	int ret;

	if(!file_ropen(fn)) {
		return FileNotFound;
	}

	int8_t __seg *buf = HMem<int8_t>::alloc(PILOAD_BUFFER_SIZE);
	if(!buf) {
		ret = InsufficientMemory;
		goto err_with_file;
	}
	ret = PiBlitL(buf, PILOAD_BUFFER_SIZE, 0, 0, 0, file_read);
	piload_maybe_extract_palette(palette, buf);

	HMem<int8_t>::free(buf);
err_with_file:
	file_close();
	return ret;
}
