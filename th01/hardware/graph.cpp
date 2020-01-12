#pragma option -Z

extern "C" {
#include <dos.h>
#include <mbctype.h>
#include <mbstring.h>
#include "ReC98.h"
#include "th01/hardware/egc.h"
#include "th01/hardware/vsync.h"
#include "th01/hardware/graph.h"
#include "th01/hardware/palette.hpp"

/// VRAM plane "structures"
/// -----------------------
#define Planes_declare(var) \
	planar8_t *var##_B = reinterpret_cast<planar8_t *>(MK_FP(SEG_PLANE_B, 0)); \
	planar8_t *var##_R = reinterpret_cast<planar8_t *>(MK_FP(SEG_PLANE_R, 0)); \
	planar8_t *var##_G = reinterpret_cast<planar8_t *>(MK_FP(SEG_PLANE_G, 0)); \
	planar8_t *var##_E = reinterpret_cast<planar8_t *>(MK_FP(SEG_PLANE_E, 0));

#define Planes_next_row(var) \
	var##_B += ROW_SIZE; \
	var##_R += ROW_SIZE; \
	var##_G += ROW_SIZE; \
	var##_E += ROW_SIZE;

#define Planes_offset(var, x, y) \
	var##_B += (x / 8) + (y * ROW_SIZE); \
	var##_R += (x / 8) + (y * ROW_SIZE); \
	var##_G += (x / 8) + (y * ROW_SIZE); \
	var##_E += (x / 8) + (y * ROW_SIZE);

#define PlanarRow_declare(var) \
	planar8_t var##_B[ROW_SIZE]; \
	planar8_t var##_R[ROW_SIZE]; \
	planar8_t var##_G[ROW_SIZE]; \
	planar8_t var##_E[ROW_SIZE]; \

#define PlanarRow_blit(dst, src, bytes) \
	memcpy(dst##_B, src##_B, bytes); \
	memcpy(dst##_R, src##_R, bytes); \
	memcpy(dst##_G, src##_G, bytes); \
	memcpy(dst##_E, src##_E, bytes);
/// -----------------------

/// Clipping
/// --------
#define fix_order(low, high) \
	if(low > high) { \
		order_tmp = low; \
		low = high; \
		high = order_tmp; \
	}

#define clip_min(low, high, minimum) \
	if(low < minimum) { \
		if(high < minimum) { \
			return; \
		} \
		low = minimum; \
	}

#define clip_max(low, high, maximum) \
	if(high > maximum) { \
		if(low > maximum) { \
			return; \
		} \
		high = maximum; \
	}

#define clip_x(left, right) \
	clip_min(left, right, 0); \
	clip_max(left, right, (RES_X - 1));

#define clip_y(top, bottom) \
	clip_min(top, bottom, 0); \
	clip_max(top, bottom, (RES_Y - 1));
/// --------

/// Temporary translation unit mismatch workarounds
/// -----------------------------------------------
#define GRCG_SETCOLOR_RMW(col) __asm { \
	push	col; \
	push	cs; \
	call	near ptr grcg_setcolor_rmw; \
	pop 	cx; \
}
#define GRCG_OFF() __asm { \
	push	cs; \
	call	near ptr grcg_off_func; \
}
#define GRAPH_ACCESSPAGE_FUNC(page, stack_clear_size) __asm { \
	push	page; \
	push 	cs; \
	call	near ptr graph_accesspage_func; \
}	\
_SP += stack_clear_size;
/// -----------------------------------------------

/// Pages
/// -----
extern page_t page_back;
/// -----

/// Points
/// ------
#define VRAM_SBYTE(plane, offset) \
	*reinterpret_cast<splanar8_t *>(MK_FP(SEG_PLANE_##plane, offset))

void z_grcg_pset(int x, int y, int col)
{
	GRCG_SETCOLOR_RMW(col);
	VRAM_SBYTE(B, ((y * ROW_SIZE) + (x >> 3))) = (0x80 >> (x & 7));
	GRCG_OFF();
}

int z_col_at(int x, int y)
{
	int ret;
	int vram_offset = ((y * ROW_SIZE) + (x >> 3));
	splanar16_t mask = (0x80 >> (x & 7));

#define test(plane, vram_offset, mask, bit) \
	if(VRAM_SBYTE(plane, vram_offset) & mask) { \
		ret |= bit; \
	}

	ret = 0;
	test(B, vram_offset, mask, 1);
	test(R, vram_offset, mask, 2);
	test(G, vram_offset, mask, 4);
	test(E, vram_offset, mask, 8);
	return ret;

#undef text
}
/// ------

/// Restorable line drawing
/// -----------------------
// Never read from, so it's supposedly only there for debugging purposes?
extern Point graph_r_last_line_end;
// `true` copies the pixels to be drawn from the same position on page 1, thus
// restoring them with the background image. `false` (the default) draws them
// regularly the given [col].
extern bool graph_r_restore_from_1;
// Not used for purely horizontal lines.
extern planar16_t graph_r_pattern;

void graph_r_hline(int left, int right, int y, int col)
{
	int full_bytes_to_put;
	int order_tmp;
	planar8_t left_pixels;
	planar8_t right_pixels;
	planar8_t *vram_row;

	fix_order(left, right);
	clip_x(left, right);

	graph_r_last_line_end.x = right;
	graph_r_last_line_end.y = y;

	vram_row = (planar8_t *)(MK_FP(GRAM_400, (y * ROW_SIZE) + (left / 8)));
	full_bytes_to_put = (right / 8) - (left / 8);
	left_pixels = 0xFF >> (left & 7);
	right_pixels = 0xFF << (7 - (right & 7));

	if(!graph_r_restore_from_1) {
		GRCG_SETCOLOR_RMW(col);
	}
	if(graph_r_restore_from_1) {
		egc_copy_rect_1_to_0(left, y, RES_X - left, 1);
	} else {
		if(full_bytes_to_put == 0) {
			vram_row[0] = (left_pixels & right_pixels);
		} else {
			vram_row[0] = left_pixels;
			for(register int x = 1; x < full_bytes_to_put; x++) {
				vram_row[x] = 0xFF;
			}
			vram_row[full_bytes_to_put] = right_pixels;
		}
	}
	if(!graph_r_restore_from_1) {
		GRCG_OFF();
	}
}

void graph_r_vline(int x, int top, int bottom, int col)
{
	int y;
	int order_tmp;
	planar16_t pattern;
	int vram_row_offset;

	fix_order(top, bottom);
	clip_y(top, bottom);

	graph_r_last_line_end.x = x;
	graph_r_last_line_end.y = bottom;

	if(graph_r_restore_from_1) {
		egc_copy_rect_1_to_0(x, top, sizeof(pattern) * 8, bottom - top);
		return;
	}
	vram_row_offset = VRAM_OFFSET(x, top);
	pattern = graph_r_pattern >> (x & 7);
	pattern |= graph_r_pattern << (16 - (x & 7));

	GRCG_SETCOLOR_RMW(col);
	for(y = top; y <= bottom; y++) {
		VRAM_PUT(B, vram_row_offset, pattern, 16);
		vram_row_offset += ROW_SIZE;
	}
	GRCG_OFF();
}

void graph_r_line_from_1(int left, int top, int right, int bottom)
{
	graph_r_restore_from_1 = true;
	graph_r_line(left, top, right, bottom, 7);
	graph_r_restore_from_1 = false;
}

void graph_r_line_patterned(
	int left, int top, int right, int bottom, int col, planar16_t pattern
)
{
	graph_r_pattern = pattern;
	graph_r_line(left, top, right, bottom, col);
	graph_r_pattern = 0x80;
}

void graph_r_line(int left, int top, int right, int bottom, int col)
{
	register int vram_offset;
	int i;
	int x_cur, y_cur;
	int w, h;
	int error;
	int y_direction;
	int order_tmp;
	int x_vram, y_vram;
	planar16_t pixels;

	vram_planar_32_pixels_t page1;

#define slope_x ((bottom - top) / (right - left))
#define slope_y ((right - left) / (bottom - top))
#define lerp(m, x) static_cast<int>(m * static_cast<float>(x))

#define clip_lerp_min(low, high, lerp_point, slope, minimum) \
	if(low < minimum) { \
		if(high < minimum) { \
			return; \
		} \
		lerp_point += lerp(slope, (minimum - low)); \
		low = minimum; \
	}
#define clip_lerp_max(low, high, lerp_point, slope, maximum) \
	if(high > maximum) { \
		if(low > maximum) { \
			return; \
		} \
		lerp_point -= lerp(slope, (high - maximum)); \
		high = maximum; \
	}

#define restore_at(bit_count) \
	GRAPH_ACCESSPAGE_FUNC(1, 0);	VRAM_SNAP_4(page1, vram_offset, 32); \
	GRAPH_ACCESSPAGE_FUNC(0, 4);	VRAM_PUT_4(vram_offset, page1, 32);

#define plot_loop(\
	step_var, step_len, step_increment, \
	plotted_var, plotted_len, plotted_increment \
) \
	error = (step_len >> 1); \
	for(i = 0; i <= step_len; i++) { \
		/* Advanced past the VRAM cursor? */ \
		if((x_cur >> 3) != x_vram || (y_vram != y_cur)) { \
			vram_offset = (y_vram * ROW_SIZE) + x_vram; \
			if(!graph_r_restore_from_1) { \
				VRAM_PUT(B, vram_offset, pixels, 16); \
				pixels = 0; \
			} else { \
				vram_offset--; \
				restore_at(vram_offset); \
			} \
			y_vram = y_cur; \
			x_vram = (x_cur >> 3); \
		} \
		pixels |= (graph_r_pattern >> (x_cur & 7)); \
		pixels |= (graph_r_pattern << (16 - (x_cur & 7))); \
		error -= plotted_len; \
		step_var += step_increment; \
		if(error < 0) { \
			error += step_len; \
			plotted_var += plotted_increment; \
		} \
	} \
	if(graph_r_restore_from_1) { \
		goto restore_last; \
	} \
	goto end;

	if(!graph_r_restore_from_1 && (left == right)) {
		graph_r_vline(left, top, bottom, col);
		return;
	}
	if(!graph_r_restore_from_1 && (top == bottom)) {
		graph_r_hline(left, right, top, col);
		return;
	}
	if(left > right) {
		order_tmp = left;
		left = right;
		right = order_tmp;
		order_tmp = top;
		top = bottom;
		bottom = order_tmp;
	}

	clip_lerp_min(left, right, top, slope_x, 0);
	clip_lerp_max(left, right, bottom, slope_x, (RES_X - 1));
	clip_lerp_min(top, bottom, left, slope_y, 0);
	clip_lerp_max(top, bottom, right, slope_y, (RES_Y - 1));
	if(bottom < 0) {
		right += lerp(slope_y, 0 - bottom);
		bottom = 0;
	}
	if(top > (RES_Y - 1)) {
		left -= lerp(slope_y, top - (RES_Y - 1));
		top = (RES_Y - 1);
	}
	graph_r_last_line_end.x = right;
	graph_r_last_line_end.y = bottom;
	x_cur = left;
	y_cur = top;
	y_direction = (top < bottom) ? 1 : -1;
	w = right - left;
	h = (bottom - top) * y_direction;
	pixels = 0;
	x_vram = (x_cur >> 3);
	y_vram = y_cur;

	if(!graph_r_restore_from_1) {
		GRCG_SETCOLOR_RMW(col);
	}
	if(w > h) {
		plot_loop(x_cur, w, 1, y_cur, h, y_direction);
	} else {
		plot_loop(y_cur, h, y_direction, x_cur, w, 1);
	}
restore_last:
	vram_offset = VRAM_OFFSET(x_cur, y_cur) - 1;
	restore_at(vram_offset);
end:
	if(!graph_r_restore_from_1) {
		GRCG_OFF();
	}

#undef plot_loop
#undef restore_at
#undef clip_lerp_min
#undef clip_lerp_max
#undef slope
}
/// -----------------------

void z_grcg_boxfill(int left, int top, int right, int bottom, int col)
{
	int x;
	int y;
	int full_bytes_to_put;
	int order_tmp;
	planar8_t left_pixels;
	planar8_t right_pixels;
	planar8_t *vram_row;

	fix_order(left, right);
	fix_order(top, bottom);
	clip_x(left, right);
	clip_y(top, bottom);

	GRCG_SETCOLOR_RMW(col);
	vram_row = (planar8_t *)(MK_FP(GRAM_400, (top * ROW_SIZE) + (left >> 3)));
	for(y = top; y <= bottom; y++) {
		full_bytes_to_put = (right >> 3) - (left >> 3);
		left_pixels = 0xFF >> (left & 7);
		right_pixels = 0xFF << (7 - (right & 7));

		if(full_bytes_to_put == 0) {
			vram_row[0] = (left_pixels & right_pixels);
		} else {
			vram_row[0] = left_pixels;
			for(x = 1; x < full_bytes_to_put; x++) {
				vram_row[x] = 0xFF;
			}
			vram_row[full_bytes_to_put] = right_pixels;
		}
		vram_row += ROW_SIZE;
	}
	GRCG_OFF();
}

void graph_r_box(int left, int top, int right, int bottom, int col)
{
	graph_r_hline(left, right, top, col);
	graph_r_vline(left, top, bottom, col);
	graph_r_vline(right, top, bottom, col);
	graph_r_hline(left, right, bottom, col);
}

int text_extent_fx(int fx, const unsigned char *str)
{
	register int ret = 0;
	register int spacing = (fx / 0x40) % 8;
	while(*str) {
		if(_ismbblead(str[0])) {
			uint16_t codepoint = ((char)str[0] << 8) + str[0];
			str++;
			str++;
			if(codepoint < 0x8540) {
				ret += GLYPH_FULL_W;
			} else if(codepoint > 0x869E) {
				ret += GLYPH_FULL_W;
			} else {
				ret += GLYPH_HALF_W;
			}
		} else {
			ret += GLYPH_HALF_W;
			str++;
		}
		ret += spacing;
	}
	return ret - spacing;
}

#include "th01/hardware/grppsafx.c"

void graph_putsa_fx(int left, int top, int fx, const unsigned char *str)
{
	uint16_t codepoint;
	planar16_t glyph_row;
	unsigned char far *vram;
	int fullwidth;
	int first_bit;
	int weight = (fx / 0x10) % 4;
	int spacing = (fx / 0x40) % 8;
	int clear_bg = (fx & FX_CLEAR_BG);
	int underline = (fx & FX_UNDERLINE);
	int reverse = (fx & FX_REVERSE);
	int w;
	int line;
	planar16_t glyph[GLYPH_H];
	planar16_t glyph_row_tmp;

	if(clear_bg) {
		w = text_extent_fx(fx, str);
		if(underline) {
			z_grcg_boxfill(left, top, (left + w - 1), (top + GLYPH_H + 1), 0);
			graph_r_hline(left, (left + w - 1), (top + GLYPH_H + 1), 7);
		} else {
			z_grcg_boxfill(left, top, (left + w - 1), (top + GLYPH_H - 1), 0);
		}
	} else if(underline) {
		w = text_extent_fx(fx, str);
		graph_r_hline(left, (left + w - 1), (top + GLYPH_H + 1), 7);
	}

	GRCG_SETCOLOR_RMW(fx);
	OUTB(0x68, 0xB); // CG ROM dot access

	while(str[0]) {
		set_vram_ptr(vram, first_bit, left, top);
		get_glyph(glyph, codepoint, fullwidth, str, left, line);

		for(line = 0; line < GLYPH_H; line++) {
			apply_weight(glyph_row, glyph[line], glyph_row_tmp, weight);
			if(reverse) {
				if(fullwidth) {
					glyph_row ^= 0xFFFF;
				} else {
					glyph_row ^= 0xFF00;
				}
			}
			put_row_and_advance(vram, glyph_row, first_bit);
		}
		advance_left(left, fullwidth, spacing);
	}

	OUTB(0x68, 0xA); // CG ROM code access
	GRCG_OFF();
}

void graph_copy_byterect_back_to_front(
	int left, int top, int right, int bottom
)
{
	int w = (right - left) / 8;
	int h = (bottom - top);
	Planes_declare(p);
	page_t page_front = page_back ^ 1;
	int row;
	PlanarRow_declare(tmp);

	Planes_offset(p, left, top);
	for(row = 0; row < h; row++) {
		PlanarRow_blit(tmp, p, w);
		graph_accesspage(page_front);
		PlanarRow_blit(p, tmp, w);
		graph_accesspage(page_back);
		Planes_next_row(p);
	}
}

void graph_move_byterect_interpage(
	int src_left, int src_top, int src_right, int src_bottom,
	int dst_left, int dst_top,
	page_t src, page_t dst
)
{
	int w = (src_right - src_left) / 8;
	int h = (src_bottom - src_top);
	Planes_declare(src);
	Planes_declare(dst);
	int row;
	PlanarRow_declare(tmp);

	Planes_offset(src, src_left, src_top);
	Planes_offset(dst, dst_left, dst_top);
	for(row = 0; row < h; row++) {
		PlanarRow_blit(tmp, src, w);
		graph_accesspage(dst);
		PlanarRow_blit(dst, tmp, w);
		graph_accesspage(src);
		Planes_next_row(src);
		Planes_next_row(dst);
	}
	graph_accesspage(page_back);
}

void z_palette_fade_from(
	uint4_t from_r, uint4_t from_g, uint4_t from_b,
	int keep[COLOR_COUNT],
	unsigned int step_ms
)
{
	RGB4 fadepal[COLOR_COUNT];
	int i;
	int col;
	int comp;

	memset(&fadepal, 0x0, sizeof(fadepal));
	for(i = 0; i < COLOR_COUNT; i++) {
		if(!keep[i]) {
			fadepal[i].c.r = from_r;
			fadepal[i].c.g = from_g;
			fadepal[i].c.b = from_b;
		} else {
			fadepal[i].c.r = z_Palettes.colors[i].c.r;
			fadepal[i].c.g = z_Palettes.colors[i].c.g;
			fadepal[i].c.b = z_Palettes.colors[i].c.b;
		}
	}
	for(i = 0; i < 16; i++) {
		z_vsync_wait();
		for(col = 0; col < COLOR_COUNT; col++) {
			for(comp = 0; comp < sizeof(RGB4); comp++) {
				if(fadepal[col].v[comp] != z_Palettes.colors[col].v[comp]) {
					fadepal[col].v[comp] +=
						(fadepal[col].v[comp] < z_Palettes.colors[col].v[comp])
						?  1
						: -1;
				}
			}
			/* TODO: Replace with the decompiled call
			 * z_palette_show_single_col(col, fadepal[col]);
			 * once that function is part of this translation unit */
			__asm {
#define push_comp(comp) \
	mov 	bx, col; \
	db 0x6B, 0xDB, 0x03; /* IMUL BX, 3, which Turbo C++ can't into? */	\
	lea 	ax, fadepal[comp]; \
	db 0x03, 0xD8; /* Turbo C++'s preferred opcode for ADD BX, AX */ \
	mov 	al, ss:[bx]; \
	cbw; \
	push	ax;
				push_comp(2)
				push_comp(1)
				push_comp(0)
				push	col
				push	cs
				call	near ptr z_palette_show_single
				add 	sp, 8
			}
		}
		delay(step_ms);
	}
}

// Resident palette
// ----------------
#define RESPAL_ID "pal98 grb"
struct hack { char x[sizeof(RESPAL_ID)]; }; // XXX
extern const hack PAL98_GRB;

#pragma option -a1
// MASTER.MAN suggests that GBR ordering is some sort of standard on PC-98.
// It does match the order of the hardware's palette register ports, after
// all. (0AAh = green, 0ACh = red, 0AEh = blue)
struct grb_t {
	uint4_t g, r, b;
};

struct respal_t {
	char id[sizeof(RESPAL_ID)];
	unsigned char tone;
	int8_t padding[5];
	grb_t pal[COLOR_COUNT];
};
// ----------------

// Memory Control Block
// Adapted from FreeDOS' kernel/hdr/mcb.h
// --------------------
#define MCB_NORMAL 0x4d
#define MCB_LAST   0x5a

struct mcb_t {
	uint8_t m_type;	// mcb type - chain or end
	uint16_t __seg* m_psp;	// owner id via psp segment
	uint16_t m_size;	// size of segment in paragraphs
	uint8_t m_fill[3];
	uint8_t m_name[8];
};
#pragma option -a.

respal_t __seg* z_respal_exist(void)
{
	union REGS regs;
	struct SREGS sregs;
	const hack ID = PAL98_GRB;
	seg_t mcb;
	int i;

#define MCB reinterpret_cast<mcb_t __seg *>(mcb)	/* For easy derefencing */
#define MCB_PARAS (sizeof(mcb_t) / 16)	/* For segment pointer arithmetic */

	// "Get list of lists"
	segread(&sregs);
	regs.h.ah = 0x52;
	intdosx(&regs, &regs, &sregs);

	mcb = *reinterpret_cast<seg_t *>(MK_FP(sregs.es, regs.w.bx - 2));
	while(1) {
		if(MCB->m_psp != 0) {
			for(i = 0; i < sizeof(ID); i++) {
				if(reinterpret_cast<respal_t *>(MCB + 1)->id[i] != ID.x[i]) {
					break;
				}
			}
			if(i == sizeof(ID)) {
				return reinterpret_cast<respal_t __seg *>(mcb + MCB_PARAS);
			}
		}
		if(MCB->m_type != MCB_NORMAL) {
			return 0;
		}
		mcb += MCB_PARAS + MCB->m_size;
	};

#undef MCB_PARAS
#undef MCB
}

int z_respal_get_show(void)
{
	int i;
	respal_t __seg *respal_seg = z_respal_exist();
	if(respal_seg) {
		grb_t *respal = respal_seg->pal;
		for(i = 0; i < COLOR_COUNT; i++) {
			/* TODO: Replace with the decompiled call
			 * z_palette_set_show(i, respal->r, respal->g, respal->b);
			 * once that function is part of this translation unit */
			__asm {
				les 	bx, respal
				mov 	al, es:[bx+2]
				cbw
				push	ax
				mov 	al, es:[bx+0]
				cbw
				push	ax
				mov 	al, es:[bx+1]
				cbw
				push	ax
				// Spelling out PUSH SI causes Turbo C++ to interpret SI as
				// reserved, and it then moves [i] to DI rather than SI
				db	0x56
				push	cs
				call	near ptr z_palette_set_show
				add 	sp, 8
			}
			respal++;
		}
		return 0;
	}
	return 1;
}

int z_respal_set(void)
{
	int i;
	respal_t __seg *respal_seg = z_respal_exist();
	if(respal_seg) {
		grb_t *respal = respal_seg->pal;
		for(i = 0; i < COLOR_COUNT; i++) {
			respal->g = z_Palettes.colors[i].c.g;
			respal->r = z_Palettes.colors[i].c.r;
			respal->b = z_Palettes.colors[i].c.b;
			respal++;
		}
		return 0;
	}
	return 1;
}

}
