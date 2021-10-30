/// Makai Stage 15 Boss - Elis
/// --------------------------

extern "C" {
#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th01/v_colors.hpp"
#include "th01/math/area.hpp"
#include "th01/math/subpixel.hpp"
#include "th01/hardware/egc.h"
#include "th01/hardware/graph.h"
#include "th01/formats/pf.hpp"
#include "th01/formats/grc.hpp"
#include "th01/formats/ptn.hpp"
#include "th01/main/playfld.hpp"
#include "th01/main/vars.hpp"
#include "th01/main/boss/entity_a.hpp"
}
#include "th01/shiftjis/fns.hpp"
#undef MISSILE_FN
#define MISSILE_FN boss3_m_ptn_1
extern const char MISSILE_FN[];
#include "th01/sprites/pellet.h"
#include "th01/main/shape.hpp"
#include "th01/main/particle.hpp"
#include "th01/main/boss/boss.hpp"
#include "th01/main/boss/palette.hpp"
#include "th01/main/bullet/missile.hpp"
#include "th01/main/bullet/pellet.hpp"
#include "th01/main/hud/hp.hpp"

// Coordinates
// -----------

static const pixel_t GIRL_W = 128;
static const pixel_t GIRL_H = 96;
static const pixel_t BAT_W = 48;
static const pixel_t BAT_H = 32;

static const pixel_t BASE_LEFT = (PLAYFIELD_CENTER_X - (GIRL_W / 2));
static const pixel_t BASE_TOP = (
	PLAYFIELD_TOP + ((PLAYFIELD_H / 21) * 5) - (GIRL_H / 2)
);
// -----------

#define stars	elis_stars
#define flash_colors	elis_flash_colors
#define invincibility_frame	elis_invincibility_frame
#define invincible	elis_invincible
#define wave_teleport_done	elis_wave_teleport_done
#define initial_hp_rendered	elis_initial_hp_rendered
extern int invincibility_frame;
extern bool16 invincible;
extern bool16 wave_teleport_done;
extern bool initial_hp_rendered;

// Entities
// --------

enum still_or_wave_cel_t {
	C_STILL = 0,
	C_WAVE_1 = 2,
	C_WAVE_2 = 3,
	C_WAVE_3 = 4,
	C_WAVE_4 = 5,
};

// "Girl" sprites
#define ent_still_or_wave	boss_entities[0]
#define ent_attack       	boss_entities[1]

#define ent_bat          	boss_entities[2]

inline void ent_attack_sync_with_still_or_wave(void) {
	ent_attack.pos_cur_set(
		ent_still_or_wave.cur_left, ent_still_or_wave.cur_top
	);
}

static const main_ptn_slot_t PTN_SLOT_BG_ENT = PTN_SLOT_BOSS_1;
static const main_ptn_slot_t PTN_SLOT_MISSILE = PTN_SLOT_BOSS_2;

static inline void ent_free(void) {
	bos_entity_free(0);
	bos_entity_free(1);
	bos_entity_free(2);
	grc_free(GRC_SLOT_BOSS_1);
	ptn_free(PTN_SLOT_BG_ENT);
	ptn_free(PTN_SLOT_MISSILE);
}
// --------

// TODO: Remove once all functions are part of this translation unit
#define nopcall_workaround(func, v) __asm { \
	push v; push cs; call near ptr func; pop cx; \
}

void girl_bg_snap(int unncessary_parameter_that_still_needs_to_be_1_or_2)
;
#define girl_bg_snap(v) nopcall_workaround(girl_bg_snap, v)

void girl_bg_put(int unncessary_parameter_that_still_needs_to_be_1_or_2)
;
#define girl_bg_put(v) nopcall_workaround(girl_bg_put, v)

void elis_load(void)
{
	extern const char boss5_bos[];
	extern const char boss5_2_bos[];
	extern const char boss5_3_bos[];
	extern const char boss5_gr_grc[];

	pellet_interlace = true;
	Pellets.unknown_seven = 7;
	ent_still_or_wave.load(boss5_bos, 0);
	ent_attack.load(boss5_2_bos, 1);
	ent_bat.load(boss5_3_bos, 2);
	grc_load(GRC_SLOT_BOSS_1, boss5_gr_grc);
	ptn_new(PTN_SLOT_BG_ENT, ((GIRL_W / PTN_W) * (GIRL_H / PTN_H)));
	Missiles.load(PTN_SLOT_MISSILE);
	boss_palette_snap();
	void elis_setup(void);
	elis_setup();
	particles_unput_update_render(PO_INITIALIZE, V_WHITE);
}

void elis_setup(void)
{
	int col;
	int comp;

	ent_still_or_wave.pos_set(
		BASE_LEFT, BASE_TOP, 48,
		PLAYFIELD_LEFT, (PLAYFIELD_RIGHT + ((GIRL_W / 4) * 3)),
		PLAYFIELD_TOP, (PLAYFIELD_BOTTOM - GIRL_H)
	);
	ent_attack.pos_set(
		BASE_LEFT, BASE_TOP, 48,
		PLAYFIELD_LEFT, (PLAYFIELD_RIGHT + ((GIRL_W / 4) * 3)),
		PLAYFIELD_TOP, (PLAYFIELD_BOTTOM - GIRL_H)
	);
	ent_bat.pos_set(
		BASE_LEFT, BASE_TOP, 48,
		PLAYFIELD_LEFT, (PLAYFIELD_RIGHT + (BAT_W * 2)),
		PLAYFIELD_TOP, (PLAYFIELD_BOTTOM - (BAT_H * 3))
	);
	ent_still_or_wave.hitbox_set(
		((GIRL_W / 4) * 1), ((GIRL_H / 8) * 1),
		((GIRL_W / 4) * 3), ((GIRL_H / 3) * 2)
	);
	// Note that [ent_attack] doesn't receive a hitbox!
	ent_bat.hitbox_set(
		((BAT_W / 6) * 1), ((BAT_H / 4) * 1),
		((BAT_W / 6) * 5), ((BAT_H / 4) * 3)
	);

	boss_phase = 0;
	boss_phase_frame = 0;
	boss_hp = 14;
	hud_hp_first_white = 10;
	hud_hp_first_redwhite = 6;
	random_seed = frame_rand;
	palette_set_grayscale(boss_post_defeat_palette, 0x0, col, comp);
}

void elis_free(void)
{
	ent_free();
}

bool16 wave_teleport(screen_x_t target_left, screen_y_t target_top)
{
	ent_attack_sync_with_still_or_wave();

	// Wave sprite
	if(boss_phase_frame == 20) {
		graph_accesspage_func(1);
		girl_bg_put(1);
		graph_accesspage_func(0);
		ent_still_or_wave.move_lock_and_put_image_8(C_WAVE_1);
		ent_still_or_wave.hitbox_orb_inactive = true;
	} else if(boss_phase_frame == 28) {
		girl_bg_put(1);
		ent_still_or_wave.move_lock_and_put_image_8(C_WAVE_2);
		ent_still_or_wave.hitbox_orb_inactive = true;
	} else if(boss_phase_frame == 36) {
		ent_still_or_wave.hitbox_orb_inactive = true;
		goto put_wave_3;
	} else if(boss_phase_frame == 44) {
		ent_still_or_wave.hitbox_orb_inactive = true;
		egc_copy_rect_1_to_0_16(
			ent_still_or_wave.cur_left,
			ent_still_or_wave.cur_top,
			GIRL_W,
			GIRL_H
		);
	} else if(boss_phase_frame == 52) {
		ent_still_or_wave.hitbox_orb_inactive = true;
		ent_still_or_wave.pos_cur_set(target_left, target_top);
		girl_bg_snap(1);
	put_wave_3:
		girl_bg_put(1); // unnecessary
		ent_still_or_wave.move_lock_and_put_image_8(C_WAVE_3);
	} else if(boss_phase_frame == 60) {
		ent_still_or_wave.hitbox_orb_inactive = true;
		girl_bg_put(1);
		ent_still_or_wave.move_lock_and_put_image_8(C_WAVE_2);
	} else if(boss_phase_frame == 68) {
		ent_still_or_wave.hitbox_orb_inactive = true;
		girl_bg_put(1);
		ent_still_or_wave.move_lock_and_put_image_8(C_WAVE_1);
	} else if(boss_phase_frame == 76) {
		ent_still_or_wave.hitbox_orb_inactive = false;
		graph_accesspage_func(1);
		ent_still_or_wave.move_lock_and_put_image_8(C_STILL);
		graph_accesspage_func(0);
		ent_still_or_wave.move_lock_and_put_image_8(C_STILL);
	} else if(boss_phase_frame > 80) {
		boss_phase_frame = 0;
		return true;
	}

	// Stars
	if((boss_phase_frame % 4) != 0) {
		return false;
	}

	enum {
		STAR_COUNT = 5,
		STAR_OFFSET_X = (GIRL_W / 4),
		STAR_OFFSET_Y = (GIRL_H / 3),
		STAR_AREA_W = (STAR_OFFSET_X + GIRL_W + STAR_OFFSET_X),
		STAR_AREA_H = (STAR_OFFSET_Y + GIRL_H),
	};
	extern struct {
		screen_x_t left[STAR_COUNT];
		screen_y_t top[STAR_COUNT];

		static screen_x_t random_left(void) {
			return (ent_still_or_wave.cur_left + (rand() % STAR_AREA_W));
		}
		static screen_y_t random_top(void) {
			return (ent_still_or_wave.cur_top + (rand() % STAR_AREA_H));
		}
	} stars;

	for(int i = 0; i < STAR_COUNT; i++) {
		if(boss_phase_frame > 4) {
			egc_copy_rect_1_to_0_16_word_w(stars.left[i], stars.top[i], 8, 8);
		}
		if((boss_phase_frame < 40) || (boss_phase_frame > 52)) {
			stars.left[i] = (stars.random_left() - STAR_OFFSET_X);
			stars.top[i] = (stars.random_top() - STAR_OFFSET_Y);
		} else {
			stars.left[i] = (stars.left[i] + (
				(stars.random_left() - STAR_OFFSET_X - stars.left[i]) / 3
			));
			stars.top[i] = (stars.top[i] + (
				(stars.random_top() - STAR_OFFSET_Y - stars.top[i]) / 3
			));
		}
		if(boss_phase_frame < 68) {
			shape8x8_star_put(stars.left[i], stars.top[i], 2);
		}
	}
	return false;
}

#define select_for_rank elis_select_for_rank
#include "th01/main/select_r.cpp"
