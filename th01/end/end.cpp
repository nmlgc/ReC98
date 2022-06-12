#pragma option -O- -1 -Z-

#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "twobyte.h"
#include "master.hpp"
#include "th01/common.h"
#include "th01/rank.h"
#include "th01/resident.hpp"
#include "th01/v_colors.hpp"
extern "C" {
#include "th01/hardware/frmdelay.h"
#include "th01/hardware/input.hpp"
#include "th01/hardware/graph.h"
#include "th01/hardware/grppsafx.h"
#include "th01/hardware/palette.h"
#include "th01/snd/mdrv2.h"
#include "th01/formats/grp.h"
#include "th01/hiscore/scoredat.hpp"
}
#include "th01/hiscore/regist.hpp"
#include "th01/end/end.hpp"
#include "th01/end/pic.hpp"
#include "th01/end/type.hpp"
#include "th01/end/vars.hpp"
#include "th01/shiftjis/end.hpp"
#include "th01/shiftjis/regist.hpp"
#include "th01/shiftjis/title.hpp"

// > rendering text to VRAM, where it wouldn't be limited to the byte grid
// > still aligning it to the byte grid
inline void pic_caption_type_n(int line, size_t len, const char str[]) {
	graph_type_ank_n(
		(((RES_X / 2) - ((len * GLYPH_HALF_W) / 2) + BYTE_MASK) & ~BYTE_MASK),
		(PIC_BOTTOM + (((line * 2) + 1) * GLYPH_H)),
		len,
		str
	);
}

// MODDERS: Remove the [incorrect_extra_w] parameter.
#define pic_caption_type_2(line_1, line_2, incorrect_extra_w) { \
	/* ZUN bug: This accesses one extra byte for the "STAGE 5 BOSS" string. \
	 * Which, luckily, happens to be the null terminator, and doesn't have \
	 * any visible effect. */ \
	pic_caption_type_n(0, (sizeof(line_1) - 1 + incorrect_extra_w), line_1); \
	\
	pic_caption_type_n(1, (sizeof(line_2) - 1 + incorrect_extra_w), line_2); \
}

/// Endings
/// -------

static const int FINAL_DELAY_FRAMES = 300;

// Function ordering fails
// -----------------------

void near end_good_makai(void);
void near end_good_jigoku(void);
// -----------------------

#define end_pic_show_and_delay(quarter, delay_frames) { \
	end_pic_show(quarter); \
	frame_delay(delay_frames); \
}

#define end_pic_white_in_and_delay(quarter, white_in_speed, delay_frames) { \
	end_pic_show(quarter); \
	grp_palette_white_in(white_in_speed); \
	frame_delay(delay_frames); \
}

void near end_good(void)
{
	enum {
		WHITE_IN_STEP = 5,
		WHITE_OUT_STEP = 10,
	};

	int i;

	end_pics_load_palette_show("ed3a.grp");

	grp_palette_settone(200);
	for(i = 0; i < ((200 - 100) / WHITE_IN_STEP); i++) {
		end_pic_show_and_delay(0, 8);
		end_pic_show_and_delay(1, 8);
		grp_palette_settone(200 - (i * WHITE_IN_STEP));
	}
	grp_palette_settone(100);

	for(i = 0; i < 10; i++) {
		end_pic_show_and_delay(0, 8);
		end_pic_show_and_delay(1, 8);
	}

	for(i = 0; i < ((200 - 100) / WHITE_OUT_STEP); i++) {
		end_pic_show_and_delay((i & 1), 8);
		grp_palette_settone(100 + (i * WHITE_OUT_STEP));
	}
	grp_palette_settone(200);

	if(end_flag == ES_MAKAI) {
		end_good_makai();
	} else {
		end_good_jigoku();
	}
}

void near end_good_jigoku(void)
{
	end_pics_load_palette_show("ed3b.grp");
	end_pic_white_in_and_delay(0, 4, 250);
	end_pic_show_and_delay(1, 200);
	end_pic_show_and_delay(2, 150);
	end_pic_show_and_delay(3, 150);
	pic_caption_type_2(END_GOOD_LINE_1, END_GOOD_LINE_2_JIGOKU, 0);
	frame_delay(FINAL_DELAY_FRAMES);
}

void near end_good_makai(void)
{
	end_pics_load_palette_show("ed5a.grp");
	end_pic_white_in_and_delay(0, 4, 300);

	for(int i = 0; i < 15; i++) {
		end_pic_show_and_delay(1, 8);
		end_pic_show_and_delay(2, 8);
	}

	end_pics_load_palette_show("ed5b.grp");
	end_pic_show_and_delay(0, 150);
	end_pic_show_and_delay(1, 100);
	end_pic_show_and_delay(2, 100);
	end_pic_show_and_delay(3, 100);

	end_pics_load_palette_show("ed5c.grp");
	end_pic_show_and_delay(0, 100);
	end_pic_show_and_delay(1, 150);
	end_pic_show_and_delay(2, 150);
	pic_caption_type_2(END_GOOD_LINE_1, END_GOOD_LINE_2_MAKAI, 0);
	frame_delay(FINAL_DELAY_FRAMES);
}
/// -------

/// Boss slideshow
/// --------------

static const int BOSS_SLIDE_DELAY = 150;
static const int BOSS_TEXT_DELAY = 50;

void near pascal boss_slide_next(int quarter)
{
	frame_delay(BOSS_SLIDE_DELAY);
	grp_palette_black_out(5);
	z_graph_clear();
	end_pic_show(quarter);
	grp_palette_black_in(5);
	frame_delay(BOSS_TEXT_DELAY);
}

void near boss_slides_animate(void)
{
	mdrv2_bgm_fade_out_nonblock();
	grp_palette_black_out(10);

	z_graph_clear();
	mdrv2_bgm_stop();
	mdrv2_bgm_load("st1.mdt");
	mdrv2_bgm_play();

	if(end_flag == ES_MAKAI) {
		end_pics_load_palette_show("endb_a.grp");
	} else {
		end_pics_load_palette_show("endb_b.grp");
	}
	end_pic_show(0);
	grp_palette_settone(100);
	frame_delay(BOSS_TEXT_DELAY);

	// ZUN calculated with one extra character? Was this character originally
	// called "ShinGyoku" after all?!
	pic_caption_type_2(SLIDES_TITLE_5, SLIDES_BOSS_5, 1);

	boss_slide_next(1);
	if(end_flag == ES_MAKAI) {
		pic_caption_type_2(SLIDES_TITLE_10, SLIDES_BOSS_10_MAKAI, 0);
	} else {
		pic_caption_type_2(SLIDES_TITLE_10, SLIDES_BOSS_10_JIGOKU, 0);
	}

	boss_slide_next(2);
	if(end_flag == ES_MAKAI) {
		pic_caption_type_2(SLIDES_TITLE_15, SLIDES_BOSS_15_MAKAI, 0);
	} else {
		pic_caption_type_2(SLIDES_TITLE_15, SLIDES_BOSS_15_JIGOKU, 0);
	}

	boss_slide_next(3);
	if(end_flag == ES_MAKAI) {
		pic_caption_type_2(SLIDES_TITLE_20, SLIDES_BOSS_20_MAKAI, 0);
	} else {
		pic_caption_type_2(SLIDES_TITLE_20, SLIDES_BOSS_20_JIGOKU, 0);
	}

	frame_delay(BOSS_SLIDE_DELAY);
}
/// --------------

/// Verdict screen
/// --------------

static const int16_t FX_TITLE = (FX_WEIGHT_HEAVY | 2);

// Coordinates
// -----------

static const screen_x_t VERDICT_LEFT = 296;
static const screen_x_t VERDICT_GAME_RIGHT = (
	VERDICT_LEFT + VERDICT_W - shiftjis_w("  ")
);
static const screen_x_t VERDICT_GAME_VERSION_LEFT = (
	VERDICT_GAME_RIGHT - shiftjis_w(GAME_VERSION)
);
static const screen_x_t VERDICT_GAME_VER_LEFT = (
	VERDICT_GAME_VERSION_LEFT - shiftjis_w(GAME_VER " ")
);
static const screen_x_t VERDICT_GAME_TITLE_LEFT = (
	VERDICT_GAME_VER_LEFT - shiftjis_w(GAME_TITLE "  ")
);

inline screen_y_t verdict_line_top(int i) {
	return (i * (GLYPH_H * 2));
}
// -----------

// Both of these needlessly print stuff to VRAM.
#define verdict_line_render0(i, str) { \
	graph_printf_fx(VERDICT_LEFT, verdict_line_top(i), COL_TYPE, str); \
	frame_delay(30); \
}
#define verdict_line_render1(i, fmt, arg) { \
	graph_printf_fx(VERDICT_LEFT, verdict_line_top(i), COL_TYPE, fmt, arg); \
	frame_delay(30); \
}

void verdict_title_calculate_and_render(void)
{
	int skill = 0;
	int level;

	// skill += ((min(max(score, 0), 2500000) / 500000) * 2);
	/**/ if(score >= 2500000) { skill += 10; }
	else if(score >= 2000000) { skill +=  8; }
	else if(score >= 1500000) { skill +=  6; }
	else if(score >= 1000000) { skill +=  4; }
	else if(score >=  500000) { skill +=  2; }

	// skill += (
	// 	((min(max(score_highest, 0), 3000000) - 1000000) / 400000) * 2
	// );
	/**/ if(score_highest >= 3000000) { skill += 10; }
	else if(score_highest >= 2600000) { skill +=  8; }
	else if(score_highest >= 2200000) { skill +=  6; }
	else if(score_highest >= 1800000) { skill +=  4; }
	else if(score_highest >= 1400000) { skill +=  2; }

	// skill += ((continues_total == 0) * 18 + (
	// 	(12 - min(max(continues_total, 0), 22)) / 2) * 2)
	// ));
	/**/ if(continues_total ==  0u) { skill += 30; }
	else if(continues_total <=  2u) { skill += 10; }
	else if(continues_total <=  4u) { skill +=  8; }
	else if(continues_total <=  6u) { skill +=  6; }
	else if(continues_total <=  8u) { skill +=  4; }
	else if(continues_total <= 10u) { skill +=  2; }
	else if(continues_total <= 12u) {}
	else if(continues_total <= 14u) { skill -=  2; }
	else if(continues_total <= 16u) { skill -=  4; }
	else if(continues_total <= 18u) { skill -=  6; }
	else if(continues_total <= 20u) { skill -=  8; }
	else /*                      */ { skill -= 10; }

	/**/ if(rank == RANK_LUNATIC) { skill += 50; }
	else if(rank ==    RANK_HARD) { skill += 30; }
	else if(rank ==  RANK_NORMAL) { skill += 10; }
	else if(rank ==    RANK_EASY) { skill -= 10; }

	/**/ if(end_flag == ES_JIGOKU) { skill += 5; }

	// skill += ((-5 * min(max(start_lives_extra, 0), 4)) + 10);
	/**/ if(start_lives_extra == 4) { skill -= 10; }
	else if(start_lives_extra == 3) { skill -=  5; }
	else if(start_lives_extra == 1) { skill +=  5; }
	else if(start_lives_extra == 0) { skill += 10; }

	int group = (rand() % VERDICT_GROUPS);

	// level = max((min(skill, 80) + 20) / 20), 0);
	/**/ if(skill >= 80) { level = 5; }
	else if(skill >= 60) { level = 4; }
	else if(skill >= 40) { level = 3; }
	else if(skill >= 20) { level = 2; }
	else if(skill >=  0) { level = 1; }
	else /*          */ { level = 0; }

	graph_printf_fx(
		(VERDICT_LEFT - VERDICT_TITLE_LEFT_OFFSET + VERDICT_TITLE_PADDED_W),
		verdict_line_top(12),
		FX_TITLE,
		"%s\0 EASY \0NORMAL\0 HARD \0LUNATIC",
		VERDICT_TITLES[group][level]
	);
}

void verdict_animate_and_regist(void)
{
	struct hack { const char *str[RANK_COUNT]; }; // XXX
	extern const hack ranks;

	struct hack RANKS = ranks;

	grp_palette_black_out(10);

	graph_accesspage_func(1);
	grp_put_palette_show("endm_a.grp");
	graph_copy_accessed_page_to_other();

	graph_accesspage_func(0);
	grp_palette_black_in(8);

	graph_type_kanji(VERDICT_GAME_TITLE_LEFT, verdict_line_top(1), GAME_TITLE);
	graph_type_ank(VERDICT_GAME_VER_LEFT, verdict_line_top(1), GAME_VER);
	graph_type_ank(
		VERDICT_GAME_VERSION_LEFT, verdict_line_top(1), GAME_VERSION
	);
	frame_delay(30);

	verdict_line_render1(2, VERDICT_RANK"%s", RANKS.str[rank]);

	// Should really all be %10lu (with the superflous right-padding removed
	// from the strings) if you're already using `long`s here. Scoreplayers
	// can definitely reach 8 digits.
	verdict_line_render1(3, VERDICT_SCORE_HIGHEST"%7lu", score_highest);
	verdict_line_render1(4, VERDICT_SCORE"%7lu", score);

	verdict_line_render0(5, VERDICT_SCENE_CONTINUES);

	// Same here, technically. Would require a layout change to make room for
	// that many halfwidth characters, though… and seriously, who continues
	// more than a 3-digit number of times *per scene*?
	verdict_line_render1(6, VERDICT_SHRINE"%3lu", continues_per_scene[0]);
	if(end_flag == ES_MAKAI) {
		verdict_line_render1(7, VERDICT_MAKAI_1"%3lu", continues_per_scene[1]);
	} else {
		verdict_line_render1(7, VERDICT_JIGOKU_1"%3lu", continues_per_scene[1]);
	}
	if(end_flag == ES_MAKAI) {
		verdict_line_render1(8, VERDICT_MAKAI_2"%3lu", continues_per_scene[2]);
	} else {
		verdict_line_render1(8, VERDICT_JIGOKU_2"%3lu", continues_per_scene[2]);
	}
	if(end_flag == ES_MAKAI) {
		verdict_line_render1(9, VERDICT_MAKAI_3"%3lu", continues_per_scene[3]);
	} else {
		verdict_line_render1(9, VERDICT_JIGOKU_3"%3lu", continues_per_scene[3]);
	}
	if(end_flag == ES_MAKAI) {
		verdict_line_render1(10, VERDICT_MAKAI_TOTAL"%5lu", continues_total);
	} else {
		verdict_line_render1(10, VERDICT_JIGOKU_TOTAL"%5lu", continues_total);
	}

	graph_type_ank(VERDICT_LEFT, verdict_line_top(11), VERDICT_THANKYOU);

	graph_printf_fx(
		(VERDICT_LEFT - VERDICT_TITLE_LEFT_OFFSET),
		verdict_line_top(12),
		FX_TITLE,
		VERDICT_TITLE
	);
	frame_delay(50);

	verdict_title_calculate_and_render();

	int timeout = 0;
	frame_delay(100);
	input_reset_sense();
	while(!(((timeout++) >= 2000) || input_ok || input_shot)) {
		input_sense(false);
		frame_delay(1);
	}

	// Unblit all text
	graph_accesspage_func(1);
	graph_copy_accessed_page_to_other();
	graph_accesspage_func(0);

	grp_palette_settone(50);
	regist_colors_set();
	if(end_flag == ES_MAKAI) {
		regist(score, SCOREDAT_CLEARED_MAKAI, REGIST_ROUTE_CLEAR);
	} else {
		regist(score, SCOREDAT_CLEARED_JIGOKU, REGIST_ROUTE_CLEAR);
	}
	end_resident_clear();
}
/// --------------
