/// Jigoku Stage 15 Boss - Kikuri
/// -----------------------------

#include "th01/main/boss/palette.cpp"

#include "platform/x86real/pc98/page.hpp"
#include "th01/rank.h"
#include "th01/resident.hpp"
#include "th01/v_colors.hpp"
#include "th01/hardware/frmdelay.h"
#include "th01/hardware/graph.h"
#include "th01/hardware/grpinv32.hpp"
#include "th01/snd/mdrv2.h"
#include "th01/math/overlap.hpp"
#include "th01/sprites/pellet.h"
#include "th01/main/hud/hp.hpp"
#include "th01/main/player/player.hpp"
#include "th01/main/bullet/laser_s.hpp"
#include "th01/main/bullet/pellet.hpp"
#include "th01/main/boss/defeat.hpp"
#include "th01/main/boss/entity_a.hpp"
#include "th01/main/stage/palette.hpp"

// Coordinates
// -----------

static const screen_x_t DISC_CENTER_X = 320;
static const screen_y_t DISC_CENTER_Y = 180;
static const pixel_t DISC_RADIUS = 90;

static const screen_x_t EYE_LEFT_CENTER_X = 307;
static const screen_x_t EYE_RIGHT_CENTER_X = 336;
static const screen_y_t EYE_BOTTOM = 147;

// That's… not quite where the light ball is?
static const screen_x_t LIGHTBALL_CENTER_X = 320;
static const screen_y_t LIGHTBALL_CENTER_Y = 224;

static const pixel_t HITBOX_W = 128;
static const pixel_t HITBOX_H = 80;

static const screen_x_t HITBOX_LEFT = (DISC_CENTER_X - (HITBOX_W / 2));
static const screen_x_t HITBOX_RIGHT = (DISC_CENTER_X + (HITBOX_W / 2) - ORB_W);
static const screen_y_t HITBOX_CENTER_Y = (DISC_CENTER_Y - 8);

// Not the actual Y coordinates of the original hitbox, due to a sign confusion
// bug in kikuri_hittest_orb()!
static const screen_y_t HITBOX_TOP = (HITBOX_CENTER_Y - (HITBOX_H / 2));
static const screen_y_t HITBOX_BOTTOM = (
	HITBOX_CENTER_Y + (HITBOX_H / 2) - ORB_H
);


static const pixel_t SOUL_W = 32;
static const pixel_t SOUL_H = 32;
static const pixel_t TEAR_W = 16;
static const pixel_t TEAR_H = 16;
static const pixel_t RIPPLE_W = 16;
static const pixel_t RIPPLE_H = 16;

static const screen_x_t SOUL_AREA_LEFT = (PLAYFIELD_LEFT + (PLAYFIELD_W / 20));
static const screen_y_t SOUL_AREA_TOP = PLAYFIELD_TOP;
static const screen_x_t SOUL_AREA_RIGHT = (
	PLAYFIELD_RIGHT - (PLAYFIELD_W / 20) - SOUL_W
);
static const screen_y_t SOUL_AREA_BOTTOM = PLAYFIELD_BOTTOM;

static const screen_y_t TEAR_TOP_MAX = (PLAYFIELD_BOTTOM - TEAR_H);
// -----------

enum kikuri_colors_t {
	COL_LIGHTBALL = 5,
	COL_LASER = 10,
};

// Always denotes the last phase that ends with that amount of HP.
enum kikuri_hp_t {
	HP_TOTAL = 14,
	HP_PHASE_2_END = 10,
	HP_PHASE_5_END = 6,
	HP_PHASE_6_END = 0,
};

// State that's suddenly no longer shared with other bosses
// --------------------------------------------------------

#define boss_phase kikuri_phase
int8_t boss_phase;
// --------------------------------------------------------

// Entities
// --------

static const int SOUL_COUNT = 2;
static const int SOUL_CELS = 3;

static const int TEAR_COUNT = 10;

// Nonzero values are also used to indicate whether a given tear is alive.
int8_t tear_anim_frame[TEAR_COUNT];

CBossEntity souls_raw[SOUL_COUNT + 3];
CBossEntity tears[10];

#define souls reinterpret_cast<CBossEntitySized<SOUL_W, SOUL_H> *>(souls_raw)

#define kikuri_ent_load(tmp_i) { \
	souls[0].load("tamasii.bos", 0); \
	souls[1].metadata_assign(souls[0]); \
	\
	tears[0].load("tamasii2.bos", 1); \
	kikuri_ptn_load(); /* MODDERS: Don't nest these load calls. */ \
	\
	for(i = 1; i < TEAR_COUNT; i++) { \
		tears[i].metadata_assign(tears[0]); \
	} \
}

inline void kikuri_ent_free() {
	bos_entity_free(0);
	bos_entity_free(1);
}
// --------

// .PTN
// ----

static const main_ptn_slot_t PTN_SLOT_RIPPLE = PTN_SLOT_BOSS_1;
static const int PTN_RIPPLE = PTN_ID(PTN_SLOT_RIPPLE, 0);

enum kikuri_ripple_cel_t {
	C_RIPPLE_LOW = 0,
	C_RIPPLE_HIGH = 1,
	C_RIPPLE_FILLED = 2,
	C_RIPPLE_EMPTY = 3,
};

inline void kikuri_ptn_load(void) {
	ptn_load(PTN_SLOT_RIPPLE, "tamayen.ptn");
}

inline void kikuri_ptn_free(void) {
	ptn_free(PTN_SLOT_RIPPLE);
}
// ----

// Patterns
// --------

enum kikuri_phase_4_subphase_t {
	P4_SOUL_ACTIVATION = 0,
	P4_PATTERN = 1,
	P4_DONE = 2,

	_kikuri_phase_4_subphase_t_FORCE_INT16 = 0x7FFF
};

union {
	int interval;
	int speed_multiplied_by_8;
} pattern_state;
// --------

#include "th01/main/select_r.cpp"

void kikuri_load(void)
{
	int i;

	pellet_interlace = true;

	for(i = 0; i < TEAR_COUNT; i++) {
		tear_anim_frame[i] = 0;
	}

	kikuri_ent_load(i);
	void kikuri_setup(void);
	kikuri_setup();
}

void kikuri_setup(void)
{
	boss_phase = 0;
	boss_phase_frame = 0;

	// Same HP and phase settings as Elis.
	boss_hp = HP_TOTAL;
	hud_hp_first_white = HP_PHASE_2_END;
	hud_hp_first_redwhite = HP_PHASE_5_END;
}

void kikuri_free(void)
{
	kikuri_ent_free();
	kikuri_ptn_free();
}

bool16 near kikuri_hittest_orb(void)
{
	// Did you mean: > HITBOX_TOP? Using < describes a hitbox from the top of
	// the playfield *until* that point instead...
	if(
		(orb_cur_left > HITBOX_LEFT) && (orb_cur_left < HITBOX_RIGHT) &&
		(orb_cur_top < HITBOX_TOP) && (orb_cur_top < HITBOX_BOTTOM)
	) {
		return true;
	}
	return false;
}

void near soul_move_and_render(int i, pixel_t delta_x, pixel_t delta_y)
{
	souls[i].locked_move_unput_and_put_8(delta_x, delta_y, 1);
	if((boss_phase_frame % 12) == 0) {
		if(souls[i].image() >= (SOUL_CELS - 1)) {
			souls[i].set_image(0);
		} else {
			souls[i].set_image(souls[i].image() + 1);
		}
	}
}

void near tears_add(screen_x_t left, screen_y_t top)
{
	for(int i = 0; i < TEAR_COUNT; i++) {
		if(tear_anim_frame[i] == 0) {
			tears[i].pos_set(
				left, top,
				SOUL_AREA_LEFT, SOUL_AREA_RIGHT, SOUL_AREA_TOP, SOUL_AREA_BOTTOM
			);
			tears[i].set_image(0);
			tear_anim_frame[i] = 1;
			return;
		}
	}
}

bool16 near tear_ripple_hittest(screen_x_t left, pixel_t extra_w)
{
	if(player_invincible != true) {
		// Translation: 8 pixels in Reimu's center vs. 10 pixels in the ripple
		// sprite's center.
		//
		// ZUN bug: … except that ripples are rendered at byte-aligned X
		// positions. This collision detection uses the internal X coordinate
		// though, which can be (and due to the deterministic nature of this
		// part of the fight, regularly is) anywhere within that byte. This
		// ends up shifting this otherwise logical hitbox up to 7 pixels to the
		// right, compared to where you would expect it based on how the
		// sprites appear on screen. (Same as Mima's flame pillars.)
		//
		// (The ideal fix would be to introduce unaligned rendering for these
		// sprites, rather than byte-aligning the coordinates here. The latter
		// would fork the game, obviously.)
		if(
			(player_left >= (left - ((PLAYER_W / 4) + (RIPPLE_W / 2)))) &&
			(player_left <= (left + extra_w))
		) {
			player_is_hit = true;
			return true;
		}
	}
	return false;
}

void near tears_update_and_render(void)
{
	for(int i = 0; i < TEAR_COUNT; i++) {
		if(tear_anim_frame[i] != 0) {
			if(tears[i].cur_top <= TEAR_TOP_MAX) {
				tears[i].locked_move_unput_and_put_8(0, +8, 1);
			} else {
				void near ripple_update_and_render(
					screen_x_t tear_left, screen_y_t tear_top_max, int8_t &frame
				);
				ripple_update_and_render(
					tears[i].cur_left, TEAR_TOP_MAX, tear_anim_frame[i]
				);
			}
		}
	}
}

// Oh hey, ZUN did write the obvious wrapper function! Definitely nicer than
// the [ptn_sloppy_unput_before_alpha_put] hack, but it still suffers from the
// same word alignment bug.
void near ripple_unput_and_put(
	screen_x_t left, vram_y_t top, int ptn_id, int quarter
)
{
	ptn_sloppy_unput_quarter_16(left, top);
	ptn_put_quarter_8(left, top, ptn_id, quarter);
}

void near ripple_update_and_render(
	screen_x_t tear_left, screen_y_t tear_top_max, int8_t &frame
)
{
	// The ripple effect relies entirely on previous cels not being unblitted,
	// and the bottom 8 pixels of the C_RIPPLE_HIGH sprite being flood-filled.
	// Therefore, placing each successive C_RIPPLE_HIGH sprite 8 pixels above
	// the last one entirely avoids the need for C_RIPPLE_FILLED. (Using that
	// sprite would have ensured the stability of the animation against an
	// overlapping player Orb, though!)

	// Expects [ptn_sloppy_unput_before_alpha_put] to be `true`.
	#define unput_and_put(left, top, frame) { \
		ptn_put_quarter_8( \
			left, \
			(top - ( \
				(frame == 0) ? 0 : \
				(frame <= 5) ? (8 * (frame - 1)) : \
				(frame <= 9) ? (8 * (9 - frame)) : \
				0 \
			)), \
			PTN_RIPPLE, \
			( \
				(frame == 0) ? C_RIPPLE_LOW : \
				(frame <= 4) ? C_RIPPLE_HIGH : \
				(frame <= 9) ? C_RIPPLE_LOW : \
				C_RIPPLE_EMPTY /* effectively just unblitting the sprite */ \
			) \
		); \
	}

	#define unput_and_put_center(frame) { \
		unput_and_put((tear_left + ( 0 * RIPPLE_W)), tear_top_max, frame); \
	}
	#define unput_and_put_inner(frame) { \
		unput_and_put((tear_left + (-1 * RIPPLE_W)), tear_top_max, frame); \
		unput_and_put((tear_left + (+1 * RIPPLE_W)), tear_top_max, frame); \
	}
	#define unput_and_put_outer(frame) { \
		unput_and_put((tear_left + (-2 * RIPPLE_W)), tear_top_max, frame); \
		unput_and_put((tear_left + (+2 * RIPPLE_W)), tear_top_max, frame); \
	}

	frame++;

	// ZUN bug: Ripple sprites can be blitted to non-word-aligned X positions,
	// which this hack doesn't support, as explained in its comment. Using such
	// a hack in the first place only makes sense if you unblit and blit each
	// ripple column individually before moving on to the next one. Which the
	// code below does, by symmetrically moving out from the center to the
	// left and right edges. But then, unblitting every successive ripple
	// column by rounding its X coordinate down and up to the nearest word will
	// also cause half of the previously drawn column to be unblitted. This is
	// exactly why most ripple animations show up with weird empty 8-pixel-wide
	// stripes on the inside (→ non-word-aligned X positions), while some do
	// show up fine (→ word-aligned X positions).
	ptn_sloppy_unput_before_alpha_put = true;

	// Ultimate hardcoding! Using entities to track this state just wastes
	// space, right? (Hint: It doesn't, this does.)
	if(frame < 5) {
		unput_and_put_center(0);
		tear_ripple_hittest(tear_left, 0);
		mdrv2_se_play(7);
	} else if(frame < 10) {
		unput_and_put_center(1);
		tear_ripple_hittest(tear_left, 0);
	} else if(frame < 15) {
		tear_ripple_hittest((tear_left - RIPPLE_W), (RIPPLE_W * 2));
		unput_and_put_center(2);
		unput_and_put_inner(0);
	} else if(frame < 20) {
		tear_ripple_hittest((tear_left - RIPPLE_W), (RIPPLE_W * 2));
		unput_and_put_center(3);
		unput_and_put_inner(1);
	} else if(frame < 25) {
		tear_ripple_hittest((tear_left - (RIPPLE_W * 2)), (RIPPLE_W * 4));
		unput_and_put_center(4);
		unput_and_put_inner(2);
		unput_and_put_outer(0);
	} else if(frame < 30) {
		tear_ripple_hittest((tear_left - (RIPPLE_W * 2)), (RIPPLE_W * 4));
		unput_and_put_center(5);
		unput_and_put_inner(3);
		unput_and_put_outer(1);
	} else if(frame < 35) {
		tear_ripple_hittest((tear_left - (RIPPLE_W * 2)), (RIPPLE_W * 4));
		unput_and_put_center(6);
		unput_and_put_inner(4);
		unput_and_put_outer(2);
	} else if(frame < 40) {
		tear_ripple_hittest((tear_left - (RIPPLE_W * 2)), (RIPPLE_W * 4));
		unput_and_put_center(7);
		unput_and_put_inner(5);
		unput_and_put_outer(3);
	} else if(frame < 45) {
		tear_ripple_hittest((tear_left - (RIPPLE_W * 2)), (RIPPLE_W * 4));
		unput_and_put_center(8);
		unput_and_put_inner(6);
		unput_and_put_outer(4);
	} else if(frame < 50) {
		tear_ripple_hittest((tear_left - (RIPPLE_W * 2)), (RIPPLE_W * 4));
		unput_and_put_center(9);
		unput_and_put_inner(7);
		unput_and_put_outer(5);
	} else if(frame < 55) {
		tear_ripple_hittest((tear_left - (RIPPLE_W * 2)), (RIPPLE_W * 4));
		unput_and_put_center(10);
		unput_and_put_inner(8);
		unput_and_put_outer(6);
	} else if(frame < 60) {
		tear_ripple_hittest((tear_left - (RIPPLE_W * 2)), (RIPPLE_W * 4));
		unput_and_put_inner(9);
		unput_and_put_outer(7);
	} else if(frame < 65) {
		unput_and_put_inner(10);
		unput_and_put_outer(8);
	} else if(frame < 70) {
		unput_and_put_outer(9);
	} else if(frame < 75) {
		unput_and_put_outer(10);
	} else {
		frame = 0;
	}

	ptn_sloppy_unput_before_alpha_put = false;

	#undef unput_and_put_outer
	#undef unput_and_put_inner
	#undef unput_and_put_center
	#undef unput_and_put
}

// Must be called for the rest of the fight after the first call in order to
// not leave inactive soul, tear, and ripple sprites in VRAM. (Thankfully, the
// original game does that.)
inline void souls_move_diagonally_and_render__tears_update_and_render(
	pixel_t velocity_base_x, pixel_t velocity_base_y
) {
	pixel_t velocity_x = polar_x(0, velocity_base_x, boss_phase_frame);

	// Using polar_x() rather than polar_y() is what makes this movement
	// diagonal instead of elliptic.
	pixel_t velocity_y = polar_x(0, velocity_base_y, boss_phase_frame);

	tears_update_and_render();
	soul_move_and_render(0, +velocity_x, velocity_y);
	soul_move_and_render(1, -velocity_x, velocity_y);
}

// What's a EGC?
void near graph_copy_line_1_to_0_masked(vram_y_t y, dots16_t mask)
{
	vram_offset_t vo = vram_offset_muldiv(0, y);
	dots16_t p1;

	if((y < 0) || (y > (RES_Y - 1))) {
		return;
	}
	for(vram_word_amount_t word_x = 0; word_x < (ROW_SIZE / 2); word_x++) {
		page_access(1);	p1 = (peek(SEG_PLANE_B, vo) & mask);
		page_access(0);	_poke_(SEG_PLANE_B, vo, p1);
		page_access(1);	p1 = (peek(SEG_PLANE_R, vo) & mask);
		page_access(0);	_poke_(SEG_PLANE_R, vo, p1);
		page_access(1);	p1 = (peek(SEG_PLANE_G, vo) & mask);
		page_access(0);	_poke_(SEG_PLANE_G, vo, p1);
		page_access(1);	p1 = (peek(SEG_PLANE_E, vo) & mask);
		page_access(0);	_poke_(SEG_PLANE_E, vo, p1);
		vo += 2;
	}
}

inline void entrance_symmetric_line_1_to_0(
	const vram_y_t &y, pixel_t offset, dots16_t mask
) {
	graph_copy_line_1_to_0_masked((              y - offset), mask);
	graph_copy_line_1_to_0_masked(((RES_Y - 1) - y + offset), mask);
}

void near pattern_symmetric_spiral_from_disc(void)
{
	static unsigned char angle;
	static unsigned char drift;
	static pixel_t distance;
	screen_x_t left;
	screen_y_t top;

	if(boss_phase_frame < 100) {
		return;
	}
	if(boss_phase_frame == 100) {
		angle = 0x00;
		drift = 0x00;
		select_for_rank(pattern_state.interval, 4, 3, 2, 1);
		select_for_rank(distance,
			DISC_RADIUS, DISC_RADIUS, DISC_RADIUS, ((DISC_RADIUS / 2) + 5)
		);
	}
	if((boss_phase_frame % pattern_state.interval) == 0) {
		left = polar_x(DISC_CENTER_X, distance, (angle + 0x00));
		top = polar_y(DISC_CENTER_Y, distance, (angle + 0x00));
		Pellets.add_single(left, top, (angle + 0x00 + drift), to_sp(3.125f));

		left = polar_x(DISC_CENTER_X, distance, (angle + 0x80));
		top = polar_y(DISC_CENTER_Y, distance, (angle + 0x80));
		Pellets.add_single(left, top, (angle + 0x80 + drift), to_sp(3.125f));

		if(boss_phase_frame >= 900) {
			boss_phase_frame = 0;
		}
		angle -= 0x08;
		drift++;
	}
}

void near pattern_spinning_aimed_rings(void)
{
	enum {
		RING = 8,
	};

	screen_x_t left;
	screen_y_t top;
	int interval;

	select_for_rank(interval, 80, 60, 55, 50);

	if((boss_phase_frame % interval) != 0) {
		return;
	}
	for(int i = 0; i < RING; i++) {
		left = polar_x(
			(LIGHTBALL_CENTER_X - (PELLET_W / 2)), 16, (i * (0x100 / RING))
		);
		top = polar_y(LIGHTBALL_CENTER_Y, 16, (i * (0x100 / RING)));
		unsigned char angle = iatan2(
			((player_center_y() + (PELLET_H / 2)) - LIGHTBALL_CENTER_Y),
			((player_center_x() + (PELLET_W / 2)) - LIGHTBALL_CENTER_X)
		);
		Pellets.add_single(
			left,
			top,
			angle,
			to_sp(3.0f),
			PM_SPIN,
			to_sp(2.0f),
			(LIGHTBALL_CENTER_X - PELLET_W),
			LIGHTBALL_CENTER_Y
		);
	}
}

kikuri_phase_4_subphase_t near phase_4_souls_activate(void)
{
	if(boss_phase_frame == 200) {
		souls[0].pos_set(
			(LIGHTBALL_CENTER_X - (SOUL_W / 2)),
			(LIGHTBALL_CENTER_Y - (SOUL_H / 2)),
			SOUL_AREA_LEFT, SOUL_AREA_RIGHT, SOUL_AREA_TOP, SOUL_AREA_BOTTOM
		);
		souls[1].pos_set(
			(LIGHTBALL_CENTER_X - (SOUL_W / 2)),
			(LIGHTBALL_CENTER_Y - (SOUL_H / 2)),
			SOUL_AREA_LEFT, SOUL_AREA_RIGHT, SOUL_AREA_TOP, SOUL_AREA_BOTTOM
		);
	} else if((boss_phase_frame > 200) && ((boss_phase_frame % 2) == 0)) {
		soul_move_and_render(0, -4, -3);
		soul_move_and_render(1, +4, -3);
		if(souls[0].cur_top < (
			SOUL_AREA_TOP + playfield_fraction_y(2 / 21.0f)
		)) {
			return P4_PATTERN;
		}
	}
	return P4_SOUL_ACTIVATION;
}

kikuri_phase_4_subphase_t near pattern_souls_spreads(void)
{
	screen_x_t left;
	screen_y_t top;
	int unused;
	pellet_group_t group;

	soul_move_and_render(0, 0, 0);
	soul_move_and_render(1, 0, 0);

	select_for_rank(unused, 100, 80, 70, 60);

	if((boss_phase_frame % 80) == 0) {
		for(int i = 0; i < SOUL_COUNT; i++) {
			left = (souls[i].cur_center_x() - (PELLET_W / 2));
			top  = (souls[i].cur_center_y() - (PELLET_H / 1));
			select_for_rank(reinterpret_cast<int &>(group),
				PG_2_SPREAD_WIDE_AIMED,
				PG_3_SPREAD_WIDE_AIMED,
				PG_5_SPREAD_WIDE_AIMED,

				// Not aimed on Lunatic?
				// (Compare pattern_bat_slow_spreads() in the Elis fight.)
				PG_5_SPREAD_WIDE
			);
			Pellets.add_group(left, top, group, to_sp(3.4375f));
		}
	}
	// Note how [boss_phase_frame] carries over from phase_4_souls_activate().
	if(boss_phase_frame > 600) {
		return P4_DONE;
	}
	return P4_PATTERN;
}

void near pattern_souls_drop_tears_and_move_diagonally(void)
{
	if(boss_phase_frame < 10) {
		select_for_rank(pattern_state.interval, 200, 160, 140, 120);
	}
	if((boss_phase_frame % pattern_state.interval) == 0) {
		tears_add(
			(souls[0].cur_center_x() - (TEAR_W / 4)), // Not half?!
			(souls[0].cur_center_y() - (TEAR_H / 2))
		);
		tears_add(
			(souls[1].cur_center_x() - (TEAR_W / 4)), // Not half?!
			(souls[1].cur_center_y() - (TEAR_H / 2))
		);
	}
	souls_move_diagonally_and_render__tears_update_and_render(6, 2);
}

#define fire_aimed_eye_laser( \
	i, origin_left, aim_offset_x, speed_multiplied_by_8, w \
) { \
	shootout_lasers[i].spawn( \
		origin_left, \
		EYE_BOTTOM, \
		(player_left + aim_offset_x), \
		PLAYFIELD_BOTTOM, \
		speed_multiplied_by_8, \
		COL_LASER, \
		20, \
		w \
	); \
}

inline void fire_random_aimed_eye_laser(
	int i,
	screen_x_t origin_left,
	pixel_t aim_range_x,
	const int &speed_multiplied_by_8,
	pixel_t w
) {
	fire_aimed_eye_laser(
		i,
		origin_left,
		((irand() % (aim_range_x * 2)) - aim_range_x),
		speed_multiplied_by_8,
		w
	);
}

void near pattern_two_crossed_eye_lasers(void)
{
	// Yup, first firing on [boss_phase_frame] 400.
	if((boss_phase_frame > 200) && ((boss_phase_frame % 200) == 0)) {
		enum {
			LASER_W = 8,
			OFFSET_X = ((PLAYFIELD_W / 10) - (LASER_W / 2)),
		};
		fire_aimed_eye_laser(
			0, EYE_LEFT_CENTER_X, +OFFSET_X, (to_sp(6.25f) / 2), LASER_W
		);
		fire_aimed_eye_laser(
			1, EYE_RIGHT_CENTER_X, -OFFSET_X, (to_sp(6.25f) / 2), LASER_W
		);
		mdrv2_se_play(6);
	}
}

void near pattern_souls_single_aimed_pellet_and_move_diagonally(void)
{
	if((boss_phase_frame % 200) == 0) {
		Pellets.add_group(
			(souls[0].cur_center_x() - (PELLET_W / 2)),
			(souls[0].cur_center_y() - (PELLET_H / 2)),
			PG_1_AIMED,
			to_sp(2.5f)
		);
		Pellets.add_group(
			(souls[1].cur_center_x() - (PELLET_W / 2)),
			(souls[1].cur_center_y() - (PELLET_H / 2)),
			PG_1_AIMED,
			to_sp(2.5f)
		);
	}
	souls_move_diagonally_and_render__tears_update_and_render(4, 2);
}

int near pattern_4_spiral_along_disc(void)
{
	static unsigned char angle;

	if(boss_phase_frame < 100) {
		return 0;
	}
	if(boss_phase_frame == 100) {
		angle = 0x20;
		select_for_rank(pattern_state.interval, 14, 8, 6, 4);
	}
	if((boss_phase_frame % pattern_state.interval) == 0) {
		enum {
			RING = 2,
		};

		for(int i = 0; i < (RING * 2); i += 2) {
			screen_x_t left = polar_x(
				DISC_CENTER_X,
				DISC_RADIUS,
				((boss_phase_frame * 4) + ((0x100 / RING) * i))
			);
			screen_y_t top = polar_y(
				DISC_CENTER_Y,
				DISC_RADIUS,
				((boss_phase_frame * 4) + ((0x100 / RING) * i))
			);
			Pellets.add_single(left, top, (angle + 0x00), to_sp(2.25f));
			Pellets.add_single(left, top, (angle + 0x40), to_sp(2.25f));
			Pellets.add_single(left, top, (angle + 0x80), to_sp(2.25f));
			Pellets.add_single(left, top, (angle + 0xC0), to_sp(2.25f));
		}
		if(boss_phase_frame <= 600) {
			angle -= 0x05;
		} else {
			boss_phase_frame = 0;
			return 1;
		}
	}
	return 0;
}

int near pattern_single_lasers_from_left_eye(void)
{
	enum {
		ORIGIN_X = EYE_LEFT_CENTER_X,
		LASER_W = 4,

		// Should *technically* subtract (LASER_W / 2), as seen in
		// pattern_two_crossed_eye_lasers().
		RANGE_X = ((PLAYFIELD_W / 10) - LASER_W),
	};

	if(boss_phase_frame <= 200) { // ZUN bloat
		return 1;
	}
	if(boss_phase_frame == 250) {
		select_laser_speed_for_rank(pattern_state.speed_multiplied_by_8,
			6.5f, 7.0f, 7.5f, 8.0f
		);
		mdrv2_se_play(6);
		fire_random_aimed_eye_laser(
			0, ORIGIN_X, RANGE_X, pattern_state.speed_multiplied_by_8, LASER_W
		);
	} else if(boss_phase_frame == 280) {
		mdrv2_se_play(6);
		fire_random_aimed_eye_laser(
			1, ORIGIN_X, RANGE_X, pattern_state.speed_multiplied_by_8, LASER_W
		);
	} else if(boss_phase_frame == 310) {
		mdrv2_se_play(6);
		fire_random_aimed_eye_laser(
			2, ORIGIN_X, RANGE_X, pattern_state.speed_multiplied_by_8, LASER_W
		);
	} else if(boss_phase_frame == 340) {
		mdrv2_se_play(6);
		fire_random_aimed_eye_laser(
			3, ORIGIN_X, RANGE_X, pattern_state.speed_multiplied_by_8, LASER_W
		);
	} else if(boss_phase_frame == 370) {
		mdrv2_se_play(6);
		fire_random_aimed_eye_laser(
			4, ORIGIN_X, RANGE_X, pattern_state.speed_multiplied_by_8, LASER_W
		);
	} else if(boss_phase_frame == 400) {
		mdrv2_se_play(6);
		fire_random_aimed_eye_laser(
			5, ORIGIN_X, RANGE_X, pattern_state.speed_multiplied_by_8, LASER_W
		);
	}
	if(boss_phase_frame > 500) {
		boss_phase_frame = 0;
		return 2;
	}
	return 1;
}

int near pattern_souls_symmetric_rain_lines(void)
{
	if(boss_phase_frame > 100) {
		// Yes, this condition can never be true here. This pattern always runs
		// after pattern_single_lasers_from_left_eye(), so it reuses the
		// [pattern_state] of that one (a laser speed), and reinterprets it as
		// an interval. Therefore, the actual values are (52, 56, 60, 64).
		if(boss_phase_frame == 100) {
			select_for_rank(pattern_state.interval, 35, 25, 23, 22);
		}
		if((boss_phase_frame % pattern_state.interval) == 0) {
			for(int i = 0; i < SOUL_COUNT; i++) {
				#define fire(i, angle, speed_base) { \
					pellets_add_single_rain( \
						(souls[i].cur_center_x() - (PELLET_W / 2)), \
						(souls[i].cur_center_y() - (PELLET_H / 2)), \
						angle, \
						speed_base \
					); \
				}

				fire(i, 0x00, 3.0f);
				fire(i, 0x00, 2.0f);
				fire(i, 0x00, 1.0f);
				fire(i, 0x80, 1.0f);
				fire(i, 0x80, 2.0f);
				fire(i, 0x80, 3.0f);
				mdrv2_se_play(7);

				#undef fire
			}
		}
	}
	if(boss_phase_frame > 250) {
		boss_phase_frame = 0;
		return 3;
	}
	return 2;
}

int near pattern_vertical_lasers_from_top(void)
{
	enum {
		LASER_COUNT = 10,
		INTERVAL = 10,
		DISTANCE_X = (PLAYFIELD_W / LASER_COUNT),

		KEYFRAME_START = 100,
		KEYFRAME_END = (KEYFRAME_START + ((LASER_COUNT - 1) * INTERVAL)),
	};
	// [shootout_lasers] would be indexed out of bounds otherwise.
	static_assert(LASER_COUNT <= SHOOTOUT_LASER_COUNT);

	static pixel_t random_range_x_half;

	if(boss_phase_frame < KEYFRAME_START) {
		return 3;
	}
	if(boss_phase_frame == KEYFRAME_START) {
		select_laser_speed_for_rank(pattern_state.speed_multiplied_by_8,
			7.5f, 8.0f, 8.5f, 9.0f
		);
		select_for_rank(random_range_x_half,
			0, (PLAYFIELD_W / 64), (PLAYFIELD_W / 40), (PLAYFIELD_W / 32)
		);
	}
	if((boss_phase_frame % INTERVAL) == 0) {
		int i = ((boss_phase_frame - KEYFRAME_START) / INTERVAL);
		pixel_t random_offset_x = (
			(irand() % ((random_range_x_half * 2) + 1)) - random_range_x_half
		);
		shootout_lasers[i].spawn(
			(PLAYFIELD_LEFT + (i * DISTANCE_X + random_offset_x)),
			PLAYFIELD_TOP,
			(PLAYFIELD_LEFT + (i * DISTANCE_X + random_offset_x)),
			PLAYFIELD_BOTTOM,
			pattern_state.speed_multiplied_by_8,
			COL_LASER,
			20,
			8
		);
		mdrv2_se_play(6);
	}
	if(boss_phase_frame >= KEYFRAME_END) {
		boss_phase_frame = 0;
		return 0;
	}
	return 3;
}

void kikuri_main(void)
{
	static struct {
		bool16 invincible;
		int invincibility_frame;

		void update_and_render(const vc_t (&flash_colors)[4]) {
			boss_hit_update_and_render(
				invincibility_frame,
				invincible,
				boss_hp,
				flash_colors,
				(sizeof(flash_colors) / sizeof(flash_colors[0])),
				7000,
				kikuri_hittest_orb()
			);
		}
	} hit;
	static pixel_t entrance_ring_radius_base;
	static bool initial_hp_rendered;
	static struct {
		union {
			kikuri_phase_4_subphase_t subphase_4;
			int phase_6_pattern;
		} u1;
		int patterns_done;

		void frame_common(void) const {
			boss_phase_frame++;
			hit.invincibility_frame++;
		}
	} phase = { P4_SOUL_ACTIVATION, 0 };

	int i;
	const vc_t flash_colors[] = { 6, 11, 8, 2 };

	// Entrance animation
	if(boss_phase == 0) {
		// Barn door transition
		// --------------------

		enum {
			Y_END = (RES_Y / 2),
		};
		#define y hit.invincibility_frame

		boss_phase_frame = 0;
		y = 0;
		hit.invincible = false;

		// MODDERS: Loop over [flash_colors] instead.
		z_palette_set_show( 2, RGB4::max(), RGB4::max(), RGB4::max());
		z_palette_set_show( 6, RGB4::max(), RGB4::max(), RGB4::max());
		z_palette_set_show( 8, RGB4::max(), RGB4::max(), RGB4::max());
		z_palette_set_show(11, RGB4::max(), RGB4::max(), RGB4::max());

		while(1) {
			boss_phase_frame++;
			if((boss_phase_frame % 3) == 0) {
				if(y < Y_END) {
					entrance_symmetric_line_1_to_0(y,  0, 0x2222); // (  * )
				}
				if(((boss_phase_frame * 2) >  8) && (y < (Y_END +  8))) {
					entrance_symmetric_line_1_to_0(y,  8, 0xAAAA); // (* * )
				}
				if(((boss_phase_frame * 2) > 16) && (y < (Y_END + 16))) {
					entrance_symmetric_line_1_to_0(y, 16, 0xEEEE); // (*** )
				}
				if(((boss_phase_frame * 2) > 24) && (y <= (Y_END + 24))) {
					entrance_symmetric_line_1_to_0(y, 24, 0xFFFF); // (****)
				}
				y++;
				if(y > (Y_END + 24)) {
					hit.invincibility_frame = 0;
					boss_phase_frame = 0;
					break;
				}
			}

			// Well, if we're blocking and overwriting VRAM page 0...
			// Not much point in restricting these to the rows that actually
			// overwrote those sprites.
			player_put_default();
			orb_put_default();

			frame_delay(1);
		}

		#undef y
		// --------------------

		// Entrance rings
		// --------------

		while(1) {
			#define frame_half	boss_phase_frame

			int tmp;

			frame_half++;
			if(entrance_rings_update_and_render(
				entrance_ring_radius_base, i, tmp, frame_half, 0, 70
			)) {
				boss_phase = 2;
				phase.patterns_done = 0;
				boss_phase_frame = 0;
				boss_palette_show();
				initial_hp_rendered = false;
				stage_palette_set(z_Palettes);
				break;
			}
entrance_rings_still_active:
			// Huh? On 29 out of 30 frames? (And also useless: At a speed of 1
			// intensity value per frame, any 4-bit source color will have been
			// ramped to any 4-bit target color by the end of frame 86.)
			if((frame_half > 71) && ((frame_half % 30) != 0)) {
				for(i = 0; i < COMPONENT_COUNT; i++) {
					// MODDERS: Loop over [flash_colors] instead.
					if(boss_palette[ 2].v[i] < z_Palettes[ 2].v[i]) {
						z_Palettes[ 2].v[i]--;
					}
					if(boss_palette[ 6].v[i] < z_Palettes[ 6].v[i]) {
						z_Palettes[ 6].v[i]--;
					}
					if(boss_palette[ 8].v[i] < z_Palettes[ 8].v[i]) {
						z_Palettes[ 8].v[i]--;
					}
					if(boss_palette[11].v[i] < z_Palettes[11].v[i]) {
						z_Palettes[11].v[i]--;
					}
				}
				z_palette_set_all_show(z_Palettes);
			}
			if(frame_half % 2) { // That's why we've renamed the variable
				frame_delay(1);
			}
			#undef frame_half
		}
		// --------------
	} else if(boss_phase == 2) {
		hud_hp_increment_render(initial_hp_rendered, boss_hp, boss_phase_frame);
		phase.frame_common();
		pattern_symmetric_spiral_from_disc();
		hit.update_and_render(flash_colors);
		if(boss_phase_frame == 0) {
			phase.patterns_done++;
		}
		if(!hit.invincible && (
			(boss_hp <= HP_PHASE_2_END) || (phase.patterns_done >= 6)
		)) {
			boss_phase = 3;
			boss_phase_frame = 0;
			hit.invincibility_frame = 0;
			phase.patterns_done = 0;
		}
	} else if(boss_phase == 3) {
		boss_phase_frame++;

		// Original color: (0xB, 0xB, 0xF)
		//   Target color: (0xF, 0xB, 0xA)
		enum {
			FADE_INTERVAL = 20,
			FADE_STEPS = (0xF - 0xA),
		};

		if((boss_phase_frame % FADE_INTERVAL) == (FADE_INTERVAL - 1)) {
			z_Palettes[COL_LIGHTBALL].c.r++;
			z_Palettes[COL_LIGHTBALL].c.b--;
			stage_palette[COL_LIGHTBALL].c.r++;
			stage_palette[COL_LIGHTBALL].c.b--;
			z_palette_set_all_show(stage_palette);
		}
		if(boss_phase_frame >= (FADE_INTERVAL * FADE_STEPS)) {
			boss_phase = 4;
			boss_phase_frame = 0;
			phase.u1.subphase_4 = P4_SOUL_ACTIVATION;
			z_palette_set_all_show(stage_palette);
			boss_palette_snap();
		}
	} else if(boss_phase == 4) {
		phase.frame_common();
		pattern_spinning_aimed_rings();

		if(phase.u1.subphase_4 == P4_SOUL_ACTIVATION) {
			phase.u1.subphase_4 = phase_4_souls_activate();
		} else {
			phase.u1.subphase_4 = pattern_souls_spreads();
		}

		hit.update_and_render(flash_colors);
		if(!hit.invincible && (phase.u1.subphase_4 == P4_DONE)) {
			boss_phase = 5;

			// Should be done during phase 6 initialization for clarity.
			phase.u1.phase_6_pattern = 0;

			boss_phase_frame = 0;
		}
	} else if(boss_phase == 5) {
		phase.frame_common();
		pattern_souls_drop_tears_and_move_diagonally();
		pattern_two_crossed_eye_lasers();
		hit.update_and_render(flash_colors);
		if(!hit.invincible && (
			(boss_hp <= HP_PHASE_5_END) || (boss_phase_frame > 1600)
		)) {
			boss_phase = 6;
			boss_phase_frame = 0;
			hit.invincibility_frame = 0;
			phase.patterns_done = 0;
		}
	} else if(boss_phase == 6) {
		phase.frame_common();
		pattern_souls_single_aimed_pellet_and_move_diagonally();

		if(phase.u1.phase_6_pattern == 0) {
			phase.u1.phase_6_pattern = pattern_4_spiral_along_disc();
		} else if(phase.u1.phase_6_pattern == 1) {
			phase.u1.phase_6_pattern = pattern_single_lasers_from_left_eye();
		} else if(phase.u1.phase_6_pattern == 2) {
			phase.u1.phase_6_pattern = pattern_souls_symmetric_rain_lines();
		} else if(phase.u1.phase_6_pattern == 3) {
			phase.u1.phase_6_pattern = pattern_vertical_lasers_from_top();
		}
		if(boss_phase_frame == 0) {
			phase.patterns_done++;
		}

		// That's a well-hidden timeout condition! Especially since there is no
		// corresponding HP rendering call to reflect this change in the HUD.
		if(phase.patterns_done > 29) {
			boss_hp = 1;
		}

		hit.update_and_render(flash_colors);
		if(boss_hp <= 0) {
			mdrv2_bgm_fade_out_nonblock();
			Pellets.unput_and_reset_nonclouds();
			shootout_lasers_unput_and_reset_broken(i, 4); // 4? Doubly broken...
			boss_defeat_animate();
		}
	}
}
