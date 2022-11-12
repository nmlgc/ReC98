// High-level overview of the differences between the three games that can't be
// easily abstracted away:
//
// 1) TH03 and TH04 allocate dedicated memory for backing up the text box area
//    in VRAM ([box_bg]), TH05 uses the bgimage system instead.

#include <stddef.h>
#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "shiftjis.hpp"
#include "master.hpp"
#include "th02/v_colors.hpp"
extern "C" {
#include "th02/hardware/frmdelay.h"
#if (GAME == 5)
	#include "th01/hardware/egc.h"
	#include "th04/hardware/bgimage.hpp"
	#include "th04/gaiji/gaiji.h"
	#include "th05/hardware/input.h"
	#include "th05/formats/pi.hpp"
#elif (GAME == 4)
	#include "th03/formats/pi.hpp"
	#include "th04/hardware/input.h"
#else
	#include "th03/hardware/input.h"
	#include "th03/formats/pi.hpp"
#endif
}
#include "th03/math/str_val.hpp"
#include "th03/cutscene/cutscene.hpp"

// Constants
// ---------

static const pixel_t PIC_W = PI_QUARTER_W;
static const pixel_t PIC_H = PI_QUARTER_H;

static const vram_byte_amount_t PIC_VRAM_W = (PIC_W / BYTE_DOTS);

static const int PIC_SLOT = 0;

// Note that this does not correspond to the tiled area painted into TH05's
// EDBK?.PI images.
static const screen_x_t BOX_LEFT = 80;
static const screen_y_t BOX_TOP = 320;
static const pixel_t BOX_W = 480;
static const pixel_t BOX_H = (GLYPH_H * 4);

static const vram_byte_amount_t BOX_VRAM_W = (BOX_W / BYTE_DOTS);
static const screen_x_t BOX_RIGHT = (BOX_LEFT + BOX_W);
static const screen_y_t BOX_BOTTOM = (BOX_TOP + BOX_H);

static const shiftjis_ank_amount_t NAME_LEN = 6;
static const shiftjis_kanji_amount_t NAME_KANJI_LEN = (
	NAME_LEN / sizeof(shiftjis_kanji_t)
);

// Adding a fullwidth colon after the name
static const pixel_t NAME_W = ((NAME_LEN * GLYPH_HALF_W) + GLYPH_FULL_W);
// ---------

// State
// -----

#if (GAME >= 4)
	// Statically allocated. MODDERS: TH03's dynamic allocation was better than
	// hardcoding a maximum size...
	extern unsigned char script[8192];

	extern unsigned char near *script_p;
#else
	// Dynamically allocated.
	extern unsigned char far *script;

	#define script_p script
#endif

extern Planar<dots16_t>* box_bg;

// Skips any delays during the cutscene if `true`.
extern bool fast_forward;

// [y] is always aligned to GLYPH_H pixels.
extern screen_point_t cursor;

extern int text_interval;
extern uint8_t text_col;
extern uint8_t text_fx; // TH04 and TH05 directly set [graph_putsa_fx_func].
extern int script_number_param_default;
// -----

#if (GAME == 5)
	// String-to-color map
	// -------------------
	// Used to automatically change the text color whenever a specific
	// Shift-JIS code point is encountered.

	static const int COLMAP_COUNT = 8;

	typedef struct {
		uint4_t values[COLMAP_COUNT];

		// Might have been originally meant for a complete character name?
		shiftjis_kanji_t keys[COLMAP_COUNT][NAME_KANJI_LEN];
	} colmap_t;

	extern colmap_t colmap;
	extern unsigned char colmap_count;
	// -------------------
#endif

// Function ordering fails
// -----------------------

#if (GAME == 5)
	// Waits the given amount of frames (0 = forever) for the OK, Shot, or
	// Cancel button to be pressed, while showing the ⏎ Return key animation
	// in a blocking way.
	void pascal near box_wait_animate(int frames_to_wait = 0);
#else
	#define box_wait_animate(frames_to_wait) { \
		input_wait_for_change(frames_to_wait); \
	}

	void near box_bg_allocate_and_snap(void);
	void near box_bg_free(void);
#endif
#if (GAME >= 4)
	// Crossfades the text box area from VRAM page 1 to VRAM page 0, spending
	// [text_interval] frames on each step.
	void near box_1_to_0_animate(void);
#endif
// -----------------------

// ZUN quirk: The cutscene system features both
// 1) a top-level input sensing mechanism (for updating the fast-forward flag),
//    and
// 2) nested, blocking input loops (during all the interruptable wait commands)
//    which are skipped based on the fast-forward flag.
// With this combination, the accurate detection of held keys matters: Since
// this function is only called once on every iteration of the loop before
// evaluating a command, a momentary key release scancode from 1) can cause 2)
// to be entered even if the fast-forward key is still being held. Only TH03's
// and TH05's input functions defend against this possibility – at the cost of
// 614.4 µs for every call to them. TH04's cutscene system does suffer from the
// detection issue, but runs significantly faster in exchange, as it's not
// slowed down on every iteration of the script interpreter loop, i.e., between
// every script command or 2-byte text pair.
inline void cutscene_input_sense(void) {
	#if (GAME == 5)
		input_reset_sense_held();
	#elif (GAME == 4)
		input_reset_sense();
	#elif (GAME == 3)
		input_mode_interface();
	#endif
}

bool16 pascal near cutscene_script_load(const char* fn)
{
	cutscene_script_free();

	if(!file_ropen(fn)) {
		return true;
	}
	size_t size = file_size();
	#if (GAME >= 4)
		// PORTERS: Required for TH03 on flat memory models as well.
		// ZUN bug: Missing an error check if [size] >= sizeof(script);
		script_p = static_cast<unsigned char near *>(script);
	#else
		script = reinterpret_cast<unsigned char far *>(hmem_allocbyte(size));
	#endif
	file_read(script_p, size);
	file_close();
	return false;
}

#if (GAME <= 4)
	void near cutscene_script_free(void)
	{
		#if (GAME == 3)
			if(script) {
				HMem<unsigned char>::free(script);
				script = nullptr;
			}
		#endif
	}
#endif

// ZUN bloat: Turn into a single global inline function.
#define egc_start_copy	near egc_start_copy
#include "th01/hardware/egcstart.cpp"
#undef egc_start_copy

#if (GAME == 5)
	#define pic_copy_to_other(left, top) { \
		egc_copy_rect_1_to_0_16(left, top, PIC_W, PIC_H); \
	}

	void pascal near pic_put_both_masked(
		screen_x_t left, vram_y_t top, int quarter, int mask_id
	)
	{
		graph_accesspage(1);
		pi_put_quarter_masked_8(left, top, PIC_SLOT, quarter, mask_id);
		pic_copy_to_other(left, top);
	}
#else
	void pascal near pic_copy_to_other(screen_x_t left, vram_y_t top)
	{
		vram_offset_t vo = vram_offset_shift(left, top);
		pixel_t y;
		vram_byte_amount_t vram_x;

		egc_start_copy();

		// Faster than TH01's very slow end_pic_show() version, but still not
		// as optimal as you can get within the EGC's limited 16-dot tile
		// register.
		y = 0;
		while(y < PIC_H) {
			vram_x = 0;
			while(vram_x < PIC_VRAM_W) {
				egc_temp_t tmp;

				graph_accesspage(0);	tmp = egc_chunk(vo);
				graph_accesspage(1);	egc_chunk(vo) = tmp;

				vram_x += EGC_REGISTER_SIZE;
				vo += EGC_REGISTER_SIZE;
			}
			y++;
			vo += (ROW_SIZE - PIC_VRAM_W);
		}
		egc_off();

		// ZUN bloat: All blitting operations in this module access the
		// intended page before they blit. That's why preliminary state
		// changes like this one are completely redundant, thankfully.
		graph_accesspage(0);
	}

	void pascal near pic_put_both_masked(
		screen_x_t left, vram_y_t top, int quarter, int mask_id
	)
	{
		enum {
			TEMP_ROW = RES_Y,
		};

		vram_word_amount_t vram_word;
		vram_offset_t vo_temp;
		pi_buffer_p_t row_p;

		pi_buffer_p_init_quarter(row_p, PIC_SLOT, quarter);

		graph_showpage(1);
		vram_offset_t vo = vram_offset_shift(left, top);
		graph_accesspage(0);
		for(pixel_t y = 0; y < PIC_H; y++) {
			// This might actually be faster than clearing the masked pixels
			// using the GRCG and doing an unaccelerated 4-plane VRAM OR.
			graph_pack_put_8_noclip(0, TEMP_ROW, row_p, PIC_W);
			egc_start_copy();
			egc_setup_copy_masked(PI_MASKS[mask_id][y & (PI_MASK_COUNT - 1)]);
			vo_temp = vram_offset_shift(0, TEMP_ROW);
			vram_word = 0;
			while(vram_word < (PIC_W / EGC_REGISTER_DOTS)) {
				egc_chunk(vo) = egc_chunk(vo_temp);
				vram_word++;
				vo += EGC_REGISTER_SIZE;
				vo_temp += EGC_REGISTER_SIZE;
			}
			egc_off();

			vo += (ROW_SIZE - PIC_VRAM_W);
			pi_buffer_p_offset(row_p, PI_W, 0);
			pi_buffer_p_normalize(row_p);
		}
		graph_showpage(0);
		pic_copy_to_other(left, top);
	}

	#define box_bg_snap_func(p, vo) { \
		(&box_bg->B)[p++] = VRAM_CHUNK(B, vo, 16); \
		(&box_bg->B)[p++] = VRAM_CHUNK(R, vo, 16); \
		(&box_bg->B)[p++] = VRAM_CHUNK(G, vo, 16); \
		(&box_bg->B)[p++] = VRAM_CHUNK(E, vo, 16); \
	}

	#define box_bg_put_func(p, vo) { \
		VRAM_CHUNK(B, vo, 16) = (&box_bg->B)[p++]; \
		VRAM_CHUNK(R, vo, 16) = (&box_bg->B)[p++]; \
		VRAM_CHUNK(G, vo, 16) = (&box_bg->B)[p++]; \
		VRAM_CHUNK(E, vo, 16) = (&box_bg->B)[p++]; \
	}

	#define box_bg_loop(func) /* No braces due to local variable layout */ \
		size_t p; \
		vram_y_t src_y; \
		screen_x_t src_x; \
		pixel_t dst_y; \
		vram_byte_amount_t dst_byte; \
		vram_offset_t vo; \
		\
		p = 0; \
		src_y = BOX_TOP; \
		dst_y = 0; \
		while(dst_y < BOX_H) { \
			src_x = BOX_LEFT; \
			dst_byte = 0; \
			while(dst_byte < BOX_VRAM_W) { \
				vo = vram_offset_shift(src_x, src_y); \
				func(p, vo); \
				dst_byte += static_cast<vram_byte_amount_t>(sizeof(dots16_t)); \
				src_x += 16; \
			} \
			dst_y++; \
			src_y++; \
		}

	void near box_bg_allocate_and_snap(void)
	{
		box_bg_free();
		graph_accesspage(0);
		box_bg = HMem< Planar<dots16_t> >::alloc(
			((BOX_VRAM_W * BOX_H) / sizeof(dots16_t))
		);
		box_bg_loop(box_bg_snap_func);
	}

	void near box_bg_free(void)
	{
		if(box_bg) {
			HMem< Planar<dots16_t> >::free(box_bg);
			box_bg = nullptr;
		}
	}

	void near box_bg_put(void)
	{
		box_bg_loop(box_bg_put_func);
	}
#endif

void pascal near script_number_param_read_first(int& ret)
{
	str_consume_up_to_3_digits(&ret, script_p, script_number_param_default);
}

void pascal near script_number_param_read_second(int& ret)
{
	if(*script_p == ',') {
		script_p++;
		script_number_param_read_first(ret);
	} else {
		ret = script_number_param_default;
	}
}

void near cursor_advance_and_animate(void)
{
	cursor.x += GLYPH_FULL_W;
	if(cursor.x >= BOX_RIGHT) {
		cursor.y += GLYPH_H;
		cursor.x = (BOX_LEFT + NAME_W);

		if(cursor.y >= BOX_BOTTOM) {
			#if (GAME >= 4)
				box_1_to_0_animate();
			#endif

			// ZUN quirk: Since [cursor.y] is >= BOX_BOTTOM here, the TH05
			// Return key animation will be displayed at the right edge of the
			// "5th" line, below BOX_BOTTOM.
			if(!fast_forward) {
				box_wait_animate(0);
			}

			// Unconditionally moving the cursor into the name area? This is
			// not what a script author would expect, especially with automatic
			// line breaks doing the opposite. If you are forced to write your
			// script in a way that anticipates such a cursor move, you might
			// as well explicitly add the necessary text box change commands
			// manually.
			cursor.x = BOX_LEFT;
			cursor.y = BOX_TOP;

			#if (GAME != 5)
				graph_accesspage(1);	box_bg_put();
				graph_accesspage(0);	box_bg_put();
			#endif
		}
	}
}

#if (GAME >= 4)
	typedef enum {
		BOX_MASK_0,
		BOX_MASK_1,
		BOX_MASK_2,
		BOX_MASK_3,
		BOX_MASK_COPY,
		BOX_MASK_COUNT,

		_box_mask_t_FORCE_UINT16 = 0xFFFF
	} box_mask_t;

	// Copies the text box area from VRAM page 1 to VRAM page 0, applying the
	// given [mask]. Assumes that the EGC is active, and initialized for a copy.
	void pascal near box_1_to_0_masked(box_mask_t mask)
	{
		extern const dot_rect_t(16, 4) BOX_MASKS[BOX_MASK_COUNT];
		egc_temp_t tmp;

		for(screen_y_t y = BOX_TOP; y < BOX_BOTTOM; y++) {
			egc_setup_copy_masked(BOX_MASKS[mask][y & 3]);

			vram_offset_t vram_offset = vram_offset_shift(BOX_LEFT, y);
			pixel_t x = 0;
			while(x < BOX_W) {
				graph_accesspage(1);	tmp = egc_chunk(vram_offset);
				graph_accesspage(0);	egc_chunk(vram_offset) = tmp;
				x += EGC_REGISTER_DOTS;
				vram_offset += EGC_REGISTER_SIZE;
			}
		}
	}

	void near box_1_to_0_animate(void)
	{
		// ZUN bloat: box_1_to_0_masked() switches the accessed page anyway.
		#if (GAME == 5)
			graph_accesspage(0);
		#endif

		egc_start_copy();
		if(!fast_forward) {
			for(int i = BOX_MASK_0; i < BOX_MASK_COPY; i++) {
				box_1_to_0_masked(static_cast<box_mask_t>(i));
				frame_delay(text_interval);
			}
		}
		box_1_to_0_masked(BOX_MASK_COPY);
		egc_off();

		#if (GAME == 5)
			frame_delay(1); // ZUN quirk
		#endif
	}
#endif

#if (GAME == 5)
	void pascal near box_wait_animate(int frames_to_wait)
	{
		enum {
			LEFT = (BOX_RIGHT + GLYPH_FULL_W),
		};

		unsigned int frames_waited = 0;
		bool16 ignore_frames = false;

		while(1) {
			cutscene_input_sense();
			if(key_det == INPUT_NONE) {
				break;
			}
			frame_delay(1);
		}

		if(frames_to_wait == 0) {
			frames_to_wait = 999;
			ignore_frames = true;
		}

		graph_accesspage(0);
		while(1) {
			cutscene_input_sense();

			// ZUN bloat: A white glyph aligned to the 8×16 cell grid, without
			// applying boldface… why not just show it on TRAM?
			bgimage_put_rect(LEFT, cursor.y, GLYPH_FULL_W, GLYPH_H);

			if(
				(frames_to_wait <= 0) ||
				(key_det & INPUT_OK) ||
				(key_det & INPUT_SHOT) ||
				(key_det & INPUT_CANCEL)
			) {
				return;
			}
			graph_gaiji_putc(
				LEFT,
				cursor.y,
				(ga_RETURN_KEY + ((frames_waited / 8) & (RETURN_KEY_CELS - 1))),
				V_WHITE
			);
			frames_waited++;
			if(!ignore_frames) {
				frames_to_wait--;
			}
			frame_delay(1);
		}
	}
#endif
