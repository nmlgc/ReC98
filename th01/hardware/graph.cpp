#pragma option -Z

extern "C" {
#include <dos.h>
#include <mbctype.h>
#include <mbstring.h>
#include "ReC98.h"
#include "th01/hardware/egc.h"
#include "th01/hardware/vsync.h"
#include "th01/hardware/graph.h"
#include "th01/hardware/palette.h"

#undef grcg_off
#define grcg_off() outportb(0x7C, 0);

extern page_t page_back;

/// VRAM plane "structures"
/// -----------------------
#define Planes_declare(var) \
	dots8_t *var##_B = reinterpret_cast<dots8_t *>(MK_FP(SEG_PLANE_B, 0)); \
	dots8_t *var##_R = reinterpret_cast<dots8_t *>(MK_FP(SEG_PLANE_R, 0)); \
	dots8_t *var##_G = reinterpret_cast<dots8_t *>(MK_FP(SEG_PLANE_G, 0)); \
	dots8_t *var##_E = reinterpret_cast<dots8_t *>(MK_FP(SEG_PLANE_E, 0));

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
	dots8_t var##_B[ROW_SIZE]; \
	dots8_t var##_R[ROW_SIZE]; \
	dots8_t var##_G[ROW_SIZE]; \
	dots8_t var##_E[ROW_SIZE]; \

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

/// BIOS
/// ----
inline void graph_access_and_show_0()
{
	graph_accesspage_func(0);
	graph_showpage_func(0);
}

inline void cgrom_code_and_grcg_off()
{
	outportb(0x68, 0xA); // CG ROM code access
	grcg_off();
}

inline void z_graph_400line()
{
	REGS regs;

	z_graph_hide();

	// 640x400
	regs.h.ah = 0x42;
	regs.h.ch = 0xC0;
	int86(0x18, &regs, &regs);

	// 16-color, analog mode
	outportb(0x6A, 1);
}

inline void z_graph_access_and_show_0()
{
	graph_access_and_show_0();
	cgrom_code_and_grcg_off();
	z_graph_show();
}

void z_graph_init()
{
	z_graph_400line();
	z_palette_set_all_show(z_Palettes);
	graph_access_and_show_0();
	z_graph_clear_0();
	cgrom_code_and_grcg_off();
	z_graph_show();
}

void graph_400line_access_and_show_0()
{
	z_graph_400line();
	z_graph_access_and_show_0();
}

void z_graph_exit()
{
	z_palette_black();
	z_graph_clear_0();
	graph_access_and_show_0();
	z_graph_show();
	cgrom_code_and_grcg_off();
}

void z_graph_show()
{
	REGS regs;
	regs.h.ah = 0x40;
	int86(0x18, &regs, &regs);
}

void z_graph_hide()
{
	REGS regs;
	regs.h.ah = 0x41;
	int86(0x18, &regs, &regs);
}
/// ----

/// Page flipping
/// -------------
void graph_showpage_func(page_t page)
{
	outportb(0xA4, page);
}

void graph_accesspage_func(int page)
{
	page_back = page;
	outportb(0xA6, page);
}
/// -------------

/// Hardware
/// --------
void z_palette_show_single(int col, int r, int g, int b)
{
	outportb(0xA8, col);
	outportb(0xAA, g);
	outportb(0xAC, r);
	outportb(0xAE, b);
}

#define grcg_setcolor(mode, col) \
	outportb(0x7C, mode); \
	outportb(0x7E, (col & 1) ? 0xFF : 0x00); \
	outportb(0x7E, (col & 2) ? 0xFF : 0x00); \
	outportb(0x7E, (col & 4) ? 0xFF : 0x00); \
	outportb(0x7E, (col & 8) ? 0xFF : 0x00);

void grcg_setcolor_rmw(int col)
{
	grcg_setcolor(0xC0, col);
}

void grcg_setcolor_tdw(int col)
{
	grcg_setcolor(0x80, col);
}

void grcg_off_func(void)
{
	grcg_off();
}
/// --------

/// Palette
/// -------
void z_palette_set_all_show(const Palette4& pal)
{
	for(int i = 0; i < COLOR_COUNT; i++) {
		z_palette_set_show(i, pal[i].c.r, pal[i].c.g, pal[i].c.b);
	}
}

void z_palette_set_show(int col, int r, int g, int b)
{
#define clamp_max(comp) ((comp) < RGB4::max() ? (comp) : RGB4::max())
#define clamp_min(comp) ((comp) > 0 ? (comp) : 0)
	r = clamp_min(clamp_max(r));
	g = clamp_min(clamp_max(g));
	b = clamp_min(clamp_max(b));

	z_Palettes[col].c.r = r;
	z_Palettes[col].c.g = g;
	z_Palettes[col].c.b = b;
	z_palette_show_single(col, r, g, b);
#undef clamp_max
#undef clamp_min
}
/// -------

/// Whole-page functions
/// --------------------
void z_graph_clear()
{
	dots8_t *plane = reinterpret_cast<dots8_t *>(MK_FP(SEG_PLANE_B, 0));

	grcg_setcolor_rmw(0);
	memset(plane, 0xFF, PLANE_SIZE);
	grcg_off_func();
}

void z_graph_clear_0(void)
{
	// Yes, page 2, twice. Which effectively is the same as page 0... at least
	// according to any real hardware and emulator tests I could come up with.
	graph_accesspage_func(2);	z_graph_clear();
	graph_accesspage_func(2);	z_graph_clear();
}

void z_graph_clear_col(uint4_t col)
{
	dots8_t *plane = reinterpret_cast<dots8_t *>(MK_FP(SEG_PLANE_B, 0));

	grcg_setcolor_rmw(col);
	memset(plane, 0xFF, PLANE_SIZE);
	grcg_off_func();
}

void graph_copy_page_back_to_front(void)
{
	PlanarRow_declare(tmp);
	Planes_declare(p);
	page_t page_front = (page_back ^ 1);

	for(int y = 0; y < RES_Y; y++) {
		PlanarRow_blit(tmp, p, ROW_SIZE);
		graph_accesspage(page_front);
		PlanarRow_blit(p, tmp, ROW_SIZE);
		graph_accesspage(page_back);
		Planes_next_row(p);
	}
}
/// --------------------

/// Palette fades
/// -------------
#define FADE_DELAY 10
#define fade_loop(pal, per_comp) \
	for(int i = 0; i < pal.range(); i++) { \
		z_vsync_wait(); \
		for(int col = 0; col < COLOR_COUNT; col++) { \
			for(int comp = 0; comp < sizeof(RGB4); comp++) { \
				per_comp; \
			} \
			z_palette_show_single_col(col, pal[col]); \
		} \
		delay(FADE_DELAY); \
	}

void z_palette_black(void)
{
	for(int col = 0; col < COLOR_COUNT; col++) {
		z_palette_show_single(col, 0, 0, 0);
	}
}

void z_palette_black_in(void)
{
	Palette4 fadepal;
	memset(&fadepal, 0, sizeof(Palette4));
	fade_loop(fadepal,
		if(fadepal[col].v[comp] < z_Palettes[col].v[comp]) {
			fadepal[col].v[comp]++;
		}
	);
}

void z_palette_black_out(void)
{
	Palette4 fadepal;
	memcpy(&fadepal, &z_Palettes, sizeof(Palette4));

	fade_loop(fadepal,
		if(fadepal[col].v[comp] > fadepal[0].min()) {
			fadepal[col].v[comp]--;
		}
	);
}

void z_palette_white(void)
{
	for(int col = 0; col < COLOR_COUNT; col++) {
		z_palette_show_single(col, RGB4::max(), RGB4::max(), RGB4::max());
	}
}

void z_palette_white_in(void)
{
	Palette4 fadepal;
	memset(&fadepal, fadepal[0].max(), sizeof(Palette4));

	fade_loop(fadepal,
		if(fadepal[col].v[comp] > z_Palettes[col].v[comp]) {
			fadepal[col].v[comp]--;
		}
	);
}

void z_palette_white_out(void)
{
	Palette4 fadepal;
	memcpy(&fadepal, &z_Palettes, sizeof(Palette4));

	fade_loop(fadepal,
		if(fadepal[col].v[comp] < fadepal[0].max()) {
			fadepal[col].v[comp]++;
		}
	);
}

void z_palette_show(void)
{
	for(int i = 0; i < COLOR_COUNT; i++) {
		z_palette_show_single_col(i, z_Palettes[i]);
	}
}
/// -------------

/// Points
/// ------
#define VRAM_SBYTE(plane, offset) \
	*reinterpret_cast<sdots8_t *>(MK_FP(SEG_PLANE_##plane, offset))

void z_grcg_pset(int x, int y, int col)
{
	grcg_setcolor_rmw(col);
	VRAM_SBYTE(B, ((y * ROW_SIZE) + (x >> 3))) = (0x80 >> (x & 7));
	grcg_off_func();
}

int z_col_at(int x, int y)
{
	int ret;
	int vram_offset = ((y * ROW_SIZE) + (x >> 3));
	sdots16_t mask = (0x80 >> (x & 7));

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
extern dots16_t graph_r_pattern;

void graph_r_hline(int left, int right, int y, int col)
{
	int x;
	int full_bytes_to_put;
	int order_tmp;
	dots8_t left_pixels;
	dots8_t right_pixels;
	dots8_t *vram_row;

	fix_order(left, right);
	clip_x(left, right);

	graph_r_last_line_end.x = right;
	graph_r_last_line_end.y = y;

	vram_row = (dots8_t *)(MK_FP(GRAM_400, (y * ROW_SIZE) + (left / 8)));
	full_bytes_to_put = (right / 8) - (left / 8);
	left_pixels = 0xFF >> (left & 7);
	right_pixels = 0xFF << (7 - (right & 7));

	if(!graph_r_restore_from_1) {
		grcg_setcolor_rmw(col);
	}
	if(graph_r_restore_from_1) {
		egc_copy_rect_1_to_0(left, y, RES_X - left, 1);
	} else {
		if(full_bytes_to_put == 0) {
			vram_row[0] = (left_pixels & right_pixels);
		} else {
			vram_row[0] = left_pixels;
			for(x = 1; x < full_bytes_to_put; x++) {
				vram_row[x] = 0xFF;
			}
			vram_row[full_bytes_to_put] = right_pixels;
		}
	}
	if(!graph_r_restore_from_1) {
		grcg_off_func();
	}
}

void graph_r_vline(int x, int top, int bottom, int col)
{
	int y;
	int order_tmp;
	dots16_t pattern;
	int vram_row_offset;

	fix_order(top, bottom);
	clip_y(top, bottom);

	graph_r_last_line_end.x = x;
	graph_r_last_line_end.y = bottom;

	if(graph_r_restore_from_1) {
		egc_copy_rect_1_to_0(x, top, sizeof(pattern) * 8, bottom - top);
		return;
	}
	vram_row_offset = vram_offset_shift(x, top);
	pattern = graph_r_pattern >> (x & 7);
	pattern |= graph_r_pattern << (16 - (x & 7));

	grcg_setcolor_rmw(col);
	for(y = top; y <= bottom; y++) {
		VRAM_PUT(B, vram_row_offset, pattern, 16);
		vram_row_offset += ROW_SIZE;
	}
	grcg_off_func();
}

void graph_r_line_from_1(int left, int top, int right, int bottom)
{
	graph_r_restore_from_1 = true;
	graph_r_line(left, top, right, bottom, 7);
	graph_r_restore_from_1 = false;
}

void graph_r_line_patterned(
	int left, int top, int right, int bottom, int col, dots16_t pattern
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
	dots16_t pixels;

	planar32_t page1;

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
	graph_accesspage_func(1);	VRAM_SNAP_PLANAR(page1, vram_offset, 32); \
	graph_accesspage_func(0);	VRAM_PUT_PLANAR(vram_offset, page1, 32);

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
		grcg_setcolor_rmw(col);
	}
	if(w > h) {
		plot_loop(x_cur, w, 1, y_cur, h, y_direction);
	} else {
		plot_loop(y_cur, h, y_direction, x_cur, w, 1);
	}
restore_last:
	vram_offset = vram_offset_shift(x_cur, y_cur) - 1;
	restore_at(vram_offset);
end:
	if(!graph_r_restore_from_1) {
		grcg_off_func();
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
	dots8_t left_pixels;
	dots8_t right_pixels;
	dots8_t *vram_row;

	fix_order(left, right);
	fix_order(top, bottom);
	clip_x(left, right);
	clip_y(top, bottom);

	grcg_setcolor_rmw(col);
	vram_row = (dots8_t *)(MK_FP(GRAM_400, (top * ROW_SIZE) + (left >> 3)));
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
	grcg_off_func();
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
	register int x = left;
	uint16_t codepoint;
	dots16_t glyph_row;
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
	dots16_t glyph[GLYPH_H];
	register dots16_t glyph_row_tmp;

	if(clear_bg) {
		w = text_extent_fx(fx, str);
		if(underline) {
			z_grcg_boxfill(x, top, (x + w - 1), (top + GLYPH_H + 1), 0);
			graph_r_hline(x, (x + w - 1), (top + GLYPH_H + 1), 7);
		} else {
			z_grcg_boxfill(x, top, (x + w - 1), (top + GLYPH_H - 1), 0);
		}
	} else if(underline) {
		w = text_extent_fx(fx, str);
		graph_r_hline(x, (x + w - 1), (top + GLYPH_H + 1), 7);
	}

	grcg_setcolor_rmw(fx);
	OUTB(0x68, 0xB); // CG ROM dot access

	while(str[0]) {
		set_vram_ptr(vram, first_bit, x, top);
		get_glyph(glyph, codepoint, fullwidth, str, x, line);

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
		advance_left(x, fullwidth, spacing);
	}

	OUTB(0x68, 0xA); // CG ROM code access
	grcg_off_func();
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
	Palette4 fadepal;
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
			fadepal[i].c.r = z_Palettes[i].c.r;
			fadepal[i].c.g = z_Palettes[i].c.g;
			fadepal[i].c.b = z_Palettes[i].c.b;
		}
	}
	for(i = 0; i < fadepal.range(); i++) {
		z_vsync_wait();
		for(col = 0; col < COLOR_COUNT; col++) {
			for(comp = 0; comp < sizeof(RGB4); comp++) {
				if(fadepal[col].v[comp] != z_Palettes[col].v[comp]) {
					fadepal.colors[col].v[comp] +=
						(fadepal[col].v[comp] < z_Palettes[col].v[comp])
						?  1
						: -1;
				}
			}
			z_palette_show_single_col(col, fadepal[col]);
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
			z_palette_set_show(i, respal->r, respal->g, respal->b);
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
			respal->g = z_Palettes[i].c.g;
			respal->r = z_Palettes[i].c.r;
			respal->b = z_Palettes[i].c.b;
			respal++;
		}
		return 0;
	}
	return 1;
}

}
