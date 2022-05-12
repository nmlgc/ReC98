/// Makai Stage 15 Boss - Elis
/// --------------------------

#include <stddef.h>
#include "platform.h"
#include "pc98.h"
#include "planar.h"
#include "master.hpp"
#include "th01/v_colors.hpp"
#include "th01/math/area.hpp"
#include "th01/math/dir.hpp"
#include "th01/math/polar.hpp"
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
	pellet_group_t group;
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

// [unput_0] should theoretically always be `true`. Making sure that both VRAM
// pages are identical avoids visual glitches from blitting cels with different
// transparent areas on top of each other (see: Mima's third arm)… but you can
// always just *assume* rather than ensure, right? :zunpet:
inline void ent_unput_and_put_both(
	elis_entity_t ent, elis_entity_cel_t cel, bool unput_0 = true
) {
	void girl_bg_put(int unncessary_parameter_that_still_needs_to_be_1_or_2);

	graph_accesspage_func(1);
	girl_bg_put(ent + 1);
	boss_entities[ent].move_lock_and_put_image_8(cel);
	graph_accesspage_func(0);
	if(unput_0) {
		girl_bg_put(ent + 1);
	}
	boss_entities[ent].move_lock_and_put_image_8(cel);
}
// --------

// Form-relative coordinates
// -------------------------

inline screen_x_t form_center_x(elis_form_t form) {
	return (ent_still_or_wave.cur_left + (GIRL_W / 2));
}

inline screen_y_t form_center_y(elis_form_t form) {
	return (ent_still_or_wave.cur_top + (GIRL_H / 2));
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

// Shared big circle
// -----------------
// Concrete circle structures must look like this: {
// 	unsigned char angle;
// 	int frame;
//
// 	screen_x_t center_x(void) { return …; };
// 	screen_y_t center_y(void) { return …; };
// };

static const pixel_t BIGCIRCLE_RADIUS = ((GIRL_W * 2) / 2);

#define bigcircle_sloppy_unput(bigcircle) { \
	shape_circle_sloppy_unput( \
		bigcircle.center_x(), bigcircle.center_y(), BIGCIRCLE_RADIUS, 0x01 \
	); \
}

#define bigcircle_put_arc(bigcircle, angle_start, angle_end, col) { \
	shape_ellipse_arc_put( \
		bigcircle.center_x(), \
		bigcircle.center_y(), \
		BIGCIRCLE_RADIUS, \
		BIGCIRCLE_RADIUS, \
		col, \
		0x01, \
		angle_start, \
		angle_end \
	); \
}

#define bigcircle_put(bigcircle, col) { \
	bigcircle_put_arc(bigcircle, 0x00, 0xFF, col); \
}

#define bigcircle_put_dot(bigcircle, offset_start, offset_end, col) { \
	bigcircle_put_arc( \
		bigcircle, \
		(bigcircle.angle + offset_start), \
		(bigcircle.angle + offset_end), \
		col \
	); \
}

#define bigcircle_is_summon_frame(start_frame) ( \
	(boss_phase_frame >= start_frame) && ((boss_phase_frame % 2) == 0) \
)

#define bigcircle_summon_done(bigcircle) \
	(bigcircle.angle >= (0x100 / 4))

#define bigcircle_summon_update_and_render(bigcircle, q4_offset_end) { \
	bigcircle_put_dot(bigcircle, 0x00, q4_offset_end, V_WHITE); \
	bigcircle_put_dot(bigcircle, 0x40, 0x42, V_WHITE); \
	bigcircle_put_dot(bigcircle, 0x80, 0x82, V_WHITE); \
	bigcircle_put_dot(bigcircle, 0xC0, 0xC2, V_WHITE); \
	\
	bigcircle.angle += 0x02; \
}

// All of the summon animation macros below are forced to be used inside an
// `if` statement, returning a non-zero value when the flash animation is done.
// MODDERS: Just turn them into regular functions.

// Renders a frame of the summon animation.
#define bigcircle_summon(bigcircle, start_frame, q4_offset_end) \
	boss_phase_frame == start_frame) { \
		mdrv2_se_play(8); \
	} \
	bigcircle_summon_update_and_render(bigcircle, q4_offset_end); \
	if(bigcircle_summon_done(bigcircle) /* return value */

// Renders a frame of the summon and flash animation.
#define bigcircle_summon_and_flash(bigcircle, start_frame, q4_offset_end) \
	bigcircle_is_summon_frame(start_frame) && (bigcircle.frames == 0)) { \
		if(bigcircle_summon(bigcircle, start_frame, q4_offset_end)) { \
			bigcircle_sloppy_unput(bigcircle);	/* (redundant) */ \
			\
			/* Also looks redundant, but we might have unblitted parts of */ \
			/* the circle during the summon animation… */ \
			bigcircle_put(bigcircle, V_WHITE); \
			\
			bigcircle.frames = 1; \
			ent_unput_and_put_both(ENT_STILL_OR_WAVE, C_STILL); \
		} \
	} else if((bigcircle.frames != 0) && (bigcircle.frames < 40)) { \
		bigcircle.frames++; \
		if((bigcircle.frames % 8) == 0) { \
			bigcircle_sloppy_unput(bigcircle);	/* (redundant) */ \
			bigcircle_put(bigcircle, COL_FX); \
		} else if((bigcircle.frames % 8) == 4) { \
			bigcircle_sloppy_unput(bigcircle);	/* (redundant) */ \
			bigcircle_put(bigcircle, V_WHITE); \
		} \
	} else if(bigcircle.frames != 0 /* return value */

// Circle around the Star of David
struct starcircle_t {
	unsigned char angle;
	int frames;

	screen_x_t center_x(void) { return form_center_x(F_GIRL); }
	screen_y_t center_y(void) { return form_center_y(F_GIRL); }
};
// -----------------

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
		ent_unput_and_put_both(ENT_STILL_OR_WAVE, C_HAND, false);
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
		ent_unput_and_put_both(ENT_STILL_OR_WAVE, C_STILL, false);
	}

	if((boss_phase_frame >= 70) && ((boss_phase_frame % INTERVAL) == 0)) {
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
		if(
			((direction == X_RIGHT) && (target_left >= PLAYFIELD_RIGHT)) ||
			((direction == X_LEFT) && (target_left <= PLAYFIELD_LEFT))
		) {
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
		ent_unput_and_put_both(ENT_STILL_OR_WAVE, C_HAND, false);
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

int pattern_pellets_along_circle(void)
{
	#define circle	pattern2_circle

	extern starcircle_t circle;
	screen_x_t left;
	screen_y_t top;

	if(boss_phase_frame < 10) {
		circle.frames = 0;
	}
	if(boss_phase_frame == 50) {
		ent_unput_and_put_both(ENT_STILL_OR_WAVE, C_HAND, false);
		circle.angle = 0x00;
		select_for_rank(reinterpret_cast<int &>(pattern_state.group),
			PG_1_AIMED,
			PG_1_RANDOM_NARROW_AIMED,
			PG_3_SPREAD_WIDE_AIMED,
			// This will spawn (32 * 5) = 160 pellets, which is 60 more than
			// the original PELLET_COUNT. As a result, Elis will only ever fire
			// up to 20 of these spreads on Lunatic, rather than the coded 32.
			PG_5_SPREAD_NARROW_AIMED
		);
	}

	// Adding a `double` value < 1.0 to an integer is still a NOP. That leads
	// to the start and end angle for quadrant IV being identical, and nothing
	// being drawn there as a result. Hard to call it a ZUN bug though, since
	// this is the only function where this happens. But if it this was
	// intended after all, why not just remove the call for quadrant IV?!
	if(bigcircle_summon_and_flash(circle, 60, 0.05)) {
		bigcircle_sloppy_unput(circle);
		circle.angle = 0x00;
		for(int i = 0; i < 32; i++) {
			// lefteye?!
			left = polar_x(girl_lefteye_x(), BIGCIRCLE_RADIUS, circle.angle);

			top = polar_y(
				form_center_y(F_GIRL), BIGCIRCLE_RADIUS, circle.angle
			);
			Pellets.add_group(left, top, pattern_state.group, to_sp(0.25f));
			circle.angle += (0x100 / 32);
		}
		boss_phase_frame = 0;
		circle.frames = 0;
		return CHOOSE_NEW;
	}
	return 3;

	#undef circle
}

// Draws a line from [angle_1] to [angle_2] on the star circle around Elis.
void pascal near starcircle_line_put(
	unsigned char angle_1, unsigned char angle_2, int col
)
{
	screen_x_t p1_x = polar_x(form_center_x(F_GIRL), BIGCIRCLE_RADIUS, angle_1);
	screen_y_t p1_y = polar_y(form_center_y(F_GIRL), BIGCIRCLE_RADIUS, angle_1);
	screen_x_t p2_x = polar_x(form_center_x(F_GIRL), BIGCIRCLE_RADIUS, angle_2);
	screen_y_t p2_y = polar_y(form_center_y(F_GIRL), BIGCIRCLE_RADIUS, angle_2);
	graph_r_line(p1_x, p1_y, p2_x, p2_y, col);
}

void pascal near starcircle_line_unput(
	unsigned char angle_1, unsigned char angle_2
)
{
	screen_x_t p1_x = polar_x(form_center_x(F_GIRL), BIGCIRCLE_RADIUS, angle_1);
	screen_y_t p1_y = polar_y(form_center_y(F_GIRL), BIGCIRCLE_RADIUS, angle_1);
	screen_x_t p2_x = polar_x(form_center_x(F_GIRL), BIGCIRCLE_RADIUS, angle_2);
	screen_y_t p2_y = polar_y(form_center_y(F_GIRL), BIGCIRCLE_RADIUS, angle_2);
	graph_r_line_unput(p1_x, p1_y, p2_x, p2_y);
}

int phase_1(int id)
{
	switch(id) {
	case CHOOSE_NEW:
		return (rand() % 4);
	case 1: return pattern_11_lasers_across();
	case 2: return pattern_random_downwards_missiles();
	case 3: return pattern_pellets_along_circle();
	}
	return CHOOSE_NEW;
}
