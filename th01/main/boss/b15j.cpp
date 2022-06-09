/// Jigoku Stage 15 Boss - Kikuri
/// -----------------------------

#include <stddef.h>
#include "th01/main/boss/palette.cpp"

#include "x86real.h"
#include "planar.h"
#include "master.hpp"
#include "th01/v_colors.hpp"
extern "C" {
#include "th01/hardware/egc.h"
#include "th01/hardware/graph.h"
#include "th01/hardware/input.hpp"
#include "th01/snd/mdrv2.h"
#include "th01/formats/ptn.hpp"
}
#include "th01/formats/pf.hpp"
#include "th01/math/area.hpp"
#include "th01/math/overlap.hpp"
#include "th01/math/polar.hpp"
#include "th01/math/subpixel.hpp"
#include "th01/sprites/pellet.h"
#include "th01/main/particle.hpp"
extern "C" {
#include "th01/main/playfld.hpp"
}
#include "th01/main/vars.hpp"
#include "th01/main/hud/hp.hpp"
#include "th01/main/bullet/pellet.hpp"
#include "th01/main/boss/boss.hpp"
#include "th01/main/boss/entity_a.hpp"
#include "th01/main/player/orb.hpp"
#include "th01/main/player/player.hpp"

// Coordinates
// -----------

static const screen_x_t DISC_CENTER_X = 320;
static const screen_y_t DISC_CENTER_Y = 180;
static const pixel_t DISC_RADIUS = 90;

// That's… not quite where the light ball is?
static const screen_x_t LIGHTBALL_CENTER_X = 320;
static const screen_y_t LIGHTBALL_CENTER_Y = 224;

static const pixel_t HITBOX_W = 96;
static const pixel_t HITBOX_H = 48;

static const screen_x_t HITBOX_LEFT = (
	DISC_CENTER_X - (HITBOX_W / 2) - (ORB_W / 2)
);
static const screen_x_t HITBOX_RIGHT = (
	DISC_CENTER_X + (HITBOX_W / 2) - (ORB_W / 2)
);

// Not the actual Y coordinates of the original hitbox, due to a sign confusion
// bug in kikuri_hittest_orb()!
static const screen_y_t HITBOX_TOP = (DISC_CENTER_Y - HITBOX_H);
static const screen_y_t HITBOX_BOTTOM = DISC_CENTER_Y;

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

// Always denotes the last phase that ends with that amount of HP.
enum kikuri_hp_t {
	HP_TOTAL = 14,
	PHASE_2_END_HP = 10,
	PHASE_5_END_HP = 6,
	PHASE_6_END_HP = 0,
};

// State that's suddenly no longer shared with other bosses
// --------------------------------------------------------

#define boss_phase kikuri_phase
extern int8_t boss_phase;
// --------------------------------------------------------

// Entities
// --------

static const int SOUL_COUNT = 2;
static const int SOUL_CELS = 3;

static const int TEAR_COUNT = 10;

#define tear_anim_frame	kikuri_tear_anim_frame
#define souls          	kikuri_souls
#define tears          	kikuri_tears
// Nonzero values are also used to indicate whether a given tear is alive.
extern int8_t tear_anim_frame[TEAR_COUNT];

extern CBossEntitySized<SOUL_W, SOUL_H> souls[SOUL_COUNT + 3];
extern CBossEntity tears[10];

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

#define flash_colors	kikuri_flash_colors
#define invincible	kikuri_invincible
#define invincibility_frame	kikuri_invincibility_frame
#define initial_hp_rendered	kikuri_initial_hp_rendered
extern bool16 invincible;
extern int invincibility_frame;
extern bool initial_hp_rendered;

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

	_kikuri_phase_4_subphase_t_FORCE_INT16 = 0x7FFF
};

#define pattern_state	kikuri_pattern_state
extern union {
	int interval;
	int speed_multiplied_by_8;
} pattern_state;
// --------

#define select_for_rank kikuri_select_for_rank
#include "th01/main/select_r.cpp"

void kikuri_load(void)
{
	int i;
	int j;

	pellet_interlace = true;
	Pellets.unknown_seven = 7;
	palette_copy(boss_palette, z_Palettes, i, j);

	for(i = 0; i < TEAR_COUNT; i++) {
		tear_anim_frame[i] = 0;
	}

	kikuri_ent_load(i);
	void kikuri_setup(void);
	kikuri_setup();
	particles_unput_update_render(PO_INITIALIZE, V_WHITE);
}

void kikuri_setup(void)
{
	int col;
	int comp;

	boss_phase = 0;
	boss_phase_frame = 0;

	// Same HP and phase settings as Elis.
	boss_hp = HP_TOTAL;
	hud_hp_first_white = PHASE_2_END_HP;
	hud_hp_first_redwhite = PHASE_5_END_HP;

	// Redundant – already called before the sprites are first rendered, and
	// (0, 0) isn't used to indicate "soul is not alive".
	souls[0].pos_set(0, 0, 50,
		SOUL_AREA_LEFT, SOUL_AREA_RIGHT, SOUL_AREA_TOP, SOUL_AREA_BOTTOM
	);
	souls[1].pos_set(0, 0, 50,
		SOUL_AREA_LEFT, SOUL_AREA_RIGHT, SOUL_AREA_TOP, SOUL_AREA_BOTTOM
	);

	palette_set_grayscale(boss_post_defeat_palette, 0x0, col, comp);
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

void pascal near soul_move_and_render(int i, pixel_t delta_x, pixel_t delta_y)
{
	souls[i].move_lock_unput_and_put_8(0, delta_x, delta_y, 1);
	if((boss_phase_frame % 12) == 0) {
		if(souls[i].bos_image >= (SOUL_CELS - 1)) {
			souls[i].bos_image = 0;
		} else {
			souls[i].set_image(souls[i].bos_image + 1);
		}
	}
}

void pascal near tears_add(screen_x_t left, screen_y_t top)
{
	for(int i = 0; i < TEAR_COUNT; i++) {
		if(tear_anim_frame[i] == 0) {
			tears[i].pos_set(
				left, top, 50,
				SOUL_AREA_LEFT, SOUL_AREA_RIGHT, SOUL_AREA_TOP, SOUL_AREA_BOTTOM
			);
			tears[i].bos_image = 0;
			tear_anim_frame[i] = 1;
			return;
		}
	}
}

bool16 pascal near tear_ripple_hittest(screen_x_t left, pixel_t extra_w)
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
		// sprites appear on screen.
		//
		// (The ideal fix would be to introduce unaligned rendering for these
		// sprites, rather than byte-aligning the coordinates here. The latter
		// would fork the game, obviously.)
		if(
			(player_left >= (left - ((PLAYER_W / 4) + (RIPPLE_W / 2)))) &&
			(player_left <= (left + extra_w))
		) {
			done = true;
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
				tears[i].move_lock_unput_and_put_8(0, 0, +8, 1);
			} else {
				void pascal near ripple_update_and_render(
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
void pascal near ripple_unput_and_put(
	screen_x_t left, vram_y_t top, int ptn_id, int quarter
)
{
	ptn_sloppy_unput_quarter_16(left, top);
	ptn_put_quarter_8(left, top, ptn_id, quarter);
}

void pascal near ripple_update_and_render(
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
	// also cause half  of the previously drawn column to be unblitted. This is
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

// What's a EGC?
void pascal near graph_copy_line_1_to_0_masked(vram_y_t y, dots16_t mask)
{
	vram_offset_t vo = vram_offset_muldiv(0, y);
	dots16_t p1;

	if((y < 0) || (y > (RES_Y - 1))) {
		return;
	}
	for(vram_word_amount_t word_x = 0; word_x < (ROW_SIZE / 2); word_x++) {
		graph_accesspage_func(1);	p1 = (peek(SEG_PLANE_B, vo) & mask);
		graph_accesspage_func(0);	poke2(SEG_PLANE_B, vo, p1);
		graph_accesspage_func(1);	p1 = (peek(SEG_PLANE_R, vo) & mask);
		graph_accesspage_func(0);	poke2(SEG_PLANE_R, vo, p1);
		graph_accesspage_func(1);	p1 = (peek(SEG_PLANE_G, vo) & mask);
		graph_accesspage_func(0);	poke2(SEG_PLANE_G, vo, p1);
		graph_accesspage_func(1);	p1 = (peek(SEG_PLANE_E, vo) & mask);
		graph_accesspage_func(0);	poke2(SEG_PLANE_E, vo, p1);
		vo += 2;
	}
}

void near pattern_symmetric_spiral_from_disc(void)
{
	#define angle   	pattern0_angle
	#define drift   	pattern0_drift
	#define distance	pattern0_distance

	extern unsigned char angle;
	extern unsigned char drift;
	extern pixel_t distance;
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

	#undef distance
	#undef drift
	#undef angle
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
			(LIGHTBALL_CENTER_Y - (SOUL_H / 2)), 50,
			SOUL_AREA_LEFT, SOUL_AREA_RIGHT, SOUL_AREA_TOP, SOUL_AREA_BOTTOM
		);
		souls[1].pos_set(
			(LIGHTBALL_CENTER_X - (SOUL_W / 2)),
			(LIGHTBALL_CENTER_Y - (SOUL_H / 2)), 50,
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
