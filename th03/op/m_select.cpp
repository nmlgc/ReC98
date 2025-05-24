/// Character selection menu
/// ------------------------

#pragma option -zPgroup_01

#include "th03/op/m_select.hpp"
#include "platform/grp_mono.hpp"
#include "platform/x86real/pc98/page.hpp"
#include "libs/master.lib/master.hpp"
#include "libs/master.lib/pc98_gfx.hpp"
#include "th01/math/clamp.hpp"
#include "th01/math/polar.hpp"
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
resident_t far* resident; // ZUN bloat: Why is this here?
static playchar_t sel[PLAYER_COUNT];
static bool sel_confirmed[PLAYER_COUNT];
static page_t page_shown;
func_t_near input_mode; // ZUN bloat: Why is this here?
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
	static_assert(PLAYCHAR_COUNT >= 6);
	for(int i = 3; i < 6; i++) {
		cdg_load_single((CDG_PIC + i), PLAYCHAR_PIC_FN[i], 0);
	}
}

void near select_cdg_load_part4_of_4(void)
{
	static_assert(PLAYCHAR_COUNT <= 9);
	for(int i = 6; i < 9; i++) {
		cdg_load_single((CDG_PIC + i), PLAYCHAR_PIC_FN[i], 0);
	}
}

void near select_init_and_load(void)
{
	snd_kaja_func(KAJA_SONG_STOP, 0);
	snd_load("select.m", SND_LOAD_SONG);
	snd_kaja_func(KAJA_SONG_PLAY, 0);

	random_seed = resident->rand;

	// We come here with page 0 accessed. Clear the other one for a clean
	// transition.
	page_access(1);
	graph_clear();
	frame_delay(1);

	palette_settone(0);
	page_show(1);
	page_access(0);
	page_shown = 1;
	text_clear();

	super_free();
	super_entry_bfnt("chname.bft");
	palette_entry_rgb("TLSL.RGB");
	select_cdg_load_part4_of_4();

	palette_100();

	// ZUN bug: Since we wait 30 frames on the first loop, we're only ever
	// going to actually see 8 trailing curves on the first iteration. At its
	// end, this count is decremented because 30 > 4.
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

void pascal near stat_star_row_put(pid_t pid, screen_y_t row_top, int stat_i)
{
	int star_i = 5;
	screen_x_t star_left = (((pid == 0) ? P1_LEFT : P2_LEFT) + STATS_W - 20);
	while(PLAYCHAR_STATS[sel[pid]][stat_i] < star_i) {
		grcg_boxfill(
			star_left,
			row_top,
			(star_left + STAT_STAR_W - 1),
			(row_top + STAT_STAR_H -1)
		);
		star_i--;
		star_left -= STAT_STAR_PADDED_W;
	}
}

void near stats_put(void)
{
	cdg_put_noalpha_8(P1_LEFT, STATS_TOP, CDG_STATS);
	if(resident->game_mode != GM_STORY) {
		cdg_put_noalpha_8(P2_LEFT, STATS_TOP, CDG_STATS);
	}

	grcg_setcolor(GC_RMW, 14);
	screen_y_t row_top = (STATS_TOP + 11);
	for(int stat_i = 0; stat_i < STAT_COUNT; stat_i++) {
		stat_star_row_put(0, row_top, stat_i);
		if(resident->game_mode != GM_STORY) {
			stat_star_row_put(1, row_top, stat_i);
		}
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
typedef uint16_t freq_t;
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
	GrpMono& gm,
	unsigned char angle_offset_x,
	unsigned char angle_offset_y,
	pixel_t radius,
	freq_t freq_x,
	freq_t freq_y
)
{
	unsigned int angle_base;
	for(angle_base = 0x00; angle_base < 0x100; angle_base++) {
		// It might not look like it, but this code is indeed affected by the
		// inaccuracy for negative sine and cosine values documented in
		// th01/math/polar.hpp, as the result of multiplying the offset angle
		// with [freq_x] or [freq_y] can overflow into negative numbers. To
		// retain the exact pixels, we must ensure that
		// 1) angle + offset is truncated to 8 bits, and
		// 2) [scaled_angle] / [FREQ_FACTOR] rounds toward zero despite
		//    shifting.
		int scaled_angle;

		// Calculate Y first, since the coordinate can fall outside of VRAM.
		// If that happens, we don't even have to calculate X.
		scaled_angle = (
			static_cast<unsigned char>(angle_base + angle_offset_y) * freq_y
		);
		if(scaled_angle < 0) {
			// Casting avoids an unnecessary register spill here...
			scaled_angle += static_cast<int>(FREQ_FACTOR - 1);
		}
		screen_y_t y = polar_y_fast(
			(RES_Y / 2), radius, (scaled_angle / FREQ_FACTOR)
		);
		if(static_cast<uscreen_x_t>(y) >= RES_Y) {
			continue;
		}

		scaled_angle = (
			static_cast<unsigned char>(angle_base + angle_offset_x) * freq_x
		);
		if(scaled_angle < 0) {
			// Casting avoids an unnecessary register spill here...
			scaled_angle += static_cast<int>(FREQ_FACTOR - 1);
		}
		screen_x_t x = polar_x_fast(
			(RES_X / 2), radius, (scaled_angle / FREQ_FACTOR)
		);

		gm.draw_point_noclip(x, y);
	}
}

struct curve_freqs_t {
	freq_t x;
	freq_t y;
	freq_t other;
};

void pascal near select_curves_put(
	GrpMono& gm, unsigned char offset, const curve_freqs_t& freqs
)
{
	// ZUN quirk: A diameter of (220 × 2) = 440 pixels is larger than the
	// vertical resolution, thus cutting off several pixels.
	curve_put(
		gm,
		(curve_cycle - (offset * 2)),
		((curve_cycle * 2) - (offset * 4)),
		220,
		freqs.other,
		freqs.y
	);

	// ZUN quirk: Halving the Y angle offset restricts this smaller curve to
	// only the first half of the sine oscillation. This is fine as long as we
	// don't subtract the trail [offset]. But once we do, the resulting Y
	// offset wraps around into the other half of the oscillation at
	//
	// 	([curve_cycle] ≤ ([curve_trail_count] * 2))
	//
	// This causes the discontinuity between the start and end of the cycle
	// as the trailing curves during the first [curve_trail_count] frames
	// appear flipped compared to their counterparts at the end of the cycle.
	// Removing the division would be the easiest fix here; the second-easiest
	// fix would be to restrict the subtraction to the first half of the
	// oscillation:
	//
	// 	(((curve_cycle / 2) - offset) & 0x7F)
	//
	curve_put(
		gm,
		((0x00 - curve_cycle) + (offset * 2)),
		((curve_cycle / 2) - offset),
		120,
		freqs.x,
		freqs.other
	);
}

// Desmos plot of the full effect:
//
// 	https://www.desmos.com/calculator/sstcw9ru5x?invertedColors=true
void near select_curves_update_and_render(void)
{
	int trail_count_half;
	int i;

	freq_t cycle_triangle = curve_cycle;
	if(cycle_triangle >= 0x80) {
		cycle_triangle = (0x100 - cycle_triangle);
	}

	curve_freqs_t freqs;
	freqs.other = (FREQ_FACTOR + (1 * cycle_triangle));
	freqs.x = (FREQ_FACTOR + (2 * cycle_triangle));
	freqs.y = ((2 * FREQ_FACTOR) + (2 * cycle_triangle));

	// ZUN quirk: Maybe these should be blitted in the opposite order? Due to
	// the different colors, this causes the trailing curves to appear on top
	// of the main one.
	GrpMono gm;
	gm.set_color_static(6);
	select_curves_put(gm, 0, freqs);

	gm.set_color_static(5);
	trail_count_half = (curve_trail_count / 2);
	if(curve_trail_count & 1) {
		trail_count_half++;
	}
	for(i = 1; i <= trail_count_half; i++) {
		select_curves_put(gm, i, freqs);
	}

	gm.set_color_static(1);
	for(i = (trail_count_half + 1); i <= curve_trail_count; i++) {
		select_curves_put(gm, i, freqs);
	}

	curve_cycle += 0x02;
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

void pascal near select_confirm(pid_t pid, bool palette_id)
{
	playchar_t playchar = sel[pid];
	resident->playchar_paletted[pid].set(playchar, palette_id);
	palette_white_in(1);

	static_assert(PLAYER_COUNT == 2);
	if(sel_confirmed[1 - pid] && (
		resident->playchar_paletted[0].v == resident->playchar_paletted[1].v
	)) {
		palette_id ^= 1;
		resident->playchar_paletted[pid].set(playchar, palette_id);
	}
	cdg_load_single(
		(CDG_PIC_SELECTED + pid), PLAYCHAR_PIC_FN[playchar], palette_id
	);

	static_assert(PLAYER_COUNT == 2);
	sel_confirmed[pid] = true;
	input_locked[pid] = true;
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
		select_confirm(pid, 0);
	}
	if(input & INPUT_BOMB) {
		select_confirm(pid, 1);
	}
}

bool near select_menu(select_mode_t mode)
{
	pid_t sp_pid = 0;
	unsigned int p1_quirk_frames = 0;

	select_init_and_load();

	for(int player = 0; player < PLAYER_COUNT; player++) {
		sel[player] = resident->playchar_paletted[player].char_id();
		sel_confirmed[player] = false;
	}
	input_mode = input_mode_interface;

	// ZUN bug: Is this supposed to be long enough for the player to release
	// the Shot key that might have entered this menu? If that was the intent,
	// the menu functions should properly lock input until the player released
	// that key. Keep holding the Shot key for more than 30 frames and the
	// menus will still confirm the initial selection on their first frame.
	// The menu needs [input_locked] anyway; why isn't it set here?!
	unsigned int vsyncs_per_loop = 30;

	if(mode == SM_STORY) {
		sel[0] = PLAYCHAR_REIMU;
		sel_confirmed[1] = true;
	} else if(mode == SM_VS_2P) {
		if(resident->key_mode == KM_KEY_KEY) {
			input_mode = input_mode_key_vs_key;
		} else if(resident->key_mode == KM_JOY_KEY) {
			input_mode = input_mode_joy_vs_key;
		} else {
			input_mode = input_mode_key_vs_joy;
		}

		// ZUN quirk: Completely unnecessary.
		vsyncs_per_loop += 16;
	}

	// This copy of the delay loop is necessary to delay input processing
	// during the initial delay time. Note how we *don't* reset [vsync_Count1]
	// to 0 to preserve the intended trail count subtraction on the first
	// iteration.
	while(vsync_Count1 < vsyncs_per_loop) {
	}

	unsigned int fadeout_frames = 0;
	while(1) {
		graph_clear();
		select_curves_update_and_render();
		if(mode == SM_STORY) {
			story_sel_pics_put();
		} else {
			vs_sel_pics_put();
		}
		stats_put();
		names_put();
		extras_put();
		cursor_put(0, (sel_confirmed[0] ? V_WHITE : 8));
		if((mode == SM_VS_2P) || ((mode == SM_VS_CPU) && sel_confirmed[0])) {
			cursor_put(1, (sel_confirmed[1] ? V_WHITE : 10));
		}
		input_mode();
		switch(mode) {
		case SM_STORY:
			select_update_player(input_sp, 0);
			break;
		case SM_VS_CPU:
			select_update_player(input_sp, sp_pid);
			break;
		case SM_VS_2P:
			select_update_player(input_mp_p1, 0);
			select_update_player(input_mp_p2, 1);
			break;
		}

		if(input_sp & INPUT_CANCEL) {
			// ZUN bloat: palette_settone(0) is a more performant way to
			// achieve the same without raising any questions about whether
			// this targets the correct VRAM page.
			graph_accesspage(0);
			graph_clear();
			graph_showpage(0);

			// Redundant in the released game, but makes sense for clearing
			// potential debug output.
			text_clear();

			select_free();
			snd_kaja_func(KAJA_SONG_STOP, 0);
			return true;
		}

		// ZUN quirk: Prevents selection from moving on to P2 before frame
		// #13? This is a delay for its own sake; input locking already
		// takes care of the one functional side effect it could have had.
		if((mode == SM_VS_CPU) && (sp_pid == 0)) {
			if(sel_confirmed[0] && (p1_quirk_frames > 12)) {
				sp_pid = 1;
				continue;
			}
			p1_quirk_frames++;
		}

		// Well, the original game also processed all the input on the 33th
		// frame, most importantly including INPUT_CANCEL...
		if(fadeout_frames > 32) {
			break;
		}

		const unsigned int frame_duration = vsync_Count1;
		while(vsync_Count1 < vsyncs_per_loop) {
		}

		if((vsync_Count1 > 4) && (curve_trail_count > 1)) {
			curve_trail_count--;
		}

		// If we went straight past the loop above, we're still in the middle
		// of a frame. So, wait until the next VSync, then cut this additional
		// frame from the next loop to maintain the original timing… *unless*
		// we're on the very first iteration (where [vsyncs_per_loop] ≥ 30)
		// where this case is expected. Very relevant if we consider that
		// palette_white_in() increments [vsync_Count1] during its whole
		// blocking runtime!
		if(frame_duration == vsync_Count1) {
			frame_delay(1);
			vsyncs_per_loop = ((vsyncs_per_loop >= 30) ? 3 : 2);
		} else {
			vsyncs_per_loop = 3;
		}

		vsync_Count1 = 0;
		graph_accesspage(page_shown);
		page_shown = (1 - page_shown);
		graph_showpage(page_shown);

		if(sel_confirmed[0] && sel_confirmed[1]) {
			// Since we moved this branch from before VSync to after VSync to
			// fix tearing, we need to increment first to avoid the fade being
			// one frame behind.
			fadeout_frames++;

			// ZUN quirk: Should have maybe been `>` rather than `>=`. Since
			// [fadeout_frames] is technically off-by-one (frame 0 is the last
			// frame of palette_white_in()), this sets the palette tone to 104
			// on frame #15.
			if(fadeout_frames >= 16) {
				palette_settone(200 - (fadeout_frames * 6));
			}
		}

		resident->rand++;
	}
	select_free();
	return false;
}
