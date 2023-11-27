// High-level overview of the differences between the three games that can't be
// easily abstracted away:
//
// 1) TH03 and TH04 allocate dedicated memory for backing up the text box area
//    in VRAM ([box_bg]), TH05 uses the bgimage system instead.
// 2) TH03 types text onto both pages, with a delay after each glyph. TH04 and
//    TH05 render all text onto VRAM page 1 (the invisible one) without any
//    delay, and then fade the new text onto page 0 during box_1_to_0_animate().
// 3) TH03 and TH04 unblit both VRAM pages when starting a new text box, while
//    TH05 leaves the text of the previous box on the visible VRAM page 0.

#pragma option -zPgroup_01

#include <stddef.h>
#include "platform.h"
#include "x86real.h"
#include "decomp.hpp"
#include "pc98.h"
#include "planar.h"
#include "shiftjis.hpp"
#include "master.hpp"
#include "libs/kaja/kaja.h"
#include "th02/v_colors.hpp"
extern "C" {
#include "th02/hardware/frmdelay.h"
#if (GAME == 5)
	#include "th04/hardware/bgimage.hpp"
	#include "th04/hardware/grppsafx.h"
	#include "th04/snd/snd.h"
	#include "th04/gaiji/gaiji.h"
	#include "th05/hardware/input.h"
	#include "th05/formats/pi.hpp"
#elif (GAME == 4)
	#include "th03/formats/pi.hpp"
	#include "th04/hardware/input.h"
	#include "th04/hardware/grppsafx.h"
	#include "th04/snd/snd.h"
#else
	#include "th01/hardware/grppsafx.h"
	#include "th03/hardware/input.h"
	#include "th03/formats/pi.hpp"
	#include "th03/snd/snd.h"

	// Let's rather not have this one global, since it might be wrong in an
	// in-game context?
	#define key_det input_sp
#endif
}
#include "th03/cutscene/cutscene.hpp"

#pragma option -a2

#if (GAME == 3)
	#undef grcg_off // ZUN bloat
#endif

// Constants
// ---------

static const pixel_t PIC_W = PI_QUARTER_W;
static const pixel_t PIC_H = PI_QUARTER_H;
static const screen_x_t PIC_LEFT = ((RES_X / 2) - (PIC_W / 2));
static const screen_y_t PIC_TOP = 64;
static const screen_x_t PIC_RIGHT = (PIC_LEFT + PIC_W);
static const screen_x_t PIC_BOTTOM = (PIC_TOP + PIC_H);

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

static const int TEXT_INTERVAL_DEFAULT = ((GAME == 5) ? 2 : 1);
// ---------

// State
// -----

#if (GAME >= 4)
	// Statically allocated. MODDERS: TH03's dynamic allocation was better than
	// hardcoding a maximum size...
	extern unsigned char script[8192];

	extern unsigned char near *script_p;

	// Required by `script.hpp`.
	#define script_p script_p
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
extern vc_t text_col;
extern uint8_t text_fx; // TH04 and TH05 directly set [graph_putsa_fx_func].

#if (GAME >= 4)
	#define text_fx graph_putsa_fx_func
#endif
// -----

#if (GAME == 5)
	// String-to-color map
	// -------------------
	// Used to automatically change the text color whenever a specific
	// Shift-JIS code point is encountered.

	static const int COLMAP_COUNT = 8;

	typedef struct {
		vc_t values[COLMAP_COUNT];

		// Might have been originally meant for a complete character name?
		ShiftJISKanji keys[COLMAP_COUNT][NAME_KANJI_LEN];
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
		// ZUN landmine: Missing an error check if [size] >= sizeof(script);
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

// Picture crossfading works by doing a masked blit of the new picture on top
// of the old one on the invisible VRAM page, then blitting the result to the
// visible page using an EGC inter-page copy. While the latter is notoriously
// slow (see TH01's end_pic_show() for more info), blitting a packed-pixel
// format from RAM to VRAM is even worse on PC-98: At best, the inner 8-pixel
// XLOOP of master.lib's graph_pack_put_8() takes 81 cycles on a 486 and 141
// cycles on a 386, and these are just the raw instruction timings without any
// of the PC-98's infamous VRAM latencies factored in. On lower-end systems,
// this can easily sum up to more than one frame for a 320×200 image. In that
// light, it's understandable why ZUN first builds the final masked image on
// the invisible VRAM plane and then uses a *relatively* quick EGC copy to
// display it.
// (Flipping the visible page on every picture change would have only made
// everything even more complicated.)
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

				// ZUN bloat: Remember that the call site temporarily switched
				// the visible page to page 1, and blitted the image to page 0.
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

		// ZUN bloat: See the call site.
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

#include "th03/formats/script.hpp"

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
			// (Same issue as with the \n command.)
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

			// ZUN landmine: The \s command is the only place in TH05 where text
			// is unblitted from any page. Not doing it here completely breaks
			// automatically added text boxes in that game, as any new text
			// will just be blitted on top of old text.
			// (Not that the feature would have been particularly usable
			// without this bug, thanks to the assignments above…)
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

// Called with [script_p] at the character past [c].
script_ret_t pascal near script_op(unsigned char c)
{
	// ZUN bloat: Needed for code generation reasons. The structure of the
	// conditional branches below ensures that the `return`s have no actual
	// effect, so this block can just be deleted.
	#if (GAME == 5)
		#define palette_black_in(x)  palette_black_in(x);  return CONTINUE;
		#define palette_black_out(x) palette_black_out(x); return CONTINUE;
		#define palette_white_in(x)  palette_white_in(x);  return CONTINUE;
		#define palette_white_out(x) palette_white_out(x); return CONTINUE;
	#endif

	int i;
	int p1;
	int p2;

	// ZUN bloat: PF_FN_LEN on its own is enough, it already includes the \0
	// terminator.
	char fn[PF_FN_LEN + 3];

	c = tolower(c);
	switch(c) {
	case 'n':
		cursor.y += GLYPH_H;
		cursor.x = BOX_LEFT;
		if(cursor.y < BOX_BOTTOM) {
			break;
		}
		// ZUN quirk: Since [cursor.y] is >= BOX_BOTTOM here, the TH05 Return
		// key animation will be displayed at the right edge of the "5th" line,
		// below BOX_BOTTOM. (Same issue as in cursor_advance_and_animate().)

		// fallthrough to \s if this box is full

	case 's':
		c = *script_p;
		#if (GAME >= 4)
			box_1_to_0_animate();
		#endif
		if(c != '-') {
			script_param_read_number_first(p1, 0);
			if(!fast_forward) {
				box_wait_animate(p1);
			}
		} else {
			script_p++;
		}
		cursor.x = BOX_LEFT;
		cursor.y = BOX_TOP;

		#if (GAME == 5)
			graph_accesspage(1);
			bgimage_put_rect(BOX_LEFT, BOX_TOP, BOX_W, BOX_H);

			// ZUN bloat: All blitting operations in this module access the
			// intended page before they blit. That's why preliminary state
			// changes like this one are completely redundant, thankfully.
			graph_accesspage(0);
		#else
			// High-level overview, point 2)
			graph_accesspage(1);	box_bg_put();
			graph_accesspage(0);	box_bg_put();
		#endif
		break;

	case 'c':
		#if (GAME == 5)
			// ZUN bloat: Doesn't matter for either '=' or digits.
			c = tolower(*script_p);

			if(c == '=') {
				goto colmap_add;
			}
		#endif
		script_param_read_number_first(p1, V_WHITE);
		text_col = p1;
		break;

	case 'b':
		script_param_read_number_first(p1, WEIGHT_BOLD);
		#if (GAME >= 4)
			graph_putsa_fx_func = static_cast<graph_putsa_fx_func_t>(p1);
		#else
			switch(p1) {
			case WEIGHT_NORMAL:	text_fx = FX_WEIGHT_NORMAL;	break;
			case WEIGHT_HEAVY: 	text_fx = FX_WEIGHT_HEAVY; 	break;
			case WEIGHT_BOLD:  	text_fx = FX_WEIGHT_BOLD;  	break;
			case WEIGHT_BLACK: 	text_fx = FX_WEIGHT_BLACK; 	break;
			}
		#endif
		break;

	case 'w':
		c = tolower(*script_p);
		if((c == 'o') || (c == 'i')) {
			script_op_fade(c, palette_white_in, palette_white_out, p1);
		} else {
			#if (GAME >= 4)
				box_1_to_0_animate();
			#endif
			script_param_number_default = 64;
			if(c != 'm') {
				if(c == 'k') {
					script_p++;
				}
				script_param_read_number_first(p1);
				if(!fast_forward) {
					#if (GAME >= 4)
						frame_delay(p1);
					#else
						if(c != 'k')  {
							frame_delay(p1);
						} else {
							input_wait_for_ok(p1);
						}
					#endif
					#if (GAME == 5) // ZUN bloat
						return CONTINUE;
					#endif
				}
			} else {
				script_p++;
				c = *script_p;
				if(c == 'k') {
					script_p++;
				}
				script_param_read_number_first(p1);
				script_param_read_number_second(p2);
				if(!fast_forward) {
					// ZUN landmine: Does not prevent the potential deadlock
					// issue with this function.
					#if (GAME >= 4)
						snd_delay_until_measure(p1, p2);
					#else
						if(c != 'k')  {
							snd_delay_until_measure(p1, p2);
						} else {
							input_wait_for_ok_or_measure(p1, p2);
						}
					#endif
				}
			}
		}
		break;

	case 'v':
		if(*script_p != 'p') {
			script_param_read_number_first(p1, TEXT_INTERVAL_DEFAULT);
			text_interval = p1;
		} else {
			script_p++;
			script_param_read_number_first(p1, 0);
			graph_showpage(p1);
		}
		break;

	case 't':
		script_param_read_number_first(p1, 100);
		if(!fast_forward) {
			frame_delay(1);
		}
		palette_settone(p1);
		break;

	case 'f':
		c = *script_p;
		if(c != 'm') {
			if((c == 'i') || (c == 'o')) {
				script_op_fade(c, palette_black_in, palette_black_out, p1);
			}
		} else {
			script_p++;
			script_param_read_number_first(p1, 1);
			snd_kaja_func(KAJA_SONG_FADE, p1);
			#if (GAME <= 4) // ZUN bloat: `break` or `return`, pick one!
				return CONTINUE;
			#endif
		}
		break;

	case 'g':
		if((GAME == 5) || (*script_p != 'a')) {
			script_op_shake(fast_forward, p2, p1);
		} else {
			script_p++;
			script_param_read_number_first(p1, 0);

			graph_accesspage(1);
			#if (GAME == 3)
				// Might look like a ZUN bug, but actually works around the
				// master.lib bug mentioned in the comment of this function,
				// which ZUN only fixed for TH04 and TH05. In the original
				// binary, the ASCII→digit conversion inside
				// str_consume_up_to_3_digits() is done by ADDing a negative
				// number, which causes the x86 carry flag to always be set
				// when we get here and haven't fallen back onto the default
				// value. Therefore, the bug will always add 1 onto the gaiji
				// ID, which can be worked around by subtracting 1 from ID
				// before passing it as a parameter. Once graph_gaiji_putc()
				// returns, the carry flag happens to be cleared, which is
				// why the subtraction is not necessary for the call below to
				// display the intended gaiji.
				graph_gaiji_putc(cursor.x, cursor.y, (p1 - 1), text_col);

				graph_accesspage(0);
			#endif
			// [text_fx] is also ignored here...
			graph_gaiji_putc(cursor.x, cursor.y, p1, text_col);
			// ZUN quirk: No [text_interval]-based delay in TH03.

			cursor_advance_and_animate();
		}
		return CONTINUE;

	case 'k':
		// ZUN landmine: Should have also been done in TH04. Without this call,
		// this command will wait on an invisible text box, and needs to be
		// preceded by a \vp1 command to actually work as a mid-box pause.
		#if (GAME == 5)
			box_1_to_0_animate();
		#endif

		script_param_read_number_first(p1, 0);
		if(!fast_forward) {
			// ZUN quirk: This parameter is ignored in TH03. Labeling this as a
			// quirk because the original TH03 scripts call this command with a
			// non-0 parameter in 19 of 34 cases, suggesting that ZUN made the
			// conscious decision to override these parameters with 0 later in
			// development.
			box_wait_animate((GAME >= 4) ? p1 : 0);
		}
		return CONTINUE;

	case '@':
		graph_accesspage(1);	graph_clear();
		graph_accesspage(0);	graph_clear();
		#if (GAME == 5)
			bgimage_snap();
		#else
			// ZUN landmine: Missing a box_bg_allocate_and_snap() or equivalent
			// call. Any future box_bg_put() call will still display the box
			// area snapped from any previously displayed background image.
			// This bug therefore effectively restricts usage of this command
			// to either the beginning of a script (before the first background
			// image is shown) or its end (after no more new text boxes are
			// started).
		#endif
		break;

	case 'p':
		c = *script_p;
		script_p++;
		if((c == '=') || (c == '@')) {
			graph_accesspage(1);
			if(c == '=') {
				pi_palette_apply(PIC_SLOT);
			}
			pi_put_8(0, 0, PIC_SLOT);
			graph_copy_page(0);
			graph_accesspage(0);
			#if (GAME == 5)
				bgimage_snap();
			#else
				box_bg_allocate_and_snap();
			#endif
		} else if(c == '-') {
			pi_free(PIC_SLOT);
			return CONTINUE;
		} else if(c == 'p') {
			pi_palette_apply(PIC_SLOT);
			return CONTINUE;
		} else if(c != ',') {
			script_p--;
		} else {
			script_param_read_fn(fn, p1, c);
			#if (GAME >= 4)
				pi_free(PIC_SLOT);
			#endif
			pi_load(PIC_SLOT, fn);
		}
		break;

	case '=':
		script_param_number_default = PI_QUARTER_COUNT;
		c = *script_p;
		if(c != '=') {
			script_param_read_number_first(p1);
			#if (GAME == 5)
				frame_delay(1); // ZUN quirk
				graph_showpage(0);
				graph_accesspage(1);
			#else
				// ZUN bloat: Why did ZUN temporarily switch foreground and
				// background pages for the duration of this command?! Not only
				// is it completely unnecessary, it's also downright harmful.
				// If these lines didn't exist, the entire cutscene system
				// would have been both much easier to understand *and* more
				// performant:
				//
				// • The intent for both VRAM pages would have been crystal
				//   clear: Page 0 is always shown and contains the actively
				//   displayed picture and text, and page 1 is used for
				//   temporarily storing pixels that are later crossfaded onto
				//   page 0. Through their mere existence, these lines suggest
				//   a more complex interplay between the two pages, which
				//   doesn't actually exist.
				// • TH03 wouldn't have needed to render text and gaiji to both
				//   VRAM pages.
				// • (Technically, TH03 wouldn't have even needed [box_bg] as a
				//   result, but that was a decent investment regardless –
				//   inter-page blitting is horribly slow no matter how you do
				//   it. Also, this buffer does become necessary in TH04 – see
				//   point 2) in the high-level overview)
				// • If \vp didn't exist (it's not used by the original scripts
				//   anyway), the entire system would have only needed a single
				//   graph_showpage(0) call at the start of cutscene_animate().
				//
				// ZUN landmine: Since TH04 renders text to VRAM page 1,
				// calling \= or \== in the middle of a string of text
				// temporarily shows any text rendered since the last
				// box_1_to_0_animate() call if any of the following blit
				// operations spends more than one frame with page 1 visible.
				// In practice, this only happens on very underclocked systems
				// far below the game's target of 66 MHz, but it's a landmine
				// nonetheless.
				graph_showpage(1);
				graph_accesspage(0);
			#endif
			if(p1 < PI_QUARTER_COUNT) {
				pi_put_quarter_8(PIC_LEFT, PIC_TOP, PIC_SLOT, p1);
			} else {
				grcg_setcolor(GC_RMW, 0);
				grcg_boxfill_8(
					PIC_LEFT, PIC_TOP, (PIC_RIGHT - 1), (PIC_BOTTOM - 1)
				);
				grcg_off();
			}
		} else {
			script_p++;
			script_param_read_number_first(p1);
			script_param_number_default = 1;
			script_param_read_number_second(p2);
			for(i = 0; i < PI_MASK_COUNT; i++) {
				pic_put_both_masked(PIC_LEFT, PIC_TOP, p1, i);
				if(!fast_forward) {
					frame_delay(p2);
				}
			}
			#if (GAME == 5)
				graph_accesspage(1);
				pi_put_quarter_8(PIC_LEFT, PIC_TOP, PIC_SLOT, p1);
				frame_delay(1); // ZUN quirk
			#else
				// ZUN bloat: See above.
				// ZUN landmine: See above.
				graph_showpage(1);
				graph_accesspage(0);

				pi_put_quarter_8(PIC_LEFT, PIC_TOP, PIC_SLOT, p1);
			#endif
		}
		#if (GAME <= 4)
			graph_showpage(0); // ZUN bloat: See above.
		#endif
		pic_copy_to_other(PIC_LEFT, PIC_TOP);
		break;

	case 'm':
		// TH03 uses the TH02 version of snd_load(), and consequently does the
		// right thing and stops any currently playing BGM before loading the
		// new one. It wouldn't be necessary for TH04 and TH05, but hey, still
		// doing it removes a potential implementation difference.
		script_op_bgm(true, c, fn, p1);
		break;

	case 'e':
		script_param_read_number_first(p1);
		snd_se_play_force(p1);
		break;

	#if (GAME == 5)
	colmap_add:
		script_p++;
		colmap.keys[colmap_count][0].byte[0] = *script_p;
		script_p++;
		colmap.keys[colmap_count][0].byte[1] = *script_p;

		// ZUN landmine: Jumps over the additional comma separating the two
		// parameters, and assumes it's always present. Come on!
		// script_param_read_number_second() exists to handle exactly this
		// situation in a cleaner way.
		script_p += 2;

		script_param_read_number_first(p1, V_WHITE);

		// ZUN landmine: No bounds check
		colmap.values[colmap_count] = p1;
		colmap_count++;
		break;
	#endif

	case '$':
		return STOP;
	}
	return CONTINUE;
}

void near cutscene_animate(void)
{
	extern ShiftJISKanji near CUTSCENE_KANJI[];

	#if (GAME == 5)
		int gaiji;
	#endif
	unsigned char c;
	uint8_t speedup_cycle;

	ShiftJISKanji& kanji = *CUTSCENE_KANJI;

	cursor.x = BOX_LEFT;
	cursor.y = BOX_TOP;
	text_interval = TEXT_INTERVAL_DEFAULT;
	text_col = V_WHITE;
	text_fx = FX_WEIGHT_BOLD;

	#if (GAME == 3)
		speedup_cycle = 0;
	#endif

	// Necessary because scripts can (and do) show multiple text boxes on the
	// initially black background.
	// ZUN landmine: TH05 assumes that they don't, which is true for all
	// scripts in the original game.
	#if (GAME != 5)
		box_bg_allocate_and_snap();
	#endif

	fast_forward = false;

	while(1) {
		cutscene_input_sense();
		if(key_det & INPUT_CANCEL) {
			fast_forward = true;
		} else {
			fast_forward = false;
		}

		#if (GAME == 5) // ZUN bloat: Should be part of the colmap loop.
			int i = 0;
		#endif

		// Same iteration code as in TH04's dialog system.
		c = *(script_p++);
		if(str_sep_control_or_space(c)) {
			continue;
		}

		// Opcode?
		if(c == '\\') {
			c = *(script_p++);
			if(script_op(c) == STOP) {
				break;
			}
			continue;
		}

		#if (GAME == 5)
			if(c == '@') {
				c = tolower(*script_p);
				script_p++;
				switch(c) {
				case 't':
					gaiji = gs_SWEAT;
					break;

				case 'h':
					gaiji = gs_HEART_2;
					break;

				case '?':
					gaiji = gs_QUESTION;
					break;

				case '!':
					c = *(script_p++);
					switch(c) {
					case '!':
						gaiji = gs_DOUBLE_EXCLAMATION;
						break;

					case '?':
						gaiji = gs_EXCLAMATION_QUESTION;
						break;

					default:
						script_p--;
						gaiji = gs_EXCLAMATION;
						break;
					}
					break;

				default:
					script_p--;
					script_param_read_number_first(gaiji, gs_NOTES);
					break;
				}
				graph_showpage(0);
				graph_accesspage(1);

				// Still ignoring [text_fx].
				graph_gaiji_putc(cursor.x, cursor.y, gaiji, text_col);

				cursor_advance_and_animate();
				i = 1; // ZUN bloat
				continue;
			}
		#endif

		// Regular kanji
		kanji.byte[0] = c;
		c = *script_p;
		kanji.byte[1] = c;
		script_p++;

		#if (GAME == 5)
			if(cursor.x == BOX_LEFT) {
				for(i = 0; i < colmap_count; i++) {
					if(colmap.keys[i][0].t == kanji.t) {
						text_col = colmap.values[i];
						break;
					}
				}
			}
		#endif

		#if (GAME >= 4)
			graph_showpage(0);
			graph_accesspage(1);
			graph_putsa_fx(cursor.x, cursor.y, text_col, kanji.byte);

			// ZUN bloat: All blitting operations in this module access the
			// intended page before they blit. That's why preliminary state
			// changes like this one are completely redundant, thankfully.
			#if (GAME == 5)
				graph_accesspage(0);
			#endif
		#else
			graph_accesspage(1);
			graph_putsa_fx(
				cursor.x, cursor.y, (text_col | text_fx), kanji.byte
			);
			graph_accesspage(0);
			graph_putsa_fx(
				cursor.x, cursor.y, (text_col | text_fx), kanji.byte
			);
		#endif
		cursor_advance_and_animate();
		#if (GAME == 5)
			i = 1; // ZUN bloat
		#endif

		// High-level overview, point 3)
		#if (GAME == 3)
			if(fast_forward) {
				continue;
			}
			if(key_det == INPUT_NONE) {
				frame_delay(text_interval);
			} else {
				int speedup_interval = (text_interval / 3);
				if((speedup_cycle & 1) || speedup_interval) {
					if(speedup_interval == 0) {
						speedup_interval++;
					}
					frame_delay(speedup_interval);
				}
				speedup_cycle++;
			}
		#endif
	}
	#if (GAME == 5)
		bgimage_free();
		pi_free(PIC_SLOT);
	#else
		box_bg_put();
		box_bg_free();
	#endif
}
