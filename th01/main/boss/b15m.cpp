/// Makai Stage 15 Boss - Elis
/// --------------------------

#include <stddef.h>
#include "platform.h"
#include "decomp.hpp"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th01/v_colors.hpp"
#include "th01/math/area.hpp"
#include "th01/math/dir.hpp"
#include "th01/math/subpixel.hpp"
extern "C" {
#include "th01/math/vector.hpp"
#include "th01/hardware/egc.h"
#include "th01/hardware/graph.h"
#include "th01/formats/pf.hpp"
#include "th01/formats/grc.hpp"
#include "th01/formats/ptn.hpp"
#include "th01/main/entity.hpp"
#include "th01/snd/mdrv2.h"
#include "th01/main/playfld.hpp"
#include "th01/main/vars.hpp"
#include "th01/main/boss/entity_a.hpp"
}
#include "th01/shiftjis/fns.hpp"
#undef MISSILE_FN
// Stuffing float constants at the end of a string to work around alignment
// limitations… how disgusting.
#define MISSILE_FN "boss3_m.ptn\x00\x00\x00\xC8\x43\x00\x00\x20\x44\x9A\x99\x99\x99\x99\x99\xA9\x3F"
#include "th01/sprites/pellet.h"
#include "th01/main/shape.hpp"
#include "th01/main/particle.hpp"
#include "th01/main/boss/boss.hpp"
#include "th01/main/boss/palette.hpp"
#include "th01/main/bullet/laser_s.hpp"
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

enum elis_colors_t {
	COL_FX = 4,
};

// State
// -----

#define pattern_state	elis_pattern_state
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
// -----

// Patterns
// --------
static const int CHOOSE_NEW = 0;

extern union {
	int angle_range; // ACTUAL TYPE: unsigned char
	int speed_multiplied_by_8;
} pattern_state;
// --------

// Entities
// --------

enum elis_form_t {
	F_GIRL = 0,
	F_BAT = 1,

	_elis_form_t_FORCE_INT16 = 0x7FFF,
};

enum elis_entity_t {
	// "Girl" sprites
	ENT_STILL_OR_WAVE = 0,
	ENT_ATTACK = 1,

	ENT_BAT = 2,
};

enum elis_entity_cel_t {
	// ENT_STILL_OR_WAVE
	C_STILL = 0,
	C_HAND = 1,
	C_WAVE_1 = 2,
	C_WAVE_2 = 3,
	C_WAVE_3 = 4,
	C_WAVE_4 = 5,
};

#define ent_still_or_wave	boss_entities[ENT_STILL_OR_WAVE]
#define ent_attack       	boss_entities[ENT_ATTACK]
#define ent_bat          	boss_entities[ENT_BAT]

inline void elis_ent_load(void) {
	ent_still_or_wave.load("boss5.bos", 0);
	ent_attack.load("boss5_2.bos", 1);
	ent_bat.load("boss5_3.bos", 2);
}

inline void elis_ent_free(void) {
	bos_entity_free(0);
	bos_entity_free(1);
	bos_entity_free(2);
}

inline void ent_sync(elis_entity_t dst, elis_entity_t src) {
	boss_entities[dst].pos_cur_set(
		boss_entities[src].cur_left, boss_entities[src].cur_top
	);
}

inline void ent_unput_and_put_both(elis_entity_t ent, elis_entity_cel_t cel) {
	void girl_bg_put(int unncessary_parameter_that_still_needs_to_be_1_or_2);

	graph_accesspage_func(1);
	girl_bg_put(ent + 1);
	boss_entities[ent].move_lock_and_put_image_8(cel);
	graph_accesspage_func(0);
	ent_still_or_wave.move_lock_and_put_image_8(cel);
}
// --------

// Form-relative coordinates
// -------------------------

inline screen_x_t form_center_x(elis_form_t form) {
	return (ent_still_or_wave.cur_left + (GIRL_W / 2));
}

inline screen_x_t girl_lefteye_x(void) {
	return (ent_still_or_wave.cur_left + 60);
}

inline screen_y_t girl_lefteye_y(void) {
	return (ent_still_or_wave.cur_top + 28);
}
// -------------------------

// Surround area
// -------------
// Common bullet spawn area around Elis.

static const pixel_t SURROUND_AREA_W = ((PLAYFIELD_W * 3) / 10);
static const pixel_t SURROUND_AREA_H = ((PLAYFIELD_H * 8) / 21);

inline screen_x_t surround_random_left(elis_entity_t relative_to) {
	return (
		(boss_entities[relative_to].cur_left + (rand() % SURROUND_AREA_W)) -
		((SURROUND_AREA_W - GIRL_W) / 2)
	);
}

inline screen_y_t surround_random_top(elis_entity_t relative_to) {
	return (
		(boss_entities[relative_to].cur_top + (rand() % SURROUND_AREA_H)) -
		(SURROUND_AREA_H - GIRL_H)
	);
}
// -------------

// .GRC entities
// -------------

enum elis_grc_cel_t {
	RIFT_CELS = 2,

	C_RIFT = 4,
	C_RIFT_last = (C_RIFT + RIFT_CELS - 1),
};

#define elis_grc_sloppy_unput(entities, i) { \
	grc_sloppy_unput(entities.left[i], entities.top[i]); \
}

#define elis_grc_put(entities, i, cel, col) { \
	grc_put_8(entities.left[i], entities.top[i], GRC_SLOT_BOSS_1, cel, col); \
}

#define rifts_update_and_render(rifts, start_frame, end_frame, tmp_cel) { \
	if( \
		(boss_phase_frame >= start_frame) && \
		(boss_phase_frame <= end_frame) && \
		((boss_phase_frame % 4) == 0) \
	) { \
		for(int i = 0; i < rifts.count(); i++) { \
			/* Unblit */ \
			if(boss_phase_frame > start_frame) { \
				elis_grc_sloppy_unput(rifts, i); \
			} \
			\
			/* Initialize */ \
			if( \
				((boss_phase_frame % 16) == ((i * 4) % 16)) || \
				(boss_phase_frame == start_frame) \
			) { \
				rifts.left[i] = surround_random_left(ENT_STILL_OR_WAVE); \
				rifts.top[i] = surround_random_top(ENT_STILL_OR_WAVE); \
			} \
			\
			/* Render */ \
			if(boss_phase_frame < end_frame) { \
				tmp_cel = (rand() % RIFT_CELS); \
				elis_grc_put(rifts, i, (C_RIFT + cel), COL_FX); \
			} \
		} \
		mdrv2_se_play(7); \
	} \
}
// -------------

// .PTN
// ----

static const main_ptn_slot_t PTN_SLOT_BG_ENT = PTN_SLOT_BOSS_1;
static const main_ptn_slot_t PTN_SLOT_MISSILE = PTN_SLOT_BOSS_2;
// ----

#define bg_func_init(left, top, entity_src) { \
	ent_sync(ENT_ATTACK, ENT_STILL_OR_WAVE); \
	if(entity_src == (ENT_STILL_OR_WAVE + 1)) { \
		left = ent_still_or_wave.cur_left; \
		top = ent_still_or_wave.cur_top; \
	} else if(entity_src == (ENT_ATTACK + 1)) { \
		left = ent_attack.cur_left; \
		top = ent_attack.cur_top; \
	} \
}

void girl_bg_snap(int unncessary_parameter_that_still_needs_to_be_1_or_2)
{
	int ptn_x;
	int ptn_y;
	screen_x_t left;
	screen_y_t top;
	int image;

	bg_func_init(left, top, unncessary_parameter_that_still_needs_to_be_1_or_2);

	image = 0;
	ptn_snap_rect_from_1_8(
		left, top, GIRL_W, GIRL_H, PTN_SLOT_BG_ENT, image, ptn_x, ptn_y
	);
}

void girl_bg_put(int unncessary_parameter_that_still_needs_to_be_1_or_2)
{
	int ptn_x;
	int ptn_y;
	screen_x_t left;
	screen_y_t top;
	int image = 0;

	bg_func_init(left, top, unncessary_parameter_that_still_needs_to_be_1_or_2);
	ptn_put_rect_noalpha_8(
		left, top, GIRL_W, GIRL_H, PTN_SLOT_BG_ENT, image, ptn_x, ptn_y
	);
}

void elis_load(void)
{
	pellet_interlace = true;
	Pellets.unknown_seven = 7;
	elis_ent_load();
	grc_load(GRC_SLOT_BOSS_1, "boss5_gr.grc");
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
	elis_ent_free();
	grc_free(GRC_SLOT_BOSS_1);
	ptn_free(PTN_SLOT_BG_ENT);
	ptn_free(PTN_SLOT_MISSILE);
}

bool16 wave_teleport(screen_x_t target_left, screen_y_t target_top)
{
	ent_sync(ENT_ATTACK, ENT_STILL_OR_WAVE);

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
		girl_bg_put(1);
		ent_still_or_wave.move_lock_and_put_image_8(C_WAVE_3);
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

	extern CEntities<5> stars;

	for(int i = 0; i < stars.count(); i++) {
		if(boss_phase_frame > 4) {
			egc_copy_rect_1_to_0_16_word_w(stars.left[i], stars.top[i], 8, 8);
		}
		if((boss_phase_frame < 40) || (boss_phase_frame > 52)) {
			stars.left[i] = surround_random_left(ENT_STILL_OR_WAVE);
			stars.top[i] = surround_random_top(ENT_STILL_OR_WAVE);
		} else {
			stars.left[i] = (stars.left[i] + (
				(surround_random_left(ENT_STILL_OR_WAVE) - stars.left[i]) / 3
			));
			stars.top[i] = (stars.top[i] + (
				(surround_random_top(ENT_STILL_OR_WAVE) - stars.top[i]) / 3
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

int pattern_11_lasers_across(void)
{
	enum {
		INTERVAL = 10,
	};

	#define circle_center_x	form_center_x(F_GIRL)
	#define circle_center_y	(ent_still_or_wave.cur_top + (GIRL_H / 3))

	#define circle_radius	pattern0_circle_radius
	#define direction    	pattern0_direction

	extern pixel_t circle_radius;
	extern bool16 direction; // ACTUAL TYPE: x_direction_t
	double target_left;
	double target_y;

	if(boss_phase_frame == 50) {
		direction = (rand() % 2);
		ent_unput_and_put_both(ENT_STILL_OR_WAVE, C_HAND);
		select_for_rank(pattern_state.speed_multiplied_by_8,
			(to_sp(6.25f) / 2),
			(to_sp(6.875f) / 2),
			(to_sp(7.5f) / 2),
			(to_sp(8.125f) / 2)
		);
	} else if(boss_phase_frame == 60) {
		shape_circle_put(
			circle_center_x, circle_center_y, (GIRL_W / 4), COL_FX, 0x02
		);
		circle_radius = (GIRL_W / 4);
	} else if(
		(boss_phase_frame < 120) &&
		(boss_phase_frame > 60) &&
		((boss_phase_frame % 2) == 0)
	) {
		shape_circle_sloppy_unput(
			circle_center_x, circle_center_y, circle_radius, 0x02
		);
		circle_radius += 8;
		shape_circle_put(
			circle_center_x, circle_center_y, circle_radius, COL_FX, (
				(boss_phase_frame < 100) ? 0x02 :
				(boss_phase_frame < 110) ? 0x08 :
				0x20
			)
		);
	} else if(boss_phase_frame == 120) {
		shape_circle_sloppy_unput(
			circle_center_x, circle_center_y, circle_radius, 0x20
		);
	} else if(boss_phase_frame == 150) {
		ent_unput_and_put_both(ENT_STILL_OR_WAVE, C_STILL);
	}

	if((boss_phase_frame >= 70) && ((boss_phase_frame % INTERVAL) == 0)) {
		#undef RES_Y
		#define RES_Y *reinterpret_cast<float near*>(0x13ED)

		if(direction == X_RIGHT) {
			target_left = (PLAYFIELD_LEFT +
				(((boss_phase_frame - 70) / INTERVAL) * (PLAYFIELD_W / 10))
			);
		} else {
			target_left = (PLAYFIELD_RIGHT -
				(((boss_phase_frame - 70) / INTERVAL) * (PLAYFIELD_W / 10))
			);
		}
		target_y = RES_Y;
		shootout_laser_safe(boss_phase_frame / INTERVAL).spawn(
			girl_lefteye_x(),
			girl_lefteye_y(),
			target_left,
			target_y,
			pattern_state.speed_multiplied_by_8,
			V_WHITE,
			25,
			4
		);
		mdrv2_se_play(6);

		// <= instead of < is why this pattern actually fires 11 lasers rather
		// than the 10 you might guess from looking at the target calculation
		// above.

		/* TODO: Proper decompilation, once data can be emitted here:
		* ----------------------------------------------------------
		if(
			((direction == X_RIGHT) && (target_left >= PLAYFIELD_RIGHT)) ||
			((direction == X_LEFT) && (target_left <= PLAYFIELD_LEFT))
		)
		* ----------------------------------------------------------
		* Performing arithmetic or comparisons between a double (target_left)
		* and a float (PLAYFIELD_RIGHT) variable always FLDs the float first,
		* before emitting the corresponding FPU instruction with the double,
		* which is not what we want here.
		*/
		if(direction != X_RIGHT) {
			goto firing_left;
		}
		asm {
			fld  	qword ptr [bp-8];
			fcomp	dword ptr [0x13F1];
			fstsw	word ptr [bp-18];
			FWAIT_EMU;
			mov  	ax, word ptr [bp-18];
			sahf;
		}
		if(!FLAGS_CARRY) {
			goto done;
		}
firing_left:
		if((direction == X_LEFT) && (target_left <= PLAYFIELD_LEFT)) {
done:
			boss_phase_frame = 0;
			return CHOOSE_NEW;
		}
	}
	return 1;

	#undef direction
	#undef circle_radius
	#undef circle_center_y
	#undef circle_center_x
}

int pattern_random_downwards_missiles(void)
{
	#define rifts pattern1_rifts

	extern CEntities<5> rifts;
	int cel; // ACTUAL TYPE: elis_grc_cel_t
	pixel_t velocity_x;
	pixel_t velocity_y;
	unsigned char angle;

	if(boss_phase_frame == 50) {
		ent_unput_and_put_both(ENT_STILL_OR_WAVE, C_HAND);
		select_for_rank(pattern_state.angle_range, 0x0F, 0x15, 0x19, 0x1D);
	}

	// That's quite the brave placement for this branch...
	if((boss_phase_frame > 60) && ((boss_phase_frame % 3) == 0)) {
		int i = (rand() % rifts.count());
		angle = (
			(rand() % pattern_state.angle_range) -
			((pattern_state.angle_range - 0x01) / 2) +
			0x40
		);
		vector2(velocity_x, velocity_y, 7, angle);
		Missiles.add(rifts.left[i], rifts.top[i], velocity_x, velocity_y);
	}

	rifts_update_and_render(rifts, 60, 160, cel);

	if(boss_phase_frame > 170) {
		boss_phase_frame = 0;
		return CHOOSE_NEW;
	}
	return 2;

	#undef rifts
}
