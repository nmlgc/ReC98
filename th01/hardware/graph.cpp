#include <dos.h>
#include <mem.h>
#include <mbctype.h>
#include <mbstring.h>
#include "platform/x86real/pc98/page.hpp"
#include "th01/v_colors.hpp"
#include "th01/math/clamp.hpp"
#include "th01/hardware/egc.h"
#include "th01/hardware/grcg.hpp"
#include "th01/hardware/vsync.hpp"
#include "th01/hardware/graph.h"
#include "th01/hardware/palette.h"

// Never read from, so it's supposedly only there for debugging purposes?
static screen_point_t graph_r_last_line_end;

/// VRAM plane "structures"
/// -----------------------
#define Planes_declare(var) \
	dots8_t far *var##_B = reinterpret_cast<dots8_t __seg *>(SEG_PLANE_B); \
	dots8_t far *var##_R = reinterpret_cast<dots8_t __seg *>(SEG_PLANE_R); \
	dots8_t far *var##_G = reinterpret_cast<dots8_t __seg *>(SEG_PLANE_G); \
	dots8_t far *var##_E = reinterpret_cast<dots8_t __seg *>(SEG_PLANE_E);

#define Planes_next_row(var) \
	var##_B += ROW_SIZE; \
	var##_R += ROW_SIZE; \
	var##_G += ROW_SIZE; \
	var##_E += ROW_SIZE;

#define Planes_offset(var, x, y) \
	var##_B += vram_offset_divmul(x, y); \
	var##_R += vram_offset_divmul(x, y); \
	var##_G += vram_offset_divmul(x, y); \
	var##_E += vram_offset_divmul(x, y);

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

#define fix_order(tmp, low, high) \
	if(low > high) { \
		tmp = low; \
		low = high; \
		high = tmp; \
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

inline void graph_access_and_show_0() {
	page_access(0);
	page_show(0);
}

inline void cgrom_code_and_grcg_off() {
	outportb(0x68, 0xA); // CG ROM code access
	grcg_off();
}

inline void z_graph_400line() {
	REGS regs;

	z_graph_hide();

	// 640x400
	regs.h.ah = 0x42;
	regs.h.ch = 0xC0;
	int86(0x18, &regs, &regs);

	// 16-color, analog mode
	outportb(0x6A, 1);
}

inline void z_graph_access_and_show_0() {
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

/// Hardware
/// --------

void z_palette_show_single(vc2 col, svc_comp2 r, svc_comp2 g, svc_comp2 b)
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

void grcg_setcolor_rmw(vc2 col)
{
	grcg_setcolor(0xC0, col);
}

void grcg_setcolor_tcr(vc2 col)
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

Palette4 z_Palettes = {
	// These match the Z_ATRB_* bits, interestingly?
	0x0, 0x0, 0x0, //  0: Black
	0x0, 0x0, 0xF, //  1: Blue
	0x0, 0xF, 0x0, //  2: Green
	0x0, 0xF, 0xF, //  3: Cyan
	0xF, 0x0, 0x0, //  4: Red
	0xF, 0x0, 0xF, //  5: Magenta
	0xF, 0xF, 0x0, //  6: Yellow
	0xF, 0xF, 0xF, //  7: White

	0x8, 0x8, 0x8, //  8: Gray
	0x0, 0x0, 0xA, //  9: Dark blue
	0x0, 0xA, 0x0, // 10: Dark green
	0x0, 0xA, 0xA, // 11: Dark cyan
	0xA, 0x0, 0x0, // 12: Dark red
	0xA, 0x0, 0xA, // 13: Purple
	0xA, 0xA, 0x0, // 14: Gold
	0xC, 0xC, 0xC, // 15: Silver
};

void z_palette_set_all_show(const Palette4& pal)
{
	for(int i = 0; i < COLOR_COUNT; i++) {
		z_palette_set_show(i, pal[i].c.r, pal[i].c.g, pal[i].c.b);
	}
}

void z_palette_set_show(vc2 col, svc_comp2 r, svc_comp2 g, svc_comp2 b)
{
	r = clamp_min(clamp_max(r, RGB4::max()), RGB4::min());
	g = clamp_min(clamp_max(g, RGB4::max()), RGB4::min());
	b = clamp_min(clamp_max(b, RGB4::max()), RGB4::min());

	z_Palettes[col].c.r = r;
	z_Palettes[col].c.g = g;
	z_Palettes[col].c.b = b;
	z_palette_show_single(col, r, g, b);
}
/// -------

/// Whole-page functions
/// --------------------
void z_graph_clear()
{
	dots8_t far *plane = reinterpret_cast<dots8_t __seg *>(SEG_PLANE_B);

	grcg_setcolor_rmw(0);
	memset(plane, 0xFF, PLANE_SIZE);
	grcg_off_func();
}

void z_graph_clear_0(void)
{
	// Yes, page 2, twice. Which effectively is the same as page 0... at least
	// according to any real hardware and emulator tests I could come up with.
	page_access(2);	z_graph_clear();
	page_access(2);	z_graph_clear();
}

void z_graph_clear_col(svc_t col)
{
	dots8_t far *plane = reinterpret_cast<dots8_t __seg *>(SEG_PLANE_B);

	grcg_setcolor_rmw(col);
	memset(plane, 0xFF, PLANE_SIZE);
	grcg_off_func();
}

void graph_copy_page_to_other(page_t src)
{
	PlanarRow_declare(tmp);
	Planes_declare(p);
	page_t dst = (src ^ 1);

	for(screen_y_t y = 0; y < RES_Y; y++) {
		page_access(src);	PlanarRow_blit(tmp, p, ROW_SIZE);
		page_access(dst);	PlanarRow_blit(p, tmp, ROW_SIZE);
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
		for(svc2 col = 0; col < COLOR_COUNT; col++) { \
			for(int comp = 0; comp < COMPONENT_COUNT; comp++) { \
				per_comp; \
			} \
			z_palette_show_single_col(col, pal[col]); \
		} \
		delay(FADE_DELAY); \
	}

void z_palette_black(void)
{
	for(svc2 col = 0; col < COLOR_COUNT; col++) {
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
	for(svc2 col = 0; col < COLOR_COUNT; col++) {
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

void z_grcg_pset(screen_x_t x, vram_y_t y, vc2 col)
{
	grcg_setcolor_rmw(col);
	VRAM_SBYTE(B, vram_offset_mulshift(x, y)) = (0x80 >> (x & BYTE_MASK));
	grcg_off_func();
}

int z_graph_readdot(screen_x_t x, vram_y_t y)
{
	int ret;
	vram_offset_t vram_offset = vram_offset_mulshift(x, y);
	sdots16_t mask = (0x80 >> (x & BYTE_MASK));

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

#undef test
}
/// ------

/// Restorable line drawing
/// -----------------------

// `true` copies the pixels to be drawn from the same position on page 1, thus
// restoring them with the background image. `false` (the default) draws them
// regularly in the given [col].
static bool graph_r_unput = false;

// Not used for purely horizontal lines.
static dots16_t graph_r_pattern = 0x80; // 1 pixel (*       )

void graph_r_hline(screen_x_t left, screen_x_t right, vram_y_t y, vc2 col)
{
	vram_byte_amount_t x;
	vram_byte_amount_t full_bytes_to_put;
	int order_tmp;
	dots8_t left_pixels;
	dots8_t right_pixels;
	dots8_t *vram_row;

	fix_order(order_tmp, left, right);
	clip_x(left, right);

	graph_r_last_line_end.x = right;
	graph_r_last_line_end.y = y;

	vram_row = (dots8_t *)(MK_FP(SEG_PLANE_B, vram_offset_muldiv(left, y)));
	full_bytes_to_put = (right / BYTE_DOTS) - (left / BYTE_DOTS);
	left_pixels = 0xFF >> (left & BYTE_MASK);
	right_pixels = 0xFF << (BYTE_MASK - (right & BYTE_MASK));

	if(!graph_r_unput) {
		grcg_setcolor_rmw(col);
	}
	if(graph_r_unput) {
		egc_copy_rect_1_to_0_16(left, y, RES_X - left, 1);
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
	if(!graph_r_unput) {
		grcg_off_func();
	}
}

void graph_r_vline(screen_x_t x, vram_y_t top, vram_y_t bottom, vc2 col)
{
	vram_y_t y;
	int order_tmp;
	dots16_t pattern;
	vram_offset_t vram_row_offset;

	fix_order(order_tmp, top, bottom);
	clip_y(top, bottom);

	graph_r_last_line_end.x = x;
	graph_r_last_line_end.y = bottom;

	if(graph_r_unput) {
		egc_copy_rect_1_to_0_16(
			x, top, (sizeof(pattern) * BYTE_DOTS), (bottom - top)
		);
		return;
	}
	vram_row_offset = vram_offset_shift(x, top);
	pattern = graph_r_pattern >> (x & BYTE_MASK);
	pattern |= graph_r_pattern << (16 - (x & BYTE_MASK));

	grcg_setcolor_rmw(col);
	for(y = top; y <= bottom; y++) {
		grcg_put(vram_row_offset, pattern, 16);
		vram_row_offset += ROW_SIZE;
	}
	grcg_off_func();
}

void graph_r_line_unput(
	screen_x_t left, vram_y_t top, screen_x_t right, vram_y_t bottom
)
{
	graph_r_unput = true;
	graph_r_line(left, top, right, bottom, V_WHITE);
	graph_r_unput = false;
}

void graph_r_line_patterned(
	screen_x_t left,
	vram_y_t top,
	screen_x_t right,
	vram_y_t bottom,
	vc2 col,
	dots16_t pattern
)
{
	graph_r_pattern = pattern;
	graph_r_line(left, top, right, bottom, col);
	graph_r_pattern = 0x80;
}

void graph_r_line(
	screen_x_t left,
	vram_y_t top,
	screen_x_t right,
	vram_y_t bottom,
	vc2 col
)
{
	register vram_offset_t vram_offset;
	int i;
	screen_x_t x_cur;
	vram_y_t y_cur;
	pixel_t w, h;
	int error;
	int y_direction;
	int order_tmp;
	vram_x_t x_vram;
	vram_y_t y_vram;
	dots16_t pixels;

#define lerp(m, x) static_cast<int>(m * static_cast<float>(x))

#define clip_lerp_min(low, high, lerp_point, slope_dividend, minimum) \
	if(low < minimum) { \
		if(high < minimum) { \
			return; \
		} \
		lerp_point += lerp((slope_dividend / (high - low)), (minimum - low)); \
		low = minimum; \
	}
#define clip_lerp_max(low, high, lerp_point, slope_dividend, maximum) \
	if(high > maximum) { \
		if(low > maximum) { \
			return; \
		} \
		lerp_point -= lerp((slope_dividend / (high - low)), (high - maximum)); \
		high = maximum; \
	}

#define unput32_at(vram_offset) { \
	Planar<dots32_t> page1; \
	page_access(1);	VRAM_SNAP_PLANAR(page1, vram_offset, 32); \
	page_access(0);	VRAM_PUT_PLANAR(vram_offset, page1, 32); \
}

#define plot_loop(\
	step_var, step_len, step_increment, \
	plotted_var, plotted_len, plotted_increment \
) \
	error = (step_len >> 1); \
	for(i = 0; i <= step_len; i++) { \
		/* Advanced past the VRAM cursor? */ \
		if((x_cur >> 3) != x_vram || (y_vram != y_cur)) { \
			vram_offset = (y_vram * ROW_SIZE) + x_vram; \
			if(!graph_r_unput) { \
				grcg_put(vram_offset, pixels, 16); \
				pixels = 0; \
			} else { \
				/* ZUN bug: Getting here with a [vram_offset] of 0x0000 will \
				 * cause a 4-byte write starting at 0xFFFF. On the 80286 and \
				 * later CPUs, offset overflows within an instruction are \
				 * illegal even in Real Mode, and will raise a General \
				 * Protection Fault. \
				 * As of May 2022, Anex86 is the only PC-98 emulator to \
				 * correctly replicate this behavior of real hardware, \
				 * though. */ \
				vram_offset--; \
				unput32_at(vram_offset); \
			} \
			y_vram = y_cur; \
			x_vram = (x_cur >> BYTE_BITS); \
		} \
		pixels |= (graph_r_pattern >> (x_cur & BYTE_MASK)); \
		pixels |= (graph_r_pattern << (16 - (x_cur & BYTE_MASK))); \
		error -= plotted_len; \
		step_var += step_increment; \
		if(error < 0) { \
			error += step_len; \
			plotted_var += plotted_increment; \
		} \
	} \
	if(graph_r_unput) { \
		goto restore_last; \
	} \
	goto end;

	if(!graph_r_unput && (left == right)) {
		graph_r_vline(left, top, bottom, col);
		return;
	}
	if(!graph_r_unput && (top == bottom)) {
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

	clip_lerp_min(left, right, top, (bottom - top), 0);
	clip_lerp_max(left, right, bottom, (bottom - top), (RES_X - 1));
	clip_lerp_min(top, bottom, left, (right - left), 0);
	clip_lerp_max(top, bottom, right, (right - left), (RES_Y - 1));

	// This division is safe at this point.
	#define slope_y ((right - left) / (bottom - top))

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
	x_vram = (x_cur >> BYTE_BITS);
	y_vram = y_cur;

	if(!graph_r_unput) {
		grcg_setcolor_rmw(col);
	}
	if(w > h) {
		plot_loop(x_cur, w, 1, y_cur, h, y_direction);
	} else {
		plot_loop(y_cur, h, y_direction, x_cur, w, 1);
	}
restore_last:
	// ZUN bug: Off-by-one error, as [x_cur] and [y_cur] are one past the
	// intended right / bottom coordinates after the plot_loop. Should have
	// calculated [vram_offset] from [x_vram] and [y_vram] just like the
	// plot_loop, since those values are directly updated for the next VRAM
	// byte after a blit, and would thus be correct here as well.
	//
	// This way, the offset could potentially end up at [right = 640] or
	// [bottom = -1]. Both together are not only the same as (0, 0) and thus
	// wrap from the right edge of VRAM back to the left one, but also trigger
	// the same General Protection Fault seen in the plot_loop itself.
	vram_offset = vram_offset_shift(x_cur, y_cur) - 1;
	unput32_at(vram_offset);
end:
	if(!graph_r_unput) {
		grcg_off_func();
	}

#undef plot_loop
#undef unput32_at
#undef clip_lerp_min
#undef clip_lerp_max
#undef slope_x
}

void graph_r_lineloop_put(const screen_point_t point[], int count, vc_t col)
{
	int i = 0;
	while((count - 1) > i) {
		graph_r_line(
			point[i].x, point[i].y, point[i + 1].x, point[i + 1].y, col
		);
		i++;
	}
	graph_r_line(point[i].x, point[i].y, point[0].x, point[0].y, col);
}

void graph_r_lineloop_unput(const screen_point_t point[], int count)
{
	int i = 0;
	while((count - 1) > i) {
		graph_r_line_unput(
			point[i].x, point[i].y, point[i + 1].x, point[i + 1].y
		);
		i++;
	}
	graph_r_line_unput(point[i].x, point[i].y, point[0].x, point[0].y);
}

/// -----------------------

void z_grcg_boxfill(
	screen_x_t left,
	vram_y_t top,
	screen_x_t right,
	vram_y_t bottom,
	vc2 col
)
{
	vram_byte_amount_t x;
	vram_y_t y;
	vram_byte_amount_t full_bytes_to_put;
	int order_tmp;
	dots8_t left_pixels;
	dots8_t right_pixels;
	dots8_t *vram_row;

	fix_order(order_tmp, left, right);
	fix_order(order_tmp, top, bottom);
	clip_x(left, right);
	clip_y(top, bottom);

	grcg_setcolor_rmw(col);
	vram_row = (dots8_t *)(MK_FP(SEG_PLANE_B, vram_offset_mulshift(left, top)));
	for(y = top; y <= bottom; y++) {
		full_bytes_to_put = ((right >> BYTE_BITS) - (left >> BYTE_BITS));
		left_pixels = 0xFF >> (left & BYTE_MASK);
		right_pixels = 0xFF << (BYTE_MASK - (right & BYTE_MASK));

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

void graph_r_box(
	screen_x_t left,
	vram_y_t top,
	screen_x_t right,
	vram_y_t bottom,
	vc2 col
)
{
	graph_r_hline(left, right, top, col);
	graph_r_vline(left, top, bottom, col);
	graph_r_vline(right, top, bottom, col);
	graph_r_hline(left, right, bottom, col);
}

void graph_move_byterect_interpage(
	screen_x_t src_left,
	vram_y_t src_top,
	screen_x_t src_right,
	vram_y_t src_bottom,
	screen_x_t dst_left,
	vram_y_t dst_top,
	page_t src
)
{
	pixel_t w = (src_right - src_left) / BYTE_DOTS;
	pixel_t h = (src_bottom - src_top);
	Planes_declare(src);
	Planes_declare(dst);
	pixel_t row;
	PlanarRow_declare(tmp);

	Planes_offset(src, src_left, src_top);
	Planes_offset(dst, dst_left, dst_top);

	page_t dst = (src ^ 1);
	for(row = 0; row < h; row++) {
		page_access(src);	PlanarRow_blit(tmp, src, w);
		page_access(dst);	PlanarRow_blit(dst, tmp, w);
		Planes_next_row(src);
		Planes_next_row(dst);
	}
}

void z_palette_fade_from(
	svc_comp_t from_r, svc_comp_t from_g, svc_comp_t from_b,
	vc2 keep[COLOR_COUNT],
	unsigned int step_ms
)
{
	Palette4 fadepal;
	int i;
	svc2 col;
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
			for(comp = 0; comp < COMPONENT_COUNT; comp++) {
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
