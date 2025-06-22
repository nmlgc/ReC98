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
// -----------------------------

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
