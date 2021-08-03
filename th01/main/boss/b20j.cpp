/// Jigoku Stage 20 Boss - Konngara
/// -------------------------------

extern "C" {
#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th01/common.h"
#include "th01/math/area.hpp"
#include "th01/math/subpixel.hpp"
#include "th01/math/vector.hpp"
#include "th01/hardware/frmdelay.h"
#include "th01/hardware/palette.h"
#include "th01/hardware/graph.h"
#include "th01/hardware/egc.h"
#include "th01/hardware/scrollup.hpp"
#include "th01/snd/mdrv2.h"
#include "th01/main/playfld.hpp"
#include "th01/formats/grp.h"
#include "th01/formats/grz.h"
#include "th01/formats/pf.hpp"
#include "th01/formats/ptn.hpp"
#include "th01/formats/stagedat.hpp"
#include "th01/sprites/pellet.h"
#include "th01/sprites/shape8x8.hpp"
#include "th01/main/boss/entity_a.hpp"
#include "th01/main/stage/palette.hpp"
}
#include "th01/main/stage/stageobj.hpp"
#include "th01/main/shape.hpp"
#include "th01/main/player/player.hpp"
#include "th01/main/boss/boss.hpp"
#include "th01/main/boss/palette.hpp"
#include "th01/main/bullet/pellet.hpp"
#include "th01/main/hud/hp.hpp"

// Coordinates
// -----------

static const screen_x_t HEAD_LEFT = 280;
static const screen_y_t HEAD_TOP = 80;
static const screen_x_t FACE_LEFT = 280;
static const screen_y_t FACE_TOP = 128;
// -----------

#define pattern_state	konngara_pattern_state
#define flash_colors	konngara_flash_colors
#define invincible	konngara_invincible
#define invincibility_frame	konngara_invincibility_frame
#define initial_hp_rendered	konngara_initial_hp_rendered
extern union {
	int group; // pellet_group_t
	int interval;
} pattern_state;
extern bool16 invincible;
extern int invincibility_frame;
extern bool initial_hp_rendered;

// Entities
// --------

enum face_direction_t {
	FD_RIGHT = 0,
	FD_LEFT = 1,
	FD_CENTER = 2,
	FD_COUNT = 3,
	FD_UNINITIALIZED = 9, // :zunpet:

	_face_direction_t_FORCE_INT16 = 0x7FFF
};

enum face_expression_t {
	FE_NEUTRAL = 0,
	FE_CLOSED = 1,
	FE_GLARE = 2,
	FE_AIM = 3,

	_face_expression_t_FORCE_INT16 = 0x7FFF
};

extern face_direction_t face_direction;
extern face_expression_t face_expression;
extern bool16 face_direction_can_change;

#define ent_head                	boss_entities[0]
#define ent_face_closed_or_glare	boss_entities[1]
#define ent_face_aim            	boss_entities[2]

#define head_put(direction) \
	ent_head.put_8(HEAD_LEFT, HEAD_TOP, direction);

#define face_aim_put(direction) \
	ent_face_aim.put_8(FACE_LEFT, FACE_TOP, direction);

#define face_put(expression, direction) \
	ent_face_closed_or_glare.put_8( \
		FACE_LEFT, FACE_TOP, (((expression - FE_CLOSED) * FD_COUNT) + direction) \
	);
// --------

// File names
// ----------

// TODO: Inline (if used 1×), or make `const` (if used >1×), once Konngara is
// done
char SCROLL_BG_FN[] = "boss7_d1.grp";
char boss8_a1_grp[] = "boss8_a1.grp";
char ALICE_MDT[] = "ALICE.MDT";
#include "th01/shiftjis/fns.hpp"
char boss8_1_bos[] = "boss8_1.bos";
char boss8_e1_bos[] = "boss8_e1.bos";
char boss8_e2_bos[] = "boss8_e2.bos";
char GRZ_FN[] = "boss8.grz";
char boss8_d1_grp[] = "boss8_d1.grp";
char boss8_d2_grp[] = "boss8_d2.grp";
char boss8_d3_grp[] = "boss8_d3.grp";
char boss8_d4_grp[] = "boss8_d4.grp";
// ----------

#define select_for_rank konngara_select_for_rank
#include "th01/main/select_r.cpp"

void pellet_spawnray_unput_and_put(
	screen_x_t origin_x, vram_y_t origin_y,
	screen_x_t target_x, vram_y_t target_y,
	int col
)
{
	extern screen_x_t target_prev_x;
	extern vram_y_t target_prev_y;
	if(col == 99) {
		target_prev_x = -PIXEL_NONE;
		target_prev_y = -PIXEL_NONE;
		// Umm, shouldn't we unblit in this case?
		return;
	}
	if(
		(target_prev_x != -PIXEL_NONE) && (target_prev_y != -PIXEL_NONE) &&
		(target_prev_x >= 0) && (target_prev_x < RES_X) &&
		(target_prev_y >= 0) && (target_prev_y < RES_Y)
	) {
		graph_r_line_unput(origin_x, origin_y, target_prev_x, target_prev_y);
	}
	if(
		(target_x >= 0) && (target_x < RES_X) &&
		(target_y >= 0) && (target_y < RES_Y)
	) {
		graph_r_line(origin_x, origin_y, target_x, target_y, col);
	}
	target_prev_x = target_x;
	target_prev_y = target_y;
}

// Siddhaṃ seed syllables
// ----------------------

#define SIDDHAM_COL 0x9

inline void siddham_col_white(void) {
	z_palette_set_show(SIDDHAM_COL, 0xF, 0xF, 0xF);
}

#define siddham_col_white_in_step() \
	if(z_Palettes[SIDDHAM_COL].c.r > 0x0) { \
		z_Palettes[SIDDHAM_COL].c.r--; \
	} \
	if(z_Palettes[SIDDHAM_COL].c.g > 0x9) { \
		z_Palettes[SIDDHAM_COL].c.g--; \
	} \
	if(z_Palettes[SIDDHAM_COL].c.b > 0xA) { \
		z_Palettes[SIDDHAM_COL].c.b--; \
	} \
	z_palette_set_all_show(z_Palettes);
// ----------------------

void konngara_load_and_entrance(int8_t)
{
	int i;
	int j;
	int in_quarter;
	int ramp_col;
	int ramp_comp;
	int scroll_frame;

	pellet_interlace = true;

	text_fillca(' ', (TX_BLACK | TX_REVERSE));

	// graph_accesspage_func(0);
	grp_put_palette_show(SCROLL_BG_FN);
	stage_palette_set(z_Palettes);
	stageobjs_init_and_render(BOSS_STAGE);

	graph_accesspage_func(1);
	grp_put_palette_show(boss8_a1_grp);

	graph_accesspage_func(0);
	mdrv2_bgm_load(ALICE_MDT);
	mdrv2_se_load(SE_FN);
	mdrv2_bgm_play();

	z_palette_set_black(j, i);

	text_fillca(' ', TX_WHITE);
	ent_head.load(boss8_1_bos, 0);
	ent_face_closed_or_glare.load(boss8_e1_bos, 1);
	ent_face_aim.load(boss8_e2_bos, 2);

	// Decelerating scroll
	// -------------------

	#define quarters_remaining	i
	#define line_on_top       	j

	line_on_top = 0;
	quarters_remaining = 32; // Should be divisible by 4.
	in_quarter = 0;
	scroll_frame = 0;

	do {
		z_vsync_wait_and_scrollup(line_on_top);
		line_on_top += quarters_remaining;
		if((in_quarter == 0) && (line_on_top > ((RES_Y / 4) * 1))) {
			in_quarter++;
			quarters_remaining--;
		}
		if((in_quarter == 1) && (line_on_top > ((RES_Y / 4) * 2))) {
			in_quarter++;
			quarters_remaining--;
		}
		if((in_quarter == 2) && (line_on_top > ((RES_Y / 4) * 3))) {
			in_quarter++;
			quarters_remaining--;
		}
		if((in_quarter == 3) && (line_on_top > ((RES_Y / 4) * 4))) {
			in_quarter = 0;
			quarters_remaining--;
			line_on_top -= RES_Y;
		}
		if(quarters_remaining <= 0) {
			break;
		}
		if((scroll_frame % 8) == 0) {
			z_palette_black_in_step_to(ramp_col, ramp_comp, grp_palette)
		}
		scroll_frame++;
		frame_delay(1);
	} while(1);

	#undef line_on_top
	#undef quarters_remaining
	// -------------------

	z_vsync_wait_and_scrollup(0);
	grz_load_single(0, GRZ_FN, 0);
	grz_load_single(1, GRZ_FN, 1);
	grz_load_single(2, GRZ_FN, 2);
	grz_load_single(3, GRZ_FN, 3);
	grz_load_single(4, GRZ_FN, 4);
	grz_load_single(5, GRZ_FN, 5);
	grz_load_single(6, GRZ_FN, 6);

	frame_delay(40);

	// Shaking and panning
	// -------------------

	#define MAGNITUDE  	16
	#define frame      	i
	#define line_on_top	j

	// Shake (below)
	for(frame = 0; frame < 32; frame++) {
		z_vsync_wait_and_scrollup(
			(RES_Y + MAGNITUDE) - ((frame % 2) * (MAGNITUDE * 2))
		);
		if((frame % 8) == 0) {
			mdrv2_se_play(9);
		}
		frame_delay(1);
	}

	// "Pan" up to Konngara
	for(line_on_top = RES_Y; line_on_top >= 0; line_on_top -= (MAGNITUDE * 2)) {
		z_vsync_wait_and_scrollup(line_on_top);
		egc_copy_rows_1_to_0(line_on_top, (MAGNITUDE * 2));
		frame_delay(1);
	}

	// Shake
	for(frame = 0; frame < 32; frame++) {
		z_vsync_wait_and_scrollup(
			(RES_Y + MAGNITUDE) - ((frame % 2) * MAGNITUDE)
		);
		frame_delay(1);
	}

	#undef line_on_top
	#undef frame
	#undef MAGNITUDE
	// -------------------

	frame_delay(30);

	// Flashing Siddhaṃ seed syllables
	// -------------------------------

	siddham_col_white();
	grp_put_colorkey(boss8_d1_grp);
	grp_put_colorkey(boss8_d2_grp);
	grp_put_colorkey(boss8_d3_grp);
	grp_put_colorkey(boss8_d4_grp);

	for(j = 0; j < RGB4::Range; j++) {
		siddham_col_white_in_step();
		frame_delay(10);
	}
	graph_copy_page_back_to_front();
	// -------------------------------
}

void konngara_init(void)
{
	boss_palette_snap();
	void konngara_setup();
	konngara_setup();
}

void konngara_setup(void)
{
	boss_hp = 18;
	hud_hp_first_white = 16;
	hud_hp_first_redwhite = 10;
	boss_phase = 0;
	boss_phase_frame = 0;
	face_direction_can_change = true;
	face_expression = FE_NEUTRAL;
	face_direction = FD_CENTER;
}

void konngara_free(void)
{
	bos_entity_free(0);
	bos_entity_free(1);
	bos_entity_free(2);
	for(int i = 0; i < 7; i++) {
		grx_free(i);
	}
}

void face_direction_set_and_put(face_direction_t fd_new)
{
	if(!face_direction_can_change || (face_direction == fd_new)) {
		return;
	}
	graph_accesspage_func(1);	head_put(fd_new);
	graph_accesspage_func(0);	head_put(fd_new);
	if(face_expression == FE_AIM) {
		graph_accesspage_func(1);	face_aim_put(fd_new);
		graph_accesspage_func(0);	face_aim_put(fd_new);
	} else if(face_expression != FE_NEUTRAL) {
		graph_accesspage_func(1);	face_put(face_expression, fd_new);
		graph_accesspage_func(0);	face_put(face_expression, fd_new);
	}
	face_direction = fd_new;
}

void face_expression_set_and_put(face_expression_t fe_new)
{
	if(face_expression == fe_new) {
		return;
	}
	if(fe_new == FE_AIM) {
		graph_accesspage_func(1);	face_aim_put(face_direction);
		graph_accesspage_func(0);	face_aim_put(face_direction);
	} else if(fe_new != FE_NEUTRAL) {
		graph_accesspage_func(1);	face_put(fe_new, face_direction);
		graph_accesspage_func(0);	face_put(fe_new, face_direction);
	} else {
		graph_accesspage_func(1);	head_put(face_direction);
		graph_accesspage_func(0);	head_put(face_direction);
	}
	face_expression = fe_new;
}

void slash_put(int image)
{
	graph_accesspage_func(1);	grx_put(image);
	graph_accesspage_func(0);	grx_put(image);
}

void pattern_diamond_cross_to_edges_followed_by_rain(void)
{
	#define DIAMOND_COUNT 4
	#define DIAMOND_ORIGIN_X (PLAYFIELD_CENTER_X - (DIAMOND_W / 2))
	#define DIAMOND_ORIGIN_Y (PLAYFIELD_CENTER_Y + (DIAMOND_H / 2))

	int i;

	#define diamonds pattern0_diamonds
	extern struct {
		pixel_t velocity_bottomleft_x, velocity_topleft_x;
		pixel_t velocity_bottomleft_y, velocity_topleft_y;
		screen_x_t left[DIAMOND_COUNT];
		screen_y_t top[DIAMOND_COUNT];
	} diamonds;
	extern int frames_with_diamonds_at_edges;

	#define diamonds_unput(i) \
		for(i = 0; i < DIAMOND_COUNT; i++) { \
			shape8x8_sloppy_unput(diamonds.left[i], diamonds.top[i]); \
		}

	#define diamonds_put(i) \
		for(i = 0; i < DIAMOND_COUNT; i++) { \
			shape8x8_diamond_put(diamonds.left[i], diamonds.top[i], 9); \
		}

	if(boss_phase_frame == 10) {
		face_expression_set_and_put(FE_NEUTRAL);
	}
	if(boss_phase_frame < 100) {
		return;
	} else if(boss_phase_frame == 100) {
		// MODDERS: Just use a local variable.
		select_for_rank(pattern_state.group,
			PG_2_SPREAD_NARROW_AIMED,
			PG_3_SPREAD_NARROW_AIMED,
			PG_5_SPREAD_WIDE_AIMED,
			PG_5_SPREAD_NARROW_AIMED
		);

		vector2_between(
			DIAMOND_ORIGIN_X, DIAMOND_ORIGIN_Y,
			PLAYFIELD_LEFT, player_center_y(),
			diamonds.velocity_bottomleft_x, diamonds.velocity_bottomleft_y,
			7
		);
		vector2_between(
			DIAMOND_ORIGIN_X, DIAMOND_ORIGIN_Y,
			PLAYFIELD_LEFT, PLAYFIELD_TOP,
			diamonds.velocity_topleft_x, diamonds.velocity_topleft_y,
			7
		);

		for(i = 0; i < DIAMOND_COUNT; i++) {
			diamonds.left[i] = DIAMOND_ORIGIN_X;
			diamonds.top[i] = DIAMOND_ORIGIN_Y;
		}
		Pellets.add_group(
			(PLAYFIELD_LEFT + (PLAYFIELD_W / 2) - PELLET_W),
			(PLAYFIELD_TOP + playfield_fraction_y(8 / 21.0f) - (PELLET_H / 2)),
			static_cast<pellet_group_t>(pattern_state.group),
			to_sp(3.0f)
		);
		select_for_rank(pattern_state.interval, 18, 16, 14, 12);
		mdrv2_se_play(12);
	} else if(diamonds.left[0] > PLAYFIELD_LEFT) {
		diamonds_unput(i);
		diamonds.left[0] += diamonds.velocity_bottomleft_x;
		diamonds.top[0]  += diamonds.velocity_bottomleft_y;
		diamonds.left[1] -= diamonds.velocity_bottomleft_x;
		diamonds.top[1]  += diamonds.velocity_bottomleft_y;
		diamonds.left[2] += diamonds.velocity_topleft_x;
		diamonds.top[2]  += diamonds.velocity_topleft_y;
		diamonds.left[3] -= diamonds.velocity_topleft_x;
		diamonds.top[3]  += diamonds.velocity_topleft_y;
		if(diamonds.left[0] <= PLAYFIELD_LEFT) {
			diamonds.left[0] = PLAYFIELD_LEFT;
			diamonds.left[2] = PLAYFIELD_LEFT;
			diamonds.left[1] = (PLAYFIELD_RIGHT - DIAMOND_W);
			diamonds.left[3] = (PLAYFIELD_RIGHT - DIAMOND_W);
		} else {
			diamonds_put(i);
		}
		return;
	} else if(diamonds.top[0] > PLAYFIELD_TOP) {
		diamonds_unput(i);
		diamonds.top[0] -= 3;
		diamonds.top[1] -= 3;
		diamonds.left[2] += 6;
		diamonds.left[3] -= 6;
		if(diamonds.top[0] <= PLAYFIELD_TOP) {
			diamonds.top[0] = PLAYFIELD_TOP;
		} else {
			diamonds_put(i);
		}
		return;
	} else if(frames_with_diamonds_at_edges < 200) {
		frames_with_diamonds_at_edges++;
		if((frames_with_diamonds_at_edges % pattern_state.interval) == 0)  {
			#define speed to_sp(2.5f)
			screen_x_t from_left;
			screen_y_t from_top;
			screen_x_t to_left;
			screen_y_t to_top;
			unsigned char angle;

			from_left = PLAYFIELD_LEFT;
			from_top = (PLAYFIELD_TOP + playfield_rand_y(25 / 42.0f));
			// Should actually be
			// 	to_left = (PLAYFIELD_RIGHT - playfield_rand_x(5 / 8.0f));
			to_left = (PLAYFIELD_LEFT +
				playfield_rand_x(5 / 8.0f) + playfield_fraction_x(3 / 8.0f)
			);
			to_top = PLAYFIELD_BOTTOM;
			angle = iatan2((to_top - from_top), (to_left - from_left));
			Pellets.add_single(from_left, from_top, angle, speed, PM_NORMAL);

			from_left = (PLAYFIELD_RIGHT - PELLET_W);
			from_top = (PLAYFIELD_TOP + playfield_rand_y(25 / 42.0f));
			to_left = (PLAYFIELD_LEFT + playfield_rand_x( 5 /  8.0f));
			to_top = PLAYFIELD_BOTTOM;
			angle = iatan2((to_top - from_top), (to_left - from_left));
			Pellets.add_single(from_left, from_top, angle, speed, PM_NORMAL);

			from_top = PLAYFIELD_TOP;
			from_left = (PLAYFIELD_LEFT + playfield_rand_x());
			to_top = PLAYFIELD_BOTTOM;
			to_left = (PLAYFIELD_LEFT + playfield_rand_x());
			angle = iatan2((to_top - from_top), (to_left - from_left));
			Pellets.add_single(from_left, from_top, angle, speed, PM_NORMAL);

			from_top = PLAYFIELD_TOP;
			from_left = (PLAYFIELD_LEFT + playfield_rand_x());
			to_top = PLAYFIELD_BOTTOM;
			to_left = (PLAYFIELD_LEFT + playfield_rand_x());
			angle = iatan2((to_top - from_top), (to_left - from_left));
			Pellets.add_single(from_left, from_top, angle, speed, PM_NORMAL);

			from_top = PLAYFIELD_TOP;
			from_left = (PLAYFIELD_LEFT + playfield_rand_x());
			Pellets.add_group(from_left, from_top, PG_1_AIMED, speed);

			#undef speed
		}
		return;
	} else {
		boss_phase_frame = 0;
	}
	frames_with_diamonds_at_edges = 0;

	#undef diamonds_put
	#undef diamonds_unput
	#undef diamonds
	#undef DIAMOND_ORIGIN_Y
	#undef DIAMOND_ORIGIN_X
	#undef DIAMOND_COUNT
}

char konngara_esc_cls[] = "\x1B*";
char konngara_esc_mode_graph[] = "\x1B)3";
char konngara_esc_color_bg_black_fg_black[] = "\x1B[16;40m";
char konngara_esc_cursor_to_x0_y0_0[] = "\x1B[0;0H";
char konngara_space[] = " ";
char konngara_esc_mode_kanji[] = "\x1B)0";
char konngara_esc_color_reset[] = "\x1B[0m";
char konngara_esc_cursor_to_x0_y0_1[] = "\x1B[1;1H";
