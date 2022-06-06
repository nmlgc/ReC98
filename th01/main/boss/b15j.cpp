/// Jigoku Stage 15 Boss - Kikuri
/// -----------------------------

#include <stddef.h>
#include "th01/main/boss/palette.cpp"

#include "planar.h"
#include "th01/v_colors.hpp"
extern "C" {
#include "th01/hardware/egc.h"
#include "th01/hardware/input.hpp"
#include "th01/formats/ptn.hpp"
}
#include "th01/formats/pf.hpp"
#include "th01/math/area.hpp"
#include "th01/math/overlap.hpp"
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
static const pixel_t RIPPLE_W = 16;
static const pixel_t RIPPLE_H = 16;

static const screen_x_t SOUL_AREA_LEFT = (PLAYFIELD_LEFT + (PLAYFIELD_W / 20));
static const screen_y_t SOUL_AREA_TOP = PLAYFIELD_TOP;
static const screen_x_t SOUL_AREA_RIGHT = (
	PLAYFIELD_RIGHT - (PLAYFIELD_W / 20) - SOUL_W
);
static const screen_y_t SOUL_AREA_BOTTOM = PLAYFIELD_BOTTOM;
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

inline void kikuri_ptn_load(void) {
	ptn_load(PTN_SLOT_RIPPLE, "tamayen.ptn");
}

inline void kikuri_ptn_free(void) {
	ptn_free(PTN_SLOT_RIPPLE);
}
// ----

// Patterns
// --------

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
