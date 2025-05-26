/// Character selection menu
/// ------------------------

#pragma option -zPgroup_01

#include "th03/op/m_select.hpp"
#include "decomp.hpp"
#include "libs/master.lib/master.hpp"
#include "libs/master.lib/pc98_gfx.hpp"
#include "th01/math/clamp.hpp"
#include "th02/v_colors.hpp"
#include "th02/hardware/frmdelay.h"
#include "th02/formats/bfnt.h"
#include "th03/common.h"
#include "th03/resident.hpp"
#include "th03/formats/cdg.h"
extern "C" {
#include "th03/formats/hfliplut.h"
}
#include "th03/formats/scoredat.hpp"
#include "th03/gaiji/gaiji.h"
#include "th03/hardware/input.h"
#include "th03/math/polar.hpp"
#include "th03/shiftjis/fns.hpp"
#include "th03/snd/snd.h"
#include "th03/sprites/op_cdg.hpp"

/// Constants
/// ---------

static const char* PLAYCHAR_PIC_FN[PLAYCHAR_COUNT] = PLAYCHAR_PIC_FN_DEF;

static const int STAT_COUNT = 3;
static const uint8_t PLAYCHAR_STATS[PLAYCHAR_COUNT][STAT_COUNT] = {
	{ 3, 1, 5 },
	{ 4, 4, 2 },
	{ 3, 4, 3 },
	{ 2, 3, 1 },
	{ 4, 1, 4 },
	{ 2, 2, 5 },
	{ 4, 5, 1 },
	{ 5, 2, 4 },
	{ 5, 5, 3 },
};
static const unsigned char g_CURSOR_TOP[PLAYER_COUNT][gc_GAIJI_W + 1] = {
	{ gc_P1_TOP_1, gc_P1_TOP_2 },
	{ gc_P2_TOP_1, gc_P2_TOP_2 },
};
static const unsigned char g_CURSOR_BOTTOM[PLAYER_COUNT][gc_GAIJI_W + 1] = {
	{ gc_P1_BOTTOM_1, gc_P1_BOTTOM_2 },
	{ gc_P2_BOTTOM_1, gc_P2_BOTTOM_2 },
};
/// ---------

/// Coordinates
/// -----------

static const pixel_t PIC_W = 192;
static const pixel_t PIC_H = 192;
static const pixel_t PIC_MARGIN_X = 32;

static const pixel_t NAME_W = 128;
static const pixel_t NAME_H = 16;
static const pixel_t NAME_PADDING_Y = 4;
static const pixel_t NAME_PADDED_H = (NAME_H + NAME_PADDING_Y);

static const pixel_t STATS_W = 128;
static const pixel_t EXTRA_W = 64;
static const pixel_t EXTRA_FOR_PLAYCHAR_W = 32;

static const pixel_t STAT_STAR_W = 9;
static const pixel_t STAT_STAR_PADDED_W = (STAT_STAR_W + 2);
static const pixel_t STAT_STAR_H = 16;

static const screen_x_t P1_LEFT = PIC_MARGIN_X;
static const screen_x_t P2_LEFT = (RES_X - PIC_MARGIN_X - PIC_W);
static const screen_y_t PIC_TOP = 96;

static const screen_x_t NAMES_LEFT = ((RES_X / 2) - (NAME_W / 2));
static const screen_y_t NAMES_TOP = 136;

static const screen_y_t STATS_TOP = (PIC_TOP + PIC_H + 16);
/// -----------

/// State
/// -----

static bool input_locked[PLAYER_COUNT] = { false, false };

static unsigned char curve_cycle;
static int8_t padding_1; // ZUN bloat
resident_t far* resident; // ZUN bloat: Why is this here?
static playchar_t sel[PLAYER_COUNT];
static bool sel_confirmed[PLAYER_COUNT];
static page_t page_shown;
static int8_t padding_2; // ZUN bloat
func_t_near input_mode; // ZUN bloat: Why is this here?
static unsigned int fadeout_frames;
static int16_t curve_unused; // ZUN bloat
static int curve_trail_count;
static unsigned char playchars_available;
/// -----

#include "th03/formats/score_ld.cpp"

unsigned char near playchars_available_load(void)
{
	unsigned char ret = PLAYCHAR_COUNT_LOCKED;
	for(int i = RANK_EASY; i < (RANK_LUNATIC + 1); i++) {
		if(scoredat_load_and_decode(static_cast<rank_t>(i))) {
			return PLAYCHAR_COUNT_LOCKED;
		}
		if(hi.score.cleared == SCOREDAT_CLEARED) {
			ret = PLAYCHAR_COUNT;
		}
	}
	return ret;
}

// Coincidentally, these were the only characters available in the trial
// version.
void near select_cdg_load_part1_of_4(void)
{
	hflip_lut_generate();

	static_assert(PLAYCHAR_COUNT >= 3);
	for(int i = 0; i < 3; i++) {
		cdg_load_single((CDG_PIC + i), PLAYCHAR_PIC_FN[i], 0);
	}
	cdg_load_all_noalpha(CDG_EXTRA_FOR_PLAYCHAR, "slex.cd2");
}

void near select_cdg_load_part2_of_4(void)
{
	// ZUN bloat: Shouldn't this be exclusively loaded for Story Mode?
	cdg_load_single((CDG_PIC_SELECTED + 1), "99sl.cdg", 0);

	cdg_load_single_noalpha(CDG_STATS, "slwin.cdg", 0);
	cdg_load_single_noalpha(CDG_EXTRA_BG, "slex.cdg", 0);
}

void near select_cdg_load_part3_of_4(void)
{
	// ZUN bloat: Redundant, PID 0 always has to select a character before the
	// game shows the image in this slot.
	cdg_load_single((CDG_PIC_SELECTED + 0), PLAYCHAR_PIC_FN[PLAYCHAR_REIMU], 0);

	static_assert(PLAYCHAR_COUNT >= 6);
	for(int i = 3; i < 6; i++) {
		cdg_load_single((CDG_PIC + i), PLAYCHAR_PIC_FN[i], 0);
	}
}

#define select_cdg_load_part4_of_4() { \
	static_assert(PLAYCHAR_COUNT <= 9); \
	for(int i = 6; i < 9; i++) { \
		cdg_load_single((CDG_PIC + i), PLAYCHAR_PIC_FN[i], 0); \
	} \
} \

void near select_init_and_load(void)
{
	vsync_Count1 = 0;

	snd_kaja_func(KAJA_SONG_STOP, 0);
	snd_load("select.m", SND_LOAD_SONG);
	snd_kaja_func(KAJA_SONG_PLAY, 0);

	curve_unused = 200;
	random_seed = resident->rand;

	text_clear();
	super_free();
	super_entry_bfnt("chname.bft");

	// ZUN landmine: Does nothing to avoid this happening mid-frame and causing
	// tearing.
	graph_accesspage(0);	graph_clear();
	graph_accesspage(1);	graph_clear();
	graph_showpage(0);
	page_shown = 0;

	palette_entry_rgb_show("TLSL.RGB");
	select_cdg_load_part4_of_4();

	// ZUN bug: Is this supposed to be long enough for the player to release
	// the Shot key that might have entered this menu? If that was the intent,
	// the menu functions should properly lock input until the player released
	// that key. Keep holding the Shot key for more than 30 frames and the
	// menus will still confirm the initial selection on their first frame.
	// The menu needs [input_locked] anyway; why isn't it set here?!
	while(vsync_Count1 < 30) {
	}

	// ZUN bug: [vsync_Count1] is not reset after the loop above. This causes
	// the menu functions to only actually render 8 trailing curves on their
	// first iteration: The first call to select_wait_flip_and_clear_vram()
	// will then think that the frame took longer than 30 VSync interrupts to
	// render and will consequently always decrement the count to 7.
	curve_trail_count = 8;

	playchars_available = playchars_available_load();
}

void near select_free(void)
{
	for(int i = CDG_SELECT_FIRST; i < CDG_SELECT_COUNT; i++) {
		cdg_free(i);
	}
	super_free();
}

inline void sel_p1_pic_put(void) {
	cdg_put_8(
		P1_LEFT,
		PIC_TOP,
		(!sel_confirmed[0] ? (CDG_PIC + sel[0]) : (CDG_PIC_SELECTED + 0))
	);
}

void near vs_sel_pics_put(void)
{
	sel_p1_pic_put();
	cdg_put_hflip_8(
		P2_LEFT,
		PIC_TOP,
		(!sel_confirmed[1] ? (CDG_PIC + sel[1]) : (CDG_PIC_SELECTED + 1))
	);
}

void near story_sel_pics_put(void)
{
	sel_p1_pic_put();
	cdg_put_8(P2_LEFT, PIC_TOP, (CDG_PIC_SELECTED + 1));
}

#define stat_star_row_put(pid, row_top, stat_i, star_i, star_left) { \
	star_i = 5; \
	star_left = (((pid == 0) ? P1_LEFT : P2_LEFT) + STATS_W - 20); \
	while(PLAYCHAR_STATS[sel[pid]][stat_i] < star_i) { \
		grcg_boxfill( \
			star_left, \
			row_top, \
			(star_left + STAT_STAR_W - 1), \
			(row_top + STAT_STAR_H -1) \
		); \
		star_i--; \
		star_left -= STAT_STAR_PADDED_W; \
	} \
}

void near stats_put(void)
{
	int stat_i;
	int star_i;
	screen_x_t star_left;

	cdg_put_noalpha_8(P1_LEFT, STATS_TOP, CDG_STATS);
	if(resident->game_mode != GM_STORY) {
		cdg_put_noalpha_8(P2_LEFT, STATS_TOP, CDG_STATS);
	}

	grcg_setcolor(GC_RMW, 14);
	stat_i = 0;
	screen_y_t row_top = (STATS_TOP + 11);
	while(stat_i < STAT_COUNT) {
		stat_star_row_put(0, row_top, stat_i, star_i, star_left);
		if(resident->game_mode != GM_STORY) {
			stat_star_row_put(1, row_top, stat_i, star_i, star_left);
		}
		stat_i++;
		row_top += STAT_STAR_H;
	}

	grcg_off();
}

// Either names, cursors, or both were drawn to the text layer at one point?
// Unused in the final game.
static const tram_atrb_t TRAM_COLORS_UNUSED[] = { TX_RED, TX_YELLOW, TX_WHITE };

void near names_put(void)
{
	screen_y_t top = NAMES_TOP;
	int playchar = 0;
	while(playchar < playchars_available) {
		static_assert(NAME_W == (2 * BFNT_ASSUMED_MAX_W));
		super_put((NAMES_LEFT + (0 * (NAME_W / 2))), top, ((playchar * 2) + 0));
		super_put((NAMES_LEFT + (1 * (NAME_W / 2))), top, ((playchar * 2) + 1));
		playchar++;
		top += NAME_PADDED_H;
	}
}

inline void extra_put(pid_t pid, screen_x_t box_left) {
	cdg_put_noalpha_8(box_left, STATS_TOP, CDG_EXTRA_BG);
	cdg_put_noalpha_8(
		(box_left + (EXTRA_W / 2) - (EXTRA_FOR_PLAYCHAR_W / 2)),
		(STATS_TOP + 12),
		(CDG_EXTRA_FOR_PLAYCHAR + sel[pid])
	);
}

void near extras_put(void)
{
	extra_put(0, (P1_LEFT + STATS_W));
	if(resident->game_mode != GM_STORY) {
		extra_put(1, (P2_LEFT + STATS_W));
	}
}

// Q8.8 fixed-point
typedef int freq_t;
static const freq_t FREQ_FACTOR = (1 << 8);

// Plots a variant of a Lissajous curve, but with angles calculated as
//
// 	([freq] × ([angle_base]) + [angle_offset]))
//
// instead of the standard
//
// 	(([freq] × [angle_base]) + [angle_offset])
//
// allowing the natural overflow of 8-bit angles to create interesting splits
// along the curve.
void pascal near curve_put(
	unsigned char angle_offset_x,
	unsigned char angle_offset_y,
	pixel_t radius,
	freq_t freq_x,
	freq_t freq_y
)
{
	screen_y_t x;
	screen_y_t y;
	unsigned int angle_base;
	for(angle_base = 0x00; angle_base < 0x100; angle_base++) {
		// ZUN bloat: The game original game runs this loop body 4,096 times
		// per rendered frame, magnifying every suboptimal implementation
		// choice. On an i486/Pentium, ZUN wastes:
		//
		// • ≥42 / 64 cycles by dividing by [FREQ_FACTOR] instead of
		//   right-shifting*,
		// • ≥42 / 16 cycles by not inlining grcg_pset(), and
		// • ≥100 / 40 cycles by not inlining polar().
		//
		// Total waste for all points: ≥753,664 / 491,520 cycles.
		//
		// *) Usually, this would cause inaccuracies for negative numbers as
		//    documented in th01/math/polar.hpp, but [freq_x] and [freq_y] only
		//    ever hold unsigned values.
		unsigned char angle;
		angle = (angle_base + angle_offset_x);
		angle = ((angle * freq_x) / FREQ_FACTOR);
		x = polar_x((RES_X / 2), radius, angle);

		angle = (angle_base + angle_offset_y);
		angle = ((angle * freq_y) / FREQ_FACTOR);
		y = polar_y((RES_Y / 2), radius, angle);

		grcg_pset(x, y);
	}
}

#define select_curves_put(offset, freq_x, freq_y, freq_other) { \
	/** \
	 * ZUN quirk: A diameter of (220 × 2) = 440 pixels is larger than the \
	 * vertical resolution, thus cutting off several pixels. \
	 */ \
	curve_put( \
		(curve_cycle - (offset * 2)), \
		((curve_cycle * 2) - (offset * 4)), \
		220, \
		freq_other, \
		freq_y \
	); \
	/** \
	 * ZUN quirk: Halving the Y angle offset restricts this smaller curve to \
	 * only the first half of the sine oscillation. This is fine as long as we \
	 * don't subtract the trail [offset]. But once we do, the resulting Y \
	 * offset wraps around into the other half of the oscillation at \
	 * \
	 * 	([curve_cycle] ≤ ([curve_trail_count] * 2)) \
	 * \
	 * This causes the discontinuity between the start and end of the cycle \
	 * as the trailing curves during the first [curve_trail_count] frames \
	 * appear flipped compared to their counterparts at the end of the cycle. \
	 * Removing the division would be the easiest fix here; the second-easiest \
	 * fix would be to restrict the subtraction to the first half of the \
	 * oscillation: \
	 * \
	 * 	(((curve_cycle / 2) - offset) & 0x7F) \
	 */ \
	curve_put( \
		((0x00 - curve_cycle) + (offset * 2)), \
		((curve_cycle - (offset * 2)) / 2), /* ZUN bloat: Multiply out */ \
		120, \
		freq_x, \
		freq_other \
	); \
}

// Desmos plot of the full effect:
//
// 	https://www.desmos.com/calculator/sstcw9ru5x?invertedColors=true
void near select_curves_update_and_render(void)
{
	freq_t freq_other;
	int trail_count_half;
	freq_t freq_y;
	freq_t freq_x;
	int i;

	// ZUN bloat: Should be a dedicated variable.
	#define cycle_triangle freq_other

	cycle_triangle = curve_cycle;
	if(cycle_triangle >= 0x80) {
		cycle_triangle = (0x100 - cycle_triangle);
	}

	// ZUN bloat: {
	// 	freq_other = (FREQ_FACTOR + (1 * cycle_triangle));
	// 	freq_x = (FREQ_FACTOR + (2 * cycle_triangle));
	// 	freq_y = ((2 * FREQ_FACTOR) + (2 * cycle_triangle));
	// }
	freq_other = cycle_triangle;
	freq_x = (FREQ_FACTOR + freq_other + freq_other);
	freq_other += FREQ_FACTOR;
	freq_y = (freq_other + freq_other);

	// ZUN quirk: Maybe these should be blitted in the opposite order? Due to
	// the different colors, this causes the trailing curves appear on top of
	// the main one.
	grcg_setcolor(GC_RMW, 6);
	select_curves_put(0, freq_x, freq_y, freq_other);

	grcg_setcolor(GC_RMW, 5);
	trail_count_half = (curve_trail_count / 2);
	if(curve_trail_count & 1) {
		trail_count_half++;
	}
	for(i = 1; i <= trail_count_half; i++) {
		select_curves_put(i, freq_x, freq_y, freq_other);
	}

	grcg_setcolor(GC_RMW, 1);
	for(i = (trail_count_half + 1); i <= curve_trail_count; i++) {
		select_curves_put(i, freq_x, freq_y, freq_other);
	}

	grcg_off();
	curve_cycle += 0x02;

	#undef cycle_triangle
}

inline void select_base_render(void near (*pics_put)()) {
	select_curves_update_and_render();
	pics_put();
	stats_put();
	names_put();
	extras_put();
}

void pascal near cursor_put(pid2 pid, vc_t col)
{
	// ZUN bloat: `* NAME_W` would have done the job.
	static_assert(((NAME_W / 8) * (NAME_W / 16)) == NAME_W);
	screen_x_t left = (
		(NAMES_LEFT - GAIJI_W) + (pid * (NAME_W / 8) * (NAME_W / 16))
	);

	screen_y_t top = ((NAMES_TOP - (GLYPH_H / 2)) + (sel[pid] * NAME_PADDED_H));
	graph_gaiji_puts(left, (top +       0), GAIJI_W, g_CURSOR_TOP[pid], col);
	graph_gaiji_puts(left, (top + GLYPH_H), GAIJI_W, g_CURSOR_BOTTOM[pid], col);
}

inline void cursor_put_p1(void) {
	cursor_put(0, (sel_confirmed[0] ? V_WHITE :  8));
}
inline void cursor_put_p2(void) {
	cursor_put(1, (sel_confirmed[1] ? V_WHITE : 10));
}

#define select_confirm(pid, palette_id, swap_func) { \
	int playchar = sel[pid]; \
	resident->playchar_paletted[pid].v = ( \
		TO_OPTIONAL_PALETTED(playchar) + palette_id \
	); \
	palette_white_in(1); \
	\
	static_assert(PLAYER_COUNT == 2); \
	if(sel_confirmed[1 - pid] && ( \
		resident->playchar_paletted[0].v == resident->playchar_paletted[1].v \
	)) { \
		swap_func; \
		cdg_load_single( \
			(CDG_PIC_SELECTED + pid), PLAYCHAR_PIC_FN[playchar], !palette_id \
		); \
	} else { \
		cdg_load_single( \
			(CDG_PIC_SELECTED + pid), PLAYCHAR_PIC_FN[playchar], palette_id \
		); \
	} \
	\
	static_assert(PLAYER_COUNT == 2); \
	if(sel_confirmed[1 - pid]) { \
		/**
		 * ZUN bloat: Should only be done in the main function, see the \
		 * comment there. \
		 */ \
		fadeout_frames = 0; \
	} \
	sel_confirmed[pid] = true; \
	input_locked[pid] = true; \
}

void pascal near select_update_player(input_t input, pid2 pid)
{
	if(sel_confirmed[pid]) {
		return;
	}
	if(input_locked[pid]) {
		if(input == INPUT_NONE) {
			input_locked[pid] = false;
		}
		return;
	}

	if(input & INPUT_UP) {
		ring_dec(static_cast<char>(sel[pid]), (playchars_available - 1));
		input_locked[pid] = true;
	}
	if(input & INPUT_DOWN) {
		ring_inc_ge(static_cast<char>(sel[pid]), playchars_available);
		input_locked[pid] = true;
	}
	if(input & INPUT_SHOT) {
		select_confirm(pid, 0, resident->playchar_paletted[pid].v++);
	}
	if(input & INPUT_BOMB) {
		select_confirm(pid, 1, resident->playchar_paletted[pid].v--);
	}
}

inline void sel_init_vs(void) {
	static_assert(PLAYER_COUNT == 2);
	sel[0] = resident->playchar_paletted[0].char_id();
	sel[1] = resident->playchar_paletted[1].char_id();
	sel_confirmed[0] = false;
	sel_confirmed[1] = false;
}

inline void select_input_sense(void) {
	// ZUN bloat: Already part of all four possible [input_mode]s.
	input_reset_sense_key_held();

	input_mode();
}

inline bool select_cancel(void) {
	// ZUN bloat: palette_black() is a more performant way to achieve the same
	// without raising any questions about whether this targets the correct
	// VRAM page.
	graph_accesspage(0);
	graph_clear();
	graph_showpage(0);

	// Redundant in the released game, but makes sense for clearing potential
	// debug output.
	text_clear();

	select_free();
	snd_kaja_func(KAJA_SONG_STOP, 0);
	return true;
}

// ZUN landmine: Should be done at the beginning of select_base_render() to
// ensure that the palette applies to the entire frame. Plotting the curves
// takes a while, and doing this afterward all but ensures palette tearing.
#define select_fadeout_render(quit_label) { \
	text_clear(); /* ZUN bloat: No point to this one. */ \
	\
	/** \
	 * ZUN quirk: Should have maybe been `>` rather than `>=`. Since \
	 * [fadeout_frames] is technically off-by-one (frame 0 is the last frame \
	 * of palette_white_in()), this sets the palette tone to 104 on frame #15. \
	 */ \
	if(fadeout_frames >= 16) { \
		palette_settone(200 - (fadeout_frames * 6)); \
	} \
	if(fadeout_frames > 32) { \
		goto quit_label; \
	} \
	optimization_barrier(); \
}

#define select_wait_flip_and_clear_vram() { \
	while(vsync_Count1 < 3) { \
	} \
	/** \
	 * ZUN landmine: We're not waiting for VSync if the code took longer than \
	 * 3 VSync events, ensuring screen tearing in this case. \
	 */ \
	\
	if((vsync_Count1 > 4) && (curve_trail_count > 1)) { \
		curve_trail_count--; \
	} \
	vsync_Count1 = 0; \
	graph_accesspage(page_shown); \
	page_shown = (1 - page_shown); \
	graph_showpage(page_shown); \
	\
	/**
	 * ZUN bloat: Slower than graph_clear(), which uses the GRCG's TDW \
	 * mode and a single REP STOS instruction. \
	 */ \
	grcg_setcolor(GC_RMW, 0); \
	grcg_boxfill_8(0, 0, (RES_X - 1), (RES_Y - 1)); \
	grcg_off(); \
	\
	/** \
	 * ZUN bloat: Doing this in the fade-out branch would have avoided the \
	 * need to reset it for the beginning of the animation. \
	 */ \
	fadeout_frames++; \
	\
	resident->rand++; \
}

// ZUN bloat: These three could have been merged into a single function.
bool near select_1p_vs_2p_menu(void)
{
	select_init_and_load();

	// ZUN bloat: Redundant, already done in select_init_and_load().
	text_clear();

	sel_init_vs();

	if(resident->key_mode == KM_KEY_KEY) {
		input_mode = input_mode_key_vs_key;
	} else if(resident->key_mode == KM_JOY_KEY) {
		input_mode = input_mode_joy_vs_key;
	} else {
		input_mode = input_mode_key_vs_joy;
	}

	// ZUN quirk: Not used in the other modes, and completely unnecessary.
	frame_delay(16);

	fadeout_frames = 0;
	while(1) {
		select_base_render(vs_sel_pics_put);
		cursor_put_p1();
		cursor_put_p2();
		select_input_sense();
		select_update_player(input_mp_p1, 0);
		select_update_player(input_mp_p2, 1);

		if(input_sp & INPUT_CANCEL) {
			return select_cancel();
		}
		if(sel_confirmed[0] && sel_confirmed[1]) {
			select_fadeout_render(done);
		}
		select_wait_flip_and_clear_vram();
	}
done:
	select_free();
	return false;
}

bool near select_vs_cpu_menu(void)
{
	select_init_and_load();
	sel_init_vs();
	input_mode = input_mode_interface;
	for(int pid_cur = 0; pid_cur < PLAYER_COUNT; pid_cur++) {
		fadeout_frames = 0;
		while(1) {
			select_base_render(vs_sel_pics_put);
			select_input_sense();
			cursor_put_p1();
			if(sel_confirmed[0]) {
				cursor_put_p2();
			}
			select_update_player(input_sp, pid_cur);

			if(input_sp & INPUT_CANCEL) {
				return select_cancel();
			}
			if((pid_cur == 0) && sel_confirmed[0] && (fadeout_frames > 12)) {
				break;
			}
			if((pid_cur != 0) && sel_confirmed[1]) {
				select_fadeout_render(done);
			}
			select_wait_flip_and_clear_vram();
		}
done:
	}
	select_free();
	return false;
}

bool near select_story_menu(void)
{
	select_init_and_load();
	sel[0] = PLAYCHAR_REIMU;
	sel_confirmed[0] = false;
	sel_confirmed[1] = true;
	input_mode = input_mode_interface;
	fadeout_frames = 0;
	while(1) {
		select_base_render(story_sel_pics_put);
		cursor_put_p1();
		select_input_sense();
		select_update_player(input_sp, 0);

		if(input_sp & INPUT_CANCEL) {
			return select_cancel();
		}
		if(sel_confirmed[0]) {
			select_fadeout_render(done);
		}
		select_wait_flip_and_clear_vram();
	}
done:
	select_free();
	return false;
}
