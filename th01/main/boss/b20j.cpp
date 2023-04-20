/// Jigoku Stage 20 Boss - Konngara
/// -------------------------------

#include <stdio.h>
#include "platform.h"
#include "x86real.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "platform/x86real/pc98/egc.hpp"
#include "th01/rank.h"
#include "th01/resident.hpp"
#include "th01/v_colors.hpp"
#include "th01/math/area.hpp"
#include "th01/math/overlap.hpp"
#include "th01/math/subpixel.hpp"
#include "th01/math/vector.hpp"
#include "th01/hardware/frmdelay.h"
#include "th01/hardware/palette.h"
#include "th01/hardware/graph.h"
#include "th01/hardware/egc.h"
#include "th01/hardware/scrollup.hpp"
#include "th01/hardware/text.h"
#include "th01/snd/mdrv2.h"
#include "th01/formats/grp.h"
#include "th01/formats/grz.h"
#include "th01/formats/ptn.hpp"
#include "th01/formats/stagedat.hpp"
#include "th01/sprites/pellet.h"
#include "th01/sprites/shape8x8.hpp"
#include "th01/main/entity.hpp"
#include "th01/main/playfld.hpp"
#include "th01/main/spawnray.hpp"
#include "th01/main/stage/palette.hpp"
#include "th01/main/stage/stageobj.hpp"
#include "th01/main/stage/stages.hpp"
#include "th01/main/shape.hpp"
#include "th01/main/player/player.hpp"
#include "th01/main/player/orb.hpp"
#include "th01/main/player/shot.hpp"
#include "th01/main/boss/boss.hpp"
#include "th01/main/boss/entity_a.hpp"
#include "th01/main/boss/palette.hpp"
#include "th01/main/bullet/pellet.hpp"
#include "th01/main/bullet/laser_s.hpp"
#include "th01/main/hud/hp.hpp"

static const char* unused_entrance_letters_maybe[] = { "ANGEL", "OF", "DEATH" };

// Coordinates
// -----------

static const screen_x_t HEAD_LEFT = 280;
static const screen_y_t HEAD_TOP = 80;
static const screen_x_t FACE_LEFT = 280;
static const screen_y_t FACE_TOP = 128;
static const screen_x_t CUP_LEFT = 296;
static const screen_y_t CUP_TOP = 188;
static const screen_x_t LEFT_SLEEVE_LEFT = 290;
static const screen_y_t LEFT_SLEEVE_TOP = 200;
static const screen_x_t EYE_CENTER_X = 316;
static const screen_y_t EYE_BOTTOM = 140;

static const screen_x_t HITBOX_LEFT = 288;
static const screen_y_t HITBOX_TOP = 120;

// Including the respective sprites:
//
// 	               [w]
// 	    ┌───────────────────────┐
// 	    │                       │
// 	[h] │                       │
// 	    │             sprite → ┌┤
// 	    └──────────────────────┴┘
//
static const pixel_t HITBOX_SHOT_W = 112;
static const pixel_t HITBOX_SHOT_H = 56;
static const pixel_t HITBOX_ORB_W = 96;
static const pixel_t HITBOX_ORB_H = 72;

// Slash pattern spawners are moved on a triangle along these points.
static const screen_x_t SWORD_CENTER_X = 410;
static const screen_y_t SWORD_CENTER_Y = 70;
static const screen_x_t SLASH_4_CORNER_X = 432;
static const screen_y_t SLASH_4_CORNER_Y = 232;
static const screen_x_t SLASH_5_CORNER_X = 198;
static const screen_y_t SLASH_5_CORNER_Y = 198;

static const pixel_t CUP_W = 32;

static const screen_x_t CUP_RIGHT = (CUP_LEFT + CUP_W);
static const screen_x_t CUP_CENTER_X = (CUP_LEFT + (CUP_W / 2));
// -----------

// Other constants
// ----------------

static const pixel_t SLASH_DISTANCE_2_TO_4_X = (
	SLASH_4_CORNER_X - SWORD_CENTER_X
);
static const pixel_t SLASH_DISTANCE_2_TO_4_Y = (
	SLASH_4_CORNER_Y - SWORD_CENTER_Y
);
static const pixel_t SLASH_DISTANCE_5_TO_4_X = (
	SLASH_5_CORNER_X - SLASH_4_CORNER_X // yes, backwards
);
static const pixel_t SLASH_DISTANCE_5_TO_4_Y = (
	SLASH_5_CORNER_Y - SLASH_4_CORNER_Y // yes, backwards
);
static const pixel_t SLASH_DISTANCE_5_TO_6_X = (
	SLASH_5_CORNER_X - SWORD_CENTER_X
);
static const pixel_t SLASH_DISTANCE_5_TO_6_Y = (
	SLASH_5_CORNER_Y - SWORD_CENTER_Y
);
// ----------------

static union {
	int group; // pellet_group_t
	int interval;
	subpixel_t speed;
	pixel_t delta_x;
	int unused;
} pattern_state;

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

static face_direction_t face_direction = FD_UNINITIALIZED;
static face_expression_t face_expression = FE_NEUTRAL;
static bool16 face_direction_can_change = true;

#define ent_head                	boss_entity_0
#define ent_face_closed_or_glare	boss_entity_1
#define ent_face_aim            	boss_entity_2

inline void konngara_ent_load(void) {
	ent_head.load("boss8_1.bos", 0);
	ent_face_closed_or_glare.load("boss8_e1.bos", 1);
	ent_face_aim.load("boss8_e2.bos", 2);
}

inline void konngara_ent_free(void) {
	bos_entity_free(0);
	bos_entity_free(1);
	bos_entity_free(2);
}

#define head_put(direction) \
	ent_head.put_8(HEAD_LEFT, HEAD_TOP, direction);

#define face_aim_put(direction) \
	ent_face_aim.put_8(FACE_LEFT, FACE_TOP, direction);

#define face_put(expression, direction) \
	ent_face_closed_or_glare.put_8( \
		FACE_LEFT, FACE_TOP, (((expression - FE_CLOSED) * FD_COUNT) + direction) \
	);
// --------

// Snakes
// ------

static const int SNAKE_TRAIL_COUNT = 5;

inline screen_x_t snake_target_offset_left(const screen_x_t &to_left) {
	return (to_left + (PLAYER_W / 2) - (DIAMOND_W / 2));
}

#define SNAKE_HOMING_THRESHOLD ( \
	PLAYFIELD_TOP + playfield_fraction_y(5 / 7.0f) - (DIAMOND_H / 2) \
)

template <int SnakeCount> struct Snakes {
	screen_x_t left[SnakeCount][SNAKE_TRAIL_COUNT];
	screen_y_t top[SnakeCount][SNAKE_TRAIL_COUNT];
	pixel_t velocity_x[SnakeCount];
	pixel_t velocity_y[SnakeCount];
	bool16 target_locked[SnakeCount];
	screen_x_t target_left[SnakeCount];

	int count() const {
		return SnakeCount;
	}
};

#define snakes_wobbly_aim(snakes, snake_i, to_left, speed, tmp_angle) \
	tmp_angle = iatan2( \
		(player_center_y() - snakes.top[snake_i][0]), \
		(snake_target_offset_left(to_left) - snakes.left[snake_i][0]) \
	); \
	tmp_angle += ((rand() % 2) == 0) ? +0x28 : -0x28; \
	vector2( \
		(pixel_t far &)snakes.velocity_x[snake_i], \
		(pixel_t far &)snakes.velocity_y[snake_i], \
		speed, \
		tmp_angle \
	);

#define snakes_spawn_and_wobbly_aim( \
	snakes, snake_i, origin_x, origin_y, tmp_i, tmp_angle \
) \
	for(tmp_i = 0; tmp_i < SNAKE_TRAIL_COUNT; tmp_i++) { \
		snakes.left[snake_i][tmp_i] = origin_x; \
		snakes.top[snake_i][tmp_i] = origin_y; \
	} \
	snakes_wobbly_aim(snakes, snake_i, player_left, 6, tmp_angle)

#define snakes_unput_update_render(tmp_i, tmp_j, tmp_angle) \
	for(tmp_i = 0; tmp_i < snakes.count(); tmp_i++) { \
		/* Snake update */ \
		if(snakes.left[i][0] == -PIXEL_NONE) { \
			continue; \
		} \
		/* The last trail sprite is the only one we have to unblit here. */ \
		/* Since we forward-copy the coordinates for the remaining trail */ \
		/* segments, they're then drawn on top of previously blitted */ \
		/* sprites anyway. Nifty! */ \
		shape8x8_sloppy_unput( \
			snakes.left[tmp_i][SNAKE_TRAIL_COUNT - 1], \
			snakes.top[tmp_i][SNAKE_TRAIL_COUNT - 1] \
		); \
		\
		/* Render…? Before update? */ \
		for(tmp_j = (SNAKE_TRAIL_COUNT - 2); tmp_j >= 1; tmp_j--) { \
			shape8x8_diamond_put( \
				snakes.left[tmp_i][tmp_j], snakes.top[i][tmp_j], 9 \
			); \
		} \
		shape8x8_diamond_put( \
			snakes.left[tmp_i][0], snakes.top[tmp_i][0], V_WHITE \
		); \
		\
		/* Update */ \
		if(snakes.target_locked[tmp_i] == false) { \
			snakes.target_left[tmp_i] = player_left; \
		} \
		snakes_wobbly_aim(snakes, i, snakes.target_left[tmp_i], 7, angle); \
		if(snakes.top[tmp_i][0] > SNAKE_HOMING_THRESHOLD) { \
			snakes.target_locked[tmp_i] = true; \
		} \
		\
		/* Forward copy */ \
		for(tmp_j = (SNAKE_TRAIL_COUNT - 1); tmp_j >= 1; tmp_j--) { \
			snakes.left[tmp_i][tmp_j] = snakes.left[tmp_i][tmp_j - 1]; \
			snakes.top[tmp_i][tmp_j] = snakes.top[tmp_i][tmp_j - 1]; \
		} \
		\
		snakes.left[tmp_i][0] += snakes.velocity_x[tmp_i]; \
		snakes.top[tmp_i][0] += snakes.velocity_y[tmp_i]; \
		\
		/* Yes, that's a 30×30 hitbox around the player's center point if */ \
		/* the player is not sliding, only leaving out the edges. */ \
		if(overlap_xy_ltrb_lt_gt( \
			snakes.left[tmp_i][0], \
			snakes.top[tmp_i][0], \
			player_left, \
			(player_top + (player_sliding * 10)), \
			(player_right() - DIAMOND_W), \
			(player_bottom() - DIAMOND_H) \
		)) { \
			if(!player_invincible) { \
				player_is_hit = true; \
			} \
		} \
	}

#define snakes_unput_all(snakes, tmp_i, tmp_j) \
	for(tmp_i = 0; tmp_i < snakes.count(); tmp_i++) { \
		for(j = 0; j < SNAKE_TRAIL_COUNT; j++) { \
			shape8x8_sloppy_unput(snakes.left[i][j], snakes.top[i][j]); \
		} \
	}
// ------

// File names
// ----------

#define SCROLL_BG_FN "boss7_d1.grp"
#include "th01/shiftjis/fns.hpp"
#define GRZ_FN "boss8.grz"
// ----------

#include "th01/main/select_r.cpp"

// Almost identical to Sariel's version. This one is better.
static void spawnray_unput_and_put(
	screen_x_t origin_x, vram_y_t origin_y,
	screen_x_t target_x, vram_y_t target_y,
	int col
)
{
	static screen_x_t target_prev_x = -PIXEL_NONE;
	static vram_y_t target_prev_y = -PIXEL_NONE;
	spawnray_unput_and_put_func(
		target_prev_x, target_prev_y,
		origin_x, origin_y, target_x, target_y, col, false
	);
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
	grp_put(SCROLL_BG_FN, GPF_PALETTE_SHOW);

	// ZUN bug: On its own, this call at this position in the code would just
	// be redundant as the stage palette is never used here. After all, you
	// can't enter the Pause menu or bomb during a blocking animation function.
	// However, it's also the only call to stage_palette_set() in all of
	// Konngara's code, and ends up setting a palette that doesn't exactly
	// match the one used for the rest of the fight. Most notably, this is why
	// entering the Pause menu or bombing changes color #10 from red to green,
	// which is only corrected by boss_hit_update_and_render()'s periodic reset
	// of the hardware palette to the [boss_palette].
	stage_palette_set(z_Palettes);

	stageobjs_init_and_render(BOSS_STAGE);

	graph_accesspage_func(1);
	grp_put("boss8_a1.grp", GPF_PALETTE_SHOW);
	// The stage_palette_set() call should have been here.

	graph_accesspage_func(0);
	mdrv2_bgm_load("ALICE.MDT");
	mdrv2_se_load(SE_FN); // ZUN bloat: Already done in main()
	mdrv2_bgm_play();

	z_palette_set_black(j, i);

	text_fillca(' ', TX_WHITE);
	konngara_ent_load();

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
		EGCCopy egc;
		z_vsync_wait_and_scrollup(line_on_top);
		egc.rect_interpage(0, line_on_top, RES_X, (MAGNITUDE * 2), 1);
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
	grp_put("boss8_d1.grp", GPF_COLORKEY);
	grp_put("boss8_d2.grp", GPF_COLORKEY);
	grp_put("boss8_d3.grp", GPF_COLORKEY);
	grp_put("boss8_d4.grp", GPF_COLORKEY);

	for(j = 0; j < RGB4::Range; j++) {
		siddham_col_white_in_step();
		frame_delay(10);
	}
	graph_copy_accessed_page_to_other();
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

// Happens to be entirely protected from double frees. Yes, this matters.
void konngara_free(void)
{
	konngara_ent_free();
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
	#define DIAMOND_ORIGIN_X (PLAYFIELD_CENTER_X - (DIAMOND_W / 2))
	#define DIAMOND_ORIGIN_Y (PLAYFIELD_CENTER_Y + (DIAMOND_H / 2))

	int i;

	static pixel_t velocity_bottomleft_x, velocity_topleft_x;
	static pixel_t velocity_bottomleft_y, velocity_topleft_y;
	static EntitiesTopleft<4> diamonds;
	static int frames_with_diamonds_at_edges;

	#define diamonds_unput(i) \
		for(i = 0; i < diamonds.count(); i++) { \
			shape8x8_sloppy_unput(diamonds.left[i], diamonds.top[i]); \
		}

	#define diamonds_put(i) \
		for(i = 0; i < diamonds.count(); i++) { \
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
			velocity_bottomleft_x, velocity_bottomleft_y,
			7
		);
		vector2_between(
			DIAMOND_ORIGIN_X, DIAMOND_ORIGIN_Y,
			PLAYFIELD_LEFT, PLAYFIELD_TOP,
			velocity_topleft_x, velocity_topleft_y,
			7
		);

		for(i = 0; i < diamonds.count(); i++) {
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
		diamonds.left[0] += velocity_bottomleft_x;
		diamonds.top[0]  += velocity_bottomleft_y;
		diamonds.left[1] -= velocity_bottomleft_x;
		diamonds.top[1]  += velocity_bottomleft_y;
		diamonds.left[2] += velocity_topleft_x;
		diamonds.top[2]  += velocity_topleft_y;
		diamonds.left[3] -= velocity_topleft_x;
		diamonds.top[3]  += velocity_topleft_y;
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
			from_top = playfield_rand_y(0.0f, (25 / 42.0f));
			to_left = playfield_rand_x(0.375f, 1.0f);
			to_top = PLAYFIELD_BOTTOM;
			angle = iatan2((to_top - from_top), (to_left - from_left));
			Pellets.add_single(from_left, from_top, angle, speed);

			from_left = (PLAYFIELD_RIGHT - PELLET_W);
			from_top = playfield_rand_y(0.0f, (25 / 42.0f));
			to_left  = playfield_rand_x(0.0f, 0.625f);
			to_top = PLAYFIELD_BOTTOM;
			angle = iatan2((to_top - from_top), (to_left - from_left));
			Pellets.add_single(from_left, from_top, angle, speed);

			from_top = PLAYFIELD_TOP;
			from_left = playfield_rand_x();
			to_top = PLAYFIELD_BOTTOM;
			to_left = playfield_rand_x();
			angle = iatan2((to_top - from_top), (to_left - from_left));
			Pellets.add_single(from_left, from_top, angle, speed);

			from_top = PLAYFIELD_TOP;
			from_left = playfield_rand_x();
			to_top = PLAYFIELD_BOTTOM;
			to_left = playfield_rand_x();
			angle = iatan2((to_top - from_top), (to_left - from_left));
			Pellets.add_single(from_left, from_top, angle, speed);

			from_top = PLAYFIELD_TOP;
			from_left = playfield_rand_x();
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
}

void pattern_symmetrical_from_cup_fire(unsigned char angle)
{
	Pellets.add_single(CUP_RIGHT, CUP_TOP, angle, pattern_state.speed);
	Pellets.add_single(CUP_LEFT,  CUP_TOP, angle, pattern_state.speed);
}

void pattern_symmetrical_from_cup(void)
{
	static unsigned char angle;

	if(boss_phase_frame == 10) {
		face_expression_set_and_put(FE_CLOSED);
	}
	if(boss_phase_frame < 100) {
		return;
	}
	if(boss_phase_frame == 100) {
		angle = 0x40;
		select_subpixel_for_rank(pattern_state.speed, 5.0f, 5.0f, 6.0f, 7.0f);
	}
	if((boss_phase_frame < 140) && ((boss_phase_frame % 8) == 0)) {
		pattern_symmetrical_from_cup_fire(0x40);
		return;
	}
	if((boss_phase_frame < 220) && ((boss_phase_frame % 8) == 0)) {
		angle += 0x05;
		pattern_symmetrical_from_cup_fire(angle);
		pattern_symmetrical_from_cup_fire(0x80 - angle);
		return;
	}
	if((boss_phase_frame < 300) && ((boss_phase_frame % 8) == 0)) {
		angle -= 0x0C;
		pattern_symmetrical_from_cup_fire(angle);
		pattern_symmetrical_from_cup_fire(0x80 - angle);
	}
	if(boss_phase_frame >= 300) {
		boss_phase_frame = 0;
	}
}

void pattern_two_homing_snakes_and_semicircle_spreads(void)
{
	static Snakes<2> snakes;

	int i;
	int j;
	screen_x_t pellet_left;
	screen_y_t pellet_top;
	unsigned char angle;

	if(boss_phase_frame == 10) {
		face_expression_set_and_put(FE_GLARE);
	}
	if(boss_phase_frame < 100) {
		return;
	}
	if(boss_phase_frame == 100) {
		snakes.target_locked[0] = false;
		snakes.target_locked[1] = false;
		snakes_spawn_and_wobbly_aim(snakes, 0, CUP_CENTER_X, CUP_TOP, i, angle);
		snakes.left[1][0] = -PIXEL_NONE;
		mdrv2_se_play(12);
		return;
	}
	if(boss_phase_frame < 500) {
		snakes_unput_update_render(i, j, angle)
		if(boss_phase_frame == 150) {
			snakes_spawn_and_wobbly_aim(
				snakes, 1, CUP_CENTER_X, CUP_TOP, i, angle
			);
			mdrv2_se_play(12);
		}

		if(
			(boss_phase_frame > (240 - (rank * 40))) &&
			((boss_phase_frame % 40) == 0)
		) {
			enum {
				SPREAD = 10,
			};
			pixel_t velocity_x;
			pixel_t velocity_y;
			Subpixel speed;

			angle = (rand() % (0x80 / SPREAD));
			pellet_left =
				((boss_phase_frame % 120) ==  0) ? SWORD_CENTER_X :
				((boss_phase_frame % 120) == 40) ? EYE_CENTER_X :
				/*boss_phase_frame % 120  == 80 */ CUP_CENTER_X;
			pellet_top =
				((boss_phase_frame % 120) ==  0) ? SWORD_CENTER_Y :
				((boss_phase_frame % 120) == 40) ? EYE_BOTTOM :
				/*boss_phase_frame % 120  == 80 */ CUP_TOP;

			for(i = 0; i < SPREAD; i++) {
				speed.v = (to_sp(2.5f) + (
					((i % 4) == 0) ? to_sp(0.0f) :
					((i % 4) == 1) ? to_sp(1.0f) :
					((i % 4) == 2) ? to_sp(0.0f) :
					/*i % 4  == 3 */ to_sp(2.0f)
				));

				// That result is never used?
				vector2(velocity_x, velocity_y, speed, angle);

				Pellets.add_single(
					pellet_left, pellet_top, (0x80 - angle), speed
				);
				Pellets.add_single(pellet_left, pellet_top, angle, speed);
				angle += (0x80 / SPREAD);
			}
			mdrv2_se_play(7);
		};
	} else {
		snakes_unput_all(snakes, i, j);
		boss_phase_frame = 0;
	}
}

void pattern_aimed_rows_from_top(void)
{
	enum {
		DIAMOND_SPEED = 8,
		ROW_MARGIN = (PLAYFIELD_W / 10),
	};

	static point_t diamond_velocity;

	// screen_point_t would generate too good ASM here
	static screen_x_t diamond_left;
	static screen_y_t diamond_top;

	static enum {
		RIGHT = 0,
		LEFT = 1,
		DOWN_START = 2,
		DOWN_END = (DOWN_START + (ROW_MARGIN / DIAMOND_SPEED)),
		TO_INITIAL_POSITION = 99,

		_diamond_direction_t_FORCE_INT16 = 0x7FFF
	} diamond_direction;
	static Subpixel pellet_speed;

	if(boss_phase_frame == 10) {
		face_expression_set_and_put(FE_NEUTRAL);
	}
	if(boss_phase_frame < 100) {
		return;
	}
	if(boss_phase_frame == 100) {
		vector2_between(
			LEFT_SLEEVE_LEFT, LEFT_SLEEVE_TOP,
			(PLAYFIELD_LEFT + ROW_MARGIN), PLAYFIELD_TOP,
			diamond_velocity.x, diamond_velocity.y,
			(DIAMOND_SPEED * 2)
		);
		diamond_left = LEFT_SLEEVE_LEFT;
		diamond_top = LEFT_SLEEVE_TOP;
		pellet_speed.set(3.0f);
		mdrv2_se_play(12);
		diamond_direction = TO_INITIAL_POSITION;
		select_for_rank(pattern_state.interval, 12, 10, 8, 6);
		return;
	}
	if(diamond_direction == TO_INITIAL_POSITION) {
		shape8x8_sloppy_unput(diamond_left, diamond_top);
		diamond_left += diamond_velocity.x;
		diamond_top += diamond_velocity.y;

		if(diamond_top <= PLAYFIELD_TOP) {
			diamond_left = (PLAYFIELD_LEFT + ROW_MARGIN);
			diamond_top = PLAYFIELD_TOP;
			diamond_direction = RIGHT;
			return;
		}
		shape8x8_diamond_put(diamond_left, diamond_top, 9);
	} else if(diamond_direction < TO_INITIAL_POSITION) {
		shape8x8_sloppy_unput(diamond_left, diamond_top);

		// That's quite the roundabout way of saying "-8, 0, or +8"...
		diamond_left += (DIAMOND_SPEED + (
			(diamond_direction == RIGHT) ?   0 :
			(diamond_direction ==  LEFT) ? (-DIAMOND_SPEED * 2) :
			/*            >= DOWN_START */  -DIAMOND_SPEED
		));
		if(diamond_direction >= DOWN_START) {
			diamond_top += DIAMOND_SPEED;
			reinterpret_cast<int &>(diamond_direction)++;
			if(diamond_direction >= DOWN_END) {
				diamond_direction = (diamond_left > PLAYFIELD_CENTER_X)
					? LEFT
					: RIGHT;
			}
		}
		if(diamond_left > (PLAYFIELD_RIGHT - ROW_MARGIN)) {
			diamond_direction = DOWN_START;
			diamond_left = (PLAYFIELD_RIGHT - ROW_MARGIN);
		} else if(diamond_left < (PLAYFIELD_LEFT + ROW_MARGIN)) {
			diamond_direction = DOWN_START;
			diamond_left = (PLAYFIELD_LEFT + ROW_MARGIN);
		}
		if(diamond_top >= (PLAYFIELD_TOP + (ROW_MARGIN * 3))) {
			boss_phase_frame = 0;
			return;
		}
		if(diamond_direction < DOWN_START) {
			if((boss_phase_frame % pattern_state.interval) == 0) {
				Pellets.add_group(
					diamond_left, diamond_top, PG_1_AIMED, pellet_speed
				);
				pellet_speed += 0.125f;
			}
		}
		shape8x8_diamond_put(diamond_left, diamond_top, 6);
	}
}

void pattern_aimed_spray_from_cup(void)
{
	static unsigned char spray_offset;
	static unsigned char angle; // should be local
	static int spray_delta; // should be unsigned char
	static int frames_in_current_direction;

	if(boss_phase_frame == 10) {
		face_expression_set_and_put(FE_CLOSED);
	}
	if(boss_phase_frame < 100) {
		return;
	}
	if(boss_phase_frame == 100) {
		spray_offset = 0x20;
		spray_delta = -0x08;
		frames_in_current_direction = 0;
		select_for_rank(pattern_state.interval, 5, 4, 3, 2);
	}
	if((boss_phase_frame % pattern_state.interval) == 0) {
		// Yes, the point from which these are aimed to the top-left player
		// coordinate is quite a bit away from where they're actually fired,
		// leading to some quite imperfect aiming. Probably done on purpose
		// though, and largely mitigated by the spraying motion anyway.
		angle = iatan2(
			(player_top - (CUP_TOP - 4)), (player_left - (CUP_CENTER_X - 34))
		);
		angle += spray_offset;
		spray_offset += spray_delta;
		frames_in_current_direction++;
		if(frames_in_current_direction > 8) {
			spray_delta *= -1;
			frames_in_current_direction = 0;
		}
		Pellets.add_single(CUP_CENTER_X, CUP_TOP, angle, to_sp(3.0f));
	}
	if(boss_phase_frame >= 700) {
		boss_phase_frame = 0;
	}
}

void pattern_four_homing_snakes(void)
{
	static Snakes<4> snakes;

	int i;
	int j;
	unsigned char angle;

	if(boss_phase_frame == 10) {
		face_expression_set_and_put(FE_GLARE);
	}
	if(boss_phase_frame < 100) {
		return;
	}
	if(boss_phase_frame == 100) {
		for(i = 0; i < snakes.count(); i++) {
			snakes.target_locked[i] = false;
		}
		snakes_spawn_and_wobbly_aim(snakes, 0, CUP_CENTER_X, CUP_TOP, i, angle);
		for(i = 1; i < snakes.count(); i++) {
			snakes.left[i][0] = -PIXEL_NONE;
		}
		select_for_rank(pattern_state.unused, 18, 16, 14, 12);
		mdrv2_se_play(12);
		return;
	}
	if(boss_phase_frame < 400) {
		snakes_unput_update_render(i, j, angle);
		if(boss_phase_frame == 150) {
			snakes_spawn_and_wobbly_aim(
				snakes, 1, CUP_CENTER_X, CUP_TOP, i, angle
			);
			mdrv2_se_play(12);
		}
		if(boss_phase_frame == 200) {
			snakes_spawn_and_wobbly_aim(
				snakes, 2, LEFT_SLEEVE_LEFT, LEFT_SLEEVE_TOP, i, angle
			);
			mdrv2_se_play(12);
		}
		if(boss_phase_frame == 250) {
			snakes_spawn_and_wobbly_aim(
				snakes, 3, LEFT_SLEEVE_LEFT, LEFT_SLEEVE_TOP, i, angle
			);
			mdrv2_se_play(12);
		}
	} else {
		snakes_unput_all(snakes, i, j);
		boss_phase_frame = 0;
	}
}

inline void swordray_unput_put_and_move(
	screen_x_t& end_x, screen_x_t& end_y, screen_x_t delta_x, screen_y_t delta_y
) {
	spawnray_unput_and_put(SWORD_CENTER_X, SWORD_CENTER_Y, end_x, end_y, 6);
	// Gimme those original instructions!
	if(delta_x < 0) { end_x -= -delta_x; } else { end_x += delta_x; }
	if(delta_y < 0) { end_y -= -delta_y; } else { end_y += delta_y; }
}

inline void swordray_unput(const screen_x_t& end_x, const screen_x_t& end_y) {
	graph_r_line_unput(SWORD_CENTER_X, SWORD_CENTER_Y, end_x, end_y);
}

void pattern_rain_from_edges(void)
{
	static screen_x_t end_x;
	static screen_y_t end_y;
	static int unused;

	enum {
		SPAWNRAY_SPEED = 8,
		FRAMES_VERTICAL = 25,
		FRAMES_HORIZONTAL = (PLAYFIELD_W / SPAWNRAY_SPEED),

		KEYFRAME_0 = 100,
		KEYFRAME_1 = (KEYFRAME_0 + FRAMES_VERTICAL), // up
		KEYFRAME_2 = (KEYFRAME_1 + FRAMES_HORIZONTAL), // right
		KEYFRAME_3 = (KEYFRAME_2 + FRAMES_VERTICAL), // down
		KEYFRAME_4 = (KEYFRAME_3 + FRAMES_VERTICAL), // up
		KEYFRAME_5 = (KEYFRAME_4 + FRAMES_HORIZONTAL), // left
		KEYFRAME_6 = (KEYFRAME_5 + FRAMES_VERTICAL), // down
	};

	if(boss_phase_frame == 10) {
		face_expression_set_and_put(FE_AIM);
	}
	if(boss_phase_frame < KEYFRAME_0) {
		return;
	}
	if(boss_phase_frame == KEYFRAME_0) {
		end_x = PLAYFIELD_LEFT;
		end_y = (PLAYFIELD_TOP + (SPAWNRAY_SPEED * FRAMES_VERTICAL));
		unused = 1;
		select_for_rank(pattern_state.interval, 5, 3, 2, 2);
	}
	if(boss_phase_frame < KEYFRAME_1) {
		swordray_unput_put_and_move(end_x, end_y, 0, -SPAWNRAY_SPEED);
	} else if(boss_phase_frame == KEYFRAME_1) {
		end_x = PLAYFIELD_LEFT;
		end_y = PLAYFIELD_TOP;
		swordray_unput_put_and_move(end_x, end_y, +SPAWNRAY_SPEED, 0);

		unused = 0;
	} else if(boss_phase_frame < KEYFRAME_2) {
		swordray_unput_put_and_move(end_x, end_y, +SPAWNRAY_SPEED, 0);
	} else if(boss_phase_frame == KEYFRAME_2) {
		end_x = (PLAYFIELD_RIGHT - 1);
		end_y = PLAYFIELD_TOP;
		swordray_unput_put_and_move(end_x, end_y, 0, +SPAWNRAY_SPEED);

		unused = 2;
	} else if(boss_phase_frame < KEYFRAME_3) {
		swordray_unput_put_and_move(end_x, end_y, 0, +SPAWNRAY_SPEED);
	} else if(boss_phase_frame == KEYFRAME_3) {
		end_x = (PLAYFIELD_RIGHT - 1);
		end_y = (PLAYFIELD_TOP + (SPAWNRAY_SPEED * FRAMES_VERTICAL));
		swordray_unput_put_and_move(end_x, end_y, 0, -SPAWNRAY_SPEED);

		unused = 2;
	} else if(boss_phase_frame < KEYFRAME_4) {
		swordray_unput_put_and_move(end_x, end_y, 0, -SPAWNRAY_SPEED);
	} else if(boss_phase_frame == KEYFRAME_4) {
		end_x = (PLAYFIELD_RIGHT - 1);
		end_y = PLAYFIELD_TOP;
		swordray_unput_put_and_move(end_x, end_y, -SPAWNRAY_SPEED, 0);

		unused = 0;
	} else if(boss_phase_frame < KEYFRAME_5) {
		swordray_unput_put_and_move(end_x, end_y, -SPAWNRAY_SPEED, 0);
	} else if(boss_phase_frame == KEYFRAME_5) {
		end_x = PLAYFIELD_LEFT;
		end_y = PLAYFIELD_TOP;
		swordray_unput_put_and_move(end_x, end_y, 0, +SPAWNRAY_SPEED);

		unused = 1;
	} else if(boss_phase_frame < KEYFRAME_6) {
		swordray_unput_put_and_move(end_x, end_y, 0, +SPAWNRAY_SPEED);
	} else if(boss_phase_frame == KEYFRAME_6) {
		// Wait, what, changing the end point of the ray immediately before
		// unblitting?! Technically wrong, but since line unblitting uses
		// 32-dot chunks anyway, this doesn't leave any visible glitches.
		end_y -= SPAWNRAY_SPEED;
		swordray_unput(end_x, end_y);
		boss_phase_frame = 0;
	}
	if((boss_phase_frame % 10) == 0) {
		mdrv2_se_play(6);
	}
	if((boss_phase_frame % pattern_state.interval) == 0) {
		pellets_add_single_rain(end_x, end_y, (rand() & 0x7F), 2.0f);
		pellets_add_single_rain(end_x, end_y, (rand() & 0x7F), 2.0f);
	}
}

enum slash_cel_frame_t {
	SLASH_0_FRAME = 50,
	SLASH_1_FRAME = 60,
	SLASH_2_FRAME = 100,
	SLASH_3_FRAME = 120,
	SLASH_4_FRAME = 140,
	SLASH_4_5_FRAME = 150,
	SLASH_5_FRAME = 160,
	SLASH_6_FRAME = 170,

	SLASH_FRAMES_FROM_2_TO_4 = (SLASH_4_FRAME - SLASH_2_FRAME),
	 // Yes, also backwards
	SLASH_FRAMES_FROM_5_TO_4_5 = (SLASH_4_5_FRAME - SLASH_5_FRAME),
	SLASH_FRAMES_FROM_4_5_TO_6 = (SLASH_6_FRAME - SLASH_4_5_FRAME),
};

void slash_animate(void)
{
	// MODDERS: Just use a switch.
	#define boss_phase_at_frame(frame) \
		boss_phase_frame < frame) return; if(boss_phase_frame == frame

	if(boss_phase_at_frame(SLASH_0_FRAME)) {
		slash_put(0);
		mdrv2_se_play(8);
	}
	if(boss_phase_at_frame(SLASH_1_FRAME)) {
		slash_put(1);
	}
	if(boss_phase_at_frame(SLASH_2_FRAME)) {
		slash_put(2);
	}
	if(boss_phase_at_frame(SLASH_3_FRAME)) {
		slash_put(3);
	}
	if(boss_phase_at_frame(SLASH_4_FRAME)) {
		slash_put(4);
	}
	if(boss_phase_at_frame(SLASH_5_FRAME)) {
		slash_put(5);
	}
	if(boss_phase_at_frame(SLASH_6_FRAME)) {
		slash_put(6);
	}
	if(boss_phase_frame > 200) {
		boss_phase_frame = 0;
		face_direction_can_change = true;
	}

	#undef boss_phase_at_frame
}

#define slash_spawner_step_from_2_to_4(left, top, steps) \
	left += (SLASH_DISTANCE_2_TO_4_X / (SLASH_FRAMES_FROM_2_TO_4 / steps)); \
	top  += (SLASH_DISTANCE_2_TO_4_Y / (SLASH_FRAMES_FROM_2_TO_4 / steps));

#define slash_spawner_step_from_4_to_4_5(left, top, steps) \
	left -= (SLASH_DISTANCE_5_TO_4_X / (SLASH_FRAMES_FROM_5_TO_4_5 / steps)); \
	top  -= (SLASH_DISTANCE_5_TO_4_Y / (SLASH_FRAMES_FROM_5_TO_4_5 / steps));

#define slash_spawner_step_from_4_5_to_6(left, top, steps) \
	left -= (SLASH_DISTANCE_5_TO_6_X / (SLASH_FRAMES_FROM_4_5_TO_6 / steps)); \
	top  -= (SLASH_DISTANCE_5_TO_6_Y / (SLASH_FRAMES_FROM_4_5_TO_6 / steps));

inline void slash_rain_fire(const screen_x_t& left, const screen_y_t& top) {
	pellets_add_single_rain(left, top, (rand() % 0x7F), 0.0f);
	pellets_add_single_rain(left, top, (rand() % 0x7F), 0.0f);
}

void pattern_slash_rain(void)
{
	static screen_x_t spawner_left;
	static screen_y_t spawner_top;

	if(boss_phase_frame == 10) {
		face_direction_set_and_put(FD_CENTER);
		face_expression_set_and_put(FE_CLOSED);
		face_direction_can_change = false;
		spawner_left = SWORD_CENTER_X;
		spawner_top = SWORD_CENTER_Y;
		select_for_rank(pattern_state.interval, 5, 3, 2, 1);
	}

	slash_animate();

	if(boss_phase_frame < SLASH_2_FRAME) {
		return;
	}
	if(
		(boss_phase_frame < SLASH_4_FRAME) &&
		((boss_phase_frame % pattern_state.interval) == 0)
	) {
		slash_rain_fire(spawner_left, spawner_top);
		slash_spawner_step_from_2_to_4(
			spawner_left, spawner_top, pattern_state.interval
		);
	}

	if(boss_phase_frame == SLASH_4_FRAME) {
		spawner_left = SLASH_4_CORNER_X;
		spawner_top = SLASH_4_CORNER_Y;
		// Originally meant to be the step interval between cels 4 and 5?
		select_for_rank(pattern_state.unused, 3, 2, 2, 2);
	}
	if(boss_phase_frame < SLASH_4_FRAME) {
		return;
	}
	if(boss_phase_frame < SLASH_4_5_FRAME) {
		slash_rain_fire(spawner_left, spawner_top);
		slash_spawner_step_from_4_to_4_5(spawner_left, spawner_top, 1);
	}

	if(boss_phase_frame == SLASH_4_5_FRAME) {
		spawner_left = SLASH_5_CORNER_X;
		spawner_top = SLASH_5_CORNER_Y;
		select_for_rank(pattern_state.interval, 3, 2, 1, 1);
	}
	if(boss_phase_frame < SLASH_4_5_FRAME) {
		return;
	}
	if(
		(boss_phase_frame < SLASH_6_FRAME) &&
		((boss_phase_frame % pattern_state.interval) == 0)
	) {
		slash_rain_fire(spawner_left, spawner_top);
		slash_spawner_step_from_4_5_to_6(
			spawner_left, spawner_top, pattern_state.interval
		);
	}
}

inline void slash_triangular_fire(
	const screen_x_t& left, const screen_y_t& top, const subpixel_t& speed
) {
	Pellets.add_single(left, top, 0x20, speed);
	Pellets.add_single(left, top, 0x60, speed);
}

void pattern_slash_triangular(void)
{
	static screen_x_t spawner_left;
	static screen_y_t spawner_top;

	if(boss_phase_frame == 10) {
		face_direction_set_and_put(FD_CENTER);
		face_expression_set_and_put(FE_AIM);
		face_direction_can_change = false;
		spawner_left = SWORD_CENTER_X;
		spawner_top = SWORD_CENTER_Y;
		select_subpixel_for_rank(pattern_state.speed, 2.0f, 3.0f, 4.0f, 4.5f);
	}

	slash_animate();

	if(boss_phase_frame < SLASH_2_FRAME) {
		return;
	}
	if((boss_phase_frame < SLASH_4_FRAME) && ((boss_phase_frame % 3) == 0)) {
		slash_triangular_fire(spawner_left, spawner_top, pattern_state.speed);
		slash_spawner_step_from_2_to_4(spawner_left, spawner_top, 3);
	}

	if(boss_phase_frame == SLASH_4_FRAME) {
		spawner_left = SLASH_4_CORNER_X;
		spawner_top = SLASH_4_CORNER_Y;
	}
	if(boss_phase_frame < SLASH_4_FRAME) {
		return;
	}
	if(boss_phase_frame < SLASH_4_5_FRAME) {
		slash_triangular_fire(spawner_left, spawner_top, pattern_state.speed);
		slash_spawner_step_from_4_to_4_5(spawner_left, spawner_top, 1);
	}

	if(boss_phase_frame == SLASH_4_5_FRAME) {
		spawner_left = SLASH_5_CORNER_X;
		spawner_top = SLASH_5_CORNER_Y;
	}
	if(boss_phase_frame < SLASH_4_5_FRAME) {
		return;
	}
	if((boss_phase_frame < SLASH_6_FRAME) && ((boss_phase_frame % 2) == 0)) {
		slash_triangular_fire(spawner_left, spawner_top, pattern_state.speed);
		slash_spawner_step_from_4_5_to_6(spawner_left, spawner_top, 2);
	}
}

void pattern_lasers_and_3_spread(void)
{
	// These have no reason to be static.
	static screen_x_t target_left;
	static screen_y_t target_y;

	static bool16 right_to_left;

	enum {
		INTERVAL = 10,
	};

	if(boss_phase_frame == 10) {
		face_expression_set_and_put(FE_AIM);
	}
	if(boss_phase_frame < 100) {
		return;
	}
	if(boss_phase_frame == 100) {
		right_to_left = (rand() % 2);

		// Divisor = number of lasers that are effectively fired.
		select_for_rank(pattern_state.delta_x,
			(PLAYFIELD_W / 5),
			(PLAYFIELD_W / 6.66),
			(PLAYFIELD_W / 8),
			(PLAYFIELD_W / 10)
		);
	}
	if((boss_phase_frame % INTERVAL) == 0) {
		if(right_to_left == 0) {
			target_left = (PLAYFIELD_LEFT + (
				((boss_phase_frame - 100) / INTERVAL) * pattern_state.delta_x
			));
		} else {
			target_left = (PLAYFIELD_RIGHT - (
				((boss_phase_frame - 100) / INTERVAL) * pattern_state.delta_x
			));
		}
		target_y = PLAYFIELD_BOTTOM;

		shootout_laser_safe(boss_phase_frame / INTERVAL).spawn(
			SWORD_CENTER_X, SWORD_CENTER_Y,
			target_left, target_y,
			(to_sp(8.5f) / 2), V_WHITE, 30, 5
		);
		mdrv2_se_play(6);

		if(
			((right_to_left == false) && (target_left >= PLAYFIELD_RIGHT)) ||
			((right_to_left == true)  && (target_left <= PLAYFIELD_LEFT))
		) {
			boss_phase_frame = 0;
		}

		Pellets.add_group(
			SWORD_CENTER_X, SWORD_CENTER_Y, PG_3_SPREAD_WIDE_AIMED, to_sp(4.5f)
		);
	}
}

inline void slash_aimed_fire(
	const screen_x_t& left, const screen_y_t& top, const subpixel_t& speed
) {
	Pellets.add_group(left, top, PG_1_AIMED, speed);
}

void pattern_slash_aimed(void)
{
	static screen_x_t spawner_left;
	static screen_y_t spawner_top;

	if(boss_phase_frame == 10) {
		face_direction_set_and_put(FD_CENTER);
		face_expression_set_and_put(FE_AIM);
		face_direction_can_change = false;
		spawner_left = SWORD_CENTER_X;
		spawner_top = SWORD_CENTER_Y;
		select_subpixel_for_rank(pattern_state.speed, 4.0f, 5.0f, 5.5f, 6.0f);
	}

	slash_animate();
	if(boss_phase_frame < SLASH_2_FRAME) {
		return;
	}
	if((boss_phase_frame < SLASH_4_FRAME) && ((boss_phase_frame % 3) == 0)) {
		slash_aimed_fire(spawner_left, spawner_top, pattern_state.speed);
		slash_spawner_step_from_2_to_4(spawner_left, spawner_top, 3);
	}

	if(boss_phase_frame == SLASH_4_FRAME) {
		spawner_left = SLASH_4_CORNER_X;
		spawner_top = SLASH_4_CORNER_Y;
	}
	if(boss_phase_frame < SLASH_4_FRAME) {
		return;
	}
	if(boss_phase_frame < SLASH_4_5_FRAME) {
		slash_aimed_fire(spawner_left, spawner_top, pattern_state.speed);
		slash_spawner_step_from_4_to_4_5(spawner_left, spawner_top, 1);
	}

	if(boss_phase_frame == SLASH_4_5_FRAME) {
		spawner_left = SLASH_5_CORNER_X;
		spawner_top = SLASH_5_CORNER_Y;
	}
	if(boss_phase_frame < SLASH_4_5_FRAME) {
		return;
	}
	if((boss_phase_frame < SLASH_6_FRAME) && ((boss_phase_frame % 2) == 0)) {
		slash_aimed_fire(spawner_left, spawner_top, pattern_state.speed);
		slash_spawner_step_from_4_5_to_6(spawner_left, spawner_top, 2);
	}
}

void pattern_semicircle_rain_from_sleeve(void)
{
	enum {
		SPREAD = 10,
	};
	int i;
	unsigned char angle;

	if(boss_phase_frame == 10) {
		face_expression_set_and_put(FE_AIM);
	}
	if(boss_phase_frame < 100) {
		return;
	}
	if((boss_phase_frame % 20) == 0) {
		for(i = 0, angle = 0x00; i < SPREAD; i++, angle -= (0x80 / SPREAD)) {
			pellets_add_single_rain(
				LEFT_SLEEVE_LEFT, LEFT_SLEEVE_TOP, angle, 2.0f
			);
		}
		mdrv2_se_play(7);
	} else if((boss_phase_frame % 20) == 10) {
		for(i = 0, angle = 0x00; i < SPREAD; i++, angle -= (0x80 / SPREAD)) {
			Pellets.add_single(
				LEFT_SLEEVE_LEFT, LEFT_SLEEVE_TOP, angle, to_sp(2.0f),
				PM_FALL_STRAIGHT_FROM_TOP_THEN_REGULAR, to_sp(3.0f)
			);
		}
		mdrv2_se_play(7);
	}
	if(boss_phase_frame >= 300) {
		boss_phase_frame = 0;
	}
}

enum kuji_flash_color_t {
	BLACK,
	WHITE
};

inline void kuji_flash(kuji_flash_color_t color) {
	if(color == BLACK) {
		z_palette_set_show(0, 0x0, 0x0, 0x0);
	} else {
		z_palette_set_show(0, 0xF, 0xF, 0xF);
	}
}

inline void kuji_put(kuji_flash_color_t flash_color, int image) {
	if(image == 7) {
		kuji_flash(flash_color);
		grz_load_single(0, GRZ_FN, image);
	} else {
		z_graph_clear();
		grz_load_single(0, GRZ_FN, image);
		kuji_flash(flash_color);
	}
	grx_put(0);
	if(image == 15) {
		grx_free(0);
	}
	frame_delay(10);
}

void konngara_main(void)
{
	static struct {
		bool16 invincible;
		int invincibility_frame;

		void update_and_render(const unsigned char (&flash_colors)[3]) {
			boss_hit_update_and_render(
				invincibility_frame,
				invincible,
				boss_hp,
				flash_colors,
				sizeof(flash_colors),
				10000,
				overlap_xy_xywh_le_ge_2(
					orb_cur_left,
					orb_cur_top,
					HITBOX_LEFT,
					HITBOX_TOP,
					(HITBOX_ORB_W - ORB_W),
					(HITBOX_ORB_H - ORB_H)
				),
				shot_hitbox_t(
					HITBOX_LEFT, HITBOX_TOP, HITBOX_SHOT_W, HITBOX_SHOT_H
				)
			);
		}
	} hit;

	enum {
		CHOOSE_NEW = 99,
	};

	// The IDs are associated with a different pattern in every phase.
	static int pattern_prev;
	static bool initial_hp_rendered;

	static struct {
		int pattern_cur;
		int patterns_done;

		void next(int8_t phase_new) {
			boss_phase = phase_new;
			boss_phase_frame = 0;
			hit.invincibility_frame = 0;
			pattern_cur = CHOOSE_NEW;
			patterns_done = 0;
			if(phase_new & 1) {
				face_expression_set_and_put(FE_NEUTRAL);
			}
		}

		void frame_common(face_direction_t& fd_new) {
			boss_phase_frame++;
			hit.invincibility_frame++;

			fd_new =
				(player_left < 198) ? FD_LEFT :
				(player_left > 396) ? FD_RIGHT : FD_CENTER;
			face_direction_set_and_put(fd_new);
		}
	} phase = { 0, 0 };

	int i;
	int j;
	int col;
	int comp;
	int scroll_frame;
	face_direction_t fd_track;
	const unsigned char flash_colors[3] = { 3, 4, 5 };

	#define pattern_choose( \
		phase, frame_min, count_on_first_try, count_on_second_try \
	) { \
		if(boss_phase_frame > frame_min) { \
			boss_phase_frame = 1; \
			phase.pattern_cur = (rand() % count_on_first_try); \
			if(phase.pattern_cur == pattern_prev) { \
				phase.pattern_cur = (rand() % count_on_second_try); \
			} \
			pattern_prev = phase.pattern_cur; \
			phase.patterns_done++; \
		} \
	}

	#define phase_frame_siddham_flash(phase, next_phase) { \
		if(boss_phase_frame == 50) { \
			siddham_col_white(); \
		} \
		if((boss_phase_frame > 50) && ((boss_phase_frame % 4) == 0)) { \
			siddham_col_white_in_step(); \
		} \
		\
		hit.update_and_render(flash_colors); \
		if(!hit.invincible && (boss_phase_frame > 120)) { \
			phase.next(next_phase); \
		} \
	}

	if(boss_phase == 0) {
		boss_phase = 1;
		pattern_prev = CHOOSE_NEW;
		phase.pattern_cur = CHOOSE_NEW;
		phase.patterns_done = 0;
		boss_phase_frame = 0;
		hit.invincibility_frame = 0;
		hit.invincible = false;
		initial_hp_rendered = false;
		boss_palette_snap();
		random_seed = frame_rand;
	} else if(boss_phase == 1) {
		// ZUN bug: Since the fight only ends in Phase 7 at the earliest, HP
		// subtraction in debug mode can lead to this function being called
		// with [boss_phase_frame] being larger than the initial HP value,
		// causing the heap corruption bug mentioned in the comment of this
		// function. Konngara starts with an even number of total HP, so this
		// will even happen for the easiest possible case of holding ↵ Return
		// for the first 10 frames of phase 1.
		hud_hp_increment_render(initial_hp_rendered, boss_hp, boss_phase_frame);

		phase.frame_common(fd_track);

		if(phase.pattern_cur == 0) {
			pattern_diamond_cross_to_edges_followed_by_rain();
		} else if(phase.pattern_cur == 1) {
			pattern_symmetrical_from_cup();
		} else if(phase.pattern_cur == 2) {
			pattern_two_homing_snakes_and_semicircle_spreads();
		} else if(phase.pattern_cur == CHOOSE_NEW) {
			pattern_choose(phase, 120, 3, 3);
		}
		if(boss_phase_frame == 0) {
			face_expression_set_and_put(FE_NEUTRAL);
			phase.pattern_cur = CHOOSE_NEW;
		}
		hit.update_and_render(flash_colors);
		if(!hit.invincible && ((phase.patterns_done >= 7) || (boss_hp < 16))) {
			if(phase.pattern_cur == CHOOSE_NEW) {
				phase.next(2);
			}
		}
	} else if(boss_phase == 2) {
		phase.frame_common(fd_track);
		phase_frame_siddham_flash(phase, 3);
	} else if(boss_phase == 3) {
		phase.frame_common(fd_track);

		if(phase.pattern_cur == 0) {
			pattern_aimed_rows_from_top();
		} else if(phase.pattern_cur == 1) {
			pattern_aimed_spray_from_cup();
		} else if(phase.pattern_cur == 2) {
			pattern_four_homing_snakes();
		} else if(phase.pattern_cur == 3) {
			pattern_rain_from_edges();
		} else if(phase.pattern_cur == CHOOSE_NEW) {
			pattern_choose(phase, 120, 4, 4);
		}

		if(boss_phase_frame == 0) {
			face_expression_set_and_put(FE_NEUTRAL);
			phase.pattern_cur = CHOOSE_NEW;
		}

		hit.update_and_render(flash_colors);
		if(!hit.invincible && ((phase.patterns_done >= 9) || (boss_hp < 13))) {
			if(phase.pattern_cur == CHOOSE_NEW) {
				phase.next(4);
			}
		}
	} else if(boss_phase == 4) {
		phase.frame_common(fd_track);
		phase_frame_siddham_flash(phase, 5);
	} else if(boss_phase == 5) {
		phase.frame_common(fd_track);

		if(phase.pattern_cur == 0) {
			pattern_slash_rain();
		} else if(phase.pattern_cur == 1) {
			pattern_lasers_and_3_spread();
		} else if(phase.pattern_cur == 2) {
			pattern_slash_triangular();
		} else if(phase.pattern_cur == CHOOSE_NEW) {
			pattern_choose(phase, 120, 3, 2);
		}

		if(boss_phase_frame == 0) {
			face_expression_set_and_put(FE_NEUTRAL);
			phase.pattern_cur = CHOOSE_NEW;
		}

		hit.update_and_render(flash_colors);
		if(!hit.invincible && ((phase.patterns_done >= 6) || (boss_hp < 10))) {
			if(phase.pattern_cur == CHOOSE_NEW) {
				phase.next(6);
			}
		}
	} else if(boss_phase == 6) {
		phase.frame_common(fd_track);
		phase_frame_siddham_flash(phase, 7);
	} else if(boss_phase == 7) {
		phase.frame_common(fd_track);

		if(phase.pattern_cur == 0) {
			pattern_diamond_cross_to_edges_followed_by_rain();
		} else if(phase.pattern_cur == 1) {
			pattern_symmetrical_from_cup();
		} else if(phase.pattern_cur == 2) {
			pattern_two_homing_snakes_and_semicircle_spreads();
		} else if(phase.pattern_cur == 3) {
			pattern_aimed_rows_from_top();
		} else if(phase.pattern_cur == 4) {
			pattern_aimed_spray_from_cup();
		} else if(phase.pattern_cur == 5) {
			pattern_four_homing_snakes();
		} else if(phase.pattern_cur == 6) {
			pattern_rain_from_edges();
		} else if(phase.pattern_cur == 7) {
			pattern_slash_rain();
		} else if(phase.pattern_cur == 8) {
			pattern_lasers_and_3_spread();
		} else if(phase.pattern_cur == 9) {
			pattern_slash_triangular();
		} else if(phase.pattern_cur == 10) {
			pattern_semicircle_rain_from_sleeve();
		} else if(phase.pattern_cur == 11) {
			pattern_slash_aimed();
		} else if(phase.pattern_cur == CHOOSE_NEW) {
			pattern_choose(phase, 5, 12, 2);
		}

		if(boss_phase_frame == 0) {
			face_expression_set_and_put(FE_NEUTRAL);
			phase.pattern_cur = CHOOSE_NEW;
		}

		hit.update_and_render(flash_colors);
		if(boss_hp > 0) {
			return;
		}

		// Defeat sequence (blocking)
		// ==========================

		printf("\x1B*"); // Clear text RAM
		konngara_free();
		z_graph_clear();
		mdrv2_bgm_stop();

		kuji_put(BLACK, 7);
		kuji_put(WHITE, 8);
		kuji_put(BLACK, 9);
		kuji_put(WHITE, 10);
		kuji_put(BLACK, 11);
		kuji_put(WHITE, 12);
		kuji_put(BLACK, 13);
		kuji_put(WHITE, 14);
		kuji_put(BLACK, 15);

		boss_phase_frame = 0;
		while(1) {
			enum {
				MAGNITUDE = -8
			};

			boss_phase_frame++;
			if((boss_phase_frame % 4) == 0) {
				z_palette_black_out_step(j, i);
				mdrv2_se_play(7);
			}
			z_vsync_wait_and_scrollup(
				(RES_Y - MAGNITUDE) - ((boss_phase_frame % 2) * (MAGNITUDE * 2))
			);
			if(boss_phase_frame > 64) {
				break;
			}
			frame_delay(1);
		}

		// Blit the scroll background, while covering the blit with ridiculously
		// slow text RAM clears to black and back to transparency.
		//
		// "Graph mode" (as opposed to "kanji mode") disables Shift-JIS decoding
		// inside NEC's IO.SYS. This allows new half-width glyphs at the
		// Shift-JIS lead byte code points, 0x81-0x9F and 0xE0-0xFF, to be
		// accessed via regular INT 29h text output, and consequently, printf().
		// Had to reverse-engineer that, only to find out that it has exactly
		// zero effect when printing spaces...
		// See https://github.com/joncampbell123/dosbox-x/pull/2547 for a
		// reimplementation of the original functionality into DOSBox-X.
		// --------------------------------------------------------------------

		printf("\x1B)3"); // Enter graph mode
		text_fill_black(j, i);

		grp_put(SCROLL_BG_FN, GPF_PALETTE_SHOW);
		z_palette_set_black(j, i);

		printf("\x1B)0"); // Back to regular kanji mode
		text_clear_sloppy(j, i);
		// --------------------------------------------------------------------

		// Final scroll
		// ------------

		#define scroll_speed	i
		#define line_on_top 	j

		line_on_top = 0;
		scroll_speed = 32;
		scroll_frame = 0;

		while(1) {
			z_vsync_wait_and_scrollup(line_on_top);
			line_on_top += scroll_speed;
			if(line_on_top > RES_Y) {
				line_on_top -= RES_Y;
			}
			if(scroll_frame < 150) {
				if((scroll_frame % 8) == 0) {
					z_palette_black_in_step_to(col, comp, grp_palette);
					mdrv2_se_play(7);
				}
			} else if((scroll_frame % 8) == 0) {
				if(scroll_frame == 192) {
					// We aren't playing anything, though?
					mdrv2_bgm_fade_out_nonblock();
				}
				z_palette_black_out_step_2(col, comp);
				if(z_Palettes[V_WHITE].c.r == 0) {
					break;
				}
				if(scroll_frame < 220) {
					mdrv2_se_play(7);
				}
			}
			scroll_frame++;
			frame_delay(1);
		}

		#undef line_on_top
		#undef scroll_speed
		// ------------

		z_vsync_wait_and_scrollup(0);

		// Jigoku clear! Grant 50,000 score points in the fanciest way
		for(j = 0; j < 5; j++) {
			score += 10000;
		}
		konngara_free(); // Yes, we already did this above :zunpet:
		game_cleared = true;
	}

	#undef phase_frame_siddham_flash
	#undef pattern_choose
}
